CC=g++
SRC=main.cpp
BN=VoluntaryBoundary#build name
CFLAGS=-O3 -Wall -I include/ -L lib/ -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio
RemoveCommand=rd /s /q 
#CopyCommand=copy .\src\sprites\export\* build\$(BN)\assets\

ifeq ($(UNAME_S), Linux)
	RemoveCommand = rm -rf ./
#	CopyCommand = cp ./src/sprites/export/* build/$(BN)/assets/
endif

all: build

build: clean
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
	$(CC) -o "../build/$(BN)/$(BN).exe" $(SRC) $(CFLAGS)

clean:
	@echo
	@echo "Removing all files from ./build..."
	-$(RemoveCommand)build

buildLinux: clean #WIP
	@echo "Creating game directory..."
	mkdir build
	cd build && \
		mkdir $(BN) && \
		cd $(BN) && \
			mkdir assets && \
			mkdir data
	
	@echo 
	@echo "Copying assets..."
	cp ./src/sprites/export/* build/$(BN)/assets/

	@echo
	@echo "Building binaries..."

	cd src && \
	$(CC) $(SRC) $(CFLAGS) -o "../build/$(BN)/$(BN)"
