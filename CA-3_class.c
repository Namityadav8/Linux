#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Declare semaphores
sem_t buy_sem;
sem_t sell_sem;

void completeBuy() {
    // Perform the buy operation here
    printf("Buy operation completed.\n");
}

void completeSell() {
    // Perform the sell operation here
    printf("Sell operation completed.\n");
}

void* buy_thread_function(void* arg) {
    // Start of synchronization logic
    sem_wait(&buy_sem); // Wait for a matching sell thread
    sem_post(&sell_sem); // Notify the matching sell thread
    // End of synchronization logic

    completeBuy(); // Complete the buy operation
    pthread_exit(NULL);
}

void* sell_thread_function(void* arg) {
    // Start of synchronization logic
    sem_wait(&sell_sem); // Wait for a matching buy thread
    sem_post(&buy_sem); // Notify the matching buy thread
    // End of synchronization logic

    completeSell(); // Complete the sell operation
    pthread_exit(NULL);
}

int main() {
    // Initialize semaphores
    sem_init(&buy_sem, 0, 0);
    sem_init(&sell_sem, 0, 0);

    pthread_t buy_thread, sell_thread;

    // Create buy and sell threads
    pthread_create(&buy_thread, NULL, buy_thread_function, NULL);
    pthread_create(&sell_thread, NULL, sell_thread_function, NULL);

    // Wait for threads to finish
    pthread_join(buy_thread, NULL);
    pthread_join(sell_thread, NULL);

    // Clean up semaphores
    sem_destroy(&buy_sem);
    sem_destroy(&sell_sem);

    return 0;
}