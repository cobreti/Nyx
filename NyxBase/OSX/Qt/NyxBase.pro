#-------------------------------------------------
#
# Project created by QtCreator 2013-12-31T21:57:28
#
#-------------------------------------------------

QT       -= gui
#DEFINES += STDCONSTRUCT
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

SOURCES += \
    ../Source/NyxActiveObject_Impl.cpp \
    ../Source/NyxAString_Impl.cpp \
    ../Source/NyxConsoleTraceOutput_Impl.cpp \
    ../Source/NyxEvent_Impl.cpp \
    ../Source/NyxExternalModule_Impl.cpp \
    ../Source/NyxFixedString_Impl.cpp \
    ../Source/NyxLocalTime_Impl.cpp \
    ../Source/NyxMemoryPool_Impl.cpp \
    ../Source/NyxMemPoolWString_Impl.cpp \
    ../Source/NyxMFString_Impl.cpp \
    ../Source/NyxMsgHandlers_Impl.cpp \
    ../Source/NyxMsgQueue_Impl.cpp \
    ../Source/NyxMutex_Impl.cpp \
    ../Source/NyxObjectsPool_Impl.cpp \
    ../Source/NyxTestUnitsGroup_Impl.cpp \
    ../Source/NyxThreadId_Impl.cpp \
    ../Source/NyxTime_Impl.cpp \
    ../Source/NyxTraceCompositor_Impl.cpp \
    ../Source/NyxTraceModule_Impl.cpp \
    ../Source/NyxTraceStream.cpp \
    ../Source/NyxTraceTimeReference.cpp \
    ../Source/NyxUtf8String_Impl.cpp \
    ../Source/NyxWString_Impl.cpp \
    ../../Source/NyxTaskExecuterPool_Impl.cpp \
    ../../Source/NyxThreadTaskExecuter_Impl.cpp \
    ../../Source/NyxTraceCompositorBuffer_Ansi.cpp \
    ../../Source/NyxTraceCompositorBuffer_WideChar.cpp

