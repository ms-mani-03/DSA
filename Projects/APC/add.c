
#include "apc.h"

void addition(node *tail1, node *tail2,
              node **headR, node **tailR)
{
    int carry = 0;

    *headR = NULL;
    *tailR = NULL;

    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        int sum = carry;

        if (tail1 != NULL)
        {
            sum += tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            sum += tail2->data;
            tail2 = tail2->prev;
        }

        int digit = sum % 10;
        carry = sum / 10;

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
