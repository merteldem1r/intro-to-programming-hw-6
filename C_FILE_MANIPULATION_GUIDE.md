# Comprehensive Guide to File Manipulation Functions in C

**NOTE**: Written by AI

## Table of Contents

1. [Introduction](#introduction)
2. [File Opening and Closing](#file-opening-and-closing)
3. [Writing to Files](#writing-to-files)
4. [Reading from Files](#reading-from-files)
5. [File Positioning](#file-positioning)
6. [File Management](#file-management)
7. [Error Handling](#error-handling)
8. [Advanced Topics](#advanced-topics)
9. [Practical Examples](#practical-examples)
10. [Best Practices](#best-practices)

---

## Introduction

File manipulation is a crucial part of C programming that allows programs to persist data, read configuration files, and interact with the operating system. The C Standard Library provides a comprehensive set of functions through the `stdio.h` header file that enable efficient file I/O operations.

### Key Concepts

- **Stream**: An abstraction representing an input or output channel
- **File Pointer**: A pointer to a FILE structure that maintains state information
- **EOF (End of File)**: A special marker indicating the end of file
- **Buffer**: Temporary storage for data being transferred between program and file

---

## File Opening and Closing

### `fopen()` - Opening Files

**Syntax:**

```c
FILE *fopen(const char *filename, const char *mode);
```

**Description:**
Opens a file and returns a pointer to a FILE structure. If the file cannot be opened, it returns `NULL`.

**Parameters:**

- `filename`: Name or path of the file to open
- `mode`: File access mode (see table below)

**Return Value:**

- Pointer to FILE structure on success
- NULL on failure

**File Access Modes:**

| Mode    | Description          | If File Exists                  | If File Doesn't Exist |
| ------- | -------------------- | ------------------------------- | --------------------- |
| `"r"`   | Read (text)          | Opens file                      | Error (NULL)          |
| `"w"`   | Write (text)         | Truncates file to 0 bytes       | Creates new file      |
| `"a"`   | Append (text)        | Opens file, sets pointer to EOF | Creates new file      |
| `"r+"`  | Read/Write (text)    | Opens file                      | Error (NULL)          |
| `"w+"`  | Read/Write (text)    | Truncates file                  | Creates new file      |
| `"a+"`  | Read/Append (text)   | Opens file                      | Creates new file      |
| `"rb"`  | Read (binary)        | Opens file                      | Error (NULL)          |
| `"wb"`  | Write (binary)       | Truncates file                  | Creates new file      |
| `"ab"`  | Append (binary)      | Opens file                      | Creates new file      |
| `"rb+"` | Read/Write (binary)  | Opens file                      | Error (NULL)          |
| `"wb+"` | Read/Write (binary)  | Truncates file                  | Creates new file      |
| `"ab+"` | Read/Append (binary) | Opens file                      | Creates new file      |

**Example:**

```c
FILE *file = fopen("data.txt", "w");
if (file == NULL) {
    printf("Error: Could not open file\n");
    return 1;
}
```

### `fclose()` - Closing Files

**Syntax:**

```c
int fclose(FILE *stream);
```

**Description:**
Closes an open file and flushes any buffered data to disk. Essential for proper resource management.

**Parameters:**

- `stream`: Pointer to FILE structure to close

**Return Value:**

- 0 on success
- EOF on failure

**Important Notes:**

- Always close files when done to prevent resource leaks
- Closing a file flushes buffered data to disk
- Failing to close files can result in data loss
- Multiple file pointers should each be closed individually

**Example:**

```c
FILE *file = fopen("data.txt", "r");
// ... file operations ...
if (fclose(file) != 0) {
    printf("Error closing file\n");
}
```

---

## Writing to Files

### `fprintf()` - Formatted Writing

**Syntax:**

```c
int fprintf(FILE *stream, const char *format, ...);
```

**Description:**
Writes formatted data to a file, similar to `printf()` but redirected to a file stream.

**Parameters:**

- `stream`: Pointer to FILE structure
- `format`: Format string with conversion specifiers
- `...`: Variable arguments matching format specifiers

**Return Value:**

- Number of characters written on success
- Negative value on failure

**Format Specifiers:**
| Specifier | Type | Example |
|-----------|------|---------|
| `%d` | Integer | `fprintf(file, "%d", 42);` |
| `%f` | Float/Double | `fprintf(file, "%f", 3.14);` |
| `%s` | String | `fprintf(file, "%s", "hello");` |
| `%c` | Character | `fprintf(file, "%c", 'A');` |
| `%x` | Hexadecimal | `fprintf(file, "%x", 255);` |
| `%o` | Octal | `fprintf(file, "%o", 64);` |
| `%%` | Literal % | `fprintf(file, "100%%");` |

**Example:**

```c
FILE *file = fopen("output.txt", "w");
int age = 25;
char name[] = "Alice";
fprintf(file, "Name: %s, Age: %d\n", name, age);
fclose(file);
```

### `fputs()` - String Writing

**Syntax:**

```c
int fputs(const char *string, FILE *stream);
```

**Description:**
Writes a string to a file without interpreting format specifiers.

**Parameters:**

- `string`: Null-terminated string to write
- `stream`: Pointer to FILE structure

**Return Value:**

- Non-negative value on success
- EOF on failure

**Differences from fprintf():**

- Faster than fprintf() (no format parsing)
- Cannot format data (no format specifiers)
- Automatically includes string without adding newline
- Better performance for simple string output

**Example:**

```c
FILE *file = fopen("log.txt", "a");
fputs("Application started successfully\n", file);
fclose(file);
```

### `fputc()` - Character Writing

**Syntax:**

```c
int fputc(int character, FILE *stream);
```

**Description:**
Writes a single character to a file.

**Parameters:**

- `character`: Character to write (as int)
- `stream`: Pointer to FILE structure

**Return Value:**

- Character written on success
- EOF on failure

**Example:**

```c
FILE *file = fopen("chars.txt", "w");
for (int i = 0; i < 5; i++) {
    fputc('A' + i, file);
}
fputc('\n', file);
fclose(file);
// Output: ABCDE
```

### `fwrite()` - Binary Writing

**Syntax:**

```c
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

**Description:**
Writes binary data to a file, useful for writing structured data like arrays and structs.

**Parameters:**

- `ptr`: Pointer to data buffer
- `size`: Size of each data element in bytes
- `nmemb`: Number of elements to write
- `stream`: Pointer to FILE structure

**Return Value:**

- Number of elements successfully written
- May be less than nmemb if error occurs

**Example:**

```c
struct Person {
    char name[50];
    int age;
};

struct Person people[3] = {
    {"Alice", 25},
    {"Bob", 30},
    {"Charlie", 28}
};

FILE *file = fopen("people.bin", "wb");
fwrite(people, sizeof(struct Person), 3, file);
fclose(file);
```

---

## Reading from Files

### `fgetc()` - Character Reading

**Syntax:**

```c
int fgetc(FILE *stream);
```

**Description:**
Reads a single character from a file. Commonly used in loops to process files character by character.

**Parameters:**

- `stream`: Pointer to FILE structure

**Return Value:**

- Character read (as int) on success
- EOF when end of file is reached or error occurs

**Important Notes:**

- Advances file position pointer by 1
- Must check for EOF to distinguish from valid characters
- Slower for large files compared to buffered reads

**Example:**

```c
FILE *file = fopen("input.txt", "r");
int ch;
int count = 0;

while ((ch = fgetc(file)) != EOF) {
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
        count++;
    }
}

printf("Vowel count: %d\n", count);
fclose(file);
```

### `fgets()` - Line Reading

**Syntax:**

```c
char *fgets(char *string, int size, FILE *stream);
```

**Description:**
Reads a line from a file into a string buffer. Most commonly used function for reading text files.

**Parameters:**

- `string`: Pointer to character array for storing input
- `size`: Maximum number of characters to read (including null terminator)
- `stream`: Pointer to FILE structure

**Return Value:**

- Pointer to string on success
- NULL on EOF or error

**Important Notes:**

- Reads up to (size - 1) characters or until newline is encountered
- Includes the newline character in the string if encountered
- Always null-terminates the string
- Safer than gets() which doesn't have size limit

**Example:**

```c
FILE *file = fopen("data.txt", "r");
char line[100];

while (fgets(line, sizeof(line), file) != NULL) {
    printf("%s", line); // newline already in line
}

fclose(file);
```

**Handling the Newline:**

```c
FILE *file = fopen("data.txt", "r");
char line[100];

while (fgets(line, sizeof(line), file) != NULL) {
    // Remove newline if present
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
    printf("Line: %s\n", line);
}

fclose(file);
```

### `fread()` - Binary Reading

**Syntax:**

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
```

**Description:**
Reads binary data from a file. Counterpart to `fwrite()`.

**Parameters:**

- `ptr`: Pointer to buffer for storing data
- `size`: Size of each data element in bytes
- `nmemb`: Number of elements to read
- `stream`: Pointer to FILE structure

**Return Value:**

- Number of elements successfully read
- May be less than nmemb if EOF or error is encountered

**Example:**

```c
struct Person {
    char name[50];
    int age;
};

struct Person people[10];
FILE *file = fopen("people.bin", "rb");

size_t num_read = fread(people, sizeof(struct Person), 10, file);
printf("Read %zu records\n", num_read);

for (size_t i = 0; i < num_read; i++) {
    printf("%s - %d years old\n", people[i].name, people[i].age);
}

fclose(file);
```

### `fscanf()` - Formatted Reading

**Syntax:**

```c
int fscanf(FILE *stream, const char *format, ...);
```

**Description:**
Reads formatted data from a file, similar to `scanf()` but from a file stream.

**Parameters:**

- `stream`: Pointer to FILE structure
- `format`: Format string with conversion specifiers
- `...`: Pointers to variables to store input

**Return Value:**

- Number of input items successfully read
- EOF on end of file

**Format Specifiers:** Same as scanf()
| Specifier | Input Type |
|-----------|-----------|
| `%d` | Integer |
| `%f` | Float |
| `%s` | String |
| `%c` | Character |

**Example:**

```c
FILE *file = fopen("numbers.txt", "r");
int num1, num2;
char name[50];

if (fscanf(file, "%s %d %d", name, &num1, &num2) == 3) {
    printf("Name: %s, Numbers: %d, %d\n", name, num1, num2);
}

fclose(file);
```

---

## File Positioning

### `fseek()` - Seek to Position

**Syntax:**

```c
int fseek(FILE *stream, long offset, int whence);
```

**Description:**
Moves the file position pointer to a specific location in the file.

**Parameters:**

- `stream`: Pointer to FILE structure
- `offset`: Number of bytes to move (can be negative)
- `whence`: Reference point for offset:
  - `SEEK_SET`: Beginning of file (offset = 0)
  - `SEEK_CUR`: Current position
  - `SEEK_END`: End of file

**Return Value:**

- 0 on success
- Non-zero on failure

**Important Notes:**

- Works with binary files reliably
- Behavior with text files can be unpredictable (use only SEEK_SET with offset 0 for portability)
- Can move past end of file in write mode
- Can move before beginning of file, but reading/writing is then undefined

**Example:**

```c
FILE *file = fopen("data.bin", "rb");

// Move to beginning
fseek(file, 0, SEEK_SET);

// Move 10 bytes from current position
fseek(file, 10, SEEK_CUR);

// Move to end - 100 bytes
fseek(file, -100, SEEK_END);

fclose(file);
```

### `ftell()` - Get Current Position

**Syntax:**

```c
long ftell(FILE *stream);
```

**Description:**
Returns the current position of the file pointer.

**Parameters:**

- `stream`: Pointer to FILE structure

**Return Value:**

- Current position (in bytes from beginning)
- -1L on error

**Example:**

```c
FILE *file = fopen("data.txt", "r");
printf("Initial position: %ld\n", ftell(file));

char buffer[100];
fgets(buffer, sizeof(buffer), file);
printf("Position after fgets: %ld\n", ftell(file));

fclose(file);
```

### `rewind()` - Reset to Beginning

**Syntax:**

```c
void rewind(FILE *stream);
```

**Description:**
Moves the file pointer to the beginning of the file and clears the EOF flag.

**Parameters:**

- `stream`: Pointer to FILE structure

**Return Value:**

- None (void)

**Equivalent to:**

```c
fseek(stream, 0, SEEK_SET);
clearerr(stream);  // Clear EOF flag
```

**Example:**

```c
FILE *file = fopen("data.txt", "r");

// Read file once
char buffer[100];
while (fgets(buffer, sizeof(buffer), file) != NULL) {
    printf("First pass: %s", buffer);
}

// Reset to beginning
rewind(file);

// Read file again
while (fgets(buffer, sizeof(buffer), file) != NULL) {
    printf("Second pass: %s", buffer);
}

fclose(file);
```

---

## File Management

### `remove()` - Delete File

**Syntax:**

```c
int remove(const char *filename);
```

**Description:**
Deletes a file from the filesystem.

**Parameters:**

- `filename`: Path to file to delete

**Return Value:**

- 0 on success
- Non-zero on failure

**Important Notes:**

- File must be closed before deletion
- Cannot undo deletion
- Returns error if file doesn't exist

**Example:**

```c
FILE *file = fopen("temp.txt", "w");
fputs("Temporary data\n", file);
fclose(file);

// Use temporary file...

if (remove("temp.txt") == 0) {
    printf("Temporary file deleted\n");
} else {
    printf("Error deleting file\n");
}
```

### `rename()` - Rename File

**Syntax:**

```c
int rename(const char *oldname, const char *newname);
```

**Description:**
Renames or moves a file.

**Parameters:**

- `oldname`: Current filename
- `newname`: New filename

**Return Value:**

- 0 on success
- Non-zero on failure

**Important Notes:**

- File must be closed before renaming
- Can move file to different directory
- If newname exists, behavior is implementation-defined

**Example:**

```c
FILE *file = fopen("output.txt", "w");
fputs("Important data\n", file);
fclose(file);

if (rename("output.txt", "output_backup.txt") == 0) {
    printf("File renamed successfully\n");
} else {
    printf("Error renaming file\n");
}
```

---

## Error Handling

### `ferror()` - Check for Error

**Syntax:**

```c
int ferror(FILE *stream);
```

**Description:**
Checks if an error flag is set for the stream.

**Parameters:**

- `stream`: Pointer to FILE structure

**Return Value:**

- Non-zero if error flag is set
- 0 if no error

**Example:**

```c
FILE *file = fopen("data.txt", "r");
char buffer[100];

while (fgets(buffer, sizeof(buffer), file) != NULL) {
    printf("%s", buffer);
}

if (ferror(file)) {
    printf("Error reading file\n");
} else if (feof(file)) {
    printf("End of file reached\n");
}

fclose(file);
```

### `feof()` - Check for End of File

**Syntax:**

```c
int feof(FILE *stream);
```

**Description:**
Checks if the EOF flag is set for the stream.

**Parameters:**

- `stream`: Pointer to FILE structure

**Return Value:**

- Non-zero if EOF flag is set
- 0 if not at end of file

**Important Notes:**

- EOF flag is set AFTER attempting to read past the end
- Must try to read beyond file to set EOF flag
- Don't use as loop condition; use return value of read functions

**Example:**

```c
FILE *file = fopen("data.txt", "r");
int ch;

while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
}

if (feof(file)) {
    printf("\nReached end of file\n");
}

fclose(file);
```

### `clearerr()` - Clear Error Flags

**Syntax:**

```c
void clearerr(FILE *stream);
```

**Description:**
Clears both EOF and error flags for a stream.

**Parameters:**

- `stream`: Pointer to FILE structure

**Return Value:**

- None (void)

**Example:**

```c
FILE *file = fopen("data.txt", "r");

// Try to read
char buffer[100];
fgets(buffer, sizeof(buffer), file);

// Clear flags
clearerr(file);

// Can now use file again
fseek(file, 0, SEEK_SET);
```

---

## Advanced Topics

### Buffering

**Three Types of Buffering:**

1. **Fully Buffered**: Data held in buffer until buffer is full or file is closed

   - Default for files on disk
   - More efficient for large I/O operations

2. **Line Buffered**: Data written when newline is encountered

   - Default for stdin/stdout
   - Useful for interactive programs

3. **Unbuffered**: Data written immediately
   - Used for stderr
   - Slower but ensures immediate output

**Controlling Buffer:**

```c
#include <stdio.h>

FILE *file = fopen("output.txt", "w");

// Set fully buffered (default for files)
setvbuf(file, NULL, _IOFBF, BUFSIZ);

// Set line buffered
setvbuf(file, NULL, _IOLBF, BUFSIZ);

// Set unbuffered
setvbuf(file, NULL, _IONBF, 0);

fprintf(file, "This is buffered\n");
fclose(file);
```

### `fflush()` - Force Buffer Write

**Syntax:**

```c
int fflush(FILE *stream);
```

**Description:**
Flushes buffered data to disk without closing file.

**Parameters:**

- `stream`: Pointer to FILE structure (or NULL to flush all streams)

**Return Value:**

- 0 on success
- EOF on error

**Example:**

```c
FILE *file = fopen("log.txt", "a");

fprintf(file, "Starting operation...\n");
fflush(file);  // Ensure data written to disk
// ... perform long operation ...
fprintf(file, "Operation complete\n");
fclose(file);
```

### Binary vs Text Mode

**Text Mode (`"r"`, `"w"`, `"a"`):**

- Newline conversion: `\n` ↔ `\r\n` (platform-dependent)
- Slower due to conversion
- Used for human-readable files

**Binary Mode (`"rb"`, `"wb"`, `"ab"`):**

- No conversion
- Faster
- Used for images, executables, structured data

**Example:**

```c
// Text mode - safe for text
FILE *text_file = fopen("notes.txt", "w");
fprintf(text_file, "Line 1\nLine 2\n");
fclose(text_file);

// Binary mode - for exact byte preservation
FILE *bin_file = fopen("data.bin", "wb");
unsigned char data[] = {0xFF, 0xFE, 0xFD};
fwrite(data, 1, 3, bin_file);
fclose(bin_file);
```

---

## Practical Examples

### Example 1: Copy File

```c
#include <stdio.h>

int main() {
    FILE *source = fopen("source.txt", "rb");
    if (source == NULL) {
        printf("Error opening source file\n");
        return 1;
    }

    FILE *dest = fopen("destination.txt", "wb");
    if (dest == NULL) {
        printf("Error opening destination file\n");
        fclose(source);
        return 1;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(source);
    fclose(dest);
    printf("File copied successfully\n");

    return 0;
}
```

### Example 2: Count Lines, Words, and Characters

```c
#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int lines = 0, words = 0, characters = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }

        if (isspace(ch)) {
            if (in_word) {
                words++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }

    if (in_word) words++;  // Count last word
    if (characters > 0) lines++;  // Count last line if no newline

    printf("Lines: %d, Words: %d, Characters: %d\n", lines, words, characters);

    fclose(file);
    return 0;
}
```

### Example 3: Search and Replace

```c
#include <stdio.h>
#include <string.h>

#define MAX_LINE 1000

int main() {
    FILE *input = fopen("original.txt", "r");
    FILE *output = fopen("modified.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    char line[MAX_LINE];
    const char *search = "old_text";
    const char *replace = "new_text";

    while (fgets(line, sizeof(line), input) != NULL) {
        char *pos = strstr(line, search);

        if (pos != NULL) {
            *pos = '\0';
            fprintf(output, "%s%s%s", line, replace, pos + strlen(search));
        } else {
            fputs(line, output);
        }
    }

    fclose(input);
    fclose(output);
    printf("Search and replace completed\n");

    return 0;
}
```

### Example 4: Reading CSV File

```c
#include <stdio.h>
#include <string.h>

#define MAX_LINE 1000
#define MAX_FIELD 100

void parse_csv_line(char *line, char fields[10][MAX_FIELD], int *field_count) {
    *field_count = 0;
    char *ptr = line;
    int field_index = 0;
    int in_quotes = 0;

    while (*ptr && field_index < 10) {
        if (*ptr == '"') {
            in_quotes = !in_quotes;
            ptr++;
        } else if (*ptr == ',' && !in_quotes) {
            fields[field_index][field_index] = '\0';
            field_index++;
            ptr++;
        } else {
            strncat(fields[field_index], ptr, 1);
            ptr++;
        }
    }

    if (field_index < 10) {
        fields[field_index][strlen(fields[field_index])] = '\0';
    }
    *field_count = field_index + 1;
}

int main() {
    FILE *file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char line[MAX_LINE];
    char fields[10][MAX_FIELD];
    int field_count;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline
        line[strcspn(line, "\n")] = '\0';

        parse_csv_line(line, fields, &field_count);

        printf("Fields: ");
        for (int i = 0; i < field_count; i++) {
            printf("[%s] ", fields[i]);
        }
        printf("\n");
    }

    fclose(file);
    return 0;
}
```

### Example 5: Binary File with Structures

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

int main() {
    // Write employees to binary file
    FILE *file = fopen("employees.dat", "wb");

    Employee emp1 = {1, "Alice", 50000.00};
    Employee emp2 = {2, "Bob", 60000.00};
    Employee emp3 = {3, "Charlie", 55000.00};

    fwrite(&emp1, sizeof(Employee), 1, file);
    fwrite(&emp2, sizeof(Employee), 1, file);
    fwrite(&emp3, sizeof(Employee), 1, file);
    fclose(file);

    // Read employees from binary file
    file = fopen("employees.dat", "rb");
    Employee temp;

    while (fread(&temp, sizeof(Employee), 1, file) == 1) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", temp.id, temp.name, temp.salary);
    }

    fclose(file);
    return 0;
}
```

---

## Best Practices

### 1. Always Check Return Values

```c
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    perror("fopen failed");  // Print system error message
    return 1;
}

char buffer[100];
if (fgets(buffer, sizeof(buffer), file) == NULL) {
    if (feof(file)) {
        printf("End of file\n");
    } else if (ferror(file)) {
        perror("fgets failed");
    }
}
```

### 2. Always Close Files

```c
FILE *file = fopen("data.txt", "r");
if (file != NULL) {
    // ... file operations ...
    fclose(file);
}
```

### 3. Use Resource Management Pattern

```c
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    return 1;
}

// ... operations ...

if (ferror(file)) {
    printf("Error during file operations\n");
}

fclose(file);
```

### 4. Buffer Overflow Prevention

```c
char buffer[100];
// DON'T: fgets(buffer, sizeof(buffer), file);
// DO: Use the actual size
if (fgets(buffer, sizeof(buffer), file) != NULL) {
    // Safe - limited to 99 characters + null terminator
}
```

### 5. Use Binary Mode for Non-Text Files

```c
// Images, executables, databases
FILE *file = fopen("image.jpg", "rb");  // Not "r"
```

### 6. Handle Line Endings Correctly

```c
char line[100];
while (fgets(line, sizeof(line), file) != NULL) {
    // Remove trailing newline
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
    // Process line
}
```

### 7. Use perror() for Better Error Messages

```c
#include <stdio.h>

FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    perror("Cannot open file");  // Prints: "Cannot open file: No such file or directory"
    return 1;
}
```

### 8. Validate File Size Before Reading

```c
FILE *file = fopen("data.bin", "rb");

// Get file size
fseek(file, 0, SEEK_END);
long file_size = ftell(file);
rewind(file);

if (file_size > MAX_SAFE_SIZE) {
    printf("File too large\n");
    fclose(file);
    return 1;
}
```

### 9. Use Appropriate Read Functions

```c
// For efficiency:
// - Use fread() for binary data
// - Use fgets() for lines of text
// - Use fscanf() for structured text
// - Use fgetc() only for single characters or specialized parsing
```

### 10. Consider Performance

```c
// Slow: character by character
while ((ch = fgetc(file)) != EOF) {
    process(ch);
}

// Fast: buffered reading
char buffer[8192];
size_t bytes_read;
while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
    process_buffer(buffer, bytes_read);
}
```

---

## Summary Table

| Function     | Purpose              | Input/Output           |
| ------------ | -------------------- | ---------------------- |
| `fopen()`    | Open file            | Input: filename, mode  |
| `fclose()`   | Close file           | Input: file pointer    |
| `fprintf()`  | Write formatted text | Output: formatted data |
| `fputs()`    | Write string         | Output: string         |
| `fputc()`    | Write character      | Output: single char    |
| `fwrite()`   | Write binary data    | Output: binary data    |
| `fgetc()`    | Read character       | Input: single char     |
| `fgets()`    | Read line            | Input: text line       |
| `fread()`    | Read binary data     | Input: binary data     |
| `fscanf()`   | Read formatted data  | Input: formatted data  |
| `fseek()`    | Move file pointer    | Control: position      |
| `ftell()`    | Get file position    | Control: get position  |
| `rewind()`   | Go to file start     | Control: reset         |
| `remove()`   | Delete file          | File operation         |
| `rename()`   | Rename file          | File operation         |
| `ferror()`   | Check error flag     | Status check           |
| `feof()`     | Check EOF flag       | Status check           |
| `clearerr()` | Clear flags          | Status control         |

---

## Conclusion

File manipulation in C is a powerful feature that allows programs to interact with the filesystem. Understanding these functions and their proper usage is essential for writing robust C programs. Key takeaways:

1. **Always check return values** for error handling
2. **Always close files** after use
3. **Use appropriate functions** for your data type (binary vs text)
4. **Validate input** and handle edge cases
5. **Consider performance** when working with large files
6. **Use buffering** effectively for efficient I/O

By following these best practices and understanding the nuances of each function, you can write efficient and reliable file handling code in C.
