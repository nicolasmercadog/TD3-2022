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

#define MENSAJE "HOLA PROCESO HIJO"
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


   switch (fork()){ 
      
      case -1:      
         write(STDOUT_FILENO, "\nError al crear hijo", sizeof("\nError al crear hijo"));
         return -1;
      break;

      case 0:

         write(STDOUT_FILENO, "\nEntrando proceso HIJO", sizeof("\nEntrando proceso HIJO"));

         sleep(5);

         /*  
         //El Hijo que debe hacer con la FIFO ?
         */      

         write(STDOUT_FILENO, "\nSaliendo proceso HIJO\n", sizeof("\nSaliendo proceso HIJO\n"));
         exit(0);
      break;

      default:
         write(STDOUT_FILENO, "\nEntrando proceso PADRE", sizeof("\nEntrando proceso PADRE"));

         fifo_d = open(FIFO_PATH, O_WRONLY, 0);
         if(fifo_d == -1){
            write(STDOUT_FILENO, "\nPADRE: Error al abrir FIFO ", sizeof("\nPADRE: Error al abrir FIFO "));
            return -1;
         }else {
            write(STDOUT_FILENO, "\nPADRE: FIFO abierto correctamente", sizeof("\nPADRE: FIFO abierto correctamente"));
         }

         // Se escribe en el FIFO
         err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
         if(err == -1) {
            write(STDOUT_FILENO, "\nPADRE: Error al escribir en FIFO", sizeof("\nPADRE: Error al escribir en FIFO"));
         } else {
            write(STDOUT_FILENO, "\nPADRE: Escritos MENSAJE en FIFO", sizeof("\nPADRE: Escritos MENSAJE en FIFO"));
         }

         close(fifo_d);

         wait(NULL);
         write(STDOUT_FILENO, "\nSaliendo proceso PADRE\n", sizeof("\nSaliendo proceso PADRE\n"));

      break;   
   }
   
   //Eliminaci�n FIFO
   //if (unlink(FIFO_PATH) < 0) {
    //   printf("\nNo se puede borrar FIFO.\n");  }         

   exit(0);

}
