#ifndef TYPEGETTER
#define TYPEGETTER

template <typename T>
class TypeGetter {
public:
	TypeGetter() {}
	void set(T t) {
		type = t;
	}
	T get() const { return type; }
private:
	T type;
};

#endif
