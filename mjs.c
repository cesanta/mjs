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
#define CS_P_STM32 16
/* Next id: 17 */

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
#elif defined(STM32)
#define CS_PLATFORM CS_P_STM32
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
/* Amalgamated: #include "common/platforms/platform_stm32.h" */

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
#include <dirent.h>
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
#line 1 "common/platforms/platform_stm32.h"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_COMMON_PLATFORMS_PLATFORM_STM32_H_
#define CS_COMMON_PLATFORMS_PLATFORM_STM32_H_
#if CS_PLATFORM == CS_P_STM32

#include <sys/types.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <memory.h>

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define SIZE_T_FMT "u"

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#endif /* CS_PLATFORM == CS_P_STM32 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_STM32_H_ */
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
/* should be called while `bf_run()` runs: forces it to quit */
void bf_die(struct bf_vm *vm);

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

MJS_PRIVATE int mjs_is_ident(int c);
MJS_PRIVATE int mjs_is_digit(int c);

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
bf_word_ptr_t mjs_emit_assign(struct mjs_parse_ctx *ctx, const char *name,
                              bf_word_ptr_t val, bf_opcode_t op);
bf_word_ptr_t mjs_emit_objprop(struct mjs_parse_ctx *ctx, bf_word_ptr_t obj,
                               bf_word_ptr_t prop, int for_op);
bf_word_ptr_t mjs_emit_objprop_assign(struct mjs_parse_ctx *ctx,
                                      bf_word_ptr_t prop, bf_word_ptr_t val,
                                      bf_opcode_t op);
bf_word_ptr_t mjs_emit_postop(struct mjs_parse_ctx *ctx, const char *name,
                              bf_opcode_t op);
bf_word_ptr_t mjs_emit_postop_prop(struct mjs_parse_ctx *ctx, bf_word_ptr_t obj,
                                   const char *name, bf_opcode_t op);
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
#define MJS_WORD_PTR_scope_idx_AT (16)
#define MJS_WORD_PTR_scope_idx_SET (16)
#define MJS_WORD_PTR_scope_min_AT (16)
#define MJS_WORD_PTR_scope_min_SET (16)
#define MJS_WORD_PTR_this_val_AT (16)
#define MJS_WORD_PTR_this_val_SET (16)
#define MJS_WORD_PTR_frame_AT (16)
#define MJS_WORD_PTR_frame_SET (16)
#define MJS_WORD_PTR_GT_scopes (16)
#define MJS_WORD_PTR_scopes_GT (16)
#define MJS_WORD_PTR_scope_AT (16)
#define MJS_WORD_PTR_mkobj (16)
#define MJS_WORD_PTR_addprop (16)
#define MJS_WORD_PTR_setprop (24)
#define MJS_WORD_PTR_getprop (24)
#define MJS_WORD_PTR_getvar (24)
#define MJS_WORD_PTR_setvar (24)
#define MJS_WORD_PTR_createvar (24)
#define MJS_WORD_PTR_mkarr (24)
#define MJS_WORD_PTR_arrpush (24)
#define MJS_WORD_PTR_blockenter (24)
#define MJS_WORD_PTR_blockexit (27)
#define MJS_WORD_PTR_jscall (30)
#define MJS_WORD_PTR_jscall_exit (30)
#define MJS_WORD_PTR_jscall_wrap (37)
#define MJS_WORD_PTR_jsenter (39)
#define MJS_WORD_PTR_jsexit (55)
#define MJS_WORD_PTR_anon_0 (64)
#define MJS_WORD_PTR_anon_1 (66)
#define MJS_WORD_PTR_setarg (68)
#define MJS_WORD_PTR_ffi (88)
#define MJS_WORD_PTR_undefined (90)
#define MJS_WORD_PTR_null (90)
#define MJS_WORD_PTR_true (90)
#define MJS_WORD_PTR_false (90)
#define MJS_WORD_PTR_this_for_call (90)
#define MJS_WORD_PTR_2dup (90)
#define MJS_WORD_PTR_dec (93)
#define MJS_WORD_PTR_GTEQ (98)
#define MJS_WORD_PTR_LTEQ (101)
#define MJS_WORD_PTR_SETEQ (104)
#define MJS_WORD_PTR_js_EQ (107)
#define MJS_WORD_PTR_js_LT (107)
#define MJS_WORD_PTR_js_GT (107)
#define MJS_WORD_PTR_jsinvert (107)
#define MJS_WORD_PTR_js_GTEQ (107)
#define MJS_WORD_PTR_js_LTEQ (110)
#define MJS_WORD_PTR_js_SETEQ (113)
#define MJS_WORD_PTR_js_logical_and (116)
#define MJS_WORD_PTR_js_logical_or (116)
#define MJS_WORD_PTR_anon_2 (116)
#define MJS_WORD_PTR_ifstmt (118)
#define MJS_WORD_PTR_anon_3 (123)
#define MJS_WORD_PTR_anon_4 (140)
#define MJS_WORD_PTR_repeat (147)
#define MJS_WORD_PTR_anon_5 (160)
#define MJS_WORD_PTR_anon_6 (166)
#define MJS_WORD_PTR_anon_7 (171)
#define MJS_WORD_PTR_while (181)
#define MJS_WORD_PTR_anon_8 (187)
#define MJS_WORD_PTR_anon_9 (192)
#define MJS_WORD_PTR_jsprint (204)
#define MJS_WORD_PTR_zero (211)
#define MJS_WORD_PTR_one (215)
#define MJS_WORD_PTR_nop (219)
#define MJS_WORD_PTR_inc (222)
#define MJS_WORD_PTR_swapinc (227)
#define MJS_WORD_PTR_div (230)
#define MJS_WORD_PTR_rem (230)
#define MJS_WORD_PTR_lshift (230)
#define MJS_WORD_PTR_rshift (230)
#define MJS_WORD_PTR_urshift (230)
#define MJS_WORD_PTR_and (230)
#define MJS_WORD_PTR_or (230)
#define MJS_WORD_PTR_xor (230)
#define MJS_WORD_PTR_not (230)
#define MJS_WORD_PTR_neg (230)
#define MJS_WORD_PTR_pos (230)
#define MJS_WORD_PTR_load (230)
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
#define MJS_OP_scope_idx_AT ((bf_opcode_t) 31)
#define MJS_OP_scope_idx_SET ((bf_opcode_t) 32)
#define MJS_OP_scope_min_AT ((bf_opcode_t) 33)
#define MJS_OP_scope_min_SET ((bf_opcode_t) 34)
#define MJS_OP_this_val_AT ((bf_opcode_t) 35)
#define MJS_OP_this_val_SET ((bf_opcode_t) 36)
#define MJS_OP_frame_AT ((bf_opcode_t) 37)
#define MJS_OP_frame_SET ((bf_opcode_t) 38)
#define MJS_OP_GT_scopes ((bf_opcode_t) 39)
#define MJS_OP_scopes_GT ((bf_opcode_t) 40)
#define MJS_OP_scope_AT ((bf_opcode_t) 41)
#define MJS_OP_mkobj ((bf_opcode_t) 42)
#define MJS_OP_addprop ((bf_opcode_t) 43)
#define MJS_OP_setprop ((bf_opcode_t) 44)
#define MJS_OP_getprop ((bf_opcode_t) 45)
#define MJS_OP_getvar ((bf_opcode_t) 46)
#define MJS_OP_setvar ((bf_opcode_t) 47)
#define MJS_OP_createvar ((bf_opcode_t) 48)
#define MJS_OP_mkarr ((bf_opcode_t) 49)
#define MJS_OP_arrpush ((bf_opcode_t) 50)
#define MJS_OP_blockenter ((bf_opcode_t) 51)
#define MJS_OP_blockexit ((bf_opcode_t) 52)
#define MJS_OP_jscall ((bf_opcode_t) 53)
#define MJS_OP_jscall_exit ((bf_opcode_t) 54)
#define MJS_OP_jscall_wrap ((bf_opcode_t) 55)
#define MJS_OP_jsenter ((bf_opcode_t) 56)
#define MJS_OP_jsexit ((bf_opcode_t) 57)
#define MJS_OP_setarg ((bf_opcode_t) 58)
#define MJS_OP_undefined ((bf_opcode_t) 59)
#define MJS_OP_null ((bf_opcode_t) 60)
#define MJS_OP_true ((bf_opcode_t) 61)
#define MJS_OP_false ((bf_opcode_t) 62)
#define MJS_OP_this_for_call ((bf_opcode_t) 63)
#define MJS_OP_2dup ((bf_opcode_t) 64)
#define MJS_OP_GTEQ ((bf_opcode_t) 65)
#define MJS_OP_LTEQ ((bf_opcode_t) 66)
#define MJS_OP_SETEQ ((bf_opcode_t) 67)
#define MJS_OP_js_EQ ((bf_opcode_t) 68)
#define MJS_OP_js_LT ((bf_opcode_t) 69)
#define MJS_OP_js_GT ((bf_opcode_t) 70)
#define MJS_OP_jsinvert ((bf_opcode_t) 71)
#define MJS_OP_js_GTEQ ((bf_opcode_t) 72)
#define MJS_OP_js_LTEQ ((bf_opcode_t) 73)
#define MJS_OP_js_SETEQ ((bf_opcode_t) 74)
#define MJS_OP_js_logical_and ((bf_opcode_t) 75)
#define MJS_OP_js_logical_or ((bf_opcode_t) 76)
#define MJS_OP_ifstmt ((bf_opcode_t) 77)
#define MJS_OP_repeat ((bf_opcode_t) 78)
#define MJS_OP_while ((bf_opcode_t) 79)
#define MJS_OP_jsprint ((bf_opcode_t) 80)
#define MJS_OP_zero ((bf_opcode_t) 81)
#define MJS_OP_one ((bf_opcode_t) 82)
#define MJS_OP_nop ((bf_opcode_t) 83)
#define MJS_OP_inc ((bf_opcode_t) 84)
#define MJS_OP_swapinc ((bf_opcode_t) 85)
#define MJS_OP_div ((bf_opcode_t) 86)
#define MJS_OP_rem ((bf_opcode_t) 87)
#define MJS_OP_lshift ((bf_opcode_t) 88)
#define MJS_OP_rshift ((bf_opcode_t) 89)
#define MJS_OP_urshift ((bf_opcode_t) 90)
#define MJS_OP_and ((bf_opcode_t) 91)
#define MJS_OP_or ((bf_opcode_t) 92)
#define MJS_OP_xor ((bf_opcode_t) 93)
#define MJS_OP_not ((bf_opcode_t) 94)
#define MJS_OP_neg ((bf_opcode_t) 95)
#define MJS_OP_pos ((bf_opcode_t) 96)
#define MJS_OP_load ((bf_opcode_t) 97)

#endif /* MJS_GEN_OPCODES_H_ */
#ifdef MG_MODULE_LINES
#line 1 "frozen/frozen.h"
#endif
/*
 * Copyright (c) 2004-2013 Sergey Lyubka <valenok@gmail.com>
 * Copyright (c) 2013 Cesanta Software Limited
 * All rights reserved
 *
 * This library is dual-licensed: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. For the terms of this
 * license, see <http: *www.gnu.org/licenses/>.
 *
 * You are free to use this library under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * Alternatively, you can license this library under a commercial
 * license, as set out in <http://cesanta.com/products.html>.
 */

#ifndef CS_FROZEN_FROZEN_H_
#define CS_FROZEN_FROZEN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

/* JSON token type */
enum json_token_type {
  JSON_TYPE_INVALID = 0, /* memsetting to 0 should create INVALID value */
  JSON_TYPE_STRING,
  JSON_TYPE_NUMBER,
  JSON_TYPE_TRUE,
  JSON_TYPE_FALSE,
  JSON_TYPE_NULL,
  JSON_TYPE_OBJECT_START,
  JSON_TYPE_OBJECT_END,
  JSON_TYPE_ARRAY_START,
  JSON_TYPE_ARRAY_END,

  JSON_TYPES_CNT
};

/*
 * Structure containing token type and value. Used in `json_walk()` and
 * `json_scanf()` with the format specifier `%T`.
 */
struct json_token {
  const char *ptr;           /* Points to the beginning of the value */
  int len;                   /* Value length */
  enum json_token_type type; /* Type of the token, possible values are above */
};

#define JSON_INVALID_TOKEN \
  { 0, 0, JSON_TYPE_INVALID }

/* Error codes */
#define JSON_STRING_INVALID -1
#define JSON_STRING_INCOMPLETE -2

/*
 * Callback-based SAX-like API.
 *
 * Property name and length is given only if it's available: i.e. if current
 * event is an object's property. In other cases, `name` is `NULL`. For
 * example, name is never given:
 *   - For the first value in the JSON string;
 *   - For events JSON_TYPE_OBJECT_END and JSON_TYPE_ARRAY_END
 *
 * E.g. for the input `{ "foo": 123, "bar": [ 1, 2, { "baz": true } ] }`,
 * the sequence of callback invocations will be as follows:
 *
 * - type: JSON_TYPE_OBJECT_START, name: NULL, path: "", value: NULL
 * - type: JSON_TYPE_NUMBER, name: "foo", path: ".foo", value: "123"
 * - type: JSON_TYPE_ARRAY_START,  name: "bar", path: ".bar", value: NULL
 * - type: JSON_TYPE_NUMBER, name: "0", path: ".bar[0]", value: "1"
 * - type: JSON_TYPE_NUMBER, name: "1", path: ".bar[1]", value: "2"
 * - type: JSON_TYPE_OBJECT_START, name: "2", path: ".bar[2]", value: NULL
 * - type: JSON_TYPE_TRUE, name: "baz", path: ".bar[2].baz", value: "true"
 * - type: JSON_TYPE_OBJECT_END, name: NULL, path: ".bar[2]", value: "{ \"baz\":
 *true }"
 * - type: JSON_TYPE_ARRAY_END, name: NULL, path: ".bar", value: "[ 1, 2, {
 *\"baz\": true } ]"
 * - type: JSON_TYPE_OBJECT_END, name: NULL, path: "", value: "{ \"foo\": 123,
 *\"bar\": [ 1, 2, { \"baz\": true } ] }"
 */
typedef void (*json_walk_callback_t)(void *callback_data, const char *name,
                                     size_t name_len, const char *path,
                                     const struct json_token *token);

/*
 * Parse `json_string`, invoking `callback` in a way similar to SAX parsers;
 * see `json_walk_callback_t`.
 */
int json_walk(const char *json_string, int json_string_length,
              json_walk_callback_t callback, void *callback_data);

/*
 * JSON generation API.
 * struct json_out abstracts output, allowing alternative printing plugins.
 */
struct json_out {
  int (*printer)(struct json_out *, const char *str, size_t len);
  union {
    struct {
      char *buf;
      size_t size;
      size_t len;
    } buf;
    void *data;
    FILE *fp;
  } u;
};

extern int json_printer_buf(struct json_out *, const char *, size_t);
extern int json_printer_file(struct json_out *, const char *, size_t);

#define JSON_OUT_BUF(buf, len) \
  {                            \
    json_printer_buf, {        \
      { buf, len, 0 }          \
    }                          \
  }
#define JSON_OUT_FILE(fp)   \
  {                         \
    json_printer_file, {    \
      { (void *) fp, 0, 0 } \
    }                       \
  }

typedef int (*json_printf_callback_t)(struct json_out *, va_list *ap);

/*
 * Generate formatted output into a given sting buffer.
 * This is a superset of printf() function, with extra format specifiers:
 *  - `%B` print json boolean, `true` or `false`. Accepts an `int`.
 *  - `%Q` print quoted escaped string or `null`. Accepts a `const char *`.
 *  - `%.*Q` same as `%Q`, but with length. Accepts `int`, `const char *`
 *  - `%V` print quoted base64-encoded string. Accepts a `const char *`, `int`.
 *  - `%H` print quoted hex-encoded string. Accepts a `int`, `const char *`.
 *  - `%M` invokes a json_printf_callback_t function. That callback function
 *  can consume more parameters.
 *
 * Return number of bytes printed. If the return value is bigger then the
 * supplied buffer, that is an indicator of overflow. In the overflow case,
 * overflown bytes are not printed.
 */
int json_printf(struct json_out *, const char *fmt, ...);
int json_vprintf(struct json_out *, const char *fmt, va_list ap);

/*
 * Helper %M callback that prints contiguous C arrays.
 * Consumes void *array_ptr, size_t array_size, size_t elem_size, char *fmt
 * Return number of bytes printed.
 */
int json_printf_array(struct json_out *, va_list *ap);

/*
 * Scan JSON string `str`, performing scanf-like conversions according to `fmt`.
 * This is a `scanf()` - like function, with following differences:
 *
 * 1. Object keys in the format string may be not quoted, e.g. "{key: %d}"
 * 2. Order of keys in an object is irrelevant.
 * 3. Several extra format specifiers are supported:
 *    - %B: consumes `int *`, expects boolean `true` or `false`.
 *    - %Q: consumes `char **`, expects quoted, JSON-encoded string. Scanned
 *       string is malloc-ed, caller must free() the string.
 *    - %V: consumes `char **`, `int *`. Expects base64-encoded string.
 *       Result string is base64-decoded, malloced and NUL-terminated.
 *       The length of result string is stored in `int *` placeholder.
 *       Caller must free() the result.
 *    - %H: consumes `int *`, `char **`.
 *       Expects a hex-encoded string, e.g. "fa014f".
 *       Result string is hex-decoded, malloced and NUL-terminated.
 *       The length of the result string is stored in `int *` placeholder.
 *       Caller must free() the result.
 *    - %M: consumes custom scanning function pointer and
 *       `void *user_data` parameter - see json_scanner_t definition.
 *    - %T: consumes `struct json_token *`, fills it out with matched token.
 *
 * Return number of elements successfully scanned & converted.
 * Negative number means scan error.
 */
int json_scanf(const char *str, int str_len, const char *fmt, ...);
int json_vscanf(const char *str, int str_len, const char *fmt, va_list ap);

/* json_scanf's %M handler  */
typedef void (*json_scanner_t)(const char *str, int len, void *user_data);

/*
 * Helper function to scan array item with given path and index.
 * Fills `token` with the matched JSON token.
 * Return 0 if no array element found, otherwise non-0.
 */
int json_scanf_array_elem(const char *s, int len, const char *path, int index,
                          struct json_token *token);

/*
 * Unescape JSON-encoded string src,slen into dst, dlen.
 * src and dst may overlap.
 * If destination buffer is too small (or zero-length), result string is not
 * written but the length is counted nevertheless (similar to snprintf).
 * Return the length of unescaped string in bytes.
 */
int json_unescape(const char *src, int slen, char *dst, int dlen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_FROZEN_FROZEN_H_ */
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

/*
 * Maximum number of word-sized args to ffi-ed function. If at least one
 * of the args is double, only 2 args are allowed.
 */
#define FFI_MAX_ARGS_CNT 6

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
  MJS_REFERENCE_ERROR,
  MJS_TYPE_ERROR,
  MJS_OUT_OF_MEMORY,
  MJS_INTERNAL_ERROR,
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
 * If there is no error message already set, then it's equal to
 * `mjs_set_errorf()`.
 *
 * Otherwise, an old message gets prepended with the new one, followed by a
 * colon. (the previously set error code is kept)
 */
mjs_err_t mjs_prepend_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt, ...);

/*
 * return a string representation of an error.
 * the error string might be overwritten by calls to `mjs_set_errorf`.
 */
const char *mjs_strerror(struct mjs *mjs, mjs_err_t err);

#endif /* MJS_CORE_PUBLIC_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/array_public.h"
#endif
/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

/*
 * === Arrays
 */

#ifndef MJS_ARRAY_PUBLIC_H_
#define MJS_ARRAY_PUBLIC_H_

/* Amalgamated: #include "mjs/core_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* Make an empty array object */
mjs_val_t mjs_mk_array(struct mjs *mjs);

/* Returns length on an array. If `arr` is not an array, 0 is returned. */
unsigned long mjs_array_length(struct mjs *mjs, mjs_val_t arr);

/* Insert value `v` in array `arr` at the end of the array. */
mjs_err_t mjs_array_push(struct mjs *mjs, mjs_val_t arr, mjs_val_t v);

/*
 * Return array member at index `index`. If `index` is out of bounds, undefined
 * is returned.
 */
mjs_val_t mjs_array_get(struct mjs *, mjs_val_t arr, unsigned long index);

/* Insert value `v` into `arr` at index `index`. */
mjs_err_t mjs_array_set(struct mjs *mjs, mjs_val_t arr, unsigned long index,
                        mjs_val_t v);

/* Returns true if the given value is an array */
int mjs_is_array(mjs_val_t v);

#if 0
/* Delete value in array `arr` at index `index`, if it exists. */
void mjs_array_del(struct mjs *mjs, mjs_val_t arr, unsigned long index);
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_ARRAY_PUBLIC_H_ */
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

#define MJS_CB_ARGS_MAX_CNT 4
#define MJS_CB_SIGNATURE_MAX_SIZE (MJS_CB_ARGS_MAX_CNT + 1 /* return type */)

enum cval_type {
  CVAL_TYPE_NONE,
  CVAL_TYPE_USERDATA,
  CVAL_TYPE_INT,
  CVAL_TYPE_DOUBLE,
  CVAL_TYPE_CHAR_PTR,
  CVAL_TYPE_VOID_PTR,
  CVAL_TYPE_INVALID,
};
typedef uint8_t cval_type_t;

struct ffi_sig_stat {
  int8_t is_valid;
  int8_t userdata_idx;
  int8_t args_cnt;
  int8_t args_double_cnt;
};

struct ffi_sig {
  /*
   * The first item is the return value type (for `void`, `CVAL_TYPE_NONE` is
   * used); the rest are arguments. If some argument is `CVAL_TYPE_NONE`, it
   * means that there are no more arguments.
   */
  cval_type_t val_types[MJS_CB_SIGNATURE_MAX_SIZE];
  struct ffi_sig_stat stat;
};
typedef struct ffi_sig ffi_sig_t;

MJS_PRIVATE void mjs_ffi_sig_init(ffi_sig_t *sig);
MJS_PRIVATE int mjs_ffi_sig_set_val_type(
    ffi_sig_t *sig, int idx, cval_type_t type
    );
MJS_PRIVATE struct ffi_sig_stat mjs_ffi_sig_stat_get(struct mjs *mjs, const ffi_sig_t *sig);
MJS_PRIVATE int mjs_ffi_is_regular_word(cval_type_t type);
MJS_PRIVATE int mjs_ffi_is_regular_word_or_void(cval_type_t type);

struct ffi_cb_args {
  struct ffi_cb_args *next;
  struct mjs *mjs;
  ffi_sig_t sig;
  mjs_val_t func;
  mjs_val_t userdata;
};
typedef struct ffi_cb_args ffi_cb_args_t;

MJS_PRIVATE int mjs_ffi_call(struct mjs *mjs, mjs_val_t sig);
MJS_PRIVATE void mjs_ffi_cb_free(struct bf_vm *vm);
MJS_PRIVATE void mjs_ffi_args_free_list(struct mjs *mjs);

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
#define MJS_TAG_STRING_D MAKE_TAG(1, 0x5)  /* Dictionary string  */
#define MJS_TAG_OBJECT_ARRAY MAKE_TAG(1, 0x4)
#define MJS_TAG_NOVALUE MAKE_TAG(1, 0x1)   /* Sentinel for no value */
#define MJS_TAG_MASK MAKE_TAG(1, 0xF)

#define _MJS_NULL MJS_TAG_FOREIGN
#define _MJS_UNDEFINED MJS_TAG_UNDEFINED

/*
 * Distance after the last getprop invocation; needed for "method invocation
 * pattern" implementation.
 *
 * We use enum here in order to leverage compiler warning about the too narrow
 * field.
 */
enum getprop_distance {
  /*
   * Number of words which are executed during "method invocation pattern",
   * between getting a property and calling that property.
   *
   * Currently, there are 2 words:
   *   - exit (from the getprop word)
   *   - this_for_call
   */
  GETPROP_DISTANCE_CALL = 2,

  /*
   * After reaching this value, `words_since_getprop` is not incremented more
   */
  GETPROP_DISTANCE_OVER,
};

struct mjs_vals {
  /*
   * Min index of the scope (in `mjs->scopes`) which current function can use.
   * Independently of this value, all functions can use scope 0, which is the
   * Global Object.
   *
   * TODO(dfrank): store as int, not mjs_val_t
   */
  mjs_val_t min_scope;

  /*
   * Position in the return stack which should be restored when the current
   * function returns. At top level, it's equal to -1.
   *
   * TODO(dfrank): rename appropriately
   * TODO(dfrank): store as int, not mjs_val_t
   */
  mjs_val_t call_frame;

  /*
   * Current `this` value.
   */
  mjs_val_t this_val;

  /*
   * The object against which the last `getprop` was invoked. Needed for
   * "method invocation pattern".
   */
  mjs_val_t last_getprop_obj;
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

  /*
   * Sequence of `mjs_val_t`s which are scope objects.
   *
   * There is always at least 1 element, and it is the Global Object.
   */
  struct mbuf scopes;

  mjs_ffi_resolver_t *dlsym;

  char *error_msg;
  mjs_err_t error_msg_err;

  /* Linked list of the FFI callback args */
  ffi_cb_args_t *ffi_cb_args;

  /* Needed for detecting cycles in JSON.stringify() */
  struct mbuf json_visited_stack;

  /* Set to true to trigger GC when safe */
  unsigned int need_gc : 1;
  /* while true, GC is inhibited */
  unsigned int inhibit_gc : 1;
  /*
   * number of words evaluated after latest `getprop` invocation, needed for
   * "method invocation pattern"
   */
  enum getprop_distance words_since_getprop : 2;
};

enum mjs_type {
  /* Primitive types */
  MJS_TYPE_UNDEFINED,
  MJS_TYPE_NULL,
  MJS_TYPE_BOOLEAN,
  MJS_TYPE_NUMBER,
  MJS_TYPE_STRING,
  MJS_TYPE_FOREIGN,

  /* Different classes of Object type */
  MJS_TYPE_OBJECT_GENERIC,
  MJS_TYPE_OBJECT_ARRAY,
  /*
   * TODO(dfrank): if we support prototypes, need to add items for them here
   */

  MJS_TYPES_CNT
};

MJS_PRIVATE void mjs_push_scope(struct mjs *mjs, mjs_val_t scope);
MJS_PRIVATE mjs_val_t mjs_pop_scope(struct mjs *mjs);
MJS_PRIVATE mjs_val_t mjs_scope_tos(struct mjs *mjs);
MJS_PRIVATE mjs_val_t mjs_scope_get_by_idx(struct mjs *mjs, int idx);
MJS_PRIVATE void mjs_scope_set_by_idx(struct mjs *mjs, int idx, mjs_val_t v);
MJS_PRIVATE enum mjs_type mjs_get_type(struct mjs *mjs, mjs_val_t v);

#endif /* MJS_CORE_H_ */
#ifdef MG_MODULE_LINES
#line 1 "mjs/array.h"
#endif
/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_ARRAY_H_
#define MJS_ARRAY_H_

/* Amalgamated: #include "mjs/array_public.h" */

/* Amalgamated: #include "mjs/core.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

MJS_PRIVATE mjs_val_t
mjs_array_get2(struct mjs *mjs, mjs_val_t arr, unsigned long index, int *has);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_ARRAY_H_ */
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

#define MJS_STRING_LITERAL_MAX_LEN 128

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

MJS_PRIVATE unsigned long cstr_to_ulong(const char *s, size_t len, int *ok);
MJS_PRIVATE mjs_err_t str_to_ulong(struct mjs *mjs, mjs_val_t v, int *ok,
                                   unsigned long *res);

#endif /* MJS_STRING_H_ */
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
 * Returns true if the given value is an object or array.
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

mjs_val_t mjs_mk_boolean(struct mjs *mjs, int v);
int mjs_get_bool(struct mjs *mjs, mjs_val_t v);
int mjs_is_boolean(mjs_val_t v);

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
#line 1 "mjs/conversion.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_CONVERSION_H_
#define MJS_CONVERSION_H_

/*
 * Tries to convert `mjs_val_t` to a string, returns MJS_OK if successful.
 * String is returned as a pair of pointers: `char **p, size_t *sizep`.
 *
 * Caller must also provide a non-null `need_free`, and if it is non-zero,
 * then the string `*p` should be freed by the caller.
 *
 * MJS does not support `toString()` and `valueOf()`, so, passing an object
 * always results in `MJS_TYPE_ERROR`.
 */
MJS_PRIVATE mjs_err_t mjs_to_string(struct mjs *mjs, mjs_val_t *v,
                                    char **p, size_t *sizep,
                                    int *need_free);

#endif /* MJS_CONVERSION_H_ */
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
#line 1 "mjs/ops.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_OPS_H_
#define MJS_OPS_H_

/* Amalgamated: #include "mjs/internal.h" */

void mjs_op_load(struct bf_vm *vm);
void mjs_op_json_stringify(struct bf_vm *vm);
void mjs_op_json_parse(struct bf_vm *vm);

#endif /* MJS_OPS_H_ */

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

mjs_err_t mjs_call(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                   mjs_val_t this_val, int nargs, ...);
mjs_err_t mjs_apply(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                    mjs_val_t this_val, int nargs, mjs_val_t *args);

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
/* Amalgamated: #include "mjs/internal.h" */

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
#define TOK_QUESTION                        15
#define TOK_LOGICAL_AND                     16
#define TOK_LOGICAL_OR                      17
#define TOK_OR                              18
#define TOK_XOR                             19
#define TOK_AND                             20
#define TOK_EQ                              21
#define TOK_NE                              22
#define TOK_EQ_EQ                           23
#define TOK_NE_NE                           24
#define TOK_LE                              25
#define TOK_LT                              26
#define TOK_GE                              27
#define TOK_GT                              28
#define TOK_LSHIFT                          29
#define TOK_RSHIFT                          30
#define TOK_URSHIFT                         31
#define TOK_PLUS                            32
#define TOK_MINUS                           33
#define TOK_MUL                             34
#define TOK_DIV                             35
#define TOK_REM                             36
#define TOK_PLUS_PLUS                       37
#define TOK_MINUS_MINUS                     38
#define TOK_NOT                             39
#define TOK_TILDA                           40
#define TOK_DOT                             41
#define TOK_OPEN_PAREN                      42
#define TOK_OPEN_BRACKET                    43
#define TOK_SEMICOLON                       44
#define TOK_LET                             45
#define TOK_COMMA                           46
#define TOK_IDENTIFIER                      47
#define TOK_CLOSE_BRACKET                   48
#define TOK_CLOSE_PAREN                     49
#define TOK_COLON                           50
#define TOK_IF                              51
#define TOK_WHILE                           52
#define TOK_FOR                             53
#define TOK_OPEN_CURLY                      54
#define TOK_CLOSE_CURLY                     55
#define TOK_FUNCTION                        56
#define TOK_RETURN                          57
#define TOK_NULL                            58
#define TOK_UNDEFINED                       59
#define TOK_THIS                            60
#define TOK_NUMBER                          61
#define TOK_STRING_LITERAL                  62
#define TOK_TRUE                            63
#define TOK_FALSE                           64
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
#line 1 "mjs/json.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_JSON_H_
#define MJS_JSON_H_

MJS_PRIVATE mjs_err_t to_json_or_debug(struct mjs *mjs, mjs_val_t v,
    char *buf, size_t size,
    size_t *res_len, uint8_t is_debug);


MJS_PRIVATE mjs_err_t mjs_json_stringify(struct mjs *mjs, mjs_val_t v, char *buf,
    size_t size, char **res);

