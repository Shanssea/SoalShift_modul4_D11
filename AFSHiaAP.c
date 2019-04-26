#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>

//kalau mau nge unmount, pilih sudo umount nama filesytemnya

static char *dirpath = "/home/sea/INI_FOLDER";

const char *charlist={",qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0"};

char new[500];
char neww[1000];
char full[1000];

char *dec(const char *name, int key){
	char ch;
	char *res = (char*) malloc(sizeof(char));
	int len = strlen(name);
	for (int i=0; i <= len; ++i){
		ch = name[i];
		for (int j=1; j<=94;j++){
			if (name[i]==charlist[j]){
				int a = j;
				a = a + key;
				if(a>94){
					a = a-94;				
				}
				ch = charlist[a];
			}
		}
		res[i] = ch;
	}
	//printf("\n%s\n",name);
	//printf("%s\n",res);
	return res;
}

char *decc(const char *name, int key){
	char ch;
	char *res = (char*) malloc(sizeof(char));
	int len = strlen(name);
	for (int i=0; i <= len; ++i){
		ch = name[i];
		for (int j=1; j<=94;j++){
			if (name[i]==charlist[j]){
				int a = j;
				a = a - key;
				if(a<0){
					a = a+94;				
				}
				ch = charlist[a];
			}
		}
		res[i] = ch;
	}
	//printf("\n%s\n",name);
	//printf("%s\n",res);
	return res;
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	 int res;
	char fpath[1000];
	//char newFile[100];
	char *new;
	new = dec(path,17);
	sprintf(fpath,"%s%s",dirpath,new);
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
	char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		path = dec(path,17);
		sprintf(fpath,"%s",path);
		//fpath = ec(fpath,17);
		//strcpy(fpath,ec(fpath,17));
	}
	else {
		path = dec(path,17);
		sprintf(fpath, "%s%s",dirpath,path);
		//fpath = ec(fpath,17);
		//strcpy(fpath,ec(fpath,17));
		
	}
	int res = 0;
	//int len = strlen(fpath);

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		
		
		strcpy(new,de->d_name);
		strcpy(full,dirpath);
		//neww = ec(new,17);
		strcpy(neww,decc(new,17));
		strcat(full,neww);
		res = (filler(buf, full, &st, 0));
			if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{	
	 char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};


int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
