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

/*! @brief  Kernel functions for boundary conditions
 * @author  Jianping Meng
 * @details Defining kernel functions for various boundary conditions.
 */
#ifndef BOUNDARY_KERNEL_H
#define BOUNDARY_KERNEL_H
#include "boundary.h"
// As we are using update-halo method for the discretisation,
// we need to deal with halo points when treating boundary

// Boundary conditions for two-dimensional problems
#ifdef OPS_2D
void KerCutCellZeroFlux(const int *nodeType, const int *geometryProperty,
                        Real *f) {
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC0(0, 0)];
    if (vt == Vertex_FreeFlux) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC1(0, 0)];
        switch (vg) {
            case VG_IP:
                for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                    f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                        f[OPS_ACC_MD2(xiIndex, 1, 0)];
                }
                break;
            case VG_IM:
                for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                    f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                        f[OPS_ACC_MD2(xiIndex, -1, 0)];
                }
                break;
            case VG_JP:
                for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                    f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                        f[OPS_ACC_MD2(xiIndex, 0, 1)];
                }
                break;
            case VG_JM:
                for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                    f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                        f[OPS_ACC_MD2(xiIndex, 0, -1)];
                }
                break;

            case VG_IPJP_I:
                // VG_IP
                if (vt == nodeType[OPS_ACC0(0, 1)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, 1, 0)];
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC0(1, 0)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, 0, 1)];
                    }
                }
                break;
            case VG_IPJM_I:
                // VG_IP
                if (vt == nodeType[OPS_ACC0(0, -1)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, 1, 0)];
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC0(1, 0)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, 0, -1)];
                    }
                }
                break;
            case VG_IMJP_I:
                // VG_IM
                if (vt == nodeType[OPS_ACC0(0, 1)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, -1, 0)];
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC0(-1, 0)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, 0, 1)];
                    }
                }
                break;
            case VG_IMJM_I:
                //  VG_IM
                if (vt == nodeType[OPS_ACC0(0, -1)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, -1, 0)];
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC0(-1, 0)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, 0, -1)];
                    }
                }
                break;
            default:
                break;
        }

    } else {
#ifdef debug
        ops_printf("%s\n",
                   "Warning: this node is not a free flux boundary "
                   "point: KerCutCellZeroFlux");
#endif
    }
}

