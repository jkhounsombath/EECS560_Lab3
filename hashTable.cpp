#include "hashTable.h"

hashTable::hashTable()
{
	l_size= 0;
	q_size= 0;
	l_userCount= 0;
	q_userCount= 0;
	linearTable= nullptr;
	quadraticTable= nullptr;
	l_loadFactor= 0;
	q_loadFactor= 0;
}

hashTable::hashTable(int size, std::string type)
{
	if(type == "linear")
	{
		l_size= size;
		q_size= 0;
		l_userCount= 0;
		q_userCount= 0;
		linearTable= new User[l_size];
		for(int i=0; i<l_size; i++)
		{
			User tempUser;
			linearTable[i] = tempUser;
		}
		quadraticTable= nullptr;
		l_loadFactor= 0;
		q_loadFactor= 0;
	}
	else
	{
		l_size= 0;
		q_size= size;
		l_userCount= 0;
		q_userCount= 0;
		linearTable= nullptr;
		quadraticTable= new User[q_size];
		for(int i=0; i<l_size; i++)
		{
			User tempUser;
			quadraticTable[i] = tempUser;
		}
		l_loadFactor= 0;
		q_loadFactor= 0;	
	}
}

hashTable::~hashTable()
{
	delete []linearTable;
	delete []quadraticTable;
}
int hashTable::hashFuncLinear(std::string pass, int round, int size)
{
	int numTot= 0;
	int charTot= 0;
	int j= round;
	for(unsigned short i=0; i<pass.length(); i++)
	{
		if(isdigit(pass[i]))
		{
			numTot+= pass[i] - '0';
		}
		else
		{
			charTot+= int(pass[i]);
		}
	}
	if(j > 0)
	{
		return((((charTot+numTot) % size)+j) % size);
	}
	else
	{
		return((charTot+numTot) % size);
	}
}

int hashTable::hashFuncQuadratic(std::string pass, int round, int size)
{
	int numTot= 0;
	int charTot= 0;
	int j= round;
	for(unsigned short i=0; i<pass.length(); i++)
	{
		if(isdigit(pass[i]))
		{
			numTot+= pass[i] - '0';
		}
		else
		{
			charTot+= int(pass[i]);
		}
	}
	if(j>0)
	{
		return((((charTot+numTot) % size)+ (j^2)) % size);
	}
	else
	{
		return((charTot+numTot) % size);
	}
}

void hashTable::reHashLinear(User* original)
{
	int newSize= findPrime(l_size*2);
	User* tempTable= new User[newSize];
	double newL_Factor= 0.0;
	double new_userCount= 0.0;
	newL_Factor= new_userCount/newSize;
	for(int i=0; i<newSize; i++)
	{
		User tempUser("", "");
		tempTable[i]= tempUser;
	}
	for(int i=0; i<l_size; i++)
	{
		if(original[i].getName() != "")
		{
			bool input= false;
			int j=0;
			int index= 0;
			while(input == false)
			{
				User tempUser(original[i].getName(), original[i].getPass());
				if(j == newSize)
				{
					std::cout<<"Overflow error. Could not insert value.\n";
					break;
				}
				else
				{
					index= 	hashFuncLinear(original[i].getPass(), j, newSize);
					if(tempTable[index].getName() == "")
					{
						new_userCount++;
						newL_Factor= new_userCount/newSize;
						tempTable[index]= tempUser;
						input= true;
					}
					else
					{
						j++;
					}	
				}
			}
		}
	}
	l_userCount= new_userCount;
	l_size= newSize;
	l_loadFactor= newL_Factor;
	delete [] linearTable;
	linearTable= tempTable;
	tempTable= nullptr;
}

