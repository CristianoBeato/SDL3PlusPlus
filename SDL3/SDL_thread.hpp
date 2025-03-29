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
#ifndef __SDL_THREAD_HPP__
#define __SDL_THREAD_HPP__

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_thread.h>

/*
==================================================================
SDLThread
==================================================================
    This class is a wrapper around SDL threads. It provides a simple
    interface for creating, destroying, and managing threads.
    
    Example usage:
        SDLThread thread;
        if (thread.Create(MyThreadFunction, "MyThread", nullptr))
        {
            // wait for the thread to finish
            thread.Wait();
        }
==================================================================
*/
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