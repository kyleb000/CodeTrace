#ifndef DIRECTORY
#define DIRECTORY

#include <vector>
#include <string>
#include <memory>
class DirIter;

class Directory {
public:
	Directory() {}
	Directory(std::string&);
	Directory(std::string);
	Directory(Directory&);
	Directory(Directory&&);
	Directory& operator=(std::string&);
	Directory& operator=(std::string);
	Directory& operator=(std::string&&);
	Directory& operator=(Directory&);
	Directory& operator=(Directory&&);
	DirIter begin();
	DirIter end();
	size_t size() const;
	std::string* operator[](size_t);
	~Directory() = default;
private:
	std::vector<std::string> files;
	std::string dir;
};
#endif

