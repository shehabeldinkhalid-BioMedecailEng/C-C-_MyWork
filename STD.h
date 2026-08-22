/*
 * STD.h
 * -----
 * Standard, platform-independent type definitions used across the whole
 * project. Every other file includes this instead of using int/char/short
 * directly, so if we ever port this code to a different compiler/platform,
 * we only need to change these typedefs in ONE place.
 */

#ifndef STD_H
#define STD_H

typedef unsigned char   uint8;
typedef char            int8;
typedef unsigned short  uint16;
typedef short           int16;
typedef unsigned int    uint32;
typedef int             int32;

typedef enum
{
    false,
    true
} bool;

#endif /* STD_H */
