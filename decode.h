/*
 * Project     : LSB-Steganography-project
 * File        : decode.h
 * Author      : Supriya Velishetty
 * Description : Image Steganography using C programming and LSB technique.
 */

#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

/* 
 * Structure to store information required for
 * decoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _DecodeInfo
{
    /* Source Image info */
    char *src_image_fname;
    FILE *fptr_src_image;
    uint image_capacity;
    uint bits_per_pixel;
    char image_data[MAX_IMAGE_BUF_SIZE];

    /* Secret File Info */
    char secret_fname[20];
    FILE *fptr_secret;
    char extn_secret_file[MAX_FILE_SUFFIX+1];
    char secret_data[MAX_SECRET_BUF_SIZE];
    long size_secret_file;
    char *decode_secret_data;
    char *magicstring;
    int extension_size;
    /* Stego Image Info */
    char *stego_image_fname;
    FILE *fptr_stego_image;

} DecodeInfo;


/* decoding function prototype */

/* Check operation type */
OperationType check_operation_type(char *argv[]); // Completed

/* Read and validate decode args from argv */
Status decode_read_and_validate_decode_args(char *argv[], DecodeInfo *dncInfo); //completed

/* Perform the decoding */
Status do_decoding(DecodeInfo *dncInfo);

/* Get File pointers for i/p and o/p files */
Status open_decode_files(DecodeInfo *dncInfo);

/* Store Magic String */
Status decode_magic_string(char *magic_string, DecodeInfo *dncInfo);

/* decode secret file extenstion size*/
Status decode_secret_file_extn_size(long file_size, DecodeInfo *dncInfo);
/* decode secret file extenstion */
Status decode_secret_file_extn(char *file_extn, DecodeInfo *dncInfo);

/* decode secret file size */
Status decode_secret_file_size(long file_size, DecodeInfo *dncInfo);
/* decode secret file data*/
Status decode_secret_file_data(DecodeInfo *dncInfo);

/* decode function, which does the real decoding */
Status decode_data_to_image(char *data, int size,DecodeInfo *dncInfo );

/* decode a byte from LSB of image data array */
Status decode_byte_to_lsb( char *image_buffer);

/*decode size to lsb*/
Status decode_size_to_lsb(long size, DecodeInfo *dncInfo);

#endif
