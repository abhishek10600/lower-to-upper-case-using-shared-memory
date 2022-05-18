//program to convert string to upper case using shared memory
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>

void convert_to_uppercase(char* str)
{
    //convert the given string str to uppercase
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]>='a' && str[i]<='z')
        {
            str[i] = str[i] - 32;
        }
    }
}

int main(void)
{
    void *shared_mem;
    char *data_recvd;
    int shmid;
    char buffer[100];
    shmid = shmget((key_t)12345, 1024, 0666);
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
    data_recvd = (char *)shared_mem;
    convert_to_uppercase(data_recvd);
    strcpy(shared_mem, data_recvd);
    return 0;
}
