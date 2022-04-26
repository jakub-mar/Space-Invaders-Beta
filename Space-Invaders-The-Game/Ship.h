#ifndef SHIP_H
#define SHIP_H

#include "Enemy.h"
#include "Bullet.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>

class Ship : public sf::Sprite{
private:
    sf::Texture ship_txt;
    sf::SoundBuffer shot_b;
    sf::Sound shoot_s;
    sf::SoundBuffer damaged_b;
    sf::Sound damaged_s;
    int xspeed=350;
    bool gameover=false;
    bool win=false;

public:
    bool shooted = false;
    sf::Texture boom1;

    int lives =4;
    bool GameOver(){
        return gameover;
    }
    void WinTheGame(std::vector<std::unique_ptr<Ufo>> &ufos){
        if(ufos.size()==0){
            win=true;
        }
    }
    bool Win(){
        return win;
    }
    void Move(sf::Time &elapsed){
        setTextureRect(sf::IntRect(125,0,125,200));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            setTextureRect(sf::IntRect(0,0,125,200));
            move(-xspeed*elapsed.asSeconds(),0);
            if(getGlobalBounds().left<=0){
                move(xspeed*elapsed.asSeconds(),0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            setTextureRect(sf::IntRect(250,0,125,200));
            move(xspeed*elapsed.asSeconds(),0);
            if(getGlobalBounds().left+getGlobalBounds().width>=1024){
                move(-xspeed*elapsed.asSeconds(),0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            setTextureRect(sf::IntRect(125,0,125,200));
        }
    }
    void Shot(std::vector<std::unique_ptr<Bullet>> &bullets,sf::Time &elapsed, sf::Clock &clock){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if(clock.getElapsedTime().asSeconds()>=0.5){
                shoot_s.play();
                bullets.emplace_back(std::make_unique<Bullet>(getPosition().x-85,getPosition().y-50));
                clock.restart();
                iscore-=3;
            }
        }
        for(auto &a : bullets){
            a->move(0,-700*elapsed.asSeconds());
        }
        for(unsigned int i=0;i<bullets.size() ;i++){
            if(bullets[i]->getGlobalBounds().top+bullets[i]->getGlobalBounds().height<=-5){
                bullets.erase(bullets.begin()+i);
            }


        }

    }
    Ship(sf::RenderWindow &window){
        ship_txt.loadFromFile("Textures/statki.png");
        setTextureRect(sf::IntRect(125,0,125,200));
        ship_txt.setSmooth(true);
        setTexture(ship_txt);
        setScale(0.7,0.7);
        setOrigin(ship_txt.getSize().x/2,ship_txt.getSize().y/2);
        setPosition(window.getSize().x/2+85,700);
        boom1.loadFromFile("Textures/explosion.png");
        shot_b.loadFromFile("Sounds/shoot.wav");
        shoot_s.setBuffer(shot_b);
        shoot_s.setVolume(20);
        damaged_b.loadFromFile("Sounds/explosion.wav");
        damaged_s.setBuffer(damaged_b);
        damaged_s.setVolume(20);
    }
    virtual ~Ship()=default;
    void Shooted(std::vector<std::unique_ptr<Laser>> &lasers){
        for(unsigned int i=0;i<lasers.size();i++){
            if(lasers[i]->getGlobalBounds().intersects(getGlobalBounds())){
                damaged_s.play();
                lives--;
                lasers.erase(lasers.begin()+i);
                shooted=true;
                iscore-=50;
            }

        }
        if(lives==0){
            gameover=true;
        }

    }
    void SetDefaulttxt(){
        setTexture(ship_txt);
    }
    void Collision(std::vector<std::unique_ptr<Ufo>> &ufos){
        for(auto &a : ufos){
        if(getGlobalBounds().intersects(a->getGlobalBounds())){
            lives=0;
        }
        }
    }
};

#endif // SHIP_H
