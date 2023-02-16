#include <Wukong.h>
#include <Wukong/Core/EntryPoint.h>

#include "Sandbox3D.h"


Wukong::Application* Wukong::CreateApplication()
{
	return new Sandbox3D();
}