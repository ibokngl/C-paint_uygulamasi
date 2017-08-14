#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include <stdio.h>


void ucgenciz();
void cizgiciz();
void renkler();
void renksec();
void baslik();
void dortgenciz();
void kalem();
void kalem2();
void cemberciz();
void silgi();
void silgi2();
void tumunusil();
void yeni();


const int SCREEN_W = 800;
const int SCREEN_H = 640;


bool select1=false;
bool select2=false;
bool select3=false;
bool select4=false;
bool select5=false;
bool select6=false;

bool penstate=false;
bool eraserstate=false;


    ALLEGRO_BITMAP  *bitmap,*copy;
    ALLEGRO_FONT *font_ttf=NULL;
    ALLEGRO_EVENT event; 
    ALLEGRO_DISPLAY *display;
    ALLEGRO_COLOR colorselect;
    ALLEGRO_KEYBOARD_STATE keyboard;
    ALLEGRO_MOUSE_STATE state;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

      unsigned char r=0;
      unsigned char g=0;
      unsigned char b=0;

const int FPS=60;

int main()
{
   
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_BITMAP  *pencil   = al_load_bitmap( "media/edit.png" );
    ALLEGRO_BITMAP  *line   = al_load_bitmap( "media/substract.png" );
    ALLEGRO_BITMAP  *rectangle   = al_load_bitmap( "media/shape.png" );
    ALLEGRO_BITMAP  *circle   = al_load_bitmap( "media/oval.png" );
    ALLEGRO_BITMAP  *triangle   = al_load_bitmap( "media/triangle.png" );
    ALLEGRO_BITMAP  *eraser   = al_load_bitmap( "media/eraser.png" );
    ALLEGRO_BITMAP  * kursor   = al_load_bitmap("media/kursor.png");
    ALLEGRO_BITMAP  * screen   = al_load_bitmap("media/screen.png");
    
    
    
    display=al_create_display(SCREEN_W,SCREEN_H);
    bitmap=al_create_bitmap(SCREEN_W,SCREEN_H);
    
     
    ALLEGRO_MOUSE_CURSOR * cursor = al_create_mouse_cursor( kursor, 0, 0);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    al_set_window_title( display,"Paint");
    font_ttf = al_load_ttf_font("courbd.ttf",18,ALLEGRO_TTF_NO_KERNING);
    
         al_draw_filled_rectangle(0, 0,60, 640,al_map_rgb(255,255,178));
         al_draw_filled_rectangle(60, 0,800,30,al_map_rgb(255,255,178)); 
         al_draw_rectangle(12, 120,49,340,al_map_rgb(0,0,0),2); 
       
         al_draw_bitmap (pencil, 18, 130, 0);
         al_draw_bitmap (line, 18, 160, 0);
         al_draw_bitmap (rectangle, 18, 190, 0);
         al_draw_bitmap (circle, 18, 230, 0);
         al_draw_bitmap (triangle, 18, 270, 0);
         al_draw_bitmap (eraser, 18, 310, 0);
         al_draw_bitmap (screen,60,30,0);
        
         //Renk paleti
             renkler();
             
         //Üst kısım
     al_draw_textf(font_ttf,al_map_rgb(0,0,0),10,5,0,"Yeni |"),  al_draw_textf(font_ttf,al_map_rgb(0,0,0),85,5,0,"Ac |"),
     al_draw_textf(font_ttf,al_map_rgb(0,0,0),138,5,0,"Kaydet |"), al_draw_textf(font_ttf,al_map_rgb(0,0,0),235,5,0,"Tumunu sil |");     
  
    int x=0,y=0,x2=0,y2=0,flag=0;
    bool start=true;
    
  while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))
    {
        al_wait_for_event(event_queue, &event);
        al_get_keyboard_state(&keyboard); 
        


         renksec();
         tumunusil();
         cizgiciz();
         dortgenciz();  
         silgi();
         ucgenciz();
         cemberciz();
         kalem(); 
         yeni();    
         
      if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        { return 0; }

   
      if(event.mouse.x>=60 && event.mouse.x <800 && event.mouse.y>=30 && event.mouse.y<640)
        {  
            
            if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN )
            {
                if(event.mouse.button&1)
                {
                penstate=true;
                eraserstate=true;
                }
                x=event.mouse.x;
                y=event.mouse.y;

            }
              
            if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
            {
                x2=event.mouse.x;
                y2=event.mouse.y;
                penstate=false;
                eraserstate=false;

  
                 if(select1)
                 al_draw_rectangle(x,y,x2,y2,al_map_rgb(r,g,b),2);
                 
                 if(select3)
                 al_draw_line(x,y,x2,y2,al_map_rgb( r, g, b), 2);
                 float ratio=sqrt((x-event.mouse.x)*(x-event.mouse.x)+ (y-event.mouse.y)*(y-event.mouse.y));
                 
                 if(select4)
                 al_draw_circle(x,y,ratio,al_map_rgb( r, g, b), 2);
                         
                 if(select5)
                 {
                    if(x2>x && y<y2)
                    al_draw_triangle(x,y,x2,y2,(2*x-x2),y2,al_map_rgb(r,g,b),2); 
                    else if(x2<x && y<y2)
                    al_draw_triangle(x,y,(2*x-x2),y2,x2,y2,al_map_rgb(r,g,b),2); 
                    else if(x2>x && y>y2)
                    al_draw_triangle(x2,y2,(2*x2-x),y,x,y,al_map_rgb(r,g,b),2); 
                    else if(x2<x && y>y2)
                    al_draw_triangle(x2,y2,x,y,(2*x2-x),y,al_map_rgb(r,g,b),2); 
                 }
             
            }

             if(select2)   
             kalem2(penstate);
             
              
             if(select6)
             silgi2(eraserstate);
  
    }
      if(event.mouse.x>=130 && event.mouse.x<220 && event.mouse.y>=0 && event.mouse.y<20  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
       al_save_bitmap("media/resimm.png",al_get_backbuffer(display)); 
       
       } 
     if(event.mouse.x>=85 && event.mouse.x<120 && event.mouse.y>=0 && event.mouse.y<20  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
       ALLEGRO_BITMAP  * resim   = al_load_bitmap("media/resimm.png");
       al_draw_bitmap (resim,0,0,0); 
       } 
         
         al_flip_display();   
        
    }
 
    al_destroy_bitmap(bitmap);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}

