#ifndef TESTER_H
#define TESTER_H

/** Simple method that runs the specified program, matches against the specified files, and aggregates the results*/
void testProgram(char *programCommand, const char* inputFile, const char* outputFile);

/** Runs the program on all the files in a directory*/
void runOnFiles(const char *directory, const char *program);

#endif