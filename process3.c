#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

void strrev(char* s, int size, char iter)
{
       
        if (iter < (size) / 2)
        {
                
                s[iter] ^= s[size - 1 - iter];
                s[size - 1 - iter] ^= s[iter];
                s[iter] = s[size - 1 - iter] ^ s[iter];
               
                strrev(s, size, ++iter);
        }
        
}

int main()
{
		
		char str[80] = {'\0'};
		
		int shmid = shmget('B', 80, IPC_CREAT | 0664);
		
		char* ptr = shmat(shmid, NULL, 0);
		
		strcpy(str, ptr);
		shmdt(ptr);
		shmctl(shmid, IPC_RMID, NULL);
		int size = strlen(str);
		strrev(str, size, 0);
		printf("String is reversed by P3\nSo the resultant string is: %s\nNow writing the modified string into fifo file 'TO_FIFO'\n", str);
		
		mkfifo("TO_FIFO", 0664);
		
		int fd = open("TO_FIFO", O_WRONLY);
		if (fd == -1)
		{
				perror("open");
				return -1;
		}
		write(fd, &size, sizeof(int));
		write(fd, str, size);
		close(fd);
		return 0;
}