MJS_PRIVATE mjs_err_t mjs_json_parse(struct mjs *mjs, const char *str,
                                     size_t len, mjs_val_t *res);

#endif /* MJS_JSON_H_ */
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
#ifdef MG_MODULE_LINES
#line 1 "frozen/frozen.h"
#endif
/*
 * Copyright (c) 2004-2013 Sergey Lyubka <valenok@gmail.com>
 * Copyright (c) 2013 Cesanta Software Limited
 * All rights reserved
 *
 * This library is dual-licensed: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. For the terms of this
 * license, see <http: *www.gnu.org/licenses/>.
 *
 * You are free to use this library under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * Alternatively, you can license this library under a commercial
 * license, as set out in <http://cesanta.com/products.html>.
 */

#ifndef CS_FROZEN_FROZEN_H_
#define CS_FROZEN_FROZEN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

/* JSON token type */
enum json_token_type {
  JSON_TYPE_INVALID = 0, /* memsetting to 0 should create INVALID value */
  JSON_TYPE_STRING,
  JSON_TYPE_NUMBER,
  JSON_TYPE_TRUE,
  JSON_TYPE_FALSE,
  JSON_TYPE_NULL,
  JSON_TYPE_OBJECT_START,
  JSON_TYPE_OBJECT_END,
  JSON_TYPE_ARRAY_START,
  JSON_TYPE_ARRAY_END,

  JSON_TYPES_CNT
};

/*
 * Structure containing token type and value. Used in `json_walk()` and
 * `json_scanf()` with the format specifier `%T`.
 */
struct json_token {
  const char *ptr;           /* Points to the beginning of the value */
  int len;                   /* Value length */
  enum json_token_type type; /* Type of the token, possible values are above */
};

#define JSON_INVALID_TOKEN \
  { 0, 0, JSON_TYPE_INVALID }

/* Error codes */
#define JSON_STRING_INVALID -1
#define JSON_STRING_INCOMPLETE -2

/*
 * Callback-based SAX-like API.
 *
 * Property name and length is given only if it's available: i.e. if current
 * event is an object's property. In other cases, `name` is `NULL`. For
 * example, name is never given:
 *   - For the first value in the JSON string;
 *   - For events JSON_TYPE_OBJECT_END and JSON_TYPE_ARRAY_END
 *
 * E.g. for the input `{ "foo": 123, "bar": [ 1, 2, { "baz": true } ] }`,
 * the sequence of callback invocations will be as follows:
 *
 * - type: JSON_TYPE_OBJECT_START, name: NULL, path: "", value: NULL
 * - type: JSON_TYPE_NUMBER, name: "foo", path: ".foo", value: "123"
 * - type: JSON_TYPE_ARRAY_START,  name: "bar", path: ".bar", value: NULL
 * - type: JSON_TYPE_NUMBER, name: "0", path: ".bar[0]", value: "1"
 * - type: JSON_TYPE_NUMBER, name: "1", path: ".bar[1]", value: "2"
 * - type: JSON_TYPE_OBJECT_START, name: "2", path: ".bar[2]", value: NULL
 * - type: JSON_TYPE_TRUE, name: "baz", path: ".bar[2].baz", value: "true"
 * - type: JSON_TYPE_OBJECT_END, name: NULL, path: ".bar[2]", value: "{ \"baz\":
 *true }"
 * - type: JSON_TYPE_ARRAY_END, name: NULL, path: ".bar", value: "[ 1, 2, {
 *\"baz\": true } ]"
 * - type: JSON_TYPE_OBJECT_END, name: NULL, path: "", value: "{ \"foo\": 123,
 *\"bar\": [ 1, 2, { \"baz\": true } ] }"
 */
typedef void (*json_walk_callback_t)(void *callback_data, const char *name,
                                     size_t name_len, const char *path,
                                     const struct json_token *token);

/*
 * Parse `json_string`, invoking `callback` in a way similar to SAX parsers;
 * see `json_walk_callback_t`.
 */
int json_walk(const char *json_string, int json_string_length,
              json_walk_callback_t callback, void *callback_data);

/*
 * JSON generation API.
 * struct json_out abstracts output, allowing alternative printing plugins.
 */
struct json_out {
  int (*printer)(struct json_out *, const char *str, size_t len);
  union {
    struct {
      char *buf;
      size_t size;
      size_t len;
    } buf;
    void *data;
    FILE *fp;
  } u;
};

extern int json_printer_buf(struct json_out *, const char *, size_t);
extern int json_printer_file(struct json_out *, const char *, size_t);

#define JSON_OUT_BUF(buf, len) \
  {                            \
    json_printer_buf, {        \
      { buf, len, 0 }          \
    }                          \
  }
#define JSON_OUT_FILE(fp)   \
  {                         \
    json_printer_file, {    \
      { (void *) fp, 0, 0 } \
    }                       \
  }

typedef int (*json_printf_callback_t)(struct json_out *, va_list *ap);

/*
 * Generate formatted output into a given sting buffer.
 * This is a superset of printf() function, with extra format specifiers:
 *  - `%B` print json boolean, `true` or `false`. Accepts an `int`.
 *  - `%Q` print quoted escaped string or `null`. Accepts a `const char *`.
 *  - `%.*Q` same as `%Q`, but with length. Accepts `int`, `const char *`
 *  - `%V` print quoted base64-encoded string. Accepts a `const char *`, `int`.
 *  - `%H` print quoted hex-encoded string. Accepts a `int`, `const char *`.
 *  - `%M` invokes a json_printf_callback_t function. That callback function
 *  can consume more parameters.
 *
 * Return number of bytes printed. If the return value is bigger then the
 * supplied buffer, that is an indicator of overflow. In the overflow case,
 * overflown bytes are not printed.
 */
int json_printf(struct json_out *, const char *fmt, ...);
int json_vprintf(struct json_out *, const char *fmt, va_list ap);

/*
 * Helper %M callback that prints contiguous C arrays.
 * Consumes void *array_ptr, size_t array_size, size_t elem_size, char *fmt
 * Return number of bytes printed.
 */
int json_printf_array(struct json_out *, va_list *ap);

/*
 * Scan JSON string `str`, performing scanf-like conversions according to `fmt`.
 * This is a `scanf()` - like function, with following differences:
 *
 * 1. Object keys in the format string may be not quoted, e.g. "{key: %d}"
 * 2. Order of keys in an object is irrelevant.
 * 3. Several extra format specifiers are supported:
 *    - %B: consumes `int *`, expects boolean `true` or `false`.
 *    - %Q: consumes `char **`, expects quoted, JSON-encoded string. Scanned
 *       string is malloc-ed, caller must free() the string.
 *    - %V: consumes `char **`, `int *`. Expects base64-encoded string.
 *       Result string is base64-decoded, malloced and NUL-terminated.
 *       The length of result string is stored in `int *` placeholder.
 *       Caller must free() the result.
 *    - %H: consumes `int *`, `char **`.
 *       Expects a hex-encoded string, e.g. "fa014f".
 *       Result string is hex-decoded, malloced and NUL-terminated.
 *       The length of the result string is stored in `int *` placeholder.
 *       Caller must free() the result.
 *    - %M: consumes custom scanning function pointer and
 *       `void *user_data` parameter - see json_scanner_t definition.
 *    - %T: consumes `struct json_token *`, fills it out with matched token.
 *
 * Return number of elements successfully scanned & converted.
 * Negative number means scan error.
 */
int json_scanf(const char *str, int str_len, const char *fmt, ...);
int json_vscanf(const char *str, int str_len, const char *fmt, va_list ap);

/* json_scanf's %M handler  */
typedef void (*json_scanner_t)(const char *str, int len, void *user_data);

/*
 * Helper function to scan array item with given path and index.
 * Fills `token` with the matched JSON token.
 * Return 0 if no array element found, otherwise non-0.
 */
int json_scanf_array_elem(const char *s, int len, const char *path, int index,
                          struct json_token *token);

/*
 * Unescape JSON-encoded string src,slen into dst, dlen.
 * src and dst may overlap.
 * If destination buffer is too small (or zero-length), result string is not
 * written but the length is counted nevertheless (similar to snprintf).
 * Return the length of unescaped string in bytes.
 */
int json_unescape(const char *src, int slen, char *dst, int dlen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_FROZEN_FROZEN_H_ */
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
  /* before jumping to a newly compiled code, save instruction pointer */
  bf_word_ptr_t ip = vm->ip;
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

  /* restore instruction pointer */
  vm->ip = ip;
}

