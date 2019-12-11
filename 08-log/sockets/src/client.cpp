
#include <string>

#include "client.h"

int main (int argc, char ** argv) {
  if ((argc > 1) && std::string (argv[1]) == "-u") {
      udp_client ();
  } else{
      tcp_client ();
  }
}
