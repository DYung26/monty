#include "monty.h"
int *push(int *stack, int *top, int value) {
	stack[*top] = value;
	(*top)++;
	return stack;
}

void pall(int* stack, int top) {
	int i;
	for (i = top-1; i > -1; --i) {
		printf("%d\n", stack[i]);
	}
}

int main(int argc, char *argv[]) {
	int *stack;
	int top = 0;
	int countI = 0;
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

	while (fscanf(file, "%d", &value) == 1) {
        countI++;
    }
	stack = (int*)malloc(countI*sizeof(int));

	while (fscanf(file, "%s", command) == 1) {
		lineNumber++;
		if (strcmp(command, "push") == 0) {
			int value;
			if (fscanf(file, "%d", &value) == 1) {
            	push(stack, &top, value);
			} else {
				printf("L%d: usage: push integer\n", lineNumber);
				free(stack);
    			fclose(file);
				return EXIT_FAILURE;
			}
        } else if (strcmp(command, "pall") == 0) {
            pall(stack, top);
        }
	}
	free(stack);
	fclose(file);
	return EXIT_SUCCESS;
}
