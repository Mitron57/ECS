#ifndef ECS_WORLD_H
#define ECS_WORLD_H

namespace ECS {
    struct Manager {
        static std::shared_ptr<Entity> createEntity();

        static void deleteEntity(std::shared_ptr<Entity> entity);

        template <typename... C>
        static void addComponent(const std::shared_ptr<Entity>& entity);

        template <typename S>
        static void addSystem();

        template <typename C>
        static bool hasComponent(const std::shared_ptr<Entity>& entity);

        static void run();

        template <typename C>
        static std::size_t getComponentID();
        static std::size_t getComponentID(std::size_t hash);
        template <typename... T>
        static std::tuple<std::shared_ptr<T>...> getComponents(const std::shared_ptr<Entity>& entity);

        static const std::map<std::size_t, std::shared_ptr<Entity>>& getAllEntities();

    private:
        static std::map<std::size_t, std::shared_ptr<Entity>> entities;
        static std::vector<std::unique_ptr<System>> systems;
        static std::map<std::size_t, std::size_t> componentsID;
        static std::size_t componentID;
    };
}  // namespace ECS
#endif  // ECS_WORLD_H
