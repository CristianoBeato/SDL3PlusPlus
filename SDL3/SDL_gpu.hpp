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
#ifndef __SDL_GPU_HPP__
#define __SDL_GPU_HPP__

#include <SDL3/SDL_gpu.h>
#include "SDL_window.hpp"

/*
==================================================================
SDLGPUDevice
==================================================================
    This class is a wrapper around SDL GPU devices. It provides a simple
    interface for creating, destroying, and managing GPU devices.
    
    Example usage:
        SDLGPUDevice gpuDevice;
        if (gpuDevice.CreateGPUDevice())
        {
            // Use the GPU device
            gpuDevice.DestroyGPUDevice();
        }
==================================================================
*/
class SDLGPUDevice
{
public:
    SDLGPUDevice( void ) : device( nullptr ) {}
    SDLGPUDevice( SDL_GPUDevice *device ) : device( device ) {}
    SDLGPUDevice( const SDLGPUDevice &device ) : device( device.device ) {}
    ~SDLGPUDevice( void ) { Destroy(); }

    SDL_INLINE bool Create( const SDL_GPUShaderFormat format_flags, const bool debug_mode, const char *name )
    {
        device = SDL_CreateGPUDevice( format_flags, debug_mode, name );
        return device != nullptr;
    }

    SDL_INLINE bool CreateWithProperties( const SDL_PropertiesID properties)
    {
        device = SDL_CreateGPUDeviceWithProperties( properties );
        return device != nullptr;
    }

    SDL_INLINE bool Destroy( void )
    {
        if( device != nullptr )
        {
            SDL_DestroyGPUDevice( device );
            device = nullptr;
        }
    }

    SDL_INLINE bool WindowSupportsSwapchainComposition( const SDLWindow &window, const SDL_GPUSwapchainComposition swapchain_composition ) const
    {
        return SDL_WindowSupportsGPUSwapchainComposition( device, window, swapchain_composition );
    }

    SDL_INLINE bool WindowSupportsPresentMode( const SDLWindow &window, const SDL_GPUPresentMode present_mode ) const
    {
        return SDL_WindowSupportsGPUPresentMode( device, window, present_mode );
    }

    SDL_INLINE bool ClaimWindowFor( const SDLWindow &window )
    {
        return SDL_ClaimWindowForGPUDevice( device, window );
    }

    SDL_INLINE void ReleaseWindowFromGPUDevice( const SDLWindow &window ) const
    {
        SDL_ReleaseWindowFromGPUDevice( const_cast<SDL_GPUDevice*>( device ), window );
    }

    SDL_INLINE const char* GetDriver( void ) const
    {
        return SDL_GetGPUDeviceDriver( device );
    }

    SDL_INLINE SDL_GPUShaderFormat GetShaderFormats( void ) const
    {
        return SDL_GetGPUShaderFormats( device );
    }

    SDL_INLINE bool SetGPUSwapchainParameters( const SDLWindow &window, const SDL_GPUSwapchainComposition swapchain_composition, const SDL_GPUPresentMode present_mode )
    {
        return SDL_SetGPUSwapchainParameters( device, window, swapchain_composition, present_mode );
    }

    SDL_INLINE bool SetAllowedFramesInFlight( const Uint32 allowed_frames_in_flight ) const
    {
        return SDL_SetGPUAllowedFramesInFlight( device, allowed_frames_in_flight );
    }

    SDL_INLINE SDL_GPUTextureFormat GetSwapchainTextureFormat( const SDLWindow &window ) const
    {
        return SDL_GetGPUSwapchainTextureFormat( device, window );
    }

    SDL_INLINE bool WaitForSwapchain( const SDLWindow &window ) const
    {
        return SDL_WaitForGPUSwapchain( device, window );
    }

    SDL_INLINE bool WaitForGPUIdle( void ) const
    {
        return SDL_WaitForGPUIdle( device );
    }

    SDL_INLINE bool TextureSupportsFormat( const SDL_GPUTextureFormat format, const SDL_GPUTextureType type, const SDL_GPUTextureUsageFlags usage ) const
    {
        return SDL_GPUTextureSupportsFormat( device, format, type, usage );
    }

    SDL_INLINE bool GPUTextureSupportsSampleCount( const SDL_GPUTextureFormat format, const SDL_GPUSampleCount sample_count )
    {
        return SDL_GPUTextureSupportsSampleCount( device, format, sample_count );
    }
    
