#ifndef JCXFUNCTIONANALYSER
#define JCXFUNCTIONANALYSER

#include "IFunctionAnalyser.hpp"

class JCXFunctionAnalyser : public IFunctionAnalyser {
public:
	JCXFunctionAnalyser(){}
	~JCXFunctionAnalyser() {}
	void process() override;
};
#endif