void bf_die(struct bf_vm *vm) {
  /* force bf_run() to quit */
  vm->ip = FR_EXIT_RUN;
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
#define YYNOCODE 98
#define YYACTIONTYPE unsigned short int
#define mjsParserTOKENTYPE struct mjs_token
typedef union {
  int yyinit;
  mjsParserTOKENTYPE yy0;
  bf_word_ptr_t yy8;
  const char * yy172;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define mjsParserARG_SDECL struct mjs_parse_ctx *ctx;
#define mjsParserARG_PDECL ,struct mjs_parse_ctx *ctx
#define mjsParserARG_FETCH struct mjs_parse_ctx *ctx = yypParser->ctx
#define mjsParserARG_STORE yypParser->ctx = ctx
#define YYNSTATE             187
#define YYNRULE              137
#define YY_MAX_SHIFT         186
#define YY_MIN_SHIFTREDUCE   247
#define YY_MAX_SHIFTREDUCE   383
#define YY_MIN_REDUCE        384
#define YY_MAX_REDUCE        520
#define YY_ERROR_ACTION      521
#define YY_ACCEPT_ACTION     522
#define YY_NO_ACTION         523
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
#define YY_ACTTAB_COUNT (1819)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    48,   75,   73,   71,   69,   67,   59,   58,   57,   56,
 /*    10 */    63,   62,   61,   60,   66,   65,   64,   55,   54,   53,
 /*    20 */    52,   51,   55,   54,   53,   52,   51,   10,   50,  185,
 /*    30 */   185,  184,   10,   50,  309,   48,   75,   73,   71,   69,
 /*    40 */    67,   59,   58,   57,   56,   63,   62,   61,   60,   66,
 /*    50 */    65,   64,   55,   54,   53,   52,   51,   53,   52,   51,
 /*    60 */   152,  152,   10,   50,  174,   10,   50,  174,  279,    5,
 /*    70 */    48,   75,   73,   71,   69,   67,   59,   58,   57,   56,
 /*    80 */    63,   62,   61,   60,   66,   65,   64,   55,   54,   53,
 /*    90 */    52,   51,  349,   81,  155,  351,   82,   10,   50,  361,
 /*   100 */   184,   86,  348,  337,    7,   48,   75,   73,   71,   69,
 /*   110 */    67,   59,   58,   57,   56,   63,   62,   61,   60,   66,
 /*   120 */    65,   64,   55,   54,   53,   52,   51,   85,   16,  176,
 /*   130 */   338,  313,   10,   50,   17,  376,  354,   10,   50,   82,
 /*   140 */    47,   48,   75,   73,   71,   69,   67,   59,   58,   57,
 /*   150 */    56,   63,   62,   61,   60,   66,   65,   64,   55,   54,
 /*   160 */    53,   52,   51,  165,  382,   44,   45,  180,   10,   50,
 /*   170 */    78,   77,   68,   46,  139,   70,   11,   12,   80,  383,
 /*   180 */   138,  278,  277,  133,  173,  171,  170,    1,  182,   84,
 /*   190 */    18,  341,  342,  343,  344,  345,  346,  347,  335,  373,
 /*   200 */    48,   75,   73,   71,   69,   67,   59,   58,   57,   56,
 /*   210 */    63,   62,   61,   60,   66,   65,   64,   55,   54,   53,
 /*   220 */    52,   51,  520,  334,   44,   45,  333,   10,   50,   78,
 /*   230 */    77,   68,   46,    2,   70,   11,    4,   80,   13,  138,
 /*   240 */    14,   15,   30,  173,  171,  170,    1,    6,   84,   18,
 /*   250 */   341,  342,  343,  344,  345,  346,  347,   44,   45,   31,
 /*   260 */    42,    3,   78,   77,   68,   46,    9,   70,   11,  447,
 /*   270 */    80,   88,  132,  444,   89,   72,  173,  171,  170,    1,
 /*   280 */    90,   84,   18,  341,  342,  343,  344,  163,  346,  347,
 /*   290 */    73,   71,   69,   67,   59,   58,   57,   56,   63,   62,
 /*   300 */    61,   60,   66,   65,   64,   55,   54,   53,   52,   51,
 /*   310 */    76,   83,  384,  386,  386,   10,   50,   71,   69,   67,
 /*   320 */    59,   58,   57,   56,   63,   62,   61,   60,   66,   65,
 /*   330 */    64,   55,   54,   53,   52,   51,  386,  386,   44,   45,
 /*   340 */   386,   10,   50,   78,   77,   68,   46,  386,   70,   11,
 /*   350 */   386,   80,  386,  138,  386,  386,  386,  386,  386,  386,
 /*   360 */    79,  386,   87,   18,  341,  342,  343,  344,  345,  346,
 /*   370 */   347,   69,   67,   59,   58,   57,   56,   63,   62,   61,
 /*   380 */    60,   66,   65,   64,   55,   54,   53,   52,   51,  386,
 /*   390 */   386,  386,  386,  386,   10,   50,   44,   45,  386,  386,
 /*   400 */   386,   78,   77,   68,   46,  386,   70,   11,  386,  386,
 /*   410 */   386,  138,  386,  312,  386,  386,  386,  386,   79,  386,
 /*   420 */    87,  386,  341,  342,  343,  344,  345,  346,  347,  386,
 /*   430 */   386,  386,   67,   59,   58,   57,   56,   63,   62,   61,
 /*   440 */    60,   66,   65,   64,   55,   54,   53,   52,   51,  386,
 /*   450 */   386,  386,  386,  386,   10,   50,  386,  386,  386,  386,
 /*   460 */   386,  174,  386,  166,    8,  175,  253,  254,  257,  386,
 /*   470 */   386,  386,  124,  183,  183,  386,  386,  140,  386,  386,
 /*   480 */   253,  386,  183,  386,  386,  183,  183,  183,  155,  351,
 /*   490 */   386,  386,  386,  386,   44,   45,  386,  386,  386,   78,
 /*   500 */    77,   68,   46,  386,   70,   11,  386,  386,  386,  138,
 /*   510 */   386,  386,  386,  386,  386,  386,   79,  386,   87,  386,
 /*   520 */   341,  342,  343,  344,  345,  346,  347,   59,   58,   57,
 /*   530 */    56,   63,   62,   61,   60,   66,   65,   64,   55,   54,
 /*   540 */    53,   52,   51,  386,  386,  386,  386,  386,   10,   50,
 /*   550 */   522,  186,    8,  175,  253,  254,  257,  386,  386,  386,
 /*   560 */   124,  183,  183,  386,  386,  140,  386,  386,  253,  386,
 /*   570 */   183,  386,  386,  183,  183,  183,  386,  386,  164,    8,
 /*   580 */   175,  253,  254,  257,  386,  386,  386,  124,  183,  183,
 /*   590 */   386,  386,  140,  386,  386,  253,  386,  183,  386,  386,
 /*   600 */   183,  183,  183,  161,    8,  175,  253,  254,  257,  386,
 /*   610 */   386,  386,  124,  183,  183,  386,  386,  140,  386,  386,
 /*   620 */   253,  386,  183,  386,  386,  183,  183,  183,  386,   74,
 /*   630 */    29,   28,   27,   26,   25,   24,   23,   22,   21,   20,
 /*   640 */    19,  386,  386,  416,  416,  416,  416,  416,  416,  416,
 /*   650 */   416,  416,  416,  416,  416,  386,  122,  183,  183,  153,
 /*   660 */   315,  140,  386,  287,  289,  386,  183,  386,  386,  183,
 /*   670 */   183,  183,  386,  386,  386,  386,  519,  275,  276,   63,
 /*   680 */    62,   61,   60,   66,   65,   64,   55,   54,   53,   52,
 /*   690 */    51,  386,  386,  386,  386,  386,   10,   50,  386,  386,
 /*   700 */    74,   29,   28,   27,   26,   25,   24,   23,   22,   21,
 /*   710 */    20,   19,  369,  162,  369,  386,  386,  386,  124,  183,
 /*   720 */   183,  386,  386,  140,  369,  386,  369,  386,  183,  386,
 /*   730 */   386,  183,  183,  183,  287,  289,  332,  162,  332,  386,
 /*   740 */   386,  386,  124,  183,  183,  386,  386,  140,  332,  386,
 /*   750 */   332,  386,  183,  386,  386,  183,  183,  183,  331,  162,
 /*   760 */   331,  386,  386,  386,  124,  183,  183,  386,  386,  140,
 /*   770 */   331,  386,  331,  386,  183,  386,  386,  183,  183,  183,
 /*   780 */   172,  162,  172,  386,  386,  386,  124,  183,  183,  386,
 /*   790 */   386,  140,  172,  386,  172,  386,  183,  386,  386,  183,
 /*   800 */   183,  183,  386,  249,  252,  256,  386,  386,  386,  124,
 /*   810 */   183,  183,  386,  386,  140,  386,  386,  249,  386,  183,
 /*   820 */   386,  386,  183,  183,  183,  386,  386,  248,  251,  255,
 /*   830 */   386,  386,  386,  124,  183,  183,  386,  386,  140,   70,
 /*   840 */    11,  248,  386,  183,  177,  386,  183,  183,  183,  386,
 /*   850 */   386,   79,  386,   87,  386,  341,  342,  343,  344,  345,
 /*   860 */   346,  347,   70,   11,  386,  386,  386,  179,  386,  386,
 /*   870 */   386,  386,  386,  386,   79,  386,   87,  386,  341,  342,
 /*   880 */   343,  344,  345,  346,  347,   49,  453,  453,  453,  453,
 /*   890 */   453,  453,  453,  453,  453,  453,  453,   43,   41,   40,
 /*   900 */    39,   38,   37,   36,   35,   34,   33,   32,  386,  386,
 /*   910 */   386,  119,  183,  183,  386,  386,  140,  386,  386,  386,
 /*   920 */   386,  183,  386,  386,  183,  183,  183,  386,  386,  154,
 /*   930 */   356,   66,   65,   64,   55,   54,   53,   52,   51,  386,
 /*   940 */   386,  386,  386,  386,   10,   50,  386,  250,  386,  386,
 /*   950 */   386,  386,  124,  183,  183,  386,  386,  140,  386,  386,
 /*   960 */   386,  386,  183,  386,  386,  183,  183,  183,  108,  183,
 /*   970 */   183,  386,  386,  140,  386,  167,  386,  386,  183,  386,
 /*   980 */   386,  183,  183,  183,  108,  183,  183,  386,  386,  140,
 /*   990 */   386,  168,  386,  386,  183,  386,  386,  183,  183,  183,
 /*  1000 */   386,  386,  108,  183,  183,  386,  386,  140,  386,  169,
 /*  1010 */   386,  386,  183,  386,  386,  183,  183,  183,  386,  386,
 /*  1020 */   386,  386,  122,  183,  183,  386,  314,  140,  386,  386,
 /*  1030 */   386,  386,  183,  386,  386,  183,  183,  183,  386,  386,
 /*  1040 */   119,  183,  183,  386,  386,  140,  386,   96,  183,  183,
 /*  1050 */   183,  386,  140,  183,  183,  183,  386,  183,  386,  355,
 /*  1060 */   183,  183,  183,   97,  183,  183,  386,  386,  140,   98,
 /*  1070 */   183,  183,  386,  183,  140,  386,  183,  183,  183,  183,
 /*  1080 */   386,  386,  183,  183,  183,   99,  183,  183,  386,  386,
 /*  1090 */   140,  386,  386,  386,  386,  183,  178,  178,  183,  183,
 /*  1100 */   183,  100,  183,  183,  386,  178,  140,  386,  178,  178,
 /*  1110 */   178,  183,  386,  386,  183,  183,  183,  386,  101,  183,
 /*  1120 */   183,  386,  386,  140,  386,  102,  183,  183,  183,  386,
 /*  1130 */   140,  183,  183,  183,  386,  183,  386,  386,  183,  183,
 /*  1140 */   183,  103,  183,  183,  386,  386,  140,  104,  183,  183,
 /*  1150 */   386,  183,  140,  386,  183,  183,  183,  183,  181,  181,
 /*  1160 */   183,  183,  183,  105,  183,  183,  386,  181,  140,  386,
 /*  1170 */   181,  181,  181,  183,  386,  386,  183,  183,  183,  106,
 /*  1180 */   183,  183,  386,  386,  140,  386,  386,  386,  386,  183,
 /*  1190 */   386,  386,  183,  183,  183,  386,  107,  183,  183,  386,
 /*  1200 */   386,  140,  386,   92,  183,  183,  183,  386,  140,  183,
 /*  1210 */   183,  183,  386,  183,  386,  386,  183,  183,  183,   93,
 /*  1220 */   183,  183,  386,  386,  140,  109,  183,  183,  386,  183,
 /*  1230 */   140,  386,  183,  183,  183,  183,  386,  386,  183,  183,
 /*  1240 */   183,  110,  183,  183,  386,  386,  140,  386,  386,  386,
 /*  1250 */   386,  183,  386,  386,  183,  183,  183,  111,  183,  183,
 /*  1260 */   386,  386,  140,  386,  386,  386,  386,  183,  386,  386,
 /*  1270 */   183,  183,  183,  386,  112,  183,  183,  386,  386,  140,
 /*  1280 */   386,  113,  183,  183,  183,  386,  140,  183,  183,  183,
 /*  1290 */   386,  183,  386,  386,  183,  183,  183,  114,  183,  183,
 /*  1300 */   386,  386,  140,  115,  183,  183,  386,  183,  140,  386,
 /*  1310 */   183,  183,  183,  183,  386,  386,  183,  183,  183,  116,
 /*  1320 */   183,  183,  386,  386,  140,  386,  386,  386,  386,  183,
 /*  1330 */   386,  386,  183,  183,  183,  117,  183,  183,  386,  386,
 /*  1340 */   140,  386,  386,  386,  386,  183,  386,  386,  183,  183,
 /*  1350 */   183,  386,  118,  183,  183,  386,  386,  140,  386,  120,
 /*  1360 */   183,  183,  183,  386,  140,  183,  183,  183,  386,  183,
 /*  1370 */   386,  386,  183,  183,  183,  121,  183,  183,  386,  386,
 /*  1380 */   140,  148,  183,  183,  386,  183,  140,  386,  183,  183,
 /*  1390 */   183,  183,  386,  386,  183,  183,  183,  149,  183,  183,
 /*  1400 */   386,  386,  140,  386,  386,  386,  386,  183,  386,  386,
 /*  1410 */   183,  183,  183,  156,  183,  183,  386,  386,  140,  386,
 /*  1420 */   386,  386,  386,  183,  386,  386,  183,  183,  183,  386,
 /*  1430 */   123,  183,  183,  386,  386,  140,  386,   94,  183,  183,
 /*  1440 */   183,  386,  140,  183,  183,  183,  386,  183,  386,  386,
 /*  1450 */   183,  183,  183,  318,  183,  183,  386,  386,  140,   95,
 /*  1460 */   183,  183,  386,  183,  140,  386,  183,  183,  183,  183,
 /*  1470 */   386,  386,  183,  183,  183,  157,  183,  183,  386,  386,
 /*  1480 */   140,  386,  386,  386,  386,  183,  386,  386,  183,  183,
 /*  1490 */   183,  158,  183,  183,  386,  386,  140,  386,  386,  386,
 /*  1500 */   386,  183,  386,  386,  183,  183,  183,  386,  159,  183,
 /*  1510 */   183,  386,  386,  140,  386,  150,  183,  183,  183,  386,
 /*  1520 */   140,  183,  183,  183,  386,  183,  386,  386,  183,  183,
 /*  1530 */   183,  151,  183,  183,  386,  386,  140,  134,  183,  183,
 /*  1540 */   386,  183,  140,  386,  183,  183,  183,  183,  386,  386,
 /*  1550 */   183,  183,  183,  135,  183,  183,  386,  386,  140,  386,
 /*  1560 */   386,  386,  386,  183,  386,  386,  183,  183,  183,  136,
 /*  1570 */   183,  183,  386,  386,  140,  386,  386,  386,  386,  183,
 /*  1580 */   386,  386,  183,  183,  183,  386,  137,  183,  183,  386,
 /*  1590 */   386,  140,  386,  141,  183,  183,  183,  386,  140,  183,
 /*  1600 */   183,  183,  386,  183,  386,  386,  183,  183,  183,  142,
 /*  1610 */   183,  183,  386,  386,  140,  143,  183,  183,  386,  183,
 /*  1620 */   140,  386,  183,  183,  183,  183,  386,  386,  183,  183,
 /*  1630 */   183,  144,  183,  183,  386,  386,  140,  386,  386,  386,
 /*  1640 */   386,  183,  386,  386,  183,  183,  183,  145,  183,  183,
 /*  1650 */   386,  386,  140,  386,  386,  386,  386,  183,  386,  386,
 /*  1660 */   183,  183,  183,  386,  146,  183,  183,  386,  386,  140,
 /*  1670 */   386,  147,  183,  183,  183,  386,  140,  183,  183,  183,
 /*  1680 */   386,  183,  386,  386,  183,  183,  183,  131,  183,  183,
 /*  1690 */   386,  386,  140,  160,  183,  183,  386,  183,  140,  386,
 /*  1700 */   183,  183,  183,  183,  386,  386,  183,  183,  183,  130,
 /*  1710 */   183,  183,  386,  386,  140,  386,  386,  386,  386,  183,
 /*  1720 */   386,  386,  183,  183,  183,   91,  183,  183,  386,  386,
 /*  1730 */   140,  386,  386,  386,  386,  183,  386,  386,  183,  183,
 /*  1740 */   183,  386,  129,  183,  183,  386,  386,  140,  386,  274,
 /*  1750 */   183,  183,  183,  386,  140,  183,  183,  183,  386,  183,
 /*  1760 */   386,  386,  183,  183,  183,  128,  183,  183,  386,  386,
 /*  1770 */   140,  125,  183,  183,  386,  183,  140,  386,  183,  183,
 /*  1780 */   183,  183,  386,  386,  183,  183,  183,  127,  183,  183,
 /*  1790 */   386,  386,  140,  386,  386,  386,  386,  183,  386,  386,
 /*  1800 */   183,  183,  183,  126,  183,  183,  386,  386,  140,  386,
 /*  1810 */   386,  386,  386,  183,  386,  386,  183,  183,  183,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*    10 */    25,   26,   27,   28,   29,   30,   31,   32,   33,   34,
 /*    20 */    35,   36,   32,   33,   34,   35,   36,   42,   43,   74,
 /*    30 */    75,   76,   42,   43,   49,   15,   16,   17,   18,   19,
 /*    40 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*    50 */    30,   31,   32,   33,   34,   35,   36,   34,   35,   36,
 /*    60 */    88,   89,   42,   43,   66,   42,   43,   66,   47,   49,
 /*    70 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*    80 */    25,   26,   27,   28,   29,   30,   31,   32,   33,   34,
 /*    90 */    35,   36,   94,   46,   93,   94,   42,   42,   43,   75,
 /*   100 */    76,   47,   55,   47,   49,   15,   16,   17,   18,   19,
 /*   110 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   120 */    30,   31,   32,   33,   34,   35,   36,   46,   46,   86,
 /*   130 */    49,   49,   42,   43,   46,   89,   48,   42,   43,   42,
 /*   140 */    50,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   150 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   160 */    34,   35,   36,   86,   47,   32,   33,   47,   42,   43,
 /*   170 */    37,   38,   39,   40,   48,   42,   43,   44,   45,   62,
 /*   180 */    47,   76,   76,   47,   51,   52,   53,   54,   76,   56,
 /*   190 */    57,   58,   59,   60,   61,   62,   63,   64,   55,   44,
 /*   200 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   210 */    25,   26,   27,   28,   29,   30,   31,   32,   33,   34,
 /*   220 */    35,   36,   50,   55,   32,   33,   55,   42,   43,   37,
 /*   230 */    38,   39,   40,   54,   42,   43,   49,   45,   44,   47,
 /*   240 */    44,   42,   42,   51,   52,   53,   54,    2,   56,   57,
 /*   250 */    58,   59,   60,   61,   62,   63,   64,   32,   33,   42,
 /*   260 */    50,   54,   37,   38,   39,   40,   44,   42,   43,   41,
 /*   270 */    45,   41,   47,   41,   41,    3,   51,   52,   53,   54,
 /*   280 */    41,   56,   57,   58,   59,   60,   61,   62,   63,   64,
 /*   290 */    17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   300 */    27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
 /*   310 */     3,   46,    0,   97,   97,   42,   43,   18,   19,   20,
 /*   320 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   330 */    31,   32,   33,   34,   35,   36,   97,   97,   32,   33,
 /*   340 */    97,   42,   43,   37,   38,   39,   40,   97,   42,   43,
 /*   350 */    97,   45,   97,   47,   97,   97,   97,   97,   97,   97,
 /*   360 */    54,   97,   56,   57,   58,   59,   60,   61,   62,   63,
 /*   370 */    64,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   380 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   97,
 /*   390 */    97,   97,   97,   97,   42,   43,   32,   33,   97,   97,
 /*   400 */    97,   37,   38,   39,   40,   97,   42,   43,   97,   97,
 /*   410 */    97,   47,   97,   49,   97,   97,   97,   97,   54,   97,
 /*   420 */    56,   97,   58,   59,   60,   61,   62,   63,   64,   97,
 /*   430 */    97,   97,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   440 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   97,
 /*   450 */    97,   97,   97,   97,   42,   43,   97,   97,   97,   97,
 /*   460 */    97,   66,   97,   68,   69,   70,   71,   72,   73,   97,
 /*   470 */    97,   97,   77,   78,   79,   97,   97,   82,   97,   97,
 /*   480 */    85,   97,   87,   97,   97,   90,   91,   92,   93,   94,
 /*   490 */    97,   97,   97,   97,   32,   33,   97,   97,   97,   37,
 /*   500 */    38,   39,   40,   97,   42,   43,   97,   97,   97,   47,
 /*   510 */    97,   97,   97,   97,   97,   97,   54,   97,   56,   97,
 /*   520 */    58,   59,   60,   61,   62,   63,   64,   21,   22,   23,
 /*   530 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   540 */    34,   35,   36,   97,   97,   97,   97,   97,   42,   43,
 /*   550 */    67,   68,   69,   70,   71,   72,   73,   97,   97,   97,
 /*   560 */    77,   78,   79,   97,   97,   82,   97,   97,   85,   97,
 /*   570 */    87,   97,   97,   90,   91,   92,   97,   97,   68,   69,
 /*   580 */    70,   71,   72,   73,   97,   97,   97,   77,   78,   79,
 /*   590 */    97,   97,   82,   97,   97,   85,   97,   87,   97,   97,
 /*   600 */    90,   91,   92,   68,   69,   70,   71,   72,   73,   97,
 /*   610 */    97,   97,   77,   78,   79,   97,   97,   82,   97,   97,
 /*   620 */    85,   97,   87,   97,   97,   90,   91,   92,   97,    3,
 /*   630 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   640 */    14,   97,   97,    3,    4,    5,    6,    7,    8,    9,
 /*   650 */    10,   11,   12,   13,   14,   97,   77,   78,   79,   80,
 /*   660 */    81,   82,   97,   37,   38,   97,   87,   97,   97,   90,
 /*   670 */    91,   92,   97,   97,   97,   97,   50,   37,   38,   25,
 /*   680 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*   690 */    36,   97,   97,   97,   97,   97,   42,   43,   97,   97,
 /*   700 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   710 */    13,   14,   71,   72,   73,   97,   97,   97,   77,   78,
 /*   720 */    79,   97,   97,   82,   83,   97,   85,   97,   87,   97,
 /*   730 */    97,   90,   91,   92,   37,   38,   71,   72,   73,   97,
 /*   740 */    97,   97,   77,   78,   79,   97,   97,   82,   83,   97,
 /*   750 */    85,   97,   87,   97,   97,   90,   91,   92,   71,   72,
 /*   760 */    73,   97,   97,   97,   77,   78,   79,   97,   97,   82,
 /*   770 */    83,   97,   85,   97,   87,   97,   97,   90,   91,   92,
 /*   780 */    71,   72,   73,   97,   97,   97,   77,   78,   79,   97,
 /*   790 */    97,   82,   83,   97,   85,   97,   87,   97,   97,   90,
 /*   800 */    91,   92,   97,   71,   72,   73,   97,   97,   97,   77,
 /*   810 */    78,   79,   97,   97,   82,   97,   97,   85,   97,   87,
 /*   820 */    97,   97,   90,   91,   92,   97,   97,   71,   72,   73,
 /*   830 */    97,   97,   97,   77,   78,   79,   97,   97,   82,   42,
 /*   840 */    43,   85,   97,   87,   47,   97,   90,   91,   92,   97,
 /*   850 */    97,   54,   97,   56,   97,   58,   59,   60,   61,   62,
 /*   860 */    63,   64,   42,   43,   97,   97,   97,   47,   97,   97,
 /*   870 */    97,   97,   97,   97,   54,   97,   56,   97,   58,   59,
 /*   880 */    60,   61,   62,   63,   64,    3,    4,    5,    6,    7,
 /*   890 */     8,    9,   10,   11,   12,   13,   14,    4,    5,    6,
 /*   900 */     7,    8,    9,   10,   11,   12,   13,   14,   97,   97,
 /*   910 */    97,   77,   78,   79,   97,   97,   82,   97,   97,   97,
 /*   920 */    97,   87,   97,   97,   90,   91,   92,   97,   97,   95,
 /*   930 */    96,   29,   30,   31,   32,   33,   34,   35,   36,   97,
 /*   940 */    97,   97,   97,   97,   42,   43,   97,   72,   97,   97,
 /*   950 */    97,   97,   77,   78,   79,   97,   97,   82,   97,   97,
 /*   960 */    97,   97,   87,   97,   97,   90,   91,   92,   77,   78,
 /*   970 */    79,   97,   97,   82,   97,   84,   97,   97,   87,   97,
 /*   980 */    97,   90,   91,   92,   77,   78,   79,   97,   97,   82,
 /*   990 */    97,   84,   97,   97,   87,   97,   97,   90,   91,   92,
 /*  1000 */    97,   97,   77,   78,   79,   97,   97,   82,   97,   84,
 /*  1010 */    97,   97,   87,   97,   97,   90,   91,   92,   97,   97,
 /*  1020 */    97,   97,   77,   78,   79,   97,   81,   82,   97,   97,
 /*  1030 */    97,   97,   87,   97,   97,   90,   91,   92,   97,   97,
 /*  1040 */    77,   78,   79,   97,   97,   82,   97,   77,   78,   79,
 /*  1050 */    87,   97,   82,   90,   91,   92,   97,   87,   97,   96,
 /*  1060 */    90,   91,   92,   77,   78,   79,   97,   97,   82,   77,
 /*  1070 */    78,   79,   97,   87,   82,   97,   90,   91,   92,   87,
 /*  1080 */    97,   97,   90,   91,   92,   77,   78,   79,   97,   97,
 /*  1090 */    82,   97,   97,   97,   97,   87,   78,   79,   90,   91,
 /*  1100 */    92,   77,   78,   79,   97,   87,   82,   97,   90,   91,
 /*  1110 */    92,   87,   97,   97,   90,   91,   92,   97,   77,   78,
 /*  1120 */    79,   97,   97,   82,   97,   77,   78,   79,   87,   97,
 /*  1130 */    82,   90,   91,   92,   97,   87,   97,   97,   90,   91,
 /*  1140 */    92,   77,   78,   79,   97,   97,   82,   77,   78,   79,
 /*  1150 */    97,   87,   82,   97,   90,   91,   92,   87,   78,   79,
 /*  1160 */    90,   91,   92,   77,   78,   79,   97,   87,   82,   97,
 /*  1170 */    90,   91,   92,   87,   97,   97,   90,   91,   92,   77,
 /*  1180 */    78,   79,   97,   97,   82,   97,   97,   97,   97,   87,
 /*  1190 */    97,   97,   90,   91,   92,   97,   77,   78,   79,   97,
 /*  1200 */    97,   82,   97,   77,   78,   79,   87,   97,   82,   90,
 /*  1210 */    91,   92,   97,   87,   97,   97,   90,   91,   92,   77,
 /*  1220 */    78,   79,   97,   97,   82,   77,   78,   79,   97,   87,
 /*  1230 */    82,   97,   90,   91,   92,   87,   97,   97,   90,   91,
 /*  1240 */    92,   77,   78,   79,   97,   97,   82,   97,   97,   97,
 /*  1250 */    97,   87,   97,   97,   90,   91,   92,   77,   78,   79,
 /*  1260 */    97,   97,   82,   97,   97,   97,   97,   87,   97,   97,
 /*  1270 */    90,   91,   92,   97,   77,   78,   79,   97,   97,   82,
 /*  1280 */    97,   77,   78,   79,   87,   97,   82,   90,   91,   92,
 /*  1290 */    97,   87,   97,   97,   90,   91,   92,   77,   78,   79,
 /*  1300 */    97,   97,   82,   77,   78,   79,   97,   87,   82,   97,
 /*  1310 */    90,   91,   92,   87,   97,   97,   90,   91,   92,   77,
 /*  1320 */    78,   79,   97,   97,   82,   97,   97,   97,   97,   87,
 /*  1330 */    97,   97,   90,   91,   92,   77,   78,   79,   97,   97,
 /*  1340 */    82,   97,   97,   97,   97,   87,   97,   97,   90,   91,
 /*  1350 */    92,   97,   77,   78,   79,   97,   97,   82,   97,   77,
 /*  1360 */    78,   79,   87,   97,   82,   90,   91,   92,   97,   87,
 /*  1370 */    97,   97,   90,   91,   92,   77,   78,   79,   97,   97,
 /*  1380 */    82,   77,   78,   79,   97,   87,   82,   97,   90,   91,
 /*  1390 */    92,   87,   97,   97,   90,   91,   92,   77,   78,   79,
 /*  1400 */    97,   97,   82,   97,   97,   97,   97,   87,   97,   97,
 /*  1410 */    90,   91,   92,   77,   78,   79,   97,   97,   82,   97,
 /*  1420 */    97,   97,   97,   87,   97,   97,   90,   91,   92,   97,
 /*  1430 */    77,   78,   79,   97,   97,   82,   97,   77,   78,   79,
 /*  1440 */    87,   97,   82,   90,   91,   92,   97,   87,   97,   97,
 /*  1450 */    90,   91,   92,   77,   78,   79,   97,   97,   82,   77,
 /*  1460 */    78,   79,   97,   87,   82,   97,   90,   91,   92,   87,
 /*  1470 */    97,   97,   90,   91,   92,   77,   78,   79,   97,   97,
 /*  1480 */    82,   97,   97,   97,   97,   87,   97,   97,   90,   91,
 /*  1490 */    92,   77,   78,   79,   97,   97,   82,   97,   97,   97,
 /*  1500 */    97,   87,   97,   97,   90,   91,   92,   97,   77,   78,
 /*  1510 */    79,   97,   97,   82,   97,   77,   78,   79,   87,   97,
 /*  1520 */    82,   90,   91,   92,   97,   87,   97,   97,   90,   91,
 /*  1530 */    92,   77,   78,   79,   97,   97,   82,   77,   78,   79,
 /*  1540 */    97,   87,   82,   97,   90,   91,   92,   87,   97,   97,
 /*  1550 */    90,   91,   92,   77,   78,   79,   97,   97,   82,   97,
 /*  1560 */    97,   97,   97,   87,   97,   97,   90,   91,   92,   77,
 /*  1570 */    78,   79,   97,   97,   82,   97,   97,   97,   97,   87,
 /*  1580 */    97,   97,   90,   91,   92,   97,   77,   78,   79,   97,
 /*  1590 */    97,   82,   97,   77,   78,   79,   87,   97,   82,   90,
 /*  1600 */    91,   92,   97,   87,   97,   97,   90,   91,   92,   77,
 /*  1610 */    78,   79,   97,   97,   82,   77,   78,   79,   97,   87,
 /*  1620 */    82,   97,   90,   91,   92,   87,   97,   97,   90,   91,
 /*  1630 */    92,   77,   78,   79,   97,   97,   82,   97,   97,   97,
 /*  1640 */    97,   87,   97,   97,   90,   91,   92,   77,   78,   79,
 /*  1650 */    97,   97,   82,   97,   97,   97,   97,   87,   97,   97,
 /*  1660 */    90,   91,   92,   97,   77,   78,   79,   97,   97,   82,
 /*  1670 */    97,   77,   78,   79,   87,   97,   82,   90,   91,   92,
 /*  1680 */    97,   87,   97,   97,   90,   91,   92,   77,   78,   79,
 /*  1690 */    97,   97,   82,   77,   78,   79,   97,   87,   82,   97,
 /*  1700 */    90,   91,   92,   87,   97,   97,   90,   91,   92,   77,
 /*  1710 */    78,   79,   97,   97,   82,   97,   97,   97,   97,   87,
 /*  1720 */    97,   97,   90,   91,   92,   77,   78,   79,   97,   97,
 /*  1730 */    82,   97,   97,   97,   97,   87,   97,   97,   90,   91,
 /*  1740 */    92,   97,   77,   78,   79,   97,   97,   82,   97,   77,
 /*  1750 */    78,   79,   87,   97,   82,   90,   91,   92,   97,   87,
 /*  1760 */    97,   97,   90,   91,   92,   77,   78,   79,   97,   97,
 /*  1770 */    82,   77,   78,   79,   97,   87,   82,   97,   90,   91,
 /*  1780 */    92,   87,   97,   97,   90,   91,   92,   77,   78,   79,
 /*  1790 */    97,   97,   82,   97,   97,   97,   97,   87,   97,   97,
 /*  1800 */    90,   91,   92,   77,   78,   79,   97,   97,   82,   97,
 /*  1810 */    97,   97,   97,   87,   97,   97,   90,   91,   92,
};
#define YY_SHIFT_USE_DFLT (1819)
#define YY_SHIFT_COUNT    (186)
#define YY_SHIFT_MIN      (-15)
#define YY_SHIFT_MAX      (902)
static const short yy_shift_ofst[] = {
 /*     0 */   192,  225,  192,  192,  192,  192,  192,  192,  133,  192,
 /*    10 */   364,  462,  306,  462,  462,  462,  462,  462,  462,  462,
 /*    20 */   462,  462,  462,  462,  462,  462,  462,  462,  462,  462,
 /*    30 */   462,  462,  462,  462,  462,  462,  462,  462,  462,  462,
 /*    40 */   462,  462,  462,  462,  462,  462,  462,  462,  462,  462,
 /*    50 */   462,  462,  462,  462,  462,  462,  462,  462,  462,  462,
 /*    60 */   462,  462,  462,  462,  462,  462,  462,  462,  462,  462,
 /*    70 */   462,  462,  462,  462,  462,  462,  462,  797,  820,  117,
 /*    80 */    21,  117,   56,   21,   54,   56,   97,   97,  120,  120,
 /*    90 */   136,  -15,   20,   55,   90,  126,  185,  185,  185,  185,
 /*   100 */   185,  185,  185,  185,  185,  185,  185,  185,  185,  185,
 /*   110 */   185,  185,  185,  185,  185,  185,  185,  185,  185,  185,
 /*   120 */   185,  185,  185,  185,  185,  185,  185,  273,  299,  352,
 /*   130 */   412,  506,  626,  640,  654,  654,  654,  654,  697,  882,
 /*   140 */   893,  902,  902,  902,  902,  -10,  -10,  -10,   23,   23,
 /*   150 */    23,   23,   81,   82,   88,   47,   95,   95,   95,   95,
 /*   160 */    95,  143,  155,  172,  168,  179,  171,  187,  194,  196,
 /*   170 */   199,  200,  245,  217,  210,  222,  207,  228,  230,  228,
 /*   180 */   232,  233,  272,  239,  307,  265,  312,
};
#define YY_REDUCE_USE_DFLT (-46)
#define YY_REDUCE_COUNT (90)
#define YY_REDUCE_MIN   (-45)
#define YY_REDUCE_MAX   (1726)
static const short yy_reduce_ofst[] = {
 /*     0 */   483,  395,  510,  535,  641,  665,  687,  709,  732,  756,
 /*    10 */   579,  834,  875,  891,  907,  925,  945,  963,  970,  986,
 /*    20 */   992, 1008, 1024, 1041, 1048, 1064, 1070, 1086, 1102, 1119,
 /*    30 */  1126, 1142, 1148, 1164, 1180, 1197, 1204, 1220, 1226, 1242,
 /*    40 */  1258, 1275, 1282, 1298, 1304, 1320, 1336, 1353, 1360, 1376,
 /*    50 */  1382, 1398, 1414, 1431, 1438, 1454, 1460, 1476, 1492, 1509,
 /*    60 */  1516, 1532, 1538, 1554, 1570, 1587, 1594, 1610, 1616, 1632,
 /*    70 */  1648, 1665, 1672, 1688, 1694, 1710, 1726, 1018, 1080,    1,
 /*    80 */   -45,   -2,  -28,   24,   43,   46,   77,   43,  105,  106,
 /*    90 */   112,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   521,  489,  521,  521,  521,  521,  521,  521,  496,  395,
 /*    10 */   521,  494,  521,  507,  507,  507,  521,  521,  476,  521,
 /*    20 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    30 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    40 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    50 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    60 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    70 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  489,
 /*    80 */   521,  487,  473,  521,  521,  521,  521,  521,  521,  521,
 /*    90 */   521,  521,  521,  521,  521,  521,  477,  410,  409,  408,
 /*   100 */   407,  406,  405,  404,  403,  402,  401,  400,  508,  466,
 /*   110 */   465,  464,  463,  462,  461,  460,  459,  458,  457,  495,
 /*   120 */   490,  456,  505,  448,  500,  399,  397,  418,  419,  427,
 /*   130 */   428,  429,  447,  444,  503,  502,  438,  437,  447,  445,
 /*   140 */   521,  436,  435,  434,  433,  432,  431,  430,  422,  421,
 /*   150 */   440,  439,  521,  521,  521,  521,  420,  443,  442,  441,
 /*   160 */   417,  521,  521,  482,  521,  521,  521,  521,  521,  521,
 /*   170 */   521,  521,  467,  521,  521,  497,  521,  425,  521,  423,
 /*   180 */   416,  521,  454,  501,  398,  396,  521,
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
  "AND_ASSIGN",    "XOR_ASSIGN",    "OR_ASSIGN",     "QUESTION",    
  "LOGICAL_AND",   "LOGICAL_OR",    "OR",            "XOR",         
  "AND",           "EQ",            "NE",            "EQ_EQ",       
  "NE_NE",         "LE",            "LT",            "GE",          
  "GT",            "LSHIFT",        "RSHIFT",        "URSHIFT",     
  "PLUS",          "MINUS",         "MUL",           "DIV",         
  "REM",           "PLUS_PLUS",     "MINUS_MINUS",   "NOT",         
  "TILDA",         "DOT",           "OPEN_PAREN",    "OPEN_BRACKET",
  "SEMICOLON",     "LET",           "COMMA",         "IDENTIFIER",  
  "CLOSE_BRACKET",  "CLOSE_PAREN",   "COLON",         "IF",          
  "WHILE",         "FOR",           "OPEN_CURLY",    "CLOSE_CURLY", 
  "FUNCTION",      "RETURN",        "NULL",          "UNDEFINED",   
  "THIS",          "NUMBER",        "STRING_LITERAL",  "TRUE",        
  "FALSE",         "error",         "objspeclhs",    "program",     
  "stmtlist",      "cstmtlist",     "sstmtlist",     "cstmt",       
  "sstmt",         "block",         "letspecs",      "letspec",     
  "ident",         "expr",          "sexp",          "literal",     
  "callarglist",   "callarg",       "objprop",       "block_or_stmt",
  "optexpr",       "funcdecl",      "arglistparen",  "func_literal",
  "arglist",       "argspec",       "boolean_literal",  "object_literal",
  "array_literal",  "objspeclist",   "objspec",       "arrayspeclist",
  "arrspec",     
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
 /*   8 */ "cstmtlist ::= sstmtlist SEMICOLON block",
 /*   9 */ "cstmtlist ::= cstmtlist block",
 /*  10 */ "cstmtlist ::= block",
 /*  11 */ "sstmtlist ::= sstmtlist SEMICOLON",
 /*  12 */ "sstmt ::= LET letspecs",
 /*  13 */ "letspec ::= ident ASSIGN expr",
 /*  14 */ "letspec ::= ident",
 /*  15 */ "expr ::= IDENTIFIER ASSIGN expr",
 /*  16 */ "expr ::= IDENTIFIER PLUS_ASSIGN expr",
 /*  17 */ "expr ::= IDENTIFIER MINUS_ASSIGN expr",
 /*  18 */ "expr ::= IDENTIFIER MUL_ASSIGN expr",
 /*  19 */ "expr ::= IDENTIFIER DIV_ASSIGN expr",
 /*  20 */ "expr ::= IDENTIFIER REM_ASSIGN expr",
 /*  21 */ "expr ::= IDENTIFIER LSHIFT_ASSIGN expr",
 /*  22 */ "expr ::= IDENTIFIER RSHIFT_ASSIGN expr",
 /*  23 */ "expr ::= IDENTIFIER URSHIFT_ASSIGN expr",
 /*  24 */ "expr ::= IDENTIFIER AND_ASSIGN expr",
 /*  25 */ "expr ::= IDENTIFIER XOR_ASSIGN expr",
 /*  26 */ "expr ::= IDENTIFIER OR_ASSIGN expr",
 /*  27 */ "expr ::= sexp DOT ident ASSIGN expr",
 /*  28 */ "expr ::= sexp DOT IDENTIFIER PLUS_PLUS",
 /*  29 */ "expr ::= sexp DOT IDENTIFIER MINUS_MINUS",
 /*  30 */ "expr ::= PLUS_PLUS sexp DOT ident",
 /*  31 */ "expr ::= MINUS_MINUS sexp DOT ident",
 /*  32 */ "ident ::= IDENTIFIER",
 /*  33 */ "expr ::= NOT expr",
 /*  34 */ "expr ::= expr LOGICAL_AND expr",
 /*  35 */ "expr ::= expr LOGICAL_OR expr",
 /*  36 */ "expr ::= TILDA expr",
 /*  37 */ "expr ::= MINUS expr",
 /*  38 */ "expr ::= PLUS expr",
 /*  39 */ "expr ::= PLUS_PLUS IDENTIFIER",
 /*  40 */ "expr ::= IDENTIFIER PLUS_PLUS",
 /*  41 */ "expr ::= MINUS_MINUS IDENTIFIER",
 /*  42 */ "expr ::= IDENTIFIER MINUS_MINUS",
 /*  43 */ "expr ::= expr OR expr",
 /*  44 */ "expr ::= expr XOR expr",
 /*  45 */ "expr ::= expr AND expr",
 /*  46 */ "expr ::= expr LSHIFT expr",
 /*  47 */ "expr ::= expr RSHIFT expr",
 /*  48 */ "expr ::= expr URSHIFT expr",
 /*  49 */ "expr ::= expr LE expr",
 /*  50 */ "expr ::= expr LT expr",
 /*  51 */ "expr ::= expr GE expr",
 /*  52 */ "expr ::= expr GT expr",
 /*  53 */ "expr ::= expr EQ expr",
 /*  54 */ "expr ::= expr NE expr",
 /*  55 */ "expr ::= expr PLUS expr",
 /*  56 */ "expr ::= expr MINUS expr",
 /*  57 */ "expr ::= expr MUL expr",
 /*  58 */ "expr ::= expr DIV expr",
 /*  59 */ "expr ::= expr REM expr",
 /*  60 */ "sexp ::= sexp DOT IDENTIFIER",
 /*  61 */ "expr ::= expr OPEN_BRACKET expr CLOSE_BRACKET",
 /*  62 */ "sexp ::= OPEN_PAREN expr CLOSE_PAREN",
 /*  63 */ "sexp ::= IDENTIFIER",
 /*  64 */ "expr ::= expr QUESTION expr COLON expr",
 /*  65 */ "expr ::= expr OPEN_PAREN CLOSE_PAREN",
 /*  66 */ "expr ::= expr OPEN_PAREN callarglist CLOSE_PAREN",
 /*  67 */ "callarglist ::= callarglist COMMA callarg",
 /*  68 */ "callarglist ::= callarg",
 /*  69 */ "objprop ::= expr OPEN_BRACKET expr CLOSE_BRACKET",
 /*  70 */ "objprop ::= sexp DOT ident",
 /*  71 */ "expr ::= expr OPEN_BRACKET expr CLOSE_BRACKET ASSIGN expr",
 /*  72 */ "expr ::= objprop PLUS_ASSIGN expr",
 /*  73 */ "expr ::= objprop MINUS_ASSIGN expr",
 /*  74 */ "expr ::= objprop MUL_ASSIGN expr",
 /*  75 */ "expr ::= objprop DIV_ASSIGN expr",
 /*  76 */ "expr ::= objprop REM_ASSIGN expr",
 /*  77 */ "expr ::= objprop LSHIFT_ASSIGN expr",
 /*  78 */ "expr ::= objprop RSHIFT_ASSIGN expr",
 /*  79 */ "expr ::= objprop URSHIFT_ASSIGN expr",
 /*  80 */ "expr ::= objprop AND_ASSIGN expr",
 /*  81 */ "expr ::= objprop XOR_ASSIGN expr",
 /*  82 */ "expr ::= objprop OR_ASSIGN expr",
 /*  83 */ "cstmt ::= IF OPEN_PAREN expr CLOSE_PAREN block_or_stmt",
 /*  84 */ "cstmt ::= IF OPEN_PAREN expr CLOSE_PAREN block_or_stmt ELSE block_or_stmt",
 /*  85 */ "cstmt ::= WHILE OPEN_PAREN expr CLOSE_PAREN block_or_stmt",
 /*  86 */ "block ::= OPEN_CURLY stmtlist CLOSE_CURLY",
 /*  87 */ "funcdecl ::= FUNCTION IDENTIFIER arglistparen OPEN_CURLY stmtlist CLOSE_CURLY",
 /*  88 */ "func_literal ::= FUNCTION arglistparen OPEN_CURLY stmtlist CLOSE_CURLY",
 /*  89 */ "arglist ::=",
 /*  90 */ "argspec ::= IDENTIFIER",
 /*  91 */ "arglistparen ::= OPEN_PAREN arglist CLOSE_PAREN",
 /*  92 */ "sstmt ::= RETURN",
 /*  93 */ "sstmt ::= RETURN expr",
 /*  94 */ "literal ::= NULL",
 /*  95 */ "literal ::= UNDEFINED",
 /*  96 */ "literal ::= THIS",
 /*  97 */ "literal ::= NUMBER",
 /*  98 */ "literal ::= STRING_LITERAL",
 /*  99 */ "boolean_literal ::= TRUE",
 /* 100 */ "boolean_literal ::= FALSE",
 /* 101 */ "object_literal ::= OPEN_CURLY objspeclist CLOSE_CURLY",
 /* 102 */ "objspeclist ::= objspeclist COMMA objspec",
 /* 103 */ "objspeclist ::= objspeclist COMMA",
 /* 104 */ "objspeclist ::= objspec",
 /* 105 */ "objspeclist ::=",
 /* 106 */ "objspec ::= objspeclhs COLON expr",
 /* 107 */ "array_literal ::= OPEN_BRACKET arrayspeclist CLOSE_BRACKET",
 /* 108 */ "arrayspeclist ::= arrayspeclist COMMA arrspec",
 /* 109 */ "arrayspeclist ::= arrspec",
 /* 110 */ "arrayspeclist ::=",
 /* 111 */ "arrspec ::= expr",
 /* 112 */ "stmtlist ::= cstmtlist",
 /* 113 */ "stmtlist ::= sstmtlist",
 /* 114 */ "letspecs ::= letspecs COMMA letspec",
 /* 115 */ "letspecs ::= letspec",
 /* 116 */ "sstmt ::= expr",
 /* 117 */ "expr ::= sexp",
 /* 118 */ "expr ::= expr EQ_EQ expr",
 /* 119 */ "expr ::= expr NE_NE expr",
 /* 120 */ "sexp ::= literal",
 /* 121 */ "callarg ::= expr",
 /* 122 */ "cstmt ::= FOR OPEN_PAREN optexpr SEMICOLON optexpr SEMICOLON optexpr CLOSE_PAREN block_or_stmt",
 /* 123 */ "optexpr ::=",
 /* 124 */ "optexpr ::= expr",
 /* 125 */ "block_or_stmt ::= block",
 /* 126 */ "block_or_stmt ::= sstmt SEMICOLON",
 /* 127 */ "block_or_stmt ::= cstmt",
 /* 128 */ "cstmt ::= funcdecl",
 /* 129 */ "arglist ::= arglist COMMA argspec",
 /* 130 */ "arglist ::= argspec",
 /* 131 */ "literal ::= boolean_literal",
 /* 132 */ "literal ::= func_literal",
 /* 133 */ "literal ::= object_literal",
 /* 134 */ "literal ::= array_literal",
 /* 135 */ "objspeclhs ::= IDENTIFIER",
 /* 136 */ "objspeclhs ::= STRING_LITERAL",
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
    case 67: /* program */
{
#line 41 "mjs/mjs.lem.c"

  (void) ctx;
  (void) yypminor;

#line 1011 "mjs/mjs.lem.c"
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
#line 1185 "mjs/mjs.lem.c"
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
  { 67, 1 },
  { 69, 3 },
  { 69, 2 },
  { 70, 3 },
  { 70, 3 },
  { 70, 2 },
  { 69, 1 },
  { 70, 1 },
  { 69, 3 },
  { 69, 2 },
  { 69, 1 },
  { 70, 2 },
  { 72, 2 },
  { 75, 3 },
  { 75, 1 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 5 },
  { 77, 4 },
  { 77, 4 },
  { 77, 4 },
  { 77, 4 },
  { 76, 1 },
  { 77, 2 },
  { 77, 3 },
  { 77, 3 },
  { 77, 2 },
  { 77, 2 },
  { 77, 2 },
  { 77, 2 },
  { 77, 2 },
  { 77, 2 },
  { 77, 2 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 78, 3 },
  { 77, 4 },
  { 78, 3 },
  { 78, 1 },
  { 77, 5 },
  { 77, 3 },
  { 77, 4 },
  { 80, 3 },
  { 80, 1 },
  { 82, 4 },
  { 82, 3 },
  { 77, 6 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 77, 3 },
  { 71, 5 },
  { 71, 7 },
  { 71, 5 },
  { 73, 3 },
  { 85, 6 },
  { 87, 5 },
  { 88, 0 },
  { 89, 1 },
  { 86, 3 },
  { 72, 1 },
  { 72, 2 },
  { 79, 1 },
  { 79, 1 },
  { 79, 1 },
  { 79, 1 },
  { 79, 1 },
  { 90, 1 },
  { 90, 1 },
  { 91, 3 },
  { 93, 3 },
  { 93, 2 },
  { 93, 1 },
  { 93, 0 },
  { 94, 3 },
  { 92, 3 },
  { 95, 3 },
  { 95, 1 },
  { 95, 0 },
  { 96, 1 },
  { 68, 1 },
  { 68, 1 },
  { 74, 3 },
  { 74, 1 },
  { 72, 1 },
  { 77, 1 },
  { 77, 3 },
  { 77, 3 },
  { 78, 1 },
  { 81, 1 },
  { 71, 9 },
  { 84, 0 },
  { 84, 1 },
  { 83, 1 },
  { 83, 2 },
  { 83, 1 },
  { 71, 1 },
  { 88, 3 },
  { 88, 1 },
  { 79, 1 },
  { 79, 1 },
  { 79, 1 },
  { 79, 1 },
  { 66, 1 },
  { 66, 1 },
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
#line 64 "mjs/mjs.lem.c"
{ ctx->state = 1; ctx->entry = yymsp[0].minor.yy8; }
#line 1460 "mjs/mjs.lem.c"
        break;
      case 1: /* cstmtlist ::= sstmtlist SEMICOLON cstmt */
      case 3: /* sstmtlist ::= cstmtlist SEMICOLON sstmt */ yytestcase(yyruleno==3);
      case 4: /* sstmtlist ::= sstmtlist SEMICOLON sstmt */ yytestcase(yyruleno==4);
      case 8: /* cstmtlist ::= sstmtlist SEMICOLON block */ yytestcase(yyruleno==8);
#line 82 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_add_stmt(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8); }
#line 1468 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 2: /* cstmtlist ::= cstmtlist cstmt */
      case 5: /* sstmtlist ::= cstmtlist sstmt */ yytestcase(yyruleno==5);
      case 9: /* cstmtlist ::= cstmtlist block */ yytestcase(yyruleno==9);
#line 83 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_add_stmt(ctx, yymsp[-1].minor.yy8, yymsp[0].minor.yy8); }
#line 1476 "mjs/mjs.lem.c"
  yymsp[-1].minor.yy8 = yylhsminor.yy8;
        break;
      case 6: /* cstmtlist ::= cstmt */
      case 7: /* sstmtlist ::= sstmt */ yytestcase(yyruleno==7);
#line 87 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8); mjs_emit(ctx, MJS_OP_exit); }
#line 1483 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 10: /* cstmtlist ::= block */
#line 91 "mjs/mjs.lem.c"
{ yylhsminor.yy8=yymsp[0].minor.yy8; }
#line 1489 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 11: /* sstmtlist ::= sstmtlist SEMICOLON */
#line 93 "mjs/mjs.lem.c"
{ yylhsminor.yy8=yymsp[-1].minor.yy8; }
#line 1495 "mjs/mjs.lem.c"
  yymsp[-1].minor.yy8 = yylhsminor.yy8;
        break;
      case 12: /* sstmt ::= LET letspecs */
#line 96 "mjs/mjs.lem.c"
{
  yymsp[-1].minor.yy8=yymsp[0].minor.yy8;
}
#line 1503 "mjs/mjs.lem.c"
        break;
      case 13: /* letspec ::= ident ASSIGN expr */
#line 102 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_call(ctx, yymsp[-2].minor.yy8);
  mjs_emit(ctx, MJS_OP_dup);
  mjs_emit(ctx, MJS_OP_createvar);
  mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_setvar);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1515 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 14: /* letspec ::= ident */
#line 110 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_createvar);
  mjs_emit(ctx, MJS_OP_undefined);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1526 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 15: /* expr ::= IDENTIFIER ASSIGN expr */
#line 120 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, 0); }
#line 1532 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 16: /* expr ::= IDENTIFIER PLUS_ASSIGN expr */
#line 121 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_PLUS); }
#line 1538 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 17: /* expr ::= IDENTIFIER MINUS_ASSIGN expr */
#line 122 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_MINUS); }
#line 1544 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 18: /* expr ::= IDENTIFIER MUL_ASSIGN expr */
#line 123 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_STAR); }
#line 1550 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 19: /* expr ::= IDENTIFIER DIV_ASSIGN expr */
#line 124 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_div); }
#line 1556 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 20: /* expr ::= IDENTIFIER REM_ASSIGN expr */
#line 125 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_rem); }
#line 1562 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 21: /* expr ::= IDENTIFIER LSHIFT_ASSIGN expr */
#line 126 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_lshift); }
#line 1568 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 22: /* expr ::= IDENTIFIER RSHIFT_ASSIGN expr */
#line 127 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_rshift); }
#line 1574 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 23: /* expr ::= IDENTIFIER URSHIFT_ASSIGN expr */
#line 128 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_urshift); }
#line 1580 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 24: /* expr ::= IDENTIFIER AND_ASSIGN expr */
#line 129 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_and); }
#line 1586 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 25: /* expr ::= IDENTIFIER XOR_ASSIGN expr */
#line 130 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_xor); }
#line 1592 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 26: /* expr ::= IDENTIFIER OR_ASSIGN expr */
#line 131 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_assign(ctx, yymsp[-2].minor.yy0.begin, yymsp[0].minor.yy8, MJS_OP_or); }
#line 1598 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 27: /* expr ::= sexp DOT ident ASSIGN expr */
#line 134 "mjs/mjs.lem.c"
{
  bf_word_ptr_t prop = mjs_emit_objprop(ctx, yymsp[-4].minor.yy8, yymsp[-2].minor.yy8, 0);
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, prop, yymsp[0].minor.yy8, 0);
}
#line 1607 "mjs/mjs.lem.c"
  yymsp[-4].minor.yy8 = yylhsminor.yy8;
        break;
      case 28: /* expr ::= sexp DOT IDENTIFIER PLUS_PLUS */
#line 139 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_postop_prop(ctx, yymsp[-3].minor.yy8, yymsp[-1].minor.yy0.begin, MJS_OP_PLUS);
}
#line 1615 "mjs/mjs.lem.c"
  yymsp[-3].minor.yy8 = yylhsminor.yy8;
        break;
      case 29: /* expr ::= sexp DOT IDENTIFIER MINUS_MINUS */
