# ATM
## Problem Description:
It is required to design a program for a banking system. The program should
interactively deal with the ATM user and provide different banking services.
## Code Structure:
It is required to construct a class named ATM; this class has the following members:     
Variables:  string variable in C-style strings.   
Account name: holds the name of this account owner, which is of maximum 100 letters.  
Card number: the card number of this account, which consists of 10 numbers.   
Amount: the amount of money in the account.
### Functions:
create_new_acc(): this member function is used to create a new account, entering the
name and the card number.    
Deposit(): this function adds the deposited amount to the money in the account + 1% of the
deposited amount added    
Withdrawal(): this function withdraw money from the money in the account + 3% deduced
from the account.   
Transfer(): this function transfers money from a sending account to a receiving account,
deducing 1.5% from both accounts.   
Print_acc_data(): prints the account name, card number, and amount of money
## Constants and Equations:
- The maximum number of accounts is 100 accounts   
- When depositing, an extra 1% of the depositing amount is added to the account    
- When withdrawing, an extra 3% of the withdrawn amount is deduced from the account   
- When transfer, each user has 1.5% deduced from each account    
- The program should interactively deal with the ATM user, until the user requests to
terminate the program
