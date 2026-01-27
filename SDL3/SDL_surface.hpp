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
#ifndef __SDL_SURFACE_HPP__
#define __SDL_SURFACE_HPP__

#include <SDL3/SDL_surface.h>

namespace SDL
{
    class Surface
    {
    public:
        struct color8u_t
        {
            Uint8 r = 0x00;
            Uint8 g = 0x00;
            Uint8 b = 0x00;
            Uint8 a = 0x00;   
        };

        struct color32f_t
        {
            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            float a = 0.0f;
        };
    
        Surface( void ) : surface( nullptr )
        {
        }

        Surface( const Surface &ref ) : surface( ref.surface )
        {
        }

        Surface( SDL_Surface* srfc  ) : surface( srfc )
        {
        }

        ~Surface( void )
        {
            Destroy();
        }

        SDL_INLINE bool Create( const int width, const int height, const SDL_PixelFormat format )
        {
            surface = SDL_CreateSurface( width, height, format );
            return surface != nullptr;
        }

        SDL_INLINE bool CreateFrom( const int width, const int height, const SDL_PixelFormat format, void *pixels, const int pitch )
        {
            surface = SDL_CreateSurfaceFrom( width, height, format, pixels, pitch );
            return surface != nullptr;
        }

        SDL_INLINE void Destroy( void )
        {
            if ( surface )
            {
                SDL_DestroySurface( surface );
                surface = nullptr;
            }
        }

        SDL_INLINE SDL_Palette* CreateSurfacePalette( void ) const
        {
            return SDL_CreateSurfacePalette( surface );
        }

        SDL_INLINE SDL_SurfaceFlags Flags( void ) const 
        {
            if ( !surface )
                return 0;

            return surface->flags;
        }

        SDL_INLINE SDL_PixelFormat Format( void ) const 
        {
            if( !surface )
                return SDL_PIXELFORMAT_UNKNOWN;

            return surface->format;
        }

        SDL_INLINE int Width( void ) const
        {
            if( !surface )
                return 0;

            return surface->w;
        }

        SDL_INLINE int Height( void ) const
        {
            if( !surface )
                return 0;

            return surface->h;
        }

        SDL_INLINE int Pitch( void ) const
        {
            if( !surface )
                return 0;

            return surface->pitch;
        }

        SDL_INLINE void* Pixels( void ) const 
        {
            if( !surface )
                return nullptr;

            return surface->pixels;
        }

        SDL_INLINE bool SetColorspace( const SDL_Colorspace colorspace )
        {
            return SDL_SetSurfaceColorspace( surface, colorspace );
        }

        SDL_INLINE bool                SetRLE( bool enabled )
        {
            return SDL_SetSurfaceRLE( surface, enabled );
        }

        SDL_INLINE bool                HasRLE( void ) const
        {
            return SDL_SurfaceHasRLE( surface );
        }

        SDL_INLINE bool                SetColorKey( const bool enabled, const Uint32 key )
        {
            return SDL_SetSurfaceColorKey( surface, enabled, key );
        }

        SDL_INLINE bool                HasColorKey( void ) const
        {
            return SDL_SurfaceHasColorKey( surface );
        }

        SDL_INLINE bool                HasAlternateImages( void ) const
        {
            return SDL_SurfaceHasAlternateImages( surface );
        }

        SDL_INLINE bool                SetSurfacePalette( SDL_Palette *palette )
        {
            return SDL_SetSurfacePalette( surface, palette );
        }

        SDL_INLINE bool                SetColorMod( const color8u_t rgb )
        {
            return SDL_SetSurfaceColorMod( surface, rgb.r, rgb.g, rgb.b );
        }

        SDL_INLINE bool                SetAlphaMod( const Uint8 alpha )
        {
            return SDL_SetSurfaceAlphaMod( surface, alpha );
        }

        SDL_INLINE bool                SetBlendMode( SDL_BlendMode blendMode )
        {
            return SDL_SetSurfaceBlendMode( surface, blendMode );
        }

        SDL_INLINE bool                SetClipRect( const SDL_Rect *rect )
        {
            return SDL_SetSurfaceClipRect( surface, rect );
        }

