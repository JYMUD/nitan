inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(NOR + YEL "����Ұ��" NOR, ({ "pushi yema"}));
        set("long", NOR + YEL "�������½�������Ұ��һСʱ�ɱ�����ʮ�����������������Сʱ��������\n" NOR);

    set("tili", 5000);
        set("max_tili", 5000);
        set("level", 2);

        setup();
}
