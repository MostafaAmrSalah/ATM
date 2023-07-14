#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <cmath>
using namespace std;

class ATM
{
private:
	char acount_name[100];
	char card_number[11];
	float amount;
public:

	ATM(int default_amount = 0) { amount = default_amount; }
	void create_new_acc(char name[], char cardn[]) { strcpy(acount_name, name); strcpy(card_number, cardn); }

	// setters and getters to access private variables
	char* get_name() { return acount_name; }
	char* get_card() { return card_number; }
	float get_amount() { return amount; }
	void set_name(char name[]) { strcpy(acount_name, name); }
	void set_card(char cardn[]) { strcpy(card_number, cardn); }
	void set_amount(float money) { amount = money; }

	void Deposit(float money) { amount += 1.01 * money; };
	void Withdrawal(float money) { amount -= 1.03 * money; };
	void Transfer(float money, ATM& reciever)
	{
		reciever.set_amount(reciever.get_amount() + 0.985 * money);
		amount -= 1.015 * money;
	}
	void Print_acc_data() {
		cout << "Name: " << acount_name << endl;
		cout << "Card number: " << card_number << endl;
		cout << "Amount: " << amount << endl;
	};
};

void reduce(char card[])          // to remove the spaces between the card number
{
	for (int i = 0; i < 10; i++) {
		card[i] = card[2 * i];              //numbers repeat every even number
	}
	card[10] = '\0';						//put the null at the end of the reduced card
}

int Search(ATM acounts[], char card[], int number_accounts)    // searches specific account by card number from acounts created in acounts array
{
	for (int i = 0; i < number_accounts; i++)
		if (strcmp(card, acounts[i].get_card()) == 0) return i;  // return the index of the acount
	return -1;      // return -1 if not found
}

bool isvalidcard(char card[])  //checks if the card is valid and prints the error massages, false to retake the input, true if the card number is valid
{
	int j = 0;    // used as counter for the while loop in line 63
	int counter = 0;
	bool number = true; // true if all the input is numeric value, false if character is detected
	while (card[counter] != '\0') counter++; // finds the index of the null

	while (card[j] != '\0') { if (!((card[j] >= '0' && card[j] <= '9') || card[j] == ' ')) { number = false; break; } j++; }
	// detects the characters (negative included) and changes the value of number variable

	if (!number) {
		cout << "Invalid card number, you entered a Symbol (characters and negative sign included). Please,enter 10 numbers." << endl << endl;
		// prints error massage if character is detected
		return 0;
	}

	if (counter > 19)
		for (int i = 0; i < 20; i++)
			if (card[i] != ' ' && card[i + 1] != ' ' && card[i + 1] != '\0')
			{
				cout << "You entered a number greater than 9. please enter 10 number from (0 to 9)." << endl << endl; return 0;
				// finds if the card number has a number > 9, and print the error massage
			}

	if (counter < 19) // detects if the input numbers count is less than 10 and prints error massage
	{
		cout << "Invalid card number, your input is less than 10 numbers. Please enter 10 number(from 0 to 9). " << endl << endl;
		return 0;
	}
	else if (counter > 19) // detects if the input numbers count is greater than 10 and prints error massage
	{
		cout << "Invalid card number, your input is more than 10 numbers. Please enter 10 number. " << endl << endl;
		return 0;
	}

	for (int i = 2; i < counter; i += 2) // makes sure that all the input numbers are not the same and prints error massage
	{
		if (card[0] != card[i]) { return 1; }
	}
	cout << "Invalid card. numbers must be different." << endl << endl;
	return 0;
}

bool isvalidname(char name[]) // checks if the input name is valid
{
	int j = 0;   // counter of the while loop
	while (name[j] != '\0') { // finds the index of the null
		if (!(isalpha(name[j]) || name[j] == ' ')) // makes sure the input is alphabetic and prints the error massage
		{
			cout << "Invalid name. The name must consist of alphabetic letters only." << endl << endl; return 0;
		}
		j++;
	}
	if (name[0] == '\0') { cout << "Invalid name. You can't leave it blank." << endl << endl; return 0; } // makes sure that the input is blank
	return 1;
}

