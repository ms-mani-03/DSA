#include "apc.h"
static int is_zero(node *head)
{
	return head != NULL && head -> data == 0 && head -> next == NULL;
}

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;

    // Validation
    if(cla_validation(argc, argv) == FAILURE)
    {
	    return FAILURE;
    }
    if(is_valid_number(argv[1]) == FAILURE || is_valid_number(argv[3]) == FAILURE)
    {
	    printf("Error : Invalid operand\n");
	    return FAILURE;
    }
    //Record the signs
    int sign1 = (argv[1][0] == '-') ? -1 : 1;
    int sign2 = (argv[3][0] == '-') ? -1 : 1;
    // Create 2 lists of operands
    create_list(argv[1], &head1, &tail1);
    create_list(argv[3], &head2, &tail2);
    // Remove pre zeros
    remove_pre_zeros(&head1);
    remove_pre_zeros(&head2);

    char oper = argv[2][0];

    switch(oper)
    {
	case '+':
	{
	    int cmp = compare_list(head1, head2);
	    int result_sign;
	    if(sign1 == sign2)
	    {
	    	addition(tail1, tail2, &headR, &tailR);
	        result_sign = sign1;
	    }
	    else if(cmp == 0)
	    {
		    insert_first(&headR, &tailR, 0);
		    result_sign = 1;
	    }
	    else if(cmp > 0)
	    {
		    subtraction(tail1, tail2, &headR, &tailR);
		    result_sign = sign1;
	    }
	    else
	    {
		    subtraction(tail2, tail1, &headR, &tailR);
		    result_sign = sign2;
	    }
	    if(result_sign < 0 && !is_zero(headR))
	    {
		    printf("-");
	    }
	    print_list(headR);
	    break;
	}
	case '-':
	{
	    int effective_sign2 = -sign2;
	    int cmp = compare_list(head1, head2);
	    int result_sign;
	    if(sign1 == effective_sign2)
	    {
		    addition(tail1, tail2, &headR, &tailR);
		    result_sign = sign1;
	    }
	    else if(cmp == 0)
	    {
		    insert_first(&headR, &tailR, 0);
		    result_sign = 1;
	    }
	    else if(cmp > 0)
	    {
	    	subtraction(tail1, tail2, &headR, &tailR);
	    	result_sign = sign1;
	    }
	    else
	    {
	 	subtraction(tail2, tail1, &headR, &tailR);
		result_sign = effective_sign2;
	    }
	    if(result_sign < 0 && !is_zero(headR))
	    {
		    printf("-");
	    }
	    print_list(headR);
	    break;
	}

	case 'x':
	case 'X':
	    multiplication(tail1, tail2, &headR, &tailR);
	    if(headR != NULL && !(headR -> data == 0 && headR-> next == NULL))
	    {
	        if(sign1 != sign2)
		printf("-");
	    }
	    print_list(headR);
	    break;

	case '/':
	{
	    if(head2 -> data == 0 && head2 -> next == NULL)
	    {
		    printf("Error: Division by Zero\n");
		    break;
	    }
            division(head1, head2, &headR, &tailR);
	    if(headR != NULL && !(headR -> data ==0 && headR -> next == NULL))
	    {
		    if(sign1 != sign2)
		    {
			    printf("-");
		    }
	    }
	    print_list(headR);
	    break;
	}

	default:
	    printf("Invalid operator\n");
    }
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);
    return SUCCESS;
}

