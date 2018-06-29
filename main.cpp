#include "Lex.hpp"
#include "Type.hpp"
#include "FileType.hpp"
#include "Token.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string path = "/home/kyle-pc/tests/lex_terst/example.cpp";
	fstream file(path);
	string line;
	size_t line_no = 1;
	Lex l(Type::T_FUNC_DEFN, FileType::FILE_CXX, "example.cpp", &line_no);
	while (getline(file, line)) {
		line += ' ';
		l << line;
		if(l.is_satisfied()){
			Token *t = l();
			size_t sz1 = 0;
			size_t sz2 = 1;
			cout << "Info " << t->get(sz1) << endl;
			cout << "File " << t->get(sz2) << endl;
			cout << "Line " << t->line() << endl;
			delete t;
		}
		line = "";
		++line_no;
	}
	file.close();
	return 0;
}
		