void hashTable::reHashQuadratic(User* original)
{
	int newSize= findPrime(q_size*2);
	User* tempTable= new User[newSize];
	double newQ_Factor= 0.0;
	double new_userCount= 0.0;
	newQ_Factor= new_userCount/newSize;
	for(int i=0; i<newSize; i++)
	{
		User tempUser("", "");
		tempTable[i]= tempUser;
	}
	for(int i=0; i<q_size; i++)
	{
		if(original[i].getName() != "")
		{
			bool input= false;
			int j=0;
			int index= 0;
			while(input == false)
			{
				User tempUser(original[i].getName(), original[i].getPass());
				if(j == newSize)
				{
					std::cout<<"Overflow error. Could not insert value.\n";
					break;
				}
				else
				{
					index= 	hashFuncQuadratic(original[i].getPass(), j, newSize);
					if(tempTable[index].getName() == "")
					{
						new_userCount++;
						newQ_Factor= new_userCount/newSize;
						tempTable[index]= tempUser;
						input= true;
					}
					else
					{
						j++;
					}	
				}
			}
		}
	}
	q_userCount= new_userCount;
	q_size= newSize;
	q_loadFactor= newQ_Factor;
	delete [] quadraticTable;
	quadraticTable= tempTable;
	tempTable= nullptr;
}

int hashTable::findPrime(int curSize)
{
	bool found= false;
	if (curSize <=1 )
	{
		return 2;
	}
	while(!found)
	{
		curSize++;
		if(isPrime(curSize))
		{
			found = true;
		}
	}
	return curSize;
}

bool hashTable::isPrime(int prime)
{
	if(prime <=1 ) return false;
	if(prime <=3 ) return false;
	if(prime %2 == 0 || prime%3 == 0)
	{
		return false;
	}
	for(int i=5; i*i <= prime; i=i+6)
	{
		if((prime % i == 0) || (prime % (i+2) == 0))
		{
			return false;
		}
	}
	return true;

}

void hashTable::insertLinear(std::string user, std::string pass)
{
	if(testUserPass(user, pass))
	{
		bool input= false;
		int j=0;
		int index= 0;
		while(input == false)
		{
			User tempUser(user, pass);
			if(j == l_size)
			{
				std::cout<<"Overflow error. Could not insert value.\n";
				return;
			}
			else
			{
				index= hashFuncLinear(pass, j, l_size);
				if(linearTable[index].getName() == "")
				{
					l_userCount++;
					l_loadFactor= (l_userCount/l_size);
					linearTable[index]= tempUser;
					if(l_loadFactor > 0.5)
					{
						reHashLinear(linearTable);
						return;
					}
					input= true;
				}
				else
				{
					j++;
				}
			}			
		}
	}
	else
	{
		std::cout<<"Failure. Attempting insert on further accounts\n";
	}
}

void hashTable::insertQuadratic(std::string user, std::string pass)
{
	if(testUserPass(user, pass))
	{
		bool input= false;
		int j=0;
		int index= 0;
		while(input == false)
		{
			User tempUser(user, pass);
			if(j == q_size)
			{
				std::cout<<"Overflow error. Could not insert value.\n";
				return;
			}
			else
			{
				index= hashFuncQuadratic(pass, j, q_size);
				if(quadraticTable[index].getName() == "")
				{
					q_userCount++;
					q_loadFactor= (q_userCount/q_size);
					quadraticTable[index]= tempUser;
					if(q_loadFactor > 0.5)
					{
						reHashQuadratic(quadraticTable);
						return;
					}
					input= true;
				}
				else
				{
					j++;
				}
			}			
		}
	}
	else
	{
		std::cout<<"Failure. Attempting insert on further accounts\n";
	}
}

