#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

namespace ECS {
    struct System {
        System() = default;
        virtual ~System() = default;

        virtual void onAwake() = 0;
        virtual bool onUpdate() = 0;
    };
}

#endif  // ECS_SYSTEM_H
