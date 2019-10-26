#include "header1.h"
#include <cstdlib>
#include <ctime>

void LoadGameBack()
{
    SAMPLE*bullet_sound=load_wav("assets/audio/bullet_sound.wav");
    SAMPLE*game_music=load_wav("assets/audio/game_music.wav");
    play_sample(game_music,150,127,1000,1);
    BITMAP*game_back=load_bmp("assets/img/game_back.bmp",default_palette);
    BITMAP*pocisk=create_bitmap(1,20);
    clear_to_color(pocisk,makecol(255,0,255));
    BITMAP*buffer_game=create_bitmap(1024,768); //zmienna musi byc globalna
    BITMAP*P1=load_bmp("assets/img/model_P1.bmp",default_palette);
    BITMAP*P2=load_bmp("assets/img/model_P2.bmp",default_palette);
    int x1=400,y1=600;
    int x2=400,y2=60;
    float pos_back=6;
    while(!key[KEY_ESC])
    {

        if(x1<1) x1=1024; //wjezdzanie na ekran
        if(x1>1024) x1=1; // -|- dla P1
        if(y1>=717) y1-=7;

        if(x2<1) x2=1024;
        if(x2>1024) x2=1; // -|- dla P2
        if(y2<=0) y2+=7;

        //sterowanie dla P1
        if(key[KEY_UP])y1-=7;
        if(key[KEY_DOWN])y1+=7;
        if(key[KEY_LEFT])x1-=7;
        if(key[KEY_RIGHT])x1+=7;
        //sterowanie dla P2
            if(key[KEY_W])
                y2-=7;
            if(key[KEY_S])
                y2+=7;
            if(key[KEY_A])
                x2-=7;
            if(key[KEY_D])
                x2+=7;  //koniec sterowania


        //strzelanie



        masked_blit(game_back,buffer_game,0,0,0,0,game_back->w,game_back->h);

        blit( game_back, buffer_game, 0, 0, 0, - pos_back, game_back->w, game_back->h );
        blit( game_back, buffer_game, 0, 0, 0, game_back->h - pos_back, game_back->w, pos_back );
        pos_back+=1;
        if( pos_back == game_back->h )
        {
            pos_back = 1;
        }
        if(key[KEY_ENTER])
        {
        play_sample(bullet_sound,150,127,1000,0);

        for(int i=y1; i>1; --i)
        {
           if((x2||y2)==y1)
           {
               blit(pocisk,buffer_game,0,0,x1+50,y2,pocisk->w, pocisk->h);
           }

           blit(pocisk,buffer_game,0,0,x1+50,i,pocisk->w, pocisk->h);
        }}

        masked_blit(P1,buffer_game,0,0,x1,y1,P1->w,P1->h);
        masked_blit(P2,buffer_game,0,0,x2,y2,P2->w,P2->h);
        RtnPos_x_y(buffer_game,20,20);
        blit(buffer_game,screen,0,0,0,0,1024,768 );
    }

}END_OF_FUNCTION();

