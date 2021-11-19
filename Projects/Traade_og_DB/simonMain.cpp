#include <mysql.h>
#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include <chrono>
#include <string>
#include <iomanip>

#include "Random.h"

using namespace std;

mutex mu;

MYSQL* _conn = mysql_init(0);
MYSQL_ROW _row;
MYSQL_RES* _res;
int _qstate;

bool connectToDatabase() {
	// Connects to the database with the credentials: host(localhost), user(root), password(root), database(testdb), port(3306)
	_conn = mysql_real_connect(_conn, "localhost", "root", "root", "simonsbiler", 3306, NULL, 0);
	if (_conn) {
		std::cout << "Successful connection to database!" << std::endl;
		return true;
	}

	puts("Connection to database has failed!");
	return false;
}

bool readFromDatabase() {
	unique_lock<mutex> ul(mu);
	std::string query;
	query = "SELECT * FROM bil";
	// Konvertering da mysql_query tager en const char* som parameter
	const char* q = query.c_str();
	// Executes the SQL statement q
	_qstate = mysql_query(_conn, q);
	if (!_qstate) {
		// After every query, we need to store the result. This function stores synchronous
		_res = mysql_store_result(_conn);
		// fetch_row retrieves the next row of the result set. Returns NULL if there are no more rows to retrieve
		while (_row = mysql_fetch_row(_res)) {
			// The quotations specifies the form and the datatypes (%s = string of chars), and row[0-2] where to get the data from,
			// then prints to terminal with the specifications
			printf("Car ID: %s, Registration nr.: %s, Model: %s, Year: %s\n", _row[0], _row[1], _row[2], _row[3]);
		}
		return true;
	}
	else {
		std::cout << "Query failed: " << mysql_error(_conn) << std::endl;
		return false;
	}
}

bool insertIntoDatabase(const std::string& reg, const std::string& model, const std::string& aar) {
	std::string query = "INSERT INTO bil (registreringsnr, model, aargang) VALUES ();";
	std::string values = "\"" + reg + "\", " + "\"" + model + "\", " + aar;
	query.insert(58, values);
	// Konvertering da mysql_query tager en const char* som parameter
	const char* q = query.c_str();
	// Executes the SQL statement q
	_qstate = mysql_query(_conn, q);
	if (!_qstate) {
		// After every query, we need to store the result. This function stores synchronous
		_res = mysql_store_result(_conn);
		return true;
	}
	else {
		std::cout << "Query failed: " << mysql_error(_conn) << std::endl;
		return false;
	}
}

bool make100inserts() {
	unique_lock<mutex> ul(mu);
	for (int i{}; i < 100; i++) {
		insertIntoDatabase(Random::numberPlateGenerator(), Random::randomModelGenerator(), Random::randomYearGenerator());
	}
	return true;
	std::cout << "Nae! Se hvad jeg fandt paa lossepladsen! Saa der nye varer på lageret!" << std::endl;
}

void createIfNotExist() {
	std::string query = "create table if not exists bil	(bil_id int not null auto_increment, registreringsnr char(7) not null, model char(20) not null, aargang int not null, primary key(bil_id));";
	// Konvertering da mysql_query tager en const char* som parameter
	const char* q = query.c_str();
	// Executes the SQL statement q
	_qstate = mysql_query(_conn, q);
	if (!_qstate) {
		// After every query, we need to store the result. This function stores synchronous
		_res = mysql_store_result(_conn);
	}
	else {
		std::cout << "Query failed: " << mysql_error(_conn) << std::endl;
	}
}

// Requires safemode turned off in SQL-Workbench
bool deleteGolf() {
	unique_lock<mutex> ul(mu);
	std::string query = "DELETE FROM bil WHERE model = 'VW Golf 1 GTI';";
	const char* q = query.c_str();
	_qstate = mysql_query(_conn, q);
	if (!_qstate) {
		_res = mysql_store_result(_conn);
		cout << "Saa der skrot-penge!" << endl;
		return true;
	}
	else {
		std::cout << "Query failed: " << mysql_error(_conn) << std::endl;
		return false;
	}
}

bool brugtvognsforhandlermagi() {
	unique_lock<mutex> ul(mu);
	std::string query = "UPDATE bil SET aargang = 2005 WHERE aargang = 1980;";
	const char* q = query.c_str();
	_qstate = mysql_query(_conn, q);
	if (!_qstate) {
		_res = mysql_store_result(_conn);
		cout << "God som ny!" << endl;
		return true;
	}
	else {
		std::cout << "Query failed: " << mysql_error(_conn) << std::endl;
		return false;
	}
}

bool selectSuzuki() {
	unique_lock<mutex> ul(mu);
	std::string query = "SELECT bil_id, model, registreringsnr, aargang FROM bil WHERE model = 'Suzuki Alto' AND aargang = 1985;";
	const char* q = query.c_str();
	// Executes the SQL statement q
	_qstate = mysql_query(_conn, q);
	if (!_qstate) {
		// After every query, we need to store the result. This function stores synchronous
		_res = mysql_store_result(_conn);
		// fetch_row retrieves the next row of the result set. Returns NULL if there are no more rows to retrieve
		while (_row = mysql_fetch_row(_res)) {
			// The quotations specifies the form and the datatypes (%s = string of chars), and row[0-2] where to get the data from,
			// then prints to terminal with the specifications
			printf("Car ID: %s, Registration nr.: %s, Model: %s, Year: %s\n", _row[0], _row[1], _row[2], _row[3]);
		}
		return true;
	}
	else {
		std::cout << "Query failed: " << mysql_error(_conn) << std::endl;
		return false;
	}
}

void createIndex() {
	std::string query = "CREATE INDEX mitindex ON bil(bil_id, model, aargang);";
	const char* q = query.c_str();
	_qstate = mysql_query(_conn, q);
	if (!_qstate) {
		_res = mysql_store_result(_conn);
		cout << "Indexes added!" << endl;
	}
	else {
		std::cout << "Query failed: " << mysql_error(_conn) << std::endl;
	}

	query = "CREATE UNIQUE INDEX mitandetindex ON bil(registreringsnr);";
		q = query.c_str();
	_qstate = mysql_query(_conn, q);
	if (!_qstate) {
		_res = mysql_store_result(_conn);
		cout << "Indexes added!" << endl;
	}
	else {
		std::cout << "Query failed: " << mysql_error(_conn) << std::endl;
	}
}

int main() {
	clock_t start, end;
	start = clock();

	connectToDatabase();
	createIfNotExist();
	createIndex();
    make100inserts();

	// KODE DER VIRKER!!!!
	// Seeds the random generation to current time
	srand((unsigned)time(NULL));

	//thread t2(brugtvognsforhandlermagi);
	//thread t3(deleteGolf);
	//thread t1(make100inserts);
	//thread t4(readFromDatabase);

	thread t1(selectSuzuki);

	t1.join();
	//t2.join();
	//t3.join();
	//t4.join();


	end = clock();
	// Calculating total time taken by the program.
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken by program is : " << fixed
		 << time_taken << setprecision(5);
	cout << " sec " << endl;
	
	return 0;
}