void KerCutCellEmbeddedBoundary(const int *nodeType,
                                const int *geometryProperty, Real *f) {
    /*!
     For the bounce-back type scheme, We consider zero velocity boundary first.
     To make sure the velocity at boundary is zero, the implementation
     is lattice specific.
     */
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC0(0, 0)];
    VertexGeometryTypes vg =
        (VertexGeometryTypes)geometryProperty[OPS_ACC1(0, 0)];
    if (vt >= Vertex_Boundary) {
        switch (vt) {
            case Vertex_EQMDiffuseRefl: {
                Real u{0};
                Real v{0};
                const Real sqrt3 = sqrt(3);
                switch (vg) {
                    case VG_IP: {
                        const Real f3 = f[OPS_ACC_MD2(3, 0, 0)];
                        const Real f7 = f[OPS_ACC_MD2(7, 0, 0)];
                        const Real f6 = f[OPS_ACC_MD2(6, 0, 0)];
                        const Real rhow =
                            6 * (f3 + f6 + f7) / (u * u - sqrt3 * u + 1);
                        f[OPS_ACC_MD2(5, 0, 0)] =
                            f7 + rhow * (u + v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(1, 0, 0)] =
                            f3 + 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(8, 0, 0)] =
                            f6 + rhow * (u - v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(2, 0, 0)] =
                            -(u * u - 2 * (1 + sqrt3 * v + v * v) * rhow) / 18;
                        f[OPS_ACC_MD2(4, 0, 0)] =
                            -((-2 + u * u + 2 * sqrt3 * v - 2 * v * v) * rhow) /
                            18;
                    } break;
                    case VG_IM: {
                        const Real f5 = f[OPS_ACC_MD2(5, 0, 0)];
                        const Real f1 = f[OPS_ACC_MD2(1, 0, 0)];
                        const Real f8 = f[OPS_ACC_MD2(8, 0, 0)];
                        const Real rhow =
                            6 * (f1 + f5 + f8) / (u * u + sqrt3 * u + 1);
                        f[OPS_ACC_MD2(7, 0, 0)] =
                            f5 - rhow * (u + v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(3, 0, 0)] =
                            f1 - 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(6, 0, 0)] =
                            f8 + rhow * (v - u) / (6 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(2, 0, 0)] =
                            -(u * u - 2 * (1 + sqrt3 * v + v * v) * rhow) / 18;
                        f[OPS_ACC_MD2(4, 0, 0)] =
                            -((-2 + u * u + 2 * sqrt3 * v - 2 * v * v) * rhow) /
                            18;
                    } break;
                    case VG_JP: {
                        const Real f4 = f[OPS_ACC_MD2(4, 0, 0)];
                        const Real f8 = f[OPS_ACC_MD2(8, 0, 0)];
                        const Real f7 = f[OPS_ACC_MD2(7, 0, 0)];
                        const Real rhow =
                            6 * (f4 + f8 + f7) / (v * v - sqrt3 * v + 1);
                        f[OPS_ACC_MD2(2, 0, 0)] =
                            f4 + 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(6, 0, 0)] =
                            f8 + rhow * (v - u) / (6 * sqrt3);
                        f[OPS_ACC_MD2(5, 0, 0)] =
                            f7 + rhow * (u + v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(1, 0, 0)] =
                            ((2 + 2 * sqrt3 * u + 2 * u * u - v * v) * rhow) /
                            18;
                        f[OPS_ACC_MD2(3, 0, 0)] =
                            -((-2 + 2 * sqrt3 * u - 2 * u * u + v * v) * rhow) /
                            18;
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                    } break;
                    case VG_JM: {
                        const Real f2 = f[OPS_ACC_MD2(2, 0, 0)];
                        const Real f5 = f[OPS_ACC_MD2(5, 0, 0)];
                        const Real f6 = f[OPS_ACC_MD2(6, 0, 0)];
                        const Real rhow =
                            6 * (f2 + f5 + f6) / (v * v + sqrt3 * v + 1);
                        f[OPS_ACC_MD2(4, 0, 0)] =
                            f2 - 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(8, 0, 0)] =
                            f6 + rhow * (u - v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(7, 0, 0)] =
                            f5 - rhow * (u + v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(1, 0, 0)] =
                            ((2 + 2 * sqrt3 * u + 2 * u * u - v * v) * rhow) /
                            18;
                        f[OPS_ACC_MD2(3, 0, 0)] =
                            -((-2 + 2 * sqrt3 * u - 2 * u * u + v * v) * rhow) /
                            18;
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                    } break;
                    case VG_IPJP_I: {
                        const Real f3 = f[OPS_ACC_MD2(3, 0, 0)];
                        const Real f7 = f[OPS_ACC_MD2(7, 0, 0)];
                        const Real f4 = f[OPS_ACC_MD2(4, 0, 0)];
                        const Real rhow =
                            (-36 * (f3 + f4 + f7)) /
                            (-9 + 5 * sqrt3 * u - 3 * u * u + 5 * sqrt3 * v -
                             3 * u * v - 3 * v * v);
                        f[OPS_ACC_MD2(1, 0, 0)] =
                            f3 + 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(5, 0, 0)] =
                            f7 + rhow * (u + v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(2, 0, 0)] =
                            f4 + 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(6, 0, 0)] =
                            (1 + u * u + sqrt3 * v + v * v -
                             u * (sqrt3 + 3 * v)) *
                            rhow / 36;
                        f[OPS_ACC_MD2(8, 0, 0)] =
                            (1 + u * u + u * (sqrt3 - 3 * v) - sqrt3 * v +
                             v * v) *
                            rhow / 36;
                    } break;
                    case VG_IPJM_I: {
                        const Real f2 = f[OPS_ACC_MD2(2, 0, 0)];
                        const Real f3 = f[OPS_ACC_MD2(3, 0, 0)];
                        const Real f6 = f[OPS_ACC_MD2(6, 0, 0)];
                        const Real rhow =
                            (-36 * (f2 + f3 + f6)) /
                            (-9 + 5 * sqrt3 * u - 3 * u * u - 5 * sqrt3 * v +
                             3 * u * v - 3 * v * v);
                        f[OPS_ACC_MD2(8, 0, 0)] =
                            f6 + rhow * (u - v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(1, 0, 0)] =
                            f3 + 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(4, 0, 0)] =
                            f2 - 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(5, 0, 0)] =
                            (1 + u * u + sqrt3 * v + v * v +
                             u * (sqrt3 + 3 * v)) *
                            rhow / 36;
                        f[OPS_ACC_MD2(7, 0, 0)] =
                            (1 - sqrt3 * u + u * u - sqrt3 * v + 3 * u * v +
                             v * v) *
                            rhow / 36;
                    } break;
                    case VG_IMJP_I: {
                        const Real f1 = f[OPS_ACC_MD2(1, 0, 0)];
                        const Real f4 = f[OPS_ACC_MD2(4, 0, 0)];
                        const Real f8 = f[OPS_ACC_MD2(8, 0, 0)];
                        const Real rhow =
                            (36 * (f1 + f4 + f8)) /
                            (9 + 5 * sqrt3 * u + 3 * u * u - 5 * sqrt3 * v -
                             3 * u * v + 3 * v * v);
                        f[OPS_ACC_MD2(6, 0, 0)] =
                            f8 + rhow * (v - u) / (6 * sqrt3);
                        f[OPS_ACC_MD2(3, 0, 0)] =
                            f1 - 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(2, 0, 0)] =
                            f4 + 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(5, 0, 0)] =
                            (1 + u * u + sqrt3 * v + v * v +
                             u * (sqrt3 + 3 * v)) *
                            rhow / 36;
                        f[OPS_ACC_MD2(7, 0, 0)] =
                            (1 - sqrt3 * u + u * u - sqrt3 * v + 3 * u * v +
                             v * v) *
                            rhow / 36;
                    } break;
                    case VG_IMJM_I: {
                        const Real f1 = f[OPS_ACC_MD2(1, 0, 0)];
                        const Real f5 = f[OPS_ACC_MD2(5, 0, 0)];
                        const Real f2 = f[OPS_ACC_MD2(2, 0, 0)];
                        const Real rhow =
                            (36 * (f1 + f2 + f5)) /
                            (9 + 5 * sqrt3 * u + 3 * u * u + 5 * sqrt3 * v +
                             3 * u * v + 3 * v * v);
                        f[OPS_ACC_MD2(3, 0, 0)] =
                            f1 - 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(4, 0, 0)] =
                            f2 - 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(7, 0, 0)] =
                            f5 - rhow * (u + v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(6, 0, 0)] =
                            (1 + u * u + sqrt3 * v + v * v -
                             u * (sqrt3 + 3 * v)) *
                            rhow / 36;
                        f[OPS_ACC_MD2(8, 0, 0)] =
                            (1 + u * u + u * (sqrt3 - 3 * v) - sqrt3 * v +
                             v * v) *
                            rhow / 36;
                    } break;
                    case VG_IPJP_O: {  // outter corner point
                        const Real f3 = f[OPS_ACC_MD2(3, 0, 0)];
                        const Real f7 = f[OPS_ACC_MD2(7, 0, 0)];
                        const Real f4 = f[OPS_ACC_MD2(4, 0, 0)];
                        const Real rhow =
                            (-36 * (f3 + f4 + f7)) /
                            (-9 + 5 * sqrt3 * u - 3 * u * u + 5 * sqrt3 * v -
                             3 * u * v - 3 * v * v);
                        f[OPS_ACC_MD2(1, 0, 0)] =
                            f3 + 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(5, 0, 0)] =
                            f7 + rhow * (u + v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(2, 0, 0)] =
                            f4 + 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(6, 0, 0)] =
                            (1 + u * u + sqrt3 * v + v * v -
                             u * (sqrt3 + 3 * v)) *
                            rhow / 36;
                        f[OPS_ACC_MD2(8, 0, 0)] =
                            (1 + u * u + u * (sqrt3 - 3 * v) - sqrt3 * v +
                             v * v) *
                            rhow / 36;
                    } break;
                    case VG_IPJM_O: {  // outter corner point
                        const Real f2 = f[OPS_ACC_MD2(2, 0, 0)];
                        const Real f3 = f[OPS_ACC_MD2(3, 0, 0)];
                        const Real f6 = f[OPS_ACC_MD2(6, 0, 0)];
                        const Real rhow =
                            (-36 * (f2 + f3 + f6)) /
                            (-9 + 5 * sqrt3 * u - 3 * u * u - 5 * sqrt3 * v +
                             3 * u * v - 3 * v * v);
                        f[OPS_ACC_MD2(8, 0, 0)] =
                            f6 + rhow * (u - v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(1, 0, 0)] =
                            f3 + 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(4, 0, 0)] =
                            f2 - 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(5, 0, 0)] =
                            (1 + u * u + sqrt3 * v + v * v +
                             u * (sqrt3 + 3 * v)) *
                            rhow / 36;
                        f[OPS_ACC_MD2(7, 0, 0)] =
                            (1 - sqrt3 * u + u * u - sqrt3 * v + 3 * u * v +
                             v * v) *
                            rhow / 36;
                    } break;
                    case VG_IMJP_O: {  // outter corner point
                        const Real f1 = f[OPS_ACC_MD2(1, 0, 0)];
                        const Real f4 = f[OPS_ACC_MD2(4, 0, 0)];
                        const Real f8 = f[OPS_ACC_MD2(8, 0, 0)];
                        const Real rhow =
                            (36 * (f1 + f4 + f8)) /
                            (9 + 5 * sqrt3 * u + 3 * u * u - 5 * sqrt3 * v -
                             3 * u * v + 3 * v * v);
                        f[OPS_ACC_MD2(6, 0, 0)] =
                            f8 + rhow * (v - u) / (6 * sqrt3);
                        f[OPS_ACC_MD2(3, 0, 0)] =
                            f1 - 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(2, 0, 0)] =
                            f4 + 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(5, 0, 0)] =
                            (1 + u * u + sqrt3 * v + v * v +
                             u * (sqrt3 + 3 * v)) *
                            rhow / 36;
                        f[OPS_ACC_MD2(7, 0, 0)] =
                            (1 - sqrt3 * u + u * u - sqrt3 * v + 3 * u * v +
                             v * v) *
                            rhow / 36;
                    } break;
                    case VG_IMJM_O: {  // outter corner point
                        const Real f1 = f[OPS_ACC_MD2(1, 0, 0)];
                        const Real f5 = f[OPS_ACC_MD2(5, 0, 0)];
                        const Real f2 = f[OPS_ACC_MD2(2, 0, 0)];
                        const Real rhow =
                            (36 * (f1 + f2 + f5)) /
                            (9 + 5 * sqrt3 * u + 3 * u * u + 5 * sqrt3 * v +
                             3 * u * v + 3 * v * v);
                        f[OPS_ACC_MD2(3, 0, 0)] =
                            f1 - 2 * rhow * u / (3 * sqrt3);
                        f[OPS_ACC_MD2(4, 0, 0)] =
                            f2 - 2 * rhow * v / (3 * sqrt3);
                        f[OPS_ACC_MD2(7, 0, 0)] =
                            f5 - rhow * (u + v) / (6 * sqrt3);
                        f[OPS_ACC_MD2(0, 0, 0)] =
                            2 * rhow * (2 - u * u - v * v) / 9;
                        f[OPS_ACC_MD2(6, 0, 0)] =
                            (1 + u * u + sqrt3 * v + v * v -
                             u * (sqrt3 + 3 * v)) *
                            rhow / 36;
                        f[OPS_ACC_MD2(8, 0, 0)] =
                            (1 + u * u + u * (sqrt3 - 3 * v) - sqrt3 * v +
                             v * v) *
                            rhow / 36;
                    } break;
                    default:
                        break;
                }  // vg
            }      // case Vertex_EQMDiffRefl
            break;
            default:
#ifdef debug
                ops_printf("%s\n",
                           "Warning: KerCutCellImmersedBoundary: there seems a "
                           "boundary condition that has note been implemented");
