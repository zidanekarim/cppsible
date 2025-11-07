#include <iostream>
#include <fstream>
#include <libssh/libssh.h>
#include <stdlib.h>


using namespace std;

int main(int argc, char** argv){
    ssh_session my_ssh_session = ssh_new();
    if (my_ssh_session == NULL) {
        cerr << "Error creating ssh_session";
        exit(1);
    }
    int verbosity = SSH_LOG_PROTOCOL;
    int port = 22;
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "ice03.ee.cooper.edu");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, "zidane.karim");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);

    int rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK){
        fprintf(stderr, "Error connecting to localhost: %s\n",
                ssh_get_error(my_ssh_session));
        exit(-1);
    }
    ssh_disconnect(my_ssh_session);

    ssh_free(my_ssh_session);
    return 0;
}
