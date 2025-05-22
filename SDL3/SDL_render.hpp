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

#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <SDL3/SDL_render.h>
#include "SDL_surface.hpp"
#include "SDL_window.hpp"

namespace SDL
{
    // 
    class Texture;
    class Renderer
    {
        /* data */
    public:
        Renderer( void ) : renderer( nullptr ){}
        Renderer( const Renderer &ref ) : renderer( ref.renderer ){}
        Renderer( SDL_Renderer* ptr ) : renderer( ptr ) {}
        ~Renderer( void );

        SDL_INLINE bool             Create( const Window &window, const char *name )
        {
            renderer = SDL_CreateRenderer( window, name );
            if ( !renderer )
                return false;
            return true;
        }

        SDL_INLINE bool             CreateWindowAndRenderer( const char *title, int width, int height, SDL_WindowFlags window_flags, Window* &window )
        {
            SDL_Window* win = nullptr;
            if( !SDL_CreateWindowAndRenderer( title, width, height, window_flags, &win, &renderer ) )
                return false;

            *window = win;
            return true;
        }

        SDL_INLINE bool             CreateWithProperties(SDL_PropertiesID props)
        {
            renderer = SDL_CreateRendererWithProperties( props );
            if ( !renderer )
                return false;
            return true;
        }

        SDL_INLINE bool             CreateSoftware( const Surface surface )
        {
            renderer = SDL_CreateSoftwareRenderer( surface );
            if ( !renderer )
                return false;
            return true;
        }

        SDL_INLINE void             Destroy( void )
        {
            if( renderer != nullptr )
            {
                SDL_DestroyRenderer( renderer );
                renderer = nullptr;
            }
        } 
        
        SDL_INLINE bool             Present( void ) const 
        {
            return SDL_RenderPresent( renderer );
        }

        SDL_INLINE bool             Flush( void )
        {
            return SDL_FlushRenderer( renderer );
        }
    
        SDL_INLINE bool             Clear( void )
        {
            return SDL_RenderClear( renderer );
        }

        SDL_INLINE bool GetOutputSize( int* &w, int* &h ) const
        {
            return SDL_GetRenderOutputSize( renderer, w, h );
        }

        SDL_INLINE bool GetCurrentOutputSize( int* &w, int* &h ) const
        {
            return SDL_GetCurrentRenderOutputSize( renderer, w, h );
        }
        
        SDL_INLINE bool ViewportSet( void )
        {
            return SDL_RenderViewportSet( renderer );
        }

        SDL_INLINE bool SetViewport( const SDL_Rect *rect ) const
        {
            return SDL_SetRenderViewport( renderer, rect );
        }

        SDL_INLINE bool GetViewport( SDL_Rect* &rect) const
        {
            return SDL_GetRenderViewport( renderer, rect );
        }

        SDL_INLINE bool GetSafeArea( SDL_Rect* &rect) const
        {
            return SDL_GetRenderSafeArea( renderer, rect );
        }

        SDL_INLINE bool SetClipRect( const SDL_Rect *rect )
        {
            return SDL_SetRenderClipRect( renderer, rect );
        }

        SDL_INLINE bool GetClipRect( SDL_Rect* &rect ) const
        {
            return SDL_GetRenderClipRect( renderer, rect );    
        }

        SDL_INLINE bool ClipEnabled( void )
        {
            return SDL_RenderClipEnabled( renderer );
        }

        SDL_INLINE bool SetScale( const float scaleX, const float scaleY ) const
        {
            return SDL_SetRenderScale( renderer, scaleX, scaleY );
        }

        SDL_INLINE bool GetScale( float *scaleX, float *scaleY )
        {
            return SDL_GetRenderScale( renderer, scaleX, scaleY );
        }

