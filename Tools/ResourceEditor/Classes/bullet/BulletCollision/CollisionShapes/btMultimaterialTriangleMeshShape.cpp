/*==================================================================================
    Copyright (c) 2008, binaryzebra
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    * Neither the name of the binaryzebra nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE binaryzebra AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL binaryzebra BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
=====================================================================================*/


/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2009 Erwin Coumans  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/// This file was created by Alex Silverman

#include "BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.h"
#include "BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.h"
//#include "BulletCollision/CollisionShapes/btOptimizedBvh.h"


///Obtains the material for a specific triangle
const btMaterial * btMultimaterialTriangleMeshShape::getMaterialProperties(int partID, int triIndex)
{
    const unsigned char * materialBase = 0;
    int numMaterials;
    PHY_ScalarType materialType;
    int materialStride;
    const unsigned char * triangleMaterialBase = 0;
    int numTriangles;
    int triangleMaterialStride;
    PHY_ScalarType triangleType;

    ((btTriangleIndexVertexMaterialArray*)m_meshInterface)->getLockedReadOnlyMaterialBase(&materialBase, numMaterials, materialType, materialStride,
        &triangleMaterialBase, numTriangles, triangleMaterialStride, triangleType, partID);

    // return the pointer to the place with the friction for the triangle
    // TODO: This depends on whether it's a moving mesh or not
    // BUG IN GIMPACT
    //return (btScalar*)(&materialBase[triangleMaterialBase[(triIndex-1) * triangleMaterialStride] * materialStride]);
    int * matInd = (int *)(&(triangleMaterialBase[(triIndex * triangleMaterialStride)]));
    btMaterial *matVal = (btMaterial *)(&(materialBase[*matInd * materialStride]));
    return (matVal);
}
