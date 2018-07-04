#ifndef GETREMOVER
#define GETREMOVER

#include "IComRemover.hpp"
#include "JCXComRemover.hpp"
#include "FileType.hpp"

IComRemover* get_remover(FileType type) {
	switch(type) {
		default:
			return new JCXComRemover();
	}
}

#endif
