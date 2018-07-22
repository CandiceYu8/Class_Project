#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	pid_t p1, p2, p3;
	int loop;
	loop = 0;
	p1 = fork();
	if (!p1) {
		chrt(20);
		p1 = getpid();
		while (1) {
			sleep(1);
			printf("P1 pid: %d heart beat: %d\n", p1, loop++);
			if (loop == 5)
				chrt(5);
		}
	}
	p2 = fork();
	if (!p2) {
		chrt(15);
		p2 = getpid();
		while (1) {
			sleep(1);
			printf("P2 pid: %d heart beat: %d\n", p2, loop++);
		}
	}
	p3 = fork();
	if (!p3) {
		p3 = getpid();
		while (1) {
			sleep(1);
			printf("P3 pid: %d heart beat: %d\n", p3, loop++);
			if (loop == 10)
				chrt(3);
		}
	}
	return 0;
}