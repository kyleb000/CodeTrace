#include "PyFunctionAnalyser.hpp"
#include <functional>
#include <algorithm>
#include <sstream>

void PyFunctionAnalyser::process() {
	using std::string;
	string function_name; 
	string function_type;
	string function_args;
	string& str = *query;
	
	//Lambda function to determine whether a character is a space
	auto not_space = [](char a) -> bool { return (a != ' '); };
	
	//Lambda function to detrmine whether a given string is 'def'
	auto find_def = [](string &s) -> bool {
		return (s == "def");
	};
	
	
	//removes any spaces between the beginning of the string and the
	//first nonspace character
	auto space = find_if(begin(str), end(str), not_space);
	if (space != begin(str)) {
		str.erase(begin(str), space);
	}
	
	space = find(begin(str), end(str), ' ');
	
	//we get the first word from the string
	string test = string(begin(str), space);
	
	//we only work with the rest of the string if we can find a 'def'
	//and a ':'
	if(find_def(test) && str.find(":") != string::npos) {
		
		//we cannot determine the type of the function in Python
		function_type = "none";
		
		//removes any spaces between the beginning of the string and the
		//first nonspace character
		str.erase(begin(str), begin(str) + test.length());
		space = find_if(begin(str), end(str), not_space);
		if (space != begin(str)) {
			str.erase(begin(str), space);
		}
		
		//we get the position of the parenthesis
		auto open_arg =  find(begin(str), end(str), '(');
		auto close_arg = find(begin(str), end(str), ')');
		space = find(begin(str), open_arg, ' ');
		if (space != open_arg) {
			str.erase(space, open_arg);
		}
		
		//reset the positin of the parenthesis
		open_arg =  find(begin(str), end(str), '(');
		close_arg = find(begin(str), end(str), ')');
		
		//here we search for arguments in the brackets
		auto search = open_arg+1;
		auto has_args = find_if(search, close_arg, not_space);
		size_t args = 0;
		//only if there are characters between the brackets
		if (has_args != close_arg) {
			
			//we include the last argument
			++args;
			
			//we get the number of commas, as these give us the number
			//of arguments, minus the last one
			while(search != close_arg) {
				search = find(search, close_arg, ',');
				if (search != close_arg) {
					++args;
					++search;
				}
			}
		}
		//we get the function name
		function_name = string(begin(str), open_arg);
		using std::stringstream;
		
		//we get the number of arguments
		stringstream ss;
		ss << "args:";
		ss << args;
		function_args = ss.str();
		
		fnc_data.push_back(function_name);
		fnc_data.push_back(function_type);
		fnc_data.push_back(function_args);
		_name = true;
		_type = true;
		_args = true;
		_open_arg = true;
		_close_arg = true;
		
	} else {
		//don't do anything if not a function
		return;
	}
}
