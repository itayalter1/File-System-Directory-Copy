
# File System Directory Copy

This project implements a recursive directory copy mechanism using C for file system operations. The program enables copying of directories, including subdirectories and their contents, maintaining the directory structure.

## Features

- Recursive directory copying.
- Handles all file types within the directory, including regular files and subdirectories.
- Preserves the directory structure during the copy process.
- Works with standard file system operations in C.

## How to Download the Project

To download this project, you can clone the Git repository using the following command:

```bash
git clone https://github.com/itayalter1/File-System-Directory-Copy.git
```

This will create a local copy of the repository on your machine.

## How to Compile

### Prerequisites

Ensure you have a C compiler installed (e.g., GCC).

### Compile the Program

To compile the program, run the following command in your terminal:

```bash
gcc -o directory_copy copytree.c part3.c
```

This will create an executable file named `directory_copy`.

## How to Run

### Usage

To run the program, use the following command:

```bash
./directory_copy source_directory destination_directory
```

This will recursively copy the contents of `source_directory` to `destination_directory`, preserving the directory structure.

### Example

```bash
./directory_copy /home/user/source /home/user/destination
```

This will copy the contents of `/home/user/source` into `/home/user/destination`.

## Files

- `copytree.c`: Implements the recursive directory copy function.
- `copytree.h`: Header file for the `copytree.c` implementation.
- `part3.c`: Main program that calls the directory copy function and handles input/output.

## Contact

For questions or suggestions, feel free to reach out:

- **Email:** itayalter1@gmail.com  
- **GitHub:** [itayalter1](https://github.com/itayalter1)
```

