#include "OrthographicCamera.h"
#include <limits>
OrthographicCamera::OrthographicCamera()
  : Camera() {

}

OrthographicCamera::OrthographicCamera(const Point3D& position, const Vector3D& forward, const Vector3D& up, const uint32_t near, const uint32_t far, const float zoom)
  : Camera(position, forward, up, near, far, zoom) {

}

OrthographicCamera::~OrthographicCamera() {

}

const Point3D OrthographicCamera::imageSpaceToWorldSpace(const uint16_t pixel_image_x, const uint16_t pixel_image_y) const {
  //TODO: anctual conversion
  return Point3D();
}


const Triangle2D OrthographicCamera::worldSpaceToScreenSpace(const Triangle3D& triangle3D) const {
  //TODO: actual projection
  return Triangle2D();
}

const float OrthographicCamera::getDepth(const Point3D& pixel_world, const Triangle3D& triangle) const {
  bool out_hit;
  const Point3D intersection_point = triangle.intersect(out_hit, pixel_world, this->m_forward);
  if (!out_hit) {
    return std::numeric_limits<float>::max();
  }

  return pixel_world.distance(intersection_point);
}