        SDL_INLINE SDL_Surface*        Scale( const int width, const int height, const SDL_ScaleMode scaleMode ) const
        {
            return SDL_ScaleSurface( surface, width, height, scaleMode );
        }

        SDL_INLINE SDL_PropertiesID    GetProperties( void ) const
        {
            return SDL_GetSurfaceProperties( surface );
        }

        SDL_INLINE bool                SetColorspace( SDL_Colorspace colorspace)
        {
            return SDL_SetSurfaceColorspace( surface, colorspace );
        }

        SDL_INLINE SDL_Colorspace      GetColorspace( void ) const
        {
            return SDL_GetSurfaceColorspace( surface );
        }

        SDL_INLINE SDL_Palette*        GetPalette( void ) const
        {
            return SDL_GetSurfacePalette( surface );
        }

        SDL_INLINE bool                AddAlternateImage( SDL_Surface *image )
        {
            return SDL_AddSurfaceAlternateImage( surface, image );
        }

        SDL_INLINE bool                HasAlternateImages( void ) const
        {
            return SDL_SurfaceHasAlternateImages( surface );
        }

        SDL_INLINE SDL_Surface**       GetImages( int *count) const
        {
            return SDL_GetSurfaceImages( surface, count );
        }

        SDL_INLINE void                RemoveAlternateImages( void )
        {
            SDL_RemoveSurfaceAlternateImages( surface );
        }

        SDL_INLINE bool                LockSurface( void )
        {
            return SDL_LockSurface( surface );
        }

        SDL_INLINE void                UnlockSurface( void )
        {
            SDL_UnlockSurface( surface );
        }

        SDL_INLINE bool                SetColorKey( bool enabled, Uint32 key)
        {
            return SDL_SetSurfaceColorKey( surface, enabled, key );
        }

        SDL_INLINE bool                SetColorMod( const color8u_t rgb )
        {
            return SDL_SetSurfaceColorMod( surface, rgb.r, rgb.g, rgb.b );
        }

        SDL_INLINE bool                GetAlphaMod( Uint8 *alpha ) const
        {
            return SDL_GetSurfaceAlphaMod( surface, alpha );
        }

        SDL_INLINE bool                SetBlendMode( SDL_BlendMode blendMode)
        {
            return SDL_SetSurfaceBlendMode( surface, blendMode );
        }

        SDL_INLINE bool                GetBlendMode( SDL_BlendMode *blendMode ) const
        {
            return SDL_GetSurfaceBlendMode( surface, blendMode );
        }

        SDL_INLINE bool                SetClipRect( const SDL_Rect *rect)
        {
            return SDL_SetSurfaceClipRect( surface, rect );
        }

        SDL_INLINE bool                GetSurfaceClipRect( SDL_Rect *rect)
        {
            return SDL_GetSurfaceClipRect( surface, rect );
        }

        SDL_INLINE bool                Flip( const SDL_FlipMode flip )
        {
            return SDL_FlipSurface( surface, flip );
        }

        SDL_INLINE SDL_Surface*        Duplicate( void )
        {
            return SDL_DuplicateSurface( surface );
        }

        SDL_INLINE SDL_Surface*        ConvertFormat( const SDL_PixelFormat format ) const
        {
            return SDL_ConvertSurface( surface, format );
        }

        SDL_INLINE SDL_Surface*        ConvertFormatAndColorspace( const SDL_PixelFormat format, SDL_Palette *palette, SDL_Colorspace colorspace, const SDL_PropertiesID props )
        {
            return SDL_ConvertSurfaceAndColorspace( surface, format, palette, colorspace, props );
        }

        SDL_INLINE bool                PremultiplySurfaceAlpha( const bool linear )
        {
            return SDL_PremultiplySurfaceAlpha( surface, linear );
        }

        SDL_INLINE bool                Clear( const color32f_t rgba )
        {
            return SDL_ClearSurface( surface, rgba.r, rgba.g, rgba.b, rgba.a );
        }

        SDL_INLINE bool                FillRect( const SDL_Rect *rect, const Uint32 color )
        {
            return SDL_FillSurfaceRect( surface, rect, color );
        }

        SDL_INLINE bool                FillRects( const SDL_Rect *rects, const int count, const Uint32 color )
        {
            return SDL_FillSurfaceRects( surface, rects, count, color );
        }

        SDL_INLINE bool                Blit( const Surface &src, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
        {
            return SDL_BlitSurface( src, srcrect, surface, dstrect );
        }

        SDL_INLINE bool                BlitUnchecked( const Surface &src, const SDL_Rect *srcrect, const SDL_Rect *dstrect )
        {
            return SDL_BlitSurfaceUnchecked( src, srcrect, surface, dstrect );
        }

        SDL_INLINE bool                BlitUncheckedScaled( const Surface &src, const SDL_Rect *srcrect, SDL_Surface *dst, const SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
        {
            return SDL_BlitSurfaceUncheckedScaled( src, srcrect, surface, dstrect, scaleMode );
        }

        SDL_INLINE bool                BlitScaled( const Surface &src, const SDL_Rect *srcrect, SDL_Surface *dst, const SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
        {
            return SDL_BlitSurfaceScaled( src, srcrect, surface, dstrect, scaleMode );
        }

        SDL_INLINE bool                BlitUncheckedScaled( const Surface &src, const SDL_Rect *srcrect, const SDL_Rect *dstrect, SDL_ScaleMode scaleMode)
        {
            return SDL_BlitSurfaceUncheckedScaled( src, srcrect, surface, dstrect, scaleMode );
        }

        SDL_INLINE bool                BlitTiled( const Surface &src, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
        {
            return SDL_BlitSurfaceTiled( src, srcrect, surface, dstrect );
        }

        SDL_INLINE bool                BlitTiledWithScale( const Surface &src, const SDL_Rect *srcrect, float scale, SDL_ScaleMode scaleMode, const SDL_Rect *dstrect )
        {
            return SDL_BlitSurfaceTiledWithScale( src, srcrect, scale, scaleMode, surface, dstrect );
        }

        SDL_INLINE bool                Blit9Grid( const Surface &src, const SDL_Rect *srcrect, const int left_width, const int right_width, const int top_height, const int bottom_height, const float scale, const SDL_ScaleMode scaleMode, const SDL_Rect *dstrect )
        {
            return SDL_BlitSurface9Grid( src, srcrect, left_width, right_width, top_height, bottom_height, scale, scaleMode, surface, dstrect );
        }

        SDL_INLINE Uint32              MapSurfaceRGB( const color8u_t rgb )
        {
            return  SDL_MapSurfaceRGB( surface, rgb.r, rgb.g, rgb.b );
        }

        SDL_INLINE Uint32              MapRGBA( const color8u_t rgba )
        {
            return SDL_MapSurfaceRGBA( surface, rgba.r, rgba.g, rgba.b, rgba.a );
        }

        SDL_INLINE bool                ReadPixel( const int x, const int y, color8u_t &rgba )
        {
            return SDL_ReadSurfacePixel( surface, x, y, &rgba.r, &rgba.g, &rgba.b, &rgba.a );
        }

        SDL_INLINE bool                ReadPixel( const int x, const int y, color32f_t &rgba )
        {
            return SDL_ReadSurfacePixelFloat( surface, x, y, &rgba.r, &rgba.g, &rgba.b, &rgba.a );
        }

        SDL_INLINE bool                WritePixel( const int x, const int y, const color8u_t rgba )
        {
            return SDL_WriteSurfacePixel( surface, x, y, rgba.r, rgba.g, rgba.b, rgba.a );
        }

        SDL_INLINE bool                WritePixel( const int x, const int y, const color32f_t rgba )
        {
            return SDL_WriteSurfacePixelFloat( surface, x, y, rgba.r, rgba.g, rgba.b, rgba.a );
        }

        SDL_INLINE operator bool( void ) const { return surface != nullptr; }

        SDL_INLINE operator SDL_Surface*( void ) const { return surface; }

        SDL_INLINE SDL_Surface*  GetHandle( void ) const { return surface; }

    private:
        SDL_Surface*    surface;
    };
}

#endif //!__SDL_SURFACE_HPP__