#ifdef MG_MODULE_LINES
#line 1 "mjs/license.h"
#endif
/*
 * Copyright (c) 2013-2016 Cesanta Software Limited
 * All rights reserved
 *
 * This software is dual-licensed: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. For the terms of this
 * license, see <http://www.gnu.org/licenses/>.
 *
 * You are free to use this software under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * Alternatively, you can license this software under a commercial
 * license, as set out in <https://www.cesanta.com/license>.
 *
 * THIS FILE IS AMALGAMATED, please run the unamalgam script before making edits
 * if you want to contribute them back.
 */
#ifdef MG_MODULE_LINES
#line 1 "common/platform.h"
#endif
#ifndef CS_COMMON_PLATFORM_H_
#define CS_COMMON_PLATFORM_H_

/*
 * For the "custom" platform, includes and dependencies can be
 * provided through mg_locals.h.
 */
#define CS_P_CUSTOM 0
#define CS_P_UNIX 1
#define CS_P_WINDOWS 2
#define CS_P_ESP8266 3
#define CS_P_CC3200 4
#define CS_P_MSP432 5
#define CS_P_CC3100 6
#define CS_P_TM4C129 14
#define CS_P_MBED 7
#define CS_P_WINCE 8
#define CS_P_NXP_LPC 13
#define CS_P_NXP_KINETIS 9
#define CS_P_NRF51 12
#define CS_P_NRF52 10
#define CS_P_PIC32_HARMONY 11
/* Next id: 15 */

/* If not specified explicitly, we guess platform by defines. */
#ifndef CS_PLATFORM

#if defined(TARGET_IS_MSP432P4XX) || defined(__MSP432P401R__)
#define CS_PLATFORM CS_P_MSP432
#elif defined(cc3200)
#define CS_PLATFORM CS_P_CC3200
#elif defined(__unix__) || defined(__APPLE__)
#define CS_PLATFORM CS_P_UNIX
#elif defined(WINCE)
#define CS_PLATFORM CS_P_WINCE
#elif defined(_WIN32)
#define CS_PLATFORM CS_P_WINDOWS
#elif defined(__MBED__)
#define CS_PLATFORM CS_P_MBED
#elif defined(__USE_LPCOPEN)
#define CS_PLATFORM CS_P_NXP_LPC
#elif defined(FRDM_K64F) || defined(FREEDOM)
#define CS_PLATFORM CS_P_NXP_KINETIS
#elif defined(PIC32)
#define CS_PLATFORM CS_P_PIC32_HARMONY
#elif defined(ICACHE_FLASH)
#define CS_PLATFORM CS_P_ESP8266
#elif defined(TARGET_IS_TM4C129_RA0) || defined(TARGET_IS_TM4C129_RA1) || \
    defined(TARGET_IS_TM4C129_RA2)
#define CS_PLATFORM CS_P_TM4C129
#endif

#ifndef CS_PLATFORM
#error "CS_PLATFORM is not specified and we couldn't guess it."
#endif

#endif /* !defined(CS_PLATFORM) */

#define MG_NET_IF_SOCKET 1
#define MG_NET_IF_SIMPLELINK 2
#define MG_NET_IF_LWIP_LOW_LEVEL 3
#define MG_NET_IF_PIC32_HARMONY 4

#define MG_SSL_IF_OPENSSL 1
#define MG_SSL_IF_MBEDTLS 2
#define MG_SSL_IF_SIMPLELINK 3

/* Amalgamated: #include "common/platforms/platform_unix.h" */
/* Amalgamated: #include "common/platforms/platform_windows.h" */
/* Amalgamated: #include "common/platforms/platform_esp8266.h" */
/* Amalgamated: #include "common/platforms/platform_cc3200.h" */
/* Amalgamated: #include "common/platforms/platform_cc3100.h" */
/* Amalgamated: #include "common/platforms/platform_mbed.h" */
/* Amalgamated: #include "common/platforms/platform_nrf51.h" */
/* Amalgamated: #include "common/platforms/platform_nrf52.h" */
/* Amalgamated: #include "common/platforms/platform_wince.h" */
/* Amalgamated: #include "common/platforms/platform_nxp_lpc.h" */
/* Amalgamated: #include "common/platforms/platform_nxp_kinetis.h" */
/* Amalgamated: #include "common/platforms/platform_pic32_harmony.h" */

/* Common stuff */

#ifdef __GNUC__
#define NORETURN __attribute__((noreturn))
#define NOINLINE __attribute__((noinline))
#define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#define NOINSTR __attribute__((no_instrument_function))
#else
#define NORETURN
#define NOINLINE
#define WARN_UNUSED_RESULT
#define NOINSTR
#endif /* __GNUC__ */

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif

#endif /* CS_COMMON_PLATFORM_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_windows.h"
#endif
#ifndef CS_COMMON_PLATFORMS_PLATFORM_WINDOWS_H_
#define CS_COMMON_PLATFORMS_PLATFORM_WINDOWS_H_
#if CS_PLATFORM == CS_P_WINDOWS

/*
 * MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
 * MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
 * MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
 * MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
 * MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
 * MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
 * MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio 2003)
 * MSVC++ 7.0  _MSC_VER == 1300
 * MSVC++ 6.0  _MSC_VER == 1200
 * MSVC++ 5.0  _MSC_VER == 1100
 */
#ifdef _MSC_VER
#pragma warning(disable : 4127) /* FD_SET() emits warning, disable it */
#pragma warning(disable : 4204) /* missing c99 support */
#endif

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <direct.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib") /* Linking with winsock library */
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <process.h>

#if defined(_MSC_VER) && _MSC_VER >= 1800
#define strdup _strdup
#endif

#ifndef EINPROGRESS
#define EINPROGRESS WSAEINPROGRESS
#endif
#ifndef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif
#ifndef __func__
#define STRX(x) #x
#define STR(x) STRX(x)
#define __func__ __FILE__ ":" STR(__LINE__)
#endif
#define snprintf _snprintf
#define fileno _fileno
#define vsnprintf _vsnprintf
#define sleep(x) Sleep((x) *1000)
#define to64(x) _atoi64(x)
#if !defined(__MINGW32__) && !defined(__MINGW64__)
#define popen(x, y) _popen((x), (y))
#define pclose(x) _pclose(x)
#endif
#define rmdir _rmdir
#if defined(_MSC_VER) && _MSC_VER >= 1400
#define fseeko(x, y, z) _fseeki64((x), (y), (z))
#else
#define fseeko(x, y, z) fseek((x), (y), (z))
#endif
#if defined(_MSC_VER) && _MSC_VER <= 1200
typedef unsigned long uintptr_t;
typedef long intptr_t;
#endif
typedef int socklen_t;
#if _MSC_VER >= 1700
#include <stdint.h>
#else
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif
typedef SOCKET sock_t;
typedef uint32_t in_addr_t;
#ifndef UINT16_MAX
#define UINT16_MAX 65535
#endif
#ifndef UINT32_MAX
#define UINT32_MAX 4294967295
#endif
#ifndef pid_t
#define pid_t HANDLE
#endif
#define INT64_FMT "I64d"
#define INT64_X_FMT "I64x"
#define SIZE_T_FMT "Iu"
#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)
typedef struct stat cs_stat_t;
#else
typedef struct _stati64 cs_stat_t;
#endif
#ifndef S_ISDIR
#define S_ISDIR(x) (((x) &_S_IFMT) == _S_IFDIR)
#endif
#ifndef S_ISREG
#define S_ISREG(x) (((x) &_S_IFMT) == _S_IFREG)
#endif
#define DIRSEP '\\'

#ifndef va_copy
#ifdef __va_copy
#define va_copy __va_copy
#else
#define va_copy(x, y) (x) = (y)
#endif
#endif

#ifndef MG_MAX_HTTP_REQUEST_SIZE
#define MG_MAX_HTTP_REQUEST_SIZE 8192
#endif

#ifndef MG_MAX_HTTP_SEND_MBUF
#define MG_MAX_HTTP_SEND_MBUF 4096
#endif

#ifndef MG_MAX_HTTP_HEADERS
#define MG_MAX_HTTP_HEADERS 40
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#ifndef MG_ENABLE_BROADCAST
#define MG_ENABLE_BROADCAST 1
#endif

#ifndef MG_ENABLE_DIRECTORY_LISTING
#define MG_ENABLE_DIRECTORY_LISTING 1
#endif

#ifndef MG_ENABLE_FILESYSTEM
#define MG_ENABLE_FILESYSTEM 1
#endif

#ifndef MG_ENABLE_HTTP_CGI
#define MG_ENABLE_HTTP_CGI 1
#endif

#ifndef MG_NET_IF
#define MG_NET_IF MG_NET_IF_SOCKET
#endif

#endif /* CS_PLATFORM == CS_P_WINDOWS */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_WINDOWS_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_unix.h"
#endif
#ifndef CS_COMMON_PLATFORMS_PLATFORM_UNIX_H_
#define CS_COMMON_PLATFORMS_PLATFORM_UNIX_H_
#if CS_PLATFORM == CS_P_UNIX

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#endif

/* <inttypes.h> wants this for C++ */
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

/* C++ wants that for INT64_MAX */
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

/* Enable fseeko() and ftello() functions */
#ifndef _LARGEFILE_SOURCE
#define _LARGEFILE_SOURCE
#endif

/* Enable 64-bit file offsets */
#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64
#endif

#include <arpa/inet.h>
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __APPLE__
#include <machine/endian.h>
#ifndef BYTE_ORDER
#define LITTLE_ENDIAN __DARWIN_LITTLE_ENDIAN
#define BIG_ENDIAN __DARWIN_BIG_ENDIAN
#define PDP_ENDIAN __DARWIN_PDP_ENDIAN
#define BYTE_ORDER __DARWIN_BYTE_ORDER
#endif
#endif

/*
 * osx correctly avoids defining strtoll when compiling in strict ansi mode.
 * c++ 11 standard defines strtoll as well.
 * We require strtoll, and if your embedded pre-c99 compiler lacks one, please
 * implement a shim.
 */
#if !(defined(__cplusplus) && __cplusplus >= 201103L) && \
    !(defined(__DARWIN_C_LEVEL) && __DARWIN_C_LEVEL >= 200809L)
long long strtoll(const char *, char **, int);
#endif

typedef int sock_t;
#define INVALID_SOCKET (-1)
#define SIZE_T_FMT "zu"
typedef struct stat cs_stat_t;
#define DIRSEP '/'
#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64

#ifndef __cdecl
#define __cdecl
#endif

#ifndef va_copy
#ifdef __va_copy
#define va_copy __va_copy
#else
#define va_copy(x, y) (x) = (y)
#endif
#endif

#define closesocket(x) close(x)

#ifndef MG_MAX_HTTP_REQUEST_SIZE
#define MG_MAX_HTTP_REQUEST_SIZE 8192
#endif

#ifndef MG_MAX_HTTP_SEND_MBUF
#define MG_MAX_HTTP_SEND_MBUF 4096
#endif

#ifndef MG_MAX_HTTP_HEADERS
#define MG_MAX_HTTP_HEADERS 40
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#ifndef MG_ENABLE_BROADCAST
#define MG_ENABLE_BROADCAST 1
#endif

#ifndef MG_ENABLE_DIRECTORY_LISTING
#define MG_ENABLE_DIRECTORY_LISTING 1
#endif

#ifndef MG_ENABLE_FILESYSTEM
#define MG_ENABLE_FILESYSTEM 1
#endif

#ifndef MG_ENABLE_HTTP_CGI
#define MG_ENABLE_HTTP_CGI 1
#endif

#ifndef MG_NET_IF
#define MG_NET_IF MG_NET_IF_SOCKET
#endif

#endif /* CS_PLATFORM == CS_P_UNIX */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_UNIX_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_cc3200.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_CC3200_H_
#define CS_COMMON_PLATFORMS_PLATFORM_CC3200_H_
#if CS_PLATFORM == CS_P_CC3200

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#ifndef __TI_COMPILER_VERSION__
#include <fcntl.h>
#include <sys/time.h>
#endif

#define MG_NET_IF MG_NET_IF_SIMPLELINK
#define MG_SSL_IF MG_SSL_IF_SIMPLELINK

/* Only SPIFFS supports directories, SLFS does not. */
#if defined(CC3200_FS_SPIFFS) && !defined(MG_ENABLE_DIRECTORY_LISTING)
#define MG_ENABLE_DIRECTORY_LISTING 1
#endif

/* Amalgamated: #include "common/platforms/simplelink/cs_simplelink.h" */

typedef int sock_t;
#define INVALID_SOCKET (-1)
#define SIZE_T_FMT "u"
typedef struct stat cs_stat_t;
#define DIRSEP '/'
#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define __cdecl

#define fileno(x) -1

/* Some functions we implement for Mongoose. */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __TI_COMPILER_VERSION__
struct SlTimeval_t;
#define timeval SlTimeval_t
int gettimeofday(struct timeval *t, void *tz);

int asprintf(char **strp, const char *fmt, ...);

#endif

/* TI's libc does not have stat & friends, add them. */
#ifdef __TI_COMPILER_VERSION__

#include <file.h>

typedef unsigned int mode_t;
typedef size_t _off_t;
typedef long ssize_t;

struct stat {
  int st_ino;
  mode_t st_mode;
  int st_nlink;
  time_t st_mtime;
  off_t st_size;
};

int _stat(const char *pathname, struct stat *st);
#define stat(a, b) _stat(a, b)

#define __S_IFMT 0170000

#define __S_IFDIR 0040000
#define __S_IFCHR 0020000
#define __S_IFREG 0100000

#define __S_ISTYPE(mode, mask) (((mode) &__S_IFMT) == (mask))

#define S_IFDIR __S_IFDIR
#define S_IFCHR __S_IFCHR
#define S_IFREG __S_IFREG
#define S_ISDIR(mode) __S_ISTYPE((mode), __S_IFDIR)
#define S_ISREG(mode) __S_ISTYPE((mode), __S_IFREG)

/* As of 5.2.7, TI compiler does not support va_copy() yet. */
#define va_copy(apc, ap) ((apc) = (ap))

#endif /* __TI_COMPILER_VERSION__ */

#ifdef CC3200_FS_SPIFFS
#include <common/spiffs/spiffs.h>

typedef struct {
  spiffs_DIR dh;
  struct spiffs_dirent de;
} DIR;

#define d_name name
#define dirent spiffs_dirent

DIR *opendir(const char *dir_name);
int closedir(DIR *dir);
struct dirent *readdir(DIR *dir);
#endif /* CC3200_FS_SPIFFS */

#ifdef CC3200_FS_SLFS
#define MG_FS_SLFS
#endif

#if (defined(CC3200_FS_SPIFFS) || defined(CC3200_FS_SLFS)) && !defined(MG_ENABLE_FILESYSTEM)
#define MG_ENABLE_FILESYSTEM 1
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#ifdef __cplusplus
}
#endif

#endif /* CS_PLATFORM == CS_P_CC3200 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_CC3200_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/simplelink/cs_simplelink.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_SIMPLELINK_CS_SIMPLELINK_H_
#define CS_COMMON_PLATFORMS_SIMPLELINK_CS_SIMPLELINK_H_

/* If simplelink.h is already included, all bets are off. */
#if MG_NET_IF == MG_NET_IF_SIMPLELINK && !defined(__SIMPLELINK_H__)

#include <stdbool.h>

#ifndef __TI_COMPILER_VERSION__
#undef __CONCAT
#undef FD_CLR
#undef FD_ISSET
#undef FD_SET
#undef FD_SETSIZE
#undef FD_ZERO
#undef fd_set
#endif

/* We want to disable SL_INC_STD_BSD_API_NAMING, so we include user.h ourselves
 * and undef it. */
#define PROVISIONING_API_H_
#include <simplelink/user.h>
#undef PROVISIONING_API_H_
#undef SL_INC_STD_BSD_API_NAMING

#include <simplelink/include/simplelink.h>
#include <simplelink/include/netapp.h>

/* Now define only the subset of the BSD API that we use.
 * Notably, close(), read() and write() are not defined. */
#define AF_INET SL_AF_INET

#define socklen_t SlSocklen_t
#define sockaddr SlSockAddr_t
#define sockaddr_in SlSockAddrIn_t
#define in_addr SlInAddr_t

#define SOCK_STREAM SL_SOCK_STREAM
#define SOCK_DGRAM SL_SOCK_DGRAM

#define htonl sl_Htonl
#define ntohl sl_Ntohl
#define htons sl_Htons
#define ntohs sl_Ntohs

#ifndef EACCES
#define EACCES SL_EACCES
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT SL_EAFNOSUPPORT
#endif
#ifndef EAGAIN
#define EAGAIN SL_EAGAIN
#endif
#ifndef EBADF
#define EBADF SL_EBADF
#endif
#ifndef EINVAL
#define EINVAL SL_EINVAL
#endif
#ifndef ENOMEM
#define ENOMEM SL_ENOMEM
#endif
#ifndef EWOULDBLOCK
#define EWOULDBLOCK SL_EWOULDBLOCK
#endif

#define SOMAXCONN 8

#ifdef __cplusplus
extern "C" {
#endif

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
char *inet_ntoa(struct in_addr in);
int inet_pton(int af, const char *src, void *dst);

struct mg_mgr;
struct mg_connection;

typedef void (*mg_init_cb)(struct mg_mgr *mgr);
bool mg_start_task(int priority, int stack_size, mg_init_cb mg_init);

void mg_run_in_task(void (*cb)(struct mg_mgr *mgr, void *arg), void *cb_arg);

int sl_fs_init(void);

void sl_restart_cb(struct mg_mgr *mgr);

int sl_set_ssl_opts(struct mg_connection *nc);

#ifdef __cplusplus
}
#endif

#endif /* MG_NET_IF == MG_NET_IF_SIMPLELINK && !defined(__SIMPLELINK_H__) */

#endif /* CS_COMMON_PLATFORMS_SIMPLELINK_CS_SIMPLELINK_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_esp8266.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_ESP8266_H_
#define CS_COMMON_PLATFORMS_PLATFORM_ESP8266_H_
#if CS_PLATFORM == CS_P_ESP8266

#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <machine/endian.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#define SIZE_T_FMT "u"
typedef struct stat cs_stat_t;
#define DIRSEP '/'
#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define __cdecl
#define _FILE_OFFSET_BITS 32

#ifndef RTOS_SDK
#define fileno(x) -1
#endif

#define MG_LWIP 1

/* struct timeval is defined in sys/time.h. */
#define LWIP_TIMEVAL_PRIVATE 0

#ifndef MG_NET_IF
#include <lwip/opt.h>
#if LWIP_SOCKET /* RTOS SDK has LWIP sockets */
#  define MG_NET_IF MG_NET_IF_SOCKET
#else
#  define MG_NET_IF MG_NET_IF_LWIP_LOW_LEVEL
#endif
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#endif /* CS_PLATFORM == CS_P_ESP8266 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_ESP8266_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_cc3100.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_CC3100_H_
#define CS_COMMON_PLATFORMS_PLATFORM_CC3100_H_
#if CS_PLATFORM == CS_P_CC3100

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define MG_NET_IF MG_NET_IF_SIMPLELINK
#define MG_SSL_IF MG_SSL_IF_SIMPLELINK

/*
 * CC3100 SDK and STM32 SDK include headers w/out path, just like
 * #include "simplelink.h". As result, we have to add all required directories
 * into Makefile IPATH and do the same thing (include w/out path)
 */

#include <simplelink.h>
#include <netapp.h>
#undef timeval 

typedef int sock_t;
#define INVALID_SOCKET (-1)

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define SIZE_T_FMT "u"

#define SOMAXCONN 8

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
char *inet_ntoa(struct in_addr in);
int inet_pton(int af, const char *src, void *dst);

#endif /* CS_PLATFORM == CS_P_CC3100 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_CC3100_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_mbed.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_MBED_H_
#define CS_COMMON_PLATFORMS_PLATFORM_MBED_H_
#if CS_PLATFORM == CS_P_MBED

/* Amalgamated: #include "mbed.h" */

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

/*
 * mbed can be compiled with the ARM compiler which
 * just doesn't come with a gettimeofday shim
 * because it's a BSD API and ARM targets embedded
 * non-unix platforms.
 */
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
#define _TIMEVAL_DEFINED
#define gettimeofday _gettimeofday

/* copied from GCC on ARM; for some reason useconds are signed */
typedef long suseconds_t; /* microseconds (signed) */
struct timeval {
  time_t tv_sec;       /* seconds */
  suseconds_t tv_usec; /* and microseconds */
};

#endif

#if MG_NET_IF == MG_NET_IF_SIMPLELINK

#define MG_SIMPLELINK_NO_OSI 1

#include <simplelink.h>

typedef int sock_t;
#define INVALID_SOCKET (-1)

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define SIZE_T_FMT "u"

#define SOMAXCONN 8

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
char *inet_ntoa(struct in_addr in);
int inet_pton(int af, const char *src, void *dst);

#endif /* MG_NET_IF == MG_NET_IF_SIMPLELINK */

#endif /* CS_PLATFORM == CS_P_MBED */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_MBED_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_nrf51.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */
#ifndef CS_COMMON_PLATFORMS_PLATFORM_NRF51_H_
#define CS_COMMON_PLATFORMS_PLATFORM_NRF51_H_
#if CS_PLATFORM == CS_P_NRF51

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define to64(x) strtoll(x, NULL, 10)

#define MG_NET_IF             MG_NET_IF_LWIP_LOW_LEVEL
#define MG_LWIP               1
#define MG_ENABLE_IPV6        1

/*
 * For ARM C Compiler, make lwip to export `struct timeval`; for other
 * compilers, suppress it.
 */
#if !defined(__ARMCC_VERSION)
# define LWIP_TIMEVAL_PRIVATE  0
#else
struct timeval;
int gettimeofday(struct timeval *tp, void *tzp);
#endif

#define INT64_FMT PRId64
#define SIZE_T_FMT "u"

/*
 * ARM C Compiler doesn't have strdup, so we provide it
 */
#define CS_ENABLE_STRDUP defined(__ARMCC_VERSION)

#endif /* CS_PLATFORM == CS_P_NRF51 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_NRF51_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_nrf52.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */
#ifndef CS_COMMON_PLATFORMS_PLATFORM_NRF52_H_
#define CS_COMMON_PLATFORMS_PLATFORM_NRF52_H_
#if CS_PLATFORM == CS_P_NRF52

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define to64(x) strtoll(x, NULL, 10)

#define MG_NET_IF             MG_NET_IF_LWIP_LOW_LEVEL
#define MG_LWIP               1
#define MG_ENABLE_IPV6        1

#if !defined(ENOSPC)
# define ENOSPC 28  /* No space left on device */
#endif

/*
 * For ARM C Compiler, make lwip to export `struct timeval`; for other
 * compilers, suppress it.
 */
#if !defined(__ARMCC_VERSION)
# define LWIP_TIMEVAL_PRIVATE  0
#endif

#define INT64_FMT PRId64
#define SIZE_T_FMT "u"

/*
 * ARM C Compiler doesn't have strdup, so we provide it
 */
#define CS_ENABLE_STRDUP defined(__ARMCC_VERSION)

#endif /* CS_PLATFORM == CS_P_NRF52 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_NRF52_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_wince.h"
#endif
#ifndef CS_COMMON_PLATFORMS_PLATFORM_WINCE_H_
#define CS_COMMON_PLATFORMS_PLATFORM_WINCE_H_

#if CS_PLATFORM == CS_P_WINCE

/*
 * MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
 * MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
 * MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
 * MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
 * MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
 * MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
 * MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio 2003)
 * MSVC++ 7.0  _MSC_VER == 1300
 * MSVC++ 6.0  _MSC_VER == 1200
 * MSVC++ 5.0  _MSC_VER == 1100
 */
#pragma warning(disable : 4127) /* FD_SET() emits warning, disable it */
#pragma warning(disable : 4204) /* missing c99 support */

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib, "ws2.lib") /* Linking with WinCE winsock library */

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#define strdup _strdup

#ifndef EINPROGRESS
#define EINPROGRESS WSAEINPROGRESS
#endif

#ifndef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif

#ifndef __func__
#define STRX(x) #x
#define STR(x) STRX(x)
#define __func__ __FILE__ ":" STR(__LINE__)
#endif

#define snprintf _snprintf
#define fileno _fileno
#define vsnprintf _vsnprintf
#define sleep(x) Sleep((x) *1000)
#define to64(x) _atoi64(x)
#define rmdir _rmdir

#if defined(_MSC_VER) && _MSC_VER >= 1400
#define fseeko(x, y, z) _fseeki64((x), (y), (z))
#else
#define fseeko(x, y, z) fseek((x), (y), (z))
#endif

typedef int socklen_t;

#if _MSC_VER >= 1700
#include <stdint.h>
#else
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif

typedef SOCKET sock_t;
typedef uint32_t in_addr_t;

#ifndef UINT16_MAX
#define UINT16_MAX 65535
#endif

#ifndef UINT32_MAX
#define UINT32_MAX 4294967295
#endif

#ifndef pid_t
#define pid_t HANDLE
#endif

#define INT64_FMT "I64d"
#define INT64_X_FMT "I64x"
/* TODO(alashkin): check if this is correct */
#define SIZE_T_FMT "u"

#define DIRSEP '\\'

#ifndef va_copy
#ifdef __va_copy
#define va_copy __va_copy
#else
#define va_copy(x, y) (x) = (y)
#endif
#endif

#ifndef MG_MAX_HTTP_REQUEST_SIZE
#define MG_MAX_HTTP_REQUEST_SIZE 8192
#endif

#ifndef MG_MAX_HTTP_SEND_MBUF
#define MG_MAX_HTTP_SEND_MBUF 4096
#endif

#ifndef MG_MAX_HTTP_HEADERS
#define MG_MAX_HTTP_HEADERS 40
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#define abort() DebugBreak();

#ifndef BUFSIZ
#define BUFSIZ 4096
#endif
/*
 * Explicitly disabling MG_ENABLE_THREADS for WinCE
 * because they are enabled for _WIN32 by default
 */
#ifndef MG_ENABLE_THREADS
#define MG_ENABLE_THREADS 0
#endif

#ifndef MG_ENABLE_FILESYSTEM
#define MG_ENABLE_FILESYSTEM 1
#endif

#ifndef MG_NET_IF
#define MG_NET_IF MG_NET_IF_SOCKET
#endif

typedef struct _stati64 {
  uint32_t st_mtime;
  uint32_t st_size;
  uint32_t st_mode;
} cs_stat_t;

/*
 * WinCE 6.0 has a lot of useful definitions in ATL (not windows.h) headers
 * use #ifdefs to avoid conflicts
 */

#ifndef ENOENT
#define ENOENT ERROR_PATH_NOT_FOUND
#endif

#ifndef EACCES
#define EACCES ERROR_ACCESS_DENIED
#endif

#ifndef ENOMEM
#define ENOMEM ERROR_NOT_ENOUGH_MEMORY
#endif

#ifndef _UINTPTR_T_DEFINED
typedef unsigned int* uintptr_t;
#endif

#define _S_IFREG 2
#define _S_IFDIR 4

#ifndef S_ISDIR
#define S_ISDIR(x) (((x) & _S_IFDIR) != 0)
#endif

#ifndef S_ISREG
#define S_ISREG(x) (((x) & _S_IFREG) != 0)
#endif

int open(const char *filename, int oflag, int pmode);
int _wstati64(const wchar_t *path, cs_stat_t *st);
const char *strerror();

#endif /* CS_PLATFORM == CS_P_WINCE */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_WINCE_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_nxp_lpc.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_NXP_LPC_H_
#define CS_COMMON_PLATFORMS_PLATFORM_NXP_LPC_H_

#if CS_PLATFORM == CS_P_NXP_LPC

#include <ctype.h>
#include <stdint.h>
#include <string.h>

#define SIZE_T_FMT "u"
typedef struct stat cs_stat_t;
#define INT64_FMT "lld"
#define INT64_X_FMT "llx"
#define __cdecl

#define MG_LWIP 1

#define MG_NET_IF MG_NET_IF_LWIP_LOW_LEVEL

/*
 * LPCXpress comes with 3 C library implementations: Newlib, NewlibNano and Redlib.
 * See https://community.nxp.com/message/630860 for more details.
 *
 * Redlib is the default and lacks certain things, so we provide them.
 */
#ifdef __REDLIB_INTERFACE_VERSION__

/* Let LWIP define timeval for us. */
#define LWIP_TIMEVAL_PRIVATE 1

#define va_copy(d, s) __builtin_va_copy(d, s)

#define CS_ENABLE_TO64 1
#define to64(x) cs_to64(x)

#define CS_ENABLE_STRDUP 1

#else

#include <sys/time.h>
#define LWIP_TIMEVAL_PRIVATE 0
#define to64(x) strtoll(x, NULL, 10)

#endif

#endif /* CS_PLATFORM == CS_P_NXP_LPC */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_NXP_LPC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_nxp_kinetis.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_NXP_KINETIS_H_
#define CS_COMMON_PLATFORMS_PLATFORM_NXP_KINETIS_H_

#if CS_PLATFORM == CS_P_NXP_KINETIS

#include <ctype.h>
#include <inttypes.h>
#include <string.h>
#include <sys/time.h>

#define SIZE_T_FMT "u"
typedef struct stat cs_stat_t;
#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT "lld"
#define INT64_X_FMT "llx"
#define __cdecl

#define MG_LWIP 1

#define MG_NET_IF MG_NET_IF_LWIP_LOW_LEVEL

/* struct timeval is defined in sys/time.h. */
#define LWIP_TIMEVAL_PRIVATE 0

#endif /* CS_PLATFORM == CS_P_NXP_KINETIS */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_NXP_KINETIS_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/platforms/platform_pic32_harmony.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_PIC32_HARMONY_H_
#define CS_COMMON_PLATFORMS_PLATFORM_PIC32_HARMONY_H_

#if CS_PLATFORM == CS_P_PIC32_HARMONY

#define MG_NET_IF MG_NET_IF_PIC32_HARMONY

#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#include <system_config.h>
#include <system_definitions.h>

typedef TCP_SOCKET sock_t;
#define to64(x) strtoll(x, NULL, 10)

#define SIZE_T_FMT "lu"
#define INT64_FMT "lld"

char* inet_ntoa(struct in_addr in);

#endif /* CS_PLATFORM == CS_P_PIC32_HARMONY */

#endif /* CS_COMMON_PLATFORMS_PLATFORM_PIC32_HARMONY_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/cs_dbg.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_CS_DBG_H_
#define CS_COMMON_CS_DBG_H_

/* Amalgamated: #include "common/platform.h" */

#if CS_ENABLE_STDIO
#include <stdio.h>
#endif

#ifndef CS_ENABLE_DEBUG
#define CS_ENABLE_DEBUG 0
#endif

