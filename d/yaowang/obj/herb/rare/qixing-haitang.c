#include "herb.h" 
void create() 
  {
      set_name(NOR + HIY "���Ǻ���" NOR, ({ "qixing haitang", "qixing", "haitang","herb_qixing-haitang" })); 
          if (clonep())      
                 set_default_object(__FILE__); 
          else { 
                  set("long", NOR + HIG "���껨��Ҷ��Ҳ��Ѱ���������죬�������֦�ɶ�������֦���������������߸�СС�ĻƵ㡣\n" NOR); 
                  set("base_unit", "��");
                  set("base_value", 5000); 
                  set("base_weight", 20);
               }
               setup();
  }
