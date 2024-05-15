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

    GLenum GetOpenGLTextureType(EDK3::Texture::Type t) {
        GLenum type = GL_TEXTURE_2D;
        switch (t) {
        case Texture::Type::T_Invalid:
            //printf("Invalid texture type.\n");
            //exit(EXIT_FAILURE);
            break;
        case Texture::Type::T_1D:
            type = GL_TEXTURE_1D;
            break;
        case Texture::Type::T_3D:
            type = GL_TEXTURE_3D;
            break;
        case Texture::Type::T_CUBEMAP:
            type = GL_TEXTURE_CUBE_MAP;
            break;
        }
        return type;
    }

    GLenum GetOpenGLDataPixelType(EDK3::Type t) {
        GLenum type = GL_UNSIGNED_BYTE;
        switch (t)
        {
        case EDK3::Type::T_UBYTE:
            type = GL_UNSIGNED_BYTE;
            break;
        case EDK3::Type::T_SHORT:
            type = GL_SHORT;
            break;
        case EDK3::Type::T_USHORT:
            type = GL_UNSIGNED_SHORT;
            break;
        case EDK3::Type::T_INT:
            type = GL_INT;
            break;
        case EDK3::Type::T_UINT:
            type = GL_UNSIGNED_INT;
            break;
        case EDK3::Type::T_FLOAT:
            type = GL_FLOAT;
            break;
        }
        return type;
    }

    GLenum GetOpenGLFormat(EDK3::Texture::Format t) {
        GLint format = GL_RED;
        switch (t) {
        case EDK3::Texture::Format::F_None:
            format = GL_NONE;
            break;
        case EDK3::Texture::Format::F_R:
            format = GL_RED;
            break;
        case EDK3::Texture::Format::F_RG:
            format = GL_RG;
            break;
        case EDK3::Texture::Format::F_RGB:
            format = GL_RGB;
            break;
        case EDK3::Texture::Format::F_BGR:
            format = GL_BGR;
            break;
        case EDK3::Texture::Format::F_BGRA:
            format = GL_BGRA;
            break;
        case EDK3::Texture::Format::F_RGBA:
            format = GL_RGBA;
            break;
        case EDK3::Texture::Format::F_DEPTH:
            format = GL_DEPTH_COMPONENT;
            break;
        case EDK3::Texture::Format::F_DEPTH32:
            format = GL_DEPTH_COMPONENT32;
            break;
        }
        return format;
    }

    void CustomGPUTexture::init(Type t, Format internal_format, unsigned int width,
      unsigned int height, unsigned int depth) {

      Texture::init(t, internal_format, width, height, depth);
    }

    void CustomGPUTexture::set_data(const Format f,
      const EDK3::Type t,
      const void* data,
      unsigned int mipmap_LOD) {

      glGenTextures(1, &internal_id_);
      GLenum texture_type = GetOpenGLTextureType(type());
      GLenum pixel_type = GetOpenGLDataPixelType(t);
      GLint internal_format = GetOpenGLFormat(format());
      GLint external_format = GetOpenGLFormat(f);
      glBindTexture(texture_type, internal_id_);

      switch (texture_type){
      case GL_TEXTURE_1D:
          glTexImage1D(texture_type, mipmap_LOD, 
                       internal_format, width(), 0, 
                       external_format, pixel_type, data);
          break;

      case GL_TEXTURE_2D:
          glTexImage2D(texture_type, mipmap_LOD,
              internal_format, width(), height(), 0,
              external_format, pixel_type, data);
          break;
      case GL_TEXTURE_3D:
          glTexImage3D(texture_type, mipmap_LOD,
              internal_format, width(), height(),
              depth(), 0,
              external_format, pixel_type, data);
          break;
      }
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glPixelStorei(GL_UNPACK_LSB_FIRST, 1);
      generateMipmaps();
      set_wrap(EDK3::Texture::Wrap::W_REPEAT);
      set_min_filter(EDK3::Texture::Filter::F_LINEAR);
      set_mag_filter(EDK3::Texture::Filter::F_LINEAR);

    }

    void CustomGPUTexture::bind(unsigned int textUnit) const {
        GLenum texture_type = GetOpenGLTextureType(type());
        glActiveTexture(GL_TEXTURE0 + textUnit);
        glBindTexture(texture_type, internal_id_);
    }

    unsigned int CustomGPUTexture::internal_id() const {
      return internal_id_;
    }

    GLenum GetOpenGLFilterType(EDK3::Texture::Filter f) {
        GLenum filter_type = GL_NEAREST;

        switch (f) {
        case EDK3::Texture::F_NEAREST:
            filter_type = GL_NEAREST;
            break;

        case EDK3::Texture::F_LINEAR:
            filter_type = GL_LINEAR;
            break;

        case EDK3::Texture::F_NEAREST_MIPMAP_NEAREST:
            filter_type = GL_NEAREST_MIPMAP_NEAREST;
            break;

        case EDK3::Texture::F_LINEAR_MIPMAP_NEAREST:
            filter_type = GL_LINEAR_MIPMAP_NEAREST;
            break;

        case EDK3::Texture::F_NEAREST_MIPMAP_LINEAR:
            filter_type = GL_NEAREST_MIPMAP_LINEAR;
            break;

        case EDK3::Texture::F_LINEAR_MIPMAP_LINEAR:
            filter_type = GL_LINEAR_MIPMAP_NEAREST;
            break;
        }
        return filter_type;
    }

    GLenum GetOpenGLWrappingType(EDK3::Texture::Wrap c) {
        GLenum wrapping_type = GL_REPEAT;
        switch (c){

        case Texture::Wrap::W_REPEAT:
            wrapping_type = GL_REPEAT;
            break;

        case EDK3::Texture::W_MIRRORED_REPEAT:
            wrapping_type = GL_MIRRORED_REPEAT;
            break;

        case EDK3::Texture::W_CLAMP_TO_EDGE:
            wrapping_type = GL_CLAMP_TO_EDGE;
            break;
        }
        return wrapping_type;
    }

    void CustomGPUTexture::set_min_filter(Filter f) {
      Texture::set_min_filter(f);
      GLenum texture_type = GetOpenGLTextureType(type());
      GLenum filter_type = GetOpenGLFilterType(f);

      glBindTexture(texture_type, internal_id_);
      glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, filter_type);
    }

    void CustomGPUTexture::set_mag_filter(Filter f) {
      Texture::set_mag_filter(f);
      GLenum texture_type = GetOpenGLTextureType(type());
      GLenum filter_type = GetOpenGLFilterType(f);

      glBindTexture(texture_type, internal_id_);
      glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, filter_type);
    }

    void CustomGPUTexture::set_wrap_s(Wrap c) {
      Texture::set_wrap_s(c);
      GLenum texture_type = GetOpenGLTextureType(type());

      GLenum wrapping_type = GetOpenGLWrappingType(c);

      glBindTexture(texture_type, internal_id_);
      glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, wrapping_type);
    }
    void CustomGPUTexture::set_wrap_t(Wrap c) {
      Texture::set_wrap_t(c);
      GLenum texture_type = GetOpenGLTextureType(type());

      GLenum wrapping_type = GetOpenGLWrappingType(c);

      glBindTexture(texture_type, internal_id_);
      glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, wrapping_type);
    }

    void CustomGPUTexture::set_wrap_r(Wrap c) {
      Texture::set_wrap_r(c);
      GLenum texture_type = GetOpenGLTextureType(type());

      GLenum wrapping_type = GetOpenGLWrappingType(c);

      glBindTexture(texture_type, internal_id_);
      glTexParameteri(texture_type, GL_TEXTURE_WRAP_R, wrapping_type);
    }

    void CustomGPUTexture::generateMipmaps() const {
        GLenum texture_type = GetOpenGLTextureType(Type());
        glGenerateMipmap(texture_type);
    }

    CustomGPUTexture::~CustomGPUTexture()
    {
    }
}