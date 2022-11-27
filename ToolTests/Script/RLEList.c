#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define RLE_LIST_NULL -1
#define NULL_CHAR '\0'
#define EXPORT_TO_STRING_ROW_SIZE 3
#define NUM_BASE 10
#define LETTER_AND_NEWLINE_LENGTH 2
#define LINE_FINISH '\n'
//#define EXPORT_TO_STRING_LETTER_ID 0
//#define EXPORT_TO_STRING_REPETITIONS_ID 1
//#define EXPORT_TO_STRING_LINE_ID 2


typedef struct RLENode_t {
    char letter;
    int repetitions;
    struct RLENode_t* next;
} *RLENode;

struct RLEList_t{
    //TODO: implement
    RLENode first;
    RLENode last;
    //int size
    //numLetters
};

/***
 * typedef enum {
    RLE_LIST_SUCCESS,
    RLE_LIST_OUT_OF_MEMORY,
    RLE_LIST_NULL_ARGUMENT,
    RLE_LIST_INDEX_OUT_OF_BOUNDS,
    RLE_LIST_ERROR
} RLEListResult;
 */


/*** Function Implement ***/
//implement the functions here

static RLENode RLEListGetNodeFromIndex(RLEList list, int index, RLEListResult *result);
//static int listLengthNodes (RLEList list);
static int getNumDigits (int intNum);
static int getRLEStringLength (RLEList list);
//static void RLEPrint(RLEList list);


//static void RLEPrint(RLEList list)
//{
//    RLENode temp = list->first;
//    while (temp->next)
//    {
//        printf("%c%d ", temp->letter, temp->repetitions);
//        temp = temp->next;
//    }
//    printf("\n");
//
//}

//static int listLengthNodes (RLEList list)
//{
//    assert(list);
//    int counter = 0;
//    RLENode temp = list->first;
//    while (temp->next)
//    {
//        counter++;
//        temp = temp->next;
//    }
//    return counter;
//}

RLEList RLEListCreate()
{
    RLEList linkedList = malloc(sizeof(*linkedList));
    if (!linkedList) {
        return NULL;
    }
    linkedList->first = malloc(sizeof(*(linkedList->first)));
    if (!linkedList->first) {
        free(linkedList);
        return NULL;
    }
    linkedList->first->next = NULL;
    linkedList->first->repetitions = 0;
    linkedList->first->letter= NULL_CHAR ;
    linkedList->last = linkedList->first;

    return linkedList;
}

