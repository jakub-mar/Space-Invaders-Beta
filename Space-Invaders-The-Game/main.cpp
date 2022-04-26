#include "Bullet.h"
#include "Heart.h"
#include "Ship.h"
#include "Shield.h"
#include <string>
#include "Other.h"

// W obenym wydaniu gra działa, lecz używa "zakazanego owocu" w postaci instrukcji goto, za co z góry przepraszam, 
// ale z powodu licznych problemów i małej ilości czasu przez nie spowodowanymi, zarówno w kodzie jak i w życiu, main wygląda jak wygląda i wydaje mi się, 
// że było to konieczne rozwiązanie by zapobiec ciągłemu uruchamianiu pliku .exe. 
// Za restart miała docelowo odpowiadać funkcja tworząca wektory wskaźników i ustawiająca parametry obiektów na defaultowe, zależna od boola.
// Jeżeli miałby Pan zastrzeżenia co do tego rozwiązania, mógłbym spróbować je zmienić.
//

bool returnb=false;
int main() {
    sf::RenderWindow window(sf::VideoMode(1024,768), "        SPACE INVADERS      ");
    begin: ;

    int counter=0;
    bool openframe=true;

    // add background
    CreateBackground(window);

    Ship ship(window);
    std::vector<std::unique_ptr<Heart>> hearts = CreateHearts(ship);

    sf::Music music;
    music.openFromFile("Sounds/prodigy.wav");
    music.setLoop(true);
    music.setVolume(10);
    music.play();

    std::vector<std::unique_ptr<Bullet>> bullets;

    std::vector<std::unique_ptr<Laser>> lasers;

    std::vector<std::unique_ptr<Ufo>> ufos;

    std::vector<std::unique_ptr<Shield>> shields;
    shields.emplace_back(std::make_unique<Shield>(109.6,580));
    shields.emplace_back(std::make_unique<Shield>(289.2,580));
    shields.emplace_back(std::make_unique<Shield>(468.8,580));
    shields.emplace_back(std::make_unique<Shield>(648.4,580));
    shields.emplace_back(std::make_unique<Shield>(828,580));


    sf::Font lives_f;
    lives_f.loadFromFile("slkscreb.ttf");
    sf::Text score[2];
    score[0].setFont(lives_f);
    score[1].setFont(lives_f);
    score[0].setString("Score:");

    score[0].setPosition(20,20);
    score[1].setPosition(score[0].getPosition().x+130,score[0].getPosition().y);
    score[0].setScale(0.8 ,0.8); score[1].setScale(0.8,0.8);

    sf::Text first;
    first.setFont(lives_f);
    first.setString("PRESS ENTER TO START!");
    first.setScale(1.2,1.2);
    first.setOrigin(floor(first.getLocalBounds().width /2) , floor(first.getLocalBounds().height /2 ));
    first.setPosition(window.getSize().x/2,window.getSize().y/2);
    sf::Text second;
    second.setFont(lives_f);
    second.setFillColor(sf::Color::Yellow);
    second.setCharacterSize(60);
    second.setString("space invaders");
    second.setOrigin(floor(first.getGlobalBounds().width/2) , floor(first.getLocalBounds().height/2 ));
    second.setPosition((window.getSize().x-106)/2,(window.getSize().y/2)-150);



    for(int i=0; i<5;i++){
        for(int j=0;j<11;j++){
            ufos.emplace_back(std::make_unique<Ufo>(110+75*j,30+75*i));
        }
    }



    sf::Clock clock,c2,u1,u2,s1,s2,s3;

    window.setFramerateLimit(60);



    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        window.draw(background_s);


        if(openframe==true){
            window.draw(first);
             window.draw(second);
            background_s.rotate(0.5);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                openframe=false;

            }

        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time elapsed = clock.restart();

        if(openframe==false and ship.GameOver()==0 and ship.Win()==0){

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            background_s.rotate(30*elapsed.asSeconds());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            background_s.rotate(-30*elapsed.asSeconds());
        }


        for(auto &a : shields){
            window.draw(*a);
            a->Lives(bullets,lasers,ufos);
        }

        for(unsigned int s=0; s<shields.size();s++){
            if(shields[s]->lives==0){
                shields.erase(shields.begin()+s);
            }
        }
        window.draw(ship);
        ship.Move(elapsed);
        ship.Shot(bullets,elapsed,c2);
        ship.Shooted(lasers);
        for(unsigned int a=0; a<bullets.size();a++){
            window.draw(*bullets[a]);
            bullets[a]->Boom(ufos,lasers);
            if(bullets[a]->To_remove()==true){
                bullets.erase(bullets.begin()+a);
            }
        }
        for(auto &l : lasers){
            window.draw(*l);
        }
        if(u2.getElapsedTime().asSeconds()>=1 and ufos.size()>=5){
            sf::Vector2f pos = ufos[randomi(0,ufos.size()-1)]->getPosition();
            lasers.emplace_back(std::make_unique<Laser>(pos.x+25,pos.y+25));
            u2.restart();
        }
        for(auto &a : lasers){
            a->move(0,450*elapsed.asSeconds());
        }


        for(unsigned int a=0; a<ufos.size();a++){

            window.draw(*ufos[a]);

            if(ufos[a]->isShooted()==true){
                ufos[a]->SetTexture();
                counter++;
                if(counter==15){
                    ufos.erase(ufos.begin()+a);
                    counter=0;
                }
            }

        }


        uMove(ufos,elapsed);
        LastUfos(ufos,u1);

        ship.Collision(ufos);

        for(auto &a : score){
            window.draw(a);
        }
        for(unsigned int a=0; a<hearts.size();a++){
            window.draw(*hearts[a]);
        }
        if(ship.shooted==true){
            hearts.erase(hearts.begin()+ship.lives);
            ship.shooted=false;
        }

        for(unsigned int i=0;i<lasers.size();i++){
            if(lasers[i]->getGlobalBounds().top+lasers[i]->getGlobalBounds().height>=775){
                lasers.erase(lasers.begin()+i);
            }
        }


        score[1].setString(std::to_string(iscore));

        ship.WinTheGame(ufos);
        }
        if(ship.GameOver()==1){
            background_s.rotate(0.5);
            sf::Text over[6];
            for(auto &a : over){
                a.setFont(lives_f);
            }
            over[0].setString("GAME OVER!");
            over[0].setOrigin(floor(over[0].getLocalBounds().width /2) , floor(over[0].getLocalBounds().height /2 ));
            over[0].setPosition(window.getSize().x/2,window.getSize().y/2-200);

            over[1].setString("Your score");
            over[1].setOrigin(floor(over[1].getLocalBounds().width /2) , floor(over[1].getLocalBounds().height /2 ));
            over[1].setPosition(window.getSize().x/2,window.getSize().y/2);

            over[2].setString(std::to_string(iscore));
            over[2].setOrigin(floor(over[2].getLocalBounds().width /2) , floor(over[2].getLocalBounds().height /2 ));
            over[2].setPosition(window.getSize().x/2,window.getSize().y/2+50);

            over[3].setString("Best score");
            over[3].setOrigin(floor(over[3].getLocalBounds().width /2) , floor(over[3].getLocalBounds().height /2 ));
            over[3].setPosition(window.getSize().x/2,window.getSize().y/2+150);

            over[4].setString(getScore());
            over[4].setOrigin(floor(over[4].getLocalBounds().width /2) , floor(over[4].getLocalBounds().height /2 ));
            over[4].setPosition(window.getSize().x/2,window.getSize().y/2+200);

            over[5].setString("press enter to restart");
            over[5].setOrigin(floor(over[5].getLocalBounds().width /2) , floor(over[5].getLocalBounds().height /2 ));
            over[5].setPosition(window.getSize().x/2,700);

            for(auto &a : over){
                window.draw(a);

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
               goto begin;
            }

        }
        if(ship.Win()==1){
            background_s.rotate(0.5);

            writeScore(iscore);
            sf::Text over[6];
            for(auto &a : over){
                a.setFont(lives_f);
            }
            over[0].setString("you win!");
            over[0].setOrigin(floor(over[0].getLocalBounds().width /2) , floor(over[0].getLocalBounds().height /2 ));
            over[0].setPosition(window.getSize().x/2,window.getSize().y/2-200);

            over[1].setString("Your score");
            over[1].setOrigin(floor(over[1].getLocalBounds().width /2) , floor(over[1].getLocalBounds().height /2 ));
            over[1].setPosition(window.getSize().x/2,window.getSize().y/2);

            over[2].setString(std::to_string(iscore));
            over[2].setOrigin(floor(over[2].getLocalBounds().width /2) , floor(over[2].getLocalBounds().height /2 ));
            over[2].setPosition(window.getSize().x/2,window.getSize().y/2+50);

            over[3].setString("Best score");
            over[3].setOrigin(floor(over[3].getLocalBounds().width /2) , floor(over[3].getLocalBounds().height /2 ));
            over[3].setPosition(window.getSize().x/2,window.getSize().y/2+150);

            over[4].setString(getScore());
            over[4].setOrigin(floor(over[4].getLocalBounds().width /2) , floor(over[4].getLocalBounds().height /2 ));
            over[4].setPosition(window.getSize().x/2,window.getSize().y/2+200);

            over[5].setString("press enter to restart");
            over[5].setOrigin(floor(over[5].getLocalBounds().width /2) , floor(over[5].getLocalBounds().height /2 ));
            over[5].setPosition(window.getSize().x/2,700);

            for(auto &a : over){
                window.draw(a);

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                goto begin;
            }

        }


        window.display();
    }

    return 0;
}