#endif
                break;
        }
    }
}

void KerCutCellExtrapolPressure1ST(const Real *givenBoundaryVars,
                                   const int *nodeType,
                                   const int *geometryProperty, Real *f) {
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC1(0, 0)];
    if (vt == Vertex_ExtrapolPressure1ST) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC2(0, 0)];
        Real rhoGiven = givenBoundaryVars[0];
        Real rho = 0;
        for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
            const int cx = (int)XI[xiIndex * LATTDIM];
            const int cy = (int)XI[xiIndex * LATTDIM + 1];
            switch (vg) {
                case VG_IP: {
                    if (cx > 0) {
                        f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD3(xiIndex, 1, 0)];
                    }
                } break;
                case VG_IM: {
                    if (cx < 0) {
                        f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD3(xiIndex, -1, 0)];
                    }
                } break;
                case VG_JP: {
                    if (cy > 0) {
                        f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD3(xiIndex, 0, 1)];
                    }
                } break;
                case VG_JM: {
                    if (cy < 0) {
                        f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD3(xiIndex, 0, -1)];
                    }

                } break;

                case VG_IPJP_I: {
                    // VG_IP
                    if (vt == nodeType[OPS_ACC1(0, 1)]) {
                        if ((cx > 0 && cy >= 0) || (cx >= 0 && cy > 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD3(xiIndex, 1, 0)];
                        }
                    }
                    // VG_JP
                    if (vt == nodeType[OPS_ACC1(1, 0)]) {
                        if ((cx > 0 && cy >= 0) || (cx >= 0 && cy > 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD3(xiIndex, 0, 1)];
                        }
                    }
                } break;
                case VG_IPJM_I: {
                    // VG_IP
                    if (vt == nodeType[OPS_ACC1(0, -1)]) {
                        if ((cx > 0 && cy <= 0) || (cx >= 0 && cy < 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD3(xiIndex, 1, 0)];
                        }
                    }
                    // VG_JM
                    if (vt == nodeType[OPS_ACC1(1, 0)]) {
                        if ((cx > 0 && cy <= 0) || (cx >= 0 && cy < 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD3(xiIndex, 0, -1)];
                        }
                    }
                } break;

                case VG_IMJP_I: {
                    // VG_IM
                    if (vt == nodeType[OPS_ACC1(0, 1)]) {
                        if ((cx < 0 && cy >= 0) || (cx <= 0 && cy > 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD3(xiIndex, -1, 0)];
                        }
                    }
                    // VG_JP
                    if (vt == nodeType[OPS_ACC1(-1, 0)]) {
                        if ((cx < 0 && cy >= 0) || (cx <= 0 && cy > 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD3(xiIndex, 0, 1)];
                        }
                    }
                } break;
                case VG_IMJM_I: {
                    // VG_IM
                    if (vt == nodeType[OPS_ACC1(0, -1)]) {
                        if ((cx < 0 && cy <= 0) || (cx <= 0 && cy < 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD3(xiIndex, -1, 0)];
                        }
                    }
                    // VG_JM
                    if (vt == nodeType[OPS_ACC1(-1, 0)]) {
                        if ((cx < 0 && cy <= 0) || (cx <= 0 && cy < 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD3(xiIndex, 0, -1)];
                        }
                    }
                } break;
                default:
                    break;
            }
            rho += f[OPS_ACC_MD3(xiIndex, 0, 0)];
        }
        Real ratio = rhoGiven / rho;
        for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
            f[OPS_ACC_MD3(xiIndex, 0, 0)] *= ratio;
        }

    } else {
#ifdef debug
        ops_printf("%s\n",
                   "Warning: this node is not a extrapol pressure "
                   "boundary point: KerCutCellExtraolPressure1ST");
#endif
    }
}

void KerCutCellExtrapolPressure2ND(const Real *givenBoundaryVars,
                                   const int *nodeType,
                                   const int *geometryProperty, Real *f) {
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC1(0, 0)];
    if (vt == Vertex_ExtrapolPressure2ND) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC2(0, 0)];
        Real rhoGiven = givenBoundaryVars[0];
        Real rho = 0;
        for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
            const int cx = (int)XI[xiIndex * LATTDIM];
            const int cy = (int)XI[xiIndex * LATTDIM + 1];
            switch (vg) {
                case VG_IP: {
                    if (cx > 0) {
                        f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                            2 * f[OPS_ACC_MD3(xiIndex, 1, 0)] -
                            f[OPS_ACC_MD3(xiIndex, 2, 0)];
                    }
                } break;
                case VG_IM: {
                    if (cx < 0) {
                        f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                            2 * f[OPS_ACC_MD3(xiIndex, -1, 0)] -
                            f[OPS_ACC_MD3(xiIndex, -2, 0)];
                    }
                } break;
                case VG_JP: {
                    if (cy > 0) {
                        f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                            2 * f[OPS_ACC_MD3(xiIndex, 0, 1)] -
                            f[OPS_ACC_MD3(xiIndex, 0, 2)];
                    }
                } break;
                case VG_JM: {
                    if (cy < 0) {
                        f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                            2 * f[OPS_ACC_MD3(xiIndex, 0, -1)] -
                            f[OPS_ACC_MD3(xiIndex, 0, -2)];
                    }
                } break;
                // inner corner point
                case VG_IPJP_I: {
                    // VG_IP
                    if (vt == nodeType[OPS_ACC1(0, 1)]) {
                        if ((cx > 0 && cy >= 0) || (cx >= 0 && cy > 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                2 * f[OPS_ACC_MD3(xiIndex, 1, 0)] -
                                f[OPS_ACC_MD3(xiIndex, 2, 0)];
                        }
                    }
                    // VG_JP
                    if (vt == nodeType[OPS_ACC1(1, 0)]) {
                        if ((cx > 0 && cy >= 0) || (cx >= 0 && cy > 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                2 * f[OPS_ACC_MD3(xiIndex, 0, 1)] -
                                f[OPS_ACC_MD3(xiIndex, 0, 2)];
                        }
                    }
                } break;
                case VG_IPJM_I: {
                    // VG_IP
                    if (vt == nodeType[OPS_ACC1(0, -1)]) {
                        if ((cx > 0 && cy <= 0) || (cx >= 0 && cy < 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                2 * f[OPS_ACC_MD3(xiIndex, 1, 0)] -
                                f[OPS_ACC_MD3(xiIndex, 2, 0)];
                        }
                    }
                    // VG_JM
                    if (vt == nodeType[OPS_ACC1(1, 0)]) {
                        if ((cx > 0 && cy <= 0) || (cx >= 0 && cy < 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                2 * f[OPS_ACC_MD3(xiIndex, 0, -1)] -
                                f[OPS_ACC_MD3(xiIndex, 0, -2)];
                        }
                    }
                } break;
                case VG_IMJP_I: {
                    // VG_IM
                    if (vt == nodeType[OPS_ACC1(0, 1)]) {
                        if ((cx < 0 && cy >= 0) || (cx <= 0 && cy > 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                2 * f[OPS_ACC_MD3(xiIndex, -1, 0)] -
                                f[OPS_ACC_MD3(xiIndex, -2, 0)];
                        }
                    }
                    // VG_JP
                    if (vt == nodeType[OPS_ACC1(-1, 0)]) {
                        if ((cx < 0 && cy >= 0) || (cx <= 0 && cy > 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                2 * f[OPS_ACC_MD3(xiIndex, 0, 1)] -
                                f[OPS_ACC_MD3(xiIndex, 0, 2)];
                        }
                    }
                } break;
                case VG_IMJM_I: {
                    // VG_IM
                    if (vt == nodeType[OPS_ACC1(0, -1)]) {
                        if ((cx < 0 && cy <= 0) || (cx <= 0 && cy < 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                2 * f[OPS_ACC_MD3(xiIndex, -1, 0)] -
                                f[OPS_ACC_MD3(xiIndex, -2, 0)];
                        }
                    }
                    // VG_JM
                    if (vt == nodeType[OPS_ACC1(-1, 0)]) {
                        if ((cx < 0 && cy <= 0) || (cx <= 0 && cy < 0)) {
                            f[OPS_ACC_MD3(xiIndex, 0, 0)] =
                                2 * f[OPS_ACC_MD3(xiIndex, 0, -1)] -
                                f[OPS_ACC_MD3(xiIndex, 0, -2)];
                        }
                    }
                } break;
                default:
                    break;
            }
            rho += f[OPS_ACC_MD3(xiIndex, 0, 0)];
        }
        Real ratio = rhoGiven / rho;
        for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
            f[OPS_ACC_MD3(xiIndex, 0, 0)] *= ratio;
        }
    } else {
#ifdef debug
        ops_printf("%s\n",
                   "Warning: this node is not a extrapol pressure "
                   "boundary point: KerCutCellExtraolPressure2ND");
#endif
    }
}

void KerCutCellBounceBack(const int *nodeType, const int *geometryProperty,
                          Real *f) {
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC0(0, 0)];
    if (vt == Vertex_BounceBackWall) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC1(0, 0)];
        switch (vg) {
            case VG_IP: {
                f[OPS_ACC_MD2(5, 0, 0)] = f[OPS_ACC_MD2(7, 0, 0)];
                f[OPS_ACC_MD2(1, 0, 0)] = f[OPS_ACC_MD2(3, 0, 0)];
                f[OPS_ACC_MD2(8, 0, 0)] = f[OPS_ACC_MD2(6, 0, 0)];
            } break;
            case VG_IM: {
                f[OPS_ACC_MD2(7, 0, 0)] = f[OPS_ACC_MD2(5, 0, 0)];
                f[OPS_ACC_MD2(3, 0, 0)] = f[OPS_ACC_MD2(1, 0, 0)];
                f[OPS_ACC_MD2(6, 0, 0)] = f[OPS_ACC_MD2(8, 0, 0)];
            } break;
            case VG_JP: {
                f[OPS_ACC_MD2(2, 0, 0)] = f[OPS_ACC_MD2(4, 0, 0)];
                f[OPS_ACC_MD2(6, 0, 0)] = f[OPS_ACC_MD2(8, 0, 0)];
                f[OPS_ACC_MD2(5, 0, 0)] = f[OPS_ACC_MD2(7, 0, 0)];
            } break;
            case VG_JM: {
                f[OPS_ACC_MD2(4, 0, 0)] = f[OPS_ACC_MD2(2, 0, 0)];
                f[OPS_ACC_MD2(8, 0, 0)] = f[OPS_ACC_MD2(6, 0, 0)];
                f[OPS_ACC_MD2(7, 0, 0)] = f[OPS_ACC_MD2(5, 0, 0)];
            } break;
            case VG_IPJP_I:  // inner corner point
                f[OPS_ACC_MD2(5, 0, 0)] = f[OPS_ACC_MD2(7, 0, 0)];
                break;
            case VG_IPJM_I:  // inner corner point
                f[OPS_ACC_MD2(8, 0, 0)] = f[OPS_ACC_MD2(6, 0, 0)];
                break;
            case VG_IMJP_I:  // inner corner point
                f[OPS_ACC_MD2(6, 0, 0)] = f[OPS_ACC_MD2(8, 0, 0)];
                break;
            case VG_IMJM_I:  // inner corner point
                f[OPS_ACC_MD2(7, 0, 0)] = f[OPS_ACC_MD2(5, 0, 0)];
                break;
            default:
                break;
        }
    } else {
#ifdef debug
        ops_printf("%s\n",
                   "Warning: this node is not a bounce-back boundary "
                   "point: KerCutCellBounceBack");
#endif
    }
}

