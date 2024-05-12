#pragma once

#include "scene_result.h"

namespace TriHarder {

    class IScene {
    public:
        SceneResult activate();
        SceneResult deactivate(bool close);
        SceneResult update();
        SceneResult updateTick(float deltaTime);
        SceneResult draw();
    };
}
