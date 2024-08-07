#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
DRD will report \"Invalid semaphore\" errors.
This seems to be an issue with DRD.
When a semaphore gets increased by one process, and another process waits for that semaphore, DRD does not see that and reports this error.
You can see this by adding '--trace-semaphore=yes' to the DRD flags.
You will notice that even though one process increased the semaphore, for the other process it still shows as 0.
*/

#define SEM1 "/semaphore1"
#define SEM2 "/semaphore2"

int	main(void)
{
	sem_t	*sem[2];
	pid_t	child_pid;
	int 	val;

	sem_unlink(SEM1);
	sem[0] = sem_open(SEM1, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);

	child_pid = fork();
	if (child_pid == 0)
	{
		sem_getvalue(sem[0], &val);
		printf("child: %d\n", val);
		sem_wait(sem[0]);
		sem_getvalue(sem[0], &val);
		printf("child: %d\n", val);
		exit(0);
	}
	sleep(1);
	sem_getvalue(sem[0], &val);
	printf("parent: %d\n", val);
	sem_post(sem[0]);
	sem_getvalue(sem[0], &val);
	printf("parent: %d\n", val);
	waitpid(child_pid, NULL, 0);
}
