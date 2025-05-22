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
        SDL::Thread thread;
        if (thread.Create(MyThreadFunction, "MyThread", nullptr))
        {
            // wait for the thread to finish
            thread.Wait();
        }
==================================================================
*/
namespace SDL
{
    class Thread
    {
    public:
        Thread( SDL_Thread* hnd ) : thread( hnd ){}
        Thread( const Thread &ref  ) : thread( ref.thread ) {}
        Thread( void ) : thread( nullptr ){ }
        ~Thread( void ){}

        /// @brief The actual entry point for SDL_CreateThread.
        /// @param fn the SDL_ThreadFunction function to call in the new thread
        /// @param name the name of the thread
        /// @param data a pointer that is passed to `fn`
        /// @return true on success, false on error 
        SDL_INLINE bool Create( SDL_ThreadFunction fn, const char *name, void *data )
        {
            thread = SDL_CreateThread( fn, name, data );
            return thread != nullptr;
        }
        

        /// @brief The actual entry point for SDL_CreateThreadWithProperties
        /// @param properties the properties to use 
        /// @return true on success, false on error 
        SDL_INLINE bool CreateWithProperties( const SDL_PropertiesID properties )
        {
            thread = SDL_CreateThreadWithProperties( properties );
            return thread != nullptr;
        }

        /// @brief Let a thread clean up on exit without intervention
        SDL_INLINE void Detach( void )
        {
            SDL_DetachThread( thread );
        }

        /// @brief Wait for a thread ( that is not detach ) to finish
        /// @param status a pointer filled in with the value returned from the thread
        /// function by its 'return', or -1 if the thread has been
        /// detached or isn't valid, may be NULL.
        SDL_INLINE void Wait( int* status = nullptr ) const
        {
            SDL_WaitThread( thread, status );
        }

        /// @brief Acquire thread name
        /// @return a cstring thread name
        SDL_INLINE const char* GetName( void ) const
        {
            return SDL_GetThreadName( thread );
        }
        
        /// @brief get the Thread ID 
        /// @return the ID of the thread handler 
        SDL_INLINE SDL_ThreadID GetID( void ) const
        {
            return SDL_GetThreadID( thread );
        }
        
        /// @brief Get the current state of a thread.
        /// @return the current state of a thread, or SDL_THREAD_UNKNOWN if the thread isn't valid.
        SDL_INLINE SDL_ThreadState GetState( void ) const
        {
            return SDL_GetThreadState( thread );
        }

        SDL_INLINE operator bool( void ) const { return thread != nullptr; }
        
        SDL_INLINE operator SDL_Thread*( void ) const { return thread; }

        SDL_Thread*  GetHandle( void ) const { return thread; } 

    private:
        SDL_Thread*     thread;
    };
};
#endif //!__SDL_THREAD_HPP__