#line 143 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_postop_prop(ctx, yymsp[-3].minor.yy8, yymsp[-1].minor.yy0.begin, MJS_OP_MINUS);
}
#line 1623 "mjs/mjs.lem.c"
  yymsp[-3].minor.yy8 = yylhsminor.yy8;
        break;
      case 30: /* expr ::= PLUS_PLUS sexp DOT ident */
#line 147 "mjs/mjs.lem.c"
{
  bf_word_ptr_t prop = mjs_emit_objprop(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 1);
  yymsp[-3].minor.yy8=mjs_emit_objprop_assign(ctx, prop, MJS_WORD_PTR_one, MJS_OP_PLUS);
}
#line 1632 "mjs/mjs.lem.c"
        break;
      case 31: /* expr ::= MINUS_MINUS sexp DOT ident */
#line 152 "mjs/mjs.lem.c"
{
  bf_word_ptr_t prop = mjs_emit_objprop(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 1);
  yymsp[-3].minor.yy8=mjs_emit_objprop_assign(ctx, prop, MJS_WORD_PTR_one, MJS_OP_MINUS);
}
#line 1640 "mjs/mjs.lem.c"
        break;
      case 32: /* ident ::= IDENTIFIER */
#line 157 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_ident(ctx, yymsp[0].minor.yy0.begin); }
#line 1645 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 33: /* expr ::= NOT expr */
#line 162 "mjs/mjs.lem.c"
{
  yymsp[-1].minor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_jsinvert);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1655 "mjs/mjs.lem.c"
        break;
      case 34: /* expr ::= expr LOGICAL_AND expr */
#line 167 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_js_logical_and);
}
#line 1662 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 35: /* expr ::= expr LOGICAL_OR expr */
#line 170 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_js_logical_or);
}
#line 1670 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 36: /* expr ::= TILDA expr */
#line 173 "mjs/mjs.lem.c"
{
  yymsp[-1].minor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_not);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1680 "mjs/mjs.lem.c"
        break;
      case 37: /* expr ::= MINUS expr */
#line 178 "mjs/mjs.lem.c"
{
  yymsp[-1].minor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_neg);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1689 "mjs/mjs.lem.c"
        break;
      case 38: /* expr ::= PLUS expr */
#line 184 "mjs/mjs.lem.c"
{
  yymsp[-1].minor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_pos);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1698 "mjs/mjs.lem.c"
        break;
      case 39: /* expr ::= PLUS_PLUS IDENTIFIER */
#line 190 "mjs/mjs.lem.c"
{
  yymsp[-1].minor.yy8=mjs_emit_assign(ctx, yymsp[0].minor.yy0.begin, MJS_WORD_PTR_one, MJS_OP_PLUS);
}
#line 1705 "mjs/mjs.lem.c"
        break;
      case 40: /* expr ::= IDENTIFIER PLUS_PLUS */
#line 193 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_postop(ctx, yymsp[-1].minor.yy0.begin, MJS_OP_PLUS);
}
#line 1712 "mjs/mjs.lem.c"
  yymsp[-1].minor.yy8 = yylhsminor.yy8;
        break;
      case 41: /* expr ::= MINUS_MINUS IDENTIFIER */
#line 196 "mjs/mjs.lem.c"
{
  yymsp[-1].minor.yy8=mjs_emit_assign(ctx, yymsp[0].minor.yy0.begin, MJS_WORD_PTR_one, MJS_OP_MINUS);
}
#line 1720 "mjs/mjs.lem.c"
        break;
      case 42: /* expr ::= IDENTIFIER MINUS_MINUS */
#line 199 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_postop(ctx, yymsp[-1].minor.yy0.begin, MJS_OP_MINUS);
}
#line 1727 "mjs/mjs.lem.c"
  yymsp[-1].minor.yy8 = yylhsminor.yy8;
        break;
      case 43: /* expr ::= expr OR expr */
#line 203 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_or); }
#line 1733 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 44: /* expr ::= expr XOR expr */
#line 204 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_xor); }
#line 1739 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 45: /* expr ::= expr AND expr */
#line 205 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_and); }
#line 1745 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 46: /* expr ::= expr LSHIFT expr */
#line 206 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_lshift); }
#line 1751 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 47: /* expr ::= expr RSHIFT expr */
#line 207 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_rshift); }
#line 1757 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 48: /* expr ::= expr URSHIFT expr */
#line 208 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_urshift); }
#line 1763 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 49: /* expr ::= expr LE expr */
#line 209 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_js_LTEQ); }
#line 1769 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 50: /* expr ::= expr LT expr */
#line 210 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_js_LT); }
#line 1775 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 51: /* expr ::= expr GE expr */
#line 211 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_js_GTEQ); }
#line 1781 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 52: /* expr ::= expr GT expr */
#line 212 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_js_GT); }
#line 1787 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 53: /* expr ::= expr EQ expr */
#line 213 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_js_EQ); }
#line 1793 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 54: /* expr ::= expr NE expr */
#line 214 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_js_SETEQ); }
#line 1799 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 55: /* expr ::= expr PLUS expr */
#line 217 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_PLUS); }
#line 1805 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 56: /* expr ::= expr MINUS expr */
#line 218 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_MINUS); }
#line 1811 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 57: /* expr ::= expr MUL expr */
#line 219 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_STAR); }
#line 1817 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 58: /* expr ::= expr DIV expr */
#line 220 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_div); }
#line 1823 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 59: /* expr ::= expr REM expr */
#line 221 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_bin(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_rem); }
#line 1829 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 60: /* sexp ::= sexp DOT IDENTIFIER */
#line 222 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_call(ctx, yymsp[-2].minor.yy8);
  mjs_emit_str_or_ident(ctx, yymsp[0].minor.yy0.begin);
  mjs_emit(ctx, MJS_OP_getprop);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1840 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 61: /* expr ::= expr OPEN_BRACKET expr CLOSE_BRACKET */
#line 228 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_call(ctx, yymsp[-3].minor.yy8);
  mjs_emit_call(ctx, yymsp[-1].minor.yy8);
  mjs_emit(ctx, MJS_OP_getprop);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1851 "mjs/mjs.lem.c"
  yymsp[-3].minor.yy8 = yylhsminor.yy8;
        break;
      case 62: /* sexp ::= OPEN_PAREN expr CLOSE_PAREN */
      case 101: /* object_literal ::= OPEN_CURLY objspeclist CLOSE_CURLY */ yytestcase(yyruleno==101);
      case 107: /* array_literal ::= OPEN_BRACKET arrayspeclist CLOSE_BRACKET */ yytestcase(yyruleno==107);
#line 234 "mjs/mjs.lem.c"
{ yymsp[-2].minor.yy8=yymsp[-1].minor.yy8; }
#line 1859 "mjs/mjs.lem.c"
        break;
      case 63: /* sexp ::= IDENTIFIER */
#line 236 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_var(ctx, yymsp[0].minor.yy0.begin); }
#line 1864 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 64: /* expr ::= expr QUESTION expr COLON expr */
#line 239 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_call(ctx, yymsp[-4].minor.yy8);
  mjs_emit_quote(ctx, yymsp[-2].minor.yy8);
  mjs_emit_quote(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_ifelse);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1876 "mjs/mjs.lem.c"
  yymsp[-4].minor.yy8 = yylhsminor.yy8;
        break;
      case 65: /* expr ::= expr OPEN_PAREN CLOSE_PAREN */
#line 248 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit(ctx, MJS_OP_zero);
  mjs_emit_call(ctx, yymsp[-2].minor.yy8);
  mjs_emit(ctx, MJS_OP_this_for_call);
  mjs_emit(ctx, MJS_OP_swap);
  mjs_emit(ctx, MJS_OP_jscall);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1889 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 66: /* expr ::= expr OPEN_PAREN callarglist CLOSE_PAREN */
#line 257 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit(ctx, MJS_OP_zero);
  mjs_emit_call(ctx, yymsp[-1].minor.yy8);
  mjs_emit_call(ctx, yymsp[-3].minor.yy8);
  mjs_emit(ctx, MJS_OP_this_for_call);
  mjs_emit(ctx, MJS_OP_swap);
  mjs_emit(ctx, MJS_OP_jscall);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1903 "mjs/mjs.lem.c"
  yymsp[-3].minor.yy8 = yylhsminor.yy8;
        break;
      case 67: /* callarglist ::= callarglist COMMA callarg */
#line 266 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_swapinc);
  mjs_emit_call(ctx, yymsp[-2].minor.yy8);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1914 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 68: /* callarglist ::= callarg */
#line 272 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_swapinc);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 1924 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 69: /* objprop ::= expr OPEN_BRACKET expr CLOSE_BRACKET */
#line 284 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop(ctx, yymsp[-3].minor.yy8, yymsp[-1].minor.yy8, 1);
}
#line 1932 "mjs/mjs.lem.c"
  yymsp[-3].minor.yy8 = yylhsminor.yy8;
        break;
      case 70: /* objprop ::= sexp DOT ident */
#line 288 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 1);
}
#line 1940 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 71: /* expr ::= expr OPEN_BRACKET expr CLOSE_BRACKET ASSIGN expr */
#line 292 "mjs/mjs.lem.c"
{
  bf_word_ptr_t prop = mjs_emit_objprop(ctx, yymsp[-5].minor.yy8, yymsp[-3].minor.yy8, 0);
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, prop, yymsp[0].minor.yy8, 0);
}
#line 1949 "mjs/mjs.lem.c"
  yymsp[-5].minor.yy8 = yylhsminor.yy8;
        break;
      case 72: /* expr ::= objprop PLUS_ASSIGN expr */