bool getinput(char str[], int str_length) //makes sure that the input is valid according to c++ rules
{
	bool neglect = true; // true if to neglect spaces, false if not to neglect input
	int counter = 0;
	while (neglect) {   // deletes the initial spaces before any input
		if (cin.peek() == ' ') { cin.ignore(1); }  //ignores any spaces
		else neglect = false;
	}
	cin.getline(str, str_length);

	// deletes the final spaces after any input
	while (str[counter] != '\0') counter++; counter--; //finds the null
	while (str[counter] == ' ') counter--; //finds the last non-space input
	str[counter + 1] = '\0';  //puts the null after it

	int m, n;
	int len = counter + 1;
	for (m = 0; m < len; m++) //removes extra spaces between inputs
	{
		if (str[m] == ' ' && str[m + 1] == ' ') //checks if two Consecutive spaces exists
		{
			for (n = m; n < (len - 1); n++) //shifts the input one place to the left side
				str[n] = str[n + 1];
			str[n] = '\0';  // puts the new null
			len--;  //the new length
			m--;  //shifts the counter 1 place to check the same place again till no two Consecutive spaces are detected
		}
	}

	if (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); cout << "The input is too long, please try again." << endl << endl; return 1; }
	// detects when cin function fails (when too many input is written) and sets it back and prints the error massage
	return 0;

}

bool isfloat(char money[]) // tests if the input is a valid float number
{
	int j = 0; // counter
	if (money[0] == '-') { cout << "Invalid monetary value, please enter a positive number." << endl << endl; return 0; } //if it is negative ptint error massage
	while (money[j]) {
		if (!((money[j] >= '0' && money[j] <= '9') || money[j] == '.')) //detects if any character is written and prints error massage
		{
			cout << "Invalid, your input includes symbols, please enter a valid monetary value." << endl << endl; return 0;
		} j++;
	}
	if (money[0] == '\0') { cout << "Invalid, you can't leave it blank, please enter a valid monetary value." << endl << endl; return 0; }
	//prints error f it is left blank
	return 1;
}


