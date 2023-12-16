#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/viewport.hpp"
#include "godot_cpp/core/binder_common.hpp"

#include "ExampleRef.h"

namespace godot
{
    class Example : public Control
    {
        GDCLASS(Example, Control)

    public:
        // Constants.
        enum Constants
        {
            FIRST,
            ANSWER_TO_EVERYTHING = 42,
        };

        enum
        {
            CONSTANT_WITHOUT_ENUM = 314,
        };

        enum Flags
        {
            FLAG_ONE = 1,
            FLAG_TWO = 2,
        };

        Example();
        ~Example();

        // Functions.
        void echo(String msg);
        void simple_func();
        void simple_const_func() const;
        String return_something(const String& inBase);
        Viewport* return_something_const() const;
        Ref<ExampleRef> return_empty_ref() const;
        ExampleRef* return_extended_ref() const;
        Ref<ExampleRef> extended_ref_checks(Ref<ExampleRef> inRef) const;
        Variant varargs_func(const Variant** inArgs, GDExtensionInt inArgCount,
                            GDExtensionCallError& outError);
        int varargs_func_non_void_return(const Variant** inArgs, GDExtensionInt inArgCount,
                                     GDExtensionCallError& outError);
        void varargs_func_void_return(const Variant** inArgs, GDExtensionInt inArgCount,
                                   GDExtensionCallError& outError);

        void emit_custom_signal(const String& inName, int inValue);
        int def_args(int inA = 100, int inB = 200) const;

        Array test_array() const;
        void test_typed_array_arg(const TypedArray<int64_t>& inArray);
        TypedArray<Vector2> test_tarray() const;
        Dictionary test_dictionary() const;
        Example* test_node_argument(Example* inNode) const;
        String test_string_ops() const;
        int test_vector_ops() const;

        BitField<Flags> test_bitfield(BitField<Flags> inFlags);

        // Property.
        void set_custom_position(const Vector2& inPos);
        Vector2 get_custom_position() const;
        Vector4 get_v4() const;

        // Static method.
        static int test_static(int inA, int inB);
        static void test_static2();

        // Virtual function override (no need to bind manually).
        virtual bool _has_point(const Vector2& inPoint) const override;

    protected:
        static void _bind_methods();

        void _notification( int inWhat );
        bool _set( const StringName &inName, const Variant &inValue );
        bool _get( const StringName &inName, Variant &outReturn ) const;
        void _get_property_list( List<PropertyInfo> *outList ) const;
        bool _property_can_revert( const StringName &inName ) const;
        bool _property_get_revert( const StringName &inName, Variant &outProperty ) const;

        String _to_string() const;

    private:
        Vector2 mCustomPosition;
        Vector3 mPropertyFromList;
        Vector2 mDProp[3];
    };
} // namespace godot

// Required for to avoid 'VARIANT_TYPE': undeclared identifier
VARIANT_ENUM_CAST(Example::Constants);
VARIANT_BITFIELD_CAST(Example::Flags);

#endif
