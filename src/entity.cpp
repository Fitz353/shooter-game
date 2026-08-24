#include <SDL3/SDL.h>
#include "headers/entity.h"

// Constructor of entity
Entity::Entity(float startx, float starty, float w, float h)
    : x(startx), y(starty), w(w), h(h)
{
}
