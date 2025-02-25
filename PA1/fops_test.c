// fops_test.c

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "fops.h"

int main(int argc, char* argv[]) 
{   
    if (argc < 3) { /*Make sure arguments are at least 3*/
        printf("Usage: %s <command> <filename> [message]\n", argv[0]);
        return -1;
    }
    
    const char *filename = argv[2];
    int flags;
    mode_t mode;
    char *message;
    size_t length;

    // Create a file
    if (strncmp(argv[1], "create", 6) == 0 ) 
    {
        if (argc != 3) { /*Making sure 3 arguments are used for create*/
            printf("Usage: %s create <filename>\n", argv[0]);
            return -1;
        }

        int flags = O_WRONLY|O_CREAT|O_TRUNC; 
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        int fd = create_file(filename, flags, mode); 
        if (fd < 0) {
            perror("create_file");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }

        printf("File %s created successfully. \n", filename);

        if (close_file(fd) < 0) {
            perror("close");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }  
        close_file(fd);
        
    }
        

    // Write a file
    else if (strncmp(argv[1], "write", 5) == 0 )
    {   
        if (argc != 4) { /*Making sure 4 arguments are used for write*/
            printf("Usage: %s write <filename> <message>\n", argv[0]);
        }
        int flags = O_WRONLY; 
        mode_t mode = 0;
        char *message = argv[3];
        size_t length = strlen(message);
        int fd = create_file(filename, flags, mode); // Open not create new file
        if (fd < 0) {
            perror("create_file (write)");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }
        
        ssize_t bytes_written = write_to_file(fd, message, length);
        if (bytes_written < 0) {
            perror("write_to_file");
            printf("Error: %s\n", strerror(errno));
            close_file(fd);
            return -1;
        }
        
        printf("Wrote %zd bytes to %s successfully.\n", bytes_written, filename);
        
        if (close_file(fd) < 0) {
            perror("close_file (write)");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }
        close_file(fd);
        
    }

    // Read a file
    else if (strncmp(argv[1], "read", 4) == 0)
    {
        if (argc != 3) { /*Making sure 3 arguments are used for read*/
            printf("Usage: %s read <filename>\n", argv[0]);
            return -1;
        }
        int flags = O_RDONLY; // Read only flag
        mode_t mode = 0; // Mode parameter only used when creating a file
        int fd = create_file(filename, flags, mode); // Open not create new file
        if (fd < 0) {
            perror("create_file (read)");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }
        char buf[20]; 
        size_t nbytes = sizeof(buf); 
        ssize_t bytes_read = read_from_file(fd, buf, nbytes);
        if (bytes_read < 0) {
            perror("read_from_file");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }
        buf[bytes_read] = '\0';
        printf("File reads: %s\n", buf);
        if (close_file(fd) < 0) {
            perror("close_file (read)");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }
        close_file(fd);
    }

    // Close a file 
    else if (strncmp(argv[1], "close", 5) == 0)
    {
        if (argc != 3) { /*Making sure 3 arguments are used for close*/
            printf("Usage: %s close <filename>\n", argv[0]);
            return -1;
        }
        int flags = O_RDONLY;
        mode_t mode = 0;
        int fd = create_file(filename, flags, mode); 
        if (fd < 0) {
            perror("create_file (close)");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }
        if (close_file(fd < 0)) {
            perror("close_file (close)");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }
        close_file(fd);
        printf("%s succesfully closed\n", filename);
    }

    // Delete a file
    else if (strncmp(argv[1], "delete", 6) == 0)
    {
        if (argc != 3) { /*Making sure 3 arguments are used for delete*/
            printf("Usage: %s delete <filename>\n", argv[0]);
            return -1;
        }
        if (delete_file(filename) < 0) {
            perror("delete_file");
            printf("Error: %s\n", strerror(errno));
            return -1;
        }
        delete_file(filename);
        printf("File %s deleted successfully.\n", filename);
    }

    else {
        printf("Unknown command: %s\n", argv[1]);
        return -1;
    }
    exit(0);
}