#include <iostream>
#include <fstream>
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int show_remote_processes(ssh_session session)
{
  ssh_channel channel;
  int rc;
  char buffer[256];
  int nbytes;
 
  channel = ssh_channel_new(session);
  if (channel == NULL)
    return SSH_ERROR;
 
  rc = ssh_channel_open_session(channel);
  if (rc != SSH_OK)
  {
    ssh_channel_free(channel);
    return rc;
  }
 
  rc = ssh_channel_request_exec(channel, "ps aux");
  if (rc != SSH_OK)
  {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    return rc;
  }
 
  nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
  while (nbytes > 0)
  {
    if (write(1, buffer, nbytes) != (unsigned int) nbytes)
    {
      ssh_channel_close(channel);
      ssh_channel_free(channel);
      return SSH_ERROR;
    }
    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
  }
 
  if (nbytes < 0)
  {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    return SSH_ERROR;
  }
 
  ssh_channel_send_eof(channel);
  ssh_channel_close(channel);
  ssh_channel_free(channel);
 
  return SSH_OK;
}






int main(int argc, char** argv){
    ssh_session my_ssh_session = ssh_new();
    if (my_ssh_session == NULL) {
        cerr << "Error creating ssh_session";
        exit(1);
    }
    int verbosity = SSH_LOG_PROTOCOL;
    int port = 31415;
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
    char* password = getpass("Enter your password:\n");
    int auth = ssh_userauth_password(my_ssh_session, NULL, password);
    int remote = show_remote_processes(my_ssh_session);

    ssh_disconnect(my_ssh_session);

    ssh_free(my_ssh_session);
    return 0;
}
