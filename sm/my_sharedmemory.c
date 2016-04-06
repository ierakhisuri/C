#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ	27

main()
{
	char c;
	int shmid;
	key_t key;
	char *shm, *s;

	/* we'll name our shared memory segment "5678" */

	key = 5678;

	/* create segment */

	if((shmid = shmget (key, SHMSZ, IPC_CREAT | 0666)) <0){
		perror("shmget");
		exit(1);
	}

	/* attach the segmnet to our data space */

	if ((shm = shmat (shmid, NULL, 0)) == (char *) -1){
		perror("shmat");
		exit(1);
	}

	/*put something into memory for other process to read */

	s = shm;

	for(c = 'a'; c<= 'z'; c++)
		*s++ = c;
	*s = NULL;

	while (*shm != '*')
		sleep(1);

	exit(0);
}

