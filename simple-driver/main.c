#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void){
    int fd;
    char buff[50];
    fd = open("/dev/NewDevice", O_RDONLY);
    if (fd == -1) {
        printf("Cannot open file.\n");
        return 1;
    };
    read(fd, buff, 20);
    buff[20] = 0;
    printf("Read text: %s\n", buff);
    return 0;
}
