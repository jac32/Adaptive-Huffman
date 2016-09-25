CC := clang++

SRCDIR := src
BUILDDIR := build
BINNAME := huffman
TARGET := bin/$(BINNAME) 

SRCEXT := cpp
HEADEXT := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
NOT_OBJECTS := $(subst $(BUILDDIR)/main.o,,$(OBJECTS))
CFLAGS := -std=c++11 -g #-o4#-ggdb3 # -Wall #-fno-inline-functions
LIB := `pkg-config libgvc --libs` #-lboost_program_options
INC := -I include

$(TARGET): $(OBJECTS) 
	$(CC) $(CFLAGS) $^ $(LIB) $(INC) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) 
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<


clean:
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

