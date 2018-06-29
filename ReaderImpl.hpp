#ifndef READERIMPL
#define READERIMPL

#include "Reader.hpp"
#include <vector>
#include <string>
#include "Token.hpp"
#include "TokenTracker.hpp"
#include "DirectoryReader.hpp"

enum class FindMode;

class Reader::ReaderImpl {
public:
	ReaderImpl(Reader* p, TokenTracker* t): parent(p), tracker(t){}
	ReaderImpl(ReaderImpl&);
	ReaderImpl(ReaderImpl&&);
	ReaderImpl& operator=(ReaderImpl&);
	ReaderImpl& operator=(ReaderImpl&&);
	~ReaderImpl() = default;
	void find(FindMode, std::string*);
private:
	Reader* parent;
	TokenTracker* tracker;
	DirectoryReader* dir_reader;
};

#endif
