
/**
 * Copyright 2019 United Kingdom Research and Innovation
 *
 * Authors: See AUTHORS
 *
 * Contact: [jianping.meng@stfc.ac.uk and/or jpmeng@gmail.com]
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice
 *    this list of conditions and the following disclaimer in the documentation
 *    and or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * ANDANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/

/*! @brief   Define constants and enumeration types.
 * @author  Jianping Meng
 * @details Define important constants and enumeration types including
 * boundary type, geometry types etc.
 * cycle
 */

#ifndef TYPE_H
#define TYPE_H
#include <limits>
#define DP
extern const char* RealC;
#ifdef DP
typedef double Real;
#else
typedef float Real;
#endif
const Real PI{3.1415926535897932384626433832795};
const Real EPS{std::numeric_limits<Real>::epsilon()};
const Real BOLTZ{1.3806488e-23};
const int xaxis = 1;
const int yaxis = 2;
const int zaxis = 3;
// ZERO is the zero constant with the desired precision, i.e., float or double
const Real ZERO{(Real)((int)0)};
//#define debug
#include "assert.h"
#include "ops_seq.h"
// It looks that OPS always fills the uninitialised storage with 0 so
// we try to avoid 0 value for these types
// Use this type to describe different node type in terms of boundary types
// or a fluid node
/*
 * Defining the position of a grid point relative to a polygon or polyhedron
 */
enum PointPosition {
    IsVertex = 1,
    StrictlyInterior = 2,
    StrictlyExterior = 3,
    RelativelyInteriorToEdge = 4,
    RelativelyInteriorToFace = 5
};
enum VertexTypes {
    // vtfluid is the general type of node
    // All specific fluid types should be started as vtft
    Vertex_Fluid = 10,
    Vertex_Boundary = 1000,
    // Vertex_Boundary is the general type of node
    // All specific boundary types should be started as vtbt
    Vertex_ExtrapolPressure1ST = 1006,
    Vertex_ExtrapolPressure2ND = 1007,
    Vertex_Periodic = 1008,
    Vertex_BounceBackWall = 1010,
    Vertex_FreeFlux = 1011,
    Vertex_ZouHeVelocity = 1012,
    Vertex_EQMDiffuseRefl = 1014,
    // Vertex_BoundaryCorner is the general corner type of node
    // All specific corner types should be started as vtbtco
    // for example, a corner of bounceback wall and inlet may be named as
    // vtbtbbinlet
    // It is unlikely to be used.
    Vertex_BoundaryCorner = 2000,
    // Bulk node but with immersed solid nodes
    Vertex_ImmersedSolid = -1
};  // vt
// Use this type to describe the geometry property of a node in terms of surface
// for example, it is i=0, j=0, or i=imax,j=jmax
// Rule i(x)=1 j(y)=2 k(z)=3, start(min)=0 end(max)=1
// So the surface i=0 is 10
// in the 2D case, we suppose that there are only i,j planes.
//
enum VertexGeometryTypes {
    // boundary node which usually a envelop of the region
    // boundary surface
    // VertexGeometry= VG
    VG_Fluid = 0,  // a normal fluid node, no need to give geometry property
    VG_ImmersedSolid =
        -1,  // a normal immesed solid node, no need to give geometry property
    // surface property, the normal direction
    VG_IP =
        10,  // the normal direction pointing to the Positive (P) X(I) direction
    VG_IM =
        11,  // the normal direction pointing to the Minor (M) X(I) direction
    VG_JP = 20,
    VG_JM = 21,
    VG_KP = 30,  // 3D
    VG_KM = 31,  // 3D
    // for inner corners
    // boundary cross line for 3D and corner point for 2D
    // only meaningful for 3D lines
    VG_IPKP_I = 10300,
    VG_IPKM_I = 10310,
    VG_IMKP_I = 11300,
    VG_IMKM_I = 11310,
    VG_JPKP_I = 20300,
    VG_JPKM_I = 20310,
    VG_JMKP_I = 21300,
    VG_JMKM_I = 21310,
    // for both 3D lines and 2D points
    VG_IPJP_I = 10200,
    VG_IPJM_I = 10210,
    VG_IMJP_I = 11200,
    VG_IMJM_I = 11210,
    // boundary corner point for 3D
    VG_IPJPKP_I = 1020300,
    VG_IPJPKM_I = 1020310,
    VG_IPJMKP_I = 1021300,
    VG_IPJMKM_I = 1021310,
    VG_IMJPKP_I = 1120300,
    VG_IMJPKM_I = 1120310,
    VG_IMJMKP_I = 1121300,
    VG_IMJMKM_I = 1121310,
    // for outer corners
    // only meaningful for 3D lines
    VG_IPKP_O = 10301,
    VG_IPKM_O = 10311,
    VG_IMKP_O = 11301,
    VG_IMKM_O = 11311,
    VG_JPKP_O = 20301,
    VG_JPKM_O = 20311,
    VG_JMKP_O = 21301,
    VG_JMKM_O = 21311,
    // for both 3D lines and 2D points
    VG_IPJP_O = 10201,
    VG_IPJM_O = 10211,
    VG_IMJP_O = 11201,
    VG_IMJM_O = 11211,
    // boundary corner point for 3D
    VG_IPJPKP_O = 1020301,
    VG_IPJPKM_O = 1020311,
    VG_IPJMKP_O = 1021301,
    VG_IPJMKM_O = 1021311,
    VG_IMJPKP_O = 1120301,
    VG_IMJPKM_O = 1120311,
    VG_IMJMKP_O = 1121301,
    VG_IMJMKM_O = 1121311,

};  // vg

