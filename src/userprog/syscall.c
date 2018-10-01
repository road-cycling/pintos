#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"


static void syscall_handler (struct intr_frame *);

void syscall_init (void) {
  //Registers internal interrupt VEC_NO to invoke HANDLER, which
  // is named NAME for debugging purposes.  The interrupt handler
  // will be invoked with interrupt status LEVEL.
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

//Extract the program inputs from the pointer (f->esp)
//Validate the inputs
    // Cannot be NULL
    // Cannot be kernel memory
    // Cannot be unmapped memory
    // Cannot be a bad pointer
// Run appropriate syscall
// Store ret value in f->eax

// came from looking at berkeley adapted proj instructions
//https://github.com/Berkeley-CS162/group0/blob/master/pintos/src/userprog/syscall.c

///lib/user/syscall.c
/*
    syscall0 (no args)
    syscall1 (1 arg)
    syscall2 (2 args)
    syscall3 (3 args)
*/

static void syscall_handler (struct intr_frame *f) {

  uint32_t *args = ((uint32_t *) f->esp);
  printf("Sys call number: %d ... \n", args[0]);

  if (args[0] == SYS_WRITE) {
    f->eax = write(args);

  }

  if (args[0] == SYS_EXIT) {
    f->eax = args[1];
    printf("%s: exit(%d)\n", &thread_current()->name, args[1]);
    thread_exit();
  }
}

/*

int
main (int argc, char **argv)
{
  int i;

  for (i = 0; i < argc; i++)
    printf ("%s ", argv[i]);
  printf ("\n");

  return EXIT_SUCCESS;
}

*/

// #define syscall3(NUMBER, ARG0, ARG1, ARG2)                      \
//         ({                                                      \
//           int retval;                                           \
//           asm volatile                                          \
//             ("pushl %[arg2]; pushl %[arg1]; pushl %[arg0]; "    \
//              "pushl %[number]; int $0x30; addl $16, %%esp"      \
//                : "=a" (retval)                                  \
//                : [number] "i" (NUMBER),                         \
//                  [arg0] "g" (ARG0),                             \
//                  [arg1] "g" (ARG1),                             \
//                  [arg2] "g" (ARG2)                              \
//                : "memory");                                     \
//           retval;                                               \
//         })

// int
// write (int fd, const void *buffer, unsigned size) {
//   return syscall3 (SYS_WRITE, fd, buffer, size);
// }
//size
//buffer
//fd/
//number

int write(uint32_t *args) {
  
  int sysCallNumber = (int) args[0];
  int fd = (int) args[1];
  char *buffer = (char *) args[2];
  unsigned size = (unsigned) args[3];

  printf("Syscall #%d\n", sysCallNumber);
  printf("FD: %d\n", fd);
  printf("Size: %d\n", size);

  printf("Buffer is %s\n", *buffer);

  return 1;
}

/* 
int handlers -> syscall handlers 
ptr to syscall routine. based off syscall number
jump to address of routine
*/

//fd STDOUT_FILENO
    // putbuf putchar
    // src/lib/kernel/console.c

//pagedir_get_page().