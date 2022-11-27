//
// Created by Omer Meushar on 26/11/2022.
//

#include "AsciiArtTool.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define INVERTED_CHAR '@'
#define INVERTED_SPACE ' '
#define NULL_CHAR '\0'

/*** Static Functions Declarations ***/
///are there static funcs?

/*** Function Implement ***/
RLEList asciiArtRead(FILE* in_stream)
{
//    if(in_stream == NULL){
//        return RLE_LIST_NULL_ARGUMENT;
//    }
    assert(in_stream);
    /// do we use our main in submit?? if not - change to if in comments
    RLEList list = RLEListCreate();
    char currentChar;
//    int currentResult = fscanf(in_stream, "%c", &currentChar);
    while(fscanf(in_stream, "%c", &currentChar) && !feof(in_stream))
    {
        if(RLEListAppend(list, currentChar) != RLE_LIST_SUCCESS){
            return NULL;
        }
        if(currentChar == NULL_CHAR){
            return list;
        }
    }
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{

    //int string_length = getRLEStringLength();
    // RLEListSize
    int listSize = RLEListSize(list);
    RLEListResult currentResult;
    for (int i = 0; i < listSize; ++i) {
        if(!(fprintf(out_stream, "%c", RLEListGet(list,i,&currentResult)))) {
            RLEListDestroy(list); /// omer final checks 27/11
            return RLE_LIST_NULL_ARGUMENT;
        }
        assert(currentResult==RLE_LIST_SUCCESS);
    }
    RLEListDestroy(list); /// omer final checks 27/11
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if (!out_stream && list) {
        RLEListDestroy(list); /// omer final checks 27/11
        return RLE_LIST_NULL_ARGUMENT;
    }
    else if(!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    //assert(out_stream);
    RLEListResult result;
    char* string = RLEListExportToString(list, &result);
    if(result == RLE_LIST_SUCCESS){
        if(fputs(string, out_stream) == EOF) {
            RLEListDestroy(list); /// omer final checks 27/11
            return RLE_LIST_NULL_ARGUMENT;
        }
    }
    free(string);
    RLEListDestroy(list); /// omer final checks 27/11
    return result;
}


static char invertedMapFunc(char c)
{
    if (c == INVERTED_CHAR) {
        c = INVERTED_SPACE;
    }
    else if (c == INVERTED_SPACE) {
        c = INVERTED_CHAR;
    }
    return c;
}

void invertRLEList (RLEList list)
{
    RLEListMap(list, invertedMapFunc);
}




