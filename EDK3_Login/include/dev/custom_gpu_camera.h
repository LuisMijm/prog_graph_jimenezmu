/**
 *
 * @brief Custom GPU camera header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * No OpenGL calls are needed to override "DoCull" / "DoRender" methods.
 * Just think how to fill "CamData" structure in ".cc" with the needed data 
 * to render a Drawable.
 * 
 */


#ifndef __CUSTOM_GPU_CAMERA_H__
#define __CUSTOM_GPU_CAMERA_H__ 1

#include "EDK3/camera.h"
#include "EDK3/geometry.h"
#include "ESAT/math.h"
#include "math_library/matrix_4.h"

namespace EDK3 {

namespace dev {

class CustomGPUCamera : public EDK3::Camera {
 public:
  CustomGPUCamera();

  /** Determine which objects are visible */
  virtual void doCull(const Node* root_node) override;

  /** Renders all visible (not culled) objects */
  virtual void doRender() const override;

  struct CamData {
	  Mat4 transform;
	  const EDK3::Geometry* geometry;
	  const EDK3::Material* material;
	  const EDK3::MaterialSettings* material_setting;
	  bool should_render;
  };

 protected:
  virtual ~CustomGPUCamera();

 private:
  CustomGPUCamera(const CustomGPUCamera&);
  CustomGPUCamera& operator=(const CustomGPUCamera&);

  std::vector<CamData> data_;

}; //CustomGPUCamera

} //dev

} //EDK3

#endif //__CUSTOM_GPU_CAMERA_H__