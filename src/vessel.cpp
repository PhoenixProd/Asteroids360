#include <SFML/Graphics.hpp>
#include <bullet.hpp>
#include <vessel.hpp>
#include <math.h>

void Vessel::init(void)
{
    alive = 1;
    shield = 100;
    angle = 0;
    shoot_delay = 0;
}

Vessel::Vessel(char id, char max, sf::Font *font) : rotation(0), score(0), shielding(0), shooting(0), accelerating(0)
{
    // textures, sprites, text, pos, vel, angle
    char str0[] = "texture/spaceships/spaceship00.bmp";
    char str1[] = "texture/teams/spaceship00.bmp";

    myid = id;
    str0[29] = str1[24] = '0' + (++id % 10);
    str0[28] = str1[23] = '0' + (id / 10);
    textures[0].loadFromFile(str0);
    textures[1].loadFromFile(str1);
    sprites[0].setTexture(textures[0]);
    sprites[1].setTexture(textures[1]);
    text.setFont(*font);
    pos.x = 0;
    pos.y = 0;
    vel.x = 0;
    vel.y = 0;
    text.setOrigin(0, -32);
}

void Vessel::Update(sf::RenderWindow &window, Bullet_t **bullet_list, char team_mode)
{
    if (!alive) return; // Don't update anything if not alive
    // Transtation
    if (accelerating) {
        vel.x += THRUST * cos(angle * DEG2RAD);
        vel.y += THRUST * sin(angle * DEG2RAD);
    }
    pos += vel;
    // Rotation
    angle += rotation;
    // Shooting
    if (shoot_delay > 0) {
        shoot_delay--;
    } else if (shooting) {
        sf::Vector2f axis(cos(angle * DEG2RAD), sin(angle * DEG2RAD));
        shoot_delay = COOLDOWN;
        append_bullet(bullet_list, pos + size / 2.f + axis * SHOOT_DISTANCE, vel + axis * SHOOT_VEL, myid);
    }
    // Collision
    // Display
    sprites[team_mode].setPosition(pos);
    sprites[team_mode].setRotation(angle);
    window.draw(sprites[team_mode]);
}

void Vessel::setAccelerating(bool b)
{
    accelerating = b;
}

void Vessel::setRotationRight(bool b)
{
    if (b) {
        rotation = -ROTATION_SPEED;
    } else if (rotation == -ROTATION_SPEED) {
        rotation = 0;
    }
}

void Vessel::setRotationLeft(bool b)
{
    if (b) {
        rotation = ROTATION_SPEED;
    } else if (rotation == ROTATION_SPEED) {
        rotation = 0;
    }
}

void Vessel::setShielding(bool b)
{
    shielding = b;
}

void Vessel::setShooting(bool b)
{
    shooting = b;
}

void Vessel::PressEvent(unsigned int button)
{

}

void Vessel::ReleaseEvent(unsigned int button)
{

}