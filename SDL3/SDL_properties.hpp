
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

#ifndef __SDL_THREAD_PROPERTIES_HPP__
#define __SDL_THREAD_PROPERTIES_HPP__

#include <SDL3/SDL_properties.h>

// SDL_GetGlobalProperties

// SDL_CreateProperties
// SDL_DestroyProperties
// SDL_CopyProperties
// SDL_LockProperties
// SDL_UnlockProperties
// SDL_SetPointerPropertyWithCleanup
// SDL_SetPointerProperty
// SDL_SetStringProperty
// SDL_SetNumberProperty
// SDL_SetFloatProperty
// SDL_SetBooleanProperty
// SDL_HasProperty
// SDL_GetPropertyType
// SDL_GetPointerProperty
// SDL_GetStringProperty
// SDL_GetNumberProperty
// SDL_GetFloatProperty
// SDL_GetBooleanProperty
// SDL_ClearProperty
// SDL_EnumerateProperties

class SDLProperties
{
public:
    SDLProperties( void ) : properties( 0 )
    {
    }
    
    ~SDLProperties( void )
    {
    }

    SDL_INLINE void CreateProperties( void )
    {
        properties = SDL_CreateProperties();
    }

    SDL_INLINE void DestroyProperties( void )
    {
        SDL_DestroyProperties( properties );
        properties = 0;
    }

    SDL_INLINE bool CopyProperties( const SDLProperties &prop )
    {
        return SDL_CopyProperties( properties, prop.properties );
    }

    SDL_INLINE bool LockProperties( void ) const
    {
        return SDL_LockProperties( properties );
    }

    SDL_INLINE bool UnlockProperties( void )
    {
        SDL_UnlockProperties( properties );
    }

    SDL_INLINE bool SetPointerPropertyWithCleanup( const char *name, void *value, SDL_CleanupPropertyCallback cleanup, void *userdata )
    {
        return SDL_SetPointerPropertyWithCleanup( properties, name, value, cleanup, userdata );
    }

    SDL_INLINE bool SetPointerProperty( const char *name, void *value )
    {
        return SDL_SetPointerProperty( properties, name, value );
    }

    SDL_INLINE bool SetStringProperty( const char *name, const char *value ) 
    {
        return SDL_SetStringProperty( properties, name, value );
    }

    SDL_INLINE bool SetNumberProperty( const char *name, const Sint64 value )
    {
        return SDL_SetNumberProperty( properties, name, value );
    }

    SDL_INLINE bool SetFloatProperty( const char *name, const float value )
    {
        return SDL_SetFloatProperty( properties, name, value );
    }

    SDL_INLINE bool SetBooleanProperty( const char *name, const bool value )
    {
        return ( properties, name, value );
    }

    SDL_INLINE bool HasProperty( const char* name ) const
    {
        return SDL_HasProperty( properties, name );
    }

    SDL_INLINE SDL_PropertyType GetPropertyType( const char* name ) const
    {
        return SDL_GetPropertyType( properties, name );
    }

    SDL_INLINE void* GetPointerProperty( const char *name, void *default_value ) const
    {
        return SDL_GetPointerProperty( properties, name, default_value );
    }

    SDL_INLINE const char* GetStringProperty( const char *name, const char *default_value ) const
    {
        return SDL_GetStringProperty( properties, name, default_value );
    }

    SDL_INLINE Sint64 GetNumberProperty( const char *name, Sint64 default_value ) const
    {
        return SDL_GetNumberProperty( properties, name, default_value );
    }

    SDL_INLINE float GetFloatProperty( const char *name, const float default_value ) const
    {
        return SDL_GetFloatProperty( properties, name, default_value );
    }

    SDL_INLINE bool GetBooleanProperty( const char *name, const bool default_value ) const
    {
        return SDL_GetBooleanProperty( properties, name, default_value );
    }

    SDL_INLINE bool ClearProperty( const char* name )
    {
        return SDL_ClearProperty( properties, name );
    }

    SDL_INLINE bool EnumerateProperties( SDL_EnumeratePropertiesCallback callback, void *userdata )
    {
        return SDL_EnumerateProperties( properties, callback, userdata );
    }

    SDL_INLINE operator SDL_PropertiesID( void ) const { return properties; }

    SDL_PropertiesID  GetHandle( void ) const { return properties; } 

private:
    SDL_PropertiesID properties;
};

#endif //!__SDL_THREAD_PROPERTIES_HPP__