#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<string.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace sf;
using namespace std;
class Menu{
public:
string n[5];
string s[5];
Sprite background,selections,help,pause,selections2,high,rank1,rank2,rank3,num,war,game;
Texture bg,select,h,select2,p,scores,r1,r2,r3,ba,ning,over;
Music menuOst,pOst;
Text name,left,right,pmenu,list,list2;
Font classic;
int option;
SoundBuffer b,b1;
Sound beep,beep2;
//add menu attributes here
Menu()
{
if(!bg.loadFromFile("cockpit.jpg")){
    cout<<"error"<<endl;
}
h.loadFromFile("help3.png");
help.setTexture(h);
select.loadFromFile("select.png");
selections.setTexture(select);
selections.setPosition(265,500);
selections.setScale(0.7,0.7);
p.loadFromFile("pausemenu.jpg");
pause.setTexture(p);
select2.loadFromFile("Pause2.png");
selections2.setTexture(select2);
selections2.setScale(0.3,0.3);
scores.loadFromFile("high.png");
high.setTexture(scores);
r1.loadFromFile("rank1.png");
rank1.setTexture(r1);
rank1.setScale(0.4,0.4);
rank1.setPosition(60,100);
r2.loadFromFile("rank2.png");
rank2.setTexture(r2);
rank2.setPosition(60,200);
rank2.setScale(0.4,0.4);
r3.loadFromFile("rank3.png");
rank3.setTexture(r3);
rank3.setPosition(55,300);
rank3.setScale(0.4,0.4);
ba.loadFromFile("45.png");
num.setTexture(ba);
num.setScale(0.5,0.5);
num.setPosition(80,450);
ning.loadFromFile("error.png");
war.setTexture(ning);
war.setScale(0.4,0.4);
war.setPosition(200,260);
over.loadFromFile("gameover.png");
game.setTexture(over);
game.setScale(0.3,0.3);

//text ///
classic.loadFromFile("earthorbiter.ttf");
name.setFont(classic);
name.setString("Odyssey");
name.setCharacterSize(90);
name.setStyle(sf::Text::Bold);
name.setFillColor(sf::Color::Black);
name.setPosition(190,-10);
left.setFont(classic);
left.setString("<");
left.setCharacterSize(70);
left.setPosition(60,500);
left.setStyle(sf::Text::Bold);
right.setFont(classic);
right.setString(">");
right.setCharacterSize(70);
right.setPosition(700,500);
right.setStyle(sf::Text::Bold);
pmenu.setFont(classic);
pmenu.setString("PAUSE");
pmenu.setCharacterSize(90);
pmenu.setStyle(sf::Text::Bold);
pmenu.setFillColor(sf::Color::Black);
pmenu.setPosition(230,230);
/// text ///
background.setTexture(bg);
background.setScale(0.9,0.9);
//background.setOrigin(390,20);
menuOst.openFromFile("dyinglight.ogg");
menuOst.setVolume(50.f);
pOst.openFromFile("street.ogg");
pOst.setVolume(40.f);
b.loadFromFile("beep.ogg");
beep.setBuffer(b);
beep.setVolume(90.f);
b1.loadFromFile("bosswarning.ogg");
beep2.setBuffer(b1);
beep2.setVolume(30.f);
option = 1;
//constructors body
}

void display_menu(RenderWindow &window)

{   
    Clock clock;
    float movement = 0;
    float keyTimer = 0;
    menuOst.play();
    while(window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        movement += time;
        keyTimer += time;
        Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
        if(movement >=1){
            background.move(0,-0.3);
        }
        
        if(movement >= 3){
             background.move(0,0.6);
        }
        
        if(movement >=5){
            background.setPosition(0,0);
            movement = 0;
        }
        if(name.getPosition().y != 230){
                name.move(0,1);
        }
  window.clear(Color::Black);
  window.draw(background); 
  window.draw(name); 
  if(option == 1){
    selections.setTextureRect(IntRect(0,0,355,155)); // start
    selections.setPosition(265,500);
  }
 else if(option == 2){
        selections.setTextureRect(IntRect(350,0,330,155)); // help
        selections.setPosition(265,500);
 }
 else if(option == 3){
      selections.setTextureRect(IntRect(650,0,670,155)); //highscores.
    selections.setPosition(150,500);//highscores
 }
  else if(option == 4){
     selections.setTextureRect(IntRect(1330,0,270,155)); //exit
     selections.setPosition(290,500); //exit
  }
 
  window.draw(selections);
  window.draw(left);
  window.draw(right);
    if(Keyboard::isKeyPressed(Keyboard::Right) && keyTimer >=2){
        beep.play();
            if(option == 4){
                option = 1;
            }
            else {
            option +=1;
            }
            keyTimer = 0;
    }
    if(Keyboard::isKeyPressed(Keyboard::Left) && keyTimer >=2){
        beep.play();
        if(option == 1){
            option = 4;
        }
        else {
            option -= 1;
        }
        keyTimer = 0;
    }
    if(Keyboard::isKeyPressed(Keyboard::Enter)){
        beep.play();
        if(option == 1){
            menuOst.stop();
            break;
        }
        else if(option == 2){
            while(1){
                if(Keyboard::isKeyPressed(Keyboard::B)){
                    beep.play();
                    break;
                }
                window.clear(sf::Color::Black);
                window.draw(help);
                window.display();
            }
        }
        else if(option == 3){
            highscores(window);
        }
        else if(option == 4){
            window.close();
        }
        
    }
    window.display();
    }
}
    bool pause_menu(RenderWindow &window){
        pOst.play();
        pOst.setLoop(true);
        option = 1;
        Clock clock;
        float keyTimer = 0;
        while(window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        keyTimer += time;
        Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
         window.clear(Color::Black);
         window.draw(pause); 
         window.draw(pmenu);
          if(option == 1){
    selections2.setTextureRect(IntRect(0,0,870,235)); // start
    selections2.setPosition(265,510);
        }
 else if(option == 2){
        selections2.setTextureRect(IntRect(900,0,560,235)); // help
        selections2.setPosition(275,510);
        }
 else if(option == 3){
      selections2.setTextureRect(IntRect(1490,0,980,235)); //highscores.
    selections2.setPosition(240,510);//highscores
        }
  else if(option == 4){
     selections2.setTextureRect(IntRect(2500,0,560,235)); //exit
     selections2.setPosition(290,510); //exit
         } 
          window.draw(selections2);
            window.draw(left);
            window.draw(right);
         if(Keyboard::isKeyPressed(Keyboard::Right) && keyTimer >=2){
        beep.play();
            if(option == 4){
                option = 1;
            }
            else {
            option +=1;
            }
            keyTimer = 0;
    }
    if(Keyboard::isKeyPressed(Keyboard::Left) && keyTimer >=2){
        beep.play();
        if(option == 1){
            option = 4;
        }
        else {
            option -= 1;
        }
        keyTimer = 0;
    }
    if(Keyboard::isKeyPressed(Keyboard::Enter)){
        beep.play();
        if(option == 1){
            pOst.pause();
            break;
        }
        else if(option == 2){
            while(1){
                if(Keyboard::isKeyPressed(Keyboard::B)){
                    beep.play();
                    break;
                }
                window.clear(sf::Color::Black);
                window.draw(help);
                window.display();
            }
        }
        else if(option == 3){
                return true;
        }
        else if(option == 4){
            window.close();
        }
        
    }
    window.display();
    }
        }
    void highscores(RenderWindow &window){
            read();
            Text sc,nm;
            ostringstream store,store2;
            for(int i=0;i<5;i++){
                store<<n[i]<<endl<<endl<<endl;
                store2<<s[i]<<endl<<endl<<endl;
            }
            nm.setFont(classic);
            nm.setString(store.str());
            nm.setCharacterSize(35);
            nm.setPosition(300,130);
            sc.setFont(classic);
            sc.setString(store2.str());
            sc.setCharacterSize(35);
            sc.setPosition(500,130);
            Clock clock;
            float button = 0;
            while(window.isOpen()){
                float time = clock.getElapsedTime().asSeconds();
                clock.restart();
                button+=time;
                Event e;
                while (window.pollEvent(e))
                {  
             if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
                }
                if(Keyboard::isKeyPressed(Keyboard::B) && button>=2){
                    beep.play();
                    break;
                }
                window.clear(sf::Color::Black);
                window.draw(high);
                window.draw(rank1);
                window.draw(rank2);
                window.draw(rank3);
                window.draw(num);
                window.draw(nm);
                window.draw(sc);
                window.display();
            }
    }
    bool gameOver(RenderWindow &window){
        beep2.play();
       // beep2.setLoop(true);
       left.setPosition(200,400);
       right.setPosition(580,400);
        int option = 1;
        Event e;
        Clock clock;
        float button = 0;
        while(window.isOpen()){
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            button+=time;
            while (window.pollEvent(e))
                {  
             if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
                }
                 if(option == 1){
                game.setTextureRect(IntRect(0,0,625,235)); // start
                game.setPosition(310,420);
                }
        else if(option == 2){
        game.setTextureRect(IntRect(640,0,560,235)); // help
        game.setPosition(345,420);
                }
                if(Keyboard::isKeyPressed(Keyboard::Left) && button >= 2){
                    beep.play();
                        if(option == 1){
                            option = 2;
                        }
                        else{
                          option -= 1;  
                        }
                      button = 0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Right) && button>=2){
                    beep.play();
                    if(option == 2){
                        option = 1;
                    }
                    else{
                        option+=1;
                    }
                    button = 0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter)){
                    beep.play();
                    if(option == 1){
                        return true;
                    }
                    else if(option == 2){
                        window.close();
                    }
                }
                window.draw(war);
                window.draw(game);
                window.draw(left);
                window.draw(right);
                window.display();
        }

    }
    void read(){
        
        ifstream input("highscore.txt");
       for(int i=0;i<5;i++){
            input >> s[i];
            input >> n[i];
       }
        
    }
    void write(){
        ofstream output("highscore.txt");
        for(int i=0;i<5;i++){
            output << s[i] << " " << n[i] << endl;
        }
    }
    void update(int pts,string nem){
        string boi;
        int temp;
        int updated[5];
        for(int i=0;i<5;i++){
            updated[i] = stoi(s[i]);
        }
        for(int i=5;i>=0;i--){

            if(pts>updated[i]){
                updated[i]=pts;
                n[i] = nem;
                break;              
            }
        }
        for(int i=0;i<5;i++){
            for(int j=i+1;j<5;j++){
                if(updated[j]>updated[i]){
                boi = n[i];
                n[i] = n[j];
                n[j] = boi;
                temp=updated[i];
                updated[i]=updated[j];
                updated[j]=temp;                
            }
            }
        }
        for(int i=0;i<5;i++){
            s[i] = to_string(updated[i]);
        }
    }
};
