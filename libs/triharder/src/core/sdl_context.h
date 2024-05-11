#pragma once

namespace TriHarder {

    class SdlContext {
    public:
        static SdlContext& getInstance();

        bool initialize();
        void destroy();
        [[nodiscard]] bool isInitialized() const;

    private:
        bool initialized_ = false;
    };

}
