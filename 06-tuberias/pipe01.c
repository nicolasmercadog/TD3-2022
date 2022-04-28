/*
 * Ejercicio 1 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 


int main (){

   int ipc[2], proc;
   int leido;
   char buff[80];

   pipe(ipc); // crea la tubería

   printf ("ipc[0] = %d ipc[1] =%d \n ", ipc[0], ipc[1]);// muestra el descriptor de lectura y el de escritura
   proc = fork(); // crea al hijo

   if (proc == 0 ){ //inicia el proceso hijo
      
      // Se cierra el lado de escritura del hijo
      close(ipc[1]); // cierra la tubería para escribir
      
      leido = read(ipc[0], buff, sizeof(buff)); // lee lo que hay en la tubería y se queda esperando hasta que haya algo en la tubería
      if(leido < 1){ // si no existe la tuberia muestra error
         write (STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
      }else { //si la tubería existe entonces muestra lo que hay en la tuberia por pantalla

         // Escribir en consola
         write (STDOUT_FILENO, "\nLeido de la tuberia: ", sizeof("\nLeido de la tuberia: "));
         write (STDOUT_FILENO, buff, leido-1);
         printf(", por el proceso hijo, pid %d \n", getpid());
      }
      exit(0); //finaliza el proceso hijo
   
   }
   // Se cierra el lado de lectura del padre
   close(ipc[0]);
   
   printf("\nIngrese una cadena de caracteres por consola:\n");
   // Se lee por consola
   leido = read(STDIN_FILENO, buff,  sizeof(buff));

   // Se escribe en la tuberia
   write(ipc[1], buff, leido);
   
   // Se cierra el lado de escritura. 
   close(ipc[1]);

   wait(NULL);   //espera a que termine el hijo
   write (STDOUT_FILENO, "\nEscrito en la tuberia: ", sizeof("\nEscrito en la tuberia: "));
   write (STDOUT_FILENO, buff, leido-1);
   printf(", por el proceso padre, pid %d \n", getpid());

   exit(0);//finaliza el proceso padre

}
