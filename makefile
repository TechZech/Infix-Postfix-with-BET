all: clean proj4.x

proj4.x: bet.o proj4_driver.o
	g++ -o proj4.x bet.o proj4_driver.o

proj4_driver.o: proj4_driver.cpp bet.h
	g++ -c proj4_driver.cpp -std=c++11

bet.o: bet.cpp bet.h
	g++ -c bet.cpp -std=c++11

clean:
	rm -f *.o proj4.x
