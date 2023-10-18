#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<string.h>
#include <iostream>
#include "bomb.h"
#include "bullet.h"
#include "powerup.h"
using namespace sf;

class Enemy{
 public:
 int HP;
 bool firing,dead;
 Texture shape;
 Sprite sprite1;
 int x,y;
 int idx1; //for alpha,beta and gamma invaders
 Bomb *bomb;
 int bnum;
 std::string type;
 Enemy(){
    //nothing to be done here.
 }
   Enemy(std::string png){
    
    x = 340;
    y = 10;
    shape.loadFromFile(png);
    sprite1.setTexture(shape);
    sprite1.setPosition(x,y);
    sprite1.setScale(0.75,0.75);
 }
 virtual void setDetails(std::string png,int xpos,int ypos){
    // x = xpos;
    // y = ypos;
    // shape.loadFromFile(png);
    // sprite1.setTexture(shape);
    // sprite1.setPosition(x,y);
    // sprite1.setScale(0.75,0.75);
 }
 virtual void bMake(sf::Texture &t , int x, int y){
    //nothing to be done here.
 }
 virtual void bMove(){
    //will be implemented in the inherited class.
 }
 virtual void setDetails(std::string){
    //noting to be done here.
 }
  void bound(){
    if(sprite1.getPosition().x >= 780 - 10){
		x = 0;
		sprite1.setPosition(x +10 , y);
	}
	if(sprite1.getPosition().x <= 0){
		x = 780 - 10;
		sprite1.setPosition( x , y);
	}
	if(sprite1.getPosition().y <=0){
		y = 780-10;
		sprite1.setPosition(x,y);
	}
	if(sprite1.getPosition().y >= 780 - 10){
		y = 0;
		sprite1.setPosition(x , y + 10);
	}
    }
 virtual void Emove(int limit){
   
    if(sprite1.getPosition().y == limit){
        sprite1.move(1,0);
        bound();
    }
    
    else{
        sprite1.move(0,1);
         //std::cout<<sprite1.getPosition().y<<std::endl;
    } 
    
 }
 virtual void hit(Bullet &b,bool &col,int &detect) = 0;
    
 
 virtual ~Enemy(){
    delete[] bomb;
    bomb = NULL;
 }
};
class Invaders: public Enemy{
 public:
 Invaders(){
    //nothing to be done here.
 }
 
 virtual ~Invaders(){
    
 }
};
class alpha: public Invaders{
    public:
    
    alpha(){
            type = "alpha";
    }
    void setDetails(std::string png,int xpos,int ypos){
       
    x = xpos;
    y = ypos;
    shape.loadFromFile(png); 
    sprite1.setTexture(shape);
    sprite1.setPosition(x,y);
    sprite1.setScale(0.75,0.75);
    bomb = new Bomb[2];
    bnum = 0;
    }
    void bMake(sf::Texture &t , int x, int y){
        if(bnum >=2){
			for(int i=0;i<2;i++){
				bomb[i].hit = false;
			}
			bnum = 0;
			return;
		}
	bomb[bnum].bul.setTexture(t);
	bomb[bnum].bul.setPosition(x,y);
	bomb[bnum].bul.setScale(0.7f,0.7f);
	bnum += 1;
    }
    void bMove(){
        for(int i=0;i<bnum;i++){
		bomb[i].bul.move(0.f,+10.f);
		bomb[i].y = bomb[i].y + 10;
	}
    }
    
   void hit(Bullet &b,bool &col,int &detect){
    if(sprite1.getPosition().x < b.bul.getPosition().x + b.bul.getGlobalBounds().width && sprite1.getPosition().x + sprite1.getGlobalBounds().width > b.bul.getPosition().x && sprite1.getPosition().y < b.bul.getPosition().y + b.bul.getGlobalBounds().height && sprite1.getPosition().y + sprite1.getGlobalBounds().height > b.bul.getPosition().y){
        idx1 = 1;
        col = true;
        b.hit = true;
        dead = true;
        //std::cout<<"segment"<<std::endl;
         detect +=1;
    }
    else {
        return;
    }
 }
    ~alpha(){
       // std::cout<<"enemy destroyed"<<std::endl;
        delete[] bomb;
        bomb = NULL;
    }
};
class beta: public Enemy{
    public:
    
