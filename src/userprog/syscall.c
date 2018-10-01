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
  printf("Sys call number: %d\n", args[0]);

  if (args[0] == SYS_WRITE) {
    debug_backtrace();
    printf("fd = %d\n", args[1]);
    printf("size = %d\n", args[3]);
    //f->eax = write(args);
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

int write(uint32_t *args) {
    //pushl long 4 bytes
    //int fd, const void *buffer, unsigned size;
    // int fd = args[1];
    // char *buffer =(char*) args[2];
    // unsigned size = args[3];
    //printf("FD %d\n && Buffer: %s\n", fd, *buffer);

    //printf("Buffer is %c\n")

    //printf("%d\t%s\t%d\n", fd, buffer, size)

    // printf("File Descriptor is %d\n", *(args + 1));
    // //printf("File Descriptor is %d\n", fd);
    // printf("Data is %s\n", buffer);
    // printf("Size is %d\n", *(args + 3));
    // printf("\n");
    //printf("FD: %d\tBuffer %p\tSize: %d\n", fd, buffer, size);
    //printf("Called write\n");
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