bool hashTable::testUserPass(std::string user, std::string pass)
{
	for(int i=0; i<l_size; i++)
	{
		if(linearTable[i].getName() == user)
		{
			std::cout<<"Could not insert "<<user<<"due to duplicate.\n";
			return false;
		}
	}
	for(int i=0; i<q_size; i++)
	{
		if(quadraticTable[i].getName() == user)
		{
			std::cout<<"Could not insert "<<user<<"due to duplicate.\n";
			return false;
		}
	}
	if(user.length() < 1 || user.length() > 6)
	{
		std::cout<<"Could not insert "<<user<<" due to invalid username. (Must be between 1 and 6 chars)\n";
		return false;
	}
	int charCount= 0;
	int intCount= 0;
	if(pass.length() > 7)
	{
		std::cout<<"Could not insert "<<user<<" due to invalid password. (Too long)\n";
		return false;
	}
	for(unsigned short i = 0; i < pass.length(); i++)
	{
		if(!(((int(pass[i]) >= 97) && (int(pass[i]) <= 122))))
		{
			if(!isdigit(pass[i]))
			{
				std::cout<<"Could not insert "<<user<<" due to invalid password. (Only lowercase letters allowed and digits)\n";
				return false;
			}
		}	
		else
		{
			if((int(pass[i]) >= 97) && (int(pass[i]) <= 122))
			{
				charCount++;
			}
			if(isdigit(pass[i]))
			{
				intCount++;
			}
		}
	}
	if(charCount < 3 && intCount < 2)
	{
		std::cout<<"Could not insert "<<user<<" due to invalid password. (Must have at least 3 chars and 2 ints)\n";
		return false;
	}
	return true;
}

void hashTable::printLinearTable()
{
	std::cout<<"The linear table:\n";
	for(int i=0; i<l_size; i++)
	{
		std::cout<<i<<": "<<"User: "<<linearTable[i].getName()<<" Pass: "<<linearTable[i].getPass()<<std::endl;
	}
	std::cout<<"\n\n\n\n\n\n";
}

void hashTable::printQuadraticTable()
{
	std::cout<<"The quadratic table:\n";
	for(int i=0; i<q_size; i++)
	{
		std::cout<<i<<": "<<"User: "<<quadraticTable[i].getName()<<" Pass: "<<quadraticTable[i].getPass()<<std::endl;
	}
	std::cout<<"\n\n\n\n\n\n";
}

int hashTable::getLinearSize()
{
	return l_size;
}

int hashTable::getQuadraticSize()
{
	return q_size;
}

void hashTable::forgotPassLinear(std::string username)
{
	for(int i=0; i<l_size; i++)
	{
		if(linearTable[i].getName() == username)
		{
			std::cout<<"The password associated with user "<<username<<" is: "<<linearTable[i].getPass()<<"\n\n\n\n\n";
			return;
		}
	}
	std::cout<<"This user was not in the table.\n\n\n";
}

void hashTable::forgotPassQuadratic(std::string username)
{
	for(int i=0; i<q_size; i++)
	{
		if(quadraticTable[i].getName() == username)
		{
			std::cout<<"The password associated with user "<<username<<" is: "<<quadraticTable[i].getPass()<<"\n\n\n\n\n";
			return;
		}
	}
}

void hashTable::forgotUserLinear(std::string pass)
{
	for(int i=0; i<l_size; i++)
	{
		if(linearTable[i].getPass() == pass)
		{
			std::cout<<"The user associated with password "<<pass<<" is: "<<linearTable[i].getName()<<"\n\n\n\n\n";
			return;
		}
	}
	std::cout<<"This user was not in the table.\n\n\n";
}

void hashTable::forgotUserQuadratic(std::string pass)
{
	for(int i=0; i<q_size; i++)
	{
		if(quadraticTable[i].getPass() == pass)
		{
			std::cout<<"The user associated with password "<<pass<<" is: "<<quadraticTable[i].getName()<<"\n\n\n\n\n";
			return;
		}
	}
}

void hashTable::removeUserLinear(std::string user, std::string pass)
{
	for(int i=0 ; i< l_size; i++)
	{
		if(linearTable[i].getName() == user && linearTable[i].getPass() == pass)
		{
			linearTable[i].setName("");
			linearTable[i].setPass("");
			std::cout<<"User is deleted from linear table\n";
			return;
		}
	}
	std::cout<<"The user is not in the linear table\n";
}

void hashTable::removeUserQuadratic(std::string user, std::string pass)
{
	for(int i=0 ; i< q_size; i++)
	{
		if(quadraticTable[i].getName() == user && quadraticTable[i].getPass() == pass)
		{
			quadraticTable[i].setName("");
			quadraticTable[i].setPass("");
			std::cout<<"User is deleted from the quadratic table\n";
			return;
		}
	}
	std::cout<<"The user is not in the quadratic table\n";
}
