#include "TokenTracker.hpp"
#include "TokenIterator.hpp"

TokenTracker& TokenTracker::operator<<(Token* rhs) {
	/* insert code to add the token */
	return *this;
}

TokenIterator TokenTracker::begin() {
	return TokenIterator(this, 0);
}

TokenIterator TokenTracker::end() {
	return TokenIterator(this, tokens.size());
}
