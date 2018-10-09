/*socketlen_t is a type that is used to declare a variable that can hold the length of a socket address, which itself is variable depending on the address family. 
It isn't that length itself/*
This server allow  multiple connection through a
specified port. This code has been adapted from the tutorial
server_lecture on blackboard.
*/

#include <stdio.h>
#include <stdlib.h>			// for IOs
#include <string.h> 
#include <unistd.h>
#include <sys/types.h> 			// for system calls
#include <sys/socket.h> 		// for sockets
#include <netinet/in.h>			// for internet 
#include <stdbool.h>
#include <pthread.h>                    // for thread;

/* a function to print out error message and then abort */
void error(const char *msg)
{
        perror(msg);
        exit(1);
}

void *threadFunct(int mySockfd)
{
        char buffer2[256];
        bool exitFlag = false;
        int read_writeLen;
        while(!exitFlag)
        {
                bzero(buffer2, 256);
                read_writeLen = read(mySockfd, buffer2, 255);
                if (read_writeLen < 0)
                        printf("ERROR reading from the client socket\n");

                if(strcmp(buffer2,"EXIT\n")==0)
                {
                        printf("Now socket %d will be close\n", mySockfd);
                        close(mySockfd);
                        pthread_exit(mySockfd);         // terminate the calling thread

                }
                else{
                        printf("The message read from socket %d :%s\n ",mySockfd,buffer2);
                        read_writeLen = write(mySockfd,"I got Your Message" , 18);
                        if (read_writeLen < 0)
                                printf("Unable to write to socket\n");
                }
        }
        close(mySockfd);
        return  NULL;

}
int main(int argc, char *argv[])
 // sockefd and  newsockfd  arfe file descriptor, array subscript
        // into the file descriptor table.
        int sockfd, newsockfd, portno;
        //
        socklen_t clilen;                       // store the size of the address of the client..need ded for systme call
        char buffer[256];                       // the server reads charfrom the socket connection into this buffer.
        // server_addr hold the addr of the sever &cli_adrr will contain the addr of the client
        struct sockaddr_in serv_addr, cli_addr; // sockaddr_in is a struct use for internet communication contain ip addr and port field
                                                        // defined in netinet/in.h
        int charRead_Written ;                          // the  number of char written or read by red() and write() calls

        // user need to pass in the port no on which the server will accpet connection as argument. Eroor if use fail to do that
        if(argc <2)
        {
                fprintf(stderr, "ERROR, no port provided\n");
                exit(1);
        }

        //socket() create a new socket. af_inet refer to addresses(use rather PF_INET) from the internet, scok_stream is tcp
        // return a socket descriptor on sucess and -1 on error
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0)
                error("ERROR Opening socket");

^G Get Help       ^O Write Out      ^W Where Is       ^K Cut Text       ^J Justify        ^C Cur Pos        M-U Undo          M-A Mark Text     M-] To Bracket    M-Q Previous      ^B Back           ^◀ Prev Word      ^A Home
^X Exit           ^R Read File      ^\ Replace        ^U Uncut Text     ^T To Spell       ^_ Go To Line     M-E Redo          M-6 Copy Text     ^Q Where Was      M-W Next          ^F Forward        ^▶ Next Word      ^E End

