#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex; 

int main() {
	
	if (pthread_mutex_init(&mutex, NULL) != 0) {
    	printf("Mutex initialization failed.\n");
    	return 1;
	}

	// Lock the mutex
	if (pthread_mutex_lock(&mutex) != 0) {
    	printf("Mutex locking failed.\n");
    	return 1;
	}

	// Critical section
	printf("Inside critical section.\n");

	// Unlock the mutex
	if (pthread_mutex_unlock(&mutex) != 0) {
    	printf("Mutex unlocking failed.\n");
    	return 1;
	}

	// Destroy the mutex
	if (pthread_mutex_destroy(&mutex) != 0) {
    	printf("Mutex destruction failed.\n");
    	return 1;
	}

	return 0;
}