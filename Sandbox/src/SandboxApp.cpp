#include <Wukong.h>
#include <Wukong/Core/EntryPoint.h>

#include "Sandbox3D.h"
#include "Sandbox2D.h"


Wukong::Application* Wukong::CreateApplication()
{
	return new Sandbox2D();
	//return new Sandbox3D();
}