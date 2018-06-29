#ifndef TOKENITERATOR
#define TOKENITERATOR

#include <string>

class TokenTracker;
class Token;

class TokenIterator;

bool operator==(const TokenIterator& lhs, const TokenIterator& rhs);
bool operator!=(const TokenIterator& lhs, const TokenIterator& rhs);

class TokenIterator {
public:
	friend bool operator==(const TokenIterator&, const TokenIterator&);
	friend bool operator!=(const TokenIterator&, const TokenIterator&);
	TokenIterator(TokenTracker* t, size_t s) : tracker(t), sz(s) {}
	Token* operator*() const;
	TokenIterator& operator++();
	TokenIterator operator++(int);
	TokenIterator& operator--();
	TokenIterator operator--(int);
	~TokenIterator() = default;
private:
	TokenTracker* tracker;
	size_t sz;
};

#endif
