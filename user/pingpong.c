#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int p1[2], p2[2];
	pipe(p1);
	pipe(p2);
	if (fork() == 0)
	{
		// child process
		char c;
		while (read(p1[0], &c, 1) < 1)
			;
		int pid = getpid();
		fprintf(1, "%d: received ping\n", pid);
		c = c + 1;
		write(p2[1], &c, 1);
		close(p1[0]);
		close(p1[1]);
		close(p2[0]);
		close(p2[1]);
	}
	else
	{
		// parent process
		char c = 'a';
		write(p1[1], &c, 1);
		while (read(p2[0], &c, 1) < 1)
			;
		int pid = getpid();
		fprintf(1, "%d: received pong\n", pid);
		close(p1[0]);
		close(p1[1]);
		close(p2[0]);
		close(p2[1]);
	}
	exit(0);
}
