#include "JCXFunctionAnalyser.hpp" 
#include "Files.hpp"
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <functional>
#include <iostream>
#include <tuple>

void JCXFunctionAnalyser::process() {
	using std::string;
	std::stringstream strs;
	string function_args;
	string function_name; 
	
	//lambda functions to find the presence or absence of spaces
	auto not_space = [](char a) -> bool { return (a != ' '); };
	auto is_space = [] (char b) -> bool { return (b == ' '); };
	
	//lambda to compare a string to strings in a file
	auto test_words = [] (string query, const char* file) -> bool {
		std::ifstream ign_file(file);
		std::string word;
		std::vector<std::string> words;
		while(ign_file >> word) words.push_back(word);
		return (find(begin(words), end(words), query) != end(words));
	};
	
	//lambda to find quotes
	auto fnd_chr = [] (char s) -> bool { return (s == '"' || s == '\''); };
	
	auto brac_find = [] (string& s) -> std::tuple<bool, std::string::iterator, std::string::iterator> {
		auto is_brac = [] (char c) -> bool { return (c == '{' || c == '}'); };
		//we reset the counters
		size_t open_curl = 0;
		size_t close_curl = 0;
		bool b{false};
		
		//we remove curly braces in order to not confuse the program
		auto fnd_curl = find_if(begin(s), end(s), is_brac);
		
		//we find all counts of open and close curly braces
		while (true) {
			if (fnd_curl != end(s) && !(open_curl == close_curl && open_curl !=0)) {
				if (*fnd_curl == '{') ++open_curl; else ++ close_curl;
				fnd_curl = find_if(fnd_curl+1, end(s), is_brac); 
			} else break;
		}
		
		auto fnd_open_curl = find(begin(s), end(s), '{');
		auto fnd_close_curl = find(begin(s), end(s), '}');
		
		//we only delete the body of the function if the number of open
		//curly braces matches the number of closing curly braces
		if (open_curl == close_curl && open_curl != 0) {
			size_t tmp_sz = close_curl;
			while ((--tmp_sz) > 0) {
				if (fnd_close_curl == end(s)) break;
				fnd_close_curl = find(fnd_close_curl+1, end(s), '}');
			}
			b = true;
		} else if (open_curl != 0 || close_curl != 0) b = false;
		return std::tuple<bool, std::string::iterator, std::string::iterator>(b, fnd_open_curl, fnd_close_curl);
	};
	
	auto erase_spaces = [] (string &s) {
		auto spacefnd = find(begin(s), end(s), ' ');
		while(true) {
			if (spacefnd == begin(s)) {
				s.erase(begin(s), begin(s)+1);
				spacefnd = find(begin(s), end(s), ' ');
			}else break;
		}
	};
	
	string& str = *query;
	
	if (str.size() == 0) return;
	
	//here we handle any classes we find in the query
	if (str.find("class") != string::npos) {
		//++class_cnt;
		str.erase(begin(str), begin(str)+5);
		erase_spaces(str);
		string s(begin(str), find_if(begin(str), end(str), is_space));
		str.erase(begin(str), begin(str)+s.length());
		s += "::";
		classes.push_back(s);
		auto fnd_class_brac = find(begin(str), end(str), '{');
		if (fnd_class_brac != end(str)) str.erase(begin(str), fnd_class_brac+1);
		else return;
	}
	
	for (auto e : classes) {
		function_name += e;
	}
	
	// we deal with the closing curly bracket of the class
	auto fnd_str_beg = find_if(begin(str), end(str), not_space);
	if (*fnd_str_beg == '}') { 
		classes.pop_back();
		str = "";
	}
	
	//here we remove the # strings 
	auto hashtag = find(begin(str), end(str), '#');
	if (hashtag != end(str)) {
		//if spaces are found, we find the first nonspace character
		if (*(hashtag+1) == ' ' || *(hashtag) == '\t') {
			auto no_space = find_if(hashtag+1, end(str), not_space);
			auto fnd_end_word = find(no_space, end(str), ' ');
			
			//delete the string if the condition is true
			if (test_words(string(no_space, fnd_end_word), F_HASHTG)){  
				str = "";
				return;
			}
		} else {
			//no spaces here
			auto fnd_word = hashtag+1;
			auto fnd_end_word = find(fnd_word, end(str), ' ');
			if (test_words(string(fnd_word, fnd_end_word), F_HASHTG)){  
				str = "";
				return;
			}
		} 
	}
	
	//here we remove any statements
	if (str.find(';') != string::npos && (str.find("(") == string::npos && str.find(")") == string::npos)) {
		auto semi_find = find(begin(str), end(str), ';');
		str.erase(begin(str), semi_find +1);
	}
	
	//here we remove any statements
	if (str.find(';') != string::npos && str.find(';') < str.find('(')) {
		auto semi_find = find(begin(str), end(str), ';');
		str.erase(begin(str), semi_find +1);
	}
	
	//we check if the function is a template function
	switch(get()) {
		case FileType::FILE_CXX:
			is_template = ((str.find("template") != string::npos));
			break;
		case FileType::FILE_JAVA:
			is_template = (str.find('<') != string::npos && str.find('>') != string::npos);
			break;
		default:
			break;
	}
	
	//we try to get the entire template definition in one line
	if (!temp_remove && is_template && ((str.find('<') == string::npos) && (str.find('>') == string::npos))) return;
	
	
	//here we remove the template arguments
	if (!temp_remove && str.find('<') != string::npos && is_template) {
		auto fnd_templ_gt = find(begin(str), end(str), '<');
		auto fnd_templ_lt = find(fnd_templ_gt, end(str), '>');
		str.erase(fnd_templ_gt, fnd_templ_lt+1);
		temp_remove = true;
	}
	
	//we remove the template word from the query
	if (is_template) {
		function_type = "<template>";
		auto pos = str.find("template");
		if (pos != string::npos)
		str.erase(pos, string("template").length());
	}
	
	//here we test if the string we are looking for is a function declaration
	//by checking if it has () and two words preceding them
	auto open_brac = find(begin(str), end(str), '(');
	auto close_brac = find(open_brac, end(str), ')');
	if (open_brac != end(str) && close_brac != end(str)) {
		string test = string(begin(str), open_brac);
		string tmp;
		std::stringstream testss(test);
		size_t words = 0;
		while (testss >> tmp) ++words;
		if (words < 2) return;
		else if (!ignore) { 
			line = *tmp_line;
			ignore = true;
		}
	}
	
	//we will only continue working if we find an open curly or a semi colon
	if (str.find("{") == string::npos && str.find(";") == string::npos) return;
	
	//here we remove any string literals
	while (true) {
		auto fnd_first_chr = find_if(begin(str), end(str), fnd_chr);
		if (fnd_first_chr != end(str)) {
			char test = *fnd_first_chr;
			auto fnd_next_chr = find(fnd_first_chr+1, end(str), test);
			if (*(fnd_next_chr-1) == '\\') {
				auto tmp = find(fnd_next_chr+1, end(str), test);
				if (tmp != end(str)) fnd_next_chr = tmp;
			}
			str.erase(fnd_first_chr, fnd_next_chr+1);
		}else break;
	}
	
	auto fnd_bracs = brac_find(str);
	
	//we only delete the body of the function if the number of open
	//curly braces matches the number of closing curly braces
	if (std::get<0>(fnd_bracs)) {
		str.erase(std::get<1>(fnd_bracs), std::get<2>(fnd_bracs)+1);
		ignore = false;
	} else return;
	
	
	//we test for the parenthesis to make sure we are dealing with a
	//function. We exit the function if this is not the case
	if (str.find("(") == string::npos || str.find(")") == string::npos) {
		return;
	}
	
	if (str.find(';') > str.find(')')) ignore = false;
	
	_open_arg = true;
	_close_arg = true;
	
	auto get_arg = find(begin(str), end(str), '(');
	str.insert(get_arg, ' ');
	
	//we erase any spaces between the beginning of the string and the 
	//first non space character
	auto spacefnd = find(begin(str), end(str), ' ');
	while(true) {
		if (spacefnd == begin(str)) {
			str.erase(begin(str), begin(str)+1);
			spacefnd = find(begin(str), end(str), ' ');
		}else break;
	}
	
	
	//******************************************************************
	// this section gets the type of the function
	//******************************************************************
	
	//gets the first word of the string by finding the space
	auto fnd_str = find(begin(str), end(str), ' ');
	
	//compares the first word to a list of words and deletes it if
	//the word matches anything in the list
	while (true) {
		string test(begin(str), fnd_str);
		if (test_words(test, F_IGNORE)) {
			str.erase(begin(str), fnd_str);
			fnd_str = find(begin(str), end(str), ' ');
		}
		else break;
	}
	
	//removes any spaces that are ahead of the first nonspace
	//character
	fnd_str = find(begin(str), end(str), ' ');
	auto space = find(begin(str), end(str), ' ');
	auto no_space = find_if(begin(str), end(str), not_space);
	if (*begin(str) == ' ') {
		str.erase(space, no_space);
		fnd_str = find(begin(str), end(str), ' ');
	}
		
	//holds additional information of the type
	string pre_ret;
	
	//extracts additional information of the type
	while (true) {
		fnd_str = find(begin(str), end(str), ' ');
		string test(begin(str), fnd_str);
		
		//we check if it matches any entries in a list
		if (test_words(test, F_EXTEND)){
			
			//we copy this value to the pre_ret string
			pre_ret = string(begin(str), begin(str) + test.length());
			
			//we remove it from the string
			str.erase(begin(str), begin(str) + test.length());
			
			//we remove any spaces ahead of the first nonspace 
			//character
			auto no_space = begin(str);
			while (true) {
				if (*(no_space) == ' ') ++no_space; 
				else {
					str.erase(begin(str), no_space);
					break;
				}
			}
			function_type += pre_ret;
		}
		else break;
	}
	
	fnd_str = find(begin(str), end(str), ' ');	
	
	//removes any spaces ahead of the first nonspace character
	auto get_space = find_if(begin(str), end(str), not_space);
	str.erase(begin(str), get_space);

	//gets the return type of the function
	fnd_str = find(begin(str), end(str), ' ');
	
	auto get_paren = find_if(fnd_str, end(str), not_space);
	
	if(*(get_paren) != '(') {
		function_type += string(begin(str), fnd_str);
		str.erase(begin(str), fnd_str+1);
	}
		
	_type = true;
	
	//******************************************************************
	
	//******************************************************************
	// gets the arguments from the parenthesis
	//******************************************************************
	
	//adds the word that comes before the '(' to the function name
	fnd_str = find(begin(str), end(str), '(');
	function_name += string(begin(str), fnd_str);
	
	//we remove any spaces in the function name
	if(*(end(function_name)-1) == ' ') {
		while(true) {
			if (*(end(function_name) -1) == ' ') function_name.erase(end(function_name)-1);
			else break;
		}
	}
	
	//add a space to the function name. we removed spaces previously to help keep 
	//the number of spaces to 1
	function_name += ' ';
	_name = true;
	str.erase(begin(str), fnd_str);
	
	//keeps the position of where the two brackes are
	auto open_arg = find(begin(str), end(str), '(');
	auto close_arg = find(begin(str), end(str), ')');
	
	
	//we check if the user put in any arguments
	auto is_args = find_if (open_arg+1, end(str), not_space);
	
	//finish up and exit the function if there are no arguments
	if (is_args == close_arg) {
		function_args = "none";
		fnc_data.push_back(function_name);
		fnc_data.push_back(function_type);
		fnc_data.push_back(function_args);
		function_type = "";
		is_template = temp_remove = false;
		auto fnd_end_brc = find(begin(str), end(str), ')');
		str.erase(begin(str), fnd_end_brc+1);
		if (str.find('{') == string::npos && str.find('(') == string::npos) {
			str = "";
		}
		return;
	}
	
	//we remove any spaces between the ( and the first nonspace character
	while (true) {
		if (*(open_arg+1) == ' ') {
			str.erase(open_arg+1);
			close_arg = find(begin(str), end(str), ')');
		} else break;
	}
	//we remove any 'const' type from the arguments
	while (str.find("const") != string::npos) {
		auto pos = str.find("const");
		string str_er("const");
		
		//we get the space between the const and the type of the argument
		auto fnd_b_space = find(begin(str)+pos, end(str), ' ');
		auto fnd_e_space = find_if(fnd_b_space, end(str), not_space);
		
		//we put them in a string
		string str_sp(fnd_b_space, fnd_e_space);
		
		using std::stringstream;
		stringstream ss;
		
		//we add them together
		ss << str_er << str_sp;
		str_er = ss.str();
		
		//we remove the string
		str.erase(pos, str_er.length());
		
		//get the new position of the brackets
		open_arg = find(begin(str), end(str), '(');
		close_arg = find(begin(str), end(str), ')');
	}
	
	//we remove any apersands
	auto amp_find = find(open_arg, close_arg, '&');
	while (amp_find < close_arg) {
		str.erase(amp_find, amp_find+1);
		open_arg = find(begin(str), end(str), '(');
		close_arg = find(begin(str), end(str), ')');
		amp_find = find(open_arg, close_arg, '&');
	}
	
	//we remove any asterisks
	auto ptr_find = find(open_arg, close_arg, '*');
	while (ptr_find < close_arg) {
		str.erase(ptr_find, ptr_find+1);
		open_arg = find(begin(str), end(str), '(');
		close_arg = find(begin(str), end(str), ')');
		ptr_find = find(open_arg, close_arg, '*');
	}

	if (!is_template) {
	
		//we get the name of the argument by using the space after the
		//type and the separating comma
		auto space_arg = find(open_arg, close_arg, ' ');
		auto com_arg = find(open_arg, close_arg, ',');
		
		//we go through all the arguments
		while (find(open_arg, close_arg, ',') != close_arg) {
			
			//we erase the name, the spaces and the comma
			str.erase(space_arg, com_arg+1);
			
			//if we find more commas, we get the new space and
			//comma position
			if (find(open_arg, close_arg, ',') != close_arg) {
				space_arg = find(space_arg+1, close_arg, ' ');
				com_arg = find(open_arg, close_arg, ',');
			}
			
			//get the new position of the brackets
			open_arg = find(begin(str), end(str), '(');
			close_arg = find(begin(str), end(str), ')');
		}
		//******************************************************************
		
		//******************************************************************
		//removing spaces from the arguments
		//******************************************************************
		
		//here we work with the argument names in the brackets
		string args(open_arg, close_arg+1);
		
		//we get the character before the closing bracket
		auto fnd_l_space = end(args)-2;
		
		//here we remove any spaces between the closing bracket and the 
		//last nonspace character
		while(true) {
			
			//we decrease the iterator if it is a space
			if (*fnd_l_space == ' ') --fnd_l_space;
			else {
				
				//we make sure it is not the same character
				if (fnd_l_space != end(args)-2)
					args.erase(fnd_l_space+1, end(args)-1);
				break;
			}
		}
		
		//here we remove the last argument name, as there is no comma to
		//help find it
		
		//get the reverse iterator that gets to a space. this space is 
		//between the name of the argument and the type of the argument
		auto r_space = find_if(rbegin(args), rend(args), is_space);
		
		//we erase everything between the reverse iterator and the closing
		//bracket
		args.erase(std::next(r_space).base(), end(args)-1);
		
		//we remove all the spaces in the string
		while (args.find(' ') != string::npos) {
			auto fnd = find(begin(args), end(args), ' ');
			args.erase(fnd, fnd+1);
		}
		
		//we remove the open and close bracket
		args.erase(0,1);
		args.erase(args.length()-1, args.length());
		
		//here we create a hash of the argument types
		using std::hash;
		size_t str_hash = hash<string>{}(args);
		
		strs << str_hash;
	
	} else {
		size_t args = 0;
		auto comm_find = find(open_arg, close_arg, ',');
		if (comm_find != close_arg) {
			while (comm_find != close_arg) {
				++args;
				comm_find = find(comm_find+1, close_arg, ',');
			}
			++args;
		} else {
			auto fnd_no_space = find_if(open_arg+1, end(str), not_space);
			if (fnd_no_space != close_arg) ++args;
		}
		strs << "args:" << args;
		is_template = temp_remove = false;
	}	
	
	//******************************************************************
	
	auto fnd_end_brc = find(begin(str), end(str), ')');
	str.erase(begin(str), fnd_end_brc+1);
	
	function_args += strs.str();
	fnc_data.push_back(function_name);
	fnc_data.push_back(function_type);
	fnc_data.push_back(function_args);
	function_type = "";
}
