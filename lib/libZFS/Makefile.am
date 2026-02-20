libZFS_la_CFLAGS = $(AM_CFLAGS) $(LIBRARY_CFLAGS) -fPIC
libZFS_la_CXXFLAGS = $(AM_CXXFLAGS) $(LIBRARY_CXXFLAGS)
libZFS_la_CFLAGS += $(ZLIB_FLAGS)

lib_LTLIBRARIES += libZFS.la
CPPCHECKTARGETS += libZFS.la
libZFS_la_LIBADD = \
	libzfs_core.la \
	libnvpair.la \
	libzfs.la

dist_libZFS_la_SOURCES = \
	%D%/ZFS.h \
	%D%/ZFSPool.h \
	%D%/ZFSPool.cpp

#pkgconfig_DATA += %D%/libZFS.pc
