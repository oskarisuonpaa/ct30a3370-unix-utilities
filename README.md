# ct30a3370-unix-utilities
Simple recreations of UNIX utilities CAT, GREP, ZIP, and UNZIP.

## Compiling
```
gcc -o my-cat my-cat.c -Wall -Werror
gcc -o my-grep my-grep.c -Wall -Werror
gcc -o my-zip my-zip.c -Wall -Werror
gcc -o my-unzip my-unzip.c -Wall -Werror
```

## Usage

```
./my-cat file1 [file2 ...]
./my-grep searchterm [file ...]
./my-zip file1 [file2 ...] > output_file
./my-unzip file1 [file2 ...] > output_file
```
