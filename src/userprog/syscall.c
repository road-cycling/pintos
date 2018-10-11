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

static void syscall_handler (struct intr_frame *f) {
  //intr_dump_frame(f);
  //hex_dump(f->esp, f->esp, 20, true);  
  //intr_dump_frame(f->esp);
  printf ("system call!\n");
  thread_exit ();
}
