#ifndef EXAMPLE_REF_H
#define EXAMPLE_REF_H

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot
{
    class ExampleRef : public RefCounted
    {
        GDCLASS(ExampleRef, RefCounted)

    public:
        ExampleRef();
        ~ExampleRef() override;

        int getID() const;

    protected:
        static void _bind_methods();

    private:
        static int sInstanceCount;
        static int sLastID;

        int mID;
    };
}
#endif
