output: main.o flightticket.o flighthashtable.o
	g++ main.o flightticket.o flighthashtable.o -o ftms

main.o: main.cpp
	g++ -c main.cpp

flightticket.o: flightticket.cpp flightticket.h
	g++ -c flightticket.cpp

flighthashtable.o: flighthashtable.cpp flighthashtable.h
	g++ -c flighthashtable.cpp

clean:
	rm *.o ftms