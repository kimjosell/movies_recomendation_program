#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>

class Movie {
private:
    std::string title;
    std::vector<int> genreVector;
    float imdbScore;

public:
    // Constructor
    Movie(std::string t, std::vector<int> g, float score)
        : title(t), genreVector(g), imdbScore(score) {
    }

    // Getters
    std::string getTitle() const { return title; }
    const std::vector<int>& getGenreVector() const { return genreVector; }
    float getScore() const { return imdbScore; }
};

#endif