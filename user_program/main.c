#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int user_printk_fd = open("/dev/user_printk", O_RDWR);
    printf("printk(\"%s\\n\")\n", argv[1]);
    write(user_printk_fd, argv[1], strlen(argv[1]) + 1);
    exit(0);
}