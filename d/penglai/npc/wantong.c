// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("��ͯ", ({ "wan tong", "wan", "tong" }));

        set("long", "һ���ɰ�����ͯ�������ޱȡ�\n");
        
        set("gender", random(2) ? "Ů��" : "����");
        set("age", 6);
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
                "�����ɵ�"               :   "����������˵��ʲôѽ������ôû��������������\n",
        ]));
             
        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

void unconcious()
{
        die();
}
