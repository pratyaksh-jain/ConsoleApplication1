#pragma once
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <conio.h>
#include "premium.h"
#include<fstream>

using namespace std;

int choice,ch,cid, age, sum, premium = 100000;
string fname, lname, tobacco, phone, rider;
void dashboard(int cid) {
	//Client dashboard
	cout << "Welcome to dashboard!\n";
	cout << "1. List of policies\n";
	cout << "2. Create new policy\n";
	cout << "3. Cancel policy\n";

	cout << "Enter your choice\n";
	cin >> choice;
	//Insert query
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "ManUtd@2702");

	if (choice == 1) {
		//Shows list of policies for the client
		cout << "List of policies:\n";
		con->setSchema("temp");
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* res;
		pstmt = con->prepareStatement("SELECT * from policies where cid=(?)");
		pstmt->setInt(1, cid);
		res = pstmt->executeQuery();
		bool bFound = false;
		while (res->next()) {
			bFound = true;
			cout << "Policy id: " << res->getInt(5) << "\n";
			cout << "Policy status: ";
			if (res->getInt(8) && !res->getInt(9)) {
				cout << "Inforce";
			}
			else if (res->getInt(9)) {
				cout << "Cancelled";
			}
			else
				cout << "Pending";

			cout << endl;
		}
		if (!bFound) {
			cout << "\nNo policies found";
			cout << "\nPress any key to continue.....\n";
			_getch();
		}
		delete pstmt;
		delete res;
		delete con;

	}
	else if (choice == 2) {
		//Create new policy
		cout << "Select type of policy:\n";
		cout << "1. Whole life insurance\n";
		cout << "2. Term insurance\n";
		cout << "3. Money bank policy\n";
		cout << "4. Endowment policy\n";
		cin >> ch;
		if (ch == 2) {
			con->setSchema("temp");
			sql::Statement* stmt;
			sql::PreparedStatement* pstmt;
			sql::ResultSet* res;
			pstmt = con->prepareStatement("INSERT INTO policies (cid, age, sum, premium, fname, lname, tobacco, phone_no) VALUES (?,?,?,?,?,?,?,?)");


			cout << "Enter client details\n";
			cout << "Enter first name:\n";
			cin >> fname;
			cout << "Enter last name:\n";
			cin >> lname;
			cout << "Enter client id:\n";
			cin >> cid;
			cout << "Enter age:\n";
			cin >> age;
			cout << "Enter sum assured:\n";
			cin >> sum;
			cout << "Premium: 100000\n";
			
			cout << "Tobacco status:(Y/N)\n";
			cin >> tobacco;
			cout << "Enter phone number: \n";
			cin >> phone;
			cout << "Want to add riders? \n";
			cin >> rider;
			if (rider == "yes") {
				addRider();
			}
			else if (rider == "no") {
				payment(premium);

			}
			pstmt->setInt(1, cid);

			pstmt->setInt(2, age);

			pstmt->setInt(3, sum);
			pstmt->setInt(4, premium);



			pstmt->setString(5, fname);
			pstmt->setString(6, lname);
			pstmt->setString(7, tobacco);
			pstmt->setBigInt(8, phone);
		
			res = pstmt->executeQuery();
			
			
			
			cout << "Policy created for approval! \n";
			pstmt = con->prepareStatement("SELECT * from policies");
			res = pstmt->executeQuery();
			int id = 0;
			
			while (res->next()) 
				id = res->getInt(5);
				//std::string fileName = std::to_string(id);
				//std::ofstream outFile(fileName + ".txt"); 
				// Open file for writing
				/*if (outFile.is_open()) {
					outFile << "Client Name: " << res->getString(6) << std::endl;
					outFile << "Age: " << res->getInt(2) << std::endl;

					outFile << "Smoking Status: " << res->getString(10) << std::endl;
					outFile << "Sum Assured: " << res->getInt(3) << std::endl;
					outFile << "PolicyID: " << res->getInt(5) << std::endl;






					outFile.close();
				}
				else {
					      std::cerr << "Error opening file for writing." << std::endl;
					    }*/
				cout << "Policy id: " << id << "\n";
			
			delete res;
			delete con;
			delete pstmt;
		}
		}
	else if(choice==3) {
		//Cancel policy
		cout << "List of policies:\n";
		con->setSchema("temp");
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* res;
		pstmt = con->prepareStatement("SELECT * from policies where cid=(?)");
		pstmt->setInt(1, cid);
		res = pstmt->executeQuery();
		bool bFound = false;
		while (res->next()) {
			bFound = true;
			cout << "Policy id: " << res->getInt(5) << "\n";
			cout << "Policy status: ";
			if (res->getInt(8) && !res->getInt(9)) {
				cout << "Inforce";
			}
			else if (res->getInt(9)) {
				cout << "Cancelled";
			}
			else
				cout << "Pending";

			cout << endl;
		}
		if (!bFound) {
			cout << "\nNo policies found";
			cout << "\nPress any key to continue.....\n";
			_getch();
		}
		cout << "Enter the policy id to be cancelled: ";
		int polid;
		cin >> polid;
		cout << "Cancel policy?\n";
		bool cancelled = true;
		cin >> cancelled;
		if (cancelled) {
			pstmt = con->prepareStatement("UPDATE policies SET cancelled = (?) WHERE policy_id = (?)");
			pstmt->setInt(1, 1);
			pstmt->setInt(2, polid);
			pstmt->executeQuery();
		}
		delete pstmt;
		delete res;
		delete con;
	}
	
	}
	