#ifndef ARCHIVO_HPP
#define ARCHIVO_HPP

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class Archivo {
public:
    std::string nombre;
    std::string extension;
    int tamaño;
    Archivo(std::string nombre, std::string extension, int tamaño) : nombre(nombre), extension(extension), tamaño(tamaño) {}
};


#endif //  ARCHIVO_HPP