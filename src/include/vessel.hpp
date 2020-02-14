#ifndef _VESSEL_HPP_
#define _VESSEL_HPP_

#define ROTATION_SPEED 6
// If 60 fps
#define COOLDOWN 100
#define THRUST 0.1f
#define SHOOT_VEL 4.f
#define SHOOT_DISTANCE 16.f
#define DEG2RAD 3.1415926 / 180
#define SIZE 32
#define SCORE_SIZE 12
// Number of times you have to multiply this

class Vessel {
public:
    Vessel(char id, char max, sf::Font *font, void **vessel_array);
    void init(void);
    void Update(sf::RenderWindow &window, Bullet_t **bullet_list, unsigned char team_mode);
    void PressEvent(unsigned int button);
    void ReleaseEvent(unsigned int button);
    void setAccelerating(bool b);
    void setRotationLeft(bool b);
    void setRotationRight(bool b);
    void setShielding(bool b);
    void setShooting(bool b);
    void addScore(int points);
    void collideWithVessel(Vessel *vessel);
    void collideWithOthers(void);
    char alive;             // Is vessel alive
protected:
    char myid;              // Vessel id
    sf::Texture textures[2];// Texture
    sf::Sprite sprites[2];  // Sprite
    sf::Text text;          // Individual score display

    sf::Vector2f pos;   // Vessel position
    sf::Vector2f vel;   // Velocity
    sf::Vector2f size;  // Vessel size
    float angle;        // Vessel angle in degree

    char shielding;     // Is using shield
    char shooting;      // Is shooting
    char accelerating;  // Is accelerating

    short shoot_delay;  // Time to wait before shooting again
    int shield;         // Shield time
    float rotation;     // Vessel rotation
    int score;          // Score

    Vessel **varr;
};

#endif // _VESSEL_HPP_
