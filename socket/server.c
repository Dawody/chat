#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main(int argc , char* argv[])
{
	//Variables
	int sock;
	struct sockaddr_in server;
	int mysock;
	char buff[1024];
	int rval;


	//Create socket
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		printf("Failed to create socket!\n");
		close(sock);
		exit(1);
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5000);



	//Call bind
	if(bind(sock, (struct sockaddr *)&server,sizeof(server)))
	{
		printf("bind faild!\n");
		close(sock);
		exit(1);
	}



	//Listen
	listen(sock,5);


	//Accept
	do
	{
		mysock = accept(sock , (struct sockaddr *)0 , 0);
		if(mysock == -1)
		{
			printf("accept failed!\n");
			close(sock);
			exit(1);
		}
		else
		{
			memset(buff,0,sizeof(buff));
			if( (rval=recv(mysock,buff,sizeof(buff),0)) < 0)
			{
				printf("reading stream message error!\n");
				close(sock);
				exit(1);

			}
			else if(rval==0)
			{
				printf("Ending Connection!\n");

			}
			else
			{
				printf("MSG : %s\n",buff);
			}
			printf("Got the Message (rval = %d)\n",rval);
			close(mysock);
		}
	}while(1);

	return 0;
}
