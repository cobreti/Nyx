#-------------------------------------------------
#
# Project created by QtCreator 2013-12-31T21:57:28
#
#-------------------------------------------------

QT       -= gui

TARGET = NyxNet
TEMPLATE = lib
CONFIG += staticlib



INCLUDEPATH += ../../../include
INCLUDEPATH += ../../../include/OSX
INCLUDEPATH += ../../../include/NyxNet
INCLUDEPATH += ../../../include/OSX/NyxNet
INCLUDEPATH += ../../Source

HEADERS += \
    ../../../include/OSX/NyxNet/NyxNetTypes.hpp \
    ../../../include/NyxNet/NyxNet.hpp \
    ../../../include/NyxNet/NyxNetAddress.hpp \
    ../../../include/NyxNet/NyxNetConnection.hpp \
    ../../../include/NyxNet/NyxNetConnectionHandler.hpp \
    ../../../include/NyxNet/NyxNetConnectionsTable.hpp \
    ../../../include/NyxNet/NyxNetModule.hpp \
    ../../../include/NyxNet/NyxNetNxConnection.hpp \
    ../../../include/NyxNet/NyxNetNxConnectionHandler.hpp \
    ../../../include/NyxNet/NyxNetNxDataHeader.hpp \
    ../../../include/NyxNet/NyxNetNxStreamRW.hpp \
    ../../../include/NyxNet/NyxNetPipeServer.hpp \
    ../../../include/NyxNet/NyxNetPipeSocket.hpp \
    ../../../include/NyxNet/NyxNetPipeSocketReader.hpp \
    ../../../include/NyxNet/NyxNetPipeSocketWriter.hpp \
    ../../../include/NyxNet/NyxNetPipeTraceOutput.hpp \
    ../../../include/NyxNet/NyxNetServer.hpp \
    ../../../include/NyxNet/NyxNetServerListener.hpp \
    ../../../include/NyxNet/NyxNetSocket.hpp \
    ../../../include/NyxNet/NyxNetSocketListener.hpp \
    ../../../include/NyxNet/NyxNetSSLTcpIpSocket.hpp \
    ../../../include/NyxNet/NyxNetTcpIpServer.hpp \
    ../../../include/NyxNet/NyxNetTcpIpSocket.hpp \
    ../../../include/NyxNet/NyxNetTcpIpTraceOutput.hpp \
    ../../../include/NyxNet/NyxNetTraceFlags.hpp \
    ../../../include/NyxNet/NyxNetTraceStreamWriter.hpp \
    ../Source/NyxNetModule_Impl.hpp \
    ../Source/NyxNetPipeClientConn.hpp \
    ../Source/NyxNetPipeServer_Impl.hpp \
    ../Source/NyxNetPipeSocketReader_Impl.hpp \
    ../Source/NyxNetPipeSocketWriter_Impl.hpp \
    ../Source/NyxNetSSLTcpIpSocket_Impl.hpp \
    ../Source/NyxNetTcpIpClientConn.hpp \
    ../Source/NyxNetTcpIpServer_Impl.hpp \
    ../Source/NyxNetTcpIpSocket_Impl.hpp \
    ../../Source/NyxNetConnectionsTable_Impl.h \
    ../../Source/NyxNetConnectionsTable_Impl.hpp \
    ../../Source/NyxNetNxConnection_Impl.hpp \
    ../../Source/NyxNetPipeTraceOutput_Impl.hpp \
    ../../Source/NyxNetTcpIpTraceOutput_Impl.hpp

SOURCES += \
    ../Source/NyxNetModule_Impl.cpp \
    ../Source/NyxNetPipeClientConn.cpp \
    ../Source/NyxNetPipeServer_Impl.cpp \
    ../Source/NyxNetPipeSocketReader_Impl.cpp \
    ../Source/NyxNetPipeSocketWriter_Impl.cpp \
    ../Source/NyxNetSSLTcpIpSocket_Impl.cpp \
    ../Source/NyxNetTcpIpClientConn.cpp \
    ../Source/NyxNetTcpIpServer_Impl.cpp \
    ../Source/NyxNetTcpIpSocket_Impl.cpp \
    ../Source/NyxNetTraceFlags.cpp \
    ../../Source/NyxNetConnectionsTable_Impl.cpp \
    ../../Source/NyxNetNxConnection_Impl.cpp \
    ../../Source/NyxNetPipeTraceOutput_Impl.cpp \
    ../../Source/NyxNetTcpIpTraceOutput_Impl.cpp \
    ../../Source/NyxNetTraceStreamWriter.cpp

CONFIG(debug, debug | release) {
    OBJECTS_DIR = ./Debug_64
    DESTDIR = ../../../Lib/Qt/Debug_64
}

CONFIG(release, debug | release) {
    OBJECTS_DIR = ./Release_64
    DESTDIR = ../../../Lib/Qt/Release_64
}

