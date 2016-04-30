all: chaos

chaos:
	g++ -O3 src/*.cpp -o chaos

clean:
	rm -f chaos

