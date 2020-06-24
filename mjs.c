#include "mjs.h"
#ifdef MJS_MODULE_LINES
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
#define CS_P_CC3100 6
#define CS_P_CC3200 4
#define CS_P_CC3220 17
#define CS_P_MSP432 5
#define CS_P_TM4C129 14
#define CS_P_MBED 7
#define CS_P_WINCE 8
#define CS_P_NXP_LPC 13
#define CS_P_NXP_KINETIS 9
#define CS_P_NRF51 12
#define CS_P_NRF52 10
#define CS_P_PIC32 11
#define CS_P_RS14100 18
#define CS_P_STM32 16
/* Next id: 19 */

/* If not specified explicitly, we guess platform by defines. */
#ifndef CS_PLATFORM

#if defined(TARGET_IS_MSP432P4XX) || defined(__MSP432P401R__)
#define CS_PLATFORM CS_P_MSP432
#elif defined(cc3200) || defined(TARGET_IS_CC3200)
#define CS_PLATFORM CS_P_CC3200
#elif defined(cc3220) || defined(TARGET_IS_CC3220)
#define CS_PLATFORM CS_P_CC3220
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
#elif defined(RS14100)
#define CS_PLATFORM CS_P_RS14100
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
#define MG_NET_IF_NULL 5

#define MG_SSL_IF_OPENSSL 1
#define MG_SSL_IF_MBEDTLS 2
#define MG_SSL_IF_SIMPLELINK 3

/* Amalgamated: #include "common/platforms/platform_unix.h" */
/* Amalgamated: #include "common/platforms/platform_windows.h" */
/* Amalgamated: #include "common/platforms/platform_esp32.h" */
/* Amalgamated: #include "common/platforms/platform_esp8266.h" */
/* Amalgamated: #include "common/platforms/platform_cc3100.h" */
/* Amalgamated: #include "common/platforms/platform_cc3200.h" */
/* Amalgamated: #include "common/platforms/platform_cc3220.h" */
/* Amalgamated: #include "common/platforms/platform_mbed.h" */
/* Amalgamated: #include "common/platforms/platform_nrf51.h" */
/* Amalgamated: #include "common/platforms/platform_nrf52.h" */
/* Amalgamated: #include "common/platforms/platform_wince.h" */
/* Amalgamated: #include "common/platforms/platform_nxp_lpc.h" */
/* Amalgamated: #include "common/platforms/platform_nxp_kinetis.h" */
/* Amalgamated: #include "common/platforms/platform_pic32.h" */
/* Amalgamated: #include "common/platforms/platform_rs14100.h" */
/* Amalgamated: #include "common/platforms/platform_stm32.h" */
#if CS_PLATFORM == CS_P_CUSTOM
#include <platform_custom.h>
#endif

/* Common stuff */

#if !defined(PRINTF_LIKE)
#if defined(__GNUC__) || defined(__clang__) || defined(__TI_COMPILER_VERSION__)
#define PRINTF_LIKE(f, a) __attribute__((format(printf, f, a)))
#else
#define PRINTF_LIKE(f, a)
#endif
#endif

#if !defined(WEAK)
#if (defined(__GNUC__) || defined(__clang__) || \
     defined(__TI_COMPILER_VERSION__)) &&       \
    !defined(_WIN32)
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
#ifdef MJS_MODULE_LINES
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
#include <ctype.h>

#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib") /* Linking with winsock library */
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <process.h>

#if defined(_MSC_VER) && (_MSC_VER < 1700)
typedef int bool;
#else
#include <stdbool.h>
#endif

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
#define vsnprintf _vsnprintf
#define to64(x) _atoi64(x)
#if !defined(__MINGW32__) && !defined(__MINGW64__)
#define popen(x, y) _popen((x), (y))
#define pclose(x) _pclose(x)
#define fileno _fileno
#endif
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
#define CS_DEFINE_DIRENT

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

unsigned int sleep(unsigned int seconds);

/* https://stackoverflow.com/questions/16647819/timegm-cross-platform */
#define timegm _mkgmtime

#define gmtime_r(a, b) \
  do {                 \
    *(b) = *gmtime(a); \
  } while (0)

#endif /* CS_PLATFORM == CS_P_WINDOWS */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_WINDOWS_H_ */
#ifdef MJS_MODULE_LINES
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
#include <stdbool.h>
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

#ifndef MG_HOSTS_FILE_NAME
#define MG_HOSTS_FILE_NAME "/etc/hosts"
#endif

#ifndef MG_RESOLV_CONF_FILE_NAME
#define MG_RESOLV_CONF_FILE_NAME "/etc/resolv.conf"
#endif

#endif /* CS_PLATFORM == CS_P_UNIX */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_UNIX_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_esp32.h"
#endif

#ifndef CS_COMMON_PLATFORMS_PLATFORM_ESP32_H_
#define CS_COMMON_PLATFORMS_PLATFORM_ESP32_H_
#if CS_PLATFORM == CS_P_ESP32

#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <inttypes.h>
#include <machine/endian.h>
#include <stdbool.h>
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
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_esp8266.h"
#endif

#ifndef CS_COMMON_PLATFORMS_PLATFORM_ESP8266_H_
#define CS_COMMON_PLATFORMS_PLATFORM_ESP8266_H_
#if CS_PLATFORM == CS_P_ESP8266

#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <machine/endian.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#define SIZE_T_FMT "u"
typedef struct stat cs_stat_t;
#define DIRSEP '/'
#if !defined(MGOS_VFS_DEFINE_DIRENT)
#define CS_DEFINE_DIRENT
#endif

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define __cdecl
#define _FILE_OFFSET_BITS 32

#define MG_LWIP 1

/* struct timeval is defined in sys/time.h. */
#define LWIP_TIMEVAL_PRIVATE 0

#ifndef MG_NET_IF
#include <lwip/opt.h>
#if LWIP_SOCKET /* RTOS SDK has LWIP sockets */
#define MG_NET_IF MG_NET_IF_SOCKET
#else
#define MG_NET_IF MG_NET_IF_LWIP_LOW_LEVEL
#endif
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#define inet_ntop(af, src, dst, size)                                          \
  (((af) == AF_INET) ? ipaddr_ntoa_r((const ip_addr_t *) (src), (dst), (size)) \
                     : NULL)
#define inet_pton(af, src, dst) \
  (((af) == AF_INET) ? ipaddr_aton((src), (ip_addr_t *) (dst)) : 0)

#endif /* CS_PLATFORM == CS_P_ESP8266 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_ESP8266_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_cc3100.h"
#endif

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
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/simplelink/cs_simplelink.h"
#endif

#ifndef CS_COMMON_PLATFORMS_SIMPLELINK_CS_SIMPLELINK_H_
#define CS_COMMON_PLATFORMS_SIMPLELINK_CS_SIMPLELINK_H_

#if defined(MG_NET_IF) && MG_NET_IF == MG_NET_IF_SIMPLELINK

/* If simplelink.h is already included, all bets are off. */
#if !defined(__SIMPLELINK_H__)

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

#if CS_PLATFORM == CS_P_CC3220
#include <ti/drivers/net/wifi/porting/user.h>
#include <ti/drivers/net/wifi/simplelink.h>
#include <ti/drivers/net/wifi/sl_socket.h>
#include <ti/drivers/net/wifi/netapp.h>
#else
/* We want to disable SL_INC_STD_BSD_API_NAMING, so we include user.h ourselves
 * and undef it. */
#define PROVISIONING_API_H_
#include <simplelink/user.h>
#undef PROVISIONING_API_H_
#undef SL_INC_STD_BSD_API_NAMING

#include <simplelink/include/simplelink.h>
#include <simplelink/include/netapp.h>
#endif /* CS_PLATFORM == CS_P_CC3220 */

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

int sl_set_ssl_opts(int sock, struct mg_connection *nc);

#ifdef __cplusplus
}
#endif

#endif /* !defined(__SIMPLELINK_H__) */

/* Compatibility with older versions of SimpleLink */
#if SL_MAJOR_VERSION_NUM < 2

#define SL_ERROR_BSD_EAGAIN SL_EAGAIN
#define SL_ERROR_BSD_EALREADY SL_EALREADY
#define SL_ERROR_BSD_ENOPROTOOPT SL_ENOPROTOOPT
#define SL_ERROR_BSD_ESECDATEERROR SL_ESECDATEERROR
#define SL_ERROR_BSD_ESECSNOVERIFY SL_ESECSNOVERIFY
#define SL_ERROR_FS_FAILED_TO_ALLOCATE_MEM SL_FS_ERR_FAILED_TO_ALLOCATE_MEM
#define SL_ERROR_FS_FILE_HAS_NOT_BEEN_CLOSE_CORRECTLY \
  SL_FS_FILE_HAS_NOT_BEEN_CLOSE_CORRECTLY
#define SL_ERROR_FS_FILE_NAME_EXIST SL_FS_FILE_NAME_EXIST
#define SL_ERROR_FS_FILE_NOT_EXISTS SL_FS_ERR_FILE_NOT_EXISTS
#define SL_ERROR_FS_NO_AVAILABLE_NV_INDEX SL_FS_ERR_NO_AVAILABLE_NV_INDEX
#define SL_ERROR_FS_NOT_ENOUGH_STORAGE_SPACE SL_FS_ERR_NO_AVAILABLE_BLOCKS
#define SL_ERROR_FS_NOT_SUPPORTED SL_FS_ERR_NOT_SUPPORTED
#define SL_ERROR_FS_WRONG_FILE_NAME SL_FS_WRONG_FILE_NAME
#define SL_ERROR_FS_INVALID_HANDLE SL_FS_ERR_INVALID_HANDLE
#define SL_NETCFG_MAC_ADDRESS_GET SL_MAC_ADDRESS_GET
#define SL_SOCKET_FD_ZERO SL_FD_ZERO
#define SL_SOCKET_FD_SET SL_FD_SET
#define SL_SOCKET_FD_ISSET SL_FD_ISSET
#define SL_SO_SECURE_DOMAIN_NAME_VERIFICATION SO_SECURE_DOMAIN_NAME_VERIFICATION

#define SL_FS_READ FS_MODE_OPEN_READ
#define SL_FS_WRITE FS_MODE_OPEN_WRITE

#define SL_FI_FILE_SIZE(fi) ((fi).FileLen)
#define SL_FI_FILE_MAX_SIZE(fi) ((fi).AllocatedLen)

#define SlDeviceVersion_t SlVersionFull
#define sl_DeviceGet sl_DevGet
#define SL_DEVICE_GENERAL SL_DEVICE_GENERAL_CONFIGURATION
#define SL_LEN_TYPE _u8
#define SL_OPT_TYPE _u8

#else /* SL_MAJOR_VERSION_NUM >= 2 */

#define FS_MODE_OPEN_CREATE(max_size, flag) \
  (SL_FS_CREATE | SL_FS_CREATE_MAX_SIZE(max_size))
#define SL_FI_FILE_SIZE(fi) ((fi).Len)
#define SL_FI_FILE_MAX_SIZE(fi) ((fi).MaxSize)

#define SL_LEN_TYPE _u16
#define SL_OPT_TYPE _u16

#endif /* SL_MAJOR_VERSION_NUM < 2 */

int slfs_open(const unsigned char *fname, uint32_t flags, uint32_t *token);

#endif /* MG_NET_IF == MG_NET_IF_SIMPLELINK */

#endif /* CS_COMMON_PLATFORMS_SIMPLELINK_CS_SIMPLELINK_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_cc3200.h"
#endif

#ifndef CS_COMMON_PLATFORMS_PLATFORM_CC3200_H_
#define CS_COMMON_PLATFORMS_PLATFORM_CC3200_H_
#if CS_PLATFORM == CS_P_CC3200

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
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
int settimeofday(const struct timeval *tv, const void *tz);

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
int stat(const char *pathname, struct stat *st);

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

/* 5.x series compilers don't have va_copy, 16.x do. */
#if __TI_COMPILER_VERSION__ < 16000000
#define va_copy(apc, ap) ((apc) = (ap))
#endif

#endif /* __TI_COMPILER_VERSION__ */

#ifdef CC3200_FS_SLFS
#define MG_FS_SLFS
#endif

#if (defined(CC3200_FS_SPIFFS) || defined(CC3200_FS_SLFS)) && \
    !defined(MG_ENABLE_FILESYSTEM)
#define MG_ENABLE_FILESYSTEM 1
#define CS_DEFINE_DIRENT
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#ifdef __cplusplus
}
#endif

#endif /* CS_PLATFORM == CS_P_CC3200 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_CC3200_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_cc3220.h"
#endif

#ifndef CS_COMMON_PLATFORMS_PLATFORM_CC3220_H_
#define CS_COMMON_PLATFORMS_PLATFORM_CC3220_H_
#if CS_PLATFORM == CS_P_CC3220

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#ifndef __TI_COMPILER_VERSION__
#include <fcntl.h>
#include <sys/time.h>
#endif

#define MG_NET_IF MG_NET_IF_SIMPLELINK
#ifndef MG_SSL_IF
#define MG_SSL_IF MG_SSL_IF_SIMPLELINK
#endif

/* Only SPIFFS supports directories, SLFS does not. */
#if defined(CC3220_FS_SPIFFS) && !defined(MG_ENABLE_DIRECTORY_LISTING)
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
int settimeofday(const struct timeval *tv, const void *tz);

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
int stat(const char *pathname, struct stat *st);

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

#endif /* __TI_COMPILER_VERSION__ */

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#ifdef __cplusplus
}
#endif

#endif /* CS_PLATFORM == CS_P_CC3220 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_CC3200_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_mbed.h"
#endif

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
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_nrf51.h"
#endif
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

#define MG_NET_IF MG_NET_IF_LWIP_LOW_LEVEL
#define MG_LWIP 1
#define MG_ENABLE_IPV6 1

/*
 * For ARM C Compiler, make lwip to export `struct timeval`; for other
 * compilers, suppress it.
 */
#if !defined(__ARMCC_VERSION)
#define LWIP_TIMEVAL_PRIVATE 0
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
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_nrf52.h"
#endif
#ifndef CS_COMMON_PLATFORMS_PLATFORM_NRF52_H_
#define CS_COMMON_PLATFORMS_PLATFORM_NRF52_H_
#if CS_PLATFORM == CS_P_NRF52

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define to64(x) strtoll(x, NULL, 10)

#define MG_NET_IF MG_NET_IF_LWIP_LOW_LEVEL
#define MG_LWIP 1
#define MG_ENABLE_IPV6 1

#if !defined(ENOSPC)
#define ENOSPC 28 /* No space left on device */
#endif

/*
 * For ARM C Compiler, make lwip to export `struct timeval`; for other
 * compilers, suppress it.
 */
#if !defined(__ARMCC_VERSION)
#define LWIP_TIMEVAL_PRIVATE 0
#endif

#define INT64_FMT PRId64
#define SIZE_T_FMT "u"

/*
 * ARM C Compiler doesn't have strdup, so we provide it
 */
#define CS_ENABLE_STRDUP defined(__ARMCC_VERSION)

#endif /* CS_PLATFORM == CS_P_NRF52 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_NRF52_H_ */
#ifdef MJS_MODULE_LINES
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

#ifndef EAGAIN
#define EAGAIN EWOULDBLOCK
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
#define CS_DEFINE_DIRENT

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
typedef unsigned int *uintptr_t;
#endif

#define _S_IFREG 2
#define _S_IFDIR 4

#ifndef S_ISDIR
#define S_ISDIR(x) (((x) &_S_IFDIR) != 0)
#endif

#ifndef S_ISREG
#define S_ISREG(x) (((x) &_S_IFREG) != 0)
#endif

int open(const char *filename, int oflag, int pmode);
int _wstati64(const wchar_t *path, cs_stat_t *st);
const char *strerror();

#endif /* CS_PLATFORM == CS_P_WINCE */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_WINCE_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_nxp_lpc.h"
#endif

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
 * LPCXpress comes with 3 C library implementations: Newlib, NewlibNano and
 *Redlib.
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
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_nxp_kinetis.h"
#endif

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
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_pic32.h"
#endif

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

char *inet_ntoa(struct in_addr in);

#endif /* CS_PLATFORM == CS_P_PIC32 */

#endif /* CS_COMMON_PLATFORMS_PLATFORM_PIC32_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_rs14100.h"
#endif

#ifndef CS_COMMON_PLATFORMS_PLATFORM_RS14100_H_
#define CS_COMMON_PLATFORMS_PLATFORM_RS14100_H_
#if CS_PLATFORM == CS_P_RS14100

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef MGOS_HAVE_VFS_COMMON
#include <mgos_vfs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT "lld"
#define SIZE_T_FMT "u"
typedef struct stat cs_stat_t;
#define DIRSEP '/'

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#ifndef MG_ENABLE_FILESYSTEM
#define MG_ENABLE_FILESYSTEM 1
#endif

#ifdef __cplusplus
}
#endif

#endif /* CS_PLATFORM == CS_P_RS14100 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_RS14100_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/platforms/platform_stm32.h"
#endif

#ifndef CS_COMMON_PLATFORMS_PLATFORM_STM32_H_
#define CS_COMMON_PLATFORMS_PLATFORM_STM32_H_
#if CS_PLATFORM == CS_P_STM32

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

#include <stm32_sdk_hal.h>

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT "lld"
#define SIZE_T_FMT "u"
typedef struct stat cs_stat_t;
#define DIRSEP '/'

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

#ifndef MG_ENABLE_FILESYSTEM
#define MG_ENABLE_FILESYSTEM 1
#endif

#endif /* CS_PLATFORM == CS_P_STM32 */
#endif /* CS_COMMON_PLATFORMS_PLATFORM_STM32_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/cs_dbg.h"
#endif

#ifndef CS_COMMON_CS_DBG_H_
#define CS_COMMON_CS_DBG_H_

/* Amalgamated: #include "common/platform.h" */

#if CS_ENABLE_STDIO
#include <stdio.h>
#endif

#ifndef CS_ENABLE_DEBUG
#define CS_ENABLE_DEBUG 0
#endif

#ifndef CS_LOG_PREFIX_LEN
#define CS_LOG_PREFIX_LEN 24
#endif

#ifndef CS_LOG_ENABLE_TS_DIFF
#define CS_LOG_ENABLE_TS_DIFF 0
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * Log level; `LL_INFO` is the default. Use `cs_log_set_level()` to change it.
 */
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

/*
 * Set max log level to print; messages with the level above the given one will
 * not be printed.
 */
void cs_log_set_level(enum cs_log_level level);

/*
 * A comma-separated set of prefix=level.
 * prefix is matched against the log prefix exactly as printed, including line
 * number, but partial match is ok. Check stops on first matching entry.
 * If nothing matches, default level is used.
 *
 * Examples:
 *   main.c:=4 - everything from main C at verbose debug level.
 *   mongoose.c=1,mjs.c=1,=4 - everything at verbose debug except mg_* and mjs_*
 *
 */
void cs_log_set_file_level(const char *file_level);

/*
 * Helper function which prints message prefix with the given `level`.
 * If message should be printed (according to the current log level
 * and filter), prints the prefix and returns 1, otherwise returns 0.
 *
 * Clients should typically just use `LOG()` macro.
 */
int cs_log_print_prefix(enum cs_log_level level, const char *fname, int line);

extern enum cs_log_level cs_log_level;

#if CS_ENABLE_STDIO

/*
 * Set file to write logs into. If `NULL`, logs go to `stderr`.
 */
void cs_log_set_file(FILE *file);

/*
 * Prints log to the current log file, appends "\n" in the end and flushes the
 * stream.
 */
void cs_log_printf(const char *fmt, ...) PRINTF_LIKE(1, 2);

#if CS_ENABLE_STDIO

/*
 * Format and print message `x` with the given level `l`. Example:
 *
 * ```c
 * LOG(LL_INFO, ("my info message: %d", 123));
 * LOG(LL_DEBUG, ("my debug message: %d", 123));
 * ```
 */
#define LOG(l, x)                                     \
  do {                                                \
    if (cs_log_print_prefix(l, __FILE__, __LINE__)) { \
      cs_log_printf x;                                \
    }                                                 \
  } while (0)

#else

#define LOG(l, x) ((void) l)

#endif

#ifndef CS_NDEBUG

/*
 * Shortcut for `LOG(LL_VERBOSE_DEBUG, (...))`
 */
#define DBG(x) LOG(LL_VERBOSE_DEBUG, x)

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
#ifdef MJS_MODULE_LINES
#line 1 "common/cs_time.h"
#endif

#ifndef CS_COMMON_CS_TIME_H_
#define CS_COMMON_CS_TIME_H_

#include <time.h>

/* Amalgamated: #include "common/platform.h" */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Sub-second granularity time(). */
double cs_time(void);

/*
 * Similar to (non-standard) timegm, converts broken-down time into the number
 * of seconds since Unix Epoch.
 */
double cs_timegm(const struct tm *tm);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_COMMON_CS_TIME_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/mg_str.h"
#endif

#ifndef CS_COMMON_MG_STR_H_
#define CS_COMMON_MG_STR_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Describes chunk of memory */
struct mg_str {
  const char *p; /* Memory chunk pointer */
  size_t len;    /* Memory chunk length */
};

/*
 * Helper function for creating mg_str struct from plain C string.
 * `NULL` is allowed and becomes `{NULL, 0}`.
 */
struct mg_str mg_mk_str(const char *s);

/*
 * Like `mg_mk_str`, but takes string length explicitly.
 */
struct mg_str mg_mk_str_n(const char *s, size_t len);

/* Macro for initializing mg_str. */
#define MG_MK_STR(str_literal) \
  { str_literal, sizeof(str_literal) - 1 }
#define MG_MK_STR_N(str_literal, len) \
  { str_literal, len }
#define MG_NULL_STR \
  { NULL, 0 }

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

/* Creates a copy of s (heap-allocated). */
struct mg_str mg_strdup(const struct mg_str s);

/*
 * Creates a copy of s (heap-allocated).
 * Resulting string is NUL-terminated (but NUL is not included in len).
 */
struct mg_str mg_strdup_nul(const struct mg_str s);

/*
 * Locates character in a string.
 */
const char *mg_strchr(const struct mg_str s, int c);

/*
 * Compare two `mg_str`s; return value is the same as `strcmp`.
 */
int mg_strcmp(const struct mg_str str1, const struct mg_str str2);

/*
 * Like `mg_strcmp`, but compares at most `n` characters.
 */
int mg_strncmp(const struct mg_str str1, const struct mg_str str2, size_t n);

/*
 * Compare two `mg_str`s ignoreing case; return value is the same as `strcmp`.
 */
int mg_strcasecmp(const struct mg_str str1, const struct mg_str str2);

/*
 * Free the string (assuming it was heap allocated).
 */
void mg_strfree(struct mg_str *s);

/*
 * Finds the first occurrence of a substring `needle` in the `haystack`.
 */
const char *mg_strstr(const struct mg_str haystack, const struct mg_str needle);

/* Strip whitespace at the start and the end of s */
struct mg_str mg_strstrip(struct mg_str s);

/* Returns 1 if s starts with the given prefix. */
int mg_str_starts_with(struct mg_str s, struct mg_str prefix);

#ifdef __cplusplus
}
#endif

#endif /* CS_COMMON_MG_STR_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/str_util.h"
#endif

#ifndef CS_COMMON_STR_UTIL_H_
#define CS_COMMON_STR_UTIL_H_

#include <stdarg.h>
#include <stdlib.h>

/* Amalgamated: #include "common/mg_str.h" */
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
#if !defined(_MSC_VER) || _MSC_VER >= 1900
#define CS_STRINGIFY_LIT(...) #__VA_ARGS__
#else
#define CS_STRINGIFY_LIT(x) #x
#endif

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

/*
 * Equivalent of standard `strnlen()`.
 */
size_t c_strnlen(const char *s, size_t maxlen);

/*
 * Equivalent of standard `snprintf()`.
 */
int c_snprintf(char *buf, size_t buf_size, const char *format, ...)
    PRINTF_LIKE(3, 4);

/*
 * Equivalent of standard `vsnprintf()`.
 */
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
/*
 * Equivalent of standard `strdup()`, defined if only `CS_ENABLE_STRDUP` is 1.
 */
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
 * ```c
 *    char buf[5], *p = buf;
 *    mg_avprintf(&p, sizeof(buf), "%s", "hi there");
 *    use_p_somehow(p);
 *    if (p != buf) {
 *      free(p);
 *    }
 * ```
 *
 * The purpose of this is to avoid malloc-ing if generated strings are small.
 */
int mg_asprintf(char **buf, size_t size, const char *fmt, ...)
    PRINTF_LIKE(3, 4);

/* Same as mg_asprintf, but takes varargs list. */
int mg_avprintf(char **buf, size_t size, const char *fmt, va_list ap);

/*
 * A helper function for traversing a comma separated list of values.
 * It returns a list pointer shifted to the next value or NULL if the end
 * of the list found.
 * The value is stored in a val vector. If the value has a form "x=y", then
 * eq_val vector is initialised to point to the "y" part, and val vector length
 * is adjusted to point only to "x".
 * If the list is just a comma separated list of entries, like "aa,bb,cc" then
 * `eq_val` will contain zero-length string.
 *
 * The purpose of this function is to parse comma separated string without
 * any copying/memory allocation.
 */
const char *mg_next_comma_list_entry(const char *list, struct mg_str *val,
                                     struct mg_str *eq_val);

/*
 * Like `mg_next_comma_list_entry()`, but takes `list` as `struct mg_str`.
 * NB: Test return value's .p, not .len. On last itreation that yields result
 * .len will be 0 but .p will not. When finished, .p will be NULL.
 */
struct mg_str mg_next_comma_list_entry_n(struct mg_str list, struct mg_str *val,
                                         struct mg_str *eq_val);

/*
 * Matches 0-terminated string (mg_match_prefix) or string with given length
 * mg_match_prefix_n against a glob pattern. Glob syntax:
 * ```
 * - * matches zero or more characters until a slash character /
 * - ** matches zero or more characters
 * - ? Matches exactly one character which is not a slash /
 * - | or ,  divides alternative patterns
 * - any other character matches itself
 * ```
 * Match is case-insensitive. Return number of bytes matched.
 * Examples:
 * ```
 * mg_match_prefix("a*f", len, "abcdefgh") == 6
 * mg_match_prefix("a*f", len, "abcdexgh") == 0
 * mg_match_prefix("a*f|de*,xy", len, "defgh") == 5
 * mg_match_prefix("?*", len, "abc") == 3
 * mg_match_prefix("?*", len, "") == 0
 * ```
 */
size_t mg_match_prefix(const char *pattern, int pattern_len, const char *str);

/*
 * Like `mg_match_prefix()`, but takes `pattern` and `str` as `struct mg_str`.
 */
size_t mg_match_prefix_n(const struct mg_str pattern, const struct mg_str str);

#ifdef __cplusplus
}
#endif

#endif /* CS_COMMON_STR_UTIL_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/cs_file.h"
#endif

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
/*
 * Only on platforms which support mmapping: mmap file `path` to the returned
 * address. File size is written to `*size`.
 */
char *cs_mmap_file(const char *path, size_t *size);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_COMMON_CS_FILE_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/mbuf.h"
#endif

/*
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

#ifndef MBUF_SIZE_MAX_HEADROOM
#ifdef BUFSIZ
#define MBUF_SIZE_MAX_HEADROOM BUFSIZ
#else
#define MBUF_SIZE_MAX_HEADROOM 1024
#endif
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
 * Appends data to the Mbuf and frees it (data must be heap-allocated).
 *
 * Returns the number of bytes appended or 0 if out of memory.
 * data is freed irrespective of return value.
 */
size_t mbuf_append_and_free(struct mbuf *, void *data, size_t data_size);

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

/* Moves the state from one mbuf to the other. */
void mbuf_move(struct mbuf *from, struct mbuf *to);

/* Removes all the data from mbuf (if any). */
void mbuf_clear(struct mbuf *);

/* Shrinks an Mbuf by resizing its `size` to `len`. */
void mbuf_trim(struct mbuf *);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* CS_COMMON_MBUF_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/mg_mem.h"
#endif

#ifndef CS_COMMON_MG_MEM_H_
#define CS_COMMON_MG_MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MG_MALLOC
#define MG_MALLOC malloc
#endif

#ifndef MG_CALLOC
#define MG_CALLOC calloc
#endif

#ifndef MG_REALLOC
#define MG_REALLOC realloc
#endif

#ifndef MG_FREE
#define MG_FREE free
#endif

#ifdef __cplusplus
}
#endif

#endif /* CS_COMMON_MG_MEM_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "frozen/frozen.h"
#endif

#ifndef CS_FROZEN_FROZEN_H_
#define CS_FROZEN_FROZEN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#if defined(_WIN32) && _MSC_VER < 1700
typedef int bool;
enum { false = 0, true = 1 };
#else
#include <stdbool.h>
#endif

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
 * Return number of processed bytes, or a negative error code.
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
      { (char *) fp, 0, 0 } \
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
 * Return number of bytes printed. If the return value is bigger than the
 * supplied buffer, that is an indicator of overflow. In the overflow case,
 * overflown bytes are not printed.
 */
int json_printf(struct json_out *, const char *fmt, ...);
int json_vprintf(struct json_out *, const char *fmt, va_list ap);

/*
 * Same as json_printf, but prints to a file.
 * File is created if does not exist. File is truncated if already exists.
 */
int json_fprintf(const char *file_name, const char *fmt, ...);
int json_vfprintf(const char *file_name, const char *fmt, va_list ap);

/*
 * Print JSON into an allocated 0-terminated string.
 * Return allocated string, or NULL on error.
 * Example:
 *
 * ```c
 *   char *str = json_asprintf("{a:%H}", 3, "abc");
 *   printf("%s\n", str);  // Prints "616263"
 *   free(str);
 * ```
 */
char *json_asprintf(const char *fmt, ...);
char *json_vasprintf(const char *fmt, va_list ap);

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
 *    - %B: consumes `int *` (or `char *`, if `sizeof(bool) == sizeof(char)`),
 *       expects boolean `true` or `false`.
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
 * Return -1 if no array element found, otherwise non-negative token length.
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

/*
 * Escape a string `str`, `str_len` into the printer `out`.
 * Return the number of bytes printed.
 */
int json_escape(struct json_out *out, const char *str, size_t str_len);

/*
 * Read the whole file in memory.
 * Return malloc-ed file content, or NULL on error. The caller must free().
 */
char *json_fread(const char *file_name);

/*
 * Update given JSON string `s,len` by changing the value at given `json_path`.
 * The result is saved to `out`. If `json_fmt` == NULL, that deletes the key.
 * If path is not present, missing keys are added. Array path without an
 * index pushes a value to the end of an array.
 * Return 1 if the string was changed, 0 otherwise.
 *
 * Example:  s is a JSON string { "a": 1, "b": [ 2 ] }
 *   json_setf(s, len, out, ".a", "7");     // { "a": 7, "b": [ 2 ] }
 *   json_setf(s, len, out, ".b", "7");     // { "a": 1, "b": 7 }
 *   json_setf(s, len, out, ".b[]", "7");   // { "a": 1, "b": [ 2,7 ] }
 *   json_setf(s, len, out, ".b", NULL);    // { "a": 1 }
 */
int json_setf(const char *s, int len, struct json_out *out,
              const char *json_path, const char *json_fmt, ...);

int json_vsetf(const char *s, int len, struct json_out *out,
               const char *json_path, const char *json_fmt, va_list ap);

/*
 * Pretty-print JSON string `s,len` into `out`.
 * Return number of processed bytes in `s`.
 */
int json_prettify(const char *s, int len, struct json_out *out);

/*
 * Prettify JSON file `file_name`.
 * Return number of processed bytes, or negative number of error.
 * On error, file content is not modified.
 */
int json_prettify_file(const char *file_name);

/*
 * Iterate over an object at given JSON `path`.
 * On each iteration, fill the `key` and `val` tokens. It is OK to pass NULL
 * for `key`, or `val`, in which case they won't be populated.
 * Return an opaque value suitable for the next iteration, or NULL when done.
 *
 * Example:
 *
 * ```c
 * void *h = NULL;
 * struct json_token key, val;
 * while ((h = json_next_key(s, len, h, ".foo", &key, &val)) != NULL) {
 *   printf("[%.*s] -> [%.*s]\n", key.len, key.ptr, val.len, val.ptr);
 * }
 * ```
 */
void *json_next_key(const char *s, int len, void *handle, const char *path,
                    struct json_token *key, struct json_token *val);

/*
 * Iterate over an array at given JSON `path`.
 * Similar to `json_next_key`, but fills array index `idx` instead of `key`.
 */
void *json_next_elem(const char *s, int len, void *handle, const char *path,
                     int *idx, struct json_token *val);

#ifndef JSON_MAX_PATH_LEN
#define JSON_MAX_PATH_LEN 256
#endif

#ifndef JSON_MINIMAL
#define JSON_MINIMAL 0
#endif

#ifndef JSON_ENABLE_BASE64
#define JSON_ENABLE_BASE64 !JSON_MINIMAL
#endif

#ifndef JSON_ENABLE_HEX
#define JSON_ENABLE_HEX !JSON_MINIMAL
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_FROZEN_FROZEN_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/ffi/ffi.h"
#endif

#ifndef MJS_FFI_FFI_H_
#define MJS_FFI_FFI_H_

/* Amalgamated: #include "common/platform.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Maximum number of word-sized args to ffi-ed function. If at least one
 * of the args is double, only 2 args are allowed.
 */
#define FFI_MAX_ARGS_CNT 6

typedef void(ffi_fn_t)(void);

typedef intptr_t ffi_word_t;

enum ffi_ctype {
  FFI_CTYPE_WORD,
  FFI_CTYPE_BOOL,
  FFI_CTYPE_FLOAT,
  FFI_CTYPE_DOUBLE,
};

struct ffi_arg {
  enum ffi_ctype ctype;
  union {
    uint64_t i;
    double d;
    float f;
  } v;
};

int ffi_call(ffi_fn_t *func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args);

void ffi_set_word(struct ffi_arg *arg, ffi_word_t v);
void ffi_set_bool(struct ffi_arg *arg, bool v);
void ffi_set_ptr(struct ffi_arg *arg, void *v);
void ffi_set_double(struct ffi_arg *arg, double v);
void ffi_set_float(struct ffi_arg *arg, float v);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_FFI_FFI_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_internal.h"
#endif

#ifndef MJS_INTERNAL_H_
#define MJS_INTERNAL_H_

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

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

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#if !defined(WEAK)
#if (defined(__GNUC__) || defined(__TI_COMPILER_VERSION__)) && !defined(_WIN32)
#define WEAK __attribute__((weak))
#else
#define WEAK
#endif
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "common/cs_file.h" */
/* Amalgamated: #include "common/mbuf.h" */

#if defined(_WIN32) && _MSC_VER < 1700
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef __int64 int64_t;
typedef unsigned long uintptr_t;
#define STRX(x) #x
#define STR(x) STRX(x)
#define __func__ __FILE__ ":" STR(__LINE__)
// #define snprintf _snprintf
#define vsnprintf _vsnprintf
#define isnan(x) _isnan(x)
#define va_copy(x, y) (x) = (y)
#define CS_DEFINE_DIRENT
#include <windows.h>
#else
#if defined(__unix__) || defined(__APPLE__)
#include <dlfcn.h>
#endif
#endif

/*
 * Number of bytes reserved for the jump offset initially. The most practical
 * value is 1, but for testing it's useful to set it to 0 and to some large
 * value as well (like, 4), to make sure that the code behaves correctly under
 * all circumstances.
 */
#ifndef MJS_INIT_OFFSET_SIZE
#define MJS_INIT_OFFSET_SIZE 1
#endif

#endif /* MJS_INTERNAL_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_license.h"
#endif
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_features.h"
#endif

#ifndef MJS_FEATURES_H_
#define MJS_FEATURES_H_

#if !defined(MJS_AGGRESSIVE_GC)
#define MJS_AGGRESSIVE_GC 0
#endif

#if !defined(MJS_MEMORY_STATS)
#define MJS_MEMORY_STATS 0
#endif

/*
 * MJS_GENERATE_JSC: if enabled, and if mmapping is also enabled (CS_MMAP),
 * then execution of any .js file will result in creation of a .jsc file with
 * precompiled bcode, and this .jsc file will be mmapped, instead of keeping
 * bcode in RAM.
 *
 * By default it's enabled (provided that CS_MMAP is defined)
 */
#if !defined(MJS_GENERATE_JSC)
#if defined(CS_MMAP)
#define MJS_GENERATE_JSC 1
#else
#define MJS_GENERATE_JSC 0
#endif
#endif

#endif /* MJS_FEATURES_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_core_public.h"
#endif

#ifndef MJS_CORE_PUBLIC_H_
#define MJS_CORE_PUBLIC_H_

#if !defined(_MSC_VER) || _MSC_VER >= 1700
#include <stdint.h>
#else
typedef unsigned __int64 uint64_t;
typedef int int32_t;
typedef unsigned char uint8_t;
#endif
#include <stdio.h>
#include <stddef.h>
/* Amalgamated: #include "mjs/src/mjs_license.h" */
/* Amalgamated: #include "mjs/src/mjs_features.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define MJS_ENABLE_DEBUG 1

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

typedef enum mjs_err {
  MJS_OK,
  MJS_SYNTAX_ERROR,
  MJS_REFERENCE_ERROR,
  MJS_TYPE_ERROR,
  MJS_OUT_OF_MEMORY,
  MJS_INTERNAL_ERROR,
  MJS_NOT_IMPLEMENTED_ERROR,
  MJS_FILE_READ_ERROR,
  MJS_BAD_ARGS_ERROR,

  MJS_ERRS_CNT
} mjs_err_t;
struct mjs;

/* Create MJS instance */
struct mjs *mjs_create();

struct mjs_create_opts {
  /* use non-default bytecode definition file, testing-only */
  const struct bf_code *code;
};

/*
 * Like `msj_create()`, but allows to customize initial MJS state, see `struct
 * mjs_create_opts`.
 */
struct mjs *mjs_create_opt(struct mjs_create_opts opts);

/* Destroy MJS instance */
void mjs_destroy(struct mjs *mjs);

mjs_val_t mjs_get_global(struct mjs *mjs);

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
mjs_err_t mjs_prepend_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt,
                             ...);

/*
 * Print the last error details. If print_stack_trace is non-zero, also
 * print stack trace. `msg` is the message which gets prepended to the actual
 * error message, if it's NULL, then "MJS error" is used.
 */
void mjs_print_error(struct mjs *mjs, FILE *fp, const char *msg,
                     int print_stack_trace);

/*
 * return a string representation of an error.
 * the error string might be overwritten by calls to `mjs_set_errorf`.
 */
const char *mjs_strerror(struct mjs *mjs, enum mjs_err err);

/*
 * Sets whether *.jsc files are generated when *.js file is executed. By
 * default it's 0.
 *
 * If either `MJS_GENERATE_JSC` or `CS_MMAP` is off, then this function has no
 * effect.
 */
void mjs_set_generate_jsc(struct mjs *mjs, int generate_jsc);

/*
 * When invoked from a cfunction, returns number of arguments passed to the
 * current JS function call.
 */
int mjs_nargs(struct mjs *mjs);

/*
 * When invoked from a cfunction, returns n-th argument to the current JS
 * function call.
 */
mjs_val_t mjs_arg(struct mjs *mjs, int n);

/*
 * Sets return value for the current JS function call.
 */
void mjs_return(struct mjs *mjs, mjs_val_t v);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_CORE_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_array_public.h"
#endif

/*
 * === Arrays
 */

#ifndef MJS_ARRAY_PUBLIC_H_
#define MJS_ARRAY_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */

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

/* Delete value in array `arr` at index `index`, if it exists. */
void mjs_array_del(struct mjs *mjs, mjs_val_t arr, unsigned long index);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_ARRAY_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_array.h"
#endif

#ifndef MJS_ARRAY_H_
#define MJS_ARRAY_H_

/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_array_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

MJS_PRIVATE mjs_val_t
mjs_array_get2(struct mjs *mjs, mjs_val_t arr, unsigned long index, int *has);

MJS_PRIVATE void mjs_array_splice(struct mjs *mjs);

MJS_PRIVATE void mjs_array_push_internal(struct mjs *mjs);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_ARRAY_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_ffi_public.h"
#endif

#ifndef MJS_FFI_PUBLIC_H_
#define MJS_FFI_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

enum mjs_ffi_ctype {
  MJS_FFI_CTYPE_NONE,
  MJS_FFI_CTYPE_USERDATA,
  MJS_FFI_CTYPE_CALLBACK,
  MJS_FFI_CTYPE_INT,
  MJS_FFI_CTYPE_BOOL,
  MJS_FFI_CTYPE_DOUBLE,
  MJS_FFI_CTYPE_FLOAT,
  MJS_FFI_CTYPE_CHAR_PTR,
  MJS_FFI_CTYPE_VOID_PTR,
  MJS_FFI_CTYPE_STRUCT_MG_STR_PTR,
  MJS_FFI_CTYPE_STRUCT_MG_STR,
  MJS_FFI_CTYPE_INVALID,
};

typedef void *(mjs_ffi_resolver_t)(void *handle, const char *symbol);

void mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_FFI_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_ffi.h"
#endif

#ifndef MJS_FFI_H_
#define MJS_FFI_H_

/* Amalgamated: #include "mjs/src/ffi/ffi.h" */
/* Amalgamated: #include "mjs/src/mjs_ffi_public.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

mjs_ffi_resolver_t dlsym;

#define MJS_CB_ARGS_MAX_CNT 6
#define MJS_CB_SIGNATURE_MAX_SIZE (MJS_CB_ARGS_MAX_CNT + 1 /* return type */)

typedef uint8_t mjs_ffi_ctype_t;

enum ffi_sig_type {
  FFI_SIG_FUNC,
  FFI_SIG_CALLBACK,
};

/*
 * Parsed FFI signature
 */
struct mjs_ffi_sig {
  /*
   * Callback signature, corresponds to the arg of type MJS_FFI_CTYPE_CALLBACK
   * TODO(dfrank): probably we'll need to support multiple callback/userdata
   * pairs
   *
   * NOTE(dfrank): instances of this structure are grouped into GC arenas and
   * managed by GC, and for the GC mark to work, the first element should be
   * a pointer (so that the two LSBs are not used).
   */
  struct mjs_ffi_sig *cb_sig;

  /*
   * The first item is the return value type (for `void`, `MJS_FFI_CTYPE_NONE`
   * is used); the rest are arguments. If some argument is
   * `MJS_FFI_CTYPE_NONE`, it means that there are no more arguments.
   */
  mjs_ffi_ctype_t val_types[MJS_CB_SIGNATURE_MAX_SIZE];

  /*
   * Function to call. If `is_callback` is not set, then it's the function
   * obtained by dlsym; otherwise it's a pointer to the appropriate callback
   * implementation.
   */
  ffi_fn_t *fn;

  /* Number of arguments in the signature */
  int8_t args_cnt;

  /*
   * If set, then the signature represents the callback (as opposed to a normal
   * function), and `fn` points to the suitable callback implementation.
   */
  unsigned is_callback : 1;
  unsigned is_valid : 1;
};
typedef struct mjs_ffi_sig mjs_ffi_sig_t;

/* Initialize new FFI signature */
MJS_PRIVATE void mjs_ffi_sig_init(mjs_ffi_sig_t *sig);
/* Copy existing FFI signature */
MJS_PRIVATE void mjs_ffi_sig_copy(mjs_ffi_sig_t *to, const mjs_ffi_sig_t *from);
/* Free FFI signature. NOTE: the pointer `sig` itself is not freed */
MJS_PRIVATE void mjs_ffi_sig_free(mjs_ffi_sig_t *sig);

/*
 * Creates a new FFI signature from the GC arena, and return mjs_val_t which
 * wraps it.
 */
MJS_PRIVATE mjs_val_t mjs_mk_ffi_sig(struct mjs *mjs);

/*
 * Checks whether the given value is a FFI signature.
 */
MJS_PRIVATE int mjs_is_ffi_sig(mjs_val_t v);

/*
 * Wraps FFI signature structure into mjs_val_t value.
 */
MJS_PRIVATE mjs_val_t mjs_ffi_sig_to_value(struct mjs_ffi_sig *psig);

/*
 * Extracts a pointer to the FFI signature struct from the mjs_val_t value.
 */
MJS_PRIVATE struct mjs_ffi_sig *mjs_get_ffi_sig_struct(mjs_val_t v);

/*
 * A wrapper for mjs_ffi_sig_free() suitable to use as a GC cell destructor.
 */
MJS_PRIVATE void mjs_ffi_sig_destructor(struct mjs *mjs, void *psig);

MJS_PRIVATE int mjs_ffi_sig_set_val_type(mjs_ffi_sig_t *sig, int idx,
                                         mjs_ffi_ctype_t type);
MJS_PRIVATE int mjs_ffi_sig_validate(struct mjs *mjs, mjs_ffi_sig_t *sig,
                                     enum ffi_sig_type sig_type);
MJS_PRIVATE int mjs_ffi_is_regular_word(mjs_ffi_ctype_t type);
MJS_PRIVATE int mjs_ffi_is_regular_word_or_void(mjs_ffi_ctype_t type);

struct mjs_ffi_cb_args {
  struct mjs_ffi_cb_args *next;
  struct mjs *mjs;
  mjs_ffi_sig_t sig;
  mjs_val_t func;
  mjs_val_t userdata;
};
typedef struct mjs_ffi_cb_args ffi_cb_args_t;

/*
 * cfunction:
 * Parses the FFI signature string and returns a value wrapping mjs_ffi_sig_t.
 */
MJS_PRIVATE mjs_err_t mjs_ffi_call(struct mjs *mjs);

/*
 * cfunction:
 * Performs the FFI signature call.
 */
MJS_PRIVATE mjs_err_t mjs_ffi_call2(struct mjs *mjs);

MJS_PRIVATE void mjs_ffi_cb_free(struct mjs *);
MJS_PRIVATE void mjs_ffi_args_free_list(struct mjs *mjs);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_FFI_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_mm.h"
#endif

#ifndef MJS_MM_H_
#define MJS_MM_H_

/* Amalgamated: #include "mjs/src/mjs_internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

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

#if MJS_MEMORY_STATS
  unsigned long allocations; /* cumulative counter of allocations */
  unsigned long garbage;     /* cumulative counter of garbage */
  unsigned long alive;       /* number of living cells */
#endif

  gc_cell_destructor_t destructor;
};

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_MM_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_gc.h"
#endif

#ifndef MJS_GC_H_
#define MJS_GC_H_

/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_mm.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

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
MJS_PRIVATE struct mjs_ffi_sig *new_ffi_sig(struct mjs *mjs);

MJS_PRIVATE void gc_mark(struct mjs *mjs, mjs_val_t *val);

MJS_PRIVATE void gc_arena_init(struct gc_arena *, size_t, size_t, size_t);
MJS_PRIVATE void gc_arena_destroy(struct mjs *, struct gc_arena *a);
MJS_PRIVATE void gc_sweep(struct mjs *, struct gc_arena *, size_t);
MJS_PRIVATE void *gc_alloc_cell(struct mjs *, struct gc_arena *);

MJS_PRIVATE uint64_t gc_string_mjs_val_to_offset(mjs_val_t v);

/* return 0 if v is an object/function with a bad pointer */
MJS_PRIVATE int gc_check_val(struct mjs *mjs, mjs_val_t v);

/* checks whether a pointer is within the ranges of an arena */
MJS_PRIVATE int gc_check_ptr(const struct gc_arena *a, const void *p);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_GC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_core.h"
#endif

#ifndef MJS_CORE_H
#define MJS_CORE_H

/* Amalgamated: #include "mjs/src/mjs_ffi.h" */
/* Amalgamated: #include "mjs/src/mjs_gc.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define JUMP_INSTRUCTION_SIZE 2

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
  MJS_TYPE_OBJECT_FUNCTION,
  /*
   * TODO(dfrank): if we support prototypes, need to add items for them here
   */

  MJS_TYPES_CNT
};

enum mjs_call_stack_frame_item {
  CALL_STACK_FRAME_ITEM_RETVAL_STACK_IDX, /* TOS */
  CALL_STACK_FRAME_ITEM_LOOP_ADDR_IDX,
  CALL_STACK_FRAME_ITEM_SCOPE_IDX,
  CALL_STACK_FRAME_ITEM_RETURN_ADDR,
  CALL_STACK_FRAME_ITEM_THIS,

  CALL_STACK_FRAME_ITEMS_CNT
};

/*
 * A tag is made of the sign bit and the 4 lower order bits of byte 6.
 * So in total we have 32 possible tags.
 *
 * Tag (1,0) however cannot hold a zero payload otherwise it's interpreted as an
 * INFINITY; for simplicity we're just not going to use that combination.
 */
#define MAKE_TAG(s, t) \
  ((uint64_t)(s) << 63 | (uint64_t) 0x7ff0 << 48 | (uint64_t)(t) << 48)

#define MJS_TAG_OBJECT MAKE_TAG(1, 1)
#define MJS_TAG_FOREIGN MAKE_TAG(1, 2)
#define MJS_TAG_UNDEFINED MAKE_TAG(1, 3)
#define MJS_TAG_BOOLEAN MAKE_TAG(1, 4)
#define MJS_TAG_NAN MAKE_TAG(1, 5)
#define MJS_TAG_STRING_I MAKE_TAG(1, 6)  /* Inlined string len < 5 */
#define MJS_TAG_STRING_5 MAKE_TAG(1, 7)  /* Inlined string len 5 */
#define MJS_TAG_STRING_O MAKE_TAG(1, 8)  /* Owned string */
#define MJS_TAG_STRING_F MAKE_TAG(1, 9)  /* Foreign string */
#define MJS_TAG_STRING_C MAKE_TAG(1, 10) /* String chunk */
#define MJS_TAG_STRING_D MAKE_TAG(1, 11) /* Dictionary string  */
#define MJS_TAG_ARRAY MAKE_TAG(1, 12)
#define MJS_TAG_FUNCTION MAKE_TAG(1, 13)
#define MJS_TAG_FUNCTION_FFI MAKE_TAG(1, 14)
#define MJS_TAG_NULL MAKE_TAG(1, 15)

#define MJS_TAG_MASK MAKE_TAG(1, 15)

struct mjs_vals {
  /* Current `this` value  */
  mjs_val_t this_obj;
  mjs_val_t dataview_proto;

  /*
   * The object against which the last `OP_GET` was invoked. Needed for
   * "method invocation pattern".
   */
  mjs_val_t last_getprop_obj;
};

struct mjs_bcode_part {
  /* Global index of the bcode part */
  size_t start_idx;

  /* Actual bcode data */
  struct {
    const char *p; /* Memory chunk pointer */
    size_t len;    /* Memory chunk length */
  } data;

  /*
   * Result of evaluation (not parsing: if there is an error during parsing,
   * the bcode is not even committed). It is used to determine whether we
   * need to evaluate the file: if file was already evaluated, and the result
   * was MJS_OK, then we won't evaluate it again. Otherwise, we will.
   */
  mjs_err_t exec_res : 4;

  /* If set, bcode data does not need to be freed */
  unsigned in_rom : 1;
};

struct mjs {
  struct mbuf bcode_gen;
  struct mbuf bcode_parts;
  size_t bcode_len;
  struct mbuf stack;
  struct mbuf call_stack;
  struct mbuf arg_stack;
  struct mbuf scopes;          /* Scope objects */
  struct mbuf loop_addresses;  /* Addresses for breaks & continues */
  struct mbuf owned_strings;   /* Sequence of (varint len, char data[]) */
  struct mbuf foreign_strings; /* Sequence of (varint len, char *data) */
  struct mbuf owned_values;
  struct mbuf json_visited_stack;
  struct mjs_vals vals;
  char *error_msg;
  char *stack_trace;
  enum mjs_err error;
  mjs_ffi_resolver_t *dlsym;  /* Symbol resolver function for FFI */
  ffi_cb_args_t *ffi_cb_args; /* List of FFI args descriptors */
  size_t cur_bcode_offset;

  struct gc_arena object_arena;
  struct gc_arena property_arena;
  struct gc_arena ffi_sig_arena;

  unsigned inhibit_gc : 1;
  unsigned need_gc : 1;
  unsigned generate_jsc : 1;
};

/*
 * Bcode header: type of the items, and item numbers.
 */
typedef uint32_t mjs_header_item_t;
enum mjs_header_items {
  MJS_HDR_ITEM_TOTAL_SIZE,   /* Total size of the bcode (not counting the
                                OP_BCODE_HEADER byte) */
  MJS_HDR_ITEM_BCODE_OFFSET, /* Offset to the start of the actual bcode (not
                                counting the OP_BCODE_HEADER byte) */
  MJS_HDR_ITEM_MAP_OFFSET,   /* Offset to the start of offset-to-line_no mapping
                                k*/

  MJS_HDR_ITEMS_CNT
};

MJS_PRIVATE size_t mjs_get_func_addr(mjs_val_t v);

MJS_PRIVATE int mjs_getretvalpos(struct mjs *mjs);

MJS_PRIVATE enum mjs_type mjs_get_type(mjs_val_t v);

/*
 * Prints stack trace starting from the given bcode offset; other offsets
 * (if any) will be fetched from the call_stack.
 */
MJS_PRIVATE void mjs_gen_stack_trace(struct mjs *mjs, size_t offset);

MJS_PRIVATE mjs_val_t vtop(struct mbuf *m);
MJS_PRIVATE size_t mjs_stack_size(const struct mbuf *m);
MJS_PRIVATE mjs_val_t *vptr(struct mbuf *m, int idx);
MJS_PRIVATE void push_mjs_val(struct mbuf *m, mjs_val_t v);
MJS_PRIVATE mjs_val_t mjs_pop_val(struct mbuf *m);
MJS_PRIVATE mjs_val_t mjs_pop(struct mjs *mjs);
MJS_PRIVATE void mjs_push(struct mjs *mjs, mjs_val_t v);
MJS_PRIVATE void mjs_die(struct mjs *mjs);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_CORE_H */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_conversion.h"
#endif

#ifndef MJS_CONVERSION_H_
#define MJS_CONVERSION_H_

/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

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
MJS_PRIVATE mjs_err_t mjs_to_string(struct mjs *mjs, mjs_val_t *v, char **p,
                                    size_t *sizep, int *need_free);

/*
 * Converts value to boolean as in the expression `if (v)`.
 */
MJS_PRIVATE mjs_val_t mjs_to_boolean_v(struct mjs *mjs, mjs_val_t v);

MJS_PRIVATE int mjs_is_truthy(struct mjs *mjs, mjs_val_t v);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_CONVERSION_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_object_public.h"
#endif

#ifndef MJS_OBJECT_PUBLIC_H_
#define MJS_OBJECT_PUBLIC_H_

#include <stddef.h>
/* Amalgamated: #include "mjs/src/mjs_core_public.h" */
/* Amalgamated: #include "mjs/src/mjs_ffi_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Returns true if the given value is an object or array.
 */
int mjs_is_object(mjs_val_t v);

/* Make an empty object */
mjs_val_t mjs_mk_object(struct mjs *mjs);

/* Field types for struct-object conversion. */
enum mjs_struct_field_type {
  MJS_STRUCT_FIELD_TYPE_INVALID,
  MJS_STRUCT_FIELD_TYPE_STRUCT,     /* Struct, arg points to def. */
  MJS_STRUCT_FIELD_TYPE_STRUCT_PTR, /* Ptr to struct, arg points to def. */
  MJS_STRUCT_FIELD_TYPE_INT,
  MJS_STRUCT_FIELD_TYPE_BOOL,
  MJS_STRUCT_FIELD_TYPE_DOUBLE,
  MJS_STRUCT_FIELD_TYPE_FLOAT,
  MJS_STRUCT_FIELD_TYPE_CHAR_PTR,   /* NUL-terminated string. */
  MJS_STRUCT_FIELD_TYPE_VOID_PTR,   /* Converted to foreign ptr. */
  MJS_STRUCT_FIELD_TYPE_MG_STR_PTR, /* Converted to string. */
  MJS_STRUCT_FIELD_TYPE_MG_STR,     /* Converted to string. */
  MJS_STRUCT_FIELD_TYPE_DATA,       /* Data, arg is length, becomes string. */
  MJS_STRUCT_FIELD_TYPE_INT8,
  MJS_STRUCT_FIELD_TYPE_INT16,
  MJS_STRUCT_FIELD_TYPE_UINT8,
  MJS_STRUCT_FIELD_TYPE_UINT16,
  /*
   * User-provided function. Arg is a pointer to function that takes void *
   * (pointer to field within the struct) and returns mjs_val_t:
   * mjs_val_t field_value(struct mjs *mjs, const void *field_ptr) { ... }
   */
  MJS_STRUCT_FIELD_TYPE_CUSTOM,
};

/* C structure layout descriptor - needed by mjs_struct_to_obj */
struct mjs_c_struct_member {
  const char *name;
  int offset;
  enum mjs_struct_field_type type;
  const void *arg; /* Additional argument, used for some types. */
};

/* Create flat JS object from a C memory descriptor */
mjs_val_t mjs_struct_to_obj(struct mjs *mjs, const void *base,
                            const struct mjs_c_struct_member *members);

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
 * Like mjs_get_v but lookup the prototype chain.
 */
mjs_val_t mjs_get_v_proto(struct mjs *mjs, mjs_val_t obj, mjs_val_t key);

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

/*
 * Delete own property `name` of the object `obj`. Does not follow the
 * prototype chain.
 *
 * If `name_len` is ~0, `name` is assumed to be NUL-terminated and
 * `strlen(name)` is used.
 *
 * Returns 0 on success, -1 on error.
 */
int mjs_del(struct mjs *mjs, mjs_val_t obj, const char *name, size_t len);

/*
 * Iterate over `obj` properties.
 * First call should set `iterator` to MJS_UNDEFINED.
 * Return object's key (a string), or MJS_UNDEFINED when no more keys left.
 * Do not mutate the object during iteration.
 *
 * Example:
 *   mjs_val_t key, iter = MJS_UNDEFINED;
 *   while ((key = mjs_next(mjs, obj, &iter)) != MJS_UNDEFINED) {
 *     // Do something with the obj/key ...
 *   }
 */
mjs_val_t mjs_next(struct mjs *mjs, mjs_val_t obj, mjs_val_t *iterator);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_OBJECT_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_object.h"
#endif

#ifndef MJS_OBJECT_H_
#define MJS_OBJECT_H_

/* Amalgamated: #include "mjs/src/mjs_object_public.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

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

MJS_PRIVATE struct mjs_property *mjs_get_own_property_v(struct mjs *mjs,
                                                        mjs_val_t obj,
                                                        mjs_val_t key);

/*
 * A worker function for `mjs_set()` and `mjs_set_v()`: it takes name as both
 * ptr+len and mjs_val_t. If `name` pointer is not NULL, it takes precedence
 * over `name_v`.
 */
MJS_PRIVATE mjs_err_t mjs_set_internal(struct mjs *mjs, mjs_val_t obj,
                                       mjs_val_t name_v, char *name,
                                       size_t name_len, mjs_val_t val);

/*
 * Implementation of `Object.create(proto)`
 */
MJS_PRIVATE void mjs_op_create_object(struct mjs *mjs);

#define MJS_PROTO_PROP_NAME "__p" /* Make it < 5 chars */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_OBJECT_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_primitive_public.h"
#endif

#ifndef MJS_PRIMITIVE_PUBLIC_H_
#define MJS_PRIMITIVE_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* JavaScript `null` value */
#define MJS_NULL MJS_TAG_NULL

/* JavaScript `undefined` value */
#define MJS_UNDEFINED MJS_TAG_UNDEFINED

/* Function pointer type used in `mjs_mk_foreign_func`. */
typedef void (*mjs_func_ptr_t)(void);

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
 * Make JavaScript value that holds C/C++ function pointer, similarly to
 * `mjs_mk_foreign`.
 */
mjs_val_t mjs_mk_foreign_func(struct mjs *mjs, mjs_func_ptr_t fn);

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

mjs_val_t mjs_mk_function(struct mjs *mjs, size_t off);
int mjs_is_function(mjs_val_t v);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_PRIMITIVE_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_primitive.h"
#endif

#ifndef MJS_PRIMITIVE_H
#define MJS_PRIMITIVE_H

/* Amalgamated: #include "mjs/src/mjs_primitive_public.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Convert a pointer to mjs_val_t. If pointer is not valid, mjs crashes.
 */
MJS_PRIVATE mjs_val_t mjs_legit_pointer_to_value(void *p);

/*
 * Convert a pointer to mjs_val_t. If pointer is not valid, error is set
 * in the mjs context.
 */
MJS_PRIVATE mjs_val_t mjs_pointer_to_value(struct mjs *mjs, void *p);

/*
 * Extracts a pointer from the mjs_val_t value.
 */
MJS_PRIVATE void *get_ptr(mjs_val_t v);

/*
 * Implementation for JS isNaN()
 */
MJS_PRIVATE void mjs_op_isnan(struct mjs *mjs);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_PRIMITIVE_H */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_string_public.h"
#endif

#ifndef MJS_STRING_PUBLIC_H_
#define MJS_STRING_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */

#define MJS_STRING_LITERAL_MAX_LEN 128

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

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

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_STRING_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_string.h"
#endif

#ifndef MJS_STRING_H_
#define MJS_STRING_H_

/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_string_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Size of the extra space for strings mbuf that is needed to avoid frequent
 * reallocations
 */
#define _MJS_STRING_BUF_RESERVE 100

MJS_PRIVATE unsigned long cstr_to_ulong(const char *s, size_t len, int *ok);
MJS_PRIVATE mjs_err_t
str_to_ulong(struct mjs *mjs, mjs_val_t v, int *ok, unsigned long *res);
MJS_PRIVATE int s_cmp(struct mjs *mjs, mjs_val_t a, mjs_val_t b);
MJS_PRIVATE mjs_val_t s_concat(struct mjs *mjs, mjs_val_t a, mjs_val_t b);

MJS_PRIVATE void embed_string(struct mbuf *m, size_t offset, const char *p,
                              size_t len, uint8_t /*enum embstr_flags*/ flags);

MJS_PRIVATE void mjs_mkstr(struct mjs *mjs);

MJS_PRIVATE void mjs_string_slice(struct mjs *mjs);
MJS_PRIVATE void mjs_string_index_of(struct mjs *mjs);
MJS_PRIVATE void mjs_string_char_code_at(struct mjs *mjs);

#define EMBSTR_ZERO_TERM 1
#define EMBSTR_UNESCAPE 2

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_STRING_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_util_public.h"
#endif

#ifndef MJS_UTIL_PUBLIC_H_
#define MJS_UTIL_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */
#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

const char *mjs_typeof(mjs_val_t v);

void mjs_fprintf(mjs_val_t v, struct mjs *mjs, FILE *fp);
void mjs_sprintf(mjs_val_t v, struct mjs *mjs, char *buf, size_t buflen);

#if MJS_ENABLE_DEBUG

void mjs_disasm(const uint8_t *code, size_t len);
void mjs_dump(struct mjs *mjs, int do_disasm);

#endif

/*
 * Returns the filename corresponding to the given bcode offset.
 */
const char *mjs_get_bcode_filename_by_offset(struct mjs *mjs, int offset);

/*
 * Returns the line number corresponding to the given bcode offset.
 */
int mjs_get_lineno_by_offset(struct mjs *mjs, int offset);

/*
 * Returns bcode offset of the corresponding call frame cf_num, where 0 means
 * the currently executing function, 1 means the first return address, etc.
 *
 * If given cf_num is too large, -1 is returned.
 */
int mjs_get_offset_by_call_frame_num(struct mjs *mjs, int cf_num);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_UTIL_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_util.h"
#endif

#ifndef MJS_UTIL_H_
#define MJS_UTIL_H_

/* Amalgamated: #include "frozen.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_util_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

struct mjs_bcode_part;

MJS_PRIVATE const char *opcodetostr(uint8_t opcode);
MJS_PRIVATE size_t mjs_disasm_single(const uint8_t *code, size_t i);
MJS_PRIVATE const char *mjs_stringify_type(enum mjs_type t);

/*
 * Checks that the given argument is provided, and checks its type. If check
 * fails, sets error in the mjs context, and returns 0; otherwise returns 1.
 *
 * If `arg_num` >= 0, checks argument; otherwise (`arg_num` is negative) checks
 * `this`. `arg_name` is used for the error message only. If `parg` is not
 * NULL, writes resulting value at this location in case of success.
 */
MJS_PRIVATE int mjs_check_arg(struct mjs *mjs, int arg_num,
                              const char *arg_name, enum mjs_type expected_type,
                              mjs_val_t *parg);

/*
 * mjs_normalize_idx takes and index in the string and the string size, and
 * returns the index which is >= 0 and <= size. Negative index is interpreted
 * as size + index.
 */
MJS_PRIVATE int mjs_normalize_idx(int idx, int size);

MJS_PRIVATE const char *mjs_get_bcode_filename(struct mjs *mjs,
                                               struct mjs_bcode_part *bp);

/* Print JS value `v` to the JSON stream `out`. */
void mjs_jprintf(mjs_val_t v, struct mjs *mjs, struct json_out *out);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_UTIL_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "common/cs_varint.h"
#endif

#ifndef CS_COMMON_CS_VARINT_H_
#define CS_COMMON_CS_VARINT_H_

#if defined(_WIN32) && _MSC_VER < 1700
typedef unsigned char uint8_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Returns number of bytes required to encode `num`. */
size_t cs_varint_llen(uint64_t num);

/*
 * Encodes `num` into `buf`.
 * Returns number of bytes required to encode `num`.
 * Note: return value may be greater than `buf_size` but the function will only
 * write `buf_size` bytes.
 */
size_t cs_varint_encode(uint64_t num, uint8_t *buf, size_t buf_size);

/*
 * Decodes varint stored in `buf`.
 * Stores the number of bytes consumed into `llen`.
 * If there aren't enough bytes in `buf` to decode a number, returns false.
 */
bool cs_varint_decode(const uint8_t *buf, size_t buf_size, uint64_t *num,
                      size_t *llen);

uint64_t cs_varint_decode_unsafe(const uint8_t *buf, int *llen);

#ifdef __cplusplus
}
#endif

#endif /* CS_COMMON_CS_VARINT_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_bcode.h"
#endif

#ifndef MJS_BCODE_H_
#define MJS_BCODE_H_

/* Amalgamated: #include "mjs/src/mjs_internal.h" */

/* Amalgamated: #include "mjs/src/mjs_core.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

enum mjs_opcode {
  OP_NOP,               /* ( -- ) */
  OP_DROP,              /* ( a -- ) */
  OP_DUP,               /* ( a -- a a ) */
  OP_SWAP,              /* ( a b -- b a ) */
  OP_JMP,               /* ( -- ) */
  OP_JMP_TRUE,          /* ( -- ) */
  OP_JMP_NEUTRAL_TRUE,  /* ( -- ) */
  OP_JMP_FALSE,         /* ( -- ) */
  OP_JMP_NEUTRAL_FALSE, /* ( -- ) */
  OP_FIND_SCOPE,        /* ( a -- a b ) */
  OP_PUSH_SCOPE,        /* ( -- a ) */
  OP_PUSH_STR,          /* ( -- a ) */
  OP_PUSH_TRUE,         /* ( -- a ) */
  OP_PUSH_FALSE,        /* ( -- a ) */
  OP_PUSH_INT,          /* ( -- a ) */
  OP_PUSH_DBL,          /* ( -- a ) */
  OP_PUSH_NULL,         /* ( -- a ) */
  OP_PUSH_UNDEF,        /* ( -- a ) */
  OP_PUSH_OBJ,          /* ( -- a ) */
  OP_PUSH_ARRAY,        /* ( -- a ) */
  OP_PUSH_FUNC,         /* ( -- a ) */
  OP_PUSH_THIS,         /* ( -- a ) */
  OP_GET,               /* ( key obj  -- obj[key] ) */
  OP_CREATE,            /* ( key obj -- ) */
  OP_EXPR,              /* ( ... -- a ) */
  OP_APPEND,            /* ( a b -- ) */
  OP_SET_ARG,           /* ( a -- a ) */
  OP_NEW_SCOPE,         /* ( -- ) */
  OP_DEL_SCOPE,         /* ( -- ) */
  OP_CALL,              /* ( func param1 param2 ... num_params -- result ) */
  OP_RETURN,            /* ( -- ) */
  OP_LOOP,         /* ( -- ) Push break & continue addresses to loop_labels */
  OP_BREAK,        /* ( -- ) */
  OP_CONTINUE,     /* ( -- ) */
  OP_SETRETVAL,    /* ( a -- ) */
  OP_EXIT,         /* ( -- ) */
  OP_BCODE_HEADER, /* ( -- ) */
  OP_ARGS,         /* ( -- ) Mark the beginning of function call arguments */
  OP_FOR_IN_NEXT,  /* ( name obj iter_ptr -- name obj iter_ptr_next ) */
  OP_MAX
};

struct pstate;
struct mjs;

MJS_PRIVATE void emit_byte(struct pstate *pstate, uint8_t byte);
MJS_PRIVATE void emit_int(struct pstate *pstate, int64_t n);
MJS_PRIVATE void emit_str(struct pstate *pstate, const char *ptr, size_t len);

/*
 * Inserts provided offset `v` at the offset `offset`.
 *
 * Returns delta at which the code was moved; the delta can be any: 0 or
 * positive or negative.
 */
MJS_PRIVATE int mjs_bcode_insert_offset(struct pstate *p, struct mjs *mjs,
                                        size_t offset, size_t v);

/*
 * Adds a new bcode part; does not retain `bp`.
 */
MJS_PRIVATE void mjs_bcode_part_add(struct mjs *mjs,
                                    const struct mjs_bcode_part *bp);

/*
 * Returns bcode part by the bcode number
 */
MJS_PRIVATE struct mjs_bcode_part *mjs_bcode_part_get(struct mjs *mjs, int num);

/*
 * Returns bcode part by the global bcode offset
 */
MJS_PRIVATE struct mjs_bcode_part *mjs_bcode_part_get_by_offset(struct mjs *mjs,
                                                                size_t offset);

/*
 * Returns a number of bcode parts
 */
MJS_PRIVATE int mjs_bcode_parts_cnt(struct mjs *mjs);

/*
 * Adds the bcode being generated (mjs->bcode_gen) as a next bcode part
 */
MJS_PRIVATE void mjs_bcode_commit(struct mjs *mjs);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_BCODE_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_internal.h"
#endif

#ifndef MJS_INTERNAL_H_
#define MJS_INTERNAL_H_

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

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

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#if !defined(WEAK)
#if (defined(__GNUC__) || defined(__TI_COMPILER_VERSION__)) && !defined(_WIN32)
#define WEAK __attribute__((weak))
#else
#define WEAK
#endif
#endif

#ifndef CS_ENABLE_STDIO
#define CS_ENABLE_STDIO 1
#endif

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "common/cs_file.h" */
/* Amalgamated: #include "common/mbuf.h" */

#if defined(_WIN32) && _MSC_VER < 1700
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef __int64 int64_t;
typedef unsigned long uintptr_t;
#define STRX(x) #x
#define STR(x) STRX(x)
#define __func__ __FILE__ ":" STR(__LINE__)
// #define snprintf _snprintf
#define vsnprintf _vsnprintf
#define isnan(x) _isnan(x)
#define va_copy(x, y) (x) = (y)
#define CS_DEFINE_DIRENT
#include <windows.h>
#else
#if defined(__unix__) || defined(__APPLE__)
#include <dlfcn.h>
#endif
#endif

/*
 * Number of bytes reserved for the jump offset initially. The most practical
 * value is 1, but for testing it's useful to set it to 0 and to some large
 * value as well (like, 4), to make sure that the code behaves correctly under
 * all circumstances.
 */
#ifndef MJS_INIT_OFFSET_SIZE
#define MJS_INIT_OFFSET_SIZE 1
#endif

#endif /* MJS_INTERNAL_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_tok.h"
#endif

#ifndef MJS_TOK_H_
#define MJS_TOK_H_

/* Amalgamated: #include "mjs_internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

struct tok {
  int tok;
  int len;
  const char *ptr;
};

struct pstate {
  const char *file_name; /* Source code file name */
  const char *buf;       /* Nul-terminated source code buffer */
  const char *pos;       /* Current position */
  int line_no;           /* Line number */
  int last_emitted_line_no;
  struct mbuf offset_lineno_map;
  int prev_tok;   /* Previous token, for prefix increment / decrement */
  struct tok tok; /* Parsed token */
  struct mjs *mjs;
  int start_bcode_idx; /* Index in mjs->bcode at which parsing was started */
  int cur_idx; /* Index in mjs->bcode at which newly generated code is inserted
                  */
  int depth;
};

enum {
  TOK_EOF,
  TOK_INVALID,

  TOK_COLON,
  TOK_SEMICOLON,
  TOK_COMMA,
  TOK_ASSIGN,
  TOK_OPEN_CURLY,
  TOK_CLOSE_CURLY,
  TOK_OPEN_PAREN,
  TOK_CLOSE_PAREN,
  TOK_OPEN_BRACKET,
  TOK_CLOSE_BRACKET,
  TOK_MUL,
  TOK_PLUS,
  TOK_MINUS,
  TOK_DIV,
  TOK_REM,
  TOK_AND,
  TOK_OR,
  TOK_XOR,
  TOK_DOT,
  TOK_QUESTION,
  TOK_NOT,
  TOK_TILDA,
  TOK_LT,
  TOK_GT,
  TOK_LSHIFT,
  TOK_RSHIFT,
  TOK_MINUS_MINUS,
  TOK_PLUS_PLUS,
  TOK_PLUS_ASSIGN,
  TOK_MINUS_ASSIGN,
  TOK_MUL_ASSIGN,
  TOK_DIV_ASSIGN,
  TOK_AND_ASSIGN,
  TOK_OR_ASSIGN,
  TOK_REM_ASSIGN,
  TOK_XOR_ASSIGN,
  TOK_EQ,
  TOK_NE,
  TOK_LE,
  TOK_GE,
  TOK_LOGICAL_AND,
  TOK_LOGICAL_OR,
  TOK_EQ_EQ,
  TOK_NE_NE,
  TOK_LSHIFT_ASSIGN,
  TOK_RSHIFT_ASSIGN,
  TOK_URSHIFT,
  TOK_URSHIFT_ASSIGN,

  TOK_UNARY_PLUS,
  TOK_UNARY_MINUS,
  TOK_POSTFIX_PLUS,
  TOK_POSTFIX_MINUS,

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
  TOK_KEYWORD_UNDEFINED,
  TOK_MAX
};

MJS_PRIVATE void pinit(const char *file_name, const char *buf, struct pstate *);
MJS_PRIVATE int pnext(struct pstate *);
MJS_PRIVATE int mjs_is_ident(int c);
MJS_PRIVATE int mjs_is_digit(int c);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_TOK_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_dataview.h"
#endif

#ifndef MJS_DATAVIEW_H_
#define MJS_DATAVIEW_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Functions for memory introspection.
 * These are supposed to be FFI-ed and used from the JS environment.
 */

void *mjs_mem_to_ptr(unsigned int val);
void *mjs_mem_get_ptr(void *base, int offset);
void mjs_mem_set_ptr(void *ptr, void *val);
double mjs_mem_get_dbl(void *ptr);
void mjs_mem_set_dbl(void *ptr, double val);
double mjs_mem_get_uint(void *ptr, int size, int bigendian);
double mjs_mem_get_int(void *ptr, int size, int bigendian);
void mjs_mem_set_uint(void *ptr, unsigned int val, int size, int bigendian);
void mjs_mem_set_int(void *ptr, int val, int size, int bigendian);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_DATAVIEW_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_exec_public.h"
#endif

#ifndef MJS_EXEC_PUBLIC_H_
#define MJS_EXEC_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */
#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

mjs_err_t mjs_exec(struct mjs *, const char *src, mjs_val_t *res);
mjs_err_t mjs_exec_buf(struct mjs *, const char *src, size_t, mjs_val_t *res);

mjs_err_t mjs_exec_file(struct mjs *mjs, const char *path, mjs_val_t *res);
mjs_err_t mjs_apply(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                    mjs_val_t this_val, int nargs, mjs_val_t *args);
mjs_err_t mjs_call(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                   mjs_val_t this_val, int nargs, ...);
mjs_val_t mjs_get_this(struct mjs *mjs);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_EXEC_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_exec.h"
#endif

#ifndef MJS_EXEC_H_
#define MJS_EXEC_H_

/* Amalgamated: #include "mjs/src/mjs_exec_public.h" */

/*
 * A special bcode offset value which causes mjs_execute() to exit immediately;
 * used in mjs_apply().
 */
#define MJS_BCODE_OFFSET_EXIT ((size_t) 0x7fffffff)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

MJS_PRIVATE mjs_err_t mjs_execute(struct mjs *mjs, size_t off, mjs_val_t *res);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_EXEC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_json.h"
#endif

#ifndef MJS_JSON_H_
#define MJS_JSON_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

MJS_PRIVATE mjs_err_t to_json_or_debug(struct mjs *mjs, mjs_val_t v, char *buf,
                                       size_t size, size_t *res_len,
                                       uint8_t is_debug);

MJS_PRIVATE mjs_err_t mjs_json_stringify(struct mjs *mjs, mjs_val_t v,
                                         char *buf, size_t size, char **res);
MJS_PRIVATE void mjs_op_json_stringify(struct mjs *mjs);
MJS_PRIVATE void mjs_op_json_parse(struct mjs *mjs);

MJS_PRIVATE mjs_err_t
mjs_json_parse(struct mjs *mjs, const char *str, size_t len, mjs_val_t *res);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_JSON_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_builtin.h"
#endif

#ifndef MJS_BUILTIN_H_
#define MJS_BUILTIN_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void mjs_init_builtin(struct mjs *mjs, mjs_val_t obj);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_BUILTIN_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_parser.h"
#endif

#ifndef MJS_PARSER_H
#define MJS_PARSER_H

/* Amalgamated: #include "mjs/src/mjs_internal.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

MJS_PRIVATE mjs_err_t
mjs_parse(const char *path, const char *buf, struct mjs *);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_PARSER_H */
#ifndef MJS_EXPORT_INTERNAL_HEADERS
#ifdef MJS_MODULE_LINES
#line 1 "common/cs_dbg.c"
#endif

/* Amalgamated: #include "common/cs_dbg.h" */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Amalgamated: #include "common/cs_time.h" */
/* Amalgamated: #include "common/str_util.h" */

enum cs_log_level cs_log_level WEAK =
#if CS_ENABLE_DEBUG
    LL_VERBOSE_DEBUG;
#else
    LL_ERROR;
#endif

#if CS_ENABLE_STDIO
static char *s_file_level = NULL;

void cs_log_set_file_level(const char *file_level) WEAK;

FILE *cs_log_file WEAK = NULL;

#if CS_LOG_ENABLE_TS_DIFF
double cs_log_ts WEAK;
#endif

enum cs_log_level cs_log_cur_msg_level WEAK = LL_NONE;

void cs_log_set_file_level(const char *file_level) {
  char *fl = s_file_level;
  if (file_level != NULL) {
    s_file_level = strdup(file_level);
  } else {
    s_file_level = NULL;
  }
  free(fl);
}

int cs_log_print_prefix(enum cs_log_level level, const char *file, int ln) WEAK;
int cs_log_print_prefix(enum cs_log_level level, const char *file, int ln) {
  char prefix[CS_LOG_PREFIX_LEN], *q;
  const char *p;
  size_t fl = 0, ll = 0, pl = 0;

  if (level > cs_log_level && s_file_level == NULL) return 0;

  p = file + strlen(file);

  while (p != file) {
    const char c = *(p - 1);
    if (c == '/' || c == '\\') break;
    p--;
    fl++;
  }

  ll = (ln < 10000 ? (ln < 1000 ? (ln < 100 ? (ln < 10 ? 1 : 2) : 3) : 4) : 5);
  if (fl > (sizeof(prefix) - ll - 2)) fl = (sizeof(prefix) - ll - 2);

  pl = fl + 1 + ll;
  memcpy(prefix, p, fl);
  q = prefix + pl;
  memset(q, ' ', sizeof(prefix) - pl);
  do {
    *(--q) = '0' + (ln % 10);
    ln /= 10;
  } while (ln > 0);
  *(--q) = ':';

  if (s_file_level != NULL) {
    enum cs_log_level pll = cs_log_level;
    struct mg_str fl = mg_mk_str(s_file_level), ps = MG_MK_STR_N(prefix, pl);
    struct mg_str k, v;
    while ((fl = mg_next_comma_list_entry_n(fl, &k, &v)).p != NULL) {
      bool yes = !(!mg_str_starts_with(ps, k) || v.len == 0);
      if (!yes) continue;
      pll = (enum cs_log_level)(*v.p - '0');
      break;
    }
    if (level > pll) return 0;
  }

  if (cs_log_file == NULL) cs_log_file = stderr;
  cs_log_cur_msg_level = level;
  fwrite(prefix, 1, sizeof(prefix), cs_log_file);
#if CS_LOG_ENABLE_TS_DIFF
  {
    double now = cs_time();
    fprintf(cs_log_file, "%7u ", (unsigned int) ((now - cs_log_ts) * 1000000));
    cs_log_ts = now;
  }
#endif
  return 1;
}

void cs_log_printf(const char *fmt, ...) WEAK;
void cs_log_printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(cs_log_file, fmt, ap);
  va_end(ap);
  fputc('\n', cs_log_file);
  fflush(cs_log_file);
  cs_log_cur_msg_level = LL_NONE;
}

void cs_log_set_file(FILE *file) WEAK;
void cs_log_set_file(FILE *file) {
  cs_log_file = file;
}

#else

void cs_log_set_file_level(const char *file_level) {
  (void) file_level;
}

#endif /* CS_ENABLE_STDIO */

void cs_log_set_level(enum cs_log_level level) WEAK;
void cs_log_set_level(enum cs_log_level level) {
  cs_log_level = level;
#if CS_LOG_ENABLE_TS_DIFF && CS_ENABLE_STDIO
  cs_log_ts = cs_time();
#endif
}
#ifdef MJS_MODULE_LINES
#line 1 "common/cs_file.c"
#endif

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
  int fd = open(path, O_RDONLY, 0);
  struct stat st;
  if (fd < 0) return NULL;
  fstat(fd, &st);
  *size = (size_t) st.st_size;
  r = (char *) mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (r == MAP_FAILED) return NULL;
  return r;
}
#endif
#ifdef MJS_MODULE_LINES
#line 1 "common/cs_varint.c"
#endif

/* Amalgamated: #include "cs_varint.h" */

size_t cs_varint_llen(uint64_t num) {
  size_t llen = 0;

  do {
    llen++;
  } while (num >>= 7);

  return llen;
}

size_t cs_varint_encode(uint64_t num, uint8_t *buf, size_t buf_size) {
  size_t llen = 0;

  do {
    uint8_t byte = num & 0x7f;
    num >>= 7;
    if (num != 0) byte |= 0x80;
    if (llen < buf_size) *buf++ = byte;
    llen++;
  } while (num != 0);

  return llen;
}

bool cs_varint_decode(const uint8_t *buf, size_t buf_size, uint64_t *num,
                      size_t *llen) {
  size_t i = 0, shift = 0;
  uint64_t n = 0;

  do {
    if (i == buf_size || i == (8 * sizeof(*num) / 7 + 1)) return false;
    /*
     * Each byte of varint contains 7 bits, in little endian order.
     * MSB is a continuation bit: it tells whether next byte is used.
     */
    n |= ((uint64_t)(buf[i] & 0x7f)) << shift;
    /*
     * First we increment i, then check whether it is within boundary and
     * whether decoded byte had continuation bit set.
     */
    i++;
    shift += 7;
  } while (shift < sizeof(uint64_t) * 8 && (buf[i - 1] & 0x80));

  *num = n;
  *llen = i;

  return true;
}

uint64_t cs_varint_decode_unsafe(const uint8_t *buf, int *llen) {
  uint64_t v;
  size_t l;
  cs_varint_decode(buf, ~0, &v, &l);
  *llen = l;
  return v;
}
#ifdef MJS_MODULE_LINES
#line 1 "common/mbuf.c"
#endif

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
    size_t min_size = (a->len + len);
    size_t new_size = (size_t)(min_size * MBUF_SIZE_MULTIPLIER);
    if (new_size - min_size > MBUF_SIZE_MAX_HEADROOM) {
      new_size = min_size + MBUF_SIZE_MAX_HEADROOM;
    }
    p = (char *) MBUF_REALLOC(a->buf, new_size);
    if (p == NULL && new_size != min_size) {
      new_size = min_size;
      p = (char *) MBUF_REALLOC(a->buf, new_size);
    }
    if (p != NULL) {
      a->buf = p;
      if (off != a->len) {
        memmove(a->buf + off + len, a->buf + off, a->len - off);
      }
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

size_t mbuf_append_and_free(struct mbuf *a, void *buf, size_t len) WEAK;
size_t mbuf_append_and_free(struct mbuf *a, void *data, size_t len) {
  size_t ret;
  /* Optimization: if the buffer is currently empty,
   * take over the user-provided buffer. */
  if (a->len == 0) {
    if (a->buf != NULL) free(a->buf);
    a->buf = (char *) data;
    a->len = a->size = len;
    return len;
  }
  ret = mbuf_insert(a, a->len, data, len);
  free(data);
  return ret;
}

void mbuf_remove(struct mbuf *mb, size_t n) WEAK;
void mbuf_remove(struct mbuf *mb, size_t n) {
  if (n > 0 && n <= mb->len) {
    memmove(mb->buf, mb->buf + n, mb->len - n);
    mb->len -= n;
  }
}

void mbuf_clear(struct mbuf *mb) WEAK;
void mbuf_clear(struct mbuf *mb) {
  mb->len = 0;
}

void mbuf_move(struct mbuf *from, struct mbuf *to) WEAK;
void mbuf_move(struct mbuf *from, struct mbuf *to) {
  memcpy(to, from, sizeof(*to));
  memset(from, 0, sizeof(*from));
}

#endif /* EXCLUDE_COMMON */
#ifdef MJS_MODULE_LINES
#line 1 "common/mg_str.c"
#endif

/* Amalgamated: #include "common/mg_mem.h" */
/* Amalgamated: #include "common/mg_str.h" */
/* Amalgamated: #include "common/platform.h" */

#include <ctype.h>
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
  int r = strncmp(str1->p, str2, (n1 < n2) ? n1 : n2);
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

static struct mg_str mg_strdup_common(const struct mg_str s,
                                      int nul_terminate) {
  struct mg_str r = {NULL, 0};
  if (s.len > 0 && s.p != NULL) {
    char *sc = (char *) MG_MALLOC(s.len + (nul_terminate ? 1 : 0));
    if (sc != NULL) {
      memcpy(sc, s.p, s.len);
      if (nul_terminate) sc[s.len] = '\0';
      r.p = sc;
      r.len = s.len;
    }
  }
  return r;
}

struct mg_str mg_strdup(const struct mg_str s) WEAK;
struct mg_str mg_strdup(const struct mg_str s) {
  return mg_strdup_common(s, 0 /* NUL-terminate */);
}

struct mg_str mg_strdup_nul(const struct mg_str s) WEAK;
struct mg_str mg_strdup_nul(const struct mg_str s) {
  return mg_strdup_common(s, 1 /* NUL-terminate */);
}

const char *mg_strchr(const struct mg_str s, int c) WEAK;
const char *mg_strchr(const struct mg_str s, int c) {
  size_t i;
  for (i = 0; i < s.len; i++) {
    if (s.p[i] == c) return &s.p[i];
  }
  return NULL;
}

int mg_strcmp(const struct mg_str str1, const struct mg_str str2) WEAK;
int mg_strcmp(const struct mg_str str1, const struct mg_str str2) {
  size_t i = 0;
  while (i < str1.len && i < str2.len) {
    int c1 = str1.p[i];
    int c2 = str2.p[i];
    if (c1 < c2) return -1;
    if (c1 > c2) return 1;
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

int mg_strcasecmp(const struct mg_str str1, const struct mg_str str2) WEAK;
int mg_strcasecmp(const struct mg_str str1, const struct mg_str str2) {
  size_t i = 0;
  while (i < str1.len && i < str2.len) {
    int c1 = tolower((int) str1.p[i]);
    int c2 = tolower((int) str2.p[i]);
    if (c1 < c2) return -1;
    if (c1 > c2) return 1;
    i++;
  }
  if (i < str1.len) return 1;
  if (i < str2.len) return -1;
  return 0;
}

void mg_strfree(struct mg_str *s) WEAK;
void mg_strfree(struct mg_str *s) {
  char *sp = (char *) s->p;
  s->p = NULL;
  s->len = 0;
  if (sp != NULL) free(sp);
}

const char *mg_strstr(const struct mg_str haystack,
                      const struct mg_str needle) WEAK;
const char *mg_strstr(const struct mg_str haystack,
                      const struct mg_str needle) {
  size_t i;
  if (needle.len > haystack.len) return NULL;
  for (i = 0; i <= haystack.len - needle.len; i++) {
    if (memcmp(haystack.p + i, needle.p, needle.len) == 0) {
      return haystack.p + i;
    }
  }
  return NULL;
}

struct mg_str mg_strstrip(struct mg_str s) WEAK;
struct mg_str mg_strstrip(struct mg_str s) {
  while (s.len > 0 && isspace((int) *s.p)) {
    s.p++;
    s.len--;
  }
  while (s.len > 0 && isspace((int) *(s.p + s.len - 1))) {
    s.len--;
  }
  return s;
}

int mg_str_starts_with(struct mg_str s, struct mg_str prefix) WEAK;
int mg_str_starts_with(struct mg_str s, struct mg_str prefix) {
  const struct mg_str sp = MG_MK_STR_N(s.p, prefix.len);
  if (s.len < prefix.len) return 0;
  return (mg_strcmp(sp, prefix) == 0);
}
#ifdef MJS_MODULE_LINES
#line 1 "common/str_util.c"
#endif

#ifndef EXCLUDE_COMMON

/* Amalgamated: #include "common/str_util.h" */
/* Amalgamated: #include "common/mg_mem.h" */
/* Amalgamated: #include "common/platform.h" */

#ifndef C_DISABLE_BUILTIN_SNPRINTF
#define C_DISABLE_BUILTIN_SNPRINTF 0
#endif

/* Amalgamated: #include "common/mg_mem.h" */

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
  char *ret = MG_MALLOC(len);
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
      if (size == 0) {
        size = 5;
      }
      size *= 2;
      if ((*buf = (char *) MG_MALLOC(size)) == NULL) {
        len = -1;
        break;
      }
      va_copy(ap_copy, ap);
      len = vsnprintf(*buf, size - 1, fmt, ap_copy);
      va_end(ap_copy);
    }

    /*
     * Microsoft version of vsnprintf() is not always null-terminated, so put
     * the terminator manually
     */
    (*buf)[len] = 0;
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

const char *mg_next_comma_list_entry(const char *, struct mg_str *,
                                     struct mg_str *) WEAK;
const char *mg_next_comma_list_entry(const char *list, struct mg_str *val,
                                     struct mg_str *eq_val) {
  struct mg_str ret = mg_next_comma_list_entry_n(mg_mk_str(list), val, eq_val);
  return ret.p;
}

struct mg_str mg_next_comma_list_entry_n(struct mg_str list, struct mg_str *val,
                                         struct mg_str *eq_val) WEAK;
struct mg_str mg_next_comma_list_entry_n(struct mg_str list, struct mg_str *val,
                                         struct mg_str *eq_val) {
  if (list.len == 0) {
    /* End of the list */
    list = mg_mk_str(NULL);
  } else {
    const char *chr = NULL;
    *val = list;

    if ((chr = mg_strchr(*val, ',')) != NULL) {
      /* Comma found. Store length and shift the list ptr */
      val->len = chr - val->p;
      chr++;
      list.len -= (chr - list.p);
      list.p = chr;
    } else {
      /* This value is the last one */
      list = mg_mk_str_n(list.p + list.len, 0);
    }

    if (eq_val != NULL) {
      /* Value has form "x=y", adjust pointers and lengths */
      /* so that val points to "x", and eq_val points to "y". */
      eq_val->len = 0;
      eq_val->p = (const char *) memchr(val->p, '=', val->len);
      if (eq_val->p != NULL) {
        eq_val->p++; /* Skip over '=' character */
        eq_val->len = val->p + val->len - eq_val->p;
        val->len = (eq_val->p - val->p) - 1;
      }
    }
  }

  return list;
}

size_t mg_match_prefix_n(const struct mg_str, const struct mg_str) WEAK;
size_t mg_match_prefix_n(const struct mg_str pattern, const struct mg_str str) {
  const char *or_str;
  size_t res = 0, len = 0, i = 0, j = 0;

  if ((or_str = (const char *) memchr(pattern.p, '|', pattern.len)) != NULL ||
      (or_str = (const char *) memchr(pattern.p, ',', pattern.len)) != NULL) {
    struct mg_str pstr = {pattern.p, (size_t)(or_str - pattern.p)};
    res = mg_match_prefix_n(pstr, str);
    if (res > 0) return res;
    pstr.p = or_str + 1;
    pstr.len = (pattern.p + pattern.len) - (or_str + 1);
    return mg_match_prefix_n(pstr, str);
  }

  for (; i < pattern.len && j < str.len; i++, j++) {
    if (pattern.p[i] == '?') {
      continue;
    } else if (pattern.p[i] == '*') {
      i++;
      if (i < pattern.len && pattern.p[i] == '*') {
        i++;
        len = str.len - j;
      } else {
        len = 0;
        while (j + len < str.len && str.p[j + len] != '/') len++;
      }
      if (i == pattern.len || (pattern.p[i] == '$' && i == pattern.len - 1))
        return j + len;
      do {
        const struct mg_str pstr = {pattern.p + i, pattern.len - i};
        const struct mg_str sstr = {str.p + j + len, str.len - j - len};
        res = mg_match_prefix_n(pstr, sstr);
      } while (res == 0 && len != 0 && len-- > 0);
      return res == 0 ? 0 : j + res + len;
    } else if (str_util_lowercase(&pattern.p[i]) !=
               str_util_lowercase(&str.p[j])) {
      break;
    }
  }
  if (i < pattern.len && pattern.p[i] == '$') {
    return j == str.len ? str.len : 0;
  }
  return i == pattern.len ? j : 0;
}

size_t mg_match_prefix(const char *, int, const char *) WEAK;
size_t mg_match_prefix(const char *pattern, int pattern_len, const char *str) {
  const struct mg_str pstr = {pattern, (size_t) pattern_len};
  struct mg_str s = {str, 0};
  if (str != NULL) s.len = strlen(str);
  return mg_match_prefix_n(pstr, s);
}

#endif /* EXCLUDE_COMMON */
#ifdef MJS_MODULE_LINES
#line 1 "frozen/frozen.c"
#endif

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
#undef snprintf
#undef vsnprintf
#define snprintf cs_win_snprintf
#define vsnprintf cs_win_vsnprintf
int cs_win_snprintf(char *str, size_t size, const char *format, ...);
int cs_win_vsnprintf(char *str, size_t size, const char *format, va_list ap);
#if _MSC_VER >= 1700 || (defined(__GNUC__))
#include <stdint.h>
#else
typedef _int64 int64_t;
typedef unsigned _int64 uint64_t;
#endif
#define PRId64 "I64d"
#define PRIu64 "I64u"
#else /* _WIN32 */
/* <inttypes.h> wants this for C++ */
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>
#endif /* _WIN32 */

#ifndef INT64_FMT
#define INT64_FMT PRId64
#endif
#ifndef UINT64_FMT
#define UINT64_FMT PRIu64
#endif

#ifndef va_copy
#define va_copy(x, y) x = y
#endif

#ifndef JSON_ENABLE_ARRAY
#define JSON_ENABLE_ARRAY 1
#endif

struct frozen {
  const char *end;
  const char *cur;

  const char *cur_name;
  size_t cur_name_len;

  /* For callback API */
  char path[JSON_MAX_PATH_LEN];
  size_t path_len;
  void *callback_data;
  json_walk_callback_t callback;
};

struct fstate {
  const char *ptr;
  size_t path_len;
};

#define SET_STATE(fr, ptr, str, len)              \
  struct fstate fstate = {(ptr), (fr)->path_len}; \
  json_append_to_path((fr), (str), (len));

#define CALL_BACK(fr, tok, value, len)                                        \
  do {                                                                        \
    if ((fr)->callback &&                                                     \
        ((fr)->path_len == 0 || (fr)->path[(fr)->path_len - 1] != '.')) {     \
      struct json_token t = {(value), (int) (len), (tok)};                    \
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

static int json_append_to_path(struct frozen *f, const char *str, int size) {
  int n = f->path_len;
  int left = sizeof(f->path) - n - 1;
  if (size > left) size = left;
  memcpy(f->path + n, str, size);
  f->path[n + size] = '\0';
  f->path_len += size;
  return n;
}

static void json_truncate_path(struct frozen *f, size_t len) {
  f->path_len = len;
  f->path[len] = '\0';
}

static int json_parse_object(struct frozen *f);
static int json_parse_value(struct frozen *f);

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

static int json_left(const struct frozen *f) {
  return f->end - f->cur;
}

static int json_isspace(int ch) {
  return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

static void json_skip_whitespaces(struct frozen *f) {
  while (f->cur < f->end && json_isspace(*f->cur)) f->cur++;
}

static int json_cur(struct frozen *f) {
  json_skip_whitespaces(f);
  return f->cur >= f->end ? END_OF_STRING : *(unsigned char *) f->cur;
}

static int json_test_and_skip(struct frozen *f, int expected) {
  int ch = json_cur(f);
  if (ch == expected) {
    f->cur++;
    return 0;
  }
  return ch == END_OF_STRING ? JSON_STRING_INCOMPLETE : JSON_STRING_INVALID;
}

static int json_isalpha(int ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

static int json_isdigit(int ch) {
  return ch >= '0' && ch <= '9';
}

static int json_isxdigit(int ch) {
  return json_isdigit(ch) || (ch >= 'a' && ch <= 'f') ||
         (ch >= 'A' && ch <= 'F');
}

static int json_get_escape_len(const char *s, int len) {
  switch (*s) {
    case 'u':
      return len < 6 ? JSON_STRING_INCOMPLETE
                     : json_isxdigit(s[1]) && json_isxdigit(s[2]) &&
                               json_isxdigit(s[3]) && json_isxdigit(s[4])
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
static int json_parse_identifier(struct frozen *f) {
  EXPECT(json_isalpha(json_cur(f)), JSON_STRING_INVALID);
  {
    SET_STATE(f, f->cur, "", 0);
    while (f->cur < f->end &&
           (*f->cur == '_' || json_isalpha(*f->cur) || json_isdigit(*f->cur))) {
      f->cur++;
    }
    json_truncate_path(f, fstate.path_len);
    CALL_BACK(f, JSON_TYPE_STRING, fstate.ptr, f->cur - fstate.ptr);
  }
  return 0;
}

static int json_get_utf8_char_len(unsigned char ch) {
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
static int json_parse_string(struct frozen *f) {
  int n, ch = 0, len = 0;
  TRY(json_test_and_skip(f, '"'));
  {
    SET_STATE(f, f->cur, "", 0);
    for (; f->cur < f->end; f->cur += len) {
      ch = *(unsigned char *) f->cur;
      len = json_get_utf8_char_len((unsigned char) ch);
      EXPECT(ch >= 32 && len > 0, JSON_STRING_INVALID); /* No control chars */
      EXPECT(len <= json_left(f), JSON_STRING_INCOMPLETE);
      if (ch == '\\') {
        EXPECT((n = json_get_escape_len(f->cur + 1, json_left(f))) > 0, n);
        len += n;
      } else if (ch == '"') {
        json_truncate_path(f, fstate.path_len);
        CALL_BACK(f, JSON_TYPE_STRING, fstate.ptr, f->cur - fstate.ptr);
        f->cur++;
        break;
      };
    }
  }
  return ch == '"' ? 0 : JSON_STRING_INCOMPLETE;
}

/* number = [ '-' ] digit+ [ '.' digit+ ] [ ['e'|'E'] ['+'|'-'] digit+ ] */
static int json_parse_number(struct frozen *f) {
  int ch = json_cur(f);
  SET_STATE(f, f->cur, "", 0);
  if (ch == '-') f->cur++;
  EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
  if (f->cur + 1 < f->end && f->cur[0] == '0' && f->cur[1] == 'x') {
    f->cur += 2;
    EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
    EXPECT(json_isxdigit(f->cur[0]), JSON_STRING_INVALID);
    while (f->cur < f->end && json_isxdigit(f->cur[0])) f->cur++;
  } else {
    EXPECT(json_isdigit(f->cur[0]), JSON_STRING_INVALID);
    while (f->cur < f->end && json_isdigit(f->cur[0])) f->cur++;
    if (f->cur < f->end && f->cur[0] == '.') {
      f->cur++;
      EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
      EXPECT(json_isdigit(f->cur[0]), JSON_STRING_INVALID);
      while (f->cur < f->end && json_isdigit(f->cur[0])) f->cur++;
    }
    if (f->cur < f->end && (f->cur[0] == 'e' || f->cur[0] == 'E')) {
      f->cur++;
      EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
      if ((f->cur[0] == '+' || f->cur[0] == '-')) f->cur++;
      EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
      EXPECT(json_isdigit(f->cur[0]), JSON_STRING_INVALID);
      while (f->cur < f->end && json_isdigit(f->cur[0])) f->cur++;
    }
  }
  json_truncate_path(f, fstate.path_len);
  CALL_BACK(f, JSON_TYPE_NUMBER, fstate.ptr, f->cur - fstate.ptr);
  return 0;
}

#if JSON_ENABLE_ARRAY
/* array = '[' [ value { ',' value } ] ']' */
static int json_parse_array(struct frozen *f) {
  int i = 0, current_path_len;
  char buf[20];
  CALL_BACK(f, JSON_TYPE_ARRAY_START, NULL, 0);
  TRY(json_test_and_skip(f, '['));
  {
    {
      SET_STATE(f, f->cur - 1, "", 0);
      while (json_cur(f) != ']') {
        snprintf(buf, sizeof(buf), "[%d]", i);
        i++;
        current_path_len = json_append_to_path(f, buf, strlen(buf));
        f->cur_name =
            f->path + strlen(f->path) - strlen(buf) + 1 /*opening brace*/;
        f->cur_name_len = strlen(buf) - 2 /*braces*/;
        TRY(json_parse_value(f));
        json_truncate_path(f, current_path_len);
        if (json_cur(f) == ',') f->cur++;
      }
      TRY(json_test_and_skip(f, ']'));
      json_truncate_path(f, fstate.path_len);
      CALL_BACK(f, JSON_TYPE_ARRAY_END, fstate.ptr, f->cur - fstate.ptr);
    }
  }
  return 0;
}
#endif /* JSON_ENABLE_ARRAY */

static int json_expect(struct frozen *f, const char *s, int len,
                       enum json_token_type tok_type) {
  int i, n = json_left(f);
  SET_STATE(f, f->cur, "", 0);
  for (i = 0; i < len; i++) {
    if (i >= n) return JSON_STRING_INCOMPLETE;
    if (f->cur[i] != s[i]) return JSON_STRING_INVALID;
  }
  f->cur += len;
  json_truncate_path(f, fstate.path_len);

  CALL_BACK(f, tok_type, fstate.ptr, f->cur - fstate.ptr);

  return 0;
}

/* value = 'null' | 'true' | 'false' | number | string | array | object */
static int json_parse_value(struct frozen *f) {
  int ch = json_cur(f);

  switch (ch) {
    case '"':
      TRY(json_parse_string(f));
      break;
    case '{':
      TRY(json_parse_object(f));
      break;
#if JSON_ENABLE_ARRAY
    case '[':
      TRY(json_parse_array(f));
      break;
#endif
    case 'n':
      TRY(json_expect(f, "null", 4, JSON_TYPE_NULL));
      break;
    case 't':
      TRY(json_expect(f, "true", 4, JSON_TYPE_TRUE));
      break;
    case 'f':
      TRY(json_expect(f, "false", 5, JSON_TYPE_FALSE));
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
      TRY(json_parse_number(f));
      break;
    default:
      return ch == END_OF_STRING ? JSON_STRING_INCOMPLETE : JSON_STRING_INVALID;
  }

  return 0;
}

/* key = identifier | string */
static int json_parse_key(struct frozen *f) {
  int ch = json_cur(f);
  if (json_isalpha(ch)) {
    TRY(json_parse_identifier(f));
  } else if (ch == '"') {
    TRY(json_parse_string(f));
  } else {
    return ch == END_OF_STRING ? JSON_STRING_INCOMPLETE : JSON_STRING_INVALID;
  }
  return 0;
}

/* pair = key ':' value */
static int json_parse_pair(struct frozen *f) {
  int current_path_len;
  const char *tok;
  json_skip_whitespaces(f);
  tok = f->cur;
  TRY(json_parse_key(f));
  {
    f->cur_name = *tok == '"' ? tok + 1 : tok;
    f->cur_name_len = *tok == '"' ? f->cur - tok - 2 : f->cur - tok;
    current_path_len = json_append_to_path(f, f->cur_name, f->cur_name_len);
  }
  TRY(json_test_and_skip(f, ':'));
  TRY(json_parse_value(f));
  json_truncate_path(f, current_path_len);
  return 0;
}

/* object = '{' pair { ',' pair } '}' */
static int json_parse_object(struct frozen *f) {
  CALL_BACK(f, JSON_TYPE_OBJECT_START, NULL, 0);
  TRY(json_test_and_skip(f, '{'));
  {
    SET_STATE(f, f->cur - 1, ".", 1);
    while (json_cur(f) != '}') {
      TRY(json_parse_pair(f));
      if (json_cur(f) == ',') f->cur++;
    }
    TRY(json_test_and_skip(f, '}'));
    json_truncate_path(f, fstate.path_len);
    CALL_BACK(f, JSON_TYPE_OBJECT_END, fstate.ptr, f->cur - fstate.ptr);
  }
  return 0;
}

static int json_doit(struct frozen *f) {
  if (f->cur == 0 || f->end < f->cur) return JSON_STRING_INVALID;
  if (f->end == f->cur) return JSON_STRING_INCOMPLETE;
  return json_parse_value(f);
}

int json_escape(struct json_out *out, const char *p, size_t len) WEAK;
int json_escape(struct json_out *out, const char *p, size_t len) {
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
    } else if ((cl = json_get_utf8_char_len(ch)) == 1) {
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

#if JSON_ENABLE_BASE64
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
#endif /* JSON_ENABLE_BASE64 */

static unsigned char hexdec(const char *s) {
#define HEXTOI(x) (x >= '0' && x <= '9' ? x - '0' : x - 'W')
  int a = tolower(*(const unsigned char *) s);
  int b = tolower(*(const unsigned char *) (s + 1));
  return (HEXTOI(a) << 4) | HEXTOI(b);
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
        snprintf(buf, sizeof(buf), "%lu", (unsigned long) val);
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
#if JSON_ENABLE_HEX
        const char *hex = "0123456789abcdef";
        int i, n = va_arg(ap, int);
        const unsigned char *p = va_arg(ap, const unsigned char *);
        len += out->printer(out, quote, 1);
        for (i = 0; i < n; i++) {
          len += out->printer(out, &hex[(p[i] >> 4) & 0xf], 1);
          len += out->printer(out, &hex[p[i] & 0xf], 1);
        }
        len += out->printer(out, quote, 1);
#endif /* JSON_ENABLE_HEX */
      } else if (fmt[1] == 'V') {
#if JSON_ENABLE_BASE64
        const unsigned char *p = va_arg(ap, const unsigned char *);
        int n = va_arg(ap, int);
        len += out->printer(out, quote, 1);
        len += b64enc(out, p, n);
        len += out->printer(out, quote, 1);
#endif /* JSON_ENABLE_BASE64 */
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
          len += json_escape(out, p, l);
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

        const char *end_of_format_specifier = "sdfFeEgGlhuIcx.*-0123456789";
        int n = strspn(fmt + 1, end_of_format_specifier);
        char *pbuf = buf;
        int need_len, size = sizeof(buf);
        char fmt2[20];
        va_list ap_copy;
        strncpy(fmt2, fmt,
                n + 1 > (int) sizeof(fmt2) ? sizeof(fmt2) : (size_t) n + 1);
        fmt2[n + 1] = '\0';

        va_copy(ap_copy, ap);
        need_len = vsnprintf(pbuf, size, fmt2, ap_copy);
        va_end(ap_copy);

        if (need_len < 0) {
          /*
           * Windows & eCos vsnprintf implementation return -1 on overflow
           * instead of needed size.
           */
          pbuf = NULL;
          while (need_len < 0) {
            free(pbuf);
            size *= 2;
            if ((pbuf = (char *) malloc(size)) == NULL) break;
            va_copy(ap_copy, ap);
            need_len = vsnprintf(pbuf, size, fmt2, ap_copy);
            va_end(ap_copy);
          }
        } else if (need_len >= (int) sizeof(buf)) {
          /*
           * resulting string doesn't fit into a stack-allocated buffer `buf`,
           * so we need to allocate a new buffer from heap and use it
           */
          if ((pbuf = (char *) malloc(need_len + 1)) != NULL) {
            va_copy(ap_copy, ap);
            vsnprintf(pbuf, need_len + 1, fmt2, ap_copy);
            va_end(ap_copy);
          }
        }
        if (pbuf == NULL) {
          buf[0] = '\0';
          pbuf = buf;
        }

        /*
         * however we need to parse the type ourselves in order to advance
         * the va_list by the correct amount; there is no portable way to
         * inherit the advancement made by vprintf.
         * 32-bit (linux or windows) passes va_list by value.
         */
        if ((n + 1 == (int) strlen("%" PRId64) &&
             strcmp(fmt2, "%" PRId64) == 0) ||
            (n + 1 == (int) strlen("%" PRIu64) &&
             strcmp(fmt2, "%" PRIu64) == 0)) {
          (void) va_arg(ap, int64_t);
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
    } else if (*fmt == '_' || json_isalpha(*fmt)) {
      len += out->printer(out, quote, 1);
      while (*fmt == '_' || json_isalpha(*fmt) || json_isdigit(*fmt)) {
        len += out->printer(out, fmt, 1);
        fmt++;
      }
      len += out->printer(out, quote, 1);
    } else {
      len += out->printer(out, fmt, 1);
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
    if (strpbrk(fmt, "efg") != NULL) {
      len += json_printf(out, fmt, val.d);
    } else {
      len += json_printf(out, fmt, val.i);
    }
  }
  len += json_printf(out, "]", 1);
  return len;
}

#ifdef _WIN32
int cs_win_vsnprintf(char *str, size_t size, const char *format,
                     va_list ap) WEAK;
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

  TRY(json_doit(&frozen));

  return frozen.cur - json_string;
}

struct scan_array_info {
  int found;
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
    info->found = 1;
  }
}

int json_scanf_array_elem(const char *s, int len, const char *path, int idx,
                          struct json_token *token) WEAK;
int json_scanf_array_elem(const char *s, int len, const char *path, int idx,
                          struct json_token *token) {
  struct scan_array_info info;
  info.token = token;
  info.found = 0;
  memset(token, 0, sizeof(*token));
  snprintf(info.path, sizeof(info.path), "%s[%d]", path, idx);
  json_walk(s, len, json_scanf_array_elem_cb, &info);
  return info.found ? token->len : -1;
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
        if (send - src < 5) return JSON_STRING_INCOMPLETE;
        /* Here we go: this is a \u.... escape. Process simple one-byte chars */
        if (src[1] == '0' && src[2] == '0') {
          /* This is \u00xx character from the ASCII range */
          if (dst < dend) *dst = hexdec(src + 3);
          src += 4;
        } else {
          /* Complex \uXXXX escapes drag utf8 lib... Do it at some stage */
          return JSON_STRING_INVALID;
        }
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
  char buf[32]; /* Must be enough to hold numbers */

  (void) name;
  (void) name_len;

  if (token->ptr == NULL) {
    /*
     * We're not interested here in the events for which we have no value;
     * namely, JSON_TYPE_OBJECT_START and JSON_TYPE_ARRAY_START
     */
    return;
  }

  if (strcmp(path, info->path) != 0) {
    /* It's not the path we're looking for, so, just ignore this callback */
    return;
  }

  switch (info->type) {
    case 'B':
      info->num_conversions++;
      switch (sizeof(bool)) {
        case sizeof(char):
          *(char *) info->target = (token->type == JSON_TYPE_TRUE ? 1 : 0);
          break;
        case sizeof(int):
          *(int *) info->target = (token->type == JSON_TYPE_TRUE ? 1 : 0);
          break;
        default:
          /* should never be here */
          abort();
      }
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
      if (token->type == JSON_TYPE_NULL) {
        *dst = NULL;
      } else {
        int unescaped_len = json_unescape(token->ptr, token->len, NULL, 0);
        if (unescaped_len >= 0 &&
            (*dst = (char *) malloc(unescaped_len + 1)) != NULL) {
          info->num_conversions++;
          if (json_unescape(token->ptr, token->len, *dst, unescaped_len) ==
              unescaped_len) {
            (*dst)[unescaped_len] = '\0';
          } else {
            free(*dst);
            *dst = NULL;
          }
        }
      }
      break;
    }
    case 'H': {
#if JSON_ENABLE_HEX
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
#endif /* JSON_ENABLE_HEX */
      break;
    }
    case 'V': {
#if JSON_ENABLE_BASE64
      char **dst = (char **) info->target;
      int len = token->len * 4 / 3 + 2;
      if ((*dst = (char *) malloc(len + 1)) != NULL) {
        int n = b64dec(token->ptr, token->len, *dst);
        (*dst)[n] = '\0';
        *(int *) info->user_data = n;
        info->num_conversions++;
      }
#endif /* JSON_ENABLE_BASE64 */
      break;
    }
    case 'T':
      info->num_conversions++;
      *(struct json_token *) info->target = *token;
      break;
    default:
      if (token->len >= (int) sizeof(buf)) break;
      /* Before converting, copy into tmp buffer in order to 0-terminate it */
      memcpy(buf, token->ptr, token->len);
      buf[token->len] = '\0';
      /* NB: Use of base 0 for %d, %ld, %u and %lu is intentional. */
      if (info->fmt[1] == 'd' || (info->fmt[1] == 'l' && info->fmt[2] == 'd') ||
          info->fmt[1] == 'i') {
        char *endptr = NULL;
        long r = strtol(buf, &endptr, 0 /* base */);
        if (*endptr == '\0') {
          if (info->fmt[1] == 'l') {
            *((long *) info->target) = r;
          } else {
            *((int *) info->target) = (int) r;
          }
          info->num_conversions++;
        }
      } else if (info->fmt[1] == 'u' ||
                 (info->fmt[1] == 'l' && info->fmt[2] == 'u')) {
        char *endptr = NULL;
        unsigned long r = strtoul(buf, &endptr, 0 /* base */);
        if (*endptr == '\0') {
          if (info->fmt[1] == 'l') {
            *((unsigned long *) info->target) = r;
          } else {
            *((unsigned int *) info->target) = (unsigned int) r;
          }
          info->num_conversions++;
        }
      } else {
#if !JSON_MINIMAL
        info->num_conversions += sscanf(buf, info->fmt, info->target);
#endif
      }
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
          memcpy(fmtbuf, fmt + i, conv_len);
          fmtbuf[conv_len] = '\0';
          i += conv_len;
          if (fmt[i] != '}')
            i += strspn(fmt + i, delims);
          break;
        }
      }
      json_walk(s, len, json_scanf_cb, &info);
    } else if (json_isalpha(fmt[i]) || json_get_utf8_char_len(fmt[i]) > 1) {
      char *pe;
      const char *delims = ": \r\n\t";
      int key_len = strcspn(&fmt[i], delims);
      if ((p = strrchr(path, '.')) != NULL) p[1] = '\0';
      pe = path + strlen(path);
      memcpy(pe, fmt + i, key_len);
      pe[key_len] = '\0';
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

int json_vfprintf(const char *file_name, const char *fmt, va_list ap) WEAK;
int json_vfprintf(const char *file_name, const char *fmt, va_list ap) {
  int res = -1;
  FILE *fp = fopen(file_name, "wb");
  if (fp != NULL) {
    struct json_out out = JSON_OUT_FILE(fp);
    res = json_vprintf(&out, fmt, ap);
    fputc('\n', fp);
    fclose(fp);
  }
  return res;
}

int json_fprintf(const char *file_name, const char *fmt, ...) WEAK;
int json_fprintf(const char *file_name, const char *fmt, ...) {
  int result;
  va_list ap;
  va_start(ap, fmt);
  result = json_vfprintf(file_name, fmt, ap);
  va_end(ap);
  return result;
}

char *json_fread(const char *path) WEAK;
char *json_fread(const char *path) {
  FILE *fp;
  char *data = NULL;
  if ((fp = fopen(path, "rb")) == NULL) {
  } else if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
  } else {
    long size = ftell(fp);
    if (size > 0 && (data = (char *) malloc(size + 1)) != NULL) {
      fseek(fp, 0, SEEK_SET); /* Some platforms might not have rewind(), Oo */
      if (fread(data, 1, size, fp) != (size_t) size) {
        free(data);
        data = NULL;
      } else {
        data[size] = '\0';
      }
    }
    fclose(fp);
  }
  return data;
}

struct json_setf_data {
  const char *json_path;
  const char *base; /* Pointer to the source JSON string */
  int matched;      /* Matched part of json_path */
  int pos;          /* Offset of the mutated value begin */
  int end;          /* Offset of the mutated value end */
  int prev;         /* Offset of the previous token end */
};

static int get_matched_prefix_len(const char *s1, const char *s2) {
  int i = 0;
  while (s1[i] && s2[i] && s1[i] == s2[i]) i++;
  return i;
}

static void json_vsetf_cb(void *userdata, const char *name, size_t name_len,
                          const char *path, const struct json_token *t) {
  struct json_setf_data *data = (struct json_setf_data *) userdata;
  int off, len = get_matched_prefix_len(path, data->json_path);
  if (t->ptr == NULL) return;
  off = t->ptr - data->base;
  if (len > data->matched) data->matched = len;

  /*
   * If there is no exact path match, set the mutation position to tbe end
   * of the object or array
   */
  if (len < data->matched && data->pos == 0 &&
      (t->type == JSON_TYPE_OBJECT_END || t->type == JSON_TYPE_ARRAY_END)) {
    data->pos = data->end = data->prev;
  }

  /* Exact path match. Set mutation position to the value of this token */
  if (strcmp(path, data->json_path) == 0 && t->type != JSON_TYPE_OBJECT_START &&
      t->type != JSON_TYPE_ARRAY_START) {
    data->pos = off;
    data->end = off + t->len;
  }

  /*
   * For deletion, we need to know where the previous value ends, because
   * we don't know where matched value key starts.
   * When the mutation position is not yet set, remember each value end.
   * When the mutation position is already set, but it is at the beginning
   * of the object/array, we catch the end of the object/array and see
   * whether the object/array start is closer then previously stored prev.
   */
  if (data->pos == 0) {
    data->prev = off + t->len; /* pos is not yet set */
  } else if ((t->ptr[0] == '[' || t->ptr[0] == '{') && off + 1 < data->pos &&
             off + 1 > data->prev) {
    data->prev = off + 1;
  }
  (void) name;
  (void) name_len;
}

int json_vsetf(const char *s, int len, struct json_out *out,
               const char *json_path, const char *json_fmt, va_list ap) WEAK;
int json_vsetf(const char *s, int len, struct json_out *out,
               const char *json_path, const char *json_fmt, va_list ap) {
  struct json_setf_data data;
  memset(&data, 0, sizeof(data));
  data.json_path = json_path;
  data.base = s;
  data.end = len;
  json_walk(s, len, json_vsetf_cb, &data);
  if (json_fmt == NULL) {
    /* Deletion codepath */
    json_printf(out, "%.*s", data.prev, s);
    /* Trim comma after the value that begins at object/array start */
    if (s[data.prev - 1] == '{' || s[data.prev - 1] == '[') {
      int i = data.end;
      while (i < len && json_isspace(s[i])) i++;
      if (s[i] == ',') data.end = i + 1; /* Point after comma */
    }
    json_printf(out, "%.*s", len - data.end, s + data.end);
  } else {
    /* Modification codepath */
    int n, off = data.matched, depth = 0;

    /* Print the unchanged beginning */
    json_printf(out, "%.*s", data.pos, s);

    /* Add missing keys */
    while ((n = strcspn(&json_path[off], ".[")) > 0) {
      if (s[data.prev - 1] != '{' && s[data.prev - 1] != '[' && depth == 0) {
        json_printf(out, ",");
      }
      if (off > 0 && json_path[off - 1] != '.') break;
      json_printf(out, "%.*Q:", n, json_path + off);
      off += n;
      if (json_path[off] != '\0') {
        json_printf(out, "%c", json_path[off] == '.' ? '{' : '[');
        depth++;
        off++;
      }
    }
    /* Print the new value */
    json_vprintf(out, json_fmt, ap);

    /* Close brackets/braces of the added missing keys */
    for (; off > data.matched; off--) {
      int ch = json_path[off];
      const char *p = ch == '.' ? "}" : ch == '[' ? "]" : "";
      json_printf(out, "%s", p);
    }

    /* Print the rest of the unchanged string */
    json_printf(out, "%.*s", len - data.end, s + data.end);
  }
  return data.end > data.pos ? 1 : 0;
}

int json_setf(const char *s, int len, struct json_out *out,
              const char *json_path, const char *json_fmt, ...) WEAK;
int json_setf(const char *s, int len, struct json_out *out,
              const char *json_path, const char *json_fmt, ...) {
  int result;
  va_list ap;
  va_start(ap, json_fmt);
  result = json_vsetf(s, len, out, json_path, json_fmt, ap);
  va_end(ap);
  return result;
}

struct prettify_data {
  struct json_out *out;
  int level;
  int last_token;
};

static void indent(struct json_out *out, int level) {
  while (level-- > 0) out->printer(out, "  ", 2);
}

static void print_key(struct prettify_data *pd, const char *path,
                      const char *name, int name_len) {
  if (pd->last_token != JSON_TYPE_INVALID &&
      pd->last_token != JSON_TYPE_ARRAY_START &&
      pd->last_token != JSON_TYPE_OBJECT_START) {
    pd->out->printer(pd->out, ",", 1);
  }
  if (path[0] != '\0') pd->out->printer(pd->out, "\n", 1);
  indent(pd->out, pd->level);
  if (path[0] != '\0' && path[strlen(path) - 1] != ']') {
    pd->out->printer(pd->out, "\"", 1);
    pd->out->printer(pd->out, name, (int) name_len);
    pd->out->printer(pd->out, "\"", 1);
    pd->out->printer(pd->out, ": ", 2);
  }
}

static void prettify_cb(void *userdata, const char *name, size_t name_len,
                        const char *path, const struct json_token *t) {
  struct prettify_data *pd = (struct prettify_data *) userdata;
  switch (t->type) {
    case JSON_TYPE_OBJECT_START:
    case JSON_TYPE_ARRAY_START:
      print_key(pd, path, name, name_len);
      pd->out->printer(pd->out, t->type == JSON_TYPE_ARRAY_START ? "[" : "{",
                       1);
      pd->level++;
      break;
    case JSON_TYPE_OBJECT_END:
    case JSON_TYPE_ARRAY_END:
      pd->level--;
      if (pd->last_token != JSON_TYPE_INVALID &&
          pd->last_token != JSON_TYPE_ARRAY_START &&
          pd->last_token != JSON_TYPE_OBJECT_START) {
        pd->out->printer(pd->out, "\n", 1);
        indent(pd->out, pd->level);
      }
      pd->out->printer(pd->out, t->type == JSON_TYPE_ARRAY_END ? "]" : "}", 1);
      break;
    case JSON_TYPE_NUMBER:
    case JSON_TYPE_NULL:
    case JSON_TYPE_TRUE:
    case JSON_TYPE_FALSE:
    case JSON_TYPE_STRING:
      print_key(pd, path, name, name_len);
      if (t->type == JSON_TYPE_STRING) pd->out->printer(pd->out, "\"", 1);
      pd->out->printer(pd->out, t->ptr, t->len);
      if (t->type == JSON_TYPE_STRING) pd->out->printer(pd->out, "\"", 1);
      break;
    default:
      break;
  }
  pd->last_token = t->type;
}

int json_prettify(const char *s, int len, struct json_out *out) WEAK;
int json_prettify(const char *s, int len, struct json_out *out) {
  struct prettify_data pd = {out, 0, JSON_TYPE_INVALID};
  return json_walk(s, len, prettify_cb, &pd);
}

int json_prettify_file(const char *file_name) WEAK;
int json_prettify_file(const char *file_name) {
  int res = -1;
  char *s = json_fread(file_name);
  FILE *fp;
  if (s != NULL && (fp = fopen(file_name, "wb")) != NULL) {
    struct json_out out = JSON_OUT_FILE(fp);
    res = json_prettify(s, strlen(s), &out);
    if (res < 0) {
      /* On error, restore the old content */
      fclose(fp);
      fp = fopen(file_name, "wb");
      fseek(fp, 0, SEEK_SET);
      fwrite(s, 1, strlen(s), fp);
    } else {
      fputc('\n', fp);
    }
    fclose(fp);
  }
  free(s);
  return res;
}

struct next_data {
  void *handle;            // Passed handle. Changed if a next entry is found
  const char *path;        // Path to the iterated object/array
  int path_len;            // Path length - optimisation
  int found;               // Non-0 if found the next entry
  struct json_token *key;  // Object's key
  struct json_token *val;  // Object's value
  int *idx;                // Array index
};

static void next_set_key(struct next_data *d, const char *name, int name_len,
                         int is_array) {
  if (is_array) {
    /* Array. Set index and reset key  */
    if (d->key != NULL) {
      d->key->len = 0;
      d->key->ptr = NULL;
    }
    if (d->idx != NULL) *d->idx = atoi(name);
  } else {
    /* Object. Set key and make index -1 */
    if (d->key != NULL) {
      d->key->ptr = name;
      d->key->len = name_len;
    }
    if (d->idx != NULL) *d->idx = -1;
  }
}

static void json_next_cb(void *userdata, const char *name, size_t name_len,
                         const char *path, const struct json_token *t) {
  struct next_data *d = (struct next_data *) userdata;
  const char *p = path + d->path_len;
  if (d->found) return;
  if (d->path_len >= (int) strlen(path)) return;
  if (strncmp(d->path, path, d->path_len) != 0) return;
  if (strchr(p + 1, '.') != NULL) return; /* More nested objects - skip */
  if (strchr(p + 1, '[') != NULL) return; /* Ditto for arrays */
  // {OBJECT,ARRAY}_END types do not pass name, _START does. Save key.
  if (t->type == JSON_TYPE_OBJECT_START || t->type == JSON_TYPE_ARRAY_START) {
    next_set_key(d, name, name_len, p[0] == '[');
  } else if (d->handle == NULL || d->handle < (void *) t->ptr) {
    if (t->type != JSON_TYPE_OBJECT_END && t->type != JSON_TYPE_ARRAY_END) {
      next_set_key(d, name, name_len, p[0] == '[');
    }
    if (d->val != NULL) *d->val = *t;
    d->handle = (void *) t->ptr;
    d->found = 1;
  }
}

static void *json_next(const char *s, int len, void *handle, const char *path,
                       struct json_token *key, struct json_token *val, int *i) {
  struct json_token tmpval, *v = val == NULL ? &tmpval : val;
  struct json_token tmpkey, *k = key == NULL ? &tmpkey : key;
  int tmpidx, *pidx = i == NULL ? &tmpidx : i;
  struct next_data data = {handle, path, (int) strlen(path), 0, k, v, pidx};
  json_walk(s, len, json_next_cb, &data);
  return data.found ? data.handle : NULL;
}

void *json_next_key(const char *s, int len, void *handle, const char *path,
                    struct json_token *key, struct json_token *val) WEAK;
void *json_next_key(const char *s, int len, void *handle, const char *path,
                    struct json_token *key, struct json_token *val) {
  return json_next(s, len, handle, path, key, val, NULL);
}

void *json_next_elem(const char *s, int len, void *handle, const char *path,
                     int *idx, struct json_token *val) WEAK;
void *json_next_elem(const char *s, int len, void *handle, const char *path,
                     int *idx, struct json_token *val) {
  return json_next(s, len, handle, path, NULL, val, idx);
}

static int json_sprinter(struct json_out *out, const char *str, size_t len) {
  size_t old_len = out->u.buf.buf == NULL ? 0 : strlen(out->u.buf.buf);
  size_t new_len = len + old_len;
  char *p = (char *) realloc(out->u.buf.buf, new_len + 1);
  if (p != NULL) {
    memcpy(p + old_len, str, len);
    p[new_len] = '\0';
    out->u.buf.buf = p;
  }
  return len;
}

char *json_vasprintf(const char *fmt, va_list ap) WEAK;
char *json_vasprintf(const char *fmt, va_list ap) {
  struct json_out out;
  memset(&out, 0, sizeof(out));
  out.printer = json_sprinter;
  json_vprintf(&out, fmt, ap);
  return out.u.buf.buf;
}

char *json_asprintf(const char *fmt, ...) WEAK;
char *json_asprintf(const char *fmt, ...) {
  char *result = NULL;
  va_list ap;
  va_start(ap, fmt);
  result = json_vasprintf(fmt, ap);
  va_end(ap);
  return result;
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/ffi/ffi.c"
#endif

/* Amalgamated: #include "mjs/src/ffi/ffi.h" */

#define IS_W(arg) ((arg).ctype == FFI_CTYPE_WORD)
#define IS_D(arg) ((arg).ctype == FFI_CTYPE_DOUBLE)
#define IS_F(arg) ((arg).ctype == FFI_CTYPE_FLOAT)

#define W(arg) ((ffi_word_t)(arg).v.i)
#define D(arg) ((arg).v.d)
#define F(arg) ((arg).v.f)

void ffi_set_word(struct ffi_arg *arg, ffi_word_t v) {
  arg->ctype = FFI_CTYPE_WORD;
  arg->v.i = v;
}

void ffi_set_bool(struct ffi_arg *arg, bool v) {
  arg->ctype = FFI_CTYPE_BOOL;
  arg->v.i = v;
}

void ffi_set_ptr(struct ffi_arg *arg, void *v) {
  ffi_set_word(arg, (ffi_word_t) v);
}

void ffi_set_double(struct ffi_arg *arg, double v) {
  arg->ctype = FFI_CTYPE_DOUBLE;
  arg->v.d = v;
}

void ffi_set_float(struct ffi_arg *arg, float v) {
  arg->ctype = FFI_CTYPE_FLOAT;
  arg->v.f = v;
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

typedef ffi_word_t (*w4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef ffi_word_t (*w5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                            ffi_word_t);
typedef ffi_word_t (*w6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                            ffi_word_t, ffi_word_t);

typedef ffi_word_t (*wdw_t)(double, ffi_word_t);
typedef ffi_word_t (*wwd_t)(ffi_word_t, double);
typedef ffi_word_t (*wdd_t)(double, double);

typedef ffi_word_t (*wwwd_t)(ffi_word_t, ffi_word_t, double);
typedef ffi_word_t (*wwdw_t)(ffi_word_t, double, ffi_word_t);
typedef ffi_word_t (*wwdd_t)(ffi_word_t, double, double);
typedef ffi_word_t (*wdww_t)(double, ffi_word_t, ffi_word_t);
typedef ffi_word_t (*wdwd_t)(double, ffi_word_t, double);
typedef ffi_word_t (*wddw_t)(double, double, ffi_word_t);
typedef ffi_word_t (*wddd_t)(double, double, double);

typedef ffi_word_t (*wfw_t)(float, ffi_word_t);
typedef ffi_word_t (*wwf_t)(ffi_word_t, float);
typedef ffi_word_t (*wff_t)(float, float);

typedef ffi_word_t (*wwwf_t)(ffi_word_t, ffi_word_t, float);
typedef ffi_word_t (*wwfw_t)(ffi_word_t, float, ffi_word_t);
typedef ffi_word_t (*wwff_t)(ffi_word_t, float, float);
typedef ffi_word_t (*wfww_t)(float, ffi_word_t, ffi_word_t);
typedef ffi_word_t (*wfwf_t)(float, ffi_word_t, float);
typedef ffi_word_t (*wffw_t)(float, float, ffi_word_t);
typedef ffi_word_t (*wfff_t)(float, float, float);

typedef bool (*b4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef bool (*b5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                      ffi_word_t);
typedef bool (*b6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                      ffi_word_t, ffi_word_t);
typedef bool (*bdw_t)(double, ffi_word_t);
typedef bool (*bwd_t)(ffi_word_t, double);
typedef bool (*bdd_t)(double, double);

typedef bool (*bwwd_t)(ffi_word_t, ffi_word_t, double);
typedef bool (*bwdw_t)(ffi_word_t, double, ffi_word_t);
typedef bool (*bwdd_t)(ffi_word_t, double, double);
typedef bool (*bdww_t)(double, ffi_word_t, ffi_word_t);
typedef bool (*bdwd_t)(double, ffi_word_t, double);
typedef bool (*bddw_t)(double, double, ffi_word_t);
typedef bool (*bddd_t)(double, double, double);

typedef bool (*bfw_t)(float, ffi_word_t);
typedef bool (*bwf_t)(ffi_word_t, float);
typedef bool (*bff_t)(float, float);

typedef bool (*bwwf_t)(ffi_word_t, ffi_word_t, float);
typedef bool (*bwfw_t)(ffi_word_t, float, ffi_word_t);
typedef bool (*bwff_t)(ffi_word_t, float, float);
typedef bool (*bfww_t)(float, ffi_word_t, ffi_word_t);
typedef bool (*bfwf_t)(float, ffi_word_t, float);
typedef bool (*bffw_t)(float, float, ffi_word_t);
typedef bool (*bfff_t)(float, float, float);

typedef double (*d4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef double (*d5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                        ffi_word_t);
typedef double (*d6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                        ffi_word_t, ffi_word_t);
typedef double (*ddw_t)(double, ffi_word_t);
typedef double (*dwd_t)(ffi_word_t, double);
typedef double (*ddd_t)(double, double);

typedef double (*dwwd_t)(ffi_word_t, ffi_word_t, double);
typedef double (*dwdw_t)(ffi_word_t, double, ffi_word_t);
typedef double (*dwdd_t)(ffi_word_t, double, double);
typedef double (*ddww_t)(double, ffi_word_t, ffi_word_t);
typedef double (*ddwd_t)(double, ffi_word_t, double);
typedef double (*dddw_t)(double, double, ffi_word_t);
typedef double (*dddd_t)(double, double, double);

typedef float (*f4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef float (*f5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                       ffi_word_t);
typedef float (*f6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                       ffi_word_t, ffi_word_t);
typedef float (*ffw_t)(float, ffi_word_t);
typedef float (*fwf_t)(ffi_word_t, float);
typedef float (*fff_t)(float, float);

typedef float (*fwwf_t)(ffi_word_t, ffi_word_t, float);
typedef float (*fwfw_t)(ffi_word_t, float, ffi_word_t);
typedef float (*fwff_t)(ffi_word_t, float, float);
typedef float (*ffww_t)(float, ffi_word_t, ffi_word_t);
typedef float (*ffwf_t)(float, ffi_word_t, float);
typedef float (*fffw_t)(float, float, ffi_word_t);
typedef float (*ffff_t)(float, float, float);

int ffi_call(ffi_fn_t *func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args) {
  int i, doubles = 0, floats = 0;

  if (nargs > 6) return -1;
  for (i = 0; i < nargs; i++) {
    doubles += (IS_D(args[i]));
    floats += (IS_F(args[i]));
  }

  /* Doubles and floats are not supported together atm */
  if (doubles > 0 && floats > 0) {
    return -1;
  }

  switch (res->ctype) {
    case FFI_CTYPE_WORD: { /* {{{ */
      ffi_word_t r;
      if (doubles == 0) {
        if (floats == 0) {
          /*
           * No double and no float args: we currently support up to 6
           * word-sized arguments
           */
          if (nargs <= 4) {
            w4w_t f = (w4w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
          } else if (nargs == 5) {
            w5w_t f = (w5w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
          } else if (nargs == 6) {
            w6w_t f = (w6w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                  W(args[5]));
          } else {
            abort();
          }
        } else {
          /* There are some floats */
          switch (nargs) {
            case 0:
            case 1:
            case 2:
              if (IS_F(args[0]) && IS_F(args[1])) {
                wff_t f = (wff_t) func;
                r = f(F(args[0]), F(args[1]));
              } else if (IS_F(args[0])) {
                wfw_t f = (wfw_t) func;
                r = f(F(args[0]), W(args[1]));
              } else {
                wwf_t f = (wwf_t) func;
                r = f(W(args[0]), F(args[1]));
              }
              break;

            case 3:
              if (IS_W(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
                wwwf_t f = (wwwf_t) func;
                r = f(W(args[0]), W(args[1]), F(args[2]));
              } else if (IS_W(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
                wwfw_t f = (wwfw_t) func;
                r = f(W(args[0]), F(args[1]), W(args[2]));
              } else if (IS_W(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
                wwff_t f = (wwff_t) func;
                r = f(W(args[0]), F(args[1]), F(args[2]));
              } else if (IS_F(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
                wfww_t f = (wfww_t) func;
                r = f(F(args[0]), W(args[1]), W(args[2]));
              } else if (IS_F(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
                wfwf_t f = (wfwf_t) func;
                r = f(F(args[0]), W(args[1]), F(args[2]));
              } else if (IS_F(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
                wffw_t f = (wffw_t) func;
                r = f(F(args[0]), F(args[1]), W(args[2]));
              } else if (IS_F(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
                wfff_t f = (wfff_t) func;
                r = f(F(args[0]), F(args[1]), F(args[2]));
              } else {
                // The above checks should be exhaustive
                abort();
              }
              break;
            default:
              return -1;
          }
        }
      } else {
        /* There are some doubles */
        switch (nargs) {
          case 0:
          case 1:
          case 2:
            if (IS_D(args[0]) && IS_D(args[1])) {
              wdd_t f = (wdd_t) func;
              r = f(D(args[0]), D(args[1]));
            } else if (IS_D(args[0])) {
              wdw_t f = (wdw_t) func;
              r = f(D(args[0]), W(args[1]));
            } else {
              wwd_t f = (wwd_t) func;
              r = f(W(args[0]), D(args[1]));
            }
            break;

          case 3:
            if (IS_W(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              wwwd_t f = (wwwd_t) func;
              r = f(W(args[0]), W(args[1]), D(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              wwdw_t f = (wwdw_t) func;
              r = f(W(args[0]), D(args[1]), W(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              wwdd_t f = (wwdd_t) func;
              r = f(W(args[0]), D(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
              wdww_t f = (wdww_t) func;
              r = f(D(args[0]), W(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              wdwd_t f = (wdwd_t) func;
              r = f(D(args[0]), W(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              wddw_t f = (wddw_t) func;
              r = f(D(args[0]), D(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              wddd_t f = (wddd_t) func;
              r = f(D(args[0]), D(args[1]), D(args[2]));
            } else {
              // The above checks should be exhaustive
              abort();
            }
            break;
          default:
            return -1;
        }
      }
      res->v.i = (uint64_t) r;
    } break;               /* }}} */
    case FFI_CTYPE_BOOL: { /* {{{ */
      ffi_word_t r;
      if (doubles == 0) {
        if (floats == 0) {
          /*
           * No double and no float args: we currently support up to 6
           * word-sized arguments
           */
          if (nargs <= 4) {
            b4w_t f = (b4w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
          } else if (nargs == 5) {
            b5w_t f = (b5w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
          } else if (nargs == 6) {
            b6w_t f = (b6w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                  W(args[5]));
          } else {
            abort();
          }
        } else {
          /* There are some floats */
          switch (nargs) {
            case 0:
            case 1:
            case 2:
              if (IS_F(args[0]) && IS_F(args[1])) {
                bff_t f = (bff_t) func;
                r = f(F(args[0]), F(args[1]));
              } else if (IS_F(args[0])) {
                bfw_t f = (bfw_t) func;
                r = f(F(args[0]), W(args[1]));
              } else {
                bwf_t f = (bwf_t) func;
                r = f(W(args[0]), F(args[1]));
              }
              break;

            case 3:
              if (IS_W(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
                bwwf_t f = (bwwf_t) func;
                r = f(W(args[0]), W(args[1]), F(args[2]));
              } else if (IS_W(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
                bwfw_t f = (bwfw_t) func;
                r = f(W(args[0]), F(args[1]), W(args[2]));
              } else if (IS_W(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
                bwff_t f = (bwff_t) func;
                r = f(W(args[0]), F(args[1]), F(args[2]));
              } else if (IS_F(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
                bfww_t f = (bfww_t) func;
                r = f(F(args[0]), W(args[1]), W(args[2]));
              } else if (IS_F(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
                bfwf_t f = (bfwf_t) func;
                r = f(F(args[0]), W(args[1]), F(args[2]));
              } else if (IS_F(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
                bffw_t f = (bffw_t) func;
                r = f(F(args[0]), F(args[1]), W(args[2]));
              } else if (IS_F(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
                bfff_t f = (bfff_t) func;
                r = f(F(args[0]), F(args[1]), F(args[2]));
              } else {
                // The above checks should be exhaustive
                abort();
              }
              break;
            default:
              return -1;
          }
        }
      } else {
        /* There are some doubles */
        switch (nargs) {
          case 0:
          case 1:
          case 2:
            if (IS_D(args[0]) && IS_D(args[1])) {
              bdd_t f = (bdd_t) func;
              r = f(D(args[0]), D(args[1]));
            } else if (IS_D(args[0])) {
              bdw_t f = (bdw_t) func;
              r = f(D(args[0]), W(args[1]));
            } else {
              bwd_t f = (bwd_t) func;
              r = f(W(args[0]), D(args[1]));
            }
            break;

          case 3:
            if (IS_W(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              bwwd_t f = (bwwd_t) func;
              r = f(W(args[0]), W(args[1]), D(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              bwdw_t f = (bwdw_t) func;
              r = f(W(args[0]), D(args[1]), W(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              bwdd_t f = (bwdd_t) func;
              r = f(W(args[0]), D(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
              bdww_t f = (bdww_t) func;
              r = f(D(args[0]), W(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              bdwd_t f = (bdwd_t) func;
              r = f(D(args[0]), W(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              bddw_t f = (bddw_t) func;
              r = f(D(args[0]), D(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              bddd_t f = (bddd_t) func;
              r = f(D(args[0]), D(args[1]), D(args[2]));
            } else {
              // The above checks should be exhaustive
              abort();
            }
            break;
          default:
            return -1;
        }
      }
      res->v.i = (uint64_t) r;
    } break;                 /* }}} */
    case FFI_CTYPE_DOUBLE: { /* {{{ */
      double r;
      if (doubles == 0) {
        /* No double args: we currently support up to 6 word-sized arguments
         */
        if (nargs <= 4) {
          d4w_t f = (d4w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
        } else if (nargs == 5) {
          d5w_t f = (d5w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
        } else if (nargs == 6) {
          d6w_t f = (d6w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                W(args[5]));
        } else {
          abort();
        }
      } else {
        switch (nargs) {
          case 0:
          case 1:
          case 2:
            if (IS_D(args[0]) && IS_D(args[1])) {
              ddd_t f = (ddd_t) func;
              r = f(D(args[0]), D(args[1]));
            } else if (IS_D(args[0])) {
              ddw_t f = (ddw_t) func;
              r = f(D(args[0]), W(args[1]));
            } else {
              dwd_t f = (dwd_t) func;
              r = f(W(args[0]), D(args[1]));
            }
            break;

          case 3:
            if (IS_W(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              dwwd_t f = (dwwd_t) func;
              r = f(W(args[0]), W(args[1]), D(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              dwdw_t f = (dwdw_t) func;
              r = f(W(args[0]), D(args[1]), W(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              dwdd_t f = (dwdd_t) func;
              r = f(W(args[0]), D(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
              ddww_t f = (ddww_t) func;
              r = f(D(args[0]), W(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              ddwd_t f = (ddwd_t) func;
              r = f(D(args[0]), W(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              dddw_t f = (dddw_t) func;
              r = f(D(args[0]), D(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              dddd_t f = (dddd_t) func;
              r = f(D(args[0]), D(args[1]), D(args[2]));
            } else {
              // The above checks should be exhaustive
              abort();
            }
            break;
          default:
            return -1;
        }
      }
      res->v.d = r;
    } break;                /* }}} */
    case FFI_CTYPE_FLOAT: { /* {{{ */
      double r;
      if (floats == 0) {
        /* No float args: we currently support up to 6 word-sized arguments
         */
        if (nargs <= 4) {
          f4w_t f = (f4w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
        } else if (nargs == 5) {
          f5w_t f = (f5w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
        } else if (nargs == 6) {
          f6w_t f = (f6w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                W(args[5]));
        } else {
          abort();
        }
      } else {
        /* There are some float args */
        switch (nargs) {
          case 0:
          case 1:
          case 2:
            if (IS_F(args[0]) && IS_F(args[1])) {
              fff_t f = (fff_t) func;
              r = f(F(args[0]), F(args[1]));
            } else if (IS_F(args[0])) {
              ffw_t f = (ffw_t) func;
              r = f(F(args[0]), W(args[1]));
            } else {
              fwf_t f = (fwf_t) func;
              r = f(W(args[0]), F(args[1]));
            }
            break;

          case 3:
            if (IS_W(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
              fwwf_t f = (fwwf_t) func;
              r = f(W(args[0]), W(args[1]), F(args[2]));
            } else if (IS_W(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
              fwfw_t f = (fwfw_t) func;
              r = f(W(args[0]), F(args[1]), W(args[2]));
            } else if (IS_W(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
              fwff_t f = (fwff_t) func;
              r = f(W(args[0]), F(args[1]), F(args[2]));
            } else if (IS_F(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
              ffww_t f = (ffww_t) func;
              r = f(F(args[0]), W(args[1]), W(args[2]));
            } else if (IS_F(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
              ffwf_t f = (ffwf_t) func;
              r = f(F(args[0]), W(args[1]), F(args[2]));
            } else if (IS_F(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
              fffw_t f = (fffw_t) func;
              r = f(F(args[0]), F(args[1]), W(args[2]));
            } else if (IS_F(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
              ffff_t f = (ffff_t) func;
              r = f(F(args[0]), F(args[1]), F(args[2]));
            } else {
              // The above checks should be exhaustive
              abort();
            }
            break;
          default:
            return -1;
        }
      }
      res->v.f = r;
    } break; /* }}} */
  }

  return 0;
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_array.c"
#endif

#include <stdio.h>
/* Amalgamated: #include "common/str_util.h" */
/* Amalgamated: #include "mjs/src/mjs_array.h" */
/* Amalgamated: #include "mjs/src/mjs_conversion.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

#define SPLICE_NEW_ITEM_IDX 2

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
  /* change the tag to MJS_TAG_ARRAY */
  ret &= ~MJS_TAG_MASK;
  ret |= MJS_TAG_ARRAY;
  return ret;
}

int mjs_is_array(mjs_val_t v) {
  return (v & MJS_TAG_MASK) == MJS_TAG_ARRAY;
}

mjs_val_t mjs_array_get(struct mjs *mjs, mjs_val_t arr, unsigned long index) {
  return mjs_array_get2(mjs, arr, index, NULL);
}

mjs_val_t mjs_array_get2(struct mjs *mjs, mjs_val_t arr, unsigned long index,
                         int *has) {
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
    if (ok && n >= len && n < 0xffffffff) {
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

void mjs_array_del(struct mjs *mjs, mjs_val_t arr, unsigned long index) {
  char buf[20];
  int n = v_sprintf_s(buf, sizeof(buf), "%lu", index);
  mjs_del(mjs, arr, buf, n);
}

mjs_err_t mjs_array_push(struct mjs *mjs, mjs_val_t arr, mjs_val_t v) {
  return mjs_array_set(mjs, arr, mjs_array_length(mjs, arr), v);
}

MJS_PRIVATE void mjs_array_push_internal(struct mjs *mjs) {
  mjs_err_t rcode = MJS_OK;
  mjs_val_t ret = MJS_UNDEFINED;
  int nargs = mjs_nargs(mjs);
  int i;

  /* Make sure that `this` is an array */
  if (!mjs_check_arg(mjs, -1 /*this*/, "this", MJS_TYPE_OBJECT_ARRAY, NULL)) {
    goto clean;
  }

  /* Push all args */
  for (i = 0; i < nargs; i++) {
    rcode = mjs_array_push(mjs, mjs->vals.this_obj, mjs_arg(mjs, i));
    if (rcode != MJS_OK) {
      mjs_prepend_errorf(mjs, rcode, "");
      goto clean;
    }
  }

  /* Return the new array length */
  ret = mjs_mk_number(mjs, mjs_array_length(mjs, mjs->vals.this_obj));

clean:
  mjs_return(mjs, ret);
  return;
}

static void move_item(struct mjs *mjs, mjs_val_t arr, unsigned long from,
                      unsigned long to) {
  mjs_val_t cur = mjs_array_get(mjs, arr, from);
  mjs_array_set(mjs, arr, to, cur);
  mjs_array_del(mjs, arr, from);
}

MJS_PRIVATE void mjs_array_splice(struct mjs *mjs) {
  int nargs = mjs_nargs(mjs);
  mjs_err_t rcode = MJS_OK;
  mjs_val_t ret = mjs_mk_array(mjs);
  mjs_val_t start_v = MJS_UNDEFINED;
  mjs_val_t deleteCount_v = MJS_UNDEFINED;
  int start = 0;
  int arr_len;
  int delete_cnt = 0;
  int new_items_cnt = 0;
  int delta = 0;
  int i;

  /* Make sure that `this` is an array */
  if (!mjs_check_arg(mjs, -1 /*this*/, "this", MJS_TYPE_OBJECT_ARRAY, NULL)) {
    goto clean;
  }

  /* Get array length */
  arr_len = mjs_array_length(mjs, mjs->vals.this_obj);

  /* get start from arg 0 */
  if (!mjs_check_arg(mjs, 0, "start", MJS_TYPE_NUMBER, &start_v)) {
    goto clean;
  }
  start = mjs_normalize_idx(mjs_get_int(mjs, start_v), arr_len);

  /* Handle deleteCount */
  if (nargs >= SPLICE_NEW_ITEM_IDX) {
    /* deleteCount is given; use it */
    if (!mjs_check_arg(mjs, 1, "deleteCount", MJS_TYPE_NUMBER,
                       &deleteCount_v)) {
      goto clean;
    }
    delete_cnt = mjs_get_int(mjs, deleteCount_v);
    new_items_cnt = nargs - SPLICE_NEW_ITEM_IDX;
  } else {
    /* deleteCount is not given; assume the end of the array */
    delete_cnt = arr_len - start;
  }
  if (delete_cnt > arr_len - start) {
    delete_cnt = arr_len - start;
  } else if (delete_cnt < 0) {
    delete_cnt = 0;
  }

  /* delta at which subsequent array items should be moved */
  delta = new_items_cnt - delete_cnt;

  /*
   * copy items which are going to be deleted to the separate array (will be
   * returned)
   */
  for (i = 0; i < delete_cnt; i++) {
    mjs_val_t cur = mjs_array_get(mjs, mjs->vals.this_obj, start + i);
    rcode = mjs_array_push(mjs, ret, cur);
    if (rcode != MJS_OK) {
      mjs_prepend_errorf(mjs, rcode, "");
      goto clean;
    }
  }

  /* If needed, move subsequent items */
  if (delta < 0) {
    for (i = start; i < arr_len; i++) {
      if (i >= start - delta) {
        move_item(mjs, mjs->vals.this_obj, i, i + delta);
      } else {
        mjs_array_del(mjs, mjs->vals.this_obj, i);
      }
    }
  } else if (delta > 0) {
    for (i = arr_len - 1; i >= start; i--) {
      move_item(mjs, mjs->vals.this_obj, i, i + delta);
    }
  }

  /* Set new items to the array */
  for (i = 0; i < nargs - SPLICE_NEW_ITEM_IDX; i++) {
    mjs_array_set(mjs, mjs->vals.this_obj, start + i,
                  mjs_arg(mjs, SPLICE_NEW_ITEM_IDX + i));
  }

clean:
  mjs_return(mjs, ret);
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_bcode.c"
#endif

/* Amalgamated: #include "common/cs_varint.h" */

/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_bcode.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_tok.h" */

static void add_lineno_map_item(struct pstate *pstate) {
  if (pstate->last_emitted_line_no < pstate->line_no) {
    int offset = pstate->cur_idx - pstate->start_bcode_idx;
    size_t offset_llen = cs_varint_llen(offset);
    size_t lineno_llen = cs_varint_llen(pstate->line_no);
    mbuf_resize(&pstate->offset_lineno_map,
                pstate->offset_lineno_map.size + offset_llen + lineno_llen);

    /* put offset */
    cs_varint_encode(offset, (uint8_t *) pstate->offset_lineno_map.buf +
                                 pstate->offset_lineno_map.len,
                     offset_llen);
    pstate->offset_lineno_map.len += offset_llen;

    /* put line_no */
    cs_varint_encode(pstate->line_no,
                     (uint8_t *) pstate->offset_lineno_map.buf +
                         pstate->offset_lineno_map.len,
                     lineno_llen);
    pstate->offset_lineno_map.len += lineno_llen;

    pstate->last_emitted_line_no = pstate->line_no;
  }
}

MJS_PRIVATE void emit_byte(struct pstate *pstate, uint8_t byte) {
  add_lineno_map_item(pstate);
  mbuf_insert(&pstate->mjs->bcode_gen, pstate->cur_idx, &byte, sizeof(byte));
  pstate->cur_idx += sizeof(byte);
}

MJS_PRIVATE void emit_int(struct pstate *pstate, int64_t n) {
  struct mbuf *b = &pstate->mjs->bcode_gen;
  size_t llen = cs_varint_llen(n);
  add_lineno_map_item(pstate);
  mbuf_insert(b, pstate->cur_idx, NULL, llen);
  cs_varint_encode(n, (uint8_t *) b->buf + pstate->cur_idx, llen);
  pstate->cur_idx += llen;
}

MJS_PRIVATE void emit_str(struct pstate *pstate, const char *ptr, size_t len) {
  struct mbuf *b = &pstate->mjs->bcode_gen;
  size_t llen = cs_varint_llen(len);
  add_lineno_map_item(pstate);
  mbuf_insert(b, pstate->cur_idx, NULL, llen + len);
  cs_varint_encode(len, (uint8_t *) b->buf + pstate->cur_idx, llen);
  memcpy(b->buf + pstate->cur_idx + llen, ptr, len);
  pstate->cur_idx += llen + len;
}

MJS_PRIVATE int mjs_bcode_insert_offset(struct pstate *p, struct mjs *mjs,
                                        size_t offset, size_t v) {
  int llen = (int) cs_varint_llen(v);
  int diff = llen - MJS_INIT_OFFSET_SIZE;
  assert(offset < mjs->bcode_gen.len);
  if (diff > 0) {
    mbuf_resize(&mjs->bcode_gen, mjs->bcode_gen.size + diff);
  }
  /*
   * Offset is going to take more than one was reserved, so, move the data
   * forward
   */
  memmove(mjs->bcode_gen.buf + offset + llen,
          mjs->bcode_gen.buf + offset + MJS_INIT_OFFSET_SIZE,
          mjs->bcode_gen.len - offset - MJS_INIT_OFFSET_SIZE);
  mjs->bcode_gen.len += diff;
  cs_varint_encode(v, (uint8_t *) mjs->bcode_gen.buf + offset, llen);

  /*
   * If current parsing index is after the offset at which we've inserted new
   * varint, the index might need to be adjusted
   */
  if (p->cur_idx >= (int) offset) {
    p->cur_idx += diff;
  }
  return diff;
}

MJS_PRIVATE void mjs_bcode_part_add(struct mjs *mjs,
                                    const struct mjs_bcode_part *bp) {
  mbuf_append(&mjs->bcode_parts, bp, sizeof(*bp));
}

MJS_PRIVATE struct mjs_bcode_part *mjs_bcode_part_get(struct mjs *mjs,
                                                      int num) {
  assert(num < mjs_bcode_parts_cnt(mjs));
  return (struct mjs_bcode_part *) (mjs->bcode_parts.buf +
                                    num * sizeof(struct mjs_bcode_part));
}

MJS_PRIVATE struct mjs_bcode_part *mjs_bcode_part_get_by_offset(struct mjs *mjs,
                                                                size_t offset) {
  int i;
  int parts_cnt = mjs_bcode_parts_cnt(mjs);
  struct mjs_bcode_part *bp = NULL;

  if (offset >= mjs->bcode_len) {
    return NULL;
  }

  for (i = 0; i < parts_cnt; i++) {
    bp = mjs_bcode_part_get(mjs, i);
    if (offset < bp->start_idx + bp->data.len) {
      break;
    }
  }

  /* given the non-corrupted data, the needed part must be found */
  assert(i < parts_cnt);

  return bp;
}

MJS_PRIVATE int mjs_bcode_parts_cnt(struct mjs *mjs) {
  return mjs->bcode_parts.len / sizeof(struct mjs_bcode_part);
}

MJS_PRIVATE void mjs_bcode_commit(struct mjs *mjs) {
  struct mjs_bcode_part bp;
  memset(&bp, 0, sizeof(bp));

  /* Make sure the bcode doesn't occupy any extra space */
  mbuf_trim(&mjs->bcode_gen);

  /* Transfer the ownership of the bcode data */
  bp.data.p = mjs->bcode_gen.buf;
  bp.data.len = mjs->bcode_gen.len;
  mbuf_init(&mjs->bcode_gen, 0);

  bp.start_idx = mjs->bcode_len;
  bp.exec_res = MJS_ERRS_CNT;

  mjs_bcode_part_add(mjs, &bp);

  mjs->bcode_len += bp.data.len;
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_builtin.c"
#endif

/* Amalgamated: #include "mjs/src/mjs_bcode.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_dataview.h" */
/* Amalgamated: #include "mjs/src/mjs_exec.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_json.h" */
/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

static void mjs_print(struct mjs *mjs) {
  size_t i, num_args = mjs_nargs(mjs);
  for (i = 0; i < num_args; i++) {
    mjs_fprintf(mjs_arg(mjs, i), mjs, stdout);
    putchar(' ');
  }
  putchar('\n');
  mjs_return(mjs, MJS_UNDEFINED);
}

/*
 * If the file with the given filename was already loaded, returns the
 * corresponding bcode part; otherwise returns NULL.
 */
static struct mjs_bcode_part *mjs_get_loaded_file_bcode(struct mjs *mjs,
                                                        const char *filename) {
  int parts_cnt = mjs_bcode_parts_cnt(mjs);
  int i;

  if (filename == NULL) {
    return 0;
  }

  for (i = 0; i < parts_cnt; i++) {
    struct mjs_bcode_part *bp = mjs_bcode_part_get(mjs, i);
    const char *cur_fn = mjs_get_bcode_filename(mjs, bp);
    if (strcmp(filename, cur_fn) == 0) {
      return bp;
    }
  }
  return NULL;
}

static void mjs_load(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_val_t arg0 = mjs_arg(mjs, 0);
  mjs_val_t arg1 = mjs_arg(mjs, 1);
  int custom_global = 0; /* whether the custom global object was provided */

  if (mjs_is_string(arg0)) {
    const char *path = mjs_get_cstring(mjs, &arg0);
    struct mjs_bcode_part *bp = NULL;
    mjs_err_t ret;

    if (mjs_is_object(arg1)) {
      custom_global = 1;
      push_mjs_val(&mjs->scopes, arg1);
    }
    bp = mjs_get_loaded_file_bcode(mjs, path);
    if (bp == NULL) {
      /* File was not loaded before, so, load */
      ret = mjs_exec_file(mjs, path, &res);
    } else {
      /*
       * File was already loaded before, so if it was evaluated successfully,
       * then skip the evaluation at all (and assume MJS_OK); otherwise
       * re-evaluate it again.
       *
       * However, if the custom global object was provided, then reevaluate
       * the file in any case.
       */
      if (bp->exec_res != MJS_OK || custom_global) {
        ret = mjs_execute(mjs, bp->start_idx, &res);
      } else {
        ret = MJS_OK;
      }
    }
    if (ret != MJS_OK) {
      /*
       * arg0 and path might be invalidated by executing a file, so refresh
       * them
       */
      arg0 = mjs_arg(mjs, 0);
      path = mjs_get_cstring(mjs, &arg0);
      mjs_prepend_errorf(mjs, ret, "failed to exec file \"%s\"", path);
      goto clean;
    }

  clean:
    if (custom_global) {
      mjs_pop_val(&mjs->scopes);
    }
  }
  mjs_return(mjs, res);
}

static void mjs_get_mjs(struct mjs *mjs) {
  mjs_return(mjs, mjs_mk_foreign(mjs, mjs));
}

static void mjs_chr(struct mjs *mjs) {
  mjs_val_t arg0 = mjs_arg(mjs, 0), res = MJS_NULL;
  int n = mjs_get_int(mjs, arg0);
  if (mjs_is_number(arg0) && n >= 0 && n <= 255) {
    uint8_t s = n;
    res = mjs_mk_string(mjs, (const char *) &s, sizeof(s), 1);
  }
  mjs_return(mjs, res);
}

static void mjs_do_gc(struct mjs *mjs) {
  mjs_val_t arg0 = mjs_arg(mjs, 0);
  mjs_gc(mjs, mjs_is_boolean(arg0) ? mjs_get_bool(mjs, arg0) : 0);
  mjs_return(mjs, arg0);
}

static void mjs_s2o(struct mjs *mjs) {
  mjs_return(mjs,
             mjs_struct_to_obj(mjs, mjs_get_ptr(mjs, mjs_arg(mjs, 0)),
                               (const struct mjs_c_struct_member *) mjs_get_ptr(
                                   mjs, mjs_arg(mjs, 1))));
}

void mjs_init_builtin(struct mjs *mjs, mjs_val_t obj) {
  mjs_val_t v;

  mjs_set(mjs, obj, "global", ~0, obj);

  mjs_set(mjs, obj, "load", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_load));
  mjs_set(mjs, obj, "print", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_print));
  mjs_set(mjs, obj, "ffi", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_ffi_call));
  mjs_set(mjs, obj, "ffi_cb_free", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_ffi_cb_free));
  mjs_set(mjs, obj, "mkstr", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_mkstr));
  mjs_set(mjs, obj, "getMJS", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_get_mjs));
  mjs_set(mjs, obj, "die", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_die));
  mjs_set(mjs, obj, "gc", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_do_gc));
  mjs_set(mjs, obj, "chr", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_chr));
  mjs_set(mjs, obj, "s2o", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_s2o));

  /*
   * Populate JSON.parse() and JSON.stringify()
   */
  v = mjs_mk_object(mjs);
  mjs_set(mjs, v, "stringify", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_op_json_stringify));
  mjs_set(mjs, v, "parse", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_op_json_parse));
  mjs_set(mjs, obj, "JSON", ~0, v);

  /*
   * Populate Object.create()
   */
  v = mjs_mk_object(mjs);
  mjs_set(mjs, v, "create", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_op_create_object));
  mjs_set(mjs, obj, "Object", ~0, v);

  /*
   * Populate numeric stuff
   */
  mjs_set(mjs, obj, "NaN", ~0, MJS_TAG_NAN);
  mjs_set(mjs, obj, "isNaN", ~0,
          mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_op_isnan));
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_conversion.c"
#endif

/* Amalgamated: #include "mjs/src/mjs_conversion.h" */
/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

MJS_PRIVATE mjs_err_t mjs_to_string(struct mjs *mjs, mjs_val_t *v, char **p,
                                    size_t *sizep, int *need_free) {
  mjs_err_t ret = MJS_OK;

  *p = NULL;
  *sizep = 0;
  *need_free = 0;

  if (mjs_is_string(*v)) {
    *p = (char *) mjs_get_string(mjs, v, sizep);
  } else if (mjs_is_number(*v)) {
    char buf[50] = "";
    struct json_out out = JSON_OUT_BUF(buf, sizeof(buf));
    mjs_jprintf(*v, mjs, &out);
    *sizep = strlen(buf);
    *p = malloc(*sizep + 1);
    if (*p == NULL) {
      ret = MJS_OUT_OF_MEMORY;
      goto clean;
    }
    memmove(*p, buf, *sizep + 1);
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
    mjs_set_errorf(mjs, ret,
                   "conversion from object to string is not supported");
  } else if (mjs_is_foreign(*v)) {
    *p = "TODO_foreign";
    *sizep = 12;
  } else {
    ret = MJS_TYPE_ERROR;
    mjs_set_errorf(mjs, ret, "unknown type to convert to string");
  }

clean:
  return ret;
}

MJS_PRIVATE mjs_val_t mjs_to_boolean_v(struct mjs *mjs, mjs_val_t v) {
  size_t len;
  int is_truthy;

  is_truthy =
      ((mjs_is_boolean(v) && mjs_get_bool(mjs, v)) ||
       (mjs_is_number(v) && mjs_get_double(mjs, v) != 0.0) ||
       (mjs_is_string(v) && mjs_get_string(mjs, &v, &len) && len > 0) ||
       (mjs_is_function(v)) || (mjs_is_foreign(v)) || (mjs_is_object(v))) &&
      v != MJS_TAG_NAN;

  return mjs_mk_boolean(mjs, is_truthy);
}

MJS_PRIVATE int mjs_is_truthy(struct mjs *mjs, mjs_val_t v) {
  return mjs_get_bool(mjs, mjs_to_boolean_v(mjs, v));
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_core.c"
#endif

/* Amalgamated: #include "common/cs_varint.h" */
/* Amalgamated: #include "common/str_util.h" */

/* Amalgamated: #include "mjs/src/mjs_bcode.h" */
/* Amalgamated: #include "mjs/src/mjs_builtin.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_exec.h" */
/* Amalgamated: #include "mjs/src/mjs_ffi.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_license.h" */
/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

#ifndef MJS_OBJECT_ARENA_SIZE
#define MJS_OBJECT_ARENA_SIZE 20
#endif
#ifndef MJS_PROPERTY_ARENA_SIZE
#define MJS_PROPERTY_ARENA_SIZE 20
#endif
#ifndef MJS_FUNC_FFI_ARENA_SIZE
#define MJS_FUNC_FFI_ARENA_SIZE 20
#endif

#ifndef MJS_OBJECT_ARENA_INC_SIZE
#define MJS_OBJECT_ARENA_INC_SIZE 10
#endif
#ifndef MJS_PROPERTY_ARENA_INC_SIZE
#define MJS_PROPERTY_ARENA_INC_SIZE 10
#endif
#ifndef MJS_FUNC_FFI_ARENA_INC_SIZE
#define MJS_FUNC_FFI_ARENA_INC_SIZE 10
#endif

void mjs_destroy(struct mjs *mjs) {
  {
    int parts_cnt = mjs_bcode_parts_cnt(mjs);
    int i;
    for (i = 0; i < parts_cnt; i++) {
      struct mjs_bcode_part *bp = mjs_bcode_part_get(mjs, i);
      if (!bp->in_rom) {
        free((void *) bp->data.p);
      }
    }
  }

  mbuf_free(&mjs->bcode_gen);
  mbuf_free(&mjs->bcode_parts);
  mbuf_free(&mjs->stack);
  mbuf_free(&mjs->call_stack);
  mbuf_free(&mjs->arg_stack);
  mbuf_free(&mjs->owned_strings);
  mbuf_free(&mjs->foreign_strings);
  mbuf_free(&mjs->owned_values);
  mbuf_free(&mjs->scopes);
  mbuf_free(&mjs->loop_addresses);
  mbuf_free(&mjs->json_visited_stack);
  free(mjs->error_msg);
  free(mjs->stack_trace);
  mjs_ffi_args_free_list(mjs);
  gc_arena_destroy(mjs, &mjs->object_arena);
  gc_arena_destroy(mjs, &mjs->property_arena);
  gc_arena_destroy(mjs, &mjs->ffi_sig_arena);
  free(mjs);
}

struct mjs *mjs_create(void) {
  mjs_val_t global_object;
  struct mjs *mjs = calloc(1, sizeof(*mjs));
  mbuf_init(&mjs->stack, 0);
  mbuf_init(&mjs->call_stack, 0);
  mbuf_init(&mjs->arg_stack, 0);
  mbuf_init(&mjs->owned_strings, 0);
  mbuf_init(&mjs->foreign_strings, 0);
  mbuf_init(&mjs->bcode_gen, 0);
  mbuf_init(&mjs->bcode_parts, 0);
  mbuf_init(&mjs->owned_values, 0);
  mbuf_init(&mjs->scopes, 0);
  mbuf_init(&mjs->loop_addresses, 0);
  mbuf_init(&mjs->json_visited_stack, 0);

  mjs->bcode_len = 0;

  /*
   * The compacting GC exploits the null terminator of the previous string as a
   * marker.
   */
  {
    char z = 0;
    mbuf_append(&mjs->owned_strings, &z, 1);
  }

  gc_arena_init(&mjs->object_arena, sizeof(struct mjs_object),
                MJS_OBJECT_ARENA_SIZE, MJS_OBJECT_ARENA_INC_SIZE);
  gc_arena_init(&mjs->property_arena, sizeof(struct mjs_property),
                MJS_PROPERTY_ARENA_SIZE, MJS_PROPERTY_ARENA_INC_SIZE);
  gc_arena_init(&mjs->ffi_sig_arena, sizeof(struct mjs_ffi_sig),
                MJS_FUNC_FFI_ARENA_SIZE, MJS_FUNC_FFI_ARENA_INC_SIZE);
  mjs->ffi_sig_arena.destructor = mjs_ffi_sig_destructor;

  global_object = mjs_mk_object(mjs);
  mjs_init_builtin(mjs, global_object);
  mjs_set_ffi_resolver(mjs, dlsym);
  push_mjs_val(&mjs->scopes, global_object);
  mjs->vals.this_obj = MJS_UNDEFINED;
  mjs->vals.dataview_proto = MJS_UNDEFINED;

  return mjs;
}

mjs_err_t mjs_set_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  free(mjs->error_msg);
  mjs->error_msg = NULL;
  mjs->error = err;
  if (fmt != NULL) {
    mg_avprintf(&mjs->error_msg, 0, fmt, ap);
  }
  va_end(ap);
  return err;
}

mjs_err_t mjs_prepend_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt,
                             ...) {
  char *old_error_msg = mjs->error_msg;
  char *new_error_msg = NULL;
  va_list ap;
  va_start(ap, fmt);

  /* err should never be MJS_OK here */
  assert(err != MJS_OK);

  mjs->error_msg = NULL;
  /* set error if only it wasn't already set to some error */
  if (mjs->error == MJS_OK) {
    mjs->error = err;
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

void mjs_print_error(struct mjs *mjs, FILE *fp, const char *msg,
                     int print_stack_trace) {
  if (print_stack_trace && mjs->stack_trace != NULL) {
    fprintf(fp, "%s", mjs->stack_trace);
  }

  if (msg == NULL) {
    msg = "MJS error";
  }

  fprintf(fp, "%s: %s\n", msg, mjs_strerror(mjs, mjs->error));
}

MJS_PRIVATE void mjs_die(struct mjs *mjs) {
  mjs_val_t msg_v = MJS_UNDEFINED;
  const char *msg = NULL;
  size_t msg_len = 0;

  /* get idx from arg 0 */
  if (!mjs_check_arg(mjs, 0, "msg", MJS_TYPE_STRING, &msg_v)) {
    goto clean;
  }

  msg = mjs_get_string(mjs, &msg_v, &msg_len);

  /* TODO(dfrank): take error type as an argument */
  mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "%.*s", (int) msg_len, msg);

clean:
  mjs_return(mjs, MJS_UNDEFINED);
}

const char *mjs_strerror(struct mjs *mjs, enum mjs_err err) {
  const char *err_names[] = {
      "NO_ERROR",        "SYNTAX_ERROR",    "REFERENCE_ERROR",
      "TYPE_ERROR",      "OUT_OF_MEMORY",   "INTERNAL_ERROR",
      "NOT_IMPLEMENTED", "FILE_OPEN_ERROR", "BAD_ARGUMENTS"};
  return mjs->error_msg == NULL || mjs->error_msg[0] == '\0' ? err_names[err]
                                                             : mjs->error_msg;
}

MJS_PRIVATE size_t mjs_get_func_addr(mjs_val_t v) {
  return v & ~MJS_TAG_MASK;
}

MJS_PRIVATE enum mjs_type mjs_get_type(mjs_val_t v) {
  int tag;
  if (mjs_is_number(v)) {
    return MJS_TYPE_NUMBER;
  }
  tag = (v & MJS_TAG_MASK) >> 48;
  switch (tag) {
    case MJS_TAG_FOREIGN >> 48:
      return MJS_TYPE_FOREIGN;
    case MJS_TAG_UNDEFINED >> 48:
      return MJS_TYPE_UNDEFINED;
    case MJS_TAG_OBJECT >> 48:
      return MJS_TYPE_OBJECT_GENERIC;
    case MJS_TAG_ARRAY >> 48:
      return MJS_TYPE_OBJECT_ARRAY;
    case MJS_TAG_FUNCTION >> 48:
      return MJS_TYPE_OBJECT_FUNCTION;
    case MJS_TAG_STRING_I >> 48:
    case MJS_TAG_STRING_O >> 48:
    case MJS_TAG_STRING_F >> 48:
    case MJS_TAG_STRING_D >> 48:
    case MJS_TAG_STRING_5 >> 48:
      return MJS_TYPE_STRING;
    case MJS_TAG_BOOLEAN >> 48:
      return MJS_TYPE_BOOLEAN;
    case MJS_TAG_NULL >> 48:
      return MJS_TYPE_NULL;
    default:
      abort();
      return MJS_TYPE_UNDEFINED;
  }
}

mjs_val_t mjs_get_global(struct mjs *mjs) {
  return *vptr(&mjs->scopes, 0);
}

static void mjs_append_stack_trace_line(struct mjs *mjs, size_t offset) {
  if (offset != MJS_BCODE_OFFSET_EXIT) {
    const char *filename = mjs_get_bcode_filename_by_offset(mjs, offset);
    int line_no = mjs_get_lineno_by_offset(mjs, offset);
    char *new_line = NULL;
    const char *fmt = "  at %s:%d\n";
    if (filename == NULL) {
      fprintf(stderr,
              "ERROR during stack trace generation: wrong bcode offset %d\n",
              (int) offset);
      filename = "<unknown-filename>";
    }
    mg_asprintf(&new_line, 0, fmt, filename, line_no);

    if (mjs->stack_trace != NULL) {
      char *old = mjs->stack_trace;
      mg_asprintf(&mjs->stack_trace, 0, "%s%s", mjs->stack_trace, new_line);
      free(old);
      free(new_line);
    } else {
      mjs->stack_trace = new_line;
    }
  }
}

MJS_PRIVATE void mjs_gen_stack_trace(struct mjs *mjs, size_t offset) {
  mjs_append_stack_trace_line(mjs, offset);
  while (mjs->call_stack.len >=
         sizeof(mjs_val_t) * CALL_STACK_FRAME_ITEMS_CNT) {
    int i;

    /* set current offset to it to the offset stored in the frame */
    offset = mjs_get_int(
        mjs, *vptr(&mjs->call_stack, -1 - CALL_STACK_FRAME_ITEM_RETURN_ADDR));

    /* pop frame from the call stack */
    for (i = 0; i < CALL_STACK_FRAME_ITEMS_CNT; i++) {
      mjs_pop_val(&mjs->call_stack);
    }

    mjs_append_stack_trace_line(mjs, offset);
  }
}

void mjs_own(struct mjs *mjs, mjs_val_t *v) {
  mbuf_append(&mjs->owned_values, &v, sizeof(v));
}

int mjs_disown(struct mjs *mjs, mjs_val_t *v) {
  mjs_val_t **vp = (mjs_val_t **) (mjs->owned_values.buf +
                                   mjs->owned_values.len - sizeof(v));

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

/*
 * Returns position in the data stack at which the called function is located,
 * and which should be later replaced with the returned value.
 */
MJS_PRIVATE int mjs_getretvalpos(struct mjs *mjs) {
  int pos;
  mjs_val_t *ppos = vptr(&mjs->call_stack, -1);
  // LOG(LL_INFO, ("ppos: %p %d", ppos, mjs_stack_size(&mjs->call_stack)));
  assert(ppos != NULL && mjs_is_number(*ppos));
  pos = mjs_get_int(mjs, *ppos) - 1;
  assert(pos < (int) mjs_stack_size(&mjs->stack));
  return pos;
}

int mjs_nargs(struct mjs *mjs) {
  int top = mjs_stack_size(&mjs->stack);
  int pos = mjs_getretvalpos(mjs) + 1;
  // LOG(LL_INFO, ("top: %d pos: %d", top, pos));
  return pos > 0 && pos < top ? top - pos : 0;
}

mjs_val_t mjs_arg(struct mjs *mjs, int arg_index) {
  mjs_val_t res = MJS_UNDEFINED;
  int top = mjs_stack_size(&mjs->stack);
  int pos = mjs_getretvalpos(mjs) + 1;
  // LOG(LL_INFO, ("idx %d pos: %d", arg_index, pos));
  if (pos > 0 && pos + arg_index < top) {
    res = *vptr(&mjs->stack, pos + arg_index);
  }
  return res;
}

void mjs_return(struct mjs *mjs, mjs_val_t v) {
  int pos = mjs_getretvalpos(mjs);
  // LOG(LL_INFO, ("pos: %d", pos));
  mjs->stack.len = sizeof(mjs_val_t) * pos;
  mjs_push(mjs, v);
}

MJS_PRIVATE mjs_val_t vtop(struct mbuf *m) {
  size_t size = mjs_stack_size(m);
  return size > 0 ? *vptr(m, size - 1) : MJS_UNDEFINED;
}

MJS_PRIVATE size_t mjs_stack_size(const struct mbuf *m) {
  return m->len / sizeof(mjs_val_t);
}

MJS_PRIVATE mjs_val_t *vptr(struct mbuf *m, int idx) {
  int size = mjs_stack_size(m);
  if (idx < 0) idx = size + idx;
  return idx >= 0 && idx < size ? &((mjs_val_t *) m->buf)[idx] : NULL;
}

MJS_PRIVATE mjs_val_t mjs_pop(struct mjs *mjs) {
  if (mjs->stack.len == 0) {
    mjs_set_errorf(mjs, MJS_INTERNAL_ERROR, "stack underflow");
    return MJS_UNDEFINED;
  } else {
    return mjs_pop_val(&mjs->stack);
  }
}

MJS_PRIVATE void push_mjs_val(struct mbuf *m, mjs_val_t v) {
  mbuf_append(m, &v, sizeof(v));
}

MJS_PRIVATE mjs_val_t mjs_pop_val(struct mbuf *m) {
  mjs_val_t v = MJS_UNDEFINED;
  assert(m->len >= sizeof(v));
  if (m->len >= sizeof(v)) {
    memcpy(&v, m->buf + m->len - sizeof(v), sizeof(v));
    m->len -= sizeof(v);
  }
  return v;
}

MJS_PRIVATE void mjs_push(struct mjs *mjs, mjs_val_t v) {
  push_mjs_val(&mjs->stack, v);
}

void mjs_set_generate_jsc(struct mjs *mjs, int generate_jsc) {
  mjs->generate_jsc = generate_jsc;
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_dataview.c"
#endif

/* Amalgamated: #include "mjs/src/mjs_exec_public.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

void *mjs_mem_to_ptr(unsigned val) {
  return (void *) (uintptr_t) val;
}

void *mjs_mem_get_ptr(void *base, int offset) {
  return (char *) base + offset;
}

void mjs_mem_set_ptr(void *ptr, void *val) {
  *(void **) ptr = val;
}

double mjs_mem_get_dbl(void *ptr) {
  double v;
  memcpy(&v, ptr, sizeof(v));
  return v;
}

void mjs_mem_set_dbl(void *ptr, double val) {
  memcpy(ptr, &val, sizeof(val));
}

/*
 * TODO(dfrank): add support for unsigned ints to ffi and use
 * unsigned int here
 */
double mjs_mem_get_uint(void *ptr, int size, int bigendian) {
  uint8_t *p = (uint8_t *) ptr;
  int i, inc = bigendian ? 1 : -1;
  unsigned int res = 0;
  p += bigendian ? 0 : size - 1;
  for (i = 0; i < size; i++, p += inc) {
    res <<= 8;
    res |= *p;
  }
  return res;
}

/*
 * TODO(dfrank): add support for unsigned ints to ffi and use
 * unsigned int here
 */
double mjs_mem_get_int(void *ptr, int size, int bigendian) {
  uint8_t *p = (uint8_t *) ptr;
  int i, inc = bigendian ? 1 : -1;
  int res = 0;
  p += bigendian ? 0 : size - 1;

  for (i = 0; i < size; i++, p += inc) {
    res <<= 8;
    res |= *p;
  }

  /* sign-extend */
  {
    int extra = sizeof(res) - size;
    for (i = 0; i < extra; i++) res <<= 8;
    for (i = 0; i < extra; i++) res >>= 8;
  }

  return res;
}

void mjs_mem_set_uint(void *ptr, unsigned int val, int size, int bigendian) {
  uint8_t *p = (uint8_t *) ptr + (bigendian ? size - 1 : 0);
  int i, inc = bigendian ? -1 : 1;
  for (i = 0; i < size; i++, p += inc) {
    *p = val & 0xff;
    val >>= 8;
  }
}

void mjs_mem_set_int(void *ptr, int val, int size, int bigendian) {
  mjs_mem_set_uint(ptr, val, size, bigendian);
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_exec.c"
#endif

/* Amalgamated: #include "common/cs_file.h" */
/* Amalgamated: #include "common/cs_varint.h" */

/* Amalgamated: #include "mjs/src/mjs_array.h" */
/* Amalgamated: #include "mjs/src/mjs_bcode.h" */
/* Amalgamated: #include "mjs/src/mjs_conversion.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_exec.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_parser.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "mjs/src/mjs_tok.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

#if MJS_GENERATE_JSC && defined(CS_MMAP)
#include <sys/mman.h>
#endif

/*
 * Pushes call stack frame. Offset is a global bcode offset. Retval_stack_idx
 * is an index in mjs->stack at which return value should be written later.
 */
static void call_stack_push_frame(struct mjs *mjs, size_t offset,
                                  mjs_val_t retval_stack_idx) {
  /* Pop `this` value, and apply it */
  mjs_val_t this_obj = mjs_pop_val(&mjs->arg_stack);

  /*
   * NOTE: the layout is described by enum mjs_call_stack_frame_item
   */
  push_mjs_val(&mjs->call_stack, mjs->vals.this_obj);
  mjs->vals.this_obj = this_obj;

  push_mjs_val(&mjs->call_stack, mjs_mk_number(mjs, (double) offset));
  push_mjs_val(&mjs->call_stack,
               mjs_mk_number(mjs, (double) mjs_stack_size(&mjs->scopes)));
  push_mjs_val(
      &mjs->call_stack,
      mjs_mk_number(mjs, (double) mjs_stack_size(&mjs->loop_addresses)));
  push_mjs_val(&mjs->call_stack, retval_stack_idx);
}

/*
 * Restores call stack frame. Returns the return address.
 */
static size_t call_stack_restore_frame(struct mjs *mjs) {
  size_t retval_stack_idx, return_address, scope_index, loop_addr_index;
  assert(mjs_stack_size(&mjs->call_stack) >= CALL_STACK_FRAME_ITEMS_CNT);

  /*
   * NOTE: the layout is described by enum mjs_call_stack_frame_item
   */
  retval_stack_idx = mjs_get_int(mjs, mjs_pop_val(&mjs->call_stack));
  loop_addr_index = mjs_get_int(mjs, mjs_pop_val(&mjs->call_stack));
  scope_index = mjs_get_int(mjs, mjs_pop_val(&mjs->call_stack));
  return_address = mjs_get_int(mjs, mjs_pop_val(&mjs->call_stack));
  mjs->vals.this_obj = mjs_pop_val(&mjs->call_stack);

  /* Remove created scopes */
  while (mjs_stack_size(&mjs->scopes) > scope_index) {
    mjs_pop_val(&mjs->scopes);
  }

  /* Remove loop addresses */
  while (mjs_stack_size(&mjs->loop_addresses) > loop_addr_index) {
    mjs_pop_val(&mjs->loop_addresses);
  }

  /* Shrink stack, leave return value on top */
  mjs->stack.len = retval_stack_idx * sizeof(mjs_val_t);

  /* Jump to the return address */
  return return_address;
}

static mjs_val_t mjs_find_scope(struct mjs *mjs, mjs_val_t key) {
  size_t num_scopes = mjs_stack_size(&mjs->scopes);
  while (num_scopes > 0) {
    mjs_val_t scope = *vptr(&mjs->scopes, num_scopes - 1);
    num_scopes--;
    if (mjs_get_own_property_v(mjs, scope, key) != NULL) return scope;
  }
  mjs_set_errorf(mjs, MJS_REFERENCE_ERROR, "[%s] is not defined",
                 mjs_get_cstring(mjs, &key));
  return MJS_UNDEFINED;
}

mjs_val_t mjs_get_this(struct mjs *mjs) {
  return mjs->vals.this_obj;
}

static double do_arith_op(double da, double db, int op, bool *resnan) {
  *resnan = false;

  if (isnan(da) || isnan(db)) {
    *resnan = true;
    return 0;
  }
  /* clang-format off */
  switch (op) {
    case TOK_MINUS:   return da - db;
    case TOK_PLUS:    return da + db;
    case TOK_MUL:     return da * db;
    case TOK_DIV:
      if (db != 0) {
        return da / db;
      } else {
        /* TODO(dfrank): add support for Infinity and return it here */
        *resnan = true;
        return 0;
      }
    case TOK_REM:
      /*
       * TODO(dfrank): probably support remainder operation as it is in JS
       * (which works with non-integer divisor).
       */
      db = (int) db;
      if (db != 0) {
        bool neg = false;
        if (da < 0) {
          neg = true;
          da = -da;
        }
        if (db < 0) {
          db = -db;
        }
        da = (double) ((int64_t) da % (int64_t) db);
        if (neg) {
          da = -da;
        }
        return da;
      } else {
        *resnan = true;
        return 0;
      }
    case TOK_AND:     return (double) ((int64_t) da & (int64_t) db);
    case TOK_OR:      return (double) ((int64_t) da | (int64_t) db);
    case TOK_XOR:     return (double) ((int64_t) da ^ (int64_t) db);
    case TOK_LSHIFT:  return (double) ((int64_t) da << (int64_t) db);
    case TOK_RSHIFT:  return (double) ((int64_t) da >> (int64_t) db);
    case TOK_URSHIFT: return (double) ((uint32_t) da >> (uint32_t) db);
  }
  /* clang-format on */
  *resnan = true;
  return 0;
}

static void set_no_autoconversion_error(struct mjs *mjs) {
  mjs_prepend_errorf(mjs, MJS_TYPE_ERROR,
                     "implicit type conversion is prohibited");
}

static mjs_val_t do_op(struct mjs *mjs, mjs_val_t a, mjs_val_t b, int op) {
  mjs_val_t ret = MJS_UNDEFINED;
  bool resnan = false;
  if ((mjs_is_foreign(a) || mjs_is_number(a)) &&
      (mjs_is_foreign(b) || mjs_is_number(b))) {
    int is_result_ptr = 0;
    double da, db, result;

    if (mjs_is_foreign(a) && mjs_is_foreign(b)) {
      /* When two operands are pointers, only subtraction is supported */
      if (op != TOK_MINUS) {
        mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "invalid operands");
      }
    } else if (mjs_is_foreign(a) || mjs_is_foreign(b)) {
      /*
       * When one of the operands is a pointer, only + and - are supported,
       * and the result is a pointer.
       */
      if (op != TOK_MINUS && op != TOK_PLUS) {
        mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "invalid operands");
      }
      is_result_ptr = 1;
    }
    da = mjs_is_number(a) ? mjs_get_double(mjs, a)
                          : (double) (uintptr_t) mjs_get_ptr(mjs, a);
    db = mjs_is_number(b) ? mjs_get_double(mjs, b)
                          : (double) (uintptr_t) mjs_get_ptr(mjs, b);
    result = do_arith_op(da, db, op, &resnan);
    if (resnan) {
      ret = MJS_TAG_NAN;
    } else {
      /*
       * If at least one of the operands was a pointer, result should also be
       * a pointer
       */
      ret = is_result_ptr ? mjs_mk_foreign(mjs, (void *) (uintptr_t) result)
                          : mjs_mk_number(mjs, result);
    }
  } else if (mjs_is_string(a) && mjs_is_string(b) && (op == TOK_PLUS)) {
    ret = s_concat(mjs, a, b);
  } else {
    set_no_autoconversion_error(mjs);
  }
  return ret;
}

static void op_assign(struct mjs *mjs, int op) {
  mjs_val_t val = mjs_pop(mjs);
  mjs_val_t obj = mjs_pop(mjs);
  mjs_val_t key = mjs_pop(mjs);
  if (mjs_is_object(obj) && mjs_is_string(key)) {
    mjs_val_t v = mjs_get_v(mjs, obj, key);
    mjs_set_v(mjs, obj, key, do_op(mjs, v, val, op));
    mjs_push(mjs, v);
  } else {
    mjs_set_errorf(mjs, MJS_TYPE_ERROR, "invalid operand");
  }
}

static int check_equal(struct mjs *mjs, mjs_val_t a, mjs_val_t b) {
  int ret = 0;
  if (a == MJS_TAG_NAN && b == MJS_TAG_NAN) {
    ret = 0;
  } else if (a == b) {
    ret = 1;
  } else if (mjs_is_number(a) && mjs_is_number(b)) {
    /*
     * The case of equal numbers is handled above, so here the result is always
     * false
     */
    ret = 0;
  } else if (mjs_is_string(a) && mjs_is_string(b)) {
    ret = s_cmp(mjs, a, b) == 0;
  } else if (mjs_is_foreign(a) && b == MJS_NULL) {
    ret = mjs_get_ptr(mjs, a) == NULL;
  } else if (a == MJS_NULL && mjs_is_foreign(b)) {
    ret = mjs_get_ptr(mjs, b) == NULL;
  } else {
    ret = 0;
  }
  return ret;
}

static void exec_expr(struct mjs *mjs, int op) {
  switch (op) {
    case TOK_DOT:
      break;
    case TOK_MINUS:
    case TOK_PLUS:
    case TOK_MUL:
    case TOK_DIV:
    case TOK_REM:
    case TOK_XOR:
    case TOK_AND:
    case TOK_OR:
    case TOK_LSHIFT:
    case TOK_RSHIFT:
    case TOK_URSHIFT: {
      mjs_val_t b = mjs_pop(mjs);
      mjs_val_t a = mjs_pop(mjs);
      mjs_push(mjs, do_op(mjs, a, b, op));
      break;
    }
    case TOK_UNARY_MINUS: {
      double a = mjs_get_double(mjs, mjs_pop(mjs));
      mjs_push(mjs, mjs_mk_number(mjs, -a));
      break;
    }
    case TOK_NOT: {
      mjs_val_t val = mjs_pop(mjs);
      mjs_push(mjs, mjs_mk_boolean(mjs, !mjs_is_truthy(mjs, val)));
      break;
    }
    case TOK_TILDA: {
      double a = mjs_get_double(mjs, mjs_pop(mjs));
      mjs_push(mjs, mjs_mk_number(mjs, (double) (~(int64_t) a)));
      break;
    }
    case TOK_UNARY_PLUS:
      break;
    case TOK_EQ:
      mjs_set_errorf(mjs, MJS_NOT_IMPLEMENTED_ERROR, "Use ===, not ==");
      break;
    case TOK_NE:
      mjs_set_errorf(mjs, MJS_NOT_IMPLEMENTED_ERROR, "Use !==, not !=");
      break;
    case TOK_EQ_EQ: {
      mjs_val_t a = mjs_pop(mjs);
      mjs_val_t b = mjs_pop(mjs);
      mjs_push(mjs, mjs_mk_boolean(mjs, check_equal(mjs, a, b)));
      break;
    }
    case TOK_NE_NE: {
      mjs_val_t a = mjs_pop(mjs);
      mjs_val_t b = mjs_pop(mjs);
      mjs_push(mjs, mjs_mk_boolean(mjs, !check_equal(mjs, a, b)));
      break;
    }
    case TOK_LT: {
      double b = mjs_get_double(mjs, mjs_pop(mjs));
      double a = mjs_get_double(mjs, mjs_pop(mjs));
      mjs_push(mjs, mjs_mk_boolean(mjs, a < b));
      break;
    }
    case TOK_GT: {
      double b = mjs_get_double(mjs, mjs_pop(mjs));
      double a = mjs_get_double(mjs, mjs_pop(mjs));
      mjs_push(mjs, mjs_mk_boolean(mjs, a > b));
      break;
    }
    case TOK_LE: {
      double b = mjs_get_double(mjs, mjs_pop(mjs));
      double a = mjs_get_double(mjs, mjs_pop(mjs));
      mjs_push(mjs, mjs_mk_boolean(mjs, a <= b));
      break;
    }
    case TOK_GE: {
      double b = mjs_get_double(mjs, mjs_pop(mjs));
      double a = mjs_get_double(mjs, mjs_pop(mjs));
      mjs_push(mjs, mjs_mk_boolean(mjs, a >= b));
      break;
    }
    case TOK_ASSIGN: {
      mjs_val_t val = mjs_pop(mjs);
      mjs_val_t obj = mjs_pop(mjs);
      mjs_val_t key = mjs_pop(mjs);
      if (mjs_is_object(obj)) {
        mjs_set_v(mjs, obj, key, val);
      } else if (mjs_is_foreign(obj)) {
        /*
         * We don't have setters, so in order to support properties which behave
         * like setters, we have to parse key right here, instead of having real
         * built-in prototype objects
         */

        int ikey = mjs_get_int(mjs, key);
        int ival = mjs_get_int(mjs, val);

        if (!mjs_is_number(key)) {
          mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "index must be a number");
          val = MJS_UNDEFINED;
        } else if (!mjs_is_number(val) || ival < 0 || ival > 0xff) {
          mjs_prepend_errorf(mjs, MJS_TYPE_ERROR,
                             "only number 0 .. 255 can be assigned");
          val = MJS_UNDEFINED;
        } else {
          uint8_t *ptr = (uint8_t *) mjs_get_ptr(mjs, obj);
          *(ptr + ikey) = (uint8_t) ival;
        }
      } else {
        mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "unsupported object type");
      }
      mjs_push(mjs, val);
      break;
    }
    case TOK_POSTFIX_PLUS: {
      mjs_val_t obj = mjs_pop(mjs);
      mjs_val_t key = mjs_pop(mjs);
      if (mjs_is_object(obj) && mjs_is_string(key)) {
        mjs_val_t v = mjs_get_v(mjs, obj, key);
        mjs_val_t v1 = do_op(mjs, v, mjs_mk_number(mjs, 1), TOK_PLUS);
        mjs_set_v(mjs, obj, key, v1);
        mjs_push(mjs, v);
      } else {
        mjs_set_errorf(mjs, MJS_TYPE_ERROR, "invalid operand for ++");
      }
      break;
    }
    case TOK_POSTFIX_MINUS: {
      mjs_val_t obj = mjs_pop(mjs);
      mjs_val_t key = mjs_pop(mjs);
      if (mjs_is_object(obj) && mjs_is_string(key)) {
        mjs_val_t v = mjs_get_v(mjs, obj, key);
        mjs_val_t v1 = do_op(mjs, v, mjs_mk_number(mjs, 1), TOK_MINUS);
        mjs_set_v(mjs, obj, key, v1);
        mjs_push(mjs, v);
      } else {
        mjs_set_errorf(mjs, MJS_TYPE_ERROR, "invalid operand for --");
      }
      break;
    }
    case TOK_MINUS_MINUS: {
      mjs_val_t obj = mjs_pop(mjs);
      mjs_val_t key = mjs_pop(mjs);
      if (mjs_is_object(obj) && mjs_is_string(key)) {
        mjs_val_t v = mjs_get_v(mjs, obj, key);
        v = do_op(mjs, v, mjs_mk_number(mjs, 1), TOK_MINUS);
        mjs_set_v(mjs, obj, key, v);
        mjs_push(mjs, v);
      } else {
        mjs_set_errorf(mjs, MJS_TYPE_ERROR, "invalid operand for --");
      }
      break;
    }
    case TOK_PLUS_PLUS: {
      mjs_val_t obj = mjs_pop(mjs);
      mjs_val_t key = mjs_pop(mjs);
      if (mjs_is_object(obj) && mjs_is_string(key)) {
        mjs_val_t v = mjs_get_v(mjs, obj, key);
        v = do_op(mjs, v, mjs_mk_number(mjs, 1), TOK_PLUS);
        mjs_set_v(mjs, obj, key, v);
        mjs_push(mjs, v);
      } else {
        mjs_set_errorf(mjs, MJS_TYPE_ERROR, "invalid operand for ++");
      }
      break;
    }
    /*
     * NOTE: TOK_LOGICAL_AND and TOK_LOGICAL_OR don't need to be here, because
     * they are just naturally handled by the short-circuit evaluation.
     * See PARSE_LTR_BINOP() macro in mjs_parser.c.
     */

    /* clang-format off */
    case TOK_MINUS_ASSIGN:    op_assign(mjs, TOK_MINUS);    break;
    case TOK_PLUS_ASSIGN:     op_assign(mjs, TOK_PLUS);     break;
    case TOK_MUL_ASSIGN:      op_assign(mjs, TOK_MUL);      break;
    case TOK_DIV_ASSIGN:      op_assign(mjs, TOK_DIV);      break;
    case TOK_REM_ASSIGN:      op_assign(mjs, TOK_REM);      break;
    case TOK_AND_ASSIGN:      op_assign(mjs, TOK_AND);      break;
    case TOK_OR_ASSIGN:       op_assign(mjs, TOK_OR);       break;
    case TOK_XOR_ASSIGN:      op_assign(mjs, TOK_XOR);      break;
    case TOK_LSHIFT_ASSIGN:   op_assign(mjs, TOK_LSHIFT);   break;
    case TOK_RSHIFT_ASSIGN:   op_assign(mjs, TOK_RSHIFT);   break;
    case TOK_URSHIFT_ASSIGN:  op_assign(mjs, TOK_URSHIFT);  break;
    case TOK_COMMA: break;
    /* clang-format on */
    case TOK_KEYWORD_TYPEOF:
      mjs_push(mjs, mjs_mk_string(mjs, mjs_typeof(mjs_pop(mjs)), ~0, 1));
      break;
    default:
      LOG(LL_ERROR, ("Unknown expr: %d", op));
      break;
  }
}

static int getprop_builtin_string(struct mjs *mjs, mjs_val_t val,
                                  const char *name, size_t name_len,
                                  mjs_val_t *res) {
  int isnum = 0;
  int idx = cstr_to_ulong(name, name_len, &isnum);

  if (strcmp(name, "length") == 0) {
    size_t val_len;
    mjs_get_string(mjs, &val, &val_len);
    *res = mjs_mk_number(mjs, (double) val_len);
    return 1;
  } else if (strcmp(name, "at") == 0 || strcmp(name, "charCodeAt") == 0) {
    *res = mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_string_char_code_at);
    return 1;
  } else if (strcmp(name, "indexOf") == 0) {
    *res = mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_string_index_of);
    return 1;
  } else if (strcmp(name, "slice") == 0) {
    *res = mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_string_slice);
    return 1;
  } else if (isnum) {
    /*
     * string subscript: return a new one-byte string if the index
     * is not out of bounds
     */
    size_t val_len;
    const char *str = mjs_get_string(mjs, &val, &val_len);
    if (idx >= 0 && idx < (int) val_len) {
      *res = mjs_mk_string(mjs, str + idx, 1, 1);
    } else {
      *res = MJS_UNDEFINED;
    }
    return 1;
  }
  return 0;
}

static int getprop_builtin_array(struct mjs *mjs, mjs_val_t val,
                                 const char *name, size_t name_len,
                                 mjs_val_t *res) {
  if (strcmp(name, "splice") == 0) {
    *res = mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_array_splice);
    return 1;
  } else if (strcmp(name, "push") == 0) {
    *res = mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_array_push_internal);
    return 1;
  } else if (strcmp(name, "length") == 0) {
    *res = mjs_mk_number(mjs, mjs_array_length(mjs, val));
    return 1;
  }

  (void) name_len;
  return 0;
}

static int getprop_builtin_foreign(struct mjs *mjs, mjs_val_t val,
                                   const char *name, size_t name_len,
                                   mjs_val_t *res) {
  int isnum = 0;
  int idx = cstr_to_ulong(name, name_len, &isnum);

  if (!isnum) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "index must be a number");
  } else {
    uint8_t *ptr = (uint8_t *) mjs_get_ptr(mjs, val);
    *res = mjs_mk_number(mjs, *(ptr + idx));
  }
  return 1;
}

static void mjs_apply_(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED, *args = NULL;
  mjs_val_t func = mjs->vals.this_obj, v = mjs_arg(mjs, 1);
  int i, nargs = 0;
  if (mjs_is_array(v)) {
    nargs = mjs_array_length(mjs, v);
    args = calloc(nargs, sizeof(args[0]));
    for (i = 0; i < nargs; i++) args[i] = mjs_array_get(mjs, v, i);
  }
  mjs_apply(mjs, &res, func, mjs_arg(mjs, 0), nargs, args);
  free(args);
  mjs_return(mjs, res);
}

static int getprop_builtin(struct mjs *mjs, mjs_val_t val, mjs_val_t name,
                           mjs_val_t *res) {
  size_t n;
  char *s = NULL;
  int need_free = 0;
  int handled = 0;

  mjs_err_t err = mjs_to_string(mjs, &name, &s, &n, &need_free);

  if (err == MJS_OK) {
    if (mjs_is_string(val)) {
      handled = getprop_builtin_string(mjs, val, s, n, res);
    } else if (s != NULL && n == 5 && strncmp(s, "apply", n) == 0) {
      *res = mjs_mk_foreign_func(mjs, (mjs_func_ptr_t) mjs_apply_);
      handled = 1;
    } else if (mjs_is_array(val)) {
      handled = getprop_builtin_array(mjs, val, s, n, res);
    } else if (mjs_is_foreign(val)) {
      handled = getprop_builtin_foreign(mjs, val, s, n, res);
    }
  }

  if (need_free) {
    free(s);
    s = NULL;
  }

  return handled;
}

MJS_PRIVATE mjs_err_t mjs_execute(struct mjs *mjs, size_t off, mjs_val_t *res) {
  size_t i;
  uint8_t prev_opcode = OP_MAX;
  uint8_t opcode = OP_MAX;

  /*
   * remember lengths of all stacks, they will be restored in case of an error
   */
  int stack_len = mjs->stack.len;
  int call_stack_len = mjs->call_stack.len;
  int arg_stack_len = mjs->arg_stack.len;
  int scopes_len = mjs->scopes.len;
  int loop_addresses_len = mjs->loop_addresses.len;
  size_t start_off = off;
  const uint8_t *code;

  struct mjs_bcode_part bp = *mjs_bcode_part_get_by_offset(mjs, off);

  mjs_set_errorf(mjs, MJS_OK, NULL);
  free(mjs->stack_trace);
  mjs->stack_trace = NULL;

  off -= bp.start_idx;

  for (i = off; i < bp.data.len; i++) {
    mjs->cur_bcode_offset = i;

    if (mjs->need_gc) {
      if (maybe_gc(mjs)) {
        mjs->need_gc = 0;
      }
    }
#if MJS_AGGRESSIVE_GC
    maybe_gc(mjs);
#endif

    code = (const uint8_t *) bp.data.p;
    mjs_disasm_single(code, i);
    prev_opcode = opcode;
    opcode = code[i];
    switch (opcode) {
      case OP_BCODE_HEADER: {
        mjs_header_item_t bcode_offset;
        memcpy(&bcode_offset,
               code + i + 1 +
                   sizeof(mjs_header_item_t) * MJS_HDR_ITEM_BCODE_OFFSET,
               sizeof(bcode_offset));
        i += bcode_offset;
      } break;
      case OP_PUSH_NULL:
        mjs_push(mjs, mjs_mk_null());
        break;
      case OP_PUSH_UNDEF:
        mjs_push(mjs, mjs_mk_undefined());
        break;
      case OP_PUSH_FALSE:
        mjs_push(mjs, mjs_mk_boolean(mjs, 0));
        break;
      case OP_PUSH_TRUE:
        mjs_push(mjs, mjs_mk_boolean(mjs, 1));
        break;
      case OP_PUSH_OBJ:
        mjs_push(mjs, mjs_mk_object(mjs));
        break;
      case OP_PUSH_ARRAY:
        mjs_push(mjs, mjs_mk_array(mjs));
        break;
      case OP_PUSH_FUNC: {
        int llen, n = cs_varint_decode_unsafe(&code[i + 1], &llen);
        mjs_push(mjs, mjs_mk_function(mjs, bp.start_idx + i - n));
        i += llen;
        break;
      }
      case OP_PUSH_THIS:
        mjs_push(mjs, mjs->vals.this_obj);
        break;
      case OP_JMP: {
        int llen, n = cs_varint_decode_unsafe(&code[i + 1], &llen);
        i += n + llen;
        break;
      }
      case OP_JMP_FALSE: {
        int llen, n = cs_varint_decode_unsafe(&code[i + 1], &llen);
        i += llen;
        if (!mjs_is_truthy(mjs, mjs_pop(mjs))) {
          mjs_push(mjs, MJS_UNDEFINED);
          i += n;
        }
        break;
      }
      /*
       * OP_JMP_NEUTRAL_... ops are like as OP_JMP_..., but they are completely
       * stack-neutral: they just check the TOS, and increment instruction
       * pointer if the TOS is truthy/falsy.
       */
      case OP_JMP_NEUTRAL_TRUE: {
        int llen, n = cs_varint_decode_unsafe(&code[i + 1], &llen);
        i += llen;
        if (mjs_is_truthy(mjs, vtop(&mjs->stack))) {
          i += n;
        }
        break;
      }
      case OP_JMP_NEUTRAL_FALSE: {
        int llen, n = cs_varint_decode_unsafe(&code[i + 1], &llen);
        i += llen;
        if (!mjs_is_truthy(mjs, vtop(&mjs->stack))) {
          i += n;
        }
        break;
      }
      case OP_FIND_SCOPE: {
        mjs_val_t key = vtop(&mjs->stack);
        mjs_push(mjs, mjs_find_scope(mjs, key));
        break;
      }
      case OP_CREATE: {
        mjs_val_t obj = mjs_pop(mjs);
        mjs_val_t key = mjs_pop(mjs);
        if (mjs_get_own_property_v(mjs, obj, key) == NULL) {
          mjs_set_v(mjs, obj, key, MJS_UNDEFINED);
        }
        break;
      }
      case OP_APPEND: {
        mjs_val_t val = mjs_pop(mjs);
        mjs_val_t arr = mjs_pop(mjs);
        mjs_err_t err = mjs_array_push(mjs, arr, val);
        if (err != MJS_OK) {
          mjs_set_errorf(mjs, MJS_TYPE_ERROR, "append to non-array");
        }
        break;
      }
      case OP_GET: {
        mjs_val_t obj = mjs_pop(mjs);
        mjs_val_t key = mjs_pop(mjs);
        mjs_val_t val = MJS_UNDEFINED;

        if (!getprop_builtin(mjs, obj, key, &val)) {
          if (mjs_is_object(obj)) {
            val = mjs_get_v_proto(mjs, obj, key);
          } else {
            mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "type error");
          }
        }

        mjs_push(mjs, val);
        if (prev_opcode != OP_FIND_SCOPE) {
          /*
           * Previous opcode was not OP_FIND_SCOPE, so it's some "custom"
           * object which might be used as `this`, so, save it
           */
          mjs->vals.last_getprop_obj = obj;
        } else {
          /*
           * Previous opcode was OP_FIND_SCOPE, so we're getting value from
           * the scope, and it should *not* be used as `this`
           */
          mjs->vals.last_getprop_obj = MJS_UNDEFINED;
        }
        break;
      }
      case OP_DEL_SCOPE:
        if (mjs->scopes.len <= 1) {
          mjs_set_errorf(mjs, MJS_INTERNAL_ERROR, "scopes underflow");
        } else {
          mjs_pop_val(&mjs->scopes);
        }
        break;
      case OP_NEW_SCOPE:
        push_mjs_val(&mjs->scopes, mjs_mk_object(mjs));
        break;
      case OP_PUSH_SCOPE:
        assert(mjs_stack_size(&mjs->scopes) > 0);
        mjs_push(mjs, vtop(&mjs->scopes));
        break;
      case OP_PUSH_STR: {
        int llen, n = cs_varint_decode_unsafe(&code[i + 1], &llen);
        mjs_push(mjs, mjs_mk_string(mjs, (char *) code + i + 1 + llen, n, 1));
        i += llen + n;
        break;
      }
      case OP_PUSH_INT: {
        int llen;
        int64_t n = cs_varint_decode_unsafe(&code[i + 1], &llen);
        mjs_push(mjs, mjs_mk_number(mjs, (double) n));
        i += llen;
        break;
      }
      case OP_PUSH_DBL: {
        int llen, n = cs_varint_decode_unsafe(&code[i + 1], &llen);
        mjs_push(mjs, mjs_mk_number(
                          mjs, strtod((char *) code + i + 1 + llen, NULL)));
        i += llen + n;
        break;
      }
      case OP_FOR_IN_NEXT: {
        /*
         * Data stack layout:
         * ...                                    <-- Bottom of the data stack
         * <iterator_variable_name>   (string)
         * <object_that_is_iterated>  (object)
         * <iterator_foreign_ptr>                 <-- Top of the data stack
         */
        mjs_val_t *iterator = vptr(&mjs->stack, -1);
        mjs_val_t obj = *vptr(&mjs->stack, -2);
        if (mjs_is_object(obj)) {
          mjs_val_t var_name = *vptr(&mjs->stack, -3);
          mjs_val_t key = mjs_next(mjs, obj, iterator);
          if (key != MJS_UNDEFINED) {
            mjs_val_t scope = mjs_find_scope(mjs, var_name);
            mjs_set_v(mjs, scope, var_name, key);
          }
        } else {
          mjs_set_errorf(mjs, MJS_TYPE_ERROR,
                         "can't iterate over non-object value");
        }
        break;
      }
      case OP_RETURN: {
        /*
         * Return address is saved as a global bcode offset, so we need to
         * convert it to the local offset
         */
        size_t off_ret = call_stack_restore_frame(mjs);
        if (off_ret != MJS_BCODE_OFFSET_EXIT) {
          bp = *mjs_bcode_part_get_by_offset(mjs, off_ret);
          code = (const uint8_t *) bp.data.p;
          i = off_ret - bp.start_idx;
          LOG(LL_VERBOSE_DEBUG, ("RETURNING TO %d", (int) off_ret + 1));
        } else {
          goto clean;
        }
        // mjs_dump(mjs, 0, stdout);
        break;
      }
      case OP_ARGS: {
        /*
         * If OP_ARGS follows OP_GET, then last_getprop_obj is set to `this`
         * value; otherwise, last_getprop_obj is irrelevant and we have to
         * reset it to `undefined`
         */
        if (prev_opcode != OP_GET) {
          mjs->vals.last_getprop_obj = MJS_UNDEFINED;
        }

        /*
         * Push last_getprop_obj, which is going to be used as `this`, see
         * OP_CALL
         */
        push_mjs_val(&mjs->arg_stack, mjs->vals.last_getprop_obj);
        /*
         * Push current size of data stack, it's needed to place arguments
         * properly
         */
        push_mjs_val(&mjs->arg_stack,
                     mjs_mk_number(mjs, (double) mjs_stack_size(&mjs->stack)));
        break;
      }
      case OP_CALL: {
        // LOG(LL_INFO, ("BEFORE CALL"));
        // mjs_dump(mjs, 0, stdout);
        int func_pos;
        mjs_val_t *func;
        mjs_val_t retval_stack_idx = vtop(&mjs->arg_stack);
        func_pos = mjs_get_int(mjs, retval_stack_idx) - 1;
        func = vptr(&mjs->stack, func_pos);

        /* Drop data stack size (pushed by OP_ARGS) */
        mjs_pop_val(&mjs->arg_stack);

        if (mjs_is_function(*func)) {
          size_t off_call;
          call_stack_push_frame(mjs, bp.start_idx + i, retval_stack_idx);

          /*
           * Function offset is a global bcode offset, so we need to convert it
           * to the local offset
           */
          off_call = mjs_get_func_addr(*func) - 1;
          bp = *mjs_bcode_part_get_by_offset(mjs, off_call);
          code = (const uint8_t *) bp.data.p;
          i = off_call - bp.start_idx;

          *func = MJS_UNDEFINED;  // Return value
          // LOG(LL_VERBOSE_DEBUG, ("CALLING  %d", i + 1));
        } else if (mjs_is_string(*func) || mjs_is_ffi_sig(*func)) {
          /* Call ffi-ed function */

          call_stack_push_frame(mjs, bp.start_idx + i, retval_stack_idx);

          /* Perform the ffi-ed function call */
          mjs_ffi_call2(mjs);

          call_stack_restore_frame(mjs);
        } else if (mjs_is_foreign(*func)) {
          /* Call cfunction */

          call_stack_push_frame(mjs, bp.start_idx + i, retval_stack_idx);

          /* Perform the cfunction call */
          ((void (*) (struct mjs *)) mjs_get_ptr(mjs, *func))(mjs);

          call_stack_restore_frame(mjs);
        } else {
          mjs_set_errorf(mjs, MJS_TYPE_ERROR, "calling non-callable");
        }
        break;
      }
      case OP_SET_ARG: {
        int llen1, llen2, n,
            arg_no = cs_varint_decode_unsafe(&code[i + 1], &llen1);
        mjs_val_t obj, key, v;
        n = cs_varint_decode_unsafe(&code[i + llen1 + 1], &llen2);
        key = mjs_mk_string(mjs, (char *) code + i + 1 + llen1 + llen2, n, 1);
        obj = vtop(&mjs->scopes);
        v = mjs_arg(mjs, arg_no);
        mjs_set_v(mjs, obj, key, v);
        i += llen1 + llen2 + n;
        break;
      }
      case OP_SETRETVAL: {
        if (mjs_stack_size(&mjs->call_stack) < CALL_STACK_FRAME_ITEMS_CNT) {
          mjs_set_errorf(mjs, MJS_INTERNAL_ERROR, "cannot return");
        } else {
          size_t retval_pos = mjs_get_int(
              mjs, *vptr(&mjs->call_stack,
                         -1 - CALL_STACK_FRAME_ITEM_RETVAL_STACK_IDX));
          *vptr(&mjs->stack, retval_pos - 1) = mjs_pop(mjs);
        }
        // LOG(LL_INFO, ("AFTER SETRETVAL"));
        // mjs_dump(mjs, 0, stdout);
        break;
      }
      case OP_EXPR: {
        int op = code[i + 1];
        exec_expr(mjs, op);
        i++;
        break;
      }
      case OP_DROP: {
        mjs_pop(mjs);
        break;
      }
      case OP_DUP: {
        mjs_push(mjs, vtop(&mjs->stack));
        break;
      }
      case OP_SWAP: {
        mjs_val_t a = mjs_pop(mjs);
        mjs_val_t b = mjs_pop(mjs);
        mjs_push(mjs, a);
        mjs_push(mjs, b);
        break;
      }
      case OP_LOOP: {
        int l1, l2, off = cs_varint_decode_unsafe(&code[i + 1], &l1);
        /* push scope index */
        push_mjs_val(&mjs->loop_addresses,
                     mjs_mk_number(mjs, (double) mjs_stack_size(&mjs->scopes)));

        /* push break offset */
        push_mjs_val(
            &mjs->loop_addresses,
            mjs_mk_number(mjs, (double) (i + 1 /* OP_LOOP */ + l1 + off)));
        off = cs_varint_decode_unsafe(&code[i + 1 + l1], &l2);

        /* push continue offset */
        push_mjs_val(
            &mjs->loop_addresses,
            mjs_mk_number(mjs, (double) (i + 1 /* OP_LOOP*/ + l1 + l2 + off)));
        i += l1 + l2;
        break;
      }
      case OP_CONTINUE: {
        if (mjs_stack_size(&mjs->loop_addresses) >= 3) {
          size_t scopes_len = mjs_get_int(mjs, *vptr(&mjs->loop_addresses, -3));
          assert(mjs_stack_size(&mjs->scopes) >= scopes_len);
          mjs->scopes.len = scopes_len * sizeof(mjs_val_t);

          /* jump to "continue" address */
          i = mjs_get_int(mjs, vtop(&mjs->loop_addresses)) - 1;
        } else {
          mjs_set_errorf(mjs, MJS_SYNTAX_ERROR, "misplaced 'continue'");
        }
      } break;
      case OP_BREAK: {
        if (mjs_stack_size(&mjs->loop_addresses) >= 3) {
          size_t scopes_len;
          /* drop "continue" address */
          mjs_pop_val(&mjs->loop_addresses);

          /* pop "break" address and jump to it */
          i = mjs_get_int(mjs, mjs_pop_val(&mjs->loop_addresses)) - 1;

          /* restore scope index */
          scopes_len = mjs_get_int(mjs, mjs_pop_val(&mjs->loop_addresses));
          assert(mjs_stack_size(&mjs->scopes) >= scopes_len);
          mjs->scopes.len = scopes_len * sizeof(mjs_val_t);

          LOG(LL_VERBOSE_DEBUG, ("BREAKING TO %d", (int) i + 1));
        } else {
          mjs_set_errorf(mjs, MJS_SYNTAX_ERROR, "misplaced 'break'");
        }
      } break;
      case OP_NOP:
        break;
      case OP_EXIT:
        i = bp.data.len;
        break;
      default:
#if MJS_ENABLE_DEBUG
        mjs_dump(mjs, 1);
#endif
        mjs_set_errorf(mjs, MJS_INTERNAL_ERROR, "Unknown opcode: %d, off %d+%d",
                       (int) opcode, (int) bp.start_idx, (int) i);
        i = bp.data.len;
        break;
    }
    if (mjs->error != MJS_OK) {
      mjs_gen_stack_trace(mjs, bp.start_idx + i - 1 /* undo the i++ */);

      /* restore stack lenghts */
      mjs->stack.len = stack_len;
      mjs->call_stack.len = call_stack_len;
      mjs->arg_stack.len = arg_stack_len;
      mjs->scopes.len = scopes_len;
      mjs->loop_addresses.len = loop_addresses_len;

      /* script will evaluate to `undefined` */
      mjs_push(mjs, MJS_UNDEFINED);
      break;
    }
  }

clean:
  /* Remember result of the evaluation of this bcode part */
  mjs_bcode_part_get_by_offset(mjs, start_off)->exec_res = mjs->error;

  *res = mjs_pop(mjs);
  return mjs->error;
}

MJS_PRIVATE mjs_err_t mjs_exec_internal(struct mjs *mjs, const char *path,
                                        const char *src, int generate_jsc,
                                        mjs_val_t *res) {
  size_t off = mjs->bcode_len;
  mjs_val_t r = MJS_UNDEFINED;
  mjs->error = mjs_parse(path, src, mjs);
  if (cs_log_level >= LL_VERBOSE_DEBUG) mjs_dump(mjs, 1);
  if (generate_jsc == -1) generate_jsc = mjs->generate_jsc;
  if (mjs->error == MJS_OK) {
#if MJS_GENERATE_JSC && defined(CS_MMAP)
    if (generate_jsc && path != NULL) {
      const char *jsext = ".js";
      int basename_len = (int) strlen(path) - strlen(jsext);
      if (basename_len > 0 && strcmp(path + basename_len, jsext) == 0) {
        /* source file has a .js extension: create a .jsc counterpart */
        int rewrite = 1;
        int read_mmapped = 1;

        /* construct .jsc filename */
        const char *jscext = ".jsc";
        char filename_jsc[basename_len + strlen(jscext) + 1 /* nul-term */];
        memcpy(filename_jsc, path, basename_len);
        strcpy(filename_jsc + basename_len, jscext);

        /* get last bcode part */
        struct mjs_bcode_part *bp =
            mjs_bcode_part_get(mjs, mjs_bcode_parts_cnt(mjs) - 1);

        /*
         * before writing .jsc file, check if it already exists and has the
         * same contents
         *
         * TODO(dfrank): probably store crc32 before the bcode data, and only
         * compare it.
         */
        {
          size_t size;
          char *data = cs_mmap_file(filename_jsc, &size);
          if (data != NULL) {
            if (size == bp->data.len) {
              if (memcmp(data, bp->data.p, size) == 0) {
                /* .jsc file is up to date, so don't rewrite it */
                rewrite = 0;
              }
            }
            munmap(data, size);
          }
        }

        /* try to open .jsc file for writing */
        if (rewrite) {
          FILE *fp = fopen(filename_jsc, "wb");
          if (fp != NULL) {
            /* write last bcode part to .jsc */
            fwrite(bp->data.p, bp->data.len, 1, fp);
            fclose(fp);
          } else {
            LOG(LL_WARN, ("Failed to open %s for writing", filename_jsc));
            read_mmapped = 0;
          }
        }

        if (read_mmapped) {
          /* free RAM buffer with last bcode part */
          free((void *) bp->data.p);

          /* mmap .jsc file and set last bcode part buffer to it */
          bp->data.p = cs_mmap_file(filename_jsc, &bp->data.len);
          bp->in_rom = 1;
        }
      }
    }
#else
    (void) generate_jsc;
#endif

    mjs_execute(mjs, off, &r);
  }
  if (res != NULL) *res = r;
  return mjs->error;
}

mjs_err_t mjs_exec(struct mjs *mjs, const char *src, mjs_val_t *res) {
  return mjs_exec_internal(mjs, "<stdin>", src, 0 /* generate_jsc */, res);
}

mjs_err_t mjs_exec_file(struct mjs *mjs, const char *path, mjs_val_t *res) {
  mjs_err_t error = MJS_FILE_READ_ERROR;
  mjs_val_t r = MJS_UNDEFINED;
  size_t size;
  char *source_code = cs_read_file(path, &size);

  if (source_code == NULL) {
    error = MJS_FILE_READ_ERROR;
    mjs_prepend_errorf(mjs, error, "failed to read file \"%s\"", path);
    goto clean;
  }

  r = MJS_UNDEFINED;
  error = mjs_exec_internal(mjs, path, source_code, -1, &r);
  free(source_code);

clean:
  if (res != NULL) *res = r;
  return error;
}

mjs_err_t mjs_call(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                   mjs_val_t this_val, int nargs, ...) {
  va_list ap;
  int i;
  mjs_err_t ret;
  mjs_val_t *args = calloc(nargs, sizeof(mjs_val_t));
  va_start(ap, nargs);
  for (i = 0; i < nargs; i++) {
    args[i] = va_arg(ap, mjs_val_t);
  }
  va_end(ap);

  ret = mjs_apply(mjs, res, func, this_val, nargs, args);

  free(args);
  return ret;
}

mjs_err_t mjs_apply(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                    mjs_val_t this_val, int nargs, mjs_val_t *args) {
  mjs_val_t r, prev_this_val, retval_stack_idx, *resp;
  int i;

  if (!mjs_is_function(func) && !mjs_is_foreign(func) &&
      !mjs_is_ffi_sig(func)) {
    return mjs_set_errorf(mjs, MJS_TYPE_ERROR, "calling non-callable");
  }

  LOG(LL_VERBOSE_DEBUG, ("applying func %d", (int) mjs_get_func_addr(func)));

  prev_this_val = mjs->vals.this_obj;

  /* Push callable which will be later replaced with the return value */
  mjs_push(mjs, func);
  resp = vptr(&mjs->stack, -1);

  /* Remember index by which return value should be written */
  retval_stack_idx = mjs_mk_number(mjs, (double) mjs_stack_size(&mjs->stack));

  // Push all arguments
  for (i = 0; i < nargs; i++) {
    mjs_push(mjs, args[i]);
  }

  /* Push this value to arg_stack, call_stack_push_frame() expects that */
  push_mjs_val(&mjs->arg_stack, this_val);

  /* Push call stack frame, just like OP_CALL does that */
  call_stack_push_frame(mjs, MJS_BCODE_OFFSET_EXIT, retval_stack_idx);

  if (mjs_is_foreign(func)) {
    ((void (*) (struct mjs *)) mjs_get_ptr(mjs, func))(mjs);
    if (res != NULL) *res = *resp;
  } else if (mjs_is_ffi_sig(func)) {
    mjs_ffi_call2(mjs);
    if (res != NULL) *res = *resp;
  } else {
    size_t addr = mjs_get_func_addr(func);
    mjs_execute(mjs, addr, &r);
    if (res != NULL) *res = r;
  }

  /*
   * If there was an error, we need to restore frame and do the cleanup
   * which is otherwise done by OP_RETURN
   */
  if (mjs->error != MJS_OK) {
    call_stack_restore_frame(mjs);

    // Pop cell at which the returned value should've been written
    mjs_pop(mjs);
  }
  mjs->vals.this_obj = prev_this_val;

  return mjs->error;
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_ffi.c"
#endif

/* Amalgamated: #include "common/mg_str.h" */

/* Amalgamated: #include "mjs/src/ffi/ffi.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_exec.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

/*
 * on linux this is enabled only if __USE_GNU is defined, but we cannot set it
 * because dlfcn could have been included already.
 */
#ifndef RTLD_DEFAULT
#define RTLD_DEFAULT NULL
#endif

static ffi_fn_t *get_cb_impl_by_signature(const mjs_ffi_sig_t *sig);

/*
 * Data of the two related arguments: callback function pointer and the
 * userdata for it
 */
struct cbdata {
  /* JS callback function */
  mjs_val_t func;
  /* JS userdata */
  mjs_val_t userdata;

  /* index of the function pointer param */
  int8_t func_idx;
  /* index of the userdata param */
  int8_t userdata_idx;
};

void mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym) {
  mjs->dlsym = dlsym;
}

static mjs_ffi_ctype_t parse_cval_type(struct mjs *mjs, const char *s,
                                       const char *e) {
  struct mg_str ms = MG_NULL_STR;
  /* Trim leading and trailing whitespace */
  while (s < e && isspace((int) *s)) s++;
  while (e > s && isspace((int) e[-1])) e--;
  ms.p = s;
  ms.len = e - s;
  if (mg_vcmp(&ms, "void") == 0) {
    return MJS_FFI_CTYPE_NONE;
  } else if (mg_vcmp(&ms, "userdata") == 0) {
    return MJS_FFI_CTYPE_USERDATA;
  } else if (mg_vcmp(&ms, "int") == 0) {
    return MJS_FFI_CTYPE_INT;
  } else if (mg_vcmp(&ms, "bool") == 0) {
    return MJS_FFI_CTYPE_BOOL;
  } else if (mg_vcmp(&ms, "double") == 0) {
    return MJS_FFI_CTYPE_DOUBLE;
  } else if (mg_vcmp(&ms, "float") == 0) {
    return MJS_FFI_CTYPE_FLOAT;
  } else if (mg_vcmp(&ms, "char*") == 0 || mg_vcmp(&ms, "char *") == 0) {
    return MJS_FFI_CTYPE_CHAR_PTR;
  } else if (mg_vcmp(&ms, "void*") == 0 || mg_vcmp(&ms, "void *") == 0) {
    return MJS_FFI_CTYPE_VOID_PTR;
  } else if (mg_vcmp(&ms, "struct mg_str") == 0) {
    return MJS_FFI_CTYPE_STRUCT_MG_STR;
  } else if (mg_vcmp(&ms, "struct mg_str *") == 0 ||
             mg_vcmp(&ms, "struct mg_str*") == 0) {
    return MJS_FFI_CTYPE_STRUCT_MG_STR_PTR;
  } else {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "failed to parse val type \"%.*s\"",
                       (int) ms.len, ms.p);
    return MJS_FFI_CTYPE_INVALID;
  }
}

static const char *find_paren(const char *s, const char *e) {
  for (; s < e; s++) {
    if (*s == '(') return s;
  }
  return NULL;
}

static const char *find_closing_paren(const char *s, const char *e) {
  int nesting = 1;
  while (s < e) {
    if (*s == '(') {
      nesting++;
    } else if (*s == ')') {
      if (--nesting == 0) break;
    }
    s++;
  }
  return (s < e ? s : NULL);
}

MJS_PRIVATE mjs_err_t mjs_parse_ffi_signature(struct mjs *mjs, const char *s,
                                              int sig_len, mjs_ffi_sig_t *sig,
                                              enum ffi_sig_type sig_type) {
  mjs_err_t ret = MJS_OK;
  int vtidx = 0;
  const char *cur, *e, *tmp_e, *tmp;
  struct mg_str rt = MG_NULL_STR, fn = MG_NULL_STR, args = MG_NULL_STR;
  mjs_ffi_ctype_t val_type = MJS_FFI_CTYPE_INVALID;
  if (sig_len == ~0) {
    sig_len = strlen(s);
  }
  e = s + sig_len;

  mjs_ffi_sig_init(sig);

  /* Skip leading spaces */
  for (cur = s; cur < e && isspace((int) *cur); cur++)
    ;

  /* FInd the first set of parens */
  tmp_e = find_paren(cur, e);
  if (tmp_e == NULL || tmp_e - s < 2) {
    ret = MJS_TYPE_ERROR;
    mjs_prepend_errorf(mjs, ret, "1");
    goto clean;
  }
  tmp = find_closing_paren(tmp_e + 1, e);
  if (tmp == NULL) {
    ret = MJS_TYPE_ERROR;
    mjs_prepend_errorf(mjs, ret, "2");
    goto clean;
  }

  /* Now see if we have a second set of parens */
  args.p = find_paren(tmp + 1, e);
  if (args.p == NULL) {
    /* We don't - it's a regular function signature */
    fn.p = tmp_e - 1;
    while (fn.p > cur && isspace((int) *fn.p)) fn.p--;
    while (fn.p > cur && (isalnum((int) *fn.p) || *fn.p == '_')) {
      fn.p--;
      fn.len++;
    }
    fn.p++;
    rt.p = cur;
    rt.len = fn.p - rt.p;
    /* Stuff inside parens is args */
    args.p = tmp_e + 1;
    args.len = tmp - args.p;
  } else {
    /* We do - it's a function pointer, like void (*foo)(...).
     * Stuff inside the first pair of parens is the function name */
    fn.p = tmp + 1;
    fn.len = args.p - tmp;
    rt.p = cur;
    rt.len = tmp_e - rt.p;
    args.p++;
    tmp = find_closing_paren(args.p, e);
    if (tmp == NULL) {
      ret = MJS_TYPE_ERROR;
      mjs_prepend_errorf(mjs, ret, "3");
      goto clean;
    }
    args.len = tmp - args.p;
    /*
     * We ignore the name and leave sig->fn NULL here, but it will later be
     * set to the appropriate callback implementation.
     */
    sig->is_callback = 1;
  }

  val_type = parse_cval_type(mjs, rt.p, rt.p + rt.len);
  if (val_type == MJS_FFI_CTYPE_INVALID) {
    ret = mjs->error;
    goto clean;
  }
  mjs_ffi_sig_set_val_type(sig, vtidx++, val_type);

  /* Parse function name {{{ */
  if (!sig->is_callback) {
    char buf[100];
    if (mjs->dlsym == NULL) {
      ret = MJS_TYPE_ERROR;
      mjs_prepend_errorf(mjs, ret,
                         "resolver is not set, call mjs_set_ffi_resolver");
      goto clean;
    }

    snprintf(buf, sizeof(buf), "%.*s", (int) fn.len, fn.p);
    sig->fn = (ffi_fn_t *) mjs->dlsym(RTLD_DEFAULT, buf);
    if (sig->fn == NULL) {
      ret = MJS_TYPE_ERROR;
      mjs_prepend_errorf(mjs, ret, "dlsym('%s') failed", buf);
      goto clean;
    }
  } else {
    tmp_e = strchr(tmp_e, ')');
    if (tmp_e == NULL) {
      ret = MJS_TYPE_ERROR;
      goto clean;
    }
  }

  /* Advance cur to the beginning of the arg list */
  cur = tmp_e = args.p;

  /* Parse all args {{{ */
  while (tmp_e - args.p < (ptrdiff_t) args.len) {
    int level = 0; /* nested parens level */
    int is_fp = 0; /* set to 1 is current arg is a callback function ptr */
    tmp_e = cur;

    /* Advance tmp_e until the next arg separator */
    while (*tmp_e && (level > 0 || (*tmp_e != ',' && *tmp_e != ')'))) {
      switch (*tmp_e) {
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
      tmp_e++;
    }

    if (tmp_e == cur) break;

    /* Parse current arg */
    if (is_fp) {
      /* Current argument is a callback function pointer */
      if (sig->cb_sig != NULL) {
        /*
         * We already have parsed some callback argument. Currently we don't
         * support more than one callback argument, so, return error
         * TODO(dfrank): probably improve
         */
        ret = MJS_TYPE_ERROR;
        mjs_prepend_errorf(mjs, ret, "only one callback is allowed");
        goto clean;
      }

      sig->cb_sig = calloc(sizeof(*sig->cb_sig), 1);
      ret = mjs_parse_ffi_signature(mjs, cur, tmp_e - cur, sig->cb_sig,
                                    FFI_SIG_CALLBACK);
      if (ret != MJS_OK) {
        mjs_ffi_sig_free(sig->cb_sig);
        free(sig->cb_sig);
        sig->cb_sig = NULL;
        goto clean;
      }
      val_type = MJS_FFI_CTYPE_CALLBACK;
    } else {
      /* Some non-function argument */
      val_type = parse_cval_type(mjs, cur, tmp_e);
      if (val_type == MJS_FFI_CTYPE_INVALID) {
        /* parse_cval_type() has already set error message */
        ret = MJS_TYPE_ERROR;
        goto clean;
      }
    }

    if (!mjs_ffi_sig_set_val_type(sig, vtidx++, val_type)) {
      ret = MJS_TYPE_ERROR;
      mjs_prepend_errorf(mjs, ret, "too many callback args");
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
  /* }}} */

  /* Analyze the results and see if they are obviously wrong */
  mjs_ffi_sig_validate(mjs, sig, sig_type);
  if (!sig->is_valid) {
    ret = MJS_TYPE_ERROR;
    goto clean;
  }

  /* If the signature represents a callback, find the suitable implementation */
  if (sig->is_callback) {
    sig->fn = get_cb_impl_by_signature(sig);
    if (sig->fn == NULL) {
      ret = MJS_TYPE_ERROR;
      mjs_prepend_errorf(mjs, ret,
                         "the callback signature is valid, but there's "
                         "no existing callback implementation for it");
      goto clean;
    }
  }

clean:
  if (ret != MJS_OK) {
    mjs_prepend_errorf(mjs, ret, "bad ffi signature: \"%.*s\"", sig_len, s);
    sig->is_valid = 0;
  }
  return ret;
}

/* C callbacks implementation {{{ */

/* An argument or a return value for C callback impl */
union ffi_cb_data_val {
  void *p;
  uintptr_t w;
  double d;
  float f;
};

struct ffi_cb_data {
  union ffi_cb_data_val args[MJS_CB_ARGS_MAX_CNT];
};

static union ffi_cb_data_val ffi_cb_impl_generic(void *param,
                                                 struct ffi_cb_data *data) {
  struct mjs_ffi_cb_args *cbargs = (struct mjs_ffi_cb_args *) param;
  mjs_val_t *args, res = MJS_UNDEFINED;
  union ffi_cb_data_val ret;
  int i;
  struct mjs *mjs = cbargs->mjs;
  mjs_ffi_ctype_t return_ctype = MJS_FFI_CTYPE_NONE;
  mjs_err_t err;

  memset(&ret, 0, sizeof(ret));
  mjs_own(mjs, &res);

  /* There must be at least one argument: a userdata */
  assert(cbargs->sig.args_cnt > 0);

  /* Create JS arguments */
  args = calloc(1, sizeof(mjs_val_t) * cbargs->sig.args_cnt);
  for (i = 0; i < cbargs->sig.args_cnt; i++) {
    mjs_ffi_ctype_t val_type =
        cbargs->sig.val_types[i + 1 /* first val_type is return value type */];
    switch (val_type) {
      case MJS_FFI_CTYPE_USERDATA:
        args[i] = cbargs->userdata;
        break;
      case MJS_FFI_CTYPE_INT:
        args[i] = mjs_mk_number(mjs, (double) data->args[i].w);
        break;
      case MJS_FFI_CTYPE_BOOL:
        args[i] = mjs_mk_boolean(mjs, !!data->args[i].w);
        break;
      case MJS_FFI_CTYPE_CHAR_PTR: {
        const char *s = (char *) data->args[i].w;
        if (s == NULL) s = "";
        args[i] = mjs_mk_string(mjs, s, ~0, 1);
        break;
      }
      case MJS_FFI_CTYPE_VOID_PTR:
        args[i] = mjs_mk_foreign(mjs, (void *) data->args[i].w);
        break;
      case MJS_FFI_CTYPE_DOUBLE:
        args[i] = mjs_mk_number(mjs, data->args[i].d);
        break;
      case MJS_FFI_CTYPE_FLOAT:
        args[i] = mjs_mk_number(mjs, data->args[i].f);
        break;
      case MJS_FFI_CTYPE_STRUCT_MG_STR_PTR: {
        struct mg_str *s = (struct mg_str *) (void *) data->args[i].w;
        args[i] = mjs_mk_string(mjs, s->p, s->len, 1);
        break;
      }
      default:
        /* should never be here */
        LOG(LL_ERROR, ("unexpected val type for arg #%d: %d\n", i, val_type));
        abort();
    }
  }

  /*
   * save return ctype outside of `cbargs` before calling the callback, because
   * callback might call `ffi_cb_free()`, which will effectively invalidate
   * `cbargs`
   */
  return_ctype = cbargs->sig.val_types[0];

  /* Call JS function */
  LOG(LL_VERBOSE_DEBUG, ("calling JS callback void-void %d from C",
                         mjs_get_int(mjs, cbargs->func)));
  err = mjs_apply(mjs, &res, cbargs->func, MJS_UNDEFINED, cbargs->sig.args_cnt,
                  args);
  /*
   * cbargs might be invalidated by the callback (if it called ffi_cb_free), so
   * null it out
   */
  cbargs = NULL;
  if (err != MJS_OK) {
    /*
     * There's not much we can do about the error here; let's at least print it
     */
    mjs_print_error(mjs, stderr, "MJS callback error",
                    1 /* print_stack_trace */);

    goto clean;
  }

  /* Get return value, if needed */
  switch (return_ctype) {
    case MJS_FFI_CTYPE_NONE:
      /* do nothing */
      break;
    case MJS_FFI_CTYPE_INT:
      ret.w = mjs_get_int(mjs, res);
      break;
    case MJS_FFI_CTYPE_BOOL:
      ret.w = mjs_get_bool(mjs, res);
      break;
    case MJS_FFI_CTYPE_VOID_PTR:
      ret.p = mjs_get_ptr(mjs, res);
      break;
    case MJS_FFI_CTYPE_DOUBLE:
      ret.d = mjs_get_double(mjs, res);
      break;
    case MJS_FFI_CTYPE_FLOAT:
      ret.f = (float) mjs_get_double(mjs, res);
      break;
    default:
      /* should never be here */
      LOG(LL_ERROR, ("unexpected return val type %d\n", return_ctype));
      abort();
  }

clean:
  free(args);
  mjs_disown(mjs, &res);
  return ret;
}

static void ffi_init_cb_data_wwww(struct ffi_cb_data *data, uintptr_t w0,
                                  uintptr_t w1, uintptr_t w2, uintptr_t w3,
                                  uintptr_t w4, uintptr_t w5) {
  memset(data, 0, sizeof(*data));
  data->args[0].w = w0;
  data->args[1].w = w1;
  data->args[2].w = w2;
  data->args[3].w = w3;
  data->args[4].w = w4;
  data->args[5].w = w5;
}

static uintptr_t ffi_cb_impl_wpwwwww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w0, &data).w;
}

static uintptr_t ffi_cb_impl_wwpwwww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w1, &data).w;
}

static uintptr_t ffi_cb_impl_wwwpwww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w2, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwpww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w3, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwwpw(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w4, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwwwp(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w5, &data).w;
}

static uintptr_t ffi_cb_impl_wpd(uintptr_t w0, double d1) {
  struct ffi_cb_data data;

  memset(&data, 0, sizeof(data));
  data.args[0].w = w0;
  data.args[1].d = d1;

  return ffi_cb_impl_generic((void *) w0, &data).w;
}

static uintptr_t ffi_cb_impl_wdp(double d0, uintptr_t w1) {
  struct ffi_cb_data data;

  memset(&data, 0, sizeof(data));
  data.args[0].d = d0;
  data.args[1].w = w1;

  return ffi_cb_impl_generic((void *) w1, &data).w;
}
/* }}} */

static struct mjs_ffi_cb_args **ffi_get_matching(struct mjs_ffi_cb_args **plist,
                                                 mjs_val_t func,
                                                 mjs_val_t userdata) {
  for (; *plist != NULL; plist = &((*plist)->next)) {
    if ((*plist)->func == func && (*plist)->userdata == userdata) {
      break;
    }
  }
  return plist;
}

static ffi_fn_t *get_cb_impl_by_signature(const mjs_ffi_sig_t *sig) {
  if (sig->is_valid) {
    int i;
    int double_cnt = 0;
    int float_cnt = 0;
    int userdata_idx = 0 /* not a valid value: index 0 means return value */;

    for (i = 1 /*0th item is a return value*/; i < MJS_CB_SIGNATURE_MAX_SIZE;
         i++) {
      mjs_ffi_ctype_t type = sig->val_types[i];
      switch (type) {
        case MJS_FFI_CTYPE_DOUBLE:
          double_cnt++;
          break;
        case MJS_FFI_CTYPE_FLOAT:
          float_cnt++;
          break;
        case MJS_FFI_CTYPE_USERDATA:
          assert(userdata_idx == 0); /* Otherwise is_valid should be 0 */
          userdata_idx = i;
          break;
        default:
          break;
      }
    }

    if (float_cnt > 0) {
      /* TODO(dfrank): add support for floats in callbacks */
      return NULL;
    }

    assert(userdata_idx > 0); /* Otherwise is_valid should be 0 */

    if (sig->args_cnt <= MJS_CB_ARGS_MAX_CNT) {
      if (mjs_ffi_is_regular_word_or_void(sig->val_types[0])) {
        /* Return type is a word or void */
        switch (double_cnt) {
          case 0:
            /* No double arguments */
            switch (userdata_idx) {
              case 1:
                return (ffi_fn_t *) ffi_cb_impl_wpwwwww;
              case 2:
                return (ffi_fn_t *) ffi_cb_impl_wwpwwww;
              case 3:
                return (ffi_fn_t *) ffi_cb_impl_wwwpwww;
              case 4:
                return (ffi_fn_t *) ffi_cb_impl_wwwwpww;
              case 5:
                return (ffi_fn_t *) ffi_cb_impl_wwwwwpw;
              case 6:
                return (ffi_fn_t *) ffi_cb_impl_wwwwwwp;
              default:
                /* should never be here */
                abort();
            }
            break;
          case 1:
            /* 1 double argument */
            switch (userdata_idx) {
              case 1:
                return (ffi_fn_t *) ffi_cb_impl_wpd;
              case 2:
                return (ffi_fn_t *) ffi_cb_impl_wdp;
            }
            break;
        }
      }
    } else {
      /* Too many arguments for the built-in callback impls */
      /* TODO(dfrank): add support for custom app-dependent resolver */
    }
  }

  return NULL;
}

MJS_PRIVATE mjs_val_t mjs_ffi_sig_to_value(struct mjs_ffi_sig *psig) {
  if (psig == NULL) {
    return MJS_NULL;
  } else {
    return mjs_legit_pointer_to_value(psig) | MJS_TAG_FUNCTION_FFI;
  }
}

MJS_PRIVATE int mjs_is_ffi_sig(mjs_val_t v) {
  return (v & MJS_TAG_MASK) == MJS_TAG_FUNCTION_FFI;
}

MJS_PRIVATE struct mjs_ffi_sig *mjs_get_ffi_sig_struct(mjs_val_t v) {
  struct mjs_ffi_sig *ret = NULL;
  assert(mjs_is_ffi_sig(v));
  ret = (struct mjs_ffi_sig *) get_ptr(v);
  return ret;
}

MJS_PRIVATE mjs_val_t mjs_mk_ffi_sig(struct mjs *mjs) {
  struct mjs_ffi_sig *psig = new_ffi_sig(mjs);
  mjs_ffi_sig_init(psig);
  return mjs_ffi_sig_to_value(psig);
}

MJS_PRIVATE void mjs_ffi_sig_destructor(struct mjs *mjs, void *psig) {
  mjs_ffi_sig_free((mjs_ffi_sig_t *) psig);
  (void) mjs;
}

MJS_PRIVATE mjs_err_t mjs_ffi_call(struct mjs *mjs) {
  mjs_err_t e = MJS_OK;
  const char *sig_str = NULL;
  mjs_val_t sig_str_v = mjs_arg(mjs, 0);
  mjs_val_t ret_v = MJS_UNDEFINED;
  struct mjs_ffi_sig *psig = mjs_get_ffi_sig_struct(mjs_mk_ffi_sig(mjs));
  size_t sig_str_len;

  sig_str = mjs_get_string(mjs, &sig_str_v, &sig_str_len);
  e = mjs_parse_ffi_signature(mjs, sig_str, sig_str_len, psig, FFI_SIG_FUNC);
  if (e != MJS_OK) goto clean;
  ret_v = mjs_ffi_sig_to_value(psig);

clean:
  mjs_return(mjs, ret_v);
  return e;
}

MJS_PRIVATE mjs_err_t mjs_ffi_call2(struct mjs *mjs) {
  mjs_err_t ret = MJS_OK;
  mjs_ffi_sig_t *psig = NULL;
  mjs_ffi_ctype_t rtype;
  mjs_val_t sig_v = *vptr(&mjs->stack, mjs_getretvalpos(mjs));

  int i, nargs;
  struct ffi_arg res;
  struct ffi_arg args[FFI_MAX_ARGS_CNT];
  struct cbdata cbdata;

  /* TODO(dfrank): support multiple callbacks */
  mjs_val_t resv = mjs_mk_undefined();

  /*
   * String arguments, needed to support short strings which are packed into
   * mjs_val_t itself
   */
  mjs_val_t argvs[FFI_MAX_ARGS_CNT];
  struct mg_str argvmgstr[FFI_MAX_ARGS_CNT];

  if (mjs_is_ffi_sig(sig_v)) {
    psig = mjs_get_ffi_sig_struct(sig_v);
  } else {
    ret = MJS_TYPE_ERROR;
    mjs_prepend_errorf(mjs, ret, "non-ffi-callable value");
    goto clean;
  }

  memset(&cbdata, 0, sizeof(cbdata));
  cbdata.func_idx = -1;
  cbdata.userdata_idx = -1;

  rtype = psig->val_types[0];

  switch (rtype) {
    case MJS_FFI_CTYPE_DOUBLE:
      res.ctype = FFI_CTYPE_DOUBLE;
      break;
    case MJS_FFI_CTYPE_FLOAT:
      res.ctype = FFI_CTYPE_FLOAT;
      break;
    case MJS_FFI_CTYPE_BOOL:
      res.ctype = FFI_CTYPE_BOOL;
      break;
    case MJS_FFI_CTYPE_USERDATA:
    case MJS_FFI_CTYPE_INT:
    case MJS_FFI_CTYPE_CHAR_PTR:
    case MJS_FFI_CTYPE_VOID_PTR:
    case MJS_FFI_CTYPE_NONE:
      res.ctype = FFI_CTYPE_WORD;
      break;

    case MJS_FFI_CTYPE_INVALID:
      ret = MJS_TYPE_ERROR;
      mjs_prepend_errorf(mjs, ret, "wrong ffi return type");
      goto clean;
  }
  res.v.i = 0;

  nargs =
      mjs_stack_size(&mjs->stack) - mjs_get_int(mjs, vtop(&mjs->call_stack));

  if (nargs != psig->args_cnt) {
    ret = MJS_TYPE_ERROR;
    mjs_prepend_errorf(mjs, ret, "got %d actuals, but function takes %d args",
                       nargs, psig->args_cnt);
    goto clean;
  }

  for (i = 0; i < nargs; i++) {
    mjs_val_t arg = mjs_arg(mjs, i);

    switch (psig->val_types[1 /* retval type */ + i]) {
      case MJS_FFI_CTYPE_NONE:
        /*
         * Void argument: in any case, it's an error, because if C function
         * takes no arguments, then the FFI-ed JS function should be called
         * without any arguments, and thus we'll not face "void" here.
         */
        ret = MJS_TYPE_ERROR;
        if (i == 0) {
          /* FFI signature is correct, but invocation is wrong */
          mjs_prepend_errorf(mjs, ret, "ffi-ed function takes no arguments");
        } else {
          /*
           * FFI signature is wrong: we can't have "void" as a non-first
           * "argument"
           */
          mjs_prepend_errorf(mjs, ret, "bad ffi arg #%d type: \"void\"", i);
        }

        goto clean;
      case MJS_FFI_CTYPE_USERDATA:
        /* Userdata for the callback */
        if (cbdata.userdata_idx != -1) {
          ret = MJS_TYPE_ERROR;
          mjs_prepend_errorf(mjs, ret, "two or more userdata args: #%d and %d",
                             cbdata.userdata_idx, i);

          goto clean;
        }
        cbdata.userdata = arg;
        cbdata.userdata_idx = i;
        break;
      case MJS_FFI_CTYPE_INT: {
        int intval = 0;
        if (mjs_is_number(arg)) {
          intval = mjs_get_int(mjs, arg);
        } else if (mjs_is_boolean(arg)) {
          intval = mjs_get_bool(mjs, arg);
        } else {
          ret = MJS_TYPE_ERROR;
          mjs_prepend_errorf(
              mjs, ret, "actual arg #%d is not an int (the type idx is: %s)", i,
              mjs_typeof(arg));
        }
        ffi_set_word(&args[i], intval);
      } break;
      case MJS_FFI_CTYPE_STRUCT_MG_STR_PTR: {
        if (!mjs_is_string(arg)) {
          ret = MJS_TYPE_ERROR;
          mjs_prepend_errorf(
              mjs, ret, "actual arg #%d is not a string (the type idx is: %s)",
              i, mjs_typeof(arg));
          goto clean;
        }
        argvs[i] = arg;
        argvmgstr[i].p = mjs_get_string(mjs, &argvs[i], &argvmgstr[i].len);
        /*
         * String argument should be saved separately in order to support
         * short strings (which are packed into mjs_val_t itself)
         */
        ffi_set_ptr(&args[i], (void *) &argvmgstr[i]);
        break;
      }
      case MJS_FFI_CTYPE_BOOL: {
        int intval = 0;
        if (mjs_is_number(arg)) {
          intval = !!mjs_get_int(mjs, arg);
        } else if (mjs_is_boolean(arg)) {
          intval = mjs_get_bool(mjs, arg);
        } else {
          ret = MJS_TYPE_ERROR;
          mjs_prepend_errorf(
              mjs, ret, "actual arg #%d is not a bool (the type idx is: %s)", i,
              mjs_typeof(arg));
        }
        ffi_set_word(&args[i], intval);
      } break;
      case MJS_FFI_CTYPE_DOUBLE:
        ffi_set_double(&args[i], mjs_get_double(mjs, arg));
        break;
      case MJS_FFI_CTYPE_FLOAT:
        ffi_set_float(&args[i], (float) mjs_get_double(mjs, arg));
        break;
      case MJS_FFI_CTYPE_CHAR_PTR: {
        size_t s;
        if (mjs_is_string(arg)) {
          /*
           * String argument should be saved separately in order to support
           * short strings (which are packed into mjs_val_t itself)
           */
          argvs[i] = arg;
          ffi_set_ptr(&args[i], (void *) mjs_get_string(mjs, &argvs[i], &s));
        } else if (mjs_is_null(arg)) {
          ffi_set_ptr(&args[i], NULL);
        } else {
          ret = MJS_TYPE_ERROR;
          mjs_prepend_errorf(
              mjs, ret, "actual arg #%d is not a string (the type idx is: %s)",
              i, mjs_typeof(arg));
          goto clean;
        }
      } break;
      case MJS_FFI_CTYPE_VOID_PTR:
        if (mjs_is_string(arg)) {
          size_t n;
          /*
           * String argument should be saved separately in order to support
           * short strings (which are packed into mjs_val_t itself)
           */
          argvs[i] = arg;
          ffi_set_ptr(&args[i], (void *) mjs_get_string(mjs, &argvs[i], &n));
        } else if (mjs_is_foreign(arg)) {
          ffi_set_ptr(&args[i], (void *) mjs_get_ptr(mjs, arg));
        } else if (mjs_is_null(arg)) {
          ffi_set_ptr(&args[i], NULL);
        } else {
          ret = MJS_TYPE_ERROR;
          mjs_prepend_errorf(mjs, ret, "actual arg #%d is not a ptr", i);
          goto clean;
        }
        break;
      case MJS_FFI_CTYPE_CALLBACK:
        if (mjs_is_function(arg) || mjs_is_foreign(arg) ||
            mjs_is_ffi_sig(arg)) {
          /*
           * Current argument is a callback function pointer: remember the given
           * JS function and the argument index
           */
          cbdata.func = arg;
          cbdata.func_idx = i;
        } else {
          ret = MJS_TYPE_ERROR;
          mjs_prepend_errorf(mjs, ret,
                             "actual arg #%d is not a function, but %s", i,
                             mjs_stringify_type((enum mjs_type) arg));
          goto clean;
        }
        break;
      case MJS_FFI_CTYPE_INVALID:
        /* parse_cval_type() has already set a more detailed error */
        ret = MJS_TYPE_ERROR;
        mjs_prepend_errorf(mjs, ret, "wrong arg type");
        goto clean;
      default:
        abort();
        break;
    }
  }

  if (cbdata.userdata_idx >= 0 && cbdata.func_idx >= 0) {
    struct mjs_ffi_cb_args *cbargs = NULL;
    struct mjs_ffi_cb_args **pitem = NULL;

    /* the function takes a callback */

    /*
     * Get cbargs: either reuse the existing one (if the matching item exists),
     * or create a new one.
     */
    pitem = ffi_get_matching(&mjs->ffi_cb_args, cbdata.func, cbdata.userdata);
    if (*pitem == NULL) {
      /* No matching cbargs item; we need to add a new one */
      cbargs = calloc(1, sizeof(*cbargs));
      cbargs->mjs = mjs;
      cbargs->func = cbdata.func;
      cbargs->userdata = cbdata.userdata;
      mjs_ffi_sig_copy(&cbargs->sig, psig->cb_sig);

      /* Establish a link to the newly allocated item */
      *pitem = cbargs;
    } else {
      /* Found matching item: reuse it */
      cbargs = *pitem;
    }

    {
      union {
        ffi_fn_t *fn;
        void *p;
      } u;
      u.fn = psig->cb_sig->fn;
      ffi_set_ptr(&args[cbdata.func_idx], u.p);
      ffi_set_ptr(&args[cbdata.userdata_idx], cbargs);
    }
  } else if (!(cbdata.userdata_idx == -1 && cbdata.func_idx == -1)) {
    /*
     * incomplete signature: it contains either the function pointer or
     * userdata. It should contain both or none.
     *
     * It should be handled in mjs_parse_ffi_signature().
     */
    abort();
  }

  ffi_call(psig->fn, nargs, &res, args);

  switch (rtype) {
    case MJS_FFI_CTYPE_CHAR_PTR: {
      const char *s = (const char *) (uintptr_t) res.v.i;
      if (s != NULL) {
        resv = mjs_mk_string(mjs, s, ~0, 1);
      } else {
        resv = MJS_NULL;
      }
      break;
    }
    case MJS_FFI_CTYPE_VOID_PTR:
      resv = mjs_mk_foreign(mjs, (void *) (uintptr_t) res.v.i);
      break;
    case MJS_FFI_CTYPE_INT:
      resv = mjs_mk_number(mjs, (int) res.v.i);
      break;
    case MJS_FFI_CTYPE_BOOL:
      resv = mjs_mk_boolean(mjs, !!res.v.i);
      break;
    case MJS_FFI_CTYPE_DOUBLE:
      resv = mjs_mk_number(mjs, res.v.d);
      break;
    case MJS_FFI_CTYPE_FLOAT:
      resv = mjs_mk_number(mjs, res.v.f);
      break;
    default:
      resv = mjs_mk_undefined();
      break;
  }

clean:
  /*
   * If there was some error, prepend an error message with the subject
   * signature
   */
  if (ret != MJS_OK) {
    mjs_prepend_errorf(mjs, ret, "failed to call FFIed function");
    /* TODO(dfrank) stringify mjs_ffi_sig_t in some human-readable format */
  }
  mjs_return(mjs, resv);

  return ret;
}

/*
 * TODO(dfrank): make it return boolean (when booleans are supported), instead
 * of a number
 */
MJS_PRIVATE void mjs_ffi_cb_free(struct mjs *mjs) {
  mjs_val_t ret = mjs_mk_number(mjs, 0);
  mjs_val_t func = mjs_arg(mjs, 0);
  mjs_val_t userdata = mjs_arg(mjs, 1);

  if (mjs_is_function(func)) {
    struct mjs_ffi_cb_args **pitem =
        ffi_get_matching(&mjs->ffi_cb_args, func, userdata);
    if (*pitem != NULL) {
      /* Found matching item: remove it from the linked list, and free */
      struct mjs_ffi_cb_args *cbargs = *pitem;
      *pitem = cbargs->next;
      mjs_ffi_sig_free(&cbargs->sig);
      free(cbargs);
      ret = mjs_mk_number(mjs, 1);
    }
  } else {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing argument 'func'");
  }

  mjs_return(mjs, ret);
}

void mjs_ffi_args_free_list(struct mjs *mjs) {
  ffi_cb_args_t *next = mjs->ffi_cb_args;

  while (next != NULL) {
    ffi_cb_args_t *cur = next;
    next = next->next;
    free(cur);
  }
}

MJS_PRIVATE void mjs_ffi_sig_init(mjs_ffi_sig_t *sig) {
  memset(sig, 0, sizeof(*sig));
}

MJS_PRIVATE void mjs_ffi_sig_copy(mjs_ffi_sig_t *to,
                                  const mjs_ffi_sig_t *from) {
  memcpy(to, from, sizeof(*to));
  if (from->cb_sig != NULL) {
    to->cb_sig = calloc(sizeof(*to->cb_sig), 1);
    mjs_ffi_sig_copy(to->cb_sig, from->cb_sig);
  }
}

MJS_PRIVATE void mjs_ffi_sig_free(mjs_ffi_sig_t *sig) {
  if (sig->cb_sig != NULL) {
    free(sig->cb_sig);
    sig->cb_sig = NULL;
  }
}

MJS_PRIVATE int mjs_ffi_sig_set_val_type(mjs_ffi_sig_t *sig, int idx,
                                         mjs_ffi_ctype_t type) {
  if (idx < MJS_CB_SIGNATURE_MAX_SIZE) {
    sig->val_types[idx] = type;
    return 1;
  } else {
    /* Index is too large */
    return 0;
  }
}

MJS_PRIVATE int mjs_ffi_sig_validate(struct mjs *mjs, mjs_ffi_sig_t *sig,
                                     enum ffi_sig_type sig_type) {
  int ret = 0;
  int i;
  int callback_idx = 0;
  int userdata_idx = 0;

  sig->is_valid = 0;

  switch (sig_type) {
    case FFI_SIG_FUNC:
      /* Make sure return type is fine */
      if (sig->val_types[0] != MJS_FFI_CTYPE_NONE &&
          sig->val_types[0] != MJS_FFI_CTYPE_INT &&
          sig->val_types[0] != MJS_FFI_CTYPE_BOOL &&
          sig->val_types[0] != MJS_FFI_CTYPE_DOUBLE &&
          sig->val_types[0] != MJS_FFI_CTYPE_FLOAT &&
          sig->val_types[0] != MJS_FFI_CTYPE_VOID_PTR &&
          sig->val_types[0] != MJS_FFI_CTYPE_CHAR_PTR) {
        mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "invalid return value type");
        goto clean;
      }
      break;
    case FFI_SIG_CALLBACK:
      /* Make sure return type is fine */
      if (sig->val_types[0] != MJS_FFI_CTYPE_NONE &&
          sig->val_types[0] != MJS_FFI_CTYPE_INT &&
          sig->val_types[0] != MJS_FFI_CTYPE_BOOL &&
          sig->val_types[0] != MJS_FFI_CTYPE_DOUBLE &&
          sig->val_types[0] != MJS_FFI_CTYPE_FLOAT &&
          sig->val_types[0] != MJS_FFI_CTYPE_VOID_PTR) {
        mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "invalid return value type");
        goto clean;
      }
  }

  /* Handle argument types */
  for (i = 1; i < MJS_CB_SIGNATURE_MAX_SIZE; i++) {
    mjs_ffi_ctype_t type = sig->val_types[i];
    switch (type) {
      case MJS_FFI_CTYPE_USERDATA:
        if (userdata_idx != 0) {
          /* There must be at most one userdata arg, but we have more */
          mjs_prepend_errorf(mjs, MJS_TYPE_ERROR,
                             "more than one userdata arg: #%d and #%d",
                             (userdata_idx - 1), (i - 1));
          goto clean;
        }
        userdata_idx = i;
        break;
      case MJS_FFI_CTYPE_CALLBACK:
        switch (sig_type) {
          case FFI_SIG_FUNC:
            break;
          case FFI_SIG_CALLBACK:
            mjs_prepend_errorf(mjs, MJS_TYPE_ERROR,
                               "callback can't take another callback");
            goto clean;
        }
        callback_idx = i;
        break;
      case MJS_FFI_CTYPE_INT:
      case MJS_FFI_CTYPE_BOOL:
      case MJS_FFI_CTYPE_VOID_PTR:
      case MJS_FFI_CTYPE_CHAR_PTR:
      case MJS_FFI_CTYPE_STRUCT_MG_STR_PTR:
      case MJS_FFI_CTYPE_DOUBLE:
      case MJS_FFI_CTYPE_FLOAT:
        /* Do nothing */
        break;
      case MJS_FFI_CTYPE_NONE:
        /* No more arguments */
        goto args_over;
      default:
        mjs_prepend_errorf(mjs, MJS_INTERNAL_ERROR, "invalid ffi_ctype: %d",
                           type);
        goto clean;
    }

    sig->args_cnt++;
  }
args_over:

  switch (sig_type) {
    case FFI_SIG_FUNC:
      if (!((callback_idx > 0 && userdata_idx > 0) ||
            (callback_idx == 0 && userdata_idx == 0))) {
        mjs_prepend_errorf(mjs, MJS_TYPE_ERROR,
                           "callback and userdata should be either both "
                           "present or both absent");
        goto clean;
      }
      break;
    case FFI_SIG_CALLBACK:
      if (userdata_idx == 0) {
        /* No userdata arg */
        mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "no userdata arg");
        goto clean;
      }
      break;
  }

  ret = 1;

clean:
  if (ret) {
    sig->is_valid = 1;
  }
  return ret;
}

MJS_PRIVATE int mjs_ffi_is_regular_word(mjs_ffi_ctype_t type) {
  switch (type) {
    case MJS_FFI_CTYPE_INT:
    case MJS_FFI_CTYPE_BOOL:
      return 1;
    default:
      return 0;
  }
}

MJS_PRIVATE int mjs_ffi_is_regular_word_or_void(mjs_ffi_ctype_t type) {
  return (type == MJS_FFI_CTYPE_NONE || mjs_ffi_is_regular_word(type));
}

#ifdef _WIN32
void *dlsym(void *handle, const char *name) {
  static HANDLE msvcrt_dll;
  void *sym = NULL;
  if (msvcrt_dll == NULL) msvcrt_dll = GetModuleHandle("msvcrt.dll");
  if ((sym = GetProcAddress(GetModuleHandle(NULL), name)) == NULL) {
    sym = GetProcAddress(msvcrt_dll, name);
  }
  return sym;
}
#elif !defined(__unix__) && !defined(__APPLE__)
void *dlsym(void *handle, const char *name) {
  (void) handle;
  (void) name;
  return NULL;
}
#endif
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_gc.c"
#endif

#include <stdio.h>

/* Amalgamated: #include "common/cs_varint.h" */
/* Amalgamated: #include "common/mbuf.h" */

/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_ffi.h" */
/* Amalgamated: #include "mjs/src/mjs_gc.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */

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

static struct gc_block *gc_new_block(struct gc_arena *a, size_t size);
static void gc_free_block(struct gc_block *b);
static void gc_mark_mbuf_pt(struct mjs *mjs, const struct mbuf *mbuf);

MJS_PRIVATE struct mjs_object *new_object(struct mjs *mjs) {
  return (struct mjs_object *) gc_alloc_cell(mjs, &mjs->object_arena);
}

MJS_PRIVATE struct mjs_property *new_property(struct mjs *mjs) {
  return (struct mjs_property *) gc_alloc_cell(mjs, &mjs->property_arena);
}

MJS_PRIVATE struct mjs_ffi_sig *new_ffi_sig(struct mjs *mjs) {
  return (struct mjs_ffi_sig *) gc_alloc_cell(mjs, &mjs->ffi_sig_arena);
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

#if MJS_MEMORY_STATS
  a->allocations++;
  a->alive++;
#endif

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
#if MJS_MEMORY_STATS
  a->alive = 0;
#endif

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
#if MJS_MEMORY_STATS
        a->alive++;
#endif
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
#if MJS_MEMORY_STATS
        a->garbage++;
#endif
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

/* Mark an FFI signature */
static void gc_mark_ffi_sig(struct mjs *mjs, mjs_val_t *v) {
  struct mjs_ffi_sig *psig;

  assert(mjs_is_ffi_sig(*v));

  psig = mjs_get_ffi_sig_struct(*v);

  /*
   * we treat all object like things like objects but they might be functions,
   * gc_check_val checks the appropriate arena per actual value type.
   */
  if (!gc_check_val(mjs, *v)) {
    abort();
  }

  if (MARKED(psig)) return;

  MARK(psig);
}

/* Mark an object */
static void gc_mark_object(struct mjs *mjs, mjs_val_t *v) {
  struct mjs_object *obj_base;
  struct mjs_property *prop;
  struct mjs_property *next;

  assert(mjs_is_object(*v));

  obj_base = get_object_struct(*v);

  /*
   * we treat all object like things like objects but they might be functions,
   * gc_check_val checks the appropriate arena per actual value type.
   */
  if (!gc_check_val(mjs, *v)) {
    abort();
  }

  if (MARKED(obj_base)) return;

  /* mark object itself, and its properties */
  for ((prop = obj_base->properties), MARK(obj_base); prop != NULL;
       prop = next) {
    if (!gc_check_ptr(&mjs->property_arena, prop)) {
      abort();
    }

    gc_mark(mjs, &prop->name);
    gc_mark(mjs, &prop->value);

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

/* Mark a string value */
static void gc_mark_string(struct mjs *mjs, mjs_val_t *v) {
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

  assert((*v & MJS_TAG_MASK) == MJS_TAG_STRING_O);

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

MJS_PRIVATE void gc_mark(struct mjs *mjs, mjs_val_t *v) {
  if (mjs_is_object(*v)) {
    gc_mark_object(mjs, v);
  }
  if (mjs_is_ffi_sig(*v)) {
    gc_mark_ffi_sig(mjs, v);
  }
  if ((*v & MJS_TAG_MASK) == MJS_TAG_STRING_O) {
    gc_mark_string(mjs, v);
  }
}

MJS_PRIVATE uint64_t gc_string_mjs_val_to_offset(mjs_val_t v) {
  return (((uint64_t)(uintptr_t) get_ptr(v)) & ~MJS_TAG_MASK);
}

MJS_PRIVATE mjs_val_t gc_string_val_from_offset(uint64_t s) {
  return s | MJS_TAG_STRING_O;
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
      len = cs_varint_decode_unsafe((unsigned char *) &h, &llen);
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
      len = cs_varint_decode_unsafe((unsigned char *) p, &llen);
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
    gc_mark(mjs, vp);
  }
}

/*
 * mark an mbuf containing *pointers* to `mjs_val_t` values
 */
static void gc_mark_mbuf_pt(struct mjs *mjs, const struct mbuf *mbuf) {
  mjs_val_t **vp;
  for (vp = (mjs_val_t **) mbuf->buf; (char *) vp < mbuf->buf + mbuf->len;
       vp++) {
    gc_mark(mjs, *vp);
  }
}

/*
 * mark an mbuf containing `mjs_val_t` values (*not pointers* to them)
 */
static void gc_mark_mbuf_val(struct mjs *mjs, const struct mbuf *mbuf) {
  gc_mark_val_array(mjs, (mjs_val_t *) mbuf->buf,
                    mbuf->len / sizeof(mjs_val_t));
}

static void gc_mark_ffi_cbargs_list(struct mjs *mjs, ffi_cb_args_t *cbargs) {
  for (; cbargs != NULL; cbargs = cbargs->next) {
    gc_mark(mjs, &cbargs->func);
    gc_mark(mjs, &cbargs->userdata);
  }
}

/* Perform garbage collection */
void mjs_gc(struct mjs *mjs, int full) {
  gc_mark_val_array(mjs, (mjs_val_t *) &mjs->vals,
                    sizeof(mjs->vals) / sizeof(mjs_val_t));

  gc_mark_mbuf_pt(mjs, &mjs->owned_values);
  gc_mark_mbuf_val(mjs, &mjs->scopes);
  gc_mark_mbuf_val(mjs, &mjs->stack);
  gc_mark_mbuf_val(mjs, &mjs->call_stack);

  gc_mark_ffi_cbargs_list(mjs, mjs->ffi_cb_args);

  gc_compact_strings(mjs);

  gc_sweep(mjs, &mjs->object_arena, 0);
  gc_sweep(mjs, &mjs->property_arena, 0);
  gc_sweep(mjs, &mjs->ffi_sig_arena, 0);

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
  if (mjs_is_ffi_sig(v)) {
    return gc_check_ptr(&mjs->ffi_sig_arena, mjs_get_ffi_sig_struct(v));
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
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_json.c"
#endif

/* Amalgamated: #include "common/str_util.h" */
/* Amalgamated: #include "frozen.h" */
/* Amalgamated: #include "mjs/src/mjs_array.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_conversion.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */

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
  char *limit = buf + size;
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

  if (buf < limit) {
    *buf = '\0';
  } else if (size != 0) {
    /*
     * There is no room for the NULL char, but the size wasn't zero, so we can
     * safely put NULL in the previous byte
     */
    *(buf - 1) = '\0';
  }
  return i;
}

MJS_PRIVATE mjs_err_t to_json_or_debug(struct mjs *mjs, mjs_val_t v, char *buf,
                                       size_t size, size_t *res_len,
                                       uint8_t is_debug) {
  mjs_val_t el;
  char *vp;
  mjs_err_t rcode = MJS_OK;
  size_t len = 0;
  /*
   * TODO(dfrank) : also push all `mjs_val_t`s that are declared below
   */

  if (size > 0) *buf = '\0';

  if (!is_debug && should_skip_for_json(mjs_get_type(v))) {
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

  switch (mjs_get_type(v)) {
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

    case MJS_TYPE_OBJECT_FUNCTION:
    case MJS_TYPE_OBJECT_GENERIC: {
      char *b = buf;
      struct mjs_property *prop = NULL;
      struct mjs_object *o = NULL;

      mbuf_append(&mjs->json_visited_stack, (char *) &v, sizeof(v));
      b += c_snprintf(b, BUF_LEFT(size, b - buf), "{");
      o = get_object_struct(v);
      for (prop = o->properties; prop != NULL; prop = prop->next) {
        size_t n;
        const char *s;
        if (!is_debug && should_skip_for_json(mjs_get_type(prop->value))) {
          continue;
        }
        if (b - buf != 1) { /* Not the first property to be printed */
          b += c_snprintf(b, BUF_LEFT(size, b - buf), ",");
        }
        s = mjs_get_string(mjs, &prop->name, &n);
        b += c_snprintf(b, BUF_LEFT(size, b - buf), "\"%.*s\":", (int) n, s);
        {
          size_t tmp = 0;
          rcode = to_json_or_debug(mjs, prop->value, b, BUF_LEFT(size, b - buf),
                                   &tmp, is_debug);
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
          if (!is_debug && should_skip_for_json(mjs_get_type(el))) {
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

MJS_PRIVATE mjs_err_t mjs_json_stringify(struct mjs *mjs, mjs_val_t v,
                                         char *buf, size_t size, char **res) {
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
  enum mjs_err rcode;
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
    case JSON_TYPE_STRING: {
      char *dst;
      if (token->len > 0 && (dst = malloc(token->len)) != NULL) {
        int len = json_unescape(token->ptr, token->len, dst, token->len);
        if (len < 0) {
          mjs_prepend_errorf(ctx->mjs, MJS_TYPE_ERROR, "invalid JSON string");
          break;
        }
        v = mjs_mk_string(ctx->mjs, dst, len, 1 /* copy */);
        free(dst);
      } else {
        /*
         * This branch is for 0-len strings, and for malloc errors
         * TODO(lsm): on malloc error, propagate the error upstream
         */
        v = mjs_mk_string(ctx->mjs, "", 0, 1 /* copy */);
      }
      break;
    }
    case JSON_TYPE_NUMBER:
      v = mjs_mk_number(ctx->mjs, strtod(token->ptr, NULL));
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
        int idx = (int) strtod(name, NULL);
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

MJS_PRIVATE mjs_err_t
mjs_json_parse(struct mjs *mjs, const char *str, size_t len, mjs_val_t *res) {
  struct json_parse_ctx *ctx =
      (struct json_parse_ctx *) calloc(sizeof(struct json_parse_ctx), 1);
  int json_res;
  enum mjs_err rcode = MJS_OK;

  ctx->mjs = mjs;
  ctx->result = MJS_UNDEFINED;
  ctx->frame = NULL;
  ctx->rcode = MJS_OK;

  mjs_own(mjs, &ctx->result);

  {
    /*
     * We have to reallocate the buffer before invoking json_walk, because
     * frozen_cb can create new strings, which can result in the reallocation
     * of mjs string mbuf, invalidating the `str` pointer.
     */
    char *stmp = malloc(len);
    memcpy(stmp, str, len);
    json_res = json_walk(stmp, len, frozen_cb, ctx);
    free(stmp);
    stmp = NULL;

    /* str might have been invalidated, so null it out */
    str = NULL;
  }

  if (ctx->rcode != MJS_OK) {
    rcode = ctx->rcode;
    mjs_prepend_errorf(mjs, rcode, "invalid JSON string");
  } else if (json_res < 0) {
    /* There was an error during parsing */
    rcode = MJS_TYPE_ERROR;
    mjs_prepend_errorf(mjs, rcode, "invalid JSON string");
  } else {
    /* Expression is parsed successfully */
    *res = ctx->result;

    /* There should be no allocated frames */
    assert(ctx->frame == NULL);
  }

  if (rcode != MJS_OK) {
    /* There might be some allocated frames in case of malformed JSON */
    while (ctx->frame != NULL) {
      ctx->frame = free_json_frame(ctx, ctx->frame);
    }
  }

  mjs_disown(mjs, &ctx->result);
  free(ctx);

  return rcode;
}

MJS_PRIVATE void mjs_op_json_stringify(struct mjs *mjs) {
  mjs_val_t ret = MJS_UNDEFINED;
  mjs_val_t val = mjs_arg(mjs, 0);

  if (mjs_nargs(mjs) < 1) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing a value to stringify");
  } else {
    char *p = NULL;
    if (mjs_json_stringify(mjs, val, NULL, 0, &p) == MJS_OK) {
      ret = mjs_mk_string(mjs, p, ~0, 1 /* copy */);
      free(p);
    }
  }

  mjs_return(mjs, ret);
}

MJS_PRIVATE void mjs_op_json_parse(struct mjs *mjs) {
  mjs_val_t ret = MJS_UNDEFINED;
  mjs_val_t arg0 = mjs_arg(mjs, 0);

  if (mjs_is_string(arg0)) {
    size_t len;
    const char *str = mjs_get_string(mjs, &arg0, &len);
    mjs_json_parse(mjs, str, len, &ret);
  } else {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "string argument required");
  }

  mjs_return(mjs, ret);
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_main.c"
#endif

#ifdef MJS_MAIN

// #include <dlfcn.h>

/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_exec.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

int main(int argc, char *argv[]) {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_err_t err = MJS_OK;
  int i;

  for (i = 1; i < argc && argv[i][0] == '-' && err == MJS_OK; i++) {
    if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
      cs_log_set_level(atoi(argv[++i]));
    } else if (strcmp(argv[i], "-j") == 0) {
      mjs_set_generate_jsc(mjs, 1);
    } else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
      err = mjs_exec(mjs, argv[++i], &res);
    } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
      err = mjs_exec_file(mjs, argv[++i], &res);
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf("mJS (c) Cesanta, built: " __DATE__ "\n");
      printf("Usage:\n");
      printf("%s [OPTIONS] [js_file ...]\n", argv[0]);
      printf("OPTIONS:\n");
      printf("  -e string    - Execute JavaScript expression\n");
      printf("  -j           - Enable code precompiling to .jsc files\n");
      printf("  -f js_file   - Execute code from .js JavaScript file\n");
      printf("  -l level     - Set debug level, from 0 to 5\n");
      return EXIT_SUCCESS;
    } else {
      fprintf(stderr, "Unknown flag: [%s]\n", argv[i]);
      return EXIT_FAILURE;
    }
  }
  for (; i < argc && err == MJS_OK; i++) {
    err = mjs_exec_file(mjs, argv[i], &res);
  }

  if (err == MJS_OK) {
    mjs_fprintf(res, mjs, stdout);
    putchar('\n');
  } else {
    mjs_print_error(mjs, stdout, NULL, 1 /* print_stack_trace */);
  }
  mjs_destroy(mjs);

  return EXIT_SUCCESS;
}
#endif
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_object.c"
#endif

/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_conversion.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

/* Amalgamated: #include "common/mg_str.h" */

MJS_PRIVATE mjs_val_t mjs_object_to_value(struct mjs_object *o) {
  if (o == NULL) {
    return MJS_NULL;
  } else {
    return mjs_legit_pointer_to_value(o) | MJS_TAG_OBJECT;
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
  return (v & MJS_TAG_MASK) == MJS_TAG_OBJECT ||
         (v & MJS_TAG_MASK) == MJS_TAG_ARRAY;
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

MJS_PRIVATE struct mjs_property *mjs_get_own_property_v(struct mjs *mjs,
                                                        mjs_val_t obj,
                                                        mjs_val_t key) {
  size_t n;
  char *s = NULL;
  int need_free = 0;
  struct mjs_property *p = NULL;
  mjs_err_t err = mjs_to_string(mjs, &key, &s, &n, &need_free);
  if (err == MJS_OK) {
    p = mjs_get_own_property(mjs, obj, s, n);
  }
  if (need_free) free(s);
  return p;
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

mjs_val_t mjs_get_v_proto(struct mjs *mjs, mjs_val_t obj, mjs_val_t key) {
  struct mjs_property *p;
  mjs_val_t pn = mjs_mk_string(mjs, MJS_PROTO_PROP_NAME, ~0, 1);
  if ((p = mjs_get_own_property_v(mjs, obj, key)) != NULL) return p->value;
  if ((p = mjs_get_own_property_v(mjs, obj, pn)) == NULL) return MJS_UNDEFINED;
  return mjs_get_v_proto(mjs, p->value, key);
}

mjs_err_t mjs_set(struct mjs *mjs, mjs_val_t obj, const char *name,
                  size_t name_len, mjs_val_t val) {
  return mjs_set_internal(mjs, obj, MJS_UNDEFINED, (char *) name, name_len,
                          val);
}

mjs_err_t mjs_set_v(struct mjs *mjs, mjs_val_t obj, mjs_val_t name,
                    mjs_val_t val) {
  return mjs_set_internal(mjs, obj, name, NULL, 0, val);
}

MJS_PRIVATE mjs_err_t mjs_set_internal(struct mjs *mjs, mjs_val_t obj,
                                       mjs_val_t name_v, char *name,
                                       size_t name_len, mjs_val_t val) {
  mjs_err_t rcode = MJS_OK;

  struct mjs_property *p;

  int need_free = 0;

  if (name == NULL) {
    /* Pointer was not provided, so obtain one from the name_v. */
    rcode = mjs_to_string(mjs, &name_v, &name, &name_len, &need_free);
    if (rcode != MJS_OK) {
      goto clean;
    }
  } else {
    /*
     * Pointer was provided, so we ignore name_v. Here we set it to undefined,
     * and the actual value will be calculated later if needed.
     */
    name_v = MJS_UNDEFINED;
  }

  p = mjs_get_own_property(mjs, obj, name, name_len);

  if (p == NULL) {
    struct mjs_object *o;
    if (!mjs_is_object(obj)) {
      return MJS_REFERENCE_ERROR;
    }

    /*
     * name_v might be not a string here. In this case, we need to create a new
     * `name_v`, which will be a string.
     */
    if (!mjs_is_string(name_v)) {
      name_v = mjs_mk_string(mjs, name, name_len, 1);
    }

    p = mjs_mk_property(mjs, name_v, val);

    o = get_object_struct(obj);
    p->next = o->properties;
    o->properties = p;
  }

  p->value = val;

clean:
  if (need_free) {
    free(name);
    name = NULL;
  }
  return rcode;
}

MJS_PRIVATE void mjs_destroy_property(struct mjs_property **p) {
  *p = NULL;
}

/*
 * See comments in `object_public.h`
 */
int mjs_del(struct mjs *mjs, mjs_val_t obj, const char *name, size_t len) {
  struct mjs_property *prop, *prev;

  if (!mjs_is_object(obj)) {
    return -1;
  }
  if (len == (size_t) ~0) {
    len = strlen(name);
  }
  for (prev = NULL, prop = get_object_struct(obj)->properties; prop != NULL;
       prev = prop, prop = prop->next) {
    size_t n;
    const char *s = mjs_get_string(mjs, &prop->name, &n);
    if (n == len && strncmp(s, name, len) == 0) {
      if (prev) {
        prev->next = prop->next;
      } else {
        get_object_struct(obj)->properties = prop->next;
      }
      mjs_destroy_property(&prop);
      return 0;
    }
  }
  return -1;
}

mjs_val_t mjs_next(struct mjs *mjs, mjs_val_t obj, mjs_val_t *iterator) {
  struct mjs_property *p = NULL;
  mjs_val_t key = MJS_UNDEFINED;

  if (*iterator == MJS_UNDEFINED) {
    struct mjs_object *o = get_object_struct(obj);
    p = o->properties;
  } else {
    p = ((struct mjs_property *) get_ptr(*iterator))->next;
  }

  if (p == NULL) {
    *iterator = MJS_UNDEFINED;
  } else {
    key = p->name;
    *iterator = mjs_mk_foreign(mjs, p);
  }

  return key;
}

MJS_PRIVATE void mjs_op_create_object(struct mjs *mjs) {
  mjs_val_t ret = MJS_UNDEFINED;
  mjs_val_t proto_v = mjs_arg(mjs, 0);

  if (!mjs_check_arg(mjs, 0, "proto", MJS_TYPE_OBJECT_GENERIC, &proto_v)) {
    goto clean;
  }

  ret = mjs_mk_object(mjs);
  mjs_set(mjs, ret, MJS_PROTO_PROP_NAME, ~0, proto_v);

clean:
  mjs_return(mjs, ret);
}

mjs_val_t mjs_struct_to_obj(struct mjs *mjs, const void *base,
                            const struct mjs_c_struct_member *defs) {
  mjs_val_t obj;
  const struct mjs_c_struct_member *def = defs;
  if (base == NULL || def == NULL) return MJS_UNDEFINED;
  obj = mjs_mk_object(mjs);
  /* Pin the object while it is being built */
  mjs_own(mjs, &obj);
  /*
   * Because mjs inserts new properties at the head of the list,
   * start from the end so the constructed object more closely resembles
   * the definition.
   */
  while (def->name != NULL) def++;
  for (def--; def >= defs; def--) {
    mjs_val_t v = MJS_UNDEFINED;
    const char *ptr = (const char *) base + def->offset;
    switch (def->type) {
      case MJS_STRUCT_FIELD_TYPE_STRUCT: {
        const void *sub_base = (const void *) ptr;
        const struct mjs_c_struct_member *sub_def =
            (const struct mjs_c_struct_member *) def->arg;
        v = mjs_struct_to_obj(mjs, sub_base, sub_def);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_STRUCT_PTR: {
        const void **sub_base = (const void **) ptr;
        const struct mjs_c_struct_member *sub_def =
            (const struct mjs_c_struct_member *) def->arg;
        if (*sub_base != NULL) {
          v = mjs_struct_to_obj(mjs, *sub_base, sub_def);
        } else {
          v = MJS_NULL;
        }
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_INT: {
        double value = (double) (*(int *) ptr);
        v = mjs_mk_number(mjs, value);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_BOOL: {
        v = mjs_mk_boolean(mjs, *(bool *) ptr);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_DOUBLE: {
        v = mjs_mk_number(mjs, *(double *) ptr);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_FLOAT: {
        float value = *(float *) ptr;
        v = mjs_mk_number(mjs, value);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_CHAR_PTR: {
        const char *value = *(const char **) ptr;
        v = mjs_mk_string(mjs, value, ~0, 1);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_VOID_PTR: {
        v = mjs_mk_foreign(mjs, *(void **) ptr);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_MG_STR_PTR: {
        const struct mg_str *s = *(const struct mg_str **) ptr;
        if (s != NULL) {
          v = mjs_mk_string(mjs, s->p, s->len, 1);
        } else {
          v = MJS_NULL;
        }
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_MG_STR: {
        const struct mg_str *s = (const struct mg_str *) ptr;
        v = mjs_mk_string(mjs, s->p, s->len, 1);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_DATA: {
        const char *dptr = (const char *) ptr;
        const intptr_t dlen = (intptr_t) def->arg;
        v = mjs_mk_string(mjs, dptr, dlen, 1);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_INT8: {
        double value = (double) (*(int8_t *) ptr);
        v = mjs_mk_number(mjs, value);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_INT16: {
        double value = (double) (*(int16_t *) ptr);
        v = mjs_mk_number(mjs, value);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_UINT8: {
        double value = (double) (*(uint8_t *) ptr);
        v = mjs_mk_number(mjs, value);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_UINT16: {
        double value = (double) (*(uint16_t *) ptr);
        v = mjs_mk_number(mjs, value);
        break;
      }
      case MJS_STRUCT_FIELD_TYPE_CUSTOM: {
        mjs_val_t (*fptr)(struct mjs *, const void *) =
            (mjs_val_t (*) (struct mjs *, const void *)) def->arg;
        v = fptr(mjs, ptr);
      }
      default: { break; }
    }
    mjs_set(mjs, obj, def->name, ~0, v);
  }
  mjs_disown(mjs, &obj);
  return obj;
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_parser.c"
#endif

/* Amalgamated: #include "common/cs_varint.h" */

/* Amalgamated: #include "mjs/src/mjs_bcode.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_parser.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "mjs/src/mjs_tok.h" */

#ifndef MAX_TOKS_IN_EXPR
#define MAX_TOKS_IN_EXPR 40
#endif

#define FAIL_ERR(p, code)                                                      \
  do {                                                                         \
    mjs_set_errorf(p->mjs, code, "parse error at line %d: [%.*s]", p->line_no, \
                   10, p->tok.ptr);                                            \
    return code;                                                               \
  } while (0)

#define pnext1(p)                                    \
  do {                                               \
    LOG(LL_VERBOSE_DEBUG, ("  PNEXT %d", __LINE__)); \
    pnext(p);                                        \
  } while (0)

#define SYNTAX_ERROR(p) FAIL_ERR(p, MJS_SYNTAX_ERROR)
#undef EXPECT
#define EXPECT(p, t)       \
  if ((p)->tok.tok != (t)) \
    SYNTAX_ERROR(p);       \
  else                     \
    pnext1(p);

static mjs_err_t parse_statement(struct pstate *p);
static mjs_err_t parse_expr(struct pstate *p);

static int ptest(struct pstate *p) {
  struct pstate saved = *p;
  int tok = pnext(p);
  *p = saved;
  return tok;
}

static int s_unary_ops[] = {TOK_NOT, TOK_TILDA, TOK_PLUS_PLUS, TOK_MINUS_MINUS,
                            TOK_KEYWORD_TYPEOF, TOK_MINUS, TOK_PLUS, TOK_EOF};
static int s_comparison_ops[] = {TOK_LT, TOK_LE, TOK_GT, TOK_GE, TOK_EOF};
static int s_postfix_ops[] = {TOK_PLUS_PLUS, TOK_MINUS_MINUS, TOK_EOF};
static int s_equality_ops[] = {TOK_EQ, TOK_NE, TOK_EQ_EQ, TOK_NE_NE, TOK_EOF};
static int s_assign_ops[] = {
    TOK_ASSIGN,         TOK_PLUS_ASSIGN, TOK_MINUS_ASSIGN,  TOK_MUL_ASSIGN,
    TOK_DIV_ASSIGN,     TOK_REM_ASSIGN,  TOK_LSHIFT_ASSIGN, TOK_RSHIFT_ASSIGN,
    TOK_URSHIFT_ASSIGN, TOK_AND_ASSIGN,  TOK_XOR_ASSIGN,    TOK_OR_ASSIGN,
    TOK_EOF};

static int findtok(int *toks, int tok) {
  int i = 0;
  while (tok != toks[i] && toks[i] != TOK_EOF) i++;
  return toks[i];
}

static void emit_op(struct pstate *pstate, int tok) {
  assert(tok >= 0 && tok <= 255);
  emit_byte(pstate, OP_EXPR);
  emit_byte(pstate, (uint8_t) tok);
}

#define BINOP_STACK_FRAME_SIZE 16
#define STACK_LIMIT 8192

// Intentionally left as macro rather than a function, to let the
// compiler to inline calls and mimimize runtime stack usage.
#define PARSE_LTR_BINOP(p, f1, f2, ops, prev_op)                               \
  do {                                                                         \
    mjs_err_t res = MJS_OK;                                                    \
    p->depth++;                                                                \
    if (p->depth > (STACK_LIMIT / BINOP_STACK_FRAME_SIZE)) {                   \
      mjs_set_errorf(p->mjs, MJS_SYNTAX_ERROR, "parser stack overflow");       \
      res = MJS_SYNTAX_ERROR;                                                  \
      goto binop_clean;                                                        \
    }                                                                          \
    if ((res = f1(p, TOK_EOF)) != MJS_OK) goto binop_clean;                    \
    if (prev_op != TOK_EOF) emit_op(p, prev_op);                               \
    if (findtok(ops, p->tok.tok) != TOK_EOF) {                                 \
      int op = p->tok.tok;                                                     \
      size_t off_if = 0;                                                       \
      /* For AND/OR, implement short-circuit evaluation */                     \
      if (ops[0] == TOK_LOGICAL_AND || ops[0] == TOK_LOGICAL_OR) {             \
        emit_byte(p,                                                           \
                  (uint8_t)(ops[0] == TOK_LOGICAL_AND ? OP_JMP_NEUTRAL_FALSE   \
                                                      : OP_JMP_NEUTRAL_TRUE)); \
        off_if = p->cur_idx;                                                   \
        emit_init_offset(p);                                                   \
        /* No need to emit TOK_LOGICAL_AND and TOK_LOGICAL_OR: */              \
        /* Just drop the first value, and evaluate the second one. */          \
        emit_byte(p, (uint8_t) OP_DROP);                                       \
        op = TOK_EOF;                                                          \
      }                                                                        \
      pnext1(p);                                                               \
      if ((res = f2(p, op)) != MJS_OK) goto binop_clean;                       \
                                                                               \
      if (off_if != 0) {                                                       \
        mjs_bcode_insert_offset(p, p->mjs, off_if,                             \
                                p->cur_idx - off_if - MJS_INIT_OFFSET_SIZE);   \
      }                                                                        \
    }                                                                          \
  binop_clean:                                                                 \
    p->depth--;                                                                \
    return res;                                                                \
  } while (0)

#define PARSE_RTL_BINOP(p, f1, f2, ops, prev_op)        \
  do {                                                  \
    mjs_err_t res = MJS_OK;                             \
    (void) prev_op;                                     \
    if ((res = f1(p, TOK_EOF)) != MJS_OK) return res;   \
    if (findtok(ops, p->tok.tok) != TOK_EOF) {          \
      int op = p->tok.tok;                              \
      pnext1(p);                                        \
      if ((res = f2(p, TOK_EOF)) != MJS_OK) return res; \
      emit_op(p, op);                                   \
    }                                                   \
    return res;                                         \
  } while (0)

#if MJS_INIT_OFFSET_SIZE > 0
static void emit_init_offset(struct pstate *p) {
  size_t i;
  for (i = 0; i < MJS_INIT_OFFSET_SIZE; i++) {
    emit_byte(p, 0);
  }
}
#else
static void emit_init_offset(struct pstate *p) {
  (void) p;
}
#endif

static mjs_err_t parse_statement_list(struct pstate *p, int et) {
  mjs_err_t res = MJS_OK;
  int drop = 0;
  pnext1(p);
  while (res == MJS_OK && p->tok.tok != TOK_EOF && p->tok.tok != et) {
    if (drop) emit_byte(p, OP_DROP);
    res = parse_statement(p);
    drop = 1;
    while (p->tok.tok == TOK_SEMICOLON) pnext1(p);
  }

  /*
   * Client code expects statement list to contain a value, so if the statement
   * list was empty, push `undefined`.
   */
  if (!drop) {
    emit_byte(p, OP_PUSH_UNDEF);
  }
  return res;
}

static mjs_err_t parse_block(struct pstate *p, int mkscope) {
  mjs_err_t res = MJS_OK;
  p->depth++;
  if (p->depth > (STACK_LIMIT / BINOP_STACK_FRAME_SIZE)) {
    mjs_set_errorf(p->mjs, MJS_SYNTAX_ERROR, "parser stack overflow");
    res = MJS_SYNTAX_ERROR;
    return res;
  }
  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  if (mkscope) emit_byte(p, OP_NEW_SCOPE);
  res = parse_statement_list(p, TOK_CLOSE_CURLY);
  EXPECT(p, TOK_CLOSE_CURLY);
  if (mkscope) emit_byte(p, OP_DEL_SCOPE);
  return res;
}

static mjs_err_t parse_function(struct pstate *p) {
  size_t prologue, off;
  int arg_no = 0;
  int name_provided = 0;
  mjs_err_t res = MJS_OK;

  EXPECT(p, TOK_KEYWORD_FUNCTION);

  if (p->tok.tok == TOK_IDENT) {
    /* Function name was provided */
    struct tok tmp = p->tok;
    name_provided = 1;
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, tmp.ptr, tmp.len);
    emit_byte(p, OP_PUSH_SCOPE);
    emit_byte(p, OP_CREATE);
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, tmp.ptr, tmp.len);
    emit_byte(p, OP_FIND_SCOPE);
    pnext1(p);
  }

  emit_byte(p, OP_JMP);
  off = p->cur_idx;
  emit_init_offset(p);

  prologue = p->cur_idx;

  EXPECT(p, TOK_OPEN_PAREN);
  emit_byte(p, OP_NEW_SCOPE);
  // Emit names of function arguments
  while (p->tok.tok != TOK_CLOSE_PAREN) {
    if (p->tok.tok != TOK_IDENT) SYNTAX_ERROR(p);
    emit_byte(p, OP_SET_ARG);
    emit_int(p, arg_no);
    arg_no++;
    emit_str(p, p->tok.ptr, p->tok.len);
    if (ptest(p) == TOK_COMMA) pnext1(p);
    pnext1(p);
  }
  EXPECT(p, TOK_CLOSE_PAREN);
  if ((res = parse_block(p, 0)) != MJS_OK) return res;
  emit_byte(p, OP_RETURN);
  prologue += mjs_bcode_insert_offset(p, p->mjs, off,
                                      p->cur_idx - off - MJS_INIT_OFFSET_SIZE);
  emit_byte(p, OP_PUSH_FUNC);
  emit_int(p, p->cur_idx - 1 /* OP_PUSH_FUNC */ - prologue);
  if (name_provided) {
    emit_op(p, TOK_ASSIGN);
  }

  return res;
}

static mjs_err_t parse_object_literal(struct pstate *p) {
  mjs_err_t res = MJS_OK;
  EXPECT(p, TOK_OPEN_CURLY);
  emit_byte(p, OP_PUSH_OBJ);
  while (p->tok.tok != TOK_CLOSE_CURLY) {
    if (p->tok.tok != TOK_IDENT && p->tok.tok != TOK_STR) SYNTAX_ERROR(p);
    emit_byte(p, OP_DUP);
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, p->tok.ptr, p->tok.len);
    emit_byte(p, OP_SWAP);
    pnext1(p);
    EXPECT(p, TOK_COLON);
    if ((res = parse_expr(p)) != MJS_OK) return res;
    emit_op(p, TOK_ASSIGN);
    emit_byte(p, OP_DROP);
    if (p->tok.tok == TOK_COMMA) {
      pnext1(p);
    } else if (p->tok.tok != TOK_CLOSE_CURLY) {
      SYNTAX_ERROR(p);
    }
  }
  return res;
}

static mjs_err_t parse_array_literal(struct pstate *p) {
  mjs_err_t res = MJS_OK;
  EXPECT(p, TOK_OPEN_BRACKET);
  emit_byte(p, OP_PUSH_ARRAY);
  while (p->tok.tok != TOK_CLOSE_BRACKET) {
    emit_byte(p, OP_DUP);
    if ((res = parse_expr(p)) != MJS_OK) return res;
    emit_byte(p, OP_APPEND);
    if (p->tok.tok == TOK_COMMA) pnext1(p);
  }
  return res;
}

static enum mjs_err parse_literal(struct pstate *p, const struct tok *t) {
  struct mbuf *bcode_gen = &p->mjs->bcode_gen;
  enum mjs_err res = MJS_OK;
  int tok = t->tok;
  LOG(LL_VERBOSE_DEBUG, ("[%.*s] %p", p->tok.len, p->tok.ptr, (void *) &t));
  switch (t->tok) {
    case TOK_KEYWORD_FALSE:
      emit_byte(p, OP_PUSH_FALSE);
      break;
    case TOK_KEYWORD_TRUE:
      emit_byte(p, OP_PUSH_TRUE);
      break;
    case TOK_KEYWORD_UNDEFINED:
      emit_byte(p, OP_PUSH_UNDEF);
      break;
    case TOK_KEYWORD_NULL:
      emit_byte(p, OP_PUSH_NULL);
      break;
    case TOK_IDENT: {
      int prev_tok = p->prev_tok;
      int next_tok = ptest(p);
      emit_byte(p, OP_PUSH_STR);
      emit_str(p, t->ptr, t->len);
      emit_byte(p, (uint8_t)(prev_tok == TOK_DOT ? OP_SWAP : OP_FIND_SCOPE));
      if (!findtok(s_assign_ops, next_tok) &&
          !findtok(s_postfix_ops, next_tok) &&
          /* TODO(dfrank): fix: it doesn't work for prefix ops */
          !findtok(s_postfix_ops, prev_tok)) {
        emit_byte(p, OP_GET);
      }
      break;
    }
    case TOK_NUM: {
      double iv, d = strtod(t->ptr, NULL);
      unsigned long uv = strtoul(t->ptr + 2, NULL, 16);
      if (t->ptr[0] == '0' && t->ptr[1] == 'x') d = uv;
      if (modf(d, &iv) == 0) {
        emit_byte(p, OP_PUSH_INT);
        emit_int(p, (int64_t) d);
      } else {
        emit_byte(p, OP_PUSH_DBL);
        emit_str(p, t->ptr, t->len);
      }
      break;
    }
    case TOK_STR: {
      size_t oldlen;
      emit_byte(p, OP_PUSH_STR);
      oldlen = bcode_gen->len;
      embed_string(bcode_gen, p->cur_idx, t->ptr, t->len, EMBSTR_UNESCAPE);
      p->cur_idx += bcode_gen->len - oldlen;
    } break;
    case TOK_OPEN_BRACKET:
      res = parse_array_literal(p);
      break;
    case TOK_OPEN_CURLY:
      res = parse_object_literal(p);
      break;
    case TOK_OPEN_PAREN:
      pnext1(p);
      res = parse_expr(p);
      if (p->tok.tok != TOK_CLOSE_PAREN) SYNTAX_ERROR(p);
      break;
    case TOK_KEYWORD_FUNCTION:
      res = parse_function(p);
      break;
    case TOK_KEYWORD_THIS:
      emit_byte(p, OP_PUSH_THIS);
      break;
    default:
      SYNTAX_ERROR(p);
  }
  if (tok != TOK_KEYWORD_FUNCTION) pnext1(p);
  return res;
}

static mjs_err_t parse_call_dot_mem(struct pstate *p, int prev_op) {
  int ops[] = {TOK_DOT, TOK_OPEN_PAREN, TOK_OPEN_BRACKET, TOK_EOF};
  mjs_err_t res = MJS_OK;
  if ((res = parse_literal(p, &p->tok)) != MJS_OK) return res;
  while (findtok(ops, p->tok.tok) != TOK_EOF) {
    if (p->tok.tok == TOK_OPEN_BRACKET) {
      int prev_tok = p->prev_tok;
      EXPECT(p, TOK_OPEN_BRACKET);
      if ((res = parse_expr(p)) != MJS_OK) return res;
      emit_byte(p, OP_SWAP);
      EXPECT(p, TOK_CLOSE_BRACKET);
      if (!findtok(s_assign_ops, p->tok.tok) &&
          !findtok(s_postfix_ops, p->tok.tok) &&
          /* TODO(dfrank): fix: it doesn't work for prefix ops */
          !findtok(s_postfix_ops, prev_tok)) {
        emit_byte(p, OP_GET);
      }
    } else if (p->tok.tok == TOK_OPEN_PAREN) {
      EXPECT(p, TOK_OPEN_PAREN);
      emit_byte(p, OP_ARGS);
      while (p->tok.tok != TOK_CLOSE_PAREN) {
        if ((res = parse_expr(p)) != MJS_OK) return res;
        if (p->tok.tok == TOK_COMMA) pnext1(p);
      }
      emit_byte(p, OP_CALL);
      EXPECT(p, TOK_CLOSE_PAREN);
    } else if (p->tok.tok == TOK_DOT) {
      EXPECT(p, TOK_DOT);
      if ((res = parse_call_dot_mem(p, TOK_DOT)) != MJS_OK) return res;
    }
  }
  (void) prev_op;
  return res;
}

static mjs_err_t parse_postfix(struct pstate *p, int prev_op) {
  mjs_err_t res = MJS_OK;
  if ((res = parse_call_dot_mem(p, prev_op)) != MJS_OK) return res;
  if (p->tok.tok == TOK_PLUS_PLUS || p->tok.tok == TOK_MINUS_MINUS) {
    int op = p->tok.tok == TOK_PLUS_PLUS ? TOK_POSTFIX_PLUS : TOK_POSTFIX_MINUS;
    emit_op(p, op);
    pnext1(p);
  }
  return res;
}

static mjs_err_t parse_unary(struct pstate *p, int prev_op) {
  mjs_err_t res = MJS_OK;
  int op = TOK_EOF;
  if (findtok(s_unary_ops, p->tok.tok) != TOK_EOF) {
    op = p->tok.tok;
    pnext1(p);
  }
  if (findtok(s_unary_ops, p->tok.tok) != TOK_EOF) {
    res = parse_unary(p, prev_op);
  } else {
    res = parse_postfix(p, prev_op);
  }
  if (res != MJS_OK) return res;
  if (op != TOK_EOF) {
    if (op == TOK_MINUS) op = TOK_UNARY_MINUS;
    if (op == TOK_PLUS) op = TOK_UNARY_PLUS;
    emit_op(p, op);
  }
  return res;
}

static mjs_err_t parse_mul_div_rem(struct pstate *p, int prev_op) {
  int ops[] = {TOK_MUL, TOK_DIV, TOK_REM, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_unary, parse_mul_div_rem, ops, prev_op);
}

static mjs_err_t parse_plus_minus(struct pstate *p, int prev_op) {
  int ops[] = {TOK_PLUS, TOK_MINUS, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_mul_div_rem, parse_plus_minus, ops, prev_op);
}

static mjs_err_t parse_shifts(struct pstate *p, int prev_op) {
  int ops[] = {TOK_LSHIFT, TOK_RSHIFT, TOK_URSHIFT, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_plus_minus, parse_shifts, ops, prev_op);
}

static mjs_err_t parse_comparison(struct pstate *p, int prev_op) {
  PARSE_LTR_BINOP(p, parse_shifts, parse_comparison, s_comparison_ops, prev_op);
}

static mjs_err_t parse_equality(struct pstate *p, int prev_op) {
  PARSE_LTR_BINOP(p, parse_comparison, parse_equality, s_equality_ops, prev_op);
}

static mjs_err_t parse_bitwise_and(struct pstate *p, int prev_op) {
  int ops[] = {TOK_AND, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_equality, parse_bitwise_and, ops, prev_op);
}

static mjs_err_t parse_bitwise_xor(struct pstate *p, int prev_op) {
  int ops[] = {TOK_XOR, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_bitwise_and, parse_bitwise_xor, ops, prev_op);
}

static mjs_err_t parse_bitwise_or(struct pstate *p, int prev_op) {
  int ops[] = {TOK_OR, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_bitwise_xor, parse_bitwise_or, ops, prev_op);
}

static mjs_err_t parse_logical_and(struct pstate *p, int prev_op) {
  int ops[] = {TOK_LOGICAL_AND, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_bitwise_or, parse_logical_and, ops, prev_op);
}

static mjs_err_t parse_logical_or(struct pstate *p, int prev_op) {
  int ops[] = {TOK_LOGICAL_OR, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_logical_and, parse_logical_or, ops, prev_op);
}

static mjs_err_t parse_ternary(struct pstate *p, int prev_op) {
  mjs_err_t res = MJS_OK;
  if ((res = parse_logical_or(p, TOK_EOF)) != MJS_OK) return res;
  if (prev_op != TOK_EOF) emit_op(p, prev_op);

  if (p->tok.tok == TOK_QUESTION) {
    size_t off_if, off_endif, off_else;
    EXPECT(p, TOK_QUESTION);

    emit_byte(p, OP_JMP_FALSE);
    off_if = p->cur_idx;
    emit_init_offset(p);

    if ((res = parse_ternary(p, TOK_EOF)) != MJS_OK) return res;

    emit_byte(p, OP_JMP);
    off_else = p->cur_idx;
    emit_init_offset(p);
    off_endif = p->cur_idx;

    emit_byte(p, OP_DROP);

    EXPECT(p, TOK_COLON);
    if ((res = parse_ternary(p, TOK_EOF)) != MJS_OK) return res;

    /*
     * NOTE: if inserting offset causes the code to move, off_endif needs to be
     * adjusted
     */
    off_endif += mjs_bcode_insert_offset(
        p, p->mjs, off_else, p->cur_idx - off_else - MJS_INIT_OFFSET_SIZE);

    mjs_bcode_insert_offset(p, p->mjs, off_if,
                            off_endif - off_if - MJS_INIT_OFFSET_SIZE);
  }

  return res;
}

static mjs_err_t parse_assignment(struct pstate *p, int prev_op) {
  PARSE_RTL_BINOP(p, parse_ternary, parse_assignment, s_assign_ops, prev_op);
}

static mjs_err_t parse_expr(struct pstate *p) {
  return parse_assignment(p, TOK_EOF);
}

static mjs_err_t parse_let(struct pstate *p) {
  mjs_err_t res = MJS_OK;
  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  EXPECT(p, TOK_KEYWORD_LET);
  for (;;) {
    struct tok tmp = p->tok;
    EXPECT(p, TOK_IDENT);

    emit_byte(p, OP_PUSH_STR);
    emit_str(p, tmp.ptr, tmp.len);
    emit_byte(p, OP_PUSH_SCOPE);
    emit_byte(p, OP_CREATE);

    if (p->tok.tok == TOK_ASSIGN) {
      pnext1(p);
      emit_byte(p, OP_PUSH_STR);
      emit_str(p, tmp.ptr, tmp.len);
      emit_byte(p, OP_FIND_SCOPE);
      if ((res = parse_expr(p)) != MJS_OK) return res;
      emit_op(p, TOK_ASSIGN);
    } else {
      emit_byte(p, OP_PUSH_UNDEF);
    }
    if (p->tok.tok == TOK_COMMA) {
      emit_byte(p, OP_DROP);
      pnext1(p);
    }
    if (p->tok.tok == TOK_SEMICOLON || p->tok.tok == TOK_EOF) break;
  }
  return res;
}

static mjs_err_t parse_block_or_stmt(struct pstate *p, int cs) {
  if (ptest(p) == TOK_OPEN_CURLY) {
    return parse_block(p, cs);
  } else {
    return parse_statement(p);
  }
}

static mjs_err_t parse_for_in(struct pstate *p) {
  mjs_err_t res = MJS_OK;
  size_t off_b, off_check_end;

  /* new scope should be pushed before OP_LOOP instruction */
  emit_byte(p, OP_NEW_SCOPE);

  /* Put iterator variable name to the stack */
  if (p->tok.tok == TOK_KEYWORD_LET) {
    EXPECT(p, TOK_KEYWORD_LET);
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, p->tok.ptr, p->tok.len);
    emit_byte(p, OP_PUSH_SCOPE);
    emit_byte(p, OP_CREATE);
  }
  emit_byte(p, OP_PUSH_STR);
  emit_str(p, p->tok.ptr, p->tok.len);

  /* Put object to the stack */
  EXPECT(p, TOK_IDENT);
  EXPECT(p, TOK_KEYWORD_IN);
  parse_expr(p);
  EXPECT(p, TOK_CLOSE_PAREN);

  emit_byte(p, OP_PUSH_UNDEF); /* Push iterator */

  /* Before parsing condition statement, push break/continue offsets  */
  emit_byte(p, OP_LOOP);
  off_b = p->cur_idx;
  emit_init_offset(p);
  emit_byte(p, 0); /* Point OP_CONTINUE to the next instruction */

  emit_byte(p, OP_FOR_IN_NEXT);
  emit_byte(p, OP_DUP);
  emit_byte(p, OP_JMP_FALSE);
  off_check_end = p->cur_idx;
  emit_init_offset(p);

  // Parse loop body
  if (p->tok.tok == TOK_OPEN_CURLY) {
    if ((res = parse_statement_list(p, TOK_CLOSE_CURLY)) != MJS_OK) return res;
    pnext1(p);
  } else {
    if ((res = parse_statement(p)) != MJS_OK) return res;
  }
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_CONTINUE);

  /* jump cond -> break */
  mjs_bcode_insert_offset(p, p->mjs, off_check_end,
                          p->cur_idx - off_check_end - MJS_INIT_OFFSET_SIZE);

  /* NOTE: jump C -> cond link is already established, it's constant: zero */

  emit_byte(p, OP_BREAK);

  /* jump B -> cond */
  mjs_bcode_insert_offset(p, p->mjs, off_b,
                          p->cur_idx - off_b - MJS_INIT_OFFSET_SIZE);

  emit_byte(p, OP_DROP);
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_DEL_SCOPE);

  return res;
}

static int check_for_in(struct pstate *p) {
  struct pstate saved = *p;
  int forin = 0;
  if (p->tok.tok == TOK_KEYWORD_LET) pnext1(p);
  if (p->tok.tok == TOK_IDENT) {
    pnext1(p);
    if (p->tok.tok == TOK_KEYWORD_IN) forin = 1;
  }
  *p = saved;
  return forin;
}

static mjs_err_t parse_for(struct pstate *p) {
  mjs_err_t res = MJS_OK;
  size_t off_b, off_c, off_init_end;
  size_t off_incr_begin, off_cond_begin, off_cond_end;
  int buf_cur_idx;

  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  EXPECT(p, TOK_KEYWORD_FOR);
  EXPECT(p, TOK_OPEN_PAREN);

  /* Look forward - is it for..in ? */
  if (check_for_in(p)) return parse_for_in(p);

  /*
   * BC is a break+continue offsets (a part of OP_LOOP opcode)
   *
   *  BC init  incr  cond  body  break  del_scope
   *  ||    |  ^     ^  |        ^      ^
   *  ||    +--|-----+  |        |      |
   *  |+-------+        +--------+      |
   *  +---------------------------------+
   *
   * The order to setup links:
   *
   *   cond -> break
   *   init -> cond
   *   C -> incr
   *   B -> del_scope
   */

  /* new scope should be pushed before OP_LOOP instruction */
  emit_byte(p, OP_NEW_SCOPE);

  /* Before parsing condition statement, push break/continue offsets  */
  emit_byte(p, OP_LOOP);
  off_b = p->cur_idx;
  emit_init_offset(p);
  off_c = p->cur_idx;
  emit_init_offset(p);

  /* Parse init statement */
  if (p->tok.tok == TOK_KEYWORD_LET) {
    if ((res = parse_let(p)) != MJS_OK) return res;
  } else {
    if ((res = parse_expr(p)) != MJS_OK) return res;
  }
  EXPECT(p, TOK_SEMICOLON);
  emit_byte(p, OP_DROP);

  emit_byte(p, OP_JMP);
  off_init_end = p->cur_idx;
  emit_init_offset(p);

  off_incr_begin = p->cur_idx;
  off_cond_begin = p->cur_idx;

  /* Parse cond statement */
  if ((res = parse_expr(p)) != MJS_OK) return res;
  EXPECT(p, TOK_SEMICOLON);

  /* Parse incr statement */
  /* Incr statement should be placed before cond, so, adjust cur_idx */
  buf_cur_idx = p->cur_idx;
  p->cur_idx = off_incr_begin;

  if ((res = parse_expr(p)) != MJS_OK) return res;
  EXPECT(p, TOK_CLOSE_PAREN);
  emit_byte(p, OP_DROP);

  /*
   * Now incr is inserted before cond, so we adjust cur_idx back, and set
   * off_cond_begin to the correct value
   */
  {
    int incr_size = p->cur_idx - off_incr_begin;
    off_cond_begin += incr_size;
    p->cur_idx = buf_cur_idx + incr_size;
  }

  /* p->cur_idx is now at the end of "cond" */
  /* Exit the loop if false */
  emit_byte(p, OP_JMP_FALSE);
  off_cond_end = p->cur_idx;
  emit_init_offset(p);

  /* Parse loop body */
  if (p->tok.tok == TOK_OPEN_CURLY) {
    if ((res = parse_statement_list(p, TOK_CLOSE_CURLY)) != MJS_OK) return res;
    pnext1(p);
  } else {
    if ((res = parse_statement(p)) != MJS_OK) return res;
  }
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_CONTINUE);

  /* p->cur_idx is at the "break" item now */

  /* jump cond -> break */
  mjs_bcode_insert_offset(p, p->mjs, off_cond_end,
                          p->cur_idx - off_cond_end - MJS_INIT_OFFSET_SIZE);

  /* jump init -> cond (and adjust off_incr_begin which may move) */
  off_incr_begin += mjs_bcode_insert_offset(
      p, p->mjs, off_init_end,
      off_cond_begin - off_init_end - MJS_INIT_OFFSET_SIZE);

  /* jump C -> incr */
  mjs_bcode_insert_offset(p, p->mjs, off_c,
                          off_incr_begin - off_c - MJS_INIT_OFFSET_SIZE);

  emit_byte(p, OP_BREAK);

  /* jump B -> del_scope */
  mjs_bcode_insert_offset(p, p->mjs, off_b,
                          p->cur_idx - off_b - MJS_INIT_OFFSET_SIZE);

  emit_byte(p, OP_DEL_SCOPE);

  return res;
}

static mjs_err_t parse_while(struct pstate *p) {
  size_t off_cond_end, off_b;
  mjs_err_t res = MJS_OK;

  EXPECT(p, TOK_KEYWORD_WHILE);
  EXPECT(p, TOK_OPEN_PAREN);

  /* new scope should be pushed before OP_LOOP instruction */
  emit_byte(p, OP_NEW_SCOPE);

  /*
   * BC is a break+continue offsets (a part of OP_LOOP opcode)
   *
   *   BC cond body break del_scope
   *   || ^  |      ^     ^
   *   || |  |      |     |
   *   |+-+  +------+     |
   *   +------------------+
   *
   * The order to setup links:
   *
   *    cond -> break
   *    C -> cond
   *    B -> del_scope
   */

  emit_byte(p, OP_LOOP);
  off_b = p->cur_idx;
  emit_init_offset(p);
  emit_byte(p, 0); /* Point OP_CONTINUE to the next instruction */

  // parse condition statement
  if ((res = parse_expr(p)) != MJS_OK) return res;
  EXPECT(p, TOK_CLOSE_PAREN);

  // Exit the loop if false
  emit_byte(p, OP_JMP_FALSE);
  off_cond_end = p->cur_idx;
  emit_init_offset(p);

  // Parse loop body
  if (p->tok.tok == TOK_OPEN_CURLY) {
    if ((res = parse_statement_list(p, TOK_CLOSE_CURLY)) != MJS_OK) return res;
    pnext1(p);
  } else {
    if ((res = parse_statement(p)) != MJS_OK) return res;
  }
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_CONTINUE);

  /* jump cond -> break */
  mjs_bcode_insert_offset(p, p->mjs, off_cond_end,
                          p->cur_idx - off_cond_end - MJS_INIT_OFFSET_SIZE);

  /* NOTE: jump C -> cond link is already established, it's constant: zero */

  emit_byte(p, OP_BREAK);

  /* jump B -> cond */
  mjs_bcode_insert_offset(p, p->mjs, off_b,
                          p->cur_idx - off_b - MJS_INIT_OFFSET_SIZE);

  emit_byte(p, OP_DEL_SCOPE);
  return res;
}

static mjs_err_t parse_if(struct pstate *p) {
  size_t off_if, off_endif;
  mjs_err_t res = MJS_OK;
  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  EXPECT(p, TOK_KEYWORD_IF);
  EXPECT(p, TOK_OPEN_PAREN);
  if ((res = parse_expr(p)) != MJS_OK) return res;

  emit_byte(p, OP_JMP_FALSE);
  off_if = p->cur_idx;
  emit_init_offset(p);

  EXPECT(p, TOK_CLOSE_PAREN);
  if ((res = parse_block_or_stmt(p, 1)) != MJS_OK) return res;

  if (p->tok.tok == TOK_KEYWORD_ELSE) {
    /*
     * Else clause is present, so, if the condition is not true, the jump
     * target (off_endif) should be not the current offset, but the offset
     * after jump-over-else opcode
     */
    size_t off_else, off_endelse;
    pnext1(p);
    emit_byte(p, OP_JMP);
    off_else = p->cur_idx;
    emit_init_offset(p);
    off_endif = p->cur_idx;

    emit_byte(p, OP_DROP);
    if ((res = parse_block_or_stmt(p, 1)) != MJS_OK) return res;
    off_endelse = p->cur_idx;

    /*
     * NOTE: if inserting offset causes the code to move, off_endif needs to be
     * adjusted
     */
    off_endif += mjs_bcode_insert_offset(
        p, p->mjs, off_else, off_endelse - off_else - MJS_INIT_OFFSET_SIZE);
  } else {
    /* Else clause is not present, so, current offset is a jump target
     * (off_endif) */
    off_endif = p->cur_idx;
  }

  mjs_bcode_insert_offset(p, p->mjs, off_if,
                          off_endif - off_if - MJS_INIT_OFFSET_SIZE);

  return res;
}

static void pstate_revert(struct pstate *p, struct pstate *old,
                          int old_bcode_gen_len) {
  p->pos = old->pos;
  p->line_no = old->line_no;
  p->last_emitted_line_no = old->last_emitted_line_no;
  p->offset_lineno_map.len = old->offset_lineno_map.len;
  p->prev_tok = old->prev_tok;
  p->tok = old->tok;
  p->mjs->bcode_gen.len = old_bcode_gen_len;
  p->cur_idx = old->cur_idx;
  p->depth = old->depth;
}

static mjs_err_t parse_return(struct pstate *p) {
  int old_bcode_gen_len;
  struct pstate p_saved;
  EXPECT(p, TOK_KEYWORD_RETURN);
  p_saved = *p;
  old_bcode_gen_len = p->mjs->bcode_gen.len;
  if (parse_expr(p) != MJS_OK) {
    /*
     * Failed to parse an expression to return, so return the parser to the
     * prior state and push undefined.
     */
    pstate_revert(p, &p_saved, old_bcode_gen_len);
    emit_byte(p, OP_PUSH_UNDEF);
  }
  emit_byte(p, OP_SETRETVAL);
  emit_byte(p, OP_RETURN);
  return MJS_OK;
}

static mjs_err_t parse_statement(struct pstate *p) {
  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  switch (p->tok.tok) {
    case TOK_SEMICOLON:
      emit_byte(p, OP_PUSH_UNDEF);
      pnext1(p);
      return MJS_OK;
    case TOK_KEYWORD_LET:
      return parse_let(p);
    case TOK_OPEN_CURLY:
      return parse_block(p, 1);
    case TOK_KEYWORD_RETURN:
      return parse_return(p);
    case TOK_KEYWORD_FOR:
      return parse_for(p);
    case TOK_KEYWORD_WHILE:
      return parse_while(p);
    case TOK_KEYWORD_BREAK:
      emit_byte(p, OP_PUSH_UNDEF);
      emit_byte(p, OP_BREAK);
      pnext1(p);
      return MJS_OK;
    case TOK_KEYWORD_CONTINUE:
      emit_byte(p, OP_CONTINUE);
      pnext1(p);
      return MJS_OK;
    case TOK_KEYWORD_IF:
      return parse_if(p);
    case TOK_KEYWORD_CASE:
    case TOK_KEYWORD_CATCH:
    case TOK_KEYWORD_DELETE:
    case TOK_KEYWORD_DO:
    case TOK_KEYWORD_INSTANCEOF:
    case TOK_KEYWORD_NEW:
    case TOK_KEYWORD_SWITCH:
    case TOK_KEYWORD_THROW:
    case TOK_KEYWORD_TRY:
    case TOK_KEYWORD_VAR:
    case TOK_KEYWORD_VOID:
    case TOK_KEYWORD_WITH:
      mjs_set_errorf(p->mjs, MJS_SYNTAX_ERROR, "[%.*s] is not implemented",
                     p->tok.len, p->tok.ptr);
      return MJS_SYNTAX_ERROR;
    default: {
      mjs_err_t res = MJS_OK;
      for (;;) {
        if ((res = parse_expr(p)) != MJS_OK) return res;
        if (p->tok.tok != TOK_COMMA) break;
        emit_byte(p, OP_DROP);
        pnext1(p);
      }
      return res;
    }
  }
}

MJS_PRIVATE mjs_err_t
mjs_parse(const char *path, const char *buf, struct mjs *mjs) {
  mjs_err_t res = MJS_OK;
  struct pstate p;
  size_t start_idx, llen;
  int map_len;
  mjs_header_item_t bcode_offset, map_offset, total_size;

  pinit(path, buf, &p);
  p.mjs = mjs;
  p.cur_idx = p.mjs->bcode_gen.len;
  emit_byte(&p, OP_BCODE_HEADER);

  /*
   * TODO(dfrank): don't access mjs->bcode_gen directly, use emit_... API which
   * takes care of p->cur_idx
   */

  /* Remember starting bcode position, and reserve the room for bcode header */
  start_idx = p.mjs->bcode_gen.len;
  mbuf_append(&p.mjs->bcode_gen, NULL,
              sizeof(mjs_header_item_t) * MJS_HDR_ITEMS_CNT);

  /* Append NULL-terminated filename */
  mbuf_append(&p.mjs->bcode_gen, path, strlen(path) + 1 /* null-terminate */);

  bcode_offset = p.mjs->bcode_gen.len - start_idx;
  memcpy(p.mjs->bcode_gen.buf + start_idx +
             sizeof(mjs_header_item_t) * MJS_HDR_ITEM_BCODE_OFFSET,
         &bcode_offset, sizeof(mjs_header_item_t));

  p.start_bcode_idx = p.mjs->bcode_gen.len;
  p.cur_idx = p.mjs->bcode_gen.len;

  res = parse_statement_list(&p, TOK_EOF);
  emit_byte(&p, OP_EXIT);

  /* remember map offset */
  map_offset = p.mjs->bcode_gen.len - start_idx;
  memcpy(p.mjs->bcode_gen.buf + start_idx +
             sizeof(mjs_header_item_t) * MJS_HDR_ITEM_MAP_OFFSET,
         &map_offset, sizeof(mjs_header_item_t));

  /* put map length varint */
  map_len = p.offset_lineno_map.len;
  llen = cs_varint_llen(map_len);
  mbuf_resize(&p.mjs->bcode_gen, p.mjs->bcode_gen.size + llen);
  cs_varint_encode(
      map_len, (uint8_t *) p.mjs->bcode_gen.buf + p.mjs->bcode_gen.len, llen);
  p.mjs->bcode_gen.len += llen;

  /* put the map itself */
  mbuf_append(&p.mjs->bcode_gen, p.offset_lineno_map.buf,
              p.offset_lineno_map.len);

  total_size = p.mjs->bcode_gen.len - start_idx;
  memcpy(p.mjs->bcode_gen.buf + start_idx +
             sizeof(mjs_header_item_t) * MJS_HDR_ITEM_TOTAL_SIZE,
         &total_size, sizeof(mjs_header_item_t));

  mbuf_free(&p.offset_lineno_map);

  /*
   * If parsing was successful, commit the bcode; otherwise drop generated
   * bcode
   */
  if (res == MJS_OK) {
    mjs_bcode_commit(mjs);
  } else {
    mbuf_free(&mjs->bcode_gen);
  }

  return res;
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_primitive.c"
#endif

/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */

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
  /*
   * NOTE(dfrank): without double cast, all numbers >= 0x80000000 are always
   * converted to exactly 0x80000000.
   */
  return (int) (unsigned int) get_double(v);
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
  return (v ? 1 : 0) | MJS_TAG_BOOLEAN;
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

#define MJS_IS_POINTER_LEGIT(n) \
  (((n) &MJS_TAG_MASK) == 0 || ((n) &MJS_TAG_MASK) == (~0 & MJS_TAG_MASK))

MJS_PRIVATE mjs_val_t mjs_pointer_to_value(struct mjs *mjs, void *p) {
  uint64_t n = ((uint64_t)(uintptr_t) p);

  if (!MJS_IS_POINTER_LEGIT(n)) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "invalid pointer value: %p", p);
  }
  return n & ~MJS_TAG_MASK;
}

MJS_PRIVATE mjs_val_t mjs_legit_pointer_to_value(void *p) {
  uint64_t n = ((uint64_t)(uintptr_t) p);

  assert(MJS_IS_POINTER_LEGIT(n));
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
  return mjs_pointer_to_value(mjs, p) | MJS_TAG_FOREIGN;
}

mjs_val_t mjs_mk_foreign_func(struct mjs *mjs, mjs_func_ptr_t fn) {
  union {
    mjs_func_ptr_t fn;
    void *p;
  } u;
  u.fn = fn;
  (void) mjs;
  return mjs_pointer_to_value(mjs, u.p) | MJS_TAG_FOREIGN;
}

int mjs_is_foreign(mjs_val_t v) {
  return (v & MJS_TAG_MASK) == MJS_TAG_FOREIGN;
}

mjs_val_t mjs_mk_function(struct mjs *mjs, size_t off) {
  (void) mjs;
  return (mjs_val_t) off | MJS_TAG_FUNCTION;
}

int mjs_is_function(mjs_val_t v) {
  return (v & MJS_TAG_MASK) == MJS_TAG_FUNCTION;
}

MJS_PRIVATE void mjs_op_isnan(struct mjs *mjs) {
  mjs_val_t ret = MJS_UNDEFINED;
  mjs_val_t val = mjs_arg(mjs, 0);

  ret = mjs_mk_boolean(mjs, val == MJS_TAG_NAN);

  mjs_return(mjs, ret);
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_string.c"
#endif

/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "common/cs_varint.h" */
/* Amalgamated: #include "common/mg_str.h" */
/* Amalgamated: #include "mjs/src/mjs_conversion.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */

// No UTF
typedef unsigned short Rune;
static int chartorune(Rune *rune, const char *str) {
  *rune = *(unsigned char *) str;
  return 1;
}
static int runetochar(char *str, Rune *rune) {
  str[0] = (char) *rune;
  return 1;
}

#ifndef MJS_STRING_BUF_RESERVE
#define MJS_STRING_BUF_RESERVE 100
#endif

MJS_PRIVATE size_t unescape(const char *s, size_t len, char *to);

MJS_PRIVATE void embed_string(struct mbuf *m, size_t offset, const char *p,
                              size_t len, uint8_t /*enum embstr_flags*/ flags);

/* TODO(lsm): NaN payload location depends on endianness, make crossplatform */
#define GET_VAL_NAN_PAYLOAD(v) ((char *) &(v))

int mjs_is_string(mjs_val_t v) {
  uint64_t t = v & MJS_TAG_MASK;
  return t == MJS_TAG_STRING_I || t == MJS_TAG_STRING_F ||
         t == MJS_TAG_STRING_O || t == MJS_TAG_STRING_5 ||
         t == MJS_TAG_STRING_D;
}

mjs_val_t mjs_mk_string(struct mjs *mjs, const char *p, size_t len, int copy) {
  struct mbuf *m;
  mjs_val_t offset, tag = MJS_TAG_STRING_F;
  if (len == 0) {
    /*
     * Zero length for foreign string has a special meaning (that the foreign
     * string is not inlined into mjs_val_t), so when creating a zero-length
     * string, we always assume it'll be owned. Since the length is zero, it
     * doesn't matter anyway.
     */
    copy = 1;
  }
  m = copy ? &mjs->owned_strings : &mjs->foreign_strings;
  offset = m->len;

  if (len == ~((size_t) 0)) len = strlen(p);

  if (copy) {
    /* owned string */
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
      // } else if ((dict_index = v_find_string_in_dictionary(p, len)) >= 0) {
      //   offset = 0;
      //   GET_VAL_NAN_PAYLOAD(offset)[0] = dict_index;
      //   tag = MJS_TAG_STRING_D;
    } else {
      if (gc_strings_is_gc_needed(mjs)) {
        mjs->need_gc = 1;
      }

      /*
       * Before embedding new string, check if the reallocation is needed.  If
       * so, perform the reallocation by calling `mbuf_resize` manually, since
       * we need to preallocate some extra space (`MJS_STRING_BUF_RESERVE`)
       */
      if ((m->len + len) > m->size) {
        char *prev_buf = m->buf;
        mbuf_resize(m, m->len + len + MJS_STRING_BUF_RESERVE);

        /*
         * There is a corner case: when the source pointer is located within
         * the mbuf. In this case, we should adjust the pointer, because it
         * might have just been reallocated.
         */
        if (p >= prev_buf && p < (prev_buf + m->len)) {
          p += (m->buf - prev_buf);
        }
      }

      embed_string(m, m->len, p, len, EMBSTR_ZERO_TERM);
      tag = MJS_TAG_STRING_O;
    }
  } else {
    /* foreign string */
    if (sizeof(void *) <= 4 && len <= (1 << 15)) {
      /* small foreign strings can fit length and ptr in the mjs_val_t */
      offset = (uint64_t) len << 32 | (uint64_t)(uintptr_t) p;
    } else {
      /* bigger strings need indirection that uses ram */
      size_t pos = m->len;
      size_t llen = cs_varint_llen(len);

      /* allocate space for len and ptr */
      mbuf_insert(m, pos, NULL, llen + sizeof(p));

      cs_varint_encode(len, (uint8_t *) (m->buf + pos), llen);
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
  size_t size = 0, llen;

  if (!mjs_is_string(*v)) {
    goto clean;
  }

  if (tag == MJS_TAG_STRING_I) {
    p = GET_VAL_NAN_PAYLOAD(*v) + 1;
    size = p[-1];
  } else if (tag == MJS_TAG_STRING_5) {
    p = GET_VAL_NAN_PAYLOAD(*v);
    size = 5;
    // } else if (tag == MJS_TAG_STRING_D) {
    //   int index = ((unsigned char *) GET_VAL_NAN_PAYLOAD(*v))[0];
    //   size = v_dictionary_strings[index].len;
    //   p = v_dictionary_strings[index].p;
  } else if (tag == MJS_TAG_STRING_O) {
    size_t offset = (size_t) gc_string_mjs_val_to_offset(*v);
    char *s = mjs->owned_strings.buf + offset;
    uint64_t v = 0;
    if (offset < mjs->owned_strings.len &&
        cs_varint_decode((uint8_t *) s, mjs->owned_strings.len - offset, &v,
                         &llen)) {
      size = v;
      p = s + llen;
    } else {
      goto clean;
    }
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
      uint64_t v = 0;
      if (offset < mjs->foreign_strings.len &&
          cs_varint_decode((uint8_t *) s, mjs->foreign_strings.len - offset, &v,
                           &llen)) {
        size = v;
        memcpy((char **) &p, s + llen, sizeof(p));
      } else {
        goto clean;
      }
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
  const char *s;
  if (len == (size_t) ~0) len = strlen(b);
  s = mjs_get_string(mjs, a, &n);
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

MJS_PRIVATE mjs_err_t
str_to_ulong(struct mjs *mjs, mjs_val_t v, int *ok, unsigned long *res) {
  enum mjs_err ret = MJS_OK;
  size_t len = 0;
  const char *p = mjs_get_string(mjs, &v, &len);
  *res = cstr_to_ulong(p, len, ok);

  return ret;
}

MJS_PRIVATE int s_cmp(struct mjs *mjs, mjs_val_t a, mjs_val_t b) {
  size_t a_len, b_len;
  const char *a_ptr, *b_ptr;

  a_ptr = mjs_get_string(mjs, &a, &a_len);
  b_ptr = mjs_get_string(mjs, &b, &b_len);

  if (a_len == b_len) {
    return memcmp(a_ptr, b_ptr, a_len);
  }
  if (a_len > b_len) {
    return 1;
  } else if (a_len < b_len) {
    return -1;
  } else {
    return 0;
  }
}

MJS_PRIVATE mjs_val_t s_concat(struct mjs *mjs, mjs_val_t a, mjs_val_t b) {
  size_t a_len, b_len, res_len;
  const char *a_ptr, *b_ptr, *res_ptr;
  mjs_val_t res;

  /* Find out lengths of both srtings */
  a_ptr = mjs_get_string(mjs, &a, &a_len);
  b_ptr = mjs_get_string(mjs, &b, &b_len);

  /* Create a placeholder string */
  res = mjs_mk_string(mjs, NULL, a_len + b_len, 1);

  /* mjs_mk_string() may have reallocated mbuf - revalidate pointers */
  a_ptr = mjs_get_string(mjs, &a, &a_len);
  b_ptr = mjs_get_string(mjs, &b, &b_len);

  /* Copy strings into the placeholder */
  res_ptr = mjs_get_string(mjs, &res, &res_len);
  memcpy((char *) res_ptr, a_ptr, a_len);
  memcpy((char *) res_ptr + a_len, b_ptr, b_len);

  return res;
}

MJS_PRIVATE void mjs_string_slice(struct mjs *mjs) {
  int nargs = mjs_nargs(mjs);
  mjs_val_t ret = mjs_mk_number(mjs, 0);
  mjs_val_t beginSlice_v = MJS_UNDEFINED;
  mjs_val_t endSlice_v = MJS_UNDEFINED;
  int beginSlice = 0;
  int endSlice = 0;
  size_t size;
  const char *s = NULL;

  /* get string from `this` */
  if (!mjs_check_arg(mjs, -1 /*this*/, "this", MJS_TYPE_STRING, NULL)) {
    goto clean;
  }
  s = mjs_get_string(mjs, &mjs->vals.this_obj, &size);

  /* get idx from arg 0 */
  if (!mjs_check_arg(mjs, 0, "beginSlice", MJS_TYPE_NUMBER, &beginSlice_v)) {
    goto clean;
  }
  beginSlice = mjs_normalize_idx(mjs_get_int(mjs, beginSlice_v), size);

  if (nargs >= 2) {
    /* endSlice is given; use it */
    /* get idx from arg 0 */
    if (!mjs_check_arg(mjs, 1, "endSlice", MJS_TYPE_NUMBER, &endSlice_v)) {
      goto clean;
    }
    endSlice = mjs_normalize_idx(mjs_get_int(mjs, endSlice_v), size);
  } else {
    /* endSlice is not given; assume the end of the string */
    endSlice = size;
  }

  if (endSlice < beginSlice) {
    endSlice = beginSlice;
  }

  ret = mjs_mk_string(mjs, s + beginSlice, endSlice - beginSlice, 1);

clean:
  mjs_return(mjs, ret);
}

MJS_PRIVATE void mjs_string_index_of(struct mjs *mjs) {
  mjs_val_t ret = mjs_mk_number(mjs, -1);
  mjs_val_t substr_v = MJS_UNDEFINED;
  mjs_val_t idx_v = MJS_UNDEFINED;
  int idx = 0;
  const char *str = NULL, *substr = NULL;
  size_t str_len = 0, substr_len = 0;

  if (!mjs_check_arg(mjs, -1 /* this */, "this", MJS_TYPE_STRING, NULL)) {
    goto clean;
  }
  str = mjs_get_string(mjs, &mjs->vals.this_obj, &str_len);

  if (!mjs_check_arg(mjs, 0, "searchValue", MJS_TYPE_STRING, &substr_v)) {
    goto clean;
  }
  substr = mjs_get_string(mjs, &substr_v, &substr_len);
  if (mjs_nargs(mjs) > 1) {
    if (!mjs_check_arg(mjs, 1, "fromIndex", MJS_TYPE_NUMBER, &idx_v)) {
      goto clean;
    }
    idx = mjs_get_int(mjs, idx_v);
    if (idx < 0) idx = 0;
    if ((size_t) idx > str_len) idx = str_len;
  }
  {
    const char *substr_p;
    struct mg_str mgstr, mgsubstr;
    mgstr.p = str + idx;
    mgstr.len = str_len - idx;
    mgsubstr.p = substr;
    mgsubstr.len = substr_len;
    substr_p = mg_strstr(mgstr, mgsubstr);
    if (substr_p != NULL) {
      ret = mjs_mk_number(mjs, (int) (substr_p - str));
    }
  }

clean:
  mjs_return(mjs, ret);
}

MJS_PRIVATE void mjs_string_char_code_at(struct mjs *mjs) {
  mjs_val_t ret = MJS_UNDEFINED;
  mjs_val_t idx_v = MJS_UNDEFINED;
  int idx = 0;
  size_t size;
  const char *s = NULL;

  /* get string from `this` */
  if (!mjs_check_arg(mjs, -1 /*this*/, "this", MJS_TYPE_STRING, NULL)) {
    goto clean;
  }
  s = mjs_get_string(mjs, &mjs->vals.this_obj, &size);

  /* get idx from arg 0 */
  if (!mjs_check_arg(mjs, 0, "index", MJS_TYPE_NUMBER, &idx_v)) {
    goto clean;
  }
  idx = mjs_normalize_idx(mjs_get_int(mjs, idx_v), size);
  if (idx >= 0 && idx < (int) size) {
    ret = mjs_mk_number(mjs, ((unsigned char *) s)[idx]);
  }

clean:
  mjs_return(mjs, ret);
}

MJS_PRIVATE void mjs_mkstr(struct mjs *mjs) {
  int nargs = mjs_nargs(mjs);
  mjs_val_t ret = MJS_UNDEFINED;

  char *ptr = NULL;
  int offset = 0;
  int len = 0;
  int copy = 0;

  mjs_val_t ptr_v = MJS_UNDEFINED;
  mjs_val_t offset_v = MJS_UNDEFINED;
  mjs_val_t len_v = MJS_UNDEFINED;
  mjs_val_t copy_v = MJS_UNDEFINED;

  if (nargs == 2) {
    ptr_v = mjs_arg(mjs, 0);
    len_v = mjs_arg(mjs, 1);
  } else if (nargs == 3) {
    ptr_v = mjs_arg(mjs, 0);
    offset_v = mjs_arg(mjs, 1);
    len_v = mjs_arg(mjs, 2);
  } else if (nargs == 4) {
    ptr_v = mjs_arg(mjs, 0);
    offset_v = mjs_arg(mjs, 1);
    len_v = mjs_arg(mjs, 2);
    copy_v = mjs_arg(mjs, 3);
  } else {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR,
                       "mkstr takes 2, 3 or 4 arguments: (ptr, len), (ptr, "
                       "offset, len) or (ptr, offset, len, copy)");
    goto clean;
  }

  if (!mjs_is_foreign(ptr_v)) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "ptr should be a foreign pointer");
    goto clean;
  }

  if (offset_v != MJS_UNDEFINED && !mjs_is_number(offset_v)) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "offset should be a number");
    goto clean;
  }

  if (!mjs_is_number(len_v)) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "len should be a number");
    goto clean;
  }

  copy = mjs_is_truthy(mjs, copy_v);

  /* all arguments are fine */

  ptr = (char *) mjs_get_ptr(mjs, ptr_v);
  if (offset_v != MJS_UNDEFINED) {
    offset = mjs_get_int(mjs, offset_v);
  }
  len = mjs_get_int(mjs, len_v);

  ret = mjs_mk_string(mjs, ptr + offset, len, copy);

clean:
  mjs_return(mjs, ret);
}

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
  size_t k = cs_varint_llen(n);

  /* total length: varing length + string len + zero-term */
  size_t tot_len = k + n + !!(flags & EMBSTR_ZERO_TERM);

  /* Allocate buffer */
  mbuf_insert(m, offset, NULL, tot_len);

  /* Fixup p if it was relocated by mbuf_insert() above */
  if (p_backed_by_mbuf) {
    p += m->buf - old_base;
  }

  /* Write length */
  cs_varint_encode(n, (unsigned char *) m->buf + offset, k);

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
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_tok.c"
#endif

#include <stdlib.h>
#include <string.h>

/* Amalgamated: #include "common/cs_dbg.h" */
/* Amalgamated: #include "mjs/src/mjs_tok.h" */

MJS_PRIVATE void pinit(const char *file_name, const char *buf,
                       struct pstate *p) {
  memset(p, 0, sizeof(*p));
  p->line_no = 1;
  p->last_emitted_line_no = 1;
  p->file_name = file_name;
  p->buf = p->pos = buf;
  mbuf_init(&p->offset_lineno_map, 0);
}

// We're not relying on the target libc ctype, as it may incorrectly
// handle negative arguments, e.g. isspace(-1).
static int mjs_is_space(int c) {
  return c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == '\f' ||
         c == '\v';
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
  if (p->pos[1] != '\0' && strchr(second_chars, p->pos[1]) != NULL) {
    p->tok.len++;
    p->pos++;
    return p->pos[-1] << 8 | p->pos[0];
  }
  return p->pos[0];
}

// Try to parse a token that takes exactly 3 chars.
static int longtok3(struct pstate *p, char a, char b, char c) {
  if (p->pos[0] == a && p->pos[1] == b && p->pos[2] == c) {
    p->tok.len += 2;
    p->pos += 2;
    return p->pos[-2] << 16 | p->pos[-1] << 8 | p->pos[0];
  }
  return TOK_EOF;
}

// Try to parse a token that takes exactly 4 chars.
static int longtok4(struct pstate *p, char a, char b, char c, char d) {
  if (p->pos[0] == a && p->pos[1] == b && p->pos[2] == c && p->pos[3] == d) {
    p->tok.len += 3;
    p->pos += 3;
    return p->pos[-3] << 24 | p->pos[-2] << 16 | p->pos[-1] << 8 | p->pos[0];
  }
  return TOK_EOF;
}

static int getnum(struct pstate *p) {
  if (p->pos[0] == '0' && p->pos[1] == 'x') {
    // MSVC6 strtod cannot parse 0x... numbers, thus this ugly workaround.
    strtoul(p->pos + 2, (char **) &p->pos, 16);
  } else {
    strtod(p->pos, (char **) &p->pos);
  }
  p->tok.len = p->pos - p->tok.ptr;
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
  p->tok.len = p->pos - p->tok.ptr;
  p->pos--;
  return TOK_IDENT;
}

static int getstr(struct pstate *p) {
  int quote = *p->pos++;
  p->tok.ptr++;
  while (p->pos[0] != '\0' && p->pos[0] != quote) {
    if (p->pos[0] == '\\' && p->pos[1] != '\0' &&
        (p->pos[1] == quote || strchr("bfnrtv\\", p->pos[1]) != NULL)) {
      p->pos += 2;
    } else {
      p->pos++;
    }
  }
  p->tok.len = p->pos - p->tok.ptr;
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

static int ptranslate(int tok) {
#define DT(a, b) ((a) << 8 | (b))
#define TT(a, b, c) ((a) << 16 | (b) << 8 | (c))
#define QT(a, b, c, d) ((a) << 24 | (b) << 16 | (c) << 8 | (d))
  /* Map token ID produced by mjs_tok.c to token ID produced by lemon */
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
    case '<': return TOK_LT;
    case '>': return TOK_GT;
    case DT('<','<'): return TOK_LSHIFT;
    case DT('>','>'): return TOK_RSHIFT;
    case DT('-','-'): return TOK_MINUS_MINUS;
    case DT('+','+'): return TOK_PLUS_PLUS;
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
    case TT('=','=','='): return TOK_EQ_EQ;
    case TT('!','=','='): return TOK_NE_NE;
    case TT('<','<','='): return TOK_LSHIFT_ASSIGN;
    case TT('>','>','='): return TOK_RSHIFT_ASSIGN;
    case TT('>','>','>'): return TOK_URSHIFT;
    case QT('>','>','>','='): return TOK_URSHIFT_ASSIGN;
  }
  /* clang-format on */
  return tok;
}

MJS_PRIVATE int pnext(struct pstate *p) {
  int tmp, tok = TOK_INVALID;

  skip_spaces_and_comments(p);
  p->tok.ptr = p->pos;
  p->tok.len = 1;

  if (p->pos[0] == '\0') {
    tok = TOK_EOF;
  } else if (mjs_is_digit(p->pos[0])) {
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
    tok += is_reserved_word_token(p->tok.ptr, p->tok.len);
  } else if (strchr(",.:;{}[]()?", p->pos[0]) != NULL) {
    tok = p->pos[0];
  } else if ((tmp = longtok3(p, '<', '<', '=')) != TOK_EOF ||
             (tmp = longtok3(p, '>', '>', '=')) != TOK_EOF ||
             (tmp = longtok4(p, '>', '>', '>', '=')) != TOK_EOF ||
             (tmp = longtok3(p, '>', '>', '>')) != TOK_EOF ||
             (tmp = longtok3(p, '=', '=', '=')) != TOK_EOF ||
             (tmp = longtok3(p, '!', '=', '=')) != TOK_EOF ||
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
  LOG(LL_VERBOSE_DEBUG, ("  --> %d [%.*s]", tok, p->tok.len, p->tok.ptr));
  p->prev_tok = p->tok.tok;
  p->tok.tok = ptranslate(tok);
  return p->tok.tok;
}
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_util.c"
#endif

/* Amalgamated: #include "common/cs_varint.h" */
/* Amalgamated: #include "frozen.h" */
/* Amalgamated: #include "mjs/src/mjs_array.h" */
/* Amalgamated: #include "mjs/src/mjs_bcode.h" */
/* Amalgamated: #include "mjs/src/mjs_core.h" */
/* Amalgamated: #include "mjs/src/mjs_internal.h" */
/* Amalgamated: #include "mjs/src/mjs_object.h" */
/* Amalgamated: #include "mjs/src/mjs_primitive.h" */
/* Amalgamated: #include "mjs/src/mjs_string.h" */
/* Amalgamated: #include "mjs/src/mjs_util.h" */
/* Amalgamated: #include "mjs/src/mjs_tok.h" */

const char *mjs_typeof(mjs_val_t v) {
  return mjs_stringify_type(mjs_get_type(v));
}

MJS_PRIVATE const char *mjs_stringify_type(enum mjs_type t) {
  switch (t) {
    case MJS_TYPE_NUMBER:
      return "number";
    case MJS_TYPE_BOOLEAN:
      return "boolean";
    case MJS_TYPE_STRING:
      return "string";
    case MJS_TYPE_OBJECT_ARRAY:
      return "array";
    case MJS_TYPE_OBJECT_GENERIC:
      return "object";
    case MJS_TYPE_FOREIGN:
      return "foreign_ptr";
    case MJS_TYPE_OBJECT_FUNCTION:
      return "function";
    case MJS_TYPE_NULL:
      return "null";
    case MJS_TYPE_UNDEFINED:
      return "undefined";
    default:
      return "???";
  }
}

void mjs_jprintf(mjs_val_t v, struct mjs *mjs, struct json_out *out) {
  if (mjs_is_number(v)) {
    double iv, d = mjs_get_double(mjs, v);
    if (modf(d, &iv) == 0) {
      json_printf(out, "%" INT64_FMT, (int64_t) d);
    } else {
      json_printf(out, "%f", mjs_get_double(mjs, v));
    }
  } else if (mjs_is_boolean(v)) {
    json_printf(out, "%s", mjs_get_bool(mjs, v) ? "true" : "false");
  } else if (mjs_is_string(v)) {
    size_t i, size;
    const char *s = mjs_get_string(mjs, &v, &size);
    for (i = 0; i < size; i++) {
      int ch = ((unsigned char *) s)[i];
      if (isprint(ch)) {
        json_printf(out, "%c", ch);
      } else {
        json_printf(out, "%s%02x", "\\x", ch);
      }
    }
  } else if (mjs_is_array(v)) {
    json_printf(out, "%s", "<array>");
  } else if (mjs_is_object(v)) {
    json_printf(out, "%s", "<object>");
  } else if (mjs_is_foreign(v)) {
    json_printf(out, "%s%lx%s", "<foreign_ptr@",
                (unsigned long) (uintptr_t) mjs_get_ptr(mjs, v), ">");
  } else if (mjs_is_function(v)) {
    json_printf(out, "%s%d%s", "<function@", (int) mjs_get_func_addr(v), ">");
  } else if (mjs_is_null(v)) {
    json_printf(out, "%s", "null");
  } else if (mjs_is_undefined(v)) {
    json_printf(out, "%s", "undefined");
  } else {
    json_printf(out, "%s%" INT64_FMT "%s", "<???", (int64_t) v, ">");
  }
}

void mjs_sprintf(mjs_val_t v, struct mjs *mjs, char *buf, size_t n) {
  struct json_out out = JSON_OUT_BUF(buf, n);
  mjs_jprintf(v, mjs, &out);
}

void mjs_fprintf(mjs_val_t v, struct mjs *mjs, FILE *fp) {
  struct json_out out = JSON_OUT_FILE(fp);
  mjs_jprintf(v, mjs, &out);
}

#if MJS_ENABLE_DEBUG

MJS_PRIVATE const char *opcodetostr(uint8_t opcode) {
  static const char *names[] = {
      "NOP", "DROP", "DUP", "SWAP", "JMP", "JMP_TRUE", "JMP_NEUTRAL_TRUE",
      "JMP_FALSE", "JMP_NEUTRAL_FALSE", "FIND_SCOPE", "PUSH_SCOPE", "PUSH_STR",
      "PUSH_TRUE", "PUSH_FALSE", "PUSH_INT", "PUSH_DBL", "PUSH_NULL",
      "PUSH_UNDEF", "PUSH_OBJ", "PUSH_ARRAY", "PUSH_FUNC", "PUSH_THIS", "GET",
      "CREATE", "EXPR", "APPEND", "SET_ARG", "NEW_SCOPE", "DEL_SCOPE", "CALL",
      "RETURN", "LOOP", "BREAK", "CONTINUE", "SETRETVAL", "EXIT", "BCODE_HDR",
      "ARGS", "FOR_IN_NEXT",
  };
  const char *name = "???";
  assert(ARRAY_SIZE(names) == OP_MAX);
  if (opcode < ARRAY_SIZE(names)) name = names[opcode];
  return name;
}

MJS_PRIVATE size_t mjs_disasm_single(const uint8_t *code, size_t i) {
  char buf[40];
  size_t start_i = i;
  size_t llen;
  uint64_t n;

  snprintf(buf, sizeof(buf), "\t%-3u %-8s", (unsigned) i, opcodetostr(code[i]));

  switch (code[i]) {
    case OP_PUSH_FUNC: {
      cs_varint_decode(&code[i + 1], ~0, &n, &llen);
      LOG(LL_VERBOSE_DEBUG, ("%s %04u", buf, (unsigned) (i - n)));
      i += llen;
      break;
    }
    case OP_PUSH_INT: {
      cs_varint_decode(&code[i + 1], ~0, &n, &llen);
      LOG(LL_VERBOSE_DEBUG, ("%s\t%lu", buf, (unsigned long) n));
      i += llen;
      break;
    }
    case OP_SET_ARG: {
      size_t llen2;
      uint64_t arg_no;
      cs_varint_decode(&code[i + 1], ~0, &arg_no, &llen);
      cs_varint_decode(&code[i + llen + 1], ~0, &n, &llen2);
      LOG(LL_VERBOSE_DEBUG, ("%s\t[%.*s] %u", buf, (int) n,
                             code + i + 1 + llen + llen2, (unsigned) arg_no));
      i += llen + llen2 + n;
      break;
    }
    case OP_PUSH_STR:
    case OP_PUSH_DBL: {
      cs_varint_decode(&code[i + 1], ~0, &n, &llen);
      LOG(LL_VERBOSE_DEBUG, ("%s\t[%.*s]", buf, (int) n, code + i + 1 + llen));
      i += llen + n;
      break;
    }
    case OP_JMP:
    case OP_JMP_TRUE:
    case OP_JMP_NEUTRAL_TRUE:
    case OP_JMP_FALSE:
    case OP_JMP_NEUTRAL_FALSE: {
      cs_varint_decode(&code[i + 1], ~0, &n, &llen);
      LOG(LL_VERBOSE_DEBUG,
          ("%s\t%u", buf,
           (unsigned) (i + n + llen +
                       1 /* becaue i will be incremented on the usual terms */)));
      i += llen;
      break;
    }
    case OP_LOOP: {
      size_t l1, l2;
      uint64_t n1, n2;
      cs_varint_decode(&code[i + 1], ~0, &n1, &l1);
      cs_varint_decode(&code[i + l1 + 1], ~0, &n2, &l2);
      LOG(LL_VERBOSE_DEBUG,
          ("%s\tB:%lu C:%lu (%d)", buf,
           (unsigned long) (i + 1 /* OP_LOOP */ + l1 + n1),
           (unsigned long) (i + 1 /* OP_LOOP */ + l1 + l2 + n2), (int) i));
      i += l1 + l2;
      break;
    }
    case OP_EXPR: {
      int op = code[i + 1];
      const char *name = "???";
      /* clang-format off */
      switch (op) {
        case TOK_DOT:       name = "."; break;
        case TOK_MINUS:     name = "-"; break;
        case TOK_PLUS:      name = "+"; break;
        case TOK_MUL:       name = "*"; break;
        case TOK_DIV:       name = "/"; break;
        case TOK_REM:       name = "%"; break;
        case TOK_XOR:       name = "^"; break;
        case TOK_AND:       name = "&"; break;
        case TOK_OR:        name = "|"; break;
        case TOK_LSHIFT:    name = "<<"; break;
        case TOK_RSHIFT:    name = ">>"; break;
        case TOK_URSHIFT:   name = ">>>"; break;
        case TOK_UNARY_MINUS:   name = "- (unary)"; break;
        case TOK_UNARY_PLUS:    name = "+ (unary)"; break;
        case TOK_NOT:       name = "!"; break;
        case TOK_TILDA:     name = "~"; break;
        case TOK_EQ:        name = "=="; break;
        case TOK_NE:        name = "!="; break;
        case TOK_EQ_EQ:     name = "==="; break;
        case TOK_NE_NE:     name = "!=="; break;
        case TOK_LT:        name = "<"; break;
        case TOK_GT:        name = ">"; break;
        case TOK_LE:        name = "<="; break;
        case TOK_GE:        name = ">="; break;
        case TOK_ASSIGN:    name = "="; break;
        case TOK_POSTFIX_PLUS:  name = "++ (postfix)"; break;
        case TOK_POSTFIX_MINUS: name = "-- (postfix)"; break;
        case TOK_MINUS_MINUS:   name = "--"; break;
        case TOK_PLUS_PLUS:     name = "++"; break;
        case TOK_LOGICAL_AND:   name = "&&"; break;
        case TOK_LOGICAL_OR:    name = "||"; break;
        case TOK_KEYWORD_TYPEOF:  name = "typeof"; break;
        case TOK_PLUS_ASSIGN:     name = "+="; break;
        case TOK_MINUS_ASSIGN:    name = "-="; break;
        case TOK_MUL_ASSIGN:      name = "*="; break;
        case TOK_DIV_ASSIGN:      name = "/="; break;
        case TOK_REM_ASSIGN:      name = "%="; break;
        case TOK_XOR_ASSIGN:      name = "^="; break;
        case TOK_AND_ASSIGN:      name = "&="; break;
        case TOK_OR_ASSIGN:       name = "|="; break;
        case TOK_LSHIFT_ASSIGN:   name = "<<="; break;
        case TOK_RSHIFT_ASSIGN:   name = ">>="; break;
        case TOK_URSHIFT_ASSIGN:  name = ">>>="; break;
      }
      /* clang-format on */
      LOG(LL_VERBOSE_DEBUG, ("%s\t%s", buf, name));
      i++;
      break;
    }
    case OP_BCODE_HEADER: {
      size_t start = 0;
      mjs_header_item_t map_offset = 0, total_size = 0;
      start = i;
      memcpy(&total_size, &code[i + 1], sizeof(total_size));
      memcpy(&map_offset,
             &code[i + 1 + MJS_HDR_ITEM_MAP_OFFSET * sizeof(total_size)],
             sizeof(map_offset));
      i += sizeof(mjs_header_item_t) * MJS_HDR_ITEMS_CNT;
      LOG(LL_VERBOSE_DEBUG, ("%s\t[%s] end:%lu map_offset: %lu", buf,
                             &code[i + 1], (unsigned long) start + total_size,
                             (unsigned long) start + map_offset));
      i += strlen((char *) (code + i + 1)) + 1;
      break;
    }
    default:
      LOG(LL_VERBOSE_DEBUG, ("%s", buf));
      break;
  }
  return i - start_i;
}

void mjs_disasm(const uint8_t *code, size_t len) {
  size_t i, start = 0;
  mjs_header_item_t map_offset = 0, total_size = 0;

  for (i = 0; i < len; i++) {
    size_t delta = mjs_disasm_single(code, i);
    if (code[i] == OP_BCODE_HEADER) {
      start = i;
      memcpy(&total_size, &code[i + 1], sizeof(total_size));
      memcpy(&map_offset,
             &code[i + 1 + MJS_HDR_ITEM_MAP_OFFSET * sizeof(total_size)],
             sizeof(map_offset));
    }

    i += delta;

    if (map_offset > 0 && i == start + map_offset) {
      i = start + total_size - 1;
      continue;
    }
  }
}

static void mjs_dump_obj_stack(const char *name, const struct mbuf *m,
                               struct mjs *mjs) {
  char buf[50];
  size_t i, n;
  n = mjs_stack_size(m);
  LOG(LL_VERBOSE_DEBUG, ("%12s (%d elems): ", name, (int) n));
  for (i = 0; i < n; i++) {
    mjs_sprintf(((mjs_val_t *) m->buf)[i], mjs, buf, sizeof(buf));
    LOG(LL_VERBOSE_DEBUG, ("%34s", buf));
  }
}

void mjs_dump(struct mjs *mjs, int do_disasm) {
  LOG(LL_VERBOSE_DEBUG, ("------- MJS VM DUMP BEGIN"));
  mjs_dump_obj_stack("DATA_STACK", &mjs->stack, mjs);
  mjs_dump_obj_stack("CALL_STACK", &mjs->call_stack, mjs);
  mjs_dump_obj_stack("SCOPES", &mjs->scopes, mjs);
  mjs_dump_obj_stack("LOOP_OFFSETS", &mjs->loop_addresses, mjs);
  mjs_dump_obj_stack("ARG_STACK", &mjs->arg_stack, mjs);
  if (do_disasm) {
    int parts_cnt = mjs_bcode_parts_cnt(mjs);
    int i;
    LOG(LL_VERBOSE_DEBUG, ("%23s", "CODE:"));
    for (i = 0; i < parts_cnt; i++) {
      struct mjs_bcode_part *bp = mjs_bcode_part_get(mjs, i);
      mjs_disasm((uint8_t *) bp->data.p, bp->data.len);
    }
  }
  LOG(LL_VERBOSE_DEBUG, ("------- MJS VM DUMP END"));
}

MJS_PRIVATE int mjs_check_arg(struct mjs *mjs, int arg_num,
                              const char *arg_name, enum mjs_type expected_type,
                              mjs_val_t *parg) {
  mjs_val_t arg = MJS_UNDEFINED;
  enum mjs_type actual_type;

  if (arg_num >= 0) {
    int nargs = mjs_nargs(mjs);
    if (nargs < arg_num + 1) {
      mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing argument %s", arg_name);
      return 0;
    }

    arg = mjs_arg(mjs, arg_num);
  } else {
    /* use `this` */
    arg = mjs->vals.this_obj;
  }

  actual_type = mjs_get_type(arg);
  if (actual_type != expected_type) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "%s should be a %s, %s given",
                       arg_name, mjs_stringify_type(expected_type),
                       mjs_stringify_type(actual_type));
    return 0;
  }

  if (parg != NULL) {
    *parg = arg;
  }

  return 1;
}

MJS_PRIVATE int mjs_normalize_idx(int idx, int size) {
  if (idx < 0) {
    idx = size + idx;
    if (idx < 0) {
      idx = 0;
    }
  }
  if (idx > size) {
    idx = size;
  }
  return idx;
}

MJS_PRIVATE const char *mjs_get_bcode_filename(struct mjs *mjs,
                                               struct mjs_bcode_part *bp) {
  (void) mjs;
  return bp->data.p + 1 /* OP_BCODE_HEADER */ +
         sizeof(mjs_header_item_t) * MJS_HDR_ITEMS_CNT;
}

const char *mjs_get_bcode_filename_by_offset(struct mjs *mjs, int offset) {
  const char *ret = NULL;
  struct mjs_bcode_part *bp = mjs_bcode_part_get_by_offset(mjs, offset);
  if (bp != NULL) {
    ret = mjs_get_bcode_filename(mjs, bp);
  }
  return ret;
}

int mjs_get_lineno_by_offset(struct mjs *mjs, int offset) {
  size_t llen;
  uint64_t map_len;
  int prev_line_no, ret = 1;
  struct mjs_bcode_part *bp = mjs_bcode_part_get_by_offset(mjs, offset);
  uint8_t *p, *pe;
  if (bp != NULL) {
    mjs_header_item_t map_offset, bcode_offset;
    memcpy(&map_offset, bp->data.p + 1 /* OP_BCODE_HEADER */ +
                            sizeof(mjs_header_item_t) * MJS_HDR_ITEM_MAP_OFFSET,
           sizeof(map_offset));

    memcpy(&bcode_offset,
           bp->data.p + 1 /* OP_BCODE_HEADER */ +
               sizeof(mjs_header_item_t) * MJS_HDR_ITEM_BCODE_OFFSET,
           sizeof(bcode_offset));

    offset -= (1 /* OP_BCODE_HEADER */ + bcode_offset) + bp->start_idx;

    /* get pointer to the length of the map followed by the map itself */
    p = (uint8_t *) bp->data.p + 1 /* OP_BCODE_HEADER */ + map_offset;

    cs_varint_decode(p, ~0, &map_len, &llen);
    p += llen;
    pe = p + map_len;

    prev_line_no = 1;
    while (p < pe) {
      uint64_t cur_offset, line_no;
      cs_varint_decode(p, ~0, &cur_offset, &llen);
      p += llen;
      cs_varint_decode(p, ~0, &line_no, &llen);
      p += llen;

      if (cur_offset >= (uint64_t) offset) {
        ret = prev_line_no;
        break;
      }
      prev_line_no = line_no;
    }
  }
  return ret;
}

int mjs_get_offset_by_call_frame_num(struct mjs *mjs, int cf_num) {
  int ret = -1;
  if (cf_num == 0) {
    /* Return current bcode offset */
    ret = mjs->cur_bcode_offset;
  } else if (cf_num > 0 &&
             mjs->call_stack.len >=
                 sizeof(mjs_val_t) * CALL_STACK_FRAME_ITEMS_CNT * cf_num) {
    /* Get offset from the call_stack */
    int pos = CALL_STACK_FRAME_ITEM_RETURN_ADDR +
              CALL_STACK_FRAME_ITEMS_CNT * (cf_num - 1);
    mjs_val_t val = *vptr(&mjs->call_stack, -1 - pos);
    ret = mjs_get_int(mjs, val);
  }
  return ret;
}

#endif
#endif /* MJS_EXPORT_INTERNAL_HEADERS */
