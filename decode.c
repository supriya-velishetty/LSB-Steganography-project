/*
 * Project     : LSB-Steganography-project
 * File        : decode.c
 * Author      : Supriya Velishetty
 * Description : Image Steganography using C programming and LSB technique.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decode.h"
#include "common.h"
#include "types.h"

/* Open stego image and output secret file */
Status open_decode_files(DecodeInfo *dncInfo)
{
    dncInfo->fptr_stego_image = fopen(dncInfo->stego_image_fname, "rb");
    if (dncInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        return e_failure;
    }

    dncInfo->fptr_secret = fopen(dncInfo->secret_fname, "wb");
    if (dncInfo->fptr_secret == NULL)
    {
        perror("fopen");
        return e_failure;
    }
    return e_success;
}

/* Decode a byte from LSBs */
Status decode_byte_to_lsb(char *image_buffer)
{
    char ch = 0;

    for (int i = 0; i < 8; i++)
    {
        ch |= (image_buffer[i] & 1) << i;
    }

    image_buffer[0] = ch;
    return e_success;
}

/* Decode size (32 bits) from LSB */
Status decode_size_to_lsb(long size, DecodeInfo *dncInfo)
{
    unsigned char ch;
    size = 0;

    for (int i = 0; i < 32; i++)
    {
        fread(&ch, 1, 1, dncInfo->fptr_stego_image);
        size |= ((long)(ch & 1) << i);
    }

    dncInfo->size_secret_file = size;
    return e_success;
}

/* Decode magic string */
Status decode_magic_string(char *magic_string, DecodeInfo *dncInfo)
{
    int len = strlen(MAGIC_STRING);
    char buffer[8];

    for (int i = 0; i < len; i++)
    {
        fread(buffer, 8, 1, dncInfo->fptr_stego_image);
        decode_byte_to_lsb(buffer);
        magic_string[i] = buffer[0];
    }
    magic_string[len] = '\0';

    if (strcmp(magic_string, MAGIC_STRING) != 0)
        return e_failure;

    return e_success;
}

/* Decode secret file extension size */
Status decode_secret_file_extn_size(long file_size, DecodeInfo *dncInfo)
{
    decode_size_to_lsb(file_size, dncInfo);
    dncInfo->extension_size = dncInfo->size_secret_file;
    return e_success;
}

/* Decode secret file extension */
Status decode_secret_file_extn(char *file_extn, DecodeInfo *dncInfo)
{
    char buffer[8];

    for (int i = 0; i < dncInfo->extension_size; i++)
    {
        fread(buffer, 8, 1, dncInfo->fptr_stego_image);
        decode_byte_to_lsb(buffer);
        file_extn[i] = buffer[0];
    }
    file_extn[dncInfo->extension_size] = '\0';

    return e_success;
}

/* Decode secret file size */
Status decode_secret_file_size(long file_size, DecodeInfo *dncInfo)
{
    decode_size_to_lsb(file_size, dncInfo);
    return e_success;
}

/* Decode secret file data */
Status decode_secret_file_data(DecodeInfo *dncInfo)
{
    char buffer[8];

    for (long i = 0; i < dncInfo->size_secret_file; i++)
    {
        fread(buffer, 8, 1, dncInfo->fptr_stego_image);
        decode_byte_to_lsb(buffer);
        fwrite(buffer, 1, 1, dncInfo->fptr_secret);
    }
    return e_success;
}

/* Decode data helper */
Status decode_data_to_image(char *data, int size, DecodeInfo *dncInfo)
{
    char buffer[8];

    for (int i = 0; i < size; i++)
    {
        fread(buffer, 8, 1, dncInfo->fptr_stego_image);
        decode_byte_to_lsb(buffer);
        data[i] = buffer[0];
    }
    return e_success;
}
Status decode_read_and_validate_decode_args(char *argv[], DecodeInfo *dncInfo)
{
    if (argv[2] == NULL)
        return e_failure;

    dncInfo->stego_image_fname = argv[2];

    if (argv[3] != NULL)
        strcpy(dncInfo->secret_fname, argv[3]);
    else
        strcpy(dncInfo->secret_fname, "decoded.txt");

    return e_success;
}
/* Main decoding control */
Status do_decoding(DecodeInfo *dncInfo)
{
    char magic_string[10];

    //printf("---------------------------Decoding started ----------------------\n");

    /* Open files */
    if (open_decode_files(dncInfo) == e_failure)
    {
        printf("Open files failed\n");
        return e_failure;
    }
    printf("Open files is a success\n");

    /* Skip BMP header (must match encode) */
    fseek(dncInfo->fptr_stego_image, 54, SEEK_SET);

    /* Decode magic string */
    if (decode_magic_string(magic_string, dncInfo) == e_failure)
    {
        printf("Decoded magic string mismatch\n");
        return e_failure;
    }
    printf("Decoded magic string successfully\n");

    /* Decode secret file extension size */
    if (decode_secret_file_extn_size(0, dncInfo) == e_failure)
    {
        printf("Decoding secret file extension size failed\n");
        return e_failure;
    }
    printf("Decoded secret file extension size successfully\n");

    /* Decode secret file extension */
    if (decode_secret_file_extn(dncInfo->extn_secret_file, dncInfo) == e_failure)
    {
        printf("Decoding secret file extension failed\n");
        return e_failure;
    }
    printf("Decoded secret file extension successfully\n");

    /* Decode secret file size */
    if (decode_secret_file_size(0, dncInfo) == e_failure)
    {
        printf("Decoding secret file size failed\n");
        return e_failure;
    }
    printf("Decoded secret file size successfully\n");

    /* Decode secret file data */
    if (decode_secret_file_data(dncInfo) == e_failure)
    {
        printf("Decoding secret file data failed\n");
        return e_failure;
    }
    printf("Decoded secret file data successfully\n");

    fclose(dncInfo->fptr_stego_image);
    fclose(dncInfo->fptr_secret);

    printf("Decoding completed successfully\n");
    return e_success;
}


