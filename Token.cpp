#include "Token.hpp"
#include "Type.hpp"

Token::Token(std::string cont, std::string f, size_t ln, Type t,
	Token* p, Token* n) : token_str(cont), file(f), line_no(ln), 
	t(t), prev_token(p), next_token(n) {}

Type Token::type() const {
	return t;
}

std::string Token::get(size_t pos) {
	return (pos%2 == 0 ? token_str : file);
}

size_t Token::line() const {
	return line_no;
}

Token* Token::next() const {
	return next_token;
}

Token* Token::prev() const {
	return prev_token;
}
