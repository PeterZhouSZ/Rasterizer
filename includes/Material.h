#pragma once

#include <string>
#include <vector>
#include "RGBColor.h"
#include "VECTOR2D.H"
#include "Triangle.h"
#include "Light.h"
#include "Camera.H"

class Material {
protected:
  float k_shininess;
public:
  Material();
  Material(const float shininess);
  ~Material();

  const RGBColor shade(const std::vector<Light*>& lights, const Camera& camera, const Vertex3D& vertex) const;

protected:
  virtual const RGBColor phongShade(const std::vector<Light*>& lights, const Camera& camera, const Vertex3D& vertex) const = 0;
  
  const RGBColor phongEquation(const std::vector<Light*>& lights, const Vector3D& N, const Vector3D& V, const Point3D vertex_position,
    const RGBColor& vertex_color, const RGBColor& diffuse_color, const RGBColor& specular_color) const;
};

class FlatMaterial : public Material {
public:
  RGBColor k_d, k_s;

  FlatMaterial();
  FlatMaterial(const RGBColor& d, const RGBColor& s, float shininess);
  ~FlatMaterial();

protected:
  virtual const RGBColor phongShade(const std::vector<Light*>& lights, const Camera& camera, const Vertex3D& vertex) const override;

};

class TexturedMaterial : public Material {
private:
  std::vector<RGBColor> m_texture_diffuse,
                        m_texture_specular;
  int m_texture_diffuse_width,
    m_texture_diffuse_height,
    m_texture_specular_width,
    m_texture_specular_height;

public:
  TexturedMaterial();
  TexturedMaterial(const std::string texture_diffuse_file, const std::string texture_specular_file, float shininess);
  ~TexturedMaterial();

protected:
  virtual const RGBColor phongShade(const std::vector<Light*>& lights, const Camera& camera, const Vertex3D& vertex) const override;

private:
  const RGBColor getTextureColor(const std::vector<RGBColor>& texture, int texture_width, int texture_height, const Vector2D& text_coords) const;
  std::vector<RGBColor> loadTexture(int& texture_width, int& texture_height, const std::string import_path) const;
};



