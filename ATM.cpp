#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;
void ShowMainMenuScreen();
void ShowQuickWithdrawScreen();
void ShowCheckBalanceScreen();
void GoBackToMainMenu();
void Login();

struct stClients
{
	string accountNumber = "";
	string PIN = "";
	string ClientName = "";
	string Phone = "";
	double Balance = 0.0f;
};
const string ClientsFilePath = "Client.txt";
vector <stClients> vClients;

stClients CurrentClient;
enum enOptions
{
	QuickWithdraw = 1, NormalWithdraw, Deposit, CheckBalance, LogOut
};
string ReadString(string Message)
{
	string S1;
	cout << Message;
	getline(cin >> ws, S1);
	return S1;
}
int ReadPositiveNumberInRange(string message, string ErrorMessage, int From, int To) {
	int number = 1;
	do {

		cout << message;
		cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> number;
		}
	} while (number < From || number > To);


	return number;
}
vector <string> SplitText(string& text, string Delim = " #//# ")
{
	vector <string> vString;

	string word = "";
	short position = 0;

	while ((position = text.find(Delim)) != string::npos)
	{
		word = text.substr(0, position);
		if (!word.empty())
		{
			vString.push_back(word);

			word.clear();
		}
		text.erase(0, position + Delim.length());
	}
	if (!text.empty())
	{
		vString.push_back(text);

	}
	return vString;
}

stClients ConvertLineToRecord(string Line, string Delim = " #//# ")
{
	stClients Client;
	vector <string> vClientsLines;
	vClientsLines = SplitText(Line);

	Client.accountNumber = vClientsLines[0];
	Client.PIN = vClientsLines[1];
	Client.ClientName = vClientsLines[2];
	Client.Phone = vClientsLines[3];
	Client.Balance = stod(vClientsLines[4]);
	return Client;
}
vector <stClients> LoadDataFromFile()
{
	vector <stClients> vClientsList;
	stClients ClientRecord;
	string Line = "";

	fstream MyFile(ClientsFilePath, ios::in);
	if (MyFile.is_open())
	{
		while (getline(MyFile, Line))
		{
			ClientRecord = ConvertLineToRecord(Line);
			vClientsList.push_back(ClientRecord);
		}
		MyFile.close();
	}
	else
	{
		cout << "Error: Could not open file \"" << ClientsFilePath << "\" for reading.\n";
	}
	return vClientsList;
}
bool FindClient(string accountNumber, string PIN, stClients& Client)
{

	for (stClients& i : vClients)
	{
		if (i.accountNumber == accountNumber && i.PIN == PIN)
		{
			Client = i;
			return true;
		}

	}
	return false;
}
void PrintHeader(string Title)
{
	cout << "===========================================\n";
	cout << setw(30) << Title << endl;
	cout << "===========================================\n";
}
void SaveVectorToFile(const string& FilePath, vector <string>& vlines)
{
	fstream Myfile(FilePath, ios::out);
	if (Myfile.is_open())
	{
		for (string& i : vlines)
		{
			if (!i.empty())
				Myfile << i << endl;
		}
		Myfile.close();

	}
	else
	{
		cout << "Error: Could not open file \"" << FilePath << "\" for writing.\n";
	}

}
string ConvertRecordToLine(stClients Record, string Delim = " #//# ")
{

	string Line = "";
	Line += Record.accountNumber + Delim;
	Line += Record.PIN + Delim;
	Line += Record.ClientName + Delim;
	Line += Record.Phone + Delim;
	Line += to_string(Record.Balance);
	return Line;
}
void DepositByAccountNumber(string accountNumber,int DepositAmount)
{
	vector <string> vlines;
	for (stClients& i : vClients)
	{
		if (i.accountNumber == accountNumber)
		{
			i.Balance += DepositAmount;
		}
		vlines.push_back(ConvertRecordToLine(i));
	}
	SaveVectorToFile(::ClientsFilePath, vlines);

}
short getQuickWithdrawAmount(short QuickWithdrawChoise)
{
	short WithdrawAmount[8] = { 20,50,100,200,400,600,800,1000 };
	return WithdrawAmount[QuickWithdrawChoise - 1];
}
bool IsOverBalance(int WithDrawAmount)
{
	return WithDrawAmount > CurrentClient.Balance;
}
void ShowOverBalanceMessage()
{
	cout << "Amount to withdraw is over the available balance!\n";
	cout << "Press any key to try angain...";
	system("pause>0");
}
char ReadLetter(string Message) {
	char letter;
	cout << Message;
	cin >> letter;
	return letter;
}
void PrintSuccessMessage(string Action)
{
	cout << Action << " complete successfully!\n";
}
bool DoAgain(string Action)
{
	return toupper(ReadLetter("Do you want to " + Action + " again? [Y / N] : ")) == 'Y';
}
void PerformQuickWithdraw(short QuickWithdrawAmount)
{
	
		
		if (toupper(ReadLetter("Are you sure? [Y/N]: ")) == 'Y')
		{
			DepositByAccountNumber(CurrentClient.accountNumber, QuickWithdrawAmount * -1);
			CurrentClient.Balance -= QuickWithdrawAmount;
			PrintSuccessMessage("Withdraw");
		}
		else
			return;

}
void ShowQuickWithdrawScreen()
{
	short QuickWithdrawChoise = 0;
	short QuickWithdrawAmount = 0;

	do
	{
		system("cls");
		cout << "===========================================\n";
		cout << setw(35) << "Quick Withdraw Screen\n";
		cout << "===========================================\n";
		cout << "\t[1] 20\t\t[2] 50\n";
		cout << "\t[3] 100\t\t[4] 200\n";
		cout << "\t[5] 400\t\t[6] 600\n";
		cout << "\t[7] 800\t\t[8] 1000\n";
		cout << "\t[9] Exit\n";
		cout << "===========================================\n";
		QuickWithdrawChoise = ReadPositiveNumberInRange("Choose what to do [1-9]: ", "Invalid input!, r-etner: ", 1, 9);
		QuickWithdrawAmount = getQuickWithdrawAmount(QuickWithdrawChoise);
		if (QuickWithdrawChoise == 9)
			return;
		if (IsOverBalance(QuickWithdrawAmount))
		{
			ShowOverBalanceMessage();
			ShowQuickWithdrawScreen();
			return;
		}

		PerformQuickWithdraw(QuickWithdrawAmount);
		ShowCheckBalanceScreen();
		

	} while (DoAgain("Withdraw"));
	GoBackToMainMenu();
}
int ReadAmount(string message, string ErrorMessage)
{
	int number = 1;
	do {

		cout << message;
		cin >> number;
		while (cin.fail() || number % 5 != 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> number;
		}
	} while (number <= 0);
	return number;
}
void PerformNormalWithdraw()
{
	int WithdrawAmount = 0;
	do
	{

		system("cls");
		PrintHeader("Normal Withdraw");
		WithdrawAmount = ReadAmount("Enter Amount multiple 5: ", "Invalid input, r-enter: ");
		if (IsOverBalance(WithdrawAmount))
		{
			ShowOverBalanceMessage();
			PerformNormalWithdraw();
			return;
		}
		if (toupper(ReadLetter("Are you sure? [Y/N]: ")) == 'Y')
		{
			DepositByAccountNumber(CurrentClient.accountNumber, WithdrawAmount * -1);
			CurrentClient.Balance -= WithdrawAmount;
			PrintSuccessMessage("Withdraw");
		}
		else
			return;
		ShowCheckBalanceScreen();
	} while (DoAgain("Withdraw"));

}

