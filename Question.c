#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define MAX_ALLOWED_LENGTH 3
#define NANO_TO_SECOND 1e9
#define OVERFLOW 3
#define YES 2
#define NO 1
#define INVALID 0

// Helper function to shift line by one char
void shiftLine(char *line, int len) {
	char temp;
	char nextVal = line[0];
	for (int j = 0; j < len; j++) {
		temp = line[(j + 1) % len];
		line[(j + 1) % len] = nextVal;
		nextVal = temp;
	}
}

// This function does multi-line rotating text
void showHeartsFancy() {
	// Happy response :)
	char output[6][200] = {"   ______      ______      ______      ______    _    _  ____   ____  _____        __     __  _   _   _     ______      ______      ______      ______  ",
				  	  "  / /___ \\    / /___ \\    / /___ \\    / /___ \\  | |  | |/ __ \\ / __ \\|  __ \\     /\\\\ \\   / / | | | | | |   / /___ \\    / /___ \\    / /___ \\    / /___ \\ ",
				  	  " / /  __) |  / /  __) |  / /  __) |  / /  __) | | |__| | |  | | |  | | |__) |   /  \\\\ \\_/ /  | | | | | |  / /  __) |  / /  __) |  / /  __) |  / /  __) |",
				  	  "< <  |__ <  < <  |__ <  < <  |__ <  < <  |__ <  |  __  | |  | | |  | |  _  /   / /\\ \\\\   /   | | | | | | < <  |__ <  < <  |__ <  < <  |__ <  < <  |__ < ",
				  	  " \\ \\ ___) |  \\ \\ ___) |  \\ \\ ___) |  \\ \\ ___) | | |  | | |__| | |__| | | \\ \\  / ____ \\| |    |_| |_| |_|  \\ \\ ___) |  \\ \\ ___) |  \\ \\ ___) |  \\ \\ ___) |",
				  	  "  \\_\\____/    \\_\\____/    \\_\\____/    \\_\\____/  |_|  |_|\\____/ \\____/|_|  \\_\\/_/    \\_\\_|    (_) (_) (_)   \\_\\____/    \\_\\____/    \\_\\____/    \\_\\____/ "};
	const int NUM_LINES = 6;
	float tickTime = 2e7;
	float totalTime = 10;
	struct timespec total = {0, tickTime};
	
	// Animate text across screen for totalTime seconds
	for (float i = 0; i < totalTime; i += (tickTime / NANO_TO_SECOND)) {
		// Clear terminal for animation
		#ifdef linux
			system("clear");
		#elif defined(_WIN32)
			system("cls");
		#endif
		// Print current frame
		for (int i = 0; i < NUM_LINES; i++) {
			printf("%s\n", output[i]);
			// Shift line by one for next frame
			shiftLine(output[i], strlen(output[i]));
		}
		fflush(stdout);
		nanosleep(&total, NULL);
	}
}

// This function only does one line of rotating text
void showHeartsSimple() {
	// Happy response :)
	// Tick time in nanoseconds and total time in seconds
	float tickTime = 5e7;
	float totalTime = 10;
	struct timespec total = {0, tickTime};
	char output[] = "<3 <3 <3 <3 HOORAY!!! <3 <3 <3 <3                               ";
	int outputLen = strlen(output);

	// Move content across screen for totalTime seconds
	for (float i = 0; i < totalTime; i += (tickTime / NANO_TO_SECOND)) {
		printf("\r%s", output);
		fflush(stdout);
		nanosleep(&total, NULL);
		shiftLine(output, outputLen);
	}

	#ifdef linux
		// Only add \n for linux, windows auto-adds
		printf("\n");
	#endif
}

// Simple Ascii art output here for rejection
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

// Checking response for overflow and converting to flag integers
int getResponse() {
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

	if (overflow) {
		return 3;
	} else if (!strcmp(resp, "yes")) {
		return 2;
	} else  if (!strcmp(resp, "no")) {
		return 1;
	} else {
		return 0;
	}
}

// Determining level of fanciness to show
int checkForFanciness() {
	while (true) {
		printf("Feeling fancy? (yes/no)\n");
		int response = getResponse();
		// Check for overflow first then varying replies
		switch(response) {
			case OVERFLOW: {
				printf("Again? :|\n");
				fflush(stdout);
				break;
			}
			case YES: {
				showHeartsFancy();
				return 0;
			}
			case NO: {
				showHeartsSimple();
				return 0;
			}
			default: {
				printf("Please enter a valid input ... again :|\n");
				fflush(stdout);
			}
		}
	}
}

// Primary controller asking the initial question
int askQuestion() {
	// Usages of fflush ensures output buffer is written to console before anything else happens
	while(true) {
		printf("Will you be my valentine? (respond with yes/no)\n");
		fflush(stdout);
		// Allow 3 chars for actual responses, 1 for newline, 1 buffer char for overflow detection, and 1 for null
		int response = getResponse();
		
		// Check for overflow first then varying replies
		switch(response) {
			case OVERFLOW: {
				printf("A lot of typing for yes/no ;)\n");
				fflush(stdout);
				break;
			}
			case YES: {
				return checkForFanciness();
			}
			case NO: {
				showSadFace();
				return 0;
			}
			default: {
				printf("Please enter a valid input :|\n");
				fflush(stdout);
			}
		}
	}
}

int main() {
	return askQuestion();
}