#ifndef CS_LOG_ENABLE_TS_DIFF
#define CS_LOG_ENABLE_TS_DIFF 0
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum cs_log_level {
  LL_NONE = -1,
  LL_ERROR = 0,
  LL_WARN = 1,
  LL_INFO = 2,
  LL_DEBUG = 3,
  LL_VERBOSE_DEBUG = 4,

  _LL_MIN = -2,
  _LL_MAX = 5,
};

void cs_log_set_level(enum cs_log_level level);

#if CS_ENABLE_STDIO

void cs_log_set_file(FILE *file);

extern enum cs_log_level cs_log_level;
void cs_log_print_prefix(const char *func);
void cs_log_printf(const char *fmt, ...);

#define LOG(l, x)                    \
  do {                               \
    if (cs_log_level >= l) {         \
      cs_log_print_prefix(__func__); \
      cs_log_printf x;               \
    }                                \
  } while (0)

#ifndef CS_NDEBUG

#define DBG(x)                              \
  do {                                      \
    if (cs_log_level >= LL_VERBOSE_DEBUG) { \
      cs_log_print_prefix(__func__);        \
      cs_log_printf x;                      \
    }                                       \
  } while (0)

#else /* NDEBUG */

#define DBG(x)

#endif

#else /* CS_ENABLE_STDIO */

#define LOG(l, x)
#define DBG(x)

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_COMMON_CS_DBG_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/cs_time.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_CS_TIME_H_
#define CS_COMMON_CS_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Sub-second granularity time(). */
double cs_time(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_COMMON_CS_TIME_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/cs_file.h"
#endif
/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_CS_FILE_H_
#define CS_COMMON_CS_FILE_H_

/* Amalgamated: #include "common/platform.h" */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * Read whole file `path` in memory. It is responsibility of the caller
 * to `free()` allocated memory. File content is guaranteed to be
 * '\0'-terminated. File size is returned in `size` variable, which does not
 * count terminating `\0`.
 * Return: allocated memory, or NULL on error.
 */
char *cs_read_file(const char *path, size_t *size);

#ifdef CS_MMAP
char *cs_mmap_file(const char *path, size_t *size);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_COMMON_CS_FILE_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/mbuf.h"
#endif
/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

/*
 * === Memory Buffers
 *
 * Mbufs are mutable/growing memory buffers, like C++ strings.
 * Mbuf can append data to the end of a buffer or insert data into arbitrary
 * position in the middle of a buffer. The buffer grows automatically when
 * needed.
 */

#ifndef CS_COMMON_MBUF_H_
#define CS_COMMON_MBUF_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdlib.h>

#ifndef MBUF_SIZE_MULTIPLIER
#define MBUF_SIZE_MULTIPLIER 1.5
#endif

/* Memory buffer descriptor */
struct mbuf {
  char *buf;   /* Buffer pointer */
  size_t len;  /* Data length. Data is located between offset 0 and len. */
  size_t size; /* Buffer size allocated by realloc(1). Must be >= len */
};

/*
 * Initialises an Mbuf.
 * `initial_capacity` specifies the initial capacity of the mbuf.
 */
void mbuf_init(struct mbuf *, size_t initial_capacity);

/* Frees the space allocated for the mbuffer and resets the mbuf structure. */
void mbuf_free(struct mbuf *);

/*
 * Appends data to the Mbuf.
 *
 * Returns the number of bytes appended or 0 if out of memory.
 */
size_t mbuf_append(struct mbuf *, const void *data, size_t data_size);

/*
 * Inserts data at a specified offset in the Mbuf.
 *
 * Existing data will be shifted forwards and the buffer will
 * be grown if necessary.
 * Returns the number of bytes inserted.
 */
size_t mbuf_insert(struct mbuf *, size_t, const void *, size_t);

/* Removes `data_size` bytes from the beginning of the buffer. */
void mbuf_remove(struct mbuf *, size_t data_size);

/*
 * Resizes an Mbuf.
 *
 * If `new_size` is smaller than buffer's `len`, the
 * resize is not performed.
 */
void mbuf_resize(struct mbuf *, size_t new_size);

/* Shrinks an Mbuf by resizing its `size` to `len`. */
void mbuf_trim(struct mbuf *);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* CS_COMMON_MBUF_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/mg_str.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_MG_STR_H_
#define CS_COMMON_MG_STR_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Describes chunk of memory */
struct mg_str {
  const char *p; /* Memory chunk pointer */
  size_t len;    /* Memory chunk length */
};

/*
 * Helper functions for creating mg_str struct from plain C string.
 * `NULL` is allowed and becomes `{NULL, 0}`.
 */
struct mg_str mg_mk_str(const char *s);
struct mg_str mg_mk_str_n(const char *s, size_t len);

/* Macro for initializing mg_str. */
#define MG_MK_STR(str_literal) \
  { str_literal, sizeof(str_literal) - 1 }

/*
 * Cross-platform version of `strcmp()` where where first string is
 * specified by `struct mg_str`.
 */
int mg_vcmp(const struct mg_str *str2, const char *str1);

/*
 * Cross-platform version of `strncasecmp()` where first string is
 * specified by `struct mg_str`.
 */
int mg_vcasecmp(const struct mg_str *str2, const char *str1);

struct mg_str mg_strdup(const struct mg_str s);
int mg_strcmp(const struct mg_str str1, const struct mg_str str2);
int mg_strncmp(const struct mg_str str1, const struct mg_str str2, size_t n);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_COMMON_MG_STR_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/str_util.h"
#endif
/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_STR_UTIL_H_
#define CS_COMMON_STR_UTIL_H_

#include <stdarg.h>
#include <stdlib.h>

#ifndef CS_ENABLE_STRDUP
#define CS_ENABLE_STRDUP 0
#endif

#ifndef CS_ENABLE_TO64
#define CS_ENABLE_TO64 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

size_t c_strnlen(const char *s, size_t maxlen);
int c_snprintf(char *buf, size_t buf_size, const char *format, ...);
int c_vsnprintf(char *buf, size_t buf_size, const char *format, va_list ap);
/*
 * Find the first occurrence of find in s, where the search is limited to the
 * first slen characters of s.
 */
const char *c_strnstr(const char *s, const char *find, size_t slen);

/*
 * Stringify binary data. Output buffer size must be 2 * size_of_input + 1
 * because each byte of input takes 2 bytes in string representation
 * plus 1 byte for the terminating \0 character.
 */
void cs_to_hex(char *to, const unsigned char *p, size_t len);

/*
 * Convert stringified binary data back to binary.
 * Does the reverse of `cs_to_hex()`.
 */
void cs_from_hex(char *to, const char *p, size_t len);

#if CS_ENABLE_STRDUP
char *strdup(const char *src);
#endif

#if CS_ENABLE_TO64
#include <stdint.h>
/*
 * Simple string -> int64 conversion routine.
 */
int64_t cs_to64(const char *s);
#endif

/*
 * Cross-platform version of `strncasecmp()`.
 */
int mg_ncasecmp(const char *s1, const char *s2, size_t len);

/*
 * Cross-platform version of `strcasecmp()`.
 */
int mg_casecmp(const char *s1, const char *s2);

/*
 * Prints message to the buffer. If the buffer is large enough to hold the
 * message, it returns buffer. If buffer is to small, it allocates a large
 * enough buffer on heap and returns allocated buffer.
 * This is a supposed use case:
 *
 *    char buf[5], *p = buf;
 *    mg_avprintf(&p, sizeof(buf), "%s", "hi there");
 *    use_p_somehow(p);
 *    if (p != buf) {
 *      free(p);
 *    }
 *
 * The purpose of this is to avoid malloc-ing if generated strings are small.
 */
int mg_asprintf(char **buf, size_t size, const char *fmt, ...);

/* Same as mg_asprintf, but takes varargs list. */
int mg_avprintf(char **buf, size_t size, const char *fmt, va_list ap);

#ifdef __cplusplus
}
#endif

#endif /* CS_COMMON_STR_UTIL_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/utf.h"
#endif
/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_UTF_H_
#define CS_COMMON_UTF_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef unsigned char uchar;

typedef unsigned short Rune; /* 16 bits */

#define nelem(a) (sizeof(a) / sizeof(a)[0])

enum {
  UTFmax = 3,               /* maximum bytes per rune */
  Runesync = 0x80,          /* cannot represent part of a UTF sequence (<) */
  Runeself = 0x80,          /* rune and UTF sequences are the same (<) */
  Runeerror = 0xFFFD        /* decoding error in UTF */
  /* Runemax    = 0xFFFC */ /* maximum rune value */
};

/* Edit .+1,/^$/ | cfn $PLAN9/src/lib9/utf/?*.c | grep -v static |grep -v __ */
int chartorune(Rune *rune, const char *str);
int fullrune(const char *str, int n);
int isdigitrune(Rune c);
int isnewline(Rune c);
int iswordchar(Rune c);
int isalpharune(Rune c);
int islowerrune(Rune c);
int isspacerune(Rune c);
int isupperrune(Rune c);
int runetochar(char *str, Rune *rune);
Rune tolowerrune(Rune c);
Rune toupperrune(Rune c);
int utfnlen(const char *s, long m);
const char *utfnshift(const char *s, long m);

#if 0 /* Not implemented. */
int istitlerune(Rune c);
int runelen(Rune c);
int runenlen(Rune *r, int nrune);
Rune *runestrcat(Rune *s1, Rune *s2);
Rune *runestrchr(Rune *s, Rune c);
Rune *runestrcpy(Rune *s1, Rune *s2);
Rune *runestrdup(Rune *s);
Rune *runestrecpy(Rune *s1, Rune *es1, Rune *s2);
int runestrcmp(Rune *s1, Rune *s2);
long runestrlen(Rune *s);
Rune *runestrncat(Rune *s1, Rune *s2, long n);
int runestrncmp(Rune *s1, Rune *s2, long n);
Rune *runestrncpy(Rune *s1, Rune *s2, long n);
Rune *runestrrchr(Rune *s, Rune c);
Rune *runestrstr(Rune *s1, Rune *s2);
Rune totitlerune(Rune c);
char *utfecpy(char *to, char *e, char *from);
int utflen(char *s);
char *utfrrune(char *s, long c);
char *utfrune(char *s, long c);
char *utfutf(char *s1, char *s2);
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* CS_COMMON_UTF_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/parser_state.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_PARSER_STATE_H_
#define MJS_PARSER_STATE_H_

struct mjs_token {
  const char *begin;
};

struct mjs_pstate {
  const char *file_name;
  const char *source_code;
  const char *pc;      /* Current parsing position */
  const char *src_end; /* End of source code */
  int line_no;         /* Line number */
  int prev_line_no;    /* Line number of previous token */
};

struct mjs_parse_ctx {
  int state;
  struct mjs_token syntax_error;

  struct mjs_pstate pstate;
  int cur_tok;           /* Current token */
  const char *tok;       /* Parsed terminal token (ident, number, string) */
  unsigned long tok_len; /* Length of the parsed terminal token */
  double cur_tok_dbl;    /* When tokenizing, parser stores TOK_NUMBER here */
};

#endif /* MJS_PARSER_STATE_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/froth/vm.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_FROTH_VM_H_
#define MJS_FROTH_VM_H_

/* Amalgamated: #include "common/platform.h" */

#define FR_STACK_SIZE 256

#define FR_EXIT_RUN -1

typedef int16_t fr_cell_t;

typedef int8_t fr_opcode_t;
typedef fr_cell_t fr_word_ptr_t;

struct fr_vm;
typedef void (*fr_native_t)(struct fr_vm *vm);

struct fr_code {
  fr_opcode_t *opcodes;      /* all word bodies */
  size_t opcodes_len;        /* max 32768 */
  fr_word_ptr_t *table;      /* points to opcodes */
  size_t table_len;          /* max 127 */
  fr_native_t *native_words; /* native words */
  size_t native_words_len;

  const char **word_names; /* table_len number of entries, for tracing */
  const char **pos_names;  /* opcodes_len number of entries, for tracing */
};

struct fr_stack {
  fr_cell_t stack[FR_STACK_SIZE];
  size_t pos;
  size_t size;
};

struct fr_vm {
  struct fr_code *code;

  fr_word_ptr_t ip;
  struct fr_stack dstack; /* data stack */
  struct fr_stack rstack; /* return stack */
};

void fr_init_vm(struct fr_vm *vm, struct fr_code *code);
void fr_run(struct fr_vm *vm, fr_word_ptr_t word);

fr_word_ptr_t fr_lookup_word(struct fr_vm *vm, fr_opcode_t op);

void fr_push(struct fr_stack *stack, fr_cell_t value);
fr_cell_t fr_pop(struct fr_stack *stack);

#endif /* MJS_FROTH_VM_H_ */
#ifdef MG_MODULE_LINES
#line 1 "bazel-out/local-dbg-asan/genfiles/mjs/vm_bcode.h"
#endif
#ifndef MJS_GEN_OPCODES_H_
#define MJS_GEN_OPCODES_H_

/* Amalgamated: #include "mjs/froth/vm.h" */

extern struct fr_code MJS_code;

#define MJS_OP_quote ((fr_opcode_t) -1)
#define MJS_OP_exit ((fr_opcode_t) 0)
#define MJS_OP_drop ((fr_opcode_t) 1)
#define MJS_OP_dup ((fr_opcode_t) 2)
#define MJS_OP_swap ((fr_opcode_t) 3)
#define MJS_OP_PUSHR ((fr_opcode_t) 4)
#define MJS_OP_POPR ((fr_opcode_t) 5)
#define MJS_OP_print ((fr_opcode_t) 6)
#define MJS_OP_EQ_ ((fr_opcode_t) 7)
#define MJS_OP_invert ((fr_opcode_t) 8)
#define MJS_OP_ADD_ ((fr_opcode_t) 9)
#define MJS_OP_call ((fr_opcode_t) 10)
#define MJS_OP_if ((fr_opcode_t) 11)
#define MJS_OP_ifelse ((fr_opcode_t) 12)
#define MJS_OP_loop ((fr_opcode_t) 13)
#define MJS_OP_foo ((fr_opcode_t) 14)
#define MJS_OP_NEQ_ ((fr_opcode_t) 15)
#define MJS_OP_anon_0 ((fr_opcode_t) 16)
#define MJS_OP_anon_1 ((fr_opcode_t) 17)
#define MJS_OP_anon_2 ((fr_opcode_t) 18)
#define MJS_OP_demo ((fr_opcode_t) 19)

#endif /* MJS_GEN_OPCODES_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/core.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_CORE_H_
#define MJS_CORE_H_

/* Amalgamated: #include "mjs/license.h" */
/* Amalgamated: #include "mjs/froth/vm.h" */

enum mjs_err {
  MJS_OK,
  MJS_SYNTAX_ERROR,
  MJS_INTERNAL_ERROR,
};

typedef enum mjs_err mjs_err_t;

struct mjs {
  struct fr_vm vm;
  char *error_msg;
  mjs_err_t error_msg_err;
};

struct mjs *mjs_create();
void mjs_destroy(struct mjs *mjs);

mjs_err_t mjs_set_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt, ...);

/*
 * return a string representation of an error.
 * the error string might be overwritten by calls to `mjs_set_errorf`.
 */
const char *mjs_strerror(struct mjs *mjs, mjs_err_t err);

#endif /* MJS_CORE_H_ */
#ifdef MG_MODULE_LINES
#line 1 "bazel-out/local-dbg-asan/genfiles/mjs/mjs.lem.h"
#endif
#define TOK_END_OF_INPUT                     1
#define TOK_NUMBER                           2
#define TOK_STRING_LITERAL                   3
#define TOK_REGEX_LITERAL                    4
#define TOK_IDENTIFIER                       5
#define TOK_OPEN_CURLY                       6
#define TOK_CLOSE_CURLY                      7
#define TOK_OPEN_PAREN                       8
#define TOK_CLOSE_PAREN                      9
#define TOK_COMMA                           10
#define TOK_OPEN_BRACKET                    11
#define TOK_CLOSE_BRACKET                   12
#define TOK_DOT                             13
#define TOK_COLON                           14
#define TOK_SEMICOLON                       15
#define TOK_EQ                              16
#define TOK_EQ_EQ                           17
#define TOK_NE                              18
#define TOK_NE_NE                           19
#define TOK_ASSIGN                          20
#define TOK_REM_ASSIGN                      21
#define TOK_MUL_ASSIGN                      22
#define TOK_DIV_ASSIGN                      23
#define TOK_XOR_ASSIGN                      24
#define TOK_PLUS_ASSIGN                     25
#define TOK_MINUS_ASSIGN                    26
#define TOK_OR_ASSIGN                       27
#define TOK_AND_ASSIGN                      28
#define TOK_LSHIFT_ASSIGN                   29
#define TOK_RSHIFT_ASSIGN                   30
#define TOK_URSHIFT_ASSIGN                  31
#define TOK_AND                             32
#define TOK_LOGICAL_OR                      33
#define TOK_PLUS                            34
#define TOK_MINUS                           35
#define TOK_PLUS_PLUS                       36
#define TOK_MINUS_MINUS                     37
#define TOK_LOGICAL_AND                     38
#define TOK_OR                              39
#define TOK_QUESTION                        40
#define TOK_TILDA                           41
#define TOK_REM                             42
#define TOK_MUL                             43
#define TOK_DIV                             44
#define TOK_XOR                             45
#define TOK_LE                              46
#define TOK_LT                              47
#define TOK_GE                              48
#define TOK_GT                              49
#define TOK_LSHIFT                          50
#define TOK_RSHIFT                          51
#define TOK_URSHIFT                         52
#define TOK_NOT                             53
#define TOK_BREAK                           54
#define TOK_CASE                            55
#define TOK_CATCH                           56
#define TOK_CONTINUE                        57
#define TOK_DEBUGGER                        58
#define TOK_DEFAULT                         59
#define TOK_DELETE                          60
#define TOK_DO                              61
#define TOK_ELSE                            62
#define TOK_FALSE                           63
#define TOK_FINALLY                         64
#define TOK_FOR                             65
#define TOK_FUNCTION                        66
#define TOK_IF                              67
#define TOK_IN                              68
#define TOK_INSTANCEOF                      69
#define TOK_NEW                             70
#define TOK_NULL                            71
#define TOK_RETURN                          72
#define TOK_SWITCH                          73
#define TOK_THIS                            74
#define TOK_THROW                           75
#define TOK_TRUE                            76
#define TOK_TRY                             77
#define TOK_TYPEOF                          78
#define TOK_VAR                             79
#define TOK_VOID                            80
#define TOK_WHILE                           81
#define TOK_WITH                            82
#define TOK_LET                             83
#define TOK_UNDEFINED                       84
#define TOK_CLASS                           85
#define TOK_ENUM                            86
#define TOK_EXTENDS                         87
#define TOK_SUPER                           88
#define TOK_CONST                           89
#define TOK_EXPORT                          90
#define TOK_IMPORT                          91
#define TOK_IMPLEMENTS                      92
#define TOK_PRIVATE                         93
#define TOK_PUBLIC                          94
#define TOK_INTERFACE                       95
#define TOK_PACKAGE                         96
#define TOK_PROTECTED                       97
#define TOK_STATIC                          98
#define TOK_YIELD                           99
#define TOK_THEN                           100
#define TOK_NUM_TOKENS                     101
#ifdef MG_MODULE_LINES
#line 1 "mjs/tokenizer.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_TOKENIZER_H_
#define MJS_TOKENIZER_H_

typedef int mjs_tok_t;

int skip_to_next_tok(const char **ptr, const char *src_end);
mjs_tok_t get_tok(const char **s, const char *src_end, double *n,
                  mjs_tok_t prev_tok);
int is_reserved_word_token(mjs_tok_t tok);

#endif /* MJS_TOKENIZER_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/parser.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_PARSER_H_
#define MJS_PARSER_H_

#include <stdlib.h>

/* Amalgamated: #include "mjs/mjs.lem.h" */
/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/tokenizer.h" */
/* Amalgamated: #include "mjs/parser_state.h" */

mjs_err_t mjs_parsen(struct mjs *mjs, const char *src, size_t len,
                     struct mjs_parse_ctx *ctx);
mjs_err_t mjs_parse(struct mjs *mjs, const char *src,
                    struct mjs_parse_ctx *ctx);
mjs_err_t mjs_parse_file(struct mjs *mjs, const char *file,
                         struct mjs_parse_ctx *ctx);

/* generated by lemon */
void *mjsParserAlloc(void *(*mallocProc)(size_t));
void mjsParserFree(void *, void (*)(void *));
void mjsParser(
    void *yyp,                /* The parser */
    int yymajor,              /* The major token code number */
    struct mjs_token yyminor, /* The value for the token */
    struct mjs_parse_ctx *ctx /* Optional %extra_argument parameter */
    );

#endif /* MJS_PARSER_H_ */
#ifdef MG_MODULE_LINES
#line 1 "common/cs_strtod.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_CS_STRTOD_H_
#define CS_COMMON_CS_STRTOD_H_

double cs_strtod(const char *str, char **endptr);

#endif /* CS_COMMON_CS_STRTOD_H_ */
#ifndef MG_EXPORT_INTERNAL_HEADERS
#ifdef MG_MODULE_LINES
#line 1 "common/cs_dbg.c"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "common/cs_dbg.h" */

#include <stdarg.h>
#include <stdio.h>

/* Amalgamated: #include "common/cs_time.h" */

enum cs_log_level cs_log_level =
#if CS_ENABLE_DEBUG
    LL_VERBOSE_DEBUG;
#else
    LL_ERROR;
#endif

#if CS_ENABLE_STDIO

FILE *cs_log_file = NULL;

#if CS_LOG_ENABLE_TS_DIFF
double cs_log_ts;
#endif

void cs_log_print_prefix(const char *func) {
  if (cs_log_file == NULL) cs_log_file = stderr;
  fprintf(cs_log_file, "%-20s ", func);
#if CS_LOG_ENABLE_TS_DIFF
  {
    double now = cs_time();
    fprintf(cs_log_file, "%7u ", (unsigned int) ((now - cs_log_ts) * 1000000));
    cs_log_ts = now;
  }
#endif
}

void cs_log_printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(cs_log_file, fmt, ap);
  va_end(ap);
  fputc('\n', cs_log_file);
  fflush(cs_log_file);
}

void cs_log_set_file(FILE *file) {
  cs_log_file = file;
}

#endif /* CS_ENABLE_STDIO */

void cs_log_set_level(enum cs_log_level level) {
  cs_log_level = level;
#if CS_LOG_ENABLE_TS_DIFF && CS_ENABLE_STDIO
  cs_log_ts = cs_time();
#endif
}
#ifdef MG_MODULE_LINES
#line 1 "common/cs_file.c"
#endif
/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "common/cs_file.h" */

#include <stdio.h>
#include <stdlib.h>

#ifdef CS_MMAP
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#endif

#ifndef EXCLUDE_COMMON
char *cs_read_file(const char *path, size_t *size) {
  FILE *fp;
  char *data = NULL;
  if ((fp = fopen(path, "rb")) == NULL) {
  } else if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
  } else {
    *size = ftell(fp);
    data = (char *) malloc(*size + 1);
    if (data != NULL) {
      fseek(fp, 0, SEEK_SET); /* Some platforms might not have rewind(), Oo */
      if (fread(data, 1, *size, fp) != *size) {
        free(data);
        return NULL;
      }
      data[*size] = '\0';
    }
    fclose(fp);
  }
  return data;
}
#endif /* EXCLUDE_COMMON */

#ifdef CS_MMAP
char *cs_mmap_file(const char *path, size_t *size) {
  char *r;
  int fd = open(path, O_RDONLY);
  struct stat st;
  if (fd == -1) return NULL;
  fstat(fd, &st);
  *size = (size_t) st.st_size;
  r = (char *) mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (r == MAP_FAILED) return NULL;
  return r;
}
#endif
#ifdef MG_MODULE_LINES
#line 1 "common/cs_strtod.c"
#endif
#include <ctype.h>
#include <math.h>

#include <stdlib.h>

int cs_strncasecmp(const char *s1, const char *s2, size_t n) {
  if (n == 0) {
    return 0;
  }

  while (n-- != 0 && tolower((int) *s1) == tolower((int) *s2)) {
    if (n == 0 || *s1 == '\0' || *s2 == '\0') {
      break;
    }
    s1++;
    s2++;
  }

  return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}

/*
 * based on Source:
 * https://github.com/anakod/Sming/blob/master/Sming/system/stringconversion.cpp#L93
 */

double cs_strtod(const char *str, char **endptr) {
  double result = 0.0;
  char c;
  const char *str_start;
  struct {
    unsigned neg : 1;        /* result is negative */
    unsigned decimals : 1;   /* parsing decimal part */
    unsigned is_exp : 1;     /* parsing exponent like e+5 */
    unsigned is_exp_neg : 1; /* exponent is negative */
  } flags = {0, 0, 0, 0};

  while (isspace((int) *str)) {
    str++;
  }

  if (*str == 0) {
    /* only space in str? */
    if (endptr != 0) *endptr = (char *) str;
    return result;
  }

  /* Handle leading plus/minus signs */
  while (*str == '-' || *str == '+') {
    if (*str == '-') {
      flags.neg = !flags.neg;
    }
    str++;
  }

  if (cs_strncasecmp(str, "NaN", 3) == 0) {
    if (endptr != 0) *endptr = (char *) str + 3;
    return NAN;
  }

  if (cs_strncasecmp(str, "INF", 3) == 0) {
    str += 3;
    if (cs_strncasecmp(str, "INITY", 5) == 0) str += 5;
    if (endptr != 0) *endptr = (char *) str;
    return flags.neg ? -INFINITY : INFINITY;
  }

  str_start = str;

  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    /* base 16 */
    str += 2;
    while ((c = tolower((int) *str))) {
      int d;
      if (c >= '0' && c <= '9') {
        d = c - '0';
      } else if (c >= 'a' && c <= 'f') {
        d = 10 + (c - 'a');
      } else {
        break;
      }
      result = 16 * result + d;
      str++;
    }
  } else if (*str == '0' && (*(str + 1) == 'b' || *(str + 1) == 'B')) {
    /* base 2 */
    str += 2;
    while ((c = *str)) {
      int d = c - '0';
      if (c != '0' && c != '1') break;
      result = 2 * result + d;
      str++;
    }
  } else if (*str == '0' && *(str + 1) >= '0' && *(str + 1) <= '7') {
    /* base 8 */
    while ((c = *str)) {
      int d = c - '0';
      if (c < '0' || c > '7') {
        /* fallback to base 10 */
        str = str_start;
        break;
      }
      result = 8 * result + d;
      str++;
    }
  }

  if (str == str_start) {
    /* base 10 */

    /* exponent specified explicitly, like in 3e-5, exponent is -5 */
    int exp = 0;
    /* exponent calculated from dot, like in 1.23, exponent is -2 */
    int exp_dot = 0;

    result = 0;

    while ((c = *str)) {
      int d;

      if (c == '.') {
        if (!flags.decimals) {
          /* going to parse decimal part */
          flags.decimals = 1;
          str++;
          continue;
        } else {
          /* non-expected dot: assume number data is over */
          break;
        }
      } else if (c == 'e' || c == 'E') {
        /* going to parse exponent part */
        flags.is_exp = 1;
        str++;
        c = *str;

        /* check sign of the exponent */
        if (c == '-' || c == '+') {
          if (c == '-') {
            flags.is_exp_neg = 1;
          }
          str++;
        }

        continue;
      }

      d = c - '0';
      if (d < 0 || d > 9) {
        break;
      }

      if (!flags.is_exp) {
        /* apply current digit to the result */
        result = 10 * result + d;
        if (flags.decimals) {
          exp_dot--;
        }
      } else {
        /* apply current digit to the exponent */
        if (flags.is_exp_neg) {
          if (exp > -1022) {
            exp = 10 * exp - d;
          }
        } else {
          if (exp < 1023) {
            exp = 10 * exp + d;
          }
        }
      }

      str++;
    }

    exp += exp_dot;

    /*
     * TODO(dfrank): it probably makes sense not to adjust intermediate `double
     * result`, but build double number accordingly to IEEE 754 from taken
     * (integer) mantissa, exponent and sign. That would work faster, and we
     * can avoid any possible round errors.
     */

    /* if exponent is non-zero, apply it */
    if (exp != 0) {
      if (exp < 0) {
        while (exp++ != 0) {
          result /= 10;
        }
      } else {
        while (exp-- != 0) {
          result *= 10;
        }
      }
    }
  }

  if (flags.neg) {
    result = -result;
  }

  if (endptr != 0) {
    *endptr = (char *) str;
  }

  return result;
}
#ifdef MG_MODULE_LINES
#line 1 "common/cs_time.c"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "common/cs_time.h" */

#ifndef _WIN32
#include <stddef.h>
/*
 * There is no sys/time.h on ARMCC.
 */
#if !(defined(__ARMCC_VERSION) || defined(__ICCARM__)) && \
    !defined(__TI_COMPILER_VERSION__) &&                  \
    (!defined(CS_PLATFORM) || CS_PLATFORM != CS_P_NXP_LPC)
#include <sys/time.h>
#endif
#else
#include <windows.h>
#endif

double cs_time(void) {
  double now;
#ifndef _WIN32
  struct timeval tv;
  if (gettimeofday(&tv, NULL /* tz */) != 0) return 0;
  now = (double) tv.tv_sec + (((double) tv.tv_usec) / 1000000.0);
#else
  SYSTEMTIME sysnow;
  FILETIME ftime;
  GetLocalTime(&sysnow);
  SystemTimeToFileTime(&sysnow, &ftime);
  /*
   * 1. VC 6.0 doesn't support conversion uint64 -> double, so, using int64
   * This should not cause a problems in this (21th) century
   * 2. Windows FILETIME is a number of 100-nanosecond intervals since January
   * 1, 1601 while time_t is a number of _seconds_ since January 1, 1970 UTC,
   * thus, we need to convert to seconds and adjust amount (subtract 11644473600
   * seconds)
   */
  now = (double) (((int64_t) ftime.dwLowDateTime +
                   ((int64_t) ftime.dwHighDateTime << 32)) /
                  10000000.0) -
        11644473600;
#endif /* _WIN32 */
  return now;
}
#ifdef MG_MODULE_LINES
#line 1 "common/mbuf.c"
#endif
/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#ifndef EXCLUDE_COMMON

#include <assert.h>
#include <string.h>
/* Amalgamated: #include "common/mbuf.h" */

#ifndef MBUF_REALLOC
#define MBUF_REALLOC realloc
#endif

#ifndef MBUF_FREE
#define MBUF_FREE free
#endif

void mbuf_init(struct mbuf *mbuf, size_t initial_size) {
  mbuf->len = mbuf->size = 0;
  mbuf->buf = NULL;
  mbuf_resize(mbuf, initial_size);
}

void mbuf_free(struct mbuf *mbuf) {
  if (mbuf->buf != NULL) {
    MBUF_FREE(mbuf->buf);
    mbuf_init(mbuf, 0);
  }
}

