// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("ũ��", ({ "nong fu", "nong", "fu" }));

        set("long", "һ����ͨ��ũ����������ûʲô������\n");

        set("gender", "Ů��");
        set("age", 23);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 121);

        
        set("inquiry", ([
                "�����ɵ�"               :   "����������ס�ڴˣ���δ���������塣\n",
        ]));
             
        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

void unconcious()
{
        die();
}
