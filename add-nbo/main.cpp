#include <stdio.h>
#include <stdint.h> // for uint32_t


uint32_t my_htonl(uint32_t n){
    uint32_t n1 = (n & 0xFF000000) >> 24;
    uint32_t n2 = (n & 0x00FF0000) >> 8;
    uint32_t n3 = (n & 0x0000FF00) << 8;
    uint32_t n4 = (n & 0x000000FF) << 24;

    return n1 | n2 | n3 | n4;
}


int main(int argc, char *argv[]) {

    FILE *fd1, *fd2;
    uint32_t buf[4];
    uint32_t buf2[4];
    uint32_t sum;

    //printf("hello bigfrog!\n");

    if(argc < 3){
        printf("[syntax]: ./add-nbo <file1> <file2>\n");
        return -1;
    }

    fd1 = fopen(argv[1], "r");
    if(!fd1){
        printf("file open error.\n");
        return -1;
    }
    fread(buf, 1, 4, fd1);


    fd2 = fopen(argv[2], "r");
    if(!fd2){
        printf("file open error.\n");
        return -1;
    }
    fread(buf2, 1, 4, fd2);


    uint32_t* p = buf;
    uint32_t* p2 = buf2;

    uint32_t n = my_htonl(*p);
    uint32_t n2 = my_htonl(*p2);


    sum = n + n2;
    printf("%u(0x%x) + ",n,n);
    printf("%u(0x%x)",n2,n2);
    printf(" = %u(0x%x)\n", sum, sum);

    return 0;
}
