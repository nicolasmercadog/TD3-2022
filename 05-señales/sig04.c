/*
 * Ejercicios 6 de TP Seniales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int n=0;

void sighijo (int a){
 printf("\nTerminó el hijo %d \n", ++n);
 //write(STDOUT_FILENO, "\n Termino el hijo \n",sizeof("\n Termino el hijo \n"));
}

int main ()
{
  pid_t hj1, hj2, hj3;

   signal(SIGCHLD, sighijo); //signal que contiene al controlador de señal hijo

   hj1 = fork(); //creo primer proceso hijo

   if (hj1 == 0){//si soy el hijo 1 entonces entra en un bucle infinito
     printf("Soy el proceso hijo 1. Mi PID = %d \n", getpid());
     while(1);
   }
   else{
     hj2 = fork(); //creo el segundo proceso hijo
     if (hj2 == 0){
       printf("Soy el proceso hijo 2. Mi PID = %d\n", getpid());
       while (1);}
       else{
         hj3 = fork(); //creo el tercer proceso hijo
         if(hj3 == 0){
           printf("Soy el proceso hijo 3. Mi PID = %d\n", getpid());
           while(1);}
           else{
             //hace una espera activa de 2 segundos y mata a los hijos
             sleep(2);
             kill(hj1, SIGKILL);
             sleep(10);
             kill(hj2, SIGKILL);
             sleep(20);
             kill(hj3, SIGKILL);
             sleep(30);
           }
       }

   }
  sleep(2);


   exit(0);
}
