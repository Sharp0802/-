#pragma once

namespace tron
{
    enum BufferType
    {
        BT_Array        = 0x8892,
        BT_ElementArray = 0x8893
    };

    enum BufferPolicy
    {
        BP_Dynamic = 0x88E8,
        BP_Static  = 0x88E4,
        BP_Stream  = 0x88E0,

        BP_Draw = 0,
        BP_Read = 1,
        BP_Copy = 2
    };

    class Buffer
    {
        BufferType _type;
        BufferPolicy _policy;
        std::shared_ptr<GLuint> _buffer;

    public:
        Buffer(BufferType type, BufferPolicy policy);

        void BufferData(const void* data, size_t size);

        void Use() const;
    };
}
