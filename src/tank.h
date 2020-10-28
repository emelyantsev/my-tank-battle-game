#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>

class Game;

class Shell;

class Tank {

    public:

        enum class State {
            ALIVE,
            DEAD
        };

        // Tank(sf::Vector2f position = sf::Vector2f{100, 200}, 
        //     sf::Color color = sf::Color(150, 40, 40), 
        //     sf::Color color1 = sf::Color(200, 20, 30), 
        //     sf::Color color2 = sf::Color(200, 20, 30),
        //     Game * p_game = nullptr) ;

        Tank() = default;

        Tank(sf::Vector2f position, 
            sf::Color color, 
            sf::Color color1, 
            sf::Color color2,
            Game * p_game) ;
        
        void Render(sf::RenderWindow& l_window);
        void Update(float time_diff);
        
        void Move(int) ;
        void Stop() ;
        void Rotate(float angle) ;

        Shell Fire() ;

        sf::Vector2f GetPosition() const ;
        float GetRotation() const ;
        sf::FloatRect GetBounds() const;

        void UpdatePoints(int points = 1) ;

        int GetPoints() const ;

        int GetElapsedTimeForShooting() const ;


    protected:

        sf::RectangleShape corpus_;
        sf::RectangleShape gun_;
        sf::CircleShape tower_;

        int speed_ = 0;
        float angle_ = 0;

        State state_ = State::ALIVE;

        int points_ = 0;

        sf::SoundBuffer buffer0_;
        sf::SoundBuffer buffer1_;

        sf::Sound sound_shot_;
        sf::Sound sound_blow_;

        Game * p_game_;

        sf::Clock shooting_timer_;
};



class Shell {

    public:

        Shell(sf::Vector2f position, sf::Vector2f speed);
        void Update(float time_diff);
        void Render(sf::RenderWindow& l_window) const;

        sf::Vector2f GetPosition() const ;

    private:

        sf::CircleShape body_;
        sf::Vector2f v_speed_ ;
};


