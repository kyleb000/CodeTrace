#ifndef IFLEXENGINE
#define IFLEXENGINE

#include <string>
class Token;

/**
 * The IFlexEngine class serves three purposes: It provides an 
 * interface for the Lex object to use, a base class for the derived
 * Lex engine objects to implement and holds variables that all the 
 * derived objects use. 
 * 
 * This class is an interface.
 **/
class IFlexEngine {
public:
	IFlexEngine(std::string fname, size_t* ln): filename(fname), line(ln){}
	virtual ~IFlexEngine() {};
	virtual IFlexEngine& operator<<(std::string& rhs) = 0;
	virtual bool is_satisfied() const = 0;
	virtual Token* get() = 0;
protected:
	std::string query;
	bool satisfied;
	std::string filename;
	size_t* line;
};

#endif
