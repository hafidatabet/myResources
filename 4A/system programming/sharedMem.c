
/* =====================================================================
   INCLUDES
   ===================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/mman.h>

// Build command:
// gcc sharedMem -o shm -lrt

/* =======================================
   CONSTANTS
   ======================================= */
#define MAX_MSG	1024
#define SHARED_MEMORY_NAME 		"PING_SYNCHRO"

/* /* =====================================================================
   GLOBAL DECLARATIONS
   ===================================================================== */
char *message;

/*=====================================================================
   PUBLIC FUNCTIONS
===================================================================== */
/* ---------------------------------------------------------------------
   Entry point
   --------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
	int shmID;
	char msg[MAX_MSG];
	
	// create shm descriptor
	shmID = shm_open(SHARED_MEMORY_NAME,
						O_CREAT | O_RDWR,
						0777);
	if (shmID == -1){
		return -1;
	}
	ftruncate(shmID, MAX_MSG);

	// map smh to pointer
	message = (char*)mmap(NULL,
						MAX_MSG,
						PROT_READ | PROT_WRITE,
						MAP_SHARED,
						shmID, 0);
	
    // Activity loop based on number of arguments
	// no arg = writer //////////////////////////
	if (argc == 1)
	{
		do
		{
			printf("> ");
			scanf("%s", msg);
			strcpy(message, msg);
		} while (strcmp(msg, "quit") != 0);
	}
	// arg = reader /////////////////////////////
	else
	{
		do
		{
			printf("-- %s --\n", message);
			sleep(1);
		} while (strcmp(message, "quit") != 0);
	}
    
	// Release ressources
	if (munmap(message, MAX_MSG) != 0){
		printf("Error unmapping\n");
	}

	shm_unlink(SHARED_MEMORY_NAME);

	return 0;
}
