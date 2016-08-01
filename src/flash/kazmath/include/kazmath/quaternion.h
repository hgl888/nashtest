/*
Copyright (c) 2008, Luke Benstead.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


#include "utility.h"

struct kmMat4;
struct kmMat3;
struct kmVec3;

typedef struct kmQuaternion {
    float x;
    float y;
    float z;
    float w;
} kmQuaternion;

kmQuaternion* const kmQuaternionConjugate(kmQuaternion* pOut, const kmQuaternion* pIn); ///< Returns pOut, sets pOut to the conjugate of pIn

const float     kmQuaternionDot(const kmQuaternion* q1, const kmQuaternion* q2); ///< Returns the dot product of the 2 quaternions

kmQuaternion* kmQuaternionExp(kmQuaternion* pOut, const kmQuaternion* pIn); ///< Returns the exponential of the quaternion

///< Makes the passed quaternion an identity quaternion

kmQuaternion* kmQuaternionIdentity(kmQuaternion* pOut);

///< Returns the inverse of the passed Quaternion

kmQuaternion* kmQuaternionInverse(kmQuaternion* pOut,
                                            const kmQuaternion* pIn);

///< Returns true if the quaternion is an identity quaternion

int kmQuaternionIsIdentity(const kmQuaternion* pIn);

///< Returns the length of the quaternion

float kmQuaternionLength(const kmQuaternion* pIn);

///< Returns the length of the quaternion squared (prevents a sqrt)

float kmQuaternionLengthSq(const kmQuaternion* pIn);

///< Returns the natural logarithm

kmQuaternion* kmQuaternionLn(kmQuaternion* pOut, const kmQuaternion* pIn);

///< Multiplies 2 quaternions together

kmQuaternion* kmQuaternionMultiply(kmQuaternion* pOut, const kmQuaternion* q1, const kmQuaternion* q2);

///< Normalizes a quaternion

kmQuaternion* kmQuaternionNormalize(kmQuaternion* pOut, const kmQuaternion* pIn);

///< Rotates a quaternion around an axis

kmQuaternion* kmQuaternionRotationAxis(kmQuaternion* pOut, const struct kmVec3* pV, float angle);

///< Creates a quaternion from a rotation matrix

kmQuaternion* kmQuaternionRotationMatrix(kmQuaternion* pOut, const struct kmMat3* pIn);

///< Create a quaternion from yaw, pitch and roll

kmQuaternion* kmQuaternionRotationYawPitchRoll(kmQuaternion* pOut, float yaw, float pitch, float roll);
///< Interpolate between 2 quaternions
kmQuaternion* kmQuaternionSlerp(kmQuaternion* pOut, const kmQuaternion* q1, const kmQuaternion* q2, float t);

///< Get the axis and angle of rotation from a quaternion
void kmQuaternionToAxisAngle(const kmQuaternion* pIn, struct kmVec3* pVector, float* pAngle);

///< Scale a quaternion
kmQuaternion* kmQuaternionScale(kmQuaternion* pOut, const kmQuaternion* pIn, float s);
kmQuaternion* kmQuaternionAssign(kmQuaternion* pOut, const kmQuaternion* pIn);
kmQuaternion* kmQuaternionAdd(kmQuaternion* pOut, const kmQuaternion* pQ1, const kmQuaternion* pQ2);
kmQuaternion* kmQuaternionRotationBetweenVec3(kmQuaternion* pOut, const struct kmVec3* vec1, const struct kmVec3* vec2, const struct kmVec3* fallback);
struct kmVec3* kmQuaternionMultiplyVec3(struct kmVec3* pOut, const kmQuaternion* q, const struct kmVec3* v);

#ifdef __cplusplus
}
#endif

#endif
