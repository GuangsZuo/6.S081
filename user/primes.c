#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void newpipeline(int *p) {
	int q[2];
	int x ;
	int status = read(p[0], &x, 4);
	//fprintf(1,"status:%d\n", status);
	if (!status) return;
	pipe(q);
	if (status!=0 && fork()==0) {
		close(q[1]);
		newpipeline(q);
	}
	else {
		int  fx=-1;
		close(q[0]);
		while (status!=0) {
			if (fx<0) {
				fx = x;
				fprintf(1, "prime %d\n",fx);
			} else {
				if (x % fx!=0) {
				write(q[1],&x, 4);
				//fprintf(1,"%d\n",x);
				}
			}
			status = read(p[0], &x, 4);
		}
		close(p[0]);
		close(q[1]);
		wait(0);
	}
}

int
main(int argc, char *argv[])
{
	int p[2];
	pipe(p);
	if (fork()==0) {
		close(p[1]);
		newpipeline(p);	
	} else {
		close(p[0]);
		for (int i=2;i<=35; ++i) write(p[1], &i, 4);
		close(p[1]);
		wait(0);
	}
	exit(0);
}
