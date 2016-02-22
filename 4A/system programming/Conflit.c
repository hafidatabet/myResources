#include "stdio.h"
#include "pthread.h"

#define MAXCNT 900000

int glocnt = 0;
int t1cnt = 0;
int t2cnt = 0;

void *incr1(void *pArg) {
	
	do
	{
		glocnt++;
		t1cnt++;
	} while (glocnt < MAXCNT);
	printf("1 - termine!\n");
	return 0;
}

void *incr2(void *pArg) {

	do
	{
		glocnt++;
		t2cnt++;
	} while (glocnt < MAXCNT);
	printf("2 - termine!\n");
	return 0;
}
int main() {
	
	pthread_t tid1, tid2;

	glocnt = 0;
	t1cnt = 0;
	t2cnt = 0;

	pthread_create(&tid1, NULL, incr1, &glocnt);
	pthread_create(&tid2, NULL, incr2, &glocnt);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("-----------------------------\n");
	printf("Glo = %d\ncnt1 = %d\ncnt2 = %d\n", glocnt, t1cnt, t2cnt);
	printf("Tot = %d\n", t1cnt + t2cnt);
}