    SDL_INLINE operator SDL_GPUDevice*( void ) const
    {
        return device;
    }

    SDL_INLINE SDL_GPUDevice* GetHandle( void ) const
    {
        return device;
    }

private:
    SDL_GPUDevice*  device;
};

/*
==================================================================
SDLGPUFence
==================================================================
    This class is a wrapper around SDL GPU fences. It provides a simple
    interface for creating, destroying, and managing GPU fences.
    
    Example usage:
        SDLGPUFence gpuFence;
        if (gpuFence.Query( device ))
        {
            // Use the GPU fence
            gpuFence.Wait( device, false ) ;
            gpuFence.Release();
        }
==================================================================
*/
class SDLGPUFence
{
public:
    SDLGPUFence( void ) : fence( nullptr ) {}
    SDLGPUFence( SDL_GPUFence *fence ) : fence( fence ) {}
    SDLGPUFence( const SDLGPUFence &fence ) : fence( fence.fence ) {}
    ~SDLGPUFence( void ){}

    SDL_INLINE bool Query( const SDLGPUDevice &device )
    {
        return SDL_QueryGPUFence( device, fence );
    }

    SDL_INLINE void WaitForFence( const SDLGPUDevice &device, bool wait_all ) const
    {
        SDL_WaitForGPUFences( device, wait_all, &fence,  1 );
    }

    SDL_INLINE void Release( const SDLGPUDevice &device )
    {
        if( fence != nullptr )
        {
            SDL_ReleaseGPUFence( device, fence );
            fence = nullptr;
        }
    }

private:
    SDL_GPUFence* fence;
};

/*
==================================================================
SDLGPUBuffer
==================================================================
    This class is a wrapper around SDL GPU buffers. It provides a simple
    interface for creating, destroying, and managing GPU buffers.
    
    Example usage:
        SDLGPUBuffer gpuBuffer;
        if (gpuBuffer.Create( device , createinfo ))
        {
            // Use the GPU buffer
            gpuBuffer.SetName( device , "My Buffer" );
            gpuBuffer.Release( device );
        }
==================================================================
*/
class SDLGPUBuffer
{
public:
    SDLGPUBuffer( void ) : buffer( nullptr ) {}
    SDLGPUBuffer( SDL_GPUBuffer *buffer ) : buffer( buffer ) {}
    SDLGPUBuffer( const SDLGPUBuffer &buffer ) : buffer( buffer.buffer ) {}
    ~SDLGPUBuffer( void ) {}

    SDL_INLINE bool Create( const SDLGPUDevice &device, const SDL_GPUBufferCreateInfo *createinfo )
    {
        buffer = SDL_CreateGPUBuffer( device, createinfo);
        return buffer != nullptr;
    }

    SDL_INLINE void Release( const SDLGPUDevice &device )
    {
        if( buffer != nullptr )
        {
            SDL_ReleaseGPUBuffer( device, buffer );
            buffer = nullptr;
        }
    }

    SDL_INLINE void SetName( const SDLGPUDevice &device, const char *name ) const
    {
        SDL_SetGPUBufferName( device, buffer, name );
    }
    
    SDL_INLINE operator SDL_GPUBuffer*( void ) const
    {
        return buffer;
    }

    SDL_INLINE SDL_GPUBuffer* GetHandle( void ) const
    {
        return buffer;
    }

private:
    SDL_GPUBuffer*  buffer;
};

/*
==================================================================
SDLGPUTransferBuffer
==================================================================
    This class is a wrapper around SDL GPU transfer buffers. It provides a simple
    interface for creating, destroying, and managing GPU transfer buffers.
    
    Example usage:
        SDLGPUTransferBuffer gpuTransferBuffer;
        if (gpuTransferBuffer.Create( device , createinfo ))
        {
            // Use the GPU transfer buffer
            gpuTransferBuffer.Release( device );
        }
==================================================================
*/
class SDLGPUTransferBuffer
{
public:
    SDLGPUTransferBuffer( void ) : transferBuffer( nullptr ) {}
    SDLGPUTransferBuffer( SDL_GPUTransferBuffer *transferBuffer ) : transferBuffer( transferBuffer ) {}
    SDLGPUTransferBuffer( const SDLGPUTransferBuffer &transferBuffer ) : transferBuffer( transferBuffer.transferBuffer ) {}
    ~SDLGPUTransferBuffer( void ) {}

