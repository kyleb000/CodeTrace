#ifndef PYFUNCTIONANALYSER
#define PYFUNCTIONANALYSER

#include "IFunctionAnalyser.hpp"

class PyFunctionAnalyser : public IFunctionAnalyser {
public:
	PyFunctionAnalyser(){}
	~PyFunctionAnalyser() = default;
	void process() override;
};
#endif
