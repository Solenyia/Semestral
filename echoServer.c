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
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
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
	
	struct sockaddr_in server_address ;         
	struct sockaddr_in client_address ;       
	
	
	if( argc < 2 ){
   		printf("server error: no socket name specified.") ;
   		return 1 ;
   	}
   	atexit(cleanup);
	
	//remove old sockets with same name as specified
	unlink( argv[1] ) ;
	
	//create socket
 	_runSafe(server_sockfd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP ));
	 memset( &server_address, 0, sizeof( server_address ) ) ;
	 server_address.sin_family = AF_INET ;
	 server_address.sin_port =  htons(5000) ;
	
	inet_pton(AF_INET, argv[1], &server_address.sin_addr);

	//bind a name to socket
	_runSafe(bind( server_sockfd, (struct sockaddr *)&server_address, sizeof( server_address ) ))

	//start listening on the named socket
	listen( server_sockfd, 5 ) ;

	while( 1 ) {

		printf("Server waiting.\n") ;
		
		//accept incomming client connection
		client_len = sizeof( client_address ) ;
		_runSafe(client_sockfd = accept( server_sockfd, (struct sockaddr *)&client_address, &client_len ));
		
		//read message from client
		_runSafe(len = read( client_sockfd, Buff, MAX_MSG_SIZE - 1 ));
		Buff[ len ] = '\0';

		//convert client's message to upper case and reply to client
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
