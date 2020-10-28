

#pragma once

#include <SFML/Graphics.hpp>

class Star : public sf::Drawable, public sf::Transformable {
    
    public:

        Star() ;

        void setColor(sf::Color color = sf::Color(75, 0, 130) ) ;
        
    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::VertexArray m_vertices;
};