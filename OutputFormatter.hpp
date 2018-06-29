#ifndef OUTPUTFORMATTER
#define OUTPUTFORMATTER

#include <iostream>
#include <string>

class Token;

class OutputFormatter {
public:
	OutputFormatter() {}
	OutputFormatter(const OutputFormatter&);
	OutputFormatter(OutputFormatter&&);
	OutputFormatter(const std::string&);
	OutputFormatter& operator=(const OutputFormatter&);
	OutputFormatter& operator=(OutputFormatter&&);
	OutputFormatter& operator=(const std::string&);
	OutputFormatter& operator << (const Token*);
	~OutputFormatter() = default;
private:
	std::string os_path;
};

#endif
