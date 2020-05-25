// Double Link List

#include<stdio.h>
#include<stdlib.h>
//#include"double_dec.h"
//#include"double_def.c"




int main()

{

	struct node *start = NULL ;
	int data , item , pos , choice;

	while ( 1 ) 
	{	printf ( " \n \n " ) ;
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
				printf ( "Enter element to be deleted : \n" ) ;
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
		}
	}
	return 0 ; 

}
