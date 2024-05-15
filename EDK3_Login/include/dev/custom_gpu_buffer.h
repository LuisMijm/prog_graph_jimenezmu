/**
 *
 * @brief Custom GPU buffer header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * Check the following OpenGL functions:
 *   glBindBuffer
 *   glBufferData
 *   glBufferSubData
 *   glDeleteBuffers
 *   glGenBuffers
 * 
 */

#ifndef __CUSTOM_GPU_BUFFER_H__
#define __CUSTOM_GPU_BUFFER_H__ 1

#include "EDK3/dev/buffer.h"

typedef unsigned int GLuint;

namespace EDK3 {

namespace dev {

class CustomGPUBuffer : public EDK3::dev::Buffer {
 public:
  CustomGPUBuffer();
  virtual void init(unsigned int size) override;
  virtual void bind(const Target t) const override;
  virtual unsigned int size() const override;
  virtual void uploadData(const void *data, unsigned int size,
                          unsigned int offset = 0) override;
  virtual void release() override;


 protected:
  virtual ~CustomGPUBuffer();
  GLuint internal_id_;
  int size_;
  EDK3::dev::Buffer::Target target_;

 private:
  CustomGPUBuffer(const CustomGPUBuffer& other);
  CustomGPUBuffer& operator=(const CustomGPUBuffer& other);

}; //CustomGPUBuffer

} //dev

} //EDK3

#endif //__CUSTOM_GPU_BUFFER_H__
