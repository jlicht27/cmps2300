#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define SERVER_PORT 5432
#define MAX_LINE 256

char* unsigned_to_binary(unsigned long msg, int size) {
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

unsigned long toggle(unsigned long x, unsigned long n) {
  unsigned long result;
  result = 1 << n;
  result = x ^ result;
  return result;
}

int main(int argc, char * argv[])
{
  FILE *fp;
  struct hostent *hp;
  struct sockaddr_in sin;
  char *host;
  char buf[MAX_LINE];
  int s;
  unsigned long message;
  unsigned long divisor;
  char* new_message;
  unsigned long remainder;
  int random;

  if (argc==2) {
    host = argv[1];
  }
  else {
    fprintf(stderr, "usage: simplex-talk host\n");
    exit(1);
  }

  /* translate host name into peer's IP address */
  hp = gethostbyname(host);
  if (hp == NULL) {
    fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
    exit(1);
  }

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
  sin.sin_port = htons(SERVER_PORT);

  /* active open */
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }
  printf("Attempting to connect to %s.\n", hp->h_name);
  if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
  {
    perror("simplex-talk: connect");
    close(s);
    exit(1);
  }
  /* main loop: get and send lines of text */
  printf("Connected to %s.\n", hp->h_name);
  printf("Send a message to the server: ");
  while (fgets(buf, sizeof(buf), stdin)) {

    char* ptr;
    message = strtoul(buf, &ptr, 2);
    divisor = strtoul("1101", &ptr, 2);
    remainder = crc_remainder(message, divisor, length(message), 4);

    srand(time(0));
    random = rand() % 10;

    if (random < 3) {
      printf("Message was altered.\n");
      printf("Original: %s\n", unsigned_to_binary(message, length(message)));
      random = rand() % length(message);
      message = toggle(message, random);
      printf("New:      %s\n", unsigned_to_binary(message, length(message)));
    }

    sprintf(new_message, "%s-%s", unsigned_to_binary(message, length(message)), unsigned_to_binary(remainder, length(remainder)));
    send(s, new_message, strlen(new_message) + 1, 0);
    printf("\nSend a message to the server: ");
  }
}
