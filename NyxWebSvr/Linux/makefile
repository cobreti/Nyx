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
				-I ../../include/Linux/NyxNet \
				-I ../../include/NyxNet \
				-I ../../include/NyxWebSvr \
				-I ./ \
				-I ../Source \
				-I /usr/include \
				-v $(CONFIG_CFLAGS)


OBJS := $(OBJDIR)/ConnHandler_Impl.o \
		$(OBJDIR)/ConnHttpHandler_Impl.o \
		$(OBJDIR)/ConnListener_Impl.o \
		$(OBJDIR)/Header_Impl.o \
		$(OBJDIR)/HttpHandlersTable_Impl.o \
		$(OBJDIR)/HttpServer_Impl.o \
		$(OBJDIR)/HttpsServer_Impl.o \
		$(OBJDIR)/Module_Impl.o


$(OBJDIR)/%.o: ./Source/%.cpp
	g++ -fPIC -o $@ $(CXX_CFLAGS) -c $^

$(OBJDIR)/%.o: ../Source/%.cpp
	g++ -fPIC -o $@ $(CXX_CFLAGS) -c $^

$(LIBDIR)/libNyxWebSvr.a: $(OBJS)	
	ar -r $(LIBDIR)/libNyxWebSvr.a $(OBJS)


all: 	$(LIBDIR)/libNyxWebSvr.a \

clean:
	-$(RM) Debug
	-$(RM) Release