    SDL_INLINE bool Create( const SDLGPUDevice &device, const SDL_GPUTransferBufferCreateInfo *createinfo )
    {
        transferBuffer = SDL_CreateGPUTransferBuffer( device, createinfo );
        return transferBuffer != nullptr;
    }

    SDL_INLINE void Release( const SDLGPUDevice &device )
    {
        if( transferBuffer != nullptr )
        {
            SDL_ReleaseGPUTransferBuffer( device, transferBuffer );
            transferBuffer = nullptr;
        }
    }

    SDL_INLINE void* Map( const SDLGPUDevice &device, const bool cycle ) const
    {
        return SDL_MapGPUTransferBuffer( device, transferBuffer, cycle );
    }

    SDL_INLINE void Unmap( const SDLGPUDevice &device )
    {
        SDL_UnmapGPUTransferBuffer( device, transferBuffer );
    }

    SDL_INLINE operator SDL_GPUTransferBuffer*( void ) const
    {
        return transferBuffer;
    }

    SDL_INLINE SDL_GPUTransferBuffer* GetHandle( void ) const
    {
        return transferBuffer;
    }

    private:
    SDL_GPUTransferBuffer* transferBuffer;
};

/*
==================================================================
SDLGPUShader
==================================================================
    This class is a wrapper around SDL GPU shaders. It provides a simple
    interface for creating, destroying, and managing GPU shaders.
    
    Example usage:
        SDLGPUShader gpuShader;
        if (gpuShader.Create( device , createinfo ))
        {
            // Use the GPU shader
            gpuShader.Release( device );
        }
==================================================================
*/
class SDLGPUShader
{
public:
    SDLGPUShader( void ) : shader( nullptr ) {}
    SDLGPUShader( SDL_GPUShader *shader ) : shader( shader ) {}
    SDLGPUShader( const SDLGPUShader &shader ) : shader( shader.shader ) {}
    ~SDLGPUShader( void ) {}

    SDL_INLINE bool Create( const SDLGPUDevice &device, const SDL_GPUShaderCreateInfo *createinfo )
    {
        shader = SDL_CreateGPUShader( device, createinfo );
        return shader != nullptr;
    }

    SDL_INLINE void Release( const SDLGPUDevice &device )
    {
        if( shader != nullptr )
        {
            SDL_ReleaseGPUShader( device, shader );
            shader = nullptr;
        }
    }

    SDL_INLINE operator SDL_GPUShader*( void ) const
    {
        return shader;
    }

    SDL_INLINE SDL_GPUShader* GetHandle( void ) const
    {
        return shader;
    }
private:
    SDL_GPUShader* shader;
};

/*
==================================================================
SDLGPUSampler
==================================================================
    This class is a wrapper around SDL GPU samplers. It provides a simple
    interface for creating, destroying, and managing GPU samplers.
    
    Example usage:
        SDLGPUSampler gpuSampler;
        if (gpuSampler.Create( device , createinfo ))
        {
            // Use the GPU sampler
            gpuSampler.Release( device );
        }
==================================================================  
*/
class SDLGPUSampler
{
public:
    SDLGPUSampler( void ) : sampler( nullptr ){}
    SDLGPUSampler( SDL_GPUSampler *sampler ) : sampler( sampler ) {}
    SDLGPUSampler( const SDLGPUSampler &sampler ) : sampler( sampler.sampler ) {}
    ~SDLGPUSampler( void ){}

    SDL_INLINE bool Create( const SDLGPUDevice &device , const SDL_GPUSamplerCreateInfo *createinfo )
    {
        sampler = SDL_CreateGPUSampler( device, createinfo );
        return sampler != nullptr;
    }

    SDL_INLINE void Release( const SDLGPUDevice &device )
    {
        if( sampler != nullptr )
        {
            SDL_ReleaseGPUSampler( device, sampler );
            sampler = nullptr;
        }
    }    
    
    SDL_INLINE operator SDL_GPUSampler*( void ) const { return sampler; }
    SDL_INLINE SDL_GPUSampler* GetHandle( void ) const { return sampler; }

private:
    SDL_GPUSampler* sampler;
};

