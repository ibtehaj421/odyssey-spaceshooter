#include <SFML/Graphics.hpp>
#include<string.h>
#include "enemy.h"
using namespace sf;
using namespace std;

class Player{
public:
int HP;
int lifeCount;
Texture tex;
Sprite sprite;
Texture sheld;
Sprite shd;
Texture life;
Sprite *lives;
float speed = 1;
bool mhit;
int x,y;
int bstream,fbstream,frstream;
Bullet *bullet;
Bullet **frenzyBullet;
PowerUp *pw;
bool hit,hopup,sheild,frenzy,red;
// sound //
SoundBuffer s;
Sound make;
// sound //
Player(std::string png_path,std::string png,std::string pngsh)
{
lifeCount = 3;
HP = 10;
tex.loadFromFile(png_path);
sprite.setTexture(tex);
x=340;y=700;
 mhit = 0;
 hit = false;
sprite.setPosition(sf::Vector2f(x,y));
sprite.setScale(0.75,0.75);
bstream = 0;
fbstream = 0;
bullet = new Bullet[10];
frenzyBullet = new Bullet*[7];
for(int i=0;i<7;i++){
	frenzyBullet[i] = new Bullet[10];
}
lives = new Sprite[lifeCount];
life.loadFromFile(png);
int lp = 10;
for(int i=0;i<lifeCount;i++){
	lives[i].setTexture(life);
	lives[i].setPosition(lp,10);
	lives[i].setScale(0.7,0.7);
	lp+=30;
}
sheld.loadFromFile(pngsh);
shd.setTexture(sheld);
shd.setPosition(x-35,y-30);
s.loadFromFile("fire.ogg");
make.setBuffer(s);
make.setVolume(20.f);
pw = NULL;
}
void bt(sf::Texture &t , int x, int y){
	
		if(bstream >=10){
			for(int i=0;i<10;i++){
				bullet[i].hit = false;
			}
			bstream = 0;
			return;
		}
	bullet[bstream].bul.setTexture(t);
	bullet[bstream].bul.setPosition(x+30,y-21);
	bullet[bstream].bul.setScale(0.7f,0.7f);
	bstream += 1;
	make.play();
}
void btfrenzy(sf::Texture &pn1,sf::Texture &pn2,sf::Texture &pn3, sf::Texture &pn4, sf::Texture &pn5,int x,int y){
		make.play();
		if(frenzy){
		if(fbstream>=10){
			for(int i=0;i<7;i++){
				for(int j=0;j<10;j++){
					frenzyBullet[i][j].hit = false;
				}
			}
			fbstream = 0;
			return;
		}
		for(int i=0;i<7;i++){
				if(i==0){
					frenzyBullet[i][fbstream].bul.setTexture(pn1);
					frenzyBullet[i][fbstream].bul.setPosition(x+30,y-21);
					frenzyBullet[i][fbstream].bul.setScale(0.7,0.7);
				}
				else if(i==1){
					frenzyBullet[i][fbstream].bul.setTexture(pn2);
					frenzyBullet[i][fbstream].bul.setPosition(x+30,y-21);
					frenzyBullet[i][fbstream].bul.setScale(0.7,0.7);
				}
				else if(i==2){
					frenzyBullet[i][fbstream].bul.setTexture(pn3);
					frenzyBullet[i][fbstream].bul.setPosition(x+30,y-21);
					frenzyBullet[i][fbstream].bul.setScale(0.7,0.7);
				}
				else if(i==3){
					frenzyBullet[i][fbstream].bul.setTexture(pn4);
					frenzyBullet[i][fbstream].bul.setPosition(x+30,y-21);
					frenzyBullet[i][fbstream].bul.setScale(0.7,0.7);
				}
				else if(i==4){
					frenzyBullet[i][fbstream].bul.setTexture(pn5);
					frenzyBullet[i][fbstream].bul.setPosition(x+30,y-21);
					frenzyBullet[i][fbstream].bul.setScale(0.7,0.7);
				}
				else if(i==5){
					frenzyBullet[i][fbstream].bul.setTexture(pn5);
					frenzyBullet[i][fbstream].bul.setPosition(x+30,y-21);
					frenzyBullet[i][fbstream].bul.setScale(0.7,0.7);
				}
				else if(i==6){
					frenzyBullet[i][fbstream].bul.setTexture(pn5);
					frenzyBullet[i][fbstream].bul.setPosition(x+30,y-21);
					frenzyBullet[i][fbstream].bul.setScale(0.7,0.7);
				}
			}
		}
		fbstream+=1;
	
}
void newLife(){
	if(lives == NULL){
	lifeCount = 3;
	lives = new Sprite[lifeCount];
	int lp = 10;
for(int i=0;i<lifeCount;i++){
	lives[i].setTexture(life);
	lives[i].setPosition(lp,10);
	lives[i].setScale(0.7,0.7);
	lp+=30;
}
	}
	else if(lives != NULL){
		lifeCount = 3;
		delete[] lives;
		lives = new Sprite[lifeCount];
		int lp = 10;
    for(int i=0;i<lifeCount;i++){
	lives[i].setTexture(life);
	lives[i].setPosition(lp,10);
	lives[i].setScale(0.7,0.7);
	lp+=30;
	}
}
}
void btfire(sf::Texture &tex,int x,int y){
		if(bstream >=10){
			for(int i=0;i<10;i++){
				bullet[i].hit = false;
			}
			bstream = 0;
			return;
		}
	bullet[bstream].bul.setTexture(tex);
	bullet[bstream].bul.setPosition(x+30,y-21);
	bullet[bstream].bul.setScale(0.7f,0.7f);
	bstream += 1;
	make.play();
}
void fire(RenderWindow &window)
{        
	if(!frenzy){
		//std::cout<<bstream<<" bullet"<<std::endl;
		if(bstream>=1){
			//std::cout<<bstream<<" bullet"<<std::endl;
	for(int i=0;i<bstream;i++){
		bullet[i].bul.move(0.f,-10.f);
		bullet[i].y = bullet[i].y - 10;
	}
	}
	}
	else if(frenzy){
		if(fbstream>=1){
		for(int i=0;i<7;i++){
			for(int j=0;j<fbstream;j++){
				if(i==0){
					frenzyBullet[i][j].bul.move(-4.5,-10.f);
				}
				else if(i==1){
					frenzyBullet[i][j].bul.move(-2.f,-10.f);
				}
				else if(i==2){
					frenzyBullet[i][j].bul.move(0.f,-10.f);
				}
				else if(i==3){
					frenzyBullet[i][j].bul.move(2.f,-10.f);
				}
				else if(i==4){
					frenzyBullet[i][j].bul.move(3.f,-10.f);
				}
				else if(i==5){
					frenzyBullet[i][j].bul.move(4,-10.f);
				}
				else if(i==6){
					frenzyBullet[i][j].bul.move(4.5,-10.f);
				}
				
			}
		}
	}
	}
}
void bound(RenderWindow &window){
	if(sprite.getPosition().x >= 780 - 10){
		x = 0;
		sprite.setPosition(x +10 , y);
	}
	if(sprite.getPosition().x <= 0){
		x = 780 - 10;
		sprite.setPosition( x , y);
	}
	if(sprite.getPosition().y <=0){
		y = 780-10;
		sprite.setPosition(x,y);
	}
	if(sprite.getPosition().y >= 780 - 10){
		y = 0;
		sprite.setPosition(x , y + 10);
	}
}
 void pbhit(Sprite &body,bool &a){
	 if(sprite.getPosition().x < body.getPosition().x +  body.getGlobalBounds().width && sprite.getPosition().x + sprite.getGlobalBounds().width >  body.getPosition().x && sprite.getPosition().y <  body.getPosition().y +  body.getGlobalBounds().height && sprite.getPosition().y + sprite.getGlobalBounds().height >  body.getPosition().y){
		hit = true;
		if(a){
			a = false;
		}
		else{
			a = true;
		}
		//cout<<"hit"<<endl;
	   }
	   else {
		return;
	   }
 }
 void phit(Sprite &body){
	   if(sprite.getPosition().x < body.getPosition().x +  body.getGlobalBounds().width && sprite.getPosition().x + sprite.getGlobalBounds().width >  body.getPosition().x && sprite.getPosition().y <  body.getPosition().y +  body.getGlobalBounds().height && sprite.getPosition().y + sprite.getGlobalBounds().height >  body.getPosition().y){
		lifeCount = 0;
		hit = true;
	   }
		else {
			return;
		}
}
void delay(int &d){
	  // if(d<20)
		d++;
}
void move(std::string s){
float delta_x=0,delta_y=0;
if(s=="l"){
	delta_x = -3;   //move the player left
}
else if(s=="r")
	 delta_x = 3;//move the player right

if(s=="u")
	delta_y-= 3;

else if(s=="d")
	delta_y=3;


delta_x*=speed;
delta_y*=speed;
 x =  x + delta_x;
 y =  y + delta_y;
sprite.move(sf::Vector2f(delta_x, delta_y));
shd.move(delta_x,delta_y);
}
void Life(){
	if(lifeCount == 0){
		delete[] lives;
		lives = NULL;
		return;
	}
	else if(lifeCount>0 && lifeCount<=5){
		int lp = 10;
		delete[] lives;
		lifeCount = lifeCount - 1;
		lives = new Sprite[lifeCount];
		for(int i=0;i<lifeCount;i++){
				lives[i].setTexture(life);
				lives[i].setPosition(lp,10);
				lives[i].setScale(0.7,0.7);
				lp+=30;
		}
		}
	else
	{return;}
}
void powerup(std::string type){
	if(hopup){
		if(type == "health"){
			int lp = 10;
			if(lifeCount == 5){
				return;
			}
			else if(lifeCount<=5){
			delete[] lives;
			 lifeCount = lifeCount + 1;
			 lives = new Sprite[lifeCount];
			 for(int i=0;i<lifeCount;i++){
				lives[i].setTexture(life);
				lives[i].setPosition(lp,10);
				lives[i].setScale(0.7,0.7);
				lp+=30;
			 }
			 }
		}
		else if(type=="sheild"){
			HP = 2000;
			sheild = true;
		}
		else if(type=="frenzy"){
			frenzy = true;
		}
		else if(type == "fire"){
			red = true;
		}
		else {
			return;
		}
			}
}
	~Player(){
		delete[] bullet;
		bullet = NULL;
		for(int i=0;i<5;i++){
			for(int j=0;j<10;i++){
				frenzyBullet[i][j].~Bullet();
			}
		}
		delete[] frenzyBullet;
		frenzyBullet = NULL;
		
	}
};

