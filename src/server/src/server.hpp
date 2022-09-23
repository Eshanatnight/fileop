#pragma once
#include <arpa/inet.h>
#include <fstream>
#include <string>

class Server
{
private:

	std::fstream m_file;
	std::string m_path;
	int m_port;
	int m_generalSocketDescriptor;
	struct sockaddr_in m_address;
	int m_addressLength;
	int m_newSocketDescriptor;

public:

	Server(const std::string& path, int port);
	void create_socket();
	void bind_socket();
	void set_listen_set();
	void accept_connection();
	void transmit_file();
};