/*
================================================================== 
SDLGPUCommandBuffer
==================================================================
    This class is a wrapper around SDL GPU command buffers. It provides a simple
    interface for creating, destroying, and managing GPU command buffers.
    
    Example usage:
        SDLGPUCommandBuffer gpuCommandBuffer;
        if (gpuCommandBuffer.Acquire( device ))
        {
            // Use the GPU command buffer
            gpuCommandBuffer.Submit();
            gpuCommandBuffer.Release();
        }
==================================================================
*/
class SDLGPUCommandBuffer
{
public:
    SDLGPUCommandBuffer( void ) : commandBuffer( nullptr ) {};
    SDLGPUCommandBuffer( SDL_GPUCommandBuffer *commandBuffer ) : commandBuffer( commandBuffer ) {}
    SDLGPUCommandBuffer( const SDLGPUCommandBuffer &commandBuffer ) : commandBuffer( commandBuffer.commandBuffer ) {}
    ~SDLGPUCommandBuffer( void ){}

    SDL_INLINE bool Acquire( const SDLGPUDevice &device )
    {
        commandBuffer = SDL_AcquireGPUCommandBuffer( device );
        return commandBuffer != nullptr;
    }

    SDL_INLINE bool Submit( void ) const
    {
        return SDL_SubmitGPUCommandBuffer( commandBuffer );
    }

    SDL_INLINE SDL_GPUFence* SubmitAndAcquireFence( void ) const
    {
        return SDL_SubmitGPUCommandBufferAndAcquireFence( commandBuffer );
    }

    SDL_INLINE bool Cancel( void ) const
    {
        SDL_CancelGPUCommandBuffer( commandBuffer );
    }

    SDL_INLINE bool AcquireSwapchainTexture( const SDLWindow &window, SDL_GPUTexture **swapchain_texture, Uint32 *swapchain_texture_width, Uint32 *swapchain_texture_height )
    {
        return SDL_AcquireGPUSwapchainTexture( commandBuffer, window, swapchain_texture, swapchain_texture_width, swapchain_texture_height );
    }

    SDL_INLINE void PushGPUVertexUniformData( Uint32 slot_index, const void *data, Uint32 length ) const
    {
        SDL_PushGPUVertexUniformData( commandBuffer, slot_index, data, length );
    }

    SDL_INLINE void PushFragmentUniformData( Uint32 slot_index, const void *data, Uint32 length ) const
    {
        SDL_PushGPUFragmentUniformData( commandBuffer, slot_index, data, length );
    }

    SDL_INLINE void PushComputeUniformData( Uint32 slot_index, const void *data, Uint32 length ) const
    {
        SDL_PushGPUComputeUniformData( commandBuffer, slot_index, data, length );
    }

    SDL_INLINE void BlitTexture( const SDL_GPUBlitInfo *info ) const
    {
        SDL_BlitGPUTexture( commandBuffer, info );
    }

    SDL_INLINE bool WaitAndAcquireGPUSwapchainTexture( const SDLWindow &window, SDL_GPUTexture **swapchain_texture, Uint32 *swapchain_texture_width, Uint32 *swapchain_texture_height ) const
    {
        return SDL_WaitAndAcquireGPUSwapchainTexture( commandBuffer, window, swapchain_texture, swapchain_texture_width, swapchain_texture_height );
    }

    SDL_INLINE void InsertDebugLabel( const char *label ) const
    {
        SDL_InsertGPUDebugLabel( commandBuffer, label );
    }

    SDL_INLINE void PushDebugGroup( const char* name ) const
    {
        SDL_PushGPUDebugGroup( commandBuffer, name );
    }

    SDL_INLINE void PopDebugGroup( void ) const
    {
        SDL_PopGPUDebugGroup( commandBuffer );
    }

    SDL_INLINE operator SDL_GPUCommandBuffer*( void ) const
    {
        return commandBuffer;
    }

    SDL_INLINE SDL_GPUCommandBuffer* GetHandle( void ) const
    {
        return commandBuffer;
    }

private:
    SDL_GPUCommandBuffer* commandBuffer;
};

