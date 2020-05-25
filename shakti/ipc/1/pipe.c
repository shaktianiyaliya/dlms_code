// C program pipe() " Communicatiom between Parent And Chaild Process 


#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 


int main( ) 
{ 
	pid_t pid ;
	int my_pipe[2]; // array of 2 integer ( 0 -> read , 1 -> write )
	int ret ;
 	char buf [1024] , str[1024] ;

	ret = pipe ( my_pipe ) ; // create pipe 

	if ( ret == -1 )
	{
		perror( " pipe " ) ;
		exit ( 1 ) ;
	}
	printf ( " Enter text : \n " ) ;
	gets ( str ) ;
	
	pid = fork() ;// for create new Process

	
	if ( pid == 0 )
	{
		printf ( " Chaild Process \n " ) ;
		close ( my_pipe[0] ) ; // Close reading end  

		write ( my_pipe[1] , str , sizeof ( str ) ) ; // write into pipe ( 1 for -> write ) 
	}
	else 
	{
		printf ( " Parent Process \n " ) ;

		close ( my_pipe[1] ) ; // Close Writing end 

		read ( my_pipe[0] , buf , sizeof ( str ) ) ; // read from pipe ( 0 for -> read data )

		printf ( "Read from pipe  is : %s " , buf ) ;
	}

	return 0;
} 
