// binary semaphore

#include<stdio.h>

struct semaphore { 
	enum value(0, 1); 

	// q contains all Process Control Blocks (PCBs) 
	// corresponding to processes got blocked 
	// while performing down operation. 
	Queue<process> q; 

} P(semaphore s) 
{ 
	if (s.value == 1) { 
		s.value = 0; 
	} 
	else { 
		// add the process to the waiting queue 
		q.push(P) 
			sleep(); 
	} 
} 
V(Semaphore s) 
{ 
	if (s.q is empty) { 
		s.value = 1; 
	} 
	else { 

		// select a process from waiting queue 
		q.pop(); 
		wakeup(); 
	} 
} 
/



struct semaphore { 
	enum value(0, 1); 

	// q contains all Process Control Blocks (PCBs) 
	// corresponding to processes got blocked 
	// while performing down operation. 
	Queue<process> q; 

} P(semaphore s) 
{ 
	if (s.value == 1) { 
		s.value = 0; 
	} 
	else { 
		// add the process to the waiting queue 
		q.push(P) 
			sleep(); 
	} 
} 
V(Semaphore s) 
{ 
	if (s.q is empty) { 
		s.value = 1; 
	} 
	else { 

		// select a process from waiting queue 
		q.pop(); 
		wakeup(); 
	} 
} 



struct semaphore { 
	enum value(0, 1); 

	// q contains all Process Control Blocks (PCBs) 
	// corresponding to processes got blocked 
	// while performing down operation. 
	Queue<process> q; 

} P(semaphore s) 
{ 
	if (s.value == 1) { 
		s.value = 0; 
	} 
	else { 
		// add the process to the waiting queue 
		q.push(P) 
			sleep(); 
	} 
} 
V(Semaphore s) 
{ 
	if (s.q is empty) { 
		s.value = 1; 
	} 
	else { 

		// select a process from waiting queue 
		q.pop(); 
		wakeup(); 
	} 
} 