/*
==================================================================
SDLGPUGraphicsPipeline
==================================================================
    This class is a wrapper around SDL GPU graphics pipelines. It provides a simple
    interface for creating, destroying, and managing GPU graphics pipelines.
    
    Example usage:
        SDLGPUGraphicsPipeline gpuGraphicsPipeline;
        if (gpuGraphicsPipeline.Create( device , createinfo ))
        {
            // Use the GPU graphics pipeline
            gpuGraphicsPipeline.Bind( commandBuffer );
            
            ... // Draw commands

            gpuGraphicsPipeline.Release( device );
        }
==================================================================
*/
class SDLGPURenderPass;
class SDLGPUGraphicsPipeline
{
public:
    SDLGPUGraphicsPipeline( void ) : graphicsPipeline( nullptr ) {}
    SDLGPUGraphicsPipeline( SDL_GPUGraphicsPipeline *pipeline ) : graphicsPipeline( pipeline ) {}
    SDLGPUGraphicsPipeline( const SDLGPUGraphicsPipeline &pipeline ) : graphicsPipeline( pipeline.graphicsPipeline ) {}
    ~SDLGPUGraphicsPipeline( void ) {}

    SDL_INLINE bool Create( const SDLGPUDevice &device, const SDL_GPUGraphicsPipelineCreateInfo *createinfo )
    {
        graphicsPipeline = SDL_CreateGPUGraphicsPipeline( device, createinfo );
        return graphicsPipeline != nullptr;
    }

    SDL_INLINE void Release( const SDLGPUDevice &device )
    {
        if( graphicsPipeline != nullptr )
        {
            SDL_ReleaseGPUGraphicsPipeline( device, graphicsPipeline );
            graphicsPipeline = nullptr;
        }
    }

    SDL_INLINE operator SDL_GPUGraphicsPipeline*( void ) const { return graphicsPipeline; }

    SDL_INLINE SDL_GPUGraphicsPipeline* GetHandle( void ) const { return graphicsPipeline; }

private:
    SDL_GPUGraphicsPipeline* graphicsPipeline;
};

/*
==================================================================
SDLGPURenderPass
==================================================================
    This class is a wrapper around SDL GPU render passes. It provides a simple
    interface for creating, destroying, and managing GPU render passes.
    
    Example usage:
        SDLGPURenderPass gpuRenderPass;
        if (gpuRenderPass.Begin( commandBuffer ))
        {
            // Use the GPU render pass
            gpuRenderPass.End();
        }
==================================================================
*/
class SDLGPURenderPass
{
public:
    SDLGPURenderPass( void ) : renderPass( nullptr ) {}
    SDLGPURenderPass( SDL_GPURenderPass *renderPass ) : renderPass( renderPass ) {}
    SDLGPURenderPass( const SDLGPURenderPass &renderPass ) : renderPass( renderPass.renderPass ) {}
    ~SDLGPURenderPass( void ) {}

    SDL_INLINE bool Begin( SDLGPUCommandBuffer command_buffer, const SDL_GPUColorTargetInfo *color_target_infos, Uint32 num_color_targets, const SDL_GPUDepthStencilTargetInfo *depth_stencil_target_info )
    {
        renderPass = SDL_BeginGPURenderPass( command_buffer, color_target_infos, num_color_targets, depth_stencil_target_info );
        return renderPass != nullptr;
    }

    SDL_INLINE void End( void ) const
    {
        SDL_EndGPURenderPass( renderPass );
    }

    SDL_INLINE void SetViewport( const SDL_GPUViewport *viewport ) const
    {
        SDL_SetGPUViewport( renderPass, viewport );
    }

    SDL_INLINE void SetScissor( const SDL_Rect *scissor ) const
    {
        SDL_SetGPUScissor( renderPass, scissor );
    }
    
    SDL_INLINE void SetBlendConstants( const SDL_FColor blend_constants ) const
    {
        SDL_SetGPUBlendConstants( renderPass, blend_constants );
    }
    
    SDL_INLINE void SetStencilReference( const Uint8 stencil_reference ) const
    {
        SDL_SetGPUStencilReference( renderPass, stencil_reference );
    }

    SDL_INLINE void BindGraphicsPipeline( const SDLGPUGraphicsPipeline &pipeline ) const
    {
        SDL_BindGPUGraphicsPipeline( renderPass, pipeline );
    }

    SDL_INLINE void BindVertexBuffers( Uint32 first_slot, const SDL_GPUBufferBinding *bindings, Uint32 num_bindings ) const
    {
        SDL_BindGPUVertexBuffers( renderPass, first_slot, bindings, num_bindings );
    }

    SDL_INLINE void BindIndexBuffer( const SDL_GPUBufferBinding *binding, SDL_GPUIndexElementSize index_element_size ) const 
    {
        SDL_BindGPUIndexBuffer( renderPass, binding, index_element_size );
    }

