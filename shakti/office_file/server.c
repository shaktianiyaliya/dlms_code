
// Server side C/C++ program to demonstrate Socket programming  ( " gcc -o server soc_server.c " ) OR ( server.c , ./a.out)



#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h> 
#include <string.h> 

#define PORT 5034


int main ( )
{

	/** create Variable  **/

	int sock ;
	struct sockaddr_in server; // in #include <netinet/in.h>
	int mysock ;
	char buff[1024] ;
	int rval ;


	/* Create Socket */

	sock = socket(AF_INET, SOCK_STREAM, 0) ; // 1 -> communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
						 //2 -> communication type : - 1) SOCK_STREAM: TCP(reliable, connection oriented)
						 //			       2) SOCK_DGRAM: UDP(unreliable, connectionless)
	
						// 3 ->	protocol: Protocol value for Internet Protocol(IP), which is 0
	if (sock  < 0) 
	{ 
		perror(" Socket creation error \n"); 
		exit ( 1 ) ; 
	} 

	server.sin_family = AF_INET; 		// IPv4 
	server.sin_addr.s_addr = INADDR_ANY ;  // bind your socket to localhost
	server.sin_port = htons ( PORT ) ;    // htons -> convert host byte order to network bytes order 

	/* Bind */


	if ( bind ( sock , ( struct sockaddr * ) & server , sizeof ( server ) ) ) // "assigning a name (** address ** ) to a socket”
	{
		perror ( " Bind Failed \n " ) ;
		exit ( 1 ) ;
	}

	/* Listen */

	listen( sock , 5 ) ; //  maximum length to which the  queue  of pending  connections  for  sock  may  grow ( max No of client )


	/* Accept  */

// the process to block until the client connects to the server.  it returns a new descriptor and all communication should be carried out using 	the new file descriptor
	do{
		mysock = accept ( sock ,( struct sockaddr * ) 0, 0 ) ; 
									// 2 -> ptr to add of client 
									// 3-> addr_storing_size_of_client_address
		if ( mysock == -1 )
		{
			perror ( " Accept Failed " ) ;
			exit ( 1 ) ;
		}
		else
		{	// void *memset(void *str, int c, size_t n) => copies the character c (an unsigned char) to the first n characters of 				the string pointed to, by the argument str

			memset ( buff , 0 , sizeof ( buff ) ); //  fill memory with a constant byte


			if ( ( rval = recv ( mysock , buff , sizeof ( buff ) , 0 ) ) < 0 )

				perror ( " Reading Stream Msg Error " ) ;

			else if ( rval == 0 )

				printf ( " Ending Connection \n " ) ;
			else 
				printf ( " MSG is : %s\n", buff ) ;

			printf ( " Got the message  ( rval = %d ) \n " , rval ) ;
		}
	
	}while( 1 );


	return 0 ;
}




































