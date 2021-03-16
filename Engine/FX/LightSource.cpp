#include "LightSource.h"

LightSource::LightSource(vec3 position_, float ambient_, float diffuse_, float specular_, vec3 colour_) :
    position(vec3(0.0f, 0.0f, 0.0f)), ambient(0.0f), diffuse(0.0f), specular(0.0f), colour(vec3(0.0f, 0.0f, 0.0f))
{
    position = position_;
    ambient = ambient_;
    diffuse = diffuse_;
    specular = specular_;
    colour = colour_;
}

LightSource::~LightSource()
{
}

void LightSource::SetPosition(vec3 position_)
{
    position = position_;
}

void LightSource::SetAmbient(float ambient_)
{
    ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_)
{
    diffuse = diffuse_;
}

void LightSource::SetSpecular(float specular_)
{
    specular = specular_;
}

void LightSource::SetColour(vec3 colour_)
{
    colour = colour_;
}

vec3 LightSource::GetPosition() const
{
    return position;
}

float LightSource::GetAmbient() const
{
    return ambient;
}

float LightSource::GetDiffuse() const
{
    return diffuse;
}

float LightSource::GetSpecular() const
{
    return specular;
}

vec3 LightSource::GetColour() const
{
    return colour;
}
