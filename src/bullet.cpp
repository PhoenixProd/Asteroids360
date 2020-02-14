#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bullet.hpp>
#include <stdlib.h>

void append_bullet(Bullet_t **bullet_list,
    sf::Vector2f pos, sf::Vector2f vel, char from_player)
{
    Bullet_t *bullet = (Bullet_t *) malloc(sizeof(Bullet_t));

    bullet->lifetime = BULLET_LIFETIME;
    bullet->pos = pos;
    bullet->vel = vel;
    bullet->from_player = from_player;
    bullet->next = *bullet_list;
    *bullet_list = bullet;
}

char collide_with_bullets(Bullet_t *bullets, sf::Vector2f pos, sf::Vector2f size)
{
    char nbr_collisions = 0;

    size += pos; // size became pos2
    while (bullets != NULL) {
        if (pos.x < bullets->pos.x && size.x > bullets->pos.x
         && pos.y < bullets->pos.y && size.y > bullets->pos.y) {
            // Collision detected
            nbr_collisions++;
            bullets->lifetime = 0;
        }
        bullets = bullets->next;
    }
    return (nbr_collisions);
}

void update_and_display_bullets(Bullet_t **bullets,
    sf::RenderWindow &window, sf::Sprite &sprite)
{
    Bullet_t *bullet = *bullets;

    while (bullet != NULL) {
        if (--bullet->lifetime < 0) {
            // Destroy this bullet
            *bullets = bullet->next;
            free(bullet);
            bullet = *bullets;
            continue;
        }
        bullet->pos += bullet->vel;
        sprite.setPosition(bullet->pos);
        window.draw(sprite);
        bullets = &bullet->next;
        bullet = *bullets;
    }
}
