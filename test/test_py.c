#include<c_labs.h>


#define NUM_THREADS 5
int main(){
    Py_Initialize();

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, &python_func, &thread_ids[i])) {
            fprintf(stderr, "Error creating thread %d\n", i + 1);
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return 0;
}