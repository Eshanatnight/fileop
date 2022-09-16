#pragma once
#include <arpa/inet.h>
#include <fstream>
#include <string>

class Client
{
private:

	std::fstream m_file;
	std::string m_filename;
	int m_port;
	int m_generalSocketDescriptor;
	struct sockaddr_in m_address;
	int m_addressLength;

public:

	Client(const std::string& filename, int Port);
	void create_socket();
	void create_connection();
	void receive_file();
};