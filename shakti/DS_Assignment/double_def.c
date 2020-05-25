//  2.  Double link list program


#include <stdio.h>
#include <stdlib.h>
#include "double_dec.h"




struct node *create_list ( struct node *start )

{
	int data, n , i ;
	
	printf ( "Enter number of Nodes : \n " ) ;
	scanf ( "%d", &n ) ;

	if ( n == 0 )
	{
		printf ( " \n  Empty List \n" ) ;
		return start ;
	}

	printf ( "Enter element to be inserted  : \n ") ;
	scanf ( "%d", &data ) ;

	start = insertatbeg ( start , data ) ;

	for ( i = 2; i<=n; i++ )
	{
		printf ( "Enter Element To Be inserted  : \n ") ;
		scanf ( "%d", &data ) ;
		start = insertatend ( start , data ) ;
	}
	
	return start ;
}

//  insert node at the beginning

struct node *insertatbeg ( struct node *start , int data )
{
	struct node *tmp;

	tmp = ( struct node * ) malloc ( sizeof ( struct node * ) ) ;

	tmp -> info = data ;
	tmp -> prev = NULL ;
	tmp -> next = start ;
	start = tmp ;
	
	return start ;
}


// insert node at the end.

struct node *insertatend ( struct node *start , int data )
{
	struct node *tmp , *p ;
	tmp = ( struct node *) malloc ( sizeof ( struct node *) ) ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}

	p = start ;
	while ( p -> next != NULL )
	{
		p = p -> next ;
	}
	
	tmp -> info = data ;
	tmp -> prev = p ;
	tmp -> next = NULL ;
	p -> next = tmp ;
	
	return start ;
}


void display_list ( struct node *start )
{
	struct node *tmp, *p ;

	tmp = ( struct node *) malloc ( sizeof ( struct node *) ) ;

	if ( start == NULL )
	{
		printf ( " List is Empty \n " );
		return ;
	}

	printf ( " The list is : \n ") ;
	p = start ;
	while ( p != NULL )
	{
		printf ( "%d \n ", p -> info ) ;
		p = p -> next ;
	}
}


// Insert the node before the given data.

struct node *insertbefore ( struct node *start , int data , int item )
{
	struct node *tmp , *p ;

	if ( start == NULL )
	{
		printf ( " List  is Empty \n " );
		return start ;
	}  
	


        // for first node 

	if ( start -> info == item ) 
	{	
		tmp = ( struct node * ) malloc ( sizeof ( struct node * ) ) ;
		tmp -> info = data ;
		tmp -> prev = NULL ;
		tmp -> next = start ;
		start = tmp ;
		return start ;
	}

	p = start ;
	while ( p -> next != NULL )
	{
		if ( p -> next -> info == item )
		{	
			tmp = ( struct node * ) malloc ( sizeof ( struct node * ) ) ;
			tmp -> info = data ;
			tmp -> prev = p -> next -> prev ;
			tmp -> next = p -> next ;
			p -> next = tmp ;
			p -> next -> prev = tmp ; 
			return start ;
		}
		p = p -> next ;
	}
	
	printf ( " Enter %d data is not found  \n " , item );

	return start ;
} 




//  Insert the node after the given data.

struct node *insertafter ( struct node *start , int data , int item )
{
	struct node *tmp , *p ;
	tmp = ( struct node *) malloc ( sizeof ( struct node * ) ) ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}

	tmp -> info = data ;

	p = start ;
	while ( p -> next != NULL ) 
	{
		if ( p -> info == item ) 
		{
			tmp -> next = p -> next ;
			tmp -> prev = p -> next -> prev ;
			p -> next = tmp ;
			p -> next -> prev = tmp ;
			return start ;
		}
		p = p -> next ;
	}
	
	printf ( " %d not present in the list \n" , item ) ;

	return start ;
}


// delete first node  

struct node *del_beg ( struct node *start )
{
	struct node *tmp ;
	tmp = ( struct node * ) malloc ( sizeof ( struct node * ) ) ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}
	
	tmp = start ;
	start = start -> next ;
	free ( tmp ) ;
	return start ;
}


//  delete node at the end


struct node *del_end ( struct node *start )
{
	struct node *tmp , *p ;
	tmp = ( struct node * ) malloc ( sizeof ( struct node * ) ) ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}

	if ( start -> next == NULL )
	{
		tmp = start ;
		start = start -> next ;
		free ( tmp ) ;
		return start ;
	}
	
	else
	{

		p = start ;

		while ( p -> next != NULL )
		{	
			tmp = p ;
			p = p -> next ;
		}
		//tmp = p -> next ;
		free ( tmp -> next ) ;
		tmp -> next = NULL ;
		return start ;
	}
}



