#include "Executive.h"
Executive::Executive(std::string fileName)
{
	std::ifstream inFile("data.txt");
	std::string tempName;
	std::string tempPass;
	hashTable linearTable(11, "linear");
	hashTable quadraticTable(11, "quadratic");
	while(inFile>>tempName)
	{
		inFile>>tempPass;
		tempName.pop_back();
		linearTable.insertLinear(tempName, tempPass);
		quadraticTable.insertQuadratic(tempName, tempPass);
	}
	linearTable.printLinearTable();
	quadraticTable.printQuadraticTable();
	
}

Executive::~Executive()
{
}

void Executive::run()
{
}