int main() {

	//initiate the varaibles
	ATM acounts[100];
	int number_accounts = 0;
	double amount;
	char money[100];
	char name[102];
	char card[101];
	char card2[101];
	char choice[10];

	while (1)
	{
		// menu
		if (number_accounts < 100) { //full list if k < 100
			cout << "1----Create new account" << endl;
			cout << "2----Deposit" << endl;
			cout << "3----transfer to another account" << endl;
			cout << "4----withdrawal" << endl;
			cout << "5----exit" << endl;
			cout << "Please enter the number of operation: ";
			if (getinput(choice, 10)) continue;
			if (choice[1] != '\0' || choice[0] > '5' || choice[0] < '1')
			{
				cout << "Invalid input, please enter an integer from 1 to 5." << endl << endl; continue;
			}
		}
		else { // new account option deleted if k = 100
			cout << "you have reached the maximum number of accounts" << endl;
			cout << "1----Deposit" << endl;
			cout << "2----transfer to another account" << endl;
			cout << "3----withdrawal" << endl;
			cout << "4----exit" << endl;
			cout << "Please enter the number of operation: ";
			if (getinput(choice, 10)) continue;
			if (choice[1] != '\0' || choice[0] > '4' || choice[0] < '1')   // checcks if the input is correct
			{
				cout << "Invalid input, please enter an integer from 1 to 4." << endl << endl; continue;
			}
		}

		if (number_accounts == 0 && (choice[0] == '2' || choice[0] == '4')) // user tries to deposit without account
		{
			cout << "Error, you must create account first." << endl << endl; continue;
		}
		if (number_accounts < 2 && choice[0] == '3') // user tries to transfer without account
		{
			cout << "Error, There must be 2 accounts at least." << endl << endl; continue;
		}
		if (number_accounts == 100) choice[0]++;

		// new account
		if (choice[0] == '1') {

			do cout << "Please enter the account name: ";
			while (getinput(name, 101) || !isvalidname(name)); //asks for and checks the name

			while (1) // asks for and checks the card number
			{
				cout << "Please enter the account number(10 numbers each separated by space) : ";
				if (getinput(card, 100) || !isvalidcard(card)) continue;
				reduce(card); // remove the spaces between inputs
				if (Search(acounts, card, number_accounts) + 1) { cout << "Invalid, You can't have 2 accounts with same number." << endl << endl; continue; }
				// if it is found previously, print error massage
				break;
			}

			acounts[number_accounts].create_new_acc(name, card); //assign the account
			acounts[number_accounts].Print_acc_data(); //prints account data
			number_accounts++;
		}
		// deposit
		else if (choice[0] == '2')
		{
			int num; //index of the account
			while (1) // asks for and checks the card number and if account exists
			{
				cout << "Please enter the account number(10 numbers each separated by space) : ";
				if (getinput(card, 100) || !isvalidcard(card)) continue;
				reduce(card);
				if (!(Search(acounts, card, number_accounts) + 1)) { cout << "Invalid, account not found." << endl << endl; continue; }
				//checks if the account is created
				num = Search(acounts, card, number_accounts);
				break;
			}

			while (1) // asks for and checks the money to be deposited
			{
				cout << "Please enter the amount to be deposited: ";
				if (getinput(money, 100) || !isfloat(money)) continue;
				amount = atof(money); //transfer character to float
				if (amount == 0) { cout << "Invalid, please enter a positive number greater than 0." << endl << endl; continue; } // if user enters 0
				break;
			}

			//deposits the money
			acounts[num].Deposit(amount);
			acounts[num].Print_acc_data();
		}
		//--------------------------------------------------------

		// transfer
		else if (choice[0] == '3')
		{
			int num, num2; //indeices of users
			while (1) // asks for and checks the card number and if account exists
			{
				cout << "Please enter the number of the sending account(10 numbers each separated by space): ";
				if (getinput(card, 100) || !isvalidcard(card)) continue;
				reduce(card);
				if (!(Search(acounts, card, number_accounts) + 1)) { cout << "Invalid, account not found." << endl << endl; continue; }
				num = Search(acounts, card, number_accounts);
				break;
			}

			if (acounts[num].get_amount() == 0 || floor(100 * (acounts[num].get_amount() / 1.015)) / 100.0 == 0)
			{
				cout << "Invalid, Your current balance is zero. Please, deposit money first." << endl << endl; continue;
			}

			while (1)// asks for and checks the card number and if account exists
			{
				cout << "Please enter the number of the receiving account(10 numbers each separated by space): ";
				if (getinput(card2, 100) || !isvalidcard(card2)) continue;
				reduce(card2);
				if (!(Search(acounts, card2, number_accounts) + 1)) { cout << "Invalid, account not found." << endl << endl; continue; }
				num2 = Search(acounts, card2, number_accounts);
				if (num == num2) { cout << "Invalid, you can't transfer to the same account." << endl << endl; continue; }
				break;
			}
			if (amount == 0) { cout << "Invalid, please enter a positive number greater than 0." << endl << endl; continue; }


			while (1) { // asks for and checks the money to be transfered
				cout << "Please enter the amount to be transferred: ";

				if (getinput(money, 100) || !isfloat(money)) continue;
				amount = atof(money);

				if (acounts[num].get_amount() - 1.015 * amount < 0) // checks if the user has enough balance
				{
					cout << "Invalid, you don't have enough money. The maximum amount you can transfer is: " << floor(100 * (acounts[num].get_amount() / 1.015)) / 100.0 << endl << endl;
					//round the output to avoid round-off error when printing the maximum amount that could be transfered
					// if the user has 4.5626, the complier might print the maximum to be 4.563, which might cause error
					continue;
				}
				break;
			}

			acounts[num].Transfer(amount, acounts[num2]);// commit the transfer
			acounts[num].Print_acc_data();
			acounts[num2].Print_acc_data();
		}
		// -------------------------------------------------------

		// withdrawal
		else if (choice[0] == '4')
		{
			bool exit;
			int num;
			while (1) // asks for and checks the card number and if account exists
			{
				cout << "Please enter the account number(10 numbers each separated by space) : ";
				if (getinput(card, 100) || !isvalidcard(card)) continue;
				reduce(card);
				if (!(Search(acounts, card, number_accounts) + 1)) { cout << "Invalid, account not found." << endl << endl; continue; }
				num = Search(acounts, card, number_accounts);
				break;
			}

			if (acounts[num].get_amount() == 0 || floor((acounts[num].get_amount() / 1.03) * 100) / 100.0 == 0)
			{
				cout << "Invalid, Your current balance is zero. Please, deposit money first." << endl << endl; continue;
			}


			while (1) { // asks for and checks the money to be withdrawn
				cout << "Please enter the amount to be withdrawn: ";

				if (getinput(money, 100) || !isfloat(money)) continue;
				amount = atof(money);

				if (amount == 0) { cout << "Invalid, please enter a positive number greater than 0." << endl << endl; continue; }

				if (acounts[num].get_amount() - 1.03 * amount < 0)
				{
					cout << "Invalid, you don't have enough money. The maximum amount you can have is: " << floor((acounts[num].get_amount() / 1.03) * 100) / 100.0 << endl << endl;
					continue;
				}
				break;
			}
			if (exit) continue;

			acounts[num].Withdrawal(amount); // commit the withdrawal
			acounts[num].Print_acc_data();
		}
		else if (choice[0] == '5') //exit th program
			break;
	}
}
