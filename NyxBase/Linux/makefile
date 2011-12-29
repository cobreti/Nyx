ifndef Config
	Config := Debug
endif


ifeq ($(Config),Release)
	OBJDIR := Release
	CONFIG_CFLAGS := -O3
else
	OBJDIR := Debug
	CONFIG_CFLAGS := -O0
endif


$(shell [ -d $(OBJDIR) ] || mkdir -p $(OBJDIR))


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
		$(OBJDIR)/NyxMemPoolWString_Impl.o


$(OBJDIR)/%.o: ./Source/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^


$(OBJDIR)/libNyxBase.a: $(OBJS)	
	ar -r $(OBJDIR)/libNyxBase.a $(OBJS)


all: 	$(OBJDIR)/libNyxBase.a \

clean:
	-$(RM) Debug
	-$(RM) Release