#line 297 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_PLUS);
}
#line 1957 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 73: /* expr ::= objprop MINUS_ASSIGN expr */
#line 301 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_MINUS);
}
#line 1965 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 74: /* expr ::= objprop MUL_ASSIGN expr */
#line 305 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_STAR);
}
#line 1973 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 75: /* expr ::= objprop DIV_ASSIGN expr */
#line 309 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_div);
}
#line 1981 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 76: /* expr ::= objprop REM_ASSIGN expr */
#line 313 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_rem);
}
#line 1989 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 77: /* expr ::= objprop LSHIFT_ASSIGN expr */
#line 317 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_lshift);
}
#line 1997 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 78: /* expr ::= objprop RSHIFT_ASSIGN expr */
#line 321 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_rshift);
}
#line 2005 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 79: /* expr ::= objprop URSHIFT_ASSIGN expr */
#line 325 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_urshift);
}
#line 2013 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 80: /* expr ::= objprop AND_ASSIGN expr */
#line 329 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_and);
}
#line 2021 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 81: /* expr ::= objprop XOR_ASSIGN expr */
#line 333 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_xor);
}
#line 2029 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 82: /* expr ::= objprop OR_ASSIGN expr */
#line 337 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_objprop_assign(ctx, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, MJS_OP_or);
}
#line 2037 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 83: /* cstmt ::= IF OPEN_PAREN expr CLOSE_PAREN block_or_stmt */
#line 342 "mjs/mjs.lem.c"
{
  yymsp[-4].minor.yy8=mjs_emit_call(ctx, yymsp[-2].minor.yy8);
  mjs_emit_quote(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_ifstmt);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2048 "mjs/mjs.lem.c"
        break;
      case 84: /* cstmt ::= IF OPEN_PAREN expr CLOSE_PAREN block_or_stmt ELSE block_or_stmt */
#line 348 "mjs/mjs.lem.c"
{
  yymsp[-6].minor.yy8=mjs_emit_call(ctx, yymsp[-4].minor.yy8);
  mjs_emit_quote(ctx, yymsp[-2].minor.yy8);
  mjs_emit_quote(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_ifelse);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2059 "mjs/mjs.lem.c"
        break;
      case 85: /* cstmt ::= WHILE OPEN_PAREN expr CLOSE_PAREN block_or_stmt */
#line 355 "mjs/mjs.lem.c"
{
  yymsp[-4].minor.yy8=mjs_emit_quote(ctx, yymsp[0].minor.yy8);
  mjs_emit_quote(ctx, yymsp[-2].minor.yy8);
  mjs_emit(ctx, MJS_OP_while);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2069 "mjs/mjs.lem.c"
        break;
      case 86: /* block ::= OPEN_CURLY stmtlist CLOSE_CURLY */
#line 367 "mjs/mjs.lem.c"
{
  yymsp[-2].minor.yy8=mjs_emit(ctx, MJS_OP_blockenter);
  mjs_emit_call(ctx, yymsp[-1].minor.yy8);
  mjs_emit(ctx, MJS_OP_blockexit);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2079 "mjs/mjs.lem.c"
        break;
      case 87: /* funcdecl ::= FUNCTION IDENTIFIER arglistparen OPEN_CURLY stmtlist CLOSE_CURLY */
#line 383 "mjs/mjs.lem.c"
{
  bf_word_ptr_t f = mjs_emit_func(ctx, yymsp[-3].minor.yy8, yymsp[-1].minor.yy8);
  yymsp[-5].minor.yy8 = mjs_emit_str_or_ident(ctx, yymsp[-4].minor.yy0.begin);
  mjs_emit(ctx, MJS_OP_dup);
  mjs_emit(ctx, MJS_OP_createvar);
  mjs_emit_call(ctx, f);
  mjs_emit(ctx, MJS_OP_setvar);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2092 "mjs/mjs.lem.c"
        break;
      case 88: /* func_literal ::= FUNCTION arglistparen OPEN_CURLY stmtlist CLOSE_CURLY */
#line 395 "mjs/mjs.lem.c"
{
  yymsp[-4].minor.yy8=mjs_emit_func(ctx, yymsp[-3].minor.yy8, yymsp[-1].minor.yy8);
}
#line 2099 "mjs/mjs.lem.c"
        break;
      case 89: /* arglist ::= */
#line 402 "mjs/mjs.lem.c"
{
  /*
   * mjs_emit_func() will check if arguments pointer is an invalid word ptr,
   * and if so, will skip calling the word generated by `argspec`s.
   */
  yymsp[1].minor.yy8 = BF_INVALID_WORD_PTR;
}
#line 2110 "mjs/mjs.lem.c"
        break;
      case 90: /* argspec ::= IDENTIFIER */
#line 409 "mjs/mjs.lem.c"
{
  /*
   * emit `"varname" setarg`
   * NOTE: do not emit `exit`, it'll be emitted by arglistparen, after
   * all `setarg`s.
   */
  yylhsminor.yy8=mjs_emit_str_or_ident(ctx, yymsp[0].minor.yy0.begin);
  mjs_emit(ctx, MJS_OP_setarg);
}
#line 2123 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 91: /* arglistparen ::= OPEN_PAREN arglist CLOSE_PAREN */
#line 419 "mjs/mjs.lem.c"
{
  /* will return the beginning of the arglist */
  yymsp[-2].minor.yy8 = yymsp[-1].minor.yy8;
  if (yymsp[-1].minor.yy8 != BF_INVALID_WORD_PTR) {
    /* terminate `"foo" setarg "bar" setarg` with an exit */
    mjs_emit(ctx, MJS_OP_exit);
  }
}
#line 2136 "mjs/mjs.lem.c"
        break;
      case 92: /* sstmt ::= RETURN */
#line 428 "mjs/mjs.lem.c"
{
  yymsp[0].minor.yy8=mjs_emit(ctx, MJS_OP_undefined);
  mjs_emit(ctx, MJS_OP_jsexit);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2145 "mjs/mjs.lem.c"
        break;
      case 93: /* sstmt ::= RETURN expr */
#line 433 "mjs/mjs.lem.c"
{
  yymsp[-1].minor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_jsexit);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2154 "mjs/mjs.lem.c"
        break;
      case 94: /* literal ::= NULL */
#line 440 "mjs/mjs.lem.c"
{
  yymsp[0].minor.yy8=mjs_emit(ctx, MJS_OP_null);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2162 "mjs/mjs.lem.c"
        break;
      case 95: /* literal ::= UNDEFINED */
#line 444 "mjs/mjs.lem.c"
{
  yymsp[0].minor.yy8=mjs_emit(ctx, MJS_OP_undefined);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2170 "mjs/mjs.lem.c"
        break;
      case 96: /* literal ::= THIS */
#line 448 "mjs/mjs.lem.c"
{
  yymsp[0].minor.yy8=mjs_emit(ctx, MJS_OP_this_val_AT);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2178 "mjs/mjs.lem.c"
        break;
      case 97: /* literal ::= NUMBER */
#line 452 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_num(ctx, yymsp[0].minor.yy0.begin); }
#line 2183 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 98: /* literal ::= STRING_LITERAL */
#line 453 "mjs/mjs.lem.c"
{ yylhsminor.yy8=mjs_emit_str(ctx, yymsp[0].minor.yy0.begin); }
#line 2189 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 99: /* boolean_literal ::= TRUE */
#line 459 "mjs/mjs.lem.c"
{
  yymsp[0].minor.yy8=mjs_emit(ctx, MJS_OP_true);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2198 "mjs/mjs.lem.c"
        break;
      case 100: /* boolean_literal ::= FALSE */
#line 463 "mjs/mjs.lem.c"
{
  yymsp[0].minor.yy8=mjs_emit(ctx, MJS_OP_false);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2206 "mjs/mjs.lem.c"
        break;
      case 102: /* objspeclist ::= objspeclist COMMA objspec */
      case 108: /* arrayspeclist ::= arrayspeclist COMMA arrspec */ yytestcase(yyruleno==108);
#line 470 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_call(ctx, yymsp[-2].minor.yy8);
  mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2216 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 103: /* objspeclist ::= objspeclist COMMA */
#line 475 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=yymsp[-1].minor.yy8;
}
#line 2224 "mjs/mjs.lem.c"
  yymsp[-1].minor.yy8 = yylhsminor.yy8;
        break;
      case 104: /* objspeclist ::= objspec */
#line 478 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit(ctx, MJS_OP_mkobj);
  mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2234 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 105: /* objspeclist ::= */
#line 483 "mjs/mjs.lem.c"
{
  yymsp[1].minor.yy8=mjs_emit(ctx, MJS_OP_mkobj);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2243 "mjs/mjs.lem.c"
        break;
      case 106: /* objspec ::= objspeclhs COLON expr */
#line 488 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_str_or_ident(ctx, yymsp[-2].minor.yy172);
  mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_addprop);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2253 "mjs/mjs.lem.c"
  yymsp[-2].minor.yy8 = yylhsminor.yy8;
        break;
      case 109: /* arrayspeclist ::= arrspec */
#line 504 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit(ctx, MJS_OP_mkarr);
  mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2263 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      case 110: /* arrayspeclist ::= */
#line 509 "mjs/mjs.lem.c"
{
  yymsp[1].minor.yy8=mjs_emit(ctx, MJS_OP_mkarr);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2272 "mjs/mjs.lem.c"
        break;
      case 111: /* arrspec ::= expr */
#line 514 "mjs/mjs.lem.c"
{
  yylhsminor.yy8=mjs_emit_call(ctx, yymsp[0].minor.yy8);
  mjs_emit(ctx, MJS_OP_arrpush);
  mjs_emit(ctx, MJS_OP_exit);
}
#line 2281 "mjs/mjs.lem.c"
  yymsp[0].minor.yy8 = yylhsminor.yy8;
        break;
      default:
      /* (112) stmtlist ::= cstmtlist */ yytestcase(yyruleno==112);
      /* (113) stmtlist ::= sstmtlist */ yytestcase(yyruleno==113);
      /* (114) letspecs ::= letspecs COMMA letspec */ yytestcase(yyruleno==114);
      /* (115) letspecs ::= letspec (OPTIMIZED OUT) */ assert(yyruleno!=115);
      /* (116) sstmt ::= expr */ yytestcase(yyruleno==116);
      /* (117) expr ::= sexp */ yytestcase(yyruleno==117);
      /* (118) expr ::= expr EQ_EQ expr */ yytestcase(yyruleno==118);
      /* (119) expr ::= expr NE_NE expr */ yytestcase(yyruleno==119);
      /* (120) sexp ::= literal (OPTIMIZED OUT) */ assert(yyruleno!=120);
      /* (121) callarg ::= expr */ yytestcase(yyruleno==121);
      /* (122) cstmt ::= FOR OPEN_PAREN optexpr SEMICOLON optexpr SEMICOLON optexpr CLOSE_PAREN block_or_stmt */ yytestcase(yyruleno==122);
      /* (123) optexpr ::= */ yytestcase(yyruleno==123);
      /* (124) optexpr ::= expr */ yytestcase(yyruleno==124);
      /* (125) block_or_stmt ::= block (OPTIMIZED OUT) */ assert(yyruleno!=125);
      /* (126) block_or_stmt ::= sstmt SEMICOLON */ yytestcase(yyruleno==126);
      /* (127) block_or_stmt ::= cstmt (OPTIMIZED OUT) */ assert(yyruleno!=127);
      /* (128) cstmt ::= funcdecl (OPTIMIZED OUT) */ assert(yyruleno!=128);
      /* (129) arglist ::= arglist COMMA argspec */ yytestcase(yyruleno==129);
      /* (130) arglist ::= argspec (OPTIMIZED OUT) */ assert(yyruleno!=130);
      /* (131) literal ::= boolean_literal (OPTIMIZED OUT) */ assert(yyruleno!=131);
      /* (132) literal ::= func_literal (OPTIMIZED OUT) */ assert(yyruleno!=132);
      /* (133) literal ::= object_literal (OPTIMIZED OUT) */ assert(yyruleno!=133);
      /* (134) literal ::= array_literal (OPTIMIZED OUT) */ assert(yyruleno!=134);
      /* (135) objspeclhs ::= IDENTIFIER */ yytestcase(yyruleno==135);
      /* (136) objspeclhs ::= STRING_LITERAL */ yytestcase(yyruleno==136);
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

#line 2352 "mjs/mjs.lem.c"
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
#line 2373 "mjs/mjs.lem.c"
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

#line 2399 "mjs/mjs.lem.c"
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
  /* 0016 -> : scope_idx@ ... ; */
  /*           <mjs_op_scope_idx_get> */ 
  /* 0016 -> : scope_idx! ... ; */
  /*           <mjs_op_scope_idx_set> */ 
  /* 0016 -> : scope_min@ ... ; */
  /*           <mjs_op_scope_min_get> */ 
  /* 0016 -> : scope_min! ... ; */
  /*           <mjs_op_scope_min_set> */ 
  /* 0016 -> : this_val@ ... ; */
  /*           <mjs_op_this_val_get> */ 
  /* 0016 -> : this_val! ... ; */
  /*           <mjs_op_this_val_set> */ 
  /* 0016 -> : frame@ ... ; */
  /*           <mjs_op_getframe> */ 
  /* 0016 -> : frame! ... ; */
  /*           <mjs_op_setframe> */ 
  /* 0016 -> : >scopes ... ; */
  /*           <mjs_op_scope_push> */ 
  /* 0016 -> : scopes> ... ; */
  /*           <mjs_op_scope_pop> */ 
  /* 0016 -> : scope@ ... ; */
  /*           <mjs_op_scope_tos> */ 
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
  /* 0024 -> : createvar ... ; */
  /*           <mjs_op_createvar> */ 
  /* 0024 -> : mkarr ... ; */
  /*           <mjs_op_mkarr> */ 
  /* 0024 -> : arrpush ... ; */
  /*           <mjs_op_arrpush> */ 
  /* 0024 -> : blockenter ... ; */
  MJS_OP_mkobj, MJS_OP_GT_scopes, MJS_OP_exit,
  /* 0027 -> : blockexit ... ; */
  MJS_OP_scopes_GT, MJS_OP_drop, MJS_OP_exit,
  /* 0030 -> : jscall ... ; */
  /*           <mjs_op_jscall> */ 
  /* 0030 -> : jscall_exit ... ; */
  MJS_OP_tmp_SET, MJS_OP_r_GT, MJS_OP_sp_SET, MJS_OP_r_GT, MJS_OP_this_val_SET, MJS_OP_tmp_AT, MJS_OP_exit,
  /* 0037 -> : jscall_wrap ... ; */
  MJS_OP_jscall, MJS_OP_exit,
  /* 0039 -> : jsenter ... ; */
  MJS_OP_r_GT, MJS_OP_tmp_SET, MJS_OP_scope_min_AT, MJS_OP_GT_r, MJS_OP_frame_AT, MJS_OP_GT_r, MJS_OP_rp_AT, MJS_OP_frame_SET, MJS_OP_scope_idx_AT, MJS_OP_scope_min_SET, MJS_OP_mkobj, MJS_OP_dup, MJS_OP_GT_scopes, MJS_OP_tmp_AT, MJS_OP_GT_r, MJS_OP_exit,
  /* 0055 -> : jsexit ... ; */
  MJS_OP_frame_AT, MJS_OP_rp_SET, MJS_OP_scope_min_AT, MJS_OP_scope_idx_SET, MJS_OP_r_GT, MJS_OP_frame_SET, MJS_OP_r_GT, MJS_OP_scope_min_SET, MJS_OP_exit,
  /* 0064 -> : anon_0 ... ; */
  MJS_OP_undefined, MJS_OP_exit,
  /* 0066 -> : anon_1 ... ; */
  MJS_OP_rot, MJS_OP_exit,
  /* 0068 -> : setarg ... ; */
  MJS_OP_rot, MJS_OP_one, MJS_OP_MINUS, MJS_OP_dup, MJS_OP_GT_r, MJS_OP_quote, 0, 0, MJS_OP_LT, MJS_OP_quote, 0, 64, MJS_OP_quote, 0, 66, MJS_OP_ifelse, MJS_OP_addprop, MJS_OP_r_GT, MJS_OP_swap, MJS_OP_exit,
  /* 0088 -> : ffi ... ; */
  MJS_OP_drop, MJS_OP_exit,
  /* 0090 -> : undefined ... ; */
  /*           <mjs_op_undefined> */ 
  /* 0090 -> : null ... ; */
  /*           <mjs_op_null> */ 
  /* 0090 -> : true ... ; */
  /*           <mjs_op_true> */ 
  /* 0090 -> : false ... ; */
  /*           <mjs_op_false> */ 
  /* 0090 -> : this_for_call ... ; */
  /*           <mjs_op_this_for_call> */ 
  /* 0090 -> : 2dup ... ; */
  MJS_OP_over, MJS_OP_over, MJS_OP_exit,
  /* 0093 -> : dec ... ; */
  MJS_OP_quote, -1, -1, MJS_OP_PLUS, MJS_OP_exit,
  /* 0098 -> : >= ... ; */
  MJS_OP_LT, MJS_OP_invert, MJS_OP_exit,
  /* 0101 -> : <= ... ; */
  MJS_OP_GT, MJS_OP_invert, MJS_OP_exit,
  /* 0104 -> : != ... ; */
  MJS_OP_EQ, MJS_OP_invert, MJS_OP_exit,
  /* 0107 -> : js= ... ; */
  /*           <mjs_op_eq> */ 
  /* 0107 -> : js< ... ; */
  /*           <mjs_op_lt> */ 
  /* 0107 -> : js> ... ; */
  /*           <mjs_op_gt> */ 
  /* 0107 -> : jsinvert ... ; */
  /*           <mjs_op_invert> */ 
  /* 0107 -> : js>= ... ; */
  MJS_OP_js_LT, MJS_OP_jsinvert, MJS_OP_exit,
  /* 0110 -> : js<= ... ; */
  MJS_OP_js_GT, MJS_OP_jsinvert, MJS_OP_exit,
  /* 0113 -> : js!= ... ; */
  MJS_OP_js_EQ, MJS_OP_jsinvert, MJS_OP_exit,
  /* 0116 -> : js_logical_and ... ; */
  /*           <mjs_op_logical_and> */ 
  /* 0116 -> : js_logical_or ... ; */
  /*           <mjs_op_logical_or> */ 
  /* 0116 -> : anon_2 ... ; */
  MJS_OP_undefined, MJS_OP_exit,
  /* 0118 -> : ifstmt ... ; */
  MJS_OP_quote, 0, 116, MJS_OP_ifelse, MJS_OP_exit,
  /* 0123 -> : anon_3 ... ; */
  MJS_OP_2dup, MJS_OP_GT_r, MJS_OP_GT_r, MJS_OP_call, MJS_OP_r_GT, MJS_OP_r_GT, MJS_OP_swap, -37, MJS_OP_dup, MJS_OP_quote, 0, 0, MJS_OP_GTEQ, MJS_OP_GT_r, MJS_OP_swap, MJS_OP_r_GT, MJS_OP_exit,
  /* 0140 -> : anon_4 ... ; */
  -47, MJS_OP_swap, MJS_OP_quote, 0, 123, MJS_OP_loop, MJS_OP_exit,
  /* 0147 -> : repeat ... ; */
  MJS_OP_swap, MJS_OP_dup, MJS_OP_quote, 0, 0, MJS_OP_GT, MJS_OP_quote, 0, -116, MJS_OP_if, MJS_OP_drop, MJS_OP_drop, MJS_OP_exit,
  /* 0160 -> : anon_5 ... ; */
  MJS_OP_call, MJS_OP_drop, MJS_OP_quote, 0, 1, MJS_OP_exit,
  /* 0166 -> : anon_6 ... ; */
  MJS_OP_drop, MJS_OP_drop, MJS_OP_drop, MJS_OP_zero, MJS_OP_exit,
  /* 0171 -> : anon_7 ... ; */
  MJS_OP_2dup, MJS_OP_call, MJS_OP_quote, 0, -96, MJS_OP_quote, 0, -90, MJS_OP_ifelse, MJS_OP_exit,
  /* 0181 -> : while ... ; */
  MJS_OP_quote, 0, -85, MJS_OP_loop, MJS_OP_undefined, MJS_OP_exit,
  /* 0187 -> : anon_8 ... ; */
  MJS_OP_str, /* " " */  ' ', 0, MJS_OP_print, MJS_OP_exit,
  /* 0192 -> : anon_9 ... ; */
  MJS_OP_swap, MJS_OP_print, MJS_OP_quote, 0, 0, MJS_OP_EQ, MJS_OP_invert, MJS_OP_quote, 0, -69, MJS_OP_if, MJS_OP_exit,
  /* 0204 -> : jsprint ... ; */
  MJS_OP_quote, 0, -64, MJS_OP_repeat, MJS_OP_cr, MJS_OP_undefined, MJS_OP_exit,
  /* 0211 -> : zero ... ; */
  MJS_OP_quote, 0, 0, MJS_OP_exit,
  /* 0215 -> : one ... ; */
  MJS_OP_quote, 0, 1, MJS_OP_exit,
  /* 0219 -> : nop ... ; */
  MJS_OP_zero, MJS_OP_drop, MJS_OP_exit,
  /* 0222 -> : inc ... ; */
  MJS_OP_quote, 0, 1, MJS_OP_PLUS, MJS_OP_exit,
  /* 0227 -> : swapinc ... ; */
  MJS_OP_swap, MJS_OP_inc, MJS_OP_exit,
  /* 0230 -> : div ... ; */
  /*           <mjs_op_div> */ 
  /* 0230 -> : rem ... ; */
  /*           <mjs_op_rem> */ 
  /* 0230 -> : lshift ... ; */
  /*           <mjs_op_lshift> */ 
  /* 0230 -> : rshift ... ; */
  /*           <mjs_op_rshift> */ 
  /* 0230 -> : urshift ... ; */
  /*           <mjs_op_urshift> */ 
  /* 0230 -> : and ... ; */
  /*           <mjs_op_and> */ 
  /* 0230 -> : or ... ; */
  /*           <mjs_op_or> */ 
  /* 0230 -> : xor ... ; */
  /*           <mjs_op_xor> */ 
  /* 0230 -> : not ... ; */
  /*           <mjs_op_not> */ 
  /* 0230 -> : neg ... ; */
  /*           <mjs_op_neg> */ 
  /* 0230 -> : pos ... ; */
  /*           <mjs_op_pos> */ 
  /* 0230 -> : load ... ; */
  /*           <mjs_op_load> */ 
}; /* 230 * sizeof(bf_opcode_t) */

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
  /* 0036 */ -36, 
  /* 0037 */ -37, 
  /* 0038 */ -38, 
  /* 0039 */ -39, 
  /* 0040 */ -40, 
  /* 0041 */ -41, 
  /* 0042 */ -42, 
  /* 0043 */ 16, 
  /* 0044 */ -43, 
  /* 0045 */ -44, 
  /* 0046 */ -45, 
  /* 0047 */ -46, 
  /* 0048 */ -47, 
  /* 0049 */ -48, 
  /* 0050 */ -49, 
  /* 0051 */ 24, 
  /* 0052 */ 27, 
  /* 0053 */ -50, 
  /* 0054 */ 30, 
  /* 0055 */ 37, 
  /* 0056 */ 39, 
  /* 0057 */ 55, 
  /* 0058 */ 68, 
  /* 0059 */ -51, 
  /* 0060 */ -52, 
  /* 0061 */ -53, 
  /* 0062 */ -54, 
  /* 0063 */ -55, 
  /* 0064 */ 90, 
  /* 0065 */ 98, 
  /* 0066 */ 101, 
  /* 0067 */ 104, 
  /* 0068 */ -56, 
  /* 0069 */ -57, 
  /* 0070 */ -58, 
  /* 0071 */ -59, 
  /* 0072 */ 107, 
  /* 0073 */ 110, 
  /* 0074 */ 113, 
  /* 0075 */ -60, 
  /* 0076 */ -61, 
  /* 0077 */ 118, 
  /* 0078 */ 147, 
  /* 0079 */ 181, 
  /* 0080 */ 204, 
  /* 0081 */ 211, 
  /* 0082 */ 215, 
  /* 0083 */ 219, 
  /* 0084 */ 222, 
  /* 0085 */ 227, 
  /* 0086 */ -62, 
  /* 0087 */ -63, 
  /* 0088 */ -64, 
  /* 0089 */ -65, 
  /* 0090 */ -66, 
  /* 0091 */ -67, 
  /* 0092 */ -68, 
  /* 0093 */ -69, 
  /* 0094 */ -70, 
  /* 0095 */ -71, 
  /* 0096 */ -72, 
  /* 0097 */ -73, 
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
void mjs_op_scope_idx_get(struct bf_vm *vm);
void mjs_op_scope_idx_set(struct bf_vm *vm);
void mjs_op_scope_min_get(struct bf_vm *vm);
void mjs_op_scope_min_set(struct bf_vm *vm);
void mjs_op_this_val_get(struct bf_vm *vm);
void mjs_op_this_val_set(struct bf_vm *vm);
void mjs_op_getframe(struct bf_vm *vm);
void mjs_op_setframe(struct bf_vm *vm);
void mjs_op_scope_push(struct bf_vm *vm);
void mjs_op_scope_pop(struct bf_vm *vm);
void mjs_op_scope_tos(struct bf_vm *vm);
void mjs_op_mkobj(struct bf_vm *vm);
void mjs_op_setprop(struct bf_vm *vm);
void mjs_op_getprop(struct bf_vm *vm);
void mjs_op_getvar(struct bf_vm *vm);
void mjs_op_setvar(struct bf_vm *vm);
void mjs_op_createvar(struct bf_vm *vm);
void mjs_op_mkarr(struct bf_vm *vm);
void mjs_op_arrpush(struct bf_vm *vm);
void mjs_op_jscall(struct bf_vm *vm);
void mjs_op_undefined(struct bf_vm *vm);
void mjs_op_null(struct bf_vm *vm);
void mjs_op_true(struct bf_vm *vm);
void mjs_op_false(struct bf_vm *vm);
void mjs_op_this_for_call(struct bf_vm *vm);
void mjs_op_eq(struct bf_vm *vm);
void mjs_op_lt(struct bf_vm *vm);
void mjs_op_gt(struct bf_vm *vm);
void mjs_op_invert(struct bf_vm *vm);
void mjs_op_logical_and(struct bf_vm *vm);
void mjs_op_logical_or(struct bf_vm *vm);
void mjs_op_div(struct bf_vm *vm);
void mjs_op_rem(struct bf_vm *vm);
void mjs_op_lshift(struct bf_vm *vm);
void mjs_op_rshift(struct bf_vm *vm);
void mjs_op_urshift(struct bf_vm *vm);
void mjs_op_and(struct bf_vm *vm);
void mjs_op_or(struct bf_vm *vm);
void mjs_op_xor(struct bf_vm *vm);
void mjs_op_not(struct bf_vm *vm);
void mjs_op_neg(struct bf_vm *vm);
void mjs_op_pos(struct bf_vm *vm);
void mjs_op_load(struct bf_vm *vm);

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
  /* -031 */ mjs_op_scope_idx_get,
  /* -032 */ mjs_op_scope_idx_set,
  /* -033 */ mjs_op_scope_min_get,
  /* -034 */ mjs_op_scope_min_set,
  /* -035 */ mjs_op_this_val_get,
  /* -036 */ mjs_op_this_val_set,
  /* -037 */ mjs_op_getframe,
  /* -038 */ mjs_op_setframe,
  /* -039 */ mjs_op_scope_push,
  /* -040 */ mjs_op_scope_pop,
  /* -041 */ mjs_op_scope_tos,
  /* -042 */ mjs_op_mkobj,
  /* -043 */ mjs_op_setprop,
  /* -044 */ mjs_op_getprop,
  /* -045 */ mjs_op_getvar,
  /* -046 */ mjs_op_setvar,
  /* -047 */ mjs_op_createvar,
  /* -048 */ mjs_op_mkarr,
  /* -049 */ mjs_op_arrpush,
  /* -050 */ mjs_op_jscall,
  /* -051 */ mjs_op_undefined,
  /* -052 */ mjs_op_null,
  /* -053 */ mjs_op_true,
  /* -054 */ mjs_op_false,
  /* -055 */ mjs_op_this_for_call,
  /* -056 */ mjs_op_eq,
  /* -057 */ mjs_op_lt,
  /* -058 */ mjs_op_gt,
  /* -059 */ mjs_op_invert,
  /* -060 */ mjs_op_logical_and,
  /* -061 */ mjs_op_logical_or,
  /* -062 */ mjs_op_div,
  /* -063 */ mjs_op_rem,
  /* -064 */ mjs_op_lshift,
  /* -065 */ mjs_op_rshift,
  /* -066 */ mjs_op_urshift,
  /* -067 */ mjs_op_and,
  /* -068 */ mjs_op_or,
  /* -069 */ mjs_op_xor,
  /* -070 */ mjs_op_not,
  /* -071 */ mjs_op_neg,
  /* -072 */ mjs_op_pos,
  /* -073 */ mjs_op_load,
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
  /* 0031 */ "scope_idx@", 
  /* 0032 */ "scope_idx!", 
  /* 0033 */ "scope_min@", 
  /* 0034 */ "scope_min!", 
  /* 0035 */ "this_val@", 
  /* 0036 */ "this_val!", 
  /* 0037 */ "frame@", 
  /* 0038 */ "frame!", 
  /* 0039 */ ">scopes", 
  /* 0040 */ "scopes>", 
  /* 0041 */ "scope@", 
  /* 0042 */ "mkobj", 
  /* 0043 */ "addprop", 
  /* 0044 */ "setprop", 
  /* 0045 */ "getprop", 
  /* 0046 */ "getvar", 
  /* 0047 */ "setvar", 
  /* 0048 */ "createvar", 
  /* 0049 */ "mkarr", 
  /* 0050 */ "arrpush", 
  /* 0051 */ "blockenter", 
  /* 0052 */ "blockexit", 
  /* 0053 */ "jscall", 
  /* 0054 */ "jscall_exit", 
  /* 0055 */ "jscall_wrap", 
  /* 0056 */ "jsenter", 
  /* 0057 */ "jsexit", 
  /* 0058 */ "setarg", 
  /* 0059 */ "undefined", 
  /* 0060 */ "null", 
  /* 0061 */ "true", 
  /* 0062 */ "false", 
  /* 0063 */ "this_for_call", 
  /* 0064 */ "2dup", 
  /* 0065 */ ">=", 
  /* 0066 */ "<=", 
  /* 0067 */ "!=", 
  /* 0068 */ "js=", 
  /* 0069 */ "js<", 
  /* 0070 */ "js>", 
  /* 0071 */ "jsinvert", 
  /* 0072 */ "js>=", 
  /* 0073 */ "js<=", 
  /* 0074 */ "js!=", 
  /* 0075 */ "js_logical_and", 
  /* 0076 */ "js_logical_or", 
  /* 0077 */ "ifstmt", 
  /* 0078 */ "repeat", 
  /* 0079 */ "while", 
  /* 0080 */ "jsprint", 
  /* 0081 */ "zero", 
  /* 0082 */ "one", 
  /* 0083 */ "nop", 
  /* 0084 */ "inc", 
  /* 0085 */ "swapinc", 
  /* 0086 */ "div", 
  /* 0087 */ "rem", 
  /* 0088 */ "lshift", 
  /* 0089 */ "rshift", 
  /* 0090 */ "urshift", 
  /* 0091 */ "and", 
  /* 0092 */ "or", 
  /* 0093 */ "xor", 
  /* 0094 */ "not", 
  /* 0095 */ "neg", 
  /* 0096 */ "pos", 
  /* 0097 */ "load", 
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
  "blockenter", 
  "blockenter+1", 
  "blockenter+2", 
  "blockexit", 
  "blockexit+1", 
  "blockexit+2", 
  "jscall_exit", 
  "jscall_exit+1", 
  "jscall_exit+2", 
  "jscall_exit+3", 
  "jscall_exit+4", 
  "jscall_exit+5", 
  "jscall_exit+6", 
  "jscall_wrap", 
  "jscall_wrap+1", 
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
  "jsenter+14", 
  "jsenter+15", 
  "jsexit", 
  "jsexit+1", 
  "jsexit+2", 
  "jsexit+3", 
  "jsexit+4", 
  "jsexit+5", 
  "jsexit+6", 
  "jsexit+7", 
  "jsexit+8", 
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
  "js>=", 
  "js>=+1", 
  "js>=+2", 
  "js<=", 
  "js<=+1", 
  "js<=+2", 
  "js!=", 
  "js!=+1", 
  "js!=+2", 
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
#line 1 "frozen/frozen.c"
#endif
/*
 * Copyright (c) 2004-2013 Sergey Lyubka <valenok@gmail.com>
 * Copyright (c) 2013 Cesanta Software Limited
 * All rights reserved
 *
 * This library is dual-licensed: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. For the terms of this
 * license, see <http: *www.gnu.org/licenses/>.
 *
 * You are free to use this library under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * Alternatively, you can license this library under a commercial
 * license, as set out in <http://cesanta.com/products.html>.
 */

#define _CRT_SECURE_NO_WARNINGS /* Disable deprecation warning in VS2005+ */

/* Amalgamated: #include "frozen.h" */
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(WEAK)
#if (defined(__GNUC__) || defined(__TI_COMPILER_VERSION__)) && !defined(_WIN32)
#define WEAK __attribute__((weak))
#else
#define WEAK
#endif
#endif

#ifdef _WIN32
#define snprintf cs_win_snprintf
#define vsnprintf cs_win_vsnprintf
int cs_win_snprintf(char *str, size_t size, const char *format, ...);
int cs_win_vsnprintf(char *str, size_t size, const char *format, va_list ap);
#if _MSC_VER >= 1700
#include <stdint.h>
#else
typedef _int64 int64_t;
typedef unsigned _int64 uint64_t;
#endif
#define PRId64 "I64d"
#define PRIu64 "I64u"
#if !defined(SIZE_T_FMT)
#if _MSC_VER >= 1310
#define SIZE_T_FMT "Iu"
#else
#define SIZE_T_FMT "u"
#endif
#endif
#else /* _WIN32 */
/* <inttypes.h> wants this for C++ */
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>
#if !defined(SIZE_T_FMT)
#define SIZE_T_FMT "zu"
#endif
#endif /* _WIN32 */

#define INT64_FMT PRId64
#define UINT64_FMT PRIu64

#ifndef va_copy
#define va_copy(x, y) x = y
#endif

#ifndef JSON_MAX_PATH_LEN
#define JSON_MAX_PATH_LEN 60
#endif

struct frozen {
  const char *end;
  const char *cur;

  const char *cur_name;
  size_t cur_name_len;

  /* For callback API */
  char path[JSON_MAX_PATH_LEN];
  int path_len;
  void *callback_data;
  json_walk_callback_t callback;
};

struct fstate {
  const char *ptr;
  int path_len;
};

#define SET_STATE(fr, ptr, str, len)              \
  struct fstate fstate = {(ptr), (fr)->path_len}; \
  append_to_path((fr), (str), (len));

#define CALL_BACK(fr, tok, value, len)                                        \
  do {                                                                        \
    if ((fr)->callback &&                                                     \
        ((fr)->path_len == 0 || (fr)->path[(fr)->path_len - 1] != '.')) {     \
      struct json_token t = {(value), (len), (tok)};                          \
                                                                              \
      /* Call the callback with the given value and current name */           \
      (fr)->callback((fr)->callback_data, (fr)->cur_name, (fr)->cur_name_len, \
                     (fr)->path, &t);                                         \
                                                                              \
      /* Reset the name */                                                    \
      (fr)->cur_name = NULL;                                                  \
      (fr)->cur_name_len = 0;                                                 \
    }                                                                         \
  } while (0)

static int append_to_path(struct frozen *f, const char *str, int size) {
  int n = f->path_len;
  f->path_len +=
      snprintf(f->path + f->path_len, sizeof(f->path) - (f->path_len + 1),
               "%.*s", size, str);

  return n;
}

static void truncate_path(struct frozen *f, int len) {
  f->path_len = len;
  f->path[len] = '\0';
}

static int parse_object(struct frozen *f);
static int parse_value(struct frozen *f);

#define EXPECT(cond, err_code)      \
  do {                              \
    if (!(cond)) return (err_code); \
  } while (0)

#define TRY(expr)          \
  do {                     \
    int _n = expr;         \
    if (_n < 0) return _n; \
  } while (0)

#define END_OF_STRING (-1)

static int left(const struct frozen *f) {
  return f->end - f->cur;
}

static int is_space(int ch) {
  return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

static void skip_whitespaces(struct frozen *f) {
  while (f->cur < f->end && is_space(*f->cur)) f->cur++;
}

static int cur(struct frozen *f) {
  skip_whitespaces(f);
  return f->cur >= f->end ? END_OF_STRING : *(unsigned char *) f->cur;
}

static int test_and_skip(struct frozen *f, int expected) {
  int ch = cur(f);
  if (ch == expected) {
    f->cur++;
    return 0;
  }
  return ch == END_OF_STRING ? JSON_STRING_INCOMPLETE : JSON_STRING_INVALID;
}

static int is_alpha(int ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

static int is_digit(int ch) {
  return ch >= '0' && ch <= '9';
}

static int is_hex_digit(int ch) {
  return is_digit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

static int get_escape_len(const char *s, int len) {
  switch (*s) {
    case 'u':
      return len < 6 ? JSON_STRING_INCOMPLETE
                     : is_hex_digit(s[1]) && is_hex_digit(s[2]) &&
                               is_hex_digit(s[3]) && is_hex_digit(s[4])
                           ? 5
                           : JSON_STRING_INVALID;
    case '"':
    case '\\':
    case '/':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
      return len < 2 ? JSON_STRING_INCOMPLETE : 1;
    default:
      return JSON_STRING_INVALID;
  }
}

/* identifier = letter { letter | digit | '_' } */
static int parse_identifier(struct frozen *f) {
  EXPECT(is_alpha(cur(f)), JSON_STRING_INVALID);
  {
    SET_STATE(f, f->cur, "", 0);
    while (f->cur < f->end &&
           (*f->cur == '_' || is_alpha(*f->cur) || is_digit(*f->cur))) {
      f->cur++;
    }
    truncate_path(f, fstate.path_len);
    CALL_BACK(f, JSON_TYPE_STRING, fstate.ptr, f->cur - fstate.ptr);
  }
  return 0;
}

static int get_utf8_char_len(unsigned char ch) {
  if ((ch & 0x80) == 0) return 1;
  switch (ch & 0xf0) {
    case 0xf0:
      return 4;
    case 0xe0:
      return 3;
    default:
      return 2;
  }
}

/* string = '"' { quoted_printable_chars } '"' */
static int parse_string(struct frozen *f) {
  int n, ch = 0, len = 0;
  TRY(test_and_skip(f, '"'));
  {
    SET_STATE(f, f->cur, "", 0);
    for (; f->cur < f->end; f->cur += len) {
      ch = *(unsigned char *) f->cur;
      len = get_utf8_char_len((unsigned char) ch);
      EXPECT(ch >= 32 && len > 0, JSON_STRING_INVALID); /* No control chars */
      EXPECT(len < left(f), JSON_STRING_INCOMPLETE);
      if (ch == '\\') {
        EXPECT((n = get_escape_len(f->cur + 1, left(f))) > 0, n);
        len += n;
      } else if (ch == '"') {
        truncate_path(f, fstate.path_len);
        CALL_BACK(f, JSON_TYPE_STRING, fstate.ptr, f->cur - fstate.ptr);
        f->cur++;
        break;
      };
    }
  }
  return ch == '"' ? 0 : JSON_STRING_INCOMPLETE;
}

/* number = [ '-' ] digit+ [ '.' digit+ ] [ ['e'|'E'] ['+'|'-'] digit+ ] */
static int parse_number(struct frozen *f) {
  int ch = cur(f);
  SET_STATE(f, f->cur, "", 0);
  if (ch == '-') f->cur++;
  EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
  EXPECT(is_digit(f->cur[0]), JSON_STRING_INVALID);
  while (f->cur < f->end && is_digit(f->cur[0])) f->cur++;
  if (f->cur < f->end && f->cur[0] == '.') {
    f->cur++;
    EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
    EXPECT(is_digit(f->cur[0]), JSON_STRING_INVALID);
    while (f->cur < f->end && is_digit(f->cur[0])) f->cur++;
  }
  if (f->cur < f->end && (f->cur[0] == 'e' || f->cur[0] == 'E')) {
    f->cur++;
    EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
    if ((f->cur[0] == '+' || f->cur[0] == '-')) f->cur++;
    EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
    EXPECT(is_digit(f->cur[0]), JSON_STRING_INVALID);
    while (f->cur < f->end && is_digit(f->cur[0])) f->cur++;
  }
  truncate_path(f, fstate.path_len);
  CALL_BACK(f, JSON_TYPE_NUMBER, fstate.ptr, f->cur - fstate.ptr);
  return 0;
}

/* array = '[' [ value { ',' value } ] ']' */
static int parse_array(struct frozen *f) {
  int i = 0, current_path_len;
  char buf[20];
  TRY(test_and_skip(f, '['));
  {
    CALL_BACK(f, JSON_TYPE_ARRAY_START, NULL, 0);
    {
      SET_STATE(f, f->cur - 1, "", 0);
      while (cur(f) != ']') {
        snprintf(buf, sizeof(buf), "[%d]", i);
        i++;
        current_path_len = append_to_path(f, buf, strlen(buf));
        f->cur_name =
            f->path + strlen(f->path) - strlen(buf) + 1 /*opening brace*/;
        f->cur_name_len = strlen(buf) - 2 /*braces*/;
        TRY(parse_value(f));
        truncate_path(f, current_path_len);
        if (cur(f) == ',') f->cur++;
      }
      TRY(test_and_skip(f, ']'));
      truncate_path(f, fstate.path_len);
      CALL_BACK(f, JSON_TYPE_ARRAY_END, fstate.ptr, f->cur - fstate.ptr);
    }
  }
  return 0;
}

static int expect(struct frozen *f, const char *s, int len,
                  enum json_token_type tok_type) {
  int i, n = left(f);
  SET_STATE(f, f->cur, "", 0);
  for (i = 0; i < len; i++) {
    if (i >= n) return JSON_STRING_INCOMPLETE;
    if (f->cur[i] != s[i]) return JSON_STRING_INVALID;
  }
  f->cur += len;
  truncate_path(f, fstate.path_len);

  CALL_BACK(f, tok_type, fstate.ptr, f->cur - fstate.ptr);

  return 0;
}

/* value = 'null' | 'true' | 'false' | number | string | array | object */
static int parse_value(struct frozen *f) {
  int ch = cur(f);

  switch (ch) {
    case '"':
      TRY(parse_string(f));
      break;
    case '{':
      TRY(parse_object(f));
      break;
    case '[':
      TRY(parse_array(f));
      break;
    case 'n':
      TRY(expect(f, "null", 4, JSON_TYPE_NULL));
      break;
    case 't':
      TRY(expect(f, "true", 4, JSON_TYPE_TRUE));
      break;
    case 'f':
      TRY(expect(f, "false", 5, JSON_TYPE_FALSE));
      break;
    case '-':
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
      TRY(parse_number(f));
      break;
    default:
      return ch == END_OF_STRING ? JSON_STRING_INCOMPLETE : JSON_STRING_INVALID;
  }

  return 0;
}

/* key = identifier | string */
static int parse_key(struct frozen *f) {
  int ch = cur(f);
#if 0
  printf("%s [%.*s]\n", __func__, (int) (f->end - f->cur), f->cur);
#endif
  if (is_alpha(ch)) {
    TRY(parse_identifier(f));
  } else if (ch == '"') {
    TRY(parse_string(f));
  } else {
    return ch == END_OF_STRING ? JSON_STRING_INCOMPLETE : JSON_STRING_INVALID;
  }
  return 0;
}

/* pair = key ':' value */
static int parse_pair(struct frozen *f) {
  int current_path_len;
  const char *tok;
  skip_whitespaces(f);
  tok = f->cur;
  TRY(parse_key(f));
  {
    f->cur_name = *tok == '"' ? tok + 1 : tok;
    f->cur_name_len = *tok == '"' ? f->cur - tok - 2 : f->cur - tok;
    current_path_len = append_to_path(f, f->cur_name, f->cur_name_len);
  }
  TRY(test_and_skip(f, ':'));
  TRY(parse_value(f));
  truncate_path(f, current_path_len);
  return 0;
}

/* object = '{' pair { ',' pair } '}' */
static int parse_object(struct frozen *f) {
  TRY(test_and_skip(f, '{'));
  {
    CALL_BACK(f, JSON_TYPE_OBJECT_START, NULL, 0);
    {
      SET_STATE(f, f->cur - 1, ".", 1);
      while (cur(f) != '}') {
        TRY(parse_pair(f));
        if (cur(f) == ',') f->cur++;
      }
      TRY(test_and_skip(f, '}'));
      truncate_path(f, fstate.path_len);
      CALL_BACK(f, JSON_TYPE_OBJECT_END, fstate.ptr, f->cur - fstate.ptr);
    }
  }
  return 0;
}

static int doit(struct frozen *f) {
  if (f->cur == 0 || f->end < f->cur) return JSON_STRING_INVALID;
  if (f->end == f->cur) return JSON_STRING_INCOMPLETE;
  return parse_value(f);
}

static int json_encode_string(struct json_out *out, const char *p, size_t len) {
  size_t i, cl, n = 0;
  const char *hex_digits = "0123456789abcdef";
  const char *specials = "btnvfr";

  for (i = 0; i < len; i++) {
    unsigned char ch = ((unsigned char *) p)[i];
    if (ch == '"' || ch == '\\') {
      n += out->printer(out, "\\", 1);
      n += out->printer(out, p + i, 1);
    } else if (ch >= '\b' && ch <= '\r') {
      n += out->printer(out, "\\", 1);
      n += out->printer(out, &specials[ch - '\b'], 1);
    } else if (isprint(ch)) {
      n += out->printer(out, p + i, 1);
    } else if ((cl = get_utf8_char_len(ch)) == 1) {
      n += out->printer(out, "\\u00", 4);
      n += out->printer(out, &hex_digits[(ch >> 4) % 0xf], 1);
      n += out->printer(out, &hex_digits[ch % 0xf], 1);
    } else {
      n += out->printer(out, p + i, cl);
      i += cl - 1;
    }
  }

  return n;
}

int json_printer_buf(struct json_out *out, const char *buf, size_t len) WEAK;
int json_printer_buf(struct json_out *out, const char *buf, size_t len) {
  size_t avail = out->u.buf.size - out->u.buf.len;
  size_t n = len < avail ? len : avail;
  memcpy(out->u.buf.buf + out->u.buf.len, buf, n);
  out->u.buf.len += n;
  if (out->u.buf.size > 0) {
    size_t idx = out->u.buf.len;
    if (idx >= out->u.buf.size) idx = out->u.buf.size - 1;
    out->u.buf.buf[idx] = '\0';
  }
  return len;
}

int json_printer_file(struct json_out *out, const char *buf, size_t len) WEAK;
int json_printer_file(struct json_out *out, const char *buf, size_t len) {
  return fwrite(buf, 1, len, out->u.fp);
}

static int b64idx(int c) {
  if (c < 26) {
    return c + 'A';
  } else if (c < 52) {
    return c - 26 + 'a';
  } else if (c < 62) {
    return c - 52 + '0';
  } else {
    return c == 62 ? '+' : '/';
  }
}

static int b64rev(int c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A';
  } else if (c >= 'a' && c <= 'z') {
    return c + 26 - 'a';
  } else if (c >= '0' && c <= '9') {
    return c + 52 - '0';
  } else if (c == '+') {
    return 62;
  } else if (c == '/') {
    return 63;
  } else {
    return 64;
  }
}

static uint8_t hexdec(const char *s) {
#define HEXTOI(x) (x >= '0' && x <= '9' ? x - '0' : x - 'W')
  int a = tolower(*(const unsigned char *) s);
  int b = tolower(*(const unsigned char *) (s + 1));
  return (HEXTOI(a) << 4) | HEXTOI(b);
}

static int b64enc(struct json_out *out, const unsigned char *p, int n) {
  char buf[4];
  int i, len = 0;
  for (i = 0; i < n; i += 3) {
    int a = p[i], b = i + 1 < n ? p[i + 1] : 0, c = i + 2 < n ? p[i + 2] : 0;
    buf[0] = b64idx(a >> 2);
    buf[1] = b64idx((a & 3) << 4 | (b >> 4));
    buf[2] = b64idx((b & 15) << 2 | (c >> 6));
    buf[3] = b64idx(c & 63);
    if (i + 1 >= n) buf[2] = '=';
    if (i + 2 >= n) buf[3] = '=';
    len += out->printer(out, buf, sizeof(buf));
  }
  return len;
}

static int b64dec(const char *src, int n, char *dst) {
  const char *end = src + n;
  int len = 0;
  while (src + 3 < end) {
    int a = b64rev(src[0]), b = b64rev(src[1]), c = b64rev(src[2]),
        d = b64rev(src[3]);
    dst[len++] = (a << 2) | (b >> 4);
    if (src[2] != '=') {
      dst[len++] = (b << 4) | (c >> 2);
      if (src[3] != '=') {
        dst[len++] = (c << 6) | d;
      }
    }
    src += 4;
  }
  return len;
}

int json_vprintf(struct json_out *out, const char *fmt, va_list xap) WEAK;
int json_vprintf(struct json_out *out, const char *fmt, va_list xap) {
  int len = 0;
  const char *quote = "\"", *null = "null";
  va_list ap;
  va_copy(ap, xap);

  while (*fmt != '\0') {
    if (strchr(":, \r\n\t[]{}\"", *fmt) != NULL) {
      len += out->printer(out, fmt, 1);
      fmt++;
    } else if (fmt[0] == '%') {
      char buf[21];
      size_t skip = 2;

      if (fmt[1] == 'l' && fmt[2] == 'l' && (fmt[3] == 'd' || fmt[3] == 'u')) {
        int64_t val = va_arg(ap, int64_t);
        const char *fmt2 = fmt[3] == 'u' ? "%" UINT64_FMT : "%" INT64_FMT;
        snprintf(buf, sizeof(buf), fmt2, val);
        len += out->printer(out, buf, strlen(buf));
        skip += 2;
      } else if (fmt[1] == 'z' && fmt[2] == 'u') {
        size_t val = va_arg(ap, size_t);
        snprintf(buf, sizeof(buf), "%" SIZE_T_FMT, val);
        len += out->printer(out, buf, strlen(buf));
        skip += 1;
      } else if (fmt[1] == 'M') {
        json_printf_callback_t f = va_arg(ap, json_printf_callback_t);
        len += f(out, &ap);
      } else if (fmt[1] == 'B') {
        int val = va_arg(ap, int);
        const char *str = val ? "true" : "false";
        len += out->printer(out, str, strlen(str));
      } else if (fmt[1] == 'H') {
        const char *hex = "0123456789abcdef";
        int i, n = va_arg(ap, int);
        const unsigned char *p = va_arg(ap, const unsigned char *);
        len += out->printer(out, quote, 1);
        for (i = 0; i < n; i++) {
          len += out->printer(out, &hex[(p[i] >> 4) & 0xf], 1);
          len += out->printer(out, &hex[p[i] & 0xf], 1);
        }
        len += out->printer(out, quote, 1);
      } else if (fmt[1] == 'V') {
        const unsigned char *p = va_arg(ap, const unsigned char *);
        int n = va_arg(ap, int);
        len += out->printer(out, quote, 1);
        len += b64enc(out, p, n);
        len += out->printer(out, quote, 1);
      } else if (fmt[1] == 'Q' ||
                 (fmt[1] == '.' && fmt[2] == '*' && fmt[3] == 'Q')) {
        size_t l = 0;
        const char *p;

        if (fmt[1] == '.') {
          l = (size_t) va_arg(ap, int);
          skip += 2;
        }
        p = va_arg(ap, char *);

        if (p == NULL) {
          len += out->printer(out, null, 4);
        } else {
          if (fmt[1] == 'Q') {
            l = strlen(p);
          }
          len += out->printer(out, quote, 1);
          len += json_encode_string(out, p, l);
          len += out->printer(out, quote, 1);
        }
      } else {
        /*
         * we delegate printing to the system printf.
         * The goal here is to delegate all modifiers parsing to the system
         * printf, as you can see below we still have to parse the format
         * types.
         *
         * Currently, %s with strings longer than 20 chars will require
         * double-buffering (an auxiliary buffer will be allocated from heap).
         * TODO(dfrank): reimplement %s and %.*s in order to avoid that.
         */

        const char *end_of_format_specifier = "sdfFgGlhuI.*-0123456789";
        size_t n = strspn(fmt + 1, end_of_format_specifier);
        char *pbuf = buf;
        size_t need_len;
        char fmt2[20];
        va_list sub_ap;
        strncpy(fmt2, fmt, n + 1 > sizeof(fmt2) ? sizeof(fmt2) : n + 1);
        fmt2[n + 1] = '\0';

        va_copy(sub_ap, ap);
        need_len =
            vsnprintf(buf, sizeof(buf), fmt2, sub_ap) + 1 /* null-term */;
        /*
         * TODO(lsm): Fix windows & eCos code path here. Their vsnprintf
         * implementation returns -1 on overflow rather needed size.
         */
        if (need_len > sizeof(buf)) {
          /*
           * resulting string doesn't fit into a stack-allocated buffer `buf`,
           * so we need to allocate a new buffer from heap and use it
           */
          pbuf = (char *) malloc(need_len);
          va_copy(sub_ap, ap);
          vsnprintf(pbuf, need_len, fmt2, sub_ap);
        }

        /*
         * however we need to parse the type ourselves in order to advance
         * the va_list by the correct amount; there is no portable way to
         * inherit the advancement made by vprintf.
         * 32-bit (linux or windows) passes va_list by value.
         */
        if ((n + 1 == strlen("%" PRId64) && strcmp(fmt2, "%" PRId64) == 0) ||
            (n + 1 == strlen("%" PRIu64) && strcmp(fmt2, "%" PRIu64) == 0)) {
          (void) va_arg(ap, int64_t);
          skip += strlen(PRIu64) - 1;
        } else if (strcmp(fmt2, "%.*s") == 0) {
          (void) va_arg(ap, int);
          (void) va_arg(ap, char *);
        } else {
          switch (fmt2[n]) {
            case 'u':
            case 'd':
              (void) va_arg(ap, int);
              break;
            case 'g':
            case 'f':
              (void) va_arg(ap, double);
              break;
            case 'p':
              (void) va_arg(ap, void *);
              break;
            default:
              /* many types are promoted to int */
              (void) va_arg(ap, int);
          }
        }

        len += out->printer(out, pbuf, strlen(pbuf));
        skip = n + 1;

        /* If buffer was allocated from heap, free it */
        if (pbuf != buf) {
          free(pbuf);
          pbuf = NULL;
        }
      }
      fmt += skip;
    } else if (*fmt == '_' || is_alpha(*fmt)) {
      len += out->printer(out, quote, 1);
      while (*fmt == '_' || is_alpha(*fmt) || is_digit(*fmt)) {
        len += out->printer(out, fmt, 1);
        fmt++;
      }
      len += out->printer(out, quote, 1);
    } else {
      fmt++;
    }
  }
  va_end(ap);

  return len;
}

int json_printf(struct json_out *out, const char *fmt, ...) WEAK;
int json_printf(struct json_out *out, const char *fmt, ...) {
  int n;
  va_list ap;
  va_start(ap, fmt);
  n = json_vprintf(out, fmt, ap);
  va_end(ap);
  return n;
}

int json_printf_array(struct json_out *out, va_list *ap) WEAK;
int json_printf_array(struct json_out *out, va_list *ap) {
  int len = 0;
  char *arr = va_arg(*ap, char *);
  size_t i, arr_size = va_arg(*ap, size_t);
  size_t elem_size = va_arg(*ap, size_t);
  const char *fmt = va_arg(*ap, char *);
  len += json_printf(out, "[", 1);
  for (i = 0; arr != NULL && i < arr_size / elem_size; i++) {
    union {
      int64_t i;
      double d;
    } val;
    memcpy(&val, arr + i * elem_size,
           elem_size > sizeof(val) ? sizeof(val) : elem_size);
    if (i > 0) len += json_printf(out, ", ");
    if (strchr(fmt, 'f') != NULL) {
      len += json_printf(out, fmt, val.d);
    } else {
      len += json_printf(out, fmt, val.i);
    }
  }
  len += json_printf(out, "]", 1);
  return len;
}

#ifdef _WIN32
int cs_win_vsnprintf(char *str, size_t size, const char *format, va_list ap) WEAK;
int cs_win_vsnprintf(char *str, size_t size, const char *format, va_list ap) {
  int res = _vsnprintf(str, size, format, ap);
  va_end(ap);
  if (res >= size) {
    str[size - 1] = '\0';
  }
  return res;
}

int cs_win_snprintf(char *str, size_t size, const char *format, ...) WEAK;
int cs_win_snprintf(char *str, size_t size, const char *format, ...) {
  int res;
  va_list ap;
  va_start(ap, format);
  res = vsnprintf(str, size, format, ap);
  va_end(ap);
  return res;
}
#endif /* _WIN32 */

int json_walk(const char *json_string, int json_string_length,
              json_walk_callback_t callback, void *callback_data) WEAK;
int json_walk(const char *json_string, int json_string_length,
              json_walk_callback_t callback, void *callback_data) {
  struct frozen frozen;

  memset(&frozen, 0, sizeof(frozen));
  frozen.end = json_string + json_string_length;
  frozen.cur = json_string;
  frozen.callback_data = callback_data;
  frozen.callback = callback;

  TRY(doit(&frozen));

  return frozen.cur - json_string;
}

struct scan_array_info {
  char path[JSON_MAX_PATH_LEN];
  struct json_token *token;
};

static void json_scanf_array_elem_cb(void *callback_data, const char *name,
                                     size_t name_len, const char *path,
                                     const struct json_token *token) {
  struct scan_array_info *info = (struct scan_array_info *) callback_data;

  (void) name;
  (void) name_len;

  if (strcmp(path, info->path) == 0) {
    *info->token = *token;
  }
}

int json_scanf_array_elem(const char *s, int len, const char *path, int idx,
                          struct json_token *token) WEAK;
int json_scanf_array_elem(const char *s, int len, const char *path, int idx,
                          struct json_token *token) {
  struct scan_array_info info;
  info.token = token;
  memset(token, 0, sizeof(*token));
  snprintf(info.path, sizeof(info.path), "%s[%d]", path, idx);
  json_walk(s, len, json_scanf_array_elem_cb, &info);
  return token->len;
}

struct json_scanf_info {
  int num_conversions;
  char *path;
  const char *fmt;
  void *target;
  void *user_data;
  int type;
};

int json_unescape(const char *src, int slen, char *dst, int dlen) WEAK;
int json_unescape(const char *src, int slen, char *dst, int dlen) {
  char *send = (char *) src + slen, *dend = dst + dlen, *orig_dst = dst, *p;
  const char *esc1 = "\"\\/bfnrt", *esc2 = "\"\\/\b\f\n\r\t";

  while (src < send) {
    if (*src == '\\') {
      if (++src >= send) return JSON_STRING_INCOMPLETE;
      if (*src == 'u') {
        /* TODO(lsm): \uXXXX escapes drag utf8 lib... Do it at some stage */
        return JSON_STRING_INVALID;
      } else if ((p = (char *) strchr(esc1, *src)) != NULL) {
        if (dst < dend) *dst = esc2[p - esc1];
      } else {
        return JSON_STRING_INVALID;
      }
    } else {
      if (dst < dend) *dst = *src;
    }
    dst++;
    src++;
  }

  return dst - orig_dst;
}

static void json_scanf_cb(void *callback_data, const char *name,
                          size_t name_len, const char *path,
                          const struct json_token *token) {
  struct json_scanf_info *info = (struct json_scanf_info *) callback_data;

  (void) name;
  (void) name_len;

  if (strcmp(path, info->path) != 0) {
    /* It's not the path we're looking for, so, just ignore this callback */
    return;
  }

  if (token->ptr == NULL) {
    /*
     * We're not interested here in the events for which we have no value;
     * namely, JSON_TYPE_OBJECT_START and JSON_TYPE_ARRAY_START
     */
    return;
  }

  switch (info->type) {
    case 'B':
      info->num_conversions++;
      *(int *) info->target = (token->type == JSON_TYPE_TRUE ? 1 : 0);
      break;
    case 'M': {
      union {
        void *p;
        json_scanner_t f;
      } u = {info->target};
      info->num_conversions++;
      u.f(token->ptr, token->len, info->user_data);
      break;
    }
    case 'Q': {
      char **dst = (char **) info->target;
      int unescaped_len = json_unescape(token->ptr, token->len, NULL, 0);
      if (unescaped_len >= 0 &&
          (*dst = (char *) malloc(unescaped_len + 1)) != NULL) {
        info->num_conversions++;
        json_unescape(token->ptr, token->len, *dst, unescaped_len);
        (*dst)[unescaped_len] = '\0';
      }
      break;
    }
    case 'H': {
      char **dst = (char **) info->user_data;
      int i, len = token->len / 2;
      *(int *) info->target = len;
      if ((*dst = (char *) malloc(len + 1)) != NULL) {
        for (i = 0; i < len; i++) {
          (*dst)[i] = hexdec(token->ptr + 2 * i);
        }
        (*dst)[len] = '\0';
        info->num_conversions++;
      }
      break;
    }
    case 'V': {
      char **dst = (char **) info->target;
      int len = token->len * 4 / 3 + 2;
      if ((*dst = (char *) malloc(len + 1)) != NULL) {
        int n = b64dec(token->ptr, token->len, *dst);
        (*dst)[n] = '\0';
        *(int *) info->user_data = n;
        info->num_conversions++;
      }
      break;
    }
    case 'T':
      info->num_conversions++;
      *(struct json_token *) info->target = *token;
      break;
    default:
      info->num_conversions += sscanf(token->ptr, info->fmt, info->target);
      break;
  }
}

int json_vscanf(const char *s, int len, const char *fmt, va_list ap) WEAK;
int json_vscanf(const char *s, int len, const char *fmt, va_list ap) {
  char path[JSON_MAX_PATH_LEN] = "", fmtbuf[20];
  int i = 0;
  char *p = NULL;
  struct json_scanf_info info = {0, path, fmtbuf, NULL, NULL, 0};

  while (fmt[i] != '\0') {
    if (fmt[i] == '{') {
      strcat(path, ".");
      i++;
    } else if (fmt[i] == '}') {
      if ((p = strrchr(path, '.')) != NULL) *p = '\0';
      i++;
    } else if (fmt[i] == '%') {
      info.target = va_arg(ap, void *);
      info.type = fmt[i + 1];
      switch (fmt[i + 1]) {
        case 'M':
        case 'V':
        case 'H':
          info.user_data = va_arg(ap, void *);
        /* FALLTHROUGH */
        case 'B':
        case 'Q':
        case 'T':
          i += 2;
          break;
        default: {
          const char *delims = ", \t\r\n]}";
          int conv_len = strcspn(fmt + i + 1, delims) + 1;
          snprintf(fmtbuf, sizeof(fmtbuf), "%.*s", conv_len, fmt + i);
          i += conv_len;
          i += strspn(fmt + i, delims);
          break;
        }
      }
      json_walk(s, len, json_scanf_cb, &info);
    } else if (is_alpha(fmt[i]) || get_utf8_char_len(fmt[i]) > 1) {
      const char *delims = ": \r\n\t";
      int key_len = strcspn(&fmt[i], delims);
      if ((p = strrchr(path, '.')) != NULL) p[1] = '\0';
      sprintf(path + strlen(path), "%.*s", key_len, &fmt[i]);
      i += key_len + strspn(fmt + i + key_len, delims);
    } else {
      i++;
    }
  }
  return info.num_conversions;
}

int json_scanf(const char *str, int len, const char *fmt, ...) WEAK;
int json_scanf(const char *str, int len, const char *fmt, ...) {
  int result;
  va_list ap;
  va_start(ap, fmt);
  result = json_vscanf(str, len, fmt, ap);
  va_end(ap);
  return result;
}
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

typedef word_t (*w4w_t)(word_t, word_t, word_t, word_t);
typedef word_t (*w5w_t)(word_t, word_t, word_t, word_t, word_t);
typedef word_t (*w6w_t)(word_t, word_t, word_t, word_t, word_t, word_t);
typedef word_t (*wdw_t)(double, word_t);
typedef word_t (*wdd_t)(double, double);

typedef double (*d4w_t)(word_t, word_t, word_t, word_t);
typedef double (*d5w_t)(word_t, word_t, word_t, word_t, word_t);
typedef double (*d6w_t)(word_t, word_t, word_t, word_t, word_t, word_t);
typedef double (*ddw_t)(double, word_t);
typedef double (*ddd_t)(double, double);

int ffi_call(ffi_fn_t func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args) {
  int i, doubles = 0;

  if (nargs > 6) return -1;
  for (i = 0; i < nargs; i++) {
    doubles += !!args[i].is_float;
  }
  if (doubles > 0 && nargs > 2) return -1;

  if (!res->is_float) {
    word_t r;
    switch (doubles) {
      case 0: {
        /* No double args: we currently support up to 6 word-sized arguments */
        if (nargs <= 4) {
          w4w_t f = (w4w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i, (word_t) args[2].v.i,
                (word_t) args[3].v.i);
        } else if (nargs == 5) {
          w5w_t f = (w5w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i, (word_t) args[2].v.i,
                (word_t) args[3].v.i, (word_t) args[4].v.i);
        } else if (nargs == 6) {
          w6w_t f = (w6w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i, (word_t) args[2].v.i,
                (word_t) args[3].v.i, (word_t) args[4].v.i, (word_t) args[5].v.i);
        } else {
          abort();
        }
        break;
      }
      case 1: {
        wdw_t f = (wdw_t) func;
        if (args[0].is_float) {
          r = f(args[0].v.d, (word_t) args[1].v.i);
        } else {
          r = f(args[1].v.d, (word_t) args[0].v.i);
        }
        break;
      }
      case 2: {
        wdd_t f = (wdd_t) func;
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
        /* No double args: we currently support up to 6 word-sized arguments */
        if (nargs <= 4) {
          d4w_t f = (d4w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i, (word_t) args[2].v.i,
                (word_t) args[3].v.i);
        } else if (nargs == 5) {
          d5w_t f = (d5w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i, (word_t) args[2].v.i,
                (word_t) args[3].v.i, (word_t) args[4].v.i);
        } else if (nargs == 6) {
          d6w_t f = (d6w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i, (word_t) args[2].v.i,
                (word_t) args[3].v.i, (word_t) args[4].v.i, (word_t) args[5].v.i);
        } else {
          abort();
        }
        break;
      }
      case 1: {
        ddw_t f = (ddw_t) func;
        if (args[0].is_float) {
          r = f(args[0].v.d, (word_t) args[1].v.i);
        } else {
          r = f(args[1].v.d, (word_t) args[0].v.i);
        }
        break;
      }
      case 2: {
        ddd_t f = (ddd_t) func;
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
#line 1 "mjs/array.c"
#endif
/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "common/str_util.h" */
/* Amalgamated: #include "mjs/internal.h" */
/* Amalgamated: #include "mjs/array.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/object.h" */
/* Amalgamated: #include "mjs/primitive.h" */
/* Amalgamated: #include "mjs/core.h" */

/* like c_snprintf but returns `size` if write is truncated */
static int v_sprintf_s(char *buf, size_t size, const char *fmt, ...) {
  size_t n;
  va_list ap;
  va_start(ap, fmt);
  n = c_vsnprintf(buf, size, fmt, ap);
  if (n > size) {
    return size;
  }
  return n;
}

mjs_val_t mjs_mk_array(struct mjs *mjs) {
  mjs_val_t ret = mjs_mk_object(mjs);
  /* change the tag to MJS_TAG_OBJECT_ARRAY */
  ret &= ~MJS_TAG_MASK;
  ret |= MJS_TAG_OBJECT_ARRAY;
  return ret;
}

int mjs_is_array(mjs_val_t v) {
  return (v & MJS_TAG_MASK) == MJS_TAG_OBJECT_ARRAY;
}

mjs_val_t mjs_array_get(struct mjs *mjs, mjs_val_t arr, unsigned long index) {
  return mjs_array_get2(mjs, arr, index, NULL);
}

mjs_val_t mjs_array_get2(struct mjs *mjs, mjs_val_t arr, unsigned long index, int *has) {
  mjs_val_t res = MJS_UNDEFINED;

  if (has != NULL) {
    *has = 0;
  }

  if (mjs_is_object(arr)) {
    struct mjs_property *p;
    char buf[20];
    int n = v_sprintf_s(buf, sizeof(buf), "%lu", index);
    p = mjs_get_own_property(mjs, arr, buf, n);
    if (p != NULL) {
      if (has != NULL) {
        *has = 1;
      }
      res = p->value;
    }
  }

  return res;
}

unsigned long mjs_array_length(struct mjs *mjs, mjs_val_t v) {
  struct mjs_property *p;
  unsigned long len = 0;

  if (!mjs_is_object(v)) {
    len = 0;
    goto clean;
  }

  for (p = get_object_struct(v)->properties; p != NULL; p = p->next) {
    int ok = 0;
    unsigned long n = 0;
    str_to_ulong(mjs, p->name, &ok, &n);
    if (ok && n >= len && n < UINT32_MAX) {
      len = n + 1;
    }
  }

clean:
  return len;
}

mjs_err_t mjs_array_set(struct mjs *mjs, mjs_val_t arr, unsigned long index,
                        mjs_val_t v) {
  mjs_err_t ret = MJS_OK;

  if (mjs_is_object(arr)) {
    char buf[20];
    int n = v_sprintf_s(buf, sizeof(buf), "%lu", index);
    ret = mjs_set(mjs, arr, buf, n, v);
  } else {
    ret = MJS_TYPE_ERROR;
  }

  return ret;
}

#if 0
void mjs_array_del(struct mjs *mjs, mjs_val_t arr, unsigned long index) {
  char buf[20];
  int n = v_sprintf_s(buf, sizeof(buf), "%lu", index);
  mjs_del(mjs, arr, buf, n);
}
#endif

mjs_err_t mjs_array_push(struct mjs *mjs, mjs_val_t arr, mjs_val_t v) {
  return mjs_array_set(mjs, arr, mjs_array_length(mjs, arr), v);
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/conversion.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/object.h" */
/* Amalgamated: #include "mjs/array.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/primitive.h" */
/* Amalgamated: #include "mjs/conversion.h" */
/* Amalgamated: #include "common/str_util.h" */

MJS_PRIVATE mjs_err_t mjs_to_string(struct mjs *mjs, mjs_val_t *v,
                                    char **p, size_t *sizep,
                                    int *need_free) {
  mjs_err_t ret = MJS_OK;

  *p = NULL;
  *sizep = 0;
  *need_free = 0;

  if (mjs_is_string(*v)) {
    *p = (char *)mjs_get_string(mjs, v, sizep);
  } else if (mjs_is_number(*v)) {
    double num = mjs_get_double(mjs, *v);
    const char *fmt = num > 1e10 ? "%.21g" : "%.10g";
    (void) num;
    (void) fmt;
    *sizep = snprintf(NULL, 0, fmt, num);
    *p = malloc(*sizep + 1 /*null term*/);
    if (*p == NULL) {
      ret = MJS_OUT_OF_MEMORY;
      goto clean;
    }
    snprintf(*p, *sizep + 1, fmt, num);
    *need_free = 1;
  } else if (mjs_is_boolean(*v)) {
    if (mjs_get_bool(mjs, *v)) {
      *p = "true";
      *sizep = 4;
    } else {
      *p = "false";
      *sizep = 5;
    }
  } else if (mjs_is_undefined(*v)) {
    *p = "undefined";
    *sizep = 9;
  } else if (mjs_is_null(*v)) {
    *p = "null";
    *sizep = 4;
  } else if (mjs_is_object(*v)) {
    ret = MJS_TYPE_ERROR;
    mjs_set_errorf(mjs, ret, "conversion from object to string is not supported");
    bf_die(&mjs->vm);
  } else if (mjs_is_foreign(*v)) {
    *p = "TODO_foreign";
    *sizep = 12;
  } else {
    ret = MJS_TYPE_ERROR;
    mjs_set_errorf(mjs, ret, "unknown type to convert to string");
    bf_die(&mjs->vm);
  }

clean:
  return ret;
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
/* Amalgamated: #include "mjs/ops.h" */
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
  if (mjs_is_boolean((mjs_val_t) cell)) {
    return !!mjs_get_bool(NULL, (mjs_val_t) cell);
  } else {
    return !!mjs_get_int32(NULL, (mjs_val_t) cell);
  }
}

struct mjs *mjs_create() {
  struct mjs_create_opts opts;
  memset(&opts, 0, sizeof(opts));
  return mjs_create_opt(opts);
}

MJS_PRIVATE void mjs_init_globals(struct mjs *mjs, mjs_val_t g) {
  mjs_set(mjs, g, "print", ~0, mjs_mk_number(mjs, MJS_WORD_PTR_jsprint));
  mjs_set(mjs, g, "ffi", ~0, mjs_mk_number(mjs, MJS_WORD_PTR_ffi));
  mjs_set(mjs, g, "ffi_cb_free", ~0, mjs_mk_foreign(mjs, mjs_ffi_cb_free));
  mjs_set(mjs, g, "load", ~0, mjs_mk_foreign(mjs, mjs_op_load));

  mjs_val_t json_v = mjs_mk_object(mjs);
  mjs_set(mjs, json_v, "stringify", ~0,
          mjs_mk_foreign(mjs, mjs_op_json_stringify));
  mjs_set(mjs, json_v, "parse", ~0,
      mjs_mk_foreign(mjs, mjs_op_json_parse));
  mjs_set(mjs, g, "JSON", ~0, json_v);
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

  /*
   * If getprop distance is not already larger than the maximum useful value,
   * increment it.
   *
   * Needed for "method invocation pattern".
   */
  if (mjs->words_since_getprop < GETPROP_DISTANCE_OVER) {
    mjs->words_since_getprop++;
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
  mbuf_init(&mjs->scopes, 0);

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

  /* create Global Object and push it to the scope chain */
  mjs_push_scope(mjs, mjs_mk_object(mjs));

  mjs->vals.call_frame = mjs_mk_number(mjs, -1);
  mjs->vals.min_scope = mjs_mk_number(mjs, 0 /* global object */);

  mjs->vals.this_val = MJS_UNDEFINED;

  /* Initial state for "method invocation pattern" stuff */
  mjs->vals.last_getprop_obj = MJS_UNDEFINED;
  mjs->words_since_getprop = GETPROP_DISTANCE_OVER;

  mjs_init_globals(mjs, mjs_get_global(mjs));
  return mjs;
}

void mjs_destroy(struct mjs *mjs) {
  bf_destroy_vm(&mjs->vm);
  mbuf_free(&mjs->owned_strings);
  mbuf_free(&mjs->foreign_strings);
  mbuf_free(&mjs->owned_values);
  mbuf_free(&mjs->scopes);
  mbuf_free(&mjs->json_visited_stack);
  mjs_ffi_args_free_list(mjs);
  gc_arena_destroy(mjs, &mjs->object_arena);
  gc_arena_destroy(mjs, &mjs->property_arena);
  free(mjs->error_msg);
  free(mjs);
}

mjs_val_t mjs_get_global(struct mjs *mjs) {
  mjs_val_t ret;
  assert(mjs->scopes.len >= sizeof(ret));
  memcpy(&ret, mjs->scopes.buf, sizeof(ret));
  return ret;
}

/*
 * Pushes a given scope object to the scopes stack
 */
MJS_PRIVATE void mjs_push_scope(struct mjs *mjs, mjs_val_t scope) {
  mbuf_append(&mjs->scopes, &scope, sizeof(scope));
}

/*
 * Pops a top scope from the scope stack and returns it
 */
MJS_PRIVATE mjs_val_t mjs_pop_scope(struct mjs *mjs) {
  assert(mjs->scopes.len >= sizeof(mjs_val_t));
  mjs->scopes.len -= sizeof(mjs_val_t);
  return *((mjs_val_t *)(mjs->scopes.buf + mjs->scopes.len));
}

/*
 * Returns a top scope object
 */
MJS_PRIVATE mjs_val_t mjs_scope_tos(struct mjs *mjs) {
  assert(mjs->scopes.len >= sizeof(mjs_val_t));
  return *((mjs_val_t *)(mjs->scopes.buf - sizeof(mjs_val_t) + mjs->scopes.len));
}

MJS_PRIVATE mjs_val_t mjs_scope_get_by_idx(struct mjs *mjs, int idx) {
  int bufidx = idx * sizeof(mjs_val_t);
  assert(mjs->scopes.len >= bufidx + sizeof(mjs_val_t) );
  return *((mjs_val_t *)(mjs->scopes.buf + bufidx));
}

MJS_PRIVATE void mjs_scope_set_by_idx(struct mjs *mjs, int idx, mjs_val_t v) {
  int bufidx = idx * sizeof(mjs_val_t);
  assert(mjs->scopes.len >= bufidx + sizeof(mjs_val_t) );
  *((mjs_val_t *)(mjs->scopes.buf + bufidx)) = v;
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
  if (fmt != NULL) {
    mg_avprintf(&mjs->error_msg, 0, fmt, ap);
  }
  va_end(ap);
  return err;
}

mjs_err_t mjs_prepend_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  char *old_error_msg = mjs->error_msg;
  char *new_error_msg = NULL;
  mjs->error_msg = NULL;
  /* set error_msg_err if only it wasn't already set to some error */
  if (mjs->error_msg_err == MJS_OK) {
    mjs->error_msg_err = err;
  }
  mg_avprintf(&new_error_msg, 0, fmt, ap);
  va_end(ap);

  if (old_error_msg != NULL) {
    mg_asprintf(&mjs->error_msg, 0, "%s: %s", new_error_msg, old_error_msg);
    free(new_error_msg);
    free(old_error_msg);
  } else {
    mjs->error_msg = new_error_msg;
  }
  return err;
}

const char *mjs_strerror(struct mjs *mjs, mjs_err_t err) {
  const char *ret = NULL;
  if (mjs->error_msg_err == err) {
    ret = mjs->error_msg;
  }
  if (ret == NULL) {
    switch (err) {
      case MJS_OK:
        ret = "";
        break;
      case MJS_SYNTAX_ERROR:
        ret = "syntax error";
        break;
      case MJS_INTERNAL_ERROR:
        ret = "internal error";
        break;
      case MJS_REFERENCE_ERROR:
        ret = "reference error";
        break;
      case MJS_TYPE_ERROR:
        ret = "type error";
        break;
      case MJS_OUT_OF_MEMORY:
        ret = "out of memory";
        break;
      /*
       * NOTE: we don't use default case here in order to leverage compiler
       * warning about the non-handled enum elements. We'll set default
       * value below.
       */
    }
    if (ret == NULL) {
      ret = "unknown error";
    }
  }
  return ret;
}

MJS_PRIVATE enum mjs_type mjs_get_type(struct mjs *mjs, mjs_val_t v) {
  int tag;
  (void) mjs;
  if (mjs_is_number(v)) {
    return MJS_TYPE_NUMBER;
  }
  tag = (v & MJS_TAG_MASK) >> 48;
  switch (tag) {
    case MJS_TAG_FOREIGN >> 48:
      if (mjs_is_null(v)) {
        return MJS_TYPE_NULL;
      }
      return MJS_TYPE_FOREIGN;
    case MJS_TAG_UNDEFINED >> 48:
      return MJS_TYPE_UNDEFINED;
    case MJS_TAG_OBJECT >> 48:
      return MJS_TYPE_OBJECT_GENERIC;
    case MJS_TAG_OBJECT_ARRAY >> 48:
      return MJS_TYPE_OBJECT_ARRAY;
    case MJS_TAG_STRING_I >> 48:
    case MJS_TAG_STRING_O >> 48:
    case MJS_TAG_STRING_F >> 48:
    case MJS_TAG_STRING_D >> 48:
    case MJS_TAG_STRING_5 >> 48:
      return MJS_TYPE_STRING;
    case MJS_TAG_BOOLEAN >> 48:
      return MJS_TYPE_BOOLEAN;
    default:
      abort();
      return MJS_TYPE_UNDEFINED;
  }
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
/* Amalgamated: #include "mjs/string.h" */
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

  free(mjs->error_msg);
  mjs->error_msg = NULL;
  mjs->error_msg_err = MJS_OK;

  LOG(LL_DEBUG, ("running %d", ctx.entry));
  bf_run(&mjs->vm, ctx.entry);
  r = bf_pop(&mjs->vm.dstack);
  err = mjs->error_msg_err;

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

mjs_err_t mjs_call(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                   mjs_val_t this_val, int nargs, ...) {
  va_list ap;
  int i;
  mjs_err_t ret;
  va_start (ap, nargs);
  mjs_val_t *args = calloc(1, sizeof(mjs_val_t) * nargs);
  for (i = 0; i < nargs; i++) {
    args[i] = va_arg(ap, mjs_val_t);
  }

  ret = mjs_apply(mjs, res, func, this_val, nargs, args);
  /*
   * NOTE: calling `bf_run()` invalidates `func` and `this_val`. If you ever
   * need to use them afterwards, you need to own them before.
   */

  free(args);
  return ret;
}

mjs_err_t mjs_apply(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                    mjs_val_t this_val, int nargs, mjs_val_t *args) {
  mjs_err_t err;
  mjs_val_t r;
  int i;

  LOG(LL_DEBUG, ("applying func %d", mjs_get_int(mjs, func)));
  for (i = nargs - 1; i >= 0; i--) {
    bf_push(&mjs->vm.dstack, args[i]);
  }
  bf_push(&mjs->vm.dstack, mjs_mk_number(mjs, nargs));
  bf_push(&mjs->vm.dstack, this_val);
  bf_push(&mjs->vm.dstack, func);
  bf_run(&mjs->vm, MJS_WORD_PTR_jscall_wrap);
  r = bf_pop(&mjs->vm.dstack);
  err = mjs->error_msg_err;

  /*
   * NOTE: calling `bf_run()` invalidates `func` and `this_val`. If you ever
   * need to use them afterwards, you need to own them before.
   */

  if (res != NULL) *res = r;

  return err;
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

#include <stdint.h>

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

typedef void (cb_fn_t)(void);

/*
 * Data of the two related arguments: callback function pointer and the
 * userdata for it
 */
struct cbdata {
  /* JS callback function */
  mjs_val_t func;
  /* JS userdata */
  mjs_val_t userdata;

  /* C function signature source */
  const char *signature;
  size_t signature_len;
  /*
   * Descriptor of the C callback function signature.
   */
  ffi_sig_t sig;
  /* index of the function pointer param */
  int8_t func_idx;
  /* index of the userdata param */
  int8_t userdata_idx;
};

void mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym) {
  mjs->dlsym = dlsym;
}

static cval_type_t parse_cval_type(struct mjs *mjs, const char *s, const char *e) {
  while (e > s && e[-1] == ' ') e--;  /* Trim trailing spaces */
  if (strncmp(s, "void", e - s) == 0) {
    return CVAL_TYPE_NONE;
  } else if (strncmp(s, "userdata", e - s) == 0) {
    return CVAL_TYPE_USERDATA;
  } else if (strncmp(s, "int", e - s) == 0) {
    return CVAL_TYPE_INT;
  } else if (strncmp(s, "double", e - s) == 0) {
    return CVAL_TYPE_DOUBLE;
  } else if (strncmp(s, "char*", 5) == 0 || strncmp(s, "char *", 6) == 0) {
    return CVAL_TYPE_CHAR_PTR;
  } else if (strncmp(s, "void*", 5) == 0 || strncmp(s, "void *", 6) == 0) {
    return CVAL_TYPE_VOID_PTR;
  } else {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "failed to parse val type \"%.*s\"", (e - s), s);
    return CVAL_TYPE_INVALID;
  }
}

static int parse_cb_signature(
    struct mjs *mjs, const char *s, const char *e, ffi_sig_t *sig
    ) {
  int ret = 1;
  int vtidx = 0;
  const char *cur = s;
  cval_type_t val_type = CVAL_TYPE_INVALID;
  mjs_ffi_sig_init(sig);

  const char *tmp_e = NULL;

  /* Parse return value type */
  tmp_e = strchr(cur, '(');
  if (tmp_e == NULL) {
    ret = 0;
    goto clean;
  }
  val_type = parse_cval_type(mjs, cur, tmp_e);
  if (val_type == CVAL_TYPE_INVALID) {
    ret = 0;
    goto clean;
  }
  mjs_ffi_sig_set_val_type(sig, vtidx++, val_type);

  /* Advance cur to the beginning of the arg list */
  tmp_e = strchr(tmp_e, ')');
  if (tmp_e == NULL) {
    ret = 0;
    goto clean;
  }
  tmp_e = strchr(tmp_e, '(');
  if (tmp_e == NULL) {
    ret = 0;
    goto clean;
  }
  cur = tmp_e + 1;

  /* Parse all args */
  while (*tmp_e && *tmp_e != ')') {
    tmp_e = cur;

    /* Advance tmp_e until the next arg separator */
    while (*tmp_e && *tmp_e != ',' && *tmp_e != ')') tmp_e++;

    /* Parse current arg */
    val_type = parse_cval_type(mjs, cur, tmp_e);
    if (val_type == CVAL_TYPE_INVALID) {
      /* parse_cval_type() has already set error message */
      ret = 0;
      goto clean;
    }
    if (!mjs_ffi_sig_set_val_type(sig, vtidx++, val_type)) {
      mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "too many callback args");
      ret = 0;
      goto clean;
    }

    if (*tmp_e == ',') {
      /* Advance cur to the next argument */
      cur = tmp_e + 1;
      while (*cur == ' ') cur++;
    } else {
      /* No more arguments */
      break;
    }
  }

  sig->stat = mjs_ffi_sig_stat_get(mjs, sig);
  if (!sig->stat.is_valid) {
    ret = 0;
    goto clean;
  }

clean:
  if (!ret) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR,
        "bad callback signature: \"%.*s\"", e - s, s);
  }
  return ret;
}

/* C callbacks implementation {{{ */

/* An argument or a return value for C callback impl */
union ffi_cb_data_val {
  void *p;
  uintptr_t w;
  double d;
};

struct ffi_cb_data {
  union ffi_cb_data_val args[MJS_CB_ARGS_MAX_CNT];
};

static union ffi_cb_data_val ffi_cb_impl_generic(void *param, struct ffi_cb_data *data) {
  struct ffi_cb_args *cbargs = (struct ffi_cb_args *)param;
  mjs_val_t res = MJS_UNDEFINED;
  union ffi_cb_data_val ret;
  int i;
  memset(&ret, 0, sizeof(ret));
  mjs_own(cbargs->mjs, &res);

  /* There must be at least one argument: a userdata */
  assert(cbargs->sig.stat.args_cnt > 0);

  /* Create JS arguments */
  mjs_val_t *args = calloc(1, sizeof(mjs_val_t) * cbargs->sig.stat.args_cnt);
  for (i = 0; i < cbargs->sig.stat.args_cnt; i++) {
    cval_type_t val_type = cbargs->sig.val_types[i + 1/* first val_type is return value type */];
    switch (val_type) {
      case CVAL_TYPE_USERDATA:
        args[i] = cbargs->userdata;
        break;
      case CVAL_TYPE_INT:
        args[i] = mjs_mk_number(cbargs->mjs, data->args[i].w);
        break;
      case CVAL_TYPE_CHAR_PTR: {
        const char *s = (char *) data->args[i].w;
        if (s == NULL) s = "";
        args[i] = mjs_mk_string(cbargs->mjs, s, ~0, 0);
        break;
      }
      case CVAL_TYPE_VOID_PTR:
        args[i] = mjs_mk_foreign(cbargs->mjs, (void *) data->args[i].w);
        break;
      case CVAL_TYPE_DOUBLE:
        args[i] = mjs_mk_number(cbargs->mjs, data->args[i].d);
        break;
      default:
        /* should never be here */
        LOG(LL_ERROR, ("unexpected val type for arg #%d: %d\n", i, val_type));
        abort();
    }
  }

  /* Call JS function */
  LOG(LL_DEBUG, ("calling JS callback void-void %d from C", mjs_get_int(cbargs->mjs, cbargs->func)));
  mjs_err_t err = mjs_apply(cbargs->mjs, &res, cbargs->func, MJS_UNDEFINED,
                            cbargs->sig.stat.args_cnt, args);
  if (err != MJS_OK) {
    /*
     * There's not much we can do about the error here; let's at least print it
     */
    fprintf(stderr, "MJS callback error: %s\n", mjs_strerror(cbargs->mjs, err));

    goto clean;
  }

  /* Get return value, if needed */
  switch (cbargs->sig.val_types[0]) {
    case CVAL_TYPE_NONE:
      /* do nothing */
      break;
    case CVAL_TYPE_INT:
      ret.w = mjs_get_int(cbargs->mjs, res);
      break;
    case CVAL_TYPE_CHAR_PTR:
    case CVAL_TYPE_VOID_PTR:
      ret.p = mjs_get_ptr(cbargs->mjs, res);
      break;
    case CVAL_TYPE_DOUBLE:
      ret.d = mjs_get_int(cbargs->mjs, res);
      break;
    default:
      /* should never be here */
      LOG(LL_ERROR, ("unexpected return val type %d\n", cbargs->sig.val_types[0]));
      abort();
  }

clean:
  free(args);
  mjs_disown(cbargs->mjs, &res);
  return ret;
}

static void ffi_init_cb_data_wwww(struct ffi_cb_data *data, uintptr_t w0, uintptr_t w1, uintptr_t w2, uintptr_t w3) {
  memset(data, 0, sizeof(*data));
  data->args[0].w = w0;
  data->args[1].w = w1;
  data->args[2].w = w2;
  data->args[3].w = w3;
}

static uintptr_t ffi_cb_impl_wpwww(uintptr_t w0, uintptr_t w1, uintptr_t w2, uintptr_t w3) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3);
  return ffi_cb_impl_generic((void *)w0, &data).w;
}

static uintptr_t ffi_cb_impl_wwpww(uintptr_t w0, uintptr_t w1, uintptr_t w2, uintptr_t w3) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3);
  return ffi_cb_impl_generic((void *)w1, &data).w;
}

static uintptr_t ffi_cb_impl_wwwpw(uintptr_t w0, uintptr_t w1, uintptr_t w2, uintptr_t w3) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3);
  return ffi_cb_impl_generic((void *)w2, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwp(uintptr_t w0, uintptr_t w1, uintptr_t w2, uintptr_t w3) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3);
  return ffi_cb_impl_generic((void *)w3, &data).w;
}
/* }}} */

static struct ffi_cb_args **ffi_get_matching(
    struct ffi_cb_args **plist,
    mjs_val_t func, mjs_val_t userdata
    ) {
  for ( ; *plist != NULL; plist = &((*plist)->next)) {
    if ((*plist)->func == func && (*plist)->userdata == userdata) {
      break;
    }
  }
  return plist;
}

static cb_fn_t *get_cb_impl_by_signature(
    const ffi_sig_t *sig
    ) {

  if (sig->stat.is_valid) {
    if (sig->stat.args_cnt <= 4) {
      if (mjs_ffi_is_regular_word_or_void(sig->val_types[0])) {
        /* Return type is a word or void */
        if (sig->stat.args_double_cnt == 0) {
          /* No double arguments */
          switch (sig->stat.userdata_idx) {
            case 1:
              return (cb_fn_t *)ffi_cb_impl_wpwww;
            case 2:
              return (cb_fn_t *)ffi_cb_impl_wwpww;
            case 3:
              return (cb_fn_t *)ffi_cb_impl_wwwpw;
            case 4:
              return (cb_fn_t *)ffi_cb_impl_wwwwp;
            default:
              /* should never be here */
              abort();
          }
        }
      }
    } else {
      /* Too many arguments for the built-in callback impls */
      /* TODO(dfrank): add support for custom app-dependent resolver */
    }
  }

  return NULL;
}

MJS_PRIVATE int mjs_ffi_call(struct mjs *mjs, mjs_val_t sig) {
  const char *s = mjs_get_cstring(mjs, &sig);
  const char *n, *e, *a = NULL;
  char *buf = NULL;
  ffi_fn_t fn;
  int i, nargs, ret = 1;
  struct ffi_arg res;
  struct ffi_arg args[FFI_MAX_ARGS_CNT];

  /* TODO(dfrank): support multiple callbacks */
  mjs_val_t resv = mjs_mk_undefined();
  mjs_val_t argvs[FFI_MAX_ARGS_CNT];

  struct cbdata cbdata;
  memset(&cbdata, 0, sizeof(cbdata));
  cbdata.func_idx = -1;
  cbdata.userdata_idx = -1;

  for (n = s; *n && *n >= 'a' && *n <= 'z';) n++;  /* Skip type name */
  while (*n == ' ' || *n == '*') n++;  /* Skip to function name */
  for (e = n; *e && *e != '(';) e++;  /* Skip function name */
  if (*e == '(') a = e + 1;

  cval_type_t rtype = parse_cval_type(mjs, s, n);
  if (rtype == CVAL_TYPE_INVALID) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "wrong ffi return type");
    ret = 0;
    goto clean;
  }

  res.size = 4;
  res.is_float = 0;
  res.v.i = 0;

  nargs = mjs_get_int(mjs, mjs_pop(mjs));
  for (i = 0; i < nargs; i++) {
    const char *ae; /* pointer to the one-past-end character */
    int level = 0; /* nested parens level */
    int is_fp = 0; /* set to 1 is current arg is a callback function ptr */
    if (a == NULL) {
      mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "got %d actuals", nargs);
      ret = 0;
      goto clean;
    }
    while (*a == ' ') a++;
    ae = a;
    while (*ae && (level > 0 || (*ae != ',' && *ae != ')'))) {
      switch (*ae) {
        case '(':
          level++;
          /*
           * only function pointer params can have parens, so, set the flag
           * that it's going to be a function pointer
           */
          is_fp = 1;
          break;
        case ')':
          level--;
          break;
      }
      ae++;
    }

    mjs_val_t arg = mjs_pop(mjs);
    if (is_fp) {
      /*
       * Current argument is a callback function pointer: remember the given JS
       * function and the argument index
       */
      cbdata.func = arg;
      cbdata.func_idx = i;
      cbdata.signature = a;
      cbdata.signature_len = (size_t)(ae - a);
      if (!parse_cb_signature(mjs, a, ae, &cbdata.sig)) {
        ret = 0;
        goto clean;
      }
    } else {
      /* Some non-function argument */
      cval_type_t ctype = parse_cval_type(mjs, a, ae);
      switch (ctype) {
        case CVAL_TYPE_NONE:
          /*
           * Void argument: in any case, it's an error, because if C function
           * takes no arguments, then the FFI-ed JS function should be called
           * without any arguments, and thus we'll not face "void" here.
           */
          if (i == 0) {
            /* FFI signature is correct, but invocation is wrong */
            mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "ffi-ed function takes no arguments");
          } else {
            /*
             * FFI signature is wrong: we can't have "void" as a non-first
             * "argument"
             */
            mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "bad ffi arg #%d type: \"void\"", i);
          }
          ret = 0;
          goto clean;
        case CVAL_TYPE_USERDATA:
          /* Userdata for the callback */
          if (cbdata.userdata_idx != -1) {
            mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "two or more userdata args: #%d and %d", cbdata.userdata_idx, i);
            ret = 0;
            goto clean;
          }
          cbdata.userdata = arg;
          cbdata.userdata_idx = i;
          break;
        case CVAL_TYPE_INT:
          ffi_set_int32(&args[i], mjs_get_int(mjs, arg));
          break;
        case CVAL_TYPE_DOUBLE:
          ffi_set_double(&args[i], mjs_get_double(mjs, arg));
          break;
        case CVAL_TYPE_CHAR_PTR:
          if (!mjs_is_string(arg)) {
            mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "actual arg #%d is not a string", i);
            ret = 0;
            goto clean;
          }
          argvs[i] = arg;
          ffi_set_ptr(&args[i], (void *) mjs_get_cstring(mjs, &argvs[i]));
          break;
        case CVAL_TYPE_VOID_PTR:
          if (!mjs_is_foreign(arg)) {
            mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "actual arg #%d is not a ptr", i);
            ret = 0;
            goto clean;
          }
          ffi_set_ptr(&args[i], (void *) mjs_get_ptr(mjs, arg));
          break;
        case CVAL_TYPE_INVALID:
          /* parse_cval_type() has already set a more detailed error */
          mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "wrong arg type");
          ret = 0;
          goto clean;
        default:
          abort();
          break;
      }
    }

    a = ae + 1;
    if (*a == '\0') a = NULL;
  }

  if (mjs->dlsym == NULL) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "resolver is not set, call mjs_set_ffi_resolver");
    ret = 0;
    goto clean;
  }

  mg_asprintf(&buf, 0, "%.*s", (int) (e - n), n);
  fn = (ffi_fn_t) mjs->dlsym(RTLD_DEFAULT, buf);
  free(buf);

  if (fn == NULL) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "cannot resolve function %s", buf);
    ret = 0;
    goto clean;
  }

  if (cbdata.userdata_idx >= 0 && cbdata.func_idx >= 0) {
    /* the function takes a callback */

    /* Get C callback implementation by the given signature */
    cb_fn_t *cb_fn = get_cb_impl_by_signature(&cbdata.sig);
    if (cb_fn == NULL) {
      mjs_prepend_errorf(mjs, MJS_TYPE_ERROR,
          "the callback signature '%.*s' is valid, but there's no existing callback implementation for it",
          cbdata.signature_len, cbdata.signature
          );
      ret = 0;
      goto clean;
    }

    /*
     * Get cbargs: either reuse the existing one (if the matching item exists),
     * or create a new one.
     */
    struct ffi_cb_args *cbargs = NULL;
    struct ffi_cb_args **pitem = ffi_get_matching(
        &mjs->ffi_cb_args, cbdata.func, cbdata.userdata
        );

    if (*pitem == NULL) {
      /* No matching cbargs item; we need to add a new one */
      cbargs = calloc(1, sizeof(*cbargs));
      cbargs->mjs = mjs;
      cbargs->func = cbdata.func;
      cbargs->userdata = cbdata.userdata;
      memcpy(&cbargs->sig, &cbdata.sig, sizeof(cbargs->sig));

      /* Establish a link to the newly allocated item */
      *pitem = cbargs;
    } else {
      /* Found matching item: reuse it */
      cbargs = *pitem;
    }

    ffi_set_ptr(&args[cbdata.func_idx], cb_fn);
    ffi_set_ptr(&args[cbdata.userdata_idx], cbargs);
  } else if (!(cbdata.userdata_idx == -1 && cbdata.func_idx == -1)) {
    /*
     * incomplete signature: it contains either the function pointer or
     * userdata. It should contain both or none.
     */
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "function pointer and userdata can't live without one another");
    ret = 0;
    goto clean;
  }

  ffi_call(fn, nargs, &res, args);

  switch (rtype) {
    case CVAL_TYPE_CHAR_PTR: {
      const char *s = (const char *) (uintptr_t) res.v.i;
      resv = mjs_mk_string(mjs, s, ~0, 1);
      break;
    }
    case CVAL_TYPE_VOID_PTR:
      resv = mjs_mk_foreign(mjs, (void *) (uintptr_t) res.v.i);
      break;
    case CVAL_TYPE_INT:
      resv = mjs_mk_number(mjs, res.v.i);
      break;
    default:
      resv = mjs_mk_undefined();
      break;
  }
