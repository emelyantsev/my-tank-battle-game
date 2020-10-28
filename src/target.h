
#include <SFML/Graphics.hpp>

#include "star.h"

class Target {

    public:

        enum class State {
            ALIVE,
            DEAD
        };


        //Target(sf::Vector2f position);
      
        virtual void Update(float time_diff) = 0;
        virtual void Render(sf::RenderWindow& l_window) const = 0;
        virtual void Blow() = 0;

        virtual sf::Vector2f GetPosition() const = 0;
        virtual sf::FloatRect GetBounds() const = 0;

        virtual State GetState() const;

        virtual ~Target() = 0;
    
    protected:

        Target::State state_ = Target::State::ALIVE;


};


class SimpleTarget : public Target {

    public:

        SimpleTarget(sf::Vector2f position);

        virtual void Update(float time_diff) override ;
        virtual void Render(sf::RenderWindow& l_window) const override ;
        virtual void Blow() override ;

        virtual sf::Vector2f GetPosition() const override ;
        virtual sf::FloatRect GetBounds() const override ;

    private:

        sf::RectangleShape body_;
        

};


class AdvancedTarget : public Target {

    public:

        AdvancedTarget(sf::Vector2f position);

        virtual void Update(float time_diff) override ;
        virtual void Render(sf::RenderWindow& l_window) const override ;
        virtual void Blow() override ;

        virtual sf::Vector2f GetPosition() const override ;
        virtual sf::FloatRect GetBounds() const override ;

    private:

        sf::CircleShape body_;
      //  Target::State state_ = Target::State::ALIVE;

        float total_time_;
        sf::Vector2f initial_position_ ;

};


class StarTarget : public Target {

    public:

        StarTarget(sf::Vector2f position);

        virtual void Update(float time_diff) override ;
        virtual void Render(sf::RenderWindow& l_window) const override ;
        virtual void Blow() override ;

        virtual sf::Vector2f GetPosition() const override ;
        virtual sf::FloatRect GetBounds() const override ;

    private:

        Star body_;
   //     Target::State state_ = Target::State::ALIVE;

        float total_time_ = 0.;
        sf::Vector2f initial_position_ ;

        sf::Vector2f direction_;

};