#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mydb], [1.0], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([1.0])
AC_CONFIG_SRCDIR([src/btree_int.c])
# AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lhistory':
AC_CHECK_LIB([history], [main])
# FIXME: Replace `main' with a function in `-lmydb':
AC_CHECK_LIB([mydb], [main])
# FIXME: Replace `main' with a function in `-lreadline':
AC_CHECK_LIB([readline], [main])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_CHECK_FUNCS([ftruncate gethostbyname memmove memset mkdir munmap socket strchr strstr strtol])

AC_CONFIG_FILES([src/Makefile])
AC_OUTPUT
