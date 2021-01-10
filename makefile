all: proj5.x

proj5.x: proj5.o passserver.o
	g++ -o proj5.x proj5.o passserver.o -lcrypt

proj5.o: proj5.cpp hashtable.h hashtable.hpp
	g++ -c proj5.cpp -std=c++11

passserver.o: passserver.cpp passserver.h hashtable.h hashtable.hpp
	g++ -c passserver.cpp -std=c++11

clean:
	rm -f *.o proj5.x
