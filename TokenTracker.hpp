#ifndef TOKENTRACKER
#define TOKENTRACKER

#include <vector>

class Token;
class TokenIterator;
class TokenTracker {
public:
	friend class TokenIterator;
	TokenTracker() {}
	~TokenTracker();
	TokenTracker& operator<<(Token*);
	TokenIterator begin();
	TokenIterator end();
private:
	TokenTracker(TokenTracker&) = delete;
	TokenTracker(TokenTracker&&) = delete;
	TokenTracker& operator = (TokenTracker&) = delete;
	TokenTracker& operator = (TokenTracker&&) = delete;
	std::vector<Token*> tokens;
};

#endif
