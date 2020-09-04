// CLIENT_FILE.H

# ifndef CLIENT_FILE_H
# define CLIENT_FILE_H

# include "libs.h"

struct Account
{
	int accNum;
	char lastName[15];
	char name[10];
	float balance;
};

struct WidthForAccount
{
	int accNum = 7;
	int lastName = 15;
	int name = 10;
	int balance = 10;
};


class ClientFile
{
public:
	ClientFile(void);
	ClientFile(const char *nameOfFile);
	~ClientFile(void)
	{
		outClientFile.close();
		inClientFile.close();
	}


	void outputAccountFieldNames(void);
	void outputSingleAccount(void);
	ofstream& createNewRandAccessFile(void);
	void addNewRecord(void);
	void printAllRecords(void);
	void printMessage(void);
	void printLine(const Account &);
	void connectToFile(void);
	
	WidthForAccount widthField;

private:
	ofstream outClientFile;
	ifstream inClientFile;
	char filename[15];
};

ClientFile::ClientFile(void)
{
	strcpy(filename, "default.txt");
}

ClientFile::ClientFile(const char *nameOfFile)
{
	strcpy(filename, nameOfFile);
}

ofstream& ClientFile::createNewRandAccessFile(void)
{
	Account blankAccount{ 0, "", "", 0.0 };


	system("cls");
	cout << "Please, enter the filename" << endl;
	cout << "? ";
	cin >> setw(10) >> filename;
	outClientFile.open(filename, ios::out);
	if (!outClientFile)
	{
		cerr << "The file can't be created!" << endl;
		exit(1);
	}
	else
	{
		cout << "File was created successfully" << endl;
	}

	for (int i = 0; i < 100; i++)
	{
		outClientFile.write((char*) &blankAccount, sizeof(Account));
	}

	outClientFile.close();
	return outClientFile;
}

void ClientFile::addNewRecord(void)
{
	system("cls");
	outClientFile.open(filename, ios::ate);

	if (!outClientFile)
	{
		cerr << "The file can't be opened!" << endl;
		exit(1);
	}

	Account account;
	cout << "Enter number of a new account (from 1 to 100, 0 - to finish): " << endl;
	cout << "? ";
	cin >> account.accNum;

	while (account.accNum > 0 && account.accNum <= 100)
	{
		cout << "Enter last name: " << endl;
		cout << "? ";
		cin >> account.lastName;
		cout << "Enter name: " << endl;
		cout << "? ";
		cin >> account.name;
		cout << "Enter balance: " << endl;
		cout << "? ";
		cin >> account.balance;

		outClientFile.seekp((account.accNum - 1) * sizeof(account));
		outClientFile.write((char*)&account, sizeof(account));

		cout << "Enter number of a new account (from 1 to 100, 0 - to finish): " << endl;
		cout << "? ";
		cin >> account.accNum;
	}

	outClientFile.close();
}

void ClientFile::printAllRecords(void)
{
	inClientFile.open(filename, ios::in);
	if (!inClientFile)
	{
		cerr << "The file can't be opened!" << endl;
		exit(1);
	}


	outputAccountFieldNames();

	Account account;

	inClientFile.read((char*)&account, sizeof(Account));

	while (! inClientFile.eof())
	{
		if (account.accNum != 0)
			printLine(account);

		inClientFile.read((char*)&account, sizeof(Account));
	}

	inClientFile.clear();
	inClientFile.seekg(0);
	inClientFile.close();
}

void ClientFile::printLine(const Account &acc)
{
	long originalFormat = cout.flags();

	cout << right 
		 << setw(widthField.accNum) << acc.accNum
		 << setw(widthField.lastName) << acc.lastName
		 << setw(widthField.name) << acc.name
		 << setiosflags(ios::fixed | ios::showpoint)
		 << setprecision(2)
		 << setw(widthField.balance) << acc.balance << endl;

	cout.flags(originalFormat);
}

void ClientFile::outputAccountFieldNames(void)
{
	long originalFormat = cout.flags();

	system("cls");
	cout << right
		 << setw(widthField.accNum) << "Number"
		 << setw(widthField.lastName) << "Last Name"
		 << setw(widthField.name) << "Name"
		 << setw(widthField.balance) << "Balance" << endl;
	cout.flags(originalFormat);
}

void ClientFile::outputSingleAccount(void)
{
	int number = 0;

	cout << "Enter number of the account (from 1 to 100, 0 - to finish)" << endl;
	cout << "? ";
	cin >> number;

	while (number < 0 || number > 100)
	{
		cout << "You've entered incorrect number, please, try again (or 0 - to finish)" << endl
			 << "? ";
		cin >> number;
		if (number == 0)
			return;
	}

	inClientFile.open(filename, ios::in);

	if (!inClientFile)
	{
		cerr << "The file can't be opened!" << endl;
		exit(1);
	}

	Account account;

	inClientFile.seekg((number - 1) * sizeof(Account));
	inClientFile.read((char*)&account, sizeof(Account));

	outputAccountFieldNames();
	printLine(account);

	inClientFile.clear();
	inClientFile.seekg(0);
	inClientFile.close();
}

void ClientFile::connectToFile(void)
{
	char nameOfFile[15] = {0};

	system("cls");
	cout << "Please, enter name of the file, which you want to connect" << endl;
	cout << "? ";
	cin >> setw(15) >> nameOfFile;

	cout << "filename = " << filename << endl;

	if (nameOfFile)
	{
		strcpy(filename, nameOfFile);
	}

	cout << "filename  = " << filename << endl;
}



void ClientFile::printMessage(void)
{
	system("cls");
	cout << "Type number to choice the action" << endl
		<< " 1 - add new record" << endl
		<< " 2 - print all the records" << endl
		<< " 3 - create new file" << endl
		<< " 4 - print the single record" << endl
		<< " 5 - connect to file" << endl
		<< " 9 - exit";
	cout << endl << "? ";
}
# endif