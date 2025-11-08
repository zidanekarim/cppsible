#include "SSHClient.h"

SSHClient::SSHClient(const string& host): host(host) {
    
    current_session = ssh_new();
    if (current_session == NULL) {
        cerr << "Error creating ssh_session";
        exit(1);
    }
    ssh_options_set(current_session, SSH_OPTIONS_HOST, host.c_str());
    ssh_options_set(current_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(current_session, SSH_OPTIONS_CIPHERS_C_S,"aes128-ctr");
    ssh_options_set(current_session, SSH_OPTIONS_PORT, &port);
}

SSHClient::~SSHClient() {
    disconnect();
    ssh_free(current_session);
}

bool SSHClient::connect(const string& user, const string& password) {
    int rc = ssh_connect(current_session);
    if (rc != SSH_OK){
        fprintf(stderr, "Error connecting to localhost: %s\n",
                ssh_get_error(current_session));
        exit(-1);
    }
    ssh_options_set(current_session, SSH_OPTIONS_USER, user.c_str());
    int auth = ssh_userauth_password(current_session, NULL, password.c_str());
    if (auth != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Error authenticating with password: %s\n",
                ssh_get_error(current_session));
        disconnect();
        return false;
    }
    return true;

}