#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//this function is used to convert the original message into binary
const char* unsigned_to_binary(unsigned long msg, int size) {

	//creating and allocating memory for b, the result
	char* b = (char *)malloc(size + 1);
	b[0] = '\0';

	//variable used to loop
	int z;

	//for the length of the message, compare message to a 1 and a bunch of 0s. (10000000)
	//the number of zeros is determined by length of message
	for (z = (1<<(size-1)); z > 0; z >>= 1) {

		//if the (message & z) is the same as just z append a 1
		//else append a 0
		strcat(b, ((msg & z) == z) ? "1" : "0");
	}

	//return the result
	return b;
}

//this function calculates the remainder of msg divided by check
unsigned long crc_remainder(unsigned long msg, unsigned long check, int mlen, int clen) {

	//shifting the message the length of the check
	unsigned long newmsg = msg << (clen-1);

	//used in loop
	unsigned long n;

	//also used for loop
	int i;

	//for the length of the message (starting from length and going to 0)
	for (i = mlen; i > 0; i--) {

		//if the current bit is a 1
		if ((newmsg & (1 << (i + clen - 2))) != 0) {

			//n is the divisor shifted left by the bit the loop is on
			n = check << (i - 1);

			//xor message with n
			newmsg = newmsg ^ n;
		}
	}
	//return new message
	return newmsg & ((1 << clen) - 1);
}

int main() {

	//original message
	unsigned long msg = 0xC74A;

	//divisor
	unsigned long divisor = 0xB;

	//message with remainder added on to the end so that it is divisible by the
	//divisor
	unsigned long newmsg = (msg << 3) + crc_remainder(msg, divisor, 16, 4);

	//variables to store the result from crc_remainder
	unsigned long rem, newrem;

	//print statements with output
	printf("Message is: ");
	printf("%s\n", unsigned_to_binary(msg, 16));
	printf("Divisor is: ");
	printf("%s\n", unsigned_to_binary(divisor, 4));

	rem = crc_remainder(msg, divisor, 16, 4);

	printf("Remainder of message and divisor: ");
	printf("%s\n", unsigned_to_binary(rem, 3));
	printf("Message with added bits is: ");
	printf("%s\n", unsigned_to_binary(newmsg, 19));

	newrem = crc_remainder(newmsg, divisor, 19, 4);

	printf("Remainder is: ");
	printf("%s\n", unsigned_to_binary(newrem, 3));


	printf("\nEXAMPLE FROM BOOK:\n\n");
	char * ptr;
	msg = strtoul("10011010", &ptr, 2);
	divisor = strtoul("1101", &ptr, 2);

	printf("Message is: ");
	printf("%s\n", unsigned_to_binary(msg, 8));
	printf("Divisor is: ");
	printf("%s\n", unsigned_to_binary(divisor, 4));

	rem = crc_remainder(msg, divisor, 8, 4);

	printf("Remainder of message and divisor: ");
	printf("%s\n", unsigned_to_binary(rem, 3));

	newmsg = (msg << 3) + rem;

	printf("Message with added bits is: ");
	printf("%s\n", unsigned_to_binary(newmsg, 11));

	newrem = crc_remainder(newmsg, divisor, 11, 4);

	printf("Remainder is: ");
	printf("%s\n", unsigned_to_binary(newrem, 3));
	return 0;
}
