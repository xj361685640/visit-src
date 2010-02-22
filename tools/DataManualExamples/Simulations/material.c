/*****************************************************************************
*
* Copyright (c) 2000 - 2008, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-400142
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#include <VisItControlInterface_V2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <materialhelpers.h>

#include "SimulationExample.h"

/* Data Access Function prototypes. */
int SimGetMetaData(VisIt_SimulationMetaData *, void *);
int SimGetMesh(int, const char *, VisIt_MeshData *, void *);
int SimGetMaterial(int, const char *, VisIt_MaterialData *, void *);
int SimGetVariable(int, const char *, visit_handle, void *);
int SimGetMixedVariable(int, const char *, visit_handle, void *);

void simulate_one_timestep(void);
void read_input_deck(void) { }
int  simulation_done(void)   { return 0; }

/* Is the simulation in run mode (not waiting for VisIt input) */
static int    runFlag = 1;
static int    simcycle = 0;
static double simtime = 0.;

/******************************************************************************
 *
 * Purpose: Callback function for control commands.
 *
 * Programmer: Brad Whitlock
 * Date:       Thu Jan 17 15:25:37 PST 2008
 *
 * Input Arguments:
 *   cmd    : The command string that we want the sim to execute.
 *   args   : String argument for the command.
 *   cbdata : User-provided callback data.
 *
 * Modifications:
 *
 *****************************************************************************/

void ControlCommandCallback(const char *cmd, const char *args, void *cbdata)
{
    if(strcmp(cmd, "halt") == 0)
        runFlag = 0;
    else if(strcmp(cmd, "step") == 0)
        simulate_one_timestep();
    else if(strcmp(cmd, "run") == 0)
        runFlag = 1;
}

/******************************************************************************
 *
 * Purpose: This is the main event loop function.
 *
 * Programmer: Brad Whitlock
 * Date:       Thu Jan 17 15:25:37 PST 2008
 *
 * Modifications:
 *  Brad Whitlock, Thu Feb 26 10:12:14 PST 2009
 *  I registered the data access functions using the V2 API.
 *
 *****************************************************************************/

void mainloop(void)
{
    int blocking, visitstate, err = 0;

    do
    {
        blocking = runFlag ? 0 : 1;
        /* Get input from VisIt or timeout so the simulation can run. */
        visitstate = VisItDetectInput(blocking, -1);

        /* Do different things depending on the output from VisItDetectInput. */
        if(visitstate >= -5 && visitstate <= -1)
        {
            fprintf(stderr, "Can't recover from error!\n");
            err = 1;
        }
        else if(visitstate == 0)
        {
            /* There was no input from VisIt, return control to sim. */
            simulate_one_timestep();
        }
        else if(visitstate == 1)
        {
            /* VisIt is trying to connect to sim. */
            if(VisItAttemptToCompleteConnection() == VISIT_OKAY)
            {
                fprintf(stderr, "VisIt connected\n");
                VisItSetCommandCallback(ControlCommandCallback, NULL);

                VisItSetGetMetaData(SimGetMetaData, NULL);
                VisItSetGetMesh(SimGetMesh, NULL);
                VisItSetGetMaterial(SimGetMaterial, NULL);
                VisItSetGetVariable(SimGetVariable, NULL);
                VisItSetGetMixedVariable(SimGetMixedVariable, NULL);
            }
            else
                fprintf(stderr, "VisIt did not connect\n");
        }
        else if(visitstate == 2)
        {
            /* VisIt wants to tell the engine something. */
            runFlag = 0;
            if(VisItProcessEngineCommand() == VISIT_ERROR)
            {
                /* Disconnect on an error or closed connection. */
                VisItDisconnect();
                /* Start running again if VisIt closes. */
                runFlag = 1;
            }
        }
    } while(!simulation_done() && err == 0);
}

/******************************************************************************
 *
 * Purpose: This is the main function for the program.
 *
 * Programmer: Brad Whitlock
 * Date:       Thu Jan 17 15:25:37 PST 2008
 *
 * Input Arguments:
 *   argc : The number of command line arguments.
 *   argv : The command line arguments.
 *
 * Modifications:
 *
 *****************************************************************************/

int main(int argc, char **argv)
{
    /* Initialize environment variables. */
    SimulationArguments(argc, argv);
    VisItSetupEnvironment();
    /* Write out .sim file that VisIt uses to connect. */
    VisItInitializeSocketAndDumpSimFile("material",
        "Demonstrates material data access function",
        "/path/to/where/sim/was/started",
        NULL, NULL, NULL);

    /* Read input problem setup, geometry, data. */
    read_input_deck();

    /* Call the main loop. */
    mainloop();

    return 0;
}

