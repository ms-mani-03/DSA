#include "apc.h"

// Function definitions
// Number validation
int is_valid_number(char *str)
{
	int i = 0;
	if(str[0] == '\0')
		return FAILURE;
	if(str[i] == '-' || str[i] == '+')
		i++;
	if(str[i] == '\0')
		return FAILURE;
	while(str[i] != '\0')
	{
		if(str[i] < '0' || str[i] > '9')
			return FAILURE;
		i++;
	}
	return SUCCESS;
}

//Operator Validation
int cla_validation(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("Error : Invalid number of arguments\n");
		printf("Usage : ./apc <operand1> <operator> < oprand2>\n"); 
		return FAILURE;
	}
	if(argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != 'X' && argv[2][0] != '*' && argv[2][0] != '/')
	{
		printf("Error : Invalid Operator\n");
		return FAILURE;
	}
	return SUCCESS;
}

//List Creation

int create_list(char *opr, node **head, node **tail)
{
    if (opr == NULL || head == NULL || tail == NULL)
        return FAILURE;

    *head = NULL;
    *tail = NULL;

    int i = 0;

    if (opr[i] == '-' || opr[i] == '+')
        i++;

    while (opr[i] != '\0')
    {
        if (insert_last(head, tail, opr[i] - '0') == FAILURE)
        {
       	    delete_list(head, tail);
            return FAILURE;
        }

        i++;
    }

    return SUCCESS;
}

// print list
void print_list(node *head)
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

// Remove Zeros
void remove_pre_zeros(node **head)
{
	node *temp;
	while(*head != NULL && (*head) -> data == 0 && (*head) -> next != NULL)
	{
		temp = *head;
		*head = (*head) -> next;
		(*head) -> prev = NULL;
		free(temp);
	}
}

// Insert_at_first
int insert_first(node **head, node **tail, int data)
{
	node *new = malloc(sizeof(node));
	if(new == NULL)
	{
		return FAILURE;
	}
	new -> data = data;
	new -> prev = NULL;
	new -> next = *head;
	if(*head == NULL)
	{
		*head = new;
		*tail = new;
		return SUCCESS;
	}
	(*head) -> prev = new;
	*head = new;
	return SUCCESS;
}

// Insert_at_last
int insert_last(node **head, node **tail, int data)
{
	node *new = malloc(sizeof(node));
	if(new == NULL)
		return FAILURE;
	new -> data = data;
	new -> next = NULL;
	new -> prev = *tail;
	if(*head == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail) -> next = new;
		*tail = new;
	}
	return SUCCESS;
}

// Calculate list lenght
int list_len(node *head)
{
	int count = 0;
	node *temp = head;
	while(temp != NULL)
	{
		count++;
		temp = temp -> next;
	}
	return count;
}
	
// Compare list
int compare_list(node *head1, node *head2)
{
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    if (len1 > len2)
        return 1;

    if (len1 < len2)
        return -1;

    node *temp1 = head1;
    node *temp2 = head2;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->data > temp2->data)
            return 1;

        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
}

//Multipliction helper

int multiply_by_digit(node *tail, int digit, node **headR, node **tailR)
{
    int carry = 0;

    if (headR == NULL || tailR == NULL)
        return FAILURE;

    *headR = NULL;
    *tailR = NULL;

    while (tail != NULL || carry != 0)
    {
        int product = carry;

        if (tail != NULL)
        {
            product += tail->data * digit;
            tail = tail->prev;
        }

        int result_digit = product % 10;
        carry = product / 10;

        if (insert_first(headR, tailR, result_digit) == FAILURE)
        {
            delete_list(headR, tailR);
            return FAILURE;
        }
    }

    if (*headR == NULL)
    {
        if (insert_first(headR, tailR, 0) == FAILURE)
        {
            delete_list(headR, tailR);
            return FAILURE;
        }
    }

    return SUCCESS;
}

//Delete_list
int delete_list(node **head, node **tail)
{
	node *temp = *head;
	while(temp != NULL)
	{
		node *next = temp -> next;
		free(temp);
		temp = next;
	}
	*head = NULL;
	*tail = NULL;
	return SUCCESS;
}
