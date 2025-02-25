# AUTHOR INFO

**Full name:**  
Nikolai Semerdjiev

**Project:**  
System Call Interface

---

# ERRORS

- Everything works, but I think I could have been more efficient with variable creation—there are a few repeated variable declarations, but without them my code would not work.
- I tried both approaches (`perror` and `strerror(errno)`) for handling errors with specific error messages.

---

# SOURCE FILES

- `fops_test.c`
- `libfops.c`
- `fops.h`

---

# SOURCES

Everything system call related – I used man pages for guidance:
- Implemented certain parameters (modes, includes, etc.) through synopsis/examples.
- [man7.org](https://man7.org/)

---

# RUNNING INSTRUCTIONS

```bash
# Compile object files, create static library, and compile the project
gcc -c libfops.c
ar crv libfops.a libfops.c
gcc fops_test.c -o fops_test libfops.a

# Run Program:
# Create File:
./fops_test create <filename>

# Write to File:
./fops_test write <filename> [message]

# Read from File:
./fops_test read <filename>

# Close File:
./fops_test close <filename>

# Delete File:
./fops_test delete <filename>
