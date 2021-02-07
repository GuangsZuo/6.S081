#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc!=2) {
	fprintf(2, "usage: sleep sleeptime\n");
	exit(1);
  } 
  int sleeptime = 0;
  for (int i=0; argv[1][i]!='\0'; ++i) {
	if (argv[1][i]<'0' || argv[1][i]>'9') {
		fprintf(2, "sleep time must be an integer.\n");
		exit(1);
	}
	sleeptime = sleeptime * 10 + argv[1][i] - '0';
  }
  int status = sleep(sleeptime);
  if (status != 0) {
	fprintf(2, "unknown error.\n");
	exit(1);
  }
  exit(0);
}
