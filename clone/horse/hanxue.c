inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(MAG "��Ѫ����" NOR, ({ "hanxue baoju", "hanxue", "baoju"}));
        set("long", HIR "���ϴ������������������ɣ�����ϥ��βί�ڵأ���\n"
                        "�纹������ա�����ǧ������ж���Ѫ\n" NOR);
        set("tili", 10000);
        set("max_tili", 10000);
        set("level", 5);

        set("can_go_any", 1);

        setup();
}
