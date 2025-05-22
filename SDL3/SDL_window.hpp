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
#include "SDL_surface.hpp"

namespace SDL
{
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
    class Window
    {
    public:
        Window( void ) : window( nullptr )
        {
        }

        Window( const Window &ref ) : window( ref.window )
        {
        }

        Window( SDL_Window* hnd )  : window( hnd )
        {
        }

        SDL_INLINE ~Window( void )
        {
        }

        SDL_INLINE bool Create( const char *title, const int w, const int h, const SDL_WindowFlags flags )
        {
            window = SDL_CreateWindow( title, w, h, flags );
            return window != nullptr;
        }

        SDL_INLINE void Destroy( void )
        {
            if ( window != nullptr )
            {
                SDL_DestroyWindow( window );
                window = nullptr;
            }
        }

        SDL_INLINE bool CreatePopup( const Window* parent, const int offset_x, const int offset_y,  const int w, const int h, const SDL_WindowFlags flags )
        {
            window = SDL_CreatePopupWindow( parent->window, offset_x, offset_y, w, h, flags );
            return window != nullptr;
        }

        SDL_INLINE bool CreateWithProperties( const SDL_PropertiesID props )
        {
            window = SDL_CreateWindowWithProperties( props );
            return window != nullptr;
        }

        SDL_INLINE bool SetWindowTitle( const char *title )
        {
            return SDL_SetWindowTitle( window, title );
        }

        SDL_INLINE bool SetIcon( const Surface icon )
        {
            return SDL_SetWindowIcon( window, icon );
        }

        SDL_INLINE bool SetPosition( const int x, const int y )
        {
            return SDL_SetWindowPosition( window, x, y );
        }

        SDL_INLINE bool SetMinimumSize( const int min_w, const int min_h )
        {
            return SDL_SetWindowMaximumSize( window, min_w, min_h ) ;
        }

        SDL_INLINE bool SetMaximumSize( const int max_w, const int max_h )
        {
            return SDL_SetWindowMaximumSize( window, max_w, max_h );
        }
        
        SDL_INLINE bool SetResizable( const bool resizable )
        {
            return SDL_SetWindowResizable( window, resizable );
        }
        
        SDL_INLINE bool SetAlwaysOnTop( const bool on_top )
        {
            return SDL_SetWindowAlwaysOnTop( window, on_top );
        }
        
        SDL_INLINE bool SetSize( const int w, const int h )
        {
            return SDL_SetWindowSize( window, w, h );
        }
        
        SDL_INLINE bool SetAspectRatio( const float min_aspect, const float max_aspect )
        {
            return SDL_SetWindowAspectRatio( window, min_aspect, max_aspect );
        }
        
        SDL_INLINE bool SetBordered( const bool bordered )
        {
            return SDL_SetWindowBordered( window,  bordered );
        }

        SDL_INLINE bool SetKeyboardGrab( const bool grabbed )
        {
            return SDL_SetWindowKeyboardGrab( window, grabbed );
        }

        SDL_INLINE bool SetMouseGrab( const bool grabbed )
        {   
            return SDL_SetWindowMouseGrab( window, grabbed );
        }

        SDL_INLINE bool Maximize( void ) const
        {
            return SDL_MaximizeWindow( window );
        }

        SDL_INLINE bool Minimize( void ) const
        {
            return SDL_MinimizeWindow( window );
        }

        SDL_INLINE bool Restore( void ) const
        {
            return SDL_RestoreWindow( window );
        }

        SDL_INLINE bool Raise( void ) const
        {
            return SDL_RaiseWindow( window );
        }

        SDL_INLINE bool Show( void ) const
        {
            return SDL_ShowWindow( window );
        }
        
        SDL_INLINE bool  Hide( void ) const
        {
            return SDL_HideWindow( window );
        }

        SDL_INLINE bool Sync( void ) const
        {
            return SDL_SyncWindow( window );
        }

        SDL_INLINE const SDL_WindowID GetID( void ) const 
        {
            return SDL_GetWindowID( window );
        }

        SDL_INLINE const Window GetParent( void ) const
        {
            return Window( SDL_GetWindowParent( window ) );
        }

        SDL_INLINE SDL_PropertiesID GetProperties( void ) const
        {
            return SDL_GetWindowProperties( window );
        }
        
        SDL_INLINE SDL_WindowFlags GetFlags( void ) const
        {
            return SDL_GetWindowFlags( window );
        }

        SDL_INLINE const char* GetTitle( void ) const
        {
            return SDL_GetWindowTitle( window );
        }

        SDL_INLINE bool GetPosition( int *x, int *y ) const
        {
            return SDL_GetWindowPosition( window, x, y );
        }

