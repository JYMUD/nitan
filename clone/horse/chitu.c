inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(NOR + RED "������" NOR, ({ "chitu ma"}));
        set("long", NOR + RED "�������£���̿��࣬�ް����ë����ͷ��β����һ�ɣ����������"
                              "�˳ߣ�˻�����������ڿ��뺣֮״��\n"
                              "������ʮ���꣬��������ǣ��������ܣ��ܽ���Ϊ��Ȩ�������������\n"
                              "����Ϊ��Ȩ�������ҡ��������ʳ���գ����ü�����\n" NOR);

        set("tili", 5000);
        set("max_tili", 5000);
        set("level", 4);

        set("can_go_any", 1);

        setup();
}
