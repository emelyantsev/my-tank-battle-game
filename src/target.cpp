
#include "target.h"
#include <iostream>

#include <cmath>

#define PI 3.14159265

// Target

Target::~Target() {};

Target::State Target::GetState() const {return state_;}

SimpleTarget::SimpleTarget(sf::Vector2f position) {

    body_.setSize( {16, 16} );
    body_.setOrigin( {8, 8} );
    body_.setPosition(position);
    body_.setFillColor(sf::Color(160,80,40) );

}

void SimpleTarget::Update(float time_diff)  {}

void SimpleTarget::Blow() {

    state_ = State::DEAD;
    body_.setFillColor(sf::Color(255, 0, 0, 50));
}

void SimpleTarget::Render(sf::RenderWindow& l_window) const  {

    l_window.draw(body_);
}


sf::Vector2f SimpleTarget::GetPosition() const {

    return body_.getPosition();
}

sf::FloatRect SimpleTarget::GetBounds() const {

    return body_.getGlobalBounds();
}


// Advanced target


AdvancedTarget::AdvancedTarget(sf::Vector2f position) : body_(10.f, 3), initial_position_(position) {

    body_.setOrigin( {10, 10} );
    body_.setPosition(position);
    body_.setFillColor(sf::Color(0, 150, 0));

    total_time_ = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2 * PI;
}

void AdvancedTarget::Update(float time_diff)  {

    
    if (state_ == State::DEAD) {
        return;
    }


    float dx = 20.0 * sin(time_diff + total_time_);
    float dy = 10.0 * sin(time_diff + total_time_);

    body_.setPosition(initial_position_ + sf::Vector2f{dx, dy}) ;

    total_time_ += time_diff;

}

void AdvancedTarget::Blow() {

    state_ = State::DEAD;
    body_.setFillColor(sf::Color(255, 0, 0, 50));
}

void AdvancedTarget::Render(sf::RenderWindow& l_window) const  {

    l_window.draw(body_);
}


sf::Vector2f AdvancedTarget::GetPosition() const {

    return body_.getPosition();
}

sf::FloatRect AdvancedTarget::GetBounds() const {

    return body_.getGlobalBounds();
}




// Star target

StarTarget::StarTarget(sf::Vector2f position) : body_(), initial_position_(position) {

    body_.setOrigin( {3, 3} );
    body_.setPosition(position);
    body_.setScale(3,3);
    
}


void StarTarget::Update(float time_diff)  {

    
    if (state_ == State::DEAD) {
        return;
    }


    if (total_time_ <= 0) {

        direction_.x = 4.0 * (std::rand() % 3 - 1);
        direction_.y = 2.0 * (std::rand() % 3 - 1);

        total_time_ = 1.0;

        //std::cout << direction_.x  << " : " << direction_.y << std::endl;
    }    

    body_.move(sf::Vector2f{direction_.x * time_diff, direction_.y * time_diff} ) ;

    total_time_ -= time_diff;

}

void StarTarget::Blow() {

    state_ = State::DEAD;
    body_.setColor(sf::Color(255, 0, 0, 50));
}

void StarTarget::Render(sf::RenderWindow& l_window) const  {

    l_window.draw(body_);
}


sf::Vector2f StarTarget::GetPosition() const {

    return body_.getPosition();
}

sf::FloatRect StarTarget::GetBounds() const {

    sf::Vector2f contour = {body_.getScale().x * 6, body_.getScale().y * 6};

    return sf::FloatRect( body_.getPosition() - contour, contour) ;
}