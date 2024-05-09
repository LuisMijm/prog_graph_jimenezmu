

#include "dev/custom_gpu_manager.h"
#include "dev/custom_gpu_shader.h"
#include "dev/custom_gpu_program.h"
#include "dev/custom_gpu_buffer.h"
#include "dev/custom_gpu_texture.h"


namespace EDK3 {
namespace dev {


  void CustomGPUManager::newShader(EDK3::ref_ptr < EDK3::dev::Shader> *output) {
    output->allocT<CustomGPUShader>();
  }

  void CustomGPUManager::newProgram(EDK3::ref_ptr<EDK3::dev::Program> *output) {
    output->allocT<CustomGPUProgram>();
  }

  void CustomGPUManager::newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>* output) {
    output->allocT<CustomGPUBuffer>();
  }
  void CustomGPUManager::newTexture1D(const Texture::Format internal_format,
    const unsigned int size,
    EDK3::ref_ptr<Texture>* output) {
    CustomGPUTexture* text = output->allocT<CustomGPUTexture>();
    text->init(EDK3::Texture::Type::T_1D, internal_format, size, 1, 1);
  }

  void CustomGPUManager::newTexture2D(const Texture::Format internal_format,
    const unsigned int width, const unsigned int height,
    EDK3::ref_ptr<Texture>* output) {
    CustomGPUTexture* text = output->allocT<CustomGPUTexture>();
    text->init(EDK3::Texture::Type::T_2D, internal_format, width, height, 1);
  }

  void CustomGPUManager::newTexture3D(const Texture::Format internal_format,
    const unsigned int width, const unsigned int height,
    const unsigned int depth,
    EDK3::ref_ptr<Texture>* output) {
    CustomGPUTexture* text = output->allocT<CustomGPUTexture>();
    text->init(EDK3::Texture::Type::T_1D, internal_format, width, height, depth);
  }

  void CustomGPUManager::clearFrameBuffer(const float rgba[4], const unsigned int FrameBufferOrMask) {

  }

  void CustomGPUManager::enableDepthTest(const CompareFunc f) {

  }

  void CustomGPUManager::disableDepthTest() {

  }

  void CustomGPUManager::enableBlend(BlendParam source, BlendParam destination, BlendOp operation, const float ConstantColor[4]) {

  }

  void CustomGPUManager::disableBlend(){

  }

  /*
  * DrawElements
  * enableVertexAttribute, disableVertexAttribute
  * 
  */

  void CustomGPUManager::enableScissor(int x, int y, unsigned int width, unsigned int height) {
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, width, height);
  }

  void CustomGPUManager::disableScissor() {
    glDisable(GL_SCISSOR_TEST);
  }
  void CustomGPUManager::enableVertexAttribute(const EDK3::dev::Buffer* buffer, const unsigned int attribute_index, const EDK3::Type type, const bool normalized, const unsigned int offset, const unsigned int stride) {

  }

  void CustomGPUManager::disableVertexAttribute(const unsigned int attrib_index) {
    
  }

  void CustomGPUManager::drawElements(const DrawMode mode, unsigned int count, const EDK3::dev::Buffer* buffer, const EDK3::Type element_type, const unsigned int offset) const {
      GLenum m = GL_TRIANGLES;
      switch (mode) {

      case kDrawMode_Triangles:
          m = GL_TRIANGLES;
          break;

      case kDrawMode_TriangleStrip:
          m = GL_TRIANGLE_STRIP;
          break;

      case kDrawMode_Points:
          m = GL_POINTS;
          break;

      case kDrawMode_Lines:
          m = GL_LINES;
          break;

      case kDrawMode_LineStrip:
          m = GL_LINE_STRIP;
          break;

      case kDrawMode_LineLoop:
          m = GL_LINE_LOOP;
          break;
      }

      GLenum t = GL_UNSIGNED_BYTE;
      switch (element_type) {
      case T_USHORT:
          t = GL_UNSIGNED_SHORT;
          break;

      case T_UINT:
          t = GL_UNSIGNED_INT;
          break;
      }

      buffer->bind(EDK3::dev::Buffer::Target::kTarget_Elements);
      glDrawElements(m, count, t, (GLvoid*) offset);
  }
}
}