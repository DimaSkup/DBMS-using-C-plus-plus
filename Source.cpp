// DBMS v.0.01 by Skup
//
// SOURCE.CPP
//
// this .cpp file contains function main()
//


# include "libs.h"		// include all the necessary libraries and headers

struct Account			// The structure of the database row
{
	int acctNum;			// the client's account number
	char lastName[15];		// the client's last name
	char firstName[15];		// the client's first name
	float balance;			// the client's balance

	char *nameOfColumn[4] = { "Name", "Last Name", "First Name", "Balance" };
};

class clientFile		// the main class of DBMS
{
public:
	clientFile()
	{
		//strcpy(databaseListFile, "DBList.txt");
	}

	int printMessage(void);
	int createDatabase(void);
	int updateRecord(fstream &file);
	int showRecord(fstream &file);
	bool isDatabaseExist(const char *);
	int connectToDatabase(fstream &file);
	void tableHeader(const Account &client, int *widthValuesArray,  int numberOfColumns) const	// print header to each column
	{
		// print header's upper line
		cout << "\xC9" << setfill('\xCD');			// \xC9 = "╔", \xCD = "═"
		for (int i = 0; i < numberOfColumns; i++)
		{
			cout << setw(widthValuesArray[i]) << '\xCB';	// \xCB = "╦"
		}
		cout << "\xBB" << endl;		// \xBB = "╗"
		
		// print name of each column
		cout << '\xCB' << setfill(' ') << setiosflags(ios::left)	// \xCB = "╦"
			<< setiosflags(ios::fixed | ios::showpoint)			// set precision and flags to print float values
			<< setprecision(2);

		for (int i = 0; i < numberOfColumns; i++)
		{
			cout << setw(widthValuesArray[i]) << '\xBA';	// \xBA = "║"
			cout << client.nameOfColumn[i];		
		}
		cout << '\xBA' << endl;		// \xBA = "║"
			
		// print header's bottom line
		cout << '\xCC' << setfill('\xCD');	// \xCC = "╠",  \xCD = "═"
		for (int i = 0; i < numberOfColumns; i++)
		{
			cout << setw(widthValuesArray[i]) << '\xCE';	// \xCE = "╬"
		}
		cout << '\xB9' << endl;		// \xB9 = "╣"

		cout << setiosflags(ios::right) << endl;
	}
	void outputLine(Account &client) const
	{
		const int numberOfColumns = 4;
		int additionalPositions = 3;
		int widthNumberField = sizeof(client.acctNum) + additionalPositions;
		int widthLastNameField = sizeof(client.lastName) + additionalPositions;
		int widthFirstNameField = sizeof(client.firstName) + additionalPositions;
		int widthBalanceField = sizeof(client.balance) + additionalPositions;

		int widthValuesArray[numberOfColumns] = { widthNumberField, widthLastNameField, widthFirstNameField, widthBalanceField };

		cout << "PSEUDO" << endl;
		char ascii[256];
		for (int i = 0; i < 256; i++)
		{
			ascii[i] = i;
			cout << "[" << hex << i << "] = " << ascii[i] << endl;
		}

		tableHeader(client, widthValuesArray, numberOfColumns);
		cout << "\xC9" << setfill('\xCD') << setw(7) << '\xCB' << setw(17) << '\xCB' << setw(12) << '\xCB' << setw(12) << "\xCD\xBB" << endl
			 << setfill(' ') << setiosflags(ios::left) 
			 << '\xBA' << setw(widthNumberField) << client.acctNum
			 << '\xBA' << setw(widthLastNameField) << client.lastName
			 << '\xBA' << setw(widthFirstNameField) << client.firstName
			 << '\xBA' << setw(widthBalanceField) << setiosflags(ios::fixed | ios::showpoint)
			 << setprecision(2) << client.balance << '\xBA'
			 << setiosflags(ios::right) << endl
			 << "\xC8" << setfill('\xCD') << setw(7) << '\xCA' << setw(17) << '\xCA' << setw(12) << '\xCA' << setw(12) << "\xCD\xBC" << endl;
	}
	//int showDBNamesList(void);

private:
	//int addDBNameToList(const char *);
	//char databaseListFile[15];
};

