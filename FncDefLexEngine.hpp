#ifndef FNCDEFLEXENGINE
#define FNCDEFLEXENGINE

#include "IFlexEngine.hpp"
#include "IFunctionAnalyser.hpp"
#include "FileType.hpp"
#include "IComRemover.hpp"

/**
 * This class derives from the IFlexEngine interface and implements its
 * members. This class deals with function declarations and generates
 * tokens regarding function declarations.
 **/

class FncDefLexEngine : public IFlexEngine {
public:
	FncDefLexEngine(FileType f, std::string fname, size_t* ln);
	~FncDefLexEngine() { delete analyser; delete remover; }
	IFlexEngine& operator<<(std::string& rhs) override;
	bool is_satisfied() const override;
	Token* get() override;
private:
	IFunctionAnalyser* analyser{nullptr};
	IComRemover* remover{nullptr};
};

#endif
