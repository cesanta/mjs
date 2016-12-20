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
#define CS_P_ESP32 15
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
#define CS_P_PIC32 11
/* Next id: 16 */

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
#define CS_PLATFORM CS_P_PIC32
#elif defined(ESP_PLATFORM)
#define CS_PLATFORM CS_P_ESP32
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
#define MG_NET_IF_PIC32 4

#define MG_SSL_IF_OPENSSL 1
#define MG_SSL_IF_MBEDTLS 2
#define MG_SSL_IF_SIMPLELINK 3

/* Amalgamated: #include "common/platforms/platform_unix.h" */
/* Amalgamated: #include "common/platforms/platform_windows.h" */
/* Amalgamated: #include "common/platforms/platform_esp32.h" */
/* Amalgamated: #include "common/platforms/platform_esp8266.h" */
/* Amalgamated: #include "common/platforms/platform_cc3200.h" */
/* Amalgamated: #include "common/platforms/platform_cc3100.h" */
/* Amalgamated: #include "common/platforms/platform_mbed.h" */
/* Amalgamated: #include "common/platforms/platform_nrf51.h" */
/* Amalgamated: #include "common/platforms/platform_nrf52.h" */
/* Amalgamated: #include "common/platforms/platform_wince.h" */
/* Amalgamated: #include "common/platforms/platform_nxp_lpc.h" */
/* Amalgamated: #include "common/platforms/platform_nxp_kinetis.h" */
/* Amalgamated: #include "common/platforms/platform_pic32.h" */

/* Common stuff */

#if !defined(WEAK)
#if (defined(__GNUC__) || defined(__TI_COMPILER_VERSION__)) && !defined(_WIN32)
#define WEAK __attribute__((weak))
#else
#define WEAK
#endif
#endif

#ifdef __GNUC__
#define NORETURN __attribute__((noreturn))
#define NOINLINE __attribute__((noinline))
#define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#define NOINSTR __attribute__((no_instrument_function))
#define DO_NOT_WARN_UNUSED __attribute__((unused))
#else
#define NORETURN
#define NOINLINE
#define WARN_UNUSED_RESULT
#define NOINSTR
#define DO_NOT_WARN_UNUSED
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
typedef struct _stati64 cs_stat_t;
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
#define MG_ENABLE_HTTP_CGI MG_ENABLE_FILESYSTEM
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
#define MG_ENABLE_HTTP_CGI MG_ENABLE_FILESYSTEM
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

#if (defined(CC3200_FS_SPIFFS) || defined(CC3200_FS_SLFS)) && \
    !defined(MG_ENABLE_FILESYSTEM)
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
#if defined(MG_NET_IF) && MG_NET_IF == MG_NET_IF_SIMPLELINK && \
    !defined(__SIMPLELINK_H__)

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
#line 1 "common/platforms/platform_esp32.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_ESP32_H_
#define CS_COMMON_PLATFORMS_PLATFORM_ESP32_H_
#if CS_PLATFORM == CS_P_ESP32

#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <machine/endian.h>
#include <stdint.h>
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

#define MG_LWIP 1

#ifndef MG_NET_IF
#define MG_NET_IF MG_NET_IF_SOCKET
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#endif /* CS_PLATFORM == CS_P_ESP32 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_ESP32_H_ */
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

/*
 * mbed.h contains C++ code (e.g. templates), thus, it should be processed
 * only if included directly to startup file (ex: main.cpp)
 */
#ifdef __cplusplus
/* Amalgamated: #include "mbed.h" */
#endif /* __cplusplus */

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct stat cs_stat_t;
#define DIRSEP '/'

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
int inet_aton(const char *cp, struct in_addr *inp);
in_addr_t inet_addr(const char *cp);

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
#line 1 "common/platforms/platform_pic32.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_PIC32_H_
#define CS_COMMON_PLATFORMS_PLATFORM_PIC32_H_

#if CS_PLATFORM == CS_P_PIC32

#define MG_NET_IF MG_NET_IF_PIC32

#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#include <system_config.h>
#include <system_definitions.h>

#include <sys/types.h>

typedef TCP_SOCKET sock_t;
#define to64(x) strtoll(x, NULL, 10)

#define SIZE_T_FMT "lu"
#define INT64_FMT "lld"

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

char* inet_ntoa(struct in_addr in);

#endif /* CS_PLATFORM == CS_P_PIC32 */

#endif /* CS_COMMON_PLATFORMS_PLATFORM_PIC32_H_ */
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

/* Amalgamated: #include "common/platform.h" */

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

#include <stdlib.h>
/* Amalgamated: #include "common/platform.h" */

#if defined(__cplusplus)
extern "C" {
#endif

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

/* Amalgamated: #include "common/platform.h" */

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

/* Amalgamated: #include "common/platform.h" */

#ifndef CS_ENABLE_STRDUP
#define CS_ENABLE_STRDUP 0
#endif

#ifndef CS_ENABLE_TO64
#define CS_ENABLE_TO64 0
#endif

/*
 * Expands to a string representation of its argument: e.g.
 * `CS_STRINGIFY_LIT(5) expands to "5"`
 */
#define CS_STRINGIFY_LIT(x) #x

/*
 * Expands to a string representation of its argument, which is allowed
 * to be a macro: e.g.
 *
 * #define FOO 123
 * CS_STRINGIFY_MACRO(FOO)
 *
 * expands to 123.
 */
#define CS_STRINGIFY_MACRO(x) CS_STRINGIFY_LIT(x)

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
#line 1 "mjs/bf/bf.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_BRAINFARTH_BRAINFARTH_H_
#define MJS_BRAINFARTH_BRAINFARTH_H_

/* Amalgamated: #include "common/platform.h" */

#define FR_STACK_SIZE 256

#define FR_EXIT_RUN -1

typedef int64_t bf_cell_t;
/* typedef int16_t bf_cell_t; */

typedef int8_t bf_opcode_t;

/* index in IRAM */
typedef int16_t bf_word_ptr_t;

/* Invalid index in RAM (bf_word_ptr_t) */
#define BF_INVALID_WORD_PTR (-1)

/* Min integer which can be represented by `bf_opcode_t` */
#define BF_MIN_LOCAL_OFFSET ((bf_opcode_t)(1 << (sizeof(bf_opcode_t)*8 - 1)))

struct bf_vm;
typedef void (*bf_native_t)(struct bf_vm *vm);

struct bf_code {
  bf_opcode_t *opcodes;      /* all word bodies */
  size_t opcodes_len;        /* max 32768 */
  bf_word_ptr_t *table;      /* points to opcodes */
  size_t table_len;          /* max 127 */
  bf_native_t *native_words; /* native words */
  size_t native_words_len;

  const char **word_names; /* table_len number of entries, for tracing */
  const char **pos_names;  /* opcodes_len number of entries, for tracing */
};

struct bf_stack {
  bf_cell_t stack[FR_STACK_SIZE];
  size_t pos;
  size_t size;
};

/*
 * Called after "entering" each word
 */
typedef void (bf_cb_op_t)(struct bf_vm *vm);

struct bf_callbacks {
  bf_cb_op_t *after_bf_enter;
};

struct bf_vm {
  struct bf_code *code;
  struct bf_mem *iram;

  bf_word_ptr_t ip;
  struct bf_stack dstack; /* data stack */
  struct bf_stack rstack; /* return stack */
  bf_cell_t tmp;

  struct bf_callbacks cb;
  void *user_data;
};

/*
 * Initialize brainforth VM.
 *
 * `cb` might be `NULL`. If it's not NULL, the pointer is not retained by the
 * bf, so the caller may free it right after `bf_init_vm()` returned.
 */
void bf_init_vm(struct bf_vm *vm, struct bf_code *code, struct bf_callbacks *cb);
void bf_destroy_vm(struct bf_vm *vm);
void bf_run(struct bf_vm *vm, bf_word_ptr_t word);

bf_word_ptr_t bf_lookup_word(struct bf_vm *vm, bf_opcode_t op);

void bf_push(struct bf_stack *stack, bf_cell_t value);
bf_cell_t bf_pop(struct bf_stack *stack);
/* returns the top of the stack value */
bf_cell_t bf_tos(struct bf_stack *stack);

void bf_print_stack(struct bf_vm *vm, struct bf_stack *stack);

/* these should be implemented by whoever embeds the VM */

int32_t bf_to_int(bf_cell_t cell);
bf_cell_t bf_from_int(int32_t i);
void bf_print_cell(struct bf_vm *vm, bf_cell_t cell);
int bf_is_true(bf_cell_t cell);

#endif /* MJS_BRAINFARTH_BRAINFARTH_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/bf/mem.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_BRAINFARTH_MEM_H_
#define MJS_BRAINFARTH_MEM_H_

/* Amalgamated: #include "common/platform.h" */
/* Amalgamated: #include "mjs/bf/bf.h" */

#define FR_PAGE_SIZE 512

#define FR_MEM_RO (1 << 0)
#define FR_MEM_FOREIGN (1 << 1)

struct bf_page {
  void *base;
  uint16_t flags;
};

struct bf_mem {
  size_t num_pages;
  struct bf_page pages[1];  // zero sized arrays are non-standard
};

struct bf_mem *bf_create_mem();
void bf_destroy_mem(struct bf_mem *mem);

bf_cell_t bf_mmap(struct bf_mem **mem, void *buf, size_t buf_len, int flags);

char bf_read_byte(struct bf_mem *mem, bf_cell_t addr);
void bf_write_byte(struct bf_mem *mem, bf_cell_t addr, char value);

/* return false if the address is unmapped */
int bf_is_mapped(struct bf_mem *mem, bf_cell_t addr);

#endif /* MJS_BRAINFARTH_MEM_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/internal.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_INTERNAL_H_
#define MJS_INTERNAL_H_

/* Amalgamated: #include "mjs/license.h" */

/* Amalgamated: #include "common/platform.h" */

#ifndef FAST
#define FAST
#endif

#ifndef STATIC
#define STATIC
#endif

#ifndef ENDL
#define ENDL "\n"
#endif

#ifdef MJS_EXPOSE_PRIVATE
#define MJS_PRIVATE
#define MJS_EXTERN extern
#else
#define MJS_PRIVATE static
#define MJS_EXTERN static
#endif

#endif /* MJS_INTERNAL_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/tok.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_TOK_H_
#define MJS_TOK_H_

/* Amalgamated: #include "mjs/internal.h" */

struct pstate {
  const char *file_name; /* Source code file name */
  const char *buf;       /* Nul-terminated source code buffer */
  const char *pos;       /* Current position */
  int line_no;           /* Line number */
  double double_val;     /* Parsed TOK_NUM value */
  const char *tok_ptr;   /* Points to the beginning of the parsed token */
  int tok_len;           /* Length of the parsed token */
};

/* lemon treats 0 as eof but doesn't generate the define for us */
#define TOK_END_OF_INPUT 0

enum {
  TOK_EOF,
  TOK_NUM = 200, /* Make sure they don't clash with ascii '+', '{', etc */
  TOK_STR,
  TOK_IDENT,
  TOK_KEYWORD_BREAK,
  TOK_KEYWORD_CASE,
  TOK_KEYWORD_CATCH,
  TOK_KEYWORD_CONTINUE,
  TOK_KEYWORD_DEBUGGER,
  TOK_KEYWORD_DEFAULT,
  TOK_KEYWORD_DELETE,
  TOK_KEYWORD_DO,
  TOK_KEYWORD_ELSE,
  TOK_KEYWORD_FALSE,
  TOK_KEYWORD_FINALLY,
  TOK_KEYWORD_FOR,
  TOK_KEYWORD_FUNCTION,
  TOK_KEYWORD_IF,
  TOK_KEYWORD_IN,
  TOK_KEYWORD_INSTANCEOF,
  TOK_KEYWORD_NEW,
  TOK_KEYWORD_NULL,
  TOK_KEYWORD_RETURN,
  TOK_KEYWORD_SWITCH,
  TOK_KEYWORD_THIS,
  TOK_KEYWORD_THROW,
  TOK_KEYWORD_TRUE,
  TOK_KEYWORD_TRY,
  TOK_KEYWORD_TYPEOF,
  TOK_KEYWORD_VAR,
  TOK_KEYWORD_VOID,
  TOK_KEYWORD_WHILE,
  TOK_KEYWORD_WITH,
  TOK_KEYWORD_LET,
  TOK_KEYWORD_UNDEFINED
};

void pinit(const char *file_name, const char *buf, struct pstate *);
int pnext(struct pstate *);

MJS_PRIVATE int is_ident(int c);
MJS_PRIVATE int is_digit(int c);

#endif /* MJS_TOK_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/parser_state.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_PARSER_STATE_H_
#define MJS_PARSER_STATE_H_

/* Amalgamated: #include "mjs/bf/bf.h" */
/* Amalgamated: #include "mjs/tok.h" */

struct mjs_token {
  const char *begin;
};

struct mjs_parse_ctx {
  int state;
  struct mjs_token syntax_error;
  struct pstate pstate;
  struct mjs *mjs;
  bf_word_ptr_t gen;
  bf_word_ptr_t entry;
};

bf_word_ptr_t mjs_emit(struct mjs_parse_ctx *ctx, bf_opcode_t op);
bf_word_ptr_t mjs_emit_call(struct mjs_parse_ctx *ctx, bf_word_ptr_t dst);
bf_word_ptr_t mjs_emit_quote(struct mjs_parse_ctx *ctx, bf_word_ptr_t dst);
bf_word_ptr_t mjs_emit_bin(struct mjs_parse_ctx *ctx, bf_word_ptr_t a,
                           bf_word_ptr_t b, bf_opcode_t op);
bf_word_ptr_t mjs_emit_num(struct mjs_parse_ctx *ctx, const char *lit);
bf_word_ptr_t mjs_emit_str(struct mjs_parse_ctx *ctx, const char *lit);
bf_word_ptr_t mjs_emit_var(struct mjs_parse_ctx *ctx, const char *ident);
bf_word_ptr_t mjs_emit_ident(struct mjs_parse_ctx *ctx, const char *ident);
bf_word_ptr_t mjs_emit_assign(struct mjs_parse_ctx *ctx, bf_word_ptr_t lhs,
                              bf_word_ptr_t val, bf_opcode_t op);
bf_word_ptr_t mjs_emit_func(struct mjs_parse_ctx *ctx, bf_word_ptr_t args,
                            bf_word_ptr_t body);
bf_word_ptr_t mjs_emit_str_or_ident(struct mjs_parse_ctx *ctx, const char *lit);
bf_word_ptr_t mjs_add_stmt(struct mjs_parse_ctx *ctx, bf_word_ptr_t stmtlist,
                           bf_word_ptr_t stmt);

bf_word_ptr_t mjs_emit_uint8(struct mjs_parse_ctx *ctx, uint8_t v);
bf_word_ptr_t mjs_emit_uint16(struct mjs_parse_ctx *ctx, uint16_t v);
bf_word_ptr_t mjs_emit_uint32(struct mjs_parse_ctx *ctx, uint32_t v);
bf_word_ptr_t mjs_emit_uint64(struct mjs_parse_ctx *ctx, uint64_t v);

#endif /* MJS_PARSER_STATE_H_ */
#ifdef MG_MODULE_LINES
#line 1 "bazel-out/local-dbg-asan/genfiles/mjs/vm.gen.h"
#endif
#ifndef MJS_GEN_OPCODES_H_
#define MJS_GEN_OPCODES_H_

/* Amalgamated: #include "mjs/bf/bf.h" */

extern struct bf_code MJS_code;

#define MJS_WORD_PTR_quote (0)
#define MJS_WORD_PTR_exit (0)
#define MJS_WORD_PTR_drop (0)
#define MJS_WORD_PTR_dup (0)
#define MJS_WORD_PTR_swap (0)
#define MJS_WORD_PTR_over (0)
#define MJS_WORD_PTR_MINUS_rot (0)
#define MJS_WORD_PTR_rot (0)
#define MJS_WORD_PTR_GT_r (3)
#define MJS_WORD_PTR_r_GT (3)
#define MJS_WORD_PTR_sp_AT (3)
#define MJS_WORD_PTR_sp_SET (3)
#define MJS_WORD_PTR_rp_AT (3)
#define MJS_WORD_PTR_rp_SET (3)
#define MJS_WORD_PTR_tmp_SET (3)
#define MJS_WORD_PTR_tmp_AT (3)
#define MJS_WORD_PTR_print (3)
#define MJS_WORD_PTR_cr (3)
#define MJS_WORD_PTR_DOT_s (3)
#define MJS_WORD_PTR_EQ (3)
#define MJS_WORD_PTR_LT (3)
#define MJS_WORD_PTR_GT (3)
#define MJS_WORD_PTR_invert (3)
#define MJS_WORD_PTR_PLUS (3)
#define MJS_WORD_PTR_MINUS (3)
#define MJS_WORD_PTR_STAR (3)
#define MJS_WORD_PTR_call (3)
#define MJS_WORD_PTR_if (3)
#define MJS_WORD_PTR_ifelse (3)
#define MJS_WORD_PTR_loop (3)
#define MJS_WORD_PTR_ndrop (16)
#define MJS_WORD_PTR_str (16)
#define MJS_WORD_PTR_scope_AT (16)
#define MJS_WORD_PTR_scope_SET (16)
#define MJS_WORD_PTR_frame_AT (16)
#define MJS_WORD_PTR_frame_SET (16)
#define MJS_WORD_PTR_mkobj (16)
#define MJS_WORD_PTR_addprop (16)
#define MJS_WORD_PTR_setprop (24)
#define MJS_WORD_PTR_getprop (24)
#define MJS_WORD_PTR_getvar (24)
#define MJS_WORD_PTR_setvar (24)
#define MJS_WORD_PTR_jscall (24)
#define MJS_WORD_PTR_jscall_exit (24)
#define MJS_WORD_PTR_jsenter (29)
#define MJS_WORD_PTR_jsexit (43)
#define MJS_WORD_PTR_anon_0 (50)
#define MJS_WORD_PTR_anon_1 (52)
#define MJS_WORD_PTR_setarg (54)
#define MJS_WORD_PTR_ffi (74)
#define MJS_WORD_PTR_undefined (76)
#define MJS_WORD_PTR_null (76)
#define MJS_WORD_PTR_2dup (76)
#define MJS_WORD_PTR_dec (79)
#define MJS_WORD_PTR_GTEQ (84)
#define MJS_WORD_PTR_LTEQ (87)
#define MJS_WORD_PTR_SETEQ (90)
#define MJS_WORD_PTR_anon_2 (93)
#define MJS_WORD_PTR_ifstmt (95)
#define MJS_WORD_PTR_anon_3 (100)
#define MJS_WORD_PTR_anon_4 (117)
#define MJS_WORD_PTR_repeat (124)
#define MJS_WORD_PTR_anon_5 (137)
#define MJS_WORD_PTR_anon_6 (143)
#define MJS_WORD_PTR_anon_7 (148)
#define MJS_WORD_PTR_while (158)
#define MJS_WORD_PTR_anon_8 (164)
#define MJS_WORD_PTR_anon_9 (169)
#define MJS_WORD_PTR_jsprint (181)
#define MJS_WORD_PTR_zero (188)
#define MJS_WORD_PTR_one (192)
#define MJS_WORD_PTR_nop (196)
#define MJS_WORD_PTR_inc (199)
#define MJS_WORD_PTR_swapinc (204)
#define MJS_WORD_PTR_div (207)
#define MJS_WORD_PTR_rem (207)
#define MJS_WORD_PTR_lshift (207)
#define MJS_WORD_PTR_rshift (207)
#define MJS_WORD_PTR_urshift (207)
#define MJS_WORD_PTR_and (207)
#define MJS_WORD_PTR_or (207)
#define MJS_WORD_PTR_xor (207)
#define MJS_OP_quote ((bf_opcode_t) -1)
#define MJS_OP_exit ((bf_opcode_t) 0)
#define MJS_OP_drop ((bf_opcode_t) 1)
#define MJS_OP_dup ((bf_opcode_t) 2)
#define MJS_OP_swap ((bf_opcode_t) 3)
#define MJS_OP_over ((bf_opcode_t) 4)
#define MJS_OP_MINUS_rot ((bf_opcode_t) 5)
#define MJS_OP_rot ((bf_opcode_t) 6)
#define MJS_OP_GT_r ((bf_opcode_t) 7)
#define MJS_OP_r_GT ((bf_opcode_t) 8)
#define MJS_OP_sp_AT ((bf_opcode_t) 9)
#define MJS_OP_sp_SET ((bf_opcode_t) 10)
#define MJS_OP_rp_AT ((bf_opcode_t) 11)
#define MJS_OP_rp_SET ((bf_opcode_t) 12)
#define MJS_OP_tmp_SET ((bf_opcode_t) 13)
#define MJS_OP_tmp_AT ((bf_opcode_t) 14)
#define MJS_OP_print ((bf_opcode_t) 15)
#define MJS_OP_cr ((bf_opcode_t) 16)
#define MJS_OP_DOT_s ((bf_opcode_t) 17)
#define MJS_OP_EQ ((bf_opcode_t) 18)
#define MJS_OP_LT ((bf_opcode_t) 19)
#define MJS_OP_GT ((bf_opcode_t) 20)
#define MJS_OP_invert ((bf_opcode_t) 21)
#define MJS_OP_PLUS ((bf_opcode_t) 22)
#define MJS_OP_MINUS ((bf_opcode_t) 23)
#define MJS_OP_STAR ((bf_opcode_t) 24)
#define MJS_OP_call ((bf_opcode_t) 25)
#define MJS_OP_if ((bf_opcode_t) 26)
#define MJS_OP_ifelse ((bf_opcode_t) 27)
#define MJS_OP_loop ((bf_opcode_t) 28)
#define MJS_OP_ndrop ((bf_opcode_t) 29)
#define MJS_OP_str ((bf_opcode_t) 30)
#define MJS_OP_scope_AT ((bf_opcode_t) 31)
#define MJS_OP_scope_SET ((bf_opcode_t) 32)
#define MJS_OP_frame_AT ((bf_opcode_t) 33)
#define MJS_OP_frame_SET ((bf_opcode_t) 34)
#define MJS_OP_mkobj ((bf_opcode_t) 35)
#define MJS_OP_addprop ((bf_opcode_t) 36)
#define MJS_OP_setprop ((bf_opcode_t) 37)
#define MJS_OP_getprop ((bf_opcode_t) 38)
#define MJS_OP_getvar ((bf_opcode_t) 39)
#define MJS_OP_setvar ((bf_opcode_t) 40)
#define MJS_OP_jscall ((bf_opcode_t) 41)
#define MJS_OP_jscall_exit ((bf_opcode_t) 42)
#define MJS_OP_jsenter ((bf_opcode_t) 43)
#define MJS_OP_jsexit ((bf_opcode_t) 44)
#define MJS_OP_setarg ((bf_opcode_t) 45)
#define MJS_OP_undefined ((bf_opcode_t) 46)
#define MJS_OP_null ((bf_opcode_t) 47)
#define MJS_OP_2dup ((bf_opcode_t) 48)
#define MJS_OP_GTEQ ((bf_opcode_t) 49)
#define MJS_OP_LTEQ ((bf_opcode_t) 50)
#define MJS_OP_SETEQ ((bf_opcode_t) 51)
#define MJS_OP_ifstmt ((bf_opcode_t) 52)
#define MJS_OP_repeat ((bf_opcode_t) 53)
#define MJS_OP_while ((bf_opcode_t) 54)
#define MJS_OP_jsprint ((bf_opcode_t) 55)
#define MJS_OP_zero ((bf_opcode_t) 56)
#define MJS_OP_one ((bf_opcode_t) 57)
#define MJS_OP_nop ((bf_opcode_t) 58)
#define MJS_OP_inc ((bf_opcode_t) 59)
#define MJS_OP_swapinc ((bf_opcode_t) 60)
#define MJS_OP_div ((bf_opcode_t) 61)
#define MJS_OP_rem ((bf_opcode_t) 62)
#define MJS_OP_lshift ((bf_opcode_t) 63)
#define MJS_OP_rshift ((bf_opcode_t) 64)
#define MJS_OP_urshift ((bf_opcode_t) 65)
#define MJS_OP_and ((bf_opcode_t) 66)
#define MJS_OP_or ((bf_opcode_t) 67)
#define MJS_OP_xor ((bf_opcode_t) 68)

#endif /* MJS_GEN_OPCODES_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/ffi/ffi.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_FFI_FFI_H_
#define MJS_FFI_FFI_H_

/* Amalgamated: #include "common/platform.h" */

typedef void (*ffi_fn_t)(void);

struct ffi_arg {
  int size;
  int is_float;
  union {
    uint64_t i;
    double d;
  } v;
};

int ffi_call(ffi_fn_t func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args);

void ffi_set_int32(struct ffi_arg *arg, uint32_t v);
void ffi_set_int64(struct ffi_arg *arg, uint64_t v);
void ffi_set_ptr(struct ffi_arg *arg, void *v);
void ffi_set_double(struct ffi_arg *arg, uint64_t v);

#endif /* MJS_FFI_FFI_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/core_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_CORE_PUBLIC_H_
#define MJS_CORE_PUBLIC_H_

#include <stdint.h>
/* Amalgamated: #include "mjs/license.h" */

/*
 *  Double-precision floating-point number, IEEE 754
 *
 *  64 bit (8 bytes) in total
 *  1  bit sign
 *  11 bits exponent
 *  52 bits mantissa
 *      7         6        5        4        3        2        1        0
 *  seeeeeee|eeeemmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm
 *
 * If an exponent is all-1 and mantissa is all-0, then it is an INFINITY:
 *  11111111|11110000|00000000|00000000|00000000|00000000|00000000|00000000
 *
 * If an exponent is all-1 and mantissa's MSB is 1, it is a quiet NaN:
 *  11111111|11111000|00000000|00000000|00000000|00000000|00000000|00000000
 *
 *  MJS NaN-packing:
 *    sign and exponent is 0xfff
 *    4 bits specify type (tag), must be non-zero
 *    48 bits specify value
 *
 *  11111111|1111tttt|vvvvvvvv|vvvvvvvv|vvvvvvvv|vvvvvvvv|vvvvvvvv|vvvvvvvv
 *   NaN marker |type|  48-bit placeholder for values: pointers, strings
 *
 * On 64-bit platforms, pointers are really 48 bit only, so they can fit,
 * provided they are sign extended
 */

typedef uint64_t mjs_val_t;

/* This if-0 is a dirty workaround to force etags to pick `struct mjs` */
#if 0
/* Opaque structure. MJS engine context. */
struct mjs {
  /* ... */
};
#endif

struct mjs;

enum mjs_err {
  MJS_OK,
  MJS_SYNTAX_ERROR,
  MJS_INTERNAL_ERROR,
  MJS_REFERENCE_ERROR,
};

typedef enum mjs_err mjs_err_t;

/* Create MJS instance */
struct mjs *mjs_create();

struct mjs_create_opts {
  /* use non-default bytecode definition file, testing-only */
  struct bf_code *code;
};

/*
 * Like `msj_create()`, but allows to customize initial MJS state, see `struct
 * mjs_create_opts`.
 */
struct mjs *mjs_create_opt(struct mjs_create_opts opts);

/* Destroy MJS instance */
void mjs_destroy(struct mjs *mjs);

mjs_val_t mjs_get_global(struct mjs *mjs);

void mjs_push(struct mjs *mjs, mjs_val_t val);
mjs_val_t mjs_pop(struct mjs *mjs);
mjs_val_t mjs_pop_arg(struct mjs *mjs, mjs_val_t *nargs);

/*
 * Tells the GC about an MJS value variable/field owned by C code.
 *
 * The user's C code should own mjs_val_t variables if the value's lifetime
 * crosses any invocation of `mjs_exec()` and friends, including `mjs_call()`.
 *
 * The registration of the variable prevents the GC from mistakenly treat the
 * object as garbage.
 *
 * User code should also explicitly disown the variables with `mjs_disown()`
 * once it goes out of scope or the structure containing the mjs_val_t field is
 * freed.
 *
 * Consider the following examples:
 *
 * Correct (owning is not necessary):
 * ```c
 * mjs_val_t res;
 * mjs_exec(mjs, "....some script", &res);
 * // ... use res somehow
 *
 * mjs_val_t res;
 * mjs_exec(mjs, "....some script2", &res);
 * // ... use new res somehow
 * ```
 *
 * WRONG:
 * ```c
 * mjs_val_t res1;
 * mjs_exec(mjs, "....some script", &res1);
 *
 * mjs_val_t res2;
 * mjs_exec(mjs, "....some script2", &res2);
 *
 * // ... use res1 (WRONG!) and res2
 * ```
 *
 * The code above is wrong, because after the second invocation of
 * `mjs_exec()`, the value of `res1` is invalidated.
 *
 * Correct (res1 is owned)
 * ```c
 * mjs_val_t res1 = MJS_UNDEFINED;
 * mjs_own(mjs, &res1);
 * mjs_exec(mjs, "....some script", &res1);
 *
 * mjs_val_t res2 = MJS_UNDEFINED;
 * mjs_exec(mjs, "....some script2", &res2);
 *
 * // ... use res1 and res2
 * mjs_disown(mjs, &res1);
 * ```
 *
 * NOTE that we explicly initialized `res1` to a valid value before owning it
 * (in this case, the value is `MJS_UNDEFINED`). Owning an uninitialized
 * variable is an undefined behaviour.
 *
 * Of course, it's not an error to own a variable even if it's not mandatory:
 * e.g. in the last example we could own both `res1` and `res2`. Probably it
 * would help us in the future, when we refactor the code so that `res2` has to
 * be owned, and we could forget to do that.
 *
 * Also, if the user code has some C function called from MJS, and in this C
 * function some MJS value (`mjs_val_t`) needs to be stored somewhhere and to
 * stay alive after the C function has returned, it also needs to be properly
 * owned.
 */
void mjs_own(struct mjs *mjs, mjs_val_t *v);

/*
 * Disowns the value previously owned by `mjs_own()`.
 *
 * Returns 1 if value is found, 0 otherwise.
 */
int mjs_disown(struct mjs *mjs, mjs_val_t *v);

mjs_err_t mjs_set_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt, ...);