void mbuf_resize(struct mbuf *a, size_t new_size) {
  if (new_size > a->size || (new_size < a->size && new_size >= a->len)) {
    char *buf = (char *) MBUF_REALLOC(a->buf, new_size);
    /*
     * In case realloc fails, there's not much we can do, except keep things as
     * they are. Note that NULL is a valid return value from realloc when
     * size == 0, but that is covered too.
     */
    if (buf == NULL && new_size != 0) return;
    a->buf = buf;
    a->size = new_size;
  }
}

void mbuf_trim(struct mbuf *mbuf) {
  mbuf_resize(mbuf, mbuf->len);
}

size_t mbuf_insert(struct mbuf *a, size_t off, const void *buf, size_t len) {
  char *p = NULL;

  assert(a != NULL);
  assert(a->len <= a->size);
  assert(off <= a->len);

  /* check overflow */
  if (~(size_t) 0 - (size_t) a->buf < len) return 0;

  if (a->len + len <= a->size) {
    memmove(a->buf + off + len, a->buf + off, a->len - off);
    if (buf != NULL) {
      memcpy(a->buf + off, buf, len);
    }
    a->len += len;
  } else {
    size_t new_size = (size_t)((a->len + len) * MBUF_SIZE_MULTIPLIER);
    if ((p = (char *) MBUF_REALLOC(a->buf, new_size)) != NULL) {
      a->buf = p;
      memmove(a->buf + off + len, a->buf + off, a->len - off);
      if (buf != NULL) memcpy(a->buf + off, buf, len);
      a->len += len;
      a->size = new_size;
    } else {
      len = 0;
    }
  }

  return len;
}

size_t mbuf_append(struct mbuf *a, const void *buf, size_t len) {
  return mbuf_insert(a, a->len, buf, len);
}

void mbuf_remove(struct mbuf *mb, size_t n) {
  if (n > 0 && n <= mb->len) {
    memmove(mb->buf, mb->buf + n, mb->len - n);
    mb->len -= n;
  }
}

#endif /* EXCLUDE_COMMON */
#ifdef MG_MODULE_LINES
#line 1 "common/mg_str.c"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "common/mg_str.h" */

#include <stdlib.h>
#include <string.h>

int mg_ncasecmp(const char *s1, const char *s2, size_t len);

struct mg_str mg_mk_str(const char *s) {
  struct mg_str ret = {s, 0};
  if (s != NULL) ret.len = strlen(s);
  return ret;
}

struct mg_str mg_mk_str_n(const char *s, size_t len) {
  struct mg_str ret = {s, len};
  return ret;
}

int mg_vcmp(const struct mg_str *str1, const char *str2) {
  size_t n2 = strlen(str2), n1 = str1->len;
  int r = memcmp(str1->p, str2, (n1 < n2) ? n1 : n2);
  if (r == 0) {
    return n1 - n2;
  }
  return r;
}

int mg_vcasecmp(const struct mg_str *str1, const char *str2) {
  size_t n2 = strlen(str2), n1 = str1->len;
  int r = mg_ncasecmp(str1->p, str2, (n1 < n2) ? n1 : n2);
  if (r == 0) {
    return n1 - n2;
  }
  return r;
}

struct mg_str mg_strdup(const struct mg_str s) {
  struct mg_str r = {NULL, 0};
  if (s.len > 0 && s.p != NULL) {
    r.p = (char *) malloc(s.len);
    if (r.p != NULL) {
      memcpy((char *) r.p, s.p, s.len);
      r.len = s.len;
    }
  }
  return r;
}

int mg_strcmp(const struct mg_str str1, const struct mg_str str2) {
  size_t i = 0;
  while (i < str1.len && i < str2.len) {
    if (str1.p[i] < str2.p[i]) return -1;
    if (str1.p[i] > str2.p[i]) return 1;
    i++;
  }
  if (i < str1.len) return 1;
  if (i < str2.len) return -1;
  return 0;
}

int mg_strncmp(const struct mg_str str1, const struct mg_str str2, size_t n) {
  struct mg_str s1 = str1;
  struct mg_str s2 = str2;

  if (s1.len > n) {
    s1.len = n;
  }
  if (s2.len > n) {
    s2.len = n;
  }
  return mg_strcmp(s1, s2);
}
#ifdef MG_MODULE_LINES
#line 1 "common/str_util.c"
#endif
/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

#ifndef EXCLUDE_COMMON

/* Amalgamated: #include "common/platform.h" */
/* Amalgamated: #include "common/str_util.h" */

#ifndef C_DISABLE_BUILTIN_SNPRINTF
#define C_DISABLE_BUILTIN_SNPRINTF 0
#endif

#ifndef MG_MALLOC
#define MG_MALLOC malloc
#endif

#ifndef MG_FREE
#define MG_FREE free
#endif

size_t c_strnlen(const char *s, size_t maxlen) {
  size_t l = 0;
  for (; l < maxlen && s[l] != '\0'; l++) {
  }
  return l;
}

#define C_SNPRINTF_APPEND_CHAR(ch)       \
  do {                                   \
    if (i < (int) buf_size) buf[i] = ch; \
    i++;                                 \
  } while (0)

#define C_SNPRINTF_FLAG_ZERO 1

#if C_DISABLE_BUILTIN_SNPRINTF
int c_vsnprintf(char *buf, size_t buf_size, const char *fmt, va_list ap) {
  return vsnprintf(buf, buf_size, fmt, ap);
}
#else
static int c_itoa(char *buf, size_t buf_size, int64_t num, int base, int flags,
                  int field_width) {
  char tmp[40];
  int i = 0, k = 0, neg = 0;

  if (num < 0) {
    neg++;
    num = -num;
  }

  /* Print into temporary buffer - in reverse order */
  do {
    int rem = num % base;
    if (rem < 10) {
      tmp[k++] = '0' + rem;
    } else {
      tmp[k++] = 'a' + (rem - 10);
    }
    num /= base;
  } while (num > 0);

  /* Zero padding */
  if (flags && C_SNPRINTF_FLAG_ZERO) {
    while (k < field_width && k < (int) sizeof(tmp) - 1) {
      tmp[k++] = '0';
    }
  }

  /* And sign */
  if (neg) {
    tmp[k++] = '-';
  }

  /* Now output */
  while (--k >= 0) {
    C_SNPRINTF_APPEND_CHAR(tmp[k]);
  }

  return i;
}

int c_vsnprintf(char *buf, size_t buf_size, const char *fmt, va_list ap) {
  int ch, i = 0, len_mod, flags, precision, field_width;

  while ((ch = *fmt++) != '\0') {
    if (ch != '%') {
      C_SNPRINTF_APPEND_CHAR(ch);
    } else {
      /*
       * Conversion specification:
       *   zero or more flags (one of: # 0 - <space> + ')
       *   an optional minimum  field  width (digits)
       *   an  optional precision (. followed by digits, or *)
       *   an optional length modifier (one of: hh h l ll L q j z t)
       *   conversion specifier (one of: d i o u x X e E f F g G a A c s p n)
       */
      flags = field_width = precision = len_mod = 0;

      /* Flags. only zero-pad flag is supported. */
      if (*fmt == '0') {
        flags |= C_SNPRINTF_FLAG_ZERO;
      }

      /* Field width */
      while (*fmt >= '0' && *fmt <= '9') {
        field_width *= 10;
        field_width += *fmt++ - '0';
      }
      /* Dynamic field width */
      if (*fmt == '*') {
        field_width = va_arg(ap, int);
        fmt++;
      }

      /* Precision */
      if (*fmt == '.') {
        fmt++;
        if (*fmt == '*') {
          precision = va_arg(ap, int);
          fmt++;
        } else {
          while (*fmt >= '0' && *fmt <= '9') {
            precision *= 10;
            precision += *fmt++ - '0';
          }
        }
      }

      /* Length modifier */
      switch (*fmt) {
        case 'h':
        case 'l':
        case 'L':
        case 'I':
        case 'q':
        case 'j':
        case 'z':
        case 't':
          len_mod = *fmt++;
          if (*fmt == 'h') {
            len_mod = 'H';
            fmt++;
          }
          if (*fmt == 'l') {
            len_mod = 'q';
            fmt++;
          }
          break;
      }

      ch = *fmt++;
      if (ch == 's') {
        const char *s = va_arg(ap, const char *); /* Always fetch parameter */
        int j;
        int pad = field_width - (precision >= 0 ? c_strnlen(s, precision) : 0);
        for (j = 0; j < pad; j++) {
          C_SNPRINTF_APPEND_CHAR(' ');
        }

        /* `s` may be NULL in case of %.*s */
        if (s != NULL) {
          /* Ignore negative and 0 precisions */
          for (j = 0; (precision <= 0 || j < precision) && s[j] != '\0'; j++) {
            C_SNPRINTF_APPEND_CHAR(s[j]);
          }
        }
      } else if (ch == 'c') {
        ch = va_arg(ap, int); /* Always fetch parameter */
        C_SNPRINTF_APPEND_CHAR(ch);
      } else if (ch == 'd' && len_mod == 0) {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, int), 10, flags,
                    field_width);
      } else if (ch == 'd' && len_mod == 'l') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, long), 10, flags,
                    field_width);
#ifdef SSIZE_MAX
      } else if (ch == 'd' && len_mod == 'z') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, ssize_t), 10, flags,
                    field_width);
#endif
      } else if (ch == 'd' && len_mod == 'q') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, int64_t), 10, flags,
                    field_width);
      } else if ((ch == 'x' || ch == 'u') && len_mod == 0) {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, unsigned),
                    ch == 'x' ? 16 : 10, flags, field_width);
      } else if ((ch == 'x' || ch == 'u') && len_mod == 'l') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, unsigned long),
                    ch == 'x' ? 16 : 10, flags, field_width);
      } else if ((ch == 'x' || ch == 'u') && len_mod == 'z') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, size_t),
                    ch == 'x' ? 16 : 10, flags, field_width);
      } else if (ch == 'p') {
        unsigned long num = (unsigned long) (uintptr_t) va_arg(ap, void *);
        C_SNPRINTF_APPEND_CHAR('0');
        C_SNPRINTF_APPEND_CHAR('x');
        i += c_itoa(buf + i, buf_size - i, num, 16, flags, 0);
      } else {
#ifndef NO_LIBC
        /*
         * TODO(lsm): abort is not nice in a library, remove it
         * Also, ESP8266 SDK doesn't have it
         */
        abort();
#endif
      }
    }
  }

  /* Zero-terminate the result */
  if (buf_size > 0) {
    buf[i < (int) buf_size ? i : (int) buf_size - 1] = '\0';
  }

  return i;
}
#endif

int c_snprintf(char *buf, size_t buf_size, const char *fmt, ...) {
  int result;
  va_list ap;
  va_start(ap, fmt);
  result = c_vsnprintf(buf, buf_size, fmt, ap);
  va_end(ap);
  return result;
}

#ifdef _WIN32
int to_wchar(const char *path, wchar_t *wbuf, size_t wbuf_len) {
  int ret;
  char buf[MAX_PATH * 2], buf2[MAX_PATH * 2], *p;

  strncpy(buf, path, sizeof(buf));
  buf[sizeof(buf) - 1] = '\0';

  /* Trim trailing slashes. Leave backslash for paths like "X:\" */
  p = buf + strlen(buf) - 1;
  while (p > buf && p[-1] != ':' && (p[0] == '\\' || p[0] == '/')) *p-- = '\0';

  memset(wbuf, 0, wbuf_len * sizeof(wchar_t));
  ret = MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, (int) wbuf_len);

  /*
   * Convert back to Unicode. If doubly-converted string does not match the
   * original, something is fishy, reject.
   */
  WideCharToMultiByte(CP_UTF8, 0, wbuf, (int) wbuf_len, buf2, sizeof(buf2),
                      NULL, NULL);
  if (strcmp(buf, buf2) != 0) {
    wbuf[0] = L'\0';
    ret = 0;
  }

  return ret;
}
#endif /* _WIN32 */

/* The simplest O(mn) algorithm. Better implementation are GPLed */
const char *c_strnstr(const char *s, const char *find, size_t slen) {
  size_t find_length = strlen(find);
  size_t i;

  for (i = 0; i < slen; i++) {
    if (i + find_length > slen) {
      return NULL;
    }

    if (strncmp(&s[i], find, find_length) == 0) {
      return &s[i];
    }
  }

  return NULL;
}

#if CS_ENABLE_STRDUP
char *strdup(const char *src) {
  size_t len = strlen(src) + 1;
  char *ret = malloc(len);
  if (ret != NULL) {
    strcpy(ret, src);
  }
  return ret;
}
#endif

void cs_to_hex(char *to, const unsigned char *p, size_t len) {
  static const char *hex = "0123456789abcdef";

  for (; len--; p++) {
    *to++ = hex[p[0] >> 4];
    *to++ = hex[p[0] & 0x0f];
  }
  *to = '\0';
}

static int fourbit(int ch) {
  if (ch >= '0' && ch <= '9') {
    return ch - '0';
  } else if (ch >= 'a' && ch <= 'f') {
    return ch - 'a' + 10;
  } else if (ch >= 'A' && ch <= 'F') {
    return ch - 'A' + 10;
  }
  return 0;
}

void cs_from_hex(char *to, const char *p, size_t len) {
  size_t i;

  for (i = 0; i < len; i += 2) {
    *to++ = (fourbit(p[i]) << 4) + fourbit(p[i + 1]);
  }
  *to = '\0';
}

#if CS_ENABLE_TO64
int64_t cs_to64(const char *s) {
  int64_t result = 0;
  int64_t neg = 1;
  while (*s && isspace((unsigned char) *s)) s++;
  if (*s == '-') {
    neg = -1;
    s++;
  }
  while (isdigit((unsigned char) *s)) {
    result *= 10;
    result += (*s - '0');
    s++;
  }
  return result * neg;
}
#endif

static int str_util_lowercase(const char *s) {
  return tolower(*(const unsigned char *) s);
}

int mg_ncasecmp(const char *s1, const char *s2, size_t len) {
  int diff = 0;

  if (len > 0) do {
      diff = str_util_lowercase(s1++) - str_util_lowercase(s2++);
    } while (diff == 0 && s1[-1] != '\0' && --len > 0);

  return diff;
}

int mg_casecmp(const char *s1, const char *s2) {
  return mg_ncasecmp(s1, s2, (size_t) ~0);
}

int mg_asprintf(char **buf, size_t size, const char *fmt, ...) {
  int ret;
  va_list ap;
  va_start(ap, fmt);
  ret = mg_avprintf(buf, size, fmt, ap);
  va_end(ap);
  return ret;
}

int mg_avprintf(char **buf, size_t size, const char *fmt, va_list ap) {
  va_list ap_copy;
  int len;

  va_copy(ap_copy, ap);
  len = vsnprintf(*buf, size, fmt, ap_copy);
  va_end(ap_copy);

  if (len < 0) {
    /* eCos and Windows are not standard-compliant and return -1 when
     * the buffer is too small. Keep allocating larger buffers until we
     * succeed or out of memory. */
    *buf = NULL; /* LCOV_EXCL_START */
    while (len < 0) {
      MG_FREE(*buf);
      size *= 2;
      if ((*buf = (char *) MG_MALLOC(size)) == NULL) break;
      va_copy(ap_copy, ap);
      len = vsnprintf(*buf, size, fmt, ap_copy);
      va_end(ap_copy);
    }
    /* LCOV_EXCL_STOP */
  } else if (len >= (int) size) {
    /* Standard-compliant code path. Allocate a buffer that is large enough. */
    if ((*buf = (char *) MG_MALLOC(len + 1)) == NULL) {
      len = -1; /* LCOV_EXCL_LINE */
    } else {    /* LCOV_EXCL_LINE */
      va_copy(ap_copy, ap);
      len = vsnprintf(*buf, len + 1, fmt, ap_copy);
      va_end(ap_copy);
    }
  }

  return len;
}

#endif /* EXCLUDE_COMMON */
#ifdef MG_MODULE_LINES
#line 1 "common/utf.c"
#endif
/*
 * The authors of this software are Rob Pike and Ken Thompson.
 *              Copyright (c) 2002 by Lucent Technologies.
 * Permission to use, copy, modify, and distribute this software for any
 * purpose without fee is hereby granted, provided that this entire notice
 * is included in all copies of any software which is or includes a copy
 * or modification of this software and in all copies of the supporting
 * documentation for such software.
 * THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY.  IN PARTICULAR, NEITHER THE AUTHORS NOR LUCENT TECHNOLOGIES MAKE
 * ANY REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
 * OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
 */

#ifndef EXCLUDE_COMMON

/* clang-format off */

#include <stdarg.h>
#include <string.h>
/* Amalgamated: #include "common/platform.h" */
/* Amalgamated: #include "common/utf.h" */

#ifndef CS_ENABLE_UTF8
#define CS_ENABLE_UTF8 0
#endif

#if CS_ENABLE_UTF8
enum {
  Bit1 = 7,
  Bitx = 6,
  Bit2 = 5,
  Bit3 = 4,
  Bit4 = 3,
  Bit5 = 2,

  T1 = ((1 << (Bit1 + 1)) - 1) ^ 0xFF, /* 0000 0000 */
  Tx = ((1 << (Bitx + 1)) - 1) ^ 0xFF, /* 1000 0000 */
  T2 = ((1 << (Bit2 + 1)) - 1) ^ 0xFF, /* 1100 0000 */
  T3 = ((1 << (Bit3 + 1)) - 1) ^ 0xFF, /* 1110 0000 */
  T4 = ((1 << (Bit4 + 1)) - 1) ^ 0xFF, /* 1111 0000 */
  T5 = ((1 << (Bit5 + 1)) - 1) ^ 0xFF, /* 1111 1000 */

  Rune1 = (1 << (Bit1 + 0 * Bitx)) - 1, /* 0000 0000 0000 0000 0111 1111 */
  Rune2 = (1 << (Bit2 + 1 * Bitx)) - 1, /* 0000 0000 0000 0111 1111 1111 */
  Rune3 = (1 << (Bit3 + 2 * Bitx)) - 1, /* 0000 0000 1111 1111 1111 1111 */
  Rune4 = (1 << (Bit4 + 3 * Bitx)) - 1, /* 0011 1111 1111 1111 1111 1111 */

  Maskx = (1 << Bitx) - 1, /* 0011 1111 */
  Testx = Maskx ^ 0xFF,    /* 1100 0000 */

  Bad = Runeerror
};

int chartorune(Rune *rune, const char *str) {
  int c, c1, c2 /* , c3 */;
  unsigned short l;

  /*
   * one character sequence
   *	00000-0007F => T1
   */
  c = *(uchar *) str;
  if (c < Tx) {
    *rune = c;
    return 1;
  }

  /*
   * two character sequence
   *	0080-07FF => T2 Tx
   */
  c1 = *(uchar *) (str + 1) ^ Tx;
  if (c1 & Testx) goto bad;
  if (c < T3) {
    if (c < T2) goto bad;
    l = ((c << Bitx) | c1) & Rune2;
    if (l <= Rune1) goto bad;
    *rune = l;
    return 2;
  }

  /*
   * three character sequence
   *	0800-FFFF => T3 Tx Tx
   */
  c2 = *(uchar *) (str + 2) ^ Tx;
  if (c2 & Testx) goto bad;
  if (c < T4) {
    l = ((((c << Bitx) | c1) << Bitx) | c2) & Rune3;
    if (l <= Rune2) goto bad;
    *rune = l;
    return 3;
  }

/*
 * four character sequence
 *	10000-10FFFF => T4 Tx Tx Tx
 */
/* if(UTFmax >= 4) {
        c3 = *(uchar*)(str+3) ^ Tx;
        if(c3 & Testx)
                goto bad;
        if(c < T5) {
                l = ((((((c << Bitx) | c1) << Bitx) | c2) << Bitx) | c3) &
Rune4;
                if(l <= Rune3)
                        goto bad;
                if(l > Runemax)
                        goto bad;
                *rune = l;
                return 4;
        }
} */

/*
 * bad decoding
 */
bad:
  *rune = Bad;
  return 1;
}

int runetochar(char *str, Rune *rune) {
  unsigned short c;

  /*
   * one character sequence
   *	00000-0007F => 00-7F
   */
  c = *rune;
  if (c <= Rune1) {
    str[0] = c;
    return 1;
  }

  /*
   * two character sequence
   *	00080-007FF => T2 Tx
   */
  if (c <= Rune2) {
    str[0] = T2 | (c >> 1 * Bitx);
    str[1] = Tx | (c & Maskx);
    return 2;
  }

  /*
   * three character sequence
   *	00800-0FFFF => T3 Tx Tx
   */
  /* if(c > Runemax)
          c = Runeerror; */
  /* if(c <= Rune3) { */
  str[0] = T3 | (c >> 2 * Bitx);
  str[1] = Tx | ((c >> 1 * Bitx) & Maskx);
  str[2] = Tx | (c & Maskx);
  return 3;
  /* } */

  /*
   * four character sequence
   *	010000-1FFFFF => T4 Tx Tx Tx
   */
  /* str[0] = T4 |  (c >> 3*Bitx);
  str[1] = Tx | ((c >> 2*Bitx) & Maskx);
  str[2] = Tx | ((c >> 1*Bitx) & Maskx);
  str[3] = Tx |  (c & Maskx);
  return 4; */
}

int fullrune(const char *str, int n) {
  int c;

  if (n <= 0) return 0;
  c = *(uchar *) str;
  if (c < Tx) return 1;
  if (c < T3) return n >= 2;
  if (UTFmax == 3 || c < T4) return n >= 3;
  return n >= 4;
}

int utfnlen(const char *s, long m) {
  int c;
  long n;
  Rune rune;
  const char *es;

  es = s + m;
  for (n = 0; s < es; n++) {
    c = *(uchar *) s;
    if (c < Runeself) {
      s++;
      continue;
    }
    if (!fullrune(s, es - s)) break;
    s += chartorune(&rune, s);
  }
  return n;
}

const char *utfnshift(const char *s, long m) {
  int c;
  long n;
  Rune rune;

  for (n = 0; n < m; n++) {
    c = *(uchar *) s;
    if (c < Runeself) {
      s++;
      continue;
    }
    s += chartorune(&rune, s);
  }
  return s;
}

/*
 * The authors of this software are Rob Pike and Ken Thompson.
 *              Copyright (c) 2002 by Lucent Technologies.
 * Permission to use, copy, modify, and distribute this software for any
 * purpose without fee is hereby granted, provided that this entire notice
 * is included in all copies of any software which is or includes a copy
 * or modification of this software and in all copies of the supporting
 * documentation for such software.
 * THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY.  IN PARTICULAR, NEITHER THE AUTHORS NOR LUCENT TECHNOLOGIES MAKE
 * ANY REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
 * OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
 */
#include <stdarg.h>
#include <string.h>
/* Amalgamated: #include "common/utf.h" */

/*
 * alpha ranges -
 *	only covers ranges not in lower||upper
 */
static Rune __alpha2[] = {
    0x00d8, 0x00f6, /* Ø - ö */
    0x00f8, 0x01f5, /* ø - ǵ */
    0x0250, 0x02a8, /* ɐ - ʨ */
    0x038e, 0x03a1, /* Ύ - Ρ */
    0x03a3, 0x03ce, /* Σ - ώ */
    0x03d0, 0x03d6, /* ϐ - ϖ */
    0x03e2, 0x03f3, /* Ϣ - ϳ */
    0x0490, 0x04c4, /* Ґ - ӄ */
    0x0561, 0x0587, /* ա - և */
    0x05d0, 0x05ea, /* א - ת */
    0x05f0, 0x05f2, /* װ - ײ */
    0x0621, 0x063a, /* ء - غ */
    0x0640, 0x064a, /* ـ - ي */
    0x0671, 0x06b7, /* ٱ - ڷ */
    0x06ba, 0x06be, /* ں - ھ */
    0x06c0, 0x06ce, /* ۀ - ێ */
    0x06d0, 0x06d3, /* ې - ۓ */
    0x0905, 0x0939, /* अ - ह */
    0x0958, 0x0961, /* क़ - ॡ */
    0x0985, 0x098c, /* অ - ঌ */
    0x098f, 0x0990, /* এ - ঐ */
    0x0993, 0x09a8, /* ও - ন */
    0x09aa, 0x09b0, /* প - র */
    0x09b6, 0x09b9, /* শ - হ */
    0x09dc, 0x09dd, /* ড় - ঢ় */
    0x09df, 0x09e1, /* য় - ৡ */
    0x09f0, 0x09f1, /* ৰ - ৱ */
    0x0a05, 0x0a0a, /* ਅ - ਊ */
    0x0a0f, 0x0a10, /* ਏ - ਐ */
    0x0a13, 0x0a28, /* ਓ - ਨ */
    0x0a2a, 0x0a30, /* ਪ - ਰ */
    0x0a32, 0x0a33, /* ਲ - ਲ਼ */
    0x0a35, 0x0a36, /* ਵ - ਸ਼ */
    0x0a38, 0x0a39, /* ਸ - ਹ */
    0x0a59, 0x0a5c, /* ਖ਼ - ੜ */
    0x0a85, 0x0a8b, /* અ - ઋ */
    0x0a8f, 0x0a91, /* એ - ઑ */
    0x0a93, 0x0aa8, /* ઓ - ન */
    0x0aaa, 0x0ab0, /* પ - ર */
    0x0ab2, 0x0ab3, /* લ - ળ */
    0x0ab5, 0x0ab9, /* વ - હ */
    0x0b05, 0x0b0c, /* ଅ - ଌ */
    0x0b0f, 0x0b10, /* ଏ - ଐ */
    0x0b13, 0x0b28, /* ଓ - ନ */
    0x0b2a, 0x0b30, /* ପ - ର */
    0x0b32, 0x0b33, /* ଲ - ଳ */
    0x0b36, 0x0b39, /* ଶ - ହ */
    0x0b5c, 0x0b5d, /* ଡ଼ - ଢ଼ */
    0x0b5f, 0x0b61, /* ୟ - ୡ */
    0x0b85, 0x0b8a, /* அ - ஊ */
    0x0b8e, 0x0b90, /* எ - ஐ */
    0x0b92, 0x0b95, /* ஒ - க */
    0x0b99, 0x0b9a, /* ங - ச */
    0x0b9e, 0x0b9f, /* ஞ - ட */
    0x0ba3, 0x0ba4, /* ண - த */
    0x0ba8, 0x0baa, /* ந - ப */
    0x0bae, 0x0bb5, /* ம - வ */
    0x0bb7, 0x0bb9, /* ஷ - ஹ */
    0x0c05, 0x0c0c, /* అ - ఌ */
    0x0c0e, 0x0c10, /* ఎ - ఐ */
    0x0c12, 0x0c28, /* ఒ - న */
    0x0c2a, 0x0c33, /* ప - ళ */
    0x0c35, 0x0c39, /* వ - హ */
    0x0c60, 0x0c61, /* ౠ - ౡ */
    0x0c85, 0x0c8c, /* ಅ - ಌ */
    0x0c8e, 0x0c90, /* ಎ - ಐ */
    0x0c92, 0x0ca8, /* ಒ - ನ */
    0x0caa, 0x0cb3, /* ಪ - ಳ */
    0x0cb5, 0x0cb9, /* ವ - ಹ */
    0x0ce0, 0x0ce1, /* ೠ - ೡ */
    0x0d05, 0x0d0c, /* അ - ഌ */
    0x0d0e, 0x0d10, /* എ - ഐ */
    0x0d12, 0x0d28, /* ഒ - ന */
    0x0d2a, 0x0d39, /* പ - ഹ */
    0x0d60, 0x0d61, /* ൠ - ൡ */
    0x0e01, 0x0e30, /* ก - ะ */
    0x0e32, 0x0e33, /* า - ำ */
    0x0e40, 0x0e46, /* เ - ๆ */
    0x0e5a, 0x0e5b, /* ๚ - ๛ */
    0x0e81, 0x0e82, /* ກ - ຂ */
    0x0e87, 0x0e88, /* ງ - ຈ */
    0x0e94, 0x0e97, /* ດ - ທ */
    0x0e99, 0x0e9f, /* ນ - ຟ */
    0x0ea1, 0x0ea3, /* ມ - ຣ */
    0x0eaa, 0x0eab, /* ສ - ຫ */
    0x0ead, 0x0eae, /* ອ - ຮ */
    0x0eb2, 0x0eb3, /* າ - ຳ */
    0x0ec0, 0x0ec4, /* ເ - ໄ */
    0x0edc, 0x0edd, /* ໜ - ໝ */
    0x0f18, 0x0f19, /* ༘ - ༙ */
    0x0f40, 0x0f47, /* ཀ - ཇ */
    0x0f49, 0x0f69, /* ཉ - ཀྵ */
    0x10d0, 0x10f6, /* ა - ჶ */
    0x1100, 0x1159, /* ᄀ - ᅙ */
    0x115f, 0x11a2, /* ᅟ - ᆢ */
    0x11a8, 0x11f9, /* ᆨ - ᇹ */
    0x1e00, 0x1e9b, /* Ḁ - ẛ */
    0x1f50, 0x1f57, /* ὐ - ὗ */
    0x1f80, 0x1fb4, /* ᾀ - ᾴ */
    0x1fb6, 0x1fbc, /* ᾶ - ᾼ */
    0x1fc2, 0x1fc4, /* ῂ - ῄ */
    0x1fc6, 0x1fcc, /* ῆ - ῌ */
    0x1fd0, 0x1fd3, /* ῐ - ΐ */
    0x1fd6, 0x1fdb, /* ῖ - Ί */
    0x1fe0, 0x1fec, /* ῠ - Ῥ */
    0x1ff2, 0x1ff4, /* ῲ - ῴ */
    0x1ff6, 0x1ffc, /* ῶ - ῼ */
    0x210a, 0x2113, /* ℊ - ℓ */
    0x2115, 0x211d, /* ℕ - ℝ */
    0x2120, 0x2122, /* ℠ - ™ */
    0x212a, 0x2131, /* K - ℱ */
    0x2133, 0x2138, /* ℳ - ℸ */
    0x3041, 0x3094, /* ぁ - ゔ */
    0x30a1, 0x30fa, /* ァ - ヺ */
    0x3105, 0x312c, /* ㄅ - ㄬ */
    0x3131, 0x318e, /* ㄱ - ㆎ */
    0x3192, 0x319f, /* ㆒ - ㆟ */
    0x3260, 0x327b, /* ㉠ - ㉻ */
    0x328a, 0x32b0, /* ㊊ - ㊰ */
    0x32d0, 0x32fe, /* ㋐ - ㋾ */
    0x3300, 0x3357, /* ㌀ - ㍗ */
    0x3371, 0x3376, /* ㍱ - ㍶ */
    0x337b, 0x3394, /* ㍻ - ㎔ */
    0x3399, 0x339e, /* ㎙ - ㎞ */
    0x33a9, 0x33ad, /* ㎩ - ㎭ */
    0x33b0, 0x33c1, /* ㎰ - ㏁ */
    0x33c3, 0x33c5, /* ㏃ - ㏅ */
    0x33c7, 0x33d7, /* ㏇ - ㏗ */
    0x33d9, 0x33dd, /* ㏙ - ㏝ */
    0x4e00, 0x9fff, /* 一 - 鿿 */
    0xac00, 0xd7a3, /* 가 - 힣 */
    0xf900, 0xfb06, /* 豈 - ﬆ */
    0xfb13, 0xfb17, /* ﬓ - ﬗ */
    0xfb1f, 0xfb28, /* ײַ - ﬨ */
    0xfb2a, 0xfb36, /* שׁ - זּ */
    0xfb38, 0xfb3c, /* טּ - לּ */
    0xfb40, 0xfb41, /* נּ - סּ */
    0xfb43, 0xfb44, /* ףּ - פּ */
    0xfb46, 0xfbb1, /* צּ - ﮱ */
    0xfbd3, 0xfd3d, /* ﯓ - ﴽ */
    0xfd50, 0xfd8f, /* ﵐ - ﶏ */
    0xfd92, 0xfdc7, /* ﶒ - ﷇ */
    0xfdf0, 0xfdf9, /* ﷰ - ﷹ */
    0xfe70, 0xfe72, /* ﹰ - ﹲ */
    0xfe76, 0xfefc, /* ﹶ - ﻼ */
    0xff66, 0xff6f, /* ｦ - ｯ */
    0xff71, 0xff9d, /* ｱ - ﾝ */
    0xffa0, 0xffbe, /* ﾠ - ﾾ */
    0xffc2, 0xffc7, /* ￂ - ￇ */
    0xffca, 0xffcf, /* ￊ - ￏ */
    0xffd2, 0xffd7, /* ￒ - ￗ */
    0xffda, 0xffdc, /* ￚ - ￜ */
};

