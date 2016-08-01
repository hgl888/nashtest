/* Threads.c */

#include "Threads.h"


#ifdef WIN32
	static WRes GetError()
	{
	  DWORD res = GetLastError();
	  return (res) ? (WRes)(res) : 1;
	}

	WRes HandleToWRes(HANDLE h) { return (h != 0) ? 0 : GetError(); }
	WRes BOOLToWRes(BOOL v) { return v ? 0 : GetError(); }

	WRes HandlePtr_Close(HANDLE *p)
	{
	  if (*p != NULL)
		if (!CloseHandle(*p))
		  return GetError();
	  *p = NULL;
	  return 0;
	}

	WRes Handle_WaitObject(HANDLE h) { return (WRes)WaitForSingleObject(h, INFINITE); }

	WRes Thread_Create(CThread *p, THREAD_FUNC_TYPE func, LPVOID param)
	{
	  unsigned threadId; /* Windows Me/98/95: threadId parameter may not be NULL in _beginthreadex/CreateThread functions */
	  *p =
		#ifdef UNDER_CE
		CreateThread(0, 0, func, param, 0, &threadId);
		#else
		(HANDLE)_beginthreadex(NULL, 0, func, param, 0, &threadId);
		#endif
		/* maybe we must use errno here, but probably GetLastError() is also OK. */
	  return HandleToWRes(*p);
	}

	WRes Event_Create(CEvent *p, BOOL manualReset, int signaled)
	{
	  *p = CreateEvent(NULL, manualReset, (signaled ? TRUE : FALSE), NULL);
	  return HandleToWRes(*p);
	}

	WRes Event_Set(CEvent *p) { return BOOLToWRes(SetEvent(*p)); }
	WRes Event_Reset(CEvent *p) { return BOOLToWRes(ResetEvent(*p)); }

	WRes ManualResetEvent_Create(CManualResetEvent *p, int signaled) { return Event_Create(p, TRUE, signaled); }
	WRes AutoResetEvent_Create(CAutoResetEvent *p, int signaled) { return Event_Create(p, FALSE, signaled); }
	WRes ManualResetEvent_CreateNotSignaled(CManualResetEvent *p) { return ManualResetEvent_Create(p, 0); }
	WRes AutoResetEvent_CreateNotSignaled(CAutoResetEvent *p) { return AutoResetEvent_Create(p, 0); }


	WRes Semaphore_Create(CSemaphore *p, UInt32 initCount, UInt32 maxCount)
	{
	  *p = CreateSemaphore(NULL, (LONG)initCount, (LONG)maxCount, NULL);
	  return HandleToWRes(*p);
	}

	static WRes Semaphore_Release(CSemaphore *p, LONG releaseCount, LONG *previousCount)
	  { return BOOLToWRes(ReleaseSemaphore(*p, releaseCount, previousCount)); }
	WRes Semaphore_ReleaseN(CSemaphore *p, UInt32 num)
	  { return Semaphore_Release(p, (LONG)num, NULL); }
	WRes Semaphore_Release1(CSemaphore *p) { return Semaphore_ReleaseN(p, 1); }

	WRes CriticalSection_Init(CCriticalSection *p)
	{
	  /* InitializeCriticalSection can raise only STATUS_NO_MEMORY exception */
	  #ifdef _MSC_VER
	  __try
	  #endif
	  {
		InitializeCriticalSection(p);
		/* InitializeCriticalSectionAndSpinCount(p, 0); */
	  }
	  #ifdef _MSC_VER
	  __except (EXCEPTION_EXECUTE_HANDLER) { return 1; }
	  #endif
	  return 0;
	}

