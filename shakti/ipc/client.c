// Client Socket programming


#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>
#include <unistd.h> 
#include <string.h> 

#define PORT 4060 //5034  


int main ( int argc , char *argv[] )
{

	/** create Variable  **/

	int sock ;
	struct sockaddr_in client; // In this structure have all the server address
	struct hostent *hp ; 
	
	
	char data[1024] = " Hello this message from client " ; 
	int rval ;

	sock = socket(AF_INET, SOCK_STREAM, 0) ; 
	if (sock  < 0) 
	{ 
		perror(" Socket creation error \n"); 
		exit ( 1 ) ; 
	} 

	client.sin_family = AF_INET;
	
	hp = gethostbyname (argv[1] ) ;
	
	if ( hp == 0 )
	{
		perror ( " gethostbyname failed " ) ;
		exit ( 1 ) ;
	}

	memcpy ( &client.sin_addr , hp -> h_addr , hp -> h_length ) ;// copy the  h_addr address to server

	client.sin_port = htons ( PORT ) ;

	if ( connect ( sock , ( struct sockaddr * ) &client , sizeof ( client ) ) < 0 )
	{
		perror ( " Connect failed " ) ;
		exit ( 1 ) ;
	}
	
	if ( send ( sock , data , sizeof ( data ) , 0 ) < 0 )

	{
		perror ( " Send data failed " ) ;
		exit ( 1 ) ;
	}

	printf ( " Sent data is : %s\n", data ) ;
	
	close ( sock ) ;

	return 0 ;
}



















