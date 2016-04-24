SHARED_LIB_DEPS =
SHARED_APP_DEPS =
STATIC_APP_DEPS =

COMMON_LOBJS	= $(COMMON_SRCS:.c=.lo)
COMMON_OBJS	= $(COMMON_SRCS:.c=.o)

ARCH_LOBJS	= $(ARCH_SRCS:.c=.lo)
ARCH_OBJS	= $(ARCH_SRCS:.c=.o)

APP_LOBJS	= $(APP_SRCS:.c=.lo)
APP_OBJS	= $(APP_SRCS:.c=.o)

SHARED_OBJS	= $(COMMON_LOBJS) $(ARCH_LOBJS)
STATIC_OBJS	= $(COMMON_OBJS)  $(ARCH_OBJS)

STATIC_LIB	= lib/$(OS_LIB_PREFIX)$(PACKAGE)$(OS_ARCHIVE_EXT)

DSO_VER		= $(OS_LIB_PREFIX)$(PACKAGE)$(OS_LIB_SUFFIX)$(VER_XYZ)
DSO_SONAME	= $(OS_LIB_PREFIX)$(PACKAGE)$(OS_LIB_SUFFIX)$(VER_SONAME)
DSO_SOLINK	= $(OS_LIB_PREFIX)$(PACKAGE)$(OS_LIB_SUFFIX)

SHARED_LIB	= lib/$(DSO_VER)
SHARED_SONAME	= lib/$(DSO_SONAME)
SHARED_SOLINK	= lib/$(DSO_SOLINK)

IMP_DEF		= $(OS_LIB_PREFIX)$(PACKAGE)$(VER_XYZ)$(OS_LIBDEF_EXT)
IMP_VER		= $(OS_LIB_PREFIX)$(PACKAGE)$(VER_XYZ)$(OS_IMPLIB_EXT)
IMP_SONAME	= $(OS_LIB_PREFIX)$(PACKAGE)$(VER_SONAME)$(OS_IMPLIB_EXT)
IMP_SOLINK	= $(OS_LIB_PREFIX)$(PACKAGE)$(OS_IMPLIB_EXT)

IMPLIB_DEF	= lib/$(IMP_DEF)
IMPLIB_VER	= lib/$(IMP_VER)
IMPLIB_SONAME	= lib/$(IMP_SONAME)
IMPLIB_SOLINK	= lib/$(IMP_SOLINK)

APP		= bin/$(OS_APP_PREFIX)$(NICKNAME)$(OS_APP_SUFFIX)
DEFAULT_APP	= bin/$(OS_APP_PREFIX)$(NICKNAME)-default$(OS_APP_SUFFIX)
SHARED_APP	= bin/$(OS_APP_PREFIX)$(NICKNAME)-shared$(OS_APP_SUFFIX)
STATIC_APP	= bin/$(OS_APP_PREFIX)$(NICKNAME)-static$(OS_APP_SUFFIX)

CFLAGS		= $(CFLAGS_DEBUG)  $(CFLAGS_CONFIG)  $(CFLAGS_SYSROOT) \
		   $(CFLAGS_COMMON) $(CFLAGS_CMDLINE) $(CFLAGS_HOST)	\
		   $(CFLAGS_PATH) $(CFLAGS_OS) $(CFLAGS_SITE)            \
		   $(CFLAGS_VERSION)

CFLAGS_SHARED	= $(CFLAGS) $(CFLAGS_PIC) $(CFLAGS_SHARED_ATTR)
CFLAGS_STATIC	= $(CFLAGS) $(CFLAGS_OBJ) $(CFLAGS_STATIC_ATTR)
CFLAGS_APP	= $(CFLAGS) $(CFLAGS_OBJ) $(CFLAGS_APP_ATTR)

LDFLAGS_SHARED	= $(LDFLAGS_DEBUG)   $(LDFLAGS_CONFIG)  $(LDFLAGS_SYSROOT) \
		   $(LDFLAGS_COMMON)  $(LDFLAGS_CMDLINE) $(LDFLAGS_HOST)    \
		   $(LDFLAGS_PATH)    $(SHARED_LIB_DEPS) $(LDFLAGS_LAST)

LDFLAGS_SHARED	+= -Wl,-soname
LDFLAGS_SHARED	+= -Wl,$(DSO_SONAME)
LDFLAGS_SHARED	+= $(LDFLAGS_IMPLIB)

LDFLAGS_APP	= $(LDFLAGS_DEBUG)   $(LDFLAGS_CONFIG)  $(LDFLAGS_SYSROOT) \
		   $(LDFLAGS_COMMON)  $(LDFLAGS_CMDLINE) $(LDFLAGS_HOST)    \
		   $(LDFLAGS_PATH)    $(SHARED_APP_DEPS) $(LDFLAGS_LAST)

LDFLAGS_STATIC	= $(LDFLAGS_DEBUG)   $(LDFLAGS_CONFIG)  $(LDFLAGS_SYSROOT) \
		   $(LDFLAGS_COMMON)  $(LDFLAGS_CMDLINE) $(LDFLAGS_HOST)    \
		   $(LDFLAGS_PATH)    $(STATIC_APP_DEPS) $(LDFLAGS_LAST)
