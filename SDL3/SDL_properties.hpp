
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

class SDLProperties
{
public:
    SDLProperties( void ) : properties( 0 )
    {
    }
    
    ~SDLProperties( void )
    {
    }

    /// @brief Create a group of properties
    SDL_INLINE void CreateProperties( void )
    {
        properties = SDL_CreateProperties();
    }

    /// @brief Destroy a group of properties.
    SDL_INLINE void DestroyProperties( void )
    {
        SDL_DestroyProperties( properties );
        properties = 0;
    }

    /// @brief Copy a group of properties.
    /// @param prop the properties to copy.
    /// @return true on success or false on failure
    SDL_INLINE bool CopyProperties( const SDLProperties &prop )
    {
        return SDL_CopyProperties( prop.properties, properties );
    }

    /// @brief Lock a group of properties
    /// @return true on success or false on failure
    SDL_INLINE bool LockProperties( void ) const
    {
        return SDL_LockProperties( properties );
    }

    /// @brief Unlock a group of properties.
    SDL_INLINE void UnlockProperties( void )
    {
        SDL_UnlockProperties( properties );
    }

    /// @brief 
    /// @param name 
    /// @param value 
    /// @param cleanup 
    /// @param userdata 
    /// @return 
    SDL_INLINE bool SetPointerPropertyWithCleanup( const char *name, void *value, SDL_CleanupPropertyCallback cleanup, void *userdata )
    {
        return SDL_SetPointerPropertyWithCleanup( properties, name, value, cleanup, userdata );
    }

    /// @brief 
    /// @param name 
    /// @param value 
    /// @return 
    SDL_INLINE bool SetPointerProperty( const char *name, void *value )
    {
        return SDL_SetPointerProperty( properties, name, value );
    }

    /// @brief 
    /// @param name 
    /// @param value 
    /// @return 
    SDL_INLINE bool SetStringProperty( const char *name, const char *value ) 
    {
        return SDL_SetStringProperty( properties, name, value );
    }

    /// @brief 
    /// @param name 
    /// @param value 
    /// @return 
    SDL_INLINE bool SetNumberProperty( const char *name, const Sint64 value )
    {
        return SDL_SetNumberProperty( properties, name, value );
    }

    /// @brief 
    /// @param name 
    /// @param value 
    /// @return 
    SDL_INLINE bool SetFloatProperty( const char *name, const float value )
    {
        return SDL_SetFloatProperty( properties, name, value );
    }

    /// @brief 
    /// @param name 
    /// @param value 
    /// @return 
    SDL_INLINE bool SetBooleanProperty( const char *name, const bool value )
    {
        return ( properties, name, value );
    }

    /// @brief 
    /// @param name 
    /// @return 
    SDL_INLINE bool HasProperty( const char* name ) const
    {
        return SDL_HasProperty( properties, name );
    }

    /// @brief 
    /// @param name 
    /// @return 
    SDL_INLINE SDL_PropertyType GetPropertyType( const char* name ) const
    {
        return SDL_GetPropertyType( properties, name );
    }

    /// @brief 
    /// @param name 
    /// @param default_value 
    /// @return 
    SDL_INLINE void* GetPointerProperty( const char *name, void *default_value ) const
    {
        return SDL_GetPointerProperty( properties, name, default_value );
    }

    /// @brief 
    /// @param name 
    /// @param default_value 
    /// @return 
    SDL_INLINE const char* GetStringProperty( const char *name, const char *default_value ) const
    {
        return SDL_GetStringProperty( properties, name, default_value );
    }

    /// @brief 
    /// @param name 
    /// @param default_value 
    /// @return 
    SDL_INLINE Sint64 GetNumberProperty( const char *name, Sint64 default_value ) const
    {
        return SDL_GetNumberProperty( properties, name, default_value );
    }

    /// @brief 
    /// @param name 
    /// @param default_value 
    /// @return 
    SDL_INLINE float GetFloatProperty( const char *name, const float default_value ) const
    {
        return SDL_GetFloatProperty( properties, name, default_value );
    }

    /// @brief 
    /// @param name 
    /// @param default_value 
    /// @return 
    SDL_INLINE bool GetBooleanProperty( const char *name, const bool default_value ) const
    {
        return SDL_GetBooleanProperty( properties, name, default_value );
    }

    /// @brief 
    /// @param name 
    /// @return 
    SDL_INLINE bool ClearProperty( const char* name )
    {
        return SDL_ClearProperty( properties, name );
    }

    /// @brief 
    /// @param callback 
    /// @param userdata 
    /// @return 
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