#ifndef _calc_h
#define _calc_h

#ifdef __cplusplus
extern "C" {
#endif

enum read_mode {
		normal, paren
};

typedef struct node {
	float i;
	struct node *next;
} node_t;

float calc(const char *eq);

void fill_stacks(const char *eq, node_t **stack1, node_t **stack2);// stack2 should be opstack
void sub_stacks(node_t **stack, node_t **opstack, node_t **sub, node_t **opsub); 
void exec_stacks(node_t **stack, node_t **substack, node_t **opsub);

void push(float value, node_t **head);
float pop(node_t **head);

float addition(node_t **stack1, node_t **stack2);
float subtraction(node_t **stack1, node_t **stack2);
float multiplication(node_t **stack1, node_t **stack2);
float division(node_t **stack1, node_t **stack2);
#ifdef __cplusplus
}
#endif
#endif