/* SIMULATE ONE TIME STEP */
#include <unistd.h>
void simulate_one_timestep(void)
{
    ++simcycle;
    simtime += 0.0134;
    printf("Simulating time step: cycle=%d, time=%lg\n", simcycle, simtime);
    sleep(1);
}

/* DATA ACCESS FUNCTIONS */

/* Values to match the Fortran example. */
#define NX 5
#define NY 4
#define XMIN 0.f
#define XMAX 4.f
#define YMIN 0.f
#define YMAX 3.f
const char *matNames[] = {"Water", "Membrane", "Air"};

#define DX (XMAX - XMIN)

/* Rectilinear mesh */
static float rmesh_x[NX];
static float rmesh_y[NY];
static const int   rmesh_dims[] = {NX, NY, 1};
static const int   rmesh_ndims = 2;

/******************************************************************************
 *
 * Purpose: This callback function returns simulation metadata.
 *
 * Programmer: Brad Whitlock
 * Date:       Thu Jan 17 15:40:23 PST 2008
 *
 * Modifications:
 *   Brad Whitlock, Thu Apr 10 11:59:07 PDT 2008
 *   Added a scalar variable so we can demonstrate mixed scalars.
 *
 *   Brad Whitlock, Thu Feb 26 10:21:57 PST 2009
 *   Use SimV2 API.
 *
 *****************************************************************************/

int
SimGetMetaData(VisIt_SimulationMetaData *md, void *cbdata)
{
    size_t sz;

    /* Set the simulation state. */
    md->currentMode = runFlag ? VISIT_SIMMODE_RUNNING : VISIT_SIMMODE_STOPPED;
    md->currentCycle = simcycle;
    md->currentTime = simtime;

#define NDOMAINS 1
    /* Allocate enough room for 1 mesh in the metadata. */
    md->numMeshes = 1;
    sz = sizeof(VisIt_MeshMetaData) * md->numMeshes;
    md->meshes = (VisIt_MeshMetaData *)malloc(sz);
    memset(md->meshes, 0, sz);

    /* Set the first mesh's properties.*/
    md->meshes[0].name = strdup("mesh2d");
    md->meshes[0].meshType = VISIT_MESHTYPE_RECTILINEAR;
    md->meshes[0].topologicalDimension = 2;
    md->meshes[0].spatialDimension = 2;
    md->meshes[0].numBlocks = NDOMAINS;
    md->meshes[0].blockTitle = strdup("Domains");
    md->meshes[0].blockPieceName = strdup("domain");
    md->meshes[0].numGroups = 0;
    md->meshes[0].units = strdup("cm");
    md->meshes[0].xLabel = strdup("Width");
    md->meshes[0].yLabel = strdup("Height");
    md->meshes[0].zLabel = strdup("Depth");

    /* Add a material */
    sz = sizeof(VisIt_MaterialMetaData);
    md->numMaterials = 1;
    md->materials = (VisIt_MaterialMetaData *)malloc(sz);
    md->materials[0].name = strdup("Material");
    md->materials[0].meshName = strdup("mesh2d");
    md->materials[0].numMaterials = 3;
    md->materials[0].materialNames = (char **)malloc(3*sizeof(char*));
    md->materials[0].materialNames[0] = strdup(matNames[0]);
    md->materials[0].materialNames[1] = strdup(matNames[1]);
    md->materials[0].materialNames[2] = strdup(matNames[2]);

    /* Add a scalar. */
    md->numVariables = 1;
    sz = sizeof(VisIt_VariableMetaData) * md->numVariables;
    md->variables = (VisIt_VariableMetaData *)malloc(sz);
    memset(md->variables, 0, sz);

    /* Add a zonal variable on mesh2d. */
    md->variables[0].name = strdup("scalar");
    md->variables[0].meshName = strdup("mesh2d");
    md->variables[0].type = VISIT_VARTYPE_SCALAR;
    md->variables[0].centering = VISIT_VARCENTERING_ZONE;

    /* Add some custom commands. */
    md->numGenericCommands = 3;
    sz = sizeof(VisIt_SimulationControlCommand) * md->numGenericCommands;
    md->genericCommands = (VisIt_SimulationControlCommand *)malloc(sz);
    memset(md->genericCommands, 0, sz);

    md->genericCommands[0].name = strdup("halt");
    md->genericCommands[0].argType = VISIT_CMDARG_NONE;
    md->genericCommands[0].enabled = 1;

    md->genericCommands[1].name = strdup("step");
    md->genericCommands[1].argType = VISIT_CMDARG_NONE;
    md->genericCommands[1].enabled = 1;

    md->genericCommands[2].name = strdup("run");
    md->genericCommands[2].argType = VISIT_CMDARG_NONE;
    md->genericCommands[2].enabled = 1;

    return VISIT_OKAY;
}

