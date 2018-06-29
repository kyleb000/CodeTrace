#include "TokenIterator.hpp"
#include "TokenTracker.hpp"

Token* TokenIterator::operator*() const {
	return tracker->tokens[sz];
}

TokenIterator& TokenIterator::operator++() {
	++sz;
	return *this;
}
TokenIterator TokenIterator::operator++(int) {
	TokenIterator ret = *this;
	++sz;
	return ret;
}
TokenIterator& TokenIterator::operator--() {
	--sz;
	return *this;
}

TokenIterator TokenIterator::operator--(int) {
	TokenIterator ret = *this;
	--sz;
	return ret;
}

bool operator==(const TokenIterator& lhs, const TokenIterator& rhs) {
	return lhs.sz == rhs.sz;
}
bool operator!=(const TokenIterator& lhs, const TokenIterator& rhs) {
	return !(lhs == rhs);
}
