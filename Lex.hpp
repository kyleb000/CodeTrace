#ifndef LEXICAL
#define LEXICAL

#include <string>
#include "IFlexEngine.hpp"

class Token;
enum class Type;
enum class FileType;

class Lex {
public:
	Lex(Type t, FileType ft, std::string fname, size_t* fn);
	Lex(Lex&);
	Lex(Lex&&);
	~Lex();
	Lex& operator = (Lex&);
	Lex& operator = (Lex&&);
	void operator<<(std::string&);
	Token* operator()();
	bool is_satisfied() const;
private:
	IFlexEngine* engine {nullptr};
	Type type;
	size_t line_no;
};


#endif
