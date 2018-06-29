#ifndef DIRECTORYREADER
#define DIRECTORYREADER

class Directory;

#include <string>
#include <vector>

class DirectoryReader;

bool operator==(const DirectoryReader& lhs, size_t rhs);
bool operator!=(const DirectoryReader& lhs, size_t rhs);

class DirectoryReader {
friend bool operator==(const DirectoryReader& lhs, size_t rhs);
friend bool operator!=(const DirectoryReader& lhs, size_t rhs);
public:
	DirectoryReader(const std::string&);
	~DirectoryReader() = default;
	Directory operator()();
	bool end_tree() const;
private:
	DirectoryReader(DirectoryReader&) = delete;
	DirectoryReader(DirectoryReader&&) = delete;
	DirectoryReader& operator =(DirectoryReader&) = delete;
	DirectoryReader& operator =(DirectoryReader&&) = delete;
	std::vector<std::string> dirs;
	std::string cur_dir;
};

#endif
