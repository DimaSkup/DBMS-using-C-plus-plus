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
	char firstName[10];		// the client's first name
	float balance;			// the client's balance
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
	void tableHeader(void) const
	{
		cout << "\xC9" << setfill('\xCD') << setw(6) << '\xCB' << setw(16) << '\xCB' << setw(11) << '\xCB' << setw(11) << "\xCD\xBB" << endl
			 << setfill(' ') << setiosflags(ios::left)
			 << '\xBA' << setw(5) << "Number"
			 << '\xBA' << setw(15) << "Last name"
			 << '\xBA' << setw(10) << "First name"
			 << '\xBA' << setw(10) << setiosflags(ios::fixed | ios::showpoint)
			 << setprecision(2) << "Balance" << '\xBA'
			 << setiosflags(ios::right) << endl
			 << "\xC8" << setfill('\xCD') << setw(6) << '\xCA' << setw(16) << '\xCA' << setw(11) << '\xCA' << setw(11) << "\xCD\xBC" << endl;
	}
	void outputLine(Account &client) const
	{
		cout << "PSEUDO" << endl;
		char ascii[256];
		for (int i = 0; i < 256; i++)
		{
			ascii[i] = i;
			cout << "[" << hex << i << "] = " << ascii[i] << endl;
		}

		tableHeader();
		cout << "\xC9" << setfill('\xCD') << setw(6) << '\xCB' << setw(16) << '\xCB' << setw(11) << '\xCB' << setw(11) << "\xCD\xBB" << endl
			 << setfill(' ') << setiosflags(ios::left) 
			 << '\xBA' << setw(5) << client.acctNum 
			 << '\xBA' << setw(15) << client.lastName
			 << '\xBA' << setw(10) << client.firstName
			 << '\xBA' << setw(10) << setiosflags(ios::fixed | ios::showpoint)
			 << setprecision(2) << client.balance << '\xBA'
			 << setiosflags(ios::right) << endl
			 << "\xC8" << setfill('\xCD') << setw(6) << '\xCA' << setw(16) << '\xCA' << setw(11) << '\xCA' << setw(11) << "\xCD\xBC" << endl;
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

