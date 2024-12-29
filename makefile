#-l for system libraries
#-L + path for other libraries

################
#### CONFIG ####
################

APP_NAME     := game
CC_FLAGS     := -Wall -pedantic -std=c++20
C_FLAGS      := -Wall -pedantic -std=gnu17
CC_COMPILER  := g++
C_COMPILER   := gcc
MKDIR	     := mkdir -p
SRC          := src
OBJ          := obj
LIBS         := 
INCLUDE_DIRS := -I$(SRC)

ifdef DEBUG
	CC_FLAGS += -g
else
	CC_FLAGS += -O3
endif

################
#### MACROS ####
################

# Compiles a file
# $(1) : Compiler
# $(2) : Object file
# $(3) : Source file
# $(4) : Dependencies
# $(5) : Flags
define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)    
endef

# Converts a .cpp file name into a .o file name (src/example.cpp -> obj/example.o)
# $(1) : Cpp file
define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

# Converts a .c or .cpp file name into a .h or .hpp file name (src/example.cpp -> src/example.hpp)
# $(1) : Cpp file
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

###############
#### RULES ####
###############

#Finds all the source code directories
SRCSUBDIRS   := $(shell find $(SRC) -type d)
#Replace the $(SRC) part of the source directorie's name with $(OBJ) 
OBJSUBDIRS  := $(patsubst $(SRC)%,$(OBJ)%,$(SRCSUBDIRS))
#Finds all the .cpp files
CPPFILES    := $(shell find $(SRC) -type f -iname *.cpp)
#Finds all the .c files
CFILES      := $(shell find $(SRC) -type f -iname *.c)
#Converts the .c and .cpp files into .o files
OBJFILES 	:= $(foreach FILE,$(CPPFILES) $(CFILES),$(call C2O,$(FILE)))

.PHONY: info

#Compiles the application
$(APP_NAME) : $(OBJSUBDIRS) $(OBJFILES)
	$(CC_COMPILER) -o $(APP_NAME) $(OBJFILES) $(LIBS)

#Generate a rule to compile every .cpp file
$(foreach FILE,$(CPPFILES),$(eval $(call COMPILE,$(CC_COMPILER),$(call C2O,$(FILE)),$(FILE),$(call C2H,$(FILE)),$(CC_FLAGS) $(INCLUDE_DIRS))))

#Generate a rule to compile every .c file
$(foreach FILE,$(CFILES),$(eval $(call COMPILE,$(C_COMPILER),$(call C2O,$(FILE)),$(FILE),$(call C2H,$(FILE)),$(C_FLAGS) $(INCLUDE_DIRS))))

#Create all obj subdirectories
$(OBJSUBDIRS) : 
	$(MKDIR) $(OBJSUBDIRS)

info :
	$(info $(SRCSUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(CPPFILES))
	$(info $(CPPOBJFILES))
	$(info $(CFILES))
	$(info $(COBJFILES))

#Remove the obj directory
clean :
	rm -rf $(OBJ)
	rm -rf $(APP_NAME)

#https://www.youtube.com/watch?v=BJatgOiiht4