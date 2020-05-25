// Queue program    "FIFO"

#include <stdio.h>
#include <stdlib.h>

	struct node 
	{
		int info ;
		struct node *next ;

	}*front = NULL , *rear = NULL ;

	void insert( int item ) ;
	int delete ( void ) ;
	void display ( void ) ;
	int isEmpty( void ) ;

int main () 
{ 
	
	
	int item , n , choice ;

	while ( 1 ) 
	{	
		printf ( " \n \n " ) ;
		printf ( " 1. Insert data into Queue \n " ) ;
		printf ( " 2. Delete data from Queue \n " ) ;
		printf ( " 3. Quite \n " ) ;

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

					printf ( " Enter Element to inserted : \n " ) ;
					scanf ( "%d" , &item ) ;
	
					insert ( item ) ;
					n-- ; 
					
				}
				display () ;

				break ;

			case 2 : 
				item = delete () ;

				printf ( " the Deleted item is = %d \n", item ) ;
				printf ( " After Deleting %d Element Queue is : \n " , item ) ;
				display ( ) ;
				

				break ; 

			case 3 : 
				exit ( 1 ) ;
				break ;

			default : 
				printf ( " Wrong Choice \n " ) ;
				break ;
		}// Switch case End
	}// while End

	return 0 ;


}// main End
 
// insert function 

void insert ( int item )
{
	struct node *tmp ;
	tmp = ( struct node * ) malloc ( sizeof ( struct node ) ) ;

	tmp -> info = item ;
	tmp -> next = NULL ;
	if ( front == NULL )
	{
		front = tmp ;
	}
	else
	{
		rear -> next = tmp ;
	}
	rear = tmp ;
}


// Delete function 


int delete ( ) 
{
	struct node * tmp ;
	int item ;
	if ( isEmpty () ) 
	{
		printf (" Queue is Underflow \n " ) ;
		exit (1) ;
	}
	tmp = front ;
	item = tmp -> info ;
	front = front -> next ;
	free( tmp ) ;
	return item ;
}

// Display Function

void display ()
{
	struct node *p;
	p = front ;
	
	if ( isEmpty () )
	{
		printf ( " Queue is Empty \n " ) ;
		return ;
	}

	printf ( " \n " ) ;
	printf ( " \n Queue Element is \n " );
	while ( p != NULL )
	{
		printf ( "%d", p -> info ) ;
		p = p -> next ;
		printf ( "\n \n" ) ;
	}
} 



int isEmpty ()
{

	if ( front == NULL )
		return 1;

	else 
		return 0 ;
}










