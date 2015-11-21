#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sock_utils.h"

void error(char *message) {
  fprintf(stdout,"Error: %s\n",message);
  exit(1);
}

char *substring (size_t start, size_t end, const char *cad, char *subcad, size_t size) {  
  int count = end - start;  
  if ( count >= --size ) {  
    count = size;  
    }  
  sprintf(subcad, "%.*s", count, cad + start);  
  return subcad;  
}
