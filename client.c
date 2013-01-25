#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "common.h"
#include <time.h>

void error(const char *msg)
{
    perror(msg);
    exit(2);
}

void gen_data(int id, Data *d)
{
    d->id=id;
    for (int i=0;i<689;i++)
    {   
        d->str[i]=random()%25+97;
    }
    d->str[689]='\0';

}

int main(int argc, char **argv)
{
    Data data;
//    printf("%d\n",sizeof(Data));
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    int id;
    char ret[3];
    
    srandom(time(NULL));

    if (argc != 2){ 
       fprintf(stderr,"usage %s <id>\n", argv[0]);
       exit(1);
    }
    
    id=atoi(argv[1]);

    portno = PORT;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    

    for(;;)
    {
       gen_data(id,&data);
      n = write(sockfd,&data,sizeof(data));
      if (n < 0) 
           error("ERROR writing to socket");
    

      n = read(sockfd,ret,3);
      if (n < 0 || strcmp("OK\0",ret)){
           fprintf(stderr,"%s",ret);
           puts("ERROR reading from socket");
      exit(5);
      }
    }

    close(sockfd);
    return 0;
}


