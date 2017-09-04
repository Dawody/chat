#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define DATA "Hello Work of SOCKET"

int main(int argc,char* argv[])
{
	
	if(argc<2)
	{
		printf("You MUST add the address first as argument!\n");
		exit(1);
	}
	//variables
	
	int sock;
	struct sockaddr_in server;
	struct hostent *hp ;
	char buff[1024];


	
	//create connection
	
	sock = socket(AF_INET , SOCK_STREAM ,0);
	
	if(sock < 0)
	{
		printf("socket failed!\n");
	        close(sock);
		exit(1);
	}


	server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);


	if(hp==0)
       	{
	       printf("gethostbyname failed!\n");
	       close(sock);
	       exit(1);
       	}

       	memcpy(&server.sin_addr, hp->h_addr , hp->h_length);
       	server.sin_port = htons(5000);

       	if(connect(sock,(struct sockaddr *)&server, sizeof(server)) < 0)
       	{
	       printf("connect failed!\n");
	       close(sock);
	       exit(1);
       	}

       	if(send(sock, DATA, sizeof(DATA), 0) < 0)
       	{
	       printf("send failed!\n");
	       close(sock);
	       exit(1);
       	}

       	printf("Send %s\n",DATA);
       	close(sock);

       







	return 0;
}
