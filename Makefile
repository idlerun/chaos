all: chaos

chaos:
	g++ src/*.cpp -o chaos

clean:
	rm -f chaos

