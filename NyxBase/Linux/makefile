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
		-c -v $(CONFIG_CFLAGS)


OBJS := $(OBJDIR)/NyxMFString_Impl.o \
	$(OBJDIR)/NyxAString_Impl.o


$(OBJDIR)/%.o: ./Source/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^


$(OBJDIR)/libNyxBase.a: $(OBJS)	
	ar -r $(OBJDIR)/libNyxBase.a $(OBJS)


all: 	$(OBJDIR)/libNyxBase.a \

clean:
	-$(RM) Debug
	-$(RM) Release


