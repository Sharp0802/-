#include "transform.h"

namespace tron::obj
{
    Transform::Transform(size_t type, tron::GameObject* object)
        : Component(type, object),
          PROP_AUTO_FIELD(Position)(0),
          PROP_AUTO_FIELD(Scale)(1),
          PROP_AUTO_FIELD(Rotation)()
    {
    }

    Transform::Transform(class GameObject* object)
        : Transform(Type<Transform>::GetID(), object)
    {
    }

    Transform::operator glm::mat4() const
    {
        const glm::mat4 t = translate(glm::mat4(1.0), Position);
        const glm::mat4 r = mat4_cast(Rotation);
        const glm::mat4 s = scale(glm::mat4(1.0), Scale);

        return t * r * s;
    }

    void Transform::Awake()
    {
    }

    void Transform::Start()
    {
    }

    void Transform::Update()
    {
    }

    void Transform::Destroy()
    {
    }
}
