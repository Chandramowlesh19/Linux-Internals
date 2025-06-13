#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>

void convert_to_uppercase(char* s)
{
		while(*s != '\0')
		{
				if (*s >= 'a' && *s <= 'z')
						*s -= 32;
				s++;
		}
}

int main()
{
		int fds[2];
		pipe(fds);
		pid_t pid1 = fork();
		if (pid1)
		{
				char str[80] = {'\0'};//Store a string
				printf("Enter a string: ");
				scanf("%[^\n]", str);
				int size = strlen(str);
				//Close read end & write from pipe
				close(fds[0]);
				write(fds[1], &size, sizeof(int));//Write 1 byte size
				write(fds[1], str, size);//Write the string itself
				close(fds[1]);
				//Get status of both child processes
				int status1;
				wait(&status1);
				if (WIFEXITED(status1))
				{
						printf("P2 is terminated normally\n");
				}
				
				
				int fd = open("TO_FIFO", O_RDONLY);
				if (fd == -1)
				{
						perror("open");
						return -1; 
				}
				read(fd, &size, sizeof(int));
				char* result_str = calloc((size + 1), sizeof(char));
				read(fd, result_str, size);
				close(fd);
				printf("Resultant string is: %s\n", result_str);
				free(result_str);
				return 0;
		}
		else
		{
				
				char read_str[80] = {'\0'};
				int size;
				
				close(fds[1]);
				read(fds[0], &size, sizeof(int));
				read(fds[0], read_str, size);
				close(fds[0]);
				convert_to_uppercase(read_str);
				printf("String read from pipe & case converted by P2 as: %s\nNow P2 stores the modified string into shared memory\n", read_str);
				
				int shmid = shmget('B', 80, IPC_CREAT | 0664);
			
				char* ptr = shmat(shmid, NULL, 0);
				strcpy(ptr, read_str);
				shmdt(ptr);
		}
		return 0;
}