/*
 * return a string representation of an error.
 * the error string might be overwritten by calls to `mjs_set_errorf`.
 */
const char *mjs_strerror(struct mjs *mjs, mjs_err_t err);

#endif /* MJS_CORE_PUBLIC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/ffi_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_FFI_PUBLIC_H_
#define MJS_FFI_PUBLIC_H_

/* Amalgamated: #include "mjs/core_public.h" */

typedef void *(mjs_ffi_resolver_t)(void *handle, const char *symbol);

void mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym);

#endif /* MJS_FFI_PUBLIC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/ffi.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_FFI_H_
#define MJS_FFI_H_

/* Amalgamated: #include "mjs/ffi_public.h" */
/* Amalgamated: #include "mjs/internal.h" */

struct bf_vm;

MJS_PRIVATE void mjs_ffi_call(struct mjs *mjs, mjs_val_t sig);

MJS_PRIVATE void mjs_ffi_cb_void_void(struct bf_vm *vm);
MJS_PRIVATE void mjs_ffi_cb_arg(struct bf_vm *vm);
MJS_PRIVATE void mjs_ffi_cb_arg_free(struct bf_vm *vm);

#endif /* MJS_FFI_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/mm.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_MM_H_
#define MJS_MM_H_

/* Amalgamated: #include "mjs/internal.h" */

struct mjs;

typedef void (*gc_cell_destructor_t)(struct mjs *mjs, void *);

struct gc_block {
  struct gc_block *next;
  struct gc_cell *base;
  size_t size;
};

struct gc_arena {
  struct gc_block *blocks;
  size_t size_increment;
  struct gc_cell *free; /* head of free list */
  size_t cell_size;

  gc_cell_destructor_t destructor;
};

#endif /* MJS_MM_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/core.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_CORE_H_
#define MJS_CORE_H_

/* Amalgamated: #include "common/mbuf.h" */
/* Amalgamated: #include "mjs/core_public.h" */
/* Amalgamated: #include "mjs/bf/bf.h" */
/* Amalgamated: #include "mjs/ffi.h" */
/* Amalgamated: #include "mjs/internal.h" */
/* Amalgamated: #include "mjs/mm.h" */

/*
 * A tag is made of the sign bit and the 4 lower order bits of byte 6.
 * So in total we have 32 possible tags.
 *
 * Tag (1,0) however cannot hold a zero payload otherwise it's interpreted as an
 * INFINITY; for simplicity we're just not going to use that combination.
 */
#define MAKE_TAG(s, t) \
    ((uint64_t)(s) << 63 | (uint64_t) 0x7ff0 << 48 | (uint64_t)(t) << 48)

#define MJS_TAG_OBJECT MAKE_TAG(1, 0xF)
#define MJS_TAG_FOREIGN MAKE_TAG(1, 0xE)
#define MJS_TAG_UNDEFINED MAKE_TAG(1, 0xD)
#define MJS_TAG_BOOLEAN MAKE_TAG(1, 0xC)
#define MJS_TAG_NAN MAKE_TAG(1, 0xB)
#define MJS_TAG_STRING_I MAKE_TAG(1, 0xA)  /* Inlined string len < 5 */
#define MJS_TAG_STRING_5 MAKE_TAG(1, 0x9)  /* Inlined string len 5 */
#define MJS_TAG_STRING_O MAKE_TAG(1, 0x8)  /* Owned string */
#define MJS_TAG_STRING_F MAKE_TAG(1, 0x7)  /* Foreign string */
#define MJS_TAG_STRING_C MAKE_TAG(1, 0x6)  /* String chunk */
#define MJS_TAG_FUNCTION MAKE_TAG(1, 0x5)  /* JavaScript function */
#define MJS_TAG_CFUNCTION MAKE_TAG(1, 0x4) /* C function */
#define MJS_TAG_STRING_D MAKE_TAG(1, 0x3)  /* Dictionary string  */
#define MJS_TAG_NOVALUE MAKE_TAG(1, 0x1)   /* Sentinel for no value */
#define MJS_TAG_MASK MAKE_TAG(1, 0xF)

#define _MJS_NULL MJS_TAG_FOREIGN
#define _MJS_UNDEFINED MJS_TAG_UNDEFINED

struct mjs_vals {
  mjs_val_t global_object;
  mjs_val_t scope;      /* current scope, chained on rstack */
  mjs_val_t call_frame; /* top-most call frame */
};

struct mjs {
  struct bf_vm vm;

  /*
   * Index of the first free byte in IRAM
   */
  bf_word_ptr_t last_code;

  struct mbuf owned_strings;   /* Sequence of (varint len, char data[]) */
  struct mbuf foreign_strings; /* Sequence of (varint len, char *data) */

  struct gc_arena object_arena;
  struct gc_arena property_arena;

  struct mbuf owned_values; /* buffer for GC roots owned by C code */
  struct mjs_vals vals;

  mjs_ffi_resolver_t *dlsym;

  char *error_msg;
  mjs_err_t error_msg_err;

  /* Set to true to trigger GC when safe */
  unsigned int need_gc : 1;
  /* while true, GC is inhibited */
  unsigned int inhibit_gc : 1;
};

#endif /* MJS_CORE_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/gc.h"
#endif
/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_GC_H_
#define MJS_GC_H_

/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/internal.h" */
/* Amalgamated: #include "mjs/mm.h" */

/*
 * performs arithmetics on gc_cell pointers as if they were arena->cell_size
 * bytes wide
 */
#define GC_CELL_OP(arena, cell, op, arg) \
  ((struct gc_cell *) (((char *) (cell)) op((arg) * (arena)->cell_size)))

struct gc_cell {
  union {
    struct gc_cell *link;
    uintptr_t word;
  } head;
};

/*
 * Perform garbage collection.
 * Pass true to full in order to reclaim unused heap back to the OS.
 */
void mjs_gc(struct mjs *mjs, int full);

MJS_PRIVATE int gc_strings_is_gc_needed(struct mjs *mjs);

/* perform gc if not inhibited */
MJS_PRIVATE int maybe_gc(struct mjs *mjs);

MJS_PRIVATE struct mjs_object *new_object(struct mjs *);
MJS_PRIVATE struct mjs_property *new_property(struct mjs *);

MJS_PRIVATE void gc_mark(struct mjs *, mjs_val_t);

MJS_PRIVATE void gc_arena_init(struct gc_arena *, size_t, size_t, size_t);
MJS_PRIVATE void gc_arena_destroy(struct mjs *, struct gc_arena *a);
MJS_PRIVATE void gc_sweep(struct mjs *, struct gc_arena *, size_t);
MJS_PRIVATE void *gc_alloc_cell(struct mjs *, struct gc_arena *);

MJS_PRIVATE uint64_t gc_string_mjs_val_to_offset(mjs_val_t v);

/* return 0 if v is an object/function with a bad pointer */
MJS_PRIVATE int gc_check_val(struct mjs *mjs, mjs_val_t v);

/* checks whether a pointer is within the ranges of an arena */
MJS_PRIVATE int gc_check_ptr(const struct gc_arena *a, const void *p);

#endif /* MJS_GC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/primitive_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_PRIMITIVE_PUBLIC_H_
#define MJS_PRIMITIVE_PUBLIC_H_

/* Amalgamated: #include "mjs/core_public.h" */

/* JavaScript `null` value */
#define MJS_NULL ((uint64_t) 0xfffe << 48)

/* JavaScript `undefined` value */
#define MJS_UNDEFINED ((uint64_t) 0xfffd << 48)

/*
 * Make `null` primitive value.
 *
 * NOTE: this function is deprecated and will be removed in future releases.
 * Use `MJS_NULL` instead.
 */
mjs_val_t mjs_mk_null(void);

/* Returns true if given value is a primitive `null` value */
int mjs_is_null(mjs_val_t v);

/*
 * Make `undefined` primitive value.
 *
 * NOTE: this function is deprecated and will be removed in future releases.
 * Use `MJS_UNDEFINED` instead.
 */
mjs_val_t mjs_mk_undefined(void);

/* Returns true if given value is a primitive `undefined` value */
int mjs_is_undefined(mjs_val_t v);

/* Make numeric primitive value */
mjs_val_t mjs_mk_number(struct mjs *mjs, double num);

/*
 * Returns number value stored in `mjs_val_t` as `double`.
 *
 * Returns NaN for non-numbers.
 */
double mjs_get_double(struct mjs *mjs, mjs_val_t v);

/*
 * Returns number value stored in `mjs_val_t` as `int`. If the number value is
 * not an integer, the fraction part will be discarded.
 *
 * If the given value is a non-number, or NaN, the result is undefined.
 */
int mjs_get_int(struct mjs *mjs, mjs_val_t v);

/*
 * Like mjs_get_int but ensures that the returned type
 * is a 32-bit signed integer.
 */
int32_t mjs_get_int32(struct mjs *mjs, mjs_val_t v);

/* Returns true if given value is a primitive number value */
int mjs_is_number(mjs_val_t v);

/*
 * Make JavaScript value that holds C/C++ `void *` pointer.
 *
 * A foreign value is completely opaque and JS code cannot do anything useful
 * with it except holding it in properties and passing it around.
 * It behaves like a sealed object with no properties.
 *
 * NOTE:
 * Only valid pointers (as defined by each supported architecture) will fully
 * preserved. In particular, all supported 64-bit architectures (x86_64, ARM-64)
 * actually define a 48-bit virtual address space.
 * Foreign values will be sign-extended as required, i.e creating a foreign
 * value of something like `(void *) -1` will work as expected. This is
 * important because in some 64-bit OSs (e.g. Solaris) the user stack grows
 * downwards from the end of the address space.
 *
 * If you need to store exactly sizeof(void*) bytes of raw data where
 * `sizeof(void*)` >= 8, please use byte arrays instead.
 */
mjs_val_t mjs_mk_foreign(struct mjs *mjs, void *ptr);

/*
 * Returns `void *` pointer stored in `mjs_val_t`.
 *
 * Returns NULL if the value is not a foreign pointer.
 */
void *mjs_get_ptr(struct mjs *mjs, mjs_val_t v);

/* Returns true if given value holds `void *` pointer */
int mjs_is_foreign(mjs_val_t v);

#endif /* MJS_PRIMITIVE_PUBLIC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/primitive.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "mjs/primitive_public.h" */
/* Amalgamated: #include "mjs/internal.h" */

MJS_PRIVATE mjs_val_t pointer_to_value(void *p);
MJS_PRIVATE void *get_ptr(mjs_val_t v);
#ifdef MG_MODULE_LINES
#line 1 "mjs/object_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_OBJECT_PUBLIC_H_
#define MJS_OBJECT_PUBLIC_H_

/* Amalgamated: #include "mjs/core_public.h" */
#include <stddef.h>

/*
 * Returns true if the given value is an object or function.
 * i.e. it returns true if the value holds properties and can be
 * used as argument to `mjs_get`, `mjs_set` and `mjs_def`.
 */
int mjs_is_object(mjs_val_t v);

/* Make an empty object */
mjs_val_t mjs_mk_object(struct mjs *mjs);

/*
 * Lookup property `name` in object `obj`. If `obj` holds no such property,
 * an `undefined` value is returned.
 *
 * If `name_len` is ~0, `name` is assumed to be NUL-terminated and
 * `strlen(name)` is used.
 */
mjs_val_t mjs_get(struct mjs *mjs, mjs_val_t obj, const char *name,
    size_t name_len);

/*
 * Like mjs_get but with a JS string.
 */
mjs_val_t mjs_get_v(struct mjs *mjs, mjs_val_t obj, mjs_val_t name);

/*
 * Set object property. Behaves just like JavaScript assignment.
 */
mjs_err_t mjs_set(struct mjs *mjs, mjs_val_t obj, const char *name, size_t len,
    mjs_val_t val);

/*
 * Like mjs_set but the name is already a JS string.
 */
mjs_err_t mjs_set_v(struct mjs *mjs, mjs_val_t obj, mjs_val_t name,
    mjs_val_t val);


#endif /* MJS_OBJECT_PUBLIC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/object.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_OBJECT_H_
#define MJS_OBJECT_H_

/* Amalgamated: #include "mjs/object_public.h" */
/* Amalgamated: #include "mjs/internal.h" */

struct mjs;

struct mjs_property {
  struct mjs_property *next; /* Linkage in struct mjs_object::properties */
  mjs_val_t name;            /* Property name (a string) */
  mjs_val_t value;           /* Property value */
};

struct mjs_object {
  struct mjs_property *properties;
};

MJS_PRIVATE struct mjs_object *get_object_struct(mjs_val_t v);
MJS_PRIVATE struct mjs_property *mjs_get_own_property(struct mjs *mjs,
                                                      mjs_val_t obj,
                                                      const char *name,
                                                      size_t len);

#endif /* MJS_OBJECT_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/string_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_STRING_PUBLIC_H_
#define MJS_STRING_PUBLIC_H_

/* Amalgamated: #include "mjs/core_public.h" */

#define MJS_STRING_LITERAL_MAX_LEN 64

/*
 * Creates a string primitive value.
 * `str` must point to the utf8 string of length `len`.
 * If `len` is ~0, `str` is assumed to be NUL-terminated and `strlen(str)` is
 * used.
 *
 * If `copy` is non-zero, the string data is copied and owned by the GC. The
 * caller can free the string data afterwards. Otherwise (`copy` is zero), the
 * caller owns the string data, and is responsible for not freeing it while it
 * is used.
 */
mjs_val_t mjs_mk_string(struct mjs *mjs, const char *str, size_t len, int copy);

/* Returns true if given value is a primitive string value */
int mjs_is_string(mjs_val_t v);

/*
 * Returns a pointer to the string stored in `mjs_val_t`.
 *
 * String length returned in `len`, which is allowed to be NULL. Returns NULL
 * if the value is not a string.
 *
 * JS strings can contain embedded NUL chars and may or may not be NUL
 * terminated.
 *
 * CAUTION: creating new JavaScript object, array, or string may kick in a
 * garbage collector, which in turn may relocate string data and invalidate
 * pointer returned by `mjs_get_string()`.
 *
 * Short JS strings are embedded inside the `mjs_val_t` value itself. This
 * is why a pointer to a `mjs_val_t` is required. It also means that the string
 * data will become invalid once that `mjs_val_t` value goes out of scope.
 */
const char *mjs_get_string(struct mjs *mjs, mjs_val_t *v, size_t *len);

/*
 * Returns a pointer to the string stored in `mjs_val_t`.
 *
 * Returns NULL if the value is not a string or if the string is not compatible
 * with a C string.
 *
 * C compatible strings contain exactly one NUL char, in terminal position.
 *
 * All strings owned by the MJS engine (see `mjs_mk_string()`) are guaranteed to
 * be NUL terminated. Out of these, those that don't include embedded NUL chars
 * are guaranteed to be C compatible.
 */
const char *mjs_get_cstring(struct mjs *mjs, mjs_val_t *v);

/*
 * Returns the standard strcmp comparison code after comparing a JS string a
 * with a possibly non null-terminated string b. NOTE: the strings are equal
 * only if their length is equal, i.e. the len field doesn't imply strncmp
 * behaviour.
 */
int mjs_strcmp(struct mjs *mjs, mjs_val_t *a, const char *b, size_t len);

#endif /* MJS_STRING_PUBLIC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/string.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_STRING_H_
#define MJS_STRING_H_

/* Amalgamated: #include "mjs/string_public.h" */

/*
 * Size of the extra space for strings mbuf that is needed to avoid frequent
 * reallocations
 */
#define _MJS_STRING_BUF_RESERVE 500

#endif /* MJS_STRING_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/exec_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_EXEC_PUBLIC_H_
#define MJS_EXEC_PUBLIC_H_

/* Amalgamated: #include "mjs/core_public.h" */

mjs_err_t mjs_exec_buf(struct mjs *mjs, const char *src, size_t len,
    mjs_val_t *res);
mjs_err_t mjs_exec(struct mjs *mjs, const char *src, mjs_val_t *res);
mjs_err_t mjs_exec_file(struct mjs *mjs, const char *filename, mjs_val_t *res);

mjs_err_t mjs_call(struct mjs *mjs, mjs_val_t *res, mjs_val_t func, int nargs, ...);

#endif /* MJS_EXEC_PUBLIC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/exec.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_EXEC_H_
#define MJS_EXEC_H_

/* Amalgamated: #include "mjs/exec_public.h" */

/*
 * At the moment, all exec functions are public, and are declared in
 * `exec_public.h`
 */

#endif /* MJS_EXEC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "bazel-out/local-dbg-asan/genfiles/mjs/mjs.lem.h"
#endif
#define TOK_THEN                             1
#define TOK_ELSE                             2
#define TOK_ASSIGN                           3
#define TOK_PLUS_ASSIGN                      4
#define TOK_MINUS_ASSIGN                     5
#define TOK_MUL_ASSIGN                       6
#define TOK_DIV_ASSIGN                       7
#define TOK_REM_ASSIGN                       8
#define TOK_LSHIFT_ASSIGN                    9
#define TOK_RSHIFT_ASSIGN                   10
#define TOK_URSHIFT_ASSIGN                  11
#define TOK_AND_ASSIGN                      12
#define TOK_XOR_ASSIGN                      13
#define TOK_OR_ASSIGN                       14
#define TOK_LOGICAL_AND                     15
#define TOK_LOGICAL_OR                      16
#define TOK_OR                              17
#define TOK_XOR                             18
#define TOK_AND                             19
#define TOK_EQ                              20
#define TOK_NE                              21
#define TOK_EQ_EQ                           22
#define TOK_NE_NE                           23
#define TOK_LE                              24
#define TOK_LT                              25
#define TOK_GE                              26
#define TOK_GT                              27
#define TOK_LSHIFT                          28
#define TOK_RSHIFT                          29
#define TOK_URSHIFT                         30
#define TOK_PLUS                            31
#define TOK_MINUS                           32
#define TOK_MUL                             33
#define TOK_DIV                             34
#define TOK_REM                             35
#define TOK_PLUS_PLUS                       36
#define TOK_MINUS_MINUS                     37
#define TOK_NOT                             38
#define TOK_TILDA                           39
#define TOK_DOT                             40
#define TOK_OPEN_PAREN                      41
#define TOK_OPEN_BRACKET                    42
#define TOK_SEMICOLON                       43
#define TOK_LET                             44
#define TOK_COMMA                           45
#define TOK_IDENTIFIER                      46
#define TOK_CLOSE_PAREN                     47
#define TOK_CLOSE_BRACKET                   48
#define TOK_IF                              49
#define TOK_WHILE                           50
#define TOK_FOR                             51
#define TOK_OPEN_CURLY                      52
#define TOK_CLOSE_CURLY                     53
#define TOK_FUNCTION                        54
#define TOK_RETURN                          55
#define TOK_NULL                            56
#define TOK_UNDEFINED                       57
#define TOK_THIS                            58
#define TOK_NUMBER                          59
#define TOK_STRING_LITERAL                  60
#define TOK_TRUE                            61
#define TOK_FALSE                           62
#define TOK_COLON                           63
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

/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/mjs.lem.h" */
/* Amalgamated: #include "mjs/parser_state.h" */
/* Amalgamated: #include "mjs/tok.h" */

mjs_err_t mjs_parse_buf(struct mjs *mjs, const char *src, size_t len,
                        struct mjs_parse_ctx *ctx);
mjs_err_t mjs_parse(struct mjs *mjs, const char *src,
                    struct mjs_parse_ctx *ctx);
mjs_err_t mjs_parse_file(struct mjs *mjs, const char *file,
                         struct mjs_parse_ctx *ctx);

void mjs_dump_bcode(struct mjs *mjs, const char *filename, bf_word_ptr_t start,
                    bf_word_ptr_t end);

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
#line 1 "mjs/varint.h"
#endif
/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_VARINT_H_
#define MJS_VARINT_H_

/* Amalgamated: #include "mjs/internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

MJS_PRIVATE int encode_varint(size_t len, unsigned char *p);
MJS_PRIVATE size_t decode_varint(const unsigned char *p, int *llen);
MJS_PRIVATE int calc_llen(size_t len);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_VARINT_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/util_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_UTIL_PUBLIC_H_
#define MJS_UTIL_PUBLIC_H_

/* Amalgamated: #include "mjs/core_public.h" */
#include <stdio.h>

/* Output a string representation of the value to stdout. */
void mjs_print(struct mjs *mjs, mjs_val_t v);

/* Output a string representation of the value to stdout followed by nl. */
void mjs_println(struct mjs *mjs, mjs_val_t v);

/* Output a string representation of the value to a file. */
void mjs_fprint(FILE *f, struct mjs *mjs, mjs_val_t v);

/* Output a string representation of the value to a file followed by nl */
void mjs_fprintln(FILE *f, struct mjs *mjs, mjs_val_t v);

#endif /* MJS_UTIL_PUBLIC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/util.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_UTIL_H_
#define MJS_UTIL_H_

/* Amalgamated: #include "mjs/util_public.h" */

/*
 * At the moment, all utility functions are public, and are declared in
 * `util_public.h`
 */

#endif /* MJS_UTIL_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/str_util.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_STR_UTIL_H_
#define MJS_STR_UTIL_H_

/* Amalgamated: #include "mjs/internal.h" */

enum embstr_flags {
  EMBSTR_ZERO_TERM = (1 << 0),
  EMBSTR_UNESCAPE = (1 << 1),
};

struct mbuf;

MJS_PRIVATE size_t unescape(const char *s, size_t len, char *to);

MJS_PRIVATE void embed_string(struct mbuf *m, size_t offset, const char *p,
                              size_t len, uint8_t /*enum embstr_flags*/ flags);
#endif /* MJS_STR_UTIL_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs//internal.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_INTERNAL_H_
#define MJS_INTERNAL_H_

/* Amalgamated: #include "mjs/license.h" */

/* Amalgamated: #include "common/platform.h" */

#ifndef FAST
#define FAST
#endif

#ifndef STATIC
#define STATIC
#endif

#ifndef ENDL
#define ENDL "\n"
#endif

#ifdef MJS_EXPOSE_PRIVATE
#define MJS_PRIVATE
#define MJS_EXTERN extern
#else
#define MJS_PRIVATE static
#define MJS_EXTERN static
#endif

#endif /* MJS_INTERNAL_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs//varint.h"
#endif
/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_VARINT_H_
#define MJS_VARINT_H_

/* Amalgamated: #include "mjs/internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

MJS_PRIVATE int encode_varint(size_t len, unsigned char *p);
MJS_PRIVATE size_t decode_varint(const unsigned char *p, int *llen);
MJS_PRIVATE int calc_llen(size_t len);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_VARINT_H_ */
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

enum cs_log_level cs_log_level WEAK =
#if CS_ENABLE_DEBUG
    LL_VERBOSE_DEBUG;
#else
    LL_ERROR;
#endif

#if CS_ENABLE_STDIO

FILE *cs_log_file WEAK = NULL;

#if CS_LOG_ENABLE_TS_DIFF
double cs_log_ts WEAK;
#endif

void cs_log_print_prefix(const char *func) WEAK;
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

void cs_log_printf(const char *fmt, ...) WEAK;
void cs_log_printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(cs_log_file, fmt, ap);
  va_end(ap);
  fputc('\n', cs_log_file);
  fflush(cs_log_file);
}

void cs_log_set_file(FILE *file) WEAK;
void cs_log_set_file(FILE *file) {
  cs_log_file = file;
}

#endif /* CS_ENABLE_STDIO */

void cs_log_set_level(enum cs_log_level level) WEAK;
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
char *cs_read_file(const char *path, size_t *size) WEAK;
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
char *cs_mmap_file(const char *path, size_t *size) WEAK;
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

double cs_time(void) WEAK;
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

void mbuf_init(struct mbuf *mbuf, size_t initial_size) WEAK;
void mbuf_init(struct mbuf *mbuf, size_t initial_size) {
  mbuf->len = mbuf->size = 0;
  mbuf->buf = NULL;
  mbuf_resize(mbuf, initial_size);
}

void mbuf_free(struct mbuf *mbuf) WEAK;
void mbuf_free(struct mbuf *mbuf) {
  if (mbuf->buf != NULL) {
    MBUF_FREE(mbuf->buf);
    mbuf_init(mbuf, 0);
  }
}

void mbuf_resize(struct mbuf *a, size_t new_size) WEAK;
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

void mbuf_trim(struct mbuf *mbuf) WEAK;
void mbuf_trim(struct mbuf *mbuf) {
  mbuf_resize(mbuf, mbuf->len);
}

size_t mbuf_insert(struct mbuf *a, size_t off, const void *buf, size_t) WEAK;
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

size_t mbuf_append(struct mbuf *a, const void *buf, size_t len) WEAK;
size_t mbuf_append(struct mbuf *a, const void *buf, size_t len) {
  return mbuf_insert(a, a->len, buf, len);
}

void mbuf_remove(struct mbuf *mb, size_t n) WEAK;
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

int mg_ncasecmp(const char *s1, const char *s2, size_t len) WEAK;

struct mg_str mg_mk_str(const char *s) WEAK;
struct mg_str mg_mk_str(const char *s) {
  struct mg_str ret = {s, 0};
  if (s != NULL) ret.len = strlen(s);
  return ret;
}

struct mg_str mg_mk_str_n(const char *s, size_t len) WEAK;
struct mg_str mg_mk_str_n(const char *s, size_t len) {
  struct mg_str ret = {s, len};
  return ret;
}

int mg_vcmp(const struct mg_str *str1, const char *str2) WEAK;
int mg_vcmp(const struct mg_str *str1, const char *str2) {
  size_t n2 = strlen(str2), n1 = str1->len;
  int r = memcmp(str1->p, str2, (n1 < n2) ? n1 : n2);
  if (r == 0) {
    return n1 - n2;
  }
  return r;
}

int mg_vcasecmp(const struct mg_str *str1, const char *str2) WEAK;
int mg_vcasecmp(const struct mg_str *str1, const char *str2) {
  size_t n2 = strlen(str2), n1 = str1->len;
  int r = mg_ncasecmp(str1->p, str2, (n1 < n2) ? n1 : n2);
  if (r == 0) {
    return n1 - n2;
  }
  return r;
}

struct mg_str mg_strdup(const struct mg_str s) WEAK;
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

int mg_strcmp(const struct mg_str str1, const struct mg_str str2) WEAK;
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

int mg_strncmp(const struct mg_str, const struct mg_str, size_t n) WEAK;
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

size_t c_strnlen(const char *s, size_t maxlen) WEAK;
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
int c_vsnprintf(char *buf, size_t buf_size, const char *fmt, va_list ap) WEAK;
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

int c_vsnprintf(char *buf, size_t buf_size, const char *fmt, va_list ap) WEAK;
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

int c_snprintf(char *buf, size_t buf_size, const char *fmt, ...) WEAK;
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
const char *c_strnstr(const char *s, const char *find, size_t slen) WEAK;
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
char *strdup(const char *src) WEAK;
char *strdup(const char *src) {
  size_t len = strlen(src) + 1;
  char *ret = malloc(len);
  if (ret != NULL) {
    strcpy(ret, src);
  }
  return ret;
}
#endif

void cs_to_hex(char *to, const unsigned char *p, size_t len) WEAK;
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

void cs_from_hex(char *to, const char *p, size_t len) WEAK;
void cs_from_hex(char *to, const char *p, size_t len) {
  size_t i;

  for (i = 0; i < len; i += 2) {
    *to++ = (fourbit(p[i]) << 4) + fourbit(p[i + 1]);
  }
  *to = '\0';
}

#if CS_ENABLE_TO64
int64_t cs_to64(const char *s) WEAK;
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

int mg_ncasecmp(const char *s1, const char *s2, size_t len) WEAK;
int mg_ncasecmp(const char *s1, const char *s2, size_t len) {
  int diff = 0;

  if (len > 0) do {
      diff = str_util_lowercase(s1++) - str_util_lowercase(s2++);
    } while (diff == 0 && s1[-1] != '\0' && --len > 0);

  return diff;
}

int mg_casecmp(const char *s1, const char *s2) WEAK;
int mg_casecmp(const char *s1, const char *s2) {
  return mg_ncasecmp(s1, s2, (size_t) ~0);
}

int mg_asprintf(char **buf, size_t size, const char *fmt, ...) WEAK;
int mg_asprintf(char **buf, size_t size, const char *fmt, ...) {
  int ret;
  va_list ap;
  va_start(ap, fmt);
  ret = mg_avprintf(buf, size, fmt, ap);
  va_end(ap);
  return ret;
}

int mg_avprintf(char **buf, size_t size, const char *fmt, va_list ap) WEAK;
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
#line 1 "mjs/bf/bf.c"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

/*
 * Brainfarth is a simple FORTH-like language borrowing a few ideas from Factor
 * (https://factorcode.org/).
 * Brainfarth is not a general purpose programming language but instead it is
 * used to implement the MJS virtual machine.
 *
 * The binary encoding is documented in the bf compiler (see the
 * `bf_codegen` docstring).
 */

#include <assert.h>

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "mjs/bf/mem.h" */
/* Amalgamated: #include "mjs/bf/bf.h" */

static void bf_cb_stub(struct bf_vm *vm) {
  (void) vm;
}

static void bf_init_stack(struct bf_stack *stack) {
  stack->size = ARRAY_SIZE(stack->stack);
  stack->pos = 0;
}

void bf_destroy_vm(struct bf_vm *vm) {
  bf_destroy_mem(vm->iram);
}

void bf_init_vm(struct bf_vm *vm, struct bf_code *code, struct bf_callbacks *cb) {
  memset(vm, 0, sizeof(*vm));
  vm->code = code;

  /* Copy provided callbacks, if any */
  if (cb != NULL) {
    memcpy(&vm->cb, cb, sizeof(vm->cb));
  }

  /* Provide default no-op callback implementations */
  if (vm->cb.after_bf_enter == NULL) {
    vm->cb.after_bf_enter = bf_cb_stub;
  }

  bf_init_stack(&vm->dstack);
  bf_init_stack(&vm->rstack);

  vm->iram = bf_create_mem();
  if (code != NULL && code->opcodes != NULL) {
    bf_mmap(&vm->iram, code->opcodes, code->opcodes_len,
            FR_MEM_RO | FR_MEM_FOREIGN);
  }
}

