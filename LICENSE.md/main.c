#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include "func.h"
#define maxusers 10
#include <sys/time.h>

#define PORT 5555



int main()
{
    int opt = 1;
	int sServer , addrlen , sClient , client_socket[10] ,
    max_clients = 10,i,sendref;
	struct sockaddr_in address;
    int ref=0;
    char message[256] = {"\n\n\t     WELCOME TO LGI SERVER v1.0\n\t<--------------------------------->\n \n\t     DEVELOPED BY :  \t CHBAB KHALID \n\t\t\t\t IMANE EL ASSARIEL \n\t\t\t\t EL HAMAMI AMAL \n\t\t\t\t EL IMRANI NOUHAILA   \n\n"};


    printf("\n\t     Welcome To Your Server\n");
    printf("\t<|----------------------------|>\n\n");
    while(ref==0)
    {
        ref=serv_menu();
    }

//---------------------------------------------------------------

	//initialise all client_socket[] to 0 so not checked
	for (i = 0; i < max_clients; i++)
	{
		client_socket[i] = 0;
	}

	//create a master socket
	if( (sServer = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		perror("\n\t Socket Failed");
		exit(EXIT_FAILURE);
	}

	//set master socket to allow multiple connections ,
	//this is just a good habit, it will work without this
	if( setsockopt(sServer, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,sizeof(opt)) < 0 )
	{
		perror("\n\t Set Socket Options");
		exit(EXIT_FAILURE);
	}

	//type of socket created
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	//bind the socket to localhost port 8888
	if (bind(sServer, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("\n\t Bind Failed :( ");
		exit(EXIT_FAILURE);
	}
	printf("\n\t Listen - port : %d \n", PORT);

	//try to specify maximum of 3 pending connections for the master socket
	if (listen(sServer, 10) < 0)
	{
		perror("\n\t Listen Failed ;)");
		exit(EXIT_FAILURE);
	}

	//accept the incoming connection
	addrlen = sizeof(address);
	printf("\n\t Waiting For Connections ...");

	while(1)
	{
            int pid;
            char login[10],password[10];

			sClient = accept(sServer,(struct sockaddr *)&address,&addrlen);
			if (sClient<0)
			{
				printf("\n\t Accept Error");
				exit(EXIT_FAILURE);
			}
			pid=fork();
			if(pid<0 || pid>0)
			{
			    close(sClient);
			}
			else if (pid==0)
			{
                printf("\n\n\t New Client , ip is : %s , port : %d\n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
// welcome msg ---------------------------------
                while(1)
            {
                sendref=send(sClient,message,strlen(message),0);
                if( sendref != strlen(message) )
                    {
                        perror("\n\t Send");
                        exit(EXIT_FAILURE);
                    }
                else
                    {
                        puts("\n\t Welcome Message Sent Successfully :)");
                        break;
                    }
            }
//------------------------------------------

//loging and password------------------------------------


            while(1)
            {
                int i=0;
                char msg[10];
                char path[256];
                char str[256];
                FILE *fp;
                FILE *fd;

                fp=fopen("users.txt","r");
                memset(&msg,0,sizeof(msg));
                read(sClient,msg,sizeof(msg));
                strcpy(login,msg);
                memset(&msg,0,sizeof(msg));
                if(checklogin(login)==1)
                {
                    memset(&password,0,sizeof(password));
                    memset(&msg,0,sizeof(msg));

                    read(sClient,msg,sizeof(msg));
                    strcpy(password,msg);
                    sprintf(path,"%s/password.txt",login);
                    fd=fopen(path,"r");
                    while(fscanf(fd,"%s",str)!=EOF)
                        {
                            int n;
                            n=strncmp(str,msg,sizeof(str));

                            if(n==0)
                            {
                            char answr[3];
                            printf("\n\t CLIENT %s CONNECTED!! \n",login);
                            memset(&answr,0,sizeof(answr));
                            strcpy(answr,"UP");
                            write(sClient,answr,strlen(answr));
                            for(i=0;i<maxusers;i++)
                                {
                                    if(strcmp(user[i].login,"")==0)
                                    {
                                        strcpy(user[i].login,login);
                                        strcpy(user[i].pswd,password);
                                        break;
                                    }
                                }
                            break;
                            }
                            else{
                                printf("\n\t Closing socket \n");
                                memset(&msg,0,sizeof(msg));
                                close(sClient);
                                break;
                            }
                            break;
                        }
                        break;
                        memset(&msg,0,sizeof(msg));

                        fclose(fd);
                }
                else
                {
                    i++;
                    if(i==3)
                    {
                        fclose(fp);
                        close(sClient);
                    }

                }

                fclose(fp);

            }
//--------------------------------------------------------

//----- menu client --------------------------------------
                while(1)
                {
                    int n;
                    char choix[2];
                    recv(sClient,choix,sizeof(choix),0);
                    n=atoi(choix);
                    switch (n)
                        {
                            case 1 : telecharger(sClient,login);
                            break;
                            case 2 : upload(sClient ,login);
                            break;
                            case 3 : delete_file(sClient,login);
                            break;
                            case 4 : lister_fichier(sClient,login);
                            break;
                            case 5 : partage(sClient,login);
                            break;
                            case 6 : ;
                            break;
                            case 7 : ;
                            break;
                            case 8 :close(sClient);
                            break;
                        }
                        if (n==7)
                        break;
                        }

                }// end of fork
            close(sClient);

	}

	return 0;
}



