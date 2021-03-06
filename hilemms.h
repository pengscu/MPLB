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

#ifndef Hilemms_H
#define Hilemms_H

#include <string.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
#include "boundary.h"
#include "evolution.h"
#include "evolution3d.h"
#include "flowfield.h"
#include "model.h"
#include "ops_seq.h"
#include "scheme.h"
#include "type.h"
// blockNum: total number if blocks.
// blockSize: array of integers specifying the block blocksize.
// meshSize: The size of mesh i.e. dx (At present dx = dy = dz).
// startPos: Starting position of each block.
void DefineProblemDomain(const int blockNum, const std::vector<int> blockSize,
                         const Real meshSize, const std::vector<Real> startPos);

// Iterator for transient simulations.
void Iterate(const int steps, const int checkPointPeriod);

// Iterator for steady simulations.
void Iterate(const Real convergenceCriteria, const int checkPointPeriod);

// Add 2D polygon.
// vertexNum: total number of vertexes.
// vertexCoords: Coordinates of each vertex.
void AddEmbeddedBody(int vertexNum, Real* vertexCoords);


// blockIndex: block Index
// compoId: component ID whose BC we want to set.
// surface: which surface to set.
// type: boundary condition type.
// MacroVarsComp: which all macrovars are to be used in specifying the BC.
// valueMacroVarsComp: specified value for the boundary condition for the macro
// vars which are defined using MacroVarsComp.
void DefineBlockBoundary(int blockIndex, int componentID,
                         BoundarySurface boundarySurface,
                         BoundaryType boundaryType,
                         const std::vector<VariableTypes>& macroVarTypes,
                         const std::vector<Real>& macroVarValues);

// blockIndex: Block Index
// blockStartPos: Starting position of the block in x, y, z directions to find
// coordinates. meshSize: Size of mesh (Assuming a constant in all 3 directions
// for stream collision scheme).
void CalculateBlockCoordinates(const int blockIndex, Real* blockStartPos,
                         Real meshsize);


void KerSetCoordinates(const Real* coordX, const Real* coordY, const int* idx,
                       Real* coordinates);
void KerSetCoordinates3D(const Real* coordX, const Real* coordY,
                         const Real* coordZ, const int* idx, Real* coordinates);

// Kernel which will call a user-defined function for initial conditions
void KerSetInitialMacroVars(Real* macroVars, const Real* coordinates,
                            const int* idx);
void AssignCoordinates(int blockIndex,
                       const std::vector<std::vector<Real>>& coordinates);
// blockIndex: Block id.
// Coordinates: Array to store coordinates of various points inside the domain.
// This function was defined in setup_comput_domain and has been declared here
// as we are not using the preprocessor code separately.

//User-defined function for initialising macroscopic variables
void InitialiseNodeMacroVars(Real* nodeMacroVars, const Real* nodeCoordinates);
//Defining the initial conditions by using user-defined functions
void DefineInitialCondition();
void  SetBlockGeometryProperty(int blockIndex);
void DefineHaloNumber(int Halo_Number, int Halo_Depth, int Scheme_Halo_points,
                      int Num_Bound_Halo_Points);
// Functions to check for inclusion.

// A wrapper Function which implements all the boundary conditions.
void ImplementBoundaryConditions();


// type: Circle/Sphere, Ellipse/Ellipsoid, superquadrics, ...
// centerPos: the position vector of the center point.
// controlParas: control parameters, e.g. radius for Circle/Sphere, ...
void EmbeddedBody(SolidBodyType type, int blockIndex,
                  std::vector<Real> centerPos, std::vector<Real> controlParas);


/**********************************************************/
/* Functions for embedded body.                           */
/**********************************************************/

void KerSetEmbeddedBodyBoundary(int* surfaceBoundary,
                               const int* geometryProperty, int* nodeType);

void KerSetEmbeddedCircle(Real* diameter, Real* centerPos,
                         const Real* coordinates, int* nodeType,
                         int* geometryProperty);

void KerSetEmbeddedEllipse(Real* semiMajorAxes, Real* semiMinorAxis,
                           Real* centerPos, const Real* coordinates,
                           int* nodeType, int* geometryProperty);

void KerSweep(const int* geometryProperty, int* nodeType);

void KerSyncGeometryProperty(const int* nodeType, int* geometryProperty);

void KerSetEmbeddedBodyGeometry(const int* nodeType, int* geometryProperty);

void HandleImmersedSolid();

#endif  // Hilemms_H