        SDL_INLINE bool SetDrawColor( const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
        {
            return SDL_SetRenderDrawColor( renderer, r, g, b, a );
        }

        SDL_INLINE bool SetDrawColorFloat( const float r, const float g, const float b, const float a )
        {
            return SDL_SetRenderDrawColorFloat( renderer, r, g, b, a );
        }

        SDL_INLINE bool GetDrawColor( Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a ) const
        {
            return SDL_GetRenderDrawColor( renderer, r, g, b, a );
        }

        SDL_INLINE bool GetDrawColorFloat( float *r, float *g, float *b, float *a) const
        {
            return SDL_GetRenderDrawColorFloat( renderer, r, g, b, a );
        }

        SDL_INLINE bool SetColorScale( const float scale )
        {
            return SDL_SetRenderColorScale( renderer, scale );
        }

        SDL_INLINE bool GetColorScale( float *scale)
        {
            return SDL_GetRenderColorScale( renderer, scale );
        }

        SDL_INLINE bool SetDrawBlendMode( const SDL_BlendMode blendMode)
        {
            return SDL_SetRenderDrawBlendMode( renderer, blendMode );
        }

        SDL_INLINE bool GetDrawBlendMode( SDL_BlendMode *blendMode ) const
        {
            return SDL_GetRenderDrawBlendMode( renderer, blendMode );
        }

        SDL_INLINE bool RenderPoint( const float x, const float y )
        {
            return SDL_RenderPoint( renderer, x, y );
        }

        SDL_INLINE bool RenderPoints( const SDL_FPoint *points, const int count )
        {
            return SDL_RenderPoints( renderer, points, count );
        }
        
        SDL_INLINE bool RenderLine( const float x1, const float y1, const float x2, const float y2 )
        {
            return SDL_RenderLine( renderer, x1, y1, x2, y2 );
        }
        
        SDL_INLINE bool RenderLines( const SDL_FPoint *points, int count)
        {
            return SDL_RenderLines( renderer, points, count );
        }
        
        SDL_INLINE bool RenderRect( const SDL_FRect *rect )
        {
            return SDL_RenderRect( renderer, rect );
        }
        
        SDL_INLINE bool RenderRects( const SDL_FRect *rects, int count)
        {
            return SDL_RenderRects( renderer, rects, count );
        }
        
        SDL_INLINE bool RenderFillRect( const SDL_FRect *rect)
        {
            return SDL_RenderFillRect( renderer, rect );
        }

        SDL_INLINE bool RenderFillRects( const SDL_FRect *rects, int count )
        {
            return SDL_RenderFillRects( renderer, rects, count );
        }

        SDL_INLINE bool RenderTexture( const Texture &texture, const SDL_FRect *srcrect, const SDL_FRect *dstrect)
        {
            return SDL_RenderTexture( renderer, texture, srcrect, dstrect );
        }

        SDL_INLINE bool RenderTextureRotated( const Texture &texture, const SDL_FRect *srcrect, const SDL_FRect *dstrect, double angle, const SDL_FPoint *center, SDL_FlipMode flip )
        {
            return SDL_RenderTextureRotated( renderer, texture, srcrect, dstrect, angle, center, flip );
        }

        SDL_INLINE bool RenderTextureAffine( const Texture &texture, const SDL_FRect *srcrect, const SDL_FPoint *origin, const SDL_FPoint *right, const SDL_FPoint *down)
        {
            return SDL_RenderTextureAffine( renderer, texture, srcrect, origin, right, down );
        }
        
        SDL_INLINE bool RenderTextureTiled( const Texture &texture, const SDL_FRect *srcrect, float scale, const SDL_FRect *dstrect )
        {
            return SDL_RenderTextureTiled( renderer, texture, srcrect, scale, dstrect );
        }

        SDL_INLINE bool RenderTexture9Grid( const Texture &texture, const SDL_FRect *srcrect, float left_width, float right_width, float top_height, float bottom_height, float scale, const SDL_FRect *dstrect )
        {
            return SDL_RenderTexture9Grid( renderer, texture, srcrect, left_width, right_width, top_height, bottom_height, scale, dstrect );
        }

        SDL_INLINE bool RenderGeometry( const Texture texture, const SDL_Vertex *vertices, int num_vertices, const int *indices, int num_indices )
        {
            return SDL_RenderGeometry( renderer, texture, vertices, num_vertices, indices, num_indices );
        }

        SDL_INLINE bool RenderGeometryRaw( const Texture texture, const float *xy, int xy_stride, const SDL_FColor *color, int color_stride, const float *uv, int uv_stride, int num_vertices, const void *indices, int num_indices, int size_indices)
        {
            return SDL_RenderGeometryRaw( renderer, texture, xy, xy_stride, color, color_stride, uv, uv_stride, num_indices, indices, num_indices, size_indices );
        }
        
        SDL_INLINE bool AddVulkanRenderSemaphores( const Uint32 wait_stage_mask, const Sint64 wait_semaphore, const Sint64 signal_semaphore)
        {
            return SDL_AddVulkanRenderSemaphores( renderer, wait_stage_mask, wait_semaphore, signal_semaphore );
        }
        
        SDL_INLINE bool SetVSync( const int vsync )
        {
            return SDL_SetRenderVSync( renderer, vsync );
        }
        
        SDL_INLINE bool GetVSync( int *vsync) const
        {
            return SDL_GetRenderVSync( renderer, vsync );
        }
        
        SDL_INLINE bool DebugText( const float x, const float y, const char *str )
        {
            return SDL_RenderDebugText( renderer, x, y, str );
        }

        SDL_INLINE bool DebugTextFormat(SDL_Renderer *renderer, float x, float y, SDL_PRINTF_FORMAT_STRING const char *fmt, ...)
        {
            //TODO: we need to use vprintf here (\-:) 
            return false;
        }
        
        SDL_INLINE bool SetTarget( Texture texture )
        {
            return SDL_SetRenderTarget( renderer, texture );
        }
        
        SDL_INLINE bool SetLogicalPresentation( const int w, const int h, SDL_RendererLogicalPresentation mode )
        {
            return SDL_SetRenderLogicalPresentation( renderer, w, h, mode );
        }
        
        SDL_INLINE bool GetLogicalPresentation( int *w, int *h, SDL_RendererLogicalPresentation *mode)
        {
            return SDL_GetRenderLogicalPresentation( renderer, w, h, mode );
        }
        
        SDL_INLINE bool GetLogicalPresentationRect( SDL_FRect *rect )
        {
            return SDL_GetRenderLogicalPresentationRect( renderer, rect );
        }
        
        SDL_INLINE bool CoordinatesFromWindow( const float window_x, float window_y, float *x, float *y)
        {
            return SDL_RenderCoordinatesFromWindow( renderer, window_x, window_y, x, y );
        }
        
        SDL_INLINE bool CoordinatesToWindow( const float x, const float y, float *window_x, float *window_y )
        {
            return SDL_RenderCoordinatesToWindow( renderer, x, y, window_x, window_y );
        }
        
        SDL_INLINE bool ConvertEventToRenderCoordinates( SDL_Event *event )
        {
            return SDL_ConvertEventToRenderCoordinates( renderer, event );
        }
        
        SDL_INLINE void* GetMetalLayer( void ) const
        {
            return SDL_GetRenderMetalLayer( renderer );
        }
        
        SDL_INLINE void* GetMetalCommandEncoder( void ) const
        {
            return SDL_GetRenderMetalCommandEncoder( renderer );
        }
        
        SDL_INLINE Texture GetRenderTarget( void ) const
        {
            return Texture( SDL_GetRenderTarget(renderer ) );
        }
        
        SDL_INLINE Surface RenderReadPixels( const SDL_Rect *rect ) const
        {
            return Surface( SDL_RenderReadPixels( renderer, rect ) );
        }

        SDL_INLINE const Window  GetWindow( void ) const 
        {
            return Window( SDL_GetRenderWindow( renderer ) );
        }

        SDL_INLINE const char*      GetName( void ) const
        {
            return SDL_GetRendererName( renderer );
        }

        SDL_INLINE SDL_PropertiesID GetProperties( void ) const
        {
            return SDL_GetRendererProperties( renderer );
        }

        SDL_INLINE operator bool( void ) const { return renderer != nullptr; }
        SDL_INLINE operator SDL_Renderer*( void ) const { return renderer; }

    private:
        SDL_Renderer*   renderer;
    };

