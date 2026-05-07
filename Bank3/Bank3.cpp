
#include <iostream>
#include<vector>
#include<fstream>
#include<string>
#include <iomanip>
#include <cmath>
using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
 enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3,
     eShowMainMenue = 4 };
 enum enMainMenueOptions {
     eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
     eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eManageUsers = 7, eLogin = 8, eExit = 9
};

enum enManageUsersOptions{ eListUsers = 1, eAddNewUsers = 2, eDeleteUsers = 3,
    eUpdateUsers = 4, eFindUsers = 5, eShowMainuMenue = 6};

enum enMainMenuePermissions {
    eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient= 4,
    pUpdateClients = 8, pFindClient = 16, pTranactions = 32,
    pManageUsers = 64
};

bool CheckAccessPermission(enMainMenuePermissions OpetionPermissions);
void StateAccess();
struct stUser
{
    string UserName="";
    string Password = "";
    int Permissions = 0;
    bool MarkForDelete = false;
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;


};

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; 

  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); 
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length()); 
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;

}

stClient ConvertLineToRecord(string Line, string Delim = "#//#")
{
    vector<string> vClintInfo = SplitString(Line, Delim);

    stClient ClintInfo;

    ClintInfo.AccountNumber = vClintInfo.at(0);
    ClintInfo.PinCode= vClintInfo.at(1);
    ClintInfo.Name = vClintInfo.at(2);
    ClintInfo.Phone = vClintInfo.at(3);

    ClintInfo.AccountBalance =stod( vClintInfo.at(4));


    return ClintInfo;

}

string ConvertRecordToLine(stClient Client, string Delim = "#//#")
{
    string Line;

    Line = Client.AccountNumber + Delim;
    Line+= Client.PinCode + Delim;
    Line += Client.Name + Delim;
    Line += Client.Phone + Delim;
    Line +=to_string( Client.AccountBalance) ;

    return Line;
}

bool ClintExistByAccountNumber(string Accountnumber,string filename)
{
    vector< stClient> vClients;
    fstream myFile;
    myFile.open(filename, ios::in);
    if (myFile.is_open())
    {
        string line;
        stClient sClient;

        while (getline(myFile, line))
        {

            sClient =  ConvertLineToRecord(line);
            if (sClient.AccountNumber == Accountnumber)
            {
                myFile.close();
                return true;


            }
            vClients.push_back(sClient);

        }
        myFile.close();


    
    }
    return false;

}

stClient ReadNewClient()
{
    stClient  Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClintExistByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
     }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

       


}

vector <stClient> LoadCleintsDataFromFile(string filename)
{
    vector <stClient> vClient;
    fstream MyFile;
    MyFile.open(filename,ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stClient Clients;

        while (getline(MyFile,Line) )
        {
            Clients = ConvertLineToRecord(Line);

            vClient.push_back(Clients);
        }
        MyFile.close();





    }
    return vClient;

}

void PrintClientRecordLine(stClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;


}

/*****/void PrintClientRecordBalanceLine(stClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowAllClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
    {
        StateAccess();
        return;

    }

    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (stClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowTotalBalances()
{

    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (stClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)

{
    for (stClient &sClient : vClients)
    {
        if (sClient.AccountNumber == AccountNumber)
        {
            Client = sClient;
            return true;

        }
      }

    return false;


}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

  
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            Client.MarkForDelete = true;
            return true;
        }
    }

    return false;


}

vector <stClient> SaveCleintsDataToFile(string FileName, vector <stClient> vClients)
{
    fstream MyFile;

    MyFile.open(FileName,ios::out);
    
    if (MyFile.is_open())
    {

        string Line;
        for (stClient Client : vClients)
        {
            if (Client.MarkForDelete == false)
            {
                Line = ConvertRecordToLine(Client);
                MyFile << Line << endl;
            }
        }
        MyFile.close();
    }

    return vClients;

}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{
    stClient Clint = ReadNewClient();
     string Line =ConvertRecordToLine(Clint);

     AddDataLineToFile(ClientsFileName, Line);


}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    stClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    char  Answer;
    stClient sClient;
    if (FindClientByAccountNumber(AccountNumber, vClients, sClient))
    {
        PrintClientCard(sClient);

        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);

            

            cout << "\n\nClient Deleted Successfully.";
            return true;


        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }




   }
    
string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void ShowDeleteClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
    {
        StateAccess();
        return;

    }
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
    {
        StateAccess();
        return;

    }
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
    {
        StateAccess();
        return;

    }
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();

}

void ShowFindClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
    {
        StateAccess();
        return;

    }
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)\n";
    cout << "     Designed By ZIAD HEGAGY";
    cout << "\n-----------------------------------\n";

}


bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClient>& vClients)
{


    char Answer = 'n';


    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }


        return false;
    }

}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    stClient Client;

    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }


    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    stClient Client;

    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();

}

//------------------------------------

stUser ConvertLineToRecordUsers(string Line, string Delim = "#//#")
{
    vector <string > Words = SplitString(Line, Delim);

    stUser sUser;
    sUser.UserName = Words.at(0);
    sUser.Password = Words.at(1);
    sUser.Permissions = stoi(Words.at(2));
    return sUser;

}

string convertRecordUsersToLine(stUser User, string Delim = "#//#")
{
    return (User.UserName + Delim + User.Password + Delim + to_string(User.Permissions));

}

vector< stUser> LoadDataUsersFromFile(string FileName)
{
    vector< stUser> vUser;

    fstream UsersFile;

    UsersFile.open(FileName, ios::in);
    if (UsersFile.is_open())
    {
        string Line;

        stUser sUser;

        while (getline(UsersFile, Line))
        {
            sUser = ConvertLineToRecordUsers(Line);
            vUser.push_back(sUser);

        }
        UsersFile.close();
    }

    return vUser;


}

bool UserExistByUserName(string UserName, string filename)
{
    vector< stUser> vUsers;
    fstream myFile;
    myFile.open(filename, ios::in);
    if (myFile.is_open())
    {
        string line;
        stUser sUsers;

        while (getline(myFile, line))
        {

            sUsers = ConvertLineToRecordUsers(line);
            if (sUsers.UserName== UserName)
            {
                myFile.close();
                return true;


            }
            vUsers.push_back(sUsers);

        }
        myFile.close();



    }
    return false;

}

//------------Add--------------
bool ReadChoiceY_N(string Message)
{
    char c = 'y';
    cout << Message;
    cin >> c;

    if (c == 'y' || c == 'Y')
        return true;
    else
        return false;


}

int ReadUserPermission()
{
    int per=0;

    if (ReadChoiceY_N("\nDo You Want to give  full Access (y or n): "))
        return -1;

    cout << "\nDo You Want to give  full Access to:\n";

    if (ReadChoiceY_N("\nShow Client List (y or n): "))
        per |= enMainMenuePermissions::pListClients;
    if (ReadChoiceY_N("\nAdd New Client (y or n): "))
        per |= enMainMenuePermissions::pAddNewClient;
    if (ReadChoiceY_N("\nDelete Client (y or n): "))
        per |= enMainMenuePermissions::pDeleteClient;
    if (ReadChoiceY_N("\nUpdate Client Info (y or n): "))
        per |= enMainMenuePermissions::pUpdateClients;
    if (ReadChoiceY_N("\nFind Client (y or n): "))
        per |= enMainMenuePermissions::pFindClient;
    if (ReadChoiceY_N("\nTransactions (y or n): "))
        per |= enMainMenuePermissions::pTranactions;
    if (ReadChoiceY_N("\nManage Users (y or n): "))
        per |= enMainMenuePermissions::pManageUsers;

    return per;

}

stUser ReadNewUser()
{
    stUser sUser;
    cout << "Enter User Name: ";
   getline( cin >>ws, sUser.UserName);

    while (UserExistByUserName(sUser.UserName, UsersFileName))
    {

        cout << "\nUser with [" << sUser.UserName << "] already exists.\nEnter another User Name? ";
        getline(cin >> ws, sUser.UserName);
    }
    cout << "\nEnter Password: ";
    getline(cin >> ws, sUser.Password);

    sUser.Permissions = ReadUserPermission();

    return sUser;

}

