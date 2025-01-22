
```
# File System Directory Copy

This project implements a recursive directory copy mechanism using C for file system operations. It enables copying directories and their contents, including subdirectories and files, while preserving the original structure of the file system.

## How the Program Works

The program recursively copies the contents of a source directory to a destination directory. It handles:

- Regular files and subdirectories.
- Preserving the directory structure during the copy process.
- Using standard file system operations in C.

## How to Run the Project

### Prerequisites

Before running the project, ensure that you have the following tools installed:

- **C Compiler:**
  - **Linux:** Ensure that `gcc` is installed.
  - **Windows:** If you're using Windows, we recommend using WSL (Windows Subsystem for Linux) for a seamless development experience.

### Steps to Run the Program

#### Option 1: Running on Linux or WSL
If you are using Linux or Windows with WSL (Windows Subsystem for Linux), follow these steps:

1. **Install the necessary dependencies:**
   For Linux or WSL:
   ```bash
   sudo apt update
   sudo apt install gcc make
   ```

2. **Clone the repository:**
   ```bash
   git clone https://github.com/itayalter1/File-System-Directory-Copy.git
   ```

3. **Navigate to the project directory:**
   ```bash
   cd File-System-Directory-Copy
   ```

4. **Compile and run the program:**
   ```bash
   make
   ./directory_copy source_directory destination_directory
   ```

#### Option 2: Running on Windows (without WSL)
If you're using Windows without WSL, follow these steps:

1. **Download and install MinGW** (Minimalist GNU for Windows).
2. **Set up the PATH environment variable** for MinGW to ensure `gcc` is available.
3. Follow the steps in Option 1 to compile and run the program.

## How to Use the Program

To use the program, run the following command:

```bash
./directory_copy source_directory destination_directory
```

This will recursively copy the contents of `source_directory` to `destination_directory`, maintaining the directory structure.

### Example

```bash
./directory_copy /home/user/source /home/user/destination
```

This will copy the contents of `/home/user/source` into `/home/user/destination`.

## Files and Directories

- **copytree.c:** Implements the recursive directory copy function.
- **copytree.h:** Header file for the `copytree.c` implementation.
- **part3.c:** Main program that calls the directory copy function and handles input/output.
- **Makefile:** Build file to compile the project.

## Technologies Used

- **Language:** C
- **File System Operations:** `opendir()`, `readdir()`, `mkdir()`, `rename()`
- **Concurrency:** N/A (single-threaded execution)

## Future Improvements

- Improve error handling and logging during the copy process.
- Add support for symbolic links.
- Implement a more advanced progress reporting mechanism.

## Contact

For questions or suggestions, feel free to reach out:

- **Email:** itayalter1@gmail.com  
- **GitHub:** [itayalter1](https://github.com/itayalter1)
```
