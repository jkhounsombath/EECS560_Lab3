#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <string>
#include <fstream>
#include "hashTable.h"


class Executive
{
	private:
		hashTable HashTable;
	public:
		Executive(std::string fileName);
		~Executive();
		void run();
};
#endif
