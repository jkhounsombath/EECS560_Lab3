#include "Executive.h"
Executive::Executive(std::string fileName)
{
	linearTable= new hashTable(11, "linear");
	quadraticTable= new hashTable(11, "quadratic");
	std::ifstream inFile("data.txt");
	std::string tempName;
	std::string tempPass;
	int i= 0;
	while(inFile>>tempName)
	{
		inFile>>tempPass;
		tempName.pop_back();
		linearTable->insertLinear(tempName, tempPass);
		quadraticTable->insertQuadratic(tempName, tempPass);
		i++;
	}
	linearTable->printLinearTable();
	quadraticTable->printQuadraticTable();
}

Executive::~Executive()
{
	delete linearTable;
	delete quadraticTable;
}

void Executive::run()
{
	std::cout<<"WELCOME TO JUSTIN'S LAB 3\n---------------------------------\n";
	int choice;
	do
	{
		std::cout<<"Choose one of the following commands:\n\n1)Add User\n2)Remove User\n3)Forgot Password\n4)Forgot Username\n5)Print Users\n6)Exit\n\nChoice: ";
		std::cin>>choice;
		if(choice == 1)
		{
			std::string name;
			std::string password;
			std::cout<<"Enter a username: \n";
			std::cin>>name;
			std::cout<<"Enter a password: \n";
			std::cin>>password;
			linearTable->insertLinear(name, password);
			quadraticTable->insertQuadratic(name, password);
		}
		else if(choice == 2)
		{
			std::string user, pass;
			std::cout<<"What is the name of the user you would like to remove?\n";
			std::cin>>user;
			std::cout<<"What is the password of the account to verify removal?\n";
			std::cin>>pass;
			linearTable->removeUserLinear(user, pass);
			quadraticTable->removeUserQuadratic(user, pass);
		}
		else if(choice == 3)
		{
			std::string user;
			std::cout<<"What was the user associated with the password?\n";
			std::cin>>user;
			std::cout<<"Output for linear: \n";
			linearTable->forgotPassLinear(user);
			std::cout<<"Output for quadratic: \n";
			quadraticTable->forgotPassQuadratic(user);
		}
		else if(choice == 4)
		{
			std::string pass;
			std::cout<<"What was the password associated with the user?\n";
			std::cin>>pass;
			std::cout<<"Output for linear: \n";
			linearTable->forgotUserLinear(pass);
			std::cout<<"Output for quadratic: \n";
			quadraticTable->forgotUserQuadratic(pass);
		}
		else if(choice == 5)
		{
			std::cout<<"Output for linear:\n";
			linearTable->printLinearTable();
			std::cout<<"Output for quadratic:\n";
			quadraticTable->printQuadraticTable();
		}
		else if(choice == 6)
		{
			std::cout<<"Good bye!\n";
		}
		else
		{
			std::cout<<"Invalid choice! (must be vaue between 1-6)\n\n\n";
		}
	}while(choice != 6);
}
