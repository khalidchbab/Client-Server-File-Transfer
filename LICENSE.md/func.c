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
#include <unistd.h>
void gotoxy(int x,int y)
 {
 printf("%c[%d;%df",0x1B,y,x);
 }

int check(char *msg)
{
    char str[100];
    FILE *fd=fopen("users.txt","r");
    int n;
    int check;
    while(fscanf(fd,"%s",str)!=EOF)
        {
            n=strncmp(str,msg,sizeof(str));

            if(n==0)
                {
                    printf("\nThis user exist !! \n");
                    check=1;
                }
        }
    fclose(fd);
    return check;
}


int checklogin(char *msg)
{
    char str[100];
    FILE *fd=fopen("users.txt","r");
    int n;
    int check;
    while(fscanf(fd,"%s",str)!=EOF)
        {
            n=strncmp(str,msg,sizeof(str));

            if(n==0)
                {
                    check=1;
                }
        }
    fclose(fd);
    return check;
}


void crt_usr()
{
// Declarations
    int count=0;
    int m;
    FILE *fd;
    char str[100];
    char login[20];


//----------------------------------
        fd=fopen("users.txt","a");

        while(fgets(str,"%s",fd)!=NULL)
            {
                count++;
                bzero(str,100);
            }
        fclose(fd);

//----------------------------------
    if(count<10)
    {
        printf("\n\t<|---------------------------------|>");
        printf("\n\t     You Are Creating A new User \n");
    // getting user loging and password
        printf("\n\t Enter User Login : ");
        scanf("%s",user[count].login);
        sprintf(login,"%s",user[count].login);
        printf("\n\t Enter User Password : ");
        scanf("%s",user[count].pswd);
//----------------------------------
// testing if user exist
        fd=fopen("users.txt","a+");

        if(fd==NULL)
        {
            printf(" \n\t Can't open file! \n");
        }
        else
        {
            m=check(login);
//------------------------------------
// creating user
            if(m!=1)
            {
                char cmd[10];
                bzero(cmd,sizeof(cmd));
                sprintf(cmd,"mkdir %s",user[count].login);
                system(cmd);
                bzero(cmd,sizeof(cmd));

                sprintf(cmd,"mkdir %s/files",user[count].login);
                system(cmd);
                bzero(cmd,sizeof(cmd));

                sprintf(cmd,"echo %s > ./%s/password.txt",user[count].pswd,user[count].login);
                system(cmd);
                fprintf(fd,user[count].login);
                fprintf(fd,"\n");

                printf("\n\t User %s Created \n",user[count].login);

                fclose(fd);

            }

        }

        count++;
    }
//----------------------------------------
    else
    {

        printf("\nSorry There is No Place to Add More users ..");

    }
    printf("\n\n----------------------------------------------------------------------------|>\n\n");
    sleep(1);
}

void supp_usr()
{
    char *old="usersv2.txt",*news="users.txt";
    FILE *fd;
    FILE *tmp;
    char str[100],usr[10];
    int n;

    printf("\n\t<|------------------------|>");
    printf("\n\t You Are Deleting A User \n");

    printf("\n\t Enter User Login To Delete : ");
    scanf("%s",usr);

    fd=fopen("users.txt","r");
    if(fd==NULL)
        {
            printf("\n\t Can't open file! \n");
        }
    tmp=fopen("usersv2.txt","w");
    if(tmp==NULL)
        {
            printf("\n\t Can't open file! \n");
        }

    while(fscanf(fd,"%s",str)!=EOF)
        {
            n=strncmp(str,usr,sizeof(str));

            if(n!=0)
                {
                    fprintf(tmp,str);
                    fprintf(tmp,"\n");
                    puts(str);
                }
            else
                {
                    char cmd[10];
                    bzero(cmd,sizeof(cmd));
                    //sprintf(cmd,"%s/password.txt",usr);
                    //remove(cmd);
                    //bzero(cmd,sizeof(cmd));
                    sprintf(cmd,"rm -rf %s",usr);
                    system(cmd);
                    bzero(cmd,sizeof(cmd));
                    printf("\n\t User Deleted Successfully :)");


                }
        }
    fclose(fd);
    fclose(tmp);
    remove(news);
    rename(old,news);

    printf("\n\n------------------------------------------------|>");


}

