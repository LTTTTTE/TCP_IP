#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorHandling(char* message);

int main(int argc, char* argv[]) {

	WSADATA wsaData;
	SOCKET h_server_socket, h_client_socket;
	SOCKADDR_IN server_address, client_address;

	int sz_client_address;
	char message[] = "Hell World";
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WASAStartup() error!");

	h_server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (h_server_socket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));

	if (bind(h_server_socket, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(h_server_socket, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	sz_client_address = sizeof(client_address);
	h_client_socket = accept(h_server_socket, (SOCKADDR*)&client_address, &sz_client_address);
	if (h_client_socket == INVALID_SOCKET)
		ErrorHandling("accpet() error");

	send(h_client_socket, message, sizeof(message), 0);
	closesocket(h_client_socket);
	closesocket(h_server_socket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}