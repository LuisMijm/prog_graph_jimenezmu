#include "dev/custom_gpu_texture.h"
#include "EDK3/dev/opengl.h"

namespace EDK3 {
    CustomGPUTexture::CustomGPUTexture() {
      internal_id_ = 0;
    }

    CustomGPUTexture::CustomGPUTexture(const CustomGPUTexture& other) {
      internal_id_ = other.internal_id_;
    }

    CustomGPUTexture& CustomGPUTexture::operator=(const CustomGPUTexture& other) {
      internal_id_ = other.internal_id_;
      return *this;
    }


    void CustomGPUTexture::init(Type t, Format internal_format, unsigned int width,
      unsigned int height, unsigned int depth) {

      Texture::init(t, internal_format, width, height, depth);
    }

    void CustomGPUTexture::set_data(const Format f,
      const EDK3::Type t,
      const void* data,
      unsigned int mipmap_LOD) {

      //glGenTextures
      //bind
      //glTexImage
      //glPixelStorei
      //glPixelstorei
    }

    void CustomGPUTexture::bind(unsigned int textUnit) const {

    }

    unsigned int CustomGPUTexture::internal_id() const {
      return internal_id_;
    }

    void CustomGPUTexture::set_min_filter(Filter f) {
      Texture::set_min_filter(f);
      switch (f)
      {
      case EDK3::Texture::F_NEAREST:
        //glTexParameteri();
        break;
      case EDK3::Texture::F_LINEAR:
        //glTexParameteri();

        break;
      case EDK3::Texture::F_NEAREST_MIPMAP_NEAREST:
        //glTexParameteri();

        break;
      case EDK3::Texture::F_LINEAR_MIPMAP_NEAREST:
        //glTexParameteri();

        break;
      case EDK3::Texture::F_NEAREST_MIPMAP_LINEAR:
        //glTexParameteri();

        break;
      case EDK3::Texture::F_LINEAR_MIPMAP_LINEAR:
        //glTexParameteri();

        break;
      }
    }
    void CustomGPUTexture::set_mag_filter(Filter f) {
      Texture::set_mag_filter(f);
      switch (f)
      {
      case EDK3::Texture::F_NEAREST:
        break;
      case EDK3::Texture::F_LINEAR:
        break;
      }

    }
    void CustomGPUTexture::set_wrap_s(Wrap c) {
      Texture::set_wrap_s(c);
      switch (c)
      {
      case EDK3::Texture::W_REPEAT:
        glTextureParameteri();

        break;
      case EDK3::Texture::W_MIRRORED_REPEAT:
        glTextureParameteri();

        break;
      case EDK3::Texture::W_CLAMP_TO_EDGE:
        glTextureParameteri();

        break;
      }
    }
    void CustomGPUTexture::set_wrap_t(Wrap c) {
      Texture::set_wrap_t(c);
      switch (c)
      {
      case EDK3::Texture::W_REPEAT:
        glTextureParameteri();

        break;
      case EDK3::Texture::W_MIRRORED_REPEAT:
        glTextureParameteri();

        break;
      case EDK3::Texture::W_CLAMP_TO_EDGE:
        glTextureParameteri();

        break;
    }
    void CustomGPUTexture::set_wrap_r(Wrap c) {
      Texture::set_wrap_r(c);
      switch (c)
      {
      case EDK3::Texture::W_REPEAT:
        glTextureParameteri();

        break;
      case EDK3::Texture::W_MIRRORED_REPEAT:
        glTextureParameteri();

        break;
      case EDK3::Texture::W_CLAMP_TO_EDGE:
        glTextureParameteri();

        break;
    }
    void CustomGPUTexture::generateMipmaps() const {
      //glGenerateMipmap()
    }
}