#include "ReaderImpl.hpp"
#include "Directory.hpp"
#include "FindMode.hpp"
#include "Type.hpp"
#include "Lex.hpp"
#include <fstream>
#include <iostream>
//#include "TokenTracker.hpp"
#include "DirIter.hpp"
#include <vector>
#include <thread>
#include <chrono>

Reader::ReaderImpl::ReaderImpl(ReaderImpl& impl) {
	parent = impl.parent;
}

Reader::ReaderImpl::ReaderImpl(ReaderImpl&& impl) {
	parent = impl.parent;
}

Reader::ReaderImpl& Reader::ReaderImpl::operator=(ReaderImpl& impl) {
	parent = impl.parent;
	return *this;
}

Reader::ReaderImpl& Reader::ReaderImpl::operator=(ReaderImpl&& impl) {
	parent = impl.parent;
	return *this;
}

void Reader::ReaderImpl::find(FindMode mode, std::string* fpath) {
	
	/*Lambda function that reads all files in a directory, passes
	 * each line in a file to a Lex object and adds the Token to the
	 * Token tracker object. The lambda captures the Reader 'this' 
	 * pointer and takes the following arguments: A Directory object 
	 * pointer to get files in a directory, and a Type enum to tell
	 * the Lex object which type of token it must generate
	 */
	auto fnc = [this](const std::string& file, Type t) { 
		std::ifstream infile(file);
		std::string s;
		Lex lex(t);
		std::cout << s << std::endl;
		while (getline(infile, s)) {
			lex << s;
			if (lex.is_satisfied())
				//*tracker << lex();
		}
	};
	
	/* Lambda function that runs the fnc lambda for the different
	 * find modes. The lambda captures the Reader 'this' pointer
	 * and the fnc lambda. It takes a Directory pointer as an 
	 * argument
	 */
	auto mode_fnc = [this, fnc](const std::string* path) { 
		fnc(*path, Type::T_FUNC_DEFN);
		fnc(*path, Type::T_FUNC_CALL);
		fnc(*path, Type::T_CLASS);
		fnc(*path, Type::T_STAT);
	};
	if (mode == FindMode::MODE_RECUR) {
		std::vector<std::thread> tvec;
		while((*dir_reader) != 0) {
			Directory dir = std::move((*dir_reader)());
			std::cout << dir.size() << std::endl;
			for (auto e = dir.begin(); e != dir.end(); ++e) {
				std::cout << *(*e) << std::endl;
				size_t sz = 4;
				while ((--sz) != 0 && e != dir.end()) {
					std::thread thr(&Reader::ReaderImpl::find, this, FindMode::MODE_CURDIR, *e);
					tvec.push_back(std::move(thr));
				}
				std::cout << tvec.size() << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				for (auto& e : tvec) {
					e.join();
				}
				tvec.erase(tvec.begin(), tvec.end());
			}
		}
	} else {
		mode_fnc(fpath);
	}	
}
