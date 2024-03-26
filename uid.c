#include <time.h>/*time_t*/
#include <stddef.h>/*NULL*/
#include <unistd.h>/*getpid*/
#include <pthread.h>

#include "uid.h"

uid_ty bad_uid = {0,((time_t)-1),0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

uid_ty UIDGenerate(void)
{
	uid_ty uid;
	static int count=0;

	uid.pid = (size_t)getpid();
	uid.time_stamp = time(NULL);
	pthread_mutex_init(&mutex, NULL);

	if(uid.time_stamp == -1)
	{
		 uid.time_stamp = 0;
	}

	pthread_mutex_lock(&mutex);
	uid.id_counter=count;
	++count;
	pthread_mutex_unlock(&mutex);




	return uid;
}

int UIDIsSame(uid_ty first, uid_ty second)
{
	return first.pid == second.pid &&
	 first.time_stamp == second.time_stamp && 
	 first.id_counter == second.id_counter;
}

uid_ty UIDGetBadUID(void)
{
	return bad_uid;
}