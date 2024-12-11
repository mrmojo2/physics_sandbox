build:
	g++ -Wall -I ./include ./src/*cpp -o ./bin/sim
run:
	./bin/sim
clean:
	rm ./bin/sim

