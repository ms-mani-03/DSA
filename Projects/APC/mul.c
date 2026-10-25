
#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *resultHead = NULL;
    node *resultTail = NULL;

    *headR = NULL;
    *tailR = NULL;

    int shift = 0;

    while (tail2 != NULL)
    {
        node *partialHead = NULL;
        node *partialTail = NULL;
        node *sumHead = NULL;
        node *sumTail = NULL;

        multiply_by_digit(tail1, tail2->data, &partialHead, &partialTail);

        if (partialHead == NULL)
            goto memory_error;

        for (int i = 0; i < shift; i++)
        {
            if (insert_last(&partialHead, &partialTail, 0) == FAILURE)
            {
                delete_list(&partialHead, &partialTail);
                goto memory_error;
            }
        }

        addition(resultTail, partialTail, &sumHead, &sumTail);

        if (sumHead == NULL)
        {
            delete_list(&partialHead, &partialTail);
            goto memory_error;
        }

        delete_list(&resultHead, &resultTail);
        delete_list(&partialHead, &partialTail);

        resultHead = sumHead;
        resultTail = sumTail;

        tail2 = tail2->prev;
        shift++;
    }

    if (resultHead == NULL)
    {
        if (insert_first(&resultHead, &resultTail, 0) == FAILURE)
            goto memory_error;
    }

    remove_pre_zeros(&resultHead);

    resultTail = resultHead;
    while (resultTail != NULL && resultTail->next != NULL)
        resultTail = resultTail->next;

    *headR = resultHead;
    *tailR = resultTail;
    return;

memory_error:
    delete_list(&resultHead, &resultTail);
    *headR = NULL;
    *tailR = NULL;
    printf("Error: Multiplication failed\n");
}

