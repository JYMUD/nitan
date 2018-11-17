// wangbofen.c

#include <ansi.h>

inherit NPC;
void create()
{
        set_name("王伯奮", ({ "wang bofen", "wang", "bofen" }) );
        set("title", HIY"金刀門"NOR"第四代弟子");
        set("gender", "男性" );
        set("shen_type", 1);
        set("age", 45);
        set("per", 15);
        set("str", 25);
        set("con", 25);
        set("dex", 25);
        set("int", 25);
        set("long",
"他是金刀無敵王元霸的長子，武功盡得乃父真傳。看起來身材甚高，太陽穴
高高鼓起，手上筋骨突出，顯然內外功造詣都甚了得。\n" );
        set("combat_exp", 300000);
        set("attitude", "friendly");
        set_skill("blade", 100);
        set_skill("dodge", 100);
        set_skill("unarmed", 100);
        set_skill("jinwu-blade", 100);
        set_skill("yanfly", 100);
        set_skill("parry", 100);
        map_skill("blade", "jinwu-blade");
        map_skill("parry", "jinwu-blade");
        map_skill("dodge", "yanfly");

        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(CLOTH_DIR"jinduan")->wear();
        add_money("gold", 2);
}