    SDL_INLINE void BindVertexSamplers( Uint32 first_slot, const SDL_GPUTextureSamplerBinding *texture_sampler_bindings, Uint32 num_bindings ) const 
    {
        SDL_BindGPUVertexSamplers( renderPass, first_slot, texture_sampler_bindings, num_bindings );
    }

    SDL_INLINE void BindVertexStorageTextures( Uint32 first_slot, SDL_GPUTexture *const *storage_textures, Uint32 num_bindings ) const 
    {
        SDL_BindGPUVertexStorageTextures( renderPass, first_slot, storage_textures, num_bindings );
    }

    SDL_INLINE void BindVertexStorageBuffers( Uint32 first_slot, SDL_GPUBuffer *const *storage_buffers, Uint32 num_bindings ) const 
    {
        SDL_BindGPUVertexStorageBuffers( renderPass, first_slot, storage_buffers, num_bindings );
    }

    SDL_INLINE void BindFragmentSamplers( Uint32 first_slot, const SDL_GPUTextureSamplerBinding *texture_sampler_bindings, Uint32 num_bindings ) const
    {
        SDL_BindGPUFragmentSamplers( renderPass, first_slot, texture_sampler_bindings, num_bindings );
    }

    SDL_INLINE void BindFragmentStorageTextures( Uint32 first_slot, SDL_GPUTexture *const *storage_textures, Uint32 num_bindings ) const
    {
        SDL_BindGPUFragmentStorageTextures( renderPass, first_slot, storage_textures, num_bindings );
    }

    SDL_INLINE void BindFragmentStorageBuffers( Uint32 first_slot, SDL_GPUBuffer *const *storage_buffers, Uint32 num_bindings ) const 
    {
        SDL_BindGPUFragmentStorageBuffers( renderPass, first_slot, storage_buffers, num_bindings );
    }

    SDL_INLINE void DrawIndexedPrimitives( Uint32 num_indices, Uint32 num_instances, Uint32 first_index, Sint32 vertex_offset, Uint32 first_instance ) const 
    {
        SDL_DrawGPUIndexedPrimitives(  renderPass, num_indices, num_instances, first_index, vertex_offset, first_instance );
    }

    SDL_INLINE void DrawGPUPrimitives( Uint32 num_vertices, Uint32 num_instances, Uint32 first_vertex, Uint32 first_instance )
    {
        SDL_DrawGPUPrimitives(  renderPass, num_vertices, num_instances, first_vertex, first_instance );
    }

    SDL_INLINE void DrawGPUPrimitivesIndirect( SDLGPUBuffer buffer, Uint32 offset, Uint32 draw_count ) const
    {
        SDL_DrawGPUPrimitivesIndirect( renderPass, buffer, offset, draw_count );
    }

    SDL_INLINE void DrawGPUIndexedPrimitivesIndirect( SDL_GPUBuffer *buffer, Uint32 offset, Uint32 draw_count ) const
    {
        SDL_DrawGPUIndexedPrimitivesIndirect( renderPass, buffer, offset, draw_count );
    }

    SDL_INLINE operator SDL_GPURenderPass*( void ) const
    {
        return renderPass;
    }

    SDL_INLINE SDL_GPURenderPass* GetHandle( void ) const
    {
        return renderPass;
    }
    
private:
    SDL_GPURenderPass* renderPass;
};

/*
================================================================== 
SDLGPUCopyPass
================================================================== 
*/
class SDLGPUCopyPass
{ 
public: 
    SDLGPUCopyPass( void );
    SDLGPUCopyPass( SDL_GPUCopyPass *copyPass ) : copyPass( copyPass ) {};
    SDLGPUCopyPass( SDLGPUCopyPass &copyPass) : copyPass( copyPass.copyPass ) {}
    ~SDLGPUCopyPass( void );

    SDL_INLINE bool Begin( SDLGPUCommandBuffer command_buffer )
    {
        copyPass = SDL_BeginGPUCopyPass( command_buffer );
        return copyPass != nullptr;
    }

    SDL_INLINE void End( void ) const
    {
        SDL_EndGPUCopyPass( copyPass );
    }

    SDL_INLINE void UploadToTexture( const SDL_GPUTextureTransferInfo *source, const SDL_GPUTextureRegion *destination, bool cycle ) const
    {
        SDL_UploadToGPUTexture( copyPass, source, destination, cycle );
    }

