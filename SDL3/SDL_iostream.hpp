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
#ifndef __SDL_IOSTREAM_HPP__
#define __SDL_IOSTREAM_HPP__

#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_asyncio.h>

namespace SDL
{
    namespace IO
    {
        class Stream
        {
        public:
            Stream( void )  : IOStream( nullptr ){}
            Stream( SDL_IOStream* iostream ) : IOStream( iostream ) {}
            Stream( const Stream &ref ) : IOStream( ref.IOStream ){}
            ~Stream( void ){}
            
            /// @brief Use this function to create a new SDL_IOStream structure for reading from and/or writing to a named file.
            /// @param file a UTF-8 string representing the filename to open.
            /// @param mode an ASCII string representing the mode to be used for opening the file. ( r, w, a, r+, w+, a+, rb, wb, ab, rb+, wb+ and ab+ )
            /// @return true to the SDL_IOStream structure that is created or false on failure;
            SDL_INLINE bool             FromFile( const char *file, const char *mode )
            {
                IOStream = SDL_IOFromFile( file, mode );
                return IOStream != nullptr;
            }
            
            /// @brief Save all the data into an SDL data stream.
            /// @param data the data to be written. If datasize is 0, may be NULL or a invalid pointer.
            /// @param datasize the number of bytes to be written.
            /// @param closeio if true, calls SDL_CloseIO() on `src` before returning, even in the case of an error.
            /// @return true on success or false on failure; call SDL_GetError() for more information.
            SDL_INLINE bool             SaveFile( const void *data, size_t datasize, bool closeio) 
            { 
                return SDL_SaveFile_IO( IOStream, data, datasize, closeio ); 
            }

            /// @brief Load all the data from an SDL data stream.
            /// @param datasize a pointer filled in with the number of bytes read, may be NULL.
            /// @param closeio if true, calls SDL_CloseIO() on `src` before returning, even in the case of an error.
            /// @return the data or NULL on failure; call SDL_GetError() for more information.
            SDL_INLINE void*            LoadFile( size_t *datasize, bool closeio) 
            {
                return SDL_LoadFile_IO( IOStream, datasize, closeio );
            }
            
            /// @brief Use this function to prepare a read-write memory buffer for use with
            /// @param mem a pointer to a buffer to feed an SDL_IOStream stream.
            /// @param size the buffer size, in bytes.
            /// @return true to the SDL_IOStream structure that is created or false on failure;
            SDL_INLINE bool             FromMem( void *mem, const size_t size )
            {
                IOStream = SDL_IOFromMem( mem, size );
                return IOStream != nullptr;
            }

            /// @brief Use this function to prepare a read-only memory buffer for use with SDL_IOStream.
            /// @param mem a pointer to a read-only buffer to feed an SDL_IOStream stream.
            /// @param size the buffer size, in bytes.
            /// @return true to a new SDL_IOStream structure or false on failure; call SDL_GetError() for more information.
            SDL_INLINE bool             FromConstMem(const void *mem, size_t size)
            {
                IOStream = SDL_IOFromConstMem( mem, size );
                return IOStream != nullptr;
            }

            /// @brief Use this function to create an SDL_IOStream that is backed by dynamically allocated memory.
            /// @return true to a new SDL_IOStream structure or false on failure; call SDL_GetError() for more information.
            SDL_INLINE bool             FromDynamicMem(void)
            {
                IOStream = SDL_IOFromDynamicMem();
                return IOStream != nullptr;
            }

            /// @brief Create a custom SDL_IOStream.
            /// @param iface the interface that implements this SDL_IOStream, initialized using SDL_INIT_INTERFACE().
            /// @param userdata the pointer that will be passed to the interface functions.
            /// @return true to a new SDL_IOStream structure or false on failure; call SDL_GetError() for more information.
            SDL_INLINE bool             OpenIO(const SDL_IOStreamInterface *iface, void *userdata)
            {
                IOStream = SDL_OpenIO( iface, userdata );
                return IOStream != nullptr;
            }

            /// @brief Seek within an SDL_IOStream data stream.
            /// @param offset an offset in bytes, relative to `whence` location; can be negative.
            /// @param whence any of `SDL_IO_SEEK_SET`, `SDL_IO_SEEK_CUR`, `SDL_IO_SEEK_END`.
            /// @return the final offset in the data stream after the seek or -1 on failure; call SDL_GetError() for more information.
            SDL_INLINE Sint64           Seek( Sint64 offset, SDL_IOWhence whence ) { return SDL_SeekIO( IOStream, offset, whence ); }

            /// @brief Determine the current read/write offset in an SDL_IOStream data stream.
            /// @return the current offset in the stream, or -1 if the information can not be determined.
            SDL_INLINE Sint64           Tell( void ) { return SDL_TellIO( IOStream ); }

            /// @brief Read from a data source.
            /// @param ptr a pointer to a buffer to read data into.
            /// @param size the number of bytes to read from the data source.
            /// @return the number of bytes read, or 0 on end of file or other failure;
            SDL_INLINE size_t           Read(  void *ptr, size_t size) { return SDL_ReadIO( IOStream, ptr, size ); }

