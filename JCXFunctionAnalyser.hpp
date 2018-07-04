#ifndef JCXFUNCTIONANALYSER
#define JCXFUNCTIONANALYSER

#include "IFunctionAnalyser.hpp"

class JCXFunctionAnalyser : public IFunctionAnalyser {
public:
	JCXFunctionAnalyser(){}
	~JCXFunctionAnalyser() {}
	void process() override;
private:
	size_t open_curl{0};
	size_t close_curl{0};
};
#endif
