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

#ifndef __LOADSO_HPP__
#define __LOADSO_HPP__

#include <SDL3/SDL_loadso.h>

namespace SDL
{
    class SharedObject
    {
    public:
        SharedObject( void ) : sharedObject( nullptr ) {};
        ~SharedObject( void ){}
        bool    Load( const char* sofile )
        {
            sharedObject = SDL_LoadObject( sofile );
            return sharedObject != nullptr;
        }

        void Unload( void )
        {
            if ( sharedObject != nullptr )
            {
                SDL_UnloadObject( sharedObject );
                sharedObject = nullptr;
            }
            
        }

        template<typename t_>
        t_ Function( const char* fnName ) const 
        {
            return reinterpret_cast<t_>( SDL_LoadFunction( sharedObject , fnName ) )
        }

    private:
        SDL_SharedObject*    sharedObject;    
    };
}
#endif //!__LOADSO_HPP__