            /// @brief Write to an SDL_IOStream data stream.
            /// @param ptr a pointer to a buffer containing data to write.
            /// @param size the number of bytes to write.
            /// @return the number of bytes written, which will be less than `size` on
            SDL_INLINE size_t           Write( const void *ptr, size_t size ) { return SDL_WriteIO( IOStream, ptr, size ); }
            
            /// @brief Flush any buffered data in the stream.
            /// @return true on success or false on failure; call SDL_GetError() for more information.
            SDL_INLINE bool             Flush( void ) { return SDL_FlushIO( IOStream ); }
            
            /// @brief Close and free an allocated SDL_IOStream structure.
            /// @return true on success or false on failure; call SDL_GetError() for more information.
            SDL_INLINE bool             Close( void ) { return SDL_CloseIO( IOStream ); }

            SDL_INLINE bool             ReadU8( Uint8 *value ){ return SDL_ReadU8( IOStream, value ); }
            SDL_INLINE bool             ReadS8( Sint8 *value ){ return SDL_ReadS8( IOStream, value ); }
            SDL_INLINE bool             ReadU16LE( Uint16 *value ){ return SDL_ReadU16LE( IOStream, value ); }
            SDL_INLINE bool             ReadS16LE( Sint16 *value ){ return SDL_ReadS16LE( IOStream, value ); }
            SDL_INLINE bool             ReadU16BE( Uint16 *value ){ return SDL_ReadU16BE( IOStream, value ); }
            SDL_INLINE bool             ReadS16BE( Sint16 *value ){ return SDL_ReadS16BE( IOStream, value ); }
            SDL_INLINE bool             ReadU32LE( Uint32 *value ){ return SDL_ReadU32LE( IOStream, value ); }
            SDL_INLINE bool             ReadS32LE( Sint32 *value ){ return SDL_ReadS32LE( IOStream, value ); }
            SDL_INLINE bool             ReadU32BE( Uint32 *value ){ return SDL_ReadU32BE( IOStream, value ); }
            SDL_INLINE bool             ReadS32BE( Sint32 *value ){ return SDL_ReadS32BE( IOStream, value ); }
            SDL_INLINE bool             ReadU64LE( Uint64 *value ){ return SDL_ReadU64LE( IOStream, value ); }
            SDL_INLINE bool             ReadS64LE( Sint64 *value ){ return SDL_ReadS64LE( IOStream, value ); }
            SDL_INLINE bool             ReadU64BE( Uint64 *value ){ return SDL_ReadU64BE( IOStream, value ); }
            SDL_INLINE bool             ReadS64BE( Sint64 *value ){ return SDL_ReadS64BE( IOStream, value ); }
            SDL_INLINE bool             WriteU8( const Uint8 value ){ return SDL_WriteU8( IOStream, value ); };
            SDL_INLINE bool             WriteS8( const Sint8 value ){ return SDL_WriteS8( IOStream, value ); };
            SDL_INLINE bool             WriteU16LE( const Uint16 value ){ return SDL_WriteU16LE( IOStream, value ); }
            SDL_INLINE bool             WriteS16LE( const Sint16 value ){ return SDL_WriteS16LE( IOStream, value ); }
            SDL_INLINE bool             WriteU16BE( const Uint16 value ){ return SDL_WriteU16BE( IOStream, value ); }
            SDL_INLINE bool             WriteS16BE( const Sint16 value ){ return SDL_WriteS16BE( IOStream, value ); }
            SDL_INLINE bool             WriteU32LE( const Uint32 value ){ return SDL_WriteU32LE( IOStream, value ); }
            SDL_INLINE bool             WriteS32LE( const Sint32 value ){ return SDL_WriteS32LE( IOStream, value ); }
            SDL_INLINE bool             WriteU32BE( const Uint32 value ){ return SDL_WriteU32BE( IOStream, value ); }
            SDL_INLINE bool             WriteS32BE( const Sint32 value ){ return SDL_WriteS32BE( IOStream, value ); }
            SDL_INLINE bool             WriteU64LE( const Uint64 value ){ return SDL_WriteU64LE( IOStream, value ); }
            SDL_INLINE bool             WriteS64LE( const Sint64 value ){ return SDL_WriteS64LE( IOStream, value ); }
            SDL_INLINE bool             WriteU64BE( const Uint64 value ){ return SDL_WriteU64BE( IOStream, value ); }
            SDL_INLINE bool             WriteS64BE( const Sint64 value ){ return SDL_WriteS64BE( IOStream, value ); }

            /// @brief Query the stream status of an SDL_IOStream.
            /// @return an SDL_IOStatus enum with the current state.
            SDL_INLINE SDL_IOStatus     GetStatus( void ) const { return SDL_GetIOStatus( IOStream ); }

            /// @brief Use this function to get the size of the data stream in an SDL_IOStream.
            /// @return the size of the data stream in the SDL_IOStream on success or a negative error code on failure; call SDL_GetError() for more information.
            SDL_INLINE Sint64           GetSize( void ) const { return SDL_GetIOSize( IOStream ); }

