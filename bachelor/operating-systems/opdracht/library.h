#include <ucontext.h>
#include <cstdlib>
#include <iostream>
#include <queue>

// Deze structuur bevat de variabelen geassocieerd met een thread.
typedef struct {
	ucontext_t context;
	unsigned char *stack;
	bool finished;
} usthread_t;

typedef void*(*function)(void*);

static usthread_t main_thread;

// De thread die nu draait
usthread_t *current_thread = 0;

#define MAX_THREADS 5
usthread_t *queue[MAX_THREADS];
int threadIndex = 0;

int freeSpot() {
	int index = threadIndex;
	index++;
	index %= MAX_THREADS;

	while(index != threadIndex) {
		if(queue[index] == NULL)
			return index;
		index++;
		index %= MAX_THREADS;
	}

	return -1;
}

int filledSpot() {
	int index = threadIndex + 1;
	index %= MAX_THREADS;

	while(index != threadIndex) {
		if(queue[index] != NULL) {
			return index;
		}

		index++;
		index %= MAX_THREADS;
	}

	return -1;
}

void usthread_init() {
    getcontext(&main_thread.context);

	main_thread.stack = 0;
	current_thread = &main_thread;

	queue[0] = &main_thread;
	for(int i = 1; i < MAX_THREADS; ++i)
		queue[i] = 0;
}

void usthread_schedule() {
	//Search next thread index
	int nextThread = filledSpot();
	//If nexthread = -1 no thread is active
	if(nextThread != -1) {
		//Swap contexts
		usthread_t* thread = queue[nextThread];
		usthread_t* old = current_thread;
		threadIndex = nextThread;

		current_thread = thread;
		swapcontext(&(old->context), &(thread->context));
	}
}

int usthread_yield() {
	usthread_schedule();
}

void usthread_exit() {
	// Finish de huidige thread en verwijder uit de queue
	int index = threadIndex;
	usthread_t* thread = queue[index];
	current_thread->finished = true;
	free(thread->stack);
	queue[index] = NULL;

	// Schedule nieuwe thread
	usthread_schedule();
}

void usthread_start_thread(function f, void *v) {
	f(v);
	usthread_exit();
}

int usthread_spawn(usthread_t *thread, function f, void *v) {
	//Fill with current context 
	getcontext(&(thread->context));
	//Allocate stack
	thread->stack = (unsigned char *)calloc( SIGSTKSZ, 1 );
    thread->context.uc_stack.ss_sp = thread->stack;
    thread->context.uc_stack.ss_size = SIGSTKSZ;
    thread->context.uc_link = NULL;
    //Make context which starts in start thread
    makecontext(&(thread->context), (void (*) (void)) usthread_start_thread, 2, f, v);
	//Search free spot for new thread
	int pos = freeSpot();
	//If pos = -1 no spot is left
	if(pos != -1)
		queue[pos] = thread;

	return 1;
}

void usthread_join( usthread_t *thread ) {
	//Wait till the thread we wait on is finished
	while(!thread->finished) {
		usthread_schedule();
	}
}