/*
 * alpha singlets -
 *	only covers ranges not in lower||upper
 */
static Rune __alpha1[] = {
    0x00aa, /* ª */
    0x00b5, /* µ */
    0x00ba, /* º */
    0x03da, /* Ϛ */
    0x03dc, /* Ϝ */
    0x03de, /* Ϟ */
    0x03e0, /* Ϡ */
    0x06d5, /* ە */
    0x09b2, /* ল */
    0x0a5e, /* ਫ਼ */
    0x0a8d, /* ઍ */
    0x0ae0, /* ૠ */
    0x0b9c, /* ஜ */
    0x0cde, /* ೞ */
    0x0e4f, /* ๏ */
    0x0e84, /* ຄ */
    0x0e8a, /* ຊ */
    0x0e8d, /* ຍ */
    0x0ea5, /* ລ */
    0x0ea7, /* ວ */
    0x0eb0, /* ະ */
    0x0ebd, /* ຽ */
    0x1fbe, /* ι */
    0x207f, /* ⁿ */
    0x20a8, /* ₨ */
    0x2102, /* ℂ */
    0x2107, /* ℇ */
    0x2124, /* ℤ */
    0x2126, /* Ω */
    0x2128, /* ℨ */
    0xfb3e, /* מּ */
    0xfe74, /* ﹴ */
};

/*
 * space ranges
 */
static Rune __space2[] = {
    0x0009, 0x000a, /* tab and newline */
    0x0020, 0x0020, /* space */
    0x00a0, 0x00a0, /*   */
    0x2000, 0x200b, /*   - ​ */
    0x2028, 0x2029, /*   -   */
    0x3000, 0x3000, /* 　 */
    0xfeff, 0xfeff, /* ﻿ */
};

/*
 * lower case ranges
 *	3rd col is conversion excess 500
 */
static Rune __toupper2[] = {
    0x0061, 0x007a, 468, /* a-z A-Z */
    0x00e0, 0x00f6, 468, /* à-ö À-Ö */
    0x00f8, 0x00fe, 468, /* ø-þ Ø-Þ */
    0x0256, 0x0257, 295, /* ɖ-ɗ Ɖ-Ɗ */
    0x0258, 0x0259, 298, /* ɘ-ə Ǝ-Ə */
    0x028a, 0x028b, 283, /* ʊ-ʋ Ʊ-Ʋ */
    0x03ad, 0x03af, 463, /* έ-ί Έ-Ί */
    0x03b1, 0x03c1, 468, /* α-ρ Α-Ρ */
    0x03c3, 0x03cb, 468, /* σ-ϋ Σ-Ϋ */
    0x03cd, 0x03ce, 437, /* ύ-ώ Ύ-Ώ */
    0x0430, 0x044f, 468, /* а-я А-Я */
    0x0451, 0x045c, 420, /* ё-ќ Ё-Ќ */
    0x045e, 0x045f, 420, /* ў-џ Ў-Џ */
    0x0561, 0x0586, 452, /* ա-ֆ Ա-Ֆ */
    0x1f00, 0x1f07, 508, /* ἀ-ἇ Ἀ-Ἇ */
    0x1f10, 0x1f15, 508, /* ἐ-ἕ Ἐ-Ἕ */
    0x1f20, 0x1f27, 508, /* ἠ-ἧ Ἠ-Ἧ */
    0x1f30, 0x1f37, 508, /* ἰ-ἷ Ἰ-Ἷ */
    0x1f40, 0x1f45, 508, /* ὀ-ὅ Ὀ-Ὅ */
    0x1f60, 0x1f67, 508, /* ὠ-ὧ Ὠ-Ὧ */
    0x1f70, 0x1f71, 574, /* ὰ-ά Ὰ-Ά */
    0x1f72, 0x1f75, 586, /* ὲ-ή Ὲ-Ή */
    0x1f76, 0x1f77, 600, /* ὶ-ί Ὶ-Ί */
    0x1f78, 0x1f79, 628, /* ὸ-ό Ὸ-Ό */
    0x1f7a, 0x1f7b, 612, /* ὺ-ύ Ὺ-Ύ */
    0x1f7c, 0x1f7d, 626, /* ὼ-ώ Ὼ-Ώ */
    0x1f80, 0x1f87, 508, /* ᾀ-ᾇ ᾈ-ᾏ */
    0x1f90, 0x1f97, 508, /* ᾐ-ᾗ ᾘ-ᾟ */
    0x1fa0, 0x1fa7, 508, /* ᾠ-ᾧ ᾨ-ᾯ */
    0x1fb0, 0x1fb1, 508, /* ᾰ-ᾱ Ᾰ-Ᾱ */
    0x1fd0, 0x1fd1, 508, /* ῐ-ῑ Ῐ-Ῑ */
    0x1fe0, 0x1fe1, 508, /* ῠ-ῡ Ῠ-Ῡ */
    0x2170, 0x217f, 484, /* ⅰ-ⅿ Ⅰ-Ⅿ */
    0x24d0, 0x24e9, 474, /* ⓐ-ⓩ Ⓐ-Ⓩ */
    0xff41, 0xff5a, 468, /* ａ-ｚ Ａ-Ｚ */
};

/*
 * lower case singlets
 *	2nd col is conversion excess 500
 */
static Rune __toupper1[] = {
    0x00ff, 621, /* ÿ Ÿ */
    0x0101, 499, /* ā Ā */
    0x0103, 499, /* ă Ă */
    0x0105, 499, /* ą Ą */
    0x0107, 499, /* ć Ć */
    0x0109, 499, /* ĉ Ĉ */
    0x010b, 499, /* ċ Ċ */
    0x010d, 499, /* č Č */
    0x010f, 499, /* ď Ď */
    0x0111, 499, /* đ Đ */
    0x0113, 499, /* ē Ē */
    0x0115, 499, /* ĕ Ĕ */
    0x0117, 499, /* ė Ė */
    0x0119, 499, /* ę Ę */
    0x011b, 499, /* ě Ě */
    0x011d, 499, /* ĝ Ĝ */
    0x011f, 499, /* ğ Ğ */
    0x0121, 499, /* ġ Ġ */
    0x0123, 499, /* ģ Ģ */
    0x0125, 499, /* ĥ Ĥ */
    0x0127, 499, /* ħ Ħ */
    0x0129, 499, /* ĩ Ĩ */
    0x012b, 499, /* ī Ī */
    0x012d, 499, /* ĭ Ĭ */
    0x012f, 499, /* į Į */
    0x0131, 268, /* ı I */
    0x0133, 499, /* ĳ Ĳ */
    0x0135, 499, /* ĵ Ĵ */
    0x0137, 499, /* ķ Ķ */
    0x013a, 499, /* ĺ Ĺ */
    0x013c, 499, /* ļ Ļ */
    0x013e, 499, /* ľ Ľ */
    0x0140, 499, /* ŀ Ŀ */
    0x0142, 499, /* ł Ł */
    0x0144, 499, /* ń Ń */
    0x0146, 499, /* ņ Ņ */
    0x0148, 499, /* ň Ň */
    0x014b, 499, /* ŋ Ŋ */
    0x014d, 499, /* ō Ō */
    0x014f, 499, /* ŏ Ŏ */
    0x0151, 499, /* ő Ő */
    0x0153, 499, /* œ Œ */
    0x0155, 499, /* ŕ Ŕ */
    0x0157, 499, /* ŗ Ŗ */
    0x0159, 499, /* ř Ř */
    0x015b, 499, /* ś Ś */
    0x015d, 499, /* ŝ Ŝ */
    0x015f, 499, /* ş Ş */
    0x0161, 499, /* š Š */
    0x0163, 499, /* ţ Ţ */
    0x0165, 499, /* ť Ť */
    0x0167, 499, /* ŧ Ŧ */
    0x0169, 499, /* ũ Ũ */
    0x016b, 499, /* ū Ū */
    0x016d, 499, /* ŭ Ŭ */
    0x016f, 499, /* ů Ů */
    0x0171, 499, /* ű Ű */
    0x0173, 499, /* ų Ų */
    0x0175, 499, /* ŵ Ŵ */
    0x0177, 499, /* ŷ Ŷ */
    0x017a, 499, /* ź Ź */
    0x017c, 499, /* ż Ż */
    0x017e, 499, /* ž Ž */
    0x017f, 200, /* ſ S */
    0x0183, 499, /* ƃ Ƃ */
    0x0185, 499, /* ƅ Ƅ */
    0x0188, 499, /* ƈ Ƈ */
    0x018c, 499, /* ƌ Ƌ */
    0x0192, 499, /* ƒ Ƒ */
    0x0199, 499, /* ƙ Ƙ */
    0x01a1, 499, /* ơ Ơ */
    0x01a3, 499, /* ƣ Ƣ */
    0x01a5, 499, /* ƥ Ƥ */
    0x01a8, 499, /* ƨ Ƨ */
    0x01ad, 499, /* ƭ Ƭ */
    0x01b0, 499, /* ư Ư */
    0x01b4, 499, /* ƴ Ƴ */
    0x01b6, 499, /* ƶ Ƶ */
    0x01b9, 499, /* ƹ Ƹ */
    0x01bd, 499, /* ƽ Ƽ */
    0x01c5, 499, /* ǅ Ǆ */
    0x01c6, 498, /* ǆ Ǆ */
    0x01c8, 499, /* ǈ Ǉ */
    0x01c9, 498, /* ǉ Ǉ */
    0x01cb, 499, /* ǋ Ǌ */
    0x01cc, 498, /* ǌ Ǌ */
    0x01ce, 499, /* ǎ Ǎ */
    0x01d0, 499, /* ǐ Ǐ */
    0x01d2, 499, /* ǒ Ǒ */
    0x01d4, 499, /* ǔ Ǔ */
    0x01d6, 499, /* ǖ Ǖ */
    0x01d8, 499, /* ǘ Ǘ */
    0x01da, 499, /* ǚ Ǚ */
    0x01dc, 499, /* ǜ Ǜ */
    0x01df, 499, /* ǟ Ǟ */
    0x01e1, 499, /* ǡ Ǡ */
    0x01e3, 499, /* ǣ Ǣ */
    0x01e5, 499, /* ǥ Ǥ */
    0x01e7, 499, /* ǧ Ǧ */
    0x01e9, 499, /* ǩ Ǩ */
    0x01eb, 499, /* ǫ Ǫ */
    0x01ed, 499, /* ǭ Ǭ */
    0x01ef, 499, /* ǯ Ǯ */
    0x01f2, 499, /* ǲ Ǳ */
    0x01f3, 498, /* ǳ Ǳ */
    0x01f5, 499, /* ǵ Ǵ */
    0x01fb, 499, /* ǻ Ǻ */
    0x01fd, 499, /* ǽ Ǽ */
    0x01ff, 499, /* ǿ Ǿ */
    0x0201, 499, /* ȁ Ȁ */
    0x0203, 499, /* ȃ Ȃ */
    0x0205, 499, /* ȅ Ȅ */
    0x0207, 499, /* ȇ Ȇ */
    0x0209, 499, /* ȉ Ȉ */
    0x020b, 499, /* ȋ Ȋ */
    0x020d, 499, /* ȍ Ȍ */
    0x020f, 499, /* ȏ Ȏ */
    0x0211, 499, /* ȑ Ȑ */
    0x0213, 499, /* ȓ Ȓ */
    0x0215, 499, /* ȕ Ȕ */
    0x0217, 499, /* ȗ Ȗ */
    0x0253, 290, /* ɓ Ɓ */
    0x0254, 294, /* ɔ Ɔ */
    0x025b, 297, /* ɛ Ɛ */
    0x0260, 295, /* ɠ Ɠ */
    0x0263, 293, /* ɣ Ɣ */
    0x0268, 291, /* ɨ Ɨ */
    0x0269, 289, /* ɩ Ɩ */
    0x026f, 289, /* ɯ Ɯ */
    0x0272, 287, /* ɲ Ɲ */
    0x0283, 282, /* ʃ Ʃ */
    0x0288, 282, /* ʈ Ʈ */
    0x0292, 281, /* ʒ Ʒ */
    0x03ac, 462, /* ά Ά */
    0x03cc, 436, /* ό Ό */
    0x03d0, 438, /* ϐ Β */
    0x03d1, 443, /* ϑ Θ */
    0x03d5, 453, /* ϕ Φ */
    0x03d6, 446, /* ϖ Π */
    0x03e3, 499, /* ϣ Ϣ */
    0x03e5, 499, /* ϥ Ϥ */
    0x03e7, 499, /* ϧ Ϧ */
    0x03e9, 499, /* ϩ Ϩ */
    0x03eb, 499, /* ϫ Ϫ */
    0x03ed, 499, /* ϭ Ϭ */
    0x03ef, 499, /* ϯ Ϯ */
    0x03f0, 414, /* ϰ Κ */
    0x03f1, 420, /* ϱ Ρ */
    0x0461, 499, /* ѡ Ѡ */
    0x0463, 499, /* ѣ Ѣ */
    0x0465, 499, /* ѥ Ѥ */
    0x0467, 499, /* ѧ Ѧ */
    0x0469, 499, /* ѩ Ѩ */
    0x046b, 499, /* ѫ Ѫ */
    0x046d, 499, /* ѭ Ѭ */
    0x046f, 499, /* ѯ Ѯ */
    0x0471, 499, /* ѱ Ѱ */
    0x0473, 499, /* ѳ Ѳ */
    0x0475, 499, /* ѵ Ѵ */
    0x0477, 499, /* ѷ Ѷ */
    0x0479, 499, /* ѹ Ѹ */
    0x047b, 499, /* ѻ Ѻ */
    0x047d, 499, /* ѽ Ѽ */
    0x047f, 499, /* ѿ Ѿ */
    0x0481, 499, /* ҁ Ҁ */
    0x0491, 499, /* ґ Ґ */
    0x0493, 499, /* ғ Ғ */
    0x0495, 499, /* ҕ Ҕ */
    0x0497, 499, /* җ Җ */
    0x0499, 499, /* ҙ Ҙ */
    0x049b, 499, /* қ Қ */
    0x049d, 499, /* ҝ Ҝ */
    0x049f, 499, /* ҟ Ҟ */
    0x04a1, 499, /* ҡ Ҡ */
    0x04a3, 499, /* ң Ң */
    0x04a5, 499, /* ҥ Ҥ */
    0x04a7, 499, /* ҧ Ҧ */
    0x04a9, 499, /* ҩ Ҩ */
    0x04ab, 499, /* ҫ Ҫ */
    0x04ad, 499, /* ҭ Ҭ */
    0x04af, 499, /* ү Ү */
    0x04b1, 499, /* ұ Ұ */
    0x04b3, 499, /* ҳ Ҳ */
    0x04b5, 499, /* ҵ Ҵ */
    0x04b7, 499, /* ҷ Ҷ */
    0x04b9, 499, /* ҹ Ҹ */
    0x04bb, 499, /* һ Һ */
    0x04bd, 499, /* ҽ Ҽ */
    0x04bf, 499, /* ҿ Ҿ */
    0x04c2, 499, /* ӂ Ӂ */
    0x04c4, 499, /* ӄ Ӄ */
    0x04c8, 499, /* ӈ Ӈ */
    0x04cc, 499, /* ӌ Ӌ */
    0x04d1, 499, /* ӑ Ӑ */
    0x04d3, 499, /* ӓ Ӓ */
    0x04d5, 499, /* ӕ Ӕ */
    0x04d7, 499, /* ӗ Ӗ */
    0x04d9, 499, /* ә Ә */
    0x04db, 499, /* ӛ Ӛ */
    0x04dd, 499, /* ӝ Ӝ */
    0x04df, 499, /* ӟ Ӟ */
    0x04e1, 499, /* ӡ Ӡ */
    0x04e3, 499, /* ӣ Ӣ */
    0x04e5, 499, /* ӥ Ӥ */
    0x04e7, 499, /* ӧ Ӧ */
    0x04e9, 499, /* ө Ө */
    0x04eb, 499, /* ӫ Ӫ */
    0x04ef, 499, /* ӯ Ӯ */
    0x04f1, 499, /* ӱ Ӱ */
    0x04f3, 499, /* ӳ Ӳ */
    0x04f5, 499, /* ӵ Ӵ */
    0x04f9, 499, /* ӹ Ӹ */
    0x1e01, 499, /* ḁ Ḁ */
    0x1e03, 499, /* ḃ Ḃ */
    0x1e05, 499, /* ḅ Ḅ */
    0x1e07, 499, /* ḇ Ḇ */
    0x1e09, 499, /* ḉ Ḉ */
    0x1e0b, 499, /* ḋ Ḋ */
    0x1e0d, 499, /* ḍ Ḍ */
    0x1e0f, 499, /* ḏ Ḏ */
    0x1e11, 499, /* ḑ Ḑ */
    0x1e13, 499, /* ḓ Ḓ */
    0x1e15, 499, /* ḕ Ḕ */
    0x1e17, 499, /* ḗ Ḗ */
    0x1e19, 499, /* ḙ Ḙ */
    0x1e1b, 499, /* ḛ Ḛ */
    0x1e1d, 499, /* ḝ Ḝ */
    0x1e1f, 499, /* ḟ Ḟ */
    0x1e21, 499, /* ḡ Ḡ */
    0x1e23, 499, /* ḣ Ḣ */
    0x1e25, 499, /* ḥ Ḥ */
    0x1e27, 499, /* ḧ Ḧ */
    0x1e29, 499, /* ḩ Ḩ */
    0x1e2b, 499, /* ḫ Ḫ */
    0x1e2d, 499, /* ḭ Ḭ */
    0x1e2f, 499, /* ḯ Ḯ */
    0x1e31, 499, /* ḱ Ḱ */
    0x1e33, 499, /* ḳ Ḳ */
    0x1e35, 499, /* ḵ Ḵ */
    0x1e37, 499, /* ḷ Ḷ */
    0x1e39, 499, /* ḹ Ḹ */
    0x1e3b, 499, /* ḻ Ḻ */
    0x1e3d, 499, /* ḽ Ḽ */
    0x1e3f, 499, /* ḿ Ḿ */
    0x1e41, 499, /* ṁ Ṁ */
    0x1e43, 499, /* ṃ Ṃ */
    0x1e45, 499, /* ṅ Ṅ */
    0x1e47, 499, /* ṇ Ṇ */
    0x1e49, 499, /* ṉ Ṉ */
    0x1e4b, 499, /* ṋ Ṋ */
    0x1e4d, 499, /* ṍ Ṍ */
    0x1e4f, 499, /* ṏ Ṏ */
    0x1e51, 499, /* ṑ Ṑ */
    0x1e53, 499, /* ṓ Ṓ */
    0x1e55, 499, /* ṕ Ṕ */
    0x1e57, 499, /* ṗ Ṗ */
    0x1e59, 499, /* ṙ Ṙ */
    0x1e5b, 499, /* ṛ Ṛ */
    0x1e5d, 499, /* ṝ Ṝ */
    0x1e5f, 499, /* ṟ Ṟ */
    0x1e61, 499, /* ṡ Ṡ */
    0x1e63, 499, /* ṣ Ṣ */
    0x1e65, 499, /* ṥ Ṥ */
    0x1e67, 499, /* ṧ Ṧ */
    0x1e69, 499, /* ṩ Ṩ */
    0x1e6b, 499, /* ṫ Ṫ */
    0x1e6d, 499, /* ṭ Ṭ */
    0x1e6f, 499, /* ṯ Ṯ */
    0x1e71, 499, /* ṱ Ṱ */
    0x1e73, 499, /* ṳ Ṳ */
    0x1e75, 499, /* ṵ Ṵ */
    0x1e77, 499, /* ṷ Ṷ */
    0x1e79, 499, /* ṹ Ṹ */
    0x1e7b, 499, /* ṻ Ṻ */
    0x1e7d, 499, /* ṽ Ṽ */
    0x1e7f, 499, /* ṿ Ṿ */
    0x1e81, 499, /* ẁ Ẁ */
    0x1e83, 499, /* ẃ Ẃ */
    0x1e85, 499, /* ẅ Ẅ */
    0x1e87, 499, /* ẇ Ẇ */
    0x1e89, 499, /* ẉ Ẉ */
    0x1e8b, 499, /* ẋ Ẋ */
    0x1e8d, 499, /* ẍ Ẍ */
    0x1e8f, 499, /* ẏ Ẏ */
    0x1e91, 499, /* ẑ Ẑ */
    0x1e93, 499, /* ẓ Ẓ */
    0x1e95, 499, /* ẕ Ẕ */
    0x1ea1, 499, /* ạ Ạ */
    0x1ea3, 499, /* ả Ả */
    0x1ea5, 499, /* ấ Ấ */
    0x1ea7, 499, /* ầ Ầ */
    0x1ea9, 499, /* ẩ Ẩ */
    0x1eab, 499, /* ẫ Ẫ */
    0x1ead, 499, /* ậ Ậ */
    0x1eaf, 499, /* ắ Ắ */
    0x1eb1, 499, /* ằ Ằ */
    0x1eb3, 499, /* ẳ Ẳ */
    0x1eb5, 499, /* ẵ Ẵ */
    0x1eb7, 499, /* ặ Ặ */
    0x1eb9, 499, /* ẹ Ẹ */
    0x1ebb, 499, /* ẻ Ẻ */
    0x1ebd, 499, /* ẽ Ẽ */
    0x1ebf, 499, /* ế Ế */
    0x1ec1, 499, /* ề Ề */
    0x1ec3, 499, /* ể Ể */
    0x1ec5, 499, /* ễ Ễ */
    0x1ec7, 499, /* ệ Ệ */
    0x1ec9, 499, /* ỉ Ỉ */
    0x1ecb, 499, /* ị Ị */
    0x1ecd, 499, /* ọ Ọ */
    0x1ecf, 499, /* ỏ Ỏ */
    0x1ed1, 499, /* ố Ố */
    0x1ed3, 499, /* ồ Ồ */
    0x1ed5, 499, /* ổ Ổ */
    0x1ed7, 499, /* ỗ Ỗ */
    0x1ed9, 499, /* ộ Ộ */
    0x1edb, 499, /* ớ Ớ */
    0x1edd, 499, /* ờ Ờ */
    0x1edf, 499, /* ở Ở */
    0x1ee1, 499, /* ỡ Ỡ */
    0x1ee3, 499, /* ợ Ợ */
    0x1ee5, 499, /* ụ Ụ */
    0x1ee7, 499, /* ủ Ủ */
    0x1ee9, 499, /* ứ Ứ */
    0x1eeb, 499, /* ừ Ừ */
    0x1eed, 499, /* ử Ử */
    0x1eef, 499, /* ữ Ữ */
    0x1ef1, 499, /* ự Ự */
    0x1ef3, 499, /* ỳ Ỳ */
    0x1ef5, 499, /* ỵ Ỵ */
    0x1ef7, 499, /* ỷ Ỷ */
    0x1ef9, 499, /* ỹ Ỹ */
    0x1f51, 508, /* ὑ Ὑ */
    0x1f53, 508, /* ὓ Ὓ */
    0x1f55, 508, /* ὕ Ὕ */
    0x1f57, 508, /* ὗ Ὗ */
    0x1fb3, 509, /* ᾳ ᾼ */
    0x1fc3, 509, /* ῃ ῌ */
    0x1fe5, 507, /* ῥ Ῥ */
    0x1ff3, 509, /* ῳ ῼ */
};

/*
 * upper case ranges
 *	3rd col is conversion excess 500
 */
static Rune __tolower2[] = {
    0x0041, 0x005a, 532, /* A-Z a-z */
    0x00c0, 0x00d6, 532, /* À-Ö à-ö */
    0x00d8, 0x00de, 532, /* Ø-Þ ø-þ */
    0x0189, 0x018a, 705, /* Ɖ-Ɗ ɖ-ɗ */
    0x018e, 0x018f, 702, /* Ǝ-Ə ɘ-ə */
    0x01b1, 0x01b2, 717, /* Ʊ-Ʋ ʊ-ʋ */
    0x0388, 0x038a, 537, /* Έ-Ί έ-ί */
    0x038e, 0x038f, 563, /* Ύ-Ώ ύ-ώ */
    0x0391, 0x03a1, 532, /* Α-Ρ α-ρ */
    0x03a3, 0x03ab, 532, /* Σ-Ϋ σ-ϋ */
    0x0401, 0x040c, 580, /* Ё-Ќ ё-ќ */
    0x040e, 0x040f, 580, /* Ў-Џ ў-џ */
    0x0410, 0x042f, 532, /* А-Я а-я */
    0x0531, 0x0556, 548, /* Ա-Ֆ ա-ֆ */
    0x10a0, 0x10c5, 548, /* Ⴀ-Ⴥ ა-ჵ */
    0x1f08, 0x1f0f, 492, /* Ἀ-Ἇ ἀ-ἇ */
    0x1f18, 0x1f1d, 492, /* Ἐ-Ἕ ἐ-ἕ */
    0x1f28, 0x1f2f, 492, /* Ἠ-Ἧ ἠ-ἧ */
    0x1f38, 0x1f3f, 492, /* Ἰ-Ἷ ἰ-ἷ */
    0x1f48, 0x1f4d, 492, /* Ὀ-Ὅ ὀ-ὅ */
    0x1f68, 0x1f6f, 492, /* Ὠ-Ὧ ὠ-ὧ */
    0x1f88, 0x1f8f, 492, /* ᾈ-ᾏ ᾀ-ᾇ */
    0x1f98, 0x1f9f, 492, /* ᾘ-ᾟ ᾐ-ᾗ */
    0x1fa8, 0x1faf, 492, /* ᾨ-ᾯ ᾠ-ᾧ */
    0x1fb8, 0x1fb9, 492, /* Ᾰ-Ᾱ ᾰ-ᾱ */
    0x1fba, 0x1fbb, 426, /* Ὰ-Ά ὰ-ά */
    0x1fc8, 0x1fcb, 414, /* Ὲ-Ή ὲ-ή */
    0x1fd8, 0x1fd9, 492, /* Ῐ-Ῑ ῐ-ῑ */
    0x1fda, 0x1fdb, 400, /* Ὶ-Ί ὶ-ί */
    0x1fe8, 0x1fe9, 492, /* Ῠ-Ῡ ῠ-ῡ */
    0x1fea, 0x1feb, 388, /* Ὺ-Ύ ὺ-ύ */
    0x1ff8, 0x1ff9, 372, /* Ὸ-Ό ὸ-ό */
    0x1ffa, 0x1ffb, 374, /* Ὼ-Ώ ὼ-ώ */
    0x2160, 0x216f, 516, /* Ⅰ-Ⅿ ⅰ-ⅿ */
    0x24b6, 0x24cf, 526, /* Ⓐ-Ⓩ ⓐ-ⓩ */
    0xff21, 0xff3a, 532, /* Ａ-Ｚ ａ-ｚ */
};

/*
 * upper case singlets
 *	2nd col is conversion excess 500
 */
