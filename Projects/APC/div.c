#include "apc.h"
#include <stdio.h>
                                              
static node *get_tail(node *head)
{
	if(head == NULL)
		return NULL;
	while(head -> next != NULL)
		head = head -> next;
	return head;
}

void division(node *head1, node *head2, node **headR, node **tailR)
{
	node *remHead = NULL;
	node *remTail = NULL;
	node *quotHead = NULL;
	node *quotTail = NULL;
	node *diffHead = NULL;
	node *diffTail = NULL;
	*headR = NULL;
	*tailR = NULL;
	if(head2 == NULL || (head2 -> data == 0 && head2 -> next == NULL))
	{
		printf("Error: Division by Zero\n");
		return;
	}
	if(head1 == NULL)
	{
		insert_first(headR, tailR, 0);
		return;
	}
	node *divTail = get_tail(head2);
	node *digit = head1;
	while(digit != NULL)
	{
		if(remHead != NULL && remHead -> data == 0 && remHead -> next == NULL)
		{
			delete_list(&remHead, &remTail);
		}
		if(insert_last(&remHead, &remTail, digit -> data) == FAILURE)
		{
			goto memory_error;
		}
		int qdigit = 0;
	while(compare_list(remHead, head2) >= 0)
	{
		if(qdigit >= 9)
			goto memory_error;
		subtraction(remTail, divTail, &diffHead, &diffTail);
		delete_list(&remHead, &remTail);
		remHead = diffHead;
		remTail = diffTail;
		diffHead = NULL;
		diffTail = NULL;
		qdigit++;
	}
	if(insert_last(&quotHead, &quotTail, qdigit) == FAILURE)
	{
		goto memory_error;
	}
	digit = digit -> next;
	}
	remove_pre_zeros(&quotHead);
	quotTail = get_tail(quotHead);
	delete_list(&remHead, &remTail);
	*headR = quotHead;
	*tailR = quotTail;
	return;
memory_error:
	delete_list(&remHead, &remTail);
	delete_list(&diffHead, &diffTail);
	delete_list(&quotHead, &quotTail);
	*headR = NULL;
	*tailR = NULL;
	printf("Error: Division failed\n");
}
