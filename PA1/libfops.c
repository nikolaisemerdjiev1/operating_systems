// libfops.c

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include "fops.h"

int create_file(const char *filename, int flags, mode_t mode) {
    int result;
    result = syscall(SYS_open, filename, flags, mode);
    return result;

}

ssize_t write_to_file(int fd, const void *buf, size_t count) { 
    ssize_t result;
    result = syscall(SYS_write, fd, buf, count);      
    return result;
}

ssize_t read_from_file(int fd, void *buf, size_t count) {
    ssize_t result;
    result = syscall(SYS_read, fd, buf, count);
    return result;
}

int close_file(int fd) {

    syscall(SYS_close, fd);

}

int delete_file(const char *filename) {
    
    int result;
    result = syscall(SYS_unlink, filename);
    return result;
}