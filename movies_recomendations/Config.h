#ifndef CONFIG_H  // Estas son "Header Guards" para evitar errores de duplicación
#define CONFIG_H

#include <string>

struct Config {
    int titleIdx = -1;
    int genresIdx = -1;
    int imdbIdx = -1;
    int tmdbIdx = -1;

    // Puedes incluir una función para verificar si se cargó bien
    bool isValid() {
        return titleIdx != -1 && genresIdx != -1;
    }
};

// Declaramos la función que buscará los índices
Config getIndicesFromHeader(std::string header);

#endif