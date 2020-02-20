hashTable: main.o Executive.o hashTable.o User.o
	g++ -g -std=c++11 -Wall main.o Executive.o hashTable.o User.o -o hashTable

main.o: main.cpp Executive.h
	g++ -g -std=c++11 -Wall -c main.cpp

User.o: User.cpp User.h
	g++ -g -std=c++11 -Wall -c User.cpp

hashTable.o: hashTable.cpp User.h
	g++ -g -std=c++11 -Wall -c hashTable.cpp

Executive.o: Executive.cpp hashTable.h
	g++ -g -std=c++11 -Wall -c Executive.cpp

clean:
	rm *.o hashTable
