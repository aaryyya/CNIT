#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
 int server_socket,client_socket;
 struct sockaddr_in server_addr,client_addr;
 socklen_t client_addr_len=sizeof(client_addr);
 
 //create socket
 server_socket=socket(AF_INET,SOCK_STREAM,0);
 if(server_socket==-1){
 perror("socket creation failed");
 return 1;
 }
 
 //bind
 server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr=INADDR_ANY;
 server_addr.sin_port=htons(12345);
 
 if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
 {
  perror("Binding failed");
  close(server_socket);
  return 1;
 }
 
 //start listening  
 if(listen(server_socket,1)==-1){
 perror("listening failed");
 close(server_socket);
 return 1;
 }
 
 printf("server ready");
 
 while(1){
 //accepting
 client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&client_addr_len);
 
 if(client_socket==-1){
 perror("accepting connection failed");
 continue;}
 
 printf("server connected to client");
 ////////////////////////////////////////////////////////
 
 char buffer[100];
 int len=sizeof(buffer);
 recv(client_socket,buffer,len,0);

printf("the bit & flag suffed data is: %s\n",buffer);
 
 
 
 
 
 
 
 
 ///////////////////////////////////////////////////////////////////
 
/* char servermessage[256] = "Hello Client and we are connected now";
 if (send(client_socket, servermessage, sizeof(servermessage), 0) < 0) {
        printf("Send failed\n");
    }*/
/*
 char serverresponse[256];
 int len = sizeof(serverresponse);
    recv(client_socket, &serverresponse, len, 0);

    printf("The reply from the server is: %s\n", serverresponse);
*/
 
 
 
 
 
 //close client
 close(client_socket);
 }
 
 //close server 
 close(server_socket);
 
 printf("server stopped");
 return 0;
 
}
