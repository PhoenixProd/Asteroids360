#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <bullet.hpp>
#include <vessel.hpp>
#include <stdlib.h>

#define FRAMERATE 60
#define FRAME_DELAY 1/FRAMERATE

class Core {
public:
    Core(sf::VideoMode mode, unsigned char nb_vessels);
    ~Core();
    void Update(void);
    void Events(void);
protected:
    sf::RenderWindow window;
    sf::VideoMode mode;
    sf::Font font;
    Vessel **vessel_array;  // Fixed-size array
    char vlen;              // vessel number
    Bullet_t *bullet_list;  // Dynamic list
    char gamemode;          // bool array : Team
    unsigned char selecting;
    sf::Texture bullet_texture;
    sf::Sprite bullet_sprite;
};

#endif //_CORE_HPP_
