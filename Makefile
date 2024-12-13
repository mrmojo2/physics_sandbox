build:
	g++ -Wall -I ./include -I ./include/Physics ./src/*cpp ./src/Physics/*cpp -lSDL2 -lSDL2_gfx -o ./bin/sim
run:
	./bin/sim
clean:
	rm ./bin/sim

