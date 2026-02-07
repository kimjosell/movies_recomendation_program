// movies_recomendations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <algorithm>
#include "Config.h"
#include "lib/csv.hpp"

struct Movie {
    std::string title;
    std::vector<int> genreTokens;
    float similarity = 0.0f;
};

std::vector<std::string> parseGenresFromString(const std::string& genresStr) {
    std::vector<std::string> genres;
    std::regex genreRegex("'([^']+)'");
    std::sregex_iterator iter(genresStr.begin(), genresStr.end(), genreRegex);
    std::sregex_iterator end;
    
    while (iter != end) {
        genres.push_back((*iter)[1].str());
        ++iter;
    }
    
    return genres;
}

std::vector<int> parseToToken(std::vector<std::string>& movieGenres, std::vector<std::string>& masterGenres)
{
    std::unordered_map<std::string, int> genreToIndex;
    for (int i = 0; i < masterGenres.size(); ++i) {
        genreToIndex[masterGenres[i]] = i;
    }

    std::vector<int> tokens(masterGenres.size(), 0);

    for (const std::string& g : movieGenres) {
        if (genreToIndex.count(g)) {
            tokens[genreToIndex[g]] = 1;
        }
    }

    return tokens;
}

float calculateSimilarity(const std::vector<int>& v1, const std::vector<int>& v2) {
    float dotProduct = 0, normA = 0, normB = 0;
    for (size_t i = 0; i < v1.size(); i++) {
        dotProduct += v1[i] * v2[i];
        normA += v1[i] * v1[i];
        normB += v2[i] * v2[i];
    }
    if (normA == 0 || normB == 0) return 0;
    return dotProduct / (sqrt(normA) * sqrt(normB));
}

int main(int argc, char* argv[])
{

    if (argc < 4) {
        std::cerr << "Error: Thre are arguments that missing" << std::endl;
        std::cerr << "Use: " << argv[0] << " \"Movie 1\" \"Movie 2\" \"Movie 3\"" << std::endl;
        return 1;
    }

    std::vector<std::string> targetMovies;

    for (int i = 1; i < 4; ++i) {
        targetMovies.push_back(argv[i]);
    }

    std::cout << "Analizing preferences: " << std::endl;
    for (const auto& title : targetMovies) {
        std::cout << "- " << title << std::endl;
    }

    std::vector<std::string> masterGenres =
    {
        "action", "comedy", "drama", "scifi", "animation"
    };

    std::vector<int> userProfile(masterGenres.size(), 0);
    std::vector<std::string> foundTargets;
    
    csv::CSVReader readerForProfile("titles.csv");
    for (auto& row : readerForProfile) {
        std::string title = row["title"].get<>();
        
        for (const auto& targetMovie : targetMovies) {
            if (title.find(targetMovie) != std::string::npos) {
                std::string genresStr = row["genres"].get<>();
                std::vector<std::string> movieGenres = parseGenresFromString(genresStr);
                std::vector<int> tokens = parseToToken(movieGenres, masterGenres);
                
                for (size_t i = 0; i < tokens.size(); i++) {
                    userProfile[i] += tokens[i];
                }
                
                foundTargets.push_back(title);
                std::cout << "Founded: " << title << std::endl;
                break;
            }
        }
    }

    if (foundTargets.size() < 3) {
        std::cerr << "\nWarning the program just found: " << foundTargets.size() 
                  << " from the 3 movies" << std::endl;
    }

    std::cout << "\nUser profile's preferences: ";
    for (size_t i = 0; i < masterGenres.size(); i++) {
        if (userProfile[i] > 0) {
            std::cout << masterGenres[i] << "(" << userProfile[i] << ") ";
        }
    }
    std::cout << "\n\n";


    std::vector<Movie> allMovies;
    
    csv::CSVReader reader("titles.csv");
    for (auto& row : reader) {
        std::string title = row["title"].get<>();
        
        bool isTarget = false;
        for (const auto& target : foundTargets) {
            if (title == target) {
                isTarget = true;
                break;
            }
        }
        if (isTarget) continue;
        
        std::string genresStr = row["genres"].get<>();
        std::vector<std::string> movieGenres = parseGenresFromString(genresStr);
        std::vector<int> tokens = parseToToken(movieGenres, masterGenres);
        
        Movie movie;
        movie.title = title;
        movie.genreTokens = tokens;
        movie.similarity = calculateSimilarity(userProfile, tokens);
        
        if (movie.similarity > 0) {
            allMovies.push_back(movie);
        }
    }

    std::sort(allMovies.begin(), allMovies.end(), 
              [](const Movie& a, const Movie& b) {
                  return a.similarity > b.similarity;
              });

    std::cout << "=== RECOMENDATIONS ===" << std::endl;
    int count = 0;
    for (const auto& movie : allMovies) {
        if (count >= 3) break;
        
        std::cout << (count + 1) << ". " << movie.title 
                  << " (Similarity: " << (movie.similarity * 100) << "%)" << std::endl;
        
        std::cout << "   Genres: ";
        for (size_t i = 0; i < movie.genreTokens.size(); i++) {
            if (movie.genreTokens[i] > 0) {
                std::cout << masterGenres[i] << " ";
            }
        }
        std::cout << "\n" << std::endl;
        
        count++;
    }

    if (allMovies.empty()) {
        std::cout << "There program did not found any movie." << std::endl;
    }

    return 0;
}
