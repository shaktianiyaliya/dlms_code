#include<stdio.h>
#include<unistd.h>

main()
{
	int pid ;
	pid = COW;

	if ( pid == 0 )
	{
		printf ( " chaild Process \n " ) ;
	}
	else 
	{
		printf ( " Parent Process \n " ) ;
	}
	
	printf ( "%d",pid ) ;
}
