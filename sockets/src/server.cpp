
#include <string>

#include "server.h"

int main (int argc, char ** argv) {
  if ((argc > 1) && std::string (argv[1]) == "-u") {
      udp_server ();
  } else{
      tcp_server ();
  }
}