void cizgiciz()
{
     if(event.mouse.x>=12 && event.mouse.x<49 && event.mouse.y>=160 && event.mouse.y<180  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
    select3=true;
    select1=false;
    select2=false;
    select4=false;
    select5=false;
    select6=false;
    }
  
         
}

void dortgenciz()
{
    if(event.mouse.x>=12 && event.mouse.x<49 && event.mouse.y>=190 && event.mouse.y<210  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
    select1=true;
    select2=false;
    select3=false;
    select4=false;
    select5=false;
    select6=false;
    }
  
}
 void kalem()
{    
    if(event.mouse.x>=12 && event.mouse.x<49 && event.mouse.y>=130 && event.mouse.y<155  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
    select2=true;
    select1=false;
    select3=false;
    select4=false;
    select5=false;
    select6=false;
    }
    
}

void kalem2(int option)
{
 if(option)  
    al_draw_filled_rectangle(event.mouse.x,event.mouse.y,event.mouse.x+4,event.mouse.y+4,al_map_rgb(r,g,b)); 
     
}

void cemberciz()
{
    if(event.mouse.x>=12 && event.mouse.x<49 && event.mouse.y>=230 && event.mouse.y<260  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
    select4=true;
    select1=false;
    select2=false;
    select3=false;
    select5=false;
    select6=false;
    }
}

void ucgenciz()
{
    if(event.mouse.x>=12 && event.mouse.x<49 && event.mouse.y>=270 && event.mouse.y<300  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
    select5=true;
    select1=false;
    select2=false;
    select3=false;
    select4=false;
    select6=false;
    }
    
}

void silgi()
{
 if(event.mouse.x>=12 && event.mouse.x<49 && event.mouse.y>=310 && event.mouse.y<340  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
    select6=true;
    select1=false;
    select2=false;
    select3=false;
    select4=false;
    select5=false;
    }   
}

void silgi2(int option)
{

    if(option)
    {
     al_draw_filled_rectangle(event.mouse.x,event.mouse.y,event.mouse.x+100,event.mouse.y+100,al_map_rgb(255,255,255)); 
    }
}


void renkler()
{

      al_draw_filled_rectangle( 20, 390, 40, 410, al_map_rgb(150,0,100)); 
      al_draw_filled_rectangle( 20, 420, 40, 440, al_map_rgb(255,0,0)); //RED 
      al_draw_filled_rectangle( 20, 450, 40, 470, al_map_rgb(0,255,0)); //GREEN 
      al_draw_filled_rectangle( 20, 480, 40, 500, al_map_rgb(0,0,255)); //BLUE 
      al_draw_filled_rectangle( 20, 510, 40, 530, al_map_rgb(240,240,0)); 
      al_draw_filled_rectangle( 20, 540, 40, 560, al_map_rgb(255,0,255));
      al_draw_filled_rectangle( 20, 570, 40, 590, al_map_rgb(0,0,0)); 
}

void renksec()
{
    
 if(event.mouse.x>20 && event.mouse.x<40 && event.mouse.y>390 && event.mouse.y<410 && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN   )
 {
          r=150;
          g=0;
          b=100;
       
 }   
      
         
 if(event.mouse.x>=20 && event.mouse.x<40 && event.mouse.y>=420 && event.mouse.y<440  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      {

          r=255;
          g=0;
          b=0;
       
      }  
 if(event.mouse.x>=20 && event.mouse.x<40 && event.mouse.y>=450 && event.mouse.y<470  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      {

          r=0;
          g=255;
          b=0;
       
      }  
 if(event.mouse.x>=20 && event.mouse.x<40 && event.mouse.y>=480 && event.mouse.y<500  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      {

          r=0;
          g=0;
          b=255;
       
      }  
 if(event.mouse.x>=20 && event.mouse.x<40 && event.mouse.y>=510 && event.mouse.y<530  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      {

          r=240;
          g=240;
          b=0;
       
      } 
 if(event.mouse.x>=20 && event.mouse.x<40 && event.mouse.y>=540 && event.mouse.y<560  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      {

          r=255;
          g=0;
          b=255;
      }
 if(event.mouse.x>=20 && event.mouse.x<40 && event.mouse.y>=570 && event.mouse.y<590  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      {

          r=0;
          g=0;
          b=0;
       
      } 
     
     
}

void tumunusil()
{
 if(event.mouse.x>=225 && event.mouse.x<360 && event.mouse.y>=0 && event.mouse.y<20  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      al_draw_filled_rectangle( 60, 30, 800, 640, al_map_rgb(255,255,255));
}

void yeni()
{
 if(event.mouse.x>=10 && event.mouse.x<70 && event.mouse.y>=0 && event.mouse.y<20  && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      al_draw_filled_rectangle( 60, 30, 800, 640, al_map_rgb(255,255,255));
}








