#include "ReaderImpl.hpp"

Reader::Reader(DirectoryReader *dr) {
	impl = new ReaderImpl(this, dr);
}

Reader::~Reader() {
	impl->~ReaderImpl();
	delete impl;
}

Reader::Reader(Reader& reader) {
	impl = reader.impl;
}

Reader::Reader(Reader&& reader) {
	impl = std::move(reader.impl);
	reader.~Reader();
}

Reader& Reader::operator =(Reader& reader) {
	impl = reader.impl;
	return *this;
}

Reader& Reader::operator =(Reader&& reader) {
	impl = std::move(reader.impl);
	reader.~Reader();
	return *this;
}

void Reader::find(FindMode mode) {
	impl->find(mode,nullptr);
}


