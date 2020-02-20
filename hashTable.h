#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <math.h>
#include "User.h"

class hashTable
{
	private:
		
		User* linearTable;
		User* quadraticTable;
		double l_userCount;
		double q_userCount;
		int l_size;
		int q_size;
		double l_loadFactor;
		double q_loadFactor;
		
	public:
		
		hashTable();
		hashTable(int size, std::string type);
		~hashTable();
		int hashFuncLinear(std::string pass, int round);
		int hashFuncQuadratic(std::string pass, int round);
		void reHashLinear(User* original);
		void reHashQuadratic(User* original);
		int findPrime(int curSize);
		bool isPrime(int prime);
		void insertLinear(std::string user, std::string pass);
		void insertQuadratic(std::string user, std::string pass);
		bool testUserPass(std::string user, std::string pass);
		User* getLinearTable;
		User* getQuadraticTable;
		void printLinearTable();
		void printQuadraticTable();
		int getLinearSize();
		int getQuadraticSize();
};
#endif
