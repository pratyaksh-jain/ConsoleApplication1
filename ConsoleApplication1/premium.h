#pragma once

#include<iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include"policy.h"

using namespace std;

void payment(float res);
//Accidental death benefit rider
float adb() {

	float initialCoverage;
	float result;
	cout << "Enter Initial Coverage (Minimum Coverage 25,000): \n";
	cin >> initialCoverage;

	result = 100000 + (initialCoverage / 25000) * 5;
	cout <<"Monthly Premium calculated: "<< result/12 << "\n";
	return result;

}
//Comprehensive care rider
float cc() {
		float initialCoverage;
		float result;
		cout << "Enter Initial Coverage (Minimum Coverage 2,00,000): \n";
		cin >> initialCoverage;



		if (initialCoverage == 200000) {
			result = 100000 + 80;
			cout << "Monthly Premium calculated: " <<result/12<<"\n";
			
		}
		else {
			result = 100000 + (initialCoverage / 300000) * 400;
			cout << "Monthly Premium calculated: " << result/12<<"\n";
		}
		return result;
}

void addRider() {
	sql::Connection* con;

	//driver = sql::mysql::get_mysql_driver_instance();
	//con = driver->connect("tcp://127.0.0.1:3306", "root", "ManUtd@2702");

	// Create and use a specific database
	//con->setSchema("temp");
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;

	/*pstmt = con->prepareStatement("INSERT INTO riders (policy_id, city, education, occupation, premium) VALUES (?,?,?,?,?)");
	pstmt->setInt(1, policy_id );
	pstmt->setString(2, city);
	pstmt->setString(3, education);
	pstmt->setString(4, occupation);
	pstmt->setInt(5, premium);*/
	int choice;

	cout << "Select the rider\n";
	cout << "1. Accidental Death Benifit\n";
	cout << "2. Comprehensive Care\n";
	cout << "Enter choice: ";
	cin >> choice;
	if (choice == 1) {
		payment(adb());
	}
	else if (choice == 2) {
		payment(cc());
	}

}

void payment(float res) {
	//Premium calculation
	string city, education, occupation;
	int choice,ch;
	cout << "Proceed to Payment-> \n";
	cout << "Enter city: \n";
	cin >> city;
	cout << "Enter educational qualification: \n";
	cin >> education;
	cout << "Enter Occupation: \n";
	cin >> occupation;
	cout << "Choose payment mode: \n";
	cout << "1. Cash\n";
	cout << "2. Credit card\n";
	cout << "3. Debit card\n";
	cout << "4. UPI\n";

	cin >> ch;
	cout << "Choose payment arrangement: \n";
	cout << "1. Monthly\n";
	cout << "2. Half-yearly\n";
	cout << "3. Annual\n";
	long float pre = (res/12) + (0.18 * (res/12));
	cin >> choice;
	if (choice == 1) {
		cout << "Monthly Premium after tax= " << pre<<"\n";
		cout << "Premium for monthly: " << pre<<"\n";

	}
	else if (choice == 2) {
		cout << "Premium after tax= " << pre<<"\n";
		cout << "Premium for half-yearly: " << (pre) * 6 - (0.1 * pre)<<"\n";
	}
	else if (choice == 3) {
		cout << "Premium after tax= " << pre << "\n";
		cout << "Premium for yearly: " << (pre) * 12 - (0.15 * pre)<<"\n";
	}
	
	
}

