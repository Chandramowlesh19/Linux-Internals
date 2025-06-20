 /***************************************************************************************************************************************

Name : Chandramowleh.S
Date : 12/06/2022
Description :create three child from the same parent
sample input : ./a.out
sample outut :    This is parent 2584
                  Child 1 with pid 2587 created
                  Child 2 with pid 2586 created
                  Child 3 with pid 2585 created
                  Child 2585 is terminated with code 0
                  Child 2586 is terminated with code 0
                  Child 2587 is terminated with code 0 

               
************************************************************************************************************************************/
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
            printf("This is parent %d\n", getpid());
				pid_t pid2 = fork();
				if (pid2)
				{
			
						//Same parent
						pid_t pid3 = fork();
						if (pid3)
						{
								int status1, status2, status3;
								//Same parent
								wait(&status1);
								if (WIFEXITED(status1))
								{
										printf("Child %d is terminated with code %d\n", pid1, WEXITSTATUS(status1));
								}
								wait(&status2);
								if (WIFEXITED(status2))
								{
										printf("Child %d is terminated with code %d\n", pid2, WEXITSTATUS(status2));
								}
								wait(&status3);
								if (WIFEXITED(status3))
								{
										printf("Child %d is terminated with code %d\n", pid3, WEXITSTATUS(status3));
								}
						}
						else
						{
                            //First Child
                  printf("Child 1 with pid %d created\n", getpid());
                  sleep(1);
                 return 0;
						}
				}
				else
				{
						//Second Child
						printf("Child 2 with pid %d created\n", getpid());
						sleep(2);
						return 0;
				}
		}
		else
		{
            //Third child
            printf("Child 3 with pid %d created\n", getpid());
           sleep(3);
            return 0;

				
		}
		return 0;
}