void modify_usr()
{

    FILE *fd;
    FILE *tmp;
    char str[100],usr[10],login[10],pswrd[10],path[100];
    int n;

    printf("\n\t<|---------------------------|>");
    printf("\n\t    You Are Modefing A User \n");

    printf("\n\t Enter User Login to modify : ");
    scanf("%s",usr);
    fd=fopen("users.txt","r");
    if(fd==NULL)
        {
            printf("\n\t Can't open file! \n");
        }
    tmp=fopen("usersv2.txt","a+");
    if(tmp==NULL)
        {
            printf("\n\t Can't open file! \n");
        }
    while(fscanf(fd,"%s",str)!=EOF)
        {
            n=strncmp(str,usr,sizeof(str));

            if(n!=0)
                {
                    fprintf(tmp,str);
                    fprintf(tmp,"\n");
                }
            else
                {
                    FILE *fp;
                    printf("\n\t Enter The new Login : ");
                    scanf("%s",login);
                    rename(str,login);
                    sprintf(str,"%s",login);
                    fprintf(tmp,str);
                    fprintf(tmp,"\n");
                    printf("\n\t Enter The New Password : ");
                    scanf("%s",pswrd);
                    sprintf(path,"./%s/password.txt",str);
                    remove(path);
                    fp=fopen(path,"a+");
                    if(fp==NULL)
                        {
                            printf(" \nCan't open file! \n");
                        }

                    fprintf(fp,pswrd);
                    fprintf(fd,"\n");
                    printf("\n\t Successfully Modified : ");
                }
        }
    fclose(fd);
    fclose(tmp);
    remove("users.txt");
    rename("usersv2.txt","users.txt");
    printf("\n----------------------------------------------------------------------------|>\n\n");

}

void find_usr()
{
    int n,found;
    FILE *fd;
    char str[100],usr[10];

    printf("\n\t<|--------------------------------|>");
    printf("\n\t    You Are Searching For A User \n");

    printf("\n\t Search : ");
    scanf("%s",usr);
    fd=fopen("users.txt","r");
    if(fd==NULL)
        {
            printf("\n\t Can't open file! \n");
        }
    while(fscanf(fd,"%s",str)!=EOF)
        {
            n=strncmp(str,usr,sizeof(str));

            if(n==0)
                {
                   found=1;
                }

        }
        if (found == 1)
        {
            printf("\n\t YEAP WE FOUND THE USER");
        }
        else
        {
            printf("\n\t ARE YOU SURE YOU DONT MEAN TO SEARCH ON FACEBOOK");
        }

    printf("\n----------------------------------------------------------------------------|>\n\n");

}






int serv_menu()
{
    int choix,start=0;
    printf("\n\t  ---------------------");
    printf("\n\t | \t  MENU \t\t|");
    printf("\n\t | -------------------- |");
    printf("\n\t | 1- ADD A USER \t|");
    printf("\n\t | 2- MODIFY A USER \t|");
    printf("\n\t | 3- DELETE A USER \t|");
    printf("\n\t | 4- SEARCH For USER\t|");
    printf("\n\t | 5- START SERVER\t|");
    printf("\n\t | 6- EXIT  \t\t|");
    printf("\n\t | 7- ABOUT  \t\t|");
    printf("\n\t |\t\t\t|");
    printf("\n\t |\t\t\t|");
    printf("\n\t  ---------------------");
    printf("\n\t   CHOICE : \t");
    scanf("%d",&choix);

    switch (choix)
    {
        case 1 : crt_usr();break;
        case 2 : modify_usr();break;
        case 3 : supp_usr();break;
        case 4 : find_usr();break;
        case 5 : start=1;break;
        case 6 : exit(1);break;
        case 7 : about();sleep(5);break;
        default : printf("\n\t\t No Such Option :)");
    }
    return start;
}


