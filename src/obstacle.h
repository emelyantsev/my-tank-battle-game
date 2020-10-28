#pragma once

#include <SFML/Graphics.hpp>

class Obstacle {

    public:

        enum class Quality {
            PENETRABLE,
            UNPENETRABLE, 
        };

        virtual sf::Vector2f GetPosition() const = 0;
        virtual sf::FloatRect GetBounds() const = 0;
        virtual Quality GetQuality() const = 0;
        virtual void Render(sf::RenderWindow& l_window) const = 0;

        virtual ~Obstacle() = default;

};



class WaterObstacle : public Obstacle {

    public:

        WaterObstacle(sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color(50, 50, 200)) ;

        virtual sf::Vector2f GetPosition() const override;
        virtual sf::FloatRect GetBounds() const override;
        virtual Quality GetQuality() const override;
        virtual void Render(sf::RenderWindow& l_window) const override;

    private:

        sf::RectangleShape body_;
        Quality quality_ = Quality::PENETRABLE;
};


class SolidObstacle : public Obstacle {

    public:

        SolidObstacle(sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color(150, 150, 150)) ;

        virtual sf::Vector2f GetPosition() const override;
        virtual sf::FloatRect GetBounds() const override;
        virtual Quality GetQuality() const override;
        virtual void Render(sf::RenderWindow& l_window) const override;

    private:

        sf::RectangleShape body_;
        Quality quality_ = Quality::UNPENETRABLE;
};
