#include "OutputFormatter.hpp"

OutputFormatter::OutputFormatter(const std::string &path) : 
os_path(path) {}

OutputFormatter::OutputFormatter(const OutputFormatter& output) : 
os_path(output.os_path) {}

OutputFormatter::OutputFormatter(OutputFormatter&& output) {
	os_path = std::move(output.os_path);
	output.~OutputFormatter();
}

OutputFormatter& OutputFormatter::operator=(const std::string& rhs) {
	os_path = rhs;
	return *this;
}

OutputFormatter& OutputFormatter::operator<<(const Token* token) {
	/* implement code to print token */
	return *this;
}

OutputFormatter& OutputFormatter::operator=(const OutputFormatter& rhs) {
	os_path = rhs.os_path;
	return *this;
}

OutputFormatter& OutputFormatter::operator=(OutputFormatter&& rhs) {
	os_path = std::move(rhs.os_path);
	rhs.~OutputFormatter();
	return *this;
}
