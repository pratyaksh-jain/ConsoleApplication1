#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "policy.h"
using namespace std;

int connect(int cid) {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "ManUtd@2702"); 

    // Create and use a specific database
    //Connecting to database
    con->setSchema("temp");


    int choice,aid;
    //Client log in
    cout << "1. Sign Up\n";
    cout << "2. Sign In\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        // Sign Up Logic
        sql::ResultSet* res;
        sql::ResultSet* res1;

        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        // Perform MySQL INSERT query to add user to the database
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
       
        pstmt = con->prepareStatement("INSERT INTO clients (username, password) VALUES (?,?)");
       
        pstmt->setString(1,username);
        pstmt->setString(2,password);
        res=pstmt->executeQuery();
        delete pstmt;
        cout <<"Welcome "<< username << "\n";
        pstmt = con->prepareStatement("SELECT * from clients");
        res = pstmt->executeQuery();
        int id = 0;
        while (res->next())
            id = res->getInt(1);
        cout <<"Client id: "<< id << "\n";
        cout << "Sign up successful!\n";
        //Calling function from policy.h
        dashboard(cid);
    }
    else if (choice == 2) {
        // Sign In Logic
        int cid,aid;
        string username, password;
        cout << "Enter client id: ";
        cin >> cid;
        cout << "Enter password: ";
        cin >> password;

        // Perform MySQL SELECT query to check user credentials
        sql::Statement* stmt;
        sql::ResultSet* res;
        sql::PreparedStatement* pstmt;
        pstmt = con->prepareStatement("SELECT * from clients where cid= (?) ;");
        pstmt->setInt(1, cid);
        res = pstmt->executeQuery();

        if (res->next()) {
            cout << "Sign in successful!\n";
            cout << "Hello "<<res->getString(3) << "\n";
            dashboard(cid);
        }
        else {
            cout << "Sign in failed. Invalid credentials.\n";
        }

        delete res;
        delete pstmt;
    }

    delete con;

    return 0;
}