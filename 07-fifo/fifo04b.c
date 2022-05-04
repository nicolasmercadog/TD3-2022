/*
 * Ejercicio 3.b del TP FIFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h> 

#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[100]="";
   int leido;

  // unlink(FIFO_PATH);    //si la FIFO existe la borro                   

   // FIFO puede ser leida, escrita y ejecutada por: 
   //err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
 //  if(err == -1) {
   //   write(STDOUT_FILENO, "\nError al crear FIFO, la FIFO ya existe", sizeof("\nError al crear FIFO, la FIFO ya existe"));
   //}else {
    //  write(STDOUT_FILENO, "\nFIFO creado correctamente\n", sizeof("\nFIFO creado correctamente\n"));
   //}

         write(STDOUT_FILENO, "\nAbriendo FIFO\n", sizeof("\nAbriendo FIFO\n"));
         write(STDOUT_FILENO, "\nEsperando a que alguien escriba en FIFO\n", sizeof("\nEsperando a que alguien escriba en FIFO\n"));

	 fifo_d = open(FIFO_PATH, O_RDONLY, 0); //el hijo abre la fifo en modo lectura	
         if(fifo_d == -1){
            write(STDOUT_FILENO, "\nError al abrir FIFO ", sizeof("\nError al abrir FIFO "));
            return -1;
         }else {
            write(STDOUT_FILENO, "\nFIFO abierto correctamente", sizeof("\nFIFO abierto correctamente"));
         }

         sleep(5);
         write(STDOUT_FILENO, "\nLeyendo de la FIFO  ", sizeof("\nLeyendo de la FIFO  "));
         
         err = read(fifo_d, buff, sizeof(buff));
         
          if(err == -1) {
            write(STDOUT_FILENO, "\nError al leer de FIFO", sizeof("\nError al leer de FIFO"));
         } else {
            write(STDOUT_FILENO, "\nMensaje LEIDO de FIFO:   ", sizeof("\nMensaje LEIDO de FIFO:   "));
            write(STDOUT_FILENO, buff, sizeof(buff));
         }

         write(STDOUT_FILENO, "\nSaliendo proceso HIJO\n", sizeof("\nSaliendo proceso HIJO\n"));
   
         close(fifo_d);

   //Eliminación FIFO
   //if (unlink(FIFO_PATH) < 0) {
    //   printf("\nNo se puede borrar FIFO.\n");  }         

   exit(0);

}
