CC := g++
TARGET := AriesRT
SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst %cpp,%o,$(SRC))

all: $(TARGET)
/src/%.o: src/%.cpp
#	$(CC) -c -O3 -fopenmp $<
# If you are using MacOS and Clang, please use the line below and comment 
# the line above because the Apple Clang Compiler doesn't support OpenMP so far
	$(CC) -c -O3 $<

$(TARGET): $(OBJ)
#	$(CC) -o $@ $^ -lgomp -lpthread
# Same as above, un-comment the line below and commnet the line above
	$(CC) -o $@ $^

clean:
	rm src/*.o

