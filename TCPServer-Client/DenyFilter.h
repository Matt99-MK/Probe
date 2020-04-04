#pragma once
#include <Poco/Net/TCPServer.h>
#include <vector>
#ifndef _DNFILTER_
#define _DNFILTER_

using namespace Poco::Net;

class RejectFilter : public TCPServerConnectionFilter
{
public:
	RejectFilter();
	bool accept(const StreamSocket&);
	std::vector<std::string> blacklist;
};
#endif // _DNFILTER_