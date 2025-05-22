/*
===========================================================================================
    This file is part of SDL3++.

    Copyright (c) 2025 Cristiano B. Santos <cristianobeato_dm@hotmail.com>
    Contributor(s): none yet.

-------------------------------------------------------------------------------------------
    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:
  
1.  The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required. 
2.  Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.
3.  This notice may not be removed or altered from any source distribution.

===========================================================================================
*/
#ifndef __SDL_MUTEX_HPP__
#define __SDL_MUTEX_HPP__

#include <SDL3/SDL_mutex.h>

namespace SDL
{
/*
==================================================================
SDLMutex
==================================================================
    This class is a wrapper around SDL mutexes. It provides a simple
    interface for creating, destroying, locking, and unlocking mutexes.
    It also provides a way to check if the mutex is valid.

    Example usage:
        SDLMutex mutex;
        if (mutex.Create())
        {
            // Use the mutex
            mutex.Lock();
            // Critical section
            mutex.Unlock();
            mutex.Destroy();
        }
==================================================================
*/
    class Mutex
    {
    public:
        Mutex( void ) : mutex( nullptr )
        {
        }

        Mutex( SDL_Mutex* mtx ) : mutex( mtx )
        {
        }

        Mutex( const Mutex &mtx ) : mutex( mtx.mutex )
        {
        }

        ~Mutex( void )
        {
            mutex = nullptr;
        }

        SDL_INLINE bool Create( void )
        {
            mutex = SDL_CreateMutex();
            return mutex != nullptr;
        }

        //
        SDL_INLINE void Destroy( void )
        {
            if( mutex != nullptr )
            {
                SDL_DestroyMutex( mutex );
                mutex = nullptr;
            }
        }

        //
        SDL_INLINE void Lock( void ) const
        {
            SDL_LockMutex( mutex );
        }

        //
        SDL_INLINE bool TryLock( void ) const
        {
            return SDL_TryLockMutex( mutex );
        }

        //
        SDL_INLINE void Unlock( void ) const
        {
            SDL_UnlockMutex( mutex );
        }

        SDL_INLINE operator SDL_Mutex*( void ) const{ return mutex; }
        SDL_INLINE SDL_Mutex*   GetHandler( void ) const { return mutex; }

    private:
        SDL_Mutex* mutex;
    };

/*
==================================================================
SDLCondition
==================================================================
    This class is a wrapper around SDL condition variables. It provides a simple
    interface for creating, destroying, signaling, and waiting on condition
    variables.

    Example usage:
        SDLCondition cond;
        if (cond.Create())
        {
            // Use the condition variable
            cond.Signal();
            cond.Wait(&mutex);
            cond.Destroy();
        }
==================================================================
*/
    class Condition
    {
    public:
        Condition( void ) : condition( nullptr ) {}
        Condition( SDL_Condition* cnd ) : condition( cnd ) {}
        Condition( const Condition &cnd ) : condition( cnd.condition ) {}
        ~Condition( void ){ condition = nullptr; }

        SDL_INLINE bool Create( void )
        {
            condition = SDL_CreateCondition();
            return condition != nullptr;
        }

        SDL_INLINE void Destroy( void )
        {
            SDL_DestroyCondition( condition );
        }

        SDL_INLINE void Signal( void )
        {
            SDL_SignalCondition( condition );
        }

        SDL_INLINE void Broadcast( void )
        {
            SDL_BroadcastCondition( condition );
        }

        SDL_INLINE void Wait( const Mutex &mutex )
        {
            SDL_WaitCondition( condition, mutex );
        }

        SDL_INLINE void WaitTimeout( Mutex &mutex, Sint32 timeoutMS )
        {
            SDL_WaitConditionTimeout( condition, mutex, timeoutMS );
        }

        SDL_INLINE operator SDL_Condition*( void ) const { return condition; }
        SDL_INLINE SDL_Condition* GetHandle( void ) const { return condition; }

    private:
        SDL_Condition* condition;
    };

/*
==================================================================
SDLRWLock
==================================================================
    This class is a wrapper around SDL read-write locks. It provides a simple
    interface for creating, destroying, locking, and unlocking read-write locks.

    Example usage:
        SDLRWLock rwlock;
        if (rwlock.Create())
        {
            // Use the read-write lock
            rwlock.LockForReading();
            // Critical section for reading
            rwlock.Unlock();
            rwlock.Destroy();
        }
==================================================================
*/
    class RWLock
    {
    public:
        RWLock( void ) : rwlock( nullptr )
        {
        }

        RWLock( SDL_RWLock* _rwlock ) : rwlock( _rwlock )
        {
        }