            /// @brief Get the properties associated with an SDL_IOStream.
            /// @return  a valid property ID on success or 0 on failure; call SDL_GetError() for more information. 
            SDL_INLINE SDL_PropertiesID GetIOProperties( void ) const { return SDL_GetIOProperties( IOStream ); }

            /// @brief Print to an SDL_IOStream data stream.
            SDL_INLINE size_t           vprintf( SDL_PRINTF_FORMAT_STRING const char *fmt, va_list ap) SDL_PRINTF_VARARG_FUNCV(2)
            {
            return SDL_IOvprintf( IOStream, fmt, ap );
            }

            /// @brief Print to an SDL_IOStream data stream.
            SDL_INLINE size_t           printf( SDL_PRINTF_FORMAT_STRING const char *fmt, ...)  SDL_PRINTF_VARARG_FUNC(2)
            {
                size_t len = 0;
                va_list args;
                va_start (args, fmt );
                len = SDL_IOvprintf( IOStream, fmt, args );
                va_end (args);
                return len;
            }

            SDL_INLINE operator bool( void ) const { return IOStream != nullptr; }
            SDL_INLINE operator SDL_IOStream*( void ) const { return IOStream; }

        private:
            SDL_IOStream* IOStream;
        };
    
        class AsyncIOQueue
        {
        public:
            AsyncIOQueue( void ) : IOasyncQueue( nullptr ){}
            AsyncIOQueue( SDL_AsyncIOQueue *queue_ ) : IOasyncQueue( queue_ ){}
            AsyncIOQueue( const AsyncIOQueue &ref ) : IOasyncQueue( ref.IOasyncQueue ){}
            ~AsyncIOQueue( void ){}

            SDL_INLINE bool Create( void )
            {
                IOasyncQueue = SDL_CreateAsyncIOQueue();
                return IOasyncQueue != nullptr;
            }

            SDL_INLINE void DestroyAsyncIOQueue( void )
            {
                if ( IOasyncQueue != nullptr )
                {
                    SDL_DestroyAsyncIOQueue( IOasyncQueue );
                    IOasyncQueue = nullptr;
                }
            }

            SDL_INLINE bool GetResult( SDL_AsyncIOOutcome *outcome )
            {
                return SDL_GetAsyncIOResult( IOasyncQueue, outcome );
            }

            SDL_INLINE bool WaitResult( SDL_AsyncIOOutcome *outcome, const Sint32 timeoutMS )
            {
                return SDL_WaitAsyncIOResult( IOasyncQueue, outcome, timeoutMS );
            }

            SDL_INLINE void Signal( void )
            {
                return SDL_SignalAsyncIOQueue( IOasyncQueue );
            }

            SDL_INLINE bool LoadFileAsync(const char *file, void *userdata)
            {
                return SDL_LoadFileAsync( file, IOasyncQueue, userdata );
            }

            SDL_INLINE operator bool( void ) const { return IOasyncQueue != nullptr; }
            SDL_INLINE operator SDL_AsyncIOQueue*( void ) const { return IOasyncQueue; }

        private:
            SDL_AsyncIOQueue * IOasyncQueue;
        };
                
        class AsyncIO
        {
        public:
            AsyncIO( void ) : asyncIO( nullptr ) {}
            AsyncIO( SDL_AsyncIO* io ) : asyncIO( io ) {}
            AsyncIO( const AsyncIO &io ) : asyncIO( io.asyncIO ) {}
            ~AsyncIO( void ) {}

            SDL_INLINE bool AsyncIOFromFile(const char *file, const char *mode)
            {
                asyncIO = SDL_AsyncIOFromFile( file, mode );
                return asyncIO != nullptr;
            }

            SDL_INLINE Sint64 SDLCALL GetSize( void ) const 
            {
                return SDL_GetAsyncIOSize( asyncIO );
            }

            SDL_INLINE bool SDLCALL Read( void *ptr, const Uint64 offset, const Uint64 size, const AsyncIOQueue &queue, void *userdata)
            {
                return SDL_ReadAsyncIO( asyncIO, ptr, offset, size, queue, userdata );
            }

            SDL_INLINE bool SDLCALL Write( void *ptr, const Uint64 offset, const Uint64 size, const AsyncIOQueue &queue, void *userdata)
            {
                return SDL_WriteAsyncIO( asyncIO, ptr, offset, size, queue, userdata );
            }

            SDL_INLINE bool SDLCALL Close( const bool flush, const AsyncIOQueue &queue, void *userdata)
            {
                return SDL_CloseAsyncIO( asyncIO, flush, queue, userdata );
            }
            
            SDL_INLINE operator bool( void ) const { return asyncIO != nullptr; }
            SDL_INLINE operator SDL_AsyncIO*( void ) const { return asyncIO; }

        private:
            SDL_AsyncIO*    asyncIO; 
        };          
    };
};
#endif //!__SDL_IOSTREAM_HPP__