clean:
  if (!ret) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "failed to call FFI signature \"%s\"", s);
  }
  mjs_push(mjs, resv);
  return ret;
}

/*
 * TODO(dfrank): make it return boolean (when booleans are supported), instead
 * of a number
 */
MJS_PRIVATE void mjs_ffi_cb_free(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int nargs = mjs_get_int(mjs, mjs_pop(mjs));
  mjs_val_t ret = mjs_mk_number(mjs, 0);
  mjs_val_t func = MJS_UNDEFINED;
  mjs_val_t userdata = MJS_UNDEFINED;
  struct ffi_cb_args **pitem = NULL;

  if (nargs < 1) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing argument 'func'");
    goto clean;
  }

  if (nargs < 2) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing argument 'userdata'");
    goto clean;
  }

  /* get user data to free */
  func = mjs_pop(mjs);
  userdata = mjs_pop(mjs);

  pitem = ffi_get_matching(&mjs->ffi_cb_args, func, userdata);

  if (*pitem == NULL) {
    /* No matching cbargs item: will return false */
    goto clean;
  } else {
    /* Found matching item: remove it from the linked list, and free */
    struct ffi_cb_args *cbargs = *pitem;
    *pitem = cbargs->next;
    free(cbargs);
    ret = mjs_mk_number(mjs, 1);
  }

