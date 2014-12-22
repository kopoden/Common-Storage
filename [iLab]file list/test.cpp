#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

unsigned process_directory( char *theDir )
{
    const int PATH_MAX = 200;
    DIR *dir = NULL;
    struct dirent entry;
    struct dirent *entryPtr = NULL;
    int retval = 0;
    unsigned count = 0;
    char pathName[PATH_MAX + 1];

    /* открыть указанный каталог, если возможно. */
	dir = opendir( theDir );

    if( dir == NULL ) {
        printf( "Error opening %s: %s", theDir, strerror( errno ) );
        return 0;
    }
    else {
        struct stat info;
        stat(theDir, &info);
        printf("%d\n", _S_ISDIR(info.st_mode));
        printf("%d\n", info.st_nlink);
        printf("%d\n", info.st_ino);
        printf("%d", info.st_gid);
    }
}
int main () {

    process_directory("new\new1");


    return 0;
}
