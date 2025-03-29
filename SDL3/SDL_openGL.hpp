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
#ifndef __SDL_OPENGL_HPP__
#define __SDL_OPENGL_HPP__

#include <SDL3/SDL_video.h>

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