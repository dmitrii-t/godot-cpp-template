#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/godot.hpp>

#include "Example.h"

// Used to mark unused parameters to indicate intent and suppress warnings.
#define UNUSED( expr ) (void)( expr )

using namespace godot;

constexpr int MAGIC_NUMBER = 42;

enum EnumWithoutClass
{
    OUTSIDE_OF_CLASS = 512
};

VARIANT_ENUM_CAST(EnumWithoutClass);

void Example::_bind_methods()
{
    // No need to bind godot pre-defined methods

    // Methods
    ClassDB::bind_method(D_METHOD("echo", "msg"), &Example::echo);


    ClassDB::bind_method(D_METHOD("simple_func"), &Example::simple_func);
    ClassDB::bind_method(D_METHOD("simple_const_func"),
                         &Example::simple_const_func);
    ClassDB::bind_method(D_METHOD("return_something"), &Example::return_something);

    ClassDB::bind_method(D_METHOD("return_something_const"),
                         &Example::return_something_const);
    
    ClassDB::bind_method(D_METHOD("return_empty_ref"), &Example::return_empty_ref);
    ClassDB::bind_method(D_METHOD("return_extended_ref"),
                         &Example::return_extended_ref);
    ClassDB::bind_method(D_METHOD("extended_ref_checks", "ref"),
                         &Example::extended_ref_checks);

    ClassDB::bind_method(D_METHOD("test_array"), &Example::test_array);
    ClassDB::bind_method(D_METHOD("test_tarray_arg", "array"),
                         &Example::test_typed_array_arg);
    ClassDB::bind_method(D_METHOD("test_tarray"), &Example::test_tarray);
    ClassDB::bind_method(D_METHOD("test_dictionary"), &Example::test_dictionary);
    ClassDB::bind_method(D_METHOD("test_node_argument"),
                         &Example::test_node_argument);
    ClassDB::bind_method(D_METHOD("test_string_ops"), &Example::test_string_ops);
    ClassDB::bind_method(D_METHOD("test_vector_ops"), &Example::test_vector_ops);

    ClassDB::bind_method(D_METHOD("test_bitfield", "flags"),
                        &Example::test_bitfield);

    ClassDB::bind_method(D_METHOD("def_args", "a", "b"), &Example::def_args,
                         DEFVAL(100), DEFVAL(200));

    ClassDB::bind_static_method("Example", D_METHOD("test_static", "a", "b"),
                                &Example::test_static);
    ClassDB::bind_static_method("Example", D_METHOD("test_static2"),
                                &Example::test_static2);

    {
        MethodInfo mi;
        mi.arguments.emplace_back(Variant::STRING, "some_argument");
        mi.name = "varargs_func";

        ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "varargs_func",
                                    &Example::varargs_func, mi);
    }

    {
        MethodInfo mi;
        mi.arguments.emplace_back(Variant::STRING, "some_argument");
        mi.name = "varargs_func_nv";

        ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "varargs_func_nv",
                                    &Example::varargs_func_non_void_return, mi);
    }

    {
        MethodInfo mi;
        mi.arguments.emplace_back(Variant::STRING, "some_argument");
        mi.name = "varargs_func_void";

        ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "varargs_func_void",
                                    &Example::varargs_func_void_return, mi);
    }

    // Properties.
    ADD_GROUP("Test group", "group_");
    ADD_SUBGROUP("Test subgroup", "group_subgroup_");

    ClassDB::bind_method(D_METHOD("get_custom_position"),
                         &Example::get_custom_position);
    ClassDB::bind_method(D_METHOD("get_v4"), &Example::get_v4);
    ClassDB::bind_method(D_METHOD("set_custom_position", "position"),
                         &Example::set_custom_position);
    ADD_PROPERTY(PropertyInfo( godot::Variant::VECTOR2, "group_subgroup_custom_position" ),
                 "set_custom_position", "get_custom_position");

    // Signals.
    ADD_SIGNAL(godot::MethodInfo( "custom_signal",
        godot::PropertyInfo( godot::Variant::STRING, "name" ),
        godot::PropertyInfo( godot::Variant::INT, "value" ) ));
    ClassDB::bind_method(D_METHOD("emit_custom_signal", "name", "value"),
                         &Example::emit_custom_signal);

    // Add a signal to invoke GDScript
    ADD_SIGNAL(MethodInfo("echo_signal", PropertyInfo(Variant::STRING, "msg")));

    // Constants.
    BIND_ENUM_CONSTANT(FIRST)
    BIND_ENUM_CONSTANT(ANSWER_TO_EVERYTHING)

    BIND_BITFIELD_FLAG(FLAG_ONE);
    BIND_BITFIELD_FLAG(FLAG_TWO);

    BIND_CONSTANT(CONSTANT_WITHOUT_ENUM);
    BIND_ENUM_CONSTANT(OUTSIDE_OF_CLASS);
}

