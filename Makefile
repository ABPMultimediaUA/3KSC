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
INCLUDE := -I$(HDRDIR) -I$(LIBDIR)irrlicht/include -I$(LIBDIR)sfml/include -I$(LIBDIR)box2D/include -I$(LIBDIR)fmod/include -I$(LIBDIR)assimp/include -I$(LIBDIR)raknet/include/raknet
LIBS	:= -L$(LIBDIR)irrlicht/lib/Linux -lIrrlicht -L$(LIBDIR) -lGL -lXxf86vm -lXext -lX11 -lXcursor -L$(LIBDIR)sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -L$(LIBDIR)box2D/lib -lbox2d -L$(LIBDIR)assimp/lib -lassimp -L$(LIBDIR)raknet/lib -lraknet -lRakNetLibStatic -L$(LIBDIR)fmod/lib -lfmodex64 -lfmodevent64 -Wl,-rpath $(LIBDIR)fmod/lib -Wl,-rpath $(LIBDIR)raknet/lib
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

#Runs after compiling
run:
	make
	./3KSC

#Cleans, compiles and runs
cleanr:
	make clean
	make
	./3KSC

#Prints sources, objects and headers lists
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))
	$(info $(INCLUDE))
	$(info $(LIBS))