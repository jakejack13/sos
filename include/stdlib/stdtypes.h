/** 
 * Library of functions for standard types and constants
 */

#ifndef _STDTYPES_H_
#define _STDTYPES_H_

#ifndef USER
/** Size type */
typedef unsigned int size_t;
/** Unsigned 64 bit integer */
typedef unsigned long long uint64_t;
/** nullptr */
#define NULL (void *) 0
#else
#include <stddef.h>
#endif

enum bool_e {
    false = 0,
    true = 1,
};
/** Boolean type */
typedef enum bool_e bool;

#endif //_STDTYPES_H_