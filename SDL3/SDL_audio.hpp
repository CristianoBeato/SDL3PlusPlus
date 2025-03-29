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
#ifndef __SDL_AUDIO_HPP__
#define __SDL_AUDIO_HPP__

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_error.h>

/*
==================================================================
SDLAudioDevice
==================================================================
    This class is a wrapper around SDL audio devices. It provides a simple
    interface for creating, destroying, and managing audio devices.
    
    Example usage:
        SDLAudioDevice audioDevice;
        if (audioDevice.Create())
        {
            // Use the audio device
            audioDevice.Open();
            audioDevice.Close();
            audioDevice.Destroy();
        }
==================================================================
*/
class SDLAudioDevice
{
public:
    SDLAudioDevice( void ) {};
    ~SDLAudioDevice( void ){}
    
    //
    inline const char* GetName( void ) const
    {
        return SDL_GetAudioDeviceName( device );
    }

    inline bool GetAudioDeviceFormat( SDL_AudioSpec *spec, int *sample_frames ) const
    {
        return SDL_GetAudioDeviceFormat( device, spec, sample_frames  );
    }

    inline int* GetChannelMap( int* count )
    {
        return SDL_GetAudioDeviceChannelMap( device, count );
    }

    inline void Open( const SDL_AudioDeviceID devid, const SDL_AudioSpec *spec )
    {
        device = SDL_OpenAudioDevice( devid, spec );
    }

    inline void Close( void )
    {
        SDL_CloseAudioDevice( device );
    }

    inline bool IsPhysical( void ) const
    {
        return SDL_IsAudioDevicePhysical( device );
    }

    inline bool IsAudioDevicePlayback( void ) const
    {
        return SDL_IsAudioDevicePlayback( device );
    }

    inline bool Pause( void ) const
    {
        return SDL_PauseAudioDevice( device );
    }

    inline bool Resume( void ) const
    {
        return SDL_ResumeAudioDevice( device );
    }

    inline bool Paused( void ) const
    {
        return SDL_AudioDevicePaused( device );
    }

    inline float GetGain( void ) const
    {
        return SDL_GetAudioDeviceGain( device );
    }

    inline float SetGain( const float gain )
    {
        return SDL_GetAudioDeviceGain( device );
    }

    inline bool BindStreams( SDL_AudioStream * const *streams, int num_streams )
    {
        return SDL_BindAudioStreams( device, streams, num_streams );
    }

    inline bool BindStream( SDL_AudioStream *stream )
    {
        return SDL_BindAudioStream( device, stream );
    }

    SDL_AudioDeviceID  GetHandle( void ) const { return device; }

    operator SDL_AudioDeviceID( void ) const { return device; } 

private:
    SDL_AudioDeviceID   device;
};

/*
==================================================================
SDLAudioStream
==================================================================
    This class is a wrapper around SDL audio streams. It provides a simple
    interface for creating, destroying, and managing audio streams.
    
    Example usage:
        SDLAudioStream audioStream;
        if (audioStream.Create())
        {
            // Use the audio stream
            audioStream.PutData();
            audioStream.GetData();
            audioStream.Destroy();
        }
==================================================================  
*/
class SDLAudioStream
{
public:
    SDLAudioStream( void ) : stream( nullptr ) {}
    ~SDLAudioStream( void ) {}

    inline bool Create( const SDL_AudioSpec *src_spec, const SDL_AudioSpec *dst_spec )
    {
        stream = SDL_CreateAudioStream( src_spec, dst_spec );
        return stream != nullptr;
    }

    inline void Destroy( void )
    {
        if ( stream != nullptr )
        {
            SDL_DestroyAudioStream( stream );
            stream = nullptr;
        }
    }

    inline void Unbind( void )
    {
        SDL_UnbindAudioStream( stream );
    }

    inline SDL_AudioDeviceID GetDevice( void ) const
    {
        return SDL_GetAudioStreamDevice( stream );
    }

    inline SDL_PropertiesID GetProperties( void ) const
    {
        return SDL_GetAudioStreamProperties( stream );
    }

    inline bool GetFormat( SDL_AudioSpec *src_spec, SDL_AudioSpec *dst_spec ) const
    {
        return SDL_GetAudioStreamFormat( stream, src_spec, dst_spec );       
    }

    inline bool SetFormat( const SDL_AudioSpec *src_spec, const SDL_AudioSpec *dst_spec ) const
    {
        return SDL_SetAudioStreamFormat( stream, src_spec, dst_spec );
    }

    inline float GetFrequencyRatio( void ) const
    {
        return SDL_GetAudioStreamFrequencyRatio( stream );
    }

    inline bool SetFrequencyRatio( const float ratio )
    {
        return SDL_SetAudioStreamFrequencyRatio( stream, ratio );
    }

    inline float GetGain( void ) const
    {
        return SDL_GetAudioStreamGain( stream );
    }

    inline bool SetGain( const float gain )
    {
        return SDL_SetAudioStreamGain( stream, gain );
    }

    inline int* GetInputChannelMap( int *count )
    {
        return SDL_GetAudioStreamInputChannelMap( stream, count );
    }

    inline int* GetOutputChannelMap( int* map, int *count )
    {
        return SDL_GetAudioStreamOutputChannelMap( stream, count );
    }

    inline bool SetInputChannelMap( const int* chmap, const int count )
    {
        return SDL_SetAudioStreamInputChannelMap( stream, chmap, count );
    }

    inline bool SetOutputChannelMap( const int* chmap, const int count )
    {
        return SDL_SetAudioStreamOutputChannelMap( stream, chmap, count );
    }

    inline bool PutData( const void *buf, int len )
    {
        return SDL_PutAudioStreamData( stream, buf, len );
    }

    inline bool GetData( void *buf, int len )
    {
        return SDL_GetAudioStreamData( stream, buf, len );
    }

    inline int GetAvailable( void ) const
    {
        return SDL_GetAudioStreamAvailable( stream );
    }

    inline int GetQueued( void ) const
    {
        return SDL_GetAudioStreamQueued( stream );
    }

    inline bool Flush( void ) const
    {
        return SDL_FlushAudioStream( stream );
    }

    inline bool Clear( void ) const
    {
        return SDL_ClearAudioStream( stream );
    }

    inline bool PauseDevice( void ) const
    {
        return SDL_PauseAudioStreamDevice( stream );
    }

    inline bool ResumeDevice( void ) const
    {
        return SDL_ResumeAudioStreamDevice( stream );
    }

    inline bool Lock( void ) const
    {
        return SDL_LockAudioStream( stream );
    }

    inline bool Unlock( void ) const
    {
        return SDL_UnlockAudioStream( stream );
    }

    inline bool SetAudioStreamGetCallback( SDL_AudioStreamCallback callback, void *userdata )
    {
        return SDL_SetAudioStreamGetCallback( stream, callback, userdata );
    }

    inline bool SetAudioStreamPutCallback( SDL_AudioStreamCallback callback, void *userdata )
    {
        return SDL_SetAudioStreamPutCallback( stream, callback, userdata );
    }

    SDL_AudioStream*  GetHandle( void ) const { return stream; }

    operator SDL_AudioStream*( void ) const { return stream; } 

private:
    SDL_AudioStream*    stream;
};

#endif //!__SDL_AUDIO_HPP__