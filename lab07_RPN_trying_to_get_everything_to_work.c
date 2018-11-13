#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct stack
{
	int data;
	struct stack *next;
} stack;

void push( stack **head, int value )
{
	stack* node = malloc( sizeof(stack) );

	if( node == NULL ) {
		fputs( "Error: Out of memory\n", stderr );
		exit( 1 );
	} else {
		node->data = value;
		node->next = *head;
		*head = node;
	}
}

int pop( stack **head )
{
	if( *head == NULL ) {
		fputs( "Error: bottom of stack!\n", stderr );
		exit( 1 );
	} else {
		stack* top = *head;
		int value = top->data;
		*head = top->next;
		free( top );
		return value;
	}
}

int eval(char op[], stack** head )
{
	int temp;
	int n1;
	int n2;
	char op2[100];
	op2 = getop(op);
	if (strcmp(op2,'+') == 0){
		return pop(head) + pop(head);
	}
	else if (strcmp(op2,'*') == 0){
		return pop(head) * pop(head);
	}
	else if (strcmp(op2,'-') == 0){
		temp = pop(head); return pop(head) - temp;
	}
	else if (strcmp(op2,'/') == 0){
		temp = pop(head); return pop(head) / temp;
	}
	else if (strcmp(op2,'GT') == 0){
		/*  -push 1 if n1 > n2 and 0 otherwise  */
		n1 = pop(head);
		n2 = pop(head);
		if (n1 > n2){
			return 1;
		}
		else {
			return 0;	
		}
	}
	else if (strcmp(op2,'GE') == 0){
	/*-push 1 if n1 >= n2 and 0 otherwise */
		n1 = pop(head);
		n2 = pop(head);
		if (n1 >= n2){
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (strcmp(op2,'LT') == 0){
		/*-push 1 if n1 < n2 and 0 otherwise */

		n1 = pop(head);
		n2 = pop(head);
		if (n1 < n2){
			return 1;
		}
		else{
			return 0;	
		}
	}
	else if (strcmp(op2,'LE') == 0){
		/* -push 1 if n1 <= n2 and 0 otherwise */
		n1 = pop(head);
		n2 = pop(head);
		if (n1 >= n2){
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (strcmp(op2,'EQ') == 0){
		/* -push 1 if n1 == n2 and 0 otherwise */
		n1 = pop(head);
		n2 = pop(head);
		if (n1 == n2){
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (strcmp(op2,'MOD') == 0){
		/*  push two copies of n1 onto the stack  */
			n1 = pop(head);
			pop(head); 
			push(head, n1); // first push the 2nd push is done by our return
			return n1;
	}
	else if (strcmp(op2,'if') == 0){
		//*  IF (n1 n2 v — x) - if v is not zero then push n1 otherwise n2 */
		// 	n1 = pop(head);
		// 	n2 = pop(head);
		// 	int v = n1 - n2
		// 	if (v != 0){
		// 		return n1;
		// 	}
		// 	else{
		// 		return n2;
		// 	}
	}
	
}
char * getop(char op[]){
	char *p = strrchr(op, ' ');	
	if (p && *(p + 1)){
    	return (p);
	}
}

int need( char op[] )
{
	char op2[100];
	op2 = getop(op);
	if (strcmp(op2,'+') == 0):
	else if (strcmp(op2,'*') == 0):
	else if (strcmp(op2,'-') == 0):
	else if (strcmp(op2,'/') == 0):
	else if (strcmp(op2,'GT') == 0):
	else if (strcmp(op2,'GE') == 0):
	else if (strcmp(op2,'LT') == 0):
	else if (strcmp(op2,'LE') == 0):
	else if (strcmp(op2,'EQ') == 0):
	else if (strcmp(op2,'MOD') == 0):
	else if (strcmp(op2,'if') == 0)
	else{
		fputs( "Invalid operand!", stderr );
		exit( 1 );
	}
}

int checknr( char* number )
{
	for( ; *number; number++ )
		if( *number < '0' || *number > '9' )
			return 0;

	return 1;
}

int main( int argc, char** argv )
{
	int i, temp, stacksize = 0;
	stack* head = NULL;

	if( argc == 1 )
	{
		printf("Usage: %s <arg> [arg] ... \n", argv[0]);
		exit(1);
	}

	for( i = 1; i < argc; i++ ) {
		char* token = argv[i];
		char* endptr;
		char op[100];

		if( checknr( token ) ) {
			/* We have a valid number. */
			temp = atoi( token );
			push( &head, temp );
			++stacksize;
		} else {
			/* We have an operand (hopefully) */
			op = token[0];

			if( stacksize < need( op ) ) {
				fputs( "Too few arguments on stack.\n", stderr );
				exit( 1 );
			}

			push( &head, eval( op, &head ) );
			stacksize -= need( op ) - 1;
		}
	}

	if( stacksize != 1 ) {
		fputs( "Too many arguments on stack.\n", stderr );
		exit( 1 );
	}

	printf( "Result: %i\n", head->data );
	return 0;
}