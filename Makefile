all:
	g++ -O3 src/*.cpp -o chaos
	g++ -O3 src/*.cpp -o order

clean:
	rm -f chaos order

