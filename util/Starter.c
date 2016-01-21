/*
 * getIPandInterfaces.c
 *
 *  Created on: Apr 25, 2013
 *      Author: cem
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void print_help(char *prgname) {
	printf("----------| HELP PAGE |------------\n");

	printf("The usage of the code:  %s Neighbor_AP_SSID Neigbor_AP_IP\n", prgname);
	printf("Example usage:  %s UCN-Netgear1 192.168.124.22\n",prgname);
	printf("-----------------------------------\n");

}


int isValidIpAddress(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    //return result != 0;
    return result;

}
//compare here IP format

int main(int argc, char *argv[]) {

	//printf("This program was called with %s.\n", argv[0]);
	printf("-----------------------------------\n");

	char *command_MM="MM";
	char *command_LB;

	switch (argc) {
	case 1:
		printf("The given command has any argument, please check -h !\n");
		break;
	case 2:
		if (strcmp(argv[1],"-h")==0){
			print_help(argv[0]);
		}
		else{
			printf("Given parameter corresponds any functionality, please try -h !\n");
		}
		break;
	case 3:
		if(!isValidIpAddress(argv[2])){
			printf("IP Address isn't in the form of X.X.X.X or X.X.X.X.X.X\n");
			break;
		}
		printf("SSID of Other AP: %s\n",argv[1]);
		printf("IP Address of Other AP: %s\n",argv[2]);
		printf("Command_MM: %s \n", command_MM);

		asprintf(&command_LB, "LB %s %s", argv[1], argv[2]);
		//printf("Command_LB: %s ", command_LB);
		//system(command_MM);
		//system(command_LB);
		printf("LB and MM are started.\n");

		//free(command_LB);
		break;
	default:
		printf("Argument count could be maximal 3, please use -h \n");
		break;
	};
	printf("-----------------------------------\n");

	return 0;
}


