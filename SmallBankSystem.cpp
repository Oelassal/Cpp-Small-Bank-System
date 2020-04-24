// SmallBankSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <Windows.h>

using namespace std;

/******************************
Class Declaration
******************************/
class account {
	int acc_no;
	string name;
	double deposit;
	char acc_type;
public:
	void create_account();//function to create account
	void show_account();//function to show account details
	void edit(); //function to edit account details
	void dep(int); //function to deposit money
	void draw(int); //function to draw amount of money from account
	void report() const;
	int ret_acc_no() const;	//function to return account number
	int ret_deposit() const;	//function to return balance amount
	char ret_type() const;	//function to return type of account
};

/******************************
Functions Declaration
******************************/
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function


void account::create_account() {
	cout << "Please Enter Account Number : ";
	cin >> acc_no;
	cout << "\nPlease Enter Account Holder Name : ";
	cin >> name;
	cout << "Please Select Account Type\n S = Saving Account\nC = Current account\n**Please note that the "
		"minimum amount for Saving Accounts is 500 and for Current account is 1000$**" << endl;
	cin >> acc_type;
	do {
		if (acc_type = 's' || 'S') {
			do {
				cout << "Please Enter Initial Amount :";
				cin >> deposit;
				if (deposit < 500)
					cout << "Please Enter a value More than or Equals to 500" << endl;
			} while (deposit < 500);
			break;
		}
		else if (acc_type = 'c' || 'C') {
			do {
				cout << "Please Enter Initial Amount :";
				cin >> deposit;
				if (deposit < 500)
					cout << "Please Enter a value More than or Equals to 1000" << endl;
			} while (deposit < 1000);
			break;
			cout << "Please enter a deposit more than 1000$";
		}
		else {
			cout << "Please Make Sure You Chose Correct Selection" << endl;
		}
	} while(acc_type = 's' || 'S' || 'C' || 'c');
	cout << "Data Saved Succesfully"<<endl;
	Sleep(1000);
	system("cls");

}



void account::show_account() {
	cout << "Account No. :" << acc_no;
	cout << "Account Name Holder : " << name << endl;
	cout << "Account Type :" << acc_type << endl;
	cout << "Remaining Balance :" << deposit << endl;
}

void account::edit() {
	cout << "\nAccount No. : " << acc_no;
	cout << "\nModify Account Holder Name : ";
	cin >> name;
	cout << "\nModify Type of Account : ";
	cin >> acc_type;
	acc_type = toupper(acc_type);
	cout << "\nModify Balance amount : ";
	cin >> deposit;
}

void account::dep(int x) {
	deposit += x;
}

void account::draw(int x) {
	deposit -= x;
}

void account::report() const {
	cout << acc_no << setw(10) << " " << name << setw(10) << " " << acc_type << setw(6) << deposit << endl;
}
int account::ret_acc_no() const {
	return acc_no;
}

int account::ret_deposit() const {
	return deposit;
}

char account::ret_type() const {
	return acc_type;
}

//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	do
	{
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";
	} while (false);

	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.ret_acc_no() == n)
		{
			ac.show_account();
			flag = true;
		}
	} 

	inFile.close();
	if (flag == false)
		cout << "\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if (ac.ret_acc_no() == n)
		{
			ac.show_account();
			cout << "\n\nEnter The New Details of account" << endl;
			ac.edit();
			int pos = (-1)*static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.ret_acc_no() != n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if (ac.ret_acc_no() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter The amount to be deposited";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw";
				cin >> amt;
				int bal = ac.ret_deposit() - amt;
				if ((bal<500 && ac.ret_type() == 'S') || (bal<1000 && ac.ret_type() == 'C'))
					cout << "Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos = (-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************


void intro()
{
	cout << "____    __    ____  _______  __        ______   ______  .___  ___. _______ " << endl;
	cout << "\\   \\  /  \\  /   / |   ____||  |      /      | /  __  \\ |   \\/   ||   ____|" << endl;
	cout << " \\   \\/    \\/   /  |  |__   |  |     |  ,----'|  |  |  ||  \\  /  ||  |__   " << endl;
	cout << "  \\            /   |   __|  |  |     |  |     |  |  |  ||  |\\/|  ||   __|  " << endl;
	cout << "   \\    /\\    /    |  |____ |  `----.|  `----.|  `--'  ||  |  |  ||  |____ " << endl;
	cout << "    \\__/  \\__/     |_______||_______| \\______| \\______/ |__|  |__||_______|" << endl;
	cout << "" << endl;
	cout << "\t\tTo Your Favorite Bank Account System" << endl;
	cout << "********************************************************************************" << endl;
	Sleep(3000);
	/***********************************************
	LOAD SCREEN
	************************************************/
	for (int i = 0; i < 100; i += 10)
	{

		cout << "Loading: " << i << " %  \n" << flush;
		system("cls");
		Sleep(1);
	}
}

void Options_menu() {


	cout << "\tMAIN MENU";
	cout << "\n\n\t01. NEW ACCOUNT";
	cout << "\n\n\t02. DEPOSIT AMOUNT";
	cout << "\n\n\t03. WITHDRAW AMOUNT";
	cout << "\n\n\t04. BALANCE ENQUIRY";
	cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
	cout << "\n\n\t06. DELETE AN ACCOUNT";
	cout << "\n\n\t07. MODIFY AN ACCOUNT";
	cout << "\n\n\t08. EXIT";
	cout << "\n\n\tSelect Your Option (1-8) ";


}

int main()
{
	/***********************************************
	Main Functions
	************************************************/
	char ch;
	int num;
	char con;
	intro();
do
{
	//Options Menu
	Options_menu();
	
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case '1':
		write_account();
		break;
	case '2':
		cout << "\n\n\tEnter The account No. : "; cin >> num;
		deposit_withdraw(num, 1);
		break;
	case '3':
		cout << "\n\n\tEnter The account No. : ";
		cin >> num;
		deposit_withdraw(num, 2);
		break;
	case '4':
		cout << "\n\n\tEnter The account No. : "; cin >> num;
		display_sp(num);
		break;
	case '5':
		display_all();
		break;
	case '6':
		cout << "\n\n\tEnter The account No. : "; cin >> num;
		delete_account(num);
		break;
	case '7':
		cout << "\n\n\tEnter The account No. : "; cin >> num;
		modify_account(num);
		break;
	case '8':
		cout << "Thank You For Trusting Our Bank" << endl;
		Sleep(1000);
		break;
	default: cout << "Please make sure to enter a correct option!!" << endl;
	}
	cin.ignore();
	cin.get();
} while (ch != '8');

return 0;
}
//***************************************************************
//    			END OF PROJECT
//