        RWLock( const RWLock &_rwlock ) : rwlock( _rwlock.rwlock )
        {
        }

        ~RWLock( void )
        {
            rwlock = nullptr;
        }

        SDL_INLINE bool Create( void )
        {
            rwlock = SDL_CreateRWLock();
            return rwlock != nullptr;
        }

        SDL_INLINE void Destroy( void )
        {
            if ( rwlock != nullptr )
            {
                SDL_DestroyRWLock( rwlock );
                rwlock = nullptr;
            }
        }

        SDL_INLINE void LockForReading( void ) const
        {
            SDL_LockRWLockForReading( rwlock );
        }

        SDL_INLINE void LockForWriting( void ) const
        {
            SDL_LockRWLockForWriting( rwlock );
        }

        SDL_INLINE bool TryLockForReading( void ) const
        {
            return SDL_TryLockRWLockForReading( rwlock );
        }

        SDL_INLINE bool TryLockForWriting( void ) const
        {
            return SDL_TryLockRWLockForWriting( rwlock );
        }

        SDL_INLINE void Unlock( void ) const
        {
            SDL_UnlockRWLock( rwlock );
        }

        operator SDL_RWLock*( void ) const { return rwlock; }
        SDL_RWLock* GetHandle( void ) const { return rwlock; }

    private:
        SDL_RWLock* rwlock;
    };

/*
==================================================================
SDLSemaphore
==================================================================
    This class is a wrapper around SDL semaphores. It provides a simple
    interface for creating, destroying, waiting, signaling, and checking
    the value of semaphores.

    Example usage:
        SDLSemaphore semaphore;
        if (semaphore.Create(1))
        {
            // Use the semaphore
            semaphore.Wait();
            // Critical section
            semaphore.Signal();
            semaphore.Destroy();
        }
==================================================================
*/
    class Semaphore
    {
    public:
        Semaphore( void ) : semaphore( nullptr )
        {
        }

        Semaphore( SDL_Semaphore *sem ) : semaphore( sem )
        {
        }

        Semaphore( const Semaphore &sem ) : semaphore( sem.semaphore )
        {
        }

        ~Semaphore( void )
        {
            semaphore = nullptr;
        }

        SDL_INLINE bool Create( const Uint32 initalVal )
        {
            semaphore = SDL_CreateSemaphore( initalVal );
            return semaphore != nullptr;
        }

        SDL_INLINE void Destroy( void )
        {
            if ( semaphore != nullptr )
            {
                SDL_DestroySemaphore( semaphore );
                semaphore = nullptr;
            }
        }

        SDL_INLINE void Wait( void ) const
        {
            SDL_WaitSemaphore( semaphore );
        }

        SDL_INLINE bool TryWait( void ) const
        {
            return SDL_TryWaitSemaphore( semaphore );
        }

        SDL_INLINE bool WaitTimeout( Sint32 timeoutMS ) const
        {
            return SDL_WaitSemaphoreTimeout( semaphore, timeoutMS );
        }

        SDL_INLINE void Signal( void ) const
        {
            SDL_SignalSemaphore( semaphore );
        }

        SDL_INLINE Uint32 GetValue( void ) const
        {
            return SDL_GetSemaphoreValue( semaphore );
        }

        operator SDL_Semaphore*( void ) const { return semaphore; }
        SDL_Semaphore* GetHandler( void ) const { return semaphore; }

    private:
        SDL_Semaphore* semaphore; 
    };

/*
==================================================================
SDLInitState
==================================================================
    Example usage:
        SDLInitState initState;
        if (initState.ShouldInit())
        {
            // Use the init state
            initState.SetInitialized(true);
            initState.ShouldQuit();
            initState.Destroy();
        }
==================================================================  
*/
    class InitState
    {
    public:
        InitState( void )
        {
            initState = new SDL_InitState();
        }

        InitState( SDL_InitState*  _initState ) : initState( _initState )
        {
        }

        InitState( const InitState &ref ) : initState( ref.initState )
        {
        }

        ~InitState( void )
        {
            if ( initState != nullptr )
            {
                delete initState;
                initState = nullptr;
            }        
        }
        
        SDL_INLINE bool ShouldInit( void )
        {
            return SDL_ShouldInit( initState );
        }
        
        SDL_INLINE bool ShouldQuit( void )
        {
            return SDL_ShouldQuit( initState );
        }
        
        SDL_INLINE void SetInitialized( const bool initialized )
        {
            SDL_SetInitialized( initState, initialized );
        }

    private:
        SDL_InitState*  initState;
    };
};
#endif // !__SDL_MUTEX_HPP__