static Rune __tolower1[] = {
    0x0100, 501, /* Ā ā */
    0x0102, 501, /* Ă ă */
    0x0104, 501, /* Ą ą */
    0x0106, 501, /* Ć ć */
    0x0108, 501, /* Ĉ ĉ */
    0x010a, 501, /* Ċ ċ */
    0x010c, 501, /* Č č */
    0x010e, 501, /* Ď ď */
    0x0110, 501, /* Đ đ */
    0x0112, 501, /* Ē ē */
    0x0114, 501, /* Ĕ ĕ */
    0x0116, 501, /* Ė ė */
    0x0118, 501, /* Ę ę */
    0x011a, 501, /* Ě ě */
    0x011c, 501, /* Ĝ ĝ */
    0x011e, 501, /* Ğ ğ */
    0x0120, 501, /* Ġ ġ */
    0x0122, 501, /* Ģ ģ */
    0x0124, 501, /* Ĥ ĥ */
    0x0126, 501, /* Ħ ħ */
    0x0128, 501, /* Ĩ ĩ */
    0x012a, 501, /* Ī ī */
    0x012c, 501, /* Ĭ ĭ */
    0x012e, 501, /* Į į */
    0x0130, 301, /* İ i */
    0x0132, 501, /* Ĳ ĳ */
    0x0134, 501, /* Ĵ ĵ */
    0x0136, 501, /* Ķ ķ */
    0x0139, 501, /* Ĺ ĺ */
    0x013b, 501, /* Ļ ļ */
    0x013d, 501, /* Ľ ľ */
    0x013f, 501, /* Ŀ ŀ */
    0x0141, 501, /* Ł ł */
    0x0143, 501, /* Ń ń */
    0x0145, 501, /* Ņ ņ */
    0x0147, 501, /* Ň ň */
    0x014a, 501, /* Ŋ ŋ */
    0x014c, 501, /* Ō ō */
    0x014e, 501, /* Ŏ ŏ */
    0x0150, 501, /* Ő ő */
    0x0152, 501, /* Œ œ */
    0x0154, 501, /* Ŕ ŕ */
    0x0156, 501, /* Ŗ ŗ */
    0x0158, 501, /* Ř ř */
    0x015a, 501, /* Ś ś */
    0x015c, 501, /* Ŝ ŝ */
    0x015e, 501, /* Ş ş */
    0x0160, 501, /* Š š */
    0x0162, 501, /* Ţ ţ */
    0x0164, 501, /* Ť ť */
    0x0166, 501, /* Ŧ ŧ */
    0x0168, 501, /* Ũ ũ */
    0x016a, 501, /* Ū ū */
    0x016c, 501, /* Ŭ ŭ */
    0x016e, 501, /* Ů ů */
    0x0170, 501, /* Ű ű */
    0x0172, 501, /* Ų ų */
    0x0174, 501, /* Ŵ ŵ */
    0x0176, 501, /* Ŷ ŷ */
    0x0178, 379, /* Ÿ ÿ */
    0x0179, 501, /* Ź ź */
    0x017b, 501, /* Ż ż */
    0x017d, 501, /* Ž ž */
    0x0181, 710, /* Ɓ ɓ */
    0x0182, 501, /* Ƃ ƃ */
    0x0184, 501, /* Ƅ ƅ */
    0x0186, 706, /* Ɔ ɔ */
    0x0187, 501, /* Ƈ ƈ */
    0x018b, 501, /* Ƌ ƌ */
    0x0190, 703, /* Ɛ ɛ */
    0x0191, 501, /* Ƒ ƒ */
    0x0193, 705, /* Ɠ ɠ */
    0x0194, 707, /* Ɣ ɣ */
    0x0196, 711, /* Ɩ ɩ */
    0x0197, 709, /* Ɨ ɨ */
    0x0198, 501, /* Ƙ ƙ */
    0x019c, 711, /* Ɯ ɯ */
    0x019d, 713, /* Ɲ ɲ */
    0x01a0, 501, /* Ơ ơ */
    0x01a2, 501, /* Ƣ ƣ */
    0x01a4, 501, /* Ƥ ƥ */
    0x01a7, 501, /* Ƨ ƨ */
    0x01a9, 718, /* Ʃ ʃ */
    0x01ac, 501, /* Ƭ ƭ */
    0x01ae, 718, /* Ʈ ʈ */
    0x01af, 501, /* Ư ư */
    0x01b3, 501, /* Ƴ ƴ */
    0x01b5, 501, /* Ƶ ƶ */
    0x01b7, 719, /* Ʒ ʒ */
    0x01b8, 501, /* Ƹ ƹ */
    0x01bc, 501, /* Ƽ ƽ */
    0x01c4, 502, /* Ǆ ǆ */
    0x01c5, 501, /* ǅ ǆ */
    0x01c7, 502, /* Ǉ ǉ */
    0x01c8, 501, /* ǈ ǉ */
    0x01ca, 502, /* Ǌ ǌ */
    0x01cb, 501, /* ǋ ǌ */
    0x01cd, 501, /* Ǎ ǎ */
    0x01cf, 501, /* Ǐ ǐ */
    0x01d1, 501, /* Ǒ ǒ */
    0x01d3, 501, /* Ǔ ǔ */
    0x01d5, 501, /* Ǖ ǖ */
    0x01d7, 501, /* Ǘ ǘ */
    0x01d9, 501, /* Ǚ ǚ */
    0x01db, 501, /* Ǜ ǜ */
    0x01de, 501, /* Ǟ ǟ */
    0x01e0, 501, /* Ǡ ǡ */
    0x01e2, 501, /* Ǣ ǣ */
    0x01e4, 501, /* Ǥ ǥ */
    0x01e6, 501, /* Ǧ ǧ */
    0x01e8, 501, /* Ǩ ǩ */
    0x01ea, 501, /* Ǫ ǫ */
    0x01ec, 501, /* Ǭ ǭ */
    0x01ee, 501, /* Ǯ ǯ */
    0x01f1, 502, /* Ǳ ǳ */
    0x01f2, 501, /* ǲ ǳ */
    0x01f4, 501, /* Ǵ ǵ */
    0x01fa, 501, /* Ǻ ǻ */
    0x01fc, 501, /* Ǽ ǽ */
    0x01fe, 501, /* Ǿ ǿ */
    0x0200, 501, /* Ȁ ȁ */
    0x0202, 501, /* Ȃ ȃ */
    0x0204, 501, /* Ȅ ȅ */
    0x0206, 501, /* Ȇ ȇ */
    0x0208, 501, /* Ȉ ȉ */
    0x020a, 501, /* Ȋ ȋ */
    0x020c, 501, /* Ȍ ȍ */
    0x020e, 501, /* Ȏ ȏ */
    0x0210, 501, /* Ȑ ȑ */
    0x0212, 501, /* Ȓ ȓ */
    0x0214, 501, /* Ȕ ȕ */
    0x0216, 501, /* Ȗ ȗ */
    0x0386, 538, /* Ά ά */
    0x038c, 564, /* Ό ό */
    0x03e2, 501, /* Ϣ ϣ */
    0x03e4, 501, /* Ϥ ϥ */
    0x03e6, 501, /* Ϧ ϧ */
    0x03e8, 501, /* Ϩ ϩ */
    0x03ea, 501, /* Ϫ ϫ */
    0x03ec, 501, /* Ϭ ϭ */
    0x03ee, 501, /* Ϯ ϯ */
    0x0460, 501, /* Ѡ ѡ */
    0x0462, 501, /* Ѣ ѣ */
    0x0464, 501, /* Ѥ ѥ */
    0x0466, 501, /* Ѧ ѧ */
    0x0468, 501, /* Ѩ ѩ */
    0x046a, 501, /* Ѫ ѫ */
    0x046c, 501, /* Ѭ ѭ */
    0x046e, 501, /* Ѯ ѯ */
    0x0470, 501, /* Ѱ ѱ */
    0x0472, 501, /* Ѳ ѳ */
    0x0474, 501, /* Ѵ ѵ */
    0x0476, 501, /* Ѷ ѷ */
    0x0478, 501, /* Ѹ ѹ */
    0x047a, 501, /* Ѻ ѻ */
    0x047c, 501, /* Ѽ ѽ */
    0x047e, 501, /* Ѿ ѿ */
    0x0480, 501, /* Ҁ ҁ */
    0x0490, 501, /* Ґ ґ */
    0x0492, 501, /* Ғ ғ */
    0x0494, 501, /* Ҕ ҕ */
    0x0496, 501, /* Җ җ */
    0x0498, 501, /* Ҙ ҙ */
    0x049a, 501, /* Қ қ */
    0x049c, 501, /* Ҝ ҝ */
    0x049e, 501, /* Ҟ ҟ */
    0x04a0, 501, /* Ҡ ҡ */
    0x04a2, 501, /* Ң ң */
    0x04a4, 501, /* Ҥ ҥ */
    0x04a6, 501, /* Ҧ ҧ */
    0x04a8, 501, /* Ҩ ҩ */
    0x04aa, 501, /* Ҫ ҫ */
    0x04ac, 501, /* Ҭ ҭ */
    0x04ae, 501, /* Ү ү */
    0x04b0, 501, /* Ұ ұ */
    0x04b2, 501, /* Ҳ ҳ */
    0x04b4, 501, /* Ҵ ҵ */
    0x04b6, 501, /* Ҷ ҷ */
    0x04b8, 501, /* Ҹ ҹ */
    0x04ba, 501, /* Һ һ */
    0x04bc, 501, /* Ҽ ҽ */
    0x04be, 501, /* Ҿ ҿ */
    0x04c1, 501, /* Ӂ ӂ */
    0x04c3, 501, /* Ӄ ӄ */
    0x04c7, 501, /* Ӈ ӈ */
    0x04cb, 501, /* Ӌ ӌ */
    0x04d0, 501, /* Ӑ ӑ */
    0x04d2, 501, /* Ӓ ӓ */
    0x04d4, 501, /* Ӕ ӕ */
    0x04d6, 501, /* Ӗ ӗ */
    0x04d8, 501, /* Ә ә */
    0x04da, 501, /* Ӛ ӛ */
    0x04dc, 501, /* Ӝ ӝ */
    0x04de, 501, /* Ӟ ӟ */
    0x04e0, 501, /* Ӡ ӡ */
    0x04e2, 501, /* Ӣ ӣ */
    0x04e4, 501, /* Ӥ ӥ */
    0x04e6, 501, /* Ӧ ӧ */
    0x04e8, 501, /* Ө ө */
    0x04ea, 501, /* Ӫ ӫ */
    0x04ee, 501, /* Ӯ ӯ */
    0x04f0, 501, /* Ӱ ӱ */
    0x04f2, 501, /* Ӳ ӳ */
    0x04f4, 501, /* Ӵ ӵ */
    0x04f8, 501, /* Ӹ ӹ */
    0x1e00, 501, /* Ḁ ḁ */
    0x1e02, 501, /* Ḃ ḃ */
    0x1e04, 501, /* Ḅ ḅ */
    0x1e06, 501, /* Ḇ ḇ */
    0x1e08, 501, /* Ḉ ḉ */
    0x1e0a, 501, /* Ḋ ḋ */
    0x1e0c, 501, /* Ḍ ḍ */
    0x1e0e, 501, /* Ḏ ḏ */
    0x1e10, 501, /* Ḑ ḑ */
    0x1e12, 501, /* Ḓ ḓ */
    0x1e14, 501, /* Ḕ ḕ */
    0x1e16, 501, /* Ḗ ḗ */
    0x1e18, 501, /* Ḙ ḙ */
    0x1e1a, 501, /* Ḛ ḛ */
    0x1e1c, 501, /* Ḝ ḝ */
    0x1e1e, 501, /* Ḟ ḟ */
    0x1e20, 501, /* Ḡ ḡ */
    0x1e22, 501, /* Ḣ ḣ */
    0x1e24, 501, /* Ḥ ḥ */
    0x1e26, 501, /* Ḧ ḧ */
    0x1e28, 501, /* Ḩ ḩ */
    0x1e2a, 501, /* Ḫ ḫ */
    0x1e2c, 501, /* Ḭ ḭ */
    0x1e2e, 501, /* Ḯ ḯ */
    0x1e30, 501, /* Ḱ ḱ */
    0x1e32, 501, /* Ḳ ḳ */
    0x1e34, 501, /* Ḵ ḵ */
    0x1e36, 501, /* Ḷ ḷ */
    0x1e38, 501, /* Ḹ ḹ */
    0x1e3a, 501, /* Ḻ ḻ */
    0x1e3c, 501, /* Ḽ ḽ */
    0x1e3e, 501, /* Ḿ ḿ */
    0x1e40, 501, /* Ṁ ṁ */
    0x1e42, 501, /* Ṃ ṃ */
    0x1e44, 501, /* Ṅ ṅ */
    0x1e46, 501, /* Ṇ ṇ */
    0x1e48, 501, /* Ṉ ṉ */
    0x1e4a, 501, /* Ṋ ṋ */
    0x1e4c, 501, /* Ṍ ṍ */
    0x1e4e, 501, /* Ṏ ṏ */
    0x1e50, 501, /* Ṑ ṑ */
    0x1e52, 501, /* Ṓ ṓ */
    0x1e54, 501, /* Ṕ ṕ */
    0x1e56, 501, /* Ṗ ṗ */
    0x1e58, 501, /* Ṙ ṙ */
    0x1e5a, 501, /* Ṛ ṛ */
    0x1e5c, 501, /* Ṝ ṝ */
    0x1e5e, 501, /* Ṟ ṟ */
    0x1e60, 501, /* Ṡ ṡ */
    0x1e62, 501, /* Ṣ ṣ */
    0x1e64, 501, /* Ṥ ṥ */
    0x1e66, 501, /* Ṧ ṧ */
    0x1e68, 501, /* Ṩ ṩ */
    0x1e6a, 501, /* Ṫ ṫ */
    0x1e6c, 501, /* Ṭ ṭ */
    0x1e6e, 501, /* Ṯ ṯ */
    0x1e70, 501, /* Ṱ ṱ */
    0x1e72, 501, /* Ṳ ṳ */
    0x1e74, 501, /* Ṵ ṵ */
    0x1e76, 501, /* Ṷ ṷ */
    0x1e78, 501, /* Ṹ ṹ */
    0x1e7a, 501, /* Ṻ ṻ */
    0x1e7c, 501, /* Ṽ ṽ */
    0x1e7e, 501, /* Ṿ ṿ */
    0x1e80, 501, /* Ẁ ẁ */
    0x1e82, 501, /* Ẃ ẃ */
    0x1e84, 501, /* Ẅ ẅ */
    0x1e86, 501, /* Ẇ ẇ */
    0x1e88, 501, /* Ẉ ẉ */
    0x1e8a, 501, /* Ẋ ẋ */
    0x1e8c, 501, /* Ẍ ẍ */
    0x1e8e, 501, /* Ẏ ẏ */
    0x1e90, 501, /* Ẑ ẑ */
    0x1e92, 501, /* Ẓ ẓ */
    0x1e94, 501, /* Ẕ ẕ */
    0x1ea0, 501, /* Ạ ạ */
    0x1ea2, 501, /* Ả ả */
    0x1ea4, 501, /* Ấ ấ */
    0x1ea6, 501, /* Ầ ầ */
    0x1ea8, 501, /* Ẩ ẩ */
    0x1eaa, 501, /* Ẫ ẫ */
    0x1eac, 501, /* Ậ ậ */
    0x1eae, 501, /* Ắ ắ */
    0x1eb0, 501, /* Ằ ằ */
    0x1eb2, 501, /* Ẳ ẳ */
    0x1eb4, 501, /* Ẵ ẵ */
    0x1eb6, 501, /* Ặ ặ */
    0x1eb8, 501, /* Ẹ ẹ */
    0x1eba, 501, /* Ẻ ẻ */
    0x1ebc, 501, /* Ẽ ẽ */
    0x1ebe, 501, /* Ế ế */
    0x1ec0, 501, /* Ề ề */
    0x1ec2, 501, /* Ể ể */
    0x1ec4, 501, /* Ễ ễ */
    0x1ec6, 501, /* Ệ ệ */
    0x1ec8, 501, /* Ỉ ỉ */
    0x1eca, 501, /* Ị ị */
    0x1ecc, 501, /* Ọ ọ */
    0x1ece, 501, /* Ỏ ỏ */
    0x1ed0, 501, /* Ố ố */
    0x1ed2, 501, /* Ồ ồ */
    0x1ed4, 501, /* Ổ ổ */
    0x1ed6, 501, /* Ỗ ỗ */
    0x1ed8, 501, /* Ộ ộ */
    0x1eda, 501, /* Ớ ớ */
    0x1edc, 501, /* Ờ ờ */
    0x1ede, 501, /* Ở ở */
    0x1ee0, 501, /* Ỡ ỡ */
    0x1ee2, 501, /* Ợ ợ */
    0x1ee4, 501, /* Ụ ụ */
    0x1ee6, 501, /* Ủ ủ */
    0x1ee8, 501, /* Ứ ứ */
    0x1eea, 501, /* Ừ ừ */
    0x1eec, 501, /* Ử ử */
    0x1eee, 501, /* Ữ ữ */
    0x1ef0, 501, /* Ự ự */
    0x1ef2, 501, /* Ỳ ỳ */
    0x1ef4, 501, /* Ỵ ỵ */
    0x1ef6, 501, /* Ỷ ỷ */
    0x1ef8, 501, /* Ỹ ỹ */
    0x1f59, 492, /* Ὑ ὑ */
    0x1f5b, 492, /* Ὓ ὓ */
    0x1f5d, 492, /* Ὕ ὕ */
    0x1f5f, 492, /* Ὗ ὗ */
    0x1fbc, 491, /* ᾼ ᾳ */
    0x1fcc, 491, /* ῌ ῃ */
    0x1fec, 493, /* Ῥ ῥ */
    0x1ffc, 491, /* ῼ ῳ */
};

static Rune *rune_bsearch(Rune c, Rune *t, int n, int ne) {
  Rune *p;
  int m;

  while (n > 1) {
    m = n / 2;
    p = t + m * ne;
    if (c >= p[0]) {
      t = p;
      n = n - m;
    } else
      n = m;
  }
  if (n && c >= t[0]) return t;
  return 0;
}

Rune tolowerrune(Rune c) {
  Rune *p;

  p = rune_bsearch(c, __tolower2, nelem(__tolower2) / 3, 3);
  if (p && c >= p[0] && c <= p[1]) return c + p[2] - 500;
  p = rune_bsearch(c, __tolower1, nelem(__tolower1) / 2, 2);
  if (p && c == p[0]) return c + p[1] - 500;
  return c;
}

Rune toupperrune(Rune c) {
  Rune *p;

  p = rune_bsearch(c, __toupper2, nelem(__toupper2) / 3, 3);
  if (p && c >= p[0] && c <= p[1]) return c + p[2] - 500;
  p = rune_bsearch(c, __toupper1, nelem(__toupper1) / 2, 2);
  if (p && c == p[0]) return c + p[1] - 500;
  return c;
}

int islowerrune(Rune c) {
  Rune *p;

  p = rune_bsearch(c, __toupper2, nelem(__toupper2) / 3, 3);
  if (p && c >= p[0] && c <= p[1]) return 1;
  p = rune_bsearch(c, __toupper1, nelem(__toupper1) / 2, 2);
  if (p && c == p[0]) return 1;
  return 0;
}

int isupperrune(Rune c) {
  Rune *p;

  p = rune_bsearch(c, __tolower2, nelem(__tolower2) / 3, 3);
  if (p && c >= p[0] && c <= p[1]) return 1;
  p = rune_bsearch(c, __tolower1, nelem(__tolower1) / 2, 2);
  if (p && c == p[0]) return 1;
  return 0;
}

int isdigitrune(Rune c) {
  return c >= '0' && c <= '9';
}

int isnewline(Rune c) {
  return c == 0xA || c == 0xD || c == 0x2028 || c == 0x2029;
}

