#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define RCVBUFSIZE 32   /* Size of receive buffer */



void sendData(char *message){
   int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    char *echoString;                /* String to send to echo server */
    char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
    unsigned int echoStringLen;      /* Length of string to echo */


  
    servIP = "127.0.0.1";             /* First arg: server IP address (dotted quad) */
    echoString =message ;        /* Second arg: string to echo */
    //strcpy(echoString,message);
    echoServPort=8000;
  

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
       // DieWithError("socket() failed");

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    echoServAddr.sin_port        = htons(echoServPort); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
       // DieWithError("connect() failed");

    echoStringLen = strlen(echoString);          /* Determine input length */

    echoString[strlen(echoString)]='\0';
    echoStringLen = strlen(echoString);   
   // int size1[1];
   // size1[0]=echoStringLen;
   // printf("%d\n",size1[0]);

  uint32_t size = echoStringLen;    
   // printf("%d\n",size);
   // size = htonl(echoStringLen);    
   // printf("%d\n",size);

    //  size = ntohl(size);    
    //  printf("%d\n",size);
 /* Send the string to the server */
    //if (send(sock, (const char*)&size, sizeof(size), 0) != echoStringLen)
       // DieWithError("send() sent a different number of bytes than expected");

	
    /* Send the string to the server */
    if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
       // DieWithError("send() sent a different number of bytes than expected");

	
    printf("\n");    /* Print a final linefeed */

    close(sock);
   // exit(0);
   

}

/*
void send_my_id()
{
 int my_id = 1233;
 int my_net_id = htonl(my_id);
 send(sock, (const char*)&my_net_id, 4, 0);
}

void receive_id()
{
 int my_net_id;
 int client_id;
 recv(client_sock, &my_net_id, 4, 0);
 client_id = ntohl(my_net_id);
}*/
//int main(int argc, char *argv[])
int main()
{	
    char message1[500]="Command  Access Point ";
	int i=0;
    char message2[500]="Command  Access Point aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  for(;;){
	if(i==0){
    		sendData(message1);
		i=1;
	}
	else{
	sendData(message2);
	i=0;
	}
    sleep(1); 
  }
}

