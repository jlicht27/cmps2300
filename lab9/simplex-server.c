#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT  5432
#define MAX_PENDING  5
#define MAX_LINE     256

int main()
{
  struct sockaddr_in sin;
  char buf[MAX_LINE];
  int buf_len, addr_len;
  int s, new_s;
  int len;
  int number;
  int response;


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

      fputs(buf, stdout);

      char z[256];
      const char ch = "?";

      number = rand() % 2;

      if (number == 0) {
        if (strchr(buf, ch) != NULL) {
          strcpy(z, "Tell me more...");
          send(new_s, z, sizeof(z), 0);
          fputs(z, stdout);
        }
        else {
          if (buf[strlen(buf)-1] == '\n') {
            buf[strlen(buf)-1] = '\0';
          }
          response = rand() % 5;
          if (response == 0) {
            strcpy(z, "Tell me more...");
            send(new_s, z, sizeof(z), 0);
            fputs(z, stdout);
          }
          if (response == 1) {
            strcpy(z, "I'm sorry to hear that.");
            send(new_s, z, sizeof(z), 0);
            fputs(z, stdout);
          }
          if (response == 2) {
            strcpy(z, "How does that make you feel?");
            send(new_s, z, sizeof(z), 0);
            fputs(z, stdout);
          }
          if (response == 3) {
            strcpy(z, "Is it really?");
            send(new_s, z, sizeof(z), 0);
            fputs(z, stdout);
          }
          if (response == 4) {
            strcpy(z, "Are you sure?");
            send(new_s, z, sizeof(z), 0);
            fputs(z, stdout);
          }
        }
      }
      else {
        if (strchr(buf, ch) != NULL) {
          strcpy(z, "Tell me more...");
          send(new_s, z, sizeof(z), 0);
          fputs(z, stdout);
        }
        else {
          if (buf[strlen(buf)-1] == '\n') {
            buf[strlen(buf)-1] = '\0';
          }
          response = rand() % 3;
          if (response == 0) {
            strcpy(z, "What makes you think ");
            strcat(strcat(z, buf), "?");
            send(new_s, z, sizeof(z), 0);
            fputs(z, stdout);
          }
          if (response == 1) {
            strcpy(z, "How long since ");
            strcat(strcat(z, buf), " started?");
            send(new_s, z, sizeof(z), 0);
            fputs(z, stdout);
          }
          if (response == 2) {
            strcpy(z, "Did you come to me because ");
            strcat(strcat(z, buf), "?");
            send(new_s, z, sizeof(z), 0);
            fputs(z, stdout);
          }
        }
      }
    }
    close(new_s);
    client_number++;
  }
}