    class Texture
    {
    public:
        Texture( void );
        Texture( const Texture &ref ) : texture( ref.texture ) {}
        Texture( SDL_Texture* _texture ) : texture( _texture ) {} 
        ~Texture( void );

        SDL_INLINE bool CreateTexture( const Renderer &renderer, const SDL_PixelFormat format, const SDL_TextureAccess access, const int w, const int h )
        {
            texture = SDL_CreateTexture( renderer, format, access, w, h );
            return texture != nullptr; 
        }

        SDL_INLINE bool CreateTextureFromSurface( const Renderer &renderer, const Surface &surface)
        {
            texture = SDL_CreateTextureFromSurface( renderer, surface );
            return texture != nullptr;
        }
        
        SDL_INLINE bool CreateTextureWithProperties( const Renderer &renderer, SDL_PropertiesID props )
        {
            texture = SDL_CreateTextureWithProperties( renderer, props );
            return texture != nullptr;
        }
        
        SDL_INLINE void Destroy( void )
        {
            if ( texture != nullptr )
            {
                SDL_DestroyTexture( texture );
                texture = nullptr;
            }
            
        }

        SDL_INLINE bool GetSize( float *w, float *h ) const 
        {
            return SDL_GetTextureSize( texture, w, h );
        }

        SDL_INLINE bool SetColorMod( const Uint8 r, const Uint8 g, const Uint8 b )
        {
            return SDL_SetTextureColorMod( texture, r, g, b );
        }

