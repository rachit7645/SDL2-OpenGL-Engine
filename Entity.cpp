#include "Entity.h"

// Using namespaces
using namespace Entities;

// Usings
using Renderer::Model;

Entity::Entity(MdPtr sharedModel, const Transform& transform)
    : model(std::move(sharedModel)),
      transform(transform)
{
}