//  2.  Double link list program


#include <stdio.h>
#include <stdlib.h>



	struct node 
	{	
		struct node *prev ;

		int info ;

		struct node *next ;
	};


	struct node *create_list ( struct node *start ) ;

	void display_list ( struct node *start ) ;


	struct node *insertatbeg ( struct node *start , int data ) ;

	struct node *insertatend ( struct node *start , int data ) ;

	struct node *insertbefore ( struct node *start , int data , int item ) ;

	struct node *insertafter ( struct node *start , int data , int item ) ;

	struct node *del_beg ( struct node *start ) ;

	struct node *del_end ( struct node *start ) ;

	struct node *delete_given_data ( struct node *start , int data ) ;


	struct node *insertatpos ( struct node *start , int data , int pos ) ;

	void sort_list ( struct node *start ); 

	struct node *insret_in_sort_list ( struct node *start , int data ) ;

	void remove_duplicate ( struct node *start ) ;

	struct node *reverse_list ( struct node *start ) ;

	int get_node ( struct node *start , int pos ) ;
	
	int get_node_end ( struct node *start , int pos ) ;




int main()

{

	struct node *start = NULL ;
	int data , item , pos , choice;

	while ( 1 ) 
	{	
		printf ( " \n \n " ) ;
		printf ( " 1.  Create List \n " ) ;
		printf ( " 2.  Insert the node before the given data \n " );
		printf ( " 3.  Insert the node after the given data \n " ) ;
		printf ( " 4.  insert node at given position \n " ) ;
		printf ( " 5.  Delete the node for given data \n " ) ;
		printf ( " 6.  sort linked list \n " ) ;
		printf ( " 7.  insert a node into the sorted list \n " ) ;
		printf ( " 8.  Removing the duplicate values in the linked list \n " ) ;
		printf ( " 9.  delete node at the beginning \n " ) ;
		printf ( " 10. delete node at the end \n " ) ;
		printf ( " 11. get the data stored in the nth node \n " ) ;
		printf ( " 12. get the nth node from the end of the list \n " ) ;
		printf ( " 13. reverse the linked list \n " ) ;
		printf ( " 14. Quite \n " ) ;

		printf ( " \n \n " ) ;
	
		printf ( " Enter Your Choice : \n " ) ;
		scanf ( "%d", &choice ) ;
		
		switch ( choice ) 
		{
			case 1 : 
				start = create_list ( start ) ;
				display_list ( start ) ;
				break ;

			case 2 : 
				printf ( "Enter the new element to be inserted : \n ") ;
				scanf ( "%d" , &data ) ;

				printf ( "Enter the element before which to inserted : \n " ) ;
				scanf ( "%d", &item ) ;

				start = insertbefore ( start , data , item ) ;
	
				printf ( " after adding list is : \n " ) ;
				display_list ( start ) ;
				break ;

			case 3 :
				
				printf ( "Enter the new element to be inserted : \n ") ;
				scanf ( "%d" , &data ) ;
	
				printf ( "Enter the element after which to inserted : \n " ) ;
				scanf ( "%d", &item ) ;

				start = insertafter ( start , data , item ) ;
	
				display_list ( start ) ;
				break ;

			case 4 :
				
				printf ( "Enter the new element to be inserted : \n ") ;
				scanf ( "%d" , &data ) ;

				printf ( " enter the position at which to insert : \n " );
				scanf ( "%d", &pos ) ;
	
				start = insertatpos ( start , data , pos );

				printf ( "after inserting  given  position list is : \n " ) ; 
				display_list ( start ) ;
				break ;

			case 5 : 
				printf ( "Eneter element to be deleted : \n" ) ;
				scanf ( "%d", &data ) ;

				start = delete_given_data ( start , data ) ;
	
				printf ( " after deleting given node  list is : \n " ) ;
	
				display_list ( start ) ;
				break ;

			case 6 : 
				sort_list ( start );
	
				printf ( " sorted list is : \n " ) ;

				display_list ( start ) ;
				break ;

			case 7 :
				printf ( "Enter the new element to be inserted in sorted list : \n ") ;
				scanf ( "%d" , &data ) ;


				start = insret_in_sort_list ( start , data ) ;

				printf ( " after inserting new node  sorted list is : \n " ) ;

				display_list ( start ) ;
				break ;

			case 8 :
				printf ( " afte removing duplicate node list is : \n " ) ;

				remove_duplicate ( start ) ;

				display_list ( start ) ;
				break ;

			case 9 : 
				start = del_beg ( start ) ;

				printf ( " after deleting begging node list is : \n " ) ;

				display_list ( start ) ;
				break ;

			case 10 :
				start = del_end ( start ) ;

				printf ( " after deleting last node list is : \n " ) ;

				display_list ( start ) ;
				break ;

			case 11 :
				printf ( " enter  which position data you want ?? \n " ) ;
				scanf ( "%d", &pos ) ;
	
				printf ( "the enter %d position  data is =%d ", pos, get_node ( start , pos ) ) ; 
				break ;

			case 12 :
				printf ( " **start at the Endnode**   Enter  which position data you want ?? \n " ) ;
				scanf ( "%d", &pos ) ;	

				printf ( " **start at the Endnode** Enter %d position data is =%d " , pos , get_node_end ( start ,  pos ) ) ;
				break ;

			case 13 :
				start = reverse_list ( start ) ;

				printf ( "reverse list is : \n " ) ;
	
				display_list ( start ) ;
				break ;

			case 14 : 
				exit ( 1 ) ;
		
			default :
				printf ( " Wrong Choice \n " );
		}// Switch case End
	}// While end 

	return 0 ; 

}// main function End



// Create list Function

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

// Display Function 

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
		return start ;
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
		exit ( 1 )  ;
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
  



// Revese list 

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

		
