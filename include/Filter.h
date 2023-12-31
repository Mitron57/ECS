#ifndef ECS_FILTER_H
#define ECS_FILTER_H

namespace ECS {
    template <typename...>
    struct Filter;

    template <typename C>
    struct Filter<C> {
        Filter() = delete;
        static std::vector<std::shared_ptr<Entity>> filter();
    };

    template <typename C, typename... C2>
    struct Filter<C, With<C2...>> {
        Filter() = delete;
        static std::vector<std::shared_ptr<Entity>> filter();
    };

    template <typename C, typename... C2>
    struct Filter<C, Without<C2...>> {
        Filter() = delete;
        static std::vector<std::shared_ptr<Entity>> filter();
    };
} // namespace ECS

#endif  // ECS_FILTER_H
