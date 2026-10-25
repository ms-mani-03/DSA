
#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    int borrow = 0;

    *headR = NULL;
    *tailR = NULL;

    while (tail1 != NULL || tail2 != NULL)
    {
        int digit1 = 0;
        int digit2 = 0;

        if (tail1 != NULL)
        {
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        digit1 -= borrow;

        if (digit1 < digit2)
        {
            digit1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int digit = digit1 - digit2;

        if (insert_first(headR, tailR, digit) == FAILURE)
        {
            delete_list(headR, tailR);
            return;
        }
    }

    if (*headR == NULL)
    {
        if (insert_first(headR, tailR, 0) == FAILURE)
            return;
    }

    remove_pre_zeros(headR);

    *tailR = *headR;
    while (*tailR != NULL && (*tailR)->next != NULL)
        *tailR = (*tailR)->next;
}

