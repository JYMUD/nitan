#include <ansi.h>
//����ҩ��

inherit ITEM; 
mapping *ansi= ({
([     "yanse":    HIC,]),
([     "yanse":    HIG,]),
([     "yanse":    HIR,]),
([     "yanse":    HIB,]),
([     "yanse":    HIM,]),
([     "yanse":    HIY,]),
([     "yanse":    RED,]),
([     "yanse":    YEL,]), 
([     "yanse":    MAG,]),
([     "yanse":    CYN,]),

});
mapping *yao= ({
([     "name":     "�컨",
       "id":       "hong hua",
       "yaoxing":  100,
]),
([     "name":     "����",
       "id":       "ding xiang",
       "yaoxing":  200,
]),
([     "name":     "ľ��",
       "id":       "mu jin",
       "yaoxing":  300,
]),
([     "name":     "����",
       "id":       "lian hua",
       "yaoxing":  400,
]),
([     "name":     "������",
       "id":       "jinyin hua",
       "yaoxing":  500,
]),
([     "name":     "�ջ�",
       "id":       "ju hua",
       "yaoxing":  600,
]),
([     "name":     "�¼�",
       "id":       "yue ji",
       "yaoxing":  700,
]),
([     "name":     "��÷",
       "id":       "la mei",
       "yaoxing":  800,
]),
([     "name":     "����",
       "id":       "xin yi",
       "yaoxing":  900,
]),
});
void create()
{
    string name,id;
    int yaoxing,yaoo,yanse;

    yanse = random(sizeof(ansi));

    yaoo = random(sizeof(yao)); 

    name = yao[yaoo]["name"];

    id = yao[yaoo]["id"]; 

    yaoxing = yao[yaoo]["yaoxing"]; 

     //set_name(ansi[yanse]["yanse"]+name+NOR,({id}) );  
     set_name(name,({id}) );  

    set_weight(100);
    if( clonep() )
    set_default_object(__FILE__);
    else {
         set("unit", "��");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
   setup();
  }

