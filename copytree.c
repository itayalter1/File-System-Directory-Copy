#include "copytree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <utime.h>

// Function to copy a file from the source to the destination
// Handles symbolic links and file permissions based on the flags provided
void copy_file(const char *src, const char *dest, int copy_symlinks, int copy_permissions) {
    struct stat src_stat;
    int result;

    // Determine whether to use lstat (for symbolic links) or stat
    if (copy_symlinks) {
        result = lstat(src, &src_stat);
    } else {
        result = stat(src, &src_stat);
    }

    // If stat or lstat fails, print an error and exit the function
    if (result < 0) {
        perror("STAT failed");
        return;
    }

    // Handle symbolic links specifically when requested
    if (copy_symlinks && S_ISLNK(src_stat.st_mode)) {
        char link_target[4096];
        ssize_t len = readlink(src, link_target, sizeof(link_target) - 1);
        if (len < 0) {
            perror("READLINK failed");
            return;
        }
        link_target[len] = '\0';

        // Remove the destination file if it exists, then create a symbolic link
        if (access(dest, F_OK) == 0) {
            if (unlink(dest) < 0) {
                perror("unlink failed");
                return;
            }
        }

        if (symlink(link_target, dest) < 0) {
            perror("SYMLINK failed");
        }
        return;
    }

    // Open the source file for reading
    int src_fd = open(src, O_RDONLY);
    if (src_fd < 0) {
        perror("open src file");
        return;
    }

    // Remove the destination file if it exists before opening it for writing
    if (access(dest, F_OK) == 0) {
        if (unlink(dest) < 0) {
            perror("unlink failed");
            close(src_fd);
            return;
        }
    }

    // Open the destination file for writing, with permissions based on the source file
    int dst_fd = open(dest, O_CREAT | O_TRUNC | O_RDWR, src_stat.st_mode & 0777);
    if (dst_fd < 0) {
        perror("open dst file");
        close(src_fd);
        return;
    }

    // Copy file contents from source to destination in chunks
    char buf[4096];
    ssize_t n;
    while ((n = read(src_fd, buf, sizeof(buf))) > 0) {
        if (write(dst_fd, buf, n) != n) {
            perror("write to dst");
            close(src_fd);
            close(dst_fd);
            return;
        }
    }
    if (n == -1) {
        perror("read from src");
    }

    // Copy permissions from the source file to the destination file, if requested
    if (copy_permissions) {
        if (fchmod(dst_fd, src_stat.st_mode) < 0) {
            perror("file permissions copy failed");
        }
    }

    close(src_fd);
    close(dst_fd);
}

// Function to create a directory if it doesn't already exist
// Ensures the target is a directory and not a file
void create_directory(const char *dest) {
    struct stat st;
    if (stat(dest, &st) < 0) {
        if (mkdir(dest, 0777) < 0) {
            perror("failed to create directory");
            return;
        }
    } else {
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "Error: %s already exists and it is not a directory", dest);
            exit(EXIT_FAILURE);
        }
    }
}

// Recursive function to copy a directory from the source to the destination
// Copies all files, subdirectories, and symbolic links, preserving permissions as needed
void copy_directory(const char *src, const char *dest, int copy_symlinks, int copy_permissions) {
    struct stat src_stat;

    // Get metadata of the source directory
    if (lstat(src, &src_stat) < 0) {
        perror("STAT failed");
        return;
    }

    // Create the destination directory, handling errors appropriately
    if (mkdir(dest, src_stat.st_mode) < 0) {
        if (errno != EEXIST) {
            perror("create main directory");
            return;
        }
    }

    // Optionally copy permissions for the directory
    if (copy_permissions) {
        if (chmod(dest, src_stat.st_mode & 0777) < 0) {
            perror("chmod failed");
            return;
        }
    }

    // Open the source directory to read its contents
    DIR *dir = opendir(src);
    if (dir < 0) {
        perror("open main directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip the special entries "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct full paths for the source and destination
        char src_path[4096];
        char dst_path[4096];
        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dst_path, sizeof(dst_path), "%s/%s", dest, entry->d_name);

        struct stat src_info;
        if (lstat(src_path, &src_info) < 0) {
            perror("STAT failed");
            closedir(dir);
            return;
        }

        // If the entry is a directory, recursively copy it
        if (S_ISDIR(src_info.st_mode)) {
            copy_directory(src_path, dst_path, copy_symlinks, copy_permissions);
        } else {
            // Otherwise, copy it as a file
            copy_file(src_path, dst_path, copy_symlinks, copy_permissions);
        }
    }

    closedir(dir);
}
