#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "approverDashboard.h"
#include "policy.h"
using namespace std;

int approver() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "ManUtd@2702");

    // Create and use a specific database
    con->setSchema("temp");

   
    cout << "Press 1 to sign-in: ";
    int choice, aid, cid;
    cin >> choice;
    
    if ( choice == 1) {
        // Sign Up Logic
        sql::ResultSet* res;
        sql::ResultSet* res1;

        string name, password;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> password;
        // Perform MySQL INSERT query to add user to the database
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;

        pstmt = con->prepareStatement("INSERT INTO approver (name, password) VALUES (?,?)");

        pstmt->setString(1, name);
        pstmt->setString(2, password);
        res = pstmt->executeQuery();
        delete pstmt;
        cout <<name << "\n";
        pstmt = con->prepareStatement("SELECT * from approver");
        res = pstmt->executeQuery();
        int id = 0;
        while (res->next())
            id = res->getInt(1);
        
        cout << "Sign in successful!\n";
        //calling function from approverDashboard.h
        approvePolicy();
        delete res;
        delete pstmt;
    }
    //else if (choice == 2) {
    //    // Sign In Logic
    //    int aid;
    //    string name, password;
    //    cout << "Enter username: ";
    //    cin >> name;
    //    cout << "Enter password: ";
    //    cin >> password;

    //    // Perform MySQL SELECT query to check user credentials
    //    sql::Statement* stmt;
    //    sql::ResultSet* res;
    //    sql::PreparedStatement* pstmt;
    //    pstmt = con->prepareStatement("SELECT * from approver where aid= (?) ;");
    //    pstmt->setInt(1, aid);
    //    res = pstmt->executeQuery();

    //    if (res->next()) {
    //        cout << "Sign in successful!\n";
    //        cout << res->getString(2) << "\n";
    //        approvePolicy();
    //    }
    //    else {
    //        cout << "Sign in failed. Invalid credentials.\n";
    //    }

    //    delete res;
    //    delete pstmt;
    //}

    delete con;

    return 0;
}