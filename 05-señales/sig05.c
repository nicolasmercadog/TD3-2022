/*
 * Ejercicios 7 de TP Seniales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pid1,pid2=0;
int status;

void sighijo (int a){
pid2=wait(&status);
 write(STDOUT_FILENO, "\n Termino el hijo \n",sizeof("\n Termino el hijo \n"));
}

int main ()
{
   signal(SIGCHLD, sighijo); //signal que contiene al controlador de señal hijo
/* a) Cree un proceso hijo que haga una espera activa de dos segundos y finalice
con la funcion exit(0). */
   pid1 = fork(); //creo primer proceso hijo
   
 	if(pid1==0){
       printf("Soy el proceso hijo. Mi PID = %d\n", getpid());
       sleep(2);
     exit(0);}
  while(pid2==0){
     printf("Soy el padre y hago una espera activa de 10 seg\n");
       sleep(10000);
       printf("El estado es: %d\n",status);}
  
  }
