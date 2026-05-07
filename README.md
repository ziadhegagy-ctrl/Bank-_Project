🏦 MyBank - Banking Management System
A console-based banking management system built with C++ that handles client accounts, transactions, and user access control.
> Designed by **ZIAD HEGAGY**
---
📋 Table of Contents
About
Features
Project Structure
Requirements
How to Run
Default Login
Permissions System
File Storage
---
📌 About
MyBank is a C++ console application that simulates a simple bank management system. It supports multiple users with different permission levels, allowing admins to manage clients, perform transactions, and control user access.
---
✨ Features
👤 Client Management
List Clients – View all registered clients with account details
Add New Client – Register a new client with account number, PIN, name, phone, and balance
Delete Client – Remove a client by account number (with confirmation)
Update Client Info – Modify existing client data
Find Client – Search for a client by account number
💰 Transactions
Deposit – Add funds to a client's account
Withdraw – Deduct funds (validates balance before withdrawal)
Total Balances – View total balance across all accounts
🔐 User Management
List Users – View all system users
Add New User – Create a user with custom permissions
Delete User – Remove a system user
Update User Info – Modify user credentials or permissions
Find User – Search for a user by username
---
🗂️ Project Structure
```
MyBank/
│
├── MyBank3.cpp         # Main source file (all logic)
├── Clients.txt         # Database file for client records (auto-created)
├── Users.txt           # Database file for user accounts (auto-created)
└── README.md
```
---
⚙️ Requirements
OS: Windows (uses `system("cls")` and `system("pause")`)
Compiler: Any C++11 compatible compiler (e.g., GCC, MSVC)
IDE: Visual Studio, Code::Blocks, or any C++ IDE
---
🚀 How to Run
Using g++ (Command Line)
```bash
# 1. Clone the repository
git clone https://github.com/your-username/MyBank.git
cd MyBank

# 2. Compile the project
g++ MyBank3.cpp -o MyBank

# 3. Run the program
./MyBank
```
Using Visual Studio
Open Visual Studio
Create a new Console Application project
Replace the default `.cpp` file content with `MyBank3.cpp`
Press Ctrl + F5 to build and run
Using Code::Blocks
Create a new Console Application project
Add `MyBank3.cpp` to the project
Press F9 to build and run
---
🔑 Default Login
When the program starts, you will see the Login Screen.
Field	Value
Username	`admin`
Password	`1234`
> ⚠️ Make sure the `Users.txt` file contains the admin credentials before first run, or add them manually in the format:
> ```
> admin#//#1234#//#-1
> ```
> The `-1` means **full access** to all features.
---
🔒 Permissions System
User permissions are stored as bitwise flags:
Permission	Value
List Clients	1
Add New Client	2
Delete Client	4
Update Client	8
Find Client	16
Transactions	32
Manage Users	64
Full Access	-1
Permissions are combined using bitwise OR. For example, a user with List + Transactions access has permission value `33` (1 + 32).
---
💾 File Storage
Data is stored in plain text files using `#//#` as a delimiter.
Clients.txt format:
```
AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
```
Users.txt format:
```
UserName#//#Password#//#Permissions
```
---
📞 Contact
For any issues or contributions, feel free to open a pull request or issue on GitHub.
