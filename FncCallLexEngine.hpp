#ifndef FNCCALLLEXENGINE
#define FNCCALLLEXENGINE

#include "IFlexEngine.hpp"

/** 
 * This class inherits from the IFlexEngine interface and implements 
 * its members. This class focuses on dealing with function calls and
 * generates tokens based on these function calls.
 **/
class FncCallLexEngine : public IFlexEngine {
public:
	FncCallLexEngine(FileType f, std::string fname, size_t* ln) : IFlexEngine(fname, ln) {}
	~FncCallLexEngine() = default;
	IFlexEngine& operator<<(std::string& rhs) override;
	bool is_satisfied() const override;
	Token* get() override;
};

#endif
