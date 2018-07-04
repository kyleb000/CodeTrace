#ifndef ICOMREMOVER
#define ICOMREMOVER

#include <string>

class IComRemover {
public:
	IComRemover() {}
	virtual ~IComRemover() {}
	virtual std::string& operator()(std::string& s) = 0;
};

#endif
