/****************************************************************************************************************************************
Name: Chandramowlesh.S
Description : dup command using system calls
*****************************************************************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
		int fd1, copy_of_stdout;

		copy_of_stdout = dup(1);

		//Above line means that 1 & 3 both point to file pointer of stdout

		fd1 = open("dest.txt", O_CREAT | O_WRONLY, 0664);//fd1 = 4
		if (fd1 == -1)
		{
				perror("open");
				return -1;
		}
		close(1);//Closing fd of stdout

		//Since fd of stdout(1) is closed, the line below makes 1 point to redirect.txt

		dup(fd1);

		printf("Message printed here with fd = %d\n", fd1);//Prints in file redirect.txt

		close(3);//Close 1

		fflush(stdout);//flush the stdout buffer data

		//dup(copy_of_stdout)

		printf("Print this Message in to stdout\n");//Prints in stdout
		return 0;
}
