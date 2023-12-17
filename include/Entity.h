#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

namespace ECS {
    struct Entity {
        explicit Entity(std::size_t id) : id(id) {}

        [[nodiscard]] const std::vector<std::uint8_t>& getSignature() const;

        template <typename C>
        void setComponent(std::size_t componentID);

        [[nodiscard]] const std::map<std::size_t, std::shared_ptr<Component>>& getComponents() const;
        [[nodiscard]] std::size_t getID() const;

    private:
        void setSignature(std::size_t componentID);
        std::size_t id {};
        std::vector<std::uint8_t> signature {};
        std::map<std::size_t, std::shared_ptr<Component>> components {};
    };
}  // namespace ECS

#endif  // ECS_ENTITY_H