// Copyright 2017 the MPLB team. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
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

/** @brief Define the main iteration
 *  @author Jianping Meng
 **/
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include "boundary.h"
#include "evolution.h"
#include "evolution3d.h"
#include "flowfield.h"
#include "hilemms.h"
#include "model.h"
#include "ops_seq.h"
#include "scheme.h"
#include "setup_comput_domain.h"
#include "type.h"

// Code_modifcication needed
// Currently defining OPS 3d here. We need some mechanism to generate this
// automatically.
extern int HALODEPTH;

BoundarySurface surface[4] = {BoundarySurface_Left, BoundarySurface_Right, BoundarySurface_Top,
                              BoundarySurface_Bottom};

BoundaryType boundType[4] = {BoundaryType_EQMDiffuseRefl, BoundaryType_EQMDiffuseRefl,
                             BoundaryType_EQMDiffuseRefl,
                             BoundaryType_EQMDiffuseRefl};

void simulate() {
    std::string caseName{"2D_lid_Driven_cavity"};
    int spaceDim{2};
    DefineCase(caseName, spaceDim);

    std::vector<std::string> compoNames{"Fluid"};
    std::vector<int> compoid{0};
    std::vector<std::string> lattNames{"d2q9"};
    DefineComponents(compoNames, compoid, lattNames);

    std::vector<VariableTypes> marcoVarTypes{Variable_Rho, Variable_U,
                                             Variable_V};
    std::vector<std::string> macroVarNames{"rho", "u", "v"};
    std::vector<int> macroVarId{0, 1, 2};
    std::vector<int> macroCompoId{0, 0, 0};
    DefineMacroVars(marcoVarTypes, macroVarNames, macroVarId, macroCompoId);

    std::vector<EquilibriumType> equTypes{Equilibrium_BGKIsothermal2nd};
    std::vector<int> equCompoId{0};
    DefineEquilibrium(equTypes, equCompoId);

    SetupScheme();
    SetupBoundary();

    int blockIndex = 0;
    int componentId{0};
    std::vector<VariableTypes> MacroVarsComp{Variable_Rho, Variable_U,
                                             Variable_V};
    std::vector<Real> inletValMacroVarsComp{1, 0, 0};
    DefineBlockBoundary(blockIndex, componentId, surface[0], boundType[0],
                        MacroVarsComp, inletValMacroVarsComp);

    std::vector<Real> outletValMacroVarsComp{1, 0, 0};
    DefineBlockBoundary(blockIndex, componentId, surface[1], boundType[1],
                        MacroVarsComp, outletValMacroVarsComp);

    std::vector<Real> topValMacroVarsComp{1, 0.01, 0};
    DefineBlockBoundary(blockIndex, componentId, surface[2], boundType[2],
                        MacroVarsComp, topValMacroVarsComp);

    std::vector<Real> bottomValMacroVarsComp{1, 0, 0};
    DefineBlockBoundary(blockIndex, componentId, surface[3], boundType[3],
                        MacroVarsComp, bottomValMacroVarsComp);
    ops_printf("Block boundary defined!\n");

    int blockNum{1};
    std::vector<int> blockSize{51, 51};
    Real meshSize{0.02};
    std::vector<Real> startPos{0.0, 0.0};
    DefineProblemDomain(blockNum, blockSize, meshSize, startPos);

    //int blockIndex{0};
    //SetupGeomPropAndNodeType(blockIndex, boundType);

    int compoIdInitialCond{0};
    std::vector<Real> initialMacroValues{1, 0, 0};
    DefineInitialCondition(blockIndex, compoIdInitialCond, initialMacroValues);
    ops_printf("%s\n", "Flowfield is Initialised now!");

    std::vector<Real> tauRef{0.001};
    SetTauRef(tauRef);

    SetTimeStep(meshSize / SoundSpeed());

    // HALODEPTH = HaloPtNum();
    // ops_printf("%s\n", "Starting to allocate...");
    // DefineHaloTransfer();
    // // above calls must be before the ops_partition call.
    // //ops_partition((char*)"LBM");
    // ops_printf("%s\n", "Flowfield is setup now!");
    // InitialiseSolution();

#if 0
    // currently this information is not playin major role in this
    // implementation.
    SchemeType scheme{stStreamCollision};
    const int steps{5000};
    const int checkPeriod{500};
    Iterate(scheme, steps, checkPeriod);
#endif

    // if 0
    // currently this information is not playin major role in this
    // implementation.
    SchemeType scheme{Scheme_StreamCollision};
    const Real convergenceCriteria{1E-2};
    const int checkPeriod{200};
    Iterate(convergenceCriteria, checkPeriod);
    //#endif
}

int main(int argc, char** argv) {
    // OPS initialisation
    ops_init(argc, argv, 1);
    double ct0, ct1, et0, et1;
    ops_timers(&ct0, &et0);
    simulate();
    ops_timers(&ct1, &et1);
    ops_printf("\nTotal Wall time %lf\n", et1 - et0);
    // Print OPS performance details to output stream
    ops_timing_output(stdout);
    ops_exit();
}