Example::Example()
{
    UtilityFunctions::print("Constructor.");
}

Example::~Example()
{
    UtilityFunctions::print("Destructor.");
}

void Example::echo(String msg)
{
    UtilityFunctions::print("Example::echo: ", msg);
}

// Methods.
void Example::simple_func()
{
    UtilityFunctions::print("  Simple func called.");
}

void Example::simple_const_func() const
{
    UtilityFunctions::print("  Simple const func called.");
}

String Example::return_something(const String& inBase)
{
    UtilityFunctions::print("  Return something called.");

    return inBase;
}

Viewport* Example::return_something_const() const
{
    UtilityFunctions::print("  Return something const called.");

    if (is_inside_tree())
    {
        Viewport* result = get_viewport();

        return result;
    }

    return nullptr;
}

Ref<ExampleRef> Example::return_empty_ref() const
{
    Ref<ExampleRef> ref;
    return ref;
}

ExampleRef* Example::return_extended_ref() const
{
    // You can instance and return a refcounted object like this, but keep in mind that refcounting
    // starts with the returned object and it will be destroyed when all references are destroyed.
    // If you store this pointer you run the risk of having a pointer to a destroyed object.
    return memnew(ExampleRef());
}

Ref<ExampleRef> Example::extended_ref_checks(Ref<ExampleRef> inRef) const
{
    // This is the preferred way of instancing and returning a refcounted object:
    Ref<ExampleRef> ref;
    ref.instantiate();

    UtilityFunctions::print(
        "  Example ref checks called with value: ", inRef->get_instance_id(),
        ", returning value: ", ref->get_instance_id());

    return ref;
}

Variant Example::varargs_func(const Variant** inArgs, GDExtensionInt inArgCount,
                              GDExtensionCallError& outError)
{
    UNUSED(inArgs);
    UNUSED(outError);

    UtilityFunctions::print("  Varargs (Variant return) called with ",
                            String::num_int64(inArgCount), " arguments");

    return inArgCount;
}

int Example::varargs_func_non_void_return(const Variant** inArgs, GDExtensionInt inArgCount,
                                          GDExtensionCallError& outError)
{
    UNUSED(inArgs);
    UNUSED(outError);

    UtilityFunctions::print("  Varargs (int return) called with ",
                            String::num_int64(inArgCount), " arguments");

    return MAGIC_NUMBER;
}

void Example::varargs_func_void_return(const Variant** inArgs, GDExtensionInt inArgCount,
                                       GDExtensionCallError& outError)
{
    UNUSED(inArgs);
    UNUSED(outError);

    UtilityFunctions::print("  Varargs (no return) called with ",
                            String::num_int64(inArgCount), " arguments");
}

void Example::emit_custom_signal(const String& inName, int inValue)
{
    emit_signal("custom_signal", inName, inValue);
}

int Example::def_args(int inA, int inB) const
{
    return inA + inB;
}

Array Example::test_array() const
{
    Array arr;

    arr.resize(2);
    arr[0] = Variant(1);
    arr[1] = Variant(2);

    return arr;
}

void Example::test_typed_array_arg(const TypedArray<int64_t>& inArray)
{
    for (int i = 0; i < inArray.size(); ++i)
    {
        UtilityFunctions::print(inArray[i]);
    }
}

