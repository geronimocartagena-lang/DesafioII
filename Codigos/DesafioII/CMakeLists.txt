cmake_minimum_required(VERSION 3.16)

project(DesafioII LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DesafioII main.cpp
    Lista.h
    Foto.cpp
    Foto.h
    Usuario.cpp
    Usuario.h
    Album.cpp
    Album.h
    Mensaje.cpp
    Mensaje.h
    Manejorecursos.cpp
    Manejorecursos.h
    Redsocial.cpp
    Redsocial.h


)

include(GNUInstallDirs)
install(TARGETS DesafioII
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
