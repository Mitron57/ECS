#include <Manager.h>

namespace ECS {
    std::map<std::size_t, std::shared_ptr<Entity>> Manager::entities;
    std::vector<std::unique_ptr<System>> Manager::systems;
    std::map<std::size_t, std::size_t> Manager::componentsID;
    std::size_t Manager::componentID;

    std::shared_ptr<Entity> Manager::createEntity() {
        static std::size_t entityID {};
        entities.emplace(entityID, std::make_shared<Entity>(entityID));
        return entities.at(entityID++);
    }

    void Manager::deleteEntity(std::shared_ptr<Entity> entity) {
        if (entity) {
            entities.erase(entity->getID());
        }
    }
    template <typename... C>
    void Manager::addComponent(const std::shared_ptr<Entity>& entity) {
        if (entity) {
            (
                [&entity] {
                    std::uint64_t hash {typeid(C).hash_code()};
                    if (!componentsID.contains(hash)) {
                        componentsID[hash] = componentID++;
                    }
                    entity->setComponent<C>(componentsID[hash]);
                }(),
                ...
            );
        }
    }

    template <typename S>
    void Manager::addSystem() {
        systems.push_back(std::make_unique<S>());
    }

    void Manager::run() {
        for (const auto& system : systems) {
            system->onAwake();
        }
        while (true) {
            for (const auto& system : systems) {
                if (!system->onUpdate()) {
                    return;
                }
            }
        }
    }

    template <typename C>
    std::size_t Manager::getComponentID() {
        return componentsID[typeid(C).hash_code()];
    }

    std::size_t Manager::getComponentID(std::size_t hash) {
        return componentsID[hash];
    }

    template <typename... T>
    std::tuple<std::shared_ptr<T>...> Manager::getComponents(
        const std::shared_ptr<Entity>& entity
    ) {
        if (entity) {
            const auto& components {entity->getComponents()};
            auto getComponent = [&components] <typename C> (C) -> std::shared_ptr<C> {
                if (components.contains(Manager::getComponentID<C>())) {
                    return std::reinterpret_pointer_cast<C>(
                        components.at(Manager::getComponentID<C>())
                    );
                }
                return nullptr;
            };
            return {getComponent(T{})...};
        }
        return {};
    }

    const std::map<std::size_t, std::shared_ptr<Entity>>&
    Manager::getAllEntities() {
        return entities;
    }

    template <typename C>
    bool Manager::hasComponent(const std::shared_ptr<Entity>& entity) {
        if (entity) {
            std::uint64_t id = Manager::getComponentID<C>();
            const std::vector<std::uint8_t>& signature = entity->getSignature();
            return id < signature.size() && signature[id] == 1;
        }
        return false;
    }
}  // namespace ECS
