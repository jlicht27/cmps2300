#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define SERVER_PORT  5432
#define MAX_PENDING  5
#define MAX_LINE     256

const char* unsigned_to_binary(unsigned long msg, int size) {
	char* b = (char *)malloc(size + 1);
	b[0] = '\0';

	int z;
	for (z = (1<<(size-1)); z > 0; z >>= 1) {
		strcat(b, ((msg & z) == z) ? "1" : "0");
	}

	return b;
}

unsigned long crc_remainder(unsigned long msg, unsigned long check, int mlen, int clen) {
	unsigned long newmsg = msg << (clen-1);
	unsigned long n;
	int i;
	for (i = mlen; i > 0; i--) {
		if ((newmsg & (1 << (i+clen-2))) != 0) {
			n = check << (i - 1);
			newmsg = newmsg ^ n;
		}
	}
	return newmsg & ((1 << clen) - 1);
}

int length(unsigned long num) {
  int count = (num == 0) ? 1  : (log2(num) + 1);
  return count;
}

int main()
{
  struct sockaddr_in sin;
  char buf[MAX_LINE];
  int buf_len, addr_len;
  int s, new_s;
  char* msg;
  char* rem;
  unsigned long message, divisor, remainder;
  unsigned long result;

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(SERVER_PORT);

  /* setup passive open */
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }
  if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
    perror("simplex-talk: bind");
    exit(1);
  }
  listen(s, MAX_PENDING);

  /* wait for connection, then receive and print text */
  printf("Waiting for client connections...\n");
  int client_number = 1;
  while(1) {
    if ((new_s = accept(s, (struct sockaddr *)&sin, &addr_len)) < 0) {
      perror("simplex-talk: accept");
      exit(1);
    }
    printf("Client %d connected.\n", client_number);
    while (buf_len = recv(new_s, buf, sizeof(buf), 0)) {

      msg = strtok(buf, "-");
      rem = strtok(NULL, "-");

      char* ptr;
      message = strtoul(msg, &ptr, 2);
      divisor = strtoul("1101", &ptr, 2);
      remainder = strtoul(rem, &ptr, 2);

      result = crc_remainder(message, divisor, length(message), 4);

      if (result == remainder) {
        printf("Message was transmitted without any errors.\n");
        printf("Original message was: ");
        printf("%s\n", unsigned_to_binary(message, length(message)));
      }
      else {
        printf("There was an error transmitting the message.\n");
      }
      printf("\n");

    }
    close(new_s);
    client_number++;
  }
}
