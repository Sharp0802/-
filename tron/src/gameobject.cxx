#include "gameobject.h"

namespace tron
{
    std::atomic<uint64_t> Object::_globalId;

    Object::Object(size_t typeId): _id(_globalId++), _typeId(typeId)
    {
    }

    PROP_GETTER_DEF(Object, ID)
    {
        return _id;
    }

    PROP_GETTER_DEF(Object, TypeID)
    {
        return _typeId;
    }

    Component::Component(size_t typeId, tron::GameObject* object): Object(typeId), _object(object)
    {
    }

    PROP_GETTER_DEF(Component, GameObject)
    {
        return _object;
    }

    GameObject::GameObject(): Object(Type<GameObject>::GetID())
    {
    }

    GameObject::~GameObject()
    {
        Destroy();
        Object::~Object();
    }

    void GameObject::Awake()
    {
        for (auto* component : _components)
            component->Awake();
    }

    void GameObject::Start()
    {
        for (auto* component : _components)
            component->Start();
    }

    void GameObject::Update()
    {
        for (auto* component : _components)
            component->Update();
    }

    void GameObject::Destroy()
    {
        if (_destroied)
            return;
        _destroied = true;
        for (auto* component : _components)
            component->Destroy();
    }
}