void RLEListDestroy(RLEList list)
{
    if (!list){
        return;
    }
    RLENode toDelete = NULL;
    while (list->first->next)
    {
        assert(RLEListSize(list)>=0);
        toDelete=list->first->next;
        list->first->next = toDelete->next;
        free(toDelete);
    }
    free(list->first);
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if(list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(RLEListSize(list)==0 || list->last->letter != value )
    {
        list->last->next = malloc(sizeof(*(list->last->next)));
        if (!list->last->next){
            return RLE_LIST_OUT_OF_MEMORY;
        }

        list->last = list->last->next;
        list->last->letter = value;
        list->last->repetitions = 1;
        list->last->next = NULL;
    }
    else { //(list->last->letter == value)
        list->last->repetitions++;
    }
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if (!list) {
        return RLE_LIST_NULL;
    }
    int counter = 0;
    RLENode temp = list->first;
    while (temp->next)
    {
        counter += temp->next->repetitions;
        temp = temp->next;
    }
    //counter+=list->last->repetitions;
    return counter;
}



///https://piazza.com/class/l8vdfbb5pf86qf/post/116
// typedef char (*MapFunction)(char);
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list || !map_function){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (RLEListSize(list) == 0) {
        return RLE_LIST_SUCCESS;
    }
    RLENode temp = list->first->next;
    temp->letter = map_function(temp->letter);
    while (temp->next)
    {
        temp->next->letter = map_function(temp->next->letter);
        if(temp->letter == temp->next->letter) {
            temp->repetitions += temp->next->repetitions;
            RLENode next = temp->next;
            temp->next = temp->next->next;
            free(next);
        }
        else {
            temp=temp->next;
        }
    }
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
//    if (!result) {
//        return NULL;
//    }
    if (!list) {
        if(result){
            *result=RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    // size of new string: 3 letters in row (including \n), times num of rows, +1 for null terminated string
    char* outString = malloc(getRLEStringLength(list)*sizeof(char));
    if (!outString) {
        if(result) {
            *result=RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    *outString = NULL_CHAR;

    RLENode temp = list->first;
    while (temp->next)
    {
        char *currentRow = malloc(sizeof(char)*(LETTER_AND_NEWLINE_LENGTH +1 + getNumDigits(temp->next->repetitions)+1));
        sprintf(currentRow, "%c%d\n", temp->next->letter, temp->next->repetitions);
        strcat(outString, currentRow);
        free(currentRow);
        temp=temp->next;
    }
    if(result){
        *result = RLE_LIST_SUCCESS;
    }
    return outString;
}

RLEListResult RLEListRemove(RLEList list, int index){

    RLEListResult result;
    RLENode prevNode = RLEListGetNodeFromIndex(list, index, &result);
    if (prevNode == NULL){
        return result;
    }

    RLENode node = prevNode->next;

    /// for debug - we should desired node by here:

    // Deal with case where repetitions > 1 (simple case)
    if(node->repetitions > 1){
        node->repetitions--;
        return RLE_LIST_SUCCESS;
    }
        // Deal with case where repetitions == 1
    else{
        // Deal with last node remove:
        if(node->next == NULL) {
            prevNode->next = NULL;
            list->last=prevNode;
        }
        // Deal with first node remove (after dummy):
//        else if()
//        {
//            prevNode->next = node->next;
//        }
            // Deal with the case where the previous node and next node have different letters:
        else if(list->first == prevNode || prevNode->letter != node->next->letter) { ///united above condition
            prevNode->next = node->next;
        }
            // Deal with case where the previous node and next node have SAME letter:
        else{
            prevNode->repetitions += node->next->repetitions;
            prevNode->next = node->next->next;
            if(list->last==node->next) {
                list->last = prevNode;
            }
            free(node->next);
        }
        free(node);
        return RLE_LIST_SUCCESS;
    }
    // return RLE_LIST_ERROR;
}

//void uniteNodes(RLEList list, RLENode prevNode, RLENode node){
//    assert(node->next);
//    prevNode->repetitions += node->next->repetitions;
//    prevNode->next = node->next->next;
//    if(list->last==node->next) {
//        list->last = prevNode;
//    }
//    free(node->next);
//}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    RLENode prevNode = RLEListGetNodeFromIndex(list, index, result);
    if (prevNode == NULL){
        return 0;
    }
    else{
        return prevNode->next->letter;
    }
    
    // if (!list) {
    //     return RLE_LIST_NULL_ARGUMENT;
    // }
    // if(index < 0 || index + 1 > RLEListSize(list)) { // CHECK THIS +1 is correct??
    //     return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    // }

    // RLENode node = list->first->next;
    // int indicesRemaining = index;

    // while(indicesRemaining >= node->repetitions){
    //     indicesRemaining -= node->repetitions;
    //     node = node->next;
    // }

    // *result = RLE_LIST_SUCCESS;
    // return node->letter;
}

static RLENode RLEListGetNodeFromIndex(RLEList list, int index, RLEListResult *result){
    if (!list) {
        if (result){
            *result = RLE_LIST_NULL_ARGUMENT;
        }

        return NULL;
    }
    if(index < 0 || index + 1 > RLEListSize(list)) { /// +1 should be correct
    if(result){
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
        return NULL;
    }
    // int current_idx = 0;
    RLENode prevNode = list->first;
    RLENode node = prevNode->next;
    int indicesRemaining = index;

    // First move to the correct node, and previous node
    while(indicesRemaining >= node->repetitions){
        indicesRemaining -= node->repetitions;
        prevNode = node;
        node = prevNode->next;
    }
    if(result){
        *result = RLE_LIST_SUCCESS;
    }
    return prevNode;
}
static int getNumDigits (int intNum) {
    int counter = 0;
    if (intNum == 0) {
        return 1;
    }
    while (intNum!=0) {
        intNum/=NUM_BASE;
        counter++;
    }
    return counter;
}

static int getRLEStringLength (RLEList list) {
    assert(list);
//    if (listLengthNodes(list)==0) {
//        return 1;
//    }
    int lenCounter = 1; ///NULL terminated in case of empty list;
    RLENode temp = list->first;
    while (temp->next)
    {
        lenCounter += LETTER_AND_NEWLINE_LENGTH;
        lenCounter += (getNumDigits(temp->next->repetitions));
        temp=temp->next;
    }
    return lenCounter;
}

