build:
	g++ -Wall -I ./include ./src/*cpp -lSDL2 -o ./bin/sim
run:
	./bin/sim
clean:
	rm ./bin/sim

