#include <ansi.h>

inherit ITEM;
inherit F_UNIQUE;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_get","你手里一松，奖励丹从指间滑落！\n");
    set("no_give","这么珍贵的药，哪能随便给人？\n");
    set("no_drop","这么宝贵的丹药，扔了多可惜呀！\n");
  set("no_put","每个人只有一个，你都这么大方！\n");
    set("no_sell","凡人哪里知道"+this_object()->query("name")+"的价值？还是自己留着吧。\n");
  }
  add_action("do_eat", "eat");
}

void create()
{
  set_name( GRN "奖励丹" NOR , ({"jiangli dan", "dan"}));
  set_weight(90);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "颗");
    set("long", "一颗金黄色的丹丸，略微能闻到些许香气。\n");
    set("value", 0);
    set("drug_type", "补品");
  }
  set("is_monitored",1);
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="dan" && arg!="qn dan")   return 0;
  
 
   me->add("potential",300000);  
   me->add("daoxing",5000000);  
  message_vision(HIG "$N轻轻掰开一颗奖励丹送入嘴中，一时间香气四溢。
只见$N脸上慢慢泛出红晕，看起来有精神多了！\n" NOR, me);
  destruct(this_object());
  return 1;
}

