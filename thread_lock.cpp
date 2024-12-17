#include <iostream>
using namespace std;

#ifdef _COMPILE_WINDOWS
#include <Windows.h>
typedef HANDLE THREADVAR;
typedef DWORD WINAPI THREADFUNCVAR;
typedef LPVOID THREADFUNCARGS;
typedef THREADFUNCVAR(*THREADFUNC)(THREADFUNCARGS);
typedef CRITICAL_SECTION THREAD_LOCK;
#endif

#ifdef _COMPILE_LINUX
#include <pthread.h>
#include <unistd.h>
typedef pthread_t THREADVAR;
typedef void* THREADFUNCVAR;
typedef void* THREADFUNCARGS;
typedef THREADFUNCVAR(*THREADFUNC)(THREADFUNCARGS);
typedef pthread_mutex_t THREAD_LOCK;
typedef unsigned long int DWORD_PTR;
typedef unsigned int DWORD;
#endif

THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg);
void StopThread(THREADVAR t);
void InitThreadLock(THREAD_LOCK& t);
void LockThread(THREAD_LOCK& t);
void UnlockThread(THREAD_LOCK& t);
void ThreadSleep(int ms);

THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam);

int globlint = 0;
bool quitnow = false;

int main() {
    THREAD_LOCK recv_lock;
    InitThreadLock(recv_lock);

    DWORD_PTR* threadArgs = new DWORD_PTR[1];
    threadArgs[0] = (DWORD_PTR)&recv_lock;

    THREADVAR recvThread = PrepareThread(MyAsyncSimpleThread, (THREADFUNCARGS)threadArgs);

    while (!quitnow) {
        LockThread(recv_lock);
        globlint++;
        if (globlint > 5000) {
            quitnow = true;
        }
        cout << "\n\tMain loop: " << globlint;
        UnlockThread(recv_lock);
        ThreadSleep(5);
    }

    StopThread(recvThread);
    return 0;
}

THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam) {
    DWORD_PTR* args = (DWORD_PTR*)lpParam;
    THREAD_LOCK& recv_lock = *((THREAD_LOCK*)args[0]);

    while (!quitnow) {
        LockThread(recv_lock);
        globlint++;
        if (globlint > 100) {
            quitnow = true;
        }
        cout << "\nAsync thread: " << globlint;
        UnlockThread(recv_lock);
        ThreadSleep(1);
    }
    return NULL;
}

THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg) {
#ifdef _COMPILE_LINUX
    pthread_t thread;
    pthread_create(&thread, NULL, f, arg);
    return thread;
#endif
#ifdef _COMPILE_WINDOWS
    DWORD threadId;
    THREADVAR threadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)f, arg, 0, &threadId);
    return threadHandle;
#endif
}

void StopThread(THREADVAR t) {
#ifdef _COMPILE_LINUX
    pthread_cancel(t);
#endif
#ifdef _COMPILE_WINDOWS
    TerminateThread(t, 0);
    CloseHandle(t);
#endif
}

void InitThreadLock(THREAD_LOCK& t) {
#ifdef _COMPILE_LINUX
    pthread_mutex_init(&t, NULL);
#endif
#ifdef _COMPILE_WINDOWS
    InitializeCriticalSection(&t);
#endif
}

void LockThread(THREAD_LOCK& t) {
#ifdef _COMPILE_LINUX
    pthread_mutex_lock(&t);
#endif
#ifdef _COMPILE_WINDOWS
    EnterCriticalSection(&t);
#endif
}

void UnlockThread(THREAD_LOCK& t) {
#ifdef _COMPILE_LINUX
    pthread_mutex_unlock(&t);
#endif
#ifdef _COMPILE_WINDOWS
    LeaveCriticalSection(&t);
#endif
}

void ThreadSleep(int ms) {
#ifdef _COMPILE_LINUX
    usleep(ms * 1000);
#endif
#ifdef _COMPILE_WINDOWS
    Sleep(ms);
#endif
}
