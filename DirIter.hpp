#ifndef DIRITER
#define DIRITER

#include <memory>
#include <string>
class Reader;
class FileIterator;
bool operator==(const DirIter& lhs, const DirIter& rhs);
bool operator!=(const DirIter& lhs, const DirIter& rhs);

class DirIter {
public:
	friend bool operator==(const DirIter&, const DirIter&);
	friend bool operator!=(const DirIter&, const DirIter&);
	DirIter(Directory* r, const size_t s) : dir(r), sz(s) {}
	std::string* operator*() const;
	DirIter& operator++();
	DirIter operator++(int);
	DirIter& operator--();
	DirIter operator--(int);
private:
	Directory* dir;
	size_t sz;
};

#endif
