#C++ compiling related
winpath=$(subst /,\,$(1))


CXX=g++ 
#turning the warnings off cuz this shitty ass project is so ass I have to redo it and I won't bother until I have the time
CXX_FLAGS= -std=c++17 -lstdc++ -static-libstdc++ -w -O2 
CXX_DEP_FLAGS= -MMD 
#the program uses a C library (tinyfiledialogs) so it needs to be compiled with a C compiler hehe 
#C compiling related stuff
CC=gcc
C_DEP_FLAGS= -MP -MD

#source diretories
SRC_DIRS=./src/ ./src/GUI/
#all of the include directories , separated for C and C++ 
INC_DIRS_CXX=include/thirdparty include/chart_visualiser  include/chart_visualiser/GUI
INC_DIRS_C=include/thirdparty/tinyfiledialog/

INCLUDE_DIR=include
INCLUDE_DIR_3RD=include/thirdparty
#build directories
BUILD_DIR=build
CXX_OBJ_DIR=$(BUILD_DIR)/cpp_objects/
C_OBJ_DIR=$(BUILD_DIR)/c_objects/

#library related
WINDOWS_LIBRARIES=comdlg32 ole32
SFML_LIBRARIES=libsfml-graphics.a libsfml-window.a libsfml-system.a
SFML_LIB_DIR=lib

#the source files for C++ and C
SRC_CXX=$(foreach D,$(SRC_DIRS),$(wildcard $(D)*.cpp)) 
SRC_C=$(foreach D,$(INC_DIRS_C),$(wildcard $(D)*.c))
#so we loop over each directory and find every cpp file in that directory. Then , when we find the cpp file , we replace it's parent
#folder with the build directory associated with it , and the returned value gets it's type changed from .cpp to .o
#pretty neat , not even ChatGPT helped me. I had to read the documentation
OBJ_C=$(foreach dir , $(INC_DIRS_C) , $(patsubst %.c,%.o,$(subst $(dir),$(C_OBJ_DIR),$(wildcard $(dir)*.c))))
OBJ_CXX=$(foreach dir , $(SRC_DIRS) , $(patsubst %.cpp,%.o,$(subst $(dir),$(CXX_OBJ_DIR),$(wildcard $(dir)*.cpp))))

#VPATH=$(SRC_DIRS) $(SRC_C)
vpath %.cpp $(SRC_DIRS)
vpath %.c $(INC_DIRS_C)

TARGET_DIR=target
TARGET=ChartVisualiser.exe
LIB_DIR=lib
RESOURCES_DIR=resources


.PHONY: include 

install: 
	@echo "-- Cloning SFML" 
	@git clone --branch 2.6.2 https://github.com/SFML/SFML 
	@echo "-- Cloning tinyfiledialog" 
	@git clone "https://github.com/native-toolkit/libtinyfiledialogs" "tinyfiledialog" 
pre-link: 
	@echo "-- Building the libraries for your particular version of MinGW" 
	@cd SFML && if not exist build mkdir build
	@cd SFML/build && cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release && mingw32-make
	@echo "-- Succesfully built the necessary .dll and .lib files"
static-link:
	@echo "-- Moving the .lib files to their particular location"
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)
	@move SFML\build\lib\*.a $(LIB_DIR)

dynamic-link:
	@echo -- Moving the .dll files and other assets to their particular locations
	@if not exist $(TARGET_DIR) mkdir $(TARGET_DIR)
	@move "SFML\build\lib\*.dll" $(TARGET_DIR)
	@move $(RESOURCES_DIR)\* $(TARGET_DIR)
	@move $(RESOURCES_DIR)\Resources $(TARGET_DIR)
include:
	@echo -- Moving the include files to their particular locations
	@if not exist include\thirdparty mkdir include\thirdparty
	@move tinyfiledialog $(INCLUDE_DIR_3RD) 
	@move SFML/include/SFML $(INCLUDE_DIR_3RD)
	@if exist SFML rmdir /s /q SFML
prepare:
	@if not exist $(call winpath,$(CXX_OBJ_DIR)) mkdir $(call winpath,$(CXX_OBJ_DIR))
	@if not exist $(call winpath,$(C_OBJ_DIR)) mkdir $(call winpath,$(C_OBJ_DIR))

clean-dep:
	@echo Cleaning up every dependency and the whole setup
	@if not exist $(RESOURCES_DIR) mkdir $(RESOURCES_DIR)
	-@del /s /q "$(TARGET_DIR)\*.dll" "$(TARGET_DIR)\$(TARGET)"
	@if exist $(TARGET_DIR) move "$(TARGET_DIR)\*" "$(RESOURCES_DIR)"
	-@move $(TARGET_DIR)/Resources "$(RESOURCES_DIR)"
	@if exist $(TARGET_DIR) rmdir /s /q $(TARGET_DIR) 
	@if exist $(LIB_DIR) rmdir /s /q $(LIB_DIR) 
	@if exist include\thirdparty rmdir /s /q include\thirdparty
set-up : 
	@make install
	@make pre-link
	@make static-link
	@make dynamic-link
	@make include

all : prepare $(TARGET)

#SFML isn't actually turned into obj files , cause it doesn't have any .cpp or .c files  
$(TARGET) : $(OBJ_C) $(OBJ_CXX) 
	@echo -- Creating the executable...
	@$(CXX) $(CXX_FLAGS) $(addprefix -I,$(INC_DIRS_CXX)) -L$(SFML_LIB_DIR) $(OBJ_C) $(OBJ_CXX) $(addprefix -l:,$(SFML_LIBRARIES)) $(addprefix -l,$(WINDOWS_LIBRARIES)) -o $(TARGET_DIR)/$(TARGET)
	@echo -- Done! You can find it at $(TARGET_DIR)/$(TARGET)
#for every cpp file that is changed , we recompile the associated object file

$(CXX_OBJ_DIR)%.o : %.cpp
	@echo -- Compiling $<
	@$(CXX) $(CXX_FLAGS) $(CXX_DEP_FLAGS) $(addprefix -I,$(INC_DIRS_CXX)) -L$(SFML_LIB_DIR) -c $< -o $@
$(C_OBJ_DIR)%.o : %.c
	@echo -- Compiling $<
	@$(CC) $(CC_FLAGS) $(C_DEP_FLAGS) $(addprefix -I,$(INC_DIRS_C)) -c $< -o $@
src_files:
	@echo "C++ source files: "
	@echo "$(SRC_CXX)"
	@echo "C source files:"
	@echo "$(SRC_C)"
obj_files:
	@echo "C++ object files:"
	@echo "$(OBJ_CXX)"
	@echo "C object files:"
	@echo "$(OBJ_C)"
clean:
	rmdir /s /q $(BUILD_DIR) 
#this is used in case I edit this file and save on windows mode(meaning I add '\r' after every end of line)
#$(CXX) represents the C++ compiler
linuxify:
	$(CXX) -std=c++20 makefile_converter.cpp -o converter.exe
	./converter.exe linux makefile
windowsify:
	$(CXX) -std=c++20 makefile_converter.cpp -o converter.exe
	./converter.exe windows makefile
	

