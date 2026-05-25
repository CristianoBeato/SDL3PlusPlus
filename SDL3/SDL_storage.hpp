/*
===========================================================================================
    This file is part of SDL3++.

    Copyright (c) 2026 Cristiano B. Santos <cristianobeato_dm@hotmail.com>
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

#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include <SDL3/SDL_storage.h>

namespace SDL
{
    class Storage
    {
    private:
        SDL_Storage*    m_storage; // storage handler
    
    public:
        Storage( void ) : m_storage( nullptr )
        {
        }

        Storage( const SDL_Storage *in_ref ) : m_storage( in_ref )
        {
        }

        Storage( const SDL::Storage& in_ref ) : m_storage( m_storage )
        {
        }

        ~Storage( void )
        {
            m_storage = nullptr;
        }

        /// @brief Opens up a read-only container for the application's filesystem.
        /// @param in_override a path to override the backend's default title root.
        /// @param in_props a property list that may contain backend-specific information.
        /// @return true on succes, false on failure.
        SDL_INLINE bool OpenTitle( const char* in_override, const SDL_PropertiesID in_props )
        {
            m_storage = SDL_OpenTitleStorage( in_override, in_props );
            return m_storage != nullptr;
        }

        /// @brief Opens up a container for a user's unique read/write filesystem.
        /// @param in_org the name of your organization.
        /// @param in_app the name of your application.
        /// @param in_props a property list that may contain backend-specific information.
        /// @return true on success or false on failure.
        SDL_INLINE bool OpenUser( const char* in_org, const char* in_app, SDL_PropertiesID in_props )
        {
            m_storage = SDL_OpenUserStorage( in_org, in_app, in_props );
            return m_storage != nullptr;
        }

        /// @brief Opens up a container for local filesystem storage. ( This is provided for development and tools )
        /// @param in_path the base path prepended to all storage paths, or NULL for no
        /// base path.
        /// @return true on success or false on failure
        SDL_INLINE bool OpenFile( const char* in_path )
        {
            m_storage = SDL_OpenFileStorage( in_path );
            return m_storage != nullptr;
        }

        /// @brief Opens up a container using a client-provided storage interface.
        /// @param in_iface the interface that implements this storage, initialized using SDL_INIT_INTERFACE().
        /// @param in_userdata the pointer that will be passed to the interface functions.
        /// @return true on success or false on failure.
        SDL_INLINE bool OpenStorage( const SDL_StorageInterface* in_iface, void* in_userdata )
        {
            m_storage = SDL_OpenStorage( in_iface, in_userdata );
            return m_storage != nullptr;
        }
        
        /// @brief Closes and frees a storage container.
        /// @return true on success or false on failure.
        SDL_INLINE bool Close( void )
        {
            auto result = SDL_CloseStorage( m_storage );
            m_storage = nullptr;
            return result;
        }

        /// @brief Checks if the storage container is ready to use.
        /// @return true if the container is ready, false otherwise.
        SDL_INLINE bool StorageReady( void ) const
        {
            if( m_storage == nullptr )
                return false;

            return SDL_StorageReady( m_storage );
        }

        /// @brief Query the size of a file within a storage container.
        /// @param in_path the relative path of the file to query.
        /// @param out_length a pointer to be filled with the file's length.
        /// @return true on success or false on failure.
        SDL_INLINE bool GetFileSize( const char* in_path, Uint64* out_length ) const
        {
            if( m_storage == nullptr ) 
                return false;
            
            return SDL_GetStorageFileSize( m_storage, in_path, out_length );
        }

        /// @brief Synchronously read a file from a storage container into a client-provided buffer.
        /// @param in_path the relative path of the file to read.
        /// @param out_destination a client-provided buffer to read the file into.
        /// @param in_length the length of the destination buffer.
        /// @return true on success or false on failure.
        SDL_INLINE bool ReadFile( const char* in_path, void *out_destination, const Uint64 in_length ) const
        {
            if( m_storage == nullptr ) 
                return false;

            return SDL_ReadStorageFile( m_storage, in_path, out_destination, in_length );
        }

        /// @brief Synchronously write a file from client memory into a storage container.
        /// @param in_path the relative path of the file to write.
        /// @param in_source a client-provided buffer to write from.
        /// @param in_length the length of the source buffer.
        /// @return true on success or false on failure.
        SDL_INLINE bool WriteFile( const char *in_path, const void *in_source, const Uint64 in_length )
        {
            if( m_storage == nullptr ) 
                return false;

            return SDL_WriteStorageFile( m_storage, in_path, in_source, in_length );
        }

        /// @brief Create a directory in a writable storage container.
        /// @param in_path the path of the directory to create.
        /// @return true on success or false on failure.
        SDL_INLINE bool CreateDirectory( const char *in_path )
        {
            if( m_storage == nullptr ) 
                return false;
            
            return SDL_CreateStorageDirectory( m_storage, in_path );
        }

        /// @brief Enumerate a directory in a storage container through a callback function.
        /// @param in_path the path of the directory to enumerate, or NULL for the root.
        /// @param in_callback a function that is called for each entry in the directory.
        /// @param in_userdata a pointer that is passed to `callback`.
        /// @return true on success or false on failure.
        SDL_INLINE bool EnumerateDirectory( const char* in_path, SDL_EnumerateDirectoryCallback in_callback, void* in_userdata )
        {
            if( m_storage == nullptr ) 
                return false;

            return SDL_EnumerateStorageDirectory( m_storage, in_path, in_callback, in_userdata );
        }

        /// @brief Remove a file or an empty directory in a writable storage container.
        /// @param in_path the path of the directory to enumerate.
        /// @return true on success or false on failure.
        SDL_INLINE bool RemovePath( const char* in_path )
        {
            if( m_storage == nullptr ) 
                return false;

            return SDL_RemoveStoragePath( m_storage, in_path );
        }

        /// @brief Rename a file or directory in a writable storage container.
        /// @param in_oldpath the old path.
        /// @param in_newpath the new path.
        /// @return true on success or false on failure.
        SDL_INLINE bool RenamePath( const char *in_oldpath, const char *in_newpath )
        {
            if( m_storage == nullptr ) 
                return false;

            return SDL_RenameStoragePath( m_storage, in_oldpath, in_newpath );
        }
        
        /// @brief Copy a file in a writable storage container.
        /// @param in_oldpath the old path.
        /// @param in_newpath the new path.
        /// @return true on success or false on failure.
        SDL_INLINE bool CopyFile( const char* in_oldpath, const char* in_newpath ) const
        {
            if( m_storage == nullptr ) 
                return false;

            return SDL_CopyStorageFile( m_storage, in_oldpath, in_newpath );
        }
        
        /// @brief Get information about a filesystem path in a storage container.
        /// @param in_path the path to query.
        /// @param out_info a pointer filled in with information about the path, or NULL to check for the existence of a file.
        /// @return true on success or false if the file doesn't exist, or another failure.
        SDL_INLINE bool GetPathInfo( const char* in_path, SDL_PathInfo* out_info ) const
        {
            if( m_storage == nullptr ) 
                return false;

            return SDL_GetStoragePathInfo( m_storage, in_path, out_info );
        }
        
        /// @brief Queries the remaining space in a storage container.
        /// @return 0 on failure/
        SDL_INLINE Uint64   GetSpaceRemaining( void ) const
        {
            if( m_storage == nullptr ) 
                return 0;

            return SDL_GetStorageSpaceRemaining( m_storage );
        }
        
        SDL_INLINE char** GlobStorageDirectory( const char *in_path, const char *in_pattern, SDL_GlobFlags in_flags, int *in_count )
        {
            if( m_storage == nullptr ) 
                return nullptr;

            return SDL_GlobStorageDirectory( m_storage, in_path, in_pattern, in_flags, in_count );
        }
    };
}; // namespace SDL

#endif //!__STORAGE_HPP__