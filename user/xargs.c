#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char* argv[]) {
	char args[8][32];
	char ch, s[32] ;
	int k = 0, si=0;
	// should parellel the pipe reading and xargs running 
	while ((read(0, &ch, 1)))  {
		if (ch=='\n') {
			s[si] = '\0';
			strcpy(args[k++], s); 
			si = 0 ;
			//printf("%s\n", args[k-1]);
		}	
		else {
			s[si++] = ch; 
		}
	}

	for (int i=0; i<k; ++i) { 
		char * param[8];
		int kk =0 ;
		for (int j=1; j<argc; ++j) param[kk++] = argv[j];
		param[kk] = args[i];

		if (fork()==0) exec(argv[1], param);
		else wait(0);
	}
	exit(0);
}
