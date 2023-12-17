#include <godot_cpp/classes/godot_physics_server2d.hpp>
#include <godot_cpp/variant//utility_functions.hpp>

#include "ExampleRef.h"

using namespace godot;

int ExampleRef::sInstanceCount = 0;
int ExampleRef::sLastID = 0;

ExampleRef::ExampleRef()
{
    mID = ++sLastID;
    sInstanceCount++;

    UtilityFunctions::print(
        "ExampleRef ", itos(mID),
        " created, current instance count: ", itos(sInstanceCount));
}

ExampleRef::~ExampleRef()
{
    sInstanceCount--;
    UtilityFunctions::print(
        "ExampleRef ", itos(mID),
        " destroyed, current instance count: ", itos(sInstanceCount));
}

int ExampleRef::getID() const
{
    return mID;
}

void ExampleRef::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_id"), &ExampleRef::getID);
}
