// Config.cpp
#include "Config.h"
#include <sstream>
#include <vector>

Config getIndicesFromHeader(std::string header) {
    Config cfg;
    std::stringstream ss(header);
    std::string cell;
    int currentIdx = 0;

    while (std::getline(ss, cell, ',')) {
        if (cell == "title") cfg.titleIdx = currentIdx;
        else if (cell == "genres") cfg.genresIdx = currentIdx;
        else if (cell == "imdb_score") cfg.imdbIdx = currentIdx;
        else if (cell == "tmdb_score") cfg.tmdbIdx = currentIdx;
        currentIdx++;
    }
    return cfg;
}