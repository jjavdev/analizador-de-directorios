#ifndef LOGICA_HPP
#define LOGICA_HPP

#include "../datos/archivo.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

class Directorio
{
public:
    std::string nombre;
    std::vector<Archivo> archivos;
    std::vector<Directorio> subdirectorios;

    void mostrarEstructuraArbol() const
    {
        std::cout << nombre << " (Directorio)" << std::endl;
        for (const auto &archivo : archivos)
        {
            std::cout << "  - " << archivo.nombre << "." << archivo.extension << " (" << archivo.tamaño << " bytes)" << std::endl;
        }
        for (const auto &subdirectorio : subdirectorios)
        {
            subdirectorio.mostrarEstructuraArbol();
        }
    }

    void buscarArchivosPorNombreOExtension(const std::string &criterio) const
    {
        for (const auto &archivo : archivos)
        {
            if (archivo.nombre == criterio || archivo.extension == criterio)
            {
                std::cout << "Se encontró el archivo " << archivo.nombre << "." << archivo.extension << " en el directorio " << nombre << " con un tamaño de " << archivo.tamaño << " bytes." << std::endl;
            }
        }
        for (const auto &subdirectorio : subdirectorios)
        {
            subdirectorio.buscarArchivosPorNombreOExtension(criterio);
        }
    }

    void generarHTMLStats(std::ofstream &outputFile) const
    {
        outputFile << "<html><body>";
        outputFile << "<h1>Estadísticas del directorio: " << nombre << "</h1>";
        outputFile << "<h2>Archivos:</h2><ul>";
        for (const auto &archivo : archivos)
        {
            outputFile << "<li>" << archivo.nombre << " (" << archivo.extension << ") - " << archivo.tamaño << " bytes</li>"; // Corregir 'tamano' a 'tamaño'
        }
        outputFile << "</ul>";
        outputFile << "<h2>Subdirectorios:</h2><ul>";
        for (const auto &subdirectorio : subdirectorios)
        {
            outputFile << "<li>" << subdirectorio.nombre << "</li>";
        }
        outputFile << "</ul>";
        outputFile << "</body></html>";
    }
};

#endif //  LOGICA_HPP