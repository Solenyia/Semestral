/* ========================================================================== */
/*                                                                            */
/*   echoClient.c                                                             */
/*   (c) 2012 Tomas Palenik                                                   */
/*                                                                            */
/*   Client opens a LOCAL-type socket and sends a message to server.          */
/* 		The message should be a lo-case string.
/*		After sending the message, 
		client expects the server to reply with a response message.           */
/* ========================================================================== */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "settings.h"

char Buff[ MAX_MSG_SIZE ] ;		// output message buffer
char Fubb[ MAX_MSG_SIZE ] ;		// input message buffer


int Sock_fd = -1 ;

void cleanup( void ){
	if( Sock_fd != -1 ){
		close( Sock_fd ) ;
		Sock_fd = -1 ;
	}
}

//client code
int main( int argc, const char *argv[] ){
   
   
   int len ;
   struct sockaddr_in address ;    //this is for local sockets
   int result ;

   
   if( argc < 2 ){
   		printf("client error: no socket name specified.") ;
   		return 1 ;
   }
   atexit( cleanup ) ;
   
   //create unnamed socket

   _runSafe( Sock_fd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP ) ) ;
   
   //set server socket name

   memset( &address, 0, sizeof( address ) ) ;
   address.sin_family = AF_INET ;
   address.sin_port = htons(5000) ;
   inet_pton(AF_INET, argv[1], &address.sin_addr);
   
   //connect to server

   _runSafe(result = connect(Sock_fd, (struct sockaddr *)&address, sizeof(address)));
   
   //write to socket

   printf("client enter message:") ;
   fgets( Buff, MAX_MSG_SIZE, stdin);
   Buff[ strlen( Buff ) - 1 ] = '\0' ;

   _runSafe(len = write(Sock_fd, Buff, strlen(Buff)));
   printf("client sending message:%s\n", Buff ) ;

   //read answer from socket
   _runSafe(len = read(Sock_fd, Fubb, MAX_MSG_SIZE -1));

   //show server reply to user
   printf("client received reply from server:%s\n", Fubb ) ;
   
   //close connection
	close( Sock_fd ) ;
	Sock_fd = -1 ;
     
	return 0 ; 
}