HEADERS += \
    ../../../include/Nyx.hpp \
    ../../../include/NyxActiveObject.hpp \
    ../../../include/NyxAlgorithm.hpp \
    ../../../include/NyxAnsiFile.hpp \
    ../../../include/NyxAString.hpp \
    ../../../include/NyxBodyBlock.hpp \
    ../../../include/NyxBuffer.hpp \
    ../../../include/NyxConsoleTraceOutput.hpp \
    ../../../include/NyxDefs.hpp \
    ../../../include/NyxDelegateBase.hpp \
    ../../../include/NyxEvent.hpp \
    ../../../include/NyxException.hpp \
    ../../../include/NyxExternalModule.hpp \
    ../../../include/NyxFile.hpp \
    ../../../include/NyxFixedString.hpp \
    ../../../include/NyxInterfaceRef.hpp \
    ../../../include/NyxLocalTime.hpp \
    ../../../include/NyxLock.hpp \
    ../../../include/NyxMemoryPool.hpp \
    ../../../include/NyxMemPoolObj.hpp \
    ../../../include/NyxMemPoolWString.hpp \
    ../../../include/NyxMFString.hpp \
    ../../../include/NyxModule.hpp \
    ../../../include/NyxMsg.hpp \
    ../../../include/NyxMsgHandler.hpp \
    ../../../include/NyxMsgHandlers.hpp \
    ../../../include/NyxMsgQueue.hpp \
    ../../../include/NyxMutex.hpp \
    ../../../include/NyxObject_Impl.hpp \
    ../../../include/NyxObject.hpp \
    ../../../include/NyxObjectsPool.hpp \
    ../../../include/NyxRange.hpp \
    ../../../include/NyxRef.hpp \
    ../../../include/NyxRefCount_Impl.hpp \
    ../../../include/NyxResException.hpp \
    ../../../include/NyxStreamHandler.hpp \
    ../../../include/NyxStreamReader.hpp \
    ../../../include/NyxStreamRW.hpp \
    ../../../include/NyxStreamWriter.hpp \
    ../../../include/NyxStringsFormat.hpp \
    ../../../include/NyxSwap.hpp \
    ../../../include/NyxTask.hpp \
    ../../../include/NyxTaskExecuter.hpp \
    ../../../include/NyxTaskExecuterPool.hpp \
    ../../../include/NyxTestUnit.hpp \
    ../../../include/NyxTestUnitsGroup.hpp \
    ../../../include/NyxTextFile.hpp \
    ../../../include/NyxThread.hpp \
    ../../../include/NyxThreadId.hpp \
    ../../../include/NyxThreadModule.hpp \
    ../../../include/NyxThreadProc.hpp \
    ../../../include/NyxTime.hpp \
    ../../../include/NyxTimeException.hpp \
    ../../../include/NyxTraceCompositor.hpp \
    ../../../include/NyxTraceCompositorBuffer_Ansi.hpp \
    ../../../include/NyxTraceCompositorBuffer_WideChar.hpp \
    ../../../include/NyxTraceCompositorBuffer.hpp \
    ../../../include/NyxTraceFeed.hpp \
    ../../../include/NyxTraceHeader.hpp \
    ../../../include/NyxTraceModule.hpp \
    ../../../include/NyxTraceOutput.hpp \
    ../../../include/NyxTraces.hpp \
    ../../../include/NyxTraceStream.hpp \
    ../../../include/NyxTraceTimeReference.hpp \
    ../../../include/NyxUtf8String.hpp \
    ../../../include/NyxWString.hpp \
    ../../../include/OSX/NyxAssert.hpp \
    ../../../include/OSX/NyxAtomicValue.hpp \
    ../../../include/OSX/NyxDbg.hpp \
    ../../../include/OSX/NyxMsgBucket.hpp \
    ../../../include/OSX/NyxSize.hpp \
    ../../../include/OSX/NyxStdAllocators.hpp \
    ../../../include/OSX/NyxSystem.hpp \
    ../../../include/OSX/NyxTraceFeeds.hpp \
    ../../../include/OSX/NyxTypes.hpp \
    ../Source/NyxActiveObject_Impl.hpp \
    ../Source/NyxAnsiFile_Impl.h \
    ../Source/NyxConsoleTraceOutput_Impl.hpp \
    ../Source/NyxEvent_Impl.hpp \
    ../Source/NyxExternalModule_Impl.hpp \
    ../Source/NyxMemoryPool_Impl.hpp \
    ../Source/NyxModule_Impl.hpp \
    ../Source/NyxMsgHandlers_Impl.hpp \
    ../Source/NyxMsgQueue_Impl.hpp \
    ../Source/NyxMutex_Impl.hpp \
    ../Source/NyxObjectsPool_Impl.hpp \
    ../Source/NyxString_Impl.hpp \
    ../Source/NyxTestUnitsGroup_Impl.hpp \
    ../Source/NyxThread_Impl.hpp \
    ../Source/NyxThreadId_Impl.hpp \
    ../Source/NyxThreadModule_Impl.hpp \
    ../Source/NyxTraceCompositor_Impl.hpp \
    ../Source/NyxTraceModule_Impl.hpp \
    ../../Source/NyxTaskExecuterPool_Impl.hpp \
    ../../Source/NyxThreadTaskExecuter_Impl.hpp


OBJECTIVE_SOURCES += \
    ../Source/NyxAnsiFile_Impl.mm \
    ../Source/NyxModule_Impl.mm \
    ../Source/NyxThread_Impl.mm \
    ../Source/NyxThreadModule_Impl.mm


INCLUDEPATH += ../../../include
INCLUDEPATH += ../../../include/OSX

CONFIG(debug, debug | release) {
    OBJECTS_DIR = ./Debug_64
    DESTDIR = ../../../Lib/Qt/Debug_64
}

CONFIG(release, debug | release) {
    OBJECTS_DIR = ./Release_64
    DESTDIR = ../../../Lib/Qt/Release_64
}
