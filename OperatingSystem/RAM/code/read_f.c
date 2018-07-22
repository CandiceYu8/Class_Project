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
#define randmax 1024*1024*100

long Random(long start, long end);       
void Read_ran(int fd, char* buffer, int nbytes);
void Read_seq(int fd, char* buffer, int nbytes);

int cycle = 10000;

int main(int argc, char const *argv[])
{
    int cnt=1;
    int iteration, forktimes;
    int nbytes;      /* 粒度大小，一次读/写多少字节 */
    const char* pathName_RAM = "/root/myram/read_file.txt";
    const char* pathName_Disc = "/usr/read_file.txt";
    struct timeval start, end;

    int fd_ram = open(pathName_RAM, O_RDONLY);
    int fd_disc = open(pathName_Disc, O_RDONLY);
    char* buffer = (char*)malloc(maxn);

    for(iteration=6; iteration<13; iteration++){
        nbytes = pow(2,iteration);
        if(nbytes >= maxn){
            return 0;
        }


        for(forktimes=1; forktimes<=32; forktimes+=5){
            cnt=1;
            gettimeofday(&start, NULL);
            while(cnt <= forktimes){
                if(fork() == 0){
                    // Read_ran(fd_ram, buffer, nbytes);
                    // Read_seq(fd_ram, buffer, nbytes);
                    // Read_ran(fd_disc, buffer, nbytes);
                    Read_seq(fd_disc, buffer, nbytes);
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
            double timeuse_ms = 1000*(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000.0;
            double latency = timeuse_ms/(double)cycle;   /* ms */
            double thoughout = nbytes*forktimes*(1000.0/1024/1024)/latency;
            printf("read Disc: nbytes %d b, thoughout %.3f Mb/s, latency %.3f ms, forktimes %d\n", nbytes, thoughout, latency, forktimes);
            // printf("read RAM: nbytes %d b, thoughout %.3f Mb/s, latency %.3f ms, forktimes %d\n", nbytes, thoughout, latency, forktimes);
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


void Read_ran(int fd, char* buffer, int nbytes)
{
    for(int j=1; j<=cycle; j++){
        if(read(fd, buffer, nbytes)<=0){
            printf("read error! \n");
            return;
        }
        if(lseek(fd, Random(0, randmax), SEEK_SET)<0){
            printf("lseek error! \n");
            return;
        }
    }
    lseek(fd, 0, SEEK_SET);
}


void Read_seq(int fd, char* buffer, int nbytes)
{
    for(int j=1; j<=cycle; j++){
        if(read(fd, buffer, nbytes)<=0){
            printf("read error! \n");
            return;
        }
    }
    lseek(fd, 0, SEEK_SET);
}