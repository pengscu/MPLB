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

/*! @brief   Head files for boundary conditions
 * @author  Jianping Meng
 * @details Declaring functions related to boundary conditions.
 */
#include "boundary.h"
/*!
 * boundaryHaloPt: the halo point needed by the boundary condition
 * In general, the periodic boundary conditions will need one halo point
 * even such as the scheme-collision scheme need no halo points.
 * Other physical boundary schemes usually don't need halo point.
 *
 */
int boundaryHaloPt{1};
const int BoundaryHaloNum() { return boundaryHaloPt; }
void SetBoundaryHaloNum(const int boundaryHaloNum) {
    boundaryHaloPt = boundaryHaloNum;
}
BndryDvType FindBdyDvType(const VertexGeometryTypes vg,
                          const Real* discreteVelocity) {
    Real cx = discreteVelocity[0];
    Real cy = discreteVelocity[1];
    BndryDvType res{BndryDv_Invalid};
    switch (vg) {
        case VG_IP: {
            if (cx < 0) {
                res = BndryDv_Incoming;
            }
            if (cx == 0) {
                res = BndryDv_Parallel;
            }
            if (cx > 0) {
                res = BndryDv_Outgoing;
            }
        } break;
        case VG_IM: {
            if (cx > 0) {
                res = BndryDv_Incoming;
            }
            if (cx == 0) {
                res = BndryDv_Parallel;
            }
            if (cx < 0) {
                res = BndryDv_Outgoing;
            }
        } break;
        case VG_JP: {
            if (cy < 0) {
                res = BndryDv_Incoming;
            }
            if (cy == 0) {
                res = BndryDv_Parallel;
            }
            if (cy > 0) {
                res = BndryDv_Outgoing;
            }

        } break;
        case VG_JM: {
            if (cy > 0) {
                res = BndryDv_Incoming;
            }
            if (cy == 0) {
                res = BndryDv_Parallel;
            }
            if (cy < 0) {
                res = BndryDv_Outgoing;
            }
        } break;
        case VG_IPJP_I: {
            if ((cx <= 0 && cy < 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cy > 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IPJM_I: {
            if ((cx <= 0 && cy > 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cy < 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMJP_I: {
            if ((cx >= 0 && cy < 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cy > 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMJM_I: {
            if ((cx >= 0 && cy > 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cy < 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }

        } break;
        case VG_IPJP_O: {
            if ((cx <= 0 && cy < 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cy > 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IPJM_O: {
            if ((cx <= 0 && cy > 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cy < 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMJP_O: {
            if ((cx >= 0 && cy < 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cy > 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMJM_O: {
            if ((cx >= 0 && cy > 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cy < 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }

        } break;
        default:
            break;
    }
#ifdef debug
    if (BndryDv_Invalid == res) {
        ops_printf("%s\n",
                   "Warning: Some wrong in determining discrete velocity type "
                   "at 2D boundary ");
    }
#endif
    return res;
}

BndryDvType FindBdyDvType3D(const VertexGeometryTypes vg,
                            const Real* discreteVelocity) {
    Real cx = discreteVelocity[0];
    Real cy = discreteVelocity[1];
    Real cz = discreteVelocity[2];
    BndryDvType res{BndryDv_Invalid};
    switch (vg) {
        case VG_IP: {
            if (cx < 0) {
                res = BndryDv_Incoming;
            }
            if (cx == 0) {
                res = BndryDv_Parallel;
            }
            if (cx > 0) {
                res = BndryDv_Outgoing;
            }
        } break;
        case VG_IM: {
            if (cx > 0) {
                res = BndryDv_Incoming;
            }
            if (cx == 0) {
                res = BndryDv_Parallel;
            }
            if (cx < 0) {
                res = BndryDv_Outgoing;
            }
        } break;
        case VG_JP: {
            if (cy < 0) {
                res = BndryDv_Incoming;
            }
            if (cy == 0) {
                res = BndryDv_Parallel;
            }
            if (cy > 0) {
                res = BndryDv_Outgoing;
            }

        } break;
        case VG_JM: {
            if (cy > 0) {
                res = BndryDv_Incoming;
            }
            if (cy == 0) {
                res = BndryDv_Parallel;
            }
            if (cy < 0) {
                res = BndryDv_Outgoing;
            }
        } break;
        case VG_KP: {
            if (cz < 0) {
                res = BndryDv_Incoming;
            }
            if (cz == 0) {
                res = BndryDv_Parallel;
            }
            if (cz > 0) {
                res = BndryDv_Outgoing;
            }

        } break;
        case VG_KM: {
            if (cz > 0) {
                res = BndryDv_Incoming;
            }
            if (cz == 0) {
                res = BndryDv_Parallel;
            }
            if (cz < 0) {
                res = BndryDv_Outgoing;
            }
        } break;
        case VG_IPJP_I: {
            if ((cx <= 0 && cy < 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cy > 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IPJM_I: {
            if ((cx <= 0 && cy > 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cy < 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMJP_I: {
            if ((cx >= 0 && cy < 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cy > 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMJM_I: {
            if ((cx >= 0 && cy > 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cy < 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }

        } break;
        case VG_IPKP_I: {
            if ((cx <= 0 && cz < 0) || (cx < 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cz > 0) || (cx > 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IPKM_I: {
            if ((cx <= 0 && cz > 0) || (cx < 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cz < 0) || (cx > 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMKP_I: {
            if ((cx >= 0 && cz < 0) || (cx > 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cz > 0) || (cx < 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMKM_I: {
            if ((cx >= 0 && cz > 0) || (cx > 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cz < 0) || (cx < 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }

        } break;
        case VG_JPKP_I: {
            if ((cy <= 0 && cz < 0) || (cy < 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cy >= 0 && cz > 0) || (cy > 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_JPKM_I: {
            if ((cy <= 0 && cz > 0) || (cy < 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cy >= 0 && cz < 0) || (cy > 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_JMKP_I: {
            if ((cy >= 0 && cz < 0) || (cy > 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cy <= 0 && cz > 0) || (cy < 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_JMKM_I: {
            if ((cy >= 0 && cz > 0) || (cy > 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cy <= 0 && cz < 0) || (cy < 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }

        } break;
        case VG_IPJP_O: {
            if ((cx <= 0 && cy < 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cy > 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IPJM_O: {
            if ((cx <= 0 && cy > 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cy < 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMJP_O: {
            if ((cx >= 0 && cy < 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cy > 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMJM_O: {
            if ((cx >= 0 && cy > 0) || (cx > 0 && cy == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cy < 0) || (cx < 0 && cy == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }

        } break;
        case VG_IPKP_O: {
            if ((cx <= 0 && cz < 0) || (cx < 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cz > 0) || (cx > 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IPKM_O: {
            if ((cx <= 0 && cz > 0) || (cx < 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cz < 0) || (cx > 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMKP_O: {
            if ((cx >= 0 && cz < 0) || (cx > 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cz > 0) || (cx < 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IMKM_O: {
            if ((cx >= 0 && cz > 0) || (cx > 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx <= 0 && cz < 0) || (cx < 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_JPKP_O: {
            if ((cx <= 0 && cz < 0) || (cx < 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cx >= 0 && cz > 0) || (cx > 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_JPKM_O: {
            if ((cy <= 0 && cz > 0) || (cy < 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cy >= 0 && cz < 0) || (cy > 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_JMKP_O: {
            if ((cy >= 0 && cz < 0) || (cy > 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cy <= 0 && cz > 0) || (cy < 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_JMKM_O: {
            if ((cy >= 0 && cz > 0) || (cy > 0 && cz == 0)) {
                res = BndryDv_Incoming;
            } else if ((cy <= 0 && cz < 0) || (cy < 0 && cz == 0)) {
                res = BndryDv_Outgoing;
            } else {
                res = BndryDv_Parallel;
            }
        } break;
        case VG_IPJPKP_I: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx <= 0 && cy <= 0 && cz <= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx >= 0 && cy >= 0 && cz >= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IPJPKM_I: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx <= 0 && cy <= 0 && cz >= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx >= 0 && cy >= 0 && cz <= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IPJMKP_I: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx <= 0 && cy >= 0 && cz <= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx >= 0 && cy <= 0 && cz >= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IPJMKM_I: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx <= 0 && cy >= 0 && cz >= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx >= 0 && cy <= 0 && cz <= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IMJPKP_I: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx >= 0 && cy <= 0 && cz <= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx <= 0 && cy >= 0 && cz >= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IMJPKM_I: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx >= 0 && cy <= 0 && cz >= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx <= 0 && cy >= 0 && cz <= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IMJMKP_I: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx >= 0 && cy >= 0 && cz <= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx <= 0 && cy <= 0 && cz >= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IMJMKM_I: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx >= 0 && cy >= 0 && cz >= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx <= 0 && cy <= 0 && cz <= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IPJPKP_O: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx <= 0 && cy <= 0 && cz <= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx >= 0 && cy >= 0 && cz >= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IPJPKM_O: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx <= 0 && cy <= 0 && cz >= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx >= 0 && cy >= 0 && cz <= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IPJMKP_O: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx <= 0 && cy >= 0 && cz <= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx >= 0 && cy <= 0 && cz >= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IPJMKM_O: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx <= 0 && cy >= 0 && cz >= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx >= 0 && cy <= 0 && cz <= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IMJPKP_O: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx >= 0 && cy <= 0 && cz <= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx <= 0 && cy >= 0 && cz >= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IMJPKM_O: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx >= 0 && cy <= 0 && cz >= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx <= 0 && cy >= 0 && cz <= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IMJMKP_O: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx >= 0 && cy >= 0 && cz <= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx <= 0 && cy <= 0 && cz >= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;
        case VG_IMJMKM_O: {
            if (cx == 0 && cy == 0 && cz == 0) {
                res = BndryDv_Parallel;
            } else {
                if (cx >= 0 && cy >= 0 && cz >= 0) {
                    res = BndryDv_Outgoing;
                } else if (cx <= 0 && cy <= 0 && cz <= 0) {
                    res = BndryDv_Incoming;
                } else {
                    res = BndryDv_Parallel;
                }
            }
        } break;

        default:
            break;
    }
#ifdef debug
    if (BndryDv_Invalid == res) {
        ops_printf("%s\n",
                   "Warning: Something wrong in determining discrete velocity "
                   "type at 3D boundary");
    }
#endif
    return res;
}

void BoundaryNormal3D(const VertexGeometryTypes vg, int* unitNormal) {
    if (nullptr != unitNormal) {
        switch (vg) {
            case VG_IP: {
                unitNormal[0] = 1;
                unitNormal[1] = 0;
                unitNormal[2] = 0;
            } break;
            case VG_IM: {
                unitNormal[0] = -1;
                unitNormal[1] = 0;
                unitNormal[2] = 0;
            } break;
            case VG_JP: {
                unitNormal[0] = 0;
                unitNormal[1] = 1;
                unitNormal[2] = 0;
            } break;
            case VG_JM: {
                unitNormal[0] = 0;
                unitNormal[1] = -1;
                unitNormal[2] = 0;
            } break;
            case VG_KP: {
                unitNormal[0] = 0;
                unitNormal[1] = 0;
                unitNormal[2] = 1;
            } break;
            case VG_KM: {
                unitNormal[0] = 0;
                unitNormal[1] = 0;
                unitNormal[2] = -1;
            } break;
            case VG_IPJP_I: {
                unitNormal[0] = 1/sqrt(2);
                unitNormal[1] = 1/sqrt(2);
                unitNormal[2] = 0;
            } break;
            case VG_IPJM_I: {
                unitNormal[0] = 1/sqrt(2);
                unitNormal[1] = -1/sqrt(2);
                unitNormal[2] = 0;
            } break;
            case VG_IMJP_I: {
                unitNormal[0] = -1/sqrt(2);
                unitNormal[1] = 1/sqrt(2);
                unitNormal[2] = 0;
            } break;
            case VG_IMJM_I: {
                unitNormal[0] = -1/sqrt(2);
                unitNormal[1] = -1/sqrt(2);
                unitNormal[2] = 0;
            } break;
            case VG_IPKP_I: {
                unitNormal[0] = 1/sqrt(2);
                unitNormal[1] = 0;
                unitNormal[2] = 1/sqrt(2);
            } break;
            case VG_IPKM_I: {
                unitNormal[0] = 1/sqrt(2);
                unitNormal[1] = 0;
                unitNormal[2] = -1/sqrt(2);
            } break;
            case VG_IMKP_I: {
                unitNormal[0] = -1/sqrt(2);
                unitNormal[1] = 0;
                unitNormal[2] = 1/sqrt(2);
            } break;
            case VG_IMKM_I: {
                unitNormal[0] = -1/sqrt(2);
                unitNormal[1] = 0;
                unitNormal[2] = -1/sqrt(2);
            } break;
            case VG_JPKP_I: {
                unitNormal[0] = 0;
                unitNormal[1] = 1/sqrt(2);
                unitNormal[2] = 1/sqrt(2);
            } break;
            case VG_JPKM_I: {
                unitNormal[0] = 0;
                unitNormal[1] = 1/sqrt(2);
                unitNormal[2] = -1/sqrt(2);
            } break;
            case VG_JMKP_I: {
                unitNormal[0] = 0;
                unitNormal[1] = -1/sqrt(2);
                unitNormal[2] = 1/sqrt(2);
            } break;
            case VG_JMKM_I: {
                unitNormal[0] = 0;
                unitNormal[1] = -1/sqrt(2);
                unitNormal[2] = -1/sqrt(2);
            } break;

            case VG_IPJP_O: {
                unitNormal[0] = 1/sqrt(2);
                unitNormal[1] = 1/sqrt(2);
                unitNormal[2] = 0;
            } break;
            case VG_IPJM_O: {
                unitNormal[0] = 1/sqrt(2);
                unitNormal[1] = -1/sqrt(2);
                unitNormal[2] = 0;
            } break;
            case VG_IMJP_O: {
                unitNormal[0] = -1/sqrt(2);
                unitNormal[1] = 1/sqrt(2);
                unitNormal[2] = 0;
            } break;
            case VG_IMJM_O: {
                unitNormal[0] = -1/sqrt(2);
                unitNormal[1] = -1/sqrt(2);
                unitNormal[2] = 0;
            } break;
            case VG_IPKP_O: {
                unitNormal[0] = 1/sqrt(2);
                unitNormal[1] = 0;
                unitNormal[2] = 1/sqrt(2);
            } break;
            case VG_IPKM_O: {
                unitNormal[0] = 1/sqrt(2);
                unitNormal[1] = 0;
                unitNormal[2] = -1/sqrt(2);
            } break;
            case VG_IMKP_O: {
                unitNormal[0] = -1/sqrt(2);
                unitNormal[1] = 0;
                unitNormal[2] = 1/sqrt(2);
            } break;
            case VG_IMKM_O: {
                unitNormal[0] = -1/sqrt(2);
                unitNormal[1] = 0;
                unitNormal[2] = -1/sqrt(2);
            } break;
            case VG_JPKP_O: {
                unitNormal[0] = 0;
                unitNormal[1] = 1/sqrt(2);
                unitNormal[2] = 1/sqrt(2);
            } break;
            case VG_JPKM_O: {
                unitNormal[0] = 0;
                unitNormal[1] = 1/sqrt(2);
                unitNormal[2] = -1/sqrt(2);
            } break;
            case VG_JMKP_O: {
                unitNormal[0] = 0;
                unitNormal[1] = -1/sqrt(2);
                unitNormal[2] = 1/sqrt(2);
            } break;
            case VG_JMKM_O: {
                unitNormal[0] = 0;
                unitNormal[1] = -1/sqrt(2);
                unitNormal[2] = -1/sqrt(2);
            } break;

            case VG_IPJPKP_I: {
                unitNormal[0] = 1/sqrt(3);
                unitNormal[1] = 1/sqrt(3);
                unitNormal[2] = 1/sqrt(3);
            } break;
            case VG_IPJPKM_I: {
                unitNormal[0] = 1/sqrt(3);
                unitNormal[1] = 1/sqrt(3);
                unitNormal[2] = -1/sqrt(3);
            } break;
            case VG_IPJMKP_I: {
                unitNormal[0] = 1/sqrt(3);
                unitNormal[1] = -1/sqrt(3);
                unitNormal[2] = 1/sqrt(3);
            } break;
            case VG_IPJMKM_I: {
                unitNormal[0] = 1/sqrt(3);
                unitNormal[1] = -1/sqrt(3);
                unitNormal[2] = -1/sqrt(3);
            } break;
            case VG_IMJPKP_I: {
                unitNormal[0] = -1/sqrt(3);
                unitNormal[1] = 1/sqrt(3);
                unitNormal[2] = 1/sqrt(3);
            } break;
            case VG_IMJPKM_I: {
                unitNormal[0] = -1/sqrt(3);
                unitNormal[1] = 1/sqrt(3);
                unitNormal[2] = -1/sqrt(3);
            } break;
            case VG_IMJMKP_I: {
                unitNormal[0] = -1/sqrt(3);
                unitNormal[1] = -1/sqrt(3);
                unitNormal[2] = 1/sqrt(3);
            } break;
            case VG_IMJMKM_I: {
                unitNormal[0] = -1/sqrt(3);
                unitNormal[1] = -1/sqrt(3);
                unitNormal[2] = -1/sqrt(3);
            } break;
             case VG_IPJPKP_O: {
                unitNormal[0] = 1/sqrt(3);
                unitNormal[1] = 1/sqrt(3);
                unitNormal[2] = 1/sqrt(3);
            } break;
            case VG_IPJPKM_O: {
                unitNormal[0] = 1/sqrt(3);
                unitNormal[1] = 1/sqrt(3);
                unitNormal[2] = -1/sqrt(3);
            } break;
            case VG_IPJMKP_O: {
                unitNormal[0] = 1/sqrt(3);
                unitNormal[1] = -1/sqrt(3);
                unitNormal[2] = 1/sqrt(3);
            } break;
            case VG_IPJMKM_O: {
                unitNormal[0] = 1/sqrt(3);
                unitNormal[1] = -1/sqrt(3);
                unitNormal[2] = -1/sqrt(3);
            } break;
            case VG_IMJPKP_O: {
                unitNormal[0] = -1/sqrt(3);
                unitNormal[1] = 1/sqrt(3);
                unitNormal[2] = 1/sqrt(3);
            } break;
            case VG_IMJPKM_O: {
                unitNormal[0] = -1/sqrt(3);
                unitNormal[1] = 1/sqrt(3);
                unitNormal[2] = -1/sqrt(3);
            } break;
            case VG_IMJMKP_O: {
                unitNormal[0] = -1/sqrt(3);
                unitNormal[1] = -1/sqrt(3);
                unitNormal[2] = 1/sqrt(3);
            } break;
            case VG_IMJMKM_O: {
                unitNormal[0] = -1/sqrt(3);
                unitNormal[1] = -1/sqrt(3);
                unitNormal[2] = -1/sqrt(3);
            } break;
            default:
                break;
        }
    }
}
#include "boundary_kernel.h"