        SDL_INLINE bool GetSize( int* w, int* h ) const
        {
            return SDL_GetWindowSize( window, w, h );
        }

        SDL_INLINE bool GetSafeArea( SDL_Rect* rect )
        {
            return SDL_GetWindowSafeArea( window, rect );
        }

        SDL_INLINE bool GetAspectRatio( float *min_aspect, float *max_aspect )
        {
            return SDL_GetWindowAspectRatio( window, min_aspect, max_aspect );
        }

        SDL_INLINE bool GetBordersSize( int *top, int *left, int *bottom, int *right )
        {
            return SDL_GetWindowBordersSize( window, top, left, bottom, right );
        }

        SDL_INLINE bool GetSizeInPixels( int *w, int *h )
        {
            return SDL_GetWindowSizeInPixels( window, w, h );
        }

        SDL_INLINE bool GetMinimumSize( int *w, int *h ) const
        {
            return SDL_GetWindowMinimumSize( window, w, h );
        }

        SDL_INLINE bool GetMaximumSize( int *w, int *h ) const
        {
            return SDL_GetWindowMaximumSize( window, w, h );
        }

        SDL_INLINE bool SetFullscreen( const bool fullscreen )
        {
            return SDL_SetWindowFullscreen( window, fullscreen );
        }

        SDL_INLINE bool HasSurface( void ) const
        {
            return SDL_WindowHasSurface( window );
        }
        
        SDL_INLINE Surface GetSurface( void ) const
        {
            return Surface( SDL_GetWindowSurface( window ) );
        }
        
        SDL_INLINE bool SetSurfaceVSync( int vsync )
        {
            return SDL_SetWindowSurfaceVSync( window, vsync );
        }
        
        SDL_INLINE bool GetSurfaceVSync( int* vsync )
        {
            return SDL_GetWindowSurfaceVSync( window, vsync );
        }

        SDL_INLINE bool UpdateSurface( void ) const
        {
            return SDL_UpdateWindowSurface( window );
        }
        
        SDL_INLINE bool UpdateSurfaceRects( const SDL_Rect *rects, int numrects ) const
        {
            return SDL_UpdateWindowSurfaceRects( window, rects, numrects );
        }
        
        SDL_INLINE bool DestroySurface( void )
        {
            return SDL_DestroyWindowSurface( window ); 
        }

        SDL_INLINE bool GetKeyboardGrab( void ) const
        {
            return SDL_GetWindowKeyboardGrab( window );
        }

        SDL_INLINE bool GetMouseGrab( void ) const
        {
            return SDL_GetWindowMouseGrab( window );
        }

        SDL_INLINE bool SetMouseRect( const SDL_Rect rect )
        {
            return SDL_SetWindowMouseRect( window, &rect );
        }

        SDL_INLINE const SDL_Rect* GetMouseRect( void ) const
        {
            return SDL_GetWindowMouseRect( window );
        }

        SDL_INLINE float GetOpacity( void )
        {
            return SDL_GetWindowOpacity( window );
        }

        SDL_INLINE bool SetOpacity( const float opacity )
        {
            return SDL_SetWindowOpacity( window, opacity );
        }

        SDL_INLINE bool SetParent( const Window* parent )
        {
            return SDL_SetWindowParent( window, parent->GetHandle() );
        }

        SDL_INLINE bool SetModal( const bool modal )
        {
            return SDL_SetWindowModal( window, modal );
        }

        SDL_INLINE bool SetFocusable( const bool focusable )
        {
            return SDL_SetWindowFocusable( window, focusable );
        }

        SDL_INLINE bool ShowSystemMenu( const int x, const int y )
        {
            return SDL_ShowWindowSystemMenu( window, x, y );
        }

        SDL_INLINE bool SetHitTest( SDL_HitTest callback, void *callback_data )
        {
            return SDL_SetWindowHitTest( window, callback, callback_data );
        }

        SDL_INLINE bool SetShape( const Surface shape )
        {
            return SDL_SetWindowShape( window, shape.GetHandle() );
        }

        SDL_INLINE bool FlashWindow( const SDL_FlashOperation operation )
        {
            return SDL_FlashWindow( window, operation );
        }

    #ifdef SDL_vulkan_h_
        SDL_INLINE bool CreateVulkanSurface( VkInstance instance, const struct VkAllocationCallbacks *allocator, VkSurfaceKHR* surface ) const
        {
            return SDL_Vulkan_CreateSurface( window, instance, allocator, surface );
        }
    #endif //SDL_vulkan_h_

        SDL_INLINE operator SDL_Window*( void ) const { return window; }

        SDL_Window*  GetHandle( void ) const { return window; } 

    private:
        SDL_Window* window;
    };
};

#endif //!__SDL_WINDOWN_HPP__