void KerCutCellEQMDiffuseRefl(const Real *givenMacroVars, const int *nodeType,
                              const int *geometryProperty, Real *f,
                              const int *componentId) {
    // This kernel is suitable for a single-speed lattice
    // but only for the second-order expansion at this moment
    // Therefore, the equilibrium function order is fixed at 2
    const int equilibriumOrder{2};
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC1(0, 0)];
    if (vt == Vertex_EQMDiffuseRefl) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC2(0, 0)];
        Real u = givenMacroVars[1];
        Real v = givenMacroVars[2];
        // for (int compoIdx = 0; compoIdx < NUMCOMPONENTS; compoIdx++) {
        const int compoIdx{*componentId};
        int numOutgoing{0};
        int numIncoming{0};
        int numParallel{0};
        int *outgoing = new int[COMPOINDEX[2 * compoIdx + 1] -
                                COMPOINDEX[2 * compoIdx] + 1];
        int *incoming = new int[COMPOINDEX[2 * compoIdx + 1] -
                                COMPOINDEX[2 * compoIdx] + 1];
        int *parallel = new int[COMPOINDEX[2 * compoIdx + 1] -
                                COMPOINDEX[2 * compoIdx] + 1];
        Real rhoIncoming{0};
        Real rhoParallel{0};
        Real deltaRho{0};
        for (int xiIdx = COMPOINDEX[2 * compoIdx];
             xiIdx <= COMPOINDEX[2 * compoIdx + 1]; xiIdx++) {
            BndryDvType bdt = FindBdyDvType(vg, &XI[xiIdx * LATTDIM]);
            switch (bdt) {
                case BndryDv_Incoming: {
                    incoming[numIncoming] = xiIdx;
                    rhoIncoming += f[OPS_ACC_MD3(xiIdx, 0, 0)];
                    numIncoming++;
                } break;
                case BndryDv_Outgoing: {
                    outgoing[numOutgoing] = xiIdx;
                    Real cx{CS * XI[xiIdx * LATTDIM]};
                    Real cy{CS * XI[xiIdx * LATTDIM + 1]};
                    deltaRho += (2 * WEIGHTS[xiIdx]) * (cx * u + cy * v);
                    numOutgoing++;
                } break;
                case BndryDv_Parallel: {
                    parallel[numParallel] = xiIdx;
                    rhoParallel +=
                        CalcBGKFeq(xiIdx, 1, u, v, 1, equilibriumOrder);
                    numParallel++;
                } break;
                default:
                    break;
            }
        }
        Real rhoWall = 2 * rhoIncoming / (1 - deltaRho - rhoParallel);
        for (int idx = 0; idx < numParallel; idx++) {
            f[OPS_ACC_MD3(parallel[idx], 0, 0)] =
                CalcBGKFeq(parallel[idx], rhoWall, u, v, 1, equilibriumOrder);
        }
        for (int idx = 0; idx < numOutgoing; idx++) {
            int xiIdx = outgoing[idx];
            Real cx{CS * XI[xiIdx * LATTDIM]};
            Real cy{CS * XI[xiIdx * LATTDIM + 1]};
            f[OPS_ACC_MD3(xiIdx, 0, 0)] =
                f[OPS_ACC_MD3(OPP[xiIdx], 0, 0)] +
                2 * rhoWall * WEIGHTS[xiIdx] * (cx * u + cy * v);
        }
        delete[] outgoing;
        delete[] incoming;
        delete[] parallel;
        //}
    } else {
#ifdef debug
        ops_printf("%s\n",
                   "Warning: this node is not a equilibrium diffuse reflection "
                   "boundary condition point: KerCutCellEQMDiffuseRefl");
#endif
    }
}

