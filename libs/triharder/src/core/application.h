#pragma once

#include "window.h"

namespace TriHarder {

    class Application {
    public:
        void run();

    private:
        UniquePtr<Window> window_;
    };

}
