
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include "player.h"
#include "menu.h"
#include "meteor.h"
#include <cstring>
#include <fstream>
#include <sstream>
const char title[] = "OOP-Project, 22I-0767 CS-D";
using namespace sf;
using namespace std;
//void FormationSetter(Enemy &en);
class Game
{
public:
Menu men;
Sprite background,enl,enr,exp,rank; //Game background sprite
Texture bg_texture,laser,ebullet,mbullet,l1,l2,l3,l4,laserRed,dbeam,enleft,enright,losion,r,dbeam1,dbeam2;
Player* p; //player
Enemy**  en; //enemy
Bullet *b; //tester bullet
Meteor *danger;
bool collision,lvl1,lvl2,meteor,mons,boss,restart,pause,blink;
Enemy *m; //for the monster.
Enemy *de; // for the dragon.
//PowerUp *pw;
// add other game attributes
int xpos,ypos,frame,row,frame2,row2,playerframe,mbombFrame; //frame variables for the sprite sheets and animations.
int detect,score,lvl,badge; //score will show player points.
int entity1,entity2; // this will allow for an entity,monster or dragon to be called only once per game.
float eBombTime,lvlTime,mTime,mBombTime,pwTime,shTime,drTime,frTime,framerate,framerate2,dangerTime,dangerEndTime,framerate3,monsbDel,monshitTimer,Dragon,bossTimer,redTime,timer,blinkTimer;
int formation,frameTrack,frameTrack2,blinkSet;
string mon,pow,dface,dfire,number,scores,playerName,compare,greybig,greysmall; //scores is for storing the integer score.
string mbul; //monster and dragon beam png string.
string alp,bet,gam; /// for assigning textures to the enemies at random.
//// music files ////
Music ost,regal;
/// music files ////
//// text files ////
Text leevel,levelnum,points,point,pname,enter; //level and level number along with points and score to show player points.
Font classic;
//// text files ////
Game()
{
 srand(time(NULL));
en = new Enemy*[6];
 alp = "img/PNG/Enemies/enemyBlue2.png";
 bet = "img/PNG/Enemies/enemyGreen5.png";
 gam = "img/PNG/Enemies/enemyRed4.png";
 mon = "regalspirit.png";
 dface = "purpledrago.png";
 number = "1";
 greybig = "img/PNG/Meteors/meteorGrey_big1.png";
 greysmall = "img/PNG/Meteors/meteorGrey_med1.png";
 de = NULL;
 m = NULL;
 danger = NULL;

p=new Player("swordfishsheet.png","img/PNG/UI/playerLife1_blue.png","img/PNG/Effects/shield2.png");
laser.loadFromFile("img/PNG/Lasers/laserBlue01.png");
l1.loadFromFile("bulletleft.png");
l2.loadFromFile("bulletleft1.png");
l3.loadFromFile("bulletright1.png");
l4.loadFromFile("bulletright.png");
laserRed.loadFromFile("img/PNG/Lasers/laserRed01.png");
ebullet.loadFromFile("img/PNG/Lasers/laserRed08.png");
mbullet.loadFromFile("regalbomb.png");
dbeam.loadFromFile("firesheet.png");
dbeam1.loadFromFile("purplefireleft.png");
dbeam2.loadFromFile("purplefireright.png");
//pw = NULL;
bg_texture.loadFromFile("citybg.jpg");
background.setTexture(bg_texture);
background.setScale(1, 1);
collision = false;
int k;
for(int i=0;i<6;i++){
    k = rand()%3;
    if(k==0){
        en[i] = new alpha;
    }
    else if(k==1){
        en[i] = new beta;
    }
    else if(k==2){
        en[i] = new gamma;
    }
}
xpos = 270;
ypos = 10;
detect = 1;
entity1 = 0;
entity2 = 0;
formation = 1;
row = 0;
frame = 0;
frame2 = 0;
row2 = 0;
score = 0;
lvl = 3;
lvl1 = lvl2 = true;
meteor = false;
frameTrack = 0;
restart = false;
pause = false;
blink = false;
scores = to_string(score);
/// setting audio files ///
ost.openFromFile("timecop.ogg");
ost.setVolume(50.f);
regal.openFromFile("regalsound.ogg");
regal.setVolume(70.f);
/// setting audio files ///
/// setting text files ///
classic.loadFromFile("earthorbiter.ttf");
leevel.setFont(classic);
leevel.setString("LEVEL");
leevel.setStyle(sf::Text::Bold);
leevel.setCharacterSize(70);
levelnum.setFont(classic);
levelnum.setString(number);
levelnum.setStyle(sf::Text::Bold);
levelnum.setCharacterSize(70);
points.setFont(classic);
points.setString("SCORE:");
points.setCharacterSize(35);
points.setStyle(sf::Text::Bold);
points.setPosition(20,730);
point.setFont(classic);
point.setString(scores);
point.setCharacterSize(35);
point.setStyle(sf::Text::Bold);
point.setPosition(200,730);
enter.setFont(classic);
enter.setString("ENTER NAME:");
enter.setStyle(sf::Text::Bold);
enter.setCharacterSize(50);
enter.setPosition(200,50);
pname.setFont(classic);
pname.setStyle(sf::Text::Bold);
pname.setString("");
pname.setCharacterSize(45);
pname.setPosition(200,100);
/// setting text files //
}
void start_game(){
   
  if(formation == 1){
  /// formation 1 ///
  int j;
    for(int i=0;i<6;i++){
       
        if(i==3){
            xpos = 270;
            ypos = 75;
        }
        if(en[i]->type=="alpha"){
        en[i]->setDetails(alp,xpos,ypos);
        }
       else if(en[i]->type=="beta"){
         en[i]->setDetails(bet,xpos,ypos);
       }
       else if(en[i]->type=="gamma"){
         en[i]->setDetails(gam,xpos,ypos);
       }
        xpos+=70;
    }
}
    /// formation 1 ///
    else if(formation == 2){
    /// formation 2 ///
    int k;
    for(int i=0;i<6;i++){
       
        if(i==0){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,200,75);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,200,75);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,200,75);
            }
        }
        if(i==1){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,270,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,270,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,270,10);
            }
        }
        if(i==2){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,340,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,340,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,340,10);
            }
        }
        if(i==3){
            if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,270,150);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,270,150);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,270,150);
            }
        }
        if(i==4){
            if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,340,150);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,340,150);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,340,150);
            }
        }
       if(i==5){
        if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,410,75);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,410,75);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,410,75);
            }
       }
    }  
    }
    //// formation 2 //////
    //// formation 3 //////
    else if(formation == 3){
        for(int i=0;i<6;i++){
       
        if(i==0){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,270,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,270,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,270,10);
            }
        }
        if(i==1){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,345,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,345,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,345,10);
            }
        }
        if(i==2){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,420,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,420,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,420,10);
            }
        }
        if(i==3){
            if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,315,75);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,315,75);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,315,75);
            }
        }
        if(i==4){
            if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,390,75);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,390,75);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,390,75);
            }
        }
       if(i==5){
        if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,350,150);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,350,150);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,350,150);
            }
       }
    }       
    }
    /// formation 3 ///
    srand(time(NULL));
    RenderWindow window(VideoMode(780, 780), title);
    men.display_menu(window);
    EnterName(window);
    animation(window);
    men.read();
    ifstream input("highscore.txt");
    for(int i=0;i<6;i++){
         input >> compare;
         if(compare == playerName){
            badge = i;
            break;
    }
    }
    /// assigning a rank badge to player ///
    if(badge == 1){
        r.loadFromFile("rank1.png");
    }
    else if(badge == 3){
        r.loadFromFile("rank2.png");
    }
    else if(badge == 5){
        r.loadFromFile("rank3.png");
    }
    rank.setTexture(r);
    rank.setScale(0.2,0.2);
    rank.setPosition(530,730);
    //cout<<playerName<<endl;
    Clock clock;
    ost.play();
    regal.setLoop(true);
    timer=0;
    //bossTimer;
     int delay; // for the bullet delay.
    mons = false;
    boss = false;
    redTime = 0;
    eBombTime = 2;
    mBombTime = 4;
    lvlTime = 0;
    mTime = 0;
    pwTime = 0;
    shTime = 0;
    frTime = 0;
    drTime = 0;
    framerate =0;
    framerate2 = 0;
    dangerTime = 0;
    dangerEndTime = 0;
    framerate3 = 0;
    monsbDel = 0;
    monshitTimer = 0;
    Dragon = rand()%100 + 30;
    pname.setCharacterSize(35);
    pname.setPosition(600,730);
    while (window.isOpen())
    {    
        //frame = 0;
        playerframe = 1;
        detect = 1;
        
        float time = clock.getElapsedTime().asSeconds();
        float time2 = clock.getElapsedTime().asMilliseconds(); 
         if(!pause){
        lvlTime +=time;
        timer += time;
        mTime +=time;
        pwTime+=time;
        shTime+=time;
        drTime += time;
        frTime += time;
        framerate+=time2;
        framerate2+=time2;
        bossTimer+=time;
        dangerTime+=time;
        dangerEndTime+=time;
        framerate3+=time;
        monsbDel += time;
        monshitTimer +=time;
        redTime +=time;
        blinkTimer+=time2;
        }
        clock.restart();
        cout<<blinkTimer<<endl;
        //delay+=time;
       //cout<<lvlTime<<endl;   
 	Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
          
	if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
            p->move("l");    // Player will move to left
	if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            p->move("r");  //player will move to right
	if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
            p->move("u");    //playet will move upwards
	if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            p->move("d");  //player will move downwards
    if(Keyboard::isKeyPressed(Keyboard::F) && delay>20){
        if(!p->frenzy && !p->red){
          p->bt(laser,p->sprite.getPosition().x , p->sprite.getPosition().y);
        }
        else if(!p->frenzy && p->red){
            p->btfire(laserRed,p->sprite.getPosition().x , p->sprite.getPosition().y);
        }
         else if(p->frenzy && !p->red){
             p->btfrenzy(l1,l2,laser,l3,l4,p->sprite.getPosition().x , p->sprite.getPosition().y);
         }
           delay = 0; 
    }
    if(Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left)){
        playerframe = 0;
    }
    if(Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Right)){
        playerframe = 2;
    }
    if(Keyboard::isKeyPressed(Keyboard::P)){
        ost.pause();
        pause = true;
        timerReset();
       restart =  men.pause_menu(window);
       pause = false;
        ost.play();
    }
	////////////////////////////////////////////////
	/////  Call your functions here            ////
    if(restart){
        Restart();
        restart = false;
    }
    if(boss){
        cout<<"drag: "<<bossTimer<<endl;
        if(bossTimer >= 30){
            drTime =0;
            bossTimer = 0;
            boss = false;
            //de->~Enemy();
            delete de;
            //de = NULL;
            score = score + 700;
            regal.pause();
            ost.play();
        }
        else{
            if(timer >= 3){
                int t = rand()%3;
                if(t==0){
                   de->bMake(dbeam,t,de->sprite1.getPosition().y);
                }
                else if(t==1){
                    de->bMake(dbeam1,t,de->sprite1.getPosition().y);
                }
                else if(t==2){
                    de->bMake(dbeam2,t,de->sprite1.getPosition().y);
                }
                de->firing = true;
                
                timer = 0;
            }
        }
            if(de->bomb !=NULL){
                de->bMove();
            }

            if(!p->hit && de->firing == true){
                for(int i=0;i<3;i++){
                    p->pbhit(de->bomb[i].bul,de->firing);
        }   
            }
            }

    if(mons){
       // m->Emove(780);
        cout<<"mons: "<<mTime<<endl;
        if(m->HP == 0 || boss == true || mTime >=30){
            mons = false;
           // m->~Enemy();
            regal.pause();
            ost.play();
            delete m;
            m = NULL;
            mTime = 0;
            score = score + 500;
        }
        
        else{
        for(int i=0;i<p->bstream;i++){
            m->hit(p->bullet[i],collision,detect);
        }
        if(m->bomb != NULL){
            if(monsbDel >=2.5){
                delete m->bomb;
                m->bomb = NULL;
                monsbDel = 0;
                monshitTimer = 0;
            }
        }
        if(timer >= mBombTime){
            m->bMake(mbullet,p->sprite.getPosition().x,p->sprite.getPosition().y);
            monsbDel = 0;
            monshitTimer = 0;
            timer = 0;
        }
        if(m->bomb != NULL){
          if(monshitTimer >=1){
        if(p->hit == false){
        p->pbhit(m->bomb->bul,p->mhit);
        p->phit(m->sprite1);
        }
       // monshitTimer = 0;
          }
        }
    }
    }
    
    if(pwTime >= 10){
        pwTime = 0;
        if(p->pw != NULL){
            //pw->~PowerUp();
             delete p->pw;
             p->pw = NULL;
        }
        if(p->pw == NULL){
        int r = rand()%4;
        cout<<r<<endl;
        if(r==0){
           p->pw = new health;
           pow = "img/PNG/Power-ups/pill_blue.png";
           p->pw->setDetails(pow,rand()%200,rand()%780); 
        }
        else if(r==1){
           p->pw = new sheild;
          pow = "img/PNG/Power-ups/star_silver.png";
          p->pw->setDetails(pow,rand()%200+350,rand()%760); 
        }
        else if(r==2){
            p->pw = new rFire;
            pow = "img/PNG/Power-ups/bolt_gold.png";
            p->pw->setDetails(pow,rand()%200,rand()%760);
        }
        else if(r==3){
            p->pw = new fireup;
            pow = "img/PNG/Power-ups/bold_silver.png";
            p->pw->setDetails(pow,rand()%200+350,rand()%760);
        }
        }
    }
    if(lvlTime >= 30 && en!=NULL){
        for(int i=0;i<6;i++){
            en[i]->idx1 = 1;
        }
        lvlTime = 0;
    }
     if(en[3]->idx1 == 1 && en[4]->idx1 == 1 && en[5]->idx1 == 1 && en[2]->idx1 == 1 && en[1]->idx1 == 1 && en[0]->idx1 == 1){
           if(!boss){
           if(mTime >=30 && entity1 == 0){
            if(en != NULL){
                m = new monster;
                m->setDetails(mon,500,70);
                ost.pause();
                regal.play();
                mons = true;
                entity1 = 1;
                mTime = 0;
                monsbDel = 0;
                monshitTimer = 0;
            }
           }
           }
         if(en !=NULL){
        for(int i=0;i<6;i++){
             en[i]->~Enemy();
        }
        delete[] en;
        en = NULL;
        en = new Enemy*[6];
     }
           
                 int k;
for(int i=0;i<6;i++){
    k = rand()%3;
    if(k==0){
        en[i] = new alpha;
    }
    else if(k==1){
        en[i] = new beta;
    }
    else if(k==2){
        en[i] = new gamma;
    }
   }    
        formation = rand()%3+1;
        xpos = 270;
        ypos = 10;
        if(formation == 1){
  /// formation 1 ///
  int j;
    for(int i=0;i<6;i++){
       
        if(i==3){
            xpos = 270;
            ypos = 75;
        }
        if(en[i]->type=="alpha"){
        en[i]->setDetails(alp,xpos,ypos);
        }
       else if(en[i]->type=="beta"){
         en[i]->setDetails(bet,xpos,ypos);
       }
       else if(en[i]->type=="gamma"){
         en[i]->setDetails(gam,xpos,ypos);
       }
        xpos+=70;
    }
}
    /// formation 1 ///
    else if(formation == 2){
    /// formation 2 ///
    int k;
    for(int i=0;i<6;i++){
       
        if(i==0){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,200,75);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,200,75);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,200,75);
            }
        }
        if(i==1){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,270,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,270,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,270,10);
            }
        }
        if(i==2){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,340,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,340,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,340,10);
            }
        }
        if(i==3){
            if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,270,150);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,270,150);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,270,150);
            }
        }
        if(i==4){
            if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,340,150);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,340,150);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,340,150);
            }
        }
       if(i==5){
        if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,410,75);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,410,75);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,410,75);
            }
       }
    }  
    }
    //// formation 2 //////
    //// formation 3 //////
    else if(formation == 3){
        for(int i=0;i<6;i++){
       
        if(i==0){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,270,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,270,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,270,10);
            }
        }
        if(i==1){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,345,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,345,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,345,10);
            }
        }
        if(i==2){
            if(en[i]->type=="alpha"){
                 en[i]->setDetails(alp,420,10);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,420,10);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,420,10);
            }
        }
        if(i==3){
            if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,315,75);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,315,75);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,315,75);
            }
        }
        if(i==4){
            if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,390,75);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,390,75);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,390,75);
            }
        }
       if(i==5){
        if(en[i]->type=="alpha"){
                en[i]->setDetails(alp,350,150);
            }
            else if(en[i]->type=="beta"){
                 en[i]->setDetails(bet,350,150);
            }
            else if(en[i]->type=="gamma"){
                 en[i]->setDetails(gam,350,150);
            }
       }
    }       
    }
     
    }
     
    if(p->hit){
        if(!p->sheild){
        p->hit = false;
        blink = true;
        blinkTimer = 0;
        p->HP = p->HP - 1;
        p->Life();
        //cout<<"hit"<<endl;
        }
    }
    if(p->pw!=NULL){
       shTime = 0;
       frTime = 0;
       redTime = 0;
       p->pw->Hit(p->sprite,p->hopup);
       p->powerup(p->pw->type);
       if(p->hopup){
        //pw->~PowerUp();
         delete p->pw;
         p->pw = NULL;
       p->hopup = false;
       }
    }
    if(p->sheild && shTime >=8){
        p->sheild = false;
        shTime = 0;
        p->HP = 10;
    }
    if(p->frenzy && frTime >=8){
        p->frenzy = false;
        frTime = 0;
    }
    if(p->red && redTime>=8){
        p->red = false;
        redTime = 0;
    }
    if(p->lives == NULL){
        ost.pause();
        cout<<"life ended"<<endl;
        men.update(score,playerName);
        men.write();
        restart = men.gameOver(window);
    }
    
        if(!boss && !mons && en != NULL){
            for(int i=0;i<6;i++){
                en[i]->bMove();
                p->phit(en[i]->sprite1);
            }
            for(int i=0;i<6;i++){
                for(int j=0;j<en[i]->bnum;j++){
                if(en[i]->bnum>=1){
                    p->pbhit(en[i]->bomb[j].bul,en[i]->bomb[j].hit);
                }
                }
            }
        }
     p->fire(window);
     p->delay(delay); //bullet spawn delay.
     p->bound(window);
     if(!boss){
     if(drTime >= Dragon){
        if(m != NULL){
            regal.pause();
           // m->~Enemy();
            delete m;
            m = NULL;
            mTime = 0;
            mons = false;
        }
        ost.pause();
        regal.play();
        boss = true;
        de = new dragon;
        de->setDetails(dface,280,10);
        drTime = 0;
        bossTimer = 0;
        Dragon = rand()%100 + 40;
        timer = 0;
     }
     }
     
   if(!boss && !mons && en !=NULL){
    if(!meteor){
        if(dangerTime >= 10){
            meteor = true;
            dangerTime = 0;
            dangerEndTime = 0;
            if(danger != NULL){
                danger->~Meteor();
                //delete danger;
            }
            int r = rand()%2;
            if(r==0){
                danger = new Meteor(greybig);
            }
            else if(r==1){
                danger = new Meteor(greysmall);
            }
        }
    }
    if(meteor){
         p->phit(danger->sprite);
         if(p->hit){
            dangerEndTime = 0;
            meteor = false;
            danger->~Meteor();
         }
        else if(dangerEndTime >= 8 || danger->bound()){
            //cout<<"position: "<<danger->sprite.getPosition().y<<endl;
            dangerEndTime = 0;
            meteor = false;
            danger->~Meteor();
            score = score + 20;
            //delete danger;
            //danger = NULL;
        }
        danger->move();
    }
    if(detect == 1){
        if(formation == 1){
     for(int i=0;i<6;i++){ //for first formation.
     int limit;
        if(i==0 || i==1 || i==2){
            limit = 325;
        }
        else {
            limit = 400;
        }
        en[i]->Emove(limit);
        
     }
        }
        else if(formation == 2){ //for the second formation.
            for(int i=0;i<6;i++){
                int limit;
                if(i==1 || i==2){
                    limit = 250;
                }
                else if(i==0 || i==5){
                    limit = 325;
                }
                else {
                    limit = 400;
                }
                en[i]->Emove(limit);
            }
        }
        else if(formation==3){ //for the third formation
                for(int i=0;i<6;i++){
                    int limit;
                    if(i==0 || i==1 || i==2){
                        limit = 250;
                    }
                    else if(i==3 || i==4){
                        limit = 325;
                    }
                    else {
                        limit = 400;
                    }
                    en[i]->Emove(limit);
                }
        }
     if(timer >= lvl && en != NULL){
            timer = 0;
            while(1){
            int enemy = rand()%6;
            int enemy2 = rand()%6;
            if(en[enemy]->idx1 == 1 && en[enemy2]->idx1 == 1 && enemy2 == enemy){
                continue;
            }
            else if(en[enemy]->idx1 != 1 && en[enemy2]->idx1 != 1){
            en[enemy]->bMake(ebullet,en[enemy]->sprite1.getPosition().x , en[enemy]->sprite1.getPosition().y);
            en[enemy2]->bMake(ebullet,en[enemy2]->sprite1.getPosition().x , en[enemy2]->sprite1.getPosition().y);
            break;
            }
     }
     }
     if(!p->frenzy){
    if(p->bstream>=1){
       if(en!=NULL){
        for(int i=0;i<p->bstream;i++){
            for(int j=0;j<6;j++){   
            en[j]->hit(p->bullet[i],collision,detect);
            }
        }
        }
    }
    }
    else if(p->frenzy){
        if(p->fbstream>=1){
            if(en!=NULL){
                int k=0;
                for(int i=0;i<5;i++){
                    for(int j=0;j<p->fbstream;j++){
                    if(k==6){
                        k = 0;
                    }
                     en[k]->hit(p->frenzyBullet[i][j],collision,detect);
                     //scoring(en[k]);
                    k++;    
                    }
                }
            }
        }
    }
    }     
   }
    scoreset();
    levelUp(window);
	//////////////////////////////////////////////
    ////////////// sprite draws //////////////////
	window.clear(Color::Black); //clears the screen
	window.draw(background);  // setting background
    window.draw(points);
    window.draw(point);
    window.draw(pname);
    window.draw(rank);
    if(boss){
        if(framerate >=60){
            if(frameTrack >= 2){
                row = 0;
                frameTrack = 0;
            }
            if(row == 9){
                frame = (frame + 1)%3;
                frameTrack +=1;
            }
            else{
        frame = (frame + 1) % 5;
            }
            if(frame >= 4){
                row = (row + 1) % 10;
                frame = 0;
            }
        framerate = 0;
        }
    de->sprite1.setTextureRect(IntRect(300*frame,row*300,300,300));
    //de->firing = false;
    window.draw(de->sprite1);
    //frame = 0;
    if(de->bomb!=NULL){
       for(int i=0;i<3;i++){
        if(de->x==0){
        if(framerate2 >= 60){
        row2 = (row2 + 1) % 4;
        framerate2 = 0;
        }
        de->bomb[i].bul.setTextureRect(IntRect(0,286*row2,216,284));
        window.draw(de->bomb[i].bul);
       }
       else if(de->x==1 || de->x==2){
            if(framerate2 >= 60){
                frame2 = (frame2+1) % 5;
                 if(frame2 >=4){
                row2 = (row2+1)%2;
                frame = 0;
            }
             framerate2 = 0;
            }
           de->bomb[i].bul.setTextureRect(IntRect(frame2*93,84*row2,93,84));
           window.draw(de->bomb[i].bul);
       }
       }
    }
    }
    if(p->sheild){
        p->sprite.setTextureRect(IntRect(playerframe*93,0,93,91));
        window.draw(p->sprite);
        window.draw(p->shd);
    }
    else{
        if(blink){
            if(blinkSet >= 6){
                blink = false;
                blinkTimer = 0;
                blinkSet = 0;
            }
            else if(blinkTimer <= 30){
                    //dont draw ship.
            }
            else if(blinkTimer >= 30){
                p->sprite.setTextureRect(IntRect(playerframe*93,0,93,91));
                window.draw(p->sprite);
                blinkTimer = 0;
                blinkSet += 1;
            }
        }
        else {
   p->sprite.setTextureRect(IntRect(playerframe*93,0,93,91));
	window.draw(p->sprite);
    }   // setting player on screen
    }
    if(p->lives != NULL){
    for(int i=0;i<p->lifeCount;i++){
        window.draw(p->lives[i]);
    }
    }
      if(!mons && en != NULL && !boss){
        if(danger != NULL){
        if(meteor == true){
        window.draw(danger->sprite);
       }
       }
       for(int i=0;i<6;i++){
       if(en[i]->idx1 == 1){
        scoring(en[i]);
        en[i]->sprite1.setPosition(2000,800);
        continue;
       }
        else{
             window.draw(en[i]->sprite1); //draw enemy sprite.
             if(en[i]->bnum>=1){
               for(int j=0;j<en[i]->bnum;j++){
                    if(en[i]->bomb[j].hit){
                        en[i]->bomb[j].bul.setPosition(2000,300);
                        continue;
                    }
                    window.draw(en[i]->bomb[j].bul);
               }
             }
        }
       }
      }
    
      else if(!boss){
        window.draw(m->sprite1);
        if(m->bomb!=NULL){
        if(framerate3>=0.5){
            mbombFrame = (mbombFrame + 1)% 5;
            framerate3 = 0;
        }
        m->bomb->bul.setTextureRect(IntRect(mbombFrame*150,0,150,151));
        window.draw(m->bomb->bul);
        }
      }
      if(!p->frenzy){
    if(p->bstream>=1){
        for(int i=0;i<p->bstream;i++){
            if(p->bullet[i].hit && !p->red){
               p->bullet[i].bul.setPosition(2000,300);
                continue;
            }
         window.draw(p->bullet[i].bul);
        }
    }
    }
    if(p->frenzy){
        if(p->fbstream>=1){
            for(int i=0;i<7;i++){
                for(int j=0;j<p->fbstream;j++){
                    window.draw(p->frenzyBullet[i][j].bul);
                }
            }
        }
    }
      
    if(p->pw != NULL){
        window.draw(p->pw->power);
    }
	window.display();  //Displying all the sprites
    }

}
void Restart(){
    xpos = 270;
    ypos = 10;
    detect = 1;
    entity1 = 0;
    entity2 = 0;
    formation = 1;
    row = 0;
    frame = 0;
    frame2 = 0;
    row2 = 0;
    score = 0;
    lvl = 3;
    lvl1 = lvl2 = true;
    meteor = false;
    frameTrack = 0;
    eBombTime = 2;
    mBombTime = 4;
    lvlTime = 0;
    mTime = 0;
    pwTime = 0;
    shTime = 0;
    frTime = 0;
    drTime = 0;
    framerate =0;
    framerate2 = 0;
    dangerTime = 0;
    dangerEndTime = 0;
    framerate3 = 0;
    monsbDel = 0;
    monshitTimer = 0;
    Dragon = rand()%100 + 30;
    p->newLife();
    mons = false;
    boss = false;
     if(en !=NULL){
        for(int i=0;i<6;i++){
             en[i]->idx1 = 1;
        } 
     }
}
void timerReset(){
        lvlTime =0;
        timer =0;
        mTime =0;
        pwTime =0;
        shTime =0;
        drTime = 0;
        frTime = 0;
        framerate=0;
        framerate2=0;
        bossTimer=0;
        dangerTime=0;
        dangerEndTime=0;
        framerate3=0;
        monsbDel =0;
        monshitTimer =0;
        redTime =0;
}
 void animation(RenderWindow &window){
        losion.loadFromFile("exploshun.png");
        exp.setTexture(losion);
        exp.setScale(0.9,0.9);
        exp.setPosition(320,380);
        enleft.loadFromFile("enleft.png");
        enright.loadFromFile("enright.png");
        enl.setTexture(enleft);
        enr.setTexture(enright);
        enl.setPosition(-10,380);
        enr.setPosition(780,380);
        enl.setScale(0.6,0.6);
        enr.setScale(0.6,0.6);
        leevel.setPosition(240,290);
        levelnum.setPosition(480,290);
        Clock clock;
        float timer = 0;
        int exit = 0;
        int frame = 0;
        while(window.isOpen()){
            Event e;
           while (window.pollEvent(e))
           {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
           }
           window.clear(sf::Color::Black);
           enl.move(3.f,0);
           enr.move(-4.f,0);
            window.draw(background);
            window.draw(leevel);
            window.draw(levelnum);
           window.draw(enl);
           window.draw(enr);
           window.display();
            if(enl.getPosition().x < enr.getPosition().x + enr.getGlobalBounds().width && enl.getPosition().x + enl.getGlobalBounds().width > enr.getPosition().x && enl.getPosition().y < enr.getPosition().y + enr.getGlobalBounds().height && enl.getPosition().y + enl.getGlobalBounds().height > enr.getPosition().y){
				while(1){
                        float time = clock.getElapsedTime().asMilliseconds();
                        clock.restart();
                        timer+=time;
                        if(timer >=60){
                                frame = (frame + 1) % 7;
                                timer = 0;
                        }
                         window.clear(sf::Color::Black);
                        exp.setTextureRect(IntRect(frame*141,0,142,112));
                            window.draw(background);
                        window.draw(exp);
                       
                        window.display();
                        if(frame == 6){
                            exit = 1;
                            break;
                        }
                }
        }
        if(exit == 1){
            break;
        }
         
        }
 }
    void scoring(Enemy *e){
        if(e->dead == true){
      if(e->type == "alpha"){
        score = score + 30;
        e->dead = false;
      }
      else if(e->type == "beta"){
        score = score + 50;
        e->dead = false;
      }
      else if(e->type == "gamma"){
        score = score + 70;
        e->dead = false;
      }
    }
    }
    void scoreset(){
        scores = to_string(score);
        point.setString(scores);
    }
    void levelUp(RenderWindow &window){
        if(score >= 1000 && lvl1){
            lvl1 = false;
            lvl = 2;
            number = "2";
            levelnum.setString(number);
            animation(window);
        }
        if(score >= 2500 && lvl2){
            lvl2 = false;
            lvl = 1;
            number = "3";
            levelnum.setString(number);
            animation(window);
        }
    }
    void EnterName(RenderWindow &window){
        sf::Event event;
        Clock clock;
        float button = 0;
        while(window.isOpen()){
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            button+=time;
            while(window.pollEvent(event)){
                if(event.type == sf::Event::TextEntered){
                    if(event.text.unicode > 20 && event.text.unicode < 128){
                        playerName += (char)event.text.unicode;
                        
                       // cout<<playerName<<" "<<playerName.size()<<endl;
                        pname.setString(playerName);
                    }
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Enter) && button>=2){
                break;
            }
            window.clear(sf::Color::Black);
            window.draw(background);
            window.draw(enter);
            window.draw(pname);
            window.display();
        }
    }
};