void KerCutCellPeriodic(const int *nodeType, const int *geometryProperty,
                        Real *f) {
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC0(0, 0)];
    if (vt == Vertex_Periodic) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC1(0, 0)];
        switch (vg) {
            case VG_IP:
                for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                    Real cx = XI[xiIndex * LATTDIM];
                    if (cx > 0) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, -1, 0)];
                    }
                }
                break;
            case VG_IM:
                for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                    Real cx = XI[xiIndex * LATTDIM];
                    if (cx < 0) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, 1, 0)];
                    }
                }
                break;
            case VG_JP:
                for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                    Real cy = XI[xiIndex * LATTDIM + 1];
                    if (cy > 0) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, 0, -1)];
                    }
                }
                break;
            case VG_JM:
                for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                    Real cy = XI[xiIndex * LATTDIM + 1];
                    if (cy < 0) {
                        f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                            f[OPS_ACC_MD2(xiIndex, 0, 1)];
                    }
                }
                break;
            // There are only inner corners for block boundaries
            case VG_IPJP_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC0(0, 1)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        Real cx = XI[xiIndex * LATTDIM];
                        Real cy = XI[xiIndex * LATTDIM + 1];
                        if (cy > 0 || cx > 0) {
                            f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD2(xiIndex, -1, 0)];
                        }
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC0(1, 0)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        Real cx = XI[xiIndex * LATTDIM];
                        Real cy = XI[xiIndex * LATTDIM + 1];
                        if (cy > 0 || cx > 0) {
                            f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD2(xiIndex, 0, -1)];
                        }
                    }
                }
            } break;
            case VG_IPJM_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC1(0, -1)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        Real cx = XI[xiIndex * LATTDIM];
                        Real cy = XI[xiIndex * LATTDIM + 1];
                        if (cy < 0 || cx > 0) {
                            f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD2(xiIndex, -1, 0)];
                        }
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC1(1, 0)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        Real cx = XI[xiIndex * LATTDIM];
                        Real cy = XI[xiIndex * LATTDIM + 1];
                        if (cy < 0 || cx > 0) {
                            f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD2(xiIndex, 0, 1)];
                        }
                    }
                }
            } break;
            case VG_IMJP_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC1(0, 1)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        Real cx = XI[xiIndex * LATTDIM];
                        Real cy = XI[xiIndex * LATTDIM + 1];
                        if (cy > 0 || cx < 0) {
                            f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD2(xiIndex, 1, 0)];
                        }
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC1(-1, 0)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        Real cx = XI[xiIndex * LATTDIM];
                        Real cy = XI[xiIndex * LATTDIM + 1];
                        if (cy > 0 || cx < 0) {
                            f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD2(xiIndex, 0, -1)];
                        }
                    }
                }
            } break;
            case VG_IMJM_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC1(0, -1)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        Real cx = XI[xiIndex * LATTDIM];
                        Real cy = XI[xiIndex * LATTDIM + 1];
                        if (cy < 0 || cx < 0) {
                            f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD2(xiIndex, 1, 0)];
                        }
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC1(-1, 0)]) {
                    for (int xiIndex = 0; xiIndex < NUMXI; xiIndex++) {
                        Real cx = XI[xiIndex * LATTDIM];
                        Real cy = XI[xiIndex * LATTDIM + 1];
                        if (cy < 0 || cx < 0) {
                            f[OPS_ACC_MD2(xiIndex, 0, 0)] =
                                f[OPS_ACC_MD2(xiIndex, 0, 1)];
                        }
                    }
                }
            } break;
            default:
                break;
        }
    } else {
#ifdef debug
        ops_printf("%s\n",
                   "Warning: this node is not a periodic boundary "
                   "point: KerCutCellPeriodic");
#endif
    }
}

