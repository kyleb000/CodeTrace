#ifndef PYFUNCTIONANALYSER
#define PYFUNCTIONANALYSER

#include "IFunctionAnalyser.hpp"

class PyFunctionAnalyser : public IFunctionAnalyser {
public:
	PyFunctionAnalyser(){}
	~PyFunctionAnalyser() = default;
	void process() override;
	size_t get_line() const override { return 0; }
};
#endif
