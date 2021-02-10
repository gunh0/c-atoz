## Virtual Thread Implementation Example

This code is an example of implementing Virtual Threads using the C language. Virtual Threads are a form of multithreading technology that shares the CPU, making them useful for increasing the number of threads without the overhead of typical threads.

<br/>

### Used Libraries

-   `pthread.h`: POSIX Thread library
-   `stdlib.h`: Library for using the malloc function
-   `unistd.h`: Library for using the usleep function

<br/>

### Function Descriptions

-   `thread_func`: Function to be executed by the Virtual Thread. It prints the number of the running Virtual Thread based on the received argument and waits for 0.1 seconds using the usleep function.
-   `main`: Creates 5 Virtual Threads and executes the `thread_func` for each. Waits until all created Virtual Threads have finished.
