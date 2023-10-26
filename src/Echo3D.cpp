#include "Echo3D.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Echo3D::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_process", "delta"), &Echo3D::_process);
}

void Echo3D::_process(double delta)
{
	UtilityFunctions::print("EchoNode3D::_proces(%d)", delta);
}

Echo3D::Echo3D()
{
}

Echo3D::~Echo3D()
{
}
