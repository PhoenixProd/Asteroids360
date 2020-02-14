#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <core.hpp>

Core::Core(sf::VideoMode mode, unsigned char nb_vessels)
{
    int i = 0;

    sf::RenderWindow window(mode, "Asteroids 360");
    window.setFramerateLimit(FRAMERATE);
    font.loadFromFile("textures/font.what");

    vlen = nb_vessels;
    vessel_array = (Vessel **) malloc(sizeof(vessel_array) * vlen);
    while (i < nb_vessels) {
        vessel_array[i] = new Vessel(i, nb_vessels, &font); // Initialize vessels
        i++;
    }
    bullet_list = NULL; // Initialize bullet list
}

Core::~Core()
{
    int i = 0;
    Bullet_t *b = bullet_list;
    Bullet_t *tmp;

    while (i < vlen)
        delete vessel_array[i++];
    free(vessel_array);
    while (b != NULL) {
        tmp = b->next;
        free(b);
        b = tmp;
    }
}

void Core::Update(void)
{
    int i = 0;

    while (i < vlen) {
        vessel_array[i++]->Update(window, &bullet_list, gamemode & 1);
    }
    update_and_display_bullets(&bullet_list, window, bullet_sprite);
    window.display();
}

void Core::Events(void)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            printf("Closing Request : Error : Permission denied.\n");
        } else if (event.type == sf::Event::JoystickButtonPressed) {
            printf("Press Event : Joystick %u, Button %u\n", event.joystickButton.joystickId, event.joystickButton.button);
            vessel_array[event.joystickButton.joystickId]->PressEvent(event.joystickButton.button);
        } else if (event.type == sf::Event::JoystickButtonReleased) {
            printf("Release Event : Joystick %u, Button %u\n", event.joystickButton.joystickId, event.joystickButton.button);
            vessel_array[event.joystickButton.joystickId]->ReleaseEvent(event.joystickButton.button);
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::A:
                    if (selecting-- == 0)
                        selecting = vlen - 1;
                    break;
                case sf::Keyboard::E:
                    if (++selecting == vlen)
                        selecting = 0;
                    break;
                case sf::Keyboard::Z:
                    vessel_array[selecting]->setAccelerating(1);
                    break;
                case sf::Keyboard::D:
                    vessel_array[selecting]->setRotationLeft(1);
                    break;
                case sf::Keyboard::Q:
                    vessel_array[selecting]->setRotationRight(1);
                    break;
                case sf::Keyboard::Space:
                    vessel_array[selecting]->setShooting(1);
                    break;
                case sf::Keyboard::RShift:
                    vessel_array[selecting]->setAccelerating(1);
                    break;
            }
        } else if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
                case sf::Keyboard::Z:
                    vessel_array[selecting]->setAccelerating(0);
                    break;
                case sf::Keyboard::D:
                    vessel_array[selecting]->setRotationLeft(0);
                    break;
                case sf::Keyboard::Q:
                    vessel_array[selecting]->setRotationRight(0);
                    break;
                case sf::Keyboard::Space:
                    vessel_array[selecting]->setShooting(0);
                    break;
                case sf::Keyboard::RShift:
                    vessel_array[selecting]->setAccelerating(0);
                    break;
            }
        }
    }
}