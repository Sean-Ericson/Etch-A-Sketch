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
#include <cstdlib>
#include <iostream>
#include <vector>

const int INIT_WIN_X = 500;
const int INIT_WIN_Y = 500;
const int DELTA_T = 0;

void handleResize(sf::RenderWindow &window, sf::Event event, sf::View view);
int randInt(int min, int max);
void initialize(void);
void update(void);
void drawStuff(void);
void drawRect(int num, sf::Color color);
void setVectorSize(int x, int y);
void colorPixel(int x, int y, sf::Color color);

sf::RenderWindow window(sf::VideoMode(INIT_WIN_X, INIT_WIN_Y, 32), "Test");
sf::Event event;
sf::View view;

std::vector< std::vector<sf::Color> > pixel;
std::vector<sf::Vector2i> points;

int main( void )
{   
    setVectorSize(INIT_WIN_X, INIT_WIN_Y);
    
    bool drawing = false;
    sf::Time deltaTime = sf::microseconds(DELTA_T);
    sf::Clock clock;
    sf::RectangleShape rect(sf::Vector2f(1.f, 1.f));
    
    initialize();
    
    rect.setFillColor(pixel[250][250]);
    rect.setPosition(250.f, 250.f);
    
    srand( time(NULL) );
    
    view.setCenter( sf::Vector2f( INIT_WIN_X / 2, INIT_WIN_Y / 2 ) );
    view.setSize( sf::Vector2f(INIT_WIN_X, INIT_WIN_Y) );
    
    //window.setKeyRepeatEnabled(false);
    window.setView(view);
    
    window.clear(sf::Color::White);
    
    drawStuff();
    
    while (window.isOpen())
    {
        clock.restart();
        
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
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                std::cout << "Pressed!" << std::endl;
                drawing = !drawing; 
            }
            while (window.pollEvent(event)){}
        }
        
        if (drawing)
            {
            //std::cout << "drawing" << std::endl;
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                if ( (points.size() == 0) || (pos != points.back()) )
                {
                    points.push_back(pos);
                }
            }
        
        update();
        drawStuff();
        
        while (clock.getElapsedTime() < deltaTime) {}
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

int randInt( int min, int max )
{
    if( min > max ){
        
        return (min + 1);
    }
    
    return (int)( ( ( rand() / (RAND_MAX * 1.0) ) * (1 + max - min) ) + min );
}

void initialize(void)
{
    for (register int i = 0; i < INIT_WIN_X; ++i)
        for (register int j = 0; j < INIT_WIN_Y; ++j)
            pixel[i][j] = sf::Color::White;
}

void update(void)
{
    if (points.size() < 1)
        return;
    
    for (int i = 0; i < (points.size() - 1); ++i)
    {
        int xInit = points[i].x, yInit = points[i].y;
        int xFinal = points[i+1].x, yFinal = points[i+1].y;
        int deltaX = xFinal - xInit, deltaY = yFinal - yInit;
        float slope = deltaY / deltaX;
        
        std::cout << "Point " << i << ": (" << points[i].x << ", " << points[i].y << ")" << std::endl;
        
        if (deltaX == 0)
            if (deltaY > 0)
                for (int j = 0; j < deltaY; ++j)
                    colorPixel(xInit, yInit + j, sf::Color::Black);
            
            else if (deltaY < 0)
                for (int j = 0; j > deltaY; --j)
                    colorPixel(xInit, yInit + j, sf::Color::Black);
            
            else if (deltaX > 0)
                for (int j = 0; j < deltaX; ++j)
                    colorPixel(xInit + j, (int)floor(yInit + (j*slope) ), sf::Color::Black );
            
            else if (deltaX < 0)
                for (int j = 0; j > deltaX; --j)
                    colorPixel(xInit + j, (int)floor(yInit + (j*slope) ), sf::Color::Black );
        
    }
}

void drawStuff(void)
{
    sf::RectangleShape rect(sf::Vector2f(1.f, 1.f));
    
    for (int i = 0; i < INIT_WIN_X; ++i)
    {
        for (int j = 0; j < INIT_WIN_Y; ++j)
        {
            rect.setPosition(i, j);
            rect.setFillColor(pixel[i][j]);
            window.draw(rect);
        }
    }
    window.display();
}

void drawRect(int num, sf::Color color)
{
    
}

void setVectorSize(int x, int y)
{
    pixel.resize(x);
    
    for (register int i = 0; i < x; ++i)
        pixel[i].resize(y);
}

void colorPixel(int x, int y, sf::Color color)
{
    if ( (x < pixel.size()) && (x >= 0) && (y < pixel[x].size()) && (y >= 0))
        pixel[x][y] = color;
}
