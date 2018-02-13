#Directories
SRCDIR	:= src/
HDRDIR	:= src/headers/
LIBDIR  := src/lib/
OBJDIR	:= obj/
SUBDIRS := $(OBJDIR)entities $(OBJDIR)managers $(OBJDIR)lib/glm/include/detail

#Files
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(subst $(SRCDIR),$(OBJDIR),$(SOURCES:%.cpp=%.o))
BINARY 	:= 3KSC

#Compiler set-up
CC		:= g++
LDFLAGS := -Wl,-rpath=$(LIBDIR)box2D/lib,-rpath=$(LIBDIR)raknet/lib,-rpath=$(LIBDIR)fmod/lib,-rpath=$(LIBDIR)assimp/lib,-rpath=$(LIBDIR)sfml/lib

INCLUDE := -I$(HDRDIR) -I$(LIBDIR)irrlicht/include -I$(LIBDIR)sfml/include -I$(LIBDIR)assimp/include -I$(LIBDIR)box2D/include -I$(LIBDIR)raknet/include/raknet -I$(LIBDIR)fmod/include
LIBS	:= -L$(LIBDIR)irrlicht/lib/Linux -lIrrlicht -L$(LIBDIR) -lGL -lXxf86vm -lXext -lX11 -lXcursor -L$(LIBDIR)sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -L$(LIBDIR)assimp/lib -lassimp -L$(LIBDIR)box2D/lib -lBox2D -L$(LIBDIR)raknet/lib -lraknet -lRakNetLibStatic -L$(LIBDIR)fmod/lib -lfmod -lfmodL -lfmodstudio -lfmodstudioL 
#Make binary
$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(INCLUDE) $(LIBS)

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