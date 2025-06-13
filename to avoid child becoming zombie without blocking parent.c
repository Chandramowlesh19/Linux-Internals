/**************************************************************************************************************************************

Name : Chandramowlesh.S
Date : 07-06-2022
Description :avoid child becoming zombie without blocking parent
sample input : ./a.out
sample output : A child created with pid 3137
parent is running
parent is running
parent is running . .
............................
Child 3137 terminated normally with exit status 0


*********************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
		pid_t pid1 = fork();
		if (pid1)
		{
				//Parent
				int status;
				do
				{
						printf("Parent is running\n");
				} while (pid1 != waitpid(pid1, &status, WNOHANG));
				printf("Child %d terminated normally with exit status %d\n\n", pid1, WEXITSTATUS(status));
				return 0;
		}
		else
		{
				//First Child
				printf("A child is created with pid %d\n", getpid());
				sleep(0.1);
				return 0;
		}
}