int main()
{
	clientFile DBMS;	// Database Management System object
	fstream file;		
	int choice;

	do
	{
		int choice;

		cout << "Choose an action:" << endl;
		cout << " 1 - Connect to database:" << endl
			 << " 2 - Create a new database:" << endl
			 << " 0 - exit" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			DBMS.connectToDatabase(file);
			break;
		case 2:
			DBMS.createDatabase();
			break;
		case 0:
			exit(1);
			break;
		default:
			cerr << "Choose the correct action!" << endl;
			break;
		}

	} while (!file.is_open());

	do
	{
		choice = DBMS.printMessage();
		
		switch (choice)
		{
		case 1:
			DBMS.createDatabase();
			break;
		case 2:
			DBMS.updateRecord(file);
			break;
		case 3:
			DBMS.showRecord(file);
			break;
		default:
			system("cls");
			cout << "Error. Exit." << endl;
			break;
		}
		file.clear();
		file.seekp(0);
	} while (choice != 0);
	
	file.close();
	return 0;
}

int clientFile::printMessage(void)
{
	int choice = 0;

	system("cls");
	cout << "Enter number to choose the action:" << endl
		 << " 1 - create a new database" << endl
		 << " 2 - update a record" << endl
		 << " 3 - show a record" << endl
		 << " 9 - show a database's list" << endl
		 << " 0 - exit" << endl
		 << endl << "? ";

	cin >> choice;

	return choice;
}

int clientFile::createDatabase(void)
{
	char dname[15];

	cout << "Enter database name (or 0 - to finish):" << endl << "? ";
	cin >> dname;


	if (isDatabaseExist(dname))
	{
		cout << "Database with such name exists! Please, enter another name" << endl;
		system("pause");
		return 0;
	}

	ofstream newDatabase(dname, ios::out);

	if (!newDatabase)
	{
		cerr << "Error. Can't create database with name " << dname << endl;
		system("pause");
		return 0;
	}

	Account blankClient{ 0, "", "", 0.0 };

	for (int i = 0; i < 100; i++)
	{
		newDatabase.write((char *)&blankClient, sizeof(Account));
	}

	newDatabase.close();

	cout << "Database " << dname << " was created successfully" << endl;
	system("pause");

	return 1;
}

int clientFile::updateRecord(fstream &file)
{
	Account client;

	cout << "Please, enter client data:" << endl;
	cout << "number: \n? "; cin >> client.acctNum;
	cout << "last name: \n? "; cin >> client.lastName;
	cout << "first name: \n? "; cin >> client.firstName;
	cout << "balance: \n? "; cin >> client.balance;

	//file.seekp(0, ios::beg);
	file.seekp((client.acctNum - 1) * sizeof(Account));
	file.write((char *)&client, sizeof(Account));

	system("pause");
	return 0;
}

int clientFile::showRecord(fstream &file)
{
	Account clientRecord;

	cout << "Enter client account number:" << endl << "? ";
	cin >> clientRecord.acctNum;

	assert(0 < clientRecord.acctNum && clientRecord.acctNum <= 100);

	file.seekg((clientRecord.acctNum - 1) * sizeof(Account));
	file.read((char *)&clientRecord, sizeof(Account));

	if (clientRecord.acctNum != 0)
	{
		cout << "OUTPUT LINE(): " << endl;
		outputLine(clientRecord);
		cout << "\nClient record:" << endl
			<< "       num = " << clientRecord.acctNum << endl
			<< " last name = " << clientRecord.lastName << endl
			<< "first name = " << clientRecord.firstName << endl
			<< "   balance = " << clientRecord.balance << endl << endl;
	}
	else	// clientRecord == 0
	{
		cout << "The record is empty" << endl;
	}
	
	system("pause");
	return 0;
}

int clientFile::connectToDatabase(fstream &file)
{
	char dbName[15];

	cout << "Enter database name:" << endl << "? ";
	cin >> dbName;

	if (!isDatabaseExist(dbName))
	{
		cerr << "Error. Database \"" << dbName << "\" doesn't exist" << endl;
		system("pause");
		return 1;
	}

	if (file.is_open())
	{
		file.close();	// Close the previous connection
	}

	file.open(dbName, ios::in | ios::out);	// create a new connection to the database

	return 0;
}

bool clientFile::isDatabaseExist(const char *fname)
{
	return access(fname, 0) != -1;
}

