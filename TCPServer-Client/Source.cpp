#include "Poco/FileStream.h"
#include "Poco/Net/SocketStream.h"

#include<Poco/Net/TCPServerParams.h>
#include "Session.h"
#include "DenyFilter.h"
using namespace Poco::Net;

int main()
{
	try {
		SocketAddress adress(Poco::Net::AddressFamily::IPv4, "127.0.0.1", "7675");
		ServerSocket socketserver(adress);
		TCPServer srv(new TCPServerConnectionFactoryImpl<SessionTCP>(), socketserver);
		RejectFilter* reject = new RejectFilter();

		srv.setConnectionFilter(reject);
		srv.start();

		std::cout << "Creating connection to remote server..." << std::endl;
		SocketAddress sa("127.0.0.1", "7670");
		StreamSocket ss(sa);
		SocketStream istr(ss);

		int n = SessionTCP::ID_MESSAGE;
		ss.sendBytes(&n, sizeof(int));
		std::string data;
		int size;
		while (TRUE)
		{
			std::cout << "Sending : ";
			std::getline(std::cin, data);

			size = data.size();
			ss.sendBytes(&size, sizeof(int));
			ss.sendBytes(data.data(), (int)data.size());
		}
		/*
		int n = SessionTCP::ID_MESSAGE;
		//Sending File
		int n = SessionTCP::ID_FILE;
		ss.sendBytes(&n, sizeof(int));
		ss.sendBytes(&n, sizeof(int));
		Poco::FileInputStream ostr("test.txt", std::ios::binary);
		Poco::StreamCopier::copyStream(ostr, istr);
		*/

		//Zatrzymywanie Server
	}

	catch (Poco::Exception& exc)
	{
		std::cerr << "B³¹d: " << exc.displayText() << std::endl;
	}
}