
inherit ITEM;

void create()
{
	int i;
        object a;

        set_name("药盒", ({ "yao he" }) );
        set_weight(500);
        set_max_encumbrance(8000);
     set("value", 200000);
    if( clonep() )
          {
          seteuid(getuid());
          for (i=1;i<=99999;i++)  
            {
            a=new("/d/gaoli/obj/jinchuang");
            a->move(this_object());
            }
          set_default_object(__FILE__);
          }
        else 
          {
          set("unit", "个");
          set("long", "一个装药的盒子。\n");
          set("no_give", 1);
  set("no_sell",1);         }
}

int is_container() { return 1; }

