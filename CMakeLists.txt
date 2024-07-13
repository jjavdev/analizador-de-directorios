cmake_minimum_required(VERSION 3.11)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v4.0.0
  GIT_PROGRESS TRUE)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# ------------------------------------------------------------------------------

project(analizador LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(analizador main.cpp)

# Incluir la carpeta que contiene los archivos de encabezado de tu proyecto
target_include_directories(analizador PRIVATE tu_directorio_de_includes)

# Enlazar ftxui a tu ejecutable
target_link_libraries(analizador PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component)

# Agregar la generación del archivo HTML como parte de un comando independiente
add_custom_command(
    OUTPUT stats.html
    COMMAND ${CMAKE_COMMAND} -E echo "<html><body><h1>Estadísticas del directorio</h1></body></html>" > stats.html
    COMMENT "Generando archivo HTML con estadísticas del directorio"
)

add_custom_target(generar_html_stats DEPENDS stats.html)

include(CTest)
enable_testing()
