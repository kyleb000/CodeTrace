#ifndef IFUNCTIONANALYSER
#define IFUNCTIONANALYSER

#include <string>
#include <vector>

const int name = 0;
const int type = 1;
const int args = 2;

class IFunctionAnalyser {
public:
	friend IFunctionAnalyser* operator << (IFunctionAnalyser* lhs, std::string& rhs) {
		lhs->query = &rhs;
		return lhs;
	}
	
	IFunctionAnalyser() {}
	virtual ~IFunctionAnalyser() {}
	bool type() const { return _type; }
	bool name() const { return _name; }
	bool open_arg() const { return _open_arg; }
	bool args() const { return _args; }
	bool close_arg() const { return _close_arg; }
	virtual void process() = 0;
	virtual size_t get_line() const = 0;
	std::string operator()(const int fnc_data_type) {
		return fnc_data[fnc_data_type];
	}
	void set_line(size_t *ln) { tmp_line = ln; }
	void clear() { 
		_type = _name = _open_arg = _close_arg = _args = false;
		fnc_data.erase(fnc_data.begin(), fnc_data.end());
	}
protected:
	std::vector<std::string> fnc_data;
	std::string* query;
	size_t* tmp_line;
	bool _type{false},
		 _name{false},
		 _open_arg{false},
		 _args{false},
		 _close_arg{false};
		 
};

#endif
