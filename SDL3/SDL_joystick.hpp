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

#ifndef __SDL_JOYSTICK_HPP__
#define __SDL_JOYSTICK_HPP__

#include <SDL3/SDL_joystick.h>

namespace SDL
{
    namespace Input
    {

        class JoystickID
        {
            public:
            JoystickID( void ) : m_ID( 0 )
            {
            }

            JoystickID( const SDL_JoystickID & in_id ) : m_ID( in_id )
            {
            }

            SDL_INLINE const char *     GetName( void ) const { return SDL_GetSensorNameForID( m_ID ); }
            SDL_INLINE const char *     GetPath( void ) const { return SDL_GetJoystickPathForID( m_ID ); }
            SDL_INLINE int              GetPlayerIndex( void ) const { return SDL_GetJoystickPlayerIndexForID( m_ID ); }
            SDL_INLINE SDL_GUID         GetGUID( void ) const { return SDL_GetJoystickGUIDForID( m_ID ); }
            SDL_INLINE Uint16           GetVendor( void ) const { return SDL_GetJoystickVendorForID( m_ID ); }
            SDL_INLINE Uint16           GetProductForID( void ) const { return SDL_GetJoystickProductForID( m_ID ); }
            SDL_INLINE Uint16           GetProductVersionForID( void ) const { return SDL_GetJoystickProductVersionForID( m_ID ); }
            SDL_INLINE SDL_JoystickType GetTypeForID( void ) const { return SDL_GetJoystickTypeForID( m_ID ); }
            SDL_INLINE SDL_JoystickID SDLCALL SDL_AttachVirtualJoystick(const SDL_VirtualJoystickDesc *desc);
            SDL_INLINE bool SDLCALL SDL_DetachVirtualJoystick(SDL_JoystickID instance_id);
            SDL_INLINE bool SDLCALL SDL_IsJoystickVirtual(SDL_JoystickID instance_id);
        
            SDL_INLINE operator SDL_JoystickID( void ) const { return m_ID; }   

            private:
                SDL_JoystickID  m_ID;
        };

        class Joystick
        {
        public:
            Joystick( void ) : 
                m_ID( 0 ),
                m_joystick( nullptr )
            {
            }

            ~Joystick( void )
            {
            }

            SDL_INLINE bool GetFromID( const SDL_JoystickID instance_id )
            {
                m_ID = instance_id;
                m_joystick = SDL_GetJoystickFromID( m_ID );
                return m_joystick != nullptr;
            }

            SDL_INLINE bool GetFromPlayerIndex( const int player_index )
            {
                m_joystick = SDL_GetJoystickFromPlayerIndex( player_index );
                // TODO: m_ID = SDL_GetJoystickGUID
                return m_joystick != nullptr;
            }

            SDL_INLINE bool Open( const SDL_JoystickID instance_id )
            {
                m_ID = instance_id;
                m_joystick = SDL_OpenJoystick( m_ID );
                return m_joystick != nullptr;   
            }

            SDL_INLINE void Close( void )
            {
                if ( m_joystick != nullptr )
                {
                    SDL_CloseJoystick( m_joystick );
                    m_joystick = nullptr;
                }
            }

            SDL_INLINE const char*      GetName( void ) const
            {
                return SDL_GetJoystickName( m_joystick );
            }

            SDL_INLINE const char*      GetPath( void ) const
            {
                return SDL_GetJoystickPath( m_joystick );
            }
            
            SDL_INLINE int              GetPlayerIndex( void ) const
            {
                return SDL_GetJoystickPlayerIndex( m_joystick );
            }

            SDL_INLINE bool             SetPlayerIndex( const int player_index )
            {
                return SDL_SetJoystickPlayerIndex( m_joystick, player_index );
            }

            SDL_INLINE SDL_GUID         GetGUID( void ) const
            {
                return SDL_GetJoystickGUID( m_joystick );
            }

            SDL_INLINE Uint16           GetVendor( void )
            {
                return SDL_GetJoystickVendor( m_joystick );
            }

            SDL_INLINE Uint16           GetProduct( void )
            {
                return SDL_GetJoystickProduct( m_joystick );
            }
            
            SDL_INLINE Uint16           GetProductVersion( void )
            {
                return SDL_GetJoystickProductVersion( m_joystick );
            }

            SDL_INLINE const char *     GetSerial( void )
            {
                return SDL_GetJoystickSerial( m_joystick );
            }
            
            SDL_INLINE Uint16           GetFirmwareVersion( void )
            {
                return SDL_GetJoystickFirmwareVersion( m_joystick );
            }
            
            SDL_INLINE SDL_JoystickType GetType( void ) const
            {
                return SDL_GetJoystickType( m_joystick );
            }
            
            SDL_INLINE void             GetGUIDInfo( Uint16 *vendor, Uint16 *product, Uint16 *version, Uint16 *crc16 ) const
            {
                auto guid = SDL_GetJoystickGUID( m_joystick );
                SDL_GetJoystickGUIDInfo( guid, vendor, product, version, crc16 );
            }
            
