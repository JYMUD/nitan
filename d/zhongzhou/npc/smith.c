#include <ansi.h>

inherit SMITH;

void create()
{
        set_name("����", ({ "tiejiang", "smith" }));
        set("title", "���е��ϰ�");
        set("shen_type", 1);
        set("gender", "����" );
        set("age", 33);
        set("long", "����������ǯ��סһ����ȵ�����Ž�¯�С�\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                   __DIR__"obj/armor",
                   __DIR__"obj/beixin",
                   "/d/city/npc/obj/jinsijia",
        }));

        setup();

        carry_object("/clone/misc/cloth")->wear();
}