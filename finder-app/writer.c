/*
* Author      : Yahya Osama Mohamed
* Date        : 26 Sept 2023
* Description : Assignment 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        exit(1);
    }
    //argv[0] holds the name of the program itself 
    const char *file_name = argv[1];
    const char *text_to_write = argv[2];

    // Open the file for writing
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Could not create or write to the file %s", file_name);
        exit(1);
    }

    // Write the text to the file
    fputs(text_to_write, file);
    fclose(file);

    // Log the action using syslog
    openlog("writer", LOG_PID, LOG_USER);
    syslog(LOG_DEBUG, "Writing %s to %s", text_to_write, file_name);
    closelog();

    printf("File %s created with content: '%s'\n", file_name, text_to_write);

    return 0;
}
