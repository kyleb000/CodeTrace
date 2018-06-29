#ifndef CLASSLEXENGINE
#define CLASSLEXENGINE

#include "IFlexEngine.hpp"

/**
 * This class inherits from the IFlexEngine interface and implements
 * its members. This class deals with class hierarchies and generates 
 * Tokens based on class hierarchies.
 **/

class ClassLexEngine : public IFlexEngine {
public:
	ClassLexEngine(FileType f, std::string fname, size_t* ln): IFlexEngine(fname,ln) {}
	~ClassLexEngine() = default;
	IFlexEngine& operator<<(std::string& rhs) override;
	bool is_satisfied() const override;
	Token* get() override;
};

#endif
