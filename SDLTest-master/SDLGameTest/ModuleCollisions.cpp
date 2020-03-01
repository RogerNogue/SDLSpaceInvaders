#include "ModuleCollisions.h"

ModuleCollisions::ModuleCollisions() :Module()
{

}

ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::Init()
{
	return true;
}

update_status ModuleCollisions::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleCollisions::CleanUp() 
{
	return true;
}