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
([     "name":     "����",
       "id":       "dan shen",
       "yaoxing":  1,
]),
([     "name":     "����",
       "id":       "dang shen",
       "yaoxing":  2,
]),
([     "name":     "����",
       "id":       "dang gui",
       "yaoxing":  3,
]),
([     "name":     "�˲�",
       "id":       "ren shen",
       "yaoxing":  4,
]),
([     "name":     "����",
       "id":       "bai zhi",
       "yaoxing":  5,
]),
([     "name":     "����",
       "id":       "san qi",
       "yaoxing":  6,
]),
([     "name":     "��",
       "id":       "mai dong",
       "yaoxing":  7,
]),
([     "name":     "���",
       "id":       "chai hu",
       "yaoxing":  8,
]),
([     "name":     "�ʲ�",
       "id":       "gan cao",
       "yaoxing":  9,
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

