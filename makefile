Lab3: main.o Executive.o hashTable.o User.o
	g++ -g -std=c++11 -Wall main.o Executive.o hashTable.o User.o -o Lab3

main.o: main.cpp Executive.h
	g++ -g -std=c++11 -Wall -c main.cpp

Executive.o: Executive.cpp hashTable.h
	g++ -g -std=c++11 -Wall -c Executive.cpp

hashTable.o: hashTable.cpp User.h
	g++ -g -std=c++11 -Wall -c hashTable.cpp

User.o: User.cpp
	g++ -g -std=c++11 -Wall -c User.cpp

clean:
	rm *.o Lab3
