
#ifndef __SDL_THREAD_HPP__
#define __SDL_THREAD_HPP__

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_thread.h>

class SDLThread
{
public:
    SDLThread( void ) : thread( nullptr )
    {
    }

    SDLThread( SDL_Thread* hnd ) : thread( hnd )
    {
    }

    ~SDLThread( void )
    {
    }

    inline bool Create( int (SDLCALL *fn )(void*), const char *name, void *data )
    {
        thread = SDL_CreateThread( fn, name, data );
        return thread != nullptr;
    }
    
    inline bool CreateWithProperties( const SDL_PropertiesID properties )
    {
        thread = SDL_CreateThreadWithProperties( properties );
        return thread != nullptr;
    }

    inline void Detach( void )
    {
        SDL_DetachThread( thread );
    }

    inline void Wait( int* status = nullptr ) const
    {
        SDL_WaitThread( thread, status );
    }

    inline const char* GetName( void ) const
    {
        return SDL_GetThreadName( thread );
    }
    
    inline SDL_ThreadID GetID( void ) const
    {
        return SDL_GetThreadID( thread );
    }
    
    inline SDL_ThreadState GetState( void ) const
    {
        return SDL_GetThreadState( thread );
    }

private:
    SDL_Thread*     thread;
};

#endif //!__SDL_THREAD_HPP__