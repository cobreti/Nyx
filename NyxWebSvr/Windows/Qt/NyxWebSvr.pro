#-------------------------------------------------
#
# Project created by QtCreator 2013-12-31T21:57:28
#
#-------------------------------------------------

QT       -= gui

TARGET = NyxWebSvr
TEMPLATE = lib
CONFIG += staticlib
# DEFINES += STDCONSTRUCT
CONFIG += c++11


INCLUDEPATH += ../../../include
INCLUDEPATH += ../../../include/Win32
INCLUDEPATH += ../../../include/NyxNet
INCLUDEPATH += ../../../include/NyxWebSvr
INCLUDEPATH += ../../../include/Win32/NyxNet
INCLUDEPATH += ../../Source

CONFIG(debug, debug | release) {
    OBJECTS_DIR = ./Debug
    DESTDIR = ../../../Lib/Qt/Debug_64
}

CONFIG(release, debug | release) {
    OBJECTS_DIR = ./Release
    DESTDIR = ../../../Lib/Qt/Release_64
}

HEADERS += \
    ../../../include/NyxWebSvr/ConnHttpHandler.hpp \
    ../../../include/NyxWebSvr/ConnListener.hpp \
    ../../../include/NyxWebSvr/ConnStream.hpp \
    ../../../include/NyxWebSvr/Header.hpp \
    ../../../include/NyxWebSvr/HttpHandler.hpp \
    ../../../include/NyxWebSvr/HttpHandlersTable.hpp \
    ../../../include/NyxWebSvr/HttpServer.hpp \
    ../../../include/NyxWebSvr/Module.hpp \
    ../Source/Module_Impl.hpp \
    ../../Source/ConnHandler_Impl.hpp \
    ../../Source/ConnHttpHandler_Impl.hpp \
    ../../Source/ConnListener_Impl.hpp \
    ../../Source/Header_Impl.hpp \
    ../../Source/HttpHandlersTable_Impl.hpp \
    ../../Source/HttpServer_Impl.hpp
#    ../../Source/HttpsServer_Impl.hpp

SOURCES += \
    ../Source/Module_Impl.cpp \
    ../../Source/ConnHandler_Impl.cpp \
    ../../Source/ConnHttpHandler_Impl.cpp \
    ../../Source/ConnListener_Impl.cpp \
    ../../Source/Header_Impl.cpp \
    ../../Source/HttpHandlersTable_Impl.cpp \
    ../../Source/HttpServer_Impl.cpp

