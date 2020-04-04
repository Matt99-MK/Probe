/////////////////////////////////////////////////////////////////////////////
//
// Simple class for MySQL connection using POCO.
//
/////////////////////////////////////////////////////////////////////////////

#include "Poco/Data/Session.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Exception.h"
#include <Poco/Data/RecordSet.h>
#include <Poco/Dynamic/Var.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

#ifndef _DTBCNT_H
#define _DTBCNT_H
class DatabaseConnection
{
public:

	enum
	{
		DROP_TO_DEFAULT_FILE = 0,
		DROP_TO_DEFAULT_OUTPUT
	};

	DatabaseConnection();
	~DatabaseConnection();

	DatabaseConnection(std::string host = "192.168.0.105", std::string port = "3306", std::string db = "Users",
		std::string user = "Mateusz", std::string password = "XXXXXXX");

	void ShowAll(std::string table, int drop = DROP_TO_DEFAULT_OUTPUT);
	std::vector<std::string> CollectIP(void);
	Poco::Tuple<int, std::string, std::string, std::string, std::string>
		SelectOne(int ID);
	std::string GetIDFromIP(std::string text);
	void X(void);
	bool Insert(int ID, std::string Name, std::string Surname, std::string IP, std::string City);

private:
	Session* session;
};

#endif