int upload(int sclient,char login[10])
{
    char flname[100],msg[256],path[512];
    FILE *fd;
    char buffer[256];
    int datasize,nbrl;
    struct stat file_state;

    bzero(msg,sizeof(msg));
    bzero(flname,sizeof(flname));
    read(sclient,flname,sizeof(flname));
    sprintf(path,"%s/files/%s",login,flname);
    if ((fd =fopen(path,"r"))==-1)
    {
		perror("open fail");
        close(sclient);
    }
	nbrl=0;
	while(fgets(buffer,"%s",fd)!=NULL)
	{
          nbrl++;
    }
    fseek(fd,0,SEEK_SET);
    stat(path,&file_state);
    datasize=file_state.st_size;
    bzero(msg,256);
    sprintf(msg,"%d",nbrl);
    write(sclient,msg,sizeof(msg));

	while(fgets(buffer,"%s",fd)!=NULL)
	{
	    write(sclient,buffer,sizeof(buffer));
	    bzero(buffer,256);
	}



	bzero(buffer,sizeof(buffer));
    fclose(fd);
    return 0;
}

int telecharger(int sclient,char login[10])
{
    int bytesReceived = 0;
    char recvBuff[1024];
    long double sz=1;

   	 /* Create file where data will be stored */
    FILE *fp;
	char fname[100];
	read(sclient, fname, 256);
	//strcat(fname,"AK");
	printf("File Name: %s\n",fname);
	printf("Receiving file...");
    memset(recvBuff, '0', sizeof(recvBuff));
   	 fp = fopen(fname, "ab");
    	if(NULL == fp)
    	{
       	 printf("Error opening file");
         return 1;
    	}
    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(sclient, recvBuff, 1024)) > 0)
    {

        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        // printf("%s \n", recvBuff);
    }
    fclose(fp);
    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }
    close(sclient);
    printf("\nFile OK....Completed\n");
    return 0;
}

//----------------------------------------------------------------------------
void lister_fichier(int sclient,char login[10])
{
    FILE *sa;
    char *list="list.txt";
    char buffer[256],cmd[256],path[256];
    int nbrl;

    sprintf(cmd,"dir %s/files /b > %s/files/list.txt",login,login);
    puts(cmd);
    system(cmd);
    bzero(cmd,sizeof(cmd));
    sprintf(path,"%s/files/list.txt",login);
    sa=fopen(path,"r");
        if (sa ==(-1))
            {
                perror("open fail");
                exit (3);
            }
    nbrl=0;
    while(fgets(buffer,"%s",sa)!=NULL)
	{
	    puts(buffer);
        nbrl++;
    }
    fseek(sa,0,SEEK_SET);
    bzero(buffer,256);
    sprintf(buffer,"%d",nbrl);
    send(sclient,buffer,sizeof(buffer),0);

    while(fgets(buffer,"%s",sa)!=NULL)
	{
	    send(sclient,buffer,sizeof(buffer),0);
	    bzero(buffer,256);
	}
    fclose(sa);
    remove(list);


}

int delete_file(int sclient, char login[10])
{
    char name[128],cmd[128];
    int status;
    bzero(name,128);
    recv(sclient,name,sizeof(name),0);
    sprintf(cmd,"rm %s/files/%s",login,name);
    status=system(cmd);
    bzero(cmd,128);

    if(status != -1)
    {
        write(sclient,"UP",sizeof("UP"));
        return 0;
    }
    else
    {
        write(sclient,"DW",sizeof("DW"));
        return -1;
    }
}

void partage(int sclient,char login[10])
{

    char name[30],login2[30],path[128],share[128];
    FILE *fd;

    bzero(name,30);
    read(sclient,name,sizeof(name));
    bzero(login2,30);
    read(sclient,login2,sizeof(login2));
    sprintf(path,"%s/sharefiles.txt",login2);
    fd=fopen(path,"a+");
    if (fd ==(-1))
    {
        printf("open fail sharedfiles");
        close(sclient);
    }

    sprintf(share,"%s/files/%s",login,name);
    fprintf(fd,share);
    fprintf(fd,"\n");

    bzero(login2,30);
    bzero(name,30);
    bzero(path,128);
    bzero(share,128);

    fclose(fd);
}


void about()
{
    FILE *sa;
    char buffer[1024];

    sa=fopen("ABOUT.txt","r");
        if (sa ==(-1))
            {
                perror("open fail");
                exit (3);
            }
    while(fgets(buffer,"%s",sa)!=NULL)
	{
	    puts(buffer);
    }
    fclose(sa);

}
