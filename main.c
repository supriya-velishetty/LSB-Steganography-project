#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "common.h"
#include "types.h"
#include "decode.h"

OperationType check_operation_type(char *argv[])
{
    if(strcmp(argv[1],"-e")==0)
    return e_encode;
    else if(strcmp(argv[1],"-d")==0)
    return e_decode;
    else 
    return e_unsupported;
}

int main(int argc, char *argv[])
{
      if(argc<2)
      {
        printf("Invalid arguments Inputs\n");
        printf("For encoding : ./a.out -e beautiful.bmp secret.txt [stego.bmp]\n");
        printf("for decoding : ./a.out -d stego.bmp [decod.txt]\n");
        return 0;
      }
      OperationType res = check_operation_type(argv);
      if(res == e_encode)
      {
        if(argc<4)
        {
            printf("Not enough arguments\n");
            return 0;
        }
        printf("Selected Encoding\n");
        EncodeInfo encode;
        if(encode_read_and_validate_encode_args(argv,&encode)==e_success)
        {
            printf("Read and validate encode arguments is successful\n");
            printf("---------------------------Encoding started ----------------------\n");
            if(do_encoding(&encode)==e_success)
            {
                printf("Encoding is successful\n");
            }
            else
            {
                printf("Failed to perform encoding\n");
            }
        }
      }
      else if(res==e_decode)
      {
        if(argc<3)
        {
            printf("Not enough arguments\n");
            return 0;
        }
        printf("Selected Decoding\n");
        DecodeInfo decode;
        if (decode_read_and_validate_decode_args(argv, &decode) == e_success)
        {
        printf("Read and validate decode arguments successful\n");
        printf("---------------------------Decoding started ----------------------\n");

        if (do_decoding(&decode) == e_success)
            printf("Decoding successful\n");
        else
            printf("Decoding failed\n");
        }     
        }
        else
        {
          printf("Invalid arguments Inputs\n");
          printf("For encoding : ./a.out -e beautiful.bmp secret.txt [stego.bmp]\n");
          printf("for decoding : ./a.out -d stego.bmp [decod.txt]\n");
        }
    //res -> e_encode -> read_and_validate_encodde_arg(); -> do_encoding();

    //res -> e_decode -> read_and_validate_decode_arg();  -> do_decoding();

    //res -> e_usupported -> error -> terminate

    return 0;
}

