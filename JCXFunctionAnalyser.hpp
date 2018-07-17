#ifndef JCXFUNCTIONANALYSER
#define JCXFUNCTIONANALYSER

#include "IFunctionAnalyser.hpp"
#include "TypeGetter.hpp"
#include "FileType.hpp"
#include <vector>
#include <tuple>
#include <sstream>

using std::string;

class JCXFunctionAnalyser : public IFunctionAnalyser, public TypeGetter<FileType> {
public:
	JCXFunctionAnalyser(){}
	~JCXFunctionAnalyser() {}
	void process() override;
	size_t get_line() const override { return line; }
	void get_name(std::string fname) { filename = fname; }
private:
	string function_type;
	size_t line{0};
	size_t class_cnt{0};
	bool ignore{false};
	bool is_template{false};
	bool temp_remove{false};
	std::vector<std::string::iterator> classes;
};
#endif
