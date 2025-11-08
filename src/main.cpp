#include <iostream>
#include <fstream>
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include "SSHClient.h"

using namespace std;




int main(int argc, char** argv){

    SSHClient client_test("tester");
    client_test.connect("tester", getenv("TESTER_PASS"));
    //string output = client_test.executeCommand("ls -la");
    
    return 0;
}
