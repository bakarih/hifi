//
//  RenderableBoxEntityItem.cpp
//  libraries/entities-renderer/src/
//
//  Created by Brad Hefta-Gaub on 8/6/14.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include <glm/gtx/quaternion.hpp>

#include <gpu/GPUConfig.h>

#include <DeferredLightingEffect.h>
#include <PerfStat.h>

#include "RenderableBoxEntityItem.h"

EntityItem* RenderableBoxEntityItem::factory(const EntityItemID& entityID, const EntityItemProperties& properties) {
    return new RenderableBoxEntityItem(entityID, properties);
}

void RenderableBoxEntityItem::render(RenderArgs* args) {
    PerformanceTimer perfTimer("RenderableBoxEntityItem::render");
    assert(getType() == EntityTypes::Box);
    glm::vec3 position = getPosition();
    glm::vec3 center = getCenter();
    glm::vec3 dimensions = getDimensions();
    glm::quat rotation = getRotation();

    const float MAX_COLOR = 255.0f;

    glm::vec4 cubeColor(getColor()[RED_INDEX] / MAX_COLOR, getColor()[GREEN_INDEX] / MAX_COLOR,
                    getColor()[BLUE_INDEX] / MAX_COLOR, getLocalRenderAlpha());


    bool debugSimulationOwnership = args->_debugFlags & RenderArgs::RENDER_DEBUG_SIMULATION_OWNERSHIP;
    bool highlightSimulationOwnership = false;
    if (debugSimulationOwnership) {
        auto nodeList = DependencyManager::get<NodeList>();
        const QUuid& myNodeID = nodeList->getSessionUUID();
        highlightSimulationOwnership = (getSimulatorID() == myNodeID);
    }

    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glm::vec3 axis = glm::axis(rotation);
        glRotatef(glm::degrees(glm::angle(rotation)), axis.x, axis.y, axis.z);
        glPushMatrix();
            glm::vec3 positionToCenter = center - position;
            glTranslatef(positionToCenter.x, positionToCenter.y, positionToCenter.z);
            glScalef(dimensions.x, dimensions.y, dimensions.z);
            if (highlightSimulationOwnership) {
                DependencyManager::get<DeferredLightingEffect>()->renderWireCube(1.0f, cubeColor);
            } else {
                DependencyManager::get<DeferredLightingEffect>()->renderSolidCube(1.0f, cubeColor);
            }
        glPopMatrix();
    glPopMatrix();

    RenderableDebugableEntityItem::render(this, args);
};
