// 神話世界・西遊記・版本４．５０
/* <SecCrypt CPL V3R05> */
 
// xqc.c 小青菜

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("小青菜", ({"xqc", "xiaoqingcai"}));
   set_weight(40);
   if (clonep())
     set_default_object(__FILE__);
   else {
                set("long", "一顆新鮮可人的小青菜。\n");
                set("unit", "顆");
     set("value", 80);
     set("food_remaining", 4);
     set("food_supply", 30);
   }
}