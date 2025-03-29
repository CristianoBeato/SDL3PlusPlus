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
class SDLMutex
{
public:
    SDLMutex( void ) : mutex( nullptr )
    {
    }

    ~SDLMutex( void )
    {
    }

    inline bool Create( void )
    {
        mutex = SDL_CreateMutex();
        return mutex != nullptr;
    }

    //
    inline void Destroy( void )
    {
        if( mutex != nullptr )
        {
            SDL_DestroyMutex( mutex );
            mutex = nullptr;
        }
    }

    //
    inline void Lock( void ) const
    {
        SDL_LockMutex( mutex );
    }

    //
    inline bool TryLock( void ) const
    {
        return SDL_TryLockMutex( mutex );
    }

    //
    inline void Unlock( void ) const
    {
        SDL_UnlockMutex( mutex );
    }

    inline operator SDL_Mutex*( void ) const{ return mutex; }
    inline SDL_Mutex*   GetHandler( void ) const { return mutex; }

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
class SDLCondition
{
public:
    SDLCondition( void );
    ~SDLCondition( void );

    inline bool Create( void )
    {
        condition = SDL_CreateCondition();
        return condition != nullptr;
    }

    inline void Destroy( void )
    {
        SDL_DestroyCondition( condition );
    }

    inline void Signal( void )
    {
        SDL_SignalCondition( condition );
    }

    inline void Broadcast( void )
    {
        SDL_BroadcastCondition( condition );
    }

    inline void Wait( SDL_Mutex * mutex )
    {
        SDL_WaitCondition( condition, mutex );
    }

    inline void WaitTimeout( SDL_Mutex * mutex, Sint32 timeoutMS )
    {
        SDL_WaitConditionTimeout( condition, mutex, timeoutMS );
    }

    inline operator SDL_Condition*( void ) const { return condition; }
    inline SDL_Condition* GetHandle( void ) const { return condition; }

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
class SDLRWLock
{
public:
    SDLRWLock( void ) : rwlock( nullptr )
    {
    }

    ~SDLRWLock( void )
    {
    }

    inline bool Create( void )
    {
        rwlock = SDL_CreateRWLock();
        return rwlock != nullptr;
    }

    inline void Destroy( void )
    {
        if ( rwlock != nullptr )
        {
            SDL_DestroyRWLock( rwlock );
            rwlock = nullptr;
        }
    }

    inline void LockForReading( void ) const
    {
        SDL_LockRWLockForReading( rwlock );
    }

    inline void LockForWriting( void ) const
    {
        SDL_LockRWLockForWriting( rwlock );
    }

    inline bool TryLockForReading( void ) const
    {
        return SDL_TryLockRWLockForReading( rwlock );
    }

    inline bool TryLockForWriting( void ) const
    {
        return SDL_TryLockRWLockForWriting( rwlock );
    }

    inline void Unlock( void ) const
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
class SDLSemaphore
{
public:
    SDLSemaphore( void ) : semaphore( nullptr )
    {
    }

    ~SDLSemaphore( void )
    {
    }

    inline bool Create( const Uint32 initalVal )
    {
        semaphore = SDL_CreateSemaphore( initalVal );
        return semaphore != nullptr;
    }

    inline void Destroy( void )
    {
        if ( semaphore != nullptr )
        {
            SDL_DestroySemaphore( semaphore );
            semaphore = nullptr;
        }
    }

    inline void Wait( void ) const
    {
        SDL_WaitSemaphore( semaphore );
    }

    inline bool TryWait( void ) const
    {
        return SDL_TryWaitSemaphore( semaphore );
    }

    inline bool WaitTimeout( Sint32 timeoutMS ) const
    {
        return SDL_WaitSemaphoreTimeout( semaphore, timeoutMS );
    }

    inline void Signal( void ) const
    {
        SDL_SignalSemaphore( semaphore );
    }

    inline Uint32 GetValue( void ) const
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
class SDLInitState
{
public:
    SDLInitState( void )
    {
        initState = new SDL_InitState();
    }

    ~SDLInitState( void )
    {
        if ( initState != nullptr )
        {
            delete initState;
            initState = nullptr;
        }        
    }
    
    inline bool ShouldInit( void )
    {
        return SDL_ShouldInit( initState );
    }
    
    inline bool ShouldQuit( void )
    {
        return SDL_ShouldQuit( initState );
    }
    
    inline void SetInitialized( const bool initialized )
    {
        SDL_SetInitialized( initState, initialized );
    }

private:
    SDL_InitState*  initState;
};

#endif // !__SDL_MUTEX_HPP__

