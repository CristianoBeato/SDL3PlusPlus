
#ifndef __SDL_MUTEX_HPP__
#define __SDL_MUTEX_HPP__

#include <SDL3/SDL_mutex.h>

// SDL_CreateMutex
// SDL_DestroyMutex
// SDL_LockMutex
// SDL_TryLockMutex
// SDL_UnlockMutex
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

// SDL_CreateCondition
// SDL_DestroyCondition
// SDL_SignalCondition
// SDL_BroadcastCondition
// SDL_WaitCondition
// SDL_WaitConditionTimeout
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

// SDL_CreateRWLock
// SDL_DestroyRWLock
// SDL_LockRWLockForReading
// SDL_LockRWLockForWriting
// SDL_TryLockRWLockForReading
// SDL_TryLockRWLockForWriting
// SDL_UnlockRWLock
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

// SDL_CreateSemaphore
// SDL_DestroySemaphore
// SDL_WaitSemaphore
// SDL_TryWaitSemaphore
// SDL_WaitSemaphoreTimeout
// SDL_SignalSemaphore
// SDL_GetSemaphoreValue
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

// SDL_ShouldInit
// SDL_ShouldQuit
// SDL_SetInitialized
class SDLInitState
{
public:
    SDLInitState( void )
    {
        initState = new SDL_InitState();
    }

    ~SDLInitState( void )
    {
        SAFE_DELETE( initState );
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

