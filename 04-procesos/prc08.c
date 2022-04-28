/*
 * Ejercicio 4 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i;
	
	pid=fork();
	switch(pid){
	
	case -1: //Caso que no pudo crear hijo y terminó en error
		printf("No pude crear proceso  hijo :( ");
	case 0:  //Es el proceso  hijo
		{printf("Soy el proceso hijo, mi pid es  %d, el pid de papá es %d y fork devolvió  %d \n",getpid(),getppid(), pid);
		sleep(30);}
		break;
	default:  //Es el proceso  padre
		printf("Soy el proceso padre, mi pid es  %d y fork devolvió %d \n",getppid(), pid);	}
	
	
	exit(0);

}

//El  proceso  hijo 4208 quedó huerfano y ahora su padre es systemd(1394)
