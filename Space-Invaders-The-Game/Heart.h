#ifndef MENU_H
#define MENU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>


class Heart : public sf::Sprite{
private:
    sf::Texture heart_txt;

public:
    Heart(int x, int y){
        heart_txt.loadFromFile("Textures/heart.png");
        setTexture(heart_txt);
        setScale(0.05,0.05);
        setPosition(x,y);

    }
    ~Heart()=default;
};

#endif // MENU_H