clean:
  mjs_push(mjs, ret);
}

MJS_PRIVATE void mjs_ffi_args_free_list(struct mjs *mjs) {
  ffi_cb_args_t *next = mjs->ffi_cb_args;

  while (next != NULL) {
    ffi_cb_args_t *cur = next;
    next = next->next;
    free(cur);
  }
}

MJS_PRIVATE void mjs_ffi_sig_init(ffi_sig_t *sig) {
  memset(sig->val_types, CVAL_TYPE_NONE, MJS_CB_SIGNATURE_MAX_SIZE);
}

MJS_PRIVATE int mjs_ffi_sig_set_val_type(
    ffi_sig_t *sig, int idx, cval_type_t type
    ) {
  if (idx < MJS_CB_SIGNATURE_MAX_SIZE) {
    sig->val_types[idx] = type;
    return 1;
  } else {
    /* Index is too large */
    return 0;
  }
}

MJS_PRIVATE struct ffi_sig_stat mjs_ffi_sig_stat_get(
    struct mjs *mjs, const ffi_sig_t *sig
    ) {
  struct ffi_sig_stat ret;
  int i;

  memset(&ret, 0, sizeof(ret));
  ret.is_valid = 1;

  /* Make sure return type is fine */
  if (sig->val_types[0] != CVAL_TYPE_NONE
      && sig->val_types[0] != CVAL_TYPE_INT
      && sig->val_types[0] != CVAL_TYPE_DOUBLE
      ) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "wrong return value type");
    ret.is_valid = 0;
    goto clean;
  }

  /* Handle argument types */
  for (i = 1; i < MJS_CB_SIGNATURE_MAX_SIZE; i++) {
    cval_type_t type = sig->val_types[i];
    switch (type) {
      case CVAL_TYPE_USERDATA:
        if (ret.userdata_idx != 0) {
          /* There must be exactly one userdata arg, but we have more */
          mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "more than one userdata arg: #%d and #%d", (ret.userdata_idx - 1), (i - 1));
          ret.is_valid = 0;
          goto clean;
        }
        ret.userdata_idx = i;
        break;
      case CVAL_TYPE_INT:
      case CVAL_TYPE_VOID_PTR:
      case CVAL_TYPE_CHAR_PTR:
        /* Do nothing */
        break;
      case CVAL_TYPE_DOUBLE:
        ret.args_double_cnt++;
        break;
      case CVAL_TYPE_NONE:
        /* No more arguments */
        goto args_over;
      default:
        ret.is_valid = 0;
        goto clean;
    }

    ret.args_cnt++;
  }
args_over:

  if (ret.userdata_idx == 0) {
    /* No userdata arg */
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "no userdata arg");
    ret.is_valid = 0;
    goto clean;
  }

clean:
  return ret;
}

MJS_PRIVATE int mjs_ffi_is_regular_word(cval_type_t type) {
  switch (type) {
    case CVAL_TYPE_INT:
      return 1;
    default:
      return 0;
  }
}

