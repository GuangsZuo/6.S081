#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int contains(char* path, char* reg) {
	for (int i=0; i<=strlen(path)-strlen(reg); ++i) {
		char* p = path + i, *q = reg;
		while (*q && *q==*p) q++, p++;
		if (*q=='\0') return 1;
	}	 
	return 0; 
}
void find(char* path, char* reg) {
	int fd;
	struct stat st;
	if ((fd=open(path,0)) < 0) {
		fprintf(2, "error path: %s\n",path);
		return ;
	}
	fstat(fd, &st);
	//fprintf(1, "%s %d %d\n", path, fd, st.type);
	if (st.type == T_FILE) {
		if (contains(path, reg)) fprintf(1, "%s\n", path);
	} else if (st.type == T_DIR) {
		char buf[256];
		struct dirent de;
		strcpy(buf, path);
		char* p = buf + strlen(path);
		*p++ = '/';
		while (read(fd, &de, sizeof(de)) == sizeof(de)) {
			if (de.inum == 0){
				continue;
			}
			if (strcmp(de.name, ".") ==0 || 
					strcmp(de.name, "..")==0) 
				continue;
			//fprintf(1, "%s\n", de.name);
			strcpy(p,de.name);
			p[DIRSIZ] = 0;
			//fprintf(1,"%s\n",buf);
			find(buf, reg);
		}
	}
	close(fd);
}

int
main(int argc, char *argv[])
{	
	char reg[32]="\0";
	char path[256]=".";	
	if (argc>1)
	strcpy(path,argv[1]); 
	if (argc>2)
	strcpy(reg,argv[2]);
	find(path, reg);
	exit(0);
} 
