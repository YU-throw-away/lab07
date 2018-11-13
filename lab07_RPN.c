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

int eval( char op, stack** head )
{
	int temp;
	switch( op ) {
		case '+': return pop(head) + pop(head);
		case '*': return pop(head) * pop(head);
		case '-': temp = pop(head); return pop(head) - temp;
		case '/': temp = pop(head); return pop(head) / temp;
	}
}

int need( char op )
{
	switch( op ) {
		case '+':
		case '*':
		case '-':
		case '/':
			return 2;
		default:
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
		char op;

		if( checknr( token ) ) {
			/* We have a valid number. */
			temp = atoi( token );
			push( &head, temp );
			++stacksize;
		} else {
			/* We have an operand (hopefully) */
			if( strlen( token ) != 1 ) {
				fprintf( stderr, "Error: Token '%s' too large.\n", token );
				exit( 1 );
			}

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