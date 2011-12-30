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
		$(OBJDIR)/NyxNetTraceStreamWriter_Linux.o \
		$(OBJDIR)/NyxNetNxConnection_Impl.o \
		$(OBJDIR)/NyxNetPipeTraceOutput_Impl.o \
		$(OBJDIR)/NyxNetTraceStreamWriter.o


$(OBJDIR)/%.o: ./Source/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^

$(OBJDIR)/%.o: ../Source/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^

$(OBJDIR)/libNyxNet.a: $(OBJS)	
	ar -r $(OBJDIR)/libNyxNet.a $(OBJS)


all: 	$(OBJDIR)/libNyxNet.a \

clean:
	-$(RM) Debug
	-$(RM) Release


