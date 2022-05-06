/*
* Ejercicio 3 del TP de Cola de mensajes
  Programa que leer de la cola de mensajes
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

#define MENSAJE "DATA PARA PROCESO"
#define MQ_PATH "/MQ_TD3" 

int err, leido;
char buff[1024];   
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
   
   unsigned int nmsj=0;
   
   signal(SIGUSR1, sig_user1); //señal para cerrar la cola de mensaje

   printf ("Mi pid es %d\n", getpid());
   
   


   attr.mq_msgsize = sizeof(buff); //tamaño máximo del mensaje
   attr.mq_maxmsg = 5; //cantidad  máxima de mensajes 

   mqd = mq_open(MQ_PATH, O_RDONLY | O_CREAT, 0666, &attr); //se crea una cola de mensaje pero en lectura, 
   //mqd = mq_open(DireccionDeColaDeMensaje, bandera, Atributos de usuario, Atributos de cola);
   /*Bandera --> O_CREAT : Crea una cola si no existe
	O_RDONLY  :  Sólo lectura
	O_WRONLY  :  Sólo escritura
	O_RDWR    :  Escritura y lectura
	O_NONBLOCK: No bloqueante
   */
   if (mqd < 0) {
      printf ("error en mq_open()");      
      exit(-1) ;}

   printf("Cola de mensajes abierta\n");
   
     // Se leen parametros de la cola de mensajes
   if (mq_getattr(mqd, &attr_rcv) == -1){
      printf ("error en mq_getattr()");
      exit(-1); }
      
         printf("Nro max. de mensajes en cola de mensajes: %ld\n",attr_rcv.mq_maxmsg);  //se lee la cantidad de mensajes máxima que se pueden enviar
   printf("Longitud max. de mensaje: %ld\n",attr_rcv.mq_msgsize); // se lee el tamaño máximo que puede tener un mensaje
   printf("Nros de mensajes pendientes en cola de mensajes: %ld\n",attr_rcv.mq_curmsgs); //Se lee la cantidad de mensajes pendientes que hay en la cola
   
	leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, 0);
	 if (( leido < 0 )){
      printf ("error en mq_receive()");
      exit(-1); }
      
      	printf("Mensaje leido: %s \n", buff);
   
      sleep(1);
   

	//   leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, 0);
   //leido= mq_receive(NombreDeCola, DondeGuardoElMensaje, AtributoDelMensaje, AtributoDefault);
  




   exit(0);
}
