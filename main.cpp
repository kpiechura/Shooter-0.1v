#include <allegro.h>
#include <winalleg.h>
#include "header1.h"

void DestrArray(int num,BITMAP*array[]);

void ClearArray(int num,BITMAP*array[]);

void RtnPos_x_y(BITMAP*bmp,int x,int y)
{textprintf_ex(bmp, font, x, y, makecol( 200, 200, 200 ), - 1, "Pos_x = %d, Pos_y = %d, Butt = %d", mouse_x, mouse_y, mouse_b );}

void BMPLoad(BITMAP*bmp);

void BMPLoadArray(BITMAP*bmp[],int ele);

int main(int argc,char*argvc[])
{
    allegro_init();
    set_window_title("Qoma");
    install_keyboard(); install_mouse(); install_timer();
    install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );
    set_volume( 255, 255 );
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0);
    set_palette(default_palette);
    clear_bitmap(screen);

    SAMPLE*click=load_sample("menu_click.wav");
    if(!click)
    {set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "ERROR: Program can't load sound." );
    allegro_exit();
    return 0;}

    SAMPLE*menu_music=load_wav("menu_music.wav");
    if(!menu_music)
    {set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "ERROR: Program can't load sound." );
    allegro_exit();
    return 0;}

    BITMAP*buffer=create_bitmap(1024,768);
    if(!buffer)
        {set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "ERROR: Program can't create buffer." );
        allegro_exit();
        return 0;}
    //BITMAPS for menu
    BITMAP*str_s[4];
    BITMAP*m_back=load_bmp("m_background.bmp",default_palette);
        str_s[0]=load_bmp("m_str1.bmp",default_palette);
        str_s[1]=load_bmp("m_str2.bmp",default_palette);
        str_s[2]=load_bmp("m_str3.bmp",default_palette);
        str_s[3]=load_bmp("m_str4.bmp",default_palette);
    BMPLoadArray(str_s,4);

    BITMAP*title=load_bmp("m_title.bmp",default_palette); BMPLoad(title);
    BITMAP*str_ver=load_bmp("m_ver.bmp",default_palette); BMPLoad(str_ver);
    //BITMAPS for options_front
    BITMAP*texts[2];
        texts[0]=load_bitmap("o_controls.bmp",default_palette);
        texts[1]=load_bitmap("o_sound.bmp",default_palette);
    BMPLoadArray(texts,2);
    //BITMAPS for credits
    BITMAP*_credits[5];
        _credits[0]=load_bmp("c_str1.bmp",default_palette);
        _credits[1]=load_bmp("c_str2.bmp",default_palette);
        _credits[2]=load_bmp("c_str3.bmp",default_palette);
        _credits[3]=load_bmp("c_author.bmp",default_palette);
        _credits[4]=load_bmp("c_reserved.bmp",default_palette);
    BMPLoadArray(_credits,5);
    //BITMAPS for options -> controls
    BITMAP*move_P1=load_bitmap("control_P1_move.bmp",default_palette); BMPLoad(move_P1);
    BITMAP*P1_str=load_bitmap("P1_str.bmp",default_palette); BMPLoad(P1_str);
    BITMAP*P2_str=load_bitmap("P2_str.bmp",default_palette); BMPLoad(P2_str);
    BITMAP*shoot_str=load_bitmap("control_shoot.bmp",default_palette); BMPLoad(shoot_str);
    BITMAP*move_P2=load_bitmap("control_P2_move.bmp",default_palette); BMPLoad(move_P2);
    BITMAP*move_str=load_bitmap("control_move.bmp",default_palette); BMPLoad(move_str);
    BITMAP*space_bmp=load_bitmap("control_P1_shoot.bmp",default_palette); BMPLoad(space_bmp);
    BITMAP*shift_bmp=load_bitmap("control_P2_shoot.bmp",default_palette); BMPLoad(shift_bmp);
    //BITMAPS for 'exit'
    BITMAP*exit_que=NULL;
    BITMAP*exit_str[2];
    ClearArray(2,exit_str);
     //loading menu
    show_mouse(screen);
    play_sample(menu_music,255,127,1000,1);
    bool pointer=true;
    back:
    while(!key[KEY_ESC])
    {
        blit(m_back,buffer,0,0,0,0,m_back->w,m_back->h);
        masked_blit(str_s[0],buffer,0,0,400,200,str_s[0]->w,str_s[0]->h);
        masked_blit(str_s[1],buffer,0,0,400,285,str_s[1]->w,str_s[1]->h);
        masked_blit(str_s[2],buffer,0,0,400,370,str_s[2]->w,str_s[2]->h);
        masked_blit(str_s[3],buffer,0,0,400,455,str_s[3]->w,str_s[3]->h);
        masked_blit(title,buffer,0,0,200,220,title->w,title->h);
        masked_blit(str_ver,buffer,0,0,1000,755,str_ver->w,str_ver->h);
        vline(buffer,350,200,490,makecol(255,255,255));
        textprintf_ex(buffer, font, 20, 20, makecol( 200, 200, 200 ), - 1, "Pos_x = %d, Pos_y = %d, Butt = %d", mouse_x, mouse_y, mouse_b );
        blit( buffer, screen, 0, 0, 0, 0, 1024, 768 );
        clear_bitmap(buffer);
        if(mouse_x>400 && mouse_x<610 && mouse_y>200 && mouse_y<230 && mouse_b==true)
        {
            play_sample( click, 255, 127, 1000, 0 );
            clear_bitmap(screen); clear_bitmap(buffer);
            scare_mouse();
            stop_sample(menu_music);
            LoadGameBack();
            break;
        }
        if(mouse_x>400 && mouse_x<525 && mouse_y>285 && mouse_y<315 && mouse_b==true)
        {
            clear_keybuf();
            play_sample( click, 255, 127, 1000, 0 );
            while(keypressed()==false)
            {
                clear_bitmap(buffer);
                blit(m_back,buffer,0,0,0,0,m_back->w,m_back->h);
                hline(buffer,160,345,400,makecol(255,255,255));
                blit(texts[0],buffer,0,0,160,270,texts[0]->w,texts[0]->h);
                blit(texts[1],buffer,0,0,160,380,texts[1]->w,texts[1]->h);
                masked_blit(str_ver,buffer,0,0,1000,755,str_ver->w,str_ver->h);
                RtnPos_x_y(buffer,20,20);
                blit(buffer,screen, 0, 0, 0, 0, 1024, 768 );
                    if(mouse_x>160 && mouse_x<350 && mouse_y>270 && mouse_y<305 && mouse_b==true)
                    {
                        play_sample( click, 255, 127, 1000, 0 );
                        clear_keybuf();
                        while(keypressed()==false)
                        {
                            clear_bitmap(buffer);
                            masked_blit(str_ver,buffer,0,0,1000,755,str_ver->w,str_ver->h);
                            blit(m_back,buffer,0,0,0,0,m_back->w,m_back->h);
                            hline(buffer,250,395,500,makecol(255,255,255));
                            blit(P1_str,buffer,0,0,315,80,P1_str->w,P1_str->h);
                            blit(P2_str,buffer,0,0,315,445,P2_str->w,P2_str->h);
                            blit(shoot_str,buffer,0,0,355,300,shoot_str->w,shoot_str->h);
                            blit(move_P1,buffer,0,0,30,140,move_P1->w,move_P1->h);
                            blit(move_P2,buffer,0,0,350,530,move_P2->w,move_P2->h);
                            blit(shoot_str,buffer,0,0,70,690,shoot_str->w,shoot_str->h);
                            blit(move_str,buffer,0,0,415,690,move_str->w,move_str->h);
                            blit(space_bmp,buffer,0,0,260,210,space_bmp->w,space_bmp->h);
                            blit(shift_bmp,buffer,0,0,50,600,shift_bmp->w,shift_bmp->h);
                            blit(move_str,buffer,0,0,85,300,move_str->w,move_str->h);
                            RtnPos_x_y(buffer,20,20);
                            blit(buffer,screen,0,0,0,0,1024,768);
                        }
                    }
                       if(mouse_x>160 && mouse_x<350 && mouse_y>380 && mouse_y<420 && mouse_b==true)
                        {
                           if(pointer==true)
                                stop_sample(menu_music);
                            if(pointer==false){
                                play_sample(menu_music,255,127,1000,1);
                            pointer=false;
                            }
                        }

            }

        }
        if(mouse_x>400 && mouse_x<525 && mouse_y>370 && mouse_y<400 && mouse_b==true)
        {
            clear_keybuf();
            play_sample( click, 255, 127, 1000, 0 );
            do{
                clear_bitmap(buffer);
                masked_blit(m_back,buffer,0,0,0,0,m_back->w,m_back->h);
                rect(buffer,250,330,515,600,makecol(0,0,255));
                hline(buffer,250,415,515,makecol(255,255,255));
                hline(buffer,250,515,515,makecol(255,255,255));
                hline(buffer,1,748,290,makecol(255,255,255));
                blit(_credits[0],buffer,0,0,280,355,_credits[0]->w,_credits[0]->h); //jakas petla moze?
                blit(_credits[1],buffer,0,0,310,455,_credits[1]->w,_credits[1]->h);
                blit(_credits[2],buffer,0,0,330,555,_credits[2]->w,_credits[2]->h);
                blit(_credits[3],buffer,0,0,250,195,_credits[3]->w,_credits[3]->h);
                blit(_credits[4],buffer,0,0,1,755,_credits[4]->w,_credits[4]->h);
                masked_blit(str_ver,buffer,0,0,1000,755,str_ver->w,str_ver->h);
                RtnPos_x_y(buffer,20,20);
                blit( buffer, screen, 0, 0, 0, 0, 1024, 768 );
            }while(keypressed()==false);
        }
        if(mouse_x>400 && mouse_x<470 && mouse_y>455 && mouse_y<485 && mouse_b==true)
        {
            play_sample( click, 255, 127, 1000, 0 );
            while(!key[KEY_ESC])
            {
                masked_blit(m_back,buffer,0,0,0,0,m_back->w,m_back->h)
                exit_que=load_bmp("m_exit_que.bmp",default_palette);
                exit_str[0]=load_bmp("m_exit_yes.bmp",default_palette);exit_str[1]=load_bmp("m_exit_no.bmp",default_palette);
                blit(exit_que,buffer,0,0,230,250,exit_que->w,exit_que->h);
                blit(exit_str[0],buffer,0,0,100,350,exit_str[0]->w,exit_str[0]->h);
                blit(exit_str[1],buffer,0,0,520,350,exit_str[1]->w,exit_str[1]->h);
                masked_blit(str_ver,buffer,0,0,1000,755,str_ver->w,str_ver->h);
                textprintf_ex(buffer, font, 20, 20, makecol( 200, 200, 200 ), - 1, "Pos_x = %d, Pos_y = %d, Butt = %d", mouse_x, mouse_y, mouse_b );
                  blit( buffer, screen, 0, 0, 0, 0, 1024, 768 );
                if(mouse_x>100 && mouse_x<180 && mouse_y>350 && mouse_y<390 && mouse_b==true)
                    exit(0);
                if(mouse_x>520 && mouse_x<570 && mouse_y>350 && mouse_y<390 && mouse_b==true)
                {
                    play_sample( click, 255, 127, 1000, 0 );
                    goto back;
                }
            }
        }
        if(mouse_x>205 && mouse_x<295 && mouse_y>225 && mouse_y<465 && mouse_b==true)
            system("start www.kpigames.hpu.pl"); //program muli jak sie kliknie na to pole
    }
    readkey();
    destroy_sample(click);
    destroy_bitmap(m_back);
    DestrArray(4,str_s); DestrArray(5,_credits);
    DestrArray(2,texts); DestrArray(2,exit_str);
    destroy_bitmap(move_P1);
    destroy_bitmap(P1_str); destroy_bitmap(P2_str);
    destroy_bitmap(shoot_str); destroy_bitmap(move_P2);
    destroy_bitmap(title);  destroy_bitmap(move_str);
    destroy_bitmap(space_bmp); destroy_bitmap(shift_bmp);
    destroy_bitmap(str_ver); destroy_bitmap(exit_que);
    destroy_bitmap(buffer);
    remove_keyboard(); remove_mouse();
    allegro_exit();
    return 0;
}END_OF_MAIN();

void DestrArray(int num,BITMAP*array[])
{for(int i=0; i<num;++i)
        destroy_bitmap(array[i]);
}END_OF_FUNCTION();

void ClearArray(int num,BITMAP*array[])
{for(int i=0;i<num;++i)
        array[i]=NULL;
}END_OF_FUNCTION();

void BMPLoad(BITMAP*bmp)
{
    if(!bmp)
        {set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "ERROR: Program can't load bitmap." );
        allegro_exit();
        return;}
}
void BMPLoadArray(BITMAP*bmp[],int ele)
{
    for(int i=0;i<ele;++i)
    {
        if(!bmp[i])
        {set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "ERROR: Program can't load bitmap." );
        allegro_exit();
        return;}
    }
}
