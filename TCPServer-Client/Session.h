#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnection.h>
#include <iostream>
#include "Poco/StreamCopier.h"
#include "Poco/FileStream.h"
#include "Poco/Net/SocketStream.h"
using namespace Poco::Net;

#ifndef _SESS_
#define _SESS_

class SessionTCP : public TCPServerConnection
{
public:
	enum
	{
		ID_MESSAGE = 1,
		ID_FILE,
	};
public:
	SessionTCP(const StreamSocket& s);
	void run();
};

#endif // _SESS_