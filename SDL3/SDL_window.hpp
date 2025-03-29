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
#ifndef __SDL_WINDOWN_HPP__
#define __SDL_WINDOWN_HPP__

#include <SDL3/SDL_video.h> 
#include <SDL3/SDL_error.h>

#include "SDL_surface.hpp"

/*
==================================================================
SDLWindow
==================================================================
    This class is a wrapper around SDL windows. It provides a simple
    interface for creating, destroying, and managing windows.
    
    Example usage:
        SDLWindow window;
        if (window.Create("My Window", 800, 600, SDL_WINDOW_SHOWN))
        {
            // Use the window
            window.Show();
            window.Destroy();
        }
==================================================================  
*/
class SDLWindow
{
public:
    SDLWindow( void ) : window( nullptr )
    {
    }

    SDLWindow( const SDLWindow &ref ) : window( ref.window )
    {
    }

    SDLWindow( SDL_Window* hnd )  : window( hnd )
    {
    }

    inline ~SDLWindow( void )
    {
    }

    inline bool Create( const char *title, const int w, const int h, const SDL_WindowFlags flags )
    {
        window = SDL_CreateWindow( title, w, h, flags );
        return window != nullptr;
    }

    inline void Destroy( void )
    {
        if ( window != nullptr )
        {
            SDL_DestroyWindow( window );
            window = nullptr;
        }
    }

    inline bool CreatePopup( const SDLWindow* parent, const int offset_x, const int offset_y,  const int w, const int h, const SDL_WindowFlags flags )
    {
        window = SDL_CreatePopupWindow( parent->window, offset_x, offset_y, w, h, flags );
        return window != nullptr;
    }

    inline bool CreateWithProperties( const SDL_PropertiesID props )
    {
        window = SDL_CreateWindowWithProperties( props );
        return window != nullptr;
    }

    inline bool SetWindowTitle( const char *title )
    {
        return SDL_SetWindowTitle( window, title );
    }

    inline bool SetIcon( const SDLSurface icon )
    {
        return SDL_SetWindowIcon( window, icon );
    }

    inline bool SetPosition( const int x, const int y )
    {
        return SDL_SetWindowPosition( window, x, y );
    }

    inline bool SetMinimumSize( const int min_w, const int min_h )
    {
        return SDL_SetWindowMaximumSize( window, min_w, min_h ) ;
    }

    inline bool SetMaximumSize( const int max_w, const int max_h )
    {
        return SDL_SetWindowMaximumSize( window, max_w, max_h );
    }
    
    inline bool SetResizable( const bool resizable )
    {
        return SDL_SetWindowResizable( window, resizable );
    }
    
    inline bool SetAlwaysOnTop( const bool on_top )
    {
        return SDL_SetWindowAlwaysOnTop( window, on_top );
    }
    
    inline bool SetSize( const int w, const int h )
    {
        return SDL_SetWindowSize( window, w, h );
    }
    
    inline bool SetAspectRatio( const float min_aspect, const float max_aspect )
    {
        return SDL_SetWindowAspectRatio( window, min_aspect, max_aspect );
    }
    
    inline bool SetBordered( const bool bordered )
    {
        return SDL_SetWindowBordered( window,  bordered );
    }

    inline bool SetKeyboardGrab( const bool grabbed )
    {
        return SDL_SetWindowKeyboardGrab( window, grabbed );
    }

    inline bool SetMouseGrab( const bool grabbed )
    {   
        return SDL_SetWindowMouseGrab( window, grabbed );
    }

    inline bool Maximize( void ) const
    {
        return SDL_MaximizeWindow( window );
    }

    inline bool Minimize( void ) const
    {
        return SDL_MinimizeWindow( window );
    }

    inline bool Restore( void ) const
    {
        return SDL_RestoreWindow( window );
    }

    inline bool Raise( void ) const
    {
        return SDL_RaiseWindow( window );
    }

    inline bool Show( void ) const
    {
        return SDL_ShowWindow( window );
    }
    
    inline bool  Hide( void ) const
    {
        return SDL_HideWindow( window );
    }

    inline bool Sync( void ) const
    {
        return SDL_SyncWindow( window );
    }

    inline const SDL_WindowID GetID( void ) const 
    {
        return SDL_GetWindowID( window );
    }

    inline const SDLWindow GetParent( void ) const
    {
        return SDLWindow( SDL_GetWindowParent( window ) );
    }

    inline SDL_PropertiesID GetProperties( void ) const
    {
        return SDL_GetWindowProperties( window );
    }
    
