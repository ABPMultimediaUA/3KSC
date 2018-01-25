#Directories
SRCDIR	:= src/
HDRDIR	:= src/headers/
LIBDIR  := src/lib/
OBJDIR	:= obj/
SUBDIRS := $(OBJDIR)entities $(OBJDIR)managers $(OBJDIR)lib/glm/include/detail

#Files
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(subst $(SRCDIR),$(OBJDIR),$(SOURCES:%.cpp=%.o))
BINARY 	:= 3KSC_HUD

#Compiler set-up
CC		:= g++
INCLUDE := -I$(HDRDIR) -I$(LIBDIR)sfml/include
LIBS	:= -L$(LIBDIR) -lGL -lXxf86vm -lXext -lX11 -lXcursor -L$(LIBDIR)sfml/lib -lsfml-graphics -lsfml-window -lsfml-system
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
	rm -f $(BINARY)
	rm -f $(BINARY).exe

#Makes binary (previous clean)
cleanc:
	make clean
	make

#Runs after compiling
run:
	make
	./$(BINARY)

#Cleans, compiles and runs
cleanr:
	make clean
	make
	./$(BINARY)

#Prints sources, objects and headers lists
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))
	$(info $(INCLUDE))
	$(info $(LIBS))