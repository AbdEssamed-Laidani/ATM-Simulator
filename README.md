# ATM Simulator

A console-based ATM (Automated Teller Machine) simulator written in C++. The application allows bank clients to log in with their account credentials and perform common banking operations.

## Features

- **Login** – Authenticate using an account number and PIN code.
- **Quick Withdraw** – Select a preset withdrawal amount (20, 50, 100, 200, 400, 600, 800, or 1000).
- **Normal Withdraw** – Enter a custom amount (must be a multiple of 5).
- **Deposit** – Add funds to the account (amount must be a multiple of 5).
- **Check Balance** – Display the current account balance.
- **Log Out** – Return to the login screen.

## Requirements

- Windows OS (uses `system("cls")` and `system("pause>0")`)
- C++11 or later
- Visual Studio (solution file included)

## Build & Run

1. Open `ATM Project.sln` in Visual Studio.
2. Build the solution (Ctrl+Shift+B).
3. Run the executable. Make sure `Client.txt` is located in the same directory as the executable.

## Client Data File

Client records are stored in `Client.txt`. Each line represents one client using the following format:

```
AccountNumber #//# PIN #//# ClientName #//# Phone #//# Balance
```

### Example

```
G34 #//# 1234 #//# Rawan #//# 999872721 #//# 9887097.000000
A150 #//# 1231 #//# Abd Samed #//# 055967806 #//# 190.000000
```

### Fields

| Field           | Description                        |
|-----------------|------------------------------------|
| AccountNumber   | Unique account identifier          |
| PIN             | 3–4 digit PIN code                 |
| ClientName      | Full name of the account holder    |
| Phone           | Phone number                       |
| Balance         | Current account balance (double)   |

## Project Structure

```
ATM-Simulator/
├── ATM.cpp              # Main source file (all application logic)
├── Client.txt           # Client data file
├── ATM Project.sln      # Visual Studio solution file
├── ATM Project.vcxproj  # Visual Studio project file
└── README.md            # This file
```

## How It Works

1. On startup, client records are loaded from `Client.txt` into memory.
2. The user is prompted to enter their account number and PIN.
3. After a successful login, the main menu is displayed.
4. All balance changes (withdrawals and deposits) are immediately saved back to `Client.txt`.
