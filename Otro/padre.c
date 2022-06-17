/*

Ej de prueba por si acaso
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int a[5]={0,0,0,0,0};

int main(void) 
{
for(int t=0; t<3 ; t++){
a[t]=fork();
}
//sleep(10);
printf("entrado a A");

if (a[1]==0){
//sleep(10);
exit(0);
printf("Pid %d\n",getpid());
}
printf("Pid 2 %d\n",getpid());
a[4]=fork();
if(a[0]==0){
sleep(10);
exit(0);
}
printf("Pid 3 %d\n",getpid());
//sleep(10);
if (a[3]==0){
//sleep(2);
exit(0);
}
printf("Pid 4 %d\n",getpid());
//sleep(10);
exit(0);
}
