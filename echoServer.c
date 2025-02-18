/* ========================================================================== */
/*                                                                            */
/*   echoServer.c                                                             */
/*   (c) 2012 Tomas Palenik                                                   */
/*                                                                            */
/*   Server opens a LOCAL-type socket and listens for a message from client.  */
/* 		The message should be a lo-case string.                               */
/*		After receiving the message, 
		the server replies with a response message - client's message 
		converted to upper case letters.							          */
/* ========================================================================== */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <ctype.h>
#include "settings.h"

char Buff[ MAX_MSG_SIZE ] ;

int server_sockfd = -1 ;
int client_sockfd = -1 ;

void cleanup( void ){
	if( server_sockfd != -1 ){
		close( server_sockfd ) ;
		server_sockfd = -1 ;
	}
	if( client_sockfd != -1 ){
		close( client_sockfd ) ;
		client_sockfd = -1 ;
	}
}

//converts string to upper case
int strToUpper( char *str , int size ){
	int i = 0 ;
	
	while( *str != '\0' &&  i++ < size ){
		*str = toupper( *str ) ;
		str++ ;		
	}
	return i ;
}

int main( int argc, const char *argv[] ){

	int len ;
	int client_len ;
	
  //local sockets
	struct sockaddr_un server_address ;         
	struct sockaddr_un client_address ;         
	
	if( argc < 2 ){
   		printf("server error: no socket name specified.") ;
   		return 1 ;
   }
   atexit( cleanup ) ;
	
	//remove old sockets with same name as specified
	
	//create socket
	
	//bind a name to socket
	    
	//start listening on the named socket

	while( 1 ) {

		printf("Server waiting.\n") ;
		
		//accept incomming client connection
		
		//read message from client
		
		//convert client's message to upper case and reply to client
		
		//close temporary socket
		close( client_sockfd ) ;
		client_sockfd = -1 ;
	}
	
	//program will never reach this point
	return 0 ;
}