/******************************************************************************
 *
 * Purpose: This callback function returns meshes.
 *
 * Programmer: Brad Whitlock
 * Date:       Fri Jan 12 13:37:17 PST 2007
 *
 * Modifications:
 *   Brad Whitlock, Thu Feb 26 10:21:57 PST 2009
 *   Use SimV2 API.
 *
 *****************************************************************************/

int
SimGetMesh(int domain, const char *name, VisIt_MeshData *mesh, void *cbdata)
{
    int ret = VISIT_ERROR;

    if(strcmp(name, "mesh2d") == 0)
    {
        int i;

        /* Make VisIt_MeshData contain a VisIt_RectilinearMesh. */
        size_t sz = sizeof(VisIt_RectilinearMesh);
        mesh->rmesh = (VisIt_RectilinearMesh *)malloc(sz);
        memset(mesh->rmesh, 0, sz);

        /* Tell VisIt which mesh object to use. */
        mesh->meshType = VISIT_MESHTYPE_RECTILINEAR;

        /* Set the mesh's number of dimensions. */
        mesh->rmesh->ndims = rmesh_ndims;

        /* Set the mesh dimensions. */
        mesh->rmesh->dims[0] = rmesh_dims[0];
        mesh->rmesh->dims[1] = rmesh_dims[1];
        mesh->rmesh->dims[2] = rmesh_dims[2];

        mesh->rmesh->baseIndex[0] = 0;
        mesh->rmesh->baseIndex[1] = 0;
        mesh->rmesh->baseIndex[2] = 0;

        mesh->rmesh->minRealIndex[0] = 0;
        mesh->rmesh->minRealIndex[1] = 0;
        mesh->rmesh->minRealIndex[2] = 0;
        mesh->rmesh->maxRealIndex[0] = rmesh_dims[0]-1;
        mesh->rmesh->maxRealIndex[1] = rmesh_dims[1]-1;
        mesh->rmesh->maxRealIndex[2] = rmesh_dims[2]-1;

        /* Initialize X coords. */
        for(i = 0; i < NX; ++i)
        {
            float t = (float)i / (float)(NX-1);
            rmesh_x[i] = (1.f-t)*XMIN + t*XMAX;
        }
        /* Initialize Y coords. */
        for(i = 0; i < NY; ++i) 
        {
            float t = (float)i / (float)(NY-1);
            rmesh_y[i] = (1.f-t)*YMIN + t*YMAX;
        }

        /* Let VisIt use the simulation's copy of the mesh coordinates. */
        mesh->rmesh->xcoords = VisIt_CreateDataArrayFromFloat(
           VISIT_OWNER_SIM, rmesh_x);
        mesh->rmesh->ycoords = VisIt_CreateDataArrayFromFloat(
           VISIT_OWNER_SIM, rmesh_y);

        ret = VISIT_OKAY;
    }

    return ret;
}

/******************************************************************************
 *
 * Purpose: This callback function returns material data.
 *
 * Programmer: Brad Whitlock
 * Date:       Fri Jan 12 13:37:17 PST 2007
 *
 * Modifications:
 *   Brad Whitlock, Thu Feb 26 10:21:57 PST 2009
 *   Use SimV2 API.
 *
 *****************************************************************************/

