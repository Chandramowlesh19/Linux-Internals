/****************************************************************************************************************************************

Name : Chandramowlesh.S
Date : 07/06/2022
Description :create child process to execute command passed through command line
sample input : ./exec_child date
sample output : This is child process with id 2817
                Tue Jun  7 23:13:07 IST 2022
                Child exited with status 0 


*****************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
		if (argc < 2)
		{
				printf("\nError : Please Pass the Command through CL. \nUsage : ./exec_child <command> \n\n");
				return -1;
		}
		pid_t pid1 = fork();
		if (pid1)
		{
				//Parent
				int child_status;
				wait(&child_status);
				if (WIFEXITED(child_status))
				{
						printf("Child exited with status %d\n\n", WEXITSTATUS(child_status));
				}
		}
		else
		{
				//First Child
				printf("\nThis is child process with id %d\n", getpid());
				argv[argc] = NULL;
				//Get the path of the command. Attach the command name to /bin/
				//Command name is 
				if (execvp(argv[1], argv + 1) == -1)
				{
						printf("Error: Incorrect command provided!\n");
						exit(1);
				}	
		}
		return 0;
}
