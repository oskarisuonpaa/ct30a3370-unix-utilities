#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void print_usage(); // Function to print program usage
FILE* open_file(const char* file_name); // Function to open a file
void close_file(FILE* file, const char* file_name); // Function to close a file
void process_file(FILE* file); // Function to process a file

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(); // Print program usage if no file is provided
        exit(1);
    }

    for (size_t i = 1; i < argc; i++) {
        FILE* file = open_file(argv[i]); // Open the file
        process_file(file); // Process the file
        close_file(file, argv[i]); // Close the file
    }

    return 0;
}

void print_usage() {
    printf("my-zip: file1 [file2 ...]\n"); // Print program usage
}

FILE* open_file(const char* file_name) {
    FILE* file = fopen(file_name, "r"); // Open the file in read mode
    if (file == NULL) {
        printf("my-zip: cannot open file\n"); // Print error message if file cannot be opened
        exit(1);
    }
    return file;
}

void close_file(FILE* file, const char* file_name) {
    if (fclose(file) != 0) {
        printf("my-zip: cannot close file\n"); // Print error message if file cannot be closed
        exit(1);
    }
}

void process_file(FILE* file) {
    char buffer[1];
    char previous_buffer = '\0';
    int count = 0;

    while (fread(buffer, 1, 1, file) == 1) {
        if (buffer[0] == previous_buffer) {
            count++; // Increment count if current character is the same as previous character
        } else {
            if (previous_buffer != '\0') {
                fwrite(&count, 4, 1, stdout); // Write the count to stdout
                fwrite(&previous_buffer, 1, 1, stdout); // Write the previous character to stdout
            }
            previous_buffer = buffer[0]; // Update previous character
            count = 1; // Reset count
        }
    }

    // Write the last set of characters
    if (count > 0 && previous_buffer != '\0') {
        fwrite(&count, 4, 1, stdout); // Write the count to stdout
        fwrite(&previous_buffer, 1, 1, stdout); // Write the previous character to stdout
    }
}
