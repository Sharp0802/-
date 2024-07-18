#pragma once

#include "property.h"

namespace tron
{
    template<typename>
    class Type
    {
        static constexpr char _ch = 0;

    public:
        static size_t GetID()
        {
            return reinterpret_cast<size_t>(&_ch);
        }
    };

    class Object
    {
        static std::atomic<uint64_t> _globalId;
        size_t _id;
        size_t _typeId;

    public:
        explicit Object(size_t typeId);

        virtual ~Object() = default;

        PROP_RO(size_t, ID);
        PROP_GETTER(ID);

        PROP_RO(size_t, TypeID);
        PROP_GETTER(TypeID);

        virtual void Awake() = 0;
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void Destroy() = 0;
    };

    class GameObject;

    class Component : public Object
    {
        GameObject* _object;

    public:
        Component(size_t typeId, GameObject* object);

        PROP_RO(GameObject*, GameObject);
        PROP_GETTER(GameObject);
    };

    class GameObject final : public Object
    {
        std::set<Component*> _components;
        bool _destroied = false;

    public:
        GameObject();

        ~GameObject() override;

        template<typename T>
        T* AddComponent()
        {
            auto p = new T(this);
            _components.emplace(p);
            return p;
        }

        template<typename T>
        void RemoveComponent(T* v)
        {
            if (!_components.contains(v))
                return;
            delete v;
            _components.erase(v);
        }

        template<typename T> requires std::is_assignable_v<Component*&, T*>
        T* GetComponent()
        {
            for (auto* component : _components)
                if (component->TypeID == Type<T>::GetID())
                    return static_cast<T*>(component);
            return nullptr;
        }

        void Awake() override;

        void Start() override;

        void Update() override;

        void Destroy() override;
    };
}
