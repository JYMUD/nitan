inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(NOR + MAG "������" NOR, ({ "wuzhui ma"}));
        set("long", NOR + MAG "�������������ëֱ����ͨ���ԣ������ޱȡ�\n"
                              "��������������һֱ������������ս��������ѫ������\n"
                              "�����ڽ���ɱ�󣬽����������͸���ͤ����ͤ������������������������\n"
                              "�˵����������ڽ�������\n" NOR);

        set("tili", 3000);
        set("max_tili", 3000);
        set("level", 3);

        setup();
}