void AddNewUser()
{
    stUser sUser = ReadNewUser();

    string line = convertRecordUsersToLine(sUser);
    AddDataLineToFile(UsersFileName,line);
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {

        cout << "Adding New User: \n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

void ShowAddUsersScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Users Screen";
    cout << "\n-----------------------------------\n";
    
    AddNewUsers();


}
//-----------------------------------

//---------------List-----------------
void PrintClientRecordLine(stUser  User)
{

    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permissions;
  

}
void ShowAllUsersScreen()
{
    vector< stUser> vUser = LoadDataUsersFromFile(UsersFileName);
    cout << "\n\t\t\t\t\tUsers List (" << vUser.size() << ") Users(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permission";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


    if (vUser.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else
    {
        for (stUser sUser : vUser)
        {
            PrintClientRecordLine(sUser);
            cout << endl;

        }
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
//--------------------------------------
 
string RaedUserName()
{
    string Name;
    cout << "\nPlease Enter User Name : ";
    getline(cin >>ws, Name);
    cout << endl;
    return Name;
}

//---------------Delete------------------------
bool FindUserByUserName(string UserName, vector <stUser > vUsers, stUser& User)
{
    for (stUser& sUser : vUsers)
    {
        if (sUser.UserName == UserName)
        {
            User = sUser;
            return true;

        }
    }
    return false;

}

bool MarkForDeletUserbyUserName(string UserName, vector <stUser >& vUsers)
{
    for (stUser &User : vUsers)
    {
        if (User.UserName == UserName)
        {
            User.MarkForDelete = true;
            return true;
        }


     }
    return false;

}

vector< stUser> SaveUsersToFile(string FileName, vector <stUser > vUsers)
{
    fstream UsersFile;

    UsersFile.open(FileName, ios::out );
    if (UsersFile.is_open())
    {
        string line;
        for (stUser U : vUsers)
        {
            if (U.MarkForDelete == false)
            {
                line=  convertRecordUsersToLine(U);
                UsersFile << line << endl;

            }
        }
     }
    return vUsers;

}

void PrintUserInfo(stUser User)
{
    cout << "\n__________________User Information___________________\n";
    cout << "\nUser Name   : " << User.UserName;
    cout << "\nPassword    : " << User.Password;
    cout << "\nPermissions : " << User.Permissions;
    cout << "\n___________________________________________________________\n";
}

bool DeleteUserByUserName(string UserName, vector <stUser > &vUsers)
{
    stUser sUser;
    if (UserName == "admin")
    {
        cout << "\nYou Can NOT Delete This User";
        return false;
    }
    if (FindUserByUserName(UserName, vUsers, sUser))
    {
        PrintUserInfo(sUser);
        if (ReadChoiceY_N("\nAre You Sure Want Delete This User (Y or N): "))
        {
            MarkForDeletUserbyUserName(UserName, vUsers);
            SaveUsersToFile(UsersFileName, vUsers);


            vUsers= LoadDataUsersFromFile(UsersFileName);
            cout << "\n\nUser Deleted Successfully.";
            return true;
        }


    }
    else
    {
        cout << "\nClient with Account Number (" << UserName << ") is Not Found!";
        return false;
    }
     


}

void DeleteUser()
{
    vector <stUser >  Users = LoadDataUsersFromFile(UsersFileName);
    DeleteUserByUserName(RaedUserName(), Users);
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    DeleteUser();


}

//--------------------------------------

//----------------Update-----------------------
stUser ReadUpdateuser(string UserName)
{

    stUser sUser;
    sUser.UserName = UserName;

    cout << "Enter New Passwrd: ";
     getline( cin >>ws, sUser.Password);
     cout << endl;

     sUser.Permissions = ReadUserPermission();

     return sUser;



}

bool UpdaateUserInfo(string UserName,vector <stUser> &vUsers)
{
    stUser sUser;
    if (FindUserByUserName(UserName, vUsers, sUser))
    {
        PrintUserInfo(sUser);
        if (ReadChoiceY_N("\nAre You Sure Want Update Information This User (Y or N): "))
        {
            
            for (stUser& U : vUsers)
            {

                if (U.UserName == UserName)
                {
                    U = ReadUpdateuser(UserName);
                    break;
                }
            }

            SaveUsersToFile(UsersFileName, vUsers);


           
            cout << "\n\nUser Update Successfully.";
            return true;
        }


    }
    else
    {
        cout << "\nUser with Account Number (" << UserName << ") is Not Found!";
        return false;
    }




}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> Users = LoadDataUsersFromFile(UsersFileName);
    

    UpdaateUserInfo(RaedUserName(), Users);

}
//--------------------------------------

//------------Find----------------
void FindUser(string UserName, vector <stUser> vUsers)
{
    stUser sUser;
    if (FindUserByUserName(UserName, vUsers, sUser))
    {
        PrintUserInfo(sUser);
    }
    else
        cout << "\nUser with Account Number (" << UserName << ") is Not Found!";
   

}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> Users = LoadDataUsersFromFile(UsersFileName);

    FindUser(RaedUserName(),Users);

}

//--------------------------------------


//&&&&&&&&&&&&&&&&&&&&&&&%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&%%%%%%%%%%%&$$$$$$$


//----------------------------------
void ShowTransactionsMenue();
void GoBackToMainMenue();
void ShowMainMenue();
void ShowManageUserMenue();

int G_PermissionUser = 0;

//------------------------------------


//___________________Login___________________________
bool find(string UserName, string Password, int& Permission)
{
    vector< stUser> sUsers;
    stUser sUser;

    bool flag = false;

    sUsers = LoadDataUsersFromFile(UsersFileName);

    flag = FindUserByUserName(UserName, sUsers, sUser);

    if (flag && Password == sUser.Password)
    {
        Permission = sUser.Permissions;
        return true;
    }

    return false;
}

string ReadPassword()
{
    string Password;
    cout << "Enter Password: ";
    
    getline(cin >> ws, Password);
    return Password;
}

void Login()
{
    string UserName = RaedUserName();
    string Password = ReadPassword();

    while (!find(UserName, Password, G_PermissionUser))
    {
        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\tLogin Screen :-)";
        cout << "\n-----------------------------------\n";
        
        cout << "\nInvlaid User Name / Password .\n";
        UserName = RaedUserName();
        Password = ReadPassword();
    }

    ShowMainMenue();

}

void ShowLoginScreen()
{
    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\tLogin Screen :-)";
    cout << "\n-----------------------------------\n";
    Login();


}

