// TCP MULTIUSER SERVER – multiuserserver.c
#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#define PORT 4444
#define BUF_SIZE 2000
#define CLADDR_LEN 100
void main() {
struct sockaddr_in addr, cl_addr;
int sockfd, len, ret, newsockfd;
char buffer[BUF_SIZE];
pid_t childpid;
char clientAddr[CLADDR_LEN];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
printf("Error creating socket!\n");
exit(1); }
printf("Socket created...\n");
memset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = INADDR_ANY;
addr.sin_port = PORT;
ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
if (ret < 0) {
printf("Error binding!\n");
exit(1); }
printf("Binding done...\n");
printf("Waiting for a connection...\n");
listen(sockfd, 5);
for (;;) { //infinite loop
len = sizeof(cl_addr);
newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
if (newsockfd < 0) {
printf("Error accepting connection!\n");
exit(1); }
printf("Connection accepted...\n");
inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
if ((childpid = fork()) == 0) { //creating a child process
close(sockfd);
//stop listening for new connections by the main process.
//the child will continue to listen.
//the main process now handles the connected client.
for (;;) {
memset(buffer, 0, BUF_SIZE);
ret = recv(newsockfd, buffer, BUF_SIZE, 0);
if(ret < 0) {
printf("Error receiving data!\n");
exit(1); }
printf("Received data from %s: %s\n", clientAddr, buffer);
ret = send(newsockfd, buffer, BUF_SIZE, 0);
if (ret < 0) {
printf("Error sending data!\n");
exit(1); }
printf("Sent data to %s: %s\n", clientAddr, buffer);
} } close(newsockfd);
} }
// TCP MULTIUSER CLIENT – multiuserclient.c
#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"
#define PORT 4444
#define BUF_SIZE 2000
int main(int argc, char**argv) {
struct sockaddr_in addr, cl_addr;
int sockfd, ret;
char buffer[BUF_SIZE];
struct hostent * server;
char * serverAddr;
if (argc < 2) {
printf("usage: client < ip address >\n");
exit(1); }
serverAddr = argv[1];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
printf("Error creating socket!\n");
exit(1); }
printf("Socket created...\n");
memset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr(serverAddr);
addr.sin_port = PORT;
ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
if (ret < 0) {
printf("Error connecting to the server!\n");
exit(1); }
printf("Connected to the server...\n");
memset(buffer, 0, BUF_SIZE);
printf("Enter your message(s): ");
while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
ret = send(sockfd, buffer, BUF_SIZE, 0);
if (ret < 0) {
printf("Error sending data!\n\t-%s", buffer);
}
ret = recv(sockfd, buffer, BUF_SIZE, 0);
if (ret < 0) {
printf("Error receiving data!\n");
}
else {
printf("Received: ");
fputs(buffer, stdout);
printf("\n"); }
}
return 0; }
// OUTPUT
// Running multiuserchat server
// Running multiuserchat server
// user@user
// user@user--desktopdesktop:~/Desktop/multiuser$ gcc tcpservernew.c :~/Desktop/multiuser$ gcc tcpservernew.c --o so s
// user@user
// user@user--desktop:~/Desktop/multiuser$ ./sdesktop:~/Desktop/multiuser$ ./s
// Socket created...
// Socket created...
// Binding done...
// Binding done...
// Waiting for a connection...
// Waiting for a connection...
// Connection accepted...
// Connection accepted...
// Received data from 192.168.200.33: lmcst
// Received data from 192.168.200.33: lmcst
// Sent data to 192.168.200.33: lmcst
// Sent data to 192.168.200.33: lmcst
// Conn
// Connection accepted...ection accepted...
// Received data from 192.168.200.33: s6cs students
// Received data from 192.168.200.33: s6cs students
// Sent data to 192.168.200.33: s6cs students
// Sent data to 192.168.200.33: s6cs students
// Running multiuser chat client 1
// Running multiuser chat client 1
// user@user
// user@user--desktop:~/Desktop/multiuser$ gcc tcpclientnew.c desktop:~/Desktop/multiuser$ gcc tcpclientnew.c --o c1o c1
// user@user
// user@user--desktop:~/Desktop/multiuser$ ./c1 desktop:~/Desktop/multiuser$ ./c1 192.168.200.33192.168.200.33
// Socket created...
// Socket created...
// Connected to the server...
// Connected to the server...
// Enter your message(s): lmcst
// Enter your message(s): lmcst
// Received: lmcst
// Received: lmcst
// Running multiuser chat client 2
// Running multiuser chat client 2
// user@user
// user@user--desktop:~/Desktop/multiuser$ gcc tcpclientnew.c desktop:~/Desktop/multiuser$ gcc tcpclientnew.c --o c2o c2
// user@user
// user@user--desktop:~/Desktop/multiuser$ ./c2 192.168.2desktop:~/Desktop/multiuser$ ./c2 192.168.200.3300.33
// Socket created...
// Socket created...
// Connected to the server...
// Connected to the server...
// Enter your message(s): s6cs students
// Enter your message(s): s6cs students
// Received: s6cs students
// Received: s6cs students
