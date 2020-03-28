#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "../my_drv.h"


int main(int argc, char **argv)
{
    char wbuf[8] ={11,22,33,44,55,66,77,88};
    char rbuf[125];
    int len = ARRSIZE(wbuf);
    int fd;

    if((fd = open("/dev/dev_meng",O_RDWR)) < 0)
        printf("/dev/dev_meng can't open!\r\n");

    write(fd, wbuf, len);
    read(fd, rbuf, len);

    close(fd);
    return 0;
}
