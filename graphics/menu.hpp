#ifndef MENU_HPP
#define MENU_HPP

#include "../negocio/logica.hpp"
#include "../datos/archivo.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

namespace fs = std::filesystem; // Capa de Presentación
using namespace ftxui;

void mostrarMenu() {
    std::string directorioInicial;

    auto input = Input(&directorioInicial, "Ingrese la ruta del directorio");
    auto button = Button("Analizar Directorio", [&] {
        if (!fs::exists(directorioInicial) || !fs::is_directory(directorioInicial) || directorioInicial.find("C:\\") != 0) {
            directorioInicial = "Directorio no válido. Debe comenzar con C:\\";
            return;
        }

        Directorio raiz;
        raiz.nombre = directorioInicial;

        for (const auto &entry : fs::directory_iterator(directorioInicial)) {
            if (fs::is_regular_file(entry.path())) {
                raiz.archivos.emplace_back(entry.path().filename().string(), entry.path().extension().string(), fs::file_size(entry.path()));
            } else if (fs::is_directory(entry.path())) {
                Directorio subdirectorio;
                subdirectorio.nombre = entry.path().filename().string();
                raiz.subdirectorios.push_back(subdirectorio);
            }
        }

        // Crear la interfaz gráfica con ftxui.
        auto document = vbox({
            text(L"Estadísticas del directorio"),
            separator(),
            hbox({
                text(L"Archivos:"),
                text(std::to_wstring(raiz.archivos.size())), // Mostrar el número de archivos.
            }),
            separator(),
            hbox({
                text(L"Subdirectorios:"),
                text(std::to_wstring(raiz.subdirectorios.size())), // Mostrar el número de subdirectorios.
            }),
        });

        // Crear una pantalla interactiva y mostrar la interfaz.
        auto screen = ScreenInteractive::TerminalOutput();
        screen.Loop(Renderer([&] { return document; }));

        // Generar un HTML con estadísticas del directorio
        std::ofstream outputFile("stats.html");
        if (outputFile.is_open()) {
            raiz.generarHTMLStats(outputFile);
            outputFile.close();
            std::cout << "Archivo HTML generado correctamente." << std::endl;
        } else {
            std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
        }
    });

    auto container = Container::Vertical({
        input,
        button,
    });

    auto renderer = Renderer(container, [&] {
        return vbox({
            text(L"Ingrese la ruta del directorio a analizar:"),
            input->Render(),
            button->Render(),
        }) | border;
    });

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
}

#endif // MENU_HPP
