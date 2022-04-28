/*
 * Ejercicio 2 de TP PIPE
 * 
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

int main (){

   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

    pipe(ipc);

   if (pipe(ipc) == -1) //si no existe la tuberia entonces finaliza el programa
      exit(-1);

//nunca se crea la tubería

   switch (fork()){ //crea un proceso hijo
      
      case 0:
         close(ipc[0]); //hay que cambiar para que cierre la lectura y no la escritura
         strncpy(buff, DATA, sizeof(DATA)); //copia lo que hay en DATA a buff
         write(ipc[1], buff, sizeof(DATA));//escribe lo que hay en buff a la tubería
         exit(0);//termina el proceso hijo
         
      default: //inicia el proceso padre
        close(ipc[1]); // se agrega para que cierre la escritura
         printf("Leyendo tuberia... \n");//nunca cierra la escritura de la tubería
         leido = read(ipc[0], buff, sizeof(buff)); //lee lo que hay en la tubería
         if(leido < 1){//si no hay nada larga un error
            write (STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
         }else {

            write (STDOUT_FILENO, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
            write (STDOUT_FILENO, buff, leido-1);
            printf(", por el proceso padre, pid %d \n", getpid());
         }
         wait(NULL); //espera al hijo

         exit(0);//termina el padre
   }
}