    beta(){
        type = "beta";
    }
    void setDetails(std::string png,int xpos,int ypos){
       
    x = xpos;
    y = ypos;
    shape.loadFromFile(png); 
    sprite1.setTexture(shape);
    sprite1.setPosition(x,y);
    sprite1.setScale(0.75,0.75);
    bomb = new Bomb[2];
    bnum = 0;
    HP = 2;
    }
    void bMake(sf::Texture &t , int x, int y){
        if(bnum >=2){
			for(int i=0;i<2;i++){
				bomb[i].hit = false;
			}
			bnum = 0;
			return;
		}
	bomb[bnum].bul.setTexture(t);
	bomb[bnum].bul.setPosition(x,y);
	bomb[bnum].bul.setScale(0.7f,0.7f);
	bnum += 1;
    }
    void bMove(){
        for(int i=0;i<bnum;i++){
		bomb[i].bul.move(0.f,+10.f);
		bomb[i].y = bomb[i].y + 10;
	}
    }
   void hit(Bullet &b,bool &col,int &detect){
    if(sprite1.getPosition().x < b.bul.getPosition().x + b.bul.getGlobalBounds().width && sprite1.getPosition().x + sprite1.getGlobalBounds().width > b.bul.getPosition().x && sprite1.getPosition().y < b.bul.getPosition().y + b.bul.getGlobalBounds().height && sprite1.getPosition().y + sprite1.getGlobalBounds().height > b.bul.getPosition().y){
        if(HP==0){
            idx1 =1;
            dead = true;
        }
        HP-=1;
        col = true;
        b.hit = true;
         detect +=1;
    }
    else {
        return;
    }
   }
    ~beta(){
      //std::cout<<"beta destroyed"<<std::endl;
        delete[] bomb;
        bomb = NULL;
    }
};
class gamma: public Enemy{
    public:
    
    gamma(){
        type = "gamma";
    }
    void setDetails(std::string png,int xpos,int ypos){
       
    x = xpos;
    y = ypos;
    shape.loadFromFile(png); 
    sprite1.setTexture(shape);
    sprite1.setPosition(x,y);
    sprite1.setScale(0.75,0.75);
    bomb = new Bomb[2];
    bnum = 0;
    HP = 3;
    idx1 = 0;
    }
    void bMake(sf::Texture &t , int x, int y){
        if(bnum >=2){
			for(int i=0;i<2;i++){
				bomb[i].hit = false;
			}
			bnum = 0;
			return;
		}
	bomb[bnum].bul.setTexture(t);
	bomb[bnum].bul.setPosition(x,y);
	bomb[bnum].bul.setScale(0.7f,0.7f);
	bnum += 1;
    }
    void bMove(){
        for(int i=0;i<bnum;i++){
		bomb[i].bul.move(0.f,+10.f);
		bomb[i].y = bomb[i].y + 10;
	}
    }
     void hit(Bullet &b,bool &col,int &detect){
    if(sprite1.getPosition().x < b.bul.getPosition().x + b.bul.getGlobalBounds().width && sprite1.getPosition().x + sprite1.getGlobalBounds().width > b.bul.getPosition().x && sprite1.getPosition().y < b.bul.getPosition().y + b.bul.getGlobalBounds().height && sprite1.getPosition().y + sprite1.getGlobalBounds().height > b.bul.getPosition().y){
        if(HP==0){
            idx1=1;
            dead = true;
        }
        HP-=1;
        col = true;
       // std::cout<<"segment"<<std::endl;
        b.hit = true;
        detect +=1;
    }
    else {
        return;
    }
     }
    ~gamma(){
      // std::cout<<"gamma destroyed"<<std::endl;
        delete[] bomb;
        bomb = NULL;
    }
};
class monster: public Enemy{
    public:
    monster(){
        type = "monster";
    }
    void setDetails(std::string png,int xpos,int ypos){
    x = xpos;
    y = ypos;
    shape.loadFromFile(png); 
    sprite1.setTexture(shape);
    sprite1.setPosition(x,y);
    sprite1.setScale(0.2,0.2);
    bomb = new Bomb;
    bnum = 0;
    HP = 15;
    idx1 = 0;
    }
   
    void bMake(sf::Texture &t , int x, int y){
        srand(time(NULL));
        if(bomb == NULL){
            bomb = new Bomb;
        }
        int r = rand()%4;
        if(r==0){
            bomb->bul.setTexture(t);
            bomb->bul.setPosition(x,y-60);
            bomb->bul.setScale(0.7,0.7);
        }
        else if(r==1){
            bomb->bul.setTexture(t);
            bomb->bul.setPosition(x+65,y);
            bomb->bul.setScale(0.7,0.7);
        }
        else if(r==2){
            bomb->bul.setTexture(t);
            bomb->bul.setPosition(x-45,y);
            bomb->bul.setScale(0.7,0.7);
        }
        else if(r==3){
            bomb->bul.setTexture(t);
            bomb->bul.setPosition(x,y+60);
            bomb->bul.setScale(0.7,0.7);
        }
        
    }
    void Emove(int limit){
            sprite1.move(2,0);
            bound();
    }
    void bMove(){
       bomb->bul.move(2.f,10.f);
	}
    void hit(Bullet &b,bool &col,int &detect){
    if(sprite1.getPosition().x < b.bul.getPosition().x + b.bul.getGlobalBounds().width && sprite1.getPosition().x + sprite1.getGlobalBounds().width > b.bul.getPosition().x && sprite1.getPosition().y < b.bul.getPosition().y + b.bul.getGlobalBounds().height && sprite1.getPosition().y + sprite1.getGlobalBounds().height > b.bul.getPosition().y){
        if(HP==0){
            idx1=1;
            dead = true;
        }
        HP-=1;
        col = true;
        b.hit = true;
        detect +=1;
    }
    else {
        return;
    }
     }
    ~monster(){
      std::cout<<"monster destroyed"<<std::endl;
        delete bomb;
        bomb = NULL;
    }
};
class dragon: public Enemy{
        public:
        
