/*
 * Project     : LSB-Steganography-project
 * File        : types.h
 * Author      : Supriya Velishetty
 * Description : Image Steganography using C programming and LSB technique.
 */

#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;

/* Status will be used in fn. return type */
typedef enum
{
    e_success,
    e_failure
} Status;

typedef enum
{
    e_encode,
    e_decode,
    e_unsupported
} OperationType;

#endif