            SDL_INLINE bool Connected( void ) const
            {
                return SDL_JoystickConnected( m_joystick );
            }
            
            SDL_INLINE SDL_JoystickID   GetID( void ) const
            {
                return SDL_GetJoystickID( m_joystick );
            }
            
            SDL_INLINE int              GetNumAxes( void )
            {
                return SDL_GetNumJoystickAxes( m_joystick );
            }
            
            SDL_INLINE bool             SetVirtualAxis( const int axis, const Sint16 value )
            {
                return SDL_SetJoystickVirtualAxis( m_joystick, axis, value );
            }
            
            SDL_INLINE int              GetNumBalls( void ) const
            {
                return SDL_GetNumJoystickBalls( m_joystick );
            }
            
            SDL_INLINE bool             SetVirtualBall( const int ball, const Sint16 xrel, const Sint16 yrel )
            {
                return SDL_SetJoystickVirtualBall( m_joystick, ball, xrel, yrel );
            }
            
            SDL_INLINE bool             SetVirtualButton( const int button, const bool down )
            {
                return SDL_SetJoystickVirtualButton( m_joystick, button, down );
            }
            
            SDL_INLINE int              GetNumHats( void ) const
            {
                return SDL_GetNumJoystickHats( m_joystick );
            }
            
            SDL_INLINE int              GetNumButtons( void ) const
            {
                return SDL_GetNumJoystickButtons( m_joystick );
            }

            SDL_INLINE Sint16           GetAxis( const int axis ) const
            {
                return SDL_GetJoystickAxis( m_joystick, axis );
            }

            SDL_INLINE bool             GetAxisInitialState( const int axis, Sint16 *state ) const
            {
                return SDL_GetJoystickAxisInitialState( m_joystick, axis, state );
            }
            
            SDL_INLINE bool             GetBall( const int ball, int *dx, int *dy ) const
            {
                return SDL_GetJoystickBall( m_joystick, ball, dx, dy );
            }
 
            SDL_INLINE Uint8            GetHat( const int hat ) const
            {
                return SDL_GetJoystickHat( m_joystick, hat );
            }
            
            SDL_INLINE bool             GetButton( const int button ) const
            {
                return SDL_GetJoystickButton( m_joystick, button );
            }
            
            SDL_INLINE bool             Rumble( const Uint16 low_frequency_rumble, const Uint16 high_frequency_rumble, const Uint32 duration_ms )
            {
                return SDL_RumbleJoystick( m_joystick, low_frequency_rumble, high_frequency_rumble, duration_ms );
            }
            
            SDL_INLINE bool             RumbleTriggers( const Uint16 left_rumble, const Uint16 right_rumble, const Uint32 duration_ms)
            {
                return SDL_RumbleJoystickTriggers( m_joystick, left_rumble, right_rumble, duration_ms );
            }
            
            SDL_INLINE bool             SetLED( const Uint8 red, const Uint8 green, const Uint8 blue )
            {
                return SDL_SetJoystickLED( m_joystick, red, green, blue );
            }
            
            SDL_INLINE bool             SendEffect( const void *data, int size)
            {
                return SDL_SendJoystickEffect( m_joystick, data, size );
            }
            
            SDL_INLINE bool             SetVirtualHat( int hat, Uint8 value )
            {
                return SDL_SetJoystickVirtualHat( m_joystick, hat, value );
            }
            
            SDL_INLINE bool             SetVirtualTouchpad( const int touchpad, const int finger, const bool down, const float x, const float y, const float pressure )
            {
                return SDL_SetJoystickVirtualTouchpad( m_joystick, touchpad, finger, down, x, y, pressure );
            }

            SDL_INLINE bool             SendVirtualSensorData( const SDL_SensorType type, const Uint64 sensor_timestamp, const float *data, const int num_values )
            {
                return SDL_SendJoystickVirtualSensorData( m_joystick, type, sensor_timestamp, data, num_values );
            }            
            
            SDL_INLINE SDL_JoystickConnectionState  GetConnectionState( void ) const
            {
                return SDL_GetJoystickConnectionState( m_joystick );
            }
            
            SDL_INLINE SDL_PowerState               GetPowerInfo( int *percent ) const
            {
                return SDL_GetJoystickPowerInfo( m_joystick, percent );
            }
            
            SDL_INLINE SDL_PropertiesID             GetProperties( void ) const
            {
                return SDL_GetJoystickProperties( m_joystick );
            }

            SDL_INLINE operator SDL_Joystick* ( void ) const { return m_joystick; } 

            SDL_INLINE operator bool( void ) const { return m_joystick != nullptr; }

        private:
            SDL_JoystickID  m_ID;
            SDL_Joystick*   m_joystick;
        };
    };
};

#endif //!__SDL_JOYSTICK_HPP__