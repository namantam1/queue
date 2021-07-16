#include <stdlib.h>
#include <stdbool.h>

#ifndef __QUEUE_H__
#define __QUEUE_H__

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void *void_ptr;
    typedef const void *c_void_ptr;

    typedef struct Queue queue;
    typedef queue *queue_ptr;

    /**
     * Create a new queue from givin data.
     * 
     * @param size: Size of generic data
     * @param data: Generic data (option)
     * 
     * @returns queue pointer
    */
    queue_ptr create_queue(size_t, c_void_ptr);

    /**
     * Function to add the element to to queue
     * 
     * @param q: queue pointer
     * @param data: data to add to queue
     * @return void(0)
    */
    void add(queue_ptr, c_void_ptr);

    /**
     * Function to remove a node from queue from top
     * 
     * @param q: queue pointer
     * @param data: a mutable data pointer with memory allocated
     * or use static varible pointer.
     * @return void(0)
    */
    bool dequeue(queue_ptr, void_ptr);

    /**
     * Function to get top node data of the queue
     * @param q: queue pointer
     * @return data pointer if queue not empty else NULL
    */
    void_ptr peek(queue_ptr);

    /**
     * TODO: Function to search an element from the given
     * key with the help of compare function.
     * 
     * @param q: queue pointer
     * @param key: key pointer
     * @param comp_fun: compare function to get data from given 
     * key which take data and key as argument.
     * @return returns pointer to the data
    */
    void_ptr search(queue_ptr, void_ptr, bool (*)(void_ptr, void_ptr));

    /**
     * Print the string representation of queue
     * 
     * @param q: queue pointer
     * @param print: print function with a data pointer argument
     * @return void(0)
    */
    void print_queue(queue_ptr, void (*)(void_ptr));

    /**
     * Function to get the current length of queue
     * 
     * @param q: queue pointer
     * @return length(int)
    */
    int length(queue_ptr);

    /**
     * Function to clear all the memory created along with queue
     * 
     * @param q: queue double pointer
    */
    void destroy_queue(queue_ptr *);

    /**
     * Function to check if queue is empty
     * 
     * @param q: queue pointer
     * @return boolean
    */
    bool is_empty(queue_ptr);

#ifdef __cplusplus
}
#endif

#endif // __QUEUE_H__