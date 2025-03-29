
#ifndef __SDL_OPENGL_HPP__
#define __SDL_OPENGL_HPP__

#include <SDL3/SDL_video.h>

// SDL_GL_CreateContext
// SDL_GL_DestroyContext
// SDL_GL_MakeCurrent
// SDL_GL_SwapWindow

// SDL_GL_GetCurrentContext
// SDL_GL_GetProcAddress
// SDL_GL_LoadLibrary
// SDL_GL_UnloadLibrary

// SDL_GL_ResetAttributes
// SDL_GL_SetAttribute
// SDL_GL_GetAttribute

// SDL_EGL_SetAttributeCallbacks
// SDL_EGL_GetWindowSurface
// SDL_EGL_GetCurrentConfig
// SDL_EGL_GetCurrentDisplay
// SDL_EGL_GetProcAddress

class SDLOpenGL
{
public:
    SDLOpenGL( void ) : 
        m_handle( nullptr ),
        m_whandle( nullptr )
    {
    }

    ~SDLOpenGL( void )
    {
    }

    void Create( SDL_Window* win )
    {
        m_whandle = win;
        m_handle = SDL_GL_CreateContext( m_whandle );
        if ( m_handle == nullptr )
            throw std::runtime_error( SDL_GetError() );
    }
    
    void Destroy( void )
    {
        if ( m_handle != nullptr )
        {
            SDL_GL_DestroyContext( m_handle );
            m_handle = nullptr;
        }

        m_whandle = nullptr;
    }

    inline void MakeCurrent( SDL_Window* win )
    {
        m_whandle = win;
        SDL_GL_MakeCurrent( m_whandle, m_handle );
    }

    inline void Swap( void )
    {
        SDL_GL_SwapWindow( m_whandle );
    }

private:
    SDL_Window*     m_whandle;
    SDL_GLContext   m_handle;
};

#endif __SDL_OPENGL_HPP__