MJS_PRIVATE int mjs_ffi_is_regular_word_or_void(cval_type_t type) {
  return (type == CVAL_TYPE_NONE || mjs_ffi_is_regular_word(type));
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
/* Amalgamated: #include "mjs/ffi.h" */

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
 * mark an array of `mjs_val_t` values (*not pointers* to them)
 */
static void gc_mark_val_array(struct mjs *mjs, mjs_val_t *vals, size_t len) {
  mjs_val_t *vp;
  for (vp = vals; vp < vals + len; vp++) {
    gc_mark(mjs, *vp);
    gc_mark_string(mjs, vp);
  }
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
 * mark an mbuf containing `mjs_val_t` values (*not pointers* to them)
 */
static void gc_mark_mbuf_val(struct mjs *mjs, const struct mbuf *mbuf) {
  gc_mark_val_array(mjs, (mjs_val_t *) mbuf->buf, mbuf->len / sizeof(mjs_val_t));
}

static void gc_mark_bf_stack(struct mjs *mjs, struct bf_stack *stack) {
  size_t i;
  mjs_val_t *v;
  for (i = 0, v = (mjs_val_t *)stack->stack; i < stack->pos; i++, v++) {
    gc_mark(mjs, *v);
    gc_mark_string(mjs, v);
  }
}

static void gc_mark_ffi_cbargs_list(struct mjs *mjs, ffi_cb_args_t *cbargs) {
  for (; cbargs != NULL; cbargs = cbargs->next) {
    gc_mark(mjs, cbargs->func);
    gc_mark_string(mjs, &cbargs->func);
    gc_mark(mjs, cbargs->userdata);
    gc_mark_string(mjs, &cbargs->userdata);
  }
}

/* Perform garbage collection */
void mjs_gc(struct mjs *mjs, int full) {
  gc_mark_val_array(mjs, (mjs_val_t *) &mjs->vals, sizeof(mjs->vals) / sizeof(mjs_val_t));

  gc_mark_mbuf_pt(mjs, &mjs->owned_values);
  gc_mark_mbuf_val(mjs, &mjs->scopes);

  gc_mark_bf_stack(mjs, &mjs->vm.dstack);
  gc_mark_bf_stack(mjs, &mjs->vm.rstack);

  gc_mark(mjs, (mjs_val_t)mjs->vm.tmp);
  gc_mark_string(mjs, (mjs_val_t *)&mjs->vm.tmp);

  gc_mark_ffi_cbargs_list(mjs, mjs->ffi_cb_args);

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
#line 1 "mjs/json.c"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

/* Amalgamated: #include "mjs/core.h" */
/* Amalgamated: #include "mjs/object.h" */
/* Amalgamated: #include "mjs/array.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/primitive.h" */
/* Amalgamated: #include "mjs/conversion.h" */
/* Amalgamated: #include "mjs/json.h" */
/* Amalgamated: #include "common/str_util.h" */
/* Amalgamated: #include "common/cs_strtod.h" */
/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "frozen/frozen.h" */

#define BUF_LEFT(size, used) (((size_t)(used) < (size)) ? ((size) - (used)) : 0)

/*
 * Returns whether the value of given type should be skipped when generating
 * JSON output
 *
 * So far it always returns 0, but we might add some logic later, if we
 * implement some non-jsonnable objects
 */
static int should_skip_for_json(enum mjs_type type) {
  int ret;
  switch (type) {
    /* All permitted values */
    case MJS_TYPE_NULL:
    case MJS_TYPE_BOOLEAN:
    case MJS_TYPE_NUMBER:
    case MJS_TYPE_STRING:
    case MJS_TYPE_OBJECT_GENERIC:
    case MJS_TYPE_OBJECT_ARRAY:
      ret = 0;
      break;
    default:
      ret = 1;
      break;
  }
  return ret;
}

static const char *hex_digits = "0123456789abcdef";
static char *append_hex(char *buf, char *limit, uint8_t c) {
  if (buf < limit) *buf++ = 'u';
  if (buf < limit) *buf++ = '0';
  if (buf < limit) *buf++ = '0';
  if (buf < limit) *buf++ = hex_digits[(int) ((c >> 4) % 0xf)];
  if (buf < limit) *buf++ = hex_digits[(int) (c & 0xf)];
  return buf;
}

/*
 * Appends quoted s to buf. Any double quote contained in s will be escaped.
 * Returns the number of characters that would have been added,
 * like snprintf.
 * If size is zero it doesn't output anything but keeps counting.
 */
static int snquote(char *buf, size_t size, const char *s, size_t len) {
  char *limit = buf + size - 1;
  const char *end;
  /*
   * String single character escape sequence:
   * http://www.ecma-international.org/ecma-262/6.0/index.html#table-34
   *
   * 0x8 -> \b
   * 0x9 -> \t
   * 0xa -> \n
   * 0xb -> \v
   * 0xc -> \f
   * 0xd -> \r
   */
  const char *specials = "btnvfr";
  size_t i = 0;

  i++;
  if (buf < limit) *buf++ = '"';

  for (end = s + len; s < end; s++) {
    if (*s == '"' || *s == '\\') {
      i++;
      if (buf < limit) *buf++ = '\\';
    } else if (*s >= '\b' && *s <= '\r') {
      i += 2;
      if (buf < limit) *buf++ = '\\';
      if (buf < limit) *buf++ = specials[*s - '\b'];
      continue;
    } else if ((unsigned char) *s < '\b' || (*s > '\r' && *s < ' ')) {
      i += 6 /* \uXXXX */;
      if (buf < limit) *buf++ = '\\';
      buf = append_hex(buf, limit, (uint8_t) *s);
      continue;
    }
    i++;
    if (buf < limit) *buf++ = *s;
  }

  i++;
  if (buf < limit) *buf++ = '"';

  if (size != 0) {
    *buf = '\0';
  }
  return i;
}

MJS_PRIVATE mjs_err_t to_json_or_debug(struct mjs *mjs, mjs_val_t v,
    char *buf, size_t size,
    size_t *res_len, uint8_t is_debug) {
  mjs_val_t el;
  char *vp;
  mjs_err_t rcode = MJS_OK;
  size_t len = 0;
  /*
   * TODO(dfrank) : also push all `mjs_val_t`s that are declared below
   */

  if (size > 0) *buf = '\0';

  if (!is_debug && should_skip_for_json(mjs_get_type(mjs, v))) {
    goto clean;
  }

  for (vp = mjs->json_visited_stack.buf;
      vp < mjs->json_visited_stack.buf + mjs->json_visited_stack.len;
      vp += sizeof(mjs_val_t)) {
    if (*(mjs_val_t *) vp == v) {
      strncpy(buf, "[Circular]", size);
      len = 10;
      goto clean;
    }
  }

  switch (mjs_get_type(mjs, v)) {
    case MJS_TYPE_NULL:
    case MJS_TYPE_BOOLEAN:
    case MJS_TYPE_NUMBER:
    case MJS_TYPE_UNDEFINED:
    case MJS_TYPE_FOREIGN:
      /* For those types, regular `mjs_to_string()` works */
      {
        /* TODO: refactor: mjs_to_string allocates memory every time */
        char *p = NULL;
        int need_free = 0;
        rcode = mjs_to_string(mjs, &v, &p, &len, &need_free);
        c_snprintf(buf, size, "%.*s", (int) len, p);
        if (need_free) {
          free(p);
        }
      }
      goto clean;

    case MJS_TYPE_STRING: {
      /*
       * For strings we can't just use `primitive_to_str()`, because we need
       * quoted value
       */
      size_t n;
      const char *str = mjs_get_string(mjs, &v, &n);
      len = snquote(buf, size, str, n);
      goto clean;
    }

    case MJS_TYPE_OBJECT_GENERIC: {
      char *b = buf;

      mbuf_append(&mjs->json_visited_stack, (char *) &v, sizeof(v));
      b += c_snprintf(b, BUF_LEFT(size, b - buf), "{");

      struct mjs_object *o = get_object_struct(v);
      struct mjs_property *prop = NULL;
      for (prop = o->properties; prop != NULL; prop = prop->next) {
        size_t n;
        const char *s;
        if (!is_debug && should_skip_for_json(mjs_get_type(mjs, prop->value))) {
          continue;
        }
        if (b - buf != 1) { /* Not the first property to be printed */
          b += c_snprintf(b, BUF_LEFT(size, b - buf), ",");
        }
        s = mjs_get_string(mjs, &prop->name, &n);
        b += c_snprintf(b, BUF_LEFT(size, b - buf), "\"%.*s\":", (int) n, s);
        {
          size_t tmp = 0;
          rcode = to_json_or_debug(mjs, prop->value, b, BUF_LEFT(size, b - buf), &tmp,
              is_debug);
          if (rcode != MJS_OK) {
            goto clean_iter;
          }
          b += tmp;
        }
      }

      b += c_snprintf(b, BUF_LEFT(size, b - buf), "}");
      mjs->json_visited_stack.len -= sizeof(v);

clean_iter:
      len = b - buf;
      goto clean;
    }
    case MJS_TYPE_OBJECT_ARRAY: {
      int has;
      char *b = buf;
      size_t i, alen = mjs_array_length(mjs, v);
      mbuf_append(&mjs->json_visited_stack, (char *) &v, sizeof(v));
      b += c_snprintf(b, BUF_LEFT(size, b - buf), "[");
      for (i = 0; i < alen; i++) {
        el = mjs_array_get2(mjs, v, i, &has);
        if (has) {
          size_t tmp = 0;
          if (!is_debug && should_skip_for_json(mjs_get_type(mjs, el))) {
            b += c_snprintf(b, BUF_LEFT(size, b - buf), "null");
          } else {
            rcode = to_json_or_debug(mjs, el, b, BUF_LEFT(size, b - buf), &tmp,
                is_debug);
            if (rcode != MJS_OK) {
              goto clean;
            }
          }
          b += tmp;
        } else {
          b += c_snprintf(b, BUF_LEFT(size, b - buf), "null");
        }
        if (i != alen - 1) {
          b += c_snprintf(b, BUF_LEFT(size, b - buf), ",");
        }
      }
      b += c_snprintf(b, BUF_LEFT(size, b - buf), "]");
      mjs->json_visited_stack.len -= sizeof(v);
      len = b - buf;
      goto clean;
    }

    case MJS_TYPES_CNT:
      abort();
  }

  abort();

  len = 0; /* for compilers that don't know about abort() */
  goto clean;

clean:
  if (rcode != MJS_OK) {
    len = 0;
  }
  if (res_len != NULL) {
    *res_len = len;
  }
  return rcode;
}

MJS_PRIVATE mjs_err_t mjs_json_stringify(struct mjs *mjs, mjs_val_t v, char *buf,
    size_t size, char **res) {
  mjs_err_t rcode = MJS_OK;
  char *p = buf;
  size_t len;

  to_json_or_debug(mjs, v, buf, size, &len, 0);

  if (len >= size) {
    /* Buffer is not large enough. Allocate a bigger one */
    p = (char *) malloc(len + 1);
    rcode = mjs_json_stringify(mjs, v, p, len + 1, res);
    assert(*res == p);
    goto clean;
  } else {
    *res = p;
    goto clean;
  }

clean:
  /*
   * If we're going to return an error, and we allocated a buffer, then free
   * it. Otherwise, caller should free it.
   */
  if (rcode != MJS_OK && p != buf) {
    free(p);
  }
  return rcode;
}

/*
 * JSON parsing frame: a separate frame is allocated for each nested
 * object/array during parsing
 */
struct json_parse_frame {
  mjs_val_t val;
  struct json_parse_frame *up;
};

/*
 * Context for JSON parsing by means of json_walk()
 */
struct json_parse_ctx {
  struct mjs *mjs;
  mjs_val_t result;
  struct json_parse_frame *frame;
};

/* Allocate JSON parse frame */
static struct json_parse_frame *alloc_json_frame(struct json_parse_ctx *ctx,
    mjs_val_t v) {
  struct json_parse_frame *frame =
    (struct json_parse_frame *) calloc(sizeof(struct json_parse_frame), 1);
  frame->val = v;
  mjs_own(ctx->mjs, &frame->val);
  return frame;
}

/* Free JSON parse frame, return the previous one (which may be NULL) */
static struct json_parse_frame *free_json_frame(
    struct json_parse_ctx *ctx, struct json_parse_frame *frame) {
  struct json_parse_frame *up = frame->up;
  mjs_disown(ctx->mjs, &frame->val);
  free(frame);
  return up;
}

/* Callback for json_walk() */
static void frozen_cb(void *data, const char *name, size_t name_len,
                      const char *path, const struct json_token *token) {
  struct json_parse_ctx *ctx = (struct json_parse_ctx *) data;
  mjs_val_t v = MJS_UNDEFINED;

  (void) path;

  mjs_own(ctx->mjs, &v);

  switch (token->type) {
    case JSON_TYPE_STRING:
      v = mjs_mk_string(ctx->mjs, token->ptr, token->len, 1 /* copy */);
      break;
    case JSON_TYPE_NUMBER:
      v = mjs_mk_number(ctx->mjs, cs_strtod(token->ptr, NULL));
      break;
    case JSON_TYPE_TRUE:
      v = mjs_mk_boolean(ctx->mjs, 1);
      break;
    case JSON_TYPE_FALSE:
      v = mjs_mk_boolean(ctx->mjs, 0);
      break;
    case JSON_TYPE_NULL:
      v = MJS_NULL;
      break;
    case JSON_TYPE_OBJECT_START:
      v = mjs_mk_object(ctx->mjs);
      break;
    case JSON_TYPE_ARRAY_START:
      v = mjs_mk_array(ctx->mjs);
      break;

    case JSON_TYPE_OBJECT_END:
    case JSON_TYPE_ARRAY_END: {
      /* Object or array has finished: deallocate its frame */
      ctx->frame = free_json_frame(ctx, ctx->frame);
    } break;

    default:
      LOG(LL_ERROR, ("Wrong token type %d\n", token->type));
      break;
  }

  if (!mjs_is_undefined(v)) {
    if (name != NULL && name_len != 0) {
      /* Need to define a property on the current object/array */
      if (mjs_is_object(ctx->frame->val)) {
        mjs_set(ctx->mjs, ctx->frame->val, name, name_len, v);
      } else if (mjs_is_array(ctx->frame->val)) {
        /*
         * TODO(dfrank): consult name_len. Currently it's not a problem due to
         * the implementation details of frozen, but it might change
         */
        int idx = (int) cs_strtod(name, NULL);
        mjs_array_set(ctx->mjs, ctx->frame->val, idx, v);
      } else {
        LOG(LL_ERROR, ("Current value is neither object nor array\n"));
      }
    } else {
      /* This is a root value */
      assert(ctx->frame == NULL);

      /*
       * This value will also be the overall result of JSON parsing
       * (it's already owned by the `mjs_alt_json_parse()`)
       */
      ctx->result = v;
    }

    if (token->type == JSON_TYPE_OBJECT_START ||
        token->type == JSON_TYPE_ARRAY_START) {
      /* New object or array has just started, so we need to allocate a frame
       * for it */
      struct json_parse_frame *new_frame = alloc_json_frame(ctx, v);
      new_frame->up = ctx->frame;
      ctx->frame = new_frame;
    }
  }

  mjs_disown(ctx->mjs, &v);
}

MJS_PRIVATE mjs_err_t mjs_json_parse(struct mjs *mjs, const char *str,
                                     size_t len, mjs_val_t *res) {
  struct json_parse_ctx *ctx =
    (struct json_parse_ctx *) calloc(sizeof(struct json_parse_ctx), 1);
  int json_res;
  enum mjs_err rcode = MJS_OK;

  ctx->mjs = mjs;
  ctx->result = MJS_UNDEFINED;
  ctx->frame = NULL;

  mjs_own(mjs, &ctx->result);

  json_res = json_walk(str, len, frozen_cb, ctx);

  if (json_res >= 0) {
    /* Expression is parsed successfully */
    *res = ctx->result;

    /* There should be no allocated frames */
    assert(ctx->frame == NULL);
  } else {
    /* There was an error during parsing */
    rcode = MJS_TYPE_ERROR;
    mjs_prepend_errorf(mjs, rcode, "invalid JSON string");

    /* There might be some allocated frames in case of malformed JSON */
    while (ctx->frame != NULL) {
      ctx->frame = free_json_frame(ctx, ctx->frame);
    }
  }

  mjs_disown(mjs, &ctx->result);
  free(ctx);

  return rcode;
}
#ifdef MG_MODULE_LINES
#line 1 "mjs/main.c"
#endif
/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */
#ifdef MJS_MAIN

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

/* Amalgamated: #include "common/cs_dbg.h" */

/* Amalgamated: #include "mjs/exec.h" */
/* Amalgamated: #include "mjs/ffi.h" */
/* Amalgamated: #include "mjs/parser.h" */
/* Amalgamated: #include "mjs/util.h" */

int main(int argc, char **argv) {
  int i, j, nexprs = 0;
  const char *exprs[16];
  struct mjs *mjs = mjs_create();
  mjs_err_t err;
  int compile = 0, print_stack = 0;

  mjs_set_ffi_resolver(mjs, dlsym);

  /* Execute inline code */
  for (i = 1; i < argc && argv[i][0] == '-'; i++) {
    if (strcmp(argv[i], "-c") == 0) {
      compile = 1;
    } else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
      exprs[nexprs++] = argv[i + 1];
      i++;
    } else if (strcmp(argv[i], "-s") == 0) {
      print_stack = 1;
    } else if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
      cs_log_set_level(atoi(argv[i + 1]));
      i++;
    }
  }

  for (j = 0; j < nexprs && j < (int) (sizeof(exprs) / sizeof(exprs[0])); j++) {
    mjs_val_t res;
    if (compile) {
      bf_word_ptr_t last_code = mjs->last_code;
      struct mjs_parse_ctx ctx;
      if ((err = mjs_parse(mjs, exprs[j], &ctx)) != MJS_OK) {
        printf("%s\n", mjs_strerror(mjs, err));
        return 1;
      }
      mjs_dump_bcode(mjs, "/dev/stdout", last_code, mjs->last_code);
    } else {
      if ((err = mjs_exec(mjs, exprs[j], &res)) != MJS_OK) {
        printf("%s\n", mjs_strerror(mjs, err));
        return 1;
      }
      mjs_println(mjs, res);
    }
  }

  if (print_stack) {
    printf("---\n");
    bf_print_stack(&mjs->vm, &mjs->vm.dstack);
    printf("\n");
  }

  return 0;
}
#endif
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
/* Amalgamated: #include "mjs/conversion.h" */

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
  return (v & MJS_TAG_MASK) == MJS_TAG_OBJECT || (v & MJS_TAG_MASK) == MJS_TAG_OBJECT_ARRAY;
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
  char *s = NULL;
  int need_free = 0;
  mjs_val_t ret = MJS_UNDEFINED;

  mjs_err_t err = mjs_to_string(mjs, &name, &s, &n, &need_free);

  if (err == MJS_OK) {
    /* Successfully converted name value to string: get the property */
    ret = mjs_get(mjs, obj, s, n);
  }

  if (need_free) {
    free(s);
    s = NULL;
  }
  return ret;
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
  char *s = NULL;
  int need_free = 0;

  mjs_err_t err = mjs_to_string(mjs, &name, &s, &n, &need_free);

  if (err == MJS_OK) {
    /* Successfully converted name value to string: set the property */
    err = mjs_set(mjs, obj, s, n, val);
  }

  if (need_free) {
    free(s);
    s = NULL;
  }

  return err;
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
/* Amalgamated: #include "mjs/array.h" */
/* Amalgamated: #include "mjs/string.h" */
/* Amalgamated: #include "mjs/conversion.h" */
/* Amalgamated: #include "mjs/util.h" */
/* Amalgamated: #include "mjs/json.h" */
/* Amalgamated: #include "mjs/parser_state.h" */
/* Amalgamated: #include "mjs/parser.h" */
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
  mjs_val_t val = MJS_UNDEFINED;

  /*
   * For "method invocation pattern": remember the last object against which
   * `getprop` was executed, and reset the words_since_getprop counter
   */
  mjs->vals.last_getprop_obj = bf_pop(&vm->dstack);
  mjs->words_since_getprop = (enum getprop_distance)0;

  if (mjs_is_object(mjs->vals.last_getprop_obj)) {
    /* The "object" is actually an object: just take a property from it */
    val = mjs_get_v(mjs, mjs->vals.last_getprop_obj, name);
  } else {
    /*
     * We don't have getters, so in order to support properties which behave
     * like getters (e.g. "string".length), we have to parse name right here,
     * instead of having real built-in prototype objects
     */
    size_t n;
    char *s = NULL;
    int need_free = 0;

    mjs_err_t err = mjs_to_string(mjs, &name, &s, &n, &need_free);

    if (err == MJS_OK) {
      if (mjs_is_string(mjs->vals.last_getprop_obj)) {
        if (strcmp(s, "length") == 0) {
          size_t val_len;
          mjs_get_string(mjs, &mjs->vals.last_getprop_obj, &val_len);
          val = mjs_mk_number(mjs, val_len);
        }
      }
    }

    if (need_free) {
      free(s);
      s = NULL;
    }
  }

  bf_push(&vm->dstack, val);
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
  struct mjs_property *p = NULL;
  size_t n;
  const char *s = mjs_get_string(mjs, &name, &n);

  assert(mjs->scopes.len % sizeof(mjs_val_t) == 0);
  int idx = mjs->scopes.len / sizeof(mjs_val_t);
  int lim = mjs_get_int(mjs, mjs->vals.min_scope);
  while (p == NULL && idx > 0) {
    mjs_val_t *scope;
    idx--;

    if (idx < lim) {
      /*
       * idx points to the caller's scope already, so, resort to global object
       */
      idx = 0;
    }

    scope = (mjs_val_t *)(mjs->scopes.buf + idx * sizeof(mjs_val_t));
    p = mjs_get_own_property(mjs, *scope, s, n);
  }

  return p;
}

void mjs_op_getvar(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t name = bf_pop(&vm->dstack);
  struct mjs_property *p = mjs_lookup_property(mjs, name);
  if (p != NULL) {
    bf_push(&vm->dstack, p->value);
  } else {
    size_t n;
    const char *s = mjs_get_string(mjs, &name, &n);
    bf_push(&vm->dstack, mjs_mk_undefined());
    mjs_set_errorf(mjs, MJS_REFERENCE_ERROR, "%s is not defined", s);
    bf_die(&mjs->vm);
  }
}

void mjs_op_setvar(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t value = bf_pop(&vm->dstack);
  mjs_val_t name = bf_pop(&vm->dstack);
  struct mjs_property *p = mjs_lookup_property(mjs, name);

  if (p != NULL) {
    p->value = value;
  } else {
    size_t n;
    const char *s = mjs_get_string(mjs, &name, &n);
    mjs_set_errorf(mjs, MJS_REFERENCE_ERROR, "%s is not defined", s);
    bf_die(&mjs->vm);
  }
  bf_push(&vm->dstack, value);
}

void mjs_op_createvar(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t name = bf_pop(&vm->dstack);
  size_t n;
  const char *s = mjs_get_string(mjs, &name, &n);
  struct mjs_property *p = mjs_get_own_property(mjs, mjs_scope_tos(mjs), s, n);

  if (p == NULL) {
    mjs_set(mjs, mjs_scope_tos(mjs), s, n, mjs_mk_undefined());
  }
}

void mjs_op_jscall(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t func = bf_pop(&vm->dstack);
  mjs_val_t fthis = bf_pop(&vm->dstack);
  size_t nargs = bf_to_int(bf_tos(&vm->dstack));
  size_t stack_pos = vm->dstack.pos - 1 /* nargs */;

  assert(stack_pos >= nargs);
  /*
   * the jscall word has this stack effect: ( argN .. arg2 arg1 N this f -- res)
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
  bf_push(&vm->rstack, mjs->vals.this_val);
  bf_push(&vm->rstack, bf_from_int(stack_pos - nargs));
  bf_push(&vm->rstack, bf_from_int(MJS_WORD_PTR_jscall_exit));

  mjs->vals.this_val = fthis;

  if (mjs_is_number(func)) {
    vm->ip = bf_to_int(func);
  } else if (mjs_is_foreign(func)) {
    void (*native)(struct bf_vm *vm);
    native = (void (*) (struct bf_vm *vm)) mjs_get_ptr(mjs, func);
    native(vm);
  } else if (mjs_is_string(func)) {
    if (!mjs_ffi_call(mjs, func)) {
      bf_die(&mjs->vm);
    }
  } else if (mjs_is_undefined(func)) {
    mjs_set_errorf(mjs, MJS_TYPE_ERROR, "undefined is not a function");
    bf_die(&mjs->vm);
  } else {
    mjs_set_errorf(mjs, MJS_TYPE_ERROR, "function is of an unknown type");
    bf_die(&mjs->vm);
  }
}

void mjs_op_scope_idx_get(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, bf_from_int(mjs->scopes.len / sizeof(mjs_val_t)));
}

void mjs_op_scope_idx_set(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int32_t scope_idx = bf_to_int(bf_pop(&vm->dstack));
  assert(scope_idx <= mjs->scopes.len / sizeof(mjs_val_t));
  mjs->scopes.len = scope_idx * sizeof(mjs_val_t);
}

void mjs_op_scope_min_get(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs->vals.min_scope);
}

void mjs_op_scope_min_set(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs->vals.min_scope = bf_pop(&vm->dstack);
}

void mjs_op_this_val_get(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs->vals.this_val);
}

void mjs_op_this_val_set(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs->vals.this_val = bf_pop(&vm->dstack);
}

void mjs_op_getframe(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs->vals.call_frame);
}

void mjs_op_setframe(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs->vals.call_frame = bf_pop(&vm->dstack);
}

void mjs_op_scope_push(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_push_scope(mjs, bf_pop(&vm->dstack));
}

void mjs_op_scope_pop(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs_pop_scope(mjs));
}

void mjs_op_scope_tos(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs_scope_tos(mjs));
}

void mjs_op_undefined(struct bf_vm *vm) {
  bf_push(&vm->dstack, mjs_mk_undefined());
}

void mjs_op_this_for_call(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  if (mjs->words_since_getprop == GETPROP_DISTANCE_CALL) {
    bf_push(&vm->dstack, mjs->vals.last_getprop_obj);
  } else {
    bf_push(&vm->dstack, mjs_mk_undefined());
  }
}

void mjs_op_null(struct bf_vm *vm) {
  bf_push(&vm->dstack, mjs_mk_null());
}

void mjs_op_true(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs_mk_boolean(mjs, 1));
}

void mjs_op_false(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs_mk_boolean(mjs, 0));
}

void mjs_op_load(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int nargs = mjs_get_int(mjs, mjs_pop(mjs));
  mjs_val_t ret = MJS_UNDEFINED;
  mjs_err_t err = MJS_OK;
  const char *filename = NULL;

  mjs_val_t filename_v = MJS_UNDEFINED;
  mjs_val_t global_obj_v = MJS_UNDEFINED;
  mjs_val_t global_obj_saved_v = MJS_UNDEFINED;
  int min_scope_saved = -1;

  if (nargs < 1) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing argument 'filename'");
    goto clean;
  }
  filename_v = mjs_pop(mjs);

  if (nargs >= 2) {
    /* Custom Global Object is given */
    mjs_own(mjs, &global_obj_saved_v);
    global_obj_v = mjs_pop(mjs);
    global_obj_saved_v = mjs_scope_get_by_idx(mjs, 0);
    mjs_scope_set_by_idx(mjs, 0, global_obj_v);
  }

  struct mjs_parse_ctx ctx;
  filename = mjs_get_cstring(mjs, &filename_v);

  err = mjs_parse_file(mjs, filename, &ctx);
  if (err != MJS_OK) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "failed to parse code. TODO: details");
    goto clean;
  }

  /* filename will be invalidated after bf_run is called */
  filename = NULL;

  /* get current global object and push it to the stack */
  bf_push(&vm->dstack, mjs_scope_get_by_idx(mjs, 0));
  mjs_op_scope_push(&mjs->vm);
  min_scope_saved = mjs_get_int(mjs, mjs->vals.min_scope);
  mjs->vals.min_scope = mjs_mk_number(mjs, mjs->scopes.len / sizeof(mjs_val_t));

  /* evaluate the code */
  bf_run(vm, ctx.entry);
  ret = bf_pop(&vm->dstack);

  /* drop scope */
  mjs_op_scope_pop(vm);
  bf_pop(&vm->dstack);

clean:
  if (nargs >= 2) {
    /* Custom Global Object was given: restore the original one */
    mjs_scope_set_by_idx(mjs, 0, global_obj_saved_v);
    mjs_disown(mjs, &global_obj_saved_v);
  }

  mjs->vals.min_scope = mjs_mk_number(mjs, min_scope_saved);

  mjs_push(mjs, ret);
}

void mjs_op_json_stringify(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int nargs = mjs_get_int(mjs, mjs_pop(mjs));
  char *p = NULL;
  mjs_val_t ret = MJS_UNDEFINED;
  mjs_val_t val = MJS_UNDEFINED;
  mjs_err_t err = MJS_OK;

  if (nargs < 1) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing a value to stringify");
    goto clean;
  }
  val = mjs_pop(mjs);

  err = mjs_json_stringify(mjs, val, NULL, 0, &p);
  if (err != MJS_OK) {
    goto clean;
  }

  ret = mjs_mk_string(mjs, p, ~0, 1 /* copy */);
  free(p);
  p = NULL;

clean:
  mjs_push(mjs, ret);
}

void mjs_op_json_parse(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int nargs = mjs_get_int(mjs, mjs_pop(mjs));
  const char *str = NULL;
  mjs_val_t ret = MJS_UNDEFINED;
  mjs_val_t str_v = MJS_UNDEFINED;
  mjs_err_t err = MJS_OK;

  if (nargs < 1) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing a string to parse");
    goto clean;
  }
  str_v = mjs_pop(mjs);

  size_t len;
  str = mjs_get_string(mjs, &str_v, &len);

  err = mjs_json_parse(mjs, str, len, &ret);
  if (err != MJS_OK) {
    goto clean;
  }

clean:
  mjs_push(mjs, ret);
}

void mjs_op_div(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  double b = mjs_get_double(mjs, bf_pop(&vm->dstack));
  double a = mjs_get_double(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, a / b));
}

void mjs_op_rem(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int b = mjs_get_int(mjs, bf_pop(&vm->dstack));
  int a = mjs_get_int(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, a % b));
}

void mjs_op_lshift(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int b = mjs_get_int(mjs, bf_pop(&vm->dstack));
  int a = mjs_get_int(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, a << b));
}

void mjs_op_rshift(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int b = mjs_get_int(mjs, bf_pop(&vm->dstack));
  int a = mjs_get_int(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, a >> b));
}

void mjs_op_urshift(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int b = mjs_get_int(mjs, bf_pop(&vm->dstack));
  int a = mjs_get_int(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, (unsigned int)a >> b));
}

void mjs_op_and(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int b = mjs_get_int(mjs, bf_pop(&vm->dstack));
  int a = mjs_get_int(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, a & b));
}

void mjs_op_or(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int b = mjs_get_int(mjs, bf_pop(&vm->dstack));
  int a = mjs_get_int(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, a | b));
}

void mjs_op_xor(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int b = mjs_get_int(mjs, bf_pop(&vm->dstack));
  int a = mjs_get_int(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, a ^ b));
}

void mjs_op_not(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int a = mjs_get_int(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, ~a));
}

void mjs_op_neg(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  double a = mjs_get_double(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_number(mjs, -a));
}

void mjs_op_pos(struct bf_vm *vm) {
  (void) vm;
}

void mjs_op_eq(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  double b = mjs_get_double(mjs, bf_pop(&vm->dstack));
  double a = mjs_get_double(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_boolean(mjs, a == b));
}

void mjs_op_lt(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  double b = mjs_get_double(mjs, bf_pop(&vm->dstack));
  double a = mjs_get_double(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_boolean(mjs, a < b));
}

void mjs_op_gt(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  double b = mjs_get_double(mjs, bf_pop(&vm->dstack));
  double a = mjs_get_double(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_boolean(mjs, a > b));
}

void mjs_op_invert(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int a = mjs_get_bool(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_boolean(mjs, !a));
}

void mjs_op_logical_and(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int b = mjs_get_bool(mjs, bf_pop(&vm->dstack));
  int a = mjs_get_bool(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_boolean(mjs, a && b));
}

void mjs_op_logical_or(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  int b = mjs_get_bool(mjs, bf_pop(&vm->dstack));
  int a = mjs_get_bool(mjs, bf_pop(&vm->dstack));
  bf_push(&vm->dstack, mjs_mk_boolean(mjs, a || b));
}

void mjs_op_mkarr(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  bf_push(&vm->dstack, mjs_mk_array(mjs));
}

void mjs_op_arrpush(struct bf_vm *vm) {
  struct mjs *mjs = (struct mjs *) vm->user_data;
  mjs_val_t val = bf_pop(&vm->dstack);
  mjs_val_t arr = bf_pop(&vm->dstack);
  mjs_array_push(mjs, arr, val);
  bf_push(&vm->dstack, arr);
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
/* Amalgamated: #include "mjs/str_util.h" */
/* Amalgamated: #include "mjs/string.h" */
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
#define DT(a, b) ((a) << 8 | (b))
#define TT(a, b, c) ((a) << 16 | (b) << 8 | (c))
#define QT(a, b, c, d) ((a) << 24 | (b) << 16 | (c) << 8 | (d))

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
    case '&': return TOK_AND;
    case '|': return TOK_OR;
    case '^': return TOK_XOR;
    case '.': return TOK_DOT;
    case '?': return TOK_QUESTION;
    case '!': return TOK_NOT;
    case '~': return TOK_TILDA;
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
    case DT('^','='): return TOK_XOR_ASSIGN;

    case DT('=','='): return TOK_EQ;
    case DT('!','='): return TOK_NE;
    case DT('<','='): return TOK_LE;
    case DT('>','='): return TOK_GE;

    case DT('&','&'): return TOK_LOGICAL_AND;
    case DT('|','|'): return TOK_LOGICAL_OR;

    case TT('<','<','='): return TOK_LSHIFT_ASSIGN;
    case TT('>','>','='): return TOK_RSHIFT_ASSIGN;
    case TT('>','>','>'): return TOK_URSHIFT;

    case QT('>','>','>','='): return TOK_URSHIFT_ASSIGN;

    case '<': return TOK_LT;
    case '>': return TOK_GT;

    case TOK_NUM: return TOK_NUMBER;
    case TOK_STR: return TOK_STRING_LITERAL;
    case TOK_IDENT: return TOK_IDENTIFIER;
    case TOK_KEYWORD_LET: return TOK_LET;
    case TOK_KEYWORD_UNDEFINED: return TOK_UNDEFINED;
    case TOK_KEYWORD_NULL: return TOK_NULL;
    case TOK_KEYWORD_IF: return TOK_IF;
    case TOK_KEYWORD_ELSE: return TOK_ELSE;
    case TOK_KEYWORD_TRUE: return TOK_TRUE;
    case TOK_KEYWORD_FALSE: return TOK_FALSE;
    case TOK_KEYWORD_FUNCTION: return TOK_FUNCTION;
    case TOK_KEYWORD_RETURN: return TOK_RETURN;
    case TOK_KEYWORD_WHILE: return TOK_WHILE;
    case TOK_KEYWORD_FOR: return TOK_FOR;
    case TOK_KEYWORD_THIS: return TOK_THIS;
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
    return mjs_emit_uint8(ctx, (bf_opcode_t) offset);
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

  while (mjs_is_ident(*ident) || mjs_is_digit(*ident)) {
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

bf_word_ptr_t mjs_emit_assign(struct mjs_parse_ctx *ctx, const char *name,
                              bf_word_ptr_t val, bf_opcode_t op) {
  bf_word_ptr_t start = mjs_emit_str_or_ident(ctx, name);
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

bf_word_ptr_t mjs_emit_objprop(struct mjs_parse_ctx *ctx, bf_word_ptr_t obj,
                               bf_word_ptr_t prop, int for_op) {
  bf_word_ptr_t start = mjs_emit_call(ctx, obj);
  mjs_emit_call(ctx, prop);
  if (for_op) {
    mjs_emit(ctx, MJS_OP_2dup);
    mjs_emit(ctx, MJS_OP_getprop);
  }
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_objprop_assign(struct mjs_parse_ctx *ctx,
                                      bf_word_ptr_t prop, bf_word_ptr_t val,
                                      bf_opcode_t op) {
  bf_word_ptr_t start = mjs_emit_call(ctx, prop);
  mjs_emit_call(ctx, val);
  if (op) {
    mjs_emit(ctx, op);
  }
  mjs_emit(ctx, MJS_OP_setprop);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_postop(struct mjs_parse_ctx *ctx, const char *name,
                              bf_opcode_t op) {
  bf_word_ptr_t start = mjs_emit_str_or_ident(ctx, name);
  mjs_emit(ctx, MJS_OP_dup);
  mjs_emit(ctx, MJS_OP_getvar);
  mjs_emit(ctx, MJS_OP_dup);
  mjs_emit(ctx, MJS_OP_GT_r);
  mjs_emit(ctx, MJS_OP_one);
  mjs_emit(ctx, op);
  mjs_emit(ctx, MJS_OP_setvar);
  mjs_emit(ctx, MJS_OP_drop);
  mjs_emit(ctx, MJS_OP_r_GT);
  mjs_emit(ctx, MJS_OP_exit);
  return start;
}

bf_word_ptr_t mjs_emit_postop_prop(struct mjs_parse_ctx *ctx, bf_word_ptr_t obj,
                                   const char *name, bf_opcode_t op) {
  bf_word_ptr_t start = mjs_emit_call(ctx, obj);
  mjs_emit_str_or_ident(ctx, name);
  mjs_emit(ctx, MJS_OP_2dup);
  mjs_emit(ctx, MJS_OP_getprop);
  mjs_emit(ctx, MJS_OP_dup);
  mjs_emit(ctx, MJS_OP_GT_r);
  mjs_emit(ctx, MJS_OP_one);
  mjs_emit(ctx, op);
  mjs_emit(ctx, MJS_OP_setprop);
  mjs_emit(ctx, MJS_OP_drop);
  mjs_emit(ctx, MJS_OP_r_GT);
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

mjs_val_t mjs_mk_boolean(struct mjs *mjs, int v) {
  (void) mjs;
  return (!!v) | MJS_TAG_BOOLEAN;
}

int mjs_get_bool(struct mjs *mjs, mjs_val_t v) {
  (void) mjs;
  if (mjs_is_boolean(v)) {
    return v & 1;
  } else {
    return 0;
  }
}

int mjs_is_boolean(mjs_val_t v) {
  return (v & MJS_TAG_MASK) == MJS_TAG_BOOLEAN;
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

MJS_PRIVATE unsigned long cstr_to_ulong(const char *s, size_t len, int *ok) {
  char *e;
  unsigned long res = strtoul(s, &e, 10);
  *ok = (e == s + len) && len != 0;
  return res;
}

MJS_PRIVATE mjs_err_t str_to_ulong(struct mjs *mjs, mjs_val_t v, int *ok,
                                      unsigned long *res) {
  enum mjs_err ret = MJS_OK;
  size_t len = 0;
  const char *p = mjs_get_string(mjs, &v, &len);
  *res = cstr_to_ulong(p, len, ok);

  return ret;
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
static int mjs_is_space(int c) {
  return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}

MJS_PRIVATE int mjs_is_digit(int c) {
  return c >= '0' && c <= '9';
}

static int mjs_is_alpha(int c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

MJS_PRIVATE int mjs_is_ident(int c) {
  return c == '_' || c == '$' || mjs_is_alpha(c);
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

// Try to parse a token that takes exactly 3 chars.
static int longtok3(struct pstate *p, char a, char b, char c) {
  if (p->pos[0] == a && p->pos[1] == b && p->pos[2] == c) {
    p->tok_len += 2;
    p->pos += 2;
    return p->pos[-2] << 16 | p->pos[-1] << 8 | p->pos[0];
  }
  return TOK_EOF;
}

// Try to parse a token that takes exactly 4 chars.
static int longtok4(struct pstate *p, char a, char b, char c, char d) {
  if (p->pos[0] == a && p->pos[1] == b && p->pos[2] == c && p->pos[3] == d) {
    p->tok_len += 3;
    p->pos += 3;
    return p->pos[-3] << 24 | p->pos[-2] << 16 | p->pos[-1] << 8 | p->pos[0];
  }
  return TOK_EOF;
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
  if (!mjs_is_alpha(s[0])) return 0;
  for (i = 0; reserved[i] != NULL; i++) {
    if (len == (int) strlen(reserved[i]) && strncmp(s, reserved[i], len) == 0)
      return i + 1;
  }
  return 0;
}

static int getident(struct pstate *p) {
  while (mjs_is_ident(p->pos[0]) || mjs_is_digit(p->pos[0])) p->pos++;
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
    while (mjs_is_space(p->pos[0])) {
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

  if (mjs_is_digit(p->pos[0])) {
    tok = getnum(p);
  } else if (p->pos[0] == '\'' || p->pos[0] == '"') {
    tok = getstr(p);
  } else if (mjs_is_ident(p->pos[0])) {
    tok = getident(p);
    /*
     * NOTE: getident() has side effects on `p`, and `is_reserved_word_token()`
     * relies on them. Since in C the order of evaluation of the operands is
     * undefined, `is_reserved_word_token()` should be called in a separate
     * statement.
     */
    tok += is_reserved_word_token(p->tok_ptr, p->tok_len);
  } else if (strchr(",.:;{}[]()?", p->pos[0]) != NULL) {
    tok = p->pos[0];
  } else if ((tmp = longtok3(p, '<', '<', '=')) != TOK_EOF ||
             (tmp = longtok3(p, '>', '>', '=')) != TOK_EOF ||
             (tmp = longtok4(p, '>', '>', '>', '=')) != TOK_EOF ||
             (tmp = longtok3(p, '>', '>', '>')) != TOK_EOF ||
             (tmp = longtok(p, "&", "&=")) != TOK_EOF ||
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
  } else if (mjs_is_boolean(v)) {
    fprintf(f, "%s", mjs_get_bool(mjs, v) ? "true" : "false");
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
