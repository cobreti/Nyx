ifndef Config
	Config := Debug
endif


ifeq ($(Config),Release)
	OBJDIR := Release
	LIBDIR := ../../Lib/Linux/Release
	CONFIG_CFLAGS := -O3
else
	OBJDIR := Debug
	LIBDIR := ../../Lib/Linux/Debug
	CONFIG_CFLAGS := -O0 -g
endif


$(shell [ -d $(OBJDIR) ] || mkdir -p $(OBJDIR))
$(shell [ -d $(LIBDIR) ] || mkdir -p $(LIBDIR))


RM := rm -rf

MKDIR := mkdir 

CXX_CFLAGS := 	-I ../../include \
				-I ../../include/Linux \
				-I ./Source \
				-I /usr/include \
				-v $(CONFIG_CFLAGS)


OBJS := $(OBJDIR)/NyxMFString_Impl.o \
	$(OBJDIR)/NyxAString_Impl.o \
	$(OBJDIR)/NyxWString_Impl.o \
	$(OBJDIR)/NyxMutex_Impl.o \
	$(OBJDIR)/NyxEvent_Impl.o \
	$(OBJDIR)/NyxThread_Impl.o \
	$(OBJDIR)/NyxThreadId_Impl.o \
	$(OBJDIR)/NyxThreadModule_Impl.o \
	$(OBJDIR)/NyxActiveObject_Impl.o \
	$(OBJDIR)/NyxModule_Impl.o \
	$(OBJDIR)/NyxTraceModule_Impl.o \
	$(OBJDIR)/NyxTraceStream.o \
	$(OBJDIR)/NyxTraceCompositor_Impl.o \
	$(OBJDIR)/NyxConsoleTraceOutput_Impl.o \
	$(OBJDIR)/NyxObjectsPool_Impl.o \
	$(OBJDIR)/NyxMsgQueue_Impl.o \
	$(OBJDIR)/NyxMsgHandlers_Impl.o \
	$(OBJDIR)/NyxMemoryPool_Impl.o \
	$(OBJDIR)/NyxMemPoolWString_Impl.o \
	$(OBJDIR)/NyxTraceCompositorBuffer_Ansi.o \
	$(OBJDIR)/NyxTraceCompositorBuffer_WideChar.o \
	$(OBJDIR)/NyxOpaqueDataBucket.o \
	$(OBJDIR)/NyxOpaqueList_Impl.o \
	$(OBJDIR)/NyxTaskExecuterPool_Impl.o \
	$(OBJDIR)/NyxThreadTaskExecuter_Impl.o \
	$(OBJDIR)/NyxAnsiFile_Impl.o \
	$(OBJDIR)/NyxTime_Impl.o \
	$(OBJDIR)/NyxLocalTime_Impl.o \
	$(OBJDIR)/NyxTraceTimeReference.o \
	$(OBJDIR)/NyxFixedString_Impl.o \
	$(OBJDIR)/NyxExternalModule_Impl.o


$(OBJDIR)/%.o: ./Source/%.cpp
	g++ -fPIC -o $@ $(CXX_CFLAGS) -c $^

$(OBJDIR)/%.o: ../Source/%.cpp
	g++ -fPIC -o $@ $(CXX_CFLAGS) -c $^

$(LIBDIR)/libNyxBase.a: $(OBJS)	
	ar -r $(LIBDIR)/libNyxBase.a $(OBJS)


all: 	$(LIBDIR)/libNyxBase.a \

clean:
	-$(RM) Debug
	-$(RM) Release


