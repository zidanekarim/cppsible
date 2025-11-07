#include <iostream>
#include <fstream>
#include <libssh/libssh.h>
using namespace std;

int main(int argc, char** argv){
    ssh session my_ssh_session = ssh_new();
    if (my_ssh_session == NULL) {
        cerr << "Error creating ssh_session";
        exit(1);
    }
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, "zidane.karim");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);


    return 0;
}
