//
// Created by Omer Meushar on 26/11/2022.
//
#include "RLEList.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#ifndef HW1_WET_ASCIIARTTOOL_H
#define HW1_WET_ASCIIARTTOOL_H

/* This function reads a given file, and returns the RLEList equivalent
 parameters: FILE* in_stream, containing an ASCII image to be compressed
 returns: RLEList list, compressed list
 */
RLEList asciiArtRead(FILE* in_stream);

/* */
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

// char invertedMapFunc(char c);
void invertRLEList (RLEList list);


#endif //HW1_WET_ASCIIARTTOOL_H
