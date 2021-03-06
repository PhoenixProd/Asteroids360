#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#define BULLET_LIFETIME 100
#define PTS_FROM_VESSEL 1

typedef struct Bullet {
    short lifetime;
    sf::Vector2f pos;
    sf::Vector2f vel;
    unsigned char from_player;
    struct Bullet *next;
} Bullet_t;

void append_bullet(Bullet_t **bullet_list,
    sf::Vector2f pos, sf::Vector2f vel, char from_player);
unsigned char collide_with_bullets(Bullet_t *bullets, sf::Vector2f pos, sf::Vector2f size, unsigned char vessel_id);
void update_and_display_bullets(Bullet_t **bullets,
    sf::RenderWindow &window, sf::Sprite &sprite);

#endif // _BULLET_HPP_