        SDL_INLINE bool SetColorModFloat( const float r, const float g, const float b)
        {
            return SDL_SetTextureColorModFloat( texture, r, g, b );
        }

        SDL_INLINE bool GetColorMod( Uint8 *r, Uint8 *g, Uint8 *b ) const
        {
            return SDL_GetTextureColorMod( texture, r, g, b );
        }

        SDL_INLINE bool GetColorModFloat( float *r, float *g, float *b ) const 
        {
            return SDL_GetTextureColorModFloat( texture, r, g, b );
        }

        SDL_INLINE bool SetAlphaMod( const Uint8 alpha )
        {
            return SDL_SetTextureAlphaMod( texture, alpha );
        }

        SDL_INLINE bool SetAlphaModFloat( const float alpha )
        {
            return SDL_SetTextureAlphaModFloat( texture, alpha );
        }

        SDL_INLINE bool GetAlphaMod( Uint8 *alpha ) const
        {
            return SDL_GetTextureAlphaMod( texture, alpha );
        }
        
        SDL_INLINE bool GetAlphaModFloat( float *alpha ) const
        {
            return SDL_GetTextureAlphaModFloat( texture, alpha );
        }
        
        SDL_INLINE bool SetBlendMode( SDL_BlendMode const blendMode ) 
        {
            return SDL_SetTextureBlendMode( texture, blendMode );
        }
        
        SDL_INLINE bool GetBlendMode( SDL_BlendMode *blendMode)
        {
            return SDL_GetTextureBlendMode( texture, blendMode );
        }
        
        SDL_INLINE bool SetScaleMode( SDL_ScaleMode const scaleMode)
        {
            return SDL_SetTextureScaleMode( texture, scaleMode );
        }
        
        SDL_INLINE bool GetScaleMode( SDL_ScaleMode *scaleMode )
        {
            return SDL_GetTextureScaleMode( texture, scaleMode );
        }
        
        SDL_INLINE bool Update( const SDL_Rect *rect, const void *pixels, int pitch)
        {
            return SDL_UpdateTexture( texture, rect, pixels, pitch );
        }
        
        SDL_INLINE bool UpdateYUV( const SDL_Rect *rect, const Uint8 *Yplane, int Ypitch, const Uint8 *Uplane, int Upitch, const Uint8 *Vplane, int Vpitch )
        {
            return SDL_UpdateYUVTexture( texture, rect, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch );
        }
        
        SDL_INLINE bool UpdateNV( const SDL_Rect *rect, const Uint8 *Yplane, int Ypitch, const Uint8 *UVplane, int UVpitch )
        {
            return SDL_UpdateNVTexture( texture, rect, Yplane, Ypitch, UVplane, UVpitch );
        }
        
        SDL_INLINE bool Lock( const SDL_Rect *rect, void **pixels, int *pitch)
        {
            return SDL_LockTexture( texture, rect, pixels, pitch );
        }
        
        SDL_INLINE bool LockToSurface( const SDL_Rect *rect, SDL_Surface **surface)
        {
            return SDL_LockTextureToSurface( texture, rect, surface );
        }
        
        SDL_INLINE void Unlock( void ) const
        {
            return SDL_UnlockTexture( texture );
        }
        
        SDL_INLINE Renderer GetRendererFromTexture( void ) const
        {
            return SDL_GetRendererFromTexture( texture );
        }
        
        SDL_INLINE SDL_PropertiesID GetProperties(SDL_Texture *texture) const
        {
            return SDL_GetTextureProperties( texture );
        }

        SDL_INLINE operator bool( void ) const { return texture != nullptr; }
        SDL_INLINE operator SDL_Texture*( void ) const { return texture; } 

    private:
        SDL_Texture*    texture;

    };
}

#endif //!__RENDERER_HPP__