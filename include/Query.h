#ifndef ECS_QUERY_H
#define ECS_QUERY_H

namespace ECS {
    template <typename... C>
    struct Query {
        [[nodiscard]] static std::vector<std::size_t> getTypeHash() {
            return {typeid(C).hash_code()...};
        }
    };

    template <typename... C>
    struct With : Query<C...> {};

    template <typename... C>
    struct Without : Query<C...> {};
}  // namespace ECS

#endif  // ECS_QUERY_H
