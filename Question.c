#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#if defined(linux)
#include<unistd.h>
#include<curses.h>
#endif

#define MAX_ALLOWED_LENGTH 3
#define NANO_TO_SECOND 1e9

void showHearts() {
	// Happy response :)
	// Tick time in nanoseconds and total time in seconds
	float tickTime = 5e7;
	float totalTime = 10;
	struct timespec total = {0, tickTime};
	char output[65] = "<3 <3 <3 <3 HOORAY!!! <3 <3 <3 <3                               ";
	fflush(stdout);

	// Move content across screen for totalTime seconds
	for(float i = 0; i < totalTime; i += (tickTime / NANO_TO_SECOND)) {
		i += tickTime / NANO_TO_SECOND;
		printf("\r%s", output);
		fflush(stdout);
		nanosleep(&total, NULL);
		char temp;
		char nextVal;
		for (int j = 0; j < 65; j++) {
			temp = output[(j + 1) % 64];
			output[(j + 1) % 64] = (j == 0) ? output[j] : nextVal;
			nextVal = temp;
		}
	}

	#ifdef linux
		// Only add \n for linux, windows auto-adds
		printf("\n");
	#endif
	fflush(stdout);
}

void showSadFace() {
	// Sad response :(
	printf("       | |                _        / /\n"
		   "   ___ | | ____ _ _   _  (_)______| |\n"
		   "  / _ \\| |/ / _` | | | |   |______| |\n"
		   " | (_) |   < (_| | |_| |  _       | |\n"
		   "  \\___/|_|\\_\\__,_|\\__, | (_)      | |\n"
		   " 		   __/ |           \\_\\\n"
		   "		  |___/");
	#ifdef linux
		// Only add \n for linux, windows auto-adds
		printf("\n");
	#endif
	fflush(stdout);
}

int main() {
	// Usages of fflush ensures output buffer is written to console before anything else happens
	while(true) {
		printf("Will you be my valentine? (respond with yes/no)\n");
		fflush(stdout);
		// Allow 3 chars for actual responses, 1 for newline, 1 buffer char for overflow detection, and 1 for null
		char resp[6];
		fscanf(stdin, "%5s", resp);
		int sizeOfInput = strlen(resp);
		bool overflow = false;
		if (sizeOfInput > MAX_ALLOWED_LENGTH) {
			// Set overflow flag and keep reading input until all read
			overflow = true;
			char v;
			while ((v = getchar()) != '\n' && v != EOF);
		}

		// Convert string to lowercase
		for (int i = 0; i < strlen(resp); i++) {
			resp[i] = tolower(resp[i]);
		}
		
		// Check for overflow first then varying replies
		if (overflow) {
			printf("A lot of typing for yes/no ;)\n");
			fflush(stdout);
		} else if (!strcmp(resp, "yes")) {
			showHearts();
			return 0;
		} else if (!strcmp(resp, "no")) {
			showSadFace();
			return 0;
		} else {
			printf("Please enter a valid input :|\n");
			fflush(stdout);
		}
	}
}
