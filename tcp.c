Code for TCP socket Server
Program No: 3(a) Server

#include<stdio.h>
#include<stdlib.h>

//fst for tcp 
#include<sys/fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>


int main(int argc,char *argv[])
{
int fd,sockfd,newsockfd, clilen,portno,n;
struct sockaddr_in seradd,cliadd;
char buffer[4096]; // to store the filename sent by client

if(argc<2)
{
fprintf(stderr,"\n\n No port\n");
exit(1);
}

portno=atoi(argv[1]);

sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
error("\n error opening socket.\n");

bzero((char *)&seradd,sizeof(seradd));
seradd.sin_family=AF_INET;
seradd.sin_addr.s_addr=(htonl)INADDR_ANY;//htonl is for
seradd.sin_port=htons(portno);

if(bind(sockfd,(struct sockaddr *)&seradd,sizeof(seradd))<0)
perror("\n IP addr cannt bind");

listen(sockfd,5);
clilen=sizeof(cliadd);
printf("\n Server waiting for client request\n");

while(1)
{
    newsockfd=accept(sockfd,(struct sockaddr *)&cliadd,&clilen);
    if(newsockfd<0)
    perror("\n Server cannot accept connection request ");

    bzero(buffer,4096);//bzero is used to clear the buffer
    read(newsockfd,buffer,4096);
    fd=open(buffer,O_RDONLY);
    if(fd<0)
    perror("\n File  doesnot exist");

    while(1)
    {
    n=read(fd,buffer,4096);
    if(n<=0)
    exit(0);
    write(newsockfd,buffer,n);
    printf("\n File transfer completet\n");
    }

    close(fd);
    close(newsockfd);
}
return 0;
}




Program No: 3(b) Client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<sys/fcntl.h>


#include<netinet/in.h>
#include<arpa/inet.h>

// there are three major steps in client side .
// they are creating socket,connecting to server and sending and receiving data
int main(int argc,char *argv[])
{
int sockfd,portno,n;
struct sockaddr_in seradd;
char buffer[4096],*serip; //serip is used to store the server ip address


if(argc<4)
{
fprintf(stderr,"usage %s serverip filename port",argv[0]);
exit(0);
}

serip=argv[1];
portno=atoi(argv[3]);

sockfd=socket(AF_INET,SOCK_STREAM,0);//creating socket
if(sockfd<0)
perror("\n Error in creating socket.\n");

perror("\n Client on line.");

bzero((char *)&seradd,sizeof(seradd));
seradd.sin_family=AF_INET;
seradd.sin_addr.s_addr=inet_addr(serip);//focus her inet_addr(serip)
seradd.sin_port=htons(portno);

if(connect(sockfd,(struct sockaddr *)&seradd,sizeof(seradd))<0)//connecting
perror("\n Error in connection setup \n");

write(sockfd,argv[2],strlen(argv[2])+1);

bzero(buffer,4096);
n=read(sockfd,buffer,4096);
if(n<=0)
{
perror("\n File not found");
exit(0);
}
write (1,buffer,n);

}












