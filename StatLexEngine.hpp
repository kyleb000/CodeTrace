#ifndef STATLEXENGINE
#define STATLEXENGINE

#include "IFlexEngine.hpp"

class StatLexEngine : public IFlexEngine {
public:
	StatLexEngine(FileType f, std::string fname, size_t* ln): IFlexEngine(fname, ln) {}
	~StatLexEngine() = default;
	IFlexEngine& operator<<(std::string& rhs) override;
	bool is_satisfied() const override;
	Token* get() override;
};

#endif