enum VariableTypes {
    Variable_Rho = 0,
    Variable_U = 1,
    Variable_V = 2,
    Variable_W = 3,
    Variable_T = 4,
    Variable_Qx = 5,
    Variable_Qy = 6,
    Variable_Qz = 7,
    // This is for the force correction needed by using He1998 scheme.
    Variable_U_Force = 8,
    Variable_V_Force = 9,
    Variable_W_Force = 10,
};

enum EquilibriumType {
    Equilibrium_BGKIsothermal2nd = 0,
    Equilibrium_BGKThermal4th = 1,
    Equilibrium_BGKSWE4th = 2,
};

enum BodyForceType { BodyForce_1st = 1, BodyForce_None = 0 };

enum SolidBodyType { SolidBody_circle = 0, SolidBody_ellipse = 1 };

enum SpaceSchemeType {
    sstupwind2nd = 10,
    sstcentral2nd = 11,
    sstcentral4th = 12,
    sstcentral6th = 13,
    sstupwind3rd = 14,
    sstupwind4th = 15,
    sstupwind5h = 16,
    sstupwind6th = 17
};

typedef enum { tstrk4th = 10, tsteuler1st = 11 } TimeSchemeType;

typedef enum {
    qtdensity = 0,
    qtvelocity = 1,
    qttemperature = 2,
    qtpressure = 3,
    qtheatflux = 4,
    qtaccerlation = 5,
    qttime = 6,
    qtlength = 7,

} QuantityType;

typedef enum {
    fthardspheregas = 0,
    ftmaxwellgas = 1,
} FluidType;

enum BoundarySurface {
    BoundarySurface_Left = 0,
    BoundarySurface_Right = 1,
    BoundarySurface_Top = 2,
    BoundarySurface_Bottom = 3,
    BoundarySurface_Front = 4,
    BoundarySurface_Back = 5,
};

enum BoundaryType {
    BoundaryType_ExtrapolPressure1ST = 16,
    BoundaryType_ExtrapolPressure2ND = 17,
    BoundaryType_Periodic = 18,
    BoundaryType_BounceBackWall = 20,
    BoundaryType_FreeFlux = 21,
    BoundaryType_ZouHeVelocity = 22,
    BoundaryType_EQMDiffuseRefl = 24
};

typedef enum {
    bpanormal = 0,
    bpacorner = 1,
} BoundaryPointAttribute;

typedef enum {
    sbpif = 0,  // f first index of i
    sbpie = 1,  // e the end of i
    sbpjf = 2,
    sbpje = 3,
    sbpkf = 4,
    sbpke = 5,
} StructuredBoundaryPosition;

typedef enum {
    Scheme_E1st2nd = 1,
    Scheme_I1st2nd = -1,
    Scheme_StreamCollision = 10,
} SchemeType;

inline bool EssentiallyEqual(const Real* a, const Real* b, const Real epsilon) {
    return fabs(*a - *b) <=
           ((fabs(*a) > fabs(*b) ? fabs(*b) : fabs(*a)) * epsilon);
}

inline bool DefinitelyGreaterThan(const Real* a, const Real* b,
                                  const Real epsilon) {
    return (*a - *b) > ((fabs(*a) < fabs(*b) ? fabs(*b) : fabs(*a)) * epsilon);
}

inline bool DefinitelyLessThan(const Real* a, const Real* b,
                               const Real epsilon) {
    return (*b - *a) > ((fabs(*a) < fabs(*b) ? fabs(*b) : fabs(*a)) * epsilon);
}

template <typename T>
inline void FreeArrayMemory(T* pointerToArray) {
    if (pointerToArray != nullptr) {
        delete[] pointerToArray;
    }
}
#endif  // TYPE_H