int
SimGetMaterial(int domain, const char *name, VisIt_MaterialData *mat,
    void *cbdata)
{
    int i, j, m, cell = 0, arrlen = 0;
    int nmats, cellmat[10], matnos[3];
    float cellmatvf[10];

    /* Allocate a VisIt_MaterialData */
    VisIt_MaterialData_init(mat, (NX-1)*(NY-1), &arrlen);

    /* Fill in the VisIt_MaterialData */
    matnos[0] = VisIt_MaterialData_addMaterial(mat, matNames[0]);
    matnos[1] = VisIt_MaterialData_addMaterial(mat, matNames[1]);
    matnos[2] = VisIt_MaterialData_addMaterial(mat, matNames[2]);

    /* The matlist table indicates the material numbers that are found in
     * each cell. Every 3 numbers indicates the material numbers in a cell.
     * A material number of 0 means that the material entry is not used.
     */
    int matlist[NY-1][NX-1][3] = {
        {{3,0,0},{2,3,0},{1,2,0},{1,0,0}},
        {{3,0,0},{2,3,0},{1,2,0},{1,0,0}},
        {{3,0,0},{2,3,0},{1,2,3},{1,2,0}}
    };

    /* The mat_vf table indicates the material volume fractions that are
     * found in a cell.
     */
    float mat_vf[NY-1][NX-1][3] = {
        {{1.,0.,0.},{0.75,0.25,0.},  {0.8125,0.1875, 0.},{1.,0.,0.}},
        {{1.,0.,0.},{0.625,0.375,0.},{0.5625,0.4375,0.}, {1.,0.,0.}},
        {{1.,0.,0.},{0.3,0.7,0.},    {0.2,0.4,0.4},      {0.55,0.45,0.}}
    };

    for(j = 0; j < NY-1; ++j)
    {
        for(i = 0; i < NX-1; ++i, ++cell)
        {
            nmats = 0;
            for(m = 0; m < 3; ++m)
            {
                if(matlist[j][i][m] > 0)
                {
                    cellmat[nmats] = matnos[matlist[j][i][m] - 1];
                    cellmatvf[nmats] = mat_vf[j][i][m];
                    nmats++;
                }
            }        
            if(nmats > 1)
                VisIt_MaterialData_addMixedCell(mat, cell, cellmat, cellmatvf, nmats, &arrlen);
            else
                VisIt_MaterialData_addCleanCell(mat, cell, cellmat[0]);
        }
    }

    return VISIT_OKAY;
}

/******************************************************************************
 *
 * Purpose: This callback function returns scalars.
 *
 * Programmer: Brad Whitlock
 * Date:       Thu Apr 10 11:47:56 PDT 2008
 *
 * Modifications:
 *   Brad Whitlock, Thu Feb 26 10:21:57 PST 2009
 *   Use SimV2 API.
 *
 *****************************************************************************/

/* Make a constant field of 1. on the mesh. We'll break up the 1.0 into
 * pieces in the mixvar.
 */
#define C1 1.f
#define C2 2.f
#define C3 3.f
#define C4 4.f
float zonal_scalar[NY-1][NX-1] = {
{C1*1.f, C2*1.f, C3*1.f, C4*1.f},
{C1*1.f, C2*1.f, C3*1.f, C4*1.f},
{C1*1.f, C2*1.f, C3*1.f, C4*1.f}
};

int
SimGetVariable(int domain, const char *name, visit_handle var, void *cbdata)
{
    int ret = VISIT_ERROR;

    if(strcmp(name, "scalar") == 0)
    {
        ret = VisIt_VariableData_setDataF(var, VISIT_OWNER_SIM, 1,
            (NX-1) * (NY-1), &zonal_scalar[0][0]); 
    }

    return ret;
}


/******************************************************************************
 *
 * Purpose: This callback function returns mixed scalars.
 *
 * Programmer: Brad Whitlock
 * Date:       Fri Jan 12 13:37:17 PST 2007
 *
 * Modifications:
 *   Brad Whitlock, Thu Feb 26 10:21:57 PST 2009
 *   Use SimV2 API.
 *
 *****************************************************************************/

/* The mesh has some mixed cells. Mixed scalars are only defined for
 * those mixed cells. That means that clean cells have no entries
 * in the mixed scalar array. For this example, we're reproducing the
 * volume fractions for the mixed cells as the mixvar data. All cells in
 * mesh have a comment indicating their location, even if they add no data.
 * Cells that have data provide their data after the comment. See the
 * mat_vf array in the GetMaterial function to draw comparisons.
 */
float mixvar[] = {
/*cell 0,0*/ /*cell 0,1*/ C2*0.75,C2*0.25,  /*cell 0,2*/ C3*0.8125,C3*0.1875, /*cell 0,3*/
/*cell 1,0*/ /*cell 1,1*/ C2*0.625,C2*0.375,/*cell 1,2*/ C3*0.5625,C3*0.4375, /*cell 1,3*/
/*cell 2,0*/ /*cell 2,1*/ C2*0.3,C2*0.7,    /*cell 2,2*/ C3*0.2,C3*0.4,C3*0.4,   /*cell 2,3*/C4*0.55,C4*0.45
};

int
SimGetMixedVariable(int domain, const char *name, visit_handle mvar,
    void *cbdata)
{
    int ret = VISIT_ERROR;

    if(strcmp(name, "scalar") == 0)
    {
        int nTuples = sizeof(mixvar) / sizeof(float);
        ret = VisIt_VariableData_setDataF(mvar, VISIT_OWNER_SIM, 1,
            nTuples, mixvar);
    }

    return ret;
}