// Delete the node for given data

struct node *delete_given_data ( struct node *start , int data )
{
	struct node *tmp , *p ;
	tmp = ( struct node * ) malloc ( sizeof ( struct node * ) ) ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}
	


	if ( start -> info == data )
	{
		tmp = start ;
		start = start -> next ;
		free ( tmp ) ;
		return start ;
	}


	p = start ;

	while ( p -> next != NULL )
	{
		if ( p -> next -> info == data ) 
		{
			tmp = p -> next ;
			p -> next = tmp -> next ;
			free ( tmp ) ;
			return start ;
		}
		p = p -> next ;
	}
	
	printf ( "%d element is not found \n ", data ) ;
	return start ;
}



// insert at position 

struct node *insertatpos ( struct node *start , int data , int pos ) 
{
	struct node *tmp , *p ;
	int i ; 
	tmp = ( struct node * ) malloc ( sizeof ( struct node * ) ) ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}

	tmp ->info = data ;

	if ( pos == 1 )
	{	
		tmp -> next = start ;
		start = tmp ;
		return start ;
	}
	p =start ; 
	for ( i = 1 ; i<pos-1 && p != NULL ; i++ ) 
	p = p -> next ;
	
	if ( p == NULL )
	{	
		printf ( " there are less than %d element \n " ,pos ) ;
	}
	
	else 
	{
		tmp -> next = p -> next ;
		p -> next = tmp ;
	}
	return start ;
}


// sorted list

void sort_list ( struct node *start )
{
	struct node *p ,*q ;
	int temp ; 
	
	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}

	p = start ;

	for ( p = start ; p -> next != NULL ; p = p -> next )
	
	{
		for ( q = p -> next ; q != NULL ; q = q -> next )
		{
			if ( p -> info  >  q -> info )

			{
				temp = p -> info ;
				p -> info = q -> info ;
				q -> info = temp ;
			}
		}
	}
	
}



	
//  get the data stored in the nth node

int get_node ( struct node *start , int pos )
{
	struct node *p ;
	int item ,i ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	} 

	p =start ; 
	for ( i = 1 ; i<pos && p != NULL ; i++ ) 
	p = p -> next ;
	
	if ( p == NULL )
	{	
		printf ( " there are less than %d element \n " ,pos ) ;
	}
	
	else 
	{
		item = p -> info ;
	}
	return item ;
}

  // get nth data from end of list 

int get_node_end ( struct node *start , int pos )
{
	struct node *tmp , *p ;
	int count = 0 , i, item ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		exit ( 1 ) ;
	}
	
	p = start ;

	while (  p != NULL )
	{
		p = p -> next ;
		count ++ ;
	}
	
	if ( count < pos ) 
	{
		return -1 ;
	}
	p = start ;

	for ( i = 1 ; i < count - pos + 1 ; i++ ) 
	
	p = p -> next ;
	
	item = p -> info ;
       
	return item ;
} 

// inserted into sorted list

struct node * insret_in_sort_list ( struct node *start , int data ) 
{
	struct node *tmp , *p ;
	tmp = ( struct node *) malloc ( sizeof ( struct node *) ) ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}

	p = start ;
	while ( p -> next != NULL )
	{
		p = p -> next ;
	}
	
	tmp -> info = data ;
	tmp -> prev = p ;
	tmp -> next = NULL ;
	p -> next = tmp ;
	
	return start ;
}



// Remove Duplicate in list

void remove_duplicate ( struct node *start ) 

{
	struct node *tmp , *p , *q ;
	tmp = ( struct node * ) malloc ( sizeof ( struct node * ) ) ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}

	p = start ;

	while ( p != NULL && p -> next != NULL ) 
	{
         
		q = p ;
  
        	/* Compare the picked element with rest of the elements */
         
		while ( q -> next != NULL )
        	{ 
            		/* If duplicate then delete it */
             
	    		if ( p -> info == q -> next -> info )
            		{ 
            		    /* sequence of steps is important here */
                 
            		    tmp = q -> next ;
			    q -> next = q -> next -> next ;
			    free ( tmp ) ;
            		} 
            		else 
			{
			     q = q -> next ;
			}
       		 } 
        
		 p = p -> next ; 
	} 
} 
  


/// Revese list 

struct node *reverse_list ( struct node *start )
{
	struct node *tmp ;

	if ( start == NULL )
	{
		printf ( " \n ** NO Element in List ** \n " ) ;
		return start ;
	}

	if( start -> next == NULL)
	{
		return start ;
	}

	tmp = reverse_list ( start -> next )  ;
	start -> next -> next = start ;
	start -> next = NULL;

	return tmp;
}

