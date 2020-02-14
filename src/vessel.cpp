#include <SFML/Graphics.hpp>
#include <bullet.hpp>
#include <vessel.hpp>
#include <math.h>

void Vessel::init(void)
{
    alive = 1;
    shield = 100;
    shoot_delay = 0;
    score = 0;
    vel.x = 0;
    vel.y = 0;
    // Define vessel position and angle
    angle = 0;
    pos.x = 0;
    pos.y = 0;
    text.setString("  0");
}

Vessel::Vessel(char id, char max, sf::Font *font, void **vessel_array) : alive(0), shielding(0), shooting(0), accelerating(0), rotation(0)
{
    char str0[] = "textures/spaceships/spaceship00.bmp";
    char str1[] = "textures/teams/spaceship00.bmp";

    myid = id;
    str0[30] = str1[25] = '0' + (++id % 10);
    str0[29] = str1[24] = '0' + (id / 10);
    textures[0].loadFromFile(str0);
    textures[1].loadFromFile(str1);
    sprites[0].setTexture(textures[0]);
    sprites[1].setTexture(textures[1]);
    sprites[0].setOrigin(SIZE/2, SIZE/2);
    sprites[1].setOrigin(SIZE/2, SIZE/2);
    text.setFont(*font);
    text.setOrigin(SIZE/2, -SIZE/2);
    text.setCharacterSize(SCORE_SIZE);
    pos.x = 0;
    pos.y = 0;
    vel.x = 0;
    vel.y = 0;
    size.x = SIZE;
    size.y = SIZE;
    varr = (Vessel **) vessel_array;
}

void Vessel::Update(sf::RenderWindow &window, Bullet_t **bullet_list, unsigned char team_mode)
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
        append_bullet(bullet_list, pos + axis * SHOOT_DISTANCE, vel + axis * SHOOT_VEL, myid);
    }
    // Collision
    unsigned char bcoll = collide_with_bullets(*bullet_list, pos, size, myid);
    if (bcoll != 255) {
        printf("Collision\n");
        alive = 0;
        varr[bcoll]->addScore(PTS_FROM_VESSEL);
        return;
    }
    // Display
    sprites[team_mode].setPosition(pos);
    sprites[team_mode].setRotation(angle);
    text.setPosition(pos);
    text.setRotation(angle);
    window.draw(text);
    window.draw(sprites[team_mode]);
}

void Vessel::collideWithVessel(Vessel *vessel)
{
    if (vessel->pos.x - SIZE < pos.x && vessel->pos.x + SIZE > pos.x
     && vessel->pos.y - SIZE < pos.y && vessel->pos.y + SIZE > pos.y
     && (vessel->pos.x - pos.x) * (vessel->pos.x - pos.x) + (vessel->pos.y - pos.y) * (vessel->pos.y - pos.y) < SIZE * SIZE) {
        if (!vessel->shielding) vessel->alive = 0;
        if (!shielding) alive = 0;
    }
}

void Vessel::collideWithOthers(void)
{
    unsigned short i = myid;

    if (!alive) return;  // No collision for death vessel
    while (i-- > 0) { // Begin with the next vessel
        if (varr[i]->alive)
            varr[i]->collideWithVessel(this);
    }
}

void Vessel::addScore(int points)
{
    char actual[] = "   \0";

    score += points;
    actual[2] = '0' + score % 10;
    if (score >= 10)
        actual[1] = '0' + (score / 10) % 10;
    if (score >= 100)
        actual[0] = '0' + (score / 100) % 10;
    text.setString(actual);
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
    switch (button) {
    }
}

void Vessel::ReleaseEvent(unsigned int button)
{
    switch (button) {
    }
}
