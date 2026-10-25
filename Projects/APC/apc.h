#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SUCCESS		1
#define FAILURE		0

#define SAME		0
#define OPERAND1	1
#define OPERAND2	2

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
}node;

int addition(node *tail1, node *tail2, node **headR, node **tailR);
int subtraction(node *tail1, node *tail2, node **headR, node **tailR);
int multiplication(node *tail1, node *tail2, node **headR, node **tailR);
int division(node *head1, node *head2, node **headR, node **tailR);

int is_valid_number(char *str);
int cla_validation(int argc, char *argv[]);
int create_list(char *opr, node **head, node **tail);
void remove_pre_zeros(node **head);
int multiply_by_digit(node *tail, int digit, node **headR, node **tailR);

int insert_first(node **head, node **tail, int data);
int insert_last(node **head, node **tail, int data);
int delete_list(node **head, node **tail);
void print_list(node *head);

int compare_list(node *head1, node *head2);
int list_len(node *head);



#endif
