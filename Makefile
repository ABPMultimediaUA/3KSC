#Directories
SRCDIR	:= src/
HDRDIR	:= $(SRCDIR)include/
LIBDIR  := lib/
INCDIR  := include/
OBJDIR	:= obj/
SUBDIRS := $(OBJDIR)entities $(OBJDIR)entities/characters $(OBJDIR)managers $(OBJDIR)AI

#Files
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(subst $(SRCDIR),$(OBJDIR),$(SOURCES:%.cpp=%.o))
BINARY 	:= 3KSC

#Compiler set-up
CC		:= g++
LDFLAGS := -Wl,-rpath=$(LIBDIR)

INCLUDE := -I$(HDRDIR) -I$(INCDIR)irrlicht -I$(INCDIR)sfml -I$(INCDIR)assimp -I$(INCDIR)box2D -I$(INCDIR)raknet/raknet -I$(INCDIR)fmod
LIBS	:= -L$(LIBDIR) -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor -lsfml-graphics -lsfml-window -lsfml-system -lBox2D -lraknet -lRakNetLibStatic -lfmod -lfmodL -lfmodstudio -lfmodstudioL 
FAST	:= -j4

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
	make $(FAST)

#Runs after compiling
run:
	make $(FAST)
	./$(BINARY)

#Cleans, compiles and runs
cleanr:
	make clean
	make $(FAST)
	./$(BINARY)

#Compile the program with 4 threads
fast:
	make $(FAST)

#Prints sources, objects and headers lists
info:
	$(info $(BINARY))
	$(info $(OBJECTS))
	$(info $(SOURCES))
	$(info $(INCLUDE))
	$(info $(LIBS))
