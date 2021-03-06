#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorHandling(char* message);

int main(int argc, char* argv[]) {

	WSADATA wsaData;
	SOCKET h_socket;
	SOCKADDR_IN server_address;

	char message[30];
	int str_len;
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WsaStartup() error!");

	h_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (h_socket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	server_address.sin_port = htons(atoi(argv[2]));

	if (connect(h_socket, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");

	str_len = recv(h_socket, message, sizeof(message) - 1, 0);
	if (str_len == -1)
		ErrorHandling("read{} error!");
	printf("Message from server: %s \n", message);

	closesocket(h_socket);
	WSACleanup();
	return 0;

	return 0;
}

void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}