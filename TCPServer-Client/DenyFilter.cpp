#include"DenyFilter.h"

RejectFilter::RejectFilter()
{
	//blacklist
}

bool RejectFilter::accept(const StreamSocket& ss)
{
	//Accept All
	//std::cout << " Inner Filter " << std::endl;

	return true;
}