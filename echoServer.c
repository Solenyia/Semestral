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
	unlink( argv[1] ) ;
	
	//create socket
 	_runSafe(server_sockfd = socket( AF_LOCAL, SOCK_STREAM, 0 ));
	
	//bind a name to socket
	memset( &server_address, 0, sizeof( server_address ) ) ;
	server_address.sun_family = AF_UNIX ;
	strncpy( server_address.sun_path, argv[1], sizeof( server_address.sun_path ) - 1 ) ;

	    
	//start listening on the named socket
	_runSafe(bind( server_sockfd, (struct sockaddr *)&server_address, sizeof( server_address ) ) == -1)

	while( 1 ) {

		printf("Server waiting.\n") ;
		
		//accept incomming client connection
		listen( server_sockfd, 5 ) ;
		client_len = sizeof( client_address ) ;
		
		//read message from client
		_runSafe(client_sockfd = accept( server_sockfd, (struct sockaddr *)&client_address, &client_len ));

		//convert client's message to upper case and reply to client
		_runSafe(len = read( client_sockfd, Buff, MAX_MSG_SIZE - 1 ));
		Buff[ len ] = '\0' ;
		printf("server received message:%s\n",Buff);
		len = strToUpper( Buff, len ) ;
		printf("server sending reply:%s\n",Buff);
		write( client_sockfd, Buff, len );
		
		//close temporary socket
		close( client_sockfd ) ;
		client_sockfd = -1 ;
	}
	
	//program will never reach this point
	return 0 ;
}
