#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "../triharder.h"

namespace TriHarder {

    template<typename T>
    class ResourceAllocator {
    public:
        ResourceAllocator() : current_id_(0) {}

        int add(const String& file_path) {
            auto it = resources_.find(file_path);
            if (it != resources_.end()) {
                return it->second.first;
            }

            SharedPtr<T> resource = std::make_shared<T>();
            if (!resource->loadFromFile(file_path)) {
                return -1;
            }

            resources_.insert(std::make_pair(file_path, std::make_pair(current_id_, resource)));
            return current_id_++;
        }

        void remove(int id) {
            for (auto it = resources_.begin(); it != resources_.end(); ++it) {
                if (it->second.first == id) {
                    resources_.erase(it->first);
                }
            }
        }

        SharedPtr<T> get(int id) const {
            for (auto it = resources_.begin(); it != resources_.end(); it++) {
                if (it->second.first == id) {
                    return it->second.second;
                }
            }
            return nullptr;
        }

        bool has(int id) const {
            return get(id) != nullptr;
        }

    private:
        int current_id_;
        std::unordered_map<String, std::pair<int, SharedPtr<T>>> resources_;
    };
}
