#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include "Client.h"
#include "approver.h"
using namespace std;

//for demonstration only. never save your password in the code!
const string server = "tcp://localhost";
const string username = "root";
const string password = "ManUtd@2702";


//int main()
//{
//    sql::Driver* driver;
//    sql::Connection* con;
//    sql::Statement* stmt;
//    sql::PreparedStatement* pstmt;
//
//    try
//    {
//        driver = get_driver_instance();
//        con = driver->connect(server, username, password);
//    }
//    catch (sql::SQLException e)
//    {
//        cout << "Could not connect to server. Error message: " << e.what() << endl;
//        system("pause");
//        exit(1);
//    }
//
//    //please create database "quickstartdb" ahead of time
//    con->setSchema("temp");
//
//    stmt = con->createStatement();
//    stmt->execute("DROP TABLE IF EXISTS inventory");
//    cout << "Finished dropping table (if existed)" << endl;
//    stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
//    cout << "Finished creating table" << endl;
//    delete stmt;
//
//    pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
//    pstmt->setString(1, "banana");
//    pstmt->setInt(2, 150);
//    pstmt->execute();
//    cout << "One row inserted." << endl;
//
//    pstmt->setString(1, "orange");
//    pstmt->setInt(2, 154);
//    pstmt->execute();
//    cout << "One row inserted." << endl;
//
//    pstmt->setString(1, "apple");
//    pstmt->setInt(2, 100);
//    pstmt->execute();
//    cout << "One row inserted." << endl;
//
//    delete pstmt;
//    delete con;
//    system("pause");
//    return 0;
//}
//Driver function
int main(int cid) {
	//Connecting to mysql server
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "ManUtd@2702");
	int choice = 0;
	do {
		//Main menu
		cout << "\n\nMain Menu\n\n";
		cout << "1. Client login\n";
		cout << "2. Approver login\n";
		cout << "3. View existing clients\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: \n";
		cin >> choice;
		if (choice == 1) {
			//Calling from client.h
			connect(cid);
		}
		else if (choice == 2) {
			cout << "Welcome Approver\n";
			//calling function from approver.h
			approver();
		}
		else if (choice == 3) {
			cout << "List of clients: \n\n";
			con->setSchema("temp");
			sql::Statement* stmt;
			sql::PreparedStatement* pstmt;
			sql::ResultSet* res;
			pstmt = con->prepareStatement("SELECT * from clients ");
			
		//	cout << cid;

			res = pstmt->executeQuery();

			while (res->next()) {
				cout << "Client id: " << res->getInt(1) << "\t";
				cout << "Username: " << res->getString(3) << "\n";
			}
			delete pstmt;
			delete res;
			delete con;

		
		}
	} while (choice);


	cout << "\n\n\nGood-Bye!";
	_getch();
}