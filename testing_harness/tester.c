#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "tester.h"
#include <errno.h>

#define FILE_IN_SUFFIX "in"
#define FILE_OUT_SUFFIX "out"
#define MAX_OUTPUT_LINE 1024

int main(int argc, const char* argv[]) {
	// we need three arguments because the first one is our own name
	if (argc != 3) {
		printf("\nUsage: tester [program to test] [directory for test and correct files]%d\n", argc);
	}
	
	const char *program = argv[1];
	const char *testDir = argv[2];
	
	printf("Listing directories...\n");
	
	runOnFiles(testDir, FILE_IN_SUFFIX);
	
	return 0;
};

void testProgram(char *programCommand, const char* inputFile, const char* outputFile) {
	
	const char *inputOperator = " < ";
	int newCommandLength = (strlen(programCommand) + strlen(inputFile) + strlen(inputOperator) + 1);
	char *programCommandRedirected = malloc(sizeof(char) * newCommandLength);
	
	snprintf(programCommandRedirected, newCommandLength, "%s%s%s", programCommand, inputOperator, inputFile);
	
	printf("\nRunning '%s'\n", programCommandRedirected);
	return;
	
	FILE *programOutput 	   = popen(programCommand, "r");
	
	FILE *correctProgramOutput = fopen(outputFile, "r");
	
	if (programOutput == NULL) {
		printf("Couldn't run '%s' under testing\n", programCommand);
		exit(EXIT_FAILURE);
	}
	
	if (correctProgramOutput == NULL) {
		printf("Couldn't open the correct output file '%s'\n", outputFile);
		exit(EXIT_FAILURE);
	}
	
	while (!feof())
	pclose(programOutput);
	
	
};

void runOnFiles(const char *directory, const char *program) {
	DIR *d = opendir(directory);
	
	if (d == NULL) {
		printf("Could not open directory: %s\n", directory);
		exit(EXIT_FAILURE);
	}
	
	struct dirent *entry = readdir(d);
	
	while (entry != NULL) {
		
		// see if the entry matches our suffix
		if (entry->d_type == DT_REG && strstr(entry->d_name, FILE_IN_SUFFIX) != NULL) {
			printf("Testing program on file '%s'\n", entry->d_name);
			testProgram("more", entry->d_name, entry->d_name);
		}

		entry = readdir(d);
	}
	
	closedir(d);
	
	return;
}