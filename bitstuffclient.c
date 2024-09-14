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
 
 char flag[] = "01111110";
    char data[30];
    int c = 0;
    char bsdata[100];
    int datasize;

    printf("\nEnter data to be transmitted in binary : ");
    scanf("%s", data);

    datasize = strlen(data);

    char newdata[100];
    strcpy(newdata, flag);

    int N = strlen(flag);
    int j = 0;

    for (int i = 0; i < datasize; i++) {
        if (data[i] == '1') { // Compare with character '1'
            bsdata[j] = data[i];
            j++;
            c++;

            if (c == 5) {
                bsdata[j] = '0'; // Insert '0'
                j++;
                c = 0;
            }
        } else {
            bsdata[j] = data[i];
            j++;
            c = 0;
        }
    }

    bsdata[j] = '\0'; // Null-terminate bsdata

    strcpy(newdata + strlen(flag), bsdata);

    strcpy(newdata + strlen(flag) + strlen(bsdata), flag);

    newdata[N + strlen(bsdata) + N] = '\0'; // Null-terminate newdata

    // Now, you should send only the required data length
    if (send(client_socket, newdata, strlen(newdata), 0) < 0) {
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
