#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

float calc(const char *eq)
{
	node_t *stack = NULL;
	node_t *opstack = NULL;
	node_t *sub = NULL;
	node_t *opsub = NULL;


	fill_stacks(eq, &stack, &opstack); // eq is equation
	sub_stacks(&stack, &opstack, &sub, &opsub);	// copy stacks into temps
	exec_stacks(&stack, &sub, &opsub);
	return pop(&stack);
}

void fill_stacks(const char *eq, node_t **stack1, node_t **stack2)
{
	int i = 0;
	int j = 0;
	int buf_size = 256;
	int len = strlen(eq);
	char temp[buf_size];
	memset(temp,0,buf_size);
	enum read_mode mode = normal;


	for (i=0; i<len+1; i++) {
		if (mode == normal) {
			if ((eq[i] > 47 && eq[i] < 58 && j < buf_size) || (eq[i] == 46 && j < buf_size)) {
				// eq[i] is a digit or .
				temp[j] = eq[i];
				j++;
			} else if ((eq[i] == 43 || eq[i] == 45 || eq[i] == 47 || eq[i] == 42) && j < buf_size) {
				// eq[i] is an operator
				temp[j] = '\0';
				if (temp[0] != '\0') push(atof(temp), stack1);
				push(eq[i], stack2);
				memset(temp,0,buf_size);
				j=0;	
			} else if (eq[i] == 123 && j < buf_size) {
				// eq[i] is an opening parens
				memset(temp,0,buf_size);
				mode = paren; // switch to parens mode,
			} else {
				// 'should' be end of eq
				temp[j] = '\0';
				if (temp[0] != '\0') push(atof(temp), stack1);
			}
		} else if (mode == paren) { // read into a temp string and make recursive call
			if ((eq[i] > 47 && eq[i] < 58 && j < buf_size) || (eq[i] == 46 && j < buf_size) ||
						(eq[i] == 43 || eq[i] == 45 || eq[i] == 47 || eq[i] == 42)) {
				// eq[i] is a valid character (digit, ., or operator)
				temp[j] = eq[i];
				j++;
			} else if (eq[i] == 125) {
				// eq[i] is a closing parens
				temp[j] = '\0';
				push(calc(temp), stack1);
				j=0;
				mode = normal;
				memset(temp,0,buf_size);
			}
		}
	}
}

void sub_stacks(node_t **stack, node_t **opstack, node_t **sub, node_t **opsub)
{
	while ((*stack)->next != NULL) {
		push(pop(stack), sub);
		push(pop(opstack), opsub);
	}
}

void exec_stacks(node_t **stack, node_t **sub, node_t **opsub)
{
	while ((*sub) != NULL) {
		switch ((int)pop(opsub)) {
			case 43:
				push(addition(stack,sub), stack);
				break;
			case 45:
				push(subtraction(stack,sub), stack);
				break;
			case 42:
				push(multiplication(stack,sub), stack);
				break;
			case 47:
				push(division(stack,sub), stack);
				break;
			default:
				push(999,stack);
		}
	}
}

void push(float value, node_t **head)
{
	node_t *new_node = malloc(sizeof(node_t));	
	new_node->i = value;
	new_node->next = *head;

	*head = new_node;
}

float pop(node_t **head)
{
	float rv = -1;
	node_t *next_node = NULL;

	if (*head == NULL) {
		return -1;
	}

	next_node = (*head)->next;
	rv = (*head)->i;
	free(*head);
	*head = next_node;

	return rv;
}

float addition(node_t **stack1, node_t **stack2)
{
	return pop(stack1)+pop(stack2);
}

float subtraction(node_t **stack1, node_t **stack2)
{
	return pop(stack1)-pop(stack2);
}

float multiplication(node_t **stack1, node_t **stack2)
{
	return pop(stack1)*pop(stack2);
}

float division(node_t **stack1, node_t **stack2)
{
	return pop(stack1)/pop(stack2);
}
