#ifndef ISUBCLASSPROCESSOR
#define ISUBCLASSPROCESSOR

#include "IFunctionAnalyser.hpp"
#include <tuple>

template <typename... Args>
class ISubClassProcessor {
public:
	ISubClassProcessor() {}
	virtual ~ISubClassProcessor() {}
	void set(Args... params) {
		args = std::tuple<Args...>(params...);
	}
	virtual void process() = 0;
protected:
	std::tuple<Args...> args;
	IFunctionAnalyser* analyser;
};

#endif
