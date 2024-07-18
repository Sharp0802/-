#pragma once

#define PROP_GETTER_NAME(name) _##name##__getter_
#define PROP_SETTER_NAME(name) _##name##__getter_

#define PROP_RW(t, name) __declspec(property(get=PROP_GETTER_NAME(name), put=PROP_SETTER_NAME(name))) t name;
#define PROP_RO(t, name) __declspec(property(get=PROP_GETTER_NAME(name))) t name;

#define PROP_GETTER(name) decltype(name) PROP_GETTER_NAME(name)()
#define PROP_SETTER(name) void PROP_SETTER_NAME(name)(decltype(name) value)

#define PROP_GETTER_DEF(cls, name) decltype(cls::name) cls::PROP_GETTER_NAME(name)()
#define PROP_SETTER_DEF(cls, name) decltype(cls::name) cls::PROP_SETTER_NAME(name)(decltype(cls::name) value)

#define PROP_AUTO_FIELD(name) _##name##__field_
#define PROP_AUTO(vis, t, name) \
    vis: \
        PROP_RW(t, name) \
    private: \
        decltype(name) PROP_AUTO_FIELD(name); \
    vis: \
        PROP_GETTER(name) const { return PROP_AUTO_FIELD(name); } \
        PROP_SETTER(name) { PROP_AUTO_FIELD(name) = value; }