    SDL_INLINE void UploadToBuffer( const SDL_GPUTransferBufferLocation *source, const SDL_GPUBufferRegion *destination, bool cycle ) const
    {
        SDL_UploadToGPUBuffer( copyPass, source, destination, cycle );
    }

    SDL_INLINE void CopyTextureToTexture( const SDL_GPUTextureLocation *source, const SDL_GPUTextureLocation *destination, Uint32 w, Uint32 h, Uint32 d, bool cycle ) const
    {
        SDL_CopyGPUTextureToTexture( copyPass, source, destination, w, h, d, cycle );
    }

    SDL_INLINE void CopyBufferToBuffer( const SDL_GPUBufferLocation *source, const SDL_GPUBufferLocation *destination, Uint32 size, bool cycle ) const
    {
        SDL_CopyGPUBufferToBuffer( copyPass, source, destination, size, cycle );
    }

    SDL_INLINE void DownloadFromTexture( const SDL_GPUTextureRegion *source, const SDL_GPUTextureTransferInfo *destination ) const
    {
        SDL_DownloadFromGPUTexture( copyPass, source, destination );
    }

    SDL_INLINE void DownloadFromBuffer( const SDL_GPUBufferRegion *source, const SDL_GPUTransferBufferLocation *destination ) const
    {
        SDL_DownloadFromGPUBuffer( copyPass, source, destination );
    }

private:
    SDL_GPUCopyPass* copyPass;
};

/*
================================================================== 
SDLGPUTexture
==================================================================
    This class is a wrapper around SDL GPU textures. It provides a simple
    interface for creating, destroying, and managing GPU textures.
    
    Example usage:
        SDLGPUTexture gpuTexture;
        if (gpuTexture.Create( device , createinfo ))
        {
            // Use the GPU texture
            gpuTexture.SetTextureName( device , "My Texture" );
            gpuTexture.Release( device );
        }
==================================================================
*/
class SDLGPUTexture
{
public:
    SDLGPUTexture( void ) : texture( nullptr ) {}
    SDLGPUTexture( const SDLGPUTexture &ref ) : texture( ref.texture ) {}
    SDLGPUTexture( SDL_GPUTexture *texture ) : texture( texture ) {};
    ~SDLGPUTexture( void ) {}

    SDL_INLINE bool Create( const SDLGPUDevice &device, const SDL_GPUTextureCreateInfo *createinfo )
    {
        texture = SDL_CreateGPUTexture( device, createinfo );
        return texture != nullptr;
    }

    SDL_INLINE void Release( const SDLGPUDevice &device )
    {
        if( texture != nullptr )
        {
            SDL_ReleaseGPUTexture( device, texture );
            texture = nullptr;
        }
    }

    SDL_INLINE void SetTextureName( const SDLGPUDevice &device, const char *name ) const
    {
        SDL_SetGPUTextureName( device, texture, name );
    }

    SDL_INLINE void GenerateMipmaps( SDLGPUCommandBuffer commandBuffer ) const
    {
        SDL_GenerateMipmapsForGPUTexture( commandBuffer, texture );
    }

    SDL_INLINE operator SDL_GPUTexture*( void ) const
    {
        return texture;
    }

    SDL_INLINE SDL_GPUTexture* GetHandle( void ) const
    {
        return texture;
    }   

private:
    SDL_GPUTexture* texture;
};

/*
================================================================== 
SDLGPUComputePass
==================================================================
    This class is a wrapper around SDL GPU compute passes. It provides a simple
    interface for creating, destroying, and managing GPU compute passes.
    
    Example usage:
        SDLGPUComputePass gpuComputePass;
        if (gpuComputePass.Create( device , createinfo ))
        {
            // Use the GPU compute pass
            gpuComputePass.Bind( commandBuffer );
            
            ... // Dispatch compute commands

            gpuComputePass.Release( device );
        }
==================================================================
*/
class SDLGPUComputePass
{
public:
    SDLGPUComputePass( void ) : computePass( nullptr ) {}
    SDLGPUComputePass( SDL_GPUComputePass* computepass ) : computePass( computepass ) {}
    SDLGPUComputePass( const SDLGPUComputePass &ref ) : computePass( ref.computePass ) {}
    ~SDLGPUComputePass( void ) {}

