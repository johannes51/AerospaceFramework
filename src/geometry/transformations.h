#pragma once

#include <stdexcept>

#include "util/asf_definitions.h"

namespace asf {
namespace geometry {

/**
 * @brief rotate calculates the rotation matrix in 3 dimensions for a angle
 * about an arbitrary axis
 * @param angle The rotation angle
 * @param axis The rotation axis
 * @return returns a 3 by 3 rotation matrix
 */
Tensor rotate(double angle, const Vector& axis);

/**
 * @brief rotateX calculates the rotation matrix about the x-axis
 * @param angle The rotation angle
 * @return returns a rotation matrix
 */
Tensor rotateX(double angle);

/**
 * @brief rotateY calculates the rotation matrix about the y-axis
 * @param angle The rotation angle
 * @return returns a rotation matrix
 */
Tensor rotateY(double angle);

/**
 * @brief rotateZ calculates the rotation matrix about the z-axis
 * @param angle The rotation angle
 * @return returns a rotation matrix
 */
Tensor rotateZ(double angle);

/**
 * @brief calculateEulerMatrixInverse calculates the inverse of the Euler matrix
 * about two angles This is used to get the attitude of the solar arrays from
 * the satellite coordinate system
 * @param theta The angle about the local y axis
 * @param psi The angle about the local z axis
 * @return returns a transformation matrix
 */
Tensor calculateEulerMatrixInverse(double theta, double psi);

} // namespace geometry
} // namespace asf
