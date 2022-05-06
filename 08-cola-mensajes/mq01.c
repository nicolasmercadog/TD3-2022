/*
* Ejercicio 1 del TP de Cola de mensajes
* Tipica implementacion de una cola de mensajes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>

#define MENSAJE "DATA PARA OTROS PROCESOS"
#define MQ_PATH "/MQ_TD3"  // El nombre de la cola de mensajes debe empezar con "/"

int main() {
   
   int err, leido;
   char buff[1024];   
   mqd_t mqd;   //Defino la cola de mensaje 
   struct mq_attr attr, attr_rcv; //atributos de la cola de mensaje
  
   // Se fijan algunos parametros de la cola de mensajes antes de crearla
   attr.mq_msgsize = sizeof(buff); //tamaño de mensajes
   attr.mq_maxmsg = 5; //tamaño máximo por mensaje
   
   // Se crea cola de mensajes
   mqd = mq_open(MQ_PATH, O_RDWR | O_CREAT, 0777, &attr);  
   if (mqd < 0) {
      printf ("error en mq_open()");   
      exit(-1); }
      
   printf("Cola de mensajes creada\n"); 
   
   // Escribe en cola de mensajes
   err = mq_send(mqd, MENSAJE, strlen(MENSAJE)+1, 1);  //strlen nos da la longitud de una cadena
   //err= mq_send(NombreDeCola, Mensaje, LargoDeMensaje, Prioridad);
   if(err == -1){  //si hay error en enviar el mensaje entonces sale con  -1
      printf ("error en mq_send()");
      exit(-1);    }

   printf("Mensaje enviado (%d)\n", err);
   
   // Se leen parametros de la cola de mensajes
   if (mq_getattr(mqd, &attr_rcv) == -1){
      printf ("error en mq_getattr()");
      exit(-1); }
      
   printf("Nro max. de mensajes en cola de mensajes: %ld\n",attr_rcv.mq_maxmsg);  //se lee la cantidad de mensajes máxima que se pueden enviar
   printf("Longitud max. de mensaje: %ld\n",attr_rcv.mq_msgsize); // se lee el tamaño máximo que puede tener un mensaje
   printf("Nros de mensajes pendientes en cola de mensajes: %ld\n",attr_rcv.mq_curmsgs); //Se lee la cantidad de mensajes pendientes que hay en la cola

   // Se lee de cola de mensajes
   leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, 0);
   //leido= mq_receive(NombreDeCola, DondeGuardoElMensaje, AtributoDelMensaje, AtributoDefault);
   if (( leido < 0 )){
      printf ("error en mq_receive()");
      exit(-1); }

   printf("Mensaje leido: %s\n", buff);
   
   // Se cierra cola de mensajes
   err = mq_close(mqd);
   if (( err < 0 )){
      printf ("error en mq_close()");
      exit(-1);   }

      printf("Cola de mensajes cerrada (%d)\n", err);
   
   // Se elimina cola de mensajes
   err = mq_unlink(MQ_PATH);
   if(err == -1){
      printf ("error en mq_unlink()");
      exit(-1);   }

      printf("Cola de mensajes eliminada (%d)\n", err);
      
   exit(0);
}
