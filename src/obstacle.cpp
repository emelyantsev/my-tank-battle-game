#include "obstacle.h"

WaterObstacle::WaterObstacle(sf::Vector2f position, sf::Vector2f size, sf::Color color) {

    body_.setPosition(position);
    body_.setFillColor(color);
    body_.setSize(size);
   // body_.setOutlineThickness(2);
   // body_.setOutlineColor(sf::Color::Black);
}

sf::Vector2f WaterObstacle::GetPosition() const { return body_.getPosition() ;  } ;
sf::FloatRect WaterObstacle::GetBounds() const { return body_.getGlobalBounds() ; };
Obstacle::Quality WaterObstacle::GetQuality() const { return quality_ ; };

void WaterObstacle::Render(sf::RenderWindow& l_window) const { l_window.draw(body_); };


SolidObstacle::SolidObstacle(sf::Vector2f position, sf::Vector2f size, sf::Color color) {

    body_.setPosition(position);
    body_.setFillColor(color);
    body_.setSize(size);
  //  body_.setOutlineThickness(5);
   // body_.setOutlineColor(sf::Color::Black);
}

sf::Vector2f SolidObstacle::GetPosition() const { return body_.getPosition() ;  } ;
sf::FloatRect SolidObstacle::GetBounds() const { return body_.getGlobalBounds() ; };
Obstacle::Quality SolidObstacle::GetQuality() const { return quality_ ; };

void SolidObstacle::Render(sf::RenderWindow& l_window) const { l_window.draw(body_); };