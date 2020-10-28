#include "star.h"


Star::Star() {

    const int vertices[] = {
        0, 0,
        0, 3,
        1, 1,
        3, 0,
        1, -1,
        0, -3,
        -1, -1,
        -3, 0,
        -1, 1,
        0, 3,
    };

    m_vertices.setPrimitiveType(sf::TriangleFan);

    for (int i = 0; i < 10; ++i) {

        sf::Vertex v;
        
        v.position = sf::Vector2f(vertices[2*i], vertices[2*i+1]) ;
        //v.color = sf::Color::Yellow;
        v.color = sf::Color(150, 50, 200);
        
        m_vertices.append(v);
    }
}


void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    states.transform *= getTransform();         
    target.draw(m_vertices, states);
}



void Star::setColor(sf::Color color) {

    for (int i = 0 ; i < m_vertices.getVertexCount(); ++i) {
        m_vertices[i].color = color;
    }
}