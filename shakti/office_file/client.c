// Client Socket programming(  (gcc soc_client.c -o soc_client  , ./client localhost )


#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>
#include <unistd.h> 
#include <string.h> 

#define PORT 5034


int main ( int argc , char *argv[] )
{

	/** create Variable  **/

	int sock ;
	struct sockaddr_in server;
	struct hostent *hp ; 
	
	char data[1024] = " Hello This is shakti " ;
	int rval ;

	sock = socket(AF_INET, SOCK_STREAM, 0) ; 
	if (sock  < 0) 
	{ 
		perror(" Socket creation error \n"); 
		exit ( 1 ) ; 
	} 

	server.sin_family = AF_INET;
	
	hp = gethostbyname (argv[1] ) ;
	
	if ( hp == 0 )
	{
		perror ( " gethostbyname failed " ) ;
		exit ( 1 ) ;
	}

	memcpy ( &server.sin_addr , hp -> h_addr , hp -> h_length ) ;

	server.sin_port = htons ( PORT ) ;

	if ( connect ( sock , ( struct sockaddr * ) &server , sizeof ( server ) ) < 0 )
	{
		perror ( " connect failed " ) ;
		exit ( 1 ) ;
	}
	
	if ( send ( sock , data , sizeof ( data ) , 0 ) < 0 )

	{
		perror ( " send failed " ) ;
		exit ( 1 ) ;
	}

	printf ( " sent is : %s\n", data ) ;
	
	close ( sock ) ;

	return 0 ;
}



















