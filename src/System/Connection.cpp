#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <sys/socket.h>

#include "Exception.hpp"
#include "Connection.hpp"

Connection::Connection(string ip, string port) {
    _ip = ip;
    _co = false;
    _port = port;
    struct sockaddr_in sock_addr;

    cout << "ip: " << _ip << " | port: " << _port << endl;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(atoi(_port.c_str()));
    if (inet_pton(AF_INET, _ip.c_str(), &sock_addr.sin_addr) == -1)
        throw Exception("ERROR: inet_pton");
    if (connect(_socket, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1)
        throw Exception("ERROR: Connection");
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
        throw Exception("Socket Initialising Failed");
    _fd = _socket;
}

Connection::Connection(int ip, int port) {
    _co = false;
    _ip = to_string(ip);
    _port = to_string(port);
    struct sockaddr_in sock_addr;

    cout << "ip: " << _ip << " | port: " << _port << endl;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(atoi(_port.c_str()));
    if (inet_pton(AF_INET, _ip.c_str(), &sock_addr.sin_addr) == -1)
        throw Exception("ERROR: inet_pton");
    if (connect(_socket, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1)
        throw Exception("ERROR: Connection");
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
        throw Exception("Socket Initialising Failed");
    _fd = _socket;
}

Connection::Connection(void) {
    _ip = "";
    _port = "";
    _co = false;

    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
        throw Exception("Socket Initialising Failed");
}

Connection::~Connection() {
    _ip.clear();
    _port.clear();
}

void Connection::send_package(string str) {
    cout << "send: " << str << endl;
    if (str.length() > 0 && str != "\n" && write(_fd, str.c_str(), str.length()) == -1)
        throw Exception("ERROR: Write from Client to the Server:\n\t" + str + "\n: FAILED on Socket: " + to_string(_fd));
}

string Connection::received_package(void) {
    int size = 0;
    int fd = _fd;
    char buffer[1024];
    int flags = fcntl(fd, F_GETFL, 0);

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK));
    size = read(fd, buffer, 1024);
    if (size < 0 && errno == EAGAIN)
        return "R: reading";
    else if (size > 0) {
        buffer[size - 1] = '\0';
        string str = string(buffer);
        while(str.find("\"") != string::npos)
            str.replace(str.find("\""), 1, "");
        cout << "STR: " << str << endl;
        return str;
    } else
        throw Exception("Error: 500");
    buffer[0] = '\0';
    return "R: reading";
}

int Connection::co(void) {
    struct sockaddr_in sock_addr;

    cout << "ip: " << _ip << " | port: " << _port << endl;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(atoi(_port.c_str()));
    if (inet_pton(AF_INET, _ip.c_str(), &sock_addr.sin_addr) == -1)
        throw Exception("ERROR: inet_pton");
    if (connect(_socket, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1)
        throw Exception("ERROR: Connection");
    _fd = _socket;
    return 0;
}

