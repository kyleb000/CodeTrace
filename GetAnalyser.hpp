#ifndef GETANALYSER
#define GETANALYSER

#include "IFunctionAnalyser.hpp"
#include "JCXFunctionAnalyser.hpp"
#include "PyFunctionAnalyser.hpp"
#include "FileType.hpp"

IFunctionAnalyser* get_analyser(FileType type) {
	switch(type) {
		case FileType::FILE_PY:
			return new PyFunctionAnalyser();
			break;
		default:
			return new JCXFunctionAnalyser();
	}
}

#endif
