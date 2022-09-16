#include "client.hpp"

#include "fmt/color.h"
#include "fmt/core.h"

#include <algorithm>
#include <ios>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Client::Client(const std::string& filename, int Port) : m_port(Port), m_filename(filename)
{
	create_socket();
	m_address.sin_family = AF_INET;
	m_address.sin_port	 = htons(m_port);
	m_addressLength		 = sizeof(m_address);

	if(inet_pton(AF_INET, "127.0.0.1", &m_address.sin_addr) <= 0)
	{
		fmt::print("[ERROR] : Invalid address\n");
	}

	create_connection();
	m_file.open("Data/" + m_filename, std::ios::out | std::ios::trunc | std::ios::binary);

	if(m_file.is_open())
	{
		fmt::print("[LOG] : File Creted.\n");
	} else {
		fmt::print("[ERROR] : File creation failed, Exititng.\n");
		exit(EXIT_FAILURE);
	}
}

void Client::create_socket()
{
	if((m_generalSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fmt::print(fg(fmt::color::red), "[ERROR] : Socket failed.\n");
		exit(EXIT_FAILURE);
	}

	fmt::print("[LOG] : Socket Created Successfully.\n");
}

void Client::create_connection()
{
	if(connect(m_generalSocketDescriptor, (struct sockaddr*)&m_address, sizeof(m_address)) < 0)
	{
		fmt::print(fg(fmt::color::red), "[ERROR] : connection attempt failed.\n");
		exit(EXIT_FAILURE);
	}

	fmt::print("[LOG] : Connection Successfull.\n");
}

void Client::receive_file()
{
	char buffer[1024] = {};
	int valread		  = read(m_generalSocketDescriptor, buffer, 1024);
	fmt::print("[LOG] : Data received {} bytes\n", valread);
	fmt::print("[LOG] : Saving data to file.\n");
	m_file << buffer;
	fmt::print("[LOG] : File Saved.\n");
}

int main(int argc, char** argv)
{
	int port;
	std::string filename;
	std::vector<std::string> args(argv, argv + argc);
	if(std::find(args.begin(), args.end(), "-p") != args.end())
	{
		port = std::stoi(*(std::find(args.begin(), args.end(), "-p") + 1));
	}
	if(std::find(args.begin(), args.end(), "-f") != args.end())
	{
		filename = *(std::find(args.begin(), args.end(), "-f") + 1);
	}

	Client client(filename, port);
	client.receive_file();
}
