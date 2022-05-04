/*
 * Ejercicio 3 del TP FIFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h> 

#define MENSAJE "MENSAJE PARA PROCESO B"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;

   unlink(FIFO_PATH);    //si la FIFO existe la borro                   

   // FIFO puede ser leida, escrita y ejecutada por: 
   err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
   if(err == -1) {
      write(STDOUT_FILENO, "\nError al crear FIFO, la FIFO ya existe", sizeof("\nError al crear FIFO, la FIFO ya existe"));
   }else {
      write(STDOUT_FILENO, "\nFIFO creado correctamente\n", sizeof("\nFIFO creado correctamente\n"));
   }
           write(STDOUT_FILENO, "\nEsperando a que alguien lea la FIFO\n", sizeof("\nEsperando a que alguien lea la FIFO\n"));
         fifo_d = open(FIFO_PATH, O_WRONLY , 0); //el padre abre la fifo O_WRONLY O_NONBLOCK
         
         if(fifo_d == -1){
            write(STDOUT_FILENO, "\nError al abrir FIFO ", sizeof("\nError al abrir FIFO "));
            return -1;
         }else {
            write(STDOUT_FILENO, "\nFIFO abierto correctamente", sizeof("\nFIFO abierto correctamente"));
         }

         // Se escribe en el FIFO
         err = write(fifo_d, MENSAJE, sizeof(MENSAJE)); //se escribe lo que hay en MENSAJE en la fifo 
         if(err == -1) {
            write(STDOUT_FILENO, "\nError al escribir en FIFO\n", sizeof("\nError al escribir en FIFO\n"));
         } else {
            write(STDOUT_FILENO, "\nEscritos MENSAJE en FIFO\n", sizeof("\nEscritos MENSAJE en FIFO\n"));
         }

        // close(fifo_d); //Si cierro la fifo, se puede abrir de nuevo?
   
   //Eliminación FIFO
   //if (unlink(FIFO_PATH) < 0) {
    //   printf("\nNo se puede borrar FIFO.\n");  }         

   exit(0);

}
