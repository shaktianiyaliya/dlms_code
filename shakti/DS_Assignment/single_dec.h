#ifndef __SLL_1_H__
#define __SLL_1_H__


struct node 
{
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


#endif
