#include <stdio.h>

#include "ZFS.h"
#include "ZFSPool.h"

ZFSPool::~ZFSPool() {
	fprintf(stderr, "in %s\n", __FUNCTION__);
	fflush(stderr);
	free(this->ivar);
	this->ivar = NULL;
}
