// regiser: prison.c
// by Doing

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "��ʮ�˲����" NOR);
        set("long", @LONG
���Ｋ����ɭ����е������Ĺ�굽���ε������������Ҳ����
͸һ�ڣ�ֻ��Ͽ��뿪���Ҳ��֪������������ã��뵽������
�����е�����İ��ա�
    �Ա���һ������(paizi)��
LONG );
        set("no_fight", 1);
        set("no_get_from", 1); 
        set("no_get", 1); 
        set("no_give", 1); 
        set("no_drop", 1); 
        set("item_desc", ([
                "paizi" : "��ʮ�˲���������뷭���Ǿ����ԣ�\n"
        ]));
}

void init()
{
        add_action("do_suicide", "suicide");
}

int do_suicide()
{
        write("����ڤ����Ҳ����ɱ��ʡʡ�ɣ�\n");
        return 1;
}

void catch_back(object me)
{
        message_vision(HIM "��Ȼһ����ص��������������ܣ������������"
               "��С�����˳�����һ��ץס$N" HIM "����\n������ס�����"
               "�ݵĽе������üһ��������...��\n\n" NOR,
               me);

        message("vision", HIY "����һ����⣬���ʱʲôҲ��������...\n\n"
                  HIM "��������ɢȥ... " + me->name() +
                  "�����ˣ�����\n\n" NOR,
                  environment(me), ({ me }));
}

void catch_ob(object me)
{
        message_vision(HIM "��Ȼһ����ص��������������ܣ������������"
                       "��С�����˳�����һ��ץס$N" HIM "����\n������ס�����"
                       "�ݵĽе�����վס���㷸���ˣ���������߰ɣ���\n\n" NOR,
                       me);

        message("vision", HIY "����һ����⣬���ʱʲôҲ��������...\n\n"
                          HIM "��������ɢȥ... " + me->name() +
                          "�����ˣ�����\n\n" NOR,
                          environment(me), ({ me }));
}

int free_ob(object me)
{
        string startroom;

        message_vision("��Ȼ����С��ð�˳�������ס$N���������ˣ������"
                       "���ˣ�Ҫ���ٸҷ������ߺ�...\n\n", me);
        message("vision", "����С���" + me->name() + "ͻȻ������ǰ��"
                          "ʧ��... �㲻��̾��һ������\n",
                          environment(me), ({ me }));

        tell_object(me, HIR "����ǰһ��...\n\n" NOR);

        if (me->is_ghost())
                startroom = "/d/death/gate";
        else
                startroom = "/d/city/wumiao";

        set("startroom", startroom, me);
        me->move(startroom);
        message("vision", "һ����ص��������ֻ��" + me->name() +
                          "ֱͦͦ�����ڵ��ϡ�\n", environment(me), ({ me }));
        return 1;
}
