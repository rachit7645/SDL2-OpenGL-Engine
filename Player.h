#ifndef PLAYER_H
#define PLAYER_H

#include "GLM.h"
#include "Entity.h"
#include "Util.h"
#include "Model.h"
#include "Transform.h"

namespace Entities
{
    class Player : public Entity
    {
    public:
        // Default constructor
        Player();
        // Main constructor
        Player(MdPtr model, const Transform& transform);
        // Player update functions
        void Move();
    private:
        // Current running speed
        f32 m_runSpeed  = 0.0f;
        // Current turning speed
        f32 m_turnSpeed = 0.0f;
        // Check inputs
        void CheckInputs();
        // Display ImGUI widgets
        void ImGuiDisplay();
    };
}

#endif