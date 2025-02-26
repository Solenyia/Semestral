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
   struct sockaddr_un address ;    //this is for local sockets
   int result ;

   
   if( argc < 2 ){
   		printf("client error: no socket name specified.") ;
   		return 1 ;
   }
   atexit( cleanup ) ;
   
   //create unnamed socket

   _runSafe( Sock_fd = socket( AF_UNIX, SOCK_STREAM, 0 ) ) ;
   
   //set server socket name

   memset( &address, 0, sizeof( address ) ) ;
   address.sun_family = AF_UNIX ;
   strncpy( address.sun_path, argv[1], sizeof( address.sun_path ) - 1 ) ;
   
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

