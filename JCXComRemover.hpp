#ifndef JCXCOMREMOVER
#define JCXCOMREMOVER

#include "IComRemover.hpp"

class JCXComRemover : public IComRemover {
public:
	JCXComRemover() {}
	~JCXComRemover() {}
	std::string& operator()(std::string& s) override;
private:
	bool is_open{false};
};

#endif
