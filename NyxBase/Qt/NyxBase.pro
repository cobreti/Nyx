#-------------------------------------------------
#
# Project created by QtCreator 2013-12-31T21:57:28
#
#-------------------------------------------------

QT       -= gui
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11



SOURCES += \
    ../Source/NyxTaskExecuterPool_Impl.cpp \
    ../Source/NyxThreadTaskExecuter_Impl.cpp \
    ../Source/NyxTraceCompositorBuffer_Ansi.cpp \
    ../Source/NyxTraceCompositorBuffer_WideChar.cpp



HEADERS += \
    ../../include/Nyx.hpp \
    ../../include/NyxActiveObject.hpp \
    ../../include/NyxAlgorithm.hpp \
    ../../include/NyxAnsiFile.hpp \
    ../../include/NyxAString.hpp \
    ../../include/NyxBodyBlock.hpp \
    ../../include/NyxBuffer.hpp \
    ../../include/NyxConsoleTraceOutput.hpp \
    ../../include/NyxDefs.hpp \
    ../../include/NyxDelegateBase.hpp \
    ../../include/NyxEvent.hpp \
    ../../include/NyxException.hpp \
    ../../include/NyxExternalModule.hpp \
    ../../include/NyxFile.hpp \
    ../../include/NyxFixedString.hpp \
    ../../include/NyxInterfaceRef.hpp \
    ../../include/NyxLocalTime.hpp \
    ../../include/NyxLock.hpp \
    ../../include/NyxMemoryPool.hpp \
    ../../include/NyxMemPoolObj.hpp \
    ../../include/NyxMemPoolWString.hpp \
    ../../include/NyxMFString.hpp \
    ../../include/NyxModule.hpp \
    ../../include/NyxMsg.hpp \
    ../../include/NyxMsgHandler.hpp \
    ../../include/NyxMsgHandlers.hpp \
    ../../include/NyxMsgQueue.hpp \
    ../../include/NyxMutex.hpp \
    ../../include/NyxObject_Impl.hpp \
    ../../include/NyxObject.hpp \
    ../../include/NyxObjectsPool.hpp \
    ../../include/NyxRange.hpp \
    ../../include/NyxRef.hpp \
    ../../include/NyxRefCount_Impl.hpp \
    ../../include/NyxResException.hpp \
    ../../include/NyxStreamHandler.hpp \
    ../../include/NyxStreamReader.hpp \
    ../../include/NyxStreamRW.hpp \
    ../../include/NyxStreamWriter.hpp \
    ../../include/NyxStringsFormat.hpp \
    ../../include/NyxSwap.hpp \
    ../../include/NyxTask.hpp \
    ../../include/NyxTaskExecuter.hpp \
    ../../include/NyxTaskExecuterPool.hpp \
    ../../include/NyxTestUnit.hpp \
    ../../include/NyxTestUnitsGroup.hpp \
    ../../include/NyxTextFile.hpp \
    ../../include/NyxThread.hpp \
    ../../include/NyxThreadId.hpp \
    ../../include/NyxThreadModule.hpp \
    ../../include/NyxThreadProc.hpp \
    ../../include/NyxTime.hpp \
    ../../include/NyxTimeException.hpp \
    ../../include/NyxTraceCompositor.hpp \
    ../../include/NyxTraceCompositorBuffer_Ansi.hpp \
    ../../include/NyxTraceCompositorBuffer_WideChar.hpp \
    ../../include/NyxTraceCompositorBuffer.hpp \
    ../../include/NyxTraceFeed.hpp \
    ../../include/NyxTraceHeader.hpp \
    ../../include/NyxTraceModule.hpp \
    ../../include/NyxTraceOutput.hpp \
    ../../include/NyxTraces.hpp \
    ../../include/NyxTraceStream.hpp \
    ../../include/NyxTraceTimeReference.hpp \
    ../../include/NyxUtf8String.hpp \
    ../../include/NyxWString.hpp \
    ../../include/OSX/NyxAssert.hpp \
    ../../include/OSX/NyxAtomicValue.hpp \
    ../../include/OSX/NyxDbg.hpp \
    ../../include/OSX/NyxMsgBucket.hpp \
    ../../include/OSX/NyxSize.hpp \
    ../../include/OSX/NyxStdAllocators.hpp \
    ../../include/OSX/NyxSystem.hpp \
    ../../include/OSX/NyxTraceFeeds.hpp \
    ../../include/OSX/NyxTypes.hpp \
    ../../Source/NyxActiveObject_Impl.hpp

