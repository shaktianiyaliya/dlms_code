// Message Received Queue 


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>


// structure for message queue

	struct msgbuf
	{
	long mtype;
	char msgtxt[200];
	} ;


int main()

{	
	struct msgbuf msg ;
 
	int msgid ;
	key_t key ;

	if ( key = ftok ( "pgm.c" , 11 ) == -1 ) // give same path used in sender and same id 
	{
		perror ( " KEY ERROR" ) ;
		exit ( 1 ) ;
	}

	if ( ( msgid = msgget ( key , 0644 ) ) == -1 ) // Genarate same id ( sender id ) && key , permision( 0644= U+rw,G+r,X+r)
	{
		perror ( " msgid " ) ;
		exit ( 1 ) ;
	}

	while ( 1 ) 
	{
		if ( msgrcv ( msgid , &msg , sizeof ( msg ) , 1 , 0 ) == -1 ) // 1 = msg type similar to sender 
									     //  0 = "indicates certain flags such as IPC_NOWAIT (returns 											immediately when no message is found in queue ) " 
		{
			perror ( " msgrcv  " ) ;
			exit ( 1 ) ;
		}
		
		printf ( "%s", msg.msgtxt ) ; // display the received msg
	}

	return 0 ;
}
