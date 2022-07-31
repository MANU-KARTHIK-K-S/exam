// GO-BACK-N : SERVER
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<arpa/inet.h>
#define W 5
#define P1 50
#define P2 10
char a[10];
char b[10];
void alpha9(int);
int main()
{
 struct sockaddr_in ser,cli;
 int s,n,sock,i,j,c=1,f;
 unsigned int s1;
 s=socket(AF_INET,SOCK_STREAM,0);
 ser.sin_family=AF_INET;
 ser.sin_port=6500;
 ser.sin_addr.s_addr=inet_addr("127.0.0.1");
 bind(s,(struct sockaddr *) &ser, sizeof(ser));
 listen(s,1);
 n=sizeof(cli);
 sock=accept(s,(struct sockaddr *)&cli, &n);
 printf("\nTCP Connection Established.\n");
 s1=(unsigned int) time(NULL);
 srand(s1);
 strcpy(b,"Time Out ");
 recv(sock,a,sizeof(a),0);
 f=atoi(a);
 while(1)
 {
 for(i=0;i<W;i++)
 {
 recv(sock,a,sizeof(a),0);
 if(strcmp(a,b)==0)
 {
 break;
 }
 }
 i=0;
 while(i<W)
 {
 j=rand()%P1;
 if(j<P2)
 {
 send(sock,b,sizeof(b),0);
 break; 
   }
 else
 {
 alpha9(c);
 if(c<=f)
 {
 printf("\nFrame %s Received ",a);
 send(sock,a,sizeof(a),0);
 }
 else
 {
 break;
 }
 c++;
 }
 if(c>f)
 {
 break;
 }
 i++;
 }
 }
 close(sock);
 close(s);
 return 0;
}
void alpha9(int z)
{
 int k,i=0,j,g;
 k=z;
 while(k>0)
 {
 i++;
 k=k/10;
 }
 g=i;
 i--;
 while(z>0)
 {
 k=z%10;
 a[i]=k+48;
 i--;
 z=z/10;
 }
 a[g]='\0';
}
GO-BACK-N : CLIENT
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#define W 5
char a[10];
char b[10];
void alpha9(int);
int main()
{
 int num;
 printf("ENTER NUMBER :");
 scanf("%d",&num);
 alpha9(num);
 printf("A :%s",a);
 /*int s,f,wl,c=1,x,i=0,j,n,p=0,e=0;
 struct sockaddr_in ser;
 s=socket(AF_INET,SOCK_STREAM,0);
 ser.sin_family=AF_INET;
 ser.sin_port=6500;
 ser.sin_addr.s_addr=inet_addr("127.0.0.1");
 connect(s,(struct sockaddr *) &ser, sizeof(ser));
 printf("\nTCP Connection Established.\n");
 printf("\nEnter the number of Frames: ");
 scanf("%d",&f);
 alpha9(f);
 send(s,a,sizeof(a),0);
 strcpy(b,"Time Out ");
 break;
 }
 else
 {
 if(p<=f)
 {
 printf("\nFrame %s Acknowledged",a);
 wl--;
 }
 else
 {
 break;
 }
 }
 if(p>f)
 {
 break;
 }
 i++;
 }
 if(wl==0 && c>f)
 {
 send(s,b,sizeof(b),0);
 break;
 }
 else
 {
 c=c-wl;
 wl=W;
 }
 }
 close(s);
 return 0;
*/
}
void alpha9(int z)
{
 int k,i=0,j,g;
 k=z;
 while(k>0)
 {
 i++;
 k=k/10;
 }
 g=i;
 i--;
 while(z>0)
 {
 k=z%10;
 a[i]=k+48;
 i--;
 z=z/10;
 }
 a[g]='\0';
}
// OUTPUT
// Server
// $ ./s 3000
// TCP Connection Established.
// Frame 1 Received
// Frame 2 Received
// Frame 3 Received
// Frame 4 Received
// Frame 5 Received
// Frame 6 Received
// Frame 7 Received
// Frame 8 Received
// Frame 9 Received
// Client
// $ ./c 3000
// ENTER NUMBER : 70826179
// A :70826179
// TCP Connection Established.
// Enter the number of Frames: 10
// Frame 1 Sent
// Frame 2 Sent
// Frame 3 Sent
// Frame 4 Sent
// Frame 5 Sent
// Frame 1 Acknowledged
// Frame 2 Acknowledged
// Time Out, Resent Frame 3 onwards
// Frame 3 Sent
// Frame 4 Sent
// Frame 5 Sent
// Frame 6 Sent
// Frame 7 Sent
// Frame 3 Acknowledged
// Frame 4 Acknowledged
// Time Out, Resent Frame 5 onwards
// Frame 5 Sent
// Frame 6 Sent
// Frame 7 Sent
// Frame 8 Sent
// Frame 9 Sent
// Frame 5 Acknowledged
// Frame 6 Acknowledged
// Frame 7 Acknowledged
// Frame 8 Acknowledged
// Frame 9 Acknowledged
// Frame 10 Sent 
//  while(1)
//  {
//  for(i=0;i<W;i++)
//  {
//  alpha9(c);
//  send(s,a,sizeof(a),0);
//  if(c<=f)
//  {
//  printf("\nFrame %d Sent",c);
//  c++;
//  }
//  }
//  i=0;
//  wl=W;
//  while(i<W)
//  {
//  recv(s,a,sizeof(a),0);
//  p=atoi(a);
//  if(strcmp(a,b)==0)
//  {
//  e=c-wl;
//  if(e<f)
//  {
//  printf("\nTime Out, Resent Frame
// %d onwards",e);
//  }
