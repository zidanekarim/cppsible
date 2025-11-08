#ifndef SSHCLIENT_H
#define SSHCLIENT_H
#include <string>
#include <libssh/libssh.h>
#include <cstdlib> 
#include <iostream>

using namespace std;

class SSHClient {
    public:
        SSHClient(const string& host);
        ~SSHClient();
        int port = 31415;
        ssh_session current_session; 
        const string& host;
        int verbosity = SSH_LOG_PROTOCOL;
        bool connect(const string& user, const string& password);
        string executeCommand(const string& command);
        void disconnect();

};


#endif