    inline SDL_WindowFlags GetFlags( void ) const
    {
        return SDL_GetWindowFlags( window );
    }

    inline const char* GetTitle( void ) const
    {
        return SDL_GetWindowTitle( window );
    }

    inline bool GetPosition( int *x, int *y ) const
    {
        return SDL_GetWindowPosition( window, x, y );
    }

    inline bool GetSize( int* w, int* h ) const
    {
        return SDL_GetWindowSize( window, w, h );
    }

    inline bool GetSafeArea( SDL_Rect* rect )
    {
        return SDL_GetWindowSafeArea( window, rect );
    }

    inline bool GetAspectRatio( float *min_aspect, float *max_aspect )
    {
        return SDL_GetWindowAspectRatio( window, min_aspect, max_aspect );
    }

    inline bool GetBordersSize( int *top, int *left, int *bottom, int *right )
    {
        return SDL_GetWindowBordersSize( window, top, left, bottom, right );
    }

    inline bool GetSizeInPixels( int *w, int *h )
    {
        return SDL_GetWindowSizeInPixels( window, w, h );
    }

    inline bool GetMinimumSize( int *w, int *h ) const
    {
        return SDL_GetWindowMinimumSize( window, w, h );
    }

    inline bool GetMaximumSize( int *w, int *h ) const
    {
        return SDL_GetWindowMaximumSize( window, w, h );
    }

    inline bool SetFullscreen( const bool fullscreen )
    {
        return SDL_SetWindowFullscreen( window, fullscreen );
    }

    inline bool HasSurface( void ) const
    {
        return SDL_WindowHasSurface( window );
    }
    
    inline SDLSurface GetSurface( void ) const
    {
        return SDLSurface( SDL_GetWindowSurface( window ) );
    }
    
    inline bool SetSurfaceVSync( int vsync )
    {
        return SDL_SetWindowSurfaceVSync( window, vsync );
    }
    
    inline bool GetSurfaceVSync( int* vsync )
    {
        return SDL_GetWindowSurfaceVSync( window, vsync );
    }

    inline bool UpdateSurface( void ) const
    {
         return SDL_UpdateWindowSurface( window );
    }
    
    inline bool UpdateSurfaceRects( const SDL_Rect *rects, int numrects ) const
    {
        return SDL_UpdateWindowSurfaceRects( window, rects, numrects );
    }
    
    inline bool DestroySurface( void )
    {
        return SDL_DestroyWindowSurface( window ); 
    }

    inline bool GetKeyboardGrab( void ) const
    {
        return SDL_GetWindowKeyboardGrab( window );
    }

    inline bool GetMouseGrab( void ) const
    {
        return SDL_GetWindowMouseGrab( window );
    }

    inline bool SetMouseRect( const SDL_Rect rect )
    {
        return SDL_SetWindowMouseRect( window, &rect );
    }

    inline const SDL_Rect* GetMouseRect( void ) const
    {
        return SDL_GetWindowMouseRect( window );
    }

    inline float GetOpacity( void )
    {
        return SDL_GetWindowOpacity( window );
    }

    inline bool SetOpacity( const float opacity )
    {
        return SDL_SetWindowOpacity( window, opacity );
    }

    inline bool SetParent( const SDLWindow* parent )
    {
        return SDL_SetWindowParent( window, parent->GetHandle() );
    }

    inline bool SetModal( const bool modal )
    {
        return SDL_SetWindowModal( window, modal );
    }

    inline bool SetFocusable( const bool focusable )
    {
        return SDL_SetWindowFocusable( window, focusable );
    }

    inline bool ShowSystemMenu( const int x, const int y )
    {
        return SDL_ShowWindowSystemMenu( window, x, y );
    }

    inline bool SetHitTest( SDL_HitTest callback, void *callback_data )
    {
        return SDL_SetWindowHitTest( window, callback, callback_data );
    }

    inline bool SetShape( const SDLSurface shape )
    {
        return SDL_SetWindowShape( window, shape.GetHandle() );
    }

    inline bool FlashWindow( const SDL_FlashOperation operation )
    {
        return SDL_FlashWindow( window, operation );
    }

#ifdef SDL_vulkan_h_
    inline bool CreateVulkanSurface( VkInstance instance, const struct VkAllocationCallbacks *allocator, VkSurfaceKHR* surface ) const
    {
        return SDL_Vulkan_CreateSurface( window, instance, allocator, surface );
    }
#endif //SDL_vulkan_h_

    SDL_Window*  GetHandle( void ) const { return window; } 

private:
    SDL_Window* window;
};

#endif //!__SDL_WINDOWN_HPP__