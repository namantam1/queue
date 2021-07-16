# Queue Implementation in C Language

## Features - 
1. Generic Data type support.
2. Auto garbage collection while dequeuing the data from queue.
3. No size restriction due to implementation with the help of linked list.
4. Better data structure management.

## How to use -

- Clone this project.
```bash
git clone https://github.com/namantam1/queue
cd queue
```
- Run the example file with make or command line.
```bash
make
# or
gcc queue.c example.c
```
- To use this queue in another project import this libary as -
```c
#include "queue/queue.h"

int main() {
    int data = 10;
    // create a new queue
    queue q = create_queue(&data);

    // do you stuff
    // ...
    // ...

    // destroy the queue if not in use to free the memory.
    destroy_queue(q);
}
```

## Issue

If you find any please don't hesitate to create an [issue](https://github.com/namantam1/queue/issues).

Any Contribution or suggestion are welcome.

## License
This project is [MIT](LICENSE) License.