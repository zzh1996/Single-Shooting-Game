#include "headers.h"

void Game::update_state() {
    if (Up)
        if(self.Y>0)
            self.Y -= planeSpeed;
    if (Down)
        if(self.Y+self.H<600)
            self.Y += planeSpeed;
    if (Left)
        if(self.X>0)
            self.X -= planeSpeed;
    if (Right)
        if(self.X+self.W<600)
            self.X += planeSpeed;
    if (Space){
        if(AmmoCoolDownCount==0) {
            shoot();
            AmmoCoolDownCount = AmmoCoolDown;
        }else
            AmmoCoolDownCount--;
    }
    for(auto i=self_ammos.begin();i!=self_ammos.end();){
        i->Y-=AmmoSpeed;
        if(i->out_of_screen()) {
            i = self_ammos.erase(i);
        }else
            i++;
    }
    for(auto i=enemies.begin();i!=enemies.end();){
        Enemy *e=*i;
        bool del=false;
        e->move();
        if(e->collides(self)) {
            decrease_life();
            e->HP-=10;
            if(e->HP<=0)
                del=true;
        }
        for(auto a=self_ammos.begin();a!=self_ammos.end();){
            if(e->collides(*a)){
                a = self_ammos.erase(a);
                e->HP--;
                if(e->HP<=0) {
                    score+=e->score;
                    del=true;
                    break;
                }
            }
            a++;
        }
        if((*i)->out_of_screen()) {
            del=true;
        }
        if(del){
            delete *i;
            i = enemies.erase(i);
        }else
            i++;
    }
    if(rand()%100<2)
        enemies.push_back(new MovingEnemy());
}

void Game::shoot(){
    self_ammos.push_back(Ammo(self.X+self.W/2-5,self.Y));
}

void Game::decrease_life(){
    life--;
    if(life==0){
        gameover();
    }
}

void Game::gameover(){

}