TypedArray<Vector2> Example::test_tarray() const
{
    TypedArray<Vector2> arr;

    arr.resize(2);
    arr[0] = Vector2(1, 2);
    arr[1] = Vector2(2, 3);

    return arr;
}

Dictionary Example::test_dictionary() const
{
    Dictionary dict;

    dict["hello"] = "world";
    dict["foo"] = "bar";

    return dict;
}

Example* Example::test_node_argument(Example* inNode) const
{
    // This should use godot::String::num_uint64(), but it is currently broken:
    //  https://github.com/godotengine/godot-cpp/issues/1014
    UtilityFunctions::print(
        "  Test node argument called with ",
        (inNode != nullptr)
            ? String::num_int64(static_cast<int64_t>(inNode->get_instance_id()))
            : "null");
    return inNode;
}

String Example::test_string_ops() const
{
    String s = String("A");
    s += "B";
    s += "C";
    s += char32_t(0x010E);
    s = s + "E";

    return s;
}

int Example::test_vector_ops() const
{
    PackedInt32Array arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.push_back(45);

    int ret = 0;
    for (const int32_t& E : arr)
    {
        ret += E;
    }

    return ret;
}

BitField<Example::Flags> Example::test_bitfield(BitField<Flags> inFlags)
{
    UtilityFunctions::print("  Got BitField: ", String::num_int64(inFlags));
    return inFlags;
}

// Properties.
void Example::set_custom_position(const Vector2& inPos)
{
    mCustomPosition = inPos;
}

Vector2 Example::get_custom_position() const
{
    return mCustomPosition;
}

Vector4 Example::get_v4() const
{
    return {1.2f, 3.4f, 5.6f, 7.8f};
}

// Static methods
int Example::test_static(int inA, int inB)
{
    return inA + inB;
}

void Example::test_static2()
{
    UtilityFunctions::print("  void static");
}

// Virtual function override.
bool Example::_has_point(const Vector2& inPoint) const
{
    auto* label = Control::get_node<Label>("Label");

    label->set_text("Got point: " + Variant(inPoint).stringify());

    return false;
}

void Example::_notification( int inWhat )
{
    UtilityFunctions::print( "Notification: ", String::num( inWhat ) );
}

bool Example::_set( const StringName &inName, const Variant &inValue )
{
    String name = inName;

    if ( name.begins_with( "dproperty" ) )
    {
        int64_t index = name.get_slicec( '_', 1 ).to_int();
        mDProp[index] = inValue;

        return true;
    }

    if ( name == "property_from_list" )
    {
        mPropertyFromList = inValue;

        return true;
    }

    return false;
}

bool Example::_get( const StringName &inName, Variant &outReturn ) const
{
    String name = inName;

    if ( name.begins_with( "dproperty" ) )
    {
        int64_t index = name.get_slicec( '_', 1 ).to_int();
        outReturn = mDProp[index];

        return true;
    }

    if ( name == "property_from_list" )
    {
        outReturn = mPropertyFromList;

        return true;
    }

    return false;
}

void Example::_get_property_list( List<PropertyInfo> *outList ) const
{
    outList->push_back( PropertyInfo( Variant::VECTOR3, "property_from_list" ) );

    for ( int i = 0; i < 3; ++i )
    {
        outList->push_back(
            PropertyInfo( Variant::VECTOR2, "dproperty_" + itos( i ) ) );
    }
}

bool Example::_property_can_revert( const StringName &inName ) const
{
    if ( inName == StringName( "property_from_list" ) &&
         mPropertyFromList != Vector3( MAGIC_NUMBER, MAGIC_NUMBER, MAGIC_NUMBER ) )
    {
        return true;
    }

    return false;
};

bool Example::_property_get_revert( const StringName &inName,
                                    Variant &outProperty ) const
{
    if ( inName == StringName( "property_from_list" ) )
    {
        outProperty = Vector3( MAGIC_NUMBER, MAGIC_NUMBER, MAGIC_NUMBER );

        return true;
    }

    return false;
};

String Example::_to_string() const
{
    return "[ GDExtension::Example <--> Instance ID:" + uitos( get_instance_id() ) + " ]";
}