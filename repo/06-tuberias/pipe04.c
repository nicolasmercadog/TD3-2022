/*
 * Ejercicio 4 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>

#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){

   write (STDOUT_FILENO, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
   exit(-1);
} //signal para detener el proceso por si hay algun error en las tuberias

int main (){

   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   signal(SIGPIPE, pipe_sign_handler); //se invoca la señal

   if (pipe(ipc) == -1)//si se crea mal la tubería finaliza  el programa con error
      exit(-1);

   //close(ipc[0]);//cierro la lectura de la tubería

   switch (fork()){ //creo un proceso hijo

      case 0:
         close(ipc[1]); //cierro la escritura de la tuberia
         printf("Leyendo tuberia... \n");
         leido = read(ipc[0], buff, sizeof(buff)); //leo el contenido de la tuberia
         if(leido < 1){
            write(STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia")); //si no se pudo leer entonces marco un error
         }else { //si se pudo leer entonces muestro en la pantalla lo que estaba en la tuberia
            write(STDOUT_FILENO, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
            write(STDOUT_FILENO, buff, leido-1);
            printf(", por el proceso hijo, pid %d \n", getpid());
         }
         exit(0);

      default://lo que hace el padre
         strncpy(buff, DATA, sizeof(DATA)); //copio lo que hay en DATA en buff
         write(ipc[1], buff, sizeof(DATA)); //escribo en la tubería lo que hay en buff

         wait(NULL);//espero al hijo

         exit(0);
   }
}
/* Al ingresar echo $? me devuelve 255, es decir que hay un error y
el error está en que si cierro la tubería al principio, esta se destruye,
quitando el close(ipc[0]) del principio  se resuelve y echo $? me devuelve 0
network*/
