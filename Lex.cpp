#include "Lex.hpp"

#include "FncCallLexEngine.hpp"
#include "FncDefLexEngine.hpp"
#include "ClassLexEngine.hpp"
#include "StatLexEngine.hpp"
#include "Type.hpp"
#include "FileType.hpp"

Lex::Lex(Type t, FileType ft, std::string fname, size_t* fn) {
	switch (t) {
		case Type::T_FUNC_DEFN:
			engine = new FncDefLexEngine(ft, fname, fn);
			break;
		/*case Type::T_FUNC_CALL:
			engine = new FncCallLexEngine(ft, fname, fn);
		case Type::T_CLASS:
			engine = new ClassLexEngine(ft, fname, fn);
		case Type::T_STAT:
			engine = new StatLexEngine(ft, fname, fn);*/
	}
}

Lex::Lex(Lex& l) {
	engine->~IFlexEngine();
	engine = l.engine;
	type = l.type;
}

Lex::Lex(Lex&& l) {
	(*engine) = std::move(*engine);
	type = l.type;
	l.~Lex();
}

Lex::~Lex() {
	if(engine) delete engine;
}

Lex& Lex::operator=(Lex& l) {
	engine->~IFlexEngine();
	engine = l.engine;
	type = l.type;
	return *this;
}

Lex& Lex::operator=(Lex&& l) {
	(*engine) = std::move(*engine);
	type = l.type;
	l.~Lex();
	return *this;
}

void Lex::operator<<(std::string& rhs) {
	(*engine) << rhs;
}

Token* Lex::operator()() {
	return engine->get();
}

bool Lex::is_satisfied() const {
	return engine->is_satisfied();
}
