#pragma once
#include  "tank.h"
#include <SFML/Graphics.hpp>

class Game;


class AItank : public Tank {


    public:

        AItank() = default;

        AItank(sf::Vector2f position, sf::Color color, sf::Color color1, sf::Color color2, Game * p_game);

        void Update(float time_diff);

        void Fire() ;

    private:


        static float calc_angle(sf::Vector2f v1, sf::Vector2f v2);

        sf::Clock clock_;
};