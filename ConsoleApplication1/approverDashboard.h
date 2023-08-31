#pragma once
#include<iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
using namespace std;

void approvePolicy() {
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "ManUtd@2702");
	cout << "List of policies to be approved:\n";
	con->setSchema("temp");
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	pstmt = con->prepareStatement("SELECT * from policies where approved=0 and cancelled=0");

	res = pstmt->executeQuery();
	while (res->next()) {
		cout << "Client id:" << res->getInt(1) << "\n";
		cout << "Policy id:" << res->getInt(5) << "\n";
		cout << "Name: " << res->getString(6) << "\n\n";

	}
	cout << "Enter policy id that needs approval:";
	int pid;
	cin >> pid;
	pstmt = con->prepareStatement("SELECT * from policies where policy_id = (?)");
	pstmt->setInt(1, pid);
	res = pstmt->executeQuery();
	if (res->next()) {
		//Policy details are mentioned
		cout << "Client id:" << res->getInt(1) << "\n";
		cout << "Age:" << res->getInt(2) << "\n";
		cout << "Sum assured:" << res->getInt(3) << "\n";
		cout << "Policy id:" << res->getInt(5) << "\n";
		cout << "Name: " << res->getString(6) << "\n";
		cout << "Surname: " << res->getString(7) << "\n\n";

		cout << "Approve policy?\n";
		bool approval=true;
		cin >> approval;
		if (approval) {
			pstmt = con->prepareStatement("UPDATE policies SET approved = (?) WHERE policy_id = (?)");
			pstmt->setInt(1, 1);
			pstmt->setInt(2, pid);
			pstmt->executeQuery();
		}
	}
	delete pstmt;
	delete res;
	delete con;
}