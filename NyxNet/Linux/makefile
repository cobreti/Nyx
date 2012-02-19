ifndef Config
	Config := Debug
endif


ifeq ($(Config),Release)
	OBJDIR := Release
	LIBDIR := ../../Lib/Linux/Release
	CONFIG_CFLAGS := -O3 -fexceptions
else
	OBJDIR := Debug
	LIBDIR := ../../Lib/Linux/Debug
	CONFIG_CFLAGS := -O0 -fexceptions -g
endif


$(shell [ -d $(OBJDIR) ] || mkdir -p $(OBJDIR))
$(shell [ -d $(LIBDIR) ] || mkdir -p $(LIBDIR))


RM := rm -rf

MKDIR := mkdir 

CXX_CFLAGS := 	-I ../../include \
				-I ../../include/Linux \
				-I ../../include/NyxNet \
				-I ./ \
				-I ./Source \
				-I /usr/include \
				-v $(CONFIG_CFLAGS)


OBJS := $(OBJDIR)/NyxNetModule_Impl.o \
		$(OBJDIR)/NyxNetPipeServer_Impl.o \
		$(OBJDIR)/NyxNetPipeClientConn.o \
		$(OBJDIR)/NyxNetPipeSocketReader_Impl.o \
		$(OBJDIR)/NyxNetPipeSocketWriter_Impl.o \
		$(OBJDIR)/NyxNetTcpIpClientConn.o \
		$(OBJDIR)/NyxNetTcpIpServer_Impl.o \
		$(OBJDIR)/NyxNetTcpIpSocket_Impl.o \
		$(OBJDIR)/NyxNetNxConnection_Impl.o \
		$(OBJDIR)/NyxNetPipeTraceOutput_Impl.o \
		$(OBJDIR)/NyxNetTraceStreamWriter.o \
		$(OBJDIR)/NyxNetTraceFlags.o


$(OBJDIR)/%.o: ./Source/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^

$(OBJDIR)/%.o: ../Source/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^

$(LIBDIR)/libNyxNet.a: $(OBJS)	
	ar -r $(LIBDIR)/libNyxNet.a $(OBJS)


all: 	$(LIBDIR)/libNyxNet.a \

clean:
	-$(RM) Debug
	-$(RM) Release


