#include "DirectoryReader.hpp"
#include "Directory.hpp"
#include <algorithm>
#include <map>
#include <dirent.h>
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>
#include <stdint.h>
#include <functional>

/* These operators compare the size of the directory list to a given
 * value. These are useful if the user wants to check if the directory
 * reader has a zero size, indicating that the directory reader has
 * searched all paths in the tree.
*/

bool operator==(const DirectoryReader& lhs, size_t rhs) {
	return lhs.dirs.size() == rhs;
}

bool operator!=(const DirectoryReader& lhs, size_t rhs) {
	return !(lhs==rhs);
}

//global scope vector. Just for the static adder function
std::vector<std::string> tmp_vec;

static int adder(const char *fpath, const struct stat *sb,
int tflag, struct FTW *ftwbuf) {
	if (tflag == 5) {
		tmp_vec.push_back(std::string(fpath));
	}
	return 0;
}

DirectoryReader::DirectoryReader(const std::string& path): cur_dir(path) {	
	if (path != "null")
		cur_dir = path;
	else {
		char buff[FILENAME_MAX];
		getcwd( buff, FILENAME_MAX );
		cur_dir = buff;
	}
	int flags = 0;
	flags |= FTW_DEPTH;
	flags |= FTW_PHYS;
	nftw(cur_dir.c_str(), adder, 20, flags);
	
	//move the data from the global vector into the class vector
	dirs = std::move(tmp_vec);
}

/* This operator returns a pointer to a Directory object it creates.
 * The function also changes the directory so the user does not have
 * to do so.
 */
Directory DirectoryReader::operator()() {
	std::string path = std::move(dirs[0]);
	dirs.erase(dirs.begin());
	path += "/";
	Directory dir(std::move(path));
	return dir;
}
