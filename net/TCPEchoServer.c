#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <string.h>
#define MAXPENDING 5    /* Maximum outstanding connection requests */

void DieWithError(char *errorMessage);  /* Error handling function */
char* HandleTCPClient(int clntSocket);   /* TCP client handling function */
void handoff_handler (char* message) ;
int main(int argc, char *argv[])
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short echoServPort;     /* Server port */
    unsigned int clntLen;            /* Length of client address data structure */

    if (argc != 2)     /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);  /* First arg:  local port */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
      
    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, 
                               &clntLen)) < 0)
            DieWithError("accept() failed");

        /* clntSock is connected to a client! */

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
	char *message;
	message=HandleTCPClient(clntSock);
   	printf("message : %s\n",message);
	 handoff_handler (message); 
	free(message);
    }
    /* NOT REACHED */
}
void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
#define RCVBUFSIZE 32   /* Size of receive buffer */



char* HandleTCPClient(int clntSocket)
{

   // int my_net_id;
   // int client_id;
  //  recv(clntSocket, &my_net_id, 4, 0);
   // client_id = ntohl(my_net_id);
   // printf("Incoming Message: %d",client_id );

    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    char *whole;
    asprintf(&whole, "%s","");
    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE , 0)) < 0)
        DieWithError("recv() failed");
   
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
       echoBuffer[recvMsgSize]='\0';
      // printf("Incoming Message: %s\n",echoBuffer);
       asprintf(&whole, "%s%s",whole,echoBuffer);
       /* See if there is more data to receive */
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
    }

  // printf("message in handle : %s\n",whole);
   close(clntSocket);    /* Close client socket */
   return whole;
}

void handoff_handler (char *message) {

	char str[] ="SSID:ufit-left";
  	char * ssid;

  	//printf ("Splitting string \"%s\" into tokens:\n",str);
  	ssid = strtok (str,",");//split in two part get first part -> SSID:ufit-left
	ssid=strtok (ssid,":"); //split in two SSID:
	ssid=strtok (NULL,":"); //get the rest part 
	//printf ("SSID %s\n",ssid);
  	
	char *ownipaddress; 
	//ownipaddress = getWlanIPaddress(); 
	printf("Request move towards to AP with IP : %s\n",ownipaddress);

	char *new_wpa_supp;
	asprintf(&new_wpa_supp,"wpa_supplicant_%s.conf",ssid);

	char *run;
	asprintf(&run,"sudo wpa_supplicant -Dwext -i eth1 -c %s & ",new_wpa_supp);
       	//printf("Command to run : %s \n",run);
	
	/*
	if( !strncmp(ownipaddress, "192.168.127", 11)) {
		system("sudo killall wpa_supplicant");
		system("sudo wpa_supplicant -Dwext -i eth1 -c wpa_supplicant_left.conf &"); 
		system("sudo dhclient eth1 "); 
		system("sudo ip r a default via 192.168.126.1 dev eth1 "); 
	}
	else {
		system("sudo killall wpa_supplicant");
		system("sudo wpa_supplicant -Dwext -i eth1 -c wpa_supplicant_right.conf &"); 
		system("sudo dhclient eth1 "); 
		system("sudo ip r a default via 192.168.127.1 dev eth1 "); 
	}		
	*/	
	free(new_wpa_supp);
	free(run);
}


