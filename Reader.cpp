#include "ReaderImpl.hpp"
#include "FileIterator.hpp"

Reader::Reader() {
	impl = new ReaderImpl(this);
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
	impl->find(mode);
}

void Reader::load(Directory* dir) {
	impl->load(dir);
}

