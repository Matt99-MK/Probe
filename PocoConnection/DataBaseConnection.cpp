#include "DatabaseConnection.h"

DatabaseConnection::DatabaseConnection()
{
	Poco::Data::MySQL::Connector::registerConnector();

	try {
		session = new Session("MySQL", "host = 192.168.0.105; port = 3306; db = Users; user = Mateusz; password = XXXXXXXX; compress = true; auto - reconnect = true");
		session->setFeature("emptyStringIsNull", true);
	}
	catch (Poco::Exception& exp)
	{
		std::cout << exp.displayText() << std::endl;
	}
}

void DatabaseConnection::X(void)
{
	
	try
	{
		*session << "delete from UserData WHERE UserID=?", use(a), now;
	}

	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

DatabaseConnection::DatabaseConnection(std::string host, std::string port, std::string db,
	std::string user, std::string password)
{
	Poco::Data::MySQL::Connector::registerConnector();
	std::string db_connect = "host =" + host + ";port =" + port + ";db=" + db + ";user=" + user + ";password=" + password + ";compress=true;auto-reconnect=true";

	try {
		session = new Session("MySQL", db_connect);
		session->setFeature("emptyStringIsNull", true);
	}

	catch (Poco::Exception& exp)
	{
		std::cout << exp.displayText() << std::endl;
	}
}

DatabaseConnection::~DatabaseConnection()
{
	session->close();
	delete session;
}
void DatabaseConnection::ShowAll(std::string table, int drop)
{
	using namespace Poco::Data;

	Statement select(*session);
	select << "SELECT * FROM %s", table, now;

	RecordSet TableContent(select); //RecordSet keep data associated with the statement

	if (drop == DatabaseConnection::DROP_TO_DEFAULT_OUTPUT)
	{
		std::size_t columns = TableContent.columnCount();
		for (std::size_t clmn = 0; clmn < columns; ++clmn)
		{
			std::cout.width(15);
			std::cout << std::left << TableContent.columnName(clmn);
		}
		std::cout << std::endl;
		std::size_t rows = TableContent.rowCount();
		for (std::size_t rows1 = 0; rows1 < rows; ++rows1)
		{
			std::cout << std::endl;
			std::cout.width(15);

			std::size_t columns = TableContent.columnCount();
			for (std::size_t column = 0; column < columns; ++column)
			{
				Poco::Dynamic::Var value = TableContent.value(column, rows1);
				std::cout.width(15);
				std::cout << std::left << value.convert<std::string>();
			}

			std::cout << std::endl;
		}
	}
	else
	{
		std::ofstream myfile;
		myfile.open("dump.txt", std::ios::trunc | std::ios::binary);

		std::size_t columns = TableContent.columnCount();
		for (std::size_t clmn = 0; clmn < columns; ++clmn)
		{
			myfile.width(15);
			myfile << std::left << TableContent.columnName(clmn);
		}
		myfile << std::endl;
		std::size_t rows = TableContent.rowCount();

		for (std::size_t rows1 = 0; rows1 < rows; ++rows1)
		{
			myfile << std::endl;
			myfile.width(15);
			std::size_t columns = TableContent.columnCount();
			for (std::size_t column = 0; column < columns; ++column)
			{
				Poco::Dynamic::Var value = TableContent.value(column, rows1);
				myfile.width(15);
				myfile << std::left << value.convert<std::string>();
			}

			myfile << std::endl;
		}

		myfile.close();
	}
}

Poco::Tuple<int, std::string, std::string, std::string, std::string> DatabaseConnection::SelectOne(int ID)
{
	typedef Poco::Tuple<int, std::string, std::string, std::string, std::string> UserInfo;
	UserInfo user;
	try
	{
		*session << "select UserID, Name, Surname, IP, City from UserData WHERE UserID=?", into(user), use(ID), now;
	}

	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}

	return user;
}
bool DatabaseConnection::Insert(int ID, std::string Name, std::string Surname, std::string IP, std::string City)
{
	try {
		*session << "insert into UserData values(?,?,?,?,?)", use(ID), use(Name), use(Surname), use(IP), use(City), now;
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return false;
	}
	return true;
}

std::string DatabaseConnection::GetIDFromIP(std::string text)
{
	int solution;
	try
	{
		*session << "select UserID from UserData WHERE IP=?", into(solution), use(text), now;
	}

	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}

	std::string ex;
	ex = std::to_string(solution);

	return ex;
}

std::vector<std::string> DatabaseConnection::CollectIP(void)
{
	using namespace Poco::Data;
	std::vector<std::string> a;
	Statement select(*session);
	select << "SELECT IP FROM %s", "UserData", now;
	RecordSet TableContent(select);
	std::size_t rows = TableContent.rowCount();

	for (auto i = 0; i != rows; ++i)
	{
		Poco::Dynamic::Var value = TableContent.value(0, i);
		a.push_back(value.convert<std::string>());
	}
	return a;
}