/**
 *
 * @brief Custom camera header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __CAMERA_CUSTOM_H__
#define __CAMERA_CUSTOM_H__ 1

#include "EDK3/camera.h"
#include "EDK3/geometry.h"

#include "ESAT/math.h"

#include "math_library/matrix_4.h"


namespace EDK3 {

class CameraCustom : public EDK3::Camera {
 public:
  CameraCustom();

  void initViewTarget(const float window_width,
                      const float window_height);

  void update(const double dt, const float window_width,
              const float window_height);

  void setEnabled(const bool enabled);
  void setSpeed(const float speed);
  void setSensitibity(const float sensitivity);
  void setSpeedModifier(const float speed_modifier);

  const bool enabled() const;
  const float speed() const;
  const float sensitivity() const;
  ESAT::Vec3 direction() const;
  ESAT::Vec2 window_size() const;
  //TODO something in the future:
  virtual void doCull(const Node* root_node) override;
  virtual void doRender() const override; 


  struct CamData {
	  Mat4 transform;
	  const EDK3::Geometry* geometry;
	  const EDK3::Material* material;
	  const EDK3::MaterialSettings* material_setting;
	  bool should_render;
  };

 protected:
  virtual ~CameraCustom(); 

  //TODO anything with these vars, these vars can be changed:
  ESAT::Vec2 window_size_;
  bool enabled_;
  float speed_;
  float sensitivity_;
  ESAT::Vec2 accum_mouse_offset_;
  ESAT::Vec3 view_dir_;
  double last_wheel_value_;
  float speed_modifier_;

 private:
  CameraCustom(const CameraCustom&);
  //CameraCustom(CameraCustom&&);
  CameraCustom& operator=(const CameraCustom&);
  std::vector<CamData> data_;

};

} //EDK3

#endif //__CAMERA_CUSTOM_H__
