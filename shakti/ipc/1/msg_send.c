//  C Program for Message Queue (Writer Process) 


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
	key_t key ;// key_t is system call ( msgsnd )

	if ( key  = ftok( "pgm.c" , 11 )== -1 ) // Generate key   ** file path ( txt or .c any ) and give any id
	{
		perror ( " key error " ) ;
		exit ( 1 ) ;
	}
	
	if ( msgid = msgget ( key , 0644 | IPC_CREAT ) == -1 ) //  get msg id && key , permision( 0644= U+rw,G+r,X+r) , msg_queue flags 
	{
		perror ( " msgid " ) ;
		exit ( 1 ) ;
	}

	printf ( " msgid = %d " , msgid ) ;

	printf ( " Enter the text : \n " ) ;

	msg.mtype = 1 ; // msgtype give 0 = read first Recevied  msg,
			// +ve = if msgtype is 10, then reads only the first message of type 10 even though other types may be in the queue at 				   the beginning)
			// and -ve =  if msgtype is -5, then it reads first message of type less than 5

	while ( gets ( msg.msgtxt ) , !feof( stdin ) )
	{
		if ( msgsnd(msgid,&msg,sizeof(msg),0 ) == -1 ) //  0 = "indicates certain flags such as IPC_NOWAIT (returns immediately when no 								message is found in queue ) " 
		
		{
			perror ( " msgsnd " ) ;
			exit ( 1 ) ;
		}
	}

	if ( msgctl ( msgid , IPC_RMID , NULL ) == -1 ) // remove msg after sending 
	{
		perror ( " msgctl " ) ;
		exit ( 1 ) ;
	}

return 0 ;

} 