static bf_opcode_t bf_fetch(struct bf_vm *vm, bf_word_ptr_t word) {
  if (word < 0) {
    return FR_EXIT_RUN;
  }
  return (bf_opcode_t) bf_read_byte(vm->iram, word);
}

static void bf_trace(struct bf_vm *vm) {
  bf_opcode_t op = bf_fetch(vm, vm->ip);
  bf_word_ptr_t word = bf_lookup_word(vm, op);
  char sword[128], pad[64];
  const char *pos_name = "???";
  const char *name = (op >= -1 ? vm->code->word_names[op + 1] : "<rel>");

  if (word < 0) {
    bf_native_t func = vm->code->native_words[-word - 1];
    snprintf(sword, sizeof(sword), "%s <%p>", name, func);
  } else {
    snprintf(sword, sizeof(sword), "%s (%04d)", name, word);
  }

  if ((size_t) vm->ip < vm->code->opcodes_len) {
    pos_name = vm->code->pos_names[vm->ip];
  }
  memset(pad, ' ', sizeof(pad));
  if (strlen(pos_name) <= 16) {
    pad[16 - strlen(pos_name)] = '\0';
  } else {
    pad[0] = '\0';
  }
  LOG(LL_DEBUG, (">> ip:%04X (%s)%sop:%02X -> %s", vm->ip, pos_name, pad,
                 (uint8_t) op, sword));
}

void bf_enter_thread(struct bf_vm *vm, bf_word_ptr_t word) {
  bf_push(&vm->rstack, bf_from_int(vm->ip));
  vm->ip = word;
}

void bf_enter(struct bf_vm *vm, bf_word_ptr_t word) {
  if (word >= 0 && bf_fetch(vm, vm->ip) == 0 && vm->rstack.pos > 0) {
    LOG(LL_DEBUG, ("tail recursion"));
    vm->ip = bf_to_int(bf_pop(&vm->rstack));
  }

  if (word < 0) {
    bf_native_t nat = vm->code->native_words[-word - 1];
    LOG(LL_DEBUG, ("calling native function %p", nat));
    nat(vm);
  } else {
    LOG(LL_DEBUG, ("%d is threaded word", word));
    bf_enter_thread(vm, word);
  }
}

void bf_run(struct bf_vm *vm, bf_word_ptr_t word) {
  bf_opcode_t op;
  vm->ip = word;

  /* push sentinel so we can exit the loop */
  bf_push(&vm->rstack, bf_from_int(FR_EXIT_RUN));

  while (vm->ip != FR_EXIT_RUN && bf_is_mapped(vm->iram, vm->ip)) {
    bf_trace(vm);

    op = bf_fetch(vm, vm->ip);
    vm->ip++;
    word = bf_lookup_word(vm, op);
    bf_enter(vm, word);

    /* Call user-provided callback */
    vm->cb.after_bf_enter(vm);
  }
}

bf_word_ptr_t bf_lookup_word(struct bf_vm *vm, bf_opcode_t op) {
  if (op < -1) {
    return vm->ip - 1 + op;
  } else {
    return vm->code->table[op + 1];
  }
}

void bf_push(struct bf_stack *stack, bf_cell_t value) {
  stack->stack[stack->pos] = value;
  stack->pos++;
}

bf_cell_t bf_pop(struct bf_stack *stack) {
  assert(stack->pos > 0);
  stack->pos--;
  return stack->stack[stack->pos];
}

bf_cell_t bf_tos(struct bf_stack *stack) {
  assert(stack->pos > 0);
  return stack->stack[stack->pos - 1];
}

void bf_print_stack(struct bf_vm *vm, struct bf_stack *stack) {
  size_t i;
  /* gforth style stack print */
  printf("<%zu> ", stack->pos);
  for (i = 0; i < stack->pos; i++) {
    bf_print_cell(vm, stack->stack[i]);
    printf(" ");
  }
}

void bf_op_todo(struct bf_vm *vm) {
  (void) vm;
  LOG(LL_ERROR, ("TODO: stub"));
}

void bf_op_quote(struct bf_vm *vm) {
  int16_t lit;
  (void) vm;
  lit = (uint8_t) bf_fetch(vm, vm->ip);
  lit <<= 8;
  lit |= (uint8_t) bf_fetch(vm, vm->ip + 1);
  vm->ip += 2;
  LOG(LL_DEBUG, ("quoting %d", lit));
  bf_push(&vm->dstack, bf_from_int(lit));
}

void bf_op_exit(struct bf_vm *vm) {
  vm->ip = bf_to_int(bf_pop(&vm->rstack));
}

void bf_op_drop(struct bf_vm *vm) {
  bf_pop(&vm->dstack);
}

void bf_op_dup(struct bf_vm *vm) {
  bf_cell_t v = bf_pop(&vm->dstack);
  /*
   * could be done more efficiently but this way we reuse the asserts and guards
   * in the stack primitives.
   */
  bf_push(&vm->dstack, v);
  bf_push(&vm->dstack, v);
}

void bf_op_swap(struct bf_vm *vm) {
  bf_cell_t a = bf_pop(&vm->dstack);
  bf_cell_t b = bf_pop(&vm->dstack);
  /*
   * could be done more efficiently but this way we reuse the asserts and guards
   * in the stack primitives.
   */
  bf_push(&vm->dstack, a);
  bf_push(&vm->dstack, b);
}

void bf_op_over(struct bf_vm *vm) {
  bf_cell_t b = bf_pop(&vm->dstack);
  bf_cell_t a = bf_pop(&vm->dstack);
  /*
   * could be done more efficiently but this way we reuse the asserts and guards
   * in the stack primitives.
   */
  bf_push(&vm->dstack, a);
  bf_push(&vm->dstack, b);
  bf_push(&vm->dstack, a);
}

void bf_op_neg_rot(struct bf_vm *vm) {
  bf_cell_t c = bf_pop(&vm->dstack);
  bf_cell_t b = bf_pop(&vm->dstack);
  bf_cell_t a = bf_pop(&vm->dstack);
  /*
   * could be done more efficiently but this way we reuse the asserts and guards
   * in the stack primitives.
   */
  bf_push(&vm->dstack, c);
  bf_push(&vm->dstack, a);
  bf_push(&vm->dstack, b);
}

void bf_op_pushr(struct bf_vm *vm) {
  bf_push(&vm->rstack, bf_pop(&vm->dstack));
}

void bf_op_popr(struct bf_vm *vm) {
  bf_push(&vm->dstack, bf_pop(&vm->rstack));
}

void bf_op_sp_save(struct bf_vm *vm) {
  bf_push(&vm->dstack, bf_from_int(vm->dstack.pos));
}

void bf_op_sp_restore(struct bf_vm *vm) {
  vm->dstack.pos = bf_to_int(bf_pop(&vm->dstack));
}

void bf_op_rp_save(struct bf_vm *vm) {
  bf_push(&vm->dstack, bf_from_int(vm->rstack.pos));
}

void bf_op_rp_restore(struct bf_vm *vm) {
  vm->rstack.pos = bf_to_int(bf_pop(&vm->dstack));
}

void bf_op_stash(struct bf_vm *vm) {
  vm->tmp = bf_pop(&vm->dstack);
}

void bf_op_unstash(struct bf_vm *vm) {
  bf_push(&vm->dstack, vm->tmp);
  vm->tmp = bf_from_int(0);
}

void bf_op_print(struct bf_vm *vm) {
  bf_cell_t v = bf_pop(&vm->dstack);
  bf_print_cell(vm, v);
}

void bf_op_cr(struct bf_vm *vm) {
  (void) vm;
  printf("\n");
}

void bf_op_print_stack(struct bf_vm *vm) {
  bf_print_stack(vm, &vm->dstack);
}

void bf_op_eq(struct bf_vm *vm) {
  bf_cell_t b = bf_pop(&vm->dstack);
  bf_cell_t a = bf_pop(&vm->dstack);
  bf_push(&vm->dstack, bf_from_int(a == b ? -1 : 0));
}

void bf_op_lt(struct bf_vm *vm) {
  bf_cell_t b = bf_pop(&vm->dstack);
  bf_cell_t a = bf_pop(&vm->dstack);
  bf_push(&vm->dstack, bf_from_int(bf_to_int(a) < bf_to_int(b) ? -1 : 0));
}

void bf_op_gt(struct bf_vm *vm) {
  bf_cell_t b = bf_pop(&vm->dstack);
  bf_cell_t a = bf_pop(&vm->dstack);
  bf_push(&vm->dstack, bf_from_int(bf_to_int(a) > bf_to_int(b) ? -1 : 0));
}

void bf_op_invert(struct bf_vm *vm) {
  bf_cell_t a = bf_pop(&vm->dstack);
  bf_push(&vm->dstack, bf_from_int(~bf_to_int(a)));
}

void bf_op_add(struct bf_vm *vm) {
  bf_cell_t b = bf_pop(&vm->dstack);
  bf_cell_t a = bf_pop(&vm->dstack);
  bf_push(&vm->dstack, bf_from_int(bf_to_int(a) + bf_to_int(b)));
}

void bf_op_sub(struct bf_vm *vm) {
  bf_cell_t b = bf_pop(&vm->dstack);
  bf_cell_t a = bf_pop(&vm->dstack);
  bf_push(&vm->dstack, bf_from_int(bf_to_int(a) - bf_to_int(b)));
}

void bf_op_mul(struct bf_vm *vm) {
  bf_cell_t b = bf_pop(&vm->dstack);
  bf_cell_t a = bf_pop(&vm->dstack);
  bf_push(&vm->dstack, bf_from_int(bf_to_int(a) * bf_to_int(b)));
}

void bf_op_call(struct bf_vm *vm) {
  bf_enter(vm, bf_to_int(bf_pop(&vm->dstack)));
}

void bf_op_if(struct bf_vm *vm) {
  bf_cell_t iftrue = bf_pop(&vm->dstack);
  bf_cell_t cond = bf_pop(&vm->dstack);
  if (bf_is_true(cond)) {
    bf_enter(vm, bf_to_int(iftrue));
  }
}

void bf_op_ifelse(struct bf_vm *vm) {
  bf_cell_t iffalse = bf_pop(&vm->dstack);
  bf_cell_t iftrue = bf_pop(&vm->dstack);
  bf_cell_t cond = bf_pop(&vm->dstack);
  bf_enter(vm, (bf_is_true(cond) ? bf_to_int(iftrue) : bf_to_int(iffalse)));
}

