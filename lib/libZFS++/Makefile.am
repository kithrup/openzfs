libZFS___la_CFLAGS = $(AM_CFLAGS) $(LIBRARY_CFLAGS) -fPIC
libZFS___la_CXXFLAGS = $(AM_CXXFLAGS) $(LIBRARY_CXXFLAGS)
libZFS___la_CFLAGS += $(ZLIB_FLAGS)

lib_LTLIBRARIES += libZFS++.la
CPPCHECKTARGETS += libZFS++.la
libZFS___la_LIBADD = \
	libzfs_core.la \
	libnvpair.la \
	libzfs.la

dist_libZFS___la_SOURCES = \
	%D%/ZFSValue.h \
	%D%/ZFSValue.cpp \
	%D%/ZFS.h \
	%D%/ZFSPool.h \
	%D%/ZFSProperties.h \
	%D%/ZFSDataset.h \
	%D%/ZFSVolume.h \
	%D%/ZFSException.h \
	%D%/ZFSPool.cpp \
	%D%/ZFS.cpp


#pkgconfig_DATA += %D%/libZFS++.pc
