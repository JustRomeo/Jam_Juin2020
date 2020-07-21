#ifndef __CONNEXION__
#define __CONNEXION__

#include <iostream>

using namespace std;
class Connection {
    public:
        Connection(void);
        Connection(int ip, int port);
        Connection(string ip, string port);
        ~Connection();

        int co(void);
        void send_package(string str);
        string received_package(void);

    private:
        int _fd;
        bool _co;
        string _ip;
        int _socket;
        string _port;

    protected:
};

#endif