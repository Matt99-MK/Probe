#include "Session.h"
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
SessionTCP::SessionTCP(const StreamSocket& s) : TCPServerConnection(s)
{
}

void SessionTCP::run()
{
	StreamSocket& ss = socket();
	SocketAddress peer = ss.address();
	IPAddress address = peer.host();
	try {
		int n;
		//std::cout << "Incoming connection from : " << peer.toString() << std::endl;
		int bytes = ss.receiveBytes(&n, sizeof(int));
		char buffer[1024];
		std::cout << "Receving message..." << std::endl;

		if (n == SessionTCP::ID_MESSAGE)
		{
			while (bytes > 0)
			{
				int size;
				int bytes = ss.receiveBytes(&size, sizeof(int));

				int n = ss.receiveBytes(buffer, sizeof(buffer));
				buffer[size] = '\0';
				std::cout << "Recived: ";
				std::cout << std::string(buffer, n) << std::endl;
			}
		}

		/*
		else if (n == SessionTCP::ID_FILE)
		{
			SocketStream ostr(ss);
			Poco::FileOutputStream istr("test1", std::ios::binary);
			Poco::StreamCopier::copyStream(ostr, istr);
		}
		*/
	}

	catch (Poco::Exception& exc)
	{
		//std::cerr << "Error: " << exc.displayText() << std::endl;
	}
}