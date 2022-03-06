CC=g++
BN=VoluntaryBoundary#build name
CFLAGS=-O3 -Wall -I./src/include/ 
RemoveCommand=rd /s /q 
#CopyCommand=copy .\src\sprites\export\* build\$(BN)\assets
UNAME_S := $(shell uname -s)
SRC = $(wildcard ./src/*.cpp)
all:
ifeq ($(OS),Windows_NT)
	@echo "Creating game directory..."
	mkdir build
	cd build && \
	mkdir $(BN) && \
	cd $(BN) && \
	mkdir assets && \
	mkdir data
	@echo "Copying assets..."
	-copy .\src\sprites\export\* build\$(BN)\assets
	-copy .\src\dlls\* build\$(BN)
	@echo "Building binaries..."
	cd src && \
	$(CC) -o "../build/$(BN)/$(BN).exe" $(SRC) $(CFLAGS) -Llib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif
ifeq ($(UNAME_S),Linux)
	@echo "You may need to install .so files from ./src/so to /usr/bin"
	mkdir -p build/$(BN)/assets
	mkdir -p build/$(BN)/data
	cp ./src/sprites/export/* ./build/$(BN)/assets/
	cp ./src/so/*.so* ./build/$(BN)
	$(CC) -o ./build/$(BN)/$(BN).bin $(SRC) $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L./src/so
endif
ifeq ($(UNAME_S),Darwin)
	@echo "Buy normal pc"
endif

clean:
	@echo
	@echo "Removing all files from ./build..."
	-$(RemoveCommand)build

install_lib:
	sudo cp ./src/so/*.so /usr/lib/