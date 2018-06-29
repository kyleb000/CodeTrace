#include "Directory.hpp"
#include "DirIter.hpp"
#include <dirent.h>
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <exception>

Directory::Directory(std::string& path): dir(path) {
	DIR *directory;
	struct dirent *ent;
	if ((directory = opendir (dir.c_str())) != NULL) {
		// print all the files and directories within directory 
		while ((ent = readdir (directory)) != NULL) {
			struct stat path_stat;
			std::string s = dir;
			if (ent->d_name[0] != '.')
				s += ent->d_name;
			stat(s.c_str(), &path_stat);
			if (S_ISREG(path_stat.st_mode)==1) {
				files.push_back(s);
			}
		}
		closedir (directory);
	} else {
		// could not open directory 
		throw (std::runtime_error("No such file or directory"));
	}
}

Directory::Directory(std::string path) : dir(path) {
	DIR *directory;
	struct dirent *ent;
	if ((directory = opendir (dir.c_str())) != NULL) {
		// print all the files and directories within directory 
		while ((ent = readdir (directory)) != NULL) {
			struct stat path_stat;
			std::string s = dir;
			if (ent->d_name[0] != '.')
				s += ent->d_name;
			stat(s.c_str(), &path_stat);
			if (S_ISREG(path_stat.st_mode)==1) {
				files.push_back(s);
			}
		}
		closedir (directory);
	} else {
		// could not open directory 
		throw (std::runtime_error("No such file or directory"));
	}
}

Directory::Directory(Directory& d) {
	files = d.files;
	dir = d.dir;
}

Directory::Directory(Directory&& d) {
	files = std::move(d.files);
	dir = std::move(d.dir);
	d.~Directory();
}

Directory& Directory::operator=(std::string& s) {
	dir = s;
	DIR *directory;
	struct dirent *ent;
	if ((directory = opendir (dir.c_str())) != NULL) {
		// print all the files and directories within directory 
		while ((ent = readdir (directory)) != NULL) {
			struct stat path_stat;
			std::string s = dir;
			if (ent->d_name[0] != '.')
				s += ent->d_name;
			stat(s.c_str(), &path_stat);
			if (S_ISREG(path_stat.st_mode)==1) {
				files.push_back(s);
			}
		}
		closedir (directory);
	} else {
		// could not open directory 
		throw (std::runtime_error("No such file or directory"));
	}
	return *this;
}

Directory& Directory::operator=(Directory& d) {
	files = d.files;
	dir = d.dir;
	return *this;
}

Directory& Directory::operator=(Directory&& d) {
	files = std::move(d.files);
	dir = std::move(d.dir);
	d.~Directory();
	return *this;
}

std::string* Directory::operator[](const size_t pos) {
	return &(files[pos]);
}

size_t Directory::size() const {
	return files.size();
}

DirIter Directory::begin() {
	return DirIter(this, 0);
}

DirIter Directory::end() {
	return DirIter(this, this->size());
}
