#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

namespace ECS {
    struct Component {
        Component() = default;
        Component(const Component& component) = default;
        Component(Component&& component) = default;

        virtual ~Component() = default;
    };
}

#endif  // ECS_COMPONENT_H
