#pragma once

#include "scene_result.h"
#include <optional>

namespace TriHarder {

    class IScene {
    public:
        virtual ~IScene() = default;

        virtual SceneResult activate() = 0;
        virtual SceneResult deactivate(bool close) = 0;
        virtual SceneResult update() = 0;
        virtual SceneResult updateTick(float deltaTime) = 0;
        virtual SceneResult draw() = 0;
    };
}
