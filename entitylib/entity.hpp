#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.h>
#include <SFML/System.h>

class Vessel {
public:
    float rotation;     // Vessel rotation
    char shielded;      // Use shield
    char alive;
protected:
    sfVector2f pos;
    sfVector2f vel;
    Sprite *sprite;     // Vessel sprite
    int shield;         // Shield power
    float angle;        // Angle in degree
    int score;          // Score
    Texture *texture;   // Vessel texture
    Text *text;         // Individual score display
};

#endif //_ENTITY_H_