    SDL_INLINE bool Begin( SDLGPUCommandBuffer command_buffer, const SDL_GPUStorageTextureReadWriteBinding *storage_texture_bindings, Uint32 num_storage_texture_bindings, const SDL_GPUStorageBufferReadWriteBinding *storage_buffer_bindings, Uint32 num_storage_buffer_bindings )
    {
        computePass = SDL_BeginGPUComputePass( command_buffer, storage_texture_bindings, num_storage_texture_bindings, storage_buffer_bindings, num_storage_buffer_bindings );
        return computePass != nullptr;
    }

    SDL_INLINE void End( void ) const
    {
        SDL_EndGPUComputePass( computePass );
    }

    SDL_INLINE void BindComputeSamplers( Uint32 first_slot, const SDL_GPUTextureSamplerBinding *texture_sampler_bindings, Uint32 num_bindings ) const
    {
        SDL_BindGPUComputeSamplers( computePass, first_slot, texture_sampler_bindings, num_bindings );
    }

    SDL_INLINE void BindComputeStorageTextures( Uint32 first_slot, SDL_GPUTexture *const *storage_textures, Uint32 num_bindings ) const
    {
        SDL_BindGPUComputeStorageTextures( computePass, first_slot, storage_textures, num_bindings );
    }

    SDL_INLINE void BindComputeStorageBuffers( Uint32 first_slot, SDL_GPUBuffer *const *storage_buffers, Uint32 num_bindings ) const
    {
        SDL_BindGPUComputeStorageBuffers( computePass, first_slot, storage_buffers, num_bindings );
    }

    SDL_INLINE void DispatchGPUCompute( Uint32 groupcount_x, Uint32 groupcount_y, Uint32 groupcount_z ) const
    {
        SDL_DispatchGPUCompute( computePass, groupcount_x, groupcount_y, groupcount_z );
    }

    SDL_INLINE bool DispatchComputeIndirect( SDL_GPUBuffer *buffer, Uint32 offset ) const
    {
        SDL_DispatchGPUComputeIndirect( computePass , buffer, offset );
    }

    SDL_INLINE operator SDL_GPUComputePass*( void ) const
    {
        return computePass;
    }

    SDL_INLINE SDL_GPUComputePass* GetHandle( void ) const
    {
        return computePass;
    }

private:
    SDL_GPUComputePass* computePass;
};

/*
================================================================== 
SDLGPUComputePipeline
==================================================================
    This class is a wrapper around SDL GPU compute pipelines. It provides a simple
    interface for creating, destroying, and managing GPU compute pipelines.
    
    Example usage:
        SDLGPUComputePipeline gpuComputePipeline;
        if (gpuComputePipeline.Create( device , createinfo ))
        {
            // Use the GPU compute pipeline
            gpuComputePipeline.Bind( computePass );
            
            ... // Dispatch compute commands

            gpuComputePipeline.Release( device );
        }
==================================================================
*/
class SDLGPUComputePipeline
{
public:
    SDLGPUComputePipeline( void ) : computePipeline( nullptr ) {}
    SDLGPUComputePipeline( SDL_GPUComputePipeline *pipeline ) : computePipeline( pipeline ) {}
    SDLGPUComputePipeline( const SDLGPUComputePipeline &ref ) : computePipeline( ref.computePipeline ) {}
    ~SDLGPUComputePipeline( void ) {}
    
    SDL_INLINE bool Create( const SDLGPUDevice &device, const SDL_GPUComputePipelineCreateInfo *createinfo )
    {
        computePipeline = SDL_CreateGPUComputePipeline( device, createinfo );
        return computePipeline != nullptr;
    }

    SDL_INLINE void Bind( SDLGPUComputePass compute_pass ) const
    {
        SDL_BindGPUComputePipeline( compute_pass, const_cast<SDL_GPUComputePipeline*>( computePipeline ) );
    }

    SDL_INLINE void Release( const SDLGPUDevice &device )
    {
        if( computePipeline != nullptr )
        {
            SDL_ReleaseGPUComputePipeline( device, computePipeline );
            computePipeline = nullptr;
        }
    }

    SDL_INLINE operator SDL_GPUComputePipeline*( void ) const
    {
        return computePipeline;
    }

    SDL_INLINE SDL_GPUComputePipeline* GetHandle( void ) const
    {
        return computePipeline;
    }

private:
    SDL_GPUComputePipeline*     computePipeline;
};

#endif //!__SDL_GPU_HPP__