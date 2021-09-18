#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <stdexcept>

#include "util/asf_definitions.h"

namespace asf {

namespace time {

class Time;

} // namespace time

namespace geometry {

class Frame;

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

/**
 * @brief calculateEcefMatrices calculates the rotation matrix in and out
 * of the ECEF system at a given time.
 * @param time This is the given time.
 * @return returns a pair of transformation matrixes (in, out)
 */
std::pair<TensorSP, TensorSP> calculateEcefMatrices(const time::Time& time, const Frame* parent, const Frame* ecef);

/**
 * @brief llaToVector Transforms a given position in LLA to a cartesian vector.
 * @param vector This is the output vector.
 * @param lat This is the latitude [rad].
 * @param lat This is the longitude [rad].
 * @param lat This is the altitude [m].
 */
void llaToVector(Vector& vector, double lat, double lon, double a);

/**
 * @brief vectorToLla Transforms a given position in LLA to a cartesian vector.
 * @param to This is the output vector [rad, rad, m].
 * @param from This is the ECEF input vector.
 */
void vectorToLla(Vector& to, const Vector& from);

} // namespace geometry
} // namespace asf

#endif // TRANSFORMATIONS_H
