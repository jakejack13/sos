/** Configuration macros and constants */

#ifndef _CONFIG_H_
#define _CONFIG_H_

/** 1 if standard io should use UART */
#define CONFIG_UART_IO 0
/** 1 if hello world kernel program should be used (useful for testing) */
#define HELLO_WORLD 0
/** 1 if the main shell program should be used */
#define SHELL 1
/** The size of the pagespace requested from the host operating system in userspace mode */
#define USER_PAGESPACE_SIZE 1024 * 1024 * 512

#endif //_CONFIG_H_