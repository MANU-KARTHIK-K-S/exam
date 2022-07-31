// SELECTIVE REPEAT : SERVER
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/time.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>
void rsendd(int ch,int c_sock){
char buff2[60];
 bzero(buff2,sizeof(buff2));
 strcpy(buff2,"reserver message :");
 buff2[strlen(buff2)]=(ch)+'0';
 buff2[strlen(buff2)]='\0';
 printf("Resending Message to client
:%s \n",buff2);
 write(c_sock, buff2, sizeof(buff2));
 usleep(1000);
}
int main() {
 int s_sock, c_sock;
 s_sock = socket(AF_INET, SOCK_STREAM,
0);
 struct sockaddr_in server, other;
 memset(&server, 0, sizeof(server));
 memset(&other, 0, sizeof(other));
 server.sin_family = AF_INET;
 server.sin_port = htons(9009);
 server.sin_addr.s_addr = INADDR_ANY;
 socklen_t add;

 if(bind(s_sock, (struct sockaddr*)&server,
sizeof(server)) == -1) {
 printf("Binding failed\n");
 return 0;
 }
 printf("\tServer Up\n Selective repeat
scheme\n\n");
 listen(s_sock, 10);
 add = sizeof(other);
 c_sock = accept(s_sock, (struct
sockaddr*)&other, &add);
 time_t t1,t2;
 char msg[50]="server message :";
 char buff[50];
 int flag=0;
fd_set set1,set2,set3;
 struct timeval timeout1,timeout2,timeout3;
 int rv1,rv2,rv3;
int tot=0;
int ok[20];
memset(ok,0,sizeof(ok));
while(tot<9){
int toti=tot;
for(int j=(0+toti);j<(3+toti);j++){
 //printf("%d %d %d \n",tot,toti,j);
 bzero(buff,sizeof(buff));
 char buff2[60];
 bzero(buff2,sizeof(buff2));
 strcpy(buff2,"server message :");
 buff2[strlen(buff2)]=(j)+'0';
 buff2[strlen(buff2)]='\0';
 printf("Message sent to client :%s
\n",buff2,tot,j);
 write(c_sock, buff2, sizeof(buff2));
 usleep(1000);
}
for(int k=0+toti;k<(toti+3);k++){
 qq:
 FD_ZERO(&set1);
 FD_SET(c_sock, &set1);
 timeout1.tv_sec = 2;
 timeout1.tv_usec = 0;

 rv1 = select(c_sock + 1, &set1, NULL, NULL,
&timeout1);
 if(rv1 == -1)
 perror("select error ");
 else if(rv1 == 0){
 printf("Timeout for message :%d \n",k);
 rsendd(k,c_sock);
 goto qq;} // a timeout occured
 else{
 read(c_sock, buff, sizeof(buff));
 printf("Message from Client: %s\n",
buff);
 if(buff[0]=='n'){
 printf(" corrupt message awk (msg
%d) \n",buff[strlen(buff)-1]-'0');
 rsendd((buff[strlen(buff)-1]-
'0'),c_sock);
 goto qq;}
 else
 tot++;
 //printf("%d %d %d \n",tot,toti,k);
 }
}
}

 close(c_sock);
 close(s_sock);
 return 0; 
        }
SELECTIVE REPEAT : CLIENT
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int isfaulty(){ //simulating corruption of
message
int d=rand()%4;
//printf("%d\n",d);
return (d>2);
}
int main() {
 srand(time(0));
 int c_sock;
 c_sock = socket(AF_INET, SOCK_STREAM,
0);
 struct sockaddr_in client;
 memset(&client, 0, sizeof(client));
 client.sin_family = AF_INET;
 client.sin_port = htons(9009);
 client.sin_addr.s_addr =
inet_addr("127.0.0.1");

 if(connect(c_sock, (struct
sockaddr*)&client, sizeof(client)) == -1) {
 printf("Connection failed");
 return 0;
 }
 printf("\n\tClient -with individual
acknowledgement scheme\n\n");
 char msg1[50]="akwnowledgementof-";
 char msg3[50]="negative akwn-";
 char msg2[50];
 char buff[100];
 int count=-1,flag=1;
 while(count<8){
 bzero(buff,sizeof(buff));
 bzero(msg2,sizeof(msg2));
 if(count==7&&flag==1){
 //sleep(3);
 printf("here\n");
 //simulate loss
 //i--;
 flag=0;

 read(c_sock,buff,sizeof(buff));
 //printf("aa %s \n",buff);
 continue;
 }
 int n = read(c_sock, buff,
sizeof(buff));
 char i=buff[strlen(buff)-1];
 printf("Message received from
server : %s \n",buff);
 int isfault=isfaulty();
 printf("correption status : %d
\n",isfault);
 printf("Response/akwn sent for
message \n");
 if(isfault)
 strcpy(msg2,msg3);
 else{
 strcpy(msg2,msg1);
 count++;}
 msg2[strlen(msg2)]=i;
 write(c_sock,msg2, sizeof(msg2));
 }

 close(c_sock);
 return 0;
}
// OUTPUT :
// Client
// $ ./c 3000
//  Client -with individual acknowledgement
// scheme
// Message received from server : server message :0
// correption status : 0
// Response/akwn sent for message
// Message received from server : server message :1
// correption status : 0
// Response/akwn sent for message
// Message received from server : server message :2
// correption status : 1
// Response/akwn sent for message
// Message received from server : reserver message :2
// correption status : 0
// Response/akwn sent for message
// Message received from server : server message :3
// correption status : 0
// Response/akwn sent for message 
//         Message received from server : server message :4
// correption status : 0
// Response/akwn sent for message
// Message received from server : server message :5
// correption status : 0
// Response/akwn sent for message
// Message received from server : server message :6
// correption status : 0
// Response/akwn sent for message
// Message received from server : server message :7
// correption status : 0
// Response/akwn sent for message
// here
// Message received from server : reserver message :8
// correption status : 0
// Response/akwn sent for message
// Server
// $ ./s 3000
//  Server Up
//  Selective repeat scheme
// Message sent to client :server message :0
// Message sent to client :server message :1
// Message sent to client :server message :2
// Message from Client: akwnowledgementof-0
// Message from Client: akwnowledgementof-1
// Message from Client: negative akwn-2
//  corrupt message awk (msg 2)
// Resending Message to client :reserver message :2
// Message from Client: akwnowledgementof-2
// Message sent to client :server message :3
// Message sent to client :server message :4
// Message sent to client :server message :5
// Message from Client: akwnowledgementof-3
// Message from Client: akwnowledgementof-4
// Message from Client: akwnowledgementof-5
// Message sent to client :server message :6
// Message sent to client :server message :7
// Message sent to client :server message :8
// Message from Client: akwnowledgementof-6
// Message from Client: akwnowledgementof-7
// Timeout for message :8
// Resending Message to client :reserver message :8
// Message from Client: akwnowledgementof-8 