void bf_op_ndrop(struct bf_vm *vm) {
  bf_cell_t n = bf_pop(&vm->dstack);
  vm->dstack.pos -= bf_to_int(n);
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/bf/mem.c"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

/*
 * Brainfarth code has access to a 16-bit addressable memory,
 * mostly for storing code. The bf memory contains both
 * statically generated read-only code (possibly mapped on flash from
 * the rodata section) and dynamically generated code.
 *
 * This file contains MMU-liked abstraction that allows the VM to
 * address a unified 16-bit byte-addressed memory backed by a set
 * of smaller pages. Each page can point to either a read-only
 * code section, a buffer on heap and it's also possible to extend it in
 * the future to access external storage that doesn't provide a memory
 * interface to the CPU (e.g. byte ordiented filesystem API), useful
 * on many embedded platforms such as CC3200.
 */

#include <assert.h>

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "mjs/bf/mem.h" */

struct bf_mem *bf_create_mem() {
  size_t size = sizeof(struct bf_mem) - sizeof(struct bf_page);
  struct bf_mem *mem = (struct bf_mem *) calloc(1, size);
  mem->num_pages = 0;
  return mem;
}

void bf_destroy_mem(struct bf_mem *mem) {
  size_t i;
  for (i = 0; i < mem->num_pages; i++) {
    if (!(mem->pages[i].flags & FR_MEM_FOREIGN)) {
      free(mem->pages[i].base);
    }
  }
  free(mem);
}

static void bf_realloc_mem(struct bf_mem **mem) {
  size_t size =
      sizeof(struct bf_mem) + sizeof(struct bf_page) * ((*mem)->num_pages - 1);
  *mem = (struct bf_mem *) realloc(*mem, size);
}

bf_cell_t bf_mmap(struct bf_mem **mem, void *data, size_t data_len, int flags) {
  size_t i;
  size_t start_page = (*mem)->num_pages;
  size_t num_pages =
      data_len / FR_PAGE_SIZE + (data_len % FR_PAGE_SIZE == 0 ? 0 : 1);

  LOG(LL_DEBUG, ("mapping %d pages", num_pages));

  (*mem)->num_pages += num_pages;
  bf_realloc_mem(mem);

  for (i = 0; i < num_pages; i++) {
    struct bf_page *page = &(*mem)->pages[start_page + i];
    page->flags = flags;
    page->base = (char *) data + i * FR_PAGE_SIZE;
  }

  return start_page * FR_PAGE_SIZE;
}

int bf_is_mapped(struct bf_mem *mem, bf_cell_t addr) {
  uint16_t page = addr / FR_PAGE_SIZE;
  return page < mem->num_pages;
}

char bf_read_byte(struct bf_mem *mem, bf_cell_t addr) {
  uint16_t page = addr / FR_PAGE_SIZE;
  uint16_t off = addr % FR_PAGE_SIZE;
  assert(page < mem->num_pages);
  return ((char *) mem->pages[page].base)[off];
}

void bf_write_byte(struct bf_mem *mem, bf_cell_t addr, char value) {
  uint16_t page = addr / FR_PAGE_SIZE;
  uint16_t off = addr % FR_PAGE_SIZE;
  assert(page < mem->num_pages);

  /* TODO: make this disabled in release builds */
  if (mem->pages[page].flags & FR_MEM_RO) {
    LOG(LL_DEBUG,
        ("Trapping write access to read only bf memory at addr 0x%X", addr));
    return;
  }

  ((char *) mem->pages[page].base)[off] = value;
}
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
#line 18 "mjs/mjs.lem.c"

  #include <assert.h>
  #include <string.h>
/* Amalgamated:   #include "mjs/parser_state.h" */
/* Amalgamated:   #include "mjs/vm.gen.h" */
#line 35 "mjs/mjs.lem.c"
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
#define YYNOCODE 94
#define YYACTIONTYPE unsigned short int
#define mjsParserTOKENTYPE struct mjs_token
typedef union {
  int yyinit;
  mjsParserTOKENTYPE yy0;
  bf_word_ptr_t yy86;
  const char * yy110;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define mjsParserARG_SDECL struct mjs_parse_ctx *ctx;
#define mjsParserARG_PDECL ,struct mjs_parse_ctx *ctx
#define mjsParserARG_FETCH struct mjs_parse_ctx *ctx = yypParser->ctx
#define mjsParserARG_STORE yypParser->ctx = ctx
#define YYNSTATE             144
#define YYNRULE              107
#define YY_MAX_SHIFT         143
#define YY_MIN_SHIFTREDUCE   194
#define YY_MAX_SHIFTREDUCE   300
#define YY_MIN_REDUCE        301
#define YY_MAX_REDUCE        407
#define YY_ERROR_ACTION      408
#define YY_ACCEPT_ACTION     409
#define YY_NO_ACTION         410
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
#define YY_ACTTAB_COUNT (1193)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    53,   55,  114,  114,  238,   49,   51,   59,   57,  127,
 /*    10 */    33,   13,   11,   64,  141,   77,   10,   34,  138,  136,
 /*    20 */   135,   61,    5,   65,   30,  286,  287,  288,  242,  243,
 /*    30 */   293,  294,   53,   55,  119,  246,   63,   49,   51,   59,
 /*    40 */    57,   67,   33,   13,   12,   64,  228,   77,   10,   34,
 /*    50 */   138,  136,  135,   61,    7,   65,   30,  286,  287,  288,
 /*    60 */   242,  243,  293,  294,   53,   55,   10,   34,  140,   49,
 /*    70 */    51,   59,   57,  277,   33,   13,   66,   64,  239,   75,
 /*    80 */    10,   34,  138,  136,  135,   61,  225,   65,   30,  286,
 /*    90 */   287,  288,  242,  126,  293,  294,   53,   55,  295,  142,
 /*   100 */   142,   49,   51,   59,   57,  127,   33,   13,  284,   64,
 /*   110 */    63,   77,  296,  129,  138,  136,  135,    1,  252,   65,
 /*   120 */    30,  286,  287,  288,  242,  243,  293,  294,   53,   55,
 /*   130 */   236,  245,    2,   49,   51,   59,   57,   28,   33,   13,
 /*   140 */   297,   64,  403,   77,  265,  266,   10,   34,   37,   61,
 /*   150 */    29,   68,   30,  286,  287,  288,  242,  243,  293,  294,
 /*   160 */    53,   55,  235,  234,  281,   49,   51,   59,   57,   62,
 /*   170 */    33,   13,    4,   14,   15,   77,  227,  244,   16,   31,
 /*   180 */     6,   61,   32,   68,    3,  286,  287,  288,  242,  243,
 /*   190 */   293,  294,   46,   45,   44,   43,   52,   50,   48,   47,
 /*   200 */    58,   56,   54,   42,   41,   40,   39,   38,  265,  266,
 /*   210 */     9,   36,   60,   53,   55,   69,  301,  303,   49,   51,
 /*   220 */    59,   57,  303,   33,   13,  303,  303,  303,   77,  303,
 /*   230 */   303,  303,  303,  303,   61,  303,   68,  303,  286,  287,
 /*   240 */   288,  242,  243,  293,  294,   53,   55,  303,  303,  303,
 /*   250 */    49,   51,   59,   57,  303,   33,   13,  303,  303,  303,
 /*   260 */   226,  303,  303,  303,  303,  303,   61,  303,   68,  303,
 /*   270 */   286,  287,  288,  242,  243,  293,  294,   53,   55,  303,
 /*   280 */   303,  303,   49,   51,   59,   57,  303,   33,   13,  303,
 /*   290 */   303,  303,   76,  303,  303,  303,  303,  303,   61,  303,
 /*   300 */    68,  303,  286,  287,  288,  242,  243,  293,  294,  127,
 /*   310 */   303,  130,    8,  139,  200,  201,  303,  303,  122,   78,
 /*   320 */    70,   70,  303,  303,  303,  303,  200,  303,   70,  303,
 /*   330 */   303,   70,   70,   70,  119,  246,  303,  409,  143,    8,
 /*   340 */   139,  200,  201,  303,  303,  122,   78,   70,   70,  303,
 /*   350 */   303,  303,  303,  200,  303,   70,  303,  303,   70,   70,
 /*   360 */    70,  303,   52,   50,   48,   47,   58,   56,   54,   42,
 /*   370 */    41,   40,   39,   38,  265,  266,  303,  303,   37,  128,
 /*   380 */     8,  139,  200,  201,  303,  303,  122,   78,   70,   70,
 /*   390 */   303,  303,  303,  303,  200,  303,   70,  303,  303,   70,
 /*   400 */    70,   70,  125,    8,  139,  200,  201,  303,  303,  122,
 /*   410 */    78,   70,   70,  303,  303,  303,  303,  200,  303,   70,
 /*   420 */   303,  303,   70,   70,   70,  303,  322,  322,  322,  322,
 /*   430 */   322,  322,  322,  322,  322,  322,  322,  322,  278,  131,
 /*   440 */   303,  303,  122,   78,   70,   70,  303,  303,  278,  303,
 /*   450 */   278,  303,   70,  303,  303,   70,   70,   70,  233,  131,
 /*   460 */   303,  303,  122,   78,   70,   70,  303,  303,  233,  303,
 /*   470 */   233,  303,   70,  303,  303,   70,   70,   70,   40,   39,
 /*   480 */    38,  265,  266,  232,  131,   37,  402,  122,   78,   70,
 /*   490 */    70,  303,  303,  232,  303,  232,  303,   70,  303,  303,
 /*   500 */    70,   70,   70,  137,  131,  303,  303,  122,   78,   70,
 /*   510 */    70,  303,  303,  137,  303,  137,  303,   70,  303,  303,
 /*   520 */    70,   70,   70,  303,  364,  364,  364,  364,  364,  364,
 /*   530 */   364,  364,  364,  364,  364,  364,  322,  322,  322,  322,
 /*   540 */   322,  322,  322,  322,  322,  322,  322,  322,   35,   27,
 /*   550 */    26,   25,   24,   23,   22,   21,   20,   19,   18,   17,
 /*   560 */   196,  199,  303,  303,  122,   78,   70,   70,  303,  303,
 /*   570 */   303,  303,  196,  303,   70,  303,  303,   70,   70,   70,
 /*   580 */   195,  198,  303,  303,  122,   78,   70,   70,  303,  303,
 /*   590 */   303,  303,  195,  303,   70,  303,  303,   70,   70,   70,
 /*   600 */   303,   58,   56,   54,   42,   41,   40,   39,   38,  265,
 /*   610 */   266,  303,  303,   37,  102,   78,   70,   70,  101,  230,
 /*   620 */   303,  303,  303,  303,   70,  303,  303,   70,   70,   70,
 /*   630 */   197,  303,  303,  122,   78,   70,   70,  303,  303,  102,
 /*   640 */    78,   70,   70,   70,  229,  303,   70,   70,   70,   70,
 /*   650 */   303,  303,   70,   70,   70,  117,   78,   70,   70,  303,
 /*   660 */   303,  303,  303,  303,  303,   70,  303,  303,   70,   70,
 /*   670 */    70,  303,  303,  116,  121,   78,   70,   70,  303,  303,
 /*   680 */   303,  132,  303,  303,   70,  303,  303,   70,   70,   70,
 /*   690 */   121,   78,   70,   70,  303,  303,  303,  133,  303,  303,
 /*   700 */    70,  303,  303,   70,   70,   70,  303,  303,  121,   78,
 /*   710 */    70,   70,  303,  303,  303,  134,  303,  303,   70,  303,
 /*   720 */   303,   70,   70,   70,  103,   78,   70,   70,  303,  303,
 /*   730 */   104,   78,   70,   70,   70,  303,  303,   70,   70,   70,
 /*   740 */    70,  303,  303,   70,   70,   70,  303,  303,  105,   78,
 /*   750 */    70,   70,  303,  303,  303,  303,  303,  303,   70,  303,
 /*   760 */   303,   70,   70,   70,  106,   78,   70,   70,  303,  303,
 /*   770 */   303,  303,  303,  303,   70,  303,  303,   70,   70,   70,
 /*   780 */   107,   78,   70,   70,  303,  303,  108,   78,   70,   70,
 /*   790 */    70,  303,  303,   70,   70,   70,   70,  303,  303,   70,
 /*   800 */    70,   70,  109,   78,   70,   70,  303,  303,  110,   78,
 /*   810 */    70,   70,   70,  303,  303,   70,   70,   70,   70,  303,
 /*   820 */   303,   70,   70,   70,  111,   78,   70,   70,  303,  303,
 /*   830 */   303,  303,  303,  303,   70,  303,  303,   70,   70,   70,
 /*   840 */   112,   78,   70,   70,  303,  303,  303,  303,  303,  303,
 /*   850 */    70,  303,  303,   70,   70,   70,  113,   78,   70,   70,
 /*   860 */   303,  303,  115,   78,   70,   70,   70,  303,  303,   70,
 /*   870 */    70,   70,   70,  303,  303,   70,   70,   70,  118,   78,
 /*   880 */    70,   70,  303,  303,  120,   78,   70,   70,   70,  303,
 /*   890 */   303,   70,   70,   70,   70,  303,  303,   70,   70,   70,
 /*   900 */    91,   78,   70,   70,  303,  303,  303,  303,  303,  303,
 /*   910 */    70,  303,  303,   70,   70,   70,   92,   78,   70,   70,
 /*   920 */   303,  303,  303,  303,  303,  303,   70,  303,  303,   70,
 /*   930 */    70,   70,   93,   78,   70,   70,  303,  303,   90,   78,
 /*   940 */    70,   70,   70,  303,  303,   70,   70,   70,   70,  303,
 /*   950 */   303,   70,   70,   70,  123,   78,   70,   70,  303,  303,
 /*   960 */   124,   78,   70,   70,   70,  303,  303,   70,   70,   70,
 /*   970 */    70,  303,  303,   70,   70,   70,  303,   42,   41,   40,
 /*   980 */    39,   38,  265,  266,  303,  303,   37,  274,  274,  303,
 /*   990 */   303,  303,  303,   94,   94,  274,  303,  303,  274,  274,
 /*  1000 */   274,   94,  303,  303,   94,   94,   94,   95,   95,  303,
 /*  1010 */   303,  303,  303,  303,  303,   95,   96,   96,   95,   95,
 /*  1020 */    95,  303,  303,  303,   96,   86,   86,   96,   96,   96,
 /*  1030 */   303,   87,   87,   86,  303,  303,   86,   86,   86,   87,
 /*  1040 */    71,   71,   87,   87,   87,  303,   72,   72,   71,  303,
 /*  1050 */   303,   71,   71,   71,   72,   73,   73,   72,   72,   72,
 /*  1060 */   303,  303,  303,   73,   74,   74,   73,   73,   73,  303,
 /*  1070 */    81,   81,   74,  303,  303,   74,   74,   74,   81,  303,
 /*  1080 */   303,   81,   81,   81,   82,   82,  303,  303,  303,  303,
 /*  1090 */   303,  303,   82,   97,   97,   82,   82,   82,  303,  303,
 /*  1100 */   303,   97,   80,   80,   97,   97,   97,  303,   98,   98,
 /*  1110 */    80,  303,  303,   80,   80,   80,   98,   79,   79,   98,
 /*  1120 */    98,   98,  303,   88,   88,   79,  303,  303,   79,   79,
 /*  1130 */    79,   88,   85,   85,   88,   88,   88,  303,  303,  303,
 /*  1140 */    85,   89,   89,   85,   85,   85,  303,   84,   84,   89,
 /*  1150 */   303,  303,   89,   89,   89,   84,  303,  303,   84,   84,
 /*  1160 */    84,   99,   99,  303,  303,  303,  303,  303,  303,   99,
 /*  1170 */    83,   83,   99,   99,   99,  303,  303,  303,   83,  100,
 /*  1180 */   100,   83,   83,   83,  303,  303,  303,  100,  303,  303,
 /*  1190 */   100,  100,  100,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    31,   32,   85,   86,   46,   36,   37,   38,   39,   65,
 /*    10 */    41,   42,   43,   44,   46,   46,   41,   42,   49,   50,
 /*    20 */    51,   52,   47,   54,   55,   56,   57,   58,   59,   60,
 /*    30 */    61,   62,   31,   32,   90,   91,   41,   36,   37,   38,
 /*    40 */    39,   46,   41,   42,   45,   44,   47,   46,   41,   42,
 /*    50 */    49,   50,   51,   52,   47,   54,   55,   56,   57,   58,
 /*    60 */    59,   60,   61,   62,   31,   32,   41,   42,   83,   36,
 /*    70 */    37,   38,   39,   48,   41,   42,   45,   44,   47,   46,
 /*    80 */    41,   42,   49,   50,   51,   52,   47,   54,   55,   56,
 /*    90 */    57,   58,   59,   60,   61,   62,   31,   32,   46,   72,
 /*   100 */    73,   36,   37,   38,   39,   65,   41,   42,   86,   44,
 /*   110 */    41,   46,   60,   83,   49,   50,   51,   52,   73,   54,
 /*   120 */    55,   56,   57,   58,   59,   60,   61,   62,   31,   32,
 /*   130 */    53,   91,   52,   36,   37,   38,   39,   45,   41,   42,
 /*   140 */    48,   44,   63,   46,   36,   37,   41,   42,   40,   52,
 /*   150 */    63,   54,   55,   56,   57,   58,   59,   60,   61,   62,
 /*   160 */    31,   32,   53,   53,   43,   36,   37,   38,   39,   45,
 /*   170 */    41,   42,   47,   43,   43,   46,   47,   53,   41,   41,
 /*   180 */     2,   52,   41,   54,   52,   56,   57,   58,   59,   60,
 /*   190 */    61,   62,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   200 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
 /*   210 */    43,    3,   40,   31,   32,   45,    0,   93,   36,   37,
 /*   220 */    38,   39,   93,   41,   42,   93,   93,   93,   46,   93,
 /*   230 */    93,   93,   93,   93,   52,   93,   54,   93,   56,   57,
 /*   240 */    58,   59,   60,   61,   62,   31,   32,   93,   93,   93,
 /*   250 */    36,   37,   38,   39,   93,   41,   42,   93,   93,   93,
 /*   260 */    46,   93,   93,   93,   93,   93,   52,   93,   54,   93,
 /*   270 */    56,   57,   58,   59,   60,   61,   62,   31,   32,   93,
 /*   280 */    93,   93,   36,   37,   38,   39,   93,   41,   42,   93,
 /*   290 */    93,   93,   46,   93,   93,   93,   93,   93,   52,   93,
 /*   300 */    54,   93,   56,   57,   58,   59,   60,   61,   62,   65,
 /*   310 */    93,   67,   68,   69,   70,   71,   93,   93,   74,   75,
 /*   320 */    76,   77,   93,   93,   93,   93,   82,   93,   84,   93,
 /*   330 */    93,   87,   88,   89,   90,   91,   93,   66,   67,   68,
 /*   340 */    69,   70,   71,   93,   93,   74,   75,   76,   77,   93,
 /*   350 */    93,   93,   93,   82,   93,   84,   93,   93,   87,   88,
 /*   360 */    89,   93,   24,   25,   26,   27,   28,   29,   30,   31,
 /*   370 */    32,   33,   34,   35,   36,   37,   93,   93,   40,   67,
 /*   380 */    68,   69,   70,   71,   93,   93,   74,   75,   76,   77,
 /*   390 */    93,   93,   93,   93,   82,   93,   84,   93,   93,   87,
 /*   400 */    88,   89,   67,   68,   69,   70,   71,   93,   93,   74,
 /*   410 */    75,   76,   77,   93,   93,   93,   93,   82,   93,   84,
 /*   420 */    93,   93,   87,   88,   89,   93,    3,    4,    5,    6,
 /*   430 */     7,    8,    9,   10,   11,   12,   13,   14,   70,   71,
 /*   440 */    93,   93,   74,   75,   76,   77,   93,   93,   80,   93,
 /*   450 */    82,   93,   84,   93,   93,   87,   88,   89,   70,   71,
 /*   460 */    93,   93,   74,   75,   76,   77,   93,   93,   80,   93,
 /*   470 */    82,   93,   84,   93,   93,   87,   88,   89,   33,   34,
 /*   480 */    35,   36,   37,   70,   71,   40,   63,   74,   75,   76,
 /*   490 */    77,   93,   93,   80,   93,   82,   93,   84,   93,   93,
 /*   500 */    87,   88,   89,   70,   71,   93,   93,   74,   75,   76,
 /*   510 */    77,   93,   93,   80,   93,   82,   93,   84,   93,   93,
 /*   520 */    87,   88,   89,   93,    3,    4,    5,    6,    7,    8,
 /*   530 */     9,   10,   11,   12,   13,   14,    3,    4,    5,    6,
 /*   540 */     7,    8,    9,   10,   11,   12,   13,   14,    3,    4,
 /*   550 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   560 */    70,   71,   93,   93,   74,   75,   76,   77,   93,   93,
 /*   570 */    93,   93,   82,   93,   84,   93,   93,   87,   88,   89,
 /*   580 */    70,   71,   93,   93,   74,   75,   76,   77,   93,   93,
 /*   590 */    93,   93,   82,   93,   84,   93,   93,   87,   88,   89,
 /*   600 */    93,   28,   29,   30,   31,   32,   33,   34,   35,   36,
 /*   610 */    37,   93,   93,   40,   74,   75,   76,   77,   78,   79,
 /*   620 */    93,   93,   93,   93,   84,   93,   93,   87,   88,   89,
 /*   630 */    71,   93,   93,   74,   75,   76,   77,   93,   93,   74,
 /*   640 */    75,   76,   77,   84,   79,   93,   87,   88,   89,   84,
 /*   650 */    93,   93,   87,   88,   89,   74,   75,   76,   77,   93,
 /*   660 */    93,   93,   93,   93,   93,   84,   93,   93,   87,   88,
 /*   670 */    89,   93,   93,   92,   74,   75,   76,   77,   93,   93,
 /*   680 */    93,   81,   93,   93,   84,   93,   93,   87,   88,   89,
 /*   690 */    74,   75,   76,   77,   93,   93,   93,   81,   93,   93,
 /*   700 */    84,   93,   93,   87,   88,   89,   93,   93,   74,   75,
 /*   710 */    76,   77,   93,   93,   93,   81,   93,   93,   84,   93,
 /*   720 */    93,   87,   88,   89,   74,   75,   76,   77,   93,   93,
 /*   730 */    74,   75,   76,   77,   84,   93,   93,   87,   88,   89,
 /*   740 */    84,   93,   93,   87,   88,   89,   93,   93,   74,   75,
 /*   750 */    76,   77,   93,   93,   93,   93,   93,   93,   84,   93,
 /*   760 */    93,   87,   88,   89,   74,   75,   76,   77,   93,   93,
 /*   770 */    93,   93,   93,   93,   84,   93,   93,   87,   88,   89,
 /*   780 */    74,   75,   76,   77,   93,   93,   74,   75,   76,   77,
 /*   790 */    84,   93,   93,   87,   88,   89,   84,   93,   93,   87,
 /*   800 */    88,   89,   74,   75,   76,   77,   93,   93,   74,   75,
 /*   810 */    76,   77,   84,   93,   93,   87,   88,   89,   84,   93,
 /*   820 */    93,   87,   88,   89,   74,   75,   76,   77,   93,   93,
 /*   830 */    93,   93,   93,   93,   84,   93,   93,   87,   88,   89,
 /*   840 */    74,   75,   76,   77,   93,   93,   93,   93,   93,   93,
 /*   850 */    84,   93,   93,   87,   88,   89,   74,   75,   76,   77,
 /*   860 */    93,   93,   74,   75,   76,   77,   84,   93,   93,   87,
 /*   870 */    88,   89,   84,   93,   93,   87,   88,   89,   74,   75,
 /*   880 */    76,   77,   93,   93,   74,   75,   76,   77,   84,   93,
 /*   890 */    93,   87,   88,   89,   84,   93,   93,   87,   88,   89,
 /*   900 */    74,   75,   76,   77,   93,   93,   93,   93,   93,   93,
 /*   910 */    84,   93,   93,   87,   88,   89,   74,   75,   76,   77,
 /*   920 */    93,   93,   93,   93,   93,   93,   84,   93,   93,   87,
 /*   930 */    88,   89,   74,   75,   76,   77,   93,   93,   74,   75,
 /*   940 */    76,   77,   84,   93,   93,   87,   88,   89,   84,   93,
 /*   950 */    93,   87,   88,   89,   74,   75,   76,   77,   93,   93,
 /*   960 */    74,   75,   76,   77,   84,   93,   93,   87,   88,   89,
 /*   970 */    84,   93,   93,   87,   88,   89,   93,   31,   32,   33,
 /*   980 */    34,   35,   36,   37,   93,   93,   40,   76,   77,   93,
 /*   990 */    93,   93,   93,   76,   77,   84,   93,   93,   87,   88,
 /*  1000 */    89,   84,   93,   93,   87,   88,   89,   76,   77,   93,
 /*  1010 */    93,   93,   93,   93,   93,   84,   76,   77,   87,   88,
 /*  1020 */    89,   93,   93,   93,   84,   76,   77,   87,   88,   89,
 /*  1030 */    93,   76,   77,   84,   93,   93,   87,   88,   89,   84,
 /*  1040 */    76,   77,   87,   88,   89,   93,   76,   77,   84,   93,
 /*  1050 */    93,   87,   88,   89,   84,   76,   77,   87,   88,   89,
 /*  1060 */    93,   93,   93,   84,   76,   77,   87,   88,   89,   93,
 /*  1070 */    76,   77,   84,   93,   93,   87,   88,   89,   84,   93,
 /*  1080 */    93,   87,   88,   89,   76,   77,   93,   93,   93,   93,
 /*  1090 */    93,   93,   84,   76,   77,   87,   88,   89,   93,   93,
 /*  1100 */    93,   84,   76,   77,   87,   88,   89,   93,   76,   77,
 /*  1110 */    84,   93,   93,   87,   88,   89,   84,   76,   77,   87,
 /*  1120 */    88,   89,   93,   76,   77,   84,   93,   93,   87,   88,
 /*  1130 */    89,   84,   76,   77,   87,   88,   89,   93,   93,   93,
 /*  1140 */    84,   76,   77,   87,   88,   89,   93,   76,   77,   84,
 /*  1150 */    93,   93,   87,   88,   89,   84,   93,   93,   87,   88,
 /*  1160 */    89,   76,   77,   93,   93,   93,   93,   93,   93,   84,
 /*  1170 */    76,   77,   87,   88,   89,   93,   93,   93,   84,   76,
 /*  1180 */    77,   87,   88,   89,   93,   93,   93,   84,   93,   93,
 /*  1190 */    87,   88,   89,
};
#define YY_SHIFT_USE_DFLT (1193)
#define YY_SHIFT_COUNT    (143)
#define YY_SHIFT_MIN      (-42)
#define YY_SHIFT_MAX      (946)
static const short yy_shift_ofst[] = {
 /*     0 */     1,   33,    1,    1,   65,   65,   65,   65,  -31,    1,
 /*    10 */   129,   97,  182,  182,  182,  182,  182,  182,  182,  182,
 /*    20 */   182,  182,  182,  182,  182,  182,  182,  182,  182,  182,
 /*    30 */   182,  182,  182,  182,  182,  182,  182,  214,  214,  214,
 /*    40 */   214,  214,  214,  214,  214,  214,  214,  214,  214,  214,
 /*    50 */   214,  214,  214,  214,  214,  214,  214,  214,  214,  214,
 /*    60 */   246,   52,   52,  -42,  -32,   -5,  -42,   69,   69,  -32,
 /*    70 */   172,  338,  338,  338,  338,  423,  521,  533,  545,  573,
 /*    80 */   573,  573,  573,  946,  946,  946,  445,  445,  445,  445,
 /*    90 */    25,  -25,    7,   39,  108,  108,  108,  108,  108,  108,
 /*   100 */   108,   -1,  105,  105,  105,  105,  105,  105,  105,  105,
 /*   110 */   105,  105,  105,  105,   31,  105,   92,  105,  105,  124,
 /*   120 */   105,  105,  105,  105,  105,   77,   79,   87,  109,   80,
 /*   130 */   110,  121,  125,  130,  131,  137,  138,  178,  141,  167,
 /*   140 */   132,  208,  170,  216,
};
#define YY_REDUCE_USE_DFLT (-84)
#define YY_REDUCE_COUNT (69)
#define YY_REDUCE_MIN   (-83)
#define YY_REDUCE_MAX   (1103)
static const short yy_reduce_ofst[] = {
 /*     0 */   271,  244,  312,  335,  368,  388,  413,  433,  490,  510,
 /*    10 */   540,  559,  565,  581,  600,  616,  634,  650,  656,  674,
 /*    20 */   690,  706,  712,  728,  734,  750,  766,  782,  788,  804,
 /*    30 */   810,  826,  842,  858,  864,  880,  886,  911,  917,  931,
 /*    40 */   940,  949,  955,  964,  970,  979,  988,  994, 1008, 1017,
 /*    50 */  1026, 1032, 1041, 1047, 1056, 1065, 1071, 1085, 1094, 1103,
 /*    60 */   911,  -56,   40,  -83,   27,  -15,   22,   30,  -15,   45,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   408,  354,  408,  408,  408,  408,  408,  408,  356,  309,
 /*    10 */   408,  408,  408,  407,  386,  386,  386,  408,  408,  408,
 /*    20 */   408,  408,  408,  408,  408,  408,  408,  408,  408,  408,
 /*    30 */   347,  408,  408,  408,  408,  408,  408,  408,  408,  408,
 /*    40 */   408,  408,  408,  408,  408,  408,  408,  408,  408,  408,
 /*    50 */   408,  408,  408,  408,  408,  408,  408,  408,  408,  408,
 /*    60 */   408,  354,  408,  344,  408,  408,  408,  408,  408,  408,
 /*    70 */   365,  378,  377,  328,  327,  333,  333,  333,  408,  323,
 /*    80 */   324,  326,  325,  374,  375,  376,  330,  329,  369,  368,
 /*    90 */   408,  408,  408,  408,  380,  379,  331,  371,  370,  367,
 /*   100 */   366,  408,  383,  321,  320,  319,  318,  317,  316,  315,
 /*   110 */   314,  313,  312,  311,  408,  405,  408,  406,  355,  408,
 /*   120 */   348,  387,  363,  310,  361,  408,  350,  408,  408,  408,
 /*   130 */   408,  408,  408,  408,  408,  408,  408,  338,  408,  357,
 /*   140 */   408,  362,  358,  408,
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
  "$",             "THEN",          "ELSE",          "ASSIGN",      
  "PLUS_ASSIGN",   "MINUS_ASSIGN",  "MUL_ASSIGN",    "DIV_ASSIGN",  
  "REM_ASSIGN",    "LSHIFT_ASSIGN",  "RSHIFT_ASSIGN",  "URSHIFT_ASSIGN",
  "AND_ASSIGN",    "XOR_ASSIGN",    "OR_ASSIGN",     "LOGICAL_AND", 
  "LOGICAL_OR",    "OR",            "XOR",           "AND",         
  "EQ",            "NE",            "EQ_EQ",         "NE_NE",       
  "LE",            "LT",            "GE",            "GT",          
  "LSHIFT",        "RSHIFT",        "URSHIFT",       "PLUS",        
  "MINUS",         "MUL",           "DIV",           "REM",         
  "PLUS_PLUS",     "MINUS_MINUS",   "NOT",           "TILDA",       
  "DOT",           "OPEN_PAREN",    "OPEN_BRACKET",  "SEMICOLON",   
  "LET",           "COMMA",         "IDENTIFIER",    "CLOSE_PAREN", 
  "CLOSE_BRACKET",  "IF",            "WHILE",         "FOR",         
  "OPEN_CURLY",    "CLOSE_CURLY",   "FUNCTION",      "RETURN",      
  "NULL",          "UNDEFINED",     "THIS",          "NUMBER",      
  "STRING_LITERAL",  "TRUE",          "FALSE",         "COLON",       
  "error",         "objspeclhs",    "program",       "stmtlist",    
  "cstmtlist",     "sstmtlist",     "cstmt",         "sstmt",       
  "letspecs",      "letspec",       "expr",          "lhs",         
  "sexp",          "literal",       "callarglist",   "callarg",     
  "block",         "optexpr",       "funcdecl",      "arglistparen",
  "func_literal",  "arglist",       "argspec",       "boolean_literal",
  "object_literal",  "array_literal",  "objspeclist",   "objspec",     
  "arrayspeclist",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= stmtlist",
 /*   1 */ "cstmtlist ::= sstmtlist SEMICOLON cstmt",
 /*   2 */ "cstmtlist ::= cstmtlist cstmt",
 /*   3 */ "sstmtlist ::= cstmtlist SEMICOLON sstmt",
 /*   4 */ "sstmtlist ::= sstmtlist SEMICOLON sstmt",
 /*   5 */ "sstmtlist ::= cstmtlist sstmt",
 /*   6 */ "cstmtlist ::= cstmt",
 /*   7 */ "sstmtlist ::= sstmt",
 /*   8 */ "sstmtlist ::= sstmtlist SEMICOLON",
 /*   9 */ "expr ::= lhs ASSIGN expr",
 /*  10 */ "expr ::= lhs PLUS_ASSIGN expr",
 /*  11 */ "expr ::= lhs MINUS_ASSIGN expr",
 /*  12 */ "expr ::= lhs MUL_ASSIGN expr",
 /*  13 */ "expr ::= lhs DIV_ASSIGN expr",
 /*  14 */ "expr ::= lhs REM_ASSIGN expr",
 /*  15 */ "expr ::= lhs LSHIFT_ASSIGN expr",
 /*  16 */ "expr ::= lhs RSHIFT_ASSIGN expr",
 /*  17 */ "expr ::= lhs URSHIFT_ASSIGN expr",
 /*  18 */ "expr ::= lhs AND_ASSIGN expr",
 /*  19 */ "expr ::= lhs XOR_ASSIGN expr",
 /*  20 */ "expr ::= lhs OR_ASSIGN expr",
 /*  21 */ "lhs ::= IDENTIFIER",
 /*  22 */ "sexp ::= sexp LE sexp",
 /*  23 */ "sexp ::= sexp LT sexp",
 /*  24 */ "sexp ::= sexp GE sexp",
 /*  25 */ "sexp ::= sexp GT sexp",
 /*  26 */ "sexp ::= sexp EQ sexp",
 /*  27 */ "sexp ::= sexp NE sexp",
 /*  28 */ "sexp ::= sexp PLUS sexp",
 /*  29 */ "sexp ::= sexp MINUS sexp",
 /*  30 */ "sexp ::= sexp MUL sexp",
 /*  31 */ "sexp ::= OPEN_PAREN expr CLOSE_PAREN",
 /*  32 */ "sexp ::= IDENTIFIER",
 /*  33 */ "expr ::= expr OPEN_PAREN CLOSE_PAREN",
 /*  34 */ "expr ::= expr OPEN_PAREN callarglist CLOSE_PAREN",
 /*  35 */ "callarglist ::= callarglist COMMA callarg",
 /*  36 */ "callarglist ::= callarg",
 /*  37 */ "cstmt ::= IF OPEN_PAREN expr CLOSE_PAREN block",
 /*  38 */ "cstmt ::= IF OPEN_PAREN expr CLOSE_PAREN block ELSE block",
 /*  39 */ "cstmt ::= WHILE OPEN_PAREN expr CLOSE_PAREN block",
 /*  40 */ "block ::= OPEN_CURLY stmtlist CLOSE_CURLY",
 /*  41 */ "funcdecl ::= FUNCTION IDENTIFIER arglistparen OPEN_CURLY stmtlist CLOSE_CURLY",
 /*  42 */ "func_literal ::= FUNCTION arglistparen OPEN_CURLY stmtlist CLOSE_CURLY",
 /*  43 */ "arglist ::=",
 /*  44 */ "argspec ::= IDENTIFIER",
 /*  45 */ "arglistparen ::= OPEN_PAREN arglist CLOSE_PAREN",
 /*  46 */ "sstmt ::= RETURN",
 /*  47 */ "sstmt ::= RETURN expr",
 /*  48 */ "literal ::= NUMBER",
 /*  49 */ "literal ::= STRING_LITERAL",
 /*  50 */ "object_literal ::= OPEN_CURLY objspeclist CLOSE_CURLY",
 /*  51 */ "objspeclist ::= objspeclist COMMA objspec",
 /*  52 */ "objspeclist ::= objspec",
 /*  53 */ "objspeclist ::=",
 /*  54 */ "objspec ::= objspeclhs COLON expr",
 /*  55 */ "stmtlist ::= cstmtlist",
 /*  56 */ "stmtlist ::= sstmtlist",
 /*  57 */ "sstmt ::= LET letspecs",
 /*  58 */ "letspecs ::= letspecs COMMA letspec",
 /*  59 */ "letspecs ::= letspec",
 /*  60 */ "letspec ::= IDENTIFIER ASSIGN expr",
 /*  61 */ "letspec ::= IDENTIFIER",
 /*  62 */ "sstmt ::= expr",
 /*  63 */ "lhs ::= sexp DOT IDENTIFIER",
 /*  64 */ "expr ::= sexp",
 /*  65 */ "sexp ::= NOT sexp",
 /*  66 */ "sexp ::= TILDA sexp",
 /*  67 */ "sexp ::= MINUS sexp",
 /*  68 */ "sexp ::= PLUS sexp",
 /*  69 */ "sexp ::= MINUS_MINUS sexp",
 /*  70 */ "sexp ::= PLUS_PLUS sexp",
 /*  71 */ "sexp ::= sexp PLUS_PLUS",
 /*  72 */ "sexp ::= sexp MINUS_MINUS",
 /*  73 */ "sexp ::= sexp LSHIFT sexp",
 /*  74 */ "sexp ::= sexp RSHIFT sexp",
 /*  75 */ "sexp ::= sexp URSHIFT sexp",
 /*  76 */ "sexp ::= sexp EQ_EQ sexp",
 /*  77 */ "sexp ::= sexp NE_NE sexp",
 /*  78 */ "sexp ::= sexp DIV sexp",
 /*  79 */ "sexp ::= sexp REM sexp",
 /*  80 */ "sexp ::= sexp DOT sexp",
 /*  81 */ "sexp ::= literal",
 /*  82 */ "callarg ::= expr",
 /*  83 */ "expr ::= expr OPEN_BRACKET expr CLOSE_BRACKET",
 /*  84 */ "cstmt ::= FOR OPEN_PAREN optexpr SEMICOLON optexpr SEMICOLON optexpr CLOSE_PAREN block",
 /*  85 */ "optexpr ::=",
 /*  86 */ "optexpr ::= expr",
 /*  87 */ "block ::= sstmt SEMICOLON",
 /*  88 */ "block ::= cstmt",
 /*  89 */ "cstmt ::= funcdecl",
 /*  90 */ "arglist ::= arglist COMMA argspec",
 /*  91 */ "arglist ::= argspec",
 /*  92 */ "literal ::= NULL",
 /*  93 */ "literal ::= UNDEFINED",
 /*  94 */ "literal ::= THIS",
 /*  95 */ "literal ::= boolean_literal",
 /*  96 */ "literal ::= func_literal",
 /*  97 */ "literal ::= object_literal",
 /*  98 */ "literal ::= array_literal",
 /*  99 */ "boolean_literal ::= TRUE",
 /* 100 */ "boolean_literal ::= FALSE",
 /* 101 */ "objspeclhs ::= IDENTIFIER",
 /* 102 */ "objspeclhs ::= STRING_LITERAL",
 /* 103 */ "array_literal ::= OPEN_BRACKET arrayspeclist CLOSE_BRACKET",
 /* 104 */ "arrayspeclist ::= arrayspeclist COMMA expr",
 /* 105 */ "arrayspeclist ::= expr",
 /* 106 */ "arrayspeclist ::=",
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
    case 66: /* program */
{
#line 41 "mjs/mjs.lem.c"

  (void) ctx;
  (void) yypminor;

#line 845 "mjs/mjs.lem.c"
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
#line 36 "mjs/mjs.lem.c"

  printf("Giving up.  Parser stack overflow\n");
#line 1019 "mjs/mjs.lem.c"
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
  { 66, 1 },
  { 68, 3 },
  { 68, 2 },
  { 69, 3 },
  { 69, 3 },
  { 69, 2 },
  { 68, 1 },
  { 69, 1 },
  { 69, 2 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 74, 3 },
  { 75, 1 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 1 },
  { 74, 3 },
  { 74, 4 },
  { 78, 3 },
  { 78, 1 },
  { 70, 5 },
  { 70, 7 },
  { 70, 5 },
  { 80, 3 },
  { 82, 6 },
  { 84, 5 },
  { 85, 0 },
  { 86, 1 },
  { 83, 3 },
  { 71, 1 },
  { 71, 2 },
  { 77, 1 },
  { 77, 1 },
  { 88, 3 },
  { 90, 3 },
  { 90, 1 },
  { 90, 0 },
  { 91, 3 },
  { 67, 1 },
  { 67, 1 },
  { 71, 2 },
  { 72, 3 },
  { 72, 1 },
  { 73, 3 },
  { 73, 1 },
  { 71, 1 },
  { 75, 3 },
  { 74, 1 },
  { 76, 2 },
  { 76, 2 },
  { 76, 2 },
  { 76, 2 },
  { 76, 2 },
  { 76, 2 },
  { 76, 2 },
  { 76, 2 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 3 },
  { 76, 1 },
  { 79, 1 },
  { 74, 4 },
  { 70, 9 },
  { 81, 0 },
  { 81, 1 },
  { 80, 2 },
  { 80, 1 },
  { 70, 1 },
  { 85, 3 },
  { 85, 1 },
  { 77, 1 },
  { 77, 1 },
  { 77, 1 },
  { 77, 1 },
  { 77, 1 },
  { 77, 1 },
  { 77, 1 },
  { 87, 1 },
  { 87, 1 },
  { 65, 1 },
  { 65, 1 },
  { 89, 3 },
  { 92, 3 },
  { 92, 1 },
  { 92, 0 },
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
        YYMINORTYPE yylhsminor;
      case 0: /* program ::= stmtlist */
#line 63 "mjs/mjs.lem.c"
{ ctx->state = 1; ctx->entry = yymsp[0].minor.yy86; }
#line 1264 "mjs/mjs.lem.c"
        break;
      case 1: /* cstmtlist ::= sstmtlist SEMICOLON cstmt */
      case 3: /* sstmtlist ::= cstmtlist SEMICOLON sstmt */ yytestcase(yyruleno==3);
      case 4: /* sstmtlist ::= sstmtlist SEMICOLON sstmt */ yytestcase(yyruleno==4);
#line 81 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_add_stmt(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86); }
#line 1271 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 2: /* cstmtlist ::= cstmtlist cstmt */
      case 5: /* sstmtlist ::= cstmtlist sstmt */ yytestcase(yyruleno==5);
#line 82 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_add_stmt(ctx, yymsp[-1].minor.yy86, yymsp[0].minor.yy86); }
#line 1278 "mjs/mjs.lem.c"
  yymsp[-1].minor.yy86 = yylhsminor.yy86;
        break;
      case 6: /* cstmtlist ::= cstmt */
      case 7: /* sstmtlist ::= sstmt */ yytestcase(yyruleno==7);
#line 86 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_call(ctx, yymsp[0].minor.yy86); mjs_emit(ctx, MJS_OP_exit); }
#line 1285 "mjs/mjs.lem.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 8: /* sstmtlist ::= sstmtlist SEMICOLON */
#line 89 "mjs/mjs.lem.c"
{ yylhsminor.yy86=yymsp[-1].minor.yy86; }
#line 1291 "mjs/mjs.lem.c"
  yymsp[-1].minor.yy86 = yylhsminor.yy86;
        break;
      case 9: /* expr ::= lhs ASSIGN expr */
#line 102 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, 0); }
#line 1297 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 10: /* expr ::= lhs PLUS_ASSIGN expr */
#line 103 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_PLUS); }
#line 1303 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 11: /* expr ::= lhs MINUS_ASSIGN expr */
#line 104 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_MINUS); }
#line 1309 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 12: /* expr ::= lhs MUL_ASSIGN expr */
#line 105 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_STAR); }
#line 1315 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 13: /* expr ::= lhs DIV_ASSIGN expr */
#line 106 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_div); }
#line 1321 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 14: /* expr ::= lhs REM_ASSIGN expr */
#line 107 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_rem); }
#line 1327 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 15: /* expr ::= lhs LSHIFT_ASSIGN expr */
#line 108 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_lshift); }
#line 1333 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 16: /* expr ::= lhs RSHIFT_ASSIGN expr */
#line 109 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_rshift); }
#line 1339 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 17: /* expr ::= lhs URSHIFT_ASSIGN expr */
#line 110 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_urshift); }
#line 1345 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 18: /* expr ::= lhs AND_ASSIGN expr */
#line 111 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_and); }
#line 1351 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 19: /* expr ::= lhs XOR_ASSIGN expr */
#line 112 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_xor); }
#line 1357 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 20: /* expr ::= lhs OR_ASSIGN expr */
#line 113 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_assign(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_or); }
#line 1363 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 21: /* lhs ::= IDENTIFIER */
#line 115 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_ident(ctx, yymsp[0].minor.yy0.begin); }
#line 1369 "mjs/mjs.lem.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 22: /* sexp ::= sexp LE sexp */
#line 133 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_bin(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_LTEQ); }
#line 1375 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 23: /* sexp ::= sexp LT sexp */
#line 134 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_bin(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_LT); }
#line 1381 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 24: /* sexp ::= sexp GE sexp */
#line 135 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_bin(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_GTEQ); }
#line 1387 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 25: /* sexp ::= sexp GT sexp */
#line 136 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_bin(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_GT); }
#line 1393 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 26: /* sexp ::= sexp EQ sexp */
#line 137 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_bin(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_EQ); }
#line 1399 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 27: /* sexp ::= sexp NE sexp */
#line 138 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_bin(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_SETEQ); }
#line 1405 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 28: /* sexp ::= sexp PLUS sexp */
#line 141 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_bin(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_PLUS); }
#line 1411 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 29: /* sexp ::= sexp MINUS sexp */
#line 142 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_bin(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_MINUS); }
#line 1417 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 30: /* sexp ::= sexp MUL sexp */
#line 143 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_bin(ctx, yymsp[-2].minor.yy86, yymsp[0].minor.yy86, MJS_OP_STAR); }
#line 1423 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 31: /* sexp ::= OPEN_PAREN expr CLOSE_PAREN */
      case 40: /* block ::= OPEN_CURLY stmtlist CLOSE_CURLY */ yytestcase(yyruleno==40);
      case 50: /* object_literal ::= OPEN_CURLY objspeclist CLOSE_CURLY */ yytestcase(yyruleno==50);
#line 147 "mjs/mjs.lem.c"
{ yymsp[-2].minor.yy86=yymsp[-1].minor.yy86; }
#line 1431 "mjs/mjs.lem.c"
        break;
      case 32: /* sexp ::= IDENTIFIER */
#line 149 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_var(ctx, yymsp[0].minor.yy0.begin); }
#line 1436 "mjs/mjs.lem.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 33: /* expr ::= expr OPEN_PAREN CLOSE_PAREN */
#line 153 "mjs/mjs.lem.c"
{
  yylhsminor.yy86=mjs_emit(ctx, MJS_OP_zero);
  mjs_emit_call(ctx, yymsp[-2].minor.yy86);
  mjs_emit(ctx, MJS_OP_jscall);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1447 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 34: /* expr ::= expr OPEN_PAREN callarglist CLOSE_PAREN */
#line 160 "mjs/mjs.lem.c"
{
  yylhsminor.yy86=mjs_emit(ctx, MJS_OP_zero);
  mjs_emit_call(ctx, yymsp[-1].minor.yy86);
  mjs_emit_call(ctx, yymsp[-3].minor.yy86);
  mjs_emit(ctx, MJS_OP_jscall);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1459 "mjs/mjs.lem.c"
  yymsp[-3].minor.yy86 = yylhsminor.yy86;
        break;
      case 35: /* callarglist ::= callarglist COMMA callarg */
#line 167 "mjs/mjs.lem.c"
{
  yylhsminor.yy86=mjs_emit_call(ctx, yymsp[0].minor.yy86);
  mjs_emit(ctx, MJS_OP_swapinc);
  mjs_emit_call(ctx, yymsp[-2].minor.yy86);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1470 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 36: /* callarglist ::= callarg */
#line 173 "mjs/mjs.lem.c"
{
  yylhsminor.yy86=mjs_emit_call(ctx, yymsp[0].minor.yy86);
  mjs_emit(ctx, MJS_OP_swapinc);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1480 "mjs/mjs.lem.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 37: /* cstmt ::= IF OPEN_PAREN expr CLOSE_PAREN block */
#line 183 "mjs/mjs.lem.c"
{
  yymsp[-4].minor.yy86=mjs_emit_call(ctx, yymsp[-2].minor.yy86);
  mjs_emit_quote(ctx, yymsp[0].minor.yy86);
  mjs_emit(ctx, MJS_OP_ifstmt);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1491 "mjs/mjs.lem.c"
        break;
      case 38: /* cstmt ::= IF OPEN_PAREN expr CLOSE_PAREN block ELSE block */
#line 189 "mjs/mjs.lem.c"
{
  yymsp[-6].minor.yy86=mjs_emit_call(ctx, yymsp[-4].minor.yy86);
  mjs_emit_quote(ctx, yymsp[-2].minor.yy86);
  mjs_emit_quote(ctx, yymsp[0].minor.yy86);
  mjs_emit(ctx, MJS_OP_ifelse);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1502 "mjs/mjs.lem.c"
        break;
      case 39: /* cstmt ::= WHILE OPEN_PAREN expr CLOSE_PAREN block */
#line 196 "mjs/mjs.lem.c"
{
  yymsp[-4].minor.yy86=mjs_emit_quote(ctx, yymsp[0].minor.yy86);
  mjs_emit_quote(ctx, yymsp[-2].minor.yy86);
  mjs_emit(ctx, MJS_OP_while);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1512 "mjs/mjs.lem.c"
        break;
      case 41: /* funcdecl ::= FUNCTION IDENTIFIER arglistparen OPEN_CURLY stmtlist CLOSE_CURLY */
#line 216 "mjs/mjs.lem.c"
{
  bf_word_ptr_t f = mjs_emit_func(ctx, yymsp[-3].minor.yy86, yymsp[-1].minor.yy86);
  yymsp[-5].minor.yy86 = mjs_emit_str_or_ident(ctx, yymsp[-4].minor.yy0.begin);
  mjs_emit_call(ctx, f);
  mjs_emit(ctx, MJS_OP_setvar);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1523 "mjs/mjs.lem.c"
        break;
      case 42: /* func_literal ::= FUNCTION arglistparen OPEN_CURLY stmtlist CLOSE_CURLY */
#line 226 "mjs/mjs.lem.c"
{
  yymsp[-4].minor.yy86=mjs_emit_func(ctx, yymsp[-3].minor.yy86, yymsp[-1].minor.yy86);
}
#line 1530 "mjs/mjs.lem.c"
        break;
      case 43: /* arglist ::= */
#line 233 "mjs/mjs.lem.c"
{
  /*
   * mjs_emit_func() will check if arguments pointer is an invalid word ptr,
   * and if so, will skip calling the word generated by `argspec`s.
   */
  yymsp[1].minor.yy86 = BF_INVALID_WORD_PTR;
}
#line 1541 "mjs/mjs.lem.c"
        break;
      case 44: /* argspec ::= IDENTIFIER */
#line 240 "mjs/mjs.lem.c"
{
  /*
   * emit `"varname" setarg`
   * NOTE: do not emit `exit`, it'll be emitted by arglistparen, after
   * all `setarg`s.
   */
  yylhsminor.yy86=mjs_emit_str_or_ident(ctx, yymsp[0].minor.yy0.begin);
  mjs_emit(ctx, MJS_OP_setarg);
}
#line 1554 "mjs/mjs.lem.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 45: /* arglistparen ::= OPEN_PAREN arglist CLOSE_PAREN */
#line 250 "mjs/mjs.lem.c"
{
  /* will return the beginning of the arglist */
  yymsp[-2].minor.yy86 = yymsp[-1].minor.yy86;
  if (yymsp[-1].minor.yy86 != BF_INVALID_WORD_PTR) {
    /* terminate `"foo" setarg "bar" setarg` with an exit */
    mjs_emit(ctx, MJS_OP_exit);
  }
}
#line 1567 "mjs/mjs.lem.c"
        break;
      case 46: /* sstmt ::= RETURN */
#line 259 "mjs/mjs.lem.c"
{
  yymsp[0].minor.yy86=mjs_emit(ctx, MJS_OP_undefined);
  mjs_emit(ctx, MJS_OP_jsexit);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1576 "mjs/mjs.lem.c"
        break;
      case 47: /* sstmt ::= RETURN expr */
#line 264 "mjs/mjs.lem.c"
{
  yymsp[-1].minor.yy86=mjs_emit_call(ctx, yymsp[0].minor.yy86);
  mjs_emit(ctx, MJS_OP_jsexit);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1585 "mjs/mjs.lem.c"
        break;
      case 48: /* literal ::= NUMBER */
#line 274 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_num(ctx, yymsp[0].minor.yy0.begin); }
#line 1590 "mjs/mjs.lem.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 49: /* literal ::= STRING_LITERAL */
#line 275 "mjs/mjs.lem.c"
{ yylhsminor.yy86=mjs_emit_str(ctx, yymsp[0].minor.yy0.begin); }
#line 1596 "mjs/mjs.lem.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 51: /* objspeclist ::= objspeclist COMMA objspec */
#line 286 "mjs/mjs.lem.c"
{
  yylhsminor.yy86=mjs_emit_call(ctx, yymsp[-2].minor.yy86);
  mjs_emit_call(ctx, yymsp[0].minor.yy86);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1606 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      case 52: /* objspeclist ::= objspec */
#line 291 "mjs/mjs.lem.c"
{
  yylhsminor.yy86=mjs_emit(ctx, MJS_OP_mkobj);
  mjs_emit_call(ctx, yymsp[0].minor.yy86);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1616 "mjs/mjs.lem.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 53: /* objspeclist ::= */
#line 296 "mjs/mjs.lem.c"
{
  yymsp[1].minor.yy86=mjs_emit(ctx, MJS_OP_mkobj);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1625 "mjs/mjs.lem.c"
        break;
      case 54: /* objspec ::= objspeclhs COLON expr */
#line 301 "mjs/mjs.lem.c"
{
  yylhsminor.yy86=mjs_emit_str_or_ident(ctx, yymsp[-2].minor.yy110);
  mjs_emit_call(ctx, yymsp[0].minor.yy86);
  mjs_emit(ctx, MJS_OP_addprop);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1635 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy86 = yylhsminor.yy86;
        break;
      default:
      /* (55) stmtlist ::= cstmtlist */ yytestcase(yyruleno==55);
      /* (56) stmtlist ::= sstmtlist */ yytestcase(yyruleno==56);
      /* (57) sstmt ::= LET letspecs */ yytestcase(yyruleno==57);
      /* (58) letspecs ::= letspecs COMMA letspec */ yytestcase(yyruleno==58);
      /* (59) letspecs ::= letspec (OPTIMIZED OUT) */ assert(yyruleno!=59);
      /* (60) letspec ::= IDENTIFIER ASSIGN expr */ yytestcase(yyruleno==60);
      /* (61) letspec ::= IDENTIFIER */ yytestcase(yyruleno==61);
      /* (62) sstmt ::= expr */ yytestcase(yyruleno==62);
      /* (63) lhs ::= sexp DOT IDENTIFIER */ yytestcase(yyruleno==63);
      /* (64) expr ::= sexp */ yytestcase(yyruleno==64);
      /* (65) sexp ::= NOT sexp */ yytestcase(yyruleno==65);
      /* (66) sexp ::= TILDA sexp */ yytestcase(yyruleno==66);
      /* (67) sexp ::= MINUS sexp */ yytestcase(yyruleno==67);
      /* (68) sexp ::= PLUS sexp */ yytestcase(yyruleno==68);
      /* (69) sexp ::= MINUS_MINUS sexp */ yytestcase(yyruleno==69);
      /* (70) sexp ::= PLUS_PLUS sexp */ yytestcase(yyruleno==70);
      /* (71) sexp ::= sexp PLUS_PLUS */ yytestcase(yyruleno==71);
      /* (72) sexp ::= sexp MINUS_MINUS */ yytestcase(yyruleno==72);
      /* (73) sexp ::= sexp LSHIFT sexp */ yytestcase(yyruleno==73);
      /* (74) sexp ::= sexp RSHIFT sexp */ yytestcase(yyruleno==74);
      /* (75) sexp ::= sexp URSHIFT sexp */ yytestcase(yyruleno==75);
      /* (76) sexp ::= sexp EQ_EQ sexp */ yytestcase(yyruleno==76);
      /* (77) sexp ::= sexp NE_NE sexp */ yytestcase(yyruleno==77);
      /* (78) sexp ::= sexp DIV sexp */ yytestcase(yyruleno==78);
      /* (79) sexp ::= sexp REM sexp */ yytestcase(yyruleno==79);
      /* (80) sexp ::= sexp DOT sexp */ yytestcase(yyruleno==80);
      /* (81) sexp ::= literal (OPTIMIZED OUT) */ assert(yyruleno!=81);
      /* (82) callarg ::= expr */ yytestcase(yyruleno==82);
      /* (83) expr ::= expr OPEN_BRACKET expr CLOSE_BRACKET */ yytestcase(yyruleno==83);
      /* (84) cstmt ::= FOR OPEN_PAREN optexpr SEMICOLON optexpr SEMICOLON optexpr CLOSE_PAREN block */ yytestcase(yyruleno==84);
      /* (85) optexpr ::= */ yytestcase(yyruleno==85);
      /* (86) optexpr ::= expr */ yytestcase(yyruleno==86);
      /* (87) block ::= sstmt SEMICOLON */ yytestcase(yyruleno==87);
      /* (88) block ::= cstmt (OPTIMIZED OUT) */ assert(yyruleno!=88);
      /* (89) cstmt ::= funcdecl (OPTIMIZED OUT) */ assert(yyruleno!=89);
      /* (90) arglist ::= arglist COMMA argspec */ yytestcase(yyruleno==90);
      /* (91) arglist ::= argspec (OPTIMIZED OUT) */ assert(yyruleno!=91);
      /* (92) literal ::= NULL */ yytestcase(yyruleno==92);
      /* (93) literal ::= UNDEFINED */ yytestcase(yyruleno==93);
      /* (94) literal ::= THIS */ yytestcase(yyruleno==94);
      /* (95) literal ::= boolean_literal (OPTIMIZED OUT) */ assert(yyruleno!=95);
      /* (96) literal ::= func_literal (OPTIMIZED OUT) */ assert(yyruleno!=96);
      /* (97) literal ::= object_literal (OPTIMIZED OUT) */ assert(yyruleno!=97);
      /* (98) literal ::= array_literal (OPTIMIZED OUT) */ assert(yyruleno!=98);
      /* (99) boolean_literal ::= TRUE */ yytestcase(yyruleno==99);
      /* (100) boolean_literal ::= FALSE */ yytestcase(yyruleno==100);
      /* (101) objspeclhs ::= IDENTIFIER */ yytestcase(yyruleno==101);
      /* (102) objspeclhs ::= STRING_LITERAL */ yytestcase(yyruleno==102);
      /* (103) array_literal ::= OPEN_BRACKET arrayspeclist CLOSE_BRACKET */ yytestcase(yyruleno==103);
      /* (104) arrayspeclist ::= arrayspeclist COMMA expr */ yytestcase(yyruleno==104);
      /* (105) arrayspeclist ::= expr */ yytestcase(yyruleno==105);
      /* (106) arrayspeclist ::= */ yytestcase(yyruleno==106);
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
#line 28 "mjs/mjs.lem.c"

#line 1733 "mjs/mjs.lem.c"
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
#line 31 "mjs/mjs.lem.c"

  ctx->syntax_error = TOKEN;
  (void) yymajor;
#line 1754 "mjs/mjs.lem.c"
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
#line 25 "mjs/mjs.lem.c"

#line 1780 "mjs/mjs.lem.c"
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
#line 1 "bazel-out/local-dbg-asan/genfiles/mjs/vm.gen.c"
#endif
/* Amalgamated: #include "mjs/vm.gen.h" */
bf_opcode_t MJS_opcodes[] = {
  /* 0000 -> : quote ... ; */
  /*           <bf_op_quote> */ 
  /* 0000 -> : exit ... ; */
  /*           <bf_op_exit> */ 
  /* 0000 -> : drop ... ; */
  /*           <bf_op_drop> */ 
  /* 0000 -> : dup ... ; */
  /*           <bf_op_dup> */ 
  /* 0000 -> : swap ... ; */
  /*           <bf_op_swap> */ 
  /* 0000 -> : over ... ; */
  /*           <bf_op_over> */ 
  /* 0000 -> : -rot ... ; */
  /*           <bf_op_neg_rot> */ 
  /* 0000 -> : rot ... ; */
  MJS_OP_MINUS_rot, MJS_OP_MINUS_rot, MJS_OP_exit,
  /* 0003 -> : >r ... ; */
  /*           <bf_op_pushr> */ 
  /* 0003 -> : r> ... ; */
  /*           <bf_op_popr> */ 
  /* 0003 -> : sp@ ... ; */
  /*           <bf_op_sp_save> */ 
  /* 0003 -> : sp! ... ; */
  /*           <bf_op_sp_restore> */ 
  /* 0003 -> : rp@ ... ; */
  /*           <bf_op_rp_save> */ 
  /* 0003 -> : rp! ... ; */
  /*           <bf_op_rp_restore> */ 
  /* 0003 -> : tmp! ... ; */
  /*           <bf_op_stash> */ 
  /* 0003 -> : tmp@ ... ; */
  /*           <bf_op_unstash> */ 
  /* 0003 -> : print ... ; */
  /*           <bf_op_print> */ 
  /* 0003 -> : cr ... ; */
  /*           <bf_op_cr> */ 
  /* 0003 -> : .s ... ; */
  /*           <bf_op_print_stack> */ 
  /* 0003 -> : = ... ; */
  /*           <bf_op_eq> */ 
  /* 0003 -> : < ... ; */
  /*           <bf_op_lt> */ 
  /* 0003 -> : > ... ; */
  /*           <bf_op_gt> */ 
  /* 0003 -> : invert ... ; */
  /*           <bf_op_invert> */ 
  /* 0003 -> : + ... ; */
  /*           <bf_op_add> */ 
  /* 0003 -> : - ... ; */
  /*           <bf_op_sub> */ 
  /* 0003 -> : * ... ; */
  /*           <bf_op_mul> */ 
  /* 0003 -> : call ... ; */
  /*           <bf_op_call> */ 
  /* 0003 -> : if ... ; */
  /*           <bf_op_if> */ 
  /* 0003 -> : ifelse ... ; */
  /*           <bf_op_ifelse> */ 
  /* 0003 -> : loop ... ; */
  MJS_OP_dup, MJS_OP_GT_r, MJS_OP_call, MJS_OP_r_GT, MJS_OP_swap, MJS_OP_quote, 0, 3, MJS_OP_quote, -1, -3, MJS_OP_ifelse, MJS_OP_exit,
  /* 0016 -> : ndrop ... ; */
  /*           <bf_op_ndrop> */ 
  /* 0016 -> : str ... ; */
  /*           <mjs_op_str> */ 
  /* 0016 -> : scope@ ... ; */
  /*           <mjs_op_getscope> */ 
  /* 0016 -> : scope! ... ; */
  /*           <mjs_op_setscope> */ 
  /* 0016 -> : frame@ ... ; */
  /*           <mjs_op_getframe> */ 
  /* 0016 -> : frame! ... ; */
  /*           <mjs_op_setframe> */ 
  /* 0016 -> : mkobj ... ; */
  /*           <mjs_op_mkobj> */ 
  /* 0016 -> : addprop ... ; */
  MJS_OP_rot, MJS_OP_dup, MJS_OP_GT_r, MJS_OP_MINUS_rot, MJS_OP_setprop, MJS_OP_drop, MJS_OP_r_GT, MJS_OP_exit,
  /* 0024 -> : setprop ... ; */
  /*           <mjs_op_setprop> */ 
  /* 0024 -> : getprop ... ; */
  /*           <mjs_op_getprop> */ 
  /* 0024 -> : getvar ... ; */
  /*           <mjs_op_getvar> */ 
  /* 0024 -> : setvar ... ; */
  /*           <mjs_op_setvar> */ 
  /* 0024 -> : jscall ... ; */
  /*           <mjs_op_jscall> */ 
  /* 0024 -> : jscall_exit ... ; */
  MJS_OP_tmp_SET, MJS_OP_r_GT, MJS_OP_sp_SET, MJS_OP_tmp_AT, MJS_OP_exit,
  /* 0029 -> : jsenter ... ; */
  MJS_OP_r_GT, MJS_OP_tmp_SET, MJS_OP_scope_AT, MJS_OP_GT_r, MJS_OP_frame_AT, MJS_OP_GT_r, MJS_OP_rp_AT, MJS_OP_frame_SET, MJS_OP_mkobj, MJS_OP_dup, MJS_OP_scope_SET, MJS_OP_tmp_AT, MJS_OP_GT_r, MJS_OP_exit,
  /* 0043 -> : jsexit ... ; */
  MJS_OP_frame_AT, MJS_OP_rp_SET, MJS_OP_r_GT, MJS_OP_frame_SET, MJS_OP_r_GT, MJS_OP_scope_SET, MJS_OP_exit,
  /* 0050 -> : anon_0 ... ; */
  MJS_OP_undefined, MJS_OP_exit,
  /* 0052 -> : anon_1 ... ; */
  MJS_OP_rot, MJS_OP_exit,
  /* 0054 -> : setarg ... ; */
  MJS_OP_rot, MJS_OP_one, MJS_OP_MINUS, MJS_OP_dup, MJS_OP_GT_r, MJS_OP_quote, 0, 0, MJS_OP_LT, MJS_OP_quote, 0, 50, MJS_OP_quote, 0, 52, MJS_OP_ifelse, MJS_OP_addprop, MJS_OP_r_GT, MJS_OP_swap, MJS_OP_exit,
  /* 0074 -> : ffi ... ; */
  MJS_OP_drop, MJS_OP_exit,
  /* 0076 -> : undefined ... ; */
  /*           <mjs_op_undefined> */ 
  /* 0076 -> : null ... ; */
  /*           <mjs_op_null> */ 
  /* 0076 -> : 2dup ... ; */
  MJS_OP_over, MJS_OP_over, MJS_OP_exit,
  /* 0079 -> : dec ... ; */
  MJS_OP_quote, -1, -1, MJS_OP_PLUS, MJS_OP_exit,
  /* 0084 -> : >= ... ; */
  MJS_OP_LT, MJS_OP_invert, MJS_OP_exit,
  /* 0087 -> : <= ... ; */
  MJS_OP_GT, MJS_OP_invert, MJS_OP_exit,
  /* 0090 -> : != ... ; */
  MJS_OP_EQ, MJS_OP_invert, MJS_OP_exit,
  /* 0093 -> : anon_2 ... ; */
  MJS_OP_undefined, MJS_OP_exit,
  /* 0095 -> : ifstmt ... ; */
  MJS_OP_quote, 0, 93, MJS_OP_ifelse, MJS_OP_exit,
  /* 0100 -> : anon_3 ... ; */
  MJS_OP_2dup, MJS_OP_GT_r, MJS_OP_GT_r, MJS_OP_call, MJS_OP_r_GT, MJS_OP_r_GT, MJS_OP_swap, -28, MJS_OP_dup, MJS_OP_quote, 0, 0, MJS_OP_GTEQ, MJS_OP_GT_r, MJS_OP_swap, MJS_OP_r_GT, MJS_OP_exit,
  /* 0117 -> : anon_4 ... ; */
  -38, MJS_OP_swap, MJS_OP_quote, 0, 100, MJS_OP_loop, MJS_OP_exit,
  /* 0124 -> : repeat ... ; */
  MJS_OP_swap, MJS_OP_dup, MJS_OP_quote, 0, 0, MJS_OP_GT, MJS_OP_quote, 0, 117, MJS_OP_if, MJS_OP_drop, MJS_OP_drop, MJS_OP_exit,
  /* 0137 -> : anon_5 ... ; */
  MJS_OP_call, MJS_OP_drop, MJS_OP_quote, 0, 1, MJS_OP_exit,
  /* 0143 -> : anon_6 ... ; */
  MJS_OP_drop, MJS_OP_drop, MJS_OP_drop, MJS_OP_zero, MJS_OP_exit,
  /* 0148 -> : anon_7 ... ; */
  MJS_OP_2dup, MJS_OP_call, MJS_OP_quote, 0, -119, MJS_OP_quote, 0, -113, MJS_OP_ifelse, MJS_OP_exit,
  /* 0158 -> : while ... ; */
  MJS_OP_quote, 0, -108, MJS_OP_loop, MJS_OP_undefined, MJS_OP_exit,
  /* 0164 -> : anon_8 ... ; */
  MJS_OP_str, /* " " */  ' ', 0, MJS_OP_print, MJS_OP_exit,
  /* 0169 -> : anon_9 ... ; */
  MJS_OP_swap, MJS_OP_print, MJS_OP_quote, 0, 0, MJS_OP_EQ, MJS_OP_invert, MJS_OP_quote, 0, -92, MJS_OP_if, MJS_OP_exit,
  /* 0181 -> : jsprint ... ; */
  MJS_OP_quote, 0, -87, MJS_OP_repeat, MJS_OP_cr, MJS_OP_undefined, MJS_OP_exit,
  /* 0188 -> : zero ... ; */
  MJS_OP_quote, 0, 0, MJS_OP_exit,
  /* 0192 -> : one ... ; */
  MJS_OP_quote, 0, 1, MJS_OP_exit,
  /* 0196 -> : nop ... ; */
  MJS_OP_zero, MJS_OP_drop, MJS_OP_exit,
  /* 0199 -> : inc ... ; */
  MJS_OP_quote, 0, 1, MJS_OP_PLUS, MJS_OP_exit,
  /* 0204 -> : swapinc ... ; */
  MJS_OP_swap, MJS_OP_inc, MJS_OP_exit,
  /* 0207 -> : div ... ; */
  /*           <mjs_op_todo> */ 
  /* 0207 -> : rem ... ; */
  /*           <mjs_op_todo> */ 
  /* 0207 -> : lshift ... ; */
  /*           <mjs_op_todo> */ 
  /* 0207 -> : rshift ... ; */
  /*           <mjs_op_todo> */ 
  /* 0207 -> : urshift ... ; */
  /*           <mjs_op_todo> */ 
  /* 0207 -> : and ... ; */
  /*           <mjs_op_todo> */ 
  /* 0207 -> : or ... ; */
  /*           <mjs_op_todo> */ 
  /* 0207 -> : xor ... ; */
  /*           <mjs_op_todo> */ 
}; /* 207 * sizeof(bf_opcode_t) */

bf_word_ptr_t MJS_word_ptrs[] = {
  /* -001 */ -1, 
  /* 0000 */ -2, 
  /* 0001 */ -3, 
  /* 0002 */ -4, 
  /* 0003 */ -5, 
  /* 0004 */ -6, 
  /* 0005 */ -7, 
  /* 0006 */ 0, 
  /* 0007 */ -8, 
  /* 0008 */ -9, 
  /* 0009 */ -10, 
  /* 0010 */ -11, 
  /* 0011 */ -12, 
  /* 0012 */ -13, 
  /* 0013 */ -14, 
  /* 0014 */ -15, 
  /* 0015 */ -16, 
  /* 0016 */ -17, 
  /* 0017 */ -18, 
  /* 0018 */ -19, 
  /* 0019 */ -20, 
  /* 0020 */ -21, 
  /* 0021 */ -22, 
  /* 0022 */ -23, 
  /* 0023 */ -24, 
  /* 0024 */ -25, 
  /* 0025 */ -26, 
  /* 0026 */ -27, 
  /* 0027 */ -28, 
  /* 0028 */ 3, 
  /* 0029 */ -29, 
  /* 0030 */ -30, 
  /* 0031 */ -31, 
  /* 0032 */ -32, 
  /* 0033 */ -33, 
  /* 0034 */ -34, 
  /* 0035 */ -35, 
  /* 0036 */ 16, 
  /* 0037 */ -36, 
  /* 0038 */ -37, 
  /* 0039 */ -38, 
  /* 0040 */ -39, 
  /* 0041 */ -40, 
  /* 0042 */ 24, 
  /* 0043 */ 29, 
  /* 0044 */ 43, 
  /* 0045 */ 54, 
  /* 0046 */ -41, 
  /* 0047 */ -42, 
  /* 0048 */ 76, 
  /* 0049 */ 84, 
  /* 0050 */ 87, 
  /* 0051 */ 90, 
  /* 0052 */ 95, 
  /* 0053 */ 124, 
  /* 0054 */ 158, 
  /* 0055 */ 181, 
  /* 0056 */ 188, 
  /* 0057 */ 192, 
  /* 0058 */ 196, 
  /* 0059 */ 199, 
  /* 0060 */ 204, 
  /* 0061 */ -43, 
  /* 0062 */ -44, 
  /* 0063 */ -45, 
  /* 0064 */ -46, 
  /* 0065 */ -47, 
  /* 0066 */ -48, 
  /* 0067 */ -49, 
  /* 0068 */ -50, 
};

void bf_op_quote(struct bf_vm *vm);
void bf_op_exit(struct bf_vm *vm);
void bf_op_drop(struct bf_vm *vm);
void bf_op_dup(struct bf_vm *vm);
void bf_op_swap(struct bf_vm *vm);
void bf_op_over(struct bf_vm *vm);
void bf_op_neg_rot(struct bf_vm *vm);
void bf_op_pushr(struct bf_vm *vm);
void bf_op_popr(struct bf_vm *vm);
void bf_op_sp_save(struct bf_vm *vm);
void bf_op_sp_restore(struct bf_vm *vm);
void bf_op_rp_save(struct bf_vm *vm);
void bf_op_rp_restore(struct bf_vm *vm);
void bf_op_stash(struct bf_vm *vm);
void bf_op_unstash(struct bf_vm *vm);
void bf_op_print(struct bf_vm *vm);
void bf_op_cr(struct bf_vm *vm);
void bf_op_print_stack(struct bf_vm *vm);
void bf_op_eq(struct bf_vm *vm);
void bf_op_lt(struct bf_vm *vm);
void bf_op_gt(struct bf_vm *vm);
void bf_op_invert(struct bf_vm *vm);
void bf_op_add(struct bf_vm *vm);
void bf_op_sub(struct bf_vm *vm);
void bf_op_mul(struct bf_vm *vm);
void bf_op_call(struct bf_vm *vm);
void bf_op_if(struct bf_vm *vm);
void bf_op_ifelse(struct bf_vm *vm);
void bf_op_ndrop(struct bf_vm *vm);
void mjs_op_str(struct bf_vm *vm);
void mjs_op_getscope(struct bf_vm *vm);
void mjs_op_setscope(struct bf_vm *vm);
void mjs_op_getframe(struct bf_vm *vm);
void mjs_op_setframe(struct bf_vm *vm);
void mjs_op_mkobj(struct bf_vm *vm);
void mjs_op_setprop(struct bf_vm *vm);
void mjs_op_getprop(struct bf_vm *vm);
void mjs_op_getvar(struct bf_vm *vm);
void mjs_op_setvar(struct bf_vm *vm);
void mjs_op_jscall(struct bf_vm *vm);
void mjs_op_undefined(struct bf_vm *vm);
void mjs_op_null(struct bf_vm *vm);
void mjs_op_todo(struct bf_vm *vm);
void mjs_op_todo(struct bf_vm *vm);
void mjs_op_todo(struct bf_vm *vm);
void mjs_op_todo(struct bf_vm *vm);
void mjs_op_todo(struct bf_vm *vm);
void mjs_op_todo(struct bf_vm *vm);
void mjs_op_todo(struct bf_vm *vm);
void mjs_op_todo(struct bf_vm *vm);

bf_native_t MJS_native_words[] = {
  /* -001 */ bf_op_quote,
  /* -002 */ bf_op_exit,
  /* -003 */ bf_op_drop,
  /* -004 */ bf_op_dup,
  /* -005 */ bf_op_swap,
  /* -006 */ bf_op_over,
  /* -007 */ bf_op_neg_rot,
  /* -008 */ bf_op_pushr,
  /* -009 */ bf_op_popr,
  /* -010 */ bf_op_sp_save,
  /* -011 */ bf_op_sp_restore,
  /* -012 */ bf_op_rp_save,
  /* -013 */ bf_op_rp_restore,
  /* -014 */ bf_op_stash,
  /* -015 */ bf_op_unstash,
  /* -016 */ bf_op_print,
  /* -017 */ bf_op_cr,
  /* -018 */ bf_op_print_stack,
  /* -019 */ bf_op_eq,
  /* -020 */ bf_op_lt,
  /* -021 */ bf_op_gt,
  /* -022 */ bf_op_invert,
  /* -023 */ bf_op_add,
  /* -024 */ bf_op_sub,
  /* -025 */ bf_op_mul,
  /* -026 */ bf_op_call,
  /* -027 */ bf_op_if,
  /* -028 */ bf_op_ifelse,
  /* -029 */ bf_op_ndrop,
  /* -030 */ mjs_op_str,
  /* -031 */ mjs_op_getscope,
  /* -032 */ mjs_op_setscope,
  /* -033 */ mjs_op_getframe,
  /* -034 */ mjs_op_setframe,
  /* -035 */ mjs_op_mkobj,
  /* -036 */ mjs_op_setprop,
  /* -037 */ mjs_op_getprop,
  /* -038 */ mjs_op_getvar,
  /* -039 */ mjs_op_setvar,
  /* -040 */ mjs_op_jscall,
  /* -041 */ mjs_op_undefined,
  /* -042 */ mjs_op_null,
  /* -043 */ mjs_op_todo,
  /* -044 */ mjs_op_todo,
  /* -045 */ mjs_op_todo,
  /* -046 */ mjs_op_todo,
  /* -047 */ mjs_op_todo,
  /* -048 */ mjs_op_todo,
  /* -049 */ mjs_op_todo,
  /* -050 */ mjs_op_todo,
};

const char *MJS_word_names[] = {
  /* -001 */ "quote", 
  /* 0000 */ "exit", 
  /* 0001 */ "drop", 
  /* 0002 */ "dup", 
  /* 0003 */ "swap", 
  /* 0004 */ "over", 
  /* 0005 */ "-rot", 
  /* 0006 */ "rot", 
  /* 0007 */ ">r", 
  /* 0008 */ "r>", 
  /* 0009 */ "sp@", 
  /* 0010 */ "sp!", 
  /* 0011 */ "rp@", 
  /* 0012 */ "rp!", 
  /* 0013 */ "tmp!", 
  /* 0014 */ "tmp@", 
  /* 0015 */ "print", 
  /* 0016 */ "cr", 
  /* 0017 */ ".s", 
  /* 0018 */ "=", 
  /* 0019 */ "<", 
  /* 0020 */ ">", 
  /* 0021 */ "invert", 
  /* 0022 */ "+", 
  /* 0023 */ "-", 
  /* 0024 */ "*", 
  /* 0025 */ "call", 
  /* 0026 */ "if", 
  /* 0027 */ "ifelse", 
  /* 0028 */ "loop", 
  /* 0029 */ "ndrop", 
  /* 0030 */ "str", 
  /* 0031 */ "scope@", 
  /* 0032 */ "scope!", 
  /* 0033 */ "frame@", 
  /* 0034 */ "frame!", 
  /* 0035 */ "mkobj", 
  /* 0036 */ "addprop", 
  /* 0037 */ "setprop", 
  /* 0038 */ "getprop", 
  /* 0039 */ "getvar", 
  /* 0040 */ "setvar", 
  /* 0041 */ "jscall", 
  /* 0042 */ "jscall_exit", 
  /* 0043 */ "jsenter", 
  /* 0044 */ "jsexit", 
  /* 0045 */ "setarg", 
  /* 0046 */ "undefined", 
  /* 0047 */ "null", 
  /* 0048 */ "2dup", 
  /* 0049 */ ">=", 
  /* 0050 */ "<=", 
  /* 0051 */ "!=", 
  /* 0052 */ "ifstmt", 
  /* 0053 */ "repeat", 
  /* 0054 */ "while", 
  /* 0055 */ "jsprint", 
  /* 0056 */ "zero", 
  /* 0057 */ "one", 
  /* 0058 */ "nop", 
  /* 0059 */ "inc", 
  /* 0060 */ "swapinc", 
  /* 0061 */ "div", 
  /* 0062 */ "rem", 
  /* 0063 */ "lshift", 
  /* 0064 */ "rshift", 
  /* 0065 */ "urshift", 
  /* 0066 */ "and", 
  /* 0067 */ "or", 
  /* 0068 */ "xor", 
};

const char *MJS_pos_names[] = {
  "rot", 
  "rot+1", 
  "rot+2", 
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
  "loop+10", 
  "loop+11", 
  "loop+12", 
  "addprop", 
  "addprop+1", 
  "addprop+2", 
  "addprop+3", 
  "addprop+4", 
  "addprop+5", 
  "addprop+6", 
  "addprop+7", 
  "jscall_exit", 
  "jscall_exit+1", 
  "jscall_exit+2", 
  "jscall_exit+3", 
  "jscall_exit+4", 
  "jsenter", 
  "jsenter+1", 
  "jsenter+2", 
  "jsenter+3", 
  "jsenter+4", 
  "jsenter+5", 
  "jsenter+6", 
  "jsenter+7", 
  "jsenter+8", 
  "jsenter+9", 
  "jsenter+10", 
  "jsenter+11", 
  "jsenter+12", 
  "jsenter+13", 
  "jsexit", 
  "jsexit+1", 
  "jsexit+2", 
  "jsexit+3", 
  "jsexit+4", 
  "jsexit+5", 
  "jsexit+6", 
  "anon_0", 
  "anon_0+1", 
  "anon_1", 
  "anon_1+1", 
  "setarg", 
  "setarg+1", 
  "setarg+2", 
  "setarg+3", 
  "setarg+4", 
  "setarg+5", 
  "setarg+6", 
  "setarg+7", 
  "setarg+8", 
  "setarg+9", 
  "setarg+10", 
  "setarg+11", 
  "setarg+12", 
  "setarg+13", 
  "setarg+14", 
  "setarg+15", 
  "setarg+16", 
  "setarg+17", 
  "setarg+18", 
  "setarg+19", 
  "ffi", 
  "ffi+1", 
  "2dup", 
  "2dup+1", 
  "2dup+2", 
  "dec", 
  "dec+1", 
  "dec+2", 
  "dec+3", 
  "dec+4", 
  ">=", 
  ">=+1", 
  ">=+2", 
  "<=", 
  "<=+1", 
  "<=+2", 
  "!=", 
  "!=+1", 
  "!=+2", 
  "anon_2", 
  "anon_2+1", 
  "ifstmt", 
  "ifstmt+1", 
  "ifstmt+2", 
  "ifstmt+3", 
  "ifstmt+4", 
  "anon_3", 
  "anon_3+1", 
  "anon_3+2", 
  "anon_3+3", 
  "anon_3+4", 
  "anon_3+5", 
  "anon_3+6", 
  "anon_3+7", 
  "anon_3+8", 
  "anon_3+9", 
  "anon_3+10", 
  "anon_3+11", 
  "anon_3+12", 
  "anon_3+13", 
  "anon_3+14", 
  "anon_3+15", 
  "anon_3+16", 
  "anon_4", 
  "anon_4+1", 
  "anon_4+2", 
  "anon_4+3", 
  "anon_4+4", 
  "anon_4+5", 
  "anon_4+6", 
  "repeat", 
  "repeat+1", 
  "repeat+2", 
  "repeat+3", 
  "repeat+4", 
  "repeat+5", 
  "repeat+6", 
  "repeat+7", 
  "repeat+8", 
  "repeat+9", 
  "repeat+10", 
  "repeat+11", 
  "repeat+12", 
  "anon_5", 
  "anon_5+1", 
  "anon_5+2", 
  "anon_5+3", 
  "anon_5+4", 
  "anon_5+5", 
  "anon_6", 
  "anon_6+1", 
  "anon_6+2", 
  "anon_6+3", 
  "anon_6+4", 
  "anon_7", 
  "anon_7+1", 
  "anon_7+2", 
  "anon_7+3", 
  "anon_7+4", 
  "anon_7+5", 
  "anon_7+6", 
  "anon_7+7", 
  "anon_7+8", 
  "anon_7+9", 
  "while", 
  "while+1", 
  "while+2", 
  "while+3", 
  "while+4", 
  "while+5", 
  "anon_8", 
  "anon_8+1", 
  "anon_8+2", 
  "anon_8+3", 
  "anon_8+4", 
  "anon_9", 
  "anon_9+1", 
  "anon_9+2", 
  "anon_9+3", 
  "anon_9+4", 
  "anon_9+5", 
  "anon_9+6", 
  "anon_9+7", 
  "anon_9+8", 
  "anon_9+9", 
  "anon_9+10", 
  "anon_9+11", 
  "jsprint", 
  "jsprint+1", 
  "jsprint+2", 
  "jsprint+3", 
  "jsprint+4", 
  "jsprint+5", 
  "jsprint+6", 
  "zero", 
  "zero+1", 
  "zero+2", 
  "zero+3", 
  "one", 
  "one+1", 
  "one+2", 
  "one+3", 
  "nop", 
  "nop+1", 
  "nop+2", 
  "inc", 
  "inc+1", 
  "inc+2", 
  "inc+3", 
  "inc+4", 
  "swapinc", 
  "swapinc+1", 
  "swapinc+2", 
};

struct bf_code MJS_code = {
  MJS_opcodes, sizeof(MJS_opcodes)/sizeof(MJS_opcodes[0]),
  MJS_word_ptrs, sizeof(MJS_word_ptrs)/sizeof(MJS_word_ptrs[0]),
  MJS_native_words, sizeof(MJS_native_words)/sizeof(MJS_native_words),
  MJS_word_names, MJS_pos_names,
};
#ifdef MG_MODULE_LINES
#line 1 "mjs/ffi/ffi.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "mjs/ffi/ffi.h" */

typedef uintptr_t word_t;

void ffi_set_int32(struct ffi_arg *arg, uint32_t v) {
  arg->size = 4;
  arg->is_float = 0;
  arg->v.i = v;
}

void ffi_set_int64(struct ffi_arg *arg, uint64_t v) {
  arg->size = 8;
  arg->is_float = 0;
  arg->v.i = v;
}

void ffi_set_ptr(struct ffi_arg *arg, void *v) {
  if (sizeof(v) == 8) {
    ffi_set_int64(arg, (uint64_t)(uintptr_t) v);
  } else {
    ffi_set_int32(arg, (uint32_t)(uintptr_t) v);
  }
}

void ffi_set_double(struct ffi_arg *arg, uint64_t v) {
  arg->size = 8;
  arg->is_float = 1;
  arg->v.d = v;
}

/*
 * The ARM ABI uses only 4 32-bit registers for paramter passing.
 * Xtensa call0 calling-convention (as used by Espressif) has 6.
 *
 * Focusing only on implementing FFI with registers means we can simplify a lot.
 *
 * ARM has some quasi-alignment rules when mixing double and integers as
 * arguments. Only:
 *   a) double, int32_t, int32_t
 *   b) int32_t, double
 * would fit in 4 registers. (the same goes for uint64_t).
 *
 * In order to simplify further, when a double-width argument is present, we
 * allow only two arguments.
 */

/*
 * We need to support x86_64 in order to support local tests.
 * x86_64 has more and wider registers, but unlike the two main
 * embedded platforms we target it has a separate register file for
 * integer values and for floating point values (both for passing args and
 * return values). E.g. if a double value is passed as a second argument
 * it gets passed in the first available floating point register.
 *
 * I.e, the compiler generates exactly the same code for:
 *
 * void foo(int a, double b) {...}
 *
 * and
 *
 * void foo(double b, int a) {...}
 *
 *
 */

typedef word_t (*i0_t)(word_t, word_t, word_t, word_t);
typedef word_t (*i1_t)(double, word_t);
typedef word_t (*i2_t)(double, double);

typedef double (*d0_t)(word_t, word_t, word_t, word_t);
typedef double (*d1_t)(double, word_t);
typedef double (*d2_t)(double, double);

int ffi_call(ffi_fn_t func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args) {
  int i, doubles = 0;

  if (nargs > 4) return -1;
  for (i = 0; i < nargs; i++) {
    doubles += !!args[i].is_float;
  }
  if (doubles > 0 && nargs > 2) return -1;

  if (!res->is_float) {
    word_t r;
    switch (doubles) {
      case 0: {
        i0_t f = (i0_t) func;
        r = f((word_t) args[0].v.i, (word_t) args[1].v.i, (word_t) args[2].v.i,
              (word_t) args[3].v.i);
        break;
      }
      case 1: {
        i1_t f = (i1_t) func;
        if (args[0].is_float) {
          r = f(args[0].v.d, (word_t) args[1].v.i);
        } else {
          r = f(args[1].v.d, (word_t) args[0].v.i);
        }
        break;
      }
      case 2: {
        i2_t f = (i2_t) func;
        r = f(args[0].v.d, args[1].v.d);
      } break;
      default:
        return -1;
    }
    res->v.i = (uint64_t) r;
  } else {
    double r;
    switch (doubles) {
      case 0: {
        d0_t f = (d0_t) func;
        r = f((word_t) args[0].v.i, (word_t) args[1].v.i, (word_t) args[2].v.i,
              (word_t) args[3].v.i);
        break;
      }
      case 1: {
        d1_t f = (d1_t) func;
        if (args[0].is_float) {
          r = f(args[0].v.d, (word_t) args[1].v.i);
        } else {
          r = f(args[1].v.d, (word_t) args[0].v.i);
        }
        break;
      }
      case 2: {
        d2_t f = (d2_t) func;
        r = f(args[0].v.d, args[1].v.d);
      } break;
      default:
        return -1;
    }
    res->v.d = r;
  }

  return 0;
}
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
/* Amalgamated: #include "mjs/ffi.h" */
/* Amalgamated: #include "mjs/bf/mem.h" */
/* Amalgamated: #include "mjs/gc.h" */
/* Amalgamated: #include "mjs/mm.h" */
/* Amalgamated: #include "mjs/primitive.h" */
/* Amalgamated: #include "mjs/object.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/vm.gen.h" */

#ifndef MJS_DEFAULT_OBJECT_ARENA_SIZE
#define MJS_DEFAULT_OBJECT_ARENA_SIZE 20
#endif
#ifndef MJS_DEFAULT_PROPERTY_ARENA_SIZE
#define MJS_DEFAULT_PROPERTY_ARENA_SIZE 80
#endif

static void object_destructor(struct mjs *mjs, void *ptr) {
  (void) mjs;
  (void) ptr;
}

int32_t bf_to_int(bf_cell_t cell) {
  mjs_val_t v = (mjs_val_t) cell;
  return mjs_get_int32(NULL, v);
}

bf_cell_t bf_from_int(int32_t i) {
  return mjs_mk_number(NULL, i);
}

void bf_print_cell(struct bf_vm *vm, bf_cell_t cell) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t v = (mjs_val_t) cell;
  if (mjs_is_number(v)) {
    printf("%d", mjs_get_int(mjs, v));
  } else if (mjs_is_string(v)) {
    printf("%s", mjs_get_cstring(mjs, &v));
  } else if (mjs_is_undefined(v)) {
    printf("undefined");
  } else if (mjs_is_null(v)) {
    printf("null");
  } else if (mjs_is_object(v)) {
    printf("[object Object]");
  } else {
    printf("<val_t %llx>", (long long unsigned int) v);
  }
}

int bf_is_true(bf_cell_t cell) {
  return !!mjs_get_int32(NULL, (mjs_val_t) cell);
}

struct mjs *mjs_create() {
  struct mjs_create_opts opts;
  memset(&opts, 0, sizeof(opts));
  return mjs_create_opt(opts);
}

MJS_PRIVATE void mjs_init_globals(struct mjs *mjs, mjs_val_t g) {
  mjs_set(mjs, g, "print", ~0, mjs_mk_number(mjs, MJS_WORD_PTR_jsprint));
  mjs_set(mjs, g, "ffi", ~0, mjs_mk_number(mjs, MJS_WORD_PTR_ffi));
  mjs_set(mjs, g, "ffi_cb_void_void", ~0, mjs_mk_foreign(mjs, mjs_ffi_cb_void_void));
  mjs_set(mjs, g, "ffi_cb_arg", ~0, mjs_mk_foreign(mjs, mjs_ffi_cb_arg));
  mjs_set(mjs, g, "ffi_cb_arg_free", ~0, mjs_mk_foreign(mjs, mjs_ffi_cb_arg_free));
}

static void cb_after_bf_enter(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;

#ifdef MJS_AGGRESSIVE_GC
  /* In "Aggressive GC" mode, perform GC after entering each word */
  mjs->need_gc = 1;
#endif

  if (mjs->need_gc) {
    if (maybe_gc(mjs)) {
      mjs->need_gc = 0;
    }
  }

  (void) vm;
}

struct mjs *mjs_create_opt(struct mjs_create_opts opts) {
  struct mjs *mjs = calloc(1, sizeof(*mjs));

  {
    struct bf_callbacks cb;
    memset(&cb, 0, sizeof(cb));
    cb.after_bf_enter = cb_after_bf_enter;
    bf_init_vm(&mjs->vm, (opts.code ? opts.code : &MJS_code), &cb);
  }
  mjs->vm.user_data = (void *) mjs;

  mjs->last_code = mjs->vm.iram->num_pages * FR_PAGE_SIZE;

  mbuf_init(&mjs->owned_strings, 0);
  mbuf_init(&mjs->foreign_strings, 0);
  mbuf_init(&mjs->owned_values, 0);

  /*
   * The compacting GC exploits the null terminator of the previous string as a
   * marker.
   */
  {
    char z = 0;
    mbuf_append(&mjs->owned_strings, &z, 1);
  }

  gc_arena_init(&mjs->object_arena, sizeof(struct mjs_object),
                MJS_DEFAULT_OBJECT_ARENA_SIZE, 10);
  mjs->object_arena.destructor = object_destructor;
  gc_arena_init(&mjs->property_arena, sizeof(struct mjs_property),
                MJS_DEFAULT_PROPERTY_ARENA_SIZE, 10);

  mjs->vals.global_object = mjs_mk_object(mjs);
  mjs->vals.scope = mjs->vals.global_object;
  mjs->vals.call_frame = mjs_mk_number(mjs, -1);

  mjs_init_globals(mjs, mjs->vals.global_object);
  return mjs;
}

void mjs_destroy(struct mjs *mjs) {
  bf_destroy_vm(&mjs->vm);
  mbuf_free(&mjs->owned_strings);
  mbuf_free(&mjs->foreign_strings);
  mbuf_free(&mjs->owned_values);
  gc_arena_destroy(mjs, &mjs->object_arena);
  gc_arena_destroy(mjs, &mjs->property_arena);
  free(mjs->error_msg);
  free(mjs);
}

mjs_val_t mjs_get_global(struct mjs *mjs) {
  return mjs->vals.global_object;
}

void mjs_push(struct mjs *mjs, mjs_val_t val) {
  bf_push(&mjs->vm.dstack, val);
}

mjs_val_t mjs_pop(struct mjs *mjs) {
  return bf_pop(&mjs->vm.dstack);
}

mjs_val_t mjs_pop_arg(struct mjs *mjs, mjs_val_t *nargs) {
  mjs_val_t arg = mjs_mk_undefined();
  int n = mjs_get_int(mjs, *nargs);
  if (n > 0) {
    arg = mjs_pop(mjs);
    n--;
    *nargs = mjs_mk_number(mjs, n);
  }
  return arg;
}

void mjs_own(struct mjs *mjs, mjs_val_t *v) {
  mbuf_append(&mjs->owned_values, &v, sizeof(v));
}

int mjs_disown(struct mjs *mjs, mjs_val_t *v) {
  mjs_val_t **vp =
    (mjs_val_t **) (mjs->owned_values.buf + mjs->owned_values.len - sizeof(v));

  for (; (char *) vp >= mjs->owned_values.buf; vp--) {
    if (*vp == v) {
      *vp = *(mjs_val_t **) (mjs->owned_values.buf + mjs->owned_values.len -
          sizeof(v));
      mjs->owned_values.len -= sizeof(v);
      return 1;
    }
  }

  return 0;
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
#line 1 "mjs/disasm_mjs.c"
#endif
#include <stdio.h>

/* Amalgamated: #include "mjs/vm.gen.h" */

int disasm_custom(char b, FILE *in, int *pos) {
  if (b == MJS_OP_str) {
    char buf[128];
    char ch;
    int p = 0;
    do {
      fread(&ch, 1, 1, in);
      buf[p++] = ch;
    } while (ch != '\0');

    printf("\"%s\" ", buf);
    *pos += p;
    return 1;
  }
  return 0;
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/exec.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "common/cs_file.h" */
/* Amalgamated: #include "common/platform.h" */
/* Amalgamated: #include "mjs/exec.h" */
/* Amalgamated: #include "mjs/parser.h" */
/* Amalgamated: #include "mjs/primitive.h" */
/* Amalgamated: #include "mjs/vm.gen.h" */

mjs_err_t mjs_exec_buf(struct mjs *mjs, const char *src, size_t len,
                       mjs_val_t *res) {
  mjs_err_t err;
  bf_cell_t r;
  struct mjs_parse_ctx ctx;

  LOG(LL_DEBUG, ("parsing %s", src));
  err = mjs_parse_buf(mjs, src, len, &ctx);
  if (err != MJS_OK) {
    return err;
  }

  LOG(LL_DEBUG, ("running %d", ctx.entry));
  bf_run(&mjs->vm, ctx.entry);
  r = bf_pop(&mjs->vm.dstack);
  if (res != NULL) {
    *(bf_cell_t *) res = r;
  }

  return err;
}

mjs_err_t mjs_exec(struct mjs *mjs, const char *src, mjs_val_t *res) {
  return mjs_exec_buf(mjs, src, strlen(src), res);
}

mjs_err_t mjs_exec_file(struct mjs *mjs, const char *filename, mjs_val_t *res) {
  mjs_err_t err;
  size_t len;
  char *body = cs_read_file(filename, &len);
  err = mjs_exec_buf(mjs, body, len, res);
  free(body);
  return err;
}

mjs_err_t mjs_call(struct mjs *mjs, mjs_val_t *res, mjs_val_t func, int nargs, ...) {
  va_list ap;
  mjs_val_t r;
  int i;

  LOG(LL_DEBUG, ("applying func %d", mjs_get_int(mjs, func)));
  va_start (ap, nargs);
  for (i = 0; i < nargs; i++) {
    bf_push(&mjs->vm.dstack, va_arg(ap, mjs_val_t));
  }
  bf_push(&mjs->vm.dstack, mjs_mk_number(mjs, nargs));
  bf_push(&mjs->vm.dstack, func);
  bf_run(&mjs->vm, MJS_OP_jscall);
  r = bf_pop(&mjs->vm.dstack);

  /*
   * NOTE: calling `bf_run()` invalidates `func`. If you ever need to use it
   * afterwards, you need to own it before.
   */

  if (res != NULL) *res = r;
  va_end(ap);

  return MJS_OK;
}

#ifdef MG_MODULE_LINES
#line 1 "mjs/ffi.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#if defined(__unix__) || defined(__APPLE__)
#include <dlfcn.h>
#endif

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "common/str_util.h" */
/* Amalgamated: #include "mjs/internal.h" */
/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/exec.h" */
/* Amalgamated: #include "mjs/ffi.h" */
/* Amalgamated: #include "mjs/ffi/ffi.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/primitive.h" */

/*
 * on linux this is enabled only if __USE_GNU is defined, but we cannot set it
 * because dlfcn could have been included already.
 */
#ifndef RTLD_DEFAULT
#define RTLD_DEFAULT NULL
#endif

void mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym) {
  mjs->dlsym = dlsym;
}

MJS_PRIVATE void mjs_ffi_call(struct mjs *mjs, mjs_val_t sig) {
  const char *s = mjs_get_cstring(mjs, &sig);
  const char *n, *e, *a = NULL;
  char *buf = NULL;
  ffi_fn_t fn;
  int i, nargs;
  struct ffi_arg res;
  struct ffi_arg args[4];
  mjs_val_t resv = mjs_mk_undefined();
  mjs_val_t argvs[4];

  n = strchr(s, ' ');
  if (n == NULL) {
    n = s;
  } else {
    n++;
  }
  e = strchr(n, '(');
  if (e == NULL) {
    e = n + strlen(n);
  } else {
    a = e + 1;
  }

  res.size = 4;
  res.is_float = 0;
  res.v.i = 0;

  nargs = mjs_get_int(mjs, mjs_pop(mjs));
  for (i = 0; i < nargs; i++) {
    const char *ae;
    if (a == NULL) {
      LOG(LL_ERROR, ("bad signature '%s', got %d actuals", s, nargs));
      goto clean;
    }
    while (*a == ' ') a++;
    ae = a;
    while (*ae && *ae != ',' && *ae != ')') ae++;

    mjs_val_t arg = mjs_pop(mjs);
    if (strncmp(a, "int", ae - a) == 0) {
      ffi_set_int32(&args[i], mjs_get_int(mjs, arg));
    } else if (strncmp(a, "char*", 5) == 0 || strncmp(a, "char *", 6) == 0) {
      if (!mjs_is_string(arg)) {
        LOG(LL_ERROR, ("actual arg not a string"));
        goto clean;
      }
      argvs[i] = arg;
      ffi_set_ptr(&args[i], (void *) mjs_get_cstring(mjs, &argvs[i]));
    } else if (strncmp(a, "void*", 5) == 0 || strncmp(a, "void *", 6) == 0) {
      if (!mjs_is_foreign(arg)) {
        LOG(LL_ERROR, ("actual arg is not a ptr"));
        goto clean;
      }
      ffi_set_ptr(&args[i], (void *) mjs_get_ptr(mjs, arg));
    } else {
      LOG(LL_ERROR, ("unsupported type %.*s", (int) (ae - a), a));
      goto clean;
    }

    while (*a && *a != ',' && *a != ')') a++;
    a++;
    if (*a == '\0') a = NULL;
  }

  if (mjs->dlsym == NULL) {
    LOG(LL_ERROR, ("resolver not set, call mjs_set_ffi_resolver"));
    goto clean;
  }

  mg_asprintf(&buf, 0, "%.*s", (int) (e - n), n);
  fn = (ffi_fn_t) mjs->dlsym(RTLD_DEFAULT, buf);
  free(buf);

  if (fn == NULL) {
    LOG(LL_ERROR, ("cannot resolve function %s", buf));
    goto clean;
  }

  ffi_call(fn, nargs, &res, args);

  resv = mjs_mk_number(mjs, res.v.i);
clean:
  mjs_push(mjs, resv);
}

struct ffi_cb_args {
  struct mjs *mjs;
  mjs_val_t func;
  mjs_val_t user_data;
};

static void ffi_cb_impl_void_void(void *param) {
  struct ffi_cb_args *cbargs = (struct ffi_cb_args *)param;
  LOG(LL_DEBUG, ("calling JS callback void-void %d from C", mjs_get_int(cbargs->mjs, cbargs->func)));
  mjs_call(cbargs->mjs, NULL, cbargs->func, 1, cbargs->user_data);
}

/*
 * ffi_cb_void_void returns an implementation of C callback with the signature
 * void (*)(void *user_data);
 */
MJS_PRIVATE void mjs_ffi_cb_void_void(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int nargs = mjs_get_int(mjs, mjs_pop(mjs));

  /* drop all provided args, if any */
  while (nargs--) {
    mjs_pop(mjs);
  }

  /* put the callback impl */
  bf_push(&vm->dstack, mjs_mk_foreign(mjs, ffi_cb_impl_void_void));
}

/*
 * ffi_cb_arg takes a callback MJS function and an optional user data
 * (which may be any MJS value), and returns a foreign pointer which should
 * be used as a C callback user data.
 */
MJS_PRIVATE void mjs_ffi_cb_arg(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int nargs = mjs_get_int(mjs, mjs_pop(mjs));

  if (nargs < 1) {
    /* TODO(dfrank): return an error */
    LOG(LL_ERROR, ("missing argument 'func'"));
    bf_push(&vm->dstack, mjs_mk_undefined());
    return;
  }

  /*
   * freed by mjs_ffi_cb_arg_free(), which should be called by the user
   * TODO(dfrank): try to improve
   */
  struct ffi_cb_args *cbargs = calloc(1, sizeof(*cbargs));
  cbargs->mjs = mjs;
  cbargs->func = MJS_UNDEFINED;
  cbargs->user_data = MJS_UNDEFINED;

  mjs_own(mjs, &cbargs->func);
  mjs_own(mjs, &cbargs->user_data);

  /* get MJS callback */
  cbargs->func = mjs_pop(mjs);
  nargs--;

  /* get user_data for MJS callback: by default, it's `undefined` */
  cbargs->user_data = MJS_UNDEFINED;
  if (nargs > 0) {
    cbargs->user_data = mjs_pop(mjs);
    nargs--;
  }

  /* drop all provided args, if any */
  while (nargs--) {
    mjs_pop(mjs);
  }

  /* push the cbargs pointer */
  bf_push(&vm->dstack, mjs_mk_foreign(mjs, cbargs));
}

/*
 * ffi_cb_arg_free frees the foreign pointer returned by
 * ffi_cb_arg()
 */
MJS_PRIVATE void mjs_ffi_cb_arg_free(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int nargs = mjs_get_int(mjs, mjs_pop(mjs));

  if (nargs < 1) {
    /* TODO(dfrank): return an error */
    LOG(LL_ERROR, ("missing argument 'arg'"));
    bf_push(&vm->dstack, mjs_mk_undefined());
    return;
  }

  /* get user data to free */
  mjs_val_t arg_ptr = mjs_pop(mjs);
  nargs--;

  /* drop all provided args, if any */
  while (nargs--) {
    mjs_pop(mjs);
  }

  struct ffi_cb_args *cbargs = (struct ffi_cb_args *)mjs_get_ptr(mjs, arg_ptr);

  mjs_disown(mjs, &cbargs->func);
  mjs_disown(mjs, &cbargs->user_data);

  free(cbargs);

  mjs_push(mjs, MJS_UNDEFINED);
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/gc.c"
#endif
/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include <stdio.h>

/* Amalgamated: #include "common/mbuf.h" */
/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/gc.h" */
/* Amalgamated: #include "mjs/internal.h" */
/* Amalgamated: #include "mjs/mm.h" */
/* Amalgamated: #include "mjs/object.h" */
/* Amalgamated: #include "mjs/primitive.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/varint.h" */

/*
 * Macros for marking reachable things: use bit 0.
 */
#define MARK(p) (((struct gc_cell *) (p))->head.word |= 1)
#define UNMARK(p) (((struct gc_cell *) (p))->head.word &= ~1)
#define MARKED(p) (((struct gc_cell *) (p))->head.word & 1)

/*
 * Similar to `MARK()` / `UNMARK()` / `MARKED()`, but `.._FREE` counterparts
 * are intended to mark free cells (as opposed to used ones), so they use
 * bit 1.
 */
#define MARK_FREE(p) (((struct gc_cell *) (p))->head.word |= 2)
#define UNMARK_FREE(p) (((struct gc_cell *) (p))->head.word &= ~2)
#define MARKED_FREE(p) (((struct gc_cell *) (p))->head.word & 2)

/*
 * When each arena has that or less free cells, GC will be scheduled
 */
#define GC_ARENA_CELLS_RESERVE 2

void gc_mark_string(struct mjs *, mjs_val_t *);

static struct gc_block *gc_new_block(struct gc_arena *a, size_t size);
static void gc_free_block(struct gc_block *b);
static void gc_mark_mbuf_pt(struct mjs *mjs, const struct mbuf *mbuf);

MJS_PRIVATE struct mjs_object *new_object(struct mjs *mjs) {
  return (struct mjs_object *) gc_alloc_cell(mjs, &mjs->object_arena);
}

MJS_PRIVATE struct mjs_property *new_property(struct mjs *mjs) {
  return (struct mjs_property *) gc_alloc_cell(mjs, &mjs->property_arena);
}

/* Initializes a new arena. */
MJS_PRIVATE void gc_arena_init(struct gc_arena *a, size_t cell_size,
                               size_t initial_size, size_t size_increment) {
  assert(cell_size >= sizeof(uintptr_t));

  memset(a, 0, sizeof(*a));
  a->cell_size = cell_size;
  a->size_increment = size_increment;
  a->blocks = gc_new_block(a, initial_size);
}

MJS_PRIVATE void gc_arena_destroy(struct mjs *mjs, struct gc_arena *a) {
  struct gc_block *b;

  if (a->blocks != NULL) {
    gc_sweep(mjs, a, 0);
    for (b = a->blocks; b != NULL;) {
      struct gc_block *tmp;
      tmp = b;
      b = b->next;
      gc_free_block(tmp);
    }
  }
}

static void gc_free_block(struct gc_block *b) {
  free(b->base);
  free(b);
}

static struct gc_block *gc_new_block(struct gc_arena *a, size_t size) {
  struct gc_cell *cur;
  struct gc_block *b;

  b = (struct gc_block *) calloc(1, sizeof(*b));
  if (b == NULL) abort();

  b->size = size;
  b->base = (struct gc_cell *) calloc(a->cell_size, b->size);
  if (b->base == NULL) abort();

  for (cur = GC_CELL_OP(a, b->base, +, 0);
       cur < GC_CELL_OP(a, b->base, +, b->size);
       cur = GC_CELL_OP(a, cur, +, 1)) {
    cur->head.link = a->free;
    a->free = cur;
  }

  return b;
}

/*
 * Returns whether the given arena has GC_ARENA_CELLS_RESERVE or less free
 * cells
 */
static int gc_arena_is_gc_needed(struct gc_arena *a) {
  struct gc_cell *r = a->free;
  int i;

  for (i = 0; i <= GC_ARENA_CELLS_RESERVE; i++, r = r->head.link) {
    if (r == NULL) {
      return 1;
    }
  }

  return 0;
}

MJS_PRIVATE int gc_strings_is_gc_needed(struct mjs *mjs) {
  struct mbuf *m = &mjs->owned_strings;
  return (double) m->len / (double) m->size > 0.9;
}

MJS_PRIVATE void *gc_alloc_cell(struct mjs *mjs, struct gc_arena *a) {
  struct gc_cell *r;

  if (a->free == NULL) {
    struct gc_block *b = gc_new_block(a, a->size_increment);
    b->next = a->blocks;
    a->blocks = b;
  }
  r = a->free;

  UNMARK(r);

  a->free = r->head.link;

  /* Schedule GC if needed */
  if (gc_arena_is_gc_needed(a)) {
    mjs->need_gc = 1;
  }

  /*
   * TODO(mkm): minor opt possible since most of the fields
   * are overwritten downstream, but not worth the yak shave time
   * when fields are added to GC-able structures */
  memset(r, 0, a->cell_size);
  return (void *) r;
}

/*
 * Scans the arena and add all unmarked cells to the free list.
 *
 * Empty blocks get deallocated. The head of the free list will contais cells
 * from the last (oldest) block. Cells will thus be allocated in block order.
 */
void gc_sweep(struct mjs *mjs, struct gc_arena *a, size_t start) {
  struct gc_block *b;
  struct gc_cell *cur;
  struct gc_block **prevp = &a->blocks;

  /*
   * Before we sweep, we should mark all free cells in a way that is
   * distinguishable from marked used cells.
   */
  {
    struct gc_cell *next;
    for (cur = a->free; cur != NULL; cur = next) {
      next = cur->head.link;
      MARK_FREE(cur);
    }
  }

  /*
   * We'll rebuild the whole `free` list, so initially we just reset it
   */
  a->free = NULL;

  for (b = a->blocks; b != NULL;) {
    size_t freed_in_block = 0;
    /*
     * if it turns out that this block is 100% garbage
     * we can release the whole block, but the addition
     * of it's cells to the free list has to be undone.
     */
    struct gc_cell *prev_free = a->free;

    for (cur = GC_CELL_OP(a, b->base, +, start);
         cur < GC_CELL_OP(a, b->base, +, b->size);
         cur = GC_CELL_OP(a, cur, +, 1)) {
      if (MARKED(cur)) {
        /* The cell is used and marked  */
        UNMARK(cur);
      } else {
        /*
         * The cell is either:
         * - free
         * - garbage that's about to be freed
         */

        if (MARKED_FREE(cur)) {
          /* The cell is free, so, just unmark it */
          UNMARK_FREE(cur);
        } else {
          /*
           * The cell is used and should be freed: call the destructor and
           * reset the memory
           */
          if (a->destructor != NULL) {
            a->destructor(mjs, cur);
          }
          memset(cur, 0, a->cell_size);
        }

        /* Add this cell to the `free` list */
        cur->head.link = a->free;
        a->free = cur;
        freed_in_block++;
      }
    }

    /*
     * don't free the initial block, which is at the tail
     * because it has a special size aimed at reducing waste
     * and simplifying initial startup. TODO(mkm): improve
     * */
    if (b->next != NULL && freed_in_block == b->size) {
      *prevp = b->next;
      gc_free_block(b);
      b = *prevp;
      a->free = prev_free;
    } else {
      prevp = &b->next;
      b = b->next;
    }
  }
}

MJS_PRIVATE void gc_mark(struct mjs *mjs, mjs_val_t v) {
  struct mjs_object *obj_base;
  struct mjs_property *prop;
  struct mjs_property *next;

  if (!mjs_is_object(v)) {
    return;
  }
  obj_base = get_object_struct(v);

  /*
   * we treat all object like things like objects but they might be functions,
   * gc_gheck_val checks the appropriate arena per actual value type.
   */
  if (!gc_check_val(mjs, v)) {
    abort();
  }

  if (MARKED(obj_base)) return;

  /* mark object itself, and its properties */
  for ((prop = obj_base->properties), MARK(obj_base); prop != NULL;
       prop = next) {
    if (!gc_check_ptr(&mjs->property_arena, prop)) {
      abort();
    }

    gc_mark_string(mjs, &prop->value);
    gc_mark_string(mjs, &prop->name);
    gc_mark(mjs, prop->value);

    next = prop->next;
    MARK(prop);
  }

  /* mark object's prototype */
  /*
   * We dropped support for object prototypes in MJS.
   * If we ever bring it back, don't forget to mark it
   */
  /* gc_mark(mjs, mjs_get_proto(mjs, v)); */
}

MJS_PRIVATE uint64_t gc_string_mjs_val_to_offset(mjs_val_t v) {
  return (((uint64_t)(uintptr_t) get_ptr(v)) & ~MJS_TAG_MASK);
}

MJS_PRIVATE mjs_val_t gc_string_val_from_offset(uint64_t s) {
  return s | MJS_TAG_STRING_O;
}

/* Mark a string value */
void gc_mark_string(struct mjs *mjs, mjs_val_t *v) {
  mjs_val_t h, tmp = 0;
  char *s;

  /* clang-format off */

  /*
   * If a value points to an unmarked string we shall:
   *  1. save the first 6 bytes of the string
   *     since we need to be able to distinguish real values from
   *     the saved first 6 bytes of the string, we need to tag the chunk
   *     as MJS_TAG_STRING_C
   *  2. encode value's address (v) into the first 6 bytes of the string.
   *  3. put the saved 8 bytes (tag + chunk) back into the value.
   *  4. mark the string by putting '\1' in the NUL terminator of the previous
   *     string chunk.
   *
   * If a value points to an already marked string we shall:
   *     (0, <6 bytes of a pointer to a mjs_val_t>), hence we have to skip
   *     the first byte. We tag the value pointer as a MJS_TAG_FOREIGN
   *     so that it won't be followed during recursive mark.
   *
   *  ... the rest is the same
   *
   *  Note: 64-bit pointers can be represented with 48-bits
   */

  /* clang-format on */

  if ((*v & MJS_TAG_MASK) != MJS_TAG_STRING_O) {
    return;
  }

  s = mjs->owned_strings.buf + gc_string_mjs_val_to_offset(*v);
  assert(s < mjs->owned_strings.buf + mjs->owned_strings.len);
  if (s[-1] == '\0') {
    memcpy(&tmp, s, sizeof(tmp) - 2);
    tmp |= MJS_TAG_STRING_C;
  } else {
    memcpy(&tmp, s, sizeof(tmp) - 2);
    tmp |= MJS_TAG_FOREIGN;
  }

  h = (mjs_val_t)(uintptr_t) v;
  s[-1] = 1;
  memcpy(s, &h, sizeof(h) - 2);
  memcpy(v, &tmp, sizeof(tmp));
}

void gc_compact_strings(struct mjs *mjs) {
  char *p = mjs->owned_strings.buf + 1;
  uint64_t h, next, head = 1;
  int len, llen;

  while (p < mjs->owned_strings.buf + mjs->owned_strings.len) {
    if (p[-1] == '\1') {
      /* relocate and update ptrs */
      h = 0;
      memcpy(&h, p, sizeof(h) - 2);

      /*
       * relocate pointers until we find the tail.
       * The tail is marked with MJS_TAG_STRING_C,
       * while mjs_val_t link pointers are tagged with MJS_TAG_FOREIGN
       */
      for (; (h & MJS_TAG_MASK) != MJS_TAG_STRING_C; h = next) {
        h &= ~MJS_TAG_MASK;
        memcpy(&next, (char *) (uintptr_t) h, sizeof(h));

        *(mjs_val_t *) (uintptr_t) h = gc_string_val_from_offset(head);
      }
      h &= ~MJS_TAG_MASK;

      /*
       * the tail contains the first 6 bytes we stole from
       * the actual string.
       */
      len = decode_varint((unsigned char *) &h, &llen);
      len += llen + 1;

      /*
       * restore the saved 6 bytes
       * TODO(mkm): think about endianness
       */
      memcpy(p, &h, sizeof(h) - 2);

      /*
       * and relocate the string data by packing it to the left.
       */
      memmove(mjs->owned_strings.buf + head, p, len);
      mjs->owned_strings.buf[head - 1] = 0x0;
      p += len;
      head += len;
    } else {
      len = decode_varint((unsigned char *) p, &llen);
      len += llen + 1;

      p += len;
    }
  }

  mjs->owned_strings.len = head;
}

MJS_PRIVATE int maybe_gc(struct mjs *mjs) {
  if (!mjs->inhibit_gc) {
    mjs_gc(mjs, 0);
    return 1;
  }
  return 0;
}

/*
 * mark an mbuf containing *pointers* to `mjs_val_t` values
 */
static void gc_mark_mbuf_pt(struct mjs *mjs, const struct mbuf *mbuf) {
  mjs_val_t **vp;
  for (vp = (mjs_val_t **) mbuf->buf; (char *) vp < mbuf->buf + mbuf->len;
       vp++) {
    gc_mark(mjs, **vp);
    gc_mark_string(mjs, *vp);
  }
}

/*
 * mark an array of `mjs_val_t` values (*not pointers* to them)
 */
static void gc_mark_val_array(struct mjs *mjs, mjs_val_t *vals, size_t len) {
  mjs_val_t *vp;
  for (vp = vals; vp < vals + len; vp++) {
    gc_mark(mjs, *vp);
    gc_mark_string(mjs, vp);
  }
}

static void gc_mark_bf_stack(struct mjs *mjs, struct bf_stack *stack) {
  size_t i;
  mjs_val_t *v;
  for (i = 0, v = (mjs_val_t *)stack->stack; i < stack->pos; i++, v++) {
    gc_mark(mjs, *v);
    gc_mark_string(mjs, v);
  }
}

/* Perform garbage collection */
void mjs_gc(struct mjs *mjs, int full) {
  gc_mark_val_array(mjs, (mjs_val_t *) &mjs->vals, sizeof(mjs->vals) / sizeof(mjs_val_t));

  gc_mark_mbuf_pt(mjs, &mjs->owned_values);

  gc_mark_bf_stack(mjs, &mjs->vm.dstack);
  gc_mark_bf_stack(mjs, &mjs->vm.rstack);

  gc_mark(mjs, (mjs_val_t)mjs->vm.tmp);
  gc_mark_string(mjs, (mjs_val_t *)&mjs->vm.tmp);

  gc_compact_strings(mjs);

  gc_sweep(mjs, &mjs->object_arena, 0);
  gc_sweep(mjs, &mjs->property_arena, 0);

  if (full) {
    /*
     * In case of full GC, we also resize strings buffer, but we still leave
     * some extra space (at most, `_MJS_STRING_BUF_RESERVE`) in order to avoid
     * frequent reallocations
     */
    size_t trimmed_size = mjs->owned_strings.len + _MJS_STRING_BUF_RESERVE;
    if (trimmed_size < mjs->owned_strings.size) {
      mbuf_resize(&mjs->owned_strings, trimmed_size);
    }
  }
}

MJS_PRIVATE int gc_check_val(struct mjs *mjs, mjs_val_t v) {
  if (mjs_is_object(v)) {
    return gc_check_ptr(&mjs->object_arena, get_object_struct(v));
  }
  return 1;
}

MJS_PRIVATE int gc_check_ptr(const struct gc_arena *a, const void *ptr) {
  const struct gc_cell *p = (const struct gc_cell *) ptr;
  struct gc_block *b;
  for (b = a->blocks; b != NULL; b = b->next) {
    if (p >= b->base && p < GC_CELL_OP(a, b->base, +, b->size)) {
      return 1;
    }
  }
  return 0;
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/object.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "mjs/gc.h" */
/* Amalgamated: #include "mjs/mm.h" */
/* Amalgamated: #include "mjs/object.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/primitive.h" */

MJS_PRIVATE mjs_val_t mjs_object_to_value(struct mjs_object *o) {
  if (o == NULL) {
    return MJS_NULL;
  } else {
    return pointer_to_value(o) | MJS_TAG_OBJECT;
  }
}

MJS_PRIVATE struct mjs_object *get_object_struct(mjs_val_t v) {
  struct mjs_object *ret = NULL;
  if (mjs_is_null(v)) {
    ret = NULL;
  } else {
    assert(mjs_is_object(v));
    ret = (struct mjs_object *) get_ptr(v);
  }
  return ret;
}

mjs_val_t mjs_mk_object(struct mjs *mjs) {
  struct mjs_object *o = new_object(mjs);
  if (o == NULL) {
    return MJS_NULL;
  }
  (void) mjs;
  o->properties = NULL;
  return mjs_object_to_value(o);
}

int mjs_is_object(mjs_val_t v) {
  return (v & MJS_TAG_MASK) == MJS_TAG_OBJECT;
}

MJS_PRIVATE struct mjs_property *mjs_get_own_property(struct mjs *mjs,
                                                      mjs_val_t obj,
                                                      const char *name,
                                                      size_t len) {
  struct mjs_property *p;
  struct mjs_object *o;

  if (!mjs_is_object(obj)) {
    return NULL;
  }

  o = get_object_struct(obj);

  if (len <= 5) {
    mjs_val_t ss = mjs_mk_string(mjs, name, len, 1);
    for (p = o->properties; p != NULL; p = p->next) {
      if (p->name == ss) return p;
    }
  } else {
    for (p = o->properties; p != NULL; p = p->next) {
      if (mjs_strcmp(mjs, &p->name, name, len) == 0) return p;
    }
    return p;
  }

  return NULL;
}

MJS_PRIVATE struct mjs_property *mjs_mk_property(struct mjs *mjs,
                                                 mjs_val_t name,
                                                 mjs_val_t value) {
  struct mjs_property *p = new_property(mjs);
  p->next = NULL;
  p->name = name;
  p->value = value;
  return p;
}

mjs_val_t mjs_get(struct mjs *mjs, mjs_val_t obj, const char *name,
                  size_t name_len) {
  struct mjs_property *p;

  if (name_len == (size_t) ~0) {
    name_len = strlen(name);
  }

  p = mjs_get_own_property(mjs, obj, name, name_len);
  if (p == NULL) {
    return MJS_UNDEFINED;
  } else {
    return p->value;
  }
}

mjs_val_t mjs_get_v(struct mjs *mjs, mjs_val_t obj, mjs_val_t name) {
  size_t n;
  const char *s = mjs_get_string(mjs, &name, &n);
  return mjs_get(mjs, obj, s, n);
}

mjs_err_t mjs_set(struct mjs *mjs, mjs_val_t obj, const char *name,
                  size_t name_len, mjs_val_t val) {
  struct mjs_property *p;

  if (name_len == (size_t) ~0) {
    name_len = strlen(name);
  }

  p = mjs_get_own_property(mjs, obj, name, name_len);
  if (p == NULL) {
    mjs_val_t namestr;
    struct mjs_object *o;
    if (!mjs_is_object(obj)) {
      return MJS_REFERENCE_ERROR;
    }

    namestr = mjs_mk_string(mjs, name, name_len, 1);
    p = mjs_mk_property(mjs, namestr, val);

    o = get_object_struct(obj);
    p->next = o->properties;
    o->properties = p;
  }

  p->value = val;
  return MJS_OK;
}

mjs_err_t mjs_set_v(struct mjs *mjs, mjs_val_t obj, mjs_val_t name,
                    mjs_val_t val) {
  size_t n;
  const char *s = mjs_get_string(mjs, &name, &n);
  return mjs_set(mjs, obj, s, n, val);
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/ops.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/*
 * This file contains bf words implemented in C.
 * The functions here must be referenced from //mjs:vm.bf.
 */

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "mjs/bf/bf.h" */
/* Amalgamated: #include "mjs/bf/mem.h" */
/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/primitive.h" */
/* Amalgamated: #include "mjs/ffi.h" */
/* Amalgamated: #include "mjs/object.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/util.h" */
/* Amalgamated: #include "mjs/vm.gen.h" */

void mjs_op_todo(struct bf_vm *vm) {
  (void) vm;
  LOG(LL_ERROR, ("TODO"));
}

void mjs_op_str(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  char ch;
  char buf[MJS_STRING_LITERAL_MAX_LEN];
  size_t len = 0;
  do {
    ch = (char) bf_read_byte(vm->iram, vm->ip++);
    if (len < MJS_STRING_LITERAL_MAX_LEN) {
      buf[len++] = ch;
    }
  } while (ch != '\0');

  bf_push(&vm->dstack, mjs_mk_string(mjs, buf, len - 1, 1));
}

void mjs_op_mkobj(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs_mk_object(mjs));
}

void mjs_op_addprop(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t val = bf_pop(&vm->dstack);
  mjs_val_t name = bf_pop(&vm->dstack);
  mjs_val_t obj = bf_pop(&vm->dstack);
  mjs_set_v(mjs, obj, name, val);
  bf_push(&vm->dstack, obj);
}

void mjs_op_setprop(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t val = bf_pop(&vm->dstack);
  mjs_val_t name = bf_pop(&vm->dstack);
  mjs_val_t obj = bf_pop(&vm->dstack);
  mjs_set_v(mjs, obj, name, val);
  bf_push(&vm->dstack, val);
}

void mjs_op_getprop(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t name = bf_pop(&vm->dstack);
  mjs_val_t obj = bf_pop(&vm->dstack);
  bf_push(&vm->dstack, mjs_get_v(mjs, obj, name));
}

/*
 * Scans the scope chain until it finds a matching property or it returns NULL.
 *
 * Currently we have only the function local scope and the global scope.
 * The current function scope is in mjs->vals.scope.
 * If you want to implement closures make sure this function walks the
 * appropriate scope chain.
 */
MJS_PRIVATE struct mjs_property *mjs_lookup_property(struct mjs *mjs,
                                                     mjs_val_t name) {
  struct mjs_property *p;
  mjs_val_t scope = mjs->vals.scope;
  size_t n;
  const char *s = mjs_get_string(mjs, &name, &n);

  p = mjs_get_own_property(mjs, scope, s, n);
  if (p != NULL) return p;
  return mjs_get_own_property(mjs, mjs_get_global(mjs), s, n);
}

void mjs_op_getvar(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t name = bf_pop(&vm->dstack);
  struct mjs_property *p = mjs_lookup_property(mjs, name);
  bf_push(&vm->dstack, (p == NULL ? mjs_mk_undefined() : p->value));
}

void mjs_op_setvar(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t value = bf_pop(&vm->dstack);
  mjs_val_t name = bf_pop(&vm->dstack);
  struct mjs_property *p = mjs_lookup_property(mjs, name);

  if (p != NULL) {
    p->value = value;
  } else {
    mjs_set_v(mjs, mjs_get_global(mjs), name, value);
  }
  bf_push(&vm->dstack, value);
}

void mjs_op_jscall(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t func = bf_pop(&vm->dstack);
  size_t nargs = bf_to_int(bf_tos(&vm->dstack));
  size_t stack_pos = vm->dstack.pos - 1 /* nargs */;

  assert(stack_pos >= nargs);
  /*
   * the jscall word has this stack effect: ( argN .. arg2 arg1 N f -- res)
   * it takes the `f` to figure out who to call, and passes the rest to the
   * function being called, including the nargs number so that the function can
   * process variable number of arguments.
   * However, it would be very annoying and error-prone if every function should
   * cleanup the stack of unwanted arguments. Thus we stash the position the
   * stack should have once `jscall` returns (all arguments consumed).
   *
   * However, we cannot restore the stack in this very function, since we don't
   * call a function from C, but instead we "branch" the interpreter to the `f`
   * implementation. When `f` returns it just continues to execute right after
   * the place that called `jscall`.
   *
   * I.e. once we start executing `f`, we cannot do anything more here. However,
   * if we push another word to the return stack, that word will be executed
   * when `f`, returns. Thus we push: /jscall_exit, which is a word that
   * restores the stack using the position we saved earlier (also on the return
   * stack). It preserves the return value of `f` which was at the top of the
   * stack.
   */
  bf_push(&vm->rstack, bf_from_int(stack_pos - nargs));
  bf_push(&vm->rstack, bf_from_int(MJS_WORD_PTR_jscall_exit));

  if (mjs_is_number(func)) {
    vm->ip = bf_to_int(func);
  } else if (mjs_is_foreign(func)) {
    void (*native)(struct bf_vm *vm);
    native = (void (*) (struct bf_vm *vm)) mjs_get_ptr(mjs, func);
    native(vm);
  } else if (mjs_is_string(func)) {
    mjs_ffi_call(mjs, func);
  } else if (mjs_is_undefined(func)) {
    printf("undefined is not a function\n");
    abort();
  } else {
    /* TODO: add mjs_die so that we can exit from exec with an error */
    printf("function is of an unknown type\n");
    abort();
  }
}

void mjs_op_getscope(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs->vals.scope);
}

void mjs_op_setscope(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs->vals.scope = bf_pop(&vm->dstack);
}

void mjs_op_getframe(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs->vals.call_frame);
}

void mjs_op_setframe(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs->vals.call_frame = bf_pop(&vm->dstack);
}

void mjs_op_undefined(struct bf_vm *vm) {
  bf_push(&vm->dstack, mjs_mk_undefined());
}

void mjs_op_null(struct bf_vm *vm) {
  bf_push(&vm->dstack, mjs_mk_null());
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/parser.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/*
 * This file implements the parser and compiler for MJS.
 *
 * We use a bottom up parser generated by lemon, the parser generator from the
 * sqlite project.
 *
 * The code generation technique is optimized for simplicity, not for space
 * and cleverness.
 *
 * You can think of it as an upside down executable syntax tree.
 *
 * A bottom up parser naturally builds a tree from the leaves up to the
 * root. The code is emitted precisely in that sequence, from the leaves
 * up. Each "node" of the tree is an anonymous bf word.
 *
 * For example `1` is a literal number expression, thus `: anon 1 ;`.
 * These are 2 bf instructions: the literal and the exit opcode (the `;`).
 * (How that encodes down to bytes is irrelevant in this discussion, see the
 * bf compiler; however an interesting note is that in most cases the
 * call to a previously defined subexpression can be encoded in one byte, a
 * negative offset).
 *
 * Another example: the `1+2` expression would be classically represented with a
 * binary node `+` and two pointers to the left and right subexpressions.
 * We do the same thing here but with executable bf code:
 *
 * ```
 * : anon3 anon1 anon2 + ;
 * ```
 *
 * These are 4 bf words: a call to the left subexpression, a call to the
 * right subexpression, the add operation and exit.
 *
 * And so forth. This technique can easily encode arbitrary expressions by
 * just appending bytes to the instruction stream. It works even if
 * subexpressions generate code that is meant to be executed straight away,
 * for example: `mqtt.subscribe('bar', function() {...})` or
 * `;1+(l=function(){return 10;})()+l()`.
 *
 * Basically all the juice is emitted even before we start to emit the code
 * for `mqtt.subscribe`.
 *
 * This is well suited for compiling straight to flash, since flash works
 * well in append only.
 *
 * ---
 *
 * Statements, again for simplicity, are chained so that the last statement
 * calls the previous one which calls the previous one etc until the first
 * is reached:
 *
 * ```
 * $ blaze run //mjs:mjs_shell -- -c -e '1;2;3;4;' >/tmp/dump.bin
 * $ blaze run //mjs:disasm /tmp/dump.bin
 * : anon1 1 ;
 * : anon2 anon1 ;
 * : anon3 2 ;
 * : anon4 anon2 drop anon3 ;
 * : anon5 3 ;
 * : anon6 anon4 drop anon5 ;
 * : anon7 4 ;
 * : anon8 anon6 drop anon7 ;
 * ```
 *
 * This is suboptimal as it requires a 16-bit word on the stack for each
 * statement in a block.
 * To put things in perspective 12 statements will waste the same memory on the
 * stack as a single object propertly (without counting the space for the
 * property name).
 *
 * This can be solved with a general inlining technique (TODO).
 * The basic idea is that we make a second pass over the generated stream and we
 * inline all the word bodies that are referenced only once. This will yield:
 *
 * ```
 * $ blaze run //mjs:mjs_shell -- -c -e '1+2;3+4;' >/tmp/dump.bin
 * $ blaze run //mjs:disasm /tmp/dump.bin
 * : anon1 1 ;
 * : anon2 2 ;
 * : anon3 anon1 anon2 + ;
 * : anon4 anon3 ;
 * : anon5 3 ;
 * : anon6 4 ;
 * : anon7 anon5 anon6 + ;
 * : anon8 anon4 drop anon7 ;
 * ```
 *
 * after inlining:
 *
 * ```
 * : anon8 1 2 drop 3 4 + ;
 * ```
 *
 * The rules of concatenative languages allow us to simply replace each
 * invocation of a word with its body.
 */

#include <stdio.h>
#include <string.h>

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "common/cs_file.h" */
/* Amalgamated: #include "mjs/bf/mem.h" */
/* Amalgamated: #include "mjs/parser.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/str_util.h" */
/* Amalgamated: #include "mjs/vm.gen.h" */

static unsigned long mjs_get_column(const char *code, const char *pos) {
  const char *p = pos;
  while (p > code && *p != '\n') {
    p--;
  }
  return p == code ? pos - p : pos - (p + 1);
}

typedef int mjs_tok_t;

static int next_tok(struct pstate *p) {
  int tok = pnext(p);
#define DT(x, y) ((x) << 8 | (y))

  /* Map token ID produced by tok.c to token ID produced by lemon */
  /* clang-format off */
  switch (tok) {
    case ':': return TOK_COLON;
    case ';': return TOK_SEMICOLON;
    case ',': return TOK_COMMA;
    case '=': return TOK_ASSIGN;
    case '{': return TOK_OPEN_CURLY;
    case '}': return TOK_CLOSE_CURLY;
    case '(': return TOK_OPEN_PAREN;
    case ')': return TOK_CLOSE_PAREN;
    case '[': return TOK_OPEN_BRACKET;
    case ']': return TOK_CLOSE_BRACKET;
    case '*': return TOK_MUL;
    case '+': return TOK_PLUS;
    case '-': return TOK_MINUS;
    case '/': return TOK_DIV;
    case '%': return TOK_REM;
    case '^': return TOK_XOR;
    case '.': return TOK_DOT;
    case DT('<','<'): return TOK_LSHIFT;
    case DT('>','>'): return TOK_RSHIFT;
    case DT('-','-'): return TOK_MINUS_MINUS;
    case DT('+','+'): return TOK_PLUS_PLUS;

    /* TODO(lsm): wrap these into a single ASSIGN op and delta */
    case DT('+','='): return TOK_PLUS_ASSIGN;
    case DT('-','='): return TOK_MINUS_ASSIGN;
    case DT('*','='): return TOK_MUL_ASSIGN;
    case DT('/','='): return TOK_DIV_ASSIGN;
    case DT('&','='): return TOK_AND_ASSIGN;
    case DT('|','='): return TOK_OR_ASSIGN;
    case DT('%','='): return TOK_REM_ASSIGN;

    case DT('=','='): return TOK_EQ;
    case DT('!','='): return TOK_NE;
    case DT('<','='): return TOK_LE;
    case DT('>','='): return TOK_GE;

    case '<': return TOK_LT;
    case '>': return TOK_GT;

    case TOK_NUM: return TOK_NUMBER;
    case TOK_STR: return TOK_STRING_LITERAL;
    case TOK_IDENT: return TOK_IDENTIFIER;
    case TOK_KEYWORD_LET: return TOK_LET;
    case TOK_KEYWORD_UNDEFINED: return TOK_UNDEFINED;
    case TOK_KEYWORD_IF: return TOK_IF;
    case TOK_KEYWORD_ELSE: return TOK_ELSE;
    case TOK_KEYWORD_TRUE: return TOK_TRUE;
    case TOK_KEYWORD_FALSE: return TOK_FALSE;
    case TOK_KEYWORD_FUNCTION: return TOK_FUNCTION;
    case TOK_KEYWORD_RETURN: return TOK_RETURN;
    case TOK_KEYWORD_WHILE: return TOK_WHILE;
    case TOK_KEYWORD_FOR: return TOK_FOR;
    default: return TOK_END_OF_INPUT;
  }
  /* clang-format on */
}

mjs_err_t mjs_parse_buf(struct mjs *mjs, const char *src, size_t len,
                        struct mjs_parse_ctx *ctx) {
  mjs_err_t err = MJS_OK;
  void *parser = mjsParserAlloc(malloc);
  struct mjs_token tok_data = {src};
  int tok;

  memset(ctx, 0, sizeof(*ctx));

  pinit(NULL, src, &ctx->pstate);

  ctx->mjs = mjs;
  ctx->gen = mjs->last_code;

  while ((tok = next_tok(&ctx->pstate)) != TOK_END_OF_INPUT) {
    tok_data.begin = ctx->pstate.tok_ptr;
    LOG(LL_DEBUG, ("sending token %d '%.*s' state %d", tok, ctx->pstate.tok_len,
                   tok_data.begin, ctx->state));
    mjsParser(parser, tok, tok_data, ctx);
  }

  tok_data.begin = ctx->pstate.tok_ptr;
  mjsParser(parser, 0, tok_data, ctx);

  if (ctx->syntax_error.begin != NULL) {
    int line_len = 0;
    const char *p;
    unsigned long col = mjs_get_column(src, ctx->syntax_error.begin);

    for (p = ctx->syntax_error.begin - col; *p != '\0' && *p != '\n'; p++) {
      line_len++;
    }

    /* fixup line number: line_no points to the beginning of the next token */
    for (; p < ctx->pstate.pos; p++) {
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

  LOG(LL_DEBUG, ("emitted %d bytes", ctx->gen - ctx->mjs->last_code));
  LOG(LL_DEBUG, ("start at %d", ctx->mjs->last_code));

  ctx->mjs->last_code = ctx->gen;

  (void) len;
  return err;
}

mjs_err_t mjs_parse(struct mjs *mjs, const char *src,
                    struct mjs_parse_ctx *ctx) {
  return mjs_parse_buf(mjs, src, strlen(src), ctx);
}

mjs_err_t mjs_parse_file(struct mjs *mjs, const char *path,
                         struct mjs_parse_ctx *ctx) {
  mjs_err_t err;

  size_t len;
  char *src = cs_read_file(path, &len);
  if (src == NULL) {
    return mjs_set_errorf(mjs, MJS_INTERNAL_ERROR, "cannot open file %s", path);
  }
  err = mjs_parse_buf(mjs, src, len, ctx);
  free(src);
  return err;
}

void mjs_dump_bcode(struct mjs *mjs, const char *filename, bf_word_ptr_t start,
                    bf_word_ptr_t end) {
  bf_word_ptr_t i;
  FILE *out = fopen(filename, "w");

  for (i = start; i < end; i++) {
    uint8_t b = (uint8_t) bf_read_byte(mjs->vm.iram, i);
    fwrite(&b, 1, 1, out);
  }
  fclose(out);
}

bf_word_ptr_t mjs_emit(struct mjs_parse_ctx *ctx, bf_opcode_t op) {
  LOG(LL_DEBUG, ("emitting opcode %d at %d", op, ctx->gen));
  return mjs_emit_uint8(ctx, (uint8_t) op);
}

bf_word_ptr_t mjs_emit_quote(struct mjs_parse_ctx *ctx, bf_word_ptr_t dst) {
  bf_word_ptr_t start = mjs_emit(ctx, MJS_OP_quote);
  mjs_emit_uint16(ctx, dst);
  return start;
}

bf_word_ptr_t mjs_emit_call(struct mjs_parse_ctx *ctx, bf_word_ptr_t dst) {
  int offset;
  /* LOG(LL_ERROR, ("EMITTING CALL TO %d", dst)); */
  /* assert(dst < ctx->gen); */
  offset = dst - ctx->gen;
  LOG(LL_DEBUG, ("emitting call to %d at %d", dst, ctx->gen));
  if (offset >= BF_MIN_LOCAL_OFFSET) {
    return mjs_emit_uint8(ctx, (bf_opcode_t)offset);
  } else {
    bf_word_ptr_t start = mjs_emit_quote(ctx, dst);
    mjs_emit(ctx, MJS_OP_call);
    return start;
  }
}

bf_word_ptr_t mjs_emit_bin(struct mjs_parse_ctx *ctx, bf_word_ptr_t a,
                           bf_word_ptr_t b, bf_opcode_t op) {
  bf_word_ptr_t start = ctx->gen;
  mjs_emit_call(ctx, a);
  mjs_emit_call(ctx, b);
  mjs_emit(ctx, op);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_num(struct mjs_parse_ctx *ctx, const char *lit) {
  int n = atoi(lit);
  bf_word_ptr_t start = mjs_emit(ctx, MJS_OP_quote);
  mjs_emit_uint16(ctx, (uint16_t) n);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_str_inline(struct mjs_parse_ctx *ctx, const char *lit) {
  bf_word_ptr_t start = mjs_emit(ctx, MJS_OP_str);
  char quote = lit[0];
  size_t len = 0, ulen, i;
  char buf[MJS_STRING_LITERAL_MAX_LEN];

  lit++;
  while (lit[len++] != quote) {
    if (lit[len] == '\\') len += 2;
  }

  ulen = unescape(lit, len - 1, buf);
  for (i = 0; i < ulen; i++) {
    mjs_emit_uint8(ctx, buf[i]);
  }
  mjs_emit_uint8(ctx, 0);
  return start;
}

bf_word_ptr_t mjs_emit_str(struct mjs_parse_ctx *ctx, const char *lit) {
  bf_word_ptr_t start = mjs_emit_str_inline(ctx, lit);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_ident_inline(struct mjs_parse_ctx *ctx,
                                    const char *ident) {
  bf_word_ptr_t start = mjs_emit(ctx, MJS_OP_str);

  while (is_ident(*ident) || is_digit(*ident)) {
    mjs_emit_uint8(ctx, *ident++);
  }

  mjs_emit_uint8(ctx, 0);
  return start;
}

bf_word_ptr_t mjs_emit_ident(struct mjs_parse_ctx *ctx, const char *ident) {
  bf_word_ptr_t start = mjs_emit_ident_inline(ctx, ident);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_str_or_ident(struct mjs_parse_ctx *ctx,
                                    const char *lit) {
  if (lit[0] == '"' || lit[0] == '\'') {
    return mjs_emit_str_inline(ctx, lit);
  } else {
    return mjs_emit_ident_inline(ctx, lit);
  }
}

bf_word_ptr_t mjs_emit_var(struct mjs_parse_ctx *ctx, const char *ident) {
  /*
   * Obviously we could encode a var reference more efficiently by creating
   * a getvar word that takes the variable name from the instruction stream.
   * The reason it is not so now is simply because of lazines.
   */
  bf_word_ptr_t start = mjs_emit_ident_inline(ctx, ident);
  mjs_emit(ctx, MJS_OP_getvar);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_assign(struct mjs_parse_ctx *ctx, bf_word_ptr_t lhs,
                              bf_word_ptr_t val, bf_opcode_t op) {
  bf_word_ptr_t start = mjs_emit_call(ctx, lhs);
  if (op != 0) {
    mjs_emit(ctx, MJS_OP_dup);
    mjs_emit(ctx, MJS_OP_getvar);
  }
  mjs_emit_call(ctx, val);
  if (op != 0) {
    mjs_emit(ctx, op);
  }
  mjs_emit(ctx, MJS_OP_setvar);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_func(struct mjs_parse_ctx *ctx, bf_word_ptr_t args,
                            bf_word_ptr_t body) {
  bf_word_ptr_t start, def;
  def = mjs_emit(ctx, MJS_OP_jsenter);
  /*
   * If arglist is not empty, emit a call to the (already emitted) word which
   * does something like: `"foo" setarg "bar" setarg`
   */
  if (args != BF_INVALID_WORD_PTR) {
    mjs_emit_call(ctx, args);
    /*
     * cleanup stuff which is left after the last `setarg` call
     * (see vm.bf for comments on its stack effect)
     */
    mjs_emit(ctx, MJS_OP_drop);
    mjs_emit(ctx, MJS_OP_drop);
  }
  mjs_emit_call(ctx, body);
  mjs_emit(ctx, MJS_OP_drop);
  mjs_emit(ctx, MJS_OP_undefined);
  mjs_emit(ctx, MJS_OP_jsexit);
  mjs_emit(ctx, MJS_OP_exit);

  start = mjs_emit_quote(ctx, def);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_add_stmt(struct mjs_parse_ctx *ctx, bf_word_ptr_t stmtlist,
                           bf_word_ptr_t stmt) {
  bf_word_ptr_t start;
  start = mjs_emit_call(ctx, stmtlist);
  mjs_emit(ctx, MJS_OP_drop);
  mjs_emit_call(ctx, stmt);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_uint8(struct mjs_parse_ctx *ctx, uint8_t v) {
  bf_word_ptr_t start = ctx->gen;
  if (!bf_is_mapped(ctx->mjs->vm.iram, ctx->gen)) {
    bf_mmap(&ctx->mjs->vm.iram, calloc(1, FR_PAGE_SIZE), FR_PAGE_SIZE, 0);
  }
  LOG(LL_DEBUG, ("emitting byte %02X at %d", v, ctx->gen));
  bf_write_byte(ctx->mjs->vm.iram, ctx->gen++, v);
  return start;
}

bf_word_ptr_t mjs_emit_uint16(struct mjs_parse_ctx *ctx, uint16_t v) {
  bf_word_ptr_t start = mjs_emit_uint8(ctx, v >> 8);
  mjs_emit_uint8(ctx, v & 0xff);
  return start;
}

bf_word_ptr_t mjs_emit_uint32(struct mjs_parse_ctx *ctx, uint32_t v) {
  bf_word_ptr_t start = mjs_emit_uint16(ctx, v >> 16);
  mjs_emit_uint16(ctx, v & 0xffff);
  return start;
}

bf_word_ptr_t mjs_emit_uint64(struct mjs_parse_ctx *ctx, uint64_t v) {
  bf_word_ptr_t start = mjs_emit_uint32(ctx, v >> 32);
  mjs_emit_uint32(ctx, v & 0xffffffff);
  return start;
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/primitive.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "mjs/primitive.h" */
/* Amalgamated: #include "mjs/core.h" */

mjs_val_t mjs_mk_null(void) {
  return MJS_NULL;
}

int mjs_is_null(mjs_val_t v) {
  return v == MJS_NULL;
}

mjs_val_t mjs_mk_undefined(void) {
  return MJS_UNDEFINED;
}

int mjs_is_undefined(mjs_val_t v) {
  return v == MJS_UNDEFINED;
}

mjs_val_t mjs_mk_number(struct mjs *mjs, double v) {
  mjs_val_t res;
  (void) mjs;
  /* not every NaN is a JS NaN */
  if (isnan(v)) {
    res = MJS_TAG_NAN;
  } else {
    union {
      double d;
      mjs_val_t r;
    } u;
    u.d = v;
    res = u.r;
  }
  return res;
}

static double get_double(mjs_val_t v) {
  union {
    double d;
    mjs_val_t v;
  } u;
  u.v = v;
  /* Due to NaN packing, any non-numeric value is already a valid NaN value */
  return u.d;
}

double mjs_get_double(struct mjs *mjs, mjs_val_t v) {
  (void) mjs;
  return get_double(v);
}

int mjs_get_int(struct mjs *mjs, mjs_val_t v) {
  (void) mjs;
  return (int) get_double(v);
}

int32_t mjs_get_int32(struct mjs *mjs, mjs_val_t v) {
  (void) mjs;
  return (int32_t) get_double(v);
}

int mjs_is_number(mjs_val_t v) {
  return v == MJS_TAG_NAN || !isnan(get_double(v));
}

MJS_PRIVATE mjs_val_t pointer_to_value(void *p) {
  uint64_t n = ((uint64_t)(uintptr_t) p);

  assert((n & MJS_TAG_MASK) == 0 || (n & MJS_TAG_MASK) == (~0 & MJS_TAG_MASK));
  return n & ~MJS_TAG_MASK;
}

MJS_PRIVATE void *get_ptr(mjs_val_t v) {
  return (void *) (uintptr_t)(v & 0xFFFFFFFFFFFFUL);
}

void *mjs_get_ptr(struct mjs *mjs, mjs_val_t v) {
  (void) mjs;
  if (!mjs_is_foreign(v)) {
    return NULL;
  }
  return get_ptr(v);
}

mjs_val_t mjs_mk_foreign(struct mjs *mjs, void *p) {
  (void) mjs;
  return pointer_to_value(p) | MJS_TAG_FOREIGN;
}

int mjs_is_foreign(mjs_val_t v) {
  return (v & MJS_TAG_MASK) == MJS_TAG_FOREIGN;
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/str_util.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "common/mbuf.h" */
/* Amalgamated: #include "common/utf.h" */
/* Amalgamated: #include "mjs/str_util.h" */
/* Amalgamated: #include "mjs/varint.h" */

enum unescape_error {
  SLRE_INVALID_HEX_DIGIT,
  SLRE_INVALID_ESC_CHAR,
  SLRE_UNTERM_ESC_SEQ,
};

static int hex(int c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -SLRE_INVALID_HEX_DIGIT;
}

static int nextesc(const char **p) {
  const unsigned char *s = (unsigned char *) (*p)++;
  switch (*s) {
    case 0:
      return -SLRE_UNTERM_ESC_SEQ;
    case 'c':
      ++*p;
      return *s & 31;
    case 'b':
      return '\b';
    case 't':
      return '\t';
    case 'n':
      return '\n';
    case 'v':
      return '\v';
    case 'f':
      return '\f';
    case 'r':
      return '\r';
    case '\\':
      return '\\';
    case 'u':
      if (isxdigit(s[1]) && isxdigit(s[2]) && isxdigit(s[3]) &&
          isxdigit(s[4])) {
        (*p) += 4;
        return hex(s[1]) << 12 | hex(s[2]) << 8 | hex(s[3]) << 4 | hex(s[4]);
      }
      return -SLRE_INVALID_HEX_DIGIT;
    case 'x':
      if (isxdigit(s[1]) && isxdigit(s[2])) {
        (*p) += 2;
        return (hex(s[1]) << 4) | hex(s[2]);
      }
      return -SLRE_INVALID_HEX_DIGIT;
    default:
      return -SLRE_INVALID_ESC_CHAR;
  }
}

MJS_PRIVATE size_t unescape(const char *s, size_t len, char *to) {
  const char *end = s + len;
  size_t n = 0;
  char tmp[4];
  Rune r;

  while (s < end) {
    s += chartorune(&r, s);
    if (r == '\\' && s < end) {
      switch (*s) {
        case '"':
          s++, r = '"';
          break;
        case '\'':
          s++, r = '\'';
          break;
        case '\n':
          s++, r = '\n';
          break;
        default: {
          const char *tmp_s = s;
          int i = nextesc(&s);
          switch (i) {
            case -SLRE_INVALID_ESC_CHAR:
              r = '\\';
              s = tmp_s;
              n += runetochar(to == NULL ? tmp : to + n, &r);
              s += chartorune(&r, s);
              break;
            case -SLRE_INVALID_HEX_DIGIT:
            default:
              r = i;
          }
        }
      }
    }
    n += runetochar(to == NULL ? tmp : to + n, &r);
  }

  return n;
}

MJS_PRIVATE void embed_string(struct mbuf *m, size_t offset, const char *p,
                              size_t len, uint8_t /*enum embstr_flags*/ flags) {
  char *old_base = m->buf;
  uint8_t p_backed_by_mbuf = p >= old_base && p < old_base + m->len;
  size_t n = (flags & EMBSTR_UNESCAPE) ? unescape(p, len, NULL) : len;

  /* Calculate how many bytes length takes */
  int k = calc_llen(n);

  /* total length: varing length + string len + zero-term */
  size_t tot_len = k + n + !!(flags & EMBSTR_ZERO_TERM);

  /* Allocate buffer */
  mbuf_insert(m, offset, NULL, tot_len);

  /* Fixup p if it was relocated by mbuf_insert() above */
  if (p_backed_by_mbuf) {
    p += m->buf - old_base;
  }

  /* Write length */
  encode_varint(n, (unsigned char *) m->buf + offset);

  /* Write string */
  if (p != 0) {
    if (flags & EMBSTR_UNESCAPE) {
      unescape(p, len, m->buf + offset + k);
    } else {
      memcpy(m->buf + offset + k, p, len);
    }
  }

  /* add NULL-terminator if needed */
  if (flags & EMBSTR_ZERO_TERM) {
    m->buf[offset + tot_len - 1] = '\0';
  }
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/string.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "common/mg_str.h" */
/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/gc.h" */
/* Amalgamated: #include "mjs/internal.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/str_util.h" */
/* Amalgamated: #include "mjs/varint.h" */

/* TODO(lsm): NaN payload location depends on endianness, make crossplatform */
#define GET_VAL_NAN_PAYLOAD(v) ((char *) &(v))

/*
 * Dictionary of read-only strings with length > 5.
 * NOTE(lsm): must be sorted lexicographically, because
 * v_find_string_in_dictionary performs binary search over this list.
 */
/* clang-format off */
MJS_PRIVATE const struct mg_str v_dictionary_strings[] = {
    MG_MK_STR("print"),
};
/* clang-format on */

static int v_find_string_in_dictionary(const char *s, size_t len) {
  size_t start = 0, end = ARRAY_SIZE(v_dictionary_strings);

  while (s != NULL && start < end) {
    size_t mid = start + (end - start) / 2;
    const struct mg_str *v = &v_dictionary_strings[mid];
    size_t min_len = len < v->len ? len : v->len;
    int comparison_result = memcmp(s, v->p, min_len);
    if (comparison_result == 0) {
      comparison_result = len - v->len;
    }
    if (comparison_result < 0) {
      end = mid;
    } else if (comparison_result > 0) {
      start = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

int mjs_is_string(mjs_val_t v) {
  uint64_t t = v & MJS_TAG_MASK;
  return t == MJS_TAG_STRING_I || t == MJS_TAG_STRING_F ||
         t == MJS_TAG_STRING_O || t == MJS_TAG_STRING_5 ||
         t == MJS_TAG_STRING_D;
}

mjs_val_t mjs_mk_string(struct mjs *mjs, const char *p, size_t len, int copy) {
  struct mbuf *m = copy ? &mjs->owned_strings : &mjs->foreign_strings;
  mjs_val_t offset = m->len, tag = MJS_TAG_STRING_F;
  int dict_index;

  if (len == ~((size_t) 0)) len = strlen(p);

  if (len <= 4) {
    char *s = GET_VAL_NAN_PAYLOAD(offset) + 1;
    offset = 0;
    if (p != 0) {
      memcpy(s, p, len);
    }
    s[-1] = len;
    tag = MJS_TAG_STRING_I;
  } else if (len == 5) {
    char *s = GET_VAL_NAN_PAYLOAD(offset);
    offset = 0;
    if (p != 0) {
      memcpy(s, p, len);
    }
    tag = MJS_TAG_STRING_5;
  } else if ((dict_index = v_find_string_in_dictionary(p, len)) >= 0) {
    offset = 0;
    GET_VAL_NAN_PAYLOAD(offset)[0] = dict_index;
    tag = MJS_TAG_STRING_D;
  } else if (copy) {
    if (gc_strings_is_gc_needed(mjs)) {
      mjs->need_gc = 1;
    }

    /*
     * Before embedding new string, check if the reallocation is needed.  If
     * so, perform the reallocation by calling `mbuf_resize` manually, since we
     * need to preallocate some extra space (`_MJS_STRING_BUF_RESERVE`)
     */
    if ((m->len + len) > m->size) {
      mbuf_resize(m, m->len + len + _MJS_STRING_BUF_RESERVE);
    }
    embed_string(m, m->len, p, len, EMBSTR_ZERO_TERM);
    tag = MJS_TAG_STRING_O;
  } else {
    /* foreign string */
    if (sizeof(void *) <= 4 && len <= UINT16_MAX) {
      /* small foreign strings can fit length and ptr in the mjs_val_t */
      offset = (uint64_t) len << 32 | (uint64_t)(uintptr_t) p;
    } else {
      /* bigger strings need indirection that uses ram */
      size_t pos = m->len;
      int llen = calc_llen(len);

      /* allocate space for len and ptr */
      mbuf_insert(m, pos, NULL, llen + sizeof(p));

      encode_varint(len, (uint8_t *) (m->buf + pos));
      memcpy(m->buf + pos + llen, &p, sizeof(p));
    }
    tag = MJS_TAG_STRING_F;
  }

  /* NOTE(lsm): don't use pointer_to_value, 32-bit ptrs will truncate */
  return (offset & ~MJS_TAG_MASK) | tag;
}

/* Get a pointer to string and string length. */
const char *mjs_get_string(struct mjs *mjs, mjs_val_t *v, size_t *sizep) {
  uint64_t tag = v[0] & MJS_TAG_MASK;
  const char *p = NULL;
  int llen;
  size_t size = 0;

  if (!mjs_is_string(*v)) {
    goto clean;
  }

  if (tag == MJS_TAG_STRING_I) {
    p = GET_VAL_NAN_PAYLOAD(*v) + 1;
    size = p[-1];
  } else if (tag == MJS_TAG_STRING_5) {
    p = GET_VAL_NAN_PAYLOAD(*v);
    size = 5;
  } else if (tag == MJS_TAG_STRING_D) {
    int index = ((unsigned char *) GET_VAL_NAN_PAYLOAD(*v))[0];
    size = v_dictionary_strings[index].len;
    p = v_dictionary_strings[index].p;
  } else if (tag == MJS_TAG_STRING_O) {
    size_t offset = (size_t) gc_string_mjs_val_to_offset(*v);
    char *s = mjs->owned_strings.buf + offset;
    size = decode_varint((uint8_t *) s, &llen);
    p = s + llen;
  } else if (tag == MJS_TAG_STRING_F) {
    /*
     * short foreign strings on <=32-bit machines can be encoded in a compact
     * form:
     *
     *     7         6        5        4        3        2        1        0
     *  11111111|1111tttt|llllllll|llllllll|ssssssss|ssssssss|ssssssss|ssssssss
     *
     * Strings longer than 2^26 will be indireceted through the foreign_strings
     * mbuf.
     *
     * We don't use a different tag to represent those two cases. Instead, all
     * foreign strings represented with the help of the foreign_strings mbuf
     * will have the upper 16-bits of the payload set to zero. This allows us to
     * represent up to 477 million foreign strings longer than 64k.
     */
    uint16_t len = (*v >> 32) & 0xFFFF;
    if (sizeof(void *) <= 4 && len != 0) {
      size = (size_t) len;
      p = (const char *) (uintptr_t) *v;
    } else {
      size_t offset = (size_t) gc_string_mjs_val_to_offset(*v);
      char *s = mjs->foreign_strings.buf + offset;

      size = decode_varint((uint8_t *) s, &llen);
      memcpy(&p, s + llen, sizeof(p));
    }
  } else {
    assert(0);
  }

clean:
  if (sizep != NULL) {
    *sizep = size;
  }
  return p;
}

const char *mjs_get_cstring(struct mjs *mjs, mjs_val_t *value) {
  size_t size;
  const char *s = mjs_get_string(mjs, value, &size);
  if (s == NULL) return NULL;
  if (s[size] != 0 || strlen(s) != size) {
    return NULL;
  }
  return s;
}

int mjs_strcmp(struct mjs *mjs, mjs_val_t *a, const char *b, size_t len) {
  size_t n;
  if (len == (size_t) ~0) len = strlen(b);
  const char *s = mjs_get_string(mjs, a, &n);
  if (n != len) {
    return n - len;
  }
  return strncmp(s, b, len);
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/tok.c"
#endif
#include <stdlib.h>
#include <string.h>

/* Amalgamated: #include "mjs/tok.h" */

void pinit(const char *file_name, const char *buf, struct pstate *p) {
  memset(p, 0, sizeof(*p));
  p->line_no = 1;
  p->file_name = file_name;
  p->buf = p->pos = buf;
}

// We're not relying on the target libc ctype, as it may incorrectly
// handle negative arguments, e.g. isspace(-1).
static int is_space(int c) {
  return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}

MJS_PRIVATE int is_digit(int c) {
  return c >= '0' && c <= '9';
}

static int is_alpha(int c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

MJS_PRIVATE int is_ident(int c) {
  return c == '_' || c == '$' || is_alpha(c);
}

// Try to parse a token that can take one or two chars.
static int longtok(struct pstate *p, const char *first_chars,
                   const char *second_chars) {
  if (strchr(first_chars, p->pos[0]) == NULL) return TOK_EOF;
  if (strchr(second_chars, p->pos[1]) != NULL) {
    p->tok_len++;
    p->pos++;
    return p->pos[-1] << 8 | p->pos[0];
  }
  return p->pos[0];
}

static int getnum(struct pstate *p) {
  p->double_val = strtod(p->pos, (char **) &p->pos);
  p->tok_len = p->pos - p->tok_ptr;
  p->pos--;
  return TOK_NUM;
}

static int is_reserved_word_token(const char *s, int len) {
  const char *reserved[] = {
      "break",     "case",   "catch", "continue",   "debugger", "default",
      "delete",    "do",     "else",  "false",      "finally",  "for",
      "function",  "if",     "in",    "instanceof", "new",      "null",
      "return",    "switch", "this",  "throw",      "true",     "try",
      "typeof",    "var",    "void",  "while",      "with",     "let",
      "undefined", NULL};
  int i;
  if (!is_alpha(s[0])) return 0;
  for (i = 0; reserved[i] != NULL; i++) {
    if (len == (int) strlen(reserved[i]) && strncmp(s, reserved[i], len) == 0)
      return i + 1;
  }
  return 0;
}

static int getident(struct pstate *p) {
  while (is_ident(p->pos[0]) || is_digit(p->pos[0])) p->pos++;
  p->tok_len = p->pos - p->tok_ptr;
  p->pos--;
  return TOK_IDENT;
}

static int getstr(struct pstate *p) {
  int quote = *p->pos++;
  while (p->pos[0] != '\0' && p->pos[0] != quote) {
    if (p->pos[0] == '\\' && p->pos[1] != '\0' &&
        (p->pos[1] == quote || strchr("bfnrtv\\", p->pos[1]) != NULL)) {
      p->pos += 2;
    } else {
      p->pos++;
    }
  }
  p->tok_len = p->pos - p->tok_ptr;
  return TOK_STR;
}

static void skip_spaces_and_comments(struct pstate *p) {
  const char *pos;
  do {
    pos = p->pos;
    while (is_space(p->pos[0])) {
      if (p->pos[0] == '\n') p->line_no++;
      p->pos++;
    }
    if (p->pos[0] == '/' && p->pos[1] == '/') {
      while (p->pos[0] != '\0' && p->pos[0] != '\n') p->pos++;
      if (p->pos[0] == '\0') p->pos++;
      p->line_no++;
    }
    if (p->pos[0] == '/' && p->pos[1] == '*') {
      p->pos += 2;
      while (p->pos[0] != '\0') {
        if (p->pos[0] == '\n') p->line_no++;
        if (p->pos[0] == '*' && p->pos[1] == '/') {
          p->pos += 2;
          break;
        }
        p->pos++;
      }
    }
  } while (pos < p->pos);
}

int pnext(struct pstate *p) {
  int tmp, tok = TOK_EOF;

  skip_spaces_and_comments(p);
  p->tok_ptr = p->pos;
  p->tok_len = 1;

  if (is_digit(p->pos[0])) {
    tok = getnum(p);
  } else if (p->pos[0] == '\'' || p->pos[0] == '"') {
    tok = getstr(p);
  } else if (is_ident(p->pos[0])) {
    tok = getident(p);
    /*
     * NOTE: getident() has side effects on `p`, and `is_reserved_word_token()`
     * relies on them. Since in C the order of evaluation of the operands is
     * undefined, `is_reserved_word_token()` should be called in a separate
     * statement.
     */
    tok += is_reserved_word_token(p->tok_ptr, p->tok_len);
  } else if (strchr(",.:;{}[]()", p->pos[0]) != NULL) {
    tok = p->pos[0];
  } else if ((tmp = longtok(p, "&", "&=")) != TOK_EOF ||
             (tmp = longtok(p, "|", "|=")) != TOK_EOF ||
             (tmp = longtok(p, "<", "<=")) != TOK_EOF ||
             (tmp = longtok(p, ">", ">=")) != TOK_EOF ||
             (tmp = longtok(p, "-", "-=")) != TOK_EOF ||
             (tmp = longtok(p, "+", "+=")) != TOK_EOF) {
    tok = tmp;
  } else if ((tmp = longtok(p, "^~+-%/*<>=!|&", "=")) != TOK_EOF) {
    tok = tmp;
  }
  if (p->pos[0] != '\0') p->pos++;

  return tok;
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/util.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "mjs/object.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/util.h" */
/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/primitive.h" */

void mjs_print(struct mjs *mjs, mjs_val_t v) {
  mjs_fprint(stdout, mjs, v);
}

void mjs_fprint(FILE *f, struct mjs *mjs, mjs_val_t v) {
  if (mjs_is_number(v)) {
    fprintf(f, "%lf", mjs_get_double(mjs, v));
  } else if (mjs_is_string(v)) {
    fprintf(f, "%s", mjs_get_cstring(mjs, &v));
  } else if (mjs_is_object(v)) {
    fprintf(f, "[object Object]");
  }
}

void mjs_println(struct mjs *mjs, mjs_val_t v) {
  mjs_fprintln(stdout, mjs, v);
}

void mjs_fprintln(FILE *f, struct mjs *mjs, mjs_val_t v) {
  mjs_fprint(f, mjs, v);
  fprintf(f, ENDL);
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/varint.c"
#endif
/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "mjs//internal.h" */
/* Amalgamated: #include "mjs//varint.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Strings in AST are encoded as tuples (length, string).
 * Length is variable-length: if high bit is set in a byte, next byte is used.
 * Maximum string length with such encoding is 2 ^ (7 * 4) == 256 MiB,
 * assuming that sizeof(size_t) == 4.
 * Small string length (less then 128 bytes) is encoded in 1 byte.
 */
MJS_PRIVATE size_t decode_varint(const unsigned char *p, int *llen) {
  size_t i = 0, string_len = 0;

  do {
    /*
     * Each byte of varint contains 7 bits, in little endian order.
     * MSB is a continuation bit: it tells whether next byte is used.
     */
    string_len |= (p[i] & 0x7f) << (7 * i);
    /*
     * First we increment i, then check whether it is within boundary and
     * whether decoded byte had continuation bit set.
     */
  } while (++i < sizeof(size_t) && (p[i - 1] & 0x80));
  *llen = i;

  return string_len;
}

/* Return number of bytes to store length */
MJS_PRIVATE int calc_llen(size_t len) {
  int n = 0;

  do {
    n++;
  } while (len >>= 7);

  return n;
}

MJS_PRIVATE int encode_varint(size_t len, unsigned char *p) {
  int i, llen = calc_llen(len);

  for (i = 0; i < llen; i++) {
    p[i] = (len & 0x7f) | (i < llen - 1 ? 0x80 : 0);
    len >>= 7;
  }

  return llen;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* MG_EXPORT_INTERNAL_HEADERS */
