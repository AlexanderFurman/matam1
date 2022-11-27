//
// Created by Omer Meushar on 26/11/2022.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AsciiArtTool.h"
#include "RLEList.h"


#define FLAG_NUM 1
#define SRC_NUM 2
#define DEST_NUM 3
#define INVERTED_FLAG "-i"
#define ENCODED_FLAG "-e"
#define READ_ONLY "r"
#define WRITE_ONLY "w"

int main(int argc, char* argv[])
{
    char* flag = argv[FLAG_NUM];
    char* srcFile = argv[SRC_NUM];
    char* destFile = argv[DEST_NUM];
    FILE *srcOpen = fopen(srcFile, READ_ONLY);
    if (srcOpen==NULL) {
        return 0;
    }
    FILE *destOpen = fopen(destFile, WRITE_ONLY);
    if (destOpen==NULL) {
        fclose(srcOpen);
        return 0;
    }
    RLEList list = asciiArtRead(srcOpen);
    if (list==NULL)
    {
        fclose(srcOpen);
        fclose(destOpen);
        return 0;
    }
    if(strcmp(flag,INVERTED_FLAG) == 0) {
        invertRLEList(list);
        asciiArtPrint(list,destOpen);
    }
    else if (strcmp(flag,ENCODED_FLAG) == 0) {
        asciiArtPrintEncoded(list, destOpen);
    }

    fclose(srcOpen);
    fclose(destOpen);
    return 0;
}
