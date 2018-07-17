#include "FncDefLexEngine.hpp"
#include "GetAnalyser.hpp"
#include "GetRemover.hpp"
#include "Token.hpp"
#include "Type.hpp"
#include <iostream>

FncDefLexEngine::FncDefLexEngine(FileType f,  std::string fname, size_t* ln):
IFlexEngine(fname,ln) {
	analyser = get_analyser(f);
	remover = get_remover(f);
}

/* This operator works by feeding a given string into a query, and 
 * then analysing the query for any tokens. If the query matches the 
 * requirements for a Token, the satisfied flag is set to true 
 * */
IFlexEngine& FncDefLexEngine::operator<<(std::string& rhs) {
	query += (*remover)(rhs);
	analyser->set_line(line);
	analyser->get_name(filename);
	analyser << query;
	analyser->process();
	satisfied = (analyser->name() && analyser->type() && 
	analyser->open_arg() && analyser->close_arg()) || analyser->args();
	return *this;
}

/* This function returns a newly generated token */
Token* FncDefLexEngine::get() {
	std::string s;
	s += analyser->operator()(type);
	s += analyser->operator()(name);
	s += analyser->operator()(args);
	analyser->clear();
	satisfied = false;
	query = "";
	return new Token(std::move(s), filename, analyser->get_line(), Type::T_FUNC_DEFN, nullptr, nullptr);
}

/* This function returns the state of the satisfied variable */
bool FncDefLexEngine::is_satisfied() const {
	return satisfied;
}

