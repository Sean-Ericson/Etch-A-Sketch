/*
 * File:   main.cpp
 * Author: anonymous
 *
 * Created on March 10, 2014, 6:52 AM
 */

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

const int INIT_WIN_X = 900;
const int INIT_WIN_Y = 900;

void handleResize(sf::RenderWindow &window, sf::Event event, sf::View view);

int main( void )
{
    sf::RenderWindow window(sf::VideoMode(INIT_WIN_X, INIT_WIN_Y, 32), "Test", sf::Style::Titlebar|sf::Style::Close);
    sf::Event event;
    sf::View view;
    
    view.setCenter( sf::Vector2f( INIT_WIN_X / 2, INIT_WIN_Y / 2 ) );
    view.setSize( sf::Vector2f(INIT_WIN_X, INIT_WIN_Y) );
    
    window.setKeyRepeatEnabled(false);
    window.setView(view);
    
    sf::CircleShape shape(150, 6);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(0.f, 0.f);
    
    window.clear(sf::Color::Green);
    window.display();
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::Resized)
            {
                handleResize(window, event, view);
            }
            
            if (event.type == sf::Event::KeyPressed)
            {
                //handleKeyPress();
            }
            
            while (window.pollEvent(event)){}
        }
        
        window.clear(sf::Color::Green);
        window.display();
    
    }
    
    return 0;
}

void handleResize(sf::RenderWindow &window, sf::Event event, sf::View view)
{
    bool limitWindowSize = true;
    int minWindowSize = 71, smallSide;
    
    if ( (limitWindowSize) && (event.size.height < minWindowSize) )
    {
        event.size.height = minWindowSize;
        window.setSize( sf::Vector2u(event.size.width, event.size.height) );
    }
    
    view.setSize(event.size.width, event.size.height);
    
    if (event.size.width <= event.size.height)
    {
        view.zoom(1.0 * INIT_WIN_X / event.size.width);
    }
    else
    {
        view.zoom(1.0 * INIT_WIN_Y / event.size.height);
    }

    window.setView(view);
}

void drawHexs(sf::RenderWindow &window, unsigned int num, float r, sf::Vector2f center)
{
    if (num == 0)
        return;
    
    sf::Clock timingClock;
    sf::Time deltaTime = sf::milliseconds(1000);
    
    float apothem = r * cos(M_PI / 6);
    float side = 2 * r * sin(M_PI / 6);
    
    sf::CircleShape hex(r, 6);
    hex.setFillColor(sf::Color::Red);
    
    for (int i = 0; i < ceil(num/6); ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            if ((i * j) > num)
                break;
            
            timingClock.restart();
            
            hex.setPosition(center.x + ((i+2) * 2 * apothem * cos(j * (M_PI / 6))), center.y + ((i+1) * 2 * apothem * sin(j * (M_PI / 6))));
            window.draw(hex);
            window.display();
            
            while (timingClock.getElapsedTime() < deltaTime){}
        }
    }
    window.display();
}