#include "Directory.hpp"
#include "DirIter.hpp"

std::string* DirIter::operator*() const {
	return (*dir)[sz];
}

DirIter& DirIter::operator++() {
	++sz;
	return *this;
}

DirIter DirIter::operator++(int) {
	DirIter ret = *this;
	++sz;
	return ret;
}

DirIter& DirIter::operator--() {
	--sz;
	return *this;
}

DirIter DirIter::operator--(int) {
	DirIter ret = *this;
	--sz;
	return ret;
}

bool operator==(const DirIter& lhs, const DirIter& rhs) {
	return lhs.sz == rhs.sz;
}

bool operator!=(const DirIter& lhs, const DirIter& rhs) {
	return !(lhs == rhs);
}
