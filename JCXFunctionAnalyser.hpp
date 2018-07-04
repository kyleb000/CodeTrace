#ifndef JCXFUNCTIONANALYSER
#define JCXFUNCTIONANALYSER

#include "IFunctionAnalyser.hpp"

class JCXFunctionAnalyser : public IFunctionAnalyser {
public:
	JCXFunctionAnalyser(){}
	~JCXFunctionAnalyser() {}
	void process() override;
	size_t get_line() const { return line; }
private:
	size_t open_curl{0};
	size_t close_curl{0};
	size_t line;
	bool ignore{false};
};
#endif
