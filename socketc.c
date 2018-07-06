/*
    C socket server example
*/

#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<time.h>
#include<stdlib.h>

int escolha1,escolha2;
int selecaoSERCLI()
{
  printf("Digite 0 para server ou 1 client:\n");
  scanf("%d",&escolha1);
  switch (escolha1)
  {
    case 0:
    printf("server selecionado!\n");
    break;
    case 1:
    printf("client selecionado\n");
    break;
    default:
    escolha1=2;
    printf("Valor invalido.\n");
  }
  return escolha1;
}


int selecaoTCPUDP()
{
  printf("Digite 0 para TCP ou 1 UDP:\n");
  scanf("%d",&escolha2);
  switch (escolha2)
  {
    case 0:
    printf("TCP selecionado!\n");
    break;
    case 1:
    printf("UDP selecionado\n");
    break;
    default:
    escolha2=2;
    printf("Valor invalido.\n");
  }
  return escolha2;
}

int main(int argc , char *argv[])
{
    selecaoSERCLI();
    selecaoTCPUDP();

    if(escolha1==0) //server selecionado
    {
        if(escolha2==0) //TCP selecionado
    {
    printf("server TCP\n");
    server_tcp();
  }
  }
if(escolha1==0) //server selecionado
{
    if(escolha2==1) //UDP selecionado

{
  server_udp();
  printf("server UDP\n");
}
}
if(escolha1==1) //cliente selecionado
{
    if(escolha2==0) //TCP selecionado
{
  printf("Client TCP\n");
  client_tcp();

}
}
if(escolha1==1) //cliente selecionado
{
    if(escolha2==1) //UDP selecionado
{
  printf("Client UDP\n");
  client_udp();



}
}
if((escolha1==2)||(escolha2==2))
{
  printf("Falha! Execute novamente a aplicação.\n");
}

}

int server_tcp(int argc , char *argv[])
{
	int socket_desc_TCP, socket_desc_UDP , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char message[80] = { 0 };
	char response[80] = { 0 };
	int i, flag = 0;
	clock_t inicio, fim;

		//Create socket TCP
		socket_desc_TCP = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_desc_TCP == -1) {
			printf("Could not create TCP socket");
		} // fim if

		puts("Socket TCP created");

		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( 8880 );

		//Bind TCP
		if( bind(socket_desc_TCP,(struct sockaddr *)&server , sizeof(server)) < 0) {
			//print the error message
			perror("bind TCP failed. Error");
			return 1;
		} // fim if

		puts("bind TCP done");

		//Listen
		listen(socket_desc_TCP , 5);

		//Accept and incoming connection
		puts("Waiting for incoming connections...");
		c = sizeof(struct sockaddr_in);

		//accept connection from an incoming client
		client_sock = accept(socket_desc_TCP, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0) {
			perror("accept failed");
			return 1;
		} // fim if

		puts("Connection accepted");

		//Receive a message from client
		while( (read_size = recv(client_sock , &message , 10*sizeof(int), 0)) > 0 ) {
			// print client msg at server side
			puts("The string sent by client is: ");
			puts(message);

			if( (strcmp(message, "ping") == 0 || strcmp(message, "Ping") == 0)) {
			  	response[0] =  'p' ;
			  	response[1] =  'o' ;
			  	response[2] =  'n' ;
			  	response[3] =  'g' ;
			  	flag = 1;
			} // fim if



			if( flag == 0 && (strcmp(message, "ping") != 0 || strcmp(message, "Ping")) != 0) {
			  	  response[0]  =  'B' ;
			  		response[1]  =  'a' ;
			  		response[2]  =  'd' ;
			  		response[3]  =  ' ' ;
			  		response[4]  =  'r' ;
			  		response[5]  =  'e' ;
			  		response[6]  =  'q' ;
			  		response[7]  =  'u' ;
			  		response[8]  =  'e' ;
			  		response[9]  =  's' ;
			  		response[10] =  't' ;
			} // fim if

			puts(response);

			write(client_sock , &response, 10*sizeof(int));

		} // fim while

		if(read_size == 0) {
			puts("\nClient disconnected");
		} // fim if
		else if(read_size == -1) {
		 	perror("recv failed");
		} // fim else if

		return 0;
} // fim função main


int server_udp(int argc , char *argv[])
{
	int socket_desc_TCP, socket_desc_UDP , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char message[80] = { 0 };
	char response[80] = { 0 };
	int i, flag = 0, slen = sizeof(client);

	// create socket UDP
	socket_desc_UDP = socket(AF_INET , SOCK_DGRAM , 0);
	if (socket_desc_UDP == -1) {
	 	printf("Could not create UDP socket");
	} // fim if

	puts("Socket UDP created");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8880 );

	// bind UDP
	if ( bind(socket_desc_UDP,(struct sockaddr *)&server, sizeof(server)) < 0) {
	  	// print the error message
	   	perror("bind UDP failed. Error");
	   	return 1;
	}

	puts("bind UDP done");

	//Listen
	//listen(socket_desc_UDP , 5);

	while( (read_size = recvfrom(socket_desc_UDP , &message , 10*sizeof(int), 0, (struct sockaddr *)&client, &slen)) > 0 ) {
		// print client msg at server side
		puts("The string sent by client is: ");
		puts(message);

		if( (strcmp(message, "ping") == 0 || strcmp(message, "Ping") == 0)) {
		  	response[0] =  'p' ;
		  	response[1] =  'o' ;
		  	response[2] =  'n' ;
		  	response[3] =  'g' ;
		  	flag = 1;
		} // fim if



		if( flag == 0 && (strcmp(message, "ping") != 0 || strcmp(message, "Ping") != 0)) {
		  	  response[0]  =  'B' ;
		  		response[1]  =  'a' ;
		  		response[2]  =  'd' ;
		  		response[3]  =  ' ' ;
		  		response[4]  =  'r' ;
		  		response[5]  =  'e' ;
		  		response[6]  =  'q' ;
		  		response[7]  =  'u' ;
		  		response[8]  =  'e' ;
		  		response[9]  =  's' ;
		  		response[10] =  't' ;
		} // fim if

		puts(response);

    write(client_sock , &response, 10*sizeof(int));

		if( sendto(socket_desc_UDP , &response, 10*sizeof(int) , 0, (struct sockaddr *) &client, sizeof(server) ) < 0) {
			puts("Send failed");
			return 1;
		} // fim if
		/*for( i = 1 ; i <= 80; i++ ){
			response[i] = 0;

			if (i==79) flag=0;
		}*/
	} // fim while

	//for( i = 1 ; i <= 80; i++ ){
	//	response[i] = 0;
	//}

	return 0;
} // fim função main

