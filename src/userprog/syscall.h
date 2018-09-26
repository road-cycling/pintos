#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);

// Terminates Pintos by calling shutdown_power_off() /devices/shutdown.h
// should rarely be used because you loose some information about possible
// deadlock situations etc.
void halt(void);

// Terminates the current user program, returning status to the kernel.
// If the processes parent waits for it, this is the status that should
// be returned. 0 success / non zero is error
void exit(int status);


//Runs the executable whose name is given in cmd_line args.
// Passing any given arguments, and returns the new process's
// program id (pid). Must return pid -1 (invalid pid) if the
// program cannot execute for any reason.
// pg30 appropriate synch (cant return until we know the child
// successfully loaded executable)
pid_t exec(const char *cmd_line);


//Waits for a child process pid and retrieves the child's exist status.
// If pid is still alive, wait until it terminates then returns the status
// that pid passed to exit. If pid did not call exit(), but was terminated by
// the kernel (killed due to exception), wait(pid) must return -1.
// (see more notes p30)
int wait(pid_t pid);


// creates a new file called file, initially initial_size bytes in size
// returns true if successful, false otherwise.
// Note: Creating a new file does not open it
// opening the new file is a separate operation (another syscall)
bool create(const char *file, unsigned initial_size);

//Deletes the file called file, Returns true if success / false otherwise
// A file may be removed regardless of O / C flags
// Removing an open file does not close it
bool remove(const char *file);

// Opens the file called file
// Returns a nonneg fd, or -1 if it could not be opened
// 0 (STDIN_FILENO) | 1 (STDOUT_FILENO). 
// Open will never return either of these FD's.
// FD (@31) are not inherited by child processes (???)
// When a single file is opened more than once, each open returns a separate fd
// do not share file position (gondree mentioned . research)
// closed independently different calls to close
int open (const char *file);

// Returns the size, in bytes of the file open as fd
// check pcb (?) what to do?
int filesize(int fd);


//Read size bytes from the file open as FD into the buffer.
// Returns the number of bytes actually read (0 @ eof)
// -1 couldnt be read. 
// Fd 0 reads from keyboard using input_getc() @ loc
int read(int fd, void *buffer, unsigned size);

//Writes size bytes from buffer to the open fd
//returns the nubmer of bytes actually written
// pintos fs does not extend file size (most os will
// extend file sys if one tries to write past it.)
// fd 1 write to the console. 
// write all of bufer in one call to putbuf()
// as long as its not bigger than a few hundredbytes
int write(int fd, const void * buffer, unsigned size);


// Changes the next byte to be read or written in open file fd to position
// expressed in bytes from the beginning of the file (position of 0 is start)
// Seek past current eof is not an err. 
// writes past end return an error.
void seek(int fd, unsigned position);

// returns the position of the next byte to be read or written in open file fd.
// expressed in bytes from the beginning of the file
unsigned tell (int fd);

//close the file descriptor fd. 
// exiting / term a process implicitly closes all its open fd.
// as if calling this for each one
void close(int fd);


//FS code is not threadsafe @32
#endif /* userprog/syscall.h */
