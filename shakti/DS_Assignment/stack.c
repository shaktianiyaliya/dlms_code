
// Stack program    "LIFO"

#include <stdio.h>
#include <stdlib.h>

	struct node 
	{
		int info ;
		struct node *next ;

	}*top = NULL ;

	void push( int item ) ;
	int pop ( void ) ;
	int peek ( void ) ;
	void display ( void ) ;
	int isEmpty( void ) ;

int main () 
{ 
	
	int item , n , choice ;

	while ( 1 ) 
	{	
		printf ( " \n \n " ) ;
		printf ( " 1. push data into stack \n " ) ;
		printf ( " 2. pop data from stack \n " ) ;
		printf ( " 3. peek data from stack \n " ) ;
		printf ( " 4. Quite \n " ) ;
		printf ( " Enter Your Choice : \n\n " ) ;
		scanf ( "%d", &choice ) ;
		printf ( " \n \n " ) ;

		switch ( choice ) 
		{
			case 1 : 
				printf ( " Enter How many element to be inserted \n " ) ;
				scanf ( "%d", &n ) ;
				
				while ( n )
				{

					printf ( " Enter Element to pushed : \n " ) ;
					scanf ( "%d" , &item ) ;
	
					push ( item ) ;
					n-- ; 
					
				}
				display () ;

				break ;

			case 2 : 
				item = pop() ;

				printf ( " the Pop item is = %d \n", item ) ;
				printf ( " After Pop %d Element Stack is : \n " , item ) ;
				display () ;

				break ; 
			
			case 3 : 
				printf ( " Peek Item is  = %d \n", item ) ;
				printf ( " After peek %d Ekement stack : \n " , item ) ;
				display () ;

				break ;

			case 4 : 
				exit ( 1 ) ;
				break ;

			default : 
				printf ( " Wrong Choice \n " ) ;
				break ;
		}// Switch case End
	}// while End

	return 0 ;


}// main End

// push function 

void push ( int item ) 
{
	struct node * tmp ;
	tmp = ( struct node * ) malloc ( sizeof ( struct node ) ) ;
	
	if ( tmp == NULL )
	{
		printf ( " Stack Overflow \n " ) ;
		return ;
	}

	tmp -> info = item ;
	tmp -> next = top ;
	top = tmp ;
}


// pop function


int pop ( void )
{
	struct node *tmp ;
	int item ;

	if ( isEmpty () )
	{
		printf ( " Stack is UnderFlow \n " ) ;
		exit (1) ;
	}
	
 	tmp = top ;
	item = tmp -> info ;
	top = top -> next ;
	free ( tmp ) ;
	return item ;
}


// peek function
 
int peek ( void )
{
	
	if ( isEmpty )
	{
		printf ( " Stack Underflow \n " ) ;
		exit (1) ;
	}

	return top -> info ;
}



void display ()
{
	struct node *p;
	p = top ;
	
	if ( isEmpty () )
	{
		printf ( " stack is Empty \n " ) ;
		return ;
	}

	
	
	printf ( " The Element is \n " );
	while ( p != NULL )
	{
		printf ( "%d", p -> info ) ;
		p = p -> next ;
		printf ( "\n " ) ;
	}
}
	

int isEmpty ()
{

	if ( top == NULL )
		return 1;

	else 
		return 0 ;
}





	