void ShowDepositScreen()
{
	int DepositAmount = 0;
	do
	{
		system("cls");
		PrintHeader("Deposit Screen");
		DepositAmount = ReadAmount("Enter Amount multiple 5: ", "Invalid input, r-enter: ");
		DepositByAccountNumber(CurrentClient.accountNumber, DepositAmount);
		CurrentClient.Balance += DepositAmount;
		PrintSuccessMessage("Deposit");
		ShowCheckBalanceScreen();
	} while (DoAgain("Deposit"));
}
void ShowCheckBalanceScreen()
{
	cout << "Your balance: " << CurrentClient.Balance << endl;
}
void GoBackToMainMenu()
{
	cout << "Press any key to back to main menu...";
	system("pause>0");
}
void PerformMainMenu(enOptions Option)
{

	switch (Option)
	{
	case QuickWithdraw:
		system("cls");
		ShowQuickWithdrawScreen();
		break;
	case NormalWithdraw:
		system("cls");
		PerformNormalWithdraw();
		GoBackToMainMenu();
		break;
	case Deposit:
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenu();
		break;
	case CheckBalance:
		system("cls");
		PrintHeader("Check Balance");
		ShowCheckBalanceScreen();
		GoBackToMainMenu();
		break;
	case LogOut:
		system("cls");
		Login();
		break;
	default:
		system("cls");
		Login();
		break;
	}
	ShowMainMenuScreen();
}

void ShowMainMenuScreen()
{

	system("cls");
	cout << "Welcome: " << CurrentClient.ClientName << endl;
	cout << "===========================================\n";
	cout << setw(35) << "ATM Main Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw\n";
	cout << "\t[2] Normal Withdraw\n";
	cout << "\t[3] Deposit\n";
	cout << "\t[4] Check Balance\n";
	cout << "\t[5] LogOut\n";
	cout << "===========================================\n";
	PerformMainMenu((enOptions)ReadPositiveNumberInRange("Choose What you want to do [1-5]: ", "Invalid Input!, r-enter your choise: ", 1, 5));
	Login();

}
void Login()
{
	bool LoginFailed = false;
	string accountNumber = "";
	string PINcode = "";

	do
	{
		system("cls");
		PrintHeader("Login Screen");
		if (LoginFailed)
		{
			cout << "Invalid AccountNumber or PIN !\n";
		}
		accountNumber = ReadString("Enter account number: ");
		PINcode = ReadString("Enter PIN: ");

		LoginFailed = !FindClient(accountNumber, PINcode,CurrentClient);

	} while (LoginFailed);

	ShowMainMenuScreen();

}

int main()
{
	vClients = LoadDataFromFile();

	Login();
	return 0;
}