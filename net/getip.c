/*
 * getIPandInterfaces.c
 *
 *  Created on: Apr 25, 2013
 *      Author: cem
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

int get_iface_list(struct ifconf *ifconf)
{
   int sock, rval;

   sock = socket(AF_INET,SOCK_STREAM,0);
   if(sock < 0)
   {
     perror("socket");
     return (-1);
   }

   if((rval = ioctl(sock, SIOCGIFCONF , (char*) ifconf  )) < 0 )
     perror("ioctl(SIOGIFCONF)");

   close(sock);

   return rval;
}
int getIPaddress(char* interface, char *ip) {
	static struct ifreq ifreqs[20];
	struct ifconf ifconf;
	int nifaces, i;

	memset(&ifconf, 0, sizeof(ifconf));
	ifconf.ifc_buf = (char*) (ifreqs);
	ifconf.ifc_len = sizeof(ifreqs);

	if (get_iface_list(&ifconf) < 0) return -1;

	nifaces = ifconf.ifc_len / sizeof(struct ifreq);

	printf("Interfaces (count = %d)\n", nifaces);

	for (i = 0; i < nifaces; i++) {
		char ip_addr[INET_ADDRSTRLEN];
		struct sockaddr_in *b = (struct sockaddr_in *) &(ifreqs[i].ifr_addr);
		inet_ntop(AF_INET, & b->sin_addr, ip_addr, sizeof ip_addr);

		if(strcmp(interface,ifreqs[i].ifr_name)==0){
			printf("\t%s\n", interface);
			strcpy(ip,ip_addr);
			break;
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if(argc>1){
		char ip_addr[INET_ADDRSTRLEN];
		getIPaddress(argv[1],ip_addr);
		printf("\t%s\n", ip_addr);
	}
   return 0;
}


