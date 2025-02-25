AUTHOR INFO

Full name: Nikolai Semerdjiev

Project: System Call Interface


ERRORS 
    - Everything works but I think I could have been more efficient with creating variables, there are a few repeats in creating variables, however, without them my code would not work
    - Tried both approaches, perror and strerror(errno) to  handle errors with specific error messages, 


SOURCE FILES 
fops_test.c
libfops.c
fops.h

SOURCES
Everything System Call Related I used man pages
    - Implemented certain parameters modes, includes, etc. through synopsis/examples
    - https://man7.org/


RUNNING INSTRUCTIONS

Compile object files for library:
gcc -c libfops.c
ls *.o

Create Static Library
ar crv libfops.a libfops.c
file libfops.a

Compile
gcc fops_test.c -o fops_test libfops.a

Run Program:
    - Create File: ./fops_test create <filename>
    - Write to File: ./fops_test write <filename> [message]
    - Read from File: ./fops_test read <filename>
    - Close File: ./fops_test close <filename>
    - Delete File: ./fops_test delete <filename>
