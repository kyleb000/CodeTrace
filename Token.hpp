#ifndef TOKEN
#define TOKEN

#include <string>

enum class Type;

class Token {

public:
	Token(std::string, std::string, size_t, Type, Token*, Token*);
	~Token() {if (next_token) delete next_token; if (prev_token) delete prev_token; }
	Type type() const;
	std::string get(size_t pos) ;
	size_t line() const;
	Token* next() const;
	Token* prev() const;
private:
	Type t;
	Token* next_token;
	Token* prev_token;
	std::string token_str;
	std::string file;
	size_t line_no;
};

#endif