void KerCutCellZouHeVelocity(const Real *givenMacroVars, const int *nodeType,
                             const int *geometryProperty, const Real *macroVars,
                             Real *f) {
    /*!
    Note: This boundary condition requires both stream and collision happenning
    at a boundary point.
    Note: This boundary condition is lattice specific.
    */
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC1(0, 0)];
    if (vt == Vertex_ZouHeVelocity) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC2(0, 0)];
        Real rho{0};
        Real u{givenMacroVars[1]};
        Real v{givenMacroVars[2]};
        Real sqrt3 = sqrt(3);
        switch (vg) {
            case VG_IP: {
                // Knows
                Real f0 = f[OPS_ACC_MD4(0, 0, 0)];
                Real f2 = f[OPS_ACC_MD4(2, 0, 0)];
                Real f3 = f[OPS_ACC_MD4(3, 0, 0)];
                Real f4 = f[OPS_ACC_MD4(4, 0, 0)];
                Real f6 = f[OPS_ACC_MD4(6, 0, 0)];
                Real f7 = f[OPS_ACC_MD4(7, 0, 0)];
                rho = sqrt3 * (f0 + f2 + 2 * f3 + f4 + 2 * f6 + 2 * f7) /
                      (sqrt3 - u);
                f[OPS_ACC_MD4(1, 0, 0)] = (2 * sqrt3 * rho * u + 9 * f3) / 9.0;
                f[OPS_ACC_MD4(5, 0, 0)] =
                    (sqrt3 * rho * u + 3 * sqrt3 * rho * v - 9 * f2 + 9 * f4 +
                     18 * f7) /
                    18.0;
                f[OPS_ACC_MD4(8, 0, 0)] =
                    (sqrt3 * rho * u - 3 * sqrt3 * rho * v + 9 * f2 - 9 * f4 +
                     18 * f6) /
                    18.0;
            } break;
            case VG_IM: {
                // Knows
                Real f0 = f[OPS_ACC_MD4(0, 0, 0)];
                Real f2 = f[OPS_ACC_MD4(2, 0, 0)];
                Real f4 = f[OPS_ACC_MD4(4, 0, 0)];
                Real f1 = f[OPS_ACC_MD4(1, 0, 0)];
                Real f5 = f[OPS_ACC_MD4(5, 0, 0)];
                Real f8 = f[OPS_ACC_MD4(8, 0, 0)];
                rho = (sqrt3 * f0 + 2 * sqrt3 * f1 + sqrt3 * f2 + sqrt3 * f4 +
                       2 * sqrt3 * f5 + 2 * sqrt3 * f8) /
                      (sqrt3 + u);
                f[OPS_ACC_MD4(3, 0, 0)] = (-2 * sqrt3 * u * rho + 9 * f1) / 9.0;
                f[OPS_ACC_MD4(6, 0, 0)] =
                    (-(sqrt3 * u * rho) + 3 * sqrt3 * v * rho - 9 * f2 +
                     9 * f4 + 18 * f8) /
                    18.0;
                f[OPS_ACC_MD4(7, 0, 0)] =
                    (-(sqrt3 * u * rho) - 3 * sqrt3 * v * rho + 9 * f2 -
                     9 * f4 + 18 * f5) /
                    18.0;
            } break;
            case VG_JP: {
                // Knows
                Real f0 = f[OPS_ACC_MD4(0, 0, 0)];
                Real f1 = f[OPS_ACC_MD4(1, 0, 0)];
                Real f3 = f[OPS_ACC_MD4(3, 0, 0)];
                Real f4 = f[OPS_ACC_MD4(4, 0, 0)];
                Real f7 = f[OPS_ACC_MD4(7, 0, 0)];
                Real f8 = f[OPS_ACC_MD4(8, 0, 0)];
                rho = (sqrt3 * f0 + sqrt3 * f1 + sqrt3 * f3 + 2 * sqrt3 * f4 +
                       2 * sqrt3 * f7 + 2 * sqrt3 * f8) /
                      (sqrt3 - v);
                f[OPS_ACC_MD4(2, 0, 0)] = (2 * sqrt3 * v * rho + 9 * f4) / 9.0;
                f[OPS_ACC_MD4(5, 0, 0)] =
                    (3 * sqrt3 * u * rho + sqrt3 * v * rho - 9 * f1 + 9 * f3 +
                     18 * f7) /
                    18.0;
                f[OPS_ACC_MD4(6, 0, 0)] =
                    (-3 * sqrt3 * u * rho + sqrt3 * v * rho + 9 * f1 - 9 * f3 +
                     18 * f8) /
                    18.0;
            } break;
            case VG_JM: {
                // Knows
                Real f0 = f[OPS_ACC_MD4(0, 0, 0)];
                Real f1 = f[OPS_ACC_MD4(1, 0, 0)];
                Real f3 = f[OPS_ACC_MD4(3, 0, 0)];
                Real f2 = f[OPS_ACC_MD4(2, 0, 0)];
                Real f5 = f[OPS_ACC_MD4(5, 0, 0)];
                Real f6 = f[OPS_ACC_MD4(6, 0, 0)];
                rho = (sqrt3 * f0 + sqrt3 * f1 + 2 * sqrt3 * f2 + sqrt3 * f3 +
                       2 * sqrt3 * f5 + 2 * sqrt3 * f6) /
                      (sqrt3 + v);
                f[OPS_ACC_MD4(4, 0, 0)] = (-2 * sqrt3 * v * rho + 9 * f2) / 9.0;
                f[OPS_ACC_MD4(7, 0, 0)] =
                    (-3 * sqrt3 * u * rho - sqrt3 * v * rho + 9 * f1 - 9 * f3 +
                     18 * f5) /
                    18.0;
                f[OPS_ACC_MD4(8, 0, 0)] =
                    (3 * sqrt3 * u * rho - sqrt3 * v * rho - 9 * f1 + 9 * f3 +
                     18 * f6) /
                    18.0;
            } break;
            case VG_IPJM_I: {
                // Knows
                Real f0 = f[OPS_ACC_MD4(0, 0, 0)];
                Real f2 = f[OPS_ACC_MD4(2, 0, 0)];
                Real f6 = f[OPS_ACC_MD4(6, 0, 0)];
                Real f3 = f[OPS_ACC_MD4(3, 0, 0)];
                rho = macroVars[OPS_ACC_MD3(0, 1, -1)];
                f[OPS_ACC_MD4(1, 0, 0)] = (2 * sqrt3 * u * rho + 9 * f3) / 9.0;
                f[OPS_ACC_MD4(5, 0, 0)] =
                    (9 * rho - 2 * sqrt3 * u * rho + 3 * sqrt3 * v * rho -
                     9 * f0 - 18 * f2 - 18 * f3 - 18 * f6) /
                    18.0;
                f[OPS_ACC_MD4(7, 0, 0)] =
                    (9 * rho - 3 * sqrt3 * u * rho + 2 * sqrt3 * v * rho -
                     9 * f0 - 18 * f2 - 18 * f3 - 18 * f6) /
                    18.0;
                f[OPS_ACC_MD4(4, 0, 0)] = (-2 * sqrt3 * v * rho + 9 * f2) / 9.0;
                f[OPS_ACC_MD4(8, 0, 0)] =
                    (sqrt3 * u * rho - sqrt3 * v * rho + 18 * f6) / 18.0;
            } break;
            case VG_IPJP_I: {
                // Knows
                Real f0 = f[OPS_ACC_MD4(0, 0, 0)];
                Real f4 = f[OPS_ACC_MD4(4, 0, 0)];
                Real f3 = f[OPS_ACC_MD4(3, 0, 0)];
                Real f7 = f[OPS_ACC_MD4(7, 0, 0)];
                rho = macroVars[OPS_ACC_MD3(0, 1, 1)];
                f[OPS_ACC_MD4(1, 0, 0)] = (2 * sqrt3 * u * rho + 9 * f3) / 9.0;
                f[OPS_ACC_MD4(5, 0, 0)] =
                    (sqrt3 * u * rho + sqrt3 * v * rho + 18 * f7) / 18.0;
                f[OPS_ACC_MD4(8, 0, 0)] =
                    (9 * rho - 2 * sqrt3 * u * rho - 3 * sqrt3 * v * rho -
                     9 * f0 - 18 * f3 - 18 * f4 - 18 * f7) /
                    18.0;
                f[OPS_ACC_MD4(2, 0, 0)] = (2 * sqrt3 * v * rho + 9 * f4) / 9.0;
                f[OPS_ACC_MD4(6, 0, 0)] =
                    (9 * rho - 3 * sqrt3 * u * rho - 2 * sqrt3 * v * rho -
                     9 * f0 - 18 * f3 - 18 * f4 - 18 * f7) /
                    18.0;
            } break;
            case VG_IMJP_I: {
                // Knows
                Real f0 = f[OPS_ACC_MD4(0, 0, 0)];
                Real f1 = f[OPS_ACC_MD4(1, 0, 0)];
                Real f8 = f[OPS_ACC_MD4(8, 0, 0)];
                Real f4 = f[OPS_ACC_MD4(4, 0, 0)];
                rho = macroVars[OPS_ACC_MD3(0, -1, 1)];
                f[OPS_ACC_MD4(5, 0, 0)] =
                    (9 * rho + 3 * sqrt3 * u * rho - 2 * sqrt3 * v * rho -
                     9 * f0 - 18 * f1 - 18 * f4 - 18 * f8) /
                    18.0;
                f[OPS_ACC_MD4(2, 0, 0)] = (2 * sqrt3 * v * rho + 9 * f4) / 9.0;
                f[OPS_ACC_MD4(6, 0, 0)] =
                    (-(sqrt3 * u * rho) + sqrt3 * v * rho + 18 * f8) / 18.0;
                f[OPS_ACC_MD4(3, 0, 0)] = (-2 * sqrt3 * u * rho + 9 * f1) / 9.0;
                f[OPS_ACC_MD4(7, 0, 0)] =
                    (9 * rho + 2 * sqrt3 * u * rho - 3 * sqrt3 * v * rho -
                     9 * f0 - 18 * f1 - 18 * f4 - 18 * f8) /
                    18.0;
            } break;
            case VG_IMJM_I: {
                // Knows
                Real f0 = f[OPS_ACC_MD4(0, 0, 0)];
                Real f1 = f[OPS_ACC_MD4(1, 0, 0)];
                Real f2 = f[OPS_ACC_MD4(2, 0, 0)];
                Real f5 = f[OPS_ACC_MD4(5, 0, 0)];
                rho = macroVars[OPS_ACC_MD3(0, -1, -1)];
                f[OPS_ACC_MD4(6, 0, 0)] =
                    (9 * rho + 2 * sqrt3 * u * rho + 3 * sqrt3 * v * rho -
                     9 * f0 - 18 * f1 - 18 * f2 - 18 * f5) /
                    18.0;
                f[OPS_ACC_MD4(3, 0, 0)] = (-2 * sqrt3 * u * rho + 9 * f1) / 9.0;
                f[OPS_ACC_MD4(7, 0, 0)] =
                    (-(sqrt3 * u * rho) - sqrt3 * v * rho + 18 * f5) / 18.0;
                f[OPS_ACC_MD4(4, 0, 0)] = (-2 * sqrt3 * v * rho + 9 * f2) / 9.0;
                f[OPS_ACC_MD4(8, 0, 0)] =
                    (9 * rho + 3 * sqrt3 * u * rho + 2 * sqrt3 * v * rho -
                     9 * f0 - 18 * f1 - 18 * f2 - 18 * f5) /
                    18.0;
            } break;
            default:
                break;
        }
    } else {
#ifdef debug
        ops_printf("%s\n",
                   "Warning: this node is not a Zou-He velocity boundary "
                   "point: KerCutCellZhouHeVelocity");
#endif
    }
}

