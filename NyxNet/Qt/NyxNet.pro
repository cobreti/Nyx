#-------------------------------------------------
#
# Project created by QtCreator 2013-12-31T21:57:28
#
#-------------------------------------------------

QT       -= gui

TARGET = NyxNet
TEMPLATE = lib
CONFIG += staticlib
# DEFINES += STDCONSTRUCT
CONFIG += c++11


INCLUDEPATH += ../../include
INCLUDEPATH += ../../include/NyxNet
INCLUDEPATH += ../Source

win32 {
    INCLUDEPATH += ../../include/Win32
    INCLUDEPATH += ../../include/Win32/NyxNet
}

HEADERS += \
    ../../include/OSX/NyxNet/NyxNetTypes.hpp \
    ../../include/NyxNet/NyxNet.hpp \
    ../../include/NyxNet/NyxNetAddress.hpp \
    ../../include/NyxNet/NyxNetConnection.hpp \
    ../../include/NyxNet/NyxNetConnectionHandler.hpp \
    ../../include/NyxNet/NyxNetConnectionsTable.hpp \
    ../../include/NyxNet/NyxNetModule.hpp \
    ../../include/NyxNet/NyxNetNxConnection.hpp \
    ../../include/NyxNet/NyxNetNxConnectionHandler.hpp \
    ../../include/NyxNet/NyxNetNxDataHeader.hpp \
    ../../include/NyxNet/NyxNetNxStreamRW.hpp \
    ../../include/NyxNet/NyxNetPipeServer.hpp \
    ../../include/NyxNet/NyxNetPipeSocket.hpp \
    ../../include/NyxNet/NyxNetPipeSocketReader.hpp \
    ../../include/NyxNet/NyxNetPipeSocketWriter.hpp \
    ../../include/NyxNet/NyxNetPipeTraceOutput.hpp \
    ../../include/NyxNet/NyxNetServer.hpp \
    ../../include/NyxNet/NyxNetServerListener.hpp \
    ../../include/NyxNet/NyxNetSocket.hpp \
    ../../include/NyxNet/NyxNetSocketListener.hpp \
    ../../include/NyxNet/NyxNetSSLTcpIpSocket.hpp \
    ../../include/NyxNet/NyxNetTcpIpServer.hpp \
    ../../include/NyxNet/NyxNetTcpIpSocket.hpp \
    ../../include/NyxNet/NyxNetTcpIpTraceOutput.hpp \
    ../../include/NyxNet/NyxNetTraceFlags.hpp \
    ../../include/NyxNet/NyxNetTraceStreamWriter.hpp

HEADERS += \
    ../Source/NyxNetConnectionsTable_Impl.h \
    ../Source/NyxNetConnectionsTable_Impl.hpp \
    ../Source/NyxNetNxConnection_Impl.hpp \
    ../Source/NyxNetPipeTraceOutput_Impl.hpp \
    ../Source/NyxNetTcpIpTraceOutput_Impl.hpp

win32 {
    HEADERS += \
        ../Windows/Source/NyxNetModule_Impl.hpp \
        ../Windows/Source/NyxNetPipeClientConn.hpp \
        ../Windows/Source/NyxNetPipeServer_Impl.hpp \
        ../Windows/Source/NyxNetPipeSocketReader_Impl.hpp \
        ../Windows/Source/NyxNetPipeSocketWriter_Impl.hpp \
        ../Windows/Source/NyxNetSSLTcpIpSocket_Impl.hpp \
        ../Windows/Source/NyxNetTcpIpClientConn.hpp \
        ../Windows/Source/NyxNetTcpIpServer_Impl.hpp \
        ../Windows/Source/NyxNetTcpIpSocket_Impl.hpp
}

SOURCES += \
    ../Source/NyxNetConnectionsTable_Impl.cpp \
    ../Source/NyxNetNxConnection_Impl.cpp \
    ../Source/NyxNetPipeTraceOutput_Impl.cpp \
    ../Source/NyxNetTcpIpTraceOutput_Impl.cpp \
    ../Source/NyxNetTraceStreamWriter.cpp


win32 {
    SOURCES += \
        ../Windows/Source/NyxNetModule_Impl.cpp \
        ../Windows/Source/NyxNetPipeClientConn.cpp \
        ../Windows/Source/NyxNetPipeServer_Impl.cpp \
        ../Windows/Source/NyxNetPipeSocketReader_Impl.cpp \
        ../Windows/Source/NyxNetPipeSocketWriter_Impl.cpp \
        ../Windows/Source/NyxNetSSLTcpIpSocket_Impl.cpp \
        ../Windows/Source/NyxNetTcpIpClientConn.cpp \
        ../Windows/Source/NyxNetTcpIpServer_Impl.cpp \
        ../Windows/Source/NyxNetTcpIpSocket_Impl.cpp \
        ../Windows/Source/NyxNetTraceFlags.cpp
}

CONFIG(debug, debug | release) {
    OBJECTS_DIR = ./Debug
    DESTDIR = ../../Lib/Qt/Debug_64
}

CONFIG(release, debug | release) {
    OBJECTS_DIR = ./Release
    DESTDIR = ../../Lib/Qt/Release_64
}