HEADERS += \
    ../Source/NyxTaskExecuterPool_Impl.hpp \
    ../Source/NyxThreadTaskExecuter_Impl.hpp

macx {
    HEADERS += \
        ../OSX/Source/NyxAnsiFile_Impl.h \
        ../OSX/Source/NyxConsoleTraceOutput_Impl.hpp \
        ../OSX/Source/NyxEvent_Impl.hpp \
        ../OSX/Source/NyxExternalModule_Impl.hpp \
        ../OSX/Source/NyxMemoryPool_Impl.hpp \
        ../OSX/Source/NyxModule_Impl.hpp \
        ../OSX/Source/NyxMsgHandlers_Impl.hpp \
        ../OSX/Source/NyxMsgQueue_Impl.hpp \
        ../OSX/Source/NyxMutex_Impl.hpp \
        ../OSX/Source/NyxObjectsPool_Impl.hpp \
        ../OSX/Source/NyxString_Impl.hpp \
        ../OSX/Source/NyxTestUnitsGroup_Impl.hpp \
        ../OSX/Source/NyxThread_Impl.hpp \
        ../OSX/Source/NyxThreadId_Impl.hpp \
        ../OSX/Source/NyxThreadModule_Impl.hpp \
        ../OSX/Source/NyxTraceCompositor_Impl.hpp \
        ../OSX/Source/NyxTraceModule_Impl.hpp \
}


macx {
    SOURCES += \
        ../OSX/Source/NyxActiveObject_Impl.cpp \
        ../OSX/Source/NyxAString_Impl.cpp \
        ../OSX/Source/NyxConsoleTraceOutput_Impl.cpp \
        ../OSX/Source/NyxEvent_Impl.cpp \
        ../OSX/Source/NyxExternalModule_Impl.cpp \
        ../OSX/Source/NyxFixedString_Impl.cpp \
        ../OSX/Source/NyxLocalTime_Impl.cpp \
        ../OSX/Source/NyxMemoryPool_Impl.cpp \
        ../OSX/Source/NyxMemPoolWString_Impl.cpp \
        ../OSX/Source/NyxMFString_Impl.cpp \
        ../OSX/Source/NyxMsgHandlers_Impl.cpp \
        ../OSX/Source/NyxMsgQueue_Impl.cpp \
        ../OSX/Source/NyxMutex_Impl.cpp \
        ../OSX/Source/NyxObjectsPool_Impl.cpp \
        ../OSX/Source/NyxTestUnitsGroup_Impl.cpp \
        ../OSX/Source/NyxThreadId_Impl.cpp \
        ../OSX/Source/NyxTime_Impl.cpp \
        ../OSX/Source/NyxTraceCompositor_Impl.cpp \
        ../OSX/Source/NyxTraceModule_Impl.cpp \
        ../OSX/Source/NyxTraceStream.cpp \
        ../OSX/Source/NyxTraceTimeReference.cpp \
        ../OSX/Source/NyxUtf8String_Impl.cpp \
        ../OSX/Source/NyxWString_Impl.cpp
}


OBJECTIVE_SOURCES += \
    ../OSX/Source/NyxAnsiFile_Impl.mm \
    ../OSX/Source/NyxModule_Impl.mm \
    ../OSX/Source/NyxThread_Impl.mm \
    ../OSX/Source/NyxThreadModule_Impl.mm


INCLUDEPATH += ../../include
INCLUDEPATH += ../../include/OSX

CONFIG(debug, debug | release) {
    OBJECTS_DIR = ./Debug_64
    DESTDIR = ../../Lib/Qt/Debug_64
}

CONFIG(release, debug | release) {
    OBJECTS_DIR = ./Release_64
    DESTDIR = ../../Lib/Qt/Release_64
}