int client_tcp(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server, client;
	char server_reply[80];
	int number[10],i, protocol, aux = 1, slen = sizeof(client);
	double numOfPackets = 0;
	int sumOfTime = 0;
	float *v;
	char ip[16];
	char temp[10];
	clock_t inicio, fim;

  printf("\nEscolha um endereço de ip: ");
	scanf("%s", ip);

	printf("\nQuantos pacotes devem ser enviados: ");
	scanf("%lf", &numOfPackets);

	v = (int *) malloc(numOfPackets * sizeof(int));

  printf("\nEscreva a mensagem a ser enviada: ");
  scanf("%s", temp);

  //Create socket TCP
  sock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
  if (sock == -1) {
    printf("Could not create socket");
   } // fim if

  puts("Socket created");

  server.sin_addr.s_addr = inet_addr(ip);
  server.sin_family = AF_INET;
  server.sin_port = htons( 8880 );

  //Connect to remote server
  if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
     perror("connect failed. Error");
     return 1;
   } // fim if

  puts("Connected\n");

  for( i = 1 ; i <= numOfPackets; i++ ){
    inicio = clock();

    if( send(sock , &temp, 10*sizeof(int) , 0) < 0) {
      puts("Send failed");
      return 1;
    } // fim if

     //Receive a reply from the server
    if( recv(sock , &server_reply , 10*sizeof(int), 0) < 0) {
      puts("recv failed");
      return;
    } // fim if

    fim = clock();
    v[i] = (fim - inicio);
    sumOfTime = sumOfTime + (fim - inicio);

  } // fim for

  bubble_sort(v, i);

  puts("Server reply :\n");
  puts(server_reply);

  printf("Tempo mínimo: %.2f us.\n",v[1]);
  printf("Tempo médio: %0.2f us.\n",sumOfTime/numOfPackets);
  printf("Tempo máximo: %0.2f us.\n",v[i-1]);
} // fim if de TCP

int client_udp(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server, client;
	char server_reply[80];
	int number[10],i, protocol, aux = 1, slen = sizeof(client);
	double numOfPackets = 0;
	int sumOfTime = 0;
	float *v;
	char ip[16];
	char temp[10];
	clock_t inicio, fim;

  printf("\nEscolha um endereço de ip: ");
	scanf("%s", ip);

  printf("\nQuantos pacotes devem ser enviados: ");
	scanf("%lf", &numOfPackets);

	v = (int *) malloc(numOfPackets * sizeof(int));


  	printf("Escreva a mensagem a ser enviada:\n");
		scanf("%s", temp);

		//Create socket UDP
		sock = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);
		if (sock == -1) {
		 	printf("Could not create socket");
		 } // fim if

		puts("Socket UDP created");

		server.sin_addr.s_addr = inet_addr(ip);
		server.sin_family = AF_INET;
		server.sin_port = htons( 8880 );

		for( i = 1 ; i <= numOfPackets; i++ ){
			inicio = clock();

			if( sendto(sock , &temp, 10*sizeof(int) , 0, (struct sockaddr *) &server, sizeof(client) ) < 0) {
				puts("Send failed");
				return 1;
			}

			 //Receive a reply from the server
			if( recvfrom(sock , &server_reply , 10*sizeof(int), 0, (struct sockaddr *)&server, &slen) < 0) {
				puts("recv failed");
				return;
			}

			fim = clock();
			v[i] = (fim - inicio);
			sumOfTime = sumOfTime + (fim - inicio);
		} // fim for

		bubble_sort(v, i);

		puts("Server reply :\n");
		puts(server_reply);

		printf("Tempo mínimo: %.2f us.\n",v[1]);
		printf("Tempo médio: %0.2f us.\n",sumOfTime/numOfPackets);
		printf("Tempo máximo: %0.2f us.\n",v[i-1]);


  } // fim else if de UDP





void bubble_sort(int list[], int n)
{
 int c, d, t;

for (c = 0 ; c < ( n - 1 ); c++) {
  for (d = 0 ; d < n - c - 1; d++) {
    if (list[d] > list[d+1]) {
    /* Swapping */
    t = list[d];
    list[d] = list[d+1];
    list[d+1] = t;
    } // fim if
  } // fim for interno
} // fim for externo
} // fim função bubble_sort
