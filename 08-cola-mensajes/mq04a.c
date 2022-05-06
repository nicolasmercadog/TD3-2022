/*
* Ejercicio 3 del TP de Cola de mensajes
  Programa que escribe en la cola de mensajes
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <signal.h>

#define MQ_PATH "/MQ_TD3" 

int err, leido;
char buff[10][1024];
int priori[10];  
int cant; 
mqd_t mqd; 
struct mq_attr attr, attr_rcv;

void sig_user1(int a){
   
   err = mq_close(mqd); //cierra la cola de mensaje
   if (( err < 0 )){
      write(STDOUT_FILENO, "\nerror en mq_close()\n", sizeof("\nerror en mq_close()\n"));
      exit(-1);   }

   write(STDOUT_FILENO, "\nCola de mensajes cerrada\n", sizeof("\nCola de mensajes cerrada\n"));


   err = mq_unlink(MQ_PATH); //borra la cola de mensaje
   if(err == -1){
        write(STDOUT_FILENO, ")\nerror en mq_unlink())\n", sizeof(")\nerror en mq_unlink())\n"));
      exit(-1);    }

   write(STDOUT_FILENO, ")\nCola de mensajes eliminada\n", sizeof(")\nCola de mensajes eliminada\n"));

   write(STDOUT_FILENO, "\nTerminando proceso...\n", sizeof("\nTerminando proceso...\n"));
   
   exit(0);
}

int main() {
   
   signal(SIGUSR1, sig_user1); //señal para cerrar la cola de mensaje

   printf ("Mi pid es %d\n", getpid());


   attr.mq_msgsize = sizeof(buff); //tamaño máximo del mensaje


   mqd = mq_open(MQ_PATH, O_WRONLY | O_CREAT, 0777, &attr); //se crea una cola de mensaje pero en lectura, 
   //mqd = mq_open(DireccionDeColaDeMensaje, bandera, Atributos de usuario, Atributos de cola);
   /*Bandera --> O_CREAT : Crea una cola si no existe
	O_RDONLY  :  Sólo lectura
	O_WRONLY  :  Sólo escritura
	O_RDWR    :  Escritura y lectura
	O_NONBLOCK: No bloqueante
   */
/*   if (mqd < 0) {
      printf ("error en mq_open()");      
      exit(-1) ;}*/

   printf("Cola de mensajes creada\n");
   
   printf("Escriba la cantidad de mensajes a enviar(menor a 10): \n");
   scanf("%d",&cant);
   
   attr.mq_maxmsg = cant; //cantidad  máxima de mensajes 
   
   
      printf("Nro max. de mensajes en cola de mensajes: %ld\n",attr.mq_maxmsg);  //se lee la cantidad de mensajes máxima que se pueden enviar
   printf("Longitud max. de mensaje: %ld\n",attr.mq_msgsize); // se lee el tamaño máximo que puede tener un mensaje
   printf("Nros de mensajes pendientes en cola de mensajes: %ld\n",attr.mq_curmsgs); //Se lee la cantidad de mensajes pendientes que hay en la cola
   
  
   for(int i=0; i<cant;i++){
   
   printf("Escriba el mensaje:  \n");
   
   read(STDIN_FILENO, buff[i], sizeof(buff[i]));
   printf("\nEscriba la prioridad:  ");
   scanf("%d", &priori[i]);
   err=0;
   err = mq_send(mqd, buff[i], strlen(buff[i]+1), priori[i]);
      printf("Mensaje enviado (%d)\n", err);
      
      if(err < 0){  //si hay error en enviar el mensaje entonces sale con  -1
      	printf ("error en mq_send()");
      	exit(-1);   } 
   }
   
 //	err = mq_send(mqd, MENSAJE, strlen(MENSAJE)+1, 1);  //strlen nos da la longitud de una cadena
   //err= mq_send(NombreDeCola, Mensaje, LargoDeMensaje, Prioridad);
   	

   
 	err = mq_close(mqd);
   if (( err < 0 )){
      printf ("error en mq_close()");
      exit(-1);   }

      printf("Cola de mensajes cerrada (%d)\n", err);
   
   // Se elimina cola de mensajes
 /*  err = mq_unlink(MQ_PATH);
   if(err == -1){
      printf ("error en mq_unlink()");
      exit(-1);   }

      printf("Cola de mensajes eliminada (%d)\n", err); */

   exit(0);
}
