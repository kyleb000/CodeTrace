#include "FncCallLexEngine.hpp"

/* This operator works by feeding a given string into a query, and 
 * then analysing the query for any tokens. If the query matches the 
 * requirements for a Token, a new token is made, the token is given
 * information and the satisfied flag is set to true 
 * */
IFlexEngine& FncCallLexEngine::operator<<(std::string& rhs) {
	query += rhs;
	//TODO: implement code that creates the Token
	return *this;
}

/* This function returns the generated token */
Token* FncCallLexEngine::get() const {
	return token;
}

/* This function returns the state of the satisfied variable */
bool FncCallLexEngine::is_satisfied() const {
	return satisfied;
}