#else
	#ifdef ENV_BEOS
	#include <kernel/OS.h>
	#else
	#include <pthread.h>
	#include <stdlib.h>
	#endif

	#include <errno.h>
	#include "GGType.h"

	#if defined(__linux__)
	#define PTHREAD_MUTEX_ERRORCHECK PTHREAD_MUTEX_ERRORCHECK_NP
	#endif

	#ifdef ENV_BEOS

	/* TODO : optimize the code and verify the returned values */

	WRes Thread_Create(CThread *thread, THREAD_FUNC_RET_TYPE (THREAD_FUNC_CALL_TYPE *startAddress)(void *), LPVOID parameter)
	{
		thread->_tid = spawn_thread((int32 (*)(void *))startAddress, "CThread", B_LOW_PRIORITY, parameter);
		if (thread->_tid >= B_OK) {
			resume_thread(thread->_tid);
		} else {
			thread->_tid = B_BAD_THREAD_ID;
		}
		thread->_created = 1;
		return 0; // SZ_OK;
	}

	WRes Thread_Wait(CThread *thread)
	{
	  int ret;

	  if (thread->_created == 0)
		return EINVAL;

	  if (thread->_tid >= B_OK)
	  {
		status_t exit_value;
		wait_for_thread(thread->_tid, &exit_value);
		thread->_tid = B_BAD_THREAD_ID;
	  } else {
		return EINVAL;
	  }

	  thread->_created = 0;

	  return 0;
	}

	WRes Thread_Close(CThread *thread)
	{
		if (!thread->_created) return SZ_OK;

		thread->_tid = B_BAD_THREAD_ID;
		thread->_created = 0;
		return SZ_OK;
	}


	WRes Event_Create(CEvent *p, XBOOL manualReset, int initialSignaled)
	{
	  p->_index_waiting = 0;
	  p->_manual_reset  = manualReset;
	  p->_state         = (initialSignaled ? XTRUE : XFALSE);
	  p->_created       = 1;
	  p->_sem           = create_sem(1,"event");
	  return 0;
	}

	WRes Event_Set(CEvent *p) {
	  int index;
	  acquire_sem(p->_sem);
	  p->_state = XTRUE;
	  for(index = 0 ; index < p->_index_waiting ; index++)
	  {
		 send_data(p->_waiting[index], '7zCN', NULL, 0);
	  }
	  p->_index_waiting = 0;
	  release_sem(p->_sem);
	  return 0;
	}

	WRes Event_Reset(CEvent *p) {
	  acquire_sem(p->_sem);
	  p->_state = XFALSE;
	  release_sem(p->_sem);
	  return 0;
	}

	WRes Event_Wait(CEvent *p) {
	  acquire_sem(p->_sem);
	  while (p->_state == XFALSE)
	  {
		thread_id sender;
		p->_waiting[p->_index_waiting++] = find_thread(NULL);
		release_sem(p->_sem);
		/* int msg = */ receive_data(&sender, NULL, 0);
		acquire_sem(p->_sem);
	  }
	  if (p->_manual_reset == XFALSE)
	  {
		 p->_state = XFALSE;
	  }
	  release_sem(p->_sem);
	  return 0;
	}

	WRes Event_Close(CEvent *p) {
	  if (p->_created)
	  {
		p->_created = 0;
		delete_sem(p->_sem);
	  }
	  return 0;
	}

	WRes Semaphore_Create(CSemaphore *p, UInt32 initiallyCount, UInt32 maxCount)
	{
	  p->_index_waiting = 0;
	  p->_count         = initiallyCount;
	  p->_maxCount      = maxCount;
	  p->_created       = 1;
	  p->_sem           = create_sem(1,"sem");
	  return 0;
	}

	WRes Semaphore_ReleaseN(CSemaphore *p, UInt32 releaseCount)
	{
	  UInt32 newCount;
	  int index;

	  if (releaseCount < 1) return EINVAL;

	  acquire_sem(p->_sem);
	  newCount = p->_count + releaseCount;
	  if (newCount > p->_maxCount)
	  {
		release_sem(p->_sem);
		return EINVAL;
	  }
	  p->_count = newCount;
	  for(index = 0 ; index < p->_index_waiting ; index++)
	  {
		 send_data(p->_waiting[index], '7zCN', NULL, 0);
	  }
	  p->_index_waiting = 0;
	  release_sem(p->_sem);
	  return 0;
	}

	WRes Semaphore_Wait(CSemaphore *p) {
	  acquire_sem(p->_sem);
	  while (p->_count < 1)
	  {
		thread_id sender;
		p->_waiting[p->_index_waiting++] = find_thread(NULL);
		release_sem(p->_sem);
		/* int msg = */ receive_data(&sender, NULL, 0);
		acquire_sem(p->_sem);
	  }
	  p->_count--;
	  release_sem(p->_sem);
	  return 0;
	}

	WRes Semaphore_Close(CSemaphore *p) {
	  if (p->_created)
	  {
		p->_created = 0;
		delete_sem(p->_sem);
	  }
	  return 0;
	}

	WRes CriticalSection_Init(CCriticalSection * lpCriticalSection)
	{
	  lpCriticalSection->_sem = create_sem(1,"cc");
	  return 0;
	}

	#else /* !ENV_BEOS */

	WRes Thread_Create(CThread *thread, THREAD_FUNC_RET_TYPE (THREAD_FUNC_CALL_TYPE *startAddress)(void *), LPVOID parameter)
	{
		pthread_attr_t attr;
		int ret;

		thread->_created = 0;

		ret = pthread_attr_init(&attr);
		if (ret) return ret;

		ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
		if (ret) return ret;

		ret = pthread_create(&thread->_tid, &attr, (void * (*)(void *))startAddress, parameter);

		/* ret2 = */ pthread_attr_destroy(&attr);

		if (ret) return ret;

		thread->_created = 1;

		return 0; // SZ_OK;
	}

	WRes Thread_Wait(CThread *thread)
	{
	  void *thread_return;
	  int ret;

	  if (thread->_created == 0)
		return EINVAL;

	  ret = pthread_join(thread->_tid,&thread_return);
	  thread->_created = 0;

	  return ret;
	}
	
	WRes Thread_Close(CThread *thread)
	{
		if (!thread->_created) return SZ_OK;

		pthread_detach(thread->_tid);
		thread->_tid = 0;
		thread->_created = 0;
		return SZ_OK;
	}

	#ifdef DEBUG_SYNCHRO

	#include <stdio.h>

	static void dump_error(int ligne,int ret,const char *text,void *param)
	{
	  printf("\n##T%d#ERROR2 (l=%d) %s : param=%p ret = %d (%s)##\n",(int)pthread_self(),ligne,text,param,ret,strerror(ret));
		// abort();
	}

	WRes Event_Create(CEvent *p, XBOOL manualReset, int initialSignaled)
	{
	  int ret;
	  pthread_mutexattr_t mutexattr;
	  memset(&mutexattr,0,sizeof(mutexattr));
	  ret = pthread_mutexattr_init(&mutexattr);
	  if (ret != 0) dump_error(__LINE__,ret,"Event_Create::pthread_mutexattr_init",&mutexattr);
	  ret = pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK);
	  if (ret != 0) dump_error(__LINE__,ret,"Event_Create::pthread_mutexattr_settype",&mutexattr);
	  ret = pthread_mutex_init(&p->_mutex,&mutexattr);
	  if (ret != 0) dump_error(__LINE__,ret,"Event_Create::pthread_mutexattr_init",&p->_mutex);
	  if (ret == 0)
	  {
		ret = pthread_cond_init(&p->_cond,0);
		if (ret != 0) dump_error(__LINE__,ret,"Event_Create::pthread_cond_init",&p->_cond);
		p->_manual_reset = manualReset;
		p->_state        = (initialSignaled ? XTRUE : XFALSE);
		p->_created = 1;
	  }
	  return ret;
	}

	WRes Event_Set(CEvent *p) {
	  int ret = pthread_mutex_lock(&p->_mutex);
	  if (ret != 0) dump_error(__LINE__,ret,"ES::pthread_mutex_lock",&p->_mutex);
	  if (ret == 0)
	  {
		p->_state = XTRUE;
		ret = pthread_cond_broadcast(&p->_cond);
		if (ret != 0) dump_error(__LINE__,ret,"ES::pthread_cond_broadcast",&p->_cond);
		if (ret == 0)
		{
		   ret = pthread_mutex_unlock(&p->_mutex);
		   if (ret != 0) dump_error(__LINE__,ret,"ES::pthread_mutex_unlock",&p->_mutex);
		}
	  }
	  return ret;
	}

	WRes Event_Reset(CEvent *p) {
	  int ret = pthread_mutex_lock(&p->_mutex);
	  if (ret != 0) dump_error(__LINE__,ret,"ER::pthread_mutex_lock",&p->_mutex);
	  if (ret == 0)
	  {
		p->_state = XFALSE;
		ret = pthread_mutex_unlock(&p->_mutex);
		if (ret != 0) dump_error(__LINE__,ret,"ER::pthread_mutex_unlock",&p->_mutex);
	  }
	  return ret;
	}

	WRes Event_Wait(CEvent *p) {
	  int ret = pthread_mutex_lock(&p->_mutex);
	  if (ret != 0) dump_error(__LINE__,ret,"EW::pthread_mutex_lock",&p->_mutex);
	  if (ret == 0)
	  {
		while ((p->_state == XFALSE) && (ret == 0))
		{
		   ret = pthread_cond_wait(&p->_cond, &p->_mutex);
		   if (ret != 0) dump_error(__LINE__,ret,"EW::pthread_cond_wait",&p->_mutex);
		}
		if (ret == 0)
		{
		   if (p->_manual_reset == XFALSE)
		   {
			 p->_state = XFALSE;
		   }
		   ret = pthread_mutex_unlock(&p->_mutex);
		   if (ret != 0) dump_error(__LINE__,ret,"EW::pthread_mutex_unlock",&p->_mutex);
		}
	  }
	  return ret;
	}

	WRes Event_Close(CEvent *p) {
	  if (p->_created)
	  {
		int ret;
		p->_created = 0;
		ret = pthread_mutex_destroy(&p->_mutex);
		if (ret != 0) dump_error(__LINE__,ret,"EC::pthread_mutex_destroy",&p->_mutex);
		ret = pthread_cond_destroy(&p->_cond);
		if (ret != 0) dump_error(__LINE__,ret,"EC::pthread_cond_destroy",&p->_cond);
	  }
	  return 0;
	}

	WRes Semaphore_Create(CSemaphore *p, UInt32 initiallyCount, UInt32 maxCount)
	{
	  int ret;
	  pthread_mutexattr_t mutexattr;
	  memset(&mutexattr,0,sizeof(mutexattr));
	  ret = pthread_mutexattr_init(&mutexattr);
	  if (ret != 0) dump_error(__LINE__,ret,"SemC::pthread_mutexattr_init",&mutexattr);
	  ret = pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK);
	  if (ret != 0) dump_error(__LINE__,ret,"SemC::pthread_mutexattr_settype",&mutexattr);
	  ret = pthread_mutex_init(&p->_mutex,&mutexattr);
	  if (ret != 0) dump_error(__LINE__,ret,"SemC::pthread_mutexattr_init",&p->_mutex);
	  if (ret == 0)
	  {
		ret = pthread_cond_init(&p->_cond,0);
		if (ret != 0) dump_error(__LINE__,ret,"SemC::pthread_cond_init",&p->_mutex);
		p->_count    = initiallyCount;
		p->_maxCount = maxCount;
		p->_created = 1;
	  }
	  return ret;
	}

	WRes Semaphore_ReleaseN(CSemaphore *p, UInt32 releaseCount)
	{
	  int ret;
	  if (releaseCount < 1) return EINVAL;

	  ret = pthread_mutex_lock(&p->_mutex);
	  if (ret != 0) dump_error(__LINE__,ret,"SemR::pthread_mutex_lock",&p->_mutex);
	  if (ret == 0)
	  {
		UInt32 newCount = p->_count + releaseCount;
		if (newCount > p->_maxCount)
		{
		  ret = pthread_mutex_unlock(&p->_mutex);
		  if (ret != 0) dump_error(__LINE__,ret,"SemR::pthread_mutex_unlock",&p->_mutex);
		  return EINVAL;
		}
		p->_count = newCount;
		ret = pthread_cond_broadcast(&p->_cond);
		if (ret != 0) dump_error(__LINE__,ret,"SemR::pthread_cond_broadcast",&p->_cond);
		if (ret == 0)
		{
		   ret = pthread_mutex_unlock(&p->_mutex);
		   if (ret != 0) dump_error(__LINE__,ret,"SemR::pthread_mutex_unlock",&p->_mutex);
		}
	  }
	  return ret;
	}

	WRes Semaphore_Wait(CSemaphore *p) {
	  int ret = pthread_mutex_lock(&p->_mutex);
	  if (ret != 0) dump_error(__LINE__,ret,"SemW::pthread_mutex_lock",&p->_mutex);
	  if (ret == 0)
	  {
		while ((p->_count < 1) && (ret == 0))
		{
		   ret = pthread_cond_wait(&p->_cond, &p->_mutex);
		   if (ret != 0) dump_error(__LINE__,ret,"SemW::pthread_cond_wait",&p->_mutex);
		}
		if (ret == 0)
		{
		  p->_count--;
		  ret = pthread_mutex_unlock(&p->_mutex);
		  if (ret != 0) dump_error(__LINE__,ret,"SemW::pthread_mutex_unlock",&p->_mutex);
		}
	  }
	  return ret;
	}

	WRes Semaphore_Close(CSemaphore *p) {
	  if (p->_created)
	  {
		int ret;
		p->_created = 0;
		ret = pthread_mutex_destroy(&p->_mutex);
		if (ret != 0) dump_error(__LINE__,ret,"Semc::pthread_mutex_destroy",&p->_mutex);
		ret = pthread_cond_destroy(&p->_cond);
		if (ret != 0) dump_error(__LINE__,ret,"Semc::pthread_cond_destroy",&p->_cond);
	  }
	  return 0;
	}

	WRes CriticalSection_Init(CCriticalSection * lpCriticalSection)
	{
		if (lpCriticalSection)
		{
			int ret;
			pthread_mutexattr_t mutexattr;
			memset(&mutexattr,0,sizeof(mutexattr));
			ret = pthread_mutexattr_init(&mutexattr);
			if (ret != 0) dump_error(__LINE__,ret,"CS I::pthread_mutexattr_init",&mutexattr);
			ret = pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK);
			if (ret != 0) dump_error(__LINE__,ret,"CS I::pthread_mutexattr_settype",&mutexattr);
			ret = pthread_mutex_init(&lpCriticalSection->_mutex,&mutexattr);
			if (ret != 0) dump_error(__LINE__,ret,"CS I::pthread_mutexattr_init",&lpCriticalSection->_mutex);
			return ret;
		}
		return EINTR;
	}

	void CriticalSection_Enter(CCriticalSection * lpCriticalSection)
	{
		if (lpCriticalSection)
		{
			int ret = pthread_mutex_lock(&(lpCriticalSection->_mutex));
					if (ret != 0) dump_error(__LINE__,ret,"CS::pthread_mutex_lock",&(lpCriticalSection->_mutex));
		}
	}

	void CriticalSection_Leave(CCriticalSection * lpCriticalSection)
	{
		if (lpCriticalSection)
		{
			int ret = pthread_mutex_unlock(&(lpCriticalSection->_mutex));
					if (ret != 0) dump_error(__LINE__,ret,"CS::pthread_mutex_unlock",&(lpCriticalSection->_mutex));
		}
	}

	void CriticalSection_Delete(CCriticalSection * lpCriticalSection)
	{
		if (lpCriticalSection)
		{
			int ret = pthread_mutex_destroy(&(lpCriticalSection->_mutex));
					if (ret != 0) dump_error(__LINE__,ret,"CS::pthread_mutex_destroy",&(lpCriticalSection->_mutex));
		}
	}

	#else

	WRes Event_Create(CEvent *p, XBOOL manualReset, int initialSignaled)
	{
	  pthread_mutex_init(&p->_mutex,0);
	  pthread_cond_init(&p->_cond,0);
	  p->_manual_reset = manualReset;
	  p->_state        = (initialSignaled ? XTRUE : XFALSE);
	  p->_created = 1;
	  return 0;
	}

	WRes Event_Set(CEvent *p) {
	  pthread_mutex_lock(&p->_mutex);
	  p->_state = XTRUE;
	  pthread_cond_broadcast(&p->_cond);
	  pthread_mutex_unlock(&p->_mutex);
	  return 0;
	}

	WRes Event_Reset(CEvent *p) {
	  pthread_mutex_lock(&p->_mutex);
	  p->_state = XFALSE;
	  pthread_mutex_unlock(&p->_mutex);
	  return 0;
	}

	WRes Event_Wait(CEvent *p) {
	  pthread_mutex_lock(&p->_mutex);
	  while (p->_state == XFALSE)
	  {
		 pthread_cond_wait(&p->_cond, &p->_mutex);
	  }
	  if (p->_manual_reset == XFALSE)
	  {
		 p->_state = XFALSE;
	  }
	  pthread_mutex_unlock(&p->_mutex);
	  return 0;
	}

	WRes Event_Close(CEvent *p) {
	  if (p->_created)
	  {
		p->_created = 0;
		pthread_mutex_destroy(&p->_mutex);
		pthread_cond_destroy(&p->_cond);
	  }
	  return 0;
	}

	WRes Semaphore_Create(CSemaphore *p, UInt32 initiallyCount, UInt32 maxCount)
	{
	  pthread_mutex_init(&p->_mutex,0);
	  pthread_cond_init(&p->_cond,0);
	  p->_count    = initiallyCount;
	  p->_maxCount = maxCount;
	  p->_created  = 1;
	  return 0;
	}

	WRes Semaphore_ReleaseN(CSemaphore *p, UInt32 releaseCount)
	{
	  UInt32 newCount;

	  if (releaseCount < 1) return EINVAL;

	  pthread_mutex_lock(&p->_mutex);

	  newCount = p->_count + releaseCount;
	  if (newCount > p->_maxCount)
	  {
		pthread_mutex_unlock(&p->_mutex);
		return EINVAL;
	  }
	  p->_count = newCount;
	  pthread_cond_broadcast(&p->_cond);
	  pthread_mutex_unlock(&p->_mutex);
	  return 0;
	}

	WRes Semaphore_Wait(CSemaphore *p) {
	  pthread_mutex_lock(&p->_mutex);
	  while (p->_count < 1)
	  {
		 pthread_cond_wait(&p->_cond, &p->_mutex);
	  }
	  p->_count--;
	  pthread_mutex_unlock(&p->_mutex);
	  return 0;
	}

	WRes Semaphore_Close(CSemaphore *p) {
	  if (p->_created)
	  {
		p->_created = 0;
		pthread_mutex_destroy(&p->_mutex);
		pthread_cond_destroy(&p->_cond);
	  }
	  return 0;
	}

	WRes CriticalSection_Init(CCriticalSection * lpCriticalSection)
	{
		return pthread_mutex_init(&(lpCriticalSection->_mutex),0);
	}

	#endif /* DEBUG_SYNCHRO */

	#endif /* ENV_BEOS */

	WRes ManualResetEvent_Create(CManualResetEvent *p, int initialSignaled)
	  { return Event_Create(p, XTRUE, initialSignaled); }

	WRes ManualResetEvent_CreateNotSignaled(CManualResetEvent *p)
	  { return ManualResetEvent_Create(p, 0); }

	WRes AutoResetEvent_Create(CAutoResetEvent *p, int initialSignaled)
	  { return Event_Create(p, XFALSE, initialSignaled); }
	WRes AutoResetEvent_CreateNotSignaled(CAutoResetEvent *p)
	  { return AutoResetEvent_Create(p, 0); }

#endif
