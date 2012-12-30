CC=mpic++
CFLAGS=-Wall -pedantic

build: bin obj bin/cleudo

rebuild: clean build

obj:
	mkdir obj

bin:
	mkdir bin

bin/cleudo: obj/main.o obj/game.o obj/helper.o obj/player.o obj/ia.o obj/human.o obj/mpiplayer.o obj/process.o obj/mpihelper.o
	$(CC) obj/*.o -o bin/cleudo $(CFLAGS)

obj/main.o: src/main.cpp src/MPI/process.hpp
	$(CC) -c src/main.cpp -o obj/main.o $(CFLAGS)

obj/game.o: src/Game/game.cpp src/Game/game.hpp src/Game/player.hpp src/Game/card.hpp
	$(CC) -c src/Game/game.cpp -o obj/game.o $(CFLAGS)

obj/player.o: src/Game/player.cpp src/Game/player.hpp src/Game/card.hpp
	$(CC) -c src/Game/player.cpp -o obj/player.o $(CFLAGS)

obj/ia.o: src/Game/player.cpp src/Game/player.hpp src/Game/IA.cpp src/Game/IA.hpp src/Game/card.hpp
	$(CC) -c src/Game/IA.cpp -o obj/ia.o $(CFLAGS)

obj/human.o: src/Game/player.cpp src/Game/player.hpp src/Game/human.cpp src/Game/human.hpp src/Game/card.hpp
	$(CC) -c src/Game/human.cpp -o obj/human.o $(CFLAGS)

obj/helper.o: src/Game/helper.cpp src/Game/helper.hpp src/Game/card.hpp
	$(CC) -c src/Game/helper.cpp -o obj/helper.o $(CFLAGS)

obj/mpiplayer.o: src/Game/player.hpp src/MPI/MPIplayer.cpp src/MPI/MPIplayer.hpp src/Game/card.hpp src/MPI/MPIMessage.hpp
	$(CC) -c src/MPI/MPIplayer.cpp -o obj/mpiplayer.o $(CFLAGS)

obj/process.o: src/MPI/process.hpp src/MPI/process.cpp src/MPI/MPIhelper.hpp src/MPI/MPIplayer.hpp src/MPI/MPIMessage.hpp src/Game/game.hpp
	$(CC) -c src/MPI/process.cpp -o obj/process.o $(CFLAGS)

obj/mpihelper.o: src/MPI/MPIhelper.hpp src/MPI/MPIhelper.cpp src/Game/human.hpp src/Game/IA.hpp src/Game/player.hpp src/Game/card.hpp
	$(CC) -c src/MPI/MPIhelper.cpp -o obj/mpihelper.o $(CFLAGS)


clean: bin obj
	rm -fr obj
	rm -fr bin
