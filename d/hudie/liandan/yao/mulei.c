#include <ansi.h>
//ľ��ҩ��

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
([     "name":     "����",
       "id":       "du zhong",
       "yaoxing":  1000,
]),
([     "name":     "����",
       "id":       "wu jiu",
       "yaoxing":  2000,
]),
([     "name":     "��ľ",
       "id":       "zhang mu",
       "yaoxing":  3000,
]),
([     "name":     "����",
       "id":       "hou pu",
       "yaoxing":  4000,
]),
([     "name":     "��ľ",
       "id":       "su mu",
       "yaoxing":  5000,
]),
([     "name":     "����",
       "id":       "chen xiang",
       "yaoxing":  6000,
]),
([     "name":     "��ľ",
       "id":       "ku mu",
       "yaoxing":  7000,
]),
([     "name":     "̴��",
       "id":       "tan xiang",
       "yaoxing":  8000,
]),
([     "name":     "�ư�",
       "id":       "huang bai",
       "yaoxing":  9000,
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

