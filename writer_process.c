//program to convert string to uppercse using shared memory
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
#include<time.h>

int main(void)
{
    void *shared_mem;
    int shmid;
    char buffer[100];
    shmid = shmget((key_t)12345, 1024, 0666 | IPC_CREAT);
    if(shmid == -1)
    {
        printf("Error in creating the shared memory \n");
        exit(0);
    }
    shared_mem = shmat(shmid, NULL, 0);
    if(shared_mem == (void *)-1)
    {
        printf("Error in attaching the shared memory \n");
        exit(0);
    }
    printf("Enter the message to be sent or added in the shared memory : ");
    fgets(buffer, 100, stdin);
    strcpy(shared_mem, buffer);
    printf("Message sent or added to the shared memory was :- %s\n", (char* )shared_mem);
    //wait for 45 seconds
    sleep(45);
    printf("Message recieved from process 2 is :- %s\n",(char* )shared_mem);
return 0;
}
