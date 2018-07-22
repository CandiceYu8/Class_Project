#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#define maxn 1024*10
#define randmax 1024*1024*200

long Random(long start, long end);
void Write_test(int nbytes);          
void Write_ran(int fd, int nbytes);
void Write_seq(int fd, int nbytes);

char* buffer = "hello world";
int cycle = 10000;

int main(int argc, char const *argv[])
{
    int cnt=1;
    int iteration, forktimes;
    int nbytes;      /* 粒度大小，一次读/写多少字节 */
    const char* pathName_RAM = "/root/myram/read_file.txt";
    const char* pathName_Disc = "/usr/read_file.txt";
    struct timeval start, end;

    int fd_ram = open(pathName_RAM, O_RDWR|O_SYNC);
    int fd_disc = open(pathName_Disc, O_RDWR|O_SYNC);

    srand((unsigned)time(NULL));
    for(iteration=6; iteration<15; iteration++){
        nbytes = pow(2,iteration);
        if(nbytes >= maxn){
            return 0;
        }


        for(forktimes=1; forktimes<=33; forktimes+=5){
            cnt=1;
            gettimeofday(&start, NULL);
            while(cnt <= forktimes){
                if(fork() == 0){
                    // Write_ran(fd_ram, nbytes);
                    Write_seq(fd_ram, nbytes);
                    // Write_ran(fd_disc, nbytes);
                    // Write_seq(fd_disc, nbytes);
                    return 0;
                }
                cnt++;
            }

            while(cnt>=1){
                if(!waitpid(-1, NULL, 0))
                    return 0;
                cnt--;
            } 
            gettimeofday(&end, NULL);
            long timeuse_us = 1000000*(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
            double latency = timeuse_us/(double)cycle/1000.0;   /* ms */
            double thoughout = nbytes*forktimes*(1000.0/1024/1024)/latency;
            // printf("write Disc: nbytes %d b, thoughout %.3f Mb/s, latency %.3f ms, forktimes %d\n", nbytes, thoughout, latency, forktimes);
            printf("write RAM: nbytes %d b, thoughout %.3f Mb/s, latency %.3f ms, forktimes %d\n", nbytes, thoughout, latency, forktimes);
        }
    }

    close(fd_ram);
    close(fd_disc);
    return 0;
}



long Random(long start, long end)
{
    long dis = end - start;
    return rand() % dis + start;
}


void Write_ran(int fd, int nbytes)
{
    for(int j=1; j<=cycle; j++){
        if(write(fd, buffer, nbytes)<=0){
            printf("write error! \n");
            return;
        }
        if(lseek(fd, Random(0, randmax), SEEK_SET)<0){
            printf("lseek error! \n");
            return;
        }
    }
    lseek(fd, 0, SEEK_SET);
}


void Write_seq(int fd, int nbytes)
{
    for(int j=1; j<=cycle; j++){
        if(write(fd, buffer, nbytes)<=0){
            printf("write error! \n");
            return;
        }
    }
    lseek(fd, 0, SEEK_SET);
}