CXX = g++
CXXFLAGS = -I include -L lib
LDFLAGS = lib/libraylib.a -lopengl32 -lgdi32 -luser32 -lws2_32 -lole32 -lwinmm

# Source files
SOURCES = src/main.cpp src/snake.cpp src/tetris.cpp src/home.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OUTPUT = src/main.exe

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q src\main.o src\snake.o src\main.exe 2>nul || echo "Files already clean"

.PHONY: all clean
