#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(); // Function prototype for printing usage information
FILE* open_file(const char* file_name); // Function prototype for opening a file
void close_file(FILE* file, const char* file_name); // Function prototype for closing a file
void search_in_file(FILE* file, const char* search_term); // Function prototype for searching in a file
void search_in_stdin(const char* search_term); // Function prototype for searching in stdin

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(); // Print usage information if no arguments are provided
        exit(1);
    }

    if (argc == 2) {
        search_in_stdin(argv[1]); // Search in stdin if only one argument is provided
        exit(0);
    }

    for (size_t i = 2; i < argc; i++) {
        FILE* file = open_file(argv[i]); // Open the file
        if (file == NULL) {
            printf("my-grep: cannot open file\n"); // Print an error message if the file cannot be opened
            exit(1);
        }
        search_in_file(file, argv[1]); // Search in the file
        close_file(file, argv[i]); // Close the file
    }

    return 0;
}

void print_usage() {
    printf("my-grep: searchterm [file ...]\n"); // Print the usage information
}

FILE* open_file(const char* file_name) {
    FILE* file = fopen(file_name, "r"); // Open the file in read mode
    if (file == NULL) {
        return NULL; // Return NULL if the file cannot be opened
    }
    return file; // Return the file pointer
}

void close_file(FILE* file, const char* file_name) {
    if (fclose(file) != 0) {
        printf("my-grep: cannot close file\n"); // Print an error message if the file cannot be closed
        exit(1);
    }
}

void search_in_file(FILE* file, const char* search_term) {
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (strstr(line, search_term) != NULL) {
            printf("%s", line); // Print the line if the search term is found
        }
    }

    free(line); // Free the memory allocated for the line
}

void search_in_stdin(const char* search_term) {
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        if (strstr(line, search_term) != NULL) {
            printf("%s", line); // Print the line if the search term is found
        }
    }

    free(line); // Free the memory allocated for the line
}