        dragon(){
            type = "dragon";
        }
        void setDetails(std::string png,int xpos,int ypos){
             x = xpos;
             y = ypos;
            shape.loadFromFile(png); 
            sprite1.setTexture(shape);
            sprite1.setPosition(x+150,y+10);
            sprite1.setScale(1,1);
            bomb = NULL;
            bnum = 3;
            HP = 50;
            idx1 = 0;
        }
        void bMake(sf::Texture &t,int x,int y){
            srand(time(NULL));
            if(bomb == NULL){
                bomb = new Bomb[3];
            }
            else if(bomb != NULL){
                for(int i=0;i<3;i++){
                    bomb[i].~Bomb();
                }
                delete[] bomb;
                bomb = new Bomb[3];
            }
            if(x==0){
                int a = rand()%200 + 50;
                int b = rand()%260 + 100;
                int c = rand()%400 + 250;
                bomb[0].bul.setTexture(t);
                bomb[0].bul.setPosition(a,y);
                bomb[0].bul.setScale(0.6,0.6);
                bomb[1].bul.setTexture(t);
                bomb[1].bul.setPosition(b,y);
                bomb[1].bul.setScale(0.6,0.6);
                bomb[2].bul.setTexture(t);
                bomb[2].bul.setPosition(c,y);
                bomb[2].bul.setScale(0.6,0.6);
                this->x = 0;
            }
            else if(x==1){
                int a = rand()%50+70;
                int b = rand()%170 + 70;
                int c = rand()%290+70;
                bomb[0].bul.setTexture(t);
                bomb[0].bul.setPosition(750,a);
                bomb[0].bul.setScale(0.8,0.8);
                bomb[1].bul.setTexture(t);
                bomb[1].bul.setPosition(750,b);
                bomb[1].bul.setScale(0.8,0.8);
                bomb[2].bul.setTexture(t);
                bomb[2].bul.setPosition(750,c);
                bomb[2].bul.setScale(0.8,0.8);
                this->x = 1;
            }
            else if(x==2){
                int a = rand()%50+70;
                int b = rand()%170 + 70;
                int c = rand()%290+70;
                bomb[0].bul.setTexture(t);
                bomb[0].bul.setPosition(0,a);
                bomb[0].bul.setScale(0.8,0.8);
                bomb[1].bul.setTexture(t);
                bomb[1].bul.setPosition(0,b);
                bomb[1].bul.setScale(0.8,0.8);
                bomb[2].bul.setTexture(t);
                bomb[2].bul.setPosition(0,c);
                bomb[2].bul.setScale(0.8,0.8);
                this->x = 2;
            }
        }
    
    void Emove(int limit){
            if(firing){
                return;
            }
            else{
            sprite1.move(1.f,0.f);
            bound();
            }
    }
    void bMove(){
           for(int i=0;i<bnum;i++){
            if(x==0){
            if(i==0){
                bomb[i].bul.move(0.f,8.f);
            }
            else if(i==1){
                bomb[i].bul.move(0.f,8.f);
            }
            else if(i==2){
                bomb[i].bul.move(0.f,8.f);
            }
            }
            else if(x==1){
                 if(i==0){
                bomb[i].bul.move(-6.f,8.f);
            }
            else if(i==1){
                bomb[i].bul.move(-6.f,8.f);
            }
            else if(i==2){
                bomb[i].bul.move(-6.f,8.f);
            }
            }
            else if(x==2){
                 if(i==0){
                bomb[i].bul.move(6.f,8.f);
            }
            else if(i==1){
                bomb[i].bul.move(6.f,8.f);
            }
            else if(i==2){
                bomb[i].bul.move(6.f,8.f);
            }
            }
           }
    }
    void hit(Bullet &b,bool &col,int &detect){
    if(sprite1.getPosition().x < b.bul.getPosition().x + b.bul.getGlobalBounds().width && sprite1.getPosition().x + sprite1.getGlobalBounds().width > b.bul.getPosition().x && sprite1.getPosition().y < b.bul.getPosition().y + b.bul.getGlobalBounds().height && sprite1.getPosition().y + sprite1.getGlobalBounds().height > b.bul.getPosition().y){
        if(HP==0){
            idx1=1;
            dead = true;
        }
        HP-=1;
        col = true;
        b.hit = true;
        detect +=1;
    }
    else {
        return;
    }
    }
    ~dragon(){
     std::cout<<"dragon destroyed"<<std::endl;
        delete[] bomb;
        bomb = NULL;
    }

};