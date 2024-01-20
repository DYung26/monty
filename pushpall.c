#include "monty.h"
void push(stack_t **stack, unsigned int value) {
	stack_t *new_node = malloc(sizeof(stack_t));
	
	new_node->n = value;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL) {
        (*stack)->prev = new_node;
    }

    *stack = new_node;
}

void pall(stack_t **stack, unsigned int n) {
	stack_t *current = *stack;
	unsigned int count = 0;

	while (current != NULL && count < n) {
		printf("%d\n", current->n);
		current = current->next;
		count++;
	}
}

void free_stack(stack_t *stack) {
	stack_t *current = stack;
	while (current != NULL) {
		stack_t *next = current->next;
		free(current);
		current = next;
	}
}

int main(int argc, char *argv[]) {
	stack_t *stack = NULL;
	instruction_t instructions[] = {
		{"push", push},
    	{"pall", pall},
    	{NULL, NULL}
	};
    int lineNumber = 0;
	int value;

	char command[10];
	FILE *file = fopen(argv[1], "r");
    if (argc != 2) {
        printf("USAGE: monty %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (file == NULL) {
        printf("Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

	while (fscanf(file, "%s", command) == 1) {
		lineNumber++;
		if (strcmp(command, "push") == 0) {
			/*int value;*/
			if (fscanf(file, "%d", &value) == 1) {
            	instructions[0].f(&stack, value); /*push(stack, value);*/
			} else {
				printf("L%d: usage: push integer\n", lineNumber);
				free_stack(stack);
    			fclose(file);
				return EXIT_FAILURE;
			}
        } else if (strcmp(command, "pall") == 0) {
			instructions[1].f(&stack, value);
        } else if ((strcmp(command, "pall") != 0) || (strcmp(command, "push") != 0)) {
			printf("L%d: unknown instruction %s\n", lineNumber, command);
			free_stack(stack);
            fclose(file);
			return EXIT_FAILURE;
		}
	}
	free_stack(stack);
	fclose(file);
	return EXIT_SUCCESS;
}