#endif
// Boundary conditions for three-dimensional problems
#ifdef OPS_3D
void KerCutCellExtrapolPressure1ST3D(const Real *givenBoundaryVars,
                                     const int *nodeType,
                                     const int *geometryProperty, Real *f) {
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC1(0, 0, 0)];
    if (vt == Vertex_ExtrapolPressure1ST) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC2(0, 0, 0)];
        Real rhoGiven = givenBoundaryVars[0];
        Real rho = 0;
        for (int xiIdx = 0; xiIdx < NUMXI; xiIdx++) {
            Real cx{CS * XI[xiIdx * LATTDIM]};
            Real cy{CS * XI[xiIdx * LATTDIM + 1]};
            Real cz{CS * XI[xiIdx * LATTDIM + 2]};
            switch (vg) {
                case VG_IP: {
                    if (cx > 0) {
                        f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                            f[OPS_ACC_MD3(xiIdx, 1, 0, 0)];
                    }
                } break;
                case VG_IM: {
                    if (cx < 0) {
                        f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                            f[OPS_ACC_MD3(xiIdx, -1, 0, 0)];
                    }
                } break;
                case VG_JP: {
                    if (cy > 0) {
                        f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                            f[OPS_ACC_MD3(xiIdx, 0, 1, 0)];
                    }
                } break;
                case VG_JM: {
                    if (cy < 0) {
                        f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                            f[OPS_ACC_MD3(xiIdx, 0, -1, 0)];
                    }
                } break;
                case VG_KP: {
                    if (cz > 0) {
                        f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 1)];
                    }
                } break;
                case VG_KM: {
                    if (cz < 0) {
                        f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                            f[OPS_ACC_MD3(xiIdx, 0, 0, -1)];
                    }
                } break;
                case VG_IPJP_I: {
                    if ((cx >= 0 && cy > 0) || (cx > 0 && cy == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 0, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 1, 0)];
                        }
                    }
                } break;
                case VG_IPJM_I: {
                    if ((cx >= 0 && cy < 0) || (cx > 0 && cy == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, -1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 0, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, -1, 0)];
                        }
                    }
                } break;
                case VG_IMJP_I: {
                    if ((cx <= 0 && cy > 0) || (cx < 0 && cy == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, -1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 0, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 1, 0)];
                        }
                    }
                } break;
                case VG_IMJM_I: {
                    if ((cx <= 0 && cy < 0) || (cx < 0 && cy == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, -1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, -1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 0, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, -1, 0)];
                        }
                    }
                } break;
                case VG_IPKP_I: {
                    if ((cx >= 0 && cz > 0) || (cx > 0 && cz == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 0, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 0, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, 1)];
                        }
                    }
                } break;
                case VG_IPKM_I: {
                    if ((cx >= 0 && cz < 0) || (cx > 0 && cz == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 0, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 0, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, -1)];
                        }
                    }
                } break;
                case VG_IMKP_I: {
                    if ((cx <= 0 && cz > 0) || (cx < 0 && cz == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 0, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, -1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 0, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, 1)];
                        }
                    }
                } break;
                case VG_IMKM_I: {
                    if ((cx <= 0 && cz < 0) || (cx < 0 && cz == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 0, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, -1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 0, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, -1)];
                        }
                    }
                } break;
                case VG_JPKP_I: {
                    if ((cy >= 0 && cz > 0) || (cy > 0 && cz == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 0, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(0, 1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, 1)];
                        }
                    }
                } break;
                case VG_JPKM_I: {
                    if ((cy >= 0 && cz < 0) || (cy > 0 && cz == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 0, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(0, 1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, -1)];
                        }
                    }
                } break;
                case VG_JMKP_I: {
                    if ((cy <= 0 && cz > 0) || (cy < 0 && cz == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 0, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, -1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(0, -1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, 1)];
                        }
                    }
                } break;
                case VG_JMKM_I: {
                    if ((cy <= 0 && cz < 0) || (cy < 0 && cz == 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 0, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, -1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(0, -1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, -1)];
                        }
                    }
                } break;
                case VG_IPJPKP_I: {
                    if ((cx >= 0 && cy >= 0 && cz >= 0) &&
                        (cx != 0 || cy != 0 || cz != 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 1, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 0, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, 1)];
                        }
                    }
                } break;
                case VG_IPJPKM_I: {
                    if ((cx >= 0 && cy >= 0 && cz <= 0) &&
                        (cx != 0 || cy != 0 || cz != 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 1, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 0, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, -1)];
                        }
                    }
                } break;
                case VG_IPJMKP_I: {
                    if ((cx >= 0 && cy <= 0 && cz >= 0) &&
                        (cx != 0 || cy != 0 || cz != 0)) {
                        if (vt == nodeType[OPS_ACC1(0, -1, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 0, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, -1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, -1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, 1)];
                        }
                    }
                } break;
                case VG_IPJMKM_I: {
                    if ((cx >= 0 && cy <= 0 && cz <= 0) &&
                        (cx != 0 || cy != 0 || cz != 0)) {
                        if (vt == nodeType[OPS_ACC1(0, -1, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, 0, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, -1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(1, -1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, -1)];
                        }
                    }
                } break;
                case VG_IMJPKP_I: {
                    if ((cx <= 0 && cy >= 0 && cz >= 0) &&
                        (cx != 0 || cy != 0 || cz != 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 1, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, -1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 0, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, 1)];
                        }
                    }
                } break;
                case VG_IMJPKM_I: {
                    if ((cx <= 0 && cy >= 0 && cz <= 0) &&
                        (cx != 0 || cy != 0 || cz != 0)) {
                        if (vt == nodeType[OPS_ACC1(0, 1, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, -1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 0, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, -1)];
                        }
                    }
                } break;
                case VG_IMJMKP_I: {
                    if ((cx <= 0 && cy <= 0 && cz >= 0) &&
                        (cx != 0 || cy != 0 || cz != 0)) {
                        if (vt == nodeType[OPS_ACC1(0, -1, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, -1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 0, 1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, -1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, -1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, 1)];
                        }
                    }
                } break;
                case VG_IMJMKM_I: {
                    if ((cx <= 0 && cy <= 0 && cz <= 0) &&
                        (cx != 0 || cy != 0 || cz != 0)) {
                        if (vt == nodeType[OPS_ACC1(0, -1, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, -1, 0, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, 0, -1)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, -1, 0)];
                        }
                        if (vt == nodeType[OPS_ACC1(-1, -1, 0)]) {
                            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] =
                                f[OPS_ACC_MD3(xiIdx, 0, 0, -1)];
                        }
                    }
                } break;
                default:
                    break;
            }
            rho += f[OPS_ACC_MD3(xiIdx, 0, 0, 0)];
        }
        Real ratio = rhoGiven / rho;
        for (int xiIdx = 0; xiIdx < NUMXI; xiIdx++) {
            f[OPS_ACC_MD3(xiIdx, 0, 0, 0)] *= ratio;
        }

    } else {
#ifdef debug
        ops_printf("%s\n",
                   "Warning: this node is not a extrapol pressure "
                   "boundary point: KerCutCellExtraolPressure1ST3D");
#endif
    }
}

void KerCutCellEQMDiffuseRefl3D(Real *f, const int *nodeType,
                                const int *geometryProperty,
                                const Real *givenMacroVars,
                                const int *componentId) {
    // This kernel is suitable for any single-speed lattice
    // but only for the second-order expansion at this moment
    // Therefore, the equilibrium function order is fixed at 2
    const int equilibriumOrder{2};
    const int compoIdx{*componentId};
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC_MD1(compoIdx, 0, 0, 0)];
    if (vt == Vertex_EQMDiffuseRefl) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC2(0, 0, 0)];
        Real u = givenMacroVars[1];
        Real v = givenMacroVars[2];
        Real w = givenMacroVars[3];
#ifdef CPU
#if DebugLevel >= 2
        ops_printf(
            "KerCutCellEQMDiffuseRefl3D: We received the following "
            "conditions for the surface %i:\n",
            geometryProperty[OPS_ACC2(0, 0, 0)]);
        ops_printf("U=%f, V=%f, W=%f for the component %i\n", u, v, w,
                   compoIdx);
#endif
#endif
        int numOutgoing{0};
        int numIncoming{0};
        int numParallel{0};
        int *outgoing = new int[COMPOINDEX[2 * compoIdx + 1] -
                                COMPOINDEX[2 * compoIdx] + 1];
        int *incoming = new int[COMPOINDEX[2 * compoIdx + 1] -
                                COMPOINDEX[2 * compoIdx] + 1];
        int *parallel = new int[COMPOINDEX[2 * compoIdx + 1] -
                                COMPOINDEX[2 * compoIdx] + 1];
        Real rhoIncoming{0};
        Real rhoParallel{0};
        Real deltaRho{0};
        for (int xiIdx = COMPOINDEX[2 * compoIdx];
             xiIdx <= COMPOINDEX[2 * compoIdx + 1]; xiIdx++) {
            Real cx{CS * XI[xiIdx * LATTDIM]};
            Real cy{CS * XI[xiIdx * LATTDIM + 1]};
            Real cz{CS * XI[xiIdx * LATTDIM + 2]};
            BndryDvType bdt = FindBdyDvType3D(vg, &XI[xiIdx * LATTDIM]);
            switch (bdt) {
                case BndryDv_Incoming: {
                    incoming[numIncoming] = xiIdx;
                    rhoIncoming += f[OPS_ACC_MD0(xiIdx, 0, 0, 0)];
                    numIncoming++;
                } break;
                case BndryDv_Outgoing: {
                    outgoing[numOutgoing] = xiIdx;
                    deltaRho +=
                        (2 * WEIGHTS[xiIdx]) * (cx * u + cy * v + cz * w);
                    numOutgoing++;
                } break;
                case BndryDv_Parallel: {
                    parallel[numParallel] = xiIdx;
                    rhoParallel +=
                        CalcBGKFeq(xiIdx, 1, u, v, w, 1, equilibriumOrder);
                    numParallel++;
                } break;
                default:
                    break;
            }
        }
        Real rhoWall = 2 * rhoIncoming / (1 - deltaRho - rhoParallel);
