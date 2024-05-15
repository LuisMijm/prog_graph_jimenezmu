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
#include "ESAT/math.h"

namespace EDK3 {

namespace dev {

class CustomGPUCamera : public EDK3::Camera {
 public:
  CustomGPUCamera();

  /** Determine which objects are visible */
  virtual void doCull(const Node* root_node) override;

  /** Renders all visible (not culled) objects */
  virtual void doRender() const override;

  struct CamData;

  /*
  struct NodeData {
	  EDK3::Geometry* geo;
	  EDK3::Material* mat;
	  EDK3::MaterialSettings* mat_settings;
	  Mat4 model; //float [16]
  };

  struct CamData {
	  std::vector<NodeData> data;
  };
  */



 protected:
  virtual ~CustomGPUCamera();

 private:
  CustomGPUCamera(const CustomGPUCamera&);
  CustomGPUCamera& operator=(const CustomGPUCamera&);

  EDK3::scoped_ptr<CamData> data_;

}; //CustomGPUCamera

} //dev

} //EDK3

#endif //__CUSTOM_GPU_CAMERA_H__