/*
 * Ejercicio 3 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>

#define FRASE_A "INFORMACION IMPORTANTE1"
#define FRASE_B "INFORMACION IMPORTANTE2"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){

   write (STDOUT_FILENO, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
}

int main (){

   int ipc1[2],ipc2[2], proc;
   int leido1,leido2, success;
   char buff1[BUFF_SIZE] = {0};
   char buff2[BUFF_SIZE] = {0};

   signal(SIGPIPE, pipe_sign_handler); // manejador de la señal de pipe

   pipe(ipc1); //crea la pipe
   pipe(ipc2);

   switch (fork()){ //se crea un hijo

      case 0:
      close(ipc1[0]);      // se cierra la tubería para leer
      strncpy(buff1, FRASE_A, sizeof(FRASE_A)); //se copia lo que hay de frase a en buff
      write(ipc1[1], buff1, sizeof(FRASE_A));//se escribe lo que hay en buff en la tuberia
      exit(0);//finaliza el hijo
      break;

      default:
      switch (fork()){ //se crea un hijo dentro del otro hijo

         case 0://realiza lo mismo que hizo el primer hijo
            close(ipc2[0]);
            strncpy(buff2, FRASE_B, sizeof(FRASE_B));
            write(ipc2[1], buff2,    sizeof(FRASE_B));
            exit(0);
         break;
         default://continua el padre
            close(ipc1[1]);//cierra la tubería para escribir
            close(ipc2[1]);//cierra la tubería para escribir
            int i;
            //for(i=0; i<; i++){ // es neesario el for?
               leido1 = read(ipc1[0], buff1, sizeof(buff1));//lee lo que hay en la tubería
               leido2 = read(ipc2[0], buff2, sizeof(buff2));//lee lo que hay en la tubería
               if(leido1 < 0 && leido2 < 0){//si la tubería está vacía marca error
                  write (STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
               }else {
                  write (STDOUT_FILENO, "Leido de la tuberia1 ", sizeof("\nLeido de la tuberia"));
                  write (STDOUT_FILENO, buff1, leido1-1); //muestra en pantalla lo que leyó de la tubería
                  printf("\n");
                  write (STDOUT_FILENO, "Leido de la tuberia2 ", sizeof("\nLeido de la tuberia"));
                  write (STDOUT_FILENO, buff2, leido2-1); //muestra en pantalla lo que leyó de la tubería
                  printf(", por el proceso padre, pid %d \n", getpid());
               }
          //  }
            //close(ipc1[0]);//
            close(ipc1[0]);//cierra la tubería para escribir
            wait(NULL);
            wait(NULL);//espera a los 2 hijos
            exit(0);//finaliza el padre
         break;
      }
   }
}

//El problema de este programa es que el padre lee de la tubería pero no sabe de cual hijo lee
//La solución sería crear 2 pipes por separado