int iswordchar(Rune c) {
  return c == '_' || isdigitrune(c) || (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z');
}

int isalpharune(Rune c) {
  Rune *p;

  if (isupperrune(c) || islowerrune(c)) return 1;
  p = rune_bsearch(c, __alpha2, nelem(__alpha2) / 2, 2);
  if (p && c >= p[0] && c <= p[1]) return 1;
  p = rune_bsearch(c, __alpha1, nelem(__alpha1), 1);
  if (p && c == p[0]) return 1;
  return 0;
}

int isspacerune(Rune c) {
  Rune *p;

  p = rune_bsearch(c, __space2, nelem(__space2) / 2, 2);
  if (p && c >= p[0] && c <= p[1]) return 1;
  return 0;
}

#else /* CS_ENABLE_UTF8 */

int chartorune(Rune *rune, const char *str) {
  *rune = *(uchar *) str;
  return 1;
}

int fullrune(const char *str, int n) {
  (void) str;
  return (n <= 0) ? 0 : 1;
}

int isdigitrune(Rune c) {
  return isdigit(c);
}

int isnewline(Rune c) {
  return c == 0xA || c == 0xD || c == 0x2028 || c == 0x2029;
}

int iswordchar(Rune c) {
  return c == '_' || isdigitrune(c) || (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z');
}

int isalpharune(Rune c) {
  return isalpha(c);
}
int islowerrune(Rune c) {
  return islower(c);
}
int isspacerune(Rune c) {
  return isspace(c);
}
int isupperrune(Rune c) {
  return isupper(c);
}

int runetochar(char *str, Rune *rune) {
  str[0] = (char) *rune;
  return 1;
}

Rune tolowerrune(Rune c) {
  return tolower(c);
}
Rune toupperrune(Rune c) {
  return toupper(c);
}
int utfnlen(const char *s, long m) {
  (void) s;
  return (int) c_strnlen(s, (size_t) m);
}

const char *utfnshift(const char *s, long m) {
  return s + m;
}

#endif /* CS_ENABLE_UTF8 */

#endif /* EXCLUDE_COMMON */
#ifdef MG_MODULE_LINES
#line 1 "bazel-out/local-dbg-asan/genfiles/mjs/mjs.lem.c"
#endif
/* clang-format off */
/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/
#line 16 "mjs/mjs.lem.c"

  #include <assert.h>
  #include <string.h>
/* Amalgamated:   #include "mjs/parser_state.h" */
#line 34 "mjs/mjs.lem.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    mjsParserTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is mjsParserTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    mjsParserARG_SDECL     A static variable declaration for the %extra_argument
**    mjsParserARG_PDECL     A parameter declaration for the %extra_argument
**    mjsParserARG_STORE     Code to store %extra_argument into yypParser
**    mjsParserARG_FETCH     Code to extract %extra_argument from yypParser
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_MIN_REDUCE      Maximum value for reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 128
#define YYACTIONTYPE unsigned short int
#define mjsParserTOKENTYPE struct mjs_token
typedef union {
  int yyinit;
  mjsParserTOKENTYPE yy0;
  int yy156;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define mjsParserARG_SDECL struct mjs_parse_ctx *ctx;
#define mjsParserARG_PDECL ,struct mjs_parse_ctx *ctx
#define mjsParserARG_FETCH struct mjs_parse_ctx *ctx = yypParser->ctx
#define mjsParserARG_STORE yypParser->ctx = ctx
#define YYNSTATE             140
#define YYNRULE              196
#define YY_MAX_SHIFT         139
#define YY_MIN_SHIFTREDUCE   287
#define YY_MAX_SHIFTREDUCE   482
#define YY_MIN_REDUCE        483
#define YY_MAX_REDUCE        678
#define YY_ERROR_ACTION      679
#define YY_ACCEPT_ACTION     680
#define YY_NO_ACTION         681
/************* End control #defines *******************************************/

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if:
**    (1)  The yy_shift_ofst[S]+X value is out of range, or
**    (2)  yy_lookahead[yy_shift_ofst[S]+X] is not equal to X, or
**    (3)  yy_shift_ofst[S] equal YY_SHIFT_USE_DFLT.
** (Implementation note: YY_SHIFT_USE_DFLT is chosen so that
** YY_SHIFT_USE_DFLT+X will be out of range for all possible lookaheads X.
** Hence only tests (1) and (2) need to be evaluated.)
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (1406)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   288,  289,  290,  291,  292,  293,  294,  295,  296,  297,
 /*    10 */   298,  299,  300,  301,  302,  303,  304,  305,  306,  307,
 /*    20 */   308,  309,  310,  311,  312,  313,  314,  315,  316,  317,
 /*    30 */   318,  319,  320,  321,  322,  323,  324,  325,  326,  327,
 /*    40 */   328,  329,  330,  331,  332,  333,  334,  335,  336,  337,
 /*    50 */   338,  339,  340,  341,  342,  343,  344,  345,  346,  347,
 /*    60 */   348,  349,  350,  351,  352,  353,  354,  355,  356,  357,
 /*    70 */   358,  359,  360,  361,  362,  363,  364,  365,  366,  367,
 /*    80 */   368,  369,  370,  371,  372,  373,  374,  375,  376,  377,
 /*    90 */   378,  379,  380,  381,  382,  383,  384,  385,  386,  387,
 /*   100 */   463,  464,  471,  436,   61,   62,   23,   38,  457,   14,
 /*   110 */    47,   45,   46,   44,   84,   69,   69,  116,  116,  478,
 /*   120 */   477,  139,  476,   69,  138,   69,   69,   69,   43,   42,
 /*   130 */   416,  417,   53,   55,   49,   51,   39,   41,   40,   57,
 /*   140 */    54,   52,   50,   48,   60,   58,   56,   83,   69,   69,
 /*   150 */   455,   59,   38,  129,  472,  126,   69,   68,   69,   69,
 /*   160 */    69,  470,  391,  132,  120,  135,  118,  118,  126,  460,
 /*   170 */    18,  119,  462,  119,  469,  416,  417,  392,  121,  133,
 /*   180 */   121,   65,  461,  673,  463,  464,  674,  436,   61,  453,
 /*   190 */    23,   12,  672,   14,   24,  122,  122,   63,  459,   66,
 /*   200 */   438,   13,   20,   36,   31,   33,   32,   26,   35,   34,
 /*   210 */    25,   27,   30,   29,   28,    2,   53,   55,   49,   51,
 /*   220 */    84,   69,   69,   57,  439,   81,   69,   69,   19,   69,
 /*   230 */   479,   69,   69,   69,   69,   59,   69,   69,   69,  127,
 /*   240 */    67,  128,  117,    3,   64,  470,   15,  132,  120,  135,
 /*   250 */   136,   67,   16,  460,   18,   17,  462,   21,  469,    5,
 /*   260 */    22,    7,   64,  133,   37,   65,  461,  485,  463,  464,
 /*   270 */   584,  436,   61,  451,   23,   12,    4,   14,   24,  485,
 /*   280 */   485,  485,  485,  485,  485,  485,  485,   36,   31,   33,
 /*   290 */    32,   26,   35,   34,   25,   27,   30,   29,   28,  485,
 /*   300 */    53,   55,   49,   51,  485,    9,    9,   57,  485,   73,
 /*   310 */    69,   69,  485,  485,  485,  485,    9,  485,   69,   59,
 /*   320 */    69,   69,   69,  118,  118,  126,  485,  485,  485,  470,
 /*   330 */   485,  132,  120,  135,  485,  485,  485,  460,   18,  485,
 /*   340 */   462,  485,  469,  485,  485,  485,  485,  133,  485,   65,
 /*   350 */   461,  485,  463,  464,  485,  436,   61,  454,   23,   12,
 /*   360 */     6,   14,   24,  485,  485,  485,  485,  485,  485,  485,
 /*   370 */   485,   36,   31,   33,   32,   26,   35,   34,   25,   27,
 /*   380 */    30,   29,   28,  485,   53,   55,   49,   51,  485,  485,
 /*   390 */   485,   57,  680,  485,   11,   11,  485,  485,   73,   69,
 /*   400 */    69,  485,  485,   59,  485,   11,  485,   69,  485,   69,
 /*   410 */    69,   69,  485,  470,  485,  132,  120,  135,  485,  485,
 /*   420 */   485,  460,   18,  485,  462,  485,  469,  485,  485,  485,
 /*   430 */   485,  133,  485,   65,  461,  483,  485,  463,  464,  485,
 /*   440 */   436,   61,   12,   23,  485,   24,   14,  485,  485,  396,
 /*   450 */   485,  485,  485,  485,   36,   31,   33,   32,   26,   35,
 /*   460 */    34,   25,   27,   30,   29,   28,  485,  485,  485,   53,
 /*   470 */    55,   49,   51,  485,  485,  485,   57,  485,    8,    8,
 /*   480 */   485,  485,   73,   69,   69,  485,  485,  485,   59,    8,
 /*   490 */   485,   69,  485,   69,   69,   69,  485,  485,  470,  485,
 /*   500 */   132,  120,  135,  485,  485,  485,  460,   18,  485,  462,
 /*   510 */   485,  469,  485,  485,  485,  485,  133,  485,   65,  461,
 /*   520 */   485,  124,  123,  485,  125,   61,  485,   23,   12,  435,
 /*   530 */    14,   24,  485,  485,  485,  485,  485,  485,  485,  485,
 /*   540 */    36,   31,   33,   32,   26,   35,   34,   25,   27,   30,
 /*   550 */    29,   28,  485,   53,   55,   49,   51,  485,  485,  485,
 /*   560 */    57,  447,  485,  485,   73,   69,   69,  485,  485,  447,
 /*   570 */   485,  447,   59,   69,  485,   69,   69,   69,  485,  485,
 /*   580 */   485,  485,  470,  485,  132,  120,  135,  485,  485,  485,
 /*   590 */   460,   18,  485,  462,  485,  469,   38,  485,  485,  485,
 /*   600 */   133,  485,   65,  461,  485,  463,  464,  485,  436,   61,
 /*   610 */   485,   23,  485,  485,   14,  485,  485,   43,   42,  416,
 /*   620 */   417,  485,  485,  485,  485,   39,   41,   40,  485,   54,
 /*   630 */    52,   50,   48,   60,   58,   56,  485,   53,   55,   49,
 /*   640 */    51,  485,  485,  485,   57,  485,  485,  446,  485,  485,
 /*   650 */    73,   69,   69,  485,  485,  446,   59,  446,  485,   69,
 /*   660 */   485,   69,   69,   69,  485,  485,  470,  485,  132,  120,
 /*   670 */   135,  485,  485,  485,  460,   18,  485,  462,  485,  469,
 /*   680 */   485,  485,  485,  485,  133,  485,   65,  461,  485,  463,
 /*   690 */   464,  485,  436,    1,  485,   23,   12,  485,   14,   24,
 /*   700 */   443,  485,  485,  485,  485,  485,  485,  485,   36,   31,
 /*   710 */    33,   32,   26,   35,   34,   25,   27,   30,   29,   28,
 /*   720 */   485,   53,   55,   49,   51,  485,  485,  445,   57,  485,
 /*   730 */    73,   69,   69,  485,  485,  445,  485,  445,  485,   69,
 /*   740 */    59,   69,   69,   69,  485,  485,  485,  485,  485,  485,
 /*   750 */   470,  485,  132,  120,  135,  485,  485,  485,  460,   18,
 /*   760 */   485,  462,  485,  469,  485,  485,  485,  485,  133,  485,
 /*   770 */    65,  461,  485,  463,  464,  485,  436,   61,  485,   23,
 /*   780 */    12,  485,   14,   24,  485,  485,  458,  485,  485,  485,
 /*   790 */   485,  485,   36,   31,   33,   32,   26,   35,   34,   25,
 /*   800 */    27,   30,   29,   28,  485,   53,   55,   49,   51,   83,
 /*   810 */    69,   69,   57,  485,  485,  130,  485,  485,   69,  485,
 /*   820 */    69,   69,   69,  485,   59,  485,  485,  463,  464,  485,
 /*   830 */   436,   61,  485,   23,  470,  485,   14,  137,  434,  434,
 /*   840 */   485,  485,  460,  485,  485,  462,  434,  469,  434,  434,
 /*   850 */   434,  485,  485,  485,  485,  461,  485,  485,  485,   53,
 /*   860 */    55,   49,   51,  485,  485,  134,   57,  485,   73,   69,
 /*   870 */    69,  485,  485,  134,  485,  134,  485,   69,   59,   69,
 /*   880 */    69,   69,  485,  485,  485,  485,  485,  485,  470,   10,
 /*   890 */    10,  137,   38,   73,   69,   69,  460,  485,  485,  462,
 /*   900 */    10,  469,   69,  485,   69,   69,   69,  485,  485,  461,
 /*   910 */   485,  485,  485,   43,   42,  416,  417,  485,  485,  485,
 /*   920 */   485,   39,   41,   40,  485,  485,  485,  485,  485,   60,
 /*   930 */    58,   56,  485,  485,  389,  485,  485,   73,   69,   69,
 /*   940 */   485,  485,  485,  485,  389,   38,   69,  485,   69,   69,
 /*   950 */    69,  485,   83,   69,   69,  485,  485,  485,  131,  485,
 /*   960 */   485,   69,  485,   69,   69,   69,   43,   42,  416,  417,
 /*   970 */    70,   69,   69,  485,   39,   41,   40,  485,  485,   69,
 /*   980 */   485,   69,   69,   69,  485,   80,   69,   69,  485,  485,
 /*   990 */    82,   69,   69,  485,   69,  485,   69,   69,   69,   69,
 /*  1000 */   485,   69,   69,   69,   71,   69,   69,  485,  485,   72,
 /*  1010 */    69,   69,  485,   69,  485,   69,   69,   69,   69,  485,
 /*  1020 */    69,   69,   69,   74,   69,   69,  485,  485,  485,  485,
 /*  1030 */   485,  485,   69,  485,   69,   69,   69,  485,  485,   79,
 /*  1040 */    69,   69,  485,  485,   85,   69,   69,  485,   69,  485,
 /*  1050 */    69,   69,   69,   69,  485,   69,   69,   69,   86,   69,
 /*  1060 */    69,  485,  485,   87,   69,   69,  485,   69,  485,   69,
 /*  1070 */    69,   69,   69,  485,   69,   69,   69,   88,   69,   69,
 /*  1080 */   485,  485,   89,   69,   69,  485,   69,  485,   69,   69,
 /*  1090 */    69,   69,  485,   69,   69,   69,   90,   69,   69,  485,
 /*  1100 */   485,   91,   69,   69,  485,   69,  485,   69,   69,   69,
 /*  1110 */    69,  485,   69,   69,   69,   92,   69,   69,  485,  485,
 /*  1120 */    93,   69,   69,  485,   69,  485,   69,   69,   69,   69,
 /*  1130 */   485,   69,   69,   69,   94,   69,   69,  485,  485,  485,
 /*  1140 */   485,  485,  485,   69,  485,   69,   69,   69,  485,   95,
 /*  1150 */    69,   69,  485,  485,   96,   69,   69,  485,   69,  485,
 /*  1160 */    69,   69,   69,   69,  485,   69,   69,   69,   97,   69,
 /*  1170 */    69,  485,  485,  485,  109,  109,  485,   69,  485,   69,
 /*  1180 */    69,   69,  109,  485,  109,  109,  109,  110,  110,  485,
 /*  1190 */   485,  485,  485,  111,  111,  110,  485,  110,  110,  110,
 /*  1200 */   485,  111,  485,  111,  111,  111,  105,  105,  485,  485,
 /*  1210 */   485,  485,  106,  106,  105,  485,  105,  105,  105,  485,
 /*  1220 */   106,  485,  106,  106,  106,   75,   75,  485,  485,  485,
 /*  1230 */   485,   76,   76,   75,  485,   75,   75,   75,  485,   76,
 /*  1240 */   485,   76,   76,   76,   77,   77,  485,  485,  485,  485,
 /*  1250 */   485,  485,   77,  485,   77,   77,   77,   78,   78,  485,
 /*  1260 */   485,  485,  101,  101,  485,   78,  485,   78,   78,   78,
 /*  1270 */   101,  485,  101,  101,  101,  485,  112,  112,  485,  485,
 /*  1280 */   485,  100,  100,  485,  112,  485,  112,  112,  112,  100,
 /*  1290 */   485,  100,  100,  100,  485,  113,  113,  485,  485,  485,
 /*  1300 */   485,  485,  485,  113,  485,  113,  113,  113,   99,   99,
 /*  1310 */   485,  485,  485,  485,  107,  107,   99,  485,   99,   99,
 /*  1320 */    99,  485,  107,  485,  107,  107,  107,   98,   98,  485,
 /*  1330 */   485,  485,  485,  108,  108,   98,  485,   98,   98,   98,
 /*  1340 */   485,  108,  485,  108,  108,  108,  104,  104,  485,  485,
 /*  1350 */   485,  485,  114,  114,  104,  485,  104,  104,  104,  485,
 /*  1360 */   114,  485,  114,  114,  114,  103,  103,  485,  485,  485,
 /*  1370 */   485,  485,  485,  103,   38,  103,  103,  103,  115,  115,
 /*  1380 */   485,  485,  485,  102,  102,  485,  115,  485,  115,  115,
 /*  1390 */   115,  102,  485,  102,  102,  102,  485,  416,  417,  485,
 /*  1400 */   485,  485,  485,   39,   41,   40,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    20 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*    30 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*    40 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    50 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
 /*    60 */    61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*    70 */    71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*    80 */    81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
 /*    90 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   100 */     2,    3,    7,    5,    6,   10,    8,   13,    5,   11,
 /*   110 */    16,   17,   18,   19,  109,  110,  111,  112,  113,    2,
 /*   120 */     3,  104,    5,  118,    5,  120,  121,  122,   34,   35,
 /*   130 */    36,   37,   34,   35,   36,   37,   42,   43,   44,   41,
 /*   140 */    46,   47,   48,   49,   50,   51,   52,  109,  110,  111,
 /*   150 */   119,   53,   13,  115,  124,  125,  118,   10,  120,  121,
 /*   160 */   122,   63,   15,   65,   66,   67,  123,  124,  125,   71,
 /*   170 */    72,  117,   74,  119,   76,   36,   37,  108,  117,   81,
 /*   180 */   119,   83,   84,   14,    2,    3,   14,    5,    6,    7,
 /*   190 */     8,    8,   14,   11,   11,  107,  108,    8,   15,  101,
 /*   200 */     9,   10,   14,   20,   21,   22,   23,   24,   25,   26,
 /*   210 */    27,   28,   29,   30,   31,    6,   34,   35,   36,   37,
 /*   220 */   109,  110,  111,   41,  113,  109,  110,  111,   10,  118,
 /*   230 */    12,  120,  121,  122,  118,   53,  120,  121,  122,    9,
 /*   240 */    10,    5,  126,    9,    8,   63,   15,   65,   66,   67,
 /*   250 */     9,   10,   15,   71,   72,    8,   74,    8,   76,   62,
 /*   260 */     8,    6,    8,   81,   20,   83,   84,  127,    2,    3,
 /*   270 */     0,    5,    6,    7,    8,    8,    9,   11,   11,  127,
 /*   280 */   127,  127,  127,  127,  127,  127,  127,   20,   21,   22,
 /*   290 */    23,   24,   25,   26,   27,   28,   29,   30,   31,  127,
 /*   300 */    34,   35,   36,   37,  127,  105,  106,   41,  127,  109,
 /*   310 */   110,  111,  127,  127,  127,  127,  116,  127,  118,   53,
 /*   320 */   120,  121,  122,  123,  124,  125,  127,  127,  127,   63,
 /*   330 */   127,   65,   66,   67,  127,  127,  127,   71,   72,  127,
 /*   340 */    74,  127,   76,  127,  127,  127,  127,   81,  127,   83,
 /*   350 */    84,  127,    2,    3,  127,    5,    6,    7,    8,    8,
 /*   360 */     9,   11,   11,  127,  127,  127,  127,  127,  127,  127,
 /*   370 */   127,   20,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   380 */    29,   30,   31,  127,   34,   35,   36,   37,  127,  127,
 /*   390 */   127,   41,  103,  127,  105,  106,  127,  127,  109,  110,
 /*   400 */   111,  127,  127,   53,  127,  116,  127,  118,  127,  120,
 /*   410 */   121,  122,  127,   63,  127,   65,   66,   67,  127,  127,
 /*   420 */   127,   71,   72,  127,   74,  127,   76,  127,  127,  127,
 /*   430 */   127,   81,  127,   83,   84,    0,  127,    2,    3,  127,
 /*   440 */     5,    6,    8,    8,  127,   11,   11,  127,  127,   15,
 /*   450 */   127,  127,  127,  127,   20,   21,   22,   23,   24,   25,
 /*   460 */    26,   27,   28,   29,   30,   31,  127,  127,  127,   34,
 /*   470 */    35,   36,   37,  127,  127,  127,   41,  127,  105,  106,
 /*   480 */   127,  127,  109,  110,  111,  127,  127,  127,   53,  116,
 /*   490 */   127,  118,  127,  120,  121,  122,  127,  127,   63,  127,
 /*   500 */    65,   66,   67,  127,  127,  127,   71,   72,  127,   74,
 /*   510 */   127,   76,  127,  127,  127,  127,   81,  127,   83,   84,
 /*   520 */   127,    2,    3,  127,    5,    6,  127,    8,    8,    9,
 /*   530 */    11,   11,  127,  127,  127,  127,  127,  127,  127,  127,
 /*   540 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   550 */    30,   31,  127,   34,   35,   36,   37,  127,  127,  127,
 /*   560 */    41,  106,  127,  127,  109,  110,  111,  127,  127,  114,
 /*   570 */   127,  116,   53,  118,  127,  120,  121,  122,  127,  127,
 /*   580 */   127,  127,   63,  127,   65,   66,   67,  127,  127,  127,
 /*   590 */    71,   72,  127,   74,  127,   76,   13,  127,  127,  127,
 /*   600 */    81,  127,   83,   84,  127,    2,    3,  127,    5,    6,
 /*   610 */   127,    8,  127,  127,   11,  127,  127,   34,   35,   36,
 /*   620 */    37,  127,  127,  127,  127,   42,   43,   44,  127,   46,
 /*   630 */    47,   48,   49,   50,   51,   52,  127,   34,   35,   36,
 /*   640 */    37,  127,  127,  127,   41,  127,  127,  106,  127,  127,
 /*   650 */   109,  110,  111,  127,  127,  114,   53,  116,  127,  118,
 /*   660 */   127,  120,  121,  122,  127,  127,   63,  127,   65,   66,
 /*   670 */    67,  127,  127,  127,   71,   72,  127,   74,  127,   76,
 /*   680 */   127,  127,  127,  127,   81,  127,   83,   84,  127,    2,
 /*   690 */     3,  127,    5,    6,  127,    8,    8,  127,   11,   11,
 /*   700 */    12,  127,  127,  127,  127,  127,  127,  127,   20,   21,
 /*   710 */    22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
 /*   720 */   127,   34,   35,   36,   37,  127,  127,  106,   41,  127,
 /*   730 */   109,  110,  111,  127,  127,  114,  127,  116,  127,  118,
 /*   740 */    53,  120,  121,  122,  127,  127,  127,  127,  127,  127,
 /*   750 */    63,  127,   65,   66,   67,  127,  127,  127,   71,   72,
 /*   760 */   127,   74,  127,   76,  127,  127,  127,  127,   81,  127,
 /*   770 */    83,   84,  127,    2,    3,  127,    5,    6,  127,    8,
 /*   780 */     8,  127,   11,   11,  127,  127,   15,  127,  127,  127,
 /*   790 */   127,  127,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   800 */    28,   29,   30,   31,  127,   34,   35,   36,   37,  109,
 /*   810 */   110,  111,   41,  127,  127,  115,  127,  127,  118,  127,
 /*   820 */   120,  121,  122,  127,   53,  127,  127,    2,    3,  127,
 /*   830 */     5,    6,  127,    8,   63,  127,   11,   66,  110,  111,
 /*   840 */   127,  127,   71,  127,  127,   74,  118,   76,  120,  121,
 /*   850 */   122,  127,  127,  127,  127,   84,  127,  127,  127,   34,
 /*   860 */    35,   36,   37,  127,  127,  106,   41,  127,  109,  110,
 /*   870 */   111,  127,  127,  114,  127,  116,  127,  118,   53,  120,
 /*   880 */   121,  122,  127,  127,  127,  127,  127,  127,   63,  105,
 /*   890 */   106,   66,   13,  109,  110,  111,   71,  127,  127,   74,
 /*   900 */   116,   76,  118,  127,  120,  121,  122,  127,  127,   84,
 /*   910 */   127,  127,  127,   34,   35,   36,   37,  127,  127,  127,
 /*   920 */   127,   42,   43,   44,  127,  127,  127,  127,  127,   50,
 /*   930 */    51,   52,  127,  127,  106,  127,  127,  109,  110,  111,
 /*   940 */   127,  127,  127,  127,  116,   13,  118,  127,  120,  121,
 /*   950 */   122,  127,  109,  110,  111,  127,  127,  127,  115,  127,
 /*   960 */   127,  118,  127,  120,  121,  122,   34,   35,   36,   37,
 /*   970 */   109,  110,  111,  127,   42,   43,   44,  127,  127,  118,
 /*   980 */   127,  120,  121,  122,  127,  109,  110,  111,  127,  127,
 /*   990 */   109,  110,  111,  127,  118,  127,  120,  121,  122,  118,
 /*  1000 */   127,  120,  121,  122,  109,  110,  111,  127,  127,  109,
 /*  1010 */   110,  111,  127,  118,  127,  120,  121,  122,  118,  127,
 /*  1020 */   120,  121,  122,  109,  110,  111,  127,  127,  127,  127,
 /*  1030 */   127,  127,  118,  127,  120,  121,  122,  127,  127,  109,
 /*  1040 */   110,  111,  127,  127,  109,  110,  111,  127,  118,  127,
 /*  1050 */   120,  121,  122,  118,  127,  120,  121,  122,  109,  110,
 /*  1060 */   111,  127,  127,  109,  110,  111,  127,  118,  127,  120,
 /*  1070 */   121,  122,  118,  127,  120,  121,  122,  109,  110,  111,
 /*  1080 */   127,  127,  109,  110,  111,  127,  118,  127,  120,  121,
 /*  1090 */   122,  118,  127,  120,  121,  122,  109,  110,  111,  127,
 /*  1100 */   127,  109,  110,  111,  127,  118,  127,  120,  121,  122,
 /*  1110 */   118,  127,  120,  121,  122,  109,  110,  111,  127,  127,
 /*  1120 */   109,  110,  111,  127,  118,  127,  120,  121,  122,  118,
 /*  1130 */   127,  120,  121,  122,  109,  110,  111,  127,  127,  127,
 /*  1140 */   127,  127,  127,  118,  127,  120,  121,  122,  127,  109,
 /*  1150 */   110,  111,  127,  127,  109,  110,  111,  127,  118,  127,
 /*  1160 */   120,  121,  122,  118,  127,  120,  121,  122,  109,  110,
 /*  1170 */   111,  127,  127,  127,  110,  111,  127,  118,  127,  120,
 /*  1180 */   121,  122,  118,  127,  120,  121,  122,  110,  111,  127,
 /*  1190 */   127,  127,  127,  110,  111,  118,  127,  120,  121,  122,
 /*  1200 */   127,  118,  127,  120,  121,  122,  110,  111,  127,  127,
 /*  1210 */   127,  127,  110,  111,  118,  127,  120,  121,  122,  127,
 /*  1220 */   118,  127,  120,  121,  122,  110,  111,  127,  127,  127,
 /*  1230 */   127,  110,  111,  118,  127,  120,  121,  122,  127,  118,
 /*  1240 */   127,  120,  121,  122,  110,  111,  127,  127,  127,  127,
 /*  1250 */   127,  127,  118,  127,  120,  121,  122,  110,  111,  127,
 /*  1260 */   127,  127,  110,  111,  127,  118,  127,  120,  121,  122,
 /*  1270 */   118,  127,  120,  121,  122,  127,  110,  111,  127,  127,
 /*  1280 */   127,  110,  111,  127,  118,  127,  120,  121,  122,  118,
 /*  1290 */   127,  120,  121,  122,  127,  110,  111,  127,  127,  127,
 /*  1300 */   127,  127,  127,  118,  127,  120,  121,  122,  110,  111,
 /*  1310 */   127,  127,  127,  127,  110,  111,  118,  127,  120,  121,
 /*  1320 */   122,  127,  118,  127,  120,  121,  122,  110,  111,  127,
 /*  1330 */   127,  127,  127,  110,  111,  118,  127,  120,  121,  122,
 /*  1340 */   127,  118,  127,  120,  121,  122,  110,  111,  127,  127,
 /*  1350 */   127,  127,  110,  111,  118,  127,  120,  121,  122,  127,
 /*  1360 */   118,  127,  120,  121,  122,  110,  111,  127,  127,  127,
 /*  1370 */   127,  127,  127,  118,   13,  120,  121,  122,  110,  111,
 /*  1380 */   127,  127,  127,  110,  111,  127,  118,  127,  120,  121,
 /*  1390 */   122,  118,  127,  120,  121,  122,  127,   36,   37,  127,
 /*  1400 */   127,  127,  127,   42,   43,   44,
};
#define YY_SHIFT_USE_DFLT (1406)
#define YY_SHIFT_COUNT    (139)
#define YY_SHIFT_MIN      (-1)
#define YY_SHIFT_MAX      (1361)
static const short yy_shift_ofst[] = {
 /*     0 */    98,  519,  603,  687,  687,  687,  687,  603,  182,  266,
 /*    10 */   350,  435,  825,  825,  825,  825,  825,  825,  771,  825,
 /*    20 */   825,  825,  825,  825,  825,  825,  825,  825,  825,  825,
 /*    30 */   825,  825,  825,  825,  825,  825,  825,  825,  825,  825,
 /*    40 */   825,  825,  825,  825,  825,  825,  825,  825,  825,  825,
 /*    50 */   825,  825,  825,  825,  825,  825,  825,  825,  825,  825,
 /*    60 */   825,  117,  117,  103,  103,  119,   -1,  103,  119,   94,
 /*    70 */   183,  267,  351,  434,  520,  583,  583,  583,  583,  688,
 /*    80 */   772,  772,  772,  772,  772,  772,  772,  772,  772,  772,
 /*    90 */   772,  772,  772,  772,  772,  772,  772,  772,  879,  879,
 /*   100 */   879,  879,  932,  932,  932, 1361, 1361, 1361, 1361,  139,
 /*   110 */   139,  139,  139,  139,  139,  139,  191,  218,   95,  230,
 /*   120 */   236,  241,  147,  169,  172,  178,  188,  209,  189,  234,
 /*   130 */   231,  237,  247,  249,  197,  252,  255,  254,  244,  270,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (68)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (1273)
static const short yy_reduce_ofst[] = {
 /*     0 */   289,  200,  373,  455,  541,  621,  759,  784,  828,  828,
 /*    10 */   828,  828,    5,  111,  116,   38,  700,  843,  861,  876,
 /*    20 */   881,  895,  900,  914,  930,  935,  949,  954,  968,  973,
 /*    30 */   987,  992, 1006, 1011, 1025, 1040, 1045, 1059,  728, 1064,
 /*    40 */  1077, 1083, 1096, 1102, 1115, 1121, 1134, 1147, 1152, 1166,
 /*    50 */  1171, 1185, 1198, 1204, 1217, 1223, 1236, 1242, 1255, 1268,
 /*    60 */  1273,   43,   30,   54,   61,   88,   17,   31,   69,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   679,  670,  679,  679,  679,  679,  679,  679,  679,  679,
 /*    10 */   679,  679,  638,  638,  678,  644,  644,  644,  679,  679,
 /*    20 */   679,  679,  679,  679,  679,  679,  679,  679,  679,  679,
 /*    30 */   679,  679,  679,  679,  679,  679,  679,  679,  679,  679,
 /*    40 */   679,  679,  679,  679,  679,  679,  679,  679,  679,  679,
 /*    50 */   679,  679,  679,  679,  679,  679,  679,  679,  679,  679,
 /*    60 */   679,  670,  679,  679,  679,  679,  679,  679,  679,  605,
 /*    70 */   679,  679,  679,  679,  679,  624,  623,  622,  621,  679,
 /*    80 */   676,  677,  671,  645,  637,  604,  603,  602,  601,  600,
 /*    90 */   599,  598,  597,  596,  595,  594,  593,  590,  617,  618,
 /*   100 */   619,  620,  614,  615,  616,  626,  625,  609,  608,  629,
 /*   110 */   628,  627,  611,  610,  607,  606,  679,  679,  679,  679,
 /*   120 */   679,  679,  679,  660,  659,  632,  679,  679,  679,  679,
 /*   130 */   679,  679,  679,  679,  640,  679,  679,  679,  591,  679,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  mjsParserARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void mjsParserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "END_OF_INPUT",  "NUMBER",        "STRING_LITERAL",
  "REGEX_LITERAL",  "IDENTIFIER",    "OPEN_CURLY",    "CLOSE_CURLY", 
  "OPEN_PAREN",    "CLOSE_PAREN",   "COMMA",         "OPEN_BRACKET",
  "CLOSE_BRACKET",  "DOT",           "COLON",         "SEMICOLON",   
  "EQ",            "EQ_EQ",         "NE",            "NE_NE",       
  "ASSIGN",        "REM_ASSIGN",    "MUL_ASSIGN",    "DIV_ASSIGN",  
  "XOR_ASSIGN",    "PLUS_ASSIGN",   "MINUS_ASSIGN",  "OR_ASSIGN",   
  "AND_ASSIGN",    "LSHIFT_ASSIGN",  "RSHIFT_ASSIGN",  "URSHIFT_ASSIGN",
  "AND",           "LOGICAL_OR",    "PLUS",          "MINUS",       
  "PLUS_PLUS",     "MINUS_MINUS",   "LOGICAL_AND",   "OR",          
  "QUESTION",      "TILDA",         "REM",           "MUL",         
  "DIV",           "XOR",           "LE",            "LT",          
  "GE",            "GT",            "LSHIFT",        "RSHIFT",      
  "URSHIFT",       "NOT",           "BREAK",         "CASE",        
  "CATCH",         "CONTINUE",      "DEBUGGER",      "DEFAULT",     
  "DELETE",        "DO",            "ELSE",          "FALSE",       
  "FINALLY",       "FOR",           "FUNCTION",      "IF",          
  "IN",            "INSTANCEOF",    "NEW",           "NULL",        
  "RETURN",        "SWITCH",        "THIS",          "THROW",       
  "TRUE",          "TRY",           "TYPEOF",        "VAR",         
  "VOID",          "WHILE",         "WITH",          "LET",         
  "UNDEFINED",     "CLASS",         "ENUM",          "EXTENDS",     
  "SUPER",         "CONST",         "EXPORT",        "IMPORT",      
  "IMPLEMENTS",    "PRIVATE",       "PUBLIC",        "INTERFACE",   
  "PACKAGE",       "PROTECTED",     "STATIC",        "YIELD",       
  "THEN",          "NUM_TOKENS",    "error",         "program",     
  "dummy",         "stmtlist",      "stmt",          "letspecs",    
  "letspec",       "expr",          "sexp",          "literal",     
  "callarglist",   "callarg",       "block",         "optexpr",     
  "funcdecl",      "arglist",       "func_literal",  "argspec",     
  "boolean_literal",  "object_literal",  "array_literal",  "objspeclist", 
  "objspec",       "objspeclhs",    "arrayspeclist",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= stmtlist",
 /*   1 */ "dummy ::= END_OF_INPUT",
 /*   2 */ "dummy ::= NUMBER",
 /*   3 */ "dummy ::= STRING_LITERAL",
 /*   4 */ "dummy ::= REGEX_LITERAL",
 /*   5 */ "dummy ::= IDENTIFIER",
 /*   6 */ "dummy ::= OPEN_CURLY",
 /*   7 */ "dummy ::= CLOSE_CURLY",
 /*   8 */ "dummy ::= OPEN_PAREN",
 /*   9 */ "dummy ::= CLOSE_PAREN",
 /*  10 */ "dummy ::= COMMA",
 /*  11 */ "dummy ::= OPEN_BRACKET",
 /*  12 */ "dummy ::= CLOSE_BRACKET",
 /*  13 */ "dummy ::= DOT",
 /*  14 */ "dummy ::= COLON",
 /*  15 */ "dummy ::= SEMICOLON",
 /*  16 */ "dummy ::= EQ",
 /*  17 */ "dummy ::= EQ_EQ",
 /*  18 */ "dummy ::= NE",
 /*  19 */ "dummy ::= NE_NE",
 /*  20 */ "dummy ::= ASSIGN",
 /*  21 */ "dummy ::= REM_ASSIGN",
 /*  22 */ "dummy ::= MUL_ASSIGN",
 /*  23 */ "dummy ::= DIV_ASSIGN",
 /*  24 */ "dummy ::= XOR_ASSIGN",
 /*  25 */ "dummy ::= PLUS_ASSIGN",
 /*  26 */ "dummy ::= MINUS_ASSIGN",
 /*  27 */ "dummy ::= OR_ASSIGN",
 /*  28 */ "dummy ::= AND_ASSIGN",
 /*  29 */ "dummy ::= LSHIFT_ASSIGN",
 /*  30 */ "dummy ::= RSHIFT_ASSIGN",
 /*  31 */ "dummy ::= URSHIFT_ASSIGN",
 /*  32 */ "dummy ::= AND",
 /*  33 */ "dummy ::= LOGICAL_OR",
 /*  34 */ "dummy ::= PLUS",
 /*  35 */ "dummy ::= MINUS",
 /*  36 */ "dummy ::= PLUS_PLUS",
 /*  37 */ "dummy ::= MINUS_MINUS",
 /*  38 */ "dummy ::= LOGICAL_AND",
 /*  39 */ "dummy ::= OR",
 /*  40 */ "dummy ::= QUESTION",
 /*  41 */ "dummy ::= TILDA",
 /*  42 */ "dummy ::= REM",
 /*  43 */ "dummy ::= MUL",
 /*  44 */ "dummy ::= DIV",
 /*  45 */ "dummy ::= XOR",
 /*  46 */ "dummy ::= LE",
 /*  47 */ "dummy ::= LT",
 /*  48 */ "dummy ::= GE",
 /*  49 */ "dummy ::= GT",
 /*  50 */ "dummy ::= LSHIFT",
 /*  51 */ "dummy ::= RSHIFT",
 /*  52 */ "dummy ::= URSHIFT",
 /*  53 */ "dummy ::= NOT",
 /*  54 */ "dummy ::= BREAK",
 /*  55 */ "dummy ::= CASE",
 /*  56 */ "dummy ::= CATCH",
 /*  57 */ "dummy ::= CONTINUE",
 /*  58 */ "dummy ::= DEBUGGER",
 /*  59 */ "dummy ::= DEFAULT",
 /*  60 */ "dummy ::= DELETE",
 /*  61 */ "dummy ::= DO",
 /*  62 */ "dummy ::= ELSE",
 /*  63 */ "dummy ::= FALSE",
 /*  64 */ "dummy ::= FINALLY",
 /*  65 */ "dummy ::= FOR",
 /*  66 */ "dummy ::= FUNCTION",
 /*  67 */ "dummy ::= IF",
 /*  68 */ "dummy ::= IN",
 /*  69 */ "dummy ::= INSTANCEOF",
 /*  70 */ "dummy ::= NEW",
 /*  71 */ "dummy ::= NULL",
 /*  72 */ "dummy ::= RETURN",
 /*  73 */ "dummy ::= SWITCH",
 /*  74 */ "dummy ::= THIS",
 /*  75 */ "dummy ::= THROW",
 /*  76 */ "dummy ::= TRUE",
 /*  77 */ "dummy ::= TRY",
 /*  78 */ "dummy ::= TYPEOF",
 /*  79 */ "dummy ::= VAR",
 /*  80 */ "dummy ::= VOID",
 /*  81 */ "dummy ::= WHILE",
 /*  82 */ "dummy ::= WITH",
 /*  83 */ "dummy ::= LET",
 /*  84 */ "dummy ::= UNDEFINED",
 /*  85 */ "dummy ::= CLASS",
 /*  86 */ "dummy ::= ENUM",
 /*  87 */ "dummy ::= EXTENDS",
 /*  88 */ "dummy ::= SUPER",
 /*  89 */ "dummy ::= CONST",
 /*  90 */ "dummy ::= EXPORT",
 /*  91 */ "dummy ::= IMPORT",
 /*  92 */ "dummy ::= IMPLEMENTS",
 /*  93 */ "dummy ::= PRIVATE",
 /*  94 */ "dummy ::= PUBLIC",
 /*  95 */ "dummy ::= INTERFACE",
 /*  96 */ "dummy ::= PACKAGE",
 /*  97 */ "dummy ::= PROTECTED",
 /*  98 */ "dummy ::= STATIC",
 /*  99 */ "dummy ::= YIELD",
 /* 100 */ "dummy ::= THEN",
 /* 101 */ "program ::= NUM_TOKENS dummy",
 /* 102 */ "stmtlist ::= stmtlist stmt",
 /* 103 */ "stmtlist ::= stmt",
 /* 104 */ "stmt ::= LET letspecs SEMICOLON",
 /* 105 */ "letspecs ::= letspecs COMMA letspec",
 /* 106 */ "letspecs ::= letspec",
 /* 107 */ "letspec ::= IDENTIFIER ASSIGN expr",
 /* 108 */ "letspec ::= IDENTIFIER",
 /* 109 */ "stmt ::= expr SEMICOLON",
 /* 110 */ "expr ::= expr ASSIGN expr",
 /* 111 */ "expr ::= expr PLUS_ASSIGN expr",
 /* 112 */ "expr ::= expr MINUS_ASSIGN expr",
 /* 113 */ "expr ::= expr MUL_ASSIGN expr",
 /* 114 */ "expr ::= expr DIV_ASSIGN expr",
 /* 115 */ "expr ::= expr REM_ASSIGN expr",
 /* 116 */ "expr ::= expr LSHIFT_ASSIGN expr",
 /* 117 */ "expr ::= expr RSHIFT_ASSIGN expr",
 /* 118 */ "expr ::= expr URSHIFT_ASSIGN expr",
 /* 119 */ "expr ::= expr AND_ASSIGN expr",
 /* 120 */ "expr ::= expr XOR_ASSIGN expr",
 /* 121 */ "expr ::= expr OR_ASSIGN expr",
 /* 122 */ "expr ::= sexp",
 /* 123 */ "sexp ::= NOT sexp",
 /* 124 */ "sexp ::= TILDA sexp",
 /* 125 */ "sexp ::= MINUS sexp",
 /* 126 */ "sexp ::= PLUS sexp",
 /* 127 */ "sexp ::= MINUS_MINUS sexp",
 /* 128 */ "sexp ::= PLUS_PLUS sexp",
 /* 129 */ "sexp ::= sexp PLUS_PLUS",
 /* 130 */ "sexp ::= sexp MINUS_MINUS",
 /* 131 */ "sexp ::= sexp LSHIFT sexp",
 /* 132 */ "sexp ::= sexp RSHIFT sexp",
 /* 133 */ "sexp ::= sexp URSHIFT sexp",
 /* 134 */ "sexp ::= sexp LE sexp",
 /* 135 */ "sexp ::= sexp LT sexp",
 /* 136 */ "sexp ::= sexp GE sexp",
 /* 137 */ "sexp ::= sexp GT sexp",
 /* 138 */ "sexp ::= sexp EQ sexp",
 /* 139 */ "sexp ::= sexp NE sexp",
 /* 140 */ "sexp ::= sexp EQ_EQ sexp",
 /* 141 */ "sexp ::= sexp NE_NE sexp",
 /* 142 */ "sexp ::= sexp PLUS sexp",
 /* 143 */ "sexp ::= sexp MINUS sexp",
 /* 144 */ "sexp ::= sexp MUL sexp",
 /* 145 */ "sexp ::= sexp DIV sexp",
 /* 146 */ "sexp ::= sexp REM sexp",
 /* 147 */ "sexp ::= sexp DOT sexp",
 /* 148 */ "sexp ::= OPEN_PAREN expr CLOSE_PAREN",
 /* 149 */ "sexp ::= IDENTIFIER",
 /* 150 */ "sexp ::= literal",
 /* 151 */ "expr ::= expr OPEN_PAREN callarglist CLOSE_PAREN",
 /* 152 */ "callarglist ::= callarglist COMMA callarg",
 /* 153 */ "callarglist ::= callarg",
 /* 154 */ "callarg ::= expr",
 /* 155 */ "callarg ::=",
 /* 156 */ "expr ::= expr OPEN_BRACKET expr CLOSE_BRACKET",
 /* 157 */ "stmt ::= IF OPEN_PAREN expr CLOSE_PAREN block",
 /* 158 */ "stmt ::= IF OPEN_PAREN expr CLOSE_PAREN block ELSE block",
 /* 159 */ "stmt ::= WHILE OPEN_PAREN expr CLOSE_PAREN block",
 /* 160 */ "stmt ::= FOR OPEN_PAREN optexpr SEMICOLON optexpr SEMICOLON optexpr CLOSE_PAREN block",
 /* 161 */ "optexpr ::=",
 /* 162 */ "optexpr ::= expr",
 /* 163 */ "block ::= stmt",
 /* 164 */ "block ::= OPEN_CURLY stmtlist CLOSE_CURLY",
 /* 165 */ "stmt ::= funcdecl",
 /* 166 */ "funcdecl ::= FUNCTION IDENTIFIER OPEN_PAREN arglist CLOSE_PAREN OPEN_CURLY stmtlist CLOSE_CURLY",
 /* 167 */ "func_literal ::= FUNCTION OPEN_PAREN arglist CLOSE_PAREN OPEN_CURLY stmtlist CLOSE_CURLY",
 /* 168 */ "arglist ::= arglist COMMA argspec",
 /* 169 */ "arglist ::= argspec",
 /* 170 */ "argspec ::= IDENTIFIER",
 /* 171 */ "stmt ::= RETURN SEMICOLON",
 /* 172 */ "stmt ::= RETURN expr SEMICOLON",
 /* 173 */ "literal ::= NULL",
 /* 174 */ "literal ::= UNDEFINED",
 /* 175 */ "literal ::= THIS",
 /* 176 */ "literal ::= NUMBER",
 /* 177 */ "literal ::= STRING_LITERAL",
 /* 178 */ "literal ::= boolean_literal",
 /* 179 */ "literal ::= func_literal",
 /* 180 */ "literal ::= object_literal",
 /* 181 */ "literal ::= array_literal",
 /* 182 */ "boolean_literal ::= TRUE",
 /* 183 */ "boolean_literal ::= FALSE",
 /* 184 */ "object_literal ::= OPEN_CURLY objspeclist CLOSE_CURLY",
 /* 185 */ "objspeclist ::= objspeclist COMMA objspec",
 /* 186 */ "objspeclist ::= objspec",
 /* 187 */ "objspeclist ::=",
 /* 188 */ "objspec ::= objspeclhs COLON expr",
 /* 189 */ "objspeclhs ::= IDENTIFIER",
 /* 190 */ "objspeclhs ::= STRING_LITERAL",
 /* 191 */ "objspeclhs ::= NUMBER",
 /* 192 */ "array_literal ::= OPEN_BRACKET arrayspeclist CLOSE_BRACKET",
 /* 193 */ "arrayspeclist ::= arrayspeclist COMMA expr",
 /* 194 */ "arrayspeclist ::= expr",
 /* 195 */ "arrayspeclist ::=",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to mjsParserAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to mjsParser and mjsParserFree.
*/
void *mjsParserAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( pParser ){
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yytos = NULL;
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    if( yyGrowStack(pParser) ){
      pParser->yystack = &pParser->yystk0;
      pParser->yystksz = 1;
    }
#endif
#ifndef YYNOERRORRECOVERY
    pParser->yyerrcnt = -1;
#endif
    pParser->yytos = pParser->yystack;
    pParser->yystack[0].stateno = 0;
    pParser->yystack[0].major = 0;
  }
  return pParser;
}

/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  mjsParserARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
    case 103: /* program */
{
#line 37 "mjs/mjs.lem.c"
 (void)ctx; 
#line 977 "mjs/mjs.lem.c"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void mjsParserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
#ifndef YYPARSEFREENEVERNULL
  if( pParser==0 ) return;
#endif
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int mjsParserStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static unsigned int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yytos->stateno;
 
  if( stateno>=YY_MIN_REDUCE ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
  do{
    i = yy_shift_ofst[stateno];
    assert( iLookAhead!=YYNOCODE );
    i += iLookAhead;
    if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   mjsParserARG_FETCH;
   yypParser->yytos--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
#line 32 "mjs/mjs.lem.c"

  printf("Giving up.  Parser stack overflow\n");
#line 1151 "mjs/mjs.lem.c"
/******** End %stack_overflow code ********************************************/
   mjsParserARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%sShift '%s', go to state %d\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%sShift '%s'\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major]);
    }
  }
}
#else
# define yyTraceShift(X,Y)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  mjsParserTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH] ){
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState);
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 103, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 103, 2 },
  { 105, 2 },
  { 105, 1 },
  { 106, 3 },
  { 107, 3 },
  { 107, 1 },
  { 108, 3 },
  { 108, 1 },
  { 106, 2 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 1 },
  { 110, 2 },
  { 110, 2 },
  { 110, 2 },
  { 110, 2 },
  { 110, 2 },
  { 110, 2 },
  { 110, 2 },
  { 110, 2 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 1 },
  { 110, 1 },
  { 109, 4 },
  { 112, 3 },
  { 112, 1 },
  { 113, 1 },
  { 113, 0 },
  { 109, 4 },
  { 106, 5 },
  { 106, 7 },
  { 106, 5 },
  { 106, 9 },
  { 115, 0 },
  { 115, 1 },
  { 114, 1 },
  { 114, 3 },
  { 106, 1 },
  { 116, 8 },
  { 118, 7 },
  { 117, 3 },
  { 117, 1 },
  { 119, 1 },
  { 106, 2 },
  { 106, 3 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 120, 1 },
  { 120, 1 },
  { 121, 3 },
  { 123, 3 },
  { 123, 1 },
  { 123, 0 },
  { 124, 3 },
  { 125, 1 },
  { 125, 1 },
  { 125, 1 },
  { 122, 3 },
  { 126, 3 },
  { 126, 1 },
  { 126, 0 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno        /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  mjsParserARG_FETCH;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    fprintf(yyTraceFILE, "%sReduce [%s], go to state %d.\n", yyTracePrompt,
      yyRuleName[yyruleno], yymsp[-yysize].stateno);
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH-1] ){
      yyStackOverflow(yypParser);
      return;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        return;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
      case 0: /* program ::= stmtlist */
#line 179 "mjs/mjs.lem.c"
{ ctx->state = 1; }
#line 1484 "mjs/mjs.lem.c"
        break;
      default:
      /* (1) dummy ::= END_OF_INPUT */ yytestcase(yyruleno==1);
      /* (2) dummy ::= NUMBER */ yytestcase(yyruleno==2);
      /* (3) dummy ::= STRING_LITERAL */ yytestcase(yyruleno==3);
      /* (4) dummy ::= REGEX_LITERAL */ yytestcase(yyruleno==4);
      /* (5) dummy ::= IDENTIFIER */ yytestcase(yyruleno==5);
      /* (6) dummy ::= OPEN_CURLY */ yytestcase(yyruleno==6);
      /* (7) dummy ::= CLOSE_CURLY */ yytestcase(yyruleno==7);
      /* (8) dummy ::= OPEN_PAREN */ yytestcase(yyruleno==8);
      /* (9) dummy ::= CLOSE_PAREN */ yytestcase(yyruleno==9);
      /* (10) dummy ::= COMMA */ yytestcase(yyruleno==10);
      /* (11) dummy ::= OPEN_BRACKET */ yytestcase(yyruleno==11);
      /* (12) dummy ::= CLOSE_BRACKET */ yytestcase(yyruleno==12);
      /* (13) dummy ::= DOT */ yytestcase(yyruleno==13);
      /* (14) dummy ::= COLON */ yytestcase(yyruleno==14);
      /* (15) dummy ::= SEMICOLON */ yytestcase(yyruleno==15);
      /* (16) dummy ::= EQ */ yytestcase(yyruleno==16);
      /* (17) dummy ::= EQ_EQ */ yytestcase(yyruleno==17);
      /* (18) dummy ::= NE */ yytestcase(yyruleno==18);
      /* (19) dummy ::= NE_NE */ yytestcase(yyruleno==19);
      /* (20) dummy ::= ASSIGN */ yytestcase(yyruleno==20);
      /* (21) dummy ::= REM_ASSIGN */ yytestcase(yyruleno==21);
      /* (22) dummy ::= MUL_ASSIGN */ yytestcase(yyruleno==22);
      /* (23) dummy ::= DIV_ASSIGN */ yytestcase(yyruleno==23);
      /* (24) dummy ::= XOR_ASSIGN */ yytestcase(yyruleno==24);
      /* (25) dummy ::= PLUS_ASSIGN */ yytestcase(yyruleno==25);
      /* (26) dummy ::= MINUS_ASSIGN */ yytestcase(yyruleno==26);
      /* (27) dummy ::= OR_ASSIGN */ yytestcase(yyruleno==27);
      /* (28) dummy ::= AND_ASSIGN */ yytestcase(yyruleno==28);
      /* (29) dummy ::= LSHIFT_ASSIGN */ yytestcase(yyruleno==29);
      /* (30) dummy ::= RSHIFT_ASSIGN */ yytestcase(yyruleno==30);
      /* (31) dummy ::= URSHIFT_ASSIGN */ yytestcase(yyruleno==31);
      /* (32) dummy ::= AND */ yytestcase(yyruleno==32);
      /* (33) dummy ::= LOGICAL_OR */ yytestcase(yyruleno==33);
      /* (34) dummy ::= PLUS */ yytestcase(yyruleno==34);
      /* (35) dummy ::= MINUS */ yytestcase(yyruleno==35);
      /* (36) dummy ::= PLUS_PLUS */ yytestcase(yyruleno==36);
      /* (37) dummy ::= MINUS_MINUS */ yytestcase(yyruleno==37);
      /* (38) dummy ::= LOGICAL_AND */ yytestcase(yyruleno==38);
      /* (39) dummy ::= OR */ yytestcase(yyruleno==39);
      /* (40) dummy ::= QUESTION */ yytestcase(yyruleno==40);
      /* (41) dummy ::= TILDA */ yytestcase(yyruleno==41);
      /* (42) dummy ::= REM */ yytestcase(yyruleno==42);
      /* (43) dummy ::= MUL */ yytestcase(yyruleno==43);
      /* (44) dummy ::= DIV */ yytestcase(yyruleno==44);
      /* (45) dummy ::= XOR */ yytestcase(yyruleno==45);
      /* (46) dummy ::= LE */ yytestcase(yyruleno==46);
      /* (47) dummy ::= LT */ yytestcase(yyruleno==47);
      /* (48) dummy ::= GE */ yytestcase(yyruleno==48);
      /* (49) dummy ::= GT */ yytestcase(yyruleno==49);
      /* (50) dummy ::= LSHIFT */ yytestcase(yyruleno==50);
      /* (51) dummy ::= RSHIFT */ yytestcase(yyruleno==51);
      /* (52) dummy ::= URSHIFT */ yytestcase(yyruleno==52);
      /* (53) dummy ::= NOT */ yytestcase(yyruleno==53);
      /* (54) dummy ::= BREAK */ yytestcase(yyruleno==54);
      /* (55) dummy ::= CASE */ yytestcase(yyruleno==55);
      /* (56) dummy ::= CATCH */ yytestcase(yyruleno==56);
      /* (57) dummy ::= CONTINUE */ yytestcase(yyruleno==57);
      /* (58) dummy ::= DEBUGGER */ yytestcase(yyruleno==58);
      /* (59) dummy ::= DEFAULT */ yytestcase(yyruleno==59);
      /* (60) dummy ::= DELETE */ yytestcase(yyruleno==60);
      /* (61) dummy ::= DO */ yytestcase(yyruleno==61);
      /* (62) dummy ::= ELSE */ yytestcase(yyruleno==62);
      /* (63) dummy ::= FALSE */ yytestcase(yyruleno==63);
      /* (64) dummy ::= FINALLY */ yytestcase(yyruleno==64);
      /* (65) dummy ::= FOR */ yytestcase(yyruleno==65);
      /* (66) dummy ::= FUNCTION */ yytestcase(yyruleno==66);
      /* (67) dummy ::= IF */ yytestcase(yyruleno==67);
      /* (68) dummy ::= IN */ yytestcase(yyruleno==68);
      /* (69) dummy ::= INSTANCEOF */ yytestcase(yyruleno==69);
      /* (70) dummy ::= NEW */ yytestcase(yyruleno==70);
      /* (71) dummy ::= NULL */ yytestcase(yyruleno==71);
      /* (72) dummy ::= RETURN */ yytestcase(yyruleno==72);
      /* (73) dummy ::= SWITCH */ yytestcase(yyruleno==73);
      /* (74) dummy ::= THIS */ yytestcase(yyruleno==74);
      /* (75) dummy ::= THROW */ yytestcase(yyruleno==75);
      /* (76) dummy ::= TRUE */ yytestcase(yyruleno==76);
      /* (77) dummy ::= TRY */ yytestcase(yyruleno==77);
      /* (78) dummy ::= TYPEOF */ yytestcase(yyruleno==78);
      /* (79) dummy ::= VAR */ yytestcase(yyruleno==79);
      /* (80) dummy ::= VOID */ yytestcase(yyruleno==80);
      /* (81) dummy ::= WHILE */ yytestcase(yyruleno==81);
      /* (82) dummy ::= WITH */ yytestcase(yyruleno==82);
      /* (83) dummy ::= LET */ yytestcase(yyruleno==83);
      /* (84) dummy ::= UNDEFINED */ yytestcase(yyruleno==84);
      /* (85) dummy ::= CLASS */ yytestcase(yyruleno==85);
      /* (86) dummy ::= ENUM */ yytestcase(yyruleno==86);
      /* (87) dummy ::= EXTENDS */ yytestcase(yyruleno==87);
      /* (88) dummy ::= SUPER */ yytestcase(yyruleno==88);
      /* (89) dummy ::= CONST */ yytestcase(yyruleno==89);
      /* (90) dummy ::= EXPORT */ yytestcase(yyruleno==90);
      /* (91) dummy ::= IMPORT */ yytestcase(yyruleno==91);
      /* (92) dummy ::= IMPLEMENTS */ yytestcase(yyruleno==92);
      /* (93) dummy ::= PRIVATE */ yytestcase(yyruleno==93);
      /* (94) dummy ::= PUBLIC */ yytestcase(yyruleno==94);
      /* (95) dummy ::= INTERFACE */ yytestcase(yyruleno==95);
      /* (96) dummy ::= PACKAGE */ yytestcase(yyruleno==96);
      /* (97) dummy ::= PROTECTED */ yytestcase(yyruleno==97);
      /* (98) dummy ::= STATIC */ yytestcase(yyruleno==98);
      /* (99) dummy ::= YIELD */ yytestcase(yyruleno==99);
      /* (100) dummy ::= THEN */ yytestcase(yyruleno==100);
      /* (101) program ::= NUM_TOKENS dummy */ yytestcase(yyruleno==101);
      /* (102) stmtlist ::= stmtlist stmt */ yytestcase(yyruleno==102);
      /* (103) stmtlist ::= stmt (OPTIMIZED OUT) */ assert(yyruleno!=103);
      /* (104) stmt ::= LET letspecs SEMICOLON */ yytestcase(yyruleno==104);
      /* (105) letspecs ::= letspecs COMMA letspec */ yytestcase(yyruleno==105);
      /* (106) letspecs ::= letspec (OPTIMIZED OUT) */ assert(yyruleno!=106);
      /* (107) letspec ::= IDENTIFIER ASSIGN expr */ yytestcase(yyruleno==107);
      /* (108) letspec ::= IDENTIFIER */ yytestcase(yyruleno==108);
      /* (109) stmt ::= expr SEMICOLON */ yytestcase(yyruleno==109);
      /* (110) expr ::= expr ASSIGN expr */ yytestcase(yyruleno==110);
      /* (111) expr ::= expr PLUS_ASSIGN expr */ yytestcase(yyruleno==111);
      /* (112) expr ::= expr MINUS_ASSIGN expr */ yytestcase(yyruleno==112);
      /* (113) expr ::= expr MUL_ASSIGN expr */ yytestcase(yyruleno==113);
      /* (114) expr ::= expr DIV_ASSIGN expr */ yytestcase(yyruleno==114);
      /* (115) expr ::= expr REM_ASSIGN expr */ yytestcase(yyruleno==115);
      /* (116) expr ::= expr LSHIFT_ASSIGN expr */ yytestcase(yyruleno==116);
      /* (117) expr ::= expr RSHIFT_ASSIGN expr */ yytestcase(yyruleno==117);
      /* (118) expr ::= expr URSHIFT_ASSIGN expr */ yytestcase(yyruleno==118);
      /* (119) expr ::= expr AND_ASSIGN expr */ yytestcase(yyruleno==119);
      /* (120) expr ::= expr XOR_ASSIGN expr */ yytestcase(yyruleno==120);
      /* (121) expr ::= expr OR_ASSIGN expr */ yytestcase(yyruleno==121);
      /* (122) expr ::= sexp */ yytestcase(yyruleno==122);
      /* (123) sexp ::= NOT sexp */ yytestcase(yyruleno==123);
      /* (124) sexp ::= TILDA sexp */ yytestcase(yyruleno==124);
      /* (125) sexp ::= MINUS sexp */ yytestcase(yyruleno==125);
      /* (126) sexp ::= PLUS sexp */ yytestcase(yyruleno==126);
      /* (127) sexp ::= MINUS_MINUS sexp */ yytestcase(yyruleno==127);
      /* (128) sexp ::= PLUS_PLUS sexp */ yytestcase(yyruleno==128);
      /* (129) sexp ::= sexp PLUS_PLUS */ yytestcase(yyruleno==129);
      /* (130) sexp ::= sexp MINUS_MINUS */ yytestcase(yyruleno==130);
      /* (131) sexp ::= sexp LSHIFT sexp */ yytestcase(yyruleno==131);
      /* (132) sexp ::= sexp RSHIFT sexp */ yytestcase(yyruleno==132);
      /* (133) sexp ::= sexp URSHIFT sexp */ yytestcase(yyruleno==133);
      /* (134) sexp ::= sexp LE sexp */ yytestcase(yyruleno==134);
      /* (135) sexp ::= sexp LT sexp */ yytestcase(yyruleno==135);
      /* (136) sexp ::= sexp GE sexp */ yytestcase(yyruleno==136);
      /* (137) sexp ::= sexp GT sexp */ yytestcase(yyruleno==137);
      /* (138) sexp ::= sexp EQ sexp */ yytestcase(yyruleno==138);
      /* (139) sexp ::= sexp NE sexp */ yytestcase(yyruleno==139);
      /* (140) sexp ::= sexp EQ_EQ sexp */ yytestcase(yyruleno==140);
      /* (141) sexp ::= sexp NE_NE sexp */ yytestcase(yyruleno==141);
      /* (142) sexp ::= sexp PLUS sexp */ yytestcase(yyruleno==142);
      /* (143) sexp ::= sexp MINUS sexp */ yytestcase(yyruleno==143);
      /* (144) sexp ::= sexp MUL sexp */ yytestcase(yyruleno==144);
      /* (145) sexp ::= sexp DIV sexp */ yytestcase(yyruleno==145);
      /* (146) sexp ::= sexp REM sexp */ yytestcase(yyruleno==146);
      /* (147) sexp ::= sexp DOT sexp */ yytestcase(yyruleno==147);
      /* (148) sexp ::= OPEN_PAREN expr CLOSE_PAREN */ yytestcase(yyruleno==148);
      /* (149) sexp ::= IDENTIFIER */ yytestcase(yyruleno==149);
      /* (150) sexp ::= literal (OPTIMIZED OUT) */ assert(yyruleno!=150);
      /* (151) expr ::= expr OPEN_PAREN callarglist CLOSE_PAREN */ yytestcase(yyruleno==151);
      /* (152) callarglist ::= callarglist COMMA callarg */ yytestcase(yyruleno==152);
      /* (153) callarglist ::= callarg (OPTIMIZED OUT) */ assert(yyruleno!=153);
      /* (154) callarg ::= expr */ yytestcase(yyruleno==154);
      /* (155) callarg ::= */ yytestcase(yyruleno==155);
      /* (156) expr ::= expr OPEN_BRACKET expr CLOSE_BRACKET */ yytestcase(yyruleno==156);
      /* (157) stmt ::= IF OPEN_PAREN expr CLOSE_PAREN block */ yytestcase(yyruleno==157);
      /* (158) stmt ::= IF OPEN_PAREN expr CLOSE_PAREN block ELSE block */ yytestcase(yyruleno==158);
      /* (159) stmt ::= WHILE OPEN_PAREN expr CLOSE_PAREN block */ yytestcase(yyruleno==159);
      /* (160) stmt ::= FOR OPEN_PAREN optexpr SEMICOLON optexpr SEMICOLON optexpr CLOSE_PAREN block */ yytestcase(yyruleno==160);
      /* (161) optexpr ::= */ yytestcase(yyruleno==161);
      /* (162) optexpr ::= expr */ yytestcase(yyruleno==162);
      /* (163) block ::= stmt (OPTIMIZED OUT) */ assert(yyruleno!=163);
      /* (164) block ::= OPEN_CURLY stmtlist CLOSE_CURLY */ yytestcase(yyruleno==164);
      /* (165) stmt ::= funcdecl (OPTIMIZED OUT) */ assert(yyruleno!=165);
      /* (166) funcdecl ::= FUNCTION IDENTIFIER OPEN_PAREN arglist CLOSE_PAREN OPEN_CURLY stmtlist CLOSE_CURLY */ yytestcase(yyruleno==166);
      /* (167) func_literal ::= FUNCTION OPEN_PAREN arglist CLOSE_PAREN OPEN_CURLY stmtlist CLOSE_CURLY */ yytestcase(yyruleno==167);
      /* (168) arglist ::= arglist COMMA argspec */ yytestcase(yyruleno==168);
      /* (169) arglist ::= argspec (OPTIMIZED OUT) */ assert(yyruleno!=169);
      /* (170) argspec ::= IDENTIFIER */ yytestcase(yyruleno==170);
      /* (171) stmt ::= RETURN SEMICOLON */ yytestcase(yyruleno==171);
      /* (172) stmt ::= RETURN expr SEMICOLON */ yytestcase(yyruleno==172);
      /* (173) literal ::= NULL */ yytestcase(yyruleno==173);
      /* (174) literal ::= UNDEFINED */ yytestcase(yyruleno==174);
      /* (175) literal ::= THIS */ yytestcase(yyruleno==175);
      /* (176) literal ::= NUMBER */ yytestcase(yyruleno==176);
      /* (177) literal ::= STRING_LITERAL */ yytestcase(yyruleno==177);
      /* (178) literal ::= boolean_literal (OPTIMIZED OUT) */ assert(yyruleno!=178);
      /* (179) literal ::= func_literal (OPTIMIZED OUT) */ assert(yyruleno!=179);
      /* (180) literal ::= object_literal (OPTIMIZED OUT) */ assert(yyruleno!=180);
      /* (181) literal ::= array_literal (OPTIMIZED OUT) */ assert(yyruleno!=181);
      /* (182) boolean_literal ::= TRUE */ yytestcase(yyruleno==182);
      /* (183) boolean_literal ::= FALSE */ yytestcase(yyruleno==183);
      /* (184) object_literal ::= OPEN_CURLY objspeclist CLOSE_CURLY */ yytestcase(yyruleno==184);
      /* (185) objspeclist ::= objspeclist COMMA objspec */ yytestcase(yyruleno==185);
      /* (186) objspeclist ::= objspec (OPTIMIZED OUT) */ assert(yyruleno!=186);
      /* (187) objspeclist ::= */ yytestcase(yyruleno==187);
      /* (188) objspec ::= objspeclhs COLON expr */ yytestcase(yyruleno==188);
      /* (189) objspeclhs ::= IDENTIFIER */ yytestcase(yyruleno==189);
      /* (190) objspeclhs ::= STRING_LITERAL */ yytestcase(yyruleno==190);
      /* (191) objspeclhs ::= NUMBER */ yytestcase(yyruleno==191);
      /* (192) array_literal ::= OPEN_BRACKET arrayspeclist CLOSE_BRACKET */ yytestcase(yyruleno==192);
      /* (193) arrayspeclist ::= arrayspeclist COMMA expr */ yytestcase(yyruleno==193);
      /* (194) arrayspeclist ::= expr */ yytestcase(yyruleno==194);
      /* (195) arrayspeclist ::= */ yytestcase(yyruleno==195);
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact <= YY_MAX_SHIFTREDUCE ){
    if( yyact>YY_MAX_SHIFT ){
      yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
    }
    yymsp -= yysize-1;
    yypParser->yytos = yymsp;
    yymsp->stateno = (YYACTIONTYPE)yyact;
    yymsp->major = (YYCODETYPE)yygoto;
    yyTraceShift(yypParser, yyact);
  }else{
    assert( yyact == YY_ACCEPT_ACTION );
    yypParser->yytos -= yysize;
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  mjsParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
#line 25 "mjs/mjs.lem.c"

#line 1724 "mjs/mjs.lem.c"
/************ End %parse_failure code *****************************************/
  mjsParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  mjsParserTOKENTYPE yyminor         /* The minor type of the error token */
){
  mjsParserARG_FETCH;
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 28 "mjs/mjs.lem.c"

  ctx->syntax_error = TOKEN;
#line 1744 "mjs/mjs.lem.c"
/************ End %syntax_error code ******************************************/
  mjsParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  mjsParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
#line 22 "mjs/mjs.lem.c"

#line 1770 "mjs/mjs.lem.c"
/*********** End %parse_accept code *******************************************/
  mjsParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "mjsParserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void mjsParser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  mjsParserTOKENTYPE yyminor       /* The value for the token */
  mjsParserARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  unsigned int yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  yypParser = (yyParser*)yyp;
  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif
  mjsParserARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput '%s'\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      yymajor = YYNOCODE;
    }else if( yyact <= YY_MAX_REDUCE ){
      yy_reduce(yypParser,yyact-YY_MIN_REDUCE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/froth/vm.c"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

/*
 * Froth is a simple FORTH-like language borrowing a few ideas from Factor
 * (https://factorcode.org/).
 * Froth is not a general purpose programming language but instead it is used
 * to implement the MJS virtual machine.
 *
 * The binary encoding is documented in the froth compiler (see the `fr_codegen`
 * docstring).
 */

#include <assert.h>

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "mjs/froth/vm.h" */

static void fr_init_stack(struct fr_stack *stack) {
  stack->size = FR_STACK_SIZE;
}

void fr_init_vm(struct fr_vm *vm, struct fr_code *code) {
  memset(vm, 0, sizeof(*vm));
  vm->code = code;

  fr_init_stack(&vm->dstack);
  fr_init_stack(&vm->rstack);
}

static fr_opcode_t fr_fetch(struct fr_vm *vm, fr_word_ptr_t word) {
  if (word < 0) {
    return -1;
  }
  assert((size_t) word < vm->code->opcodes_len);
  return vm->code->opcodes[word];
}

static void fr_trace(struct fr_vm *vm) {
  fr_opcode_t op = fr_fetch(vm, vm->ip);
  fr_word_ptr_t word = fr_lookup_word(vm, op);
  char sword[128], pad[64];
  const char *pos_name = "???";
  const char *name = vm->code->word_names[op + 1];

  if (word < 0) {
    fr_native_t func = vm->code->native_words[-word - 1];
    snprintf(sword, sizeof(sword), "%s <%p>", name, func);
  } else {
    snprintf(sword, sizeof(sword), "%s (%04d)", name, word);
  }

  pos_name = vm->code->pos_names[vm->ip];
  memset(pad, ' ', sizeof(pad));
  if (strlen(pos_name) <= 16) {
    pad[16 - strlen(pos_name)] = '\0';
  } else {
    pad[0] = '\0';
  }
  LOG(LL_ERROR, (">> ip:%04X (%s)%sop:%02X -> %s", vm->ip, pos_name, pad,
                 (uint8_t) op, sword));
}

void fr_enter_thread(struct fr_vm *vm, fr_word_ptr_t word) {
  fr_push(&vm->rstack, vm->ip);
  vm->ip = word;
}

void fr_enter(struct fr_vm *vm, fr_word_ptr_t word) {
  if (word < 0) {
    fr_native_t nat = vm->code->native_words[-word - 1];
    LOG(LL_DEBUG, ("calling native function %p", nat));
    nat(vm);
  } else {
    LOG(LL_DEBUG, ("%d is threaded word", word));
    fr_enter_thread(vm, word);
  }
}

void fr_run(struct fr_vm *vm, fr_word_ptr_t word) {
  fr_opcode_t op;
  vm->ip = word;

  /* push sentinel so we can exit the loop */
  fr_push(&vm->rstack, FR_EXIT_RUN);

  while (vm->ip != FR_EXIT_RUN && (size_t) vm->ip < vm->code->opcodes_len) {
    fr_trace(vm);

    op = fr_fetch(vm, vm->ip);
    vm->ip++;
    word = fr_lookup_word(vm, op);
    fr_enter(vm, word);
  }
}

fr_word_ptr_t fr_lookup_word(struct fr_vm *vm, fr_opcode_t op) {
  if (op < -1) {
    LOG(LL_ERROR, ("TODO: relative lookups not implemented yet"));
    return 0;
  } else {
    LOG(LL_DEBUG, ("looking up word_ptr for op %d", op));
    return vm->code->table[op + 1];
  }
}

void fr_push(struct fr_stack *stack, fr_cell_t value) {
  stack->stack[stack->pos] = value;
  stack->pos++;
}

fr_cell_t fr_pop(struct fr_stack *stack) {
  assert(stack->pos > 0);
  stack->pos--;
  return stack->stack[stack->pos];
}

void fr_op_todo(struct fr_vm *vm) {
  (void) vm;
  LOG(LL_ERROR, ("TODO: stub"));
}

void fr_op_quote(struct fr_vm *vm) {
  fr_cell_t lit;
  (void) vm;
  lit = fr_fetch(vm, vm->ip);
  lit <<= 8;
  lit |= fr_fetch(vm, vm->ip + 1);
  vm->ip += 2;
  LOG(LL_ERROR, ("quoting %d", lit));
  fr_push(&vm->dstack, lit);
}

void fr_op_exit(struct fr_vm *vm) {
  vm->ip = fr_pop(&vm->rstack);
}

void fr_op_drop(struct fr_vm *vm) {
  fr_pop(&vm->dstack);
}

void fr_op_dup(struct fr_vm *vm) {
  fr_cell_t v = fr_pop(&vm->dstack);
  /*
   * could be done more efficiently but this way we reuse the asserts and guards
   * in the stack primitives.
   */
  fr_push(&vm->dstack, v);
  fr_push(&vm->dstack, v);
}

void fr_op_swap(struct fr_vm *vm) {
  fr_cell_t a = fr_pop(&vm->dstack);
  fr_cell_t b = fr_pop(&vm->dstack);
  /*
   * could be done more efficiently but this way we reuse the asserts and guards
   * in the stack primitives.
   */
  fr_push(&vm->dstack, a);
  fr_push(&vm->dstack, b);
}

void fr_op_pushr(struct fr_vm *vm) {
  fr_push(&vm->rstack, fr_pop(&vm->dstack));
}

void fr_op_popr(struct fr_vm *vm) {
  fr_push(&vm->dstack, fr_pop(&vm->rstack));
}

void fr_op_print(struct fr_vm *vm) {
  fr_cell_t v = fr_pop(&vm->dstack);
  LOG(LL_ERROR, ("%d", v));
  printf("%d\n", v);
}

void fr_op_eq(struct fr_vm *vm) {
  fr_cell_t a = fr_pop(&vm->dstack);
  fr_cell_t b = fr_pop(&vm->dstack);
  fr_push(&vm->dstack, a == b ? -1 : 0);
}

void fr_op_invert(struct fr_vm *vm) {
  fr_cell_t a = fr_pop(&vm->dstack);
  fr_push(&vm->dstack, ~a);
}

void fr_op_add(struct fr_vm *vm) {
  fr_cell_t a = fr_pop(&vm->dstack);
  fr_cell_t b = fr_pop(&vm->dstack);
  fr_push(&vm->dstack, a + b);
}

void fr_op_call(struct fr_vm *vm) {
  fr_enter(vm, fr_pop(&vm->dstack));
}

void fr_op_if(struct fr_vm *vm) {
  fr_cell_t iftrue = fr_pop(&vm->dstack);
  fr_cell_t cond = fr_pop(&vm->dstack);
  if (cond) {
    fr_enter(vm, iftrue);
  }
}

void fr_op_ifelse(struct fr_vm *vm) {
  fr_cell_t iffalse = fr_pop(&vm->dstack);
  fr_cell_t iftrue = fr_pop(&vm->dstack);
  fr_cell_t cond = fr_pop(&vm->dstack);
  fr_enter(vm, (cond ? iftrue : iffalse));
}
#ifdef MG_MODULE_LINES
#line 1 "bazel-out/local-dbg-asan/genfiles/mjs/vm_bcode.c"
#endif
/* Amalgamated: #include "mjs/vm_bcode.h" */
fr_opcode_t MJS_opcodes[] = {
  /* 0000 -> : quote ... ; */
  /*           <fr_op_quote> */ 
  /* 0000 -> : exit ... ; */
  /*           <fr_op_exit> */ 
  /* 0000 -> : drop ... ; */
  /*           <fr_op_drop> */ 
  /* 0000 -> : dup ... ; */
  /*           <fr_op_dup> */ 
  /* 0000 -> : swap ... ; */
  /*           <fr_op_swap> */ 
  /* 0000 -> : >r ... ; */
  /*           <fr_op_pushr> */ 
  /* 0000 -> : r> ... ; */
  /*           <fr_op_popr> */ 
  /* 0000 -> : print ... ; */
  /*           <fr_op_print> */ 
  /* 0000 -> : = ... ; */
  /*           <fr_op_eq> */ 
  /* 0000 -> : invert ... ; */
  /*           <fr_op_invert> */ 
  /* 0000 -> : + ... ; */
  /*           <fr_op_add> */ 
  /* 0000 -> : call ... ; */
  /*           <fr_op_call> */ 
  /* 0000 -> : if ... ; */
  /*           <fr_op_if> */ 
  /* 0000 -> : ifelse ... ; */
  /*           <fr_op_ifelse> */ 
  /* 0000 -> : loop ... ; */
  MJS_OP_dup, MJS_OP_PUSHR, MJS_OP_call, MJS_OP_POPR, MJS_OP_swap, MJS_OP_quote, 0, 0, MJS_OP_if, MJS_OP_exit,
  /* 0010 -> : foo ... ; */
  MJS_OP_quote, 0, 66, MJS_OP_EQ_, MJS_OP_quote, -1, -8, MJS_OP_if, MJS_OP_exit,
  /* 0019 -> : != ... ; */
  MJS_OP_EQ_, MJS_OP_invert, MJS_OP_exit,
  /* 0022 -> : anon_0 ... ; */
  MJS_OP_quote, 0, 66, MJS_OP_foo, MJS_OP_exit,
  /* 0027 -> : anon_1 ... ; */
  MJS_OP_quote, 0, 0, MJS_OP_print, MJS_OP_exit,
  /* 0032 -> : anon_2 ... ; */
  MJS_OP_dup, MJS_OP_print, MJS_OP_quote, 0, 1, MJS_OP_NEQ_, MJS_OP_exit,
  /* 0039 -> : demo ... ; */
  MJS_OP_quote, 0, 10, MJS_OP_PUSHR, MJS_OP_quote, 0, 40, MJS_OP_quote, 0, 2, MJS_OP_ADD_, MJS_OP_POPR, MJS_OP_print, MJS_OP_quote, 0, 1, MJS_OP_quote, 0, 0, MJS_OP_EQ_, MJS_OP_invert, MJS_OP_quote, 0, 22, MJS_OP_quote, 0, 27, MJS_OP_ifelse, MJS_OP_quote, 0, 1, MJS_OP_quote, 0, 2, MJS_OP_quote, 0, 3, MJS_OP_quote, 0, 4, MJS_OP_quote, 0, 5, MJS_OP_quote, 0, 6, MJS_OP_quote, 0, 7, MJS_OP_quote, 0, 32, MJS_OP_loop, MJS_OP_exit,
};

fr_word_ptr_t MJS_word_ptrs[] = {
  /* -001 */ -1, 
  /* 0000 */ -2, 
  /* 0001 */ -3, 
  /* 0002 */ -4, 
  /* 0003 */ -5, 
  /* 0004 */ -6, 
  /* 0005 */ -7, 
  /* 0006 */ -8, 
  /* 0007 */ -9, 
  /* 0008 */ -10, 
  /* 0009 */ -11, 
  /* 0010 */ -12, 
  /* 0011 */ -13, 
  /* 0012 */ -14, 
  /* 0013 */ 0, 
  /* 0014 */ 10, 
  /* 0015 */ 19, 
  /* 0016 */ 22, 
  /* 0017 */ 27, 
  /* 0018 */ 32, 
  /* 0019 */ 39, 
};

void fr_op_quote(struct fr_vm *vm);
void fr_op_exit(struct fr_vm *vm);
void fr_op_drop(struct fr_vm *vm);
void fr_op_dup(struct fr_vm *vm);
void fr_op_swap(struct fr_vm *vm);
void fr_op_pushr(struct fr_vm *vm);
void fr_op_popr(struct fr_vm *vm);
void fr_op_print(struct fr_vm *vm);
void fr_op_eq(struct fr_vm *vm);
void fr_op_invert(struct fr_vm *vm);
void fr_op_add(struct fr_vm *vm);
void fr_op_call(struct fr_vm *vm);
void fr_op_if(struct fr_vm *vm);
void fr_op_ifelse(struct fr_vm *vm);

fr_native_t MJS_native_words[] = {
  /* -001 */ fr_op_quote,
  /* -002 */ fr_op_exit,
  /* -003 */ fr_op_drop,
  /* -004 */ fr_op_dup,
  /* -005 */ fr_op_swap,
  /* -006 */ fr_op_pushr,
  /* -007 */ fr_op_popr,
  /* -008 */ fr_op_print,
  /* -009 */ fr_op_eq,
  /* -010 */ fr_op_invert,
  /* -011 */ fr_op_add,
  /* -012 */ fr_op_call,
  /* -013 */ fr_op_if,
  /* -014 */ fr_op_ifelse,
};

const char *MJS_word_names[] = {
  /* -001 */ "quote", 
  /* 0000 */ "exit", 
  /* 0001 */ "drop", 
  /* 0002 */ "dup", 
  /* 0003 */ "swap", 
  /* 0004 */ ">r", 
  /* 0005 */ "r>", 
  /* 0006 */ "print", 
  /* 0007 */ "=", 
  /* 0008 */ "invert", 
  /* 0009 */ "+", 
  /* 0010 */ "call", 
  /* 0011 */ "if", 
  /* 0012 */ "ifelse", 
  /* 0013 */ "loop", 
  /* 0014 */ "foo", 
  /* 0015 */ "!=", 
  /* 0016 */ "anon_0", 
  /* 0017 */ "anon_1", 
  /* 0018 */ "anon_2", 
  /* 0019 */ "demo", 
};

const char *MJS_pos_names[] = {
  "loop", 
  "loop+1", 
  "loop+2", 
  "loop+3", 
  "loop+4", 
  "loop+5", 
  "loop+6", 
  "loop+7", 
  "loop+8", 
  "loop+9", 
  "foo", 
  "foo+1", 
  "foo+2", 
  "foo+3", 
  "foo+4", 
  "foo+5", 
  "foo+6", 
  "foo+7", 
  "foo+8", 
  "!=", 
  "!=+1", 
  "!=+2", 
  "anon_0", 
  "anon_0+1", 
  "anon_0+2", 
  "anon_0+3", 
  "anon_0+4", 
  "anon_1", 
  "anon_1+1", 
  "anon_1+2", 
  "anon_1+3", 
  "anon_1+4", 
  "anon_2", 
  "anon_2+1", 
  "anon_2+2", 
  "anon_2+3", 
  "anon_2+4", 
  "anon_2+5", 
  "anon_2+6", 
  "demo", 
  "demo+1", 
  "demo+2", 
  "demo+3", 
  "demo+4", 
  "demo+5", 
  "demo+6", 
  "demo+7", 
  "demo+8", 
  "demo+9", 
  "demo+10", 
  "demo+11", 
  "demo+12", 
  "demo+13", 
  "demo+14", 
  "demo+15", 
  "demo+16", 
  "demo+17", 
  "demo+18", 
  "demo+19", 
  "demo+20", 
  "demo+21", 
  "demo+22", 
  "demo+23", 
  "demo+24", 
  "demo+25", 
  "demo+26", 
  "demo+27", 
  "demo+28", 
  "demo+29", 
  "demo+30", 
  "demo+31", 
  "demo+32", 
  "demo+33", 
  "demo+34", 
  "demo+35", 
  "demo+36", 
  "demo+37", 
  "demo+38", 
  "demo+39", 
  "demo+40", 
  "demo+41", 
  "demo+42", 
  "demo+43", 
  "demo+44", 
  "demo+45", 
  "demo+46", 
  "demo+47", 
  "demo+48", 
  "demo+49", 
  "demo+50", 
  "demo+51", 
  "demo+52", 
  "demo+53", 
};

struct fr_code MJS_code = {
  MJS_opcodes, sizeof(MJS_opcodes)/sizeof(MJS_opcodes[0]),
  MJS_word_ptrs, sizeof(MJS_word_ptrs)/sizeof(MJS_word_ptrs),
  MJS_native_words, sizeof(MJS_native_words)/sizeof(MJS_native_words),
  MJS_word_names, MJS_pos_names,
};
#ifdef MG_MODULE_LINES
#line 1 "mjs/core.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "common/platform.h" */
/* Amalgamated: #include "common/str_util.h" */
/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/vm_bcode.h" */

struct mjs *mjs_create() {
  struct mjs *res = calloc(1, sizeof(*res));
  fr_init_vm(&res->vm, &MJS_code);
  return res;
}

void mjs_destroy(struct mjs *mjs) {
  free(mjs->error_msg);
  free(mjs);
}

mjs_err_t mjs_set_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  free(mjs->error_msg);
  mjs->error_msg = NULL;
  mjs->error_msg_err = err;
  mg_avprintf(&mjs->error_msg, 0, fmt, ap);
  va_end(ap);
  return err;
}

const char *mjs_strerror(struct mjs *mjs, mjs_err_t err) {
  if (mjs->error_msg_err == err) {
    return mjs->error_msg;
  }
  if (mjs->error_msg == NULL) {
    switch (err) {
      case MJS_SYNTAX_ERROR:
        return "syntax error";
      case MJS_INTERNAL_ERROR:
        return "internal error";
      default:
        return "unknown error";
    }
  }
  return "unset";
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/parser.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#include <stdio.h>
#include <string.h>

/* Amalgamated: #include "common/cs_file.h" */
/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "mjs/parser.h" */

static unsigned long mjs_get_column(const char *code, const char *pos) {
  const char *p = pos;
  while (p > code && *p != '\n') {
    p--;
  }
  return p == code ? pos - p : pos - (p + 1);
}

static int next_tok(struct mjs_parse_ctx *ctx) {
  ctx->pstate.prev_line_no = ctx->pstate.line_no;
  ctx->pstate.line_no += skip_to_next_tok(&ctx->pstate.pc, ctx->pstate.src_end);
  ctx->tok = ctx->pstate.pc;
  ctx->cur_tok = get_tok(&ctx->pstate.pc, ctx->pstate.src_end,
                         &ctx->cur_tok_dbl, ctx->cur_tok);
  ctx->tok_len = ctx->pstate.pc - ctx->tok;
  ctx->pstate.line_no += skip_to_next_tok(&ctx->pstate.pc, ctx->pstate.src_end);
  return ctx->cur_tok;
}

mjs_err_t mjs_parsen(struct mjs *mjs, const char *src, size_t len,
                     struct mjs_parse_ctx *ctx) {
  mjs_err_t err = MJS_OK;
  void *parser = mjsParserAlloc(malloc);
  struct mjs_token tok_data = {src};

  memset(ctx, 0, sizeof(*ctx));

  ctx->pstate.source_code = src;
  ctx->pstate.pc = src;
  ctx->pstate.src_end = src + len;
  ctx->pstate.line_no = 1;

  while (next_tok(ctx) != TOK_END_OF_INPUT) {
    mjs_tok_t tok = ctx->cur_tok;
    tok_data.begin = ctx->tok;
    LOG(LL_DEBUG,
        ("sending token %d '%s' state %d\n", tok, tok_data.begin, ctx->state));
    mjsParser(parser, tok, tok_data, ctx);
  }

  tok_data.begin = ctx->tok;
  mjsParser(parser, 0, tok_data, ctx);

  if (ctx->syntax_error.begin != NULL) {
    int line_len = 0;
    const char *p;
    unsigned long col = mjs_get_column(src, ctx->syntax_error.begin);

    for (p = ctx->syntax_error.begin - col;
         p < ctx->pstate.src_end && *p != '\0' && *p != '\n'; p++) {
      line_len++;
    }

    /* fixup line number: line_no points to the beginning of the next token */
    for (; p < ctx->pstate.pc; p++) {
      if (*p == '\n') {
        ctx->pstate.line_no--;
      }
    }

    err = mjs_set_errorf(mjs, MJS_SYNTAX_ERROR,
                         "syntax error at line %d col %lu:\n%.*s\n%*s^",
                         ctx->pstate.line_no, col, line_len,
                         ctx->syntax_error.begin - col, (int) col - 1, "");
  }

  mjsParserFree(parser, free);
  return err;
}

mjs_err_t mjs_parse(struct mjs *mjs, const char *src,
                    struct mjs_parse_ctx *ctx) {
  return mjs_parsen(mjs, src, strlen(src), ctx);
}

mjs_err_t mjs_parse_file(struct mjs *mjs, const char *path,
                         struct mjs_parse_ctx *ctx) {
  mjs_err_t err;

  size_t len;
  char *src = cs_read_file(path, &len);
  if (src == NULL) {
    return mjs_set_errorf(mjs, MJS_INTERNAL_ERROR, "cannot open file %s", path);
  }
  err = mjs_parsen(mjs, src, len, ctx);
  free(src);
  return err;
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/tokenizer.c"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#include <ctype.h>
#include <string.h>

/* Amalgamated: #include "common/cs_strtod.h" */
/* Amalgamated: #include "common/mg_str.h" */
/* Amalgamated: #include "common/utf.h" */
/* Amalgamated: #include "mjs/parser.h" */

/*
 * Must be in the same order as enum token constants. See comment
 * for function get_tok() for rationale for that.
 */
static const struct mg_str s_keywords[] = {
    MG_MK_STR("break"),      MG_MK_STR("case"),     MG_MK_STR("catch"),
    MG_MK_STR("continue"),   MG_MK_STR("debugger"), MG_MK_STR("default"),
    MG_MK_STR("delete"),     MG_MK_STR("do"),       MG_MK_STR("else"),
    MG_MK_STR("false"),      MG_MK_STR("finally"),  MG_MK_STR("for"),
    MG_MK_STR("function"),   MG_MK_STR("if"),       MG_MK_STR("in"),
    MG_MK_STR("instanceof"), MG_MK_STR("new"),      MG_MK_STR("null"),
    MG_MK_STR("return"),     MG_MK_STR("switch"),   MG_MK_STR("this"),
    MG_MK_STR("throw"),      MG_MK_STR("true"),     MG_MK_STR("try"),
    MG_MK_STR("typeof"),     MG_MK_STR("var"),      MG_MK_STR("void"),
    MG_MK_STR("while"),      MG_MK_STR("with"),     MG_MK_STR("let"),
    MG_MK_STR("undefined")};

int is_reserved_word_token(mjs_tok_t tok) {
  return tok >= TOK_BREAK && tok <= TOK_WITH;
}

/*
 * Move ptr to the next token, skipping comments and whitespaces.
 * Return number of new line characters detected.
 */
int skip_to_next_tok(const char **ptr, const char *src_end) {
  const char *s = *ptr, *p = NULL;
  int num_lines = 0;

  while (s != p && s < src_end && *s != '\0' &&
         (isspace((unsigned char) *s) || *s == '/')) {
    p = s;
    while (s < src_end && *s != '\0' && isspace((unsigned char) *s)) {
      if (*s == '\n') num_lines++;
      s++;
    }
    if ((s + 1) < src_end && s[0] == '/' && s[1] == '/') {
      s += 2;
      while (s < src_end && s[0] != '\0' && s[0] != '\n') s++;
    }
    if ((s + 1) < src_end && s[0] == '/' && s[1] == '*') {
      s += 2;
      while (s < src_end && s[0] != '\0' && !(s[-1] == '/' && s[-2] == '*')) {
        if (s[0] == '\n') num_lines++;
        s++;
      }
    }
  }
  *ptr = s;

  return num_lines;
}

/* Advance `s` pointer to the end of identifier  */
static void ident(const char **s, const char *src_end) {
  const unsigned char *p = (unsigned char *) *s;
  int n;
  Rune r;

  while ((const char *) p < src_end && p[0] != '\0') {
    if (p[0] == '$' || p[0] == '_' || isalnum(p[0])) {
      /* $, _, or any alphanumeric are valid identifier characters */
      p++;
    } else if ((const char *) (p + 5) < src_end && p[0] == '\\' &&
               p[1] == 'u' && isxdigit(p[2]) && isxdigit(p[3]) &&
               isxdigit(p[4]) && isxdigit(p[5])) {
      /* Unicode escape, \uXXXX . Could be used like "var \u0078 = 1;" */
      p += 6;
    } else if ((n = chartorune(&r, (char *) p)) > 1 && isalpharune(r)) {
      /*
       * TODO(dfrank): the chartorune() call above can read `p` past the
       * src_end, so it might crash on incorrect code. The solution would be
       * to modify `chartorune()` to accept src_end argument as well.
       */
      /* Unicode alphanumeric character */
      p += n;
    } else {
      break;
    }
  }

  *s = (char *) p;
}

static mjs_tok_t kw(const char *s, size_t len, int ntoks, mjs_tok_t tok) {
  int i;

  for (i = 0; i < ntoks; i++) {
    if (s_keywords[(tok - TOK_BREAK) + i].len == len &&
        memcmp(s_keywords[(tok - TOK_BREAK) + i].p + 1, s + 1, len - 1) == 0)
      break;
  }

  return i == ntoks ? TOK_IDENTIFIER : (mjs_tok_t)(tok + i);
}

static mjs_tok_t punct1(const char **s, const char *src_end, int ch1,
                        mjs_tok_t tok1, mjs_tok_t tok2) {
  (*s)++;
  if (*s < src_end && **s == ch1) {
    (*s)++;
    return tok1;
  } else {
    return tok2;
  }
}

static mjs_tok_t punct2(const char **s, const char *src_end, int ch1,
                        mjs_tok_t tok1, int ch2, mjs_tok_t tok2,
                        mjs_tok_t tok3) {
  if ((*s + 2) < src_end && s[0][1] == ch1 && s[0][2] == ch2) {
    (*s) += 3;
    return tok2;
  }

  return punct1(s, src_end, ch1, tok1, tok3);
}

static mjs_tok_t punct3(const char **s, const char *src_end, int ch1,
                        mjs_tok_t tok1, int ch2, mjs_tok_t tok2,
                        mjs_tok_t tok3) {
  (*s)++;
  if (*s < src_end) {
    if (**s == ch1) {
      (*s)++;
      return tok1;
    } else if (**s == ch2) {
      (*s)++;
      return tok2;
    }
  }
  return tok3;
}

static void parse_number(const char *s, const char **end, double *num) {
  *num = cs_strtod(s, (char **) end);
}

static mjs_tok_t parse_str_literal(const char **p, const char *src_end) {
  const char *s = *p;
  int quote = '\0';

  if (s < src_end) {
    quote = *s++;
  }

  /* Scan string literal, handle escape sequences */
  for (; s < src_end && *s != '\0' && *s != quote; s++) {
    if (*s == '\\') {
      switch (s[1]) {
        case 'b':
        case 'f':
        case 'n':
        case 'r':
        case 't':
        case 'v':
        case '\\':
          s++;
          break;
        default:
          if (s[1] == quote) s++;
          break;
      }
    }
  }

  if (s < src_end && *s == quote) {
    s++;
    *p = s;
    return TOK_STRING_LITERAL;
  } else {
    return TOK_END_OF_INPUT;
  }
}

/*
 * This function is the heart of the tokenizer.
 * Organized as a giant switch statement.
 *
 * Switch statement is by the first character of the input stream. If first
 * character begins with a letter, it could be either keyword or identifier.
 * get_tok() calls ident() which shifts `s` pointer to the end of the word.
 * Now, tokenizer knows that the word begins at `p` and ends at `s`.
 * It calls function kw() to scan over the keywords that start with `p[0]`
 * letter. Therefore, keyword tokens and keyword strings must be in the
 * same order, to let kw() function work properly.
 * If kw() finds a keyword match, it returns keyword token.
 * Otherwise, it returns TOK_IDENTIFIER.
 * NOTE(lsm): `prev_tok` is a previously parsed token. It is needed for
 * correctly parsing regex literals.
 */
mjs_tok_t get_tok(const char **s, const char *src_end, double *n,
                  mjs_tok_t prev_tok) {
  const char *p = *s;

  if (p >= src_end) {
    return TOK_END_OF_INPUT;
  }

  switch (*p) {
    /* Letters */
    case 'a':
      ident(s, src_end);
      return TOK_IDENTIFIER;
    case 'b':
      ident(s, src_end);
      return kw(p, *s - p, 1, TOK_BREAK);
    case 'c':
      ident(s, src_end);
      return kw(p, *s - p, 3, TOK_CASE);
    case 'd':
      ident(s, src_end);
      return kw(p, *s - p, 4, TOK_DEBUGGER);
    case 'e':
      ident(s, src_end);
      return kw(p, *s - p, 1, TOK_ELSE);
    case 'f':
      ident(s, src_end);
      return kw(p, *s - p, 4, TOK_FALSE);
    case 'g':
    case 'h':
      ident(s, src_end);
      return TOK_IDENTIFIER;
    case 'i':
      ident(s, src_end);
      return kw(p, *s - p, 3, TOK_IF);
    case 'j':
    case 'k':
      ident(s, src_end);
      return TOK_IDENTIFIER;
    case 'l':
      ident(s, src_end);
      return kw(p, *s - p, 1, TOK_LET);
    case 'm':
      ident(s, src_end);
      return TOK_IDENTIFIER;
    case 'n':
      ident(s, src_end);
      return kw(p, *s - p, 2, TOK_NEW);
    case 'o':
    case 'p':
    case 'q':
      ident(s, src_end);
      return TOK_IDENTIFIER;
    case 'r':
      ident(s, src_end);
      return kw(p, *s - p, 1, TOK_RETURN);
    case 's':
      ident(s, src_end);
      return kw(p, *s - p, 1, TOK_SWITCH);
    case 't':
      ident(s, src_end);
      return kw(p, *s - p, 5, TOK_THIS);
    case 'u':
      ident(s, src_end);
      return kw(p, *s - p, 1, TOK_UNDEFINED);
    case 'v':
      ident(s, src_end);
      return kw(p, *s - p, 2, TOK_VAR);
    case 'w':
      ident(s, src_end);
      return kw(p, *s - p, 2, TOK_WHILE);
    case 'x':
    case 'y':
    case 'z':
      ident(s, src_end);
      return TOK_IDENTIFIER;

    case '_':
    case '$':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '\\': /* Identifier may start with unicode escape sequence */
      ident(s, src_end);
      return TOK_IDENTIFIER;

    /* Numbers */
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      parse_number(p, s, n);
      return TOK_NUMBER;

    /* String literals */
    case '\'':
    case '"':
      return parse_str_literal(s, src_end);

    /* Punctuators */
    case '=':
      return punct2(s, src_end, '=', TOK_EQ, '=', TOK_EQ_EQ, TOK_ASSIGN);
    case '!':
      return punct2(s, src_end, '=', TOK_NE, '=', TOK_NE_NE, TOK_NOT);

    case '%':
      return punct1(s, src_end, '=', TOK_REM_ASSIGN, TOK_REM);
    case '*':
      return punct1(s, src_end, '=', TOK_MUL_ASSIGN, TOK_MUL);
    case '/':
      /*
       * TOK_DIV, TOK_DIV_ASSIGN, and TOK_REGEX_LITERAL start with `/` char.
       * Division can happen after an expression.
       * In expressions like this:
       *            a /= b; c /= d;
       * things between slashes is NOT a regex literal.
       * The switch below catches all cases where division happens.
       */
      switch (prev_tok) {
        case TOK_CLOSE_CURLY:
        case TOK_CLOSE_PAREN:
        case TOK_CLOSE_BRACKET:
        case TOK_IDENTIFIER:
        case TOK_NUMBER:
          return punct1(s, src_end, '=', TOK_DIV_ASSIGN, TOK_DIV);
        default:
          /* Not a division - this is a regex. Scan until closing slash */
          for (p++; p < src_end && *p != '\0' && *p != '\n'; p++) {
            if (*p == '\\') {
              /* Skip escape sequence */
              p++;
            } else if (*p == '/') {
              /* This is a closing slash */
              p++;
              /* Skip regex flags */
              while (*p == 'g' || *p == 'i' || *p == 'm') {
                p++;
              }
              *s = p;
              return TOK_REGEX_LITERAL;
            }
          }
          break;
      }
      return punct1(s, src_end, '=', TOK_DIV_ASSIGN, TOK_DIV);
    case '^':
      return punct1(s, src_end, '=', TOK_XOR_ASSIGN, TOK_XOR);

    case '+':
      return punct3(s, src_end, '+', TOK_PLUS_PLUS, '=', TOK_PLUS_ASSIGN,
                    TOK_PLUS);
    case '-':
      return punct3(s, src_end, '-', TOK_MINUS_MINUS, '=', TOK_MINUS_ASSIGN,
                    TOK_MINUS);
    case '&':
      return punct3(s, src_end, '&', TOK_LOGICAL_AND, '=', TOK_AND_ASSIGN,
                    TOK_AND);
    case '|':
      return punct3(s, src_end, '|', TOK_LOGICAL_OR, '=', TOK_OR_ASSIGN,
                    TOK_OR);

    case '<':
      if (*s + 1 < src_end && s[0][1] == '=') {
        (*s) += 2;
        return TOK_LE;
      }
      return punct2(s, src_end, '<', TOK_LSHIFT, '=', TOK_LSHIFT_ASSIGN,
                    TOK_LT);
    case '>':
      if (*s + 1 < src_end && s[0][1] == '=') {
        (*s) += 2;
        return TOK_GE;
      }
      if (*s + 3 < src_end && s[0][1] == '>' && s[0][2] == '>' &&
          s[0][3] == '=') {
        (*s) += 4;
        return TOK_URSHIFT_ASSIGN;
      }
      if (*s + 2 < src_end && s[0][1] == '>' && s[0][2] == '>') {
        (*s) += 3;
        return TOK_URSHIFT;
      }
      return punct2(s, src_end, '>', TOK_RSHIFT, '=', TOK_RSHIFT_ASSIGN,
                    TOK_GT);

    case '{':
      (*s)++;
      return TOK_OPEN_CURLY;
    case '}':
      (*s)++;
      return TOK_CLOSE_CURLY;
    case '(':
      (*s)++;
      return TOK_OPEN_PAREN;
    case ')':
      (*s)++;
      return TOK_CLOSE_PAREN;
    case '[':
      (*s)++;
      return TOK_OPEN_BRACKET;
    case ']':
      (*s)++;
      return TOK_CLOSE_BRACKET;
    case '.':
      switch (*(*s + 1)) {
        /* Numbers */
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          parse_number(p, s, n);
          return TOK_NUMBER;
      }
      (*s)++;
      return TOK_DOT;
    case ';':
      (*s)++;
      return TOK_SEMICOLON;
    case ':':
      (*s)++;
      return TOK_COLON;
    case '?':
      (*s)++;
      return TOK_QUESTION;
    case '~':
      (*s)++;
      return TOK_TILDA;
    case ',':
      (*s)++;
      return TOK_COMMA;

    default: {
      /* Handle unicode variables */
      Rune r;
      if (chartorune(&r, *s) > 1 && isalpharune(r)) {
        ident(s, src_end);
        return TOK_IDENTIFIER;
      }
      return TOK_END_OF_INPUT;
    }
  }
}

#ifdef TEST_RUN
int main(void) {
  const char *src =
      "for (var fo++ = -1; /= <= 1.17; x<<) { == <<=, 'x')} "
      "Infinity %=x<<=2";
  const char *src_end = src + strlen(src);
  mjs_tok_t tok;
  double num;
  const char *p = src;

  skip_to_next_tok(&src, src_end);
  while ((tok = get_tok(&src, src_end, &num, tok)) != TOK_END_OF_INPUT) {
    printf("%d [%.*s]\n", tok, (int) (src - p), p);
    skip_to_next_tok(&src, src_end);
    p = src;
  }
  printf("%d [%.*s]\n", tok, (int) (src - p), p);

  return 0;
}
#endif
#endif /* MG_EXPORT_INTERNAL_HEADERS */
