#ifndef READER
#define READER

#include <string>
class Token;
class FileIterator;
class Directory;
class DirectoryReader;
enum class FindMode;
class Reader {
friend class FileIterator;
public:
	class ReaderImpl;
	Reader(DirectoryReader* dr);
	~Reader();
	Reader(Reader&);
	Reader(Reader&&);
	Reader& operator = (Reader&);
	Reader& operator = (Reader&&);
	void find(FindMode);
	//static Reader get_class();
private:
	ReaderImpl* impl;
};
#endif
