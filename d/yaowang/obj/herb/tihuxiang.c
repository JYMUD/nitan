#include "herb.h" 
void create() 
  {
      set_name(NOR + HIW "������" NOR, ({ "tihu xiang", "tihu", "xiang","herb_tihuxiang" })); 
          if (clonep())      
                 set_default_object(__FILE__); 
          else { 
                  set("long", NOR + HIW "һ���ɫ��С������������Ũ�ҵ�����������\n" NOR); 
                  set("base_unit", "��");
                  set("base_value", 50); 
                  set("base_weight", 20);
               }
               setup();
  }