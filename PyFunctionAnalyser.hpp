#ifndef PYFUNCTIONANALYSER
#define PYFUNCTIONANALYSER

#include "IFunctionAnalyser.hpp"

class PyFunctionAnalyser : public IFunctionAnalyser {
public:
	PyFunctionAnalyser(){}
	~PyFunctionAnalyser() {};
	void process() override;
	size_t get_line() const override { return line; }
private:
	size_t line{0};
};
#endif
