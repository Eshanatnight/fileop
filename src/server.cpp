#include "server.hpp"
#include <vector>
#include <fmt/color.h>
#include <fmt/core.h>
#include <ios>

Server::Server(const std::string& path, int port) : m_port(port), m_path(path)
{
	create_socket();
	m_address.sin_family	  = AF_INET;
	m_address.sin_addr.s_addr = INADDR_ANY;
	m_address.sin_port		  = htons(m_port);
	m_addressLength			  = sizeof(m_address);

	bind_socket();
	set_listen_set();
	accept_connection();

	m_file.open(m_path, std::ios::in | std::ios::binary);
	if(m_file.is_open())
	{
		fmt::print("[LOG] : File is ready to Transmit.\n");
	} else {
		fmt::print(fg(fmt::color::red), "[ERROR] : File loading failed, Exititng.\n");
		exit(EXIT_FAILURE);
	}
}

void Server::create_socket()
{
	if((m_generalSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		fmt::print(fg(fmt::color::red), "[ERROR] : Socket failed");
		exit(EXIT_FAILURE);
	}

	fmt::print("[LOG] : Socket Created Successfully.\n");
}

void Server::bind_socket()
{
	if(bind(m_generalSocketDescriptor, (struct sockaddr*)&m_address, sizeof(m_address)) < 0)
	{
		fmt::print(fg(fmt::color::red), "[ERROR] : Bind failed");
		exit(EXIT_FAILURE);
	}
	fmt::print("[LOG] : Bind Successful.\n");
}

void Server::set_listen_set()
{
	if(listen(m_generalSocketDescriptor, 3) < 0)
	{
		fmt::print(fg(fmt::color::red), "[ERROR] : Listen");
		exit(EXIT_FAILURE);
	}

	fmt::print("[LOG] : Socket in Listen State (Max Connection Queue: 3)\n");
}

void Server::accept_connection()
{
	if((m_newSocketDescriptor = accept(m_generalSocketDescriptor,
			(struct sockaddr*)&m_address,
			(socklen_t*)&m_addressLength)) < 0)
	{
		fmt::print(fg(fmt::color::red), "[ERROR] : Accept");
		exit(EXIT_FAILURE);
	}
	fmt::print("[LOG] : Connected to Client.\n");
}

void Server::transmit_file()
{
	std::string contents(
		(std::istreambuf_iterator<char>(m_file)), std::istreambuf_iterator<char>());
	fmt::print("[LOG] : Transmission Data Size {} bytes", contents.length());

	fmt::print("[LOG] : Sending...\n");

	int bytes_sent = send(m_newSocketDescriptor, contents.c_str(), contents.length(), 0);
	fmt::print("[LOG] : Transmitted Data Size {} Bytes", bytes_sent);

	fmt::print("[LOG] : File Transfer Complete.\n");
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

	Server server(filename, port);
	server.transmit_file();
}