#include "JCXComRemover.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>

std::string& JCXComRemover::operator()(std::string& s) {
	if (s.find("//") != std::string::npos) { s = ""; return s; }
	if ((s.find("/*") != std::string::npos && s.find("*/") == std::string::npos) || is_open) {
		is_open = true;
		if(s.find("*/") == std::string::npos) s = "";
		if(s.find("*/") != std::string::npos) is_open = false;
	}
	else if (s.find("/*") == std::string::npos && s.find("*/") != std::string::npos) {
		is_open = false;
		auto c1 = begin(s) + s.find("*/") +2;
		s.erase(begin(s), c1);
	}
	else if (s.find("/*") != std::string::npos && s.find("*/") != std::string::npos) {
		auto c1 = begin(s) + s.find("/*");
		auto c2 = begin(s) + s.find("*/")+2;
		s.erase(c1, c2);
		return s;
	}
	while (true) {
		auto find_tab = find(begin(s), end(s), '\t');
		if (find_tab != end(s)){
			s.erase(find_tab);
		} else break;
	}			
	return s;
}
