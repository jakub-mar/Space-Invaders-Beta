#ifndef OTHER_H
#define OTHER_H

#include "Bullet.h"
#include "Heart.h"
#include "Ship.h"
#include "Shield.h"
#include <fstream>

int movec=0;

void uMove(std::vector<std::unique_ptr<Ufo>> &ufos, sf::Time &elapsed){
    for (auto &a : ufos){
        a->move(a->dir*elapsed.asSeconds(),0);

        if(a->getGlobalBounds().left+a->getGlobalBounds().width>=994 or a->getGlobalBounds().left<=30){
            for(auto &b : ufos){
                b->ChangeVel();
                b->move(0,25);


            }
        }
    }
}
void LastUfos(std::vector<std::unique_ptr<Ufo>> &ufos, sf::Clock &c1){
    if(ufos.size()<=10){
        if(c1.getElapsedTime().asSeconds()>=3){
            for (auto &a : ufos){
                a->Accelerate();
            }
            c1.restart();
        }
    }
}

std::string getScore(){
    std::fstream hscore;
    hscore.open("score.txt");
    std::string temps;
    hscore>>temps;
    hscore.close();
    return temps;
}

void writeScore(int &score){
    int temp=std::stoi(getScore());
    std::ofstream wscore;
    wscore.open("score.txt", std::ios::in | std::ios::out);
    if(score>temp){
        wscore<<score;
    }
    wscore.close();
}

sf::Sprite CreateBackground(sf::RenderWindow &window){
    sf::Texture background;
    background.loadFromFile("Textures/star-back.jpg");
    sf::Sprite background_s;
    background_s.setTexture(background);
    background_s.setScale(1.3,1.3);
    background_s.setOrigin(background.getSize().x/2,background.getSize().y/2);
    background_s.setPosition(window.getSize().x/2,window.getSize().y/2);

    return background_s;
}

std::vector<std::unique_ptr<Heart>> CreateHearts(Ship &ship){
    std::vector<std::unique_ptr<Heart>> hearts;
    for(int i=0; i<ship.lives;i++){
        hearts.emplace_back(std::make_unique<Heart>(34*i+30,720));
    }
    return hearts;
}

void CreateMusic(){
    sf::Music music;
    music.openFromFile("Sounds/prodigy.wav");
    music.setLoop(true);
    music.setVolume(10);
    music.play();

}


#endif // OTHER_H
