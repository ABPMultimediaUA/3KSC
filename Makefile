#Directories
SRCDIR	:= src/
OBJDIR	:= obj/
HDRDIR	:= src/headers/
SUBDIRS := $(OBJDIR)entities $(OBJDIR)managers

#Files
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(subst $(SRCDIR),$(OBJDIR),$(SOURCES:%.cpp=%.o))
BINARY 	:= 3KSC

#Compiler set-up
CC		:= g++
INCLUDE := -I$(HDRDIR)
LIBS	:=

#Make binary
$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(INCLUDE) $(LIBS)

#Make objects
$(OBJDIR)%.o: $(SRCDIR)%.cpp
	make setup
	$(CC) -o $@ -c $^ $(INCLUDE)

#Create object directories
setup:
	mkdir -p $(SUBDIRS)

#Deletes object files
clean:
	rm -R -f $(OBJDIR)
	rm -f 3KSC
	rm -f 3KSC.exe

#Makes binary (previous clean)
cleanc:
	make clean
	make

#Prints sources, objects and headers lists
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))
	$(info $(INCLUDE))