//---------------------------------------------------


bool CheckAccessPermission(enMainMenuePermissions OpetionPermissions)
{
    int Permissions = G_PermissionUser;

    if (Permissions == enMainMenuePermissions::eAll)
        return  true;


    //int p = 1 << (Choice - 1);

    if (( OpetionPermissions & Permissions) == OpetionPermissions)
        return true;

    else
        return false;



}

void StateAccess()
{
    system("cls");
    cout << "\n_________________________________________________________________________________\n";
    cout << "Access Denied,\nYou don`t Have Permission To Do This,\nPlease Contact Your Admin\n";
    cout << "_________________________________________________________________________________\n\n";
    GoBackToMainMenue();
}



//_________________Manage______________________

short ReadManageUsersMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void GoBackToManageUsersMenue()
{
    cout << "\n\nPress any key to go back to ManageUsers Menue...";
    system("pause>0");
    ShowManageUserMenue();
}

void PerfromManageUsersMenueOption(enManageUsersOptions ManageUsersOptions)
{
    
    switch (ManageUsersOptions)
    {
    case enManageUsersOptions::eListUsers:
    {
        system("cls");
        ShowAllUsersScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eAddNewUsers:
    {
        system("cls");
        ShowAddUsersScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case  enManageUsersOptions::eDeleteUsers:
    {
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eUpdateUsers:
    {
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eFindUsers:
    {
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenue();
        break;

    }
    case enManageUsersOptions::eShowMainuMenue:
    {
        system("cls");
        ShowMainMenue();
        break;

    }

    }

}

void ShowManageUserMenue()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
    {
        StateAccess();
        return;

    }
    system("cls");
    cout << "===========================================\n";
    cout << "\t  Manage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Users List.\n";
    cout << "\t[2] Add New Users.\n";
    cout << "\t[3] Delete Users.\n";
    cout << "\t[4] Update Users Info.\n";
    cout << "\t[5] Find Users.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";
    PerfromManageUsersMenueOption((enManageUsersOptions)ReadManageUsersMenueOption());

}
//-------------------------------------------


//_________________Transactions______________
short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();

}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
   
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {

        ShowMainMenue();

    }
    }

}

void ShowTransactionsMenue()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pTranactions))
    {
        StateAccess();
        return;

    }
    system("cls");
    cout << "===========================================\n";
    cout << "\t Transactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}
//-------------------------------------------


//__________________Main________________________
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 9]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
        ShowTransactionsMenue();
        break;
    case enMainMenueOptions::eManageUsers:
        system("cls");
        ShowManageUserMenue();
        break;

    case enMainMenueOptions::eLogin:
        system("cls");
        ShowLoginScreen();
        break;
    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;
    }

}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t   Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "\t[9] Exit.\n";
    cout << "===========================================\n";

   
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());

}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}
//-------------------------------------------


int main()
{
   
    ShowLoginScreen();
    system("pause>0");
    return 0;
}