#ifdef CPU
#if DebugLevel >= 2
        ops_printf("Calculated wall density =  %f\n", rhoWall);
#endif
#endif
        for (int idx = 0; idx < numParallel; idx++) {
            f[OPS_ACC_MD0(parallel[idx], 0, 0, 0)] = CalcBGKFeq(
                parallel[idx], rhoWall, u, v, w, 1, equilibriumOrder);
        }
        for (int idx = 0; idx < numOutgoing; idx++) {
            int xiIdx = outgoing[idx];
            Real cx{CS * XI[xiIdx * LATTDIM]};
            Real cy{CS * XI[xiIdx * LATTDIM + 1]};
            Real cz{CS * XI[xiIdx * LATTDIM + 2]};
            f[OPS_ACC_MD0(xiIdx, 0, 0, 0)] =
                f[OPS_ACC_MD0(OPP[xiIdx], 0, 0, 0)] +
                2 * rhoWall * WEIGHTS[xiIdx] * (cx * u + cy * v + cz * w);
#ifdef CPU
            const Real res{f[OPS_ACC_MD0(xiIdx, 0, 0, 0)]};
            if (isnan(res) || res <= 0 || isinf(res)) {
                ops_printf(
                    "Error! Distribution function %f becomes "
                    "invalid for the component %i at the lattice "
                    "%i\n",
                    res, compoIdx, xiIdx);
                assert(!(isnan(res) || res <= 0 || isinf(res)));
            }
#endif
        }
        delete[] outgoing;
        delete[] incoming;
        delete[] parallel;
        //}
    } else {
#ifdef CPU
#if DebugLevel >= 2
        ops_printf("%s\n",
                   "Warning: this node is not a equilibrium diffuse reflection "
                   "boundary condition point.");
#endif
#endif
    }
}

void KerCutCellPeriodic3D(Real *f, const int *nodeType,
                          const int *geometryProperty, const int *componentId) {
    const int compoId{*componentId};
    VertexTypes vt = (VertexTypes)nodeType[OPS_ACC_MD1(compoId, 0, 0, 0)];
    const int xiStartPos{COMPOINDEX[2 * compoId]};
    const int xiEndPos{COMPOINDEX[2 * compoId + 1]};
    if (vt == Vertex_Periodic) {
        VertexGeometryTypes vg =
            (VertexGeometryTypes)geometryProperty[OPS_ACC2(0, 0, 0)];
        switch (vg) {
            case VG_IP:
                for (int xiIndex = xiStartPos; xiIndex <= xiEndPos; xiIndex++) {
                    f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                        f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
                }
                break;
            case VG_IM:
                for (int xiIndex = xiStartPos; xiIndex <= xiEndPos; xiIndex++) {
                    f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                        f[OPS_ACC_MD0(xiIndex, 1, 0, 0)];
                }
                break;
            case VG_JP:
                for (int xiIndex = xiStartPos; xiIndex <= xiEndPos; xiIndex++) {
                    f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                        f[OPS_ACC_MD0(xiIndex, 0, -1, 0)];
                }
                break;
            case VG_JM:
                for (int xiIndex = xiStartPos; xiIndex <= xiEndPos; xiIndex++) {
                    f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                        f[OPS_ACC_MD0(xiIndex, 0, 1, 0)];
                }
                break;
            case VG_KP:
                for (int xiIndex = xiStartPos; xiIndex <= xiEndPos; xiIndex++) {
                    f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                        f[OPS_ACC_MD0(xiIndex, 0, 0, -1)];
                }
                break;
            case VG_KM:
                for (int xiIndex = xiStartPos; xiIndex <= xiEndPos; xiIndex++) {
                    f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 1)];
                }
                break;
                // There are only inner corners for block boundaries
            case VG_IPJP_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, -1, 0)];
                    }
                }
            } break;
            case VG_IPJM_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 1, 0)];
                    }
                }
            } break;
            case VG_IMJP_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 1, 0, 0)];
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, -1, 0)];
                    }
                }
            } break;
            case VG_IMJM_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 1, 0, 0)];
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 1, 0)];
                    }
                }
            } break;

            case VG_IPKP_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
                    }
                }
                // VG_KP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, -1)];
                    }
                }
            } break;
            case VG_IPKM_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
                    }
                }
                // VG_KM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, 1)];
                    }
                }
            } break;
            case VG_IMKP_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 1, 0, 0)];
                    }
                }
                // VG_KP
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, -1)];
                    }
                }
            } break;
            case VG_IMKM_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 1, 0, 0)];
                    }
                }
                // VG_KM
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, 1)];
                    }
                }
            } break;
            case VG_JPKP_I: {
                // VG_JP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, -1, 0)];
                    }
                }
                // VG_KP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, -1)];
                    }
                }
            } break;
            case VG_JPKM_I: {
                // VG_JP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, -1, 0)];
                    }
                }
                // VG_KM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, 1)];
                    }
                }
            } break;
            case VG_JMKP_I: {
                // VG_JM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 1, 0)];
                    }
                }
                // VG_KP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, -1)];
                    }
                }
            } break;
            case VG_JMKM_I: {
                // VG_JM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 1, 0)];
                    }
                }
                // VG_KM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, 1)];
                    }
                }
            } break;
            case VG_IPJPKP_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, -1, 0)];
                    }
                }
                // VG_KP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, -1)];
                    }
                }
            } break;
            case VG_IPJPKM_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, -1, 0)];
                    }
                }
                // VG_KM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, 1)];
                    }
                }
            } break;
            case VG_IPJMKP_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 1, 0)];
                    }
                }
                // VG_KP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, -1)];
                    }
                }
            } break;
            case VG_IPJMKM_I: {
                // VG_IP
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 1, 0)];
                    }
                }
                // VG_KM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, 1)];
                    }
                }
            } break;
            case VG_IMJPKP_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 1, 0, 0)];
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, -1, 0)];
                    }
                }
                // VG_KP
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, -1)];
                    }
                }
            } break;
            case VG_IMJPKM_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 1, 0, 0)];
                    }
                }
                // VG_JP
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, -1, 0)];
                    }
                }
                // VG_KM
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, 1)];
                    }
                }
            } break;
            case VG_IMJMKP_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 1, 0, 0)];
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, 1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 1, 0)];
                    }
                }
                // VG_KP
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, -1)];
                    }
                }

            } break;
            case VG_IMJMKM_I: {
                // VG_IM
                if (vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 1, 0, 0)];
                    }
                }
                // VG_JM
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, 0, -1)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 1, 0)];
                    }
                }
                // VG_KM
                if (vt == nodeType[OPS_ACC_MD1(compoId, -1, 0, 0)] &&
                    vt == nodeType[OPS_ACC_MD1(compoId, 0, -1, 0)]) {
                    for (int xiIndex = xiStartPos; xiIndex <= xiEndPos;
                         xiIndex++) {
                        f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                            f[OPS_ACC_MD0(xiIndex, 0, 0, 1)];
                    }
                }
            } break;
            default:
                break;
        }
#ifdef CPU
        for (int xiIndex = xiStartPos; xiIndex <= xiEndPos; xiIndex++) {
            f[OPS_ACC_MD0(xiIndex, 0, 0, 0)] =
                f[OPS_ACC_MD0(xiIndex, -1, 0, 0)];
            const Real res{f[OPS_ACC_MD0(xiIndex, 0, 0, 0)]};
            if (isnan(res) || res <= 0 || isinf(res)) {
                ops_printf(
                    "Error! Distribution function %f becomes "
                    "invalid for the component %i at the lattice "
                    "%i\n at the surface %i\n",
                    res, compoId, xiIndex, geometryProperty[OPS_ACC2(0, 0, 0)]);
                assert(!(isnan(res) || res <= 0 || isinf(res)));
            }
        }
#endif
    } else {
#ifdef CPU
#if DebugLevel >= 2
        ops_printf("%s\n",
                   "Warning: this node is not a periodic boundary "
                   "point.");
#endif
#endif
    }
}
#endif  // OPS_3D
#endif  /* BOUNDARY_KERNEL_H */