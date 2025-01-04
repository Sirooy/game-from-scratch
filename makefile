#-l for system libraries
#-L + path for other libraries

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

################
#### CONFIG ####
################

PLATFORM     := windows
BUILD_CONFIG := debug
APP_NAME     := game
C_COMPILER   := gcc
CC_COMPILER  := g++
C_FLAGS      := -Wall -pedantic -std=gnu17 -DGLFW_INCLUDE_NONE
CC_FLAGS     := -Wall -pedantic -std=c++20 -DGLFW_INCLUDE_NONE
MKDIR	     := mkdir -p
SRC          := src
OBJ          := obj
LIB 		 := lib
DEPENDENCIES := dependencies
INCLUDE_DIRS := -I$(SRC) -I$(DEPENDENCIES)/include
SYSTEM_LIBS  :=
LINKER_FLAGS :=
#Sets the libraries directory depending on the platform and build config
LIBS_DIR     := $(DEPENDENCIES)/$(LIB)/$(PLATFORM)/$(BUILD_CONFIG)

#Windows platform config
ifeq ("$(PLATFORM)","windows")
    #Add 
	C_FLAGS     += -DPLATFORM_WINDOWS
	CC_FLAGS    += -DPLATFORM_WINDOWS
	SYSTEM_LIBS := -lGdi32 -static
    #Build config (debug/release)
	ifeq ("$(BUILD_CONFIG)","debug")
        #Add debug information and the DEBUG define
		C_FLAGS      += -g3 -DDEBUG
		CC_FLAGS     += -g3 -DDEBUG
	else ifeq ("$(BUILD_CONFIG)","release")
        #Add optimizations
		C_FLAGS  	 += -O3
		CC_FLAGS 	 += -O3
        #Removes the console when executing the .exe
		LINKER_FLAGS := -mwindows
	else
        $(error Invalid build config "$(BUILD_CONFIG)")
	endif
else
    $(error Invalid platform "$(PLATFORM)")
endif

###############
#### RULES ####
###############

#Finds all the static libraries (.a and .lib files) for the current build config and platform,
#removes the path from them and adds the -l: flag for the linker
STATIC_LIBS  := $(shell find $(LIBS_DIR)* -type f \( -iname \*.a -o -iname \*.lib \) -exec basename {} \; | sed "s/^/-l:/g")
#Finds all the source code directories
SRC_SUBDIRS  := $(shell find $(SRC) -type d)
#Replace the $(SRC) part of the source directorie's name with $(OBJ) 
OBJ_SUBDIRS  := $(patsubst $(SRC)%,$(OBJ)%,$(SRC_SUBDIRS))
#Finds all the .cpp files
CPP_FILES    := $(shell find $(SRC) -type f -iname *.cpp)
#Finds all the .c files
C_FILES      := $(shell find $(SRC) -type f -iname *.c)
#Converts the .c and .cpp files into .o files
OBJ_FILES 	 := $(foreach FILE,$(CPP_FILES) $(C_FILES),$(call C2O,$(FILE)))

.PHONY: info

#Compiles and links the application
$(APP_NAME) : $(OBJ_SUBDIRS) $(OBJ_FILES)
	$(CC_COMPILER) -o $(APP_NAME) $(OBJ_FILES) -L$(LIBS_DIR) $(STATIC_LIBS) $(SYSTEM_LIBS) $(LINKER_FLAGS)

#Generate a rule to compile every .cpp file
$(foreach FILE,$(CPP_FILES),$(eval $(call COMPILE,$(CC_COMPILER),$(call C2O,$(FILE)),$(FILE),$(call C2H,$(FILE)),$(CC_FLAGS) $(INCLUDE_DIRS))))

#Generate a rule to compile every .c file
$(foreach FILE,$(C_FILES),$(eval $(call COMPILE,$(C_COMPILER),$(call C2O,$(FILE)),$(FILE),$(call C2H,$(FILE)),$(C_FLAGS) $(INCLUDE_DIRS))))

#Create all obj subdirectories
$(OBJ_SUBDIRS) : 
	$(MKDIR) $(OBJ_SUBDIRS)

info :
	$(info $(SRC_SUBDIRS))
	$(info $(OBJ_SUBDIRS))
	$(info $(CPP_FILES))
	$(info $(CPPOBJ_FILES))
	$(info $(C_FILES))
	$(info $(COBJ_FILES))
	$(info $(STATIC_LIBS))

#Remove the obj directory and .exe
clean :
	rm -rf $(OBJ)
	rm -rf $(APP_NAME)

#https://www.youtube.com/watch?v=BJatgOiiht4