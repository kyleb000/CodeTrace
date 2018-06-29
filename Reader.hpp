#ifndef READER
#define READER

#include <string>
class Token;
class FileIterator;
class Directory;
enum class FindMode;
class Reader {
friend class FileIterator;
public:
	class ReaderImpl;
	Reader();
	~Reader();
	Reader(Reader&);
	Reader(Reader&&);
	Reader& operator = (Reader&);
	Reader& operator = (Reader&&);
	void find(FindMode);
	void load(Directory*);
	static Reader get_class();
private:
	ReaderImpl* impl;
};
#endif
