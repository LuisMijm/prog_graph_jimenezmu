

#include "dev/custom_gpu_manager.h"
#include "dev/custom_gpu_shader.h"
#include "dev/custom_gpu_program.h"
#include "dev/custom_gpu_buffer.h"
#include "dev/custom_gpu_texture.h"


namespace EDK3 {
namespace dev {


  void CustomGPUManager::newShader(EDK3::ref_ptr < EDK3::dev::Shader>* output) {
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
    text->init(EDK3::Texture::Type::T_3D, internal_format, width, height, depth);
  }

  void CustomGPUManager::clearFrameBuffer(const float rgba[4], const unsigned int FrameBufferOrMask)
  {
      glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  void CustomGPUManager::enableDepthTest(const CompareFunc f)
  {
      glEnable(GL_DEPTH_TEST);
      switch (f) {
      case EDK3::dev::GPUManager::kCompareFunc_Never: glDepthFunc(GL_NEVER); break;
      case EDK3::dev::GPUManager::kCompareFunc_Less: glDepthFunc(GL_LESS); break;
      case EDK3::dev::GPUManager::kCompareFunc_Equal: glDepthFunc(GL_EQUAL); break;
      case EDK3::dev::GPUManager::kCompareFunc_LessOrEqual: glDepthFunc(GL_LEQUAL); break;
      case EDK3::dev::GPUManager::kCompareFunc_NotEqual: glDepthFunc(GL_NOTEQUAL); break;
      case EDK3::dev::GPUManager::kCompareFunc_GreaterOrEqual: glDepthFunc(GL_GEQUAL); break;
      case EDK3::dev::GPUManager::kCompareFunc_Greater: glDepthFunc(GL_GREATER); break;
      case EDK3::dev::GPUManager::kCompareFunc_Always: glDepthFunc(GL_ALWAYS); break;
      }
  }

  void CustomGPUManager::disableDepthTest()
  {
      glDisable(GL_DEPTH_TEST);
  }
  
  void CustomGPUManager::enableBlend(BlendParam source, BlendParam destination, BlendOp operation, const float ConstantColor[4])
  {
      glEnable(GL_BLEND);
      GLenum sfactor = 0;
      switch (source) {
      case kBlendParam_Zero: sfactor = GL_ZERO; break;
      case kBlendParam_One: sfactor = GL_ONE; break;
      case kBlendParam_SourceColor: sfactor = GL_SRC_COLOR; break;
      case kBlendParam_OneMinusSourceColor: sfactor = GL_ONE_MINUS_SRC_COLOR; break;
      case kBlendParam_DestinationColor: sfactor = GL_DST_COLOR; break;
      case kBlendParam_OneMinusDestinationColor: sfactor = GL_ONE_MINUS_DST_COLOR; break;
      case kBlendParam_SourceAlpha: sfactor = GL_SRC_ALPHA; break;
      case kBlendParam_OneMinusSourceAlpha: sfactor = GL_ONE_MINUS_SRC_ALPHA; break;
      case kBlendParam_DestinationAlpha: sfactor = GL_DST_ALPHA; break;
      case kBlendParam_OneMinusDestinationAlpha: sfactor = GL_ONE_MINUS_DST_ALPHA; break;
      case kBlendParam_ConstantColor: sfactor = GL_CONSTANT_COLOR; break;
      case kBlendParam_OneMinusConstantColor: sfactor = GL_ONE_MINUS_CONSTANT_COLOR; break;
      case kBlendParam_ConstantAlpha: sfactor = GL_CONSTANT_ALPHA; break;
      case kBlendParam_OneMinusConstantAlpha: sfactor = GL_ONE_MINUS_CONSTANT_ALPHA; break;
      case kBlendParam_SourceAlphaSaturate: sfactor = GL_SRC_ALPHA_SATURATE; break;
      default: break;
      }

      GLenum dfactor = 0;
      switch (destination)
      {
      case kBlendParam_Zero: dfactor = GL_ZERO; break;
      case kBlendParam_One: dfactor = GL_ONE; break;
      case kBlendParam_SourceColor: dfactor = GL_SRC_COLOR; break;
      case kBlendParam_OneMinusSourceColor: dfactor = GL_ONE_MINUS_SRC_COLOR; break;
      case kBlendParam_DestinationColor: dfactor = GL_DST_COLOR; break;
      case kBlendParam_OneMinusDestinationColor: dfactor = GL_ONE_MINUS_DST_COLOR; break;
      case kBlendParam_SourceAlpha: dfactor = GL_SRC_ALPHA; break;
      case kBlendParam_OneMinusSourceAlpha: dfactor = GL_ONE_MINUS_SRC_ALPHA; break;
      case kBlendParam_DestinationAlpha: dfactor = GL_DST_ALPHA; break;
      case kBlendParam_OneMinusDestinationAlpha: dfactor = GL_ONE_MINUS_DST_ALPHA; break;
      case kBlendParam_ConstantColor: dfactor = GL_CONSTANT_COLOR; break;
      case kBlendParam_OneMinusConstantColor: dfactor = GL_ONE_MINUS_CONSTANT_COLOR; break;
      case kBlendParam_ConstantAlpha: dfactor = GL_CONSTANT_ALPHA; break;
      case kBlendParam_OneMinusConstantAlpha: dfactor = GL_ONE_MINUS_CONSTANT_ALPHA; break;
      case kBlendParam_SourceAlphaSaturate: dfactor = GL_SRC_ALPHA_SATURATE; break;
      default: break;
      }

      switch (operation) {
      case kBlendOp_Add: glBlendEquation(GL_FUNC_ADD); break;
      case kBlendOp_Subtract: glBlendEquation(GL_FUNC_SUBTRACT); break;
      case kBlendOp_ReverseSubtract: glBlendEquation(GL_FUNC_REVERSE_SUBTRACT); break;
      case kBlendOp_Min: glBlendEquation(GL_MIN); break;
      case kBlendOp_Max: glBlendEquation(GL_MAX); break;
      }

      glBlendFunc(sfactor, dfactor);
      if (ConstantColor != nullptr) {
          glBlendColor(ConstantColor[0], ConstantColor[1], ConstantColor[2], ConstantColor[3]);
      }
      else {
          glBlendColor(1, 1, 1, 1);
      }
      GPUManager::Instance()->CheckGLError("Error en enable blend");
  }
  void CustomGPUManager::disableBlend()
  {
      glDisable(GL_BLEND);
  }

  void CustomGPUManager::enableCullFaces(const FaceType f)
  {
      glEnable(GL_CULL_FACE);
      switch (f)
      {
      case EDK3::dev::GPUManager::kFace_Back: glCullFace(GL_BACK); break;
      case EDK3::dev::GPUManager::kFace_Front: glCullFace(GL_FRONT); break;
      case EDK3::dev::GPUManager::kFace_FrontAndBack: glCullFace(GL_FRONT_AND_BACK); break;
      }
  }

  void CustomGPUManager::disableCullFaces()
  {
      glDisable(GL_CULL_FACE);
  }

  void CustomGPUManager::enableScissor(int x, int y, unsigned int width, unsigned int height)
  {
      glEnable(GL_SCISSOR_TEST);
      glScissor(x, y, width, height);
  }

  void CustomGPUManager::disableScissor()
  {
      glDisable(GL_SCISSOR_TEST);
  }

  void CustomGPUManager::enableVertexAttribute(const EDK3::dev::Buffer* buffer, const unsigned int attribute_index, const EDK3::Type type, const bool normalized, const unsigned int offset, const unsigned int stride)
  {
      buffer->bind((EDK3::dev::Buffer::kTarget_Vertex_Data));
      switch (type)
      {
      case EDK3::T_FLOAT_1:
          glVertexAttribPointer(attribute_index, 1, GL_FLOAT, normalized, stride, (void*)offset);
          break;
      case EDK3::T_FLOAT_2:
          glVertexAttribPointer(attribute_index, 2, GL_FLOAT, normalized, stride, (void*)offset);
          break;
      case EDK3::T_FLOAT_3:
          glVertexAttribPointer(attribute_index, 3, GL_FLOAT, normalized, stride, (void*)offset);
          break;
      case EDK3::T_FLOAT_4:
          glVertexAttribPointer(attribute_index, 4, GL_FLOAT, normalized, stride, (void*)offset);
          break;

      case EDK3::T_INT_1:
          glVertexAttribPointer(attribute_index, 1, GL_INT, normalized, stride, (void*)offset);
          break;
      case EDK3::T_INT_2:
          glVertexAttribPointer(attribute_index, 2, GL_INT, normalized, stride, (void*)offset);
          break;
      case EDK3::T_INT_3:
          glVertexAttribPointer(attribute_index, 3, GL_INT, normalized, stride, (void*)offset);
          break;
      case EDK3::T_INT_4:
          glVertexAttribPointer(attribute_index, 4, GL_INT, normalized, stride, (void*)offset);
          break;

      case EDK3::T_UINT_1:
          glVertexAttribPointer(attribute_index, 1, GL_UNSIGNED_INT, normalized, stride, (void*)offset);
          break;
      case EDK3::T_UINT_2:
          glVertexAttribPointer(attribute_index, 2, GL_UNSIGNED_INT, normalized, stride, (void*)offset);
          break;
      case EDK3::T_UINT_3:
          glVertexAttribPointer(attribute_index, 3, GL_UNSIGNED_INT, normalized, stride, (void*)offset);
          break;
      case EDK3::T_UINT_4:
          glVertexAttribPointer(attribute_index, 4, GL_UNSIGNED_INT, normalized, stride, (void*)offset);
          break;


      case EDK3::T_UBYTE_1:
          glVertexAttribPointer(attribute_index, 1, GL_UNSIGNED_BYTE, normalized, stride, (void*)offset);
          break;
      case EDK3::T_UBYTE_2:
          glVertexAttribPointer(attribute_index, 2, GL_UNSIGNED_BYTE, normalized, stride, (void*)offset);
          break;
      case EDK3::T_UBYTE_3:
          glVertexAttribPointer(attribute_index, 3, GL_UNSIGNED_BYTE, normalized, stride, (void*)offset);
          break;
      case EDK3::T_UBYTE_4:
          glVertexAttribPointer(attribute_index, 4, GL_UNSIGNED_BYTE, normalized, stride, (void*)offset);
          break;
      }
      glEnableVertexAttribArray(attribute_index);
  }

  void CustomGPUManager::disableVertexAttribute(const unsigned int attrib_index)
  {
      glDisableVertexAttribArray(attrib_index);
  }

  void CustomGPUManager::drawElements(const DrawMode mode, unsigned int count, const EDK3::dev::Buffer* buffer, const EDK3::Type element_type, const unsigned int offset) const
  {
      buffer->bind(EDK3::dev::Buffer::kTarget_Elements);
      GLenum draw = 0;
      switch (mode)
      {
      case kDrawMode_Triangles: draw = GL_TRIANGLES; break;
      case kDrawMode_TriangleStrip: draw = GL_TRIANGLE_STRIP; break;
      case kDrawMode_Points: draw = GL_POINTS; break;
      case kDrawMode_Lines: draw = GL_LINES; break;
      case kDrawMode_LineStrip: draw = GL_LINE_STRIP; break;
      case kDrawMode_LineLoop: draw = GL_LINE_LOOP; break;
      }

      GLenum type = 0;
      switch (element_type)
      {
      case EDK3::T_UBYTE: type = GL_UNSIGNED_BYTE; break;
      case EDK3::T_USHORT: type = GL_UNSIGNED_SHORT; break;
      case EDK3::T_UINT: type = GL_UNSIGNED_INT; break;
      }
      
      glDrawElements(draw, count, type, (void*)offset);
  }
  

}
}