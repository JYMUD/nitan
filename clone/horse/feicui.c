inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIG "����" NOR, ({ "feicui ju"}));
        set("long", HIG "��˵���Բ����Ĵ�������������\n" NOR);

        set("tili", 1000);
        set("max_tili", 1000);
        set("level", 1);

        setup();
}
