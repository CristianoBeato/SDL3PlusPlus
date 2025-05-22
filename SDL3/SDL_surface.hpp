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

        inline bool Create( const int width, const int height, const SDL_PixelFormat format )
        {
            surface = SDL_CreateSurface( width, height, format );
            return surface != nullptr;
        }

        inline bool CreateFrom( const int width, const int height, const SDL_PixelFormat format, void *pixels, const int pitch )
        {
            surface = SDL_CreateSurfaceFrom( width, height, format, pixels, pitch );
            return surface != nullptr;
        }

        inline void Destroy( void )
        {
            if ( surface )
            {
                SDL_DestroySurface( surface );
                surface = nullptr;
            }
        }

        inline SDL_Palette* CreateSurfacePalette( void ) const
        {
            return SDL_CreateSurfacePalette( surface );
        }

        // TODO: finish this !!!
        //SetSurfaceColorspace
        //SetSurfaceRLE
        //SurfaceHasRLE
        //SetSurfaceColorKey
        //SurfaceHasColorKey
        //SurfaceHasAlternateImages
        //SetSurfacePalette
        //SetSurfaceColorMod
        //SetSurfaceAlphaMod
        //SetSurfaceBlendMode
        //SetSurfaceClipRect
        //ScaleSurface
        //GetSurfaceProperties
        //GetSurfaceColorspace
        //GetSurfacePalette
        //AddSurfaceAlternateImage
        //GetSurfaceImages
        //RemoveSurfaceAlternateImages
        //LockSurface
        //UnlockSurface
        //GetSurfaceColorKey
        //GetSurfaceColorMod
        //GetSurfaceAlphaMod
        //GetSurfaceBlendMode
        //GetSurfaceClipRect
        //FlipSurface
        //DuplicateSurface
        //ConvertSurface
        //ConvertSurfaceAndColorspace
        //PremultiplySurfaceAlpha
        //ClearSurface
        //FillSurfaceRect
        //FillSurfaceRects
        //BlitSurface
        //BlitSurfaceUnchecked
        //BlitSurfaceScaled
        //BlitSurfaceUncheckedScaled
        //BlitSurfaceTiled
        //BlitSurfaceTiledWithScale
        //BlitSurface9Grid
        //MapSurfaceRGB
        //MapSurfaceRGBA
        //ReadSurfacePixel
        //ReadSurfacePixelFloat
        //WriteSurfacePixel
        //WriteSurfacePixelFloat

        operator SDL_Surface*( void ) const { return surface; }
        SDL_Surface*  GetHandle( void ) const { return surface; }

    private:
        SDL_Surface*    surface;
    };
}

#endif //!__SDL_SURFACE_HPP__