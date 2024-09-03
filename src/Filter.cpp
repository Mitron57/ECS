#include <Filter.h>

namespace ECS {
    template <typename C>
    std::vector<std::shared_ptr<Entity>> Filter<C>::filter() {
        const std::uint64_t typeId {Manager::getComponentID<C>()};
        std::vector<std::shared_ptr<Entity>> requirement {};
        for (const auto& [_, entity] : Manager::getAllEntities()) {
            auto& entityComponents {entity->getSignature()};
            if (entityComponents.size() > typeId &&
                entityComponents.at(typeId) != 0) {
                requirement.push_back(entity);
            }
        }
        return requirement;
    }

    template <typename C, typename... C2>
    std::vector<std::shared_ptr<Entity>> Filter<C, With<C2...>>::filter() {
        using namespace Utils;
        std::vector<std::uint8_t> filterBits {};
        std::vector<std::shared_ptr<Entity>> requirement {};
        fillMissingBits(filterBits, Manager::getComponentID<C>());
        filterBits.push_back(1);
        for (auto hash : With<C2...>::getTypeHash()) {
            auto componentId = Manager::getComponentID(hash);
            if (filterBits.size() <= componentId) {
                fillMissingBits(filterBits, componentId);
                filterBits.push_back(1);
            } else {
                filterBits[componentId] = 1;
            }
        }
        std::uint64_t typesId {bitSequenceToULL(filterBits)};
        for (const auto& [_, entity] : Manager::getAllEntities()) {
            const std::uint64_t signature {
                bitSequenceToULL(entity->getSignature())
            };
            if ((typesId & signature) == typesId) {
                requirement.push_back(entity);
            }
        }
        return requirement;
    }

    template <typename C, typename... C2>
    std::vector<std::shared_ptr<Entity>> Filter<C, Without<C2...>>::filter() {
        using namespace Utils;
        std::vector<std::shared_ptr<Entity>> requirement {};
        std::vector<std::uint8_t> filterBits {};
        fillMissingBits(filterBits, Manager::getComponentID<C>());
        filterBits.push_back(1);
        const std::uint64_t typeId {bitSequenceToULL(filterBits)};
        for (const auto& [_, entity] : Manager::getAllEntities()) {
            const std::uint64_t signature {
                bitSequenceToULL(entity->getSignature())
            };
            if ((typeId & signature) == signature) {
                requirement.push_back(entity);
            }
        }
        return requirement;
    }
}  // namespace ECS
