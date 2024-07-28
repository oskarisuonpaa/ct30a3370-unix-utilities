#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void print_usage(); // Function to print usage instructions
FILE* open_file(const char* file_name); // Function to open a file
void close_file(FILE* file, const char* file_name); // Function to close a file
void print_file_contents(FILE* file); // Function to print the contents of a file

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(); // Print usage instructions if no file is provided
        exit(1);
    }

    for (size_t i = 1; i < argc; i++) {
        FILE* file = open_file(argv[i]); // Open the file
        print_file_contents(file); // Print the contents of the file
        close_file(file, argv[i]); // Close the file
    }

    return 0;
}

void print_usage() {
    printf("my-cat: file1 [file2 ...]\n"); // Print the usage instructions
}

FILE* open_file(const char* file_name) {
    FILE* file = fopen(file_name, "r"); // Open the file in read mode
    if (file == NULL) {
        printf("my-cat: cannot open file\n"); // Print an error message if the file cannot be opened
        exit(1);
    }
    return file;
}

void close_file(FILE* file, const char* file_name) {
    if (fclose(file) != 0) {
        printf("my-cat: cannot close file\n"); // Print an error message if the file cannot be closed
        exit(1);
    }
}

void print_file_contents(FILE* file) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer); // Print each line of the file
    }
}
