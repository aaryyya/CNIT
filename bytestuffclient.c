#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define server_ip "127.0.0.1"


int main()
{
 int client_socket;
 struct sockaddr_in server_addr;
 
 //create socket
 client_socket=socket(AF_INET,SOCK_STREAM,0);
 if(client_socket==-1){
 perror("socket creation failed");
 return 1;
 }
 
 //connection
 server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr=inet_addr(server_ip);
 server_addr.sin_port=htons(12345);
 
 if(connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
 {
  perror("Binding failed");
  close(client_socket);
  return 1;
 }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 char flag[]="01111110";
 char esc[]="00011011";
 char data[30];
 char temp[30];
 char bsdata[30];
 int datasize;
  printf("\nEnter data to be transmitted in binary :  ");
  scanf("%s",data);
  char newdata[100];
  datasize=strlen(data);
  strcpy(newdata,flag);
  int n=strlen(flag);
  /*for(int i=n;i<n+datasize;i++)
  {
   for(int j=0;j<datasize;j++)
   {
     newdata[i]=data[j];
   }
  }
  for(int i=n+datasize;i<n+n+datasize;i++)
  {
   for(int j=0;j<n;j++)
   {
     newdata[i]=flag[j];
   }
  }*/
  int i=0;
  int k=0;
  while(i<datasize)
  {
    int j=0;
    for(j=0;j<8;j++)
    {
      temp[j]=data[i];
      i++;
    }
    int val1=strcmp(flag,temp);
    int val2=strcmp(esc,temp);
    if(!val1 || !val2)
    { 
       strcpy(bsdata+k,esc);
       k=k+8;
       strcpy(bsdata+k,temp);
       k=k+8;
    }else{
    strcpy(bsdata+k,temp);
    k=k+8;
    }
  }
  
  
  strcpy(newdata + strlen(flag), bsdata); 

  strcpy(newdata + strlen(bsdata) + strlen(flag), flag);
  
  newdata[strlen(bsdata) + strlen(flag)+strlen(flag)]='\0';
  
   if (send(client_socket, newdata, sizeof(newdata), 0) < 0) {
        printf("Send failed\n");
    }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    
 close(client_socket);
 return 0;
 }
