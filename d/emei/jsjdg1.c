#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "��ʮ�ŵ���");
        set("long", @LONG
���Ǳ��������ġ���ʮ�ŵ��ա�����·����������ǧ�۰ٻء���
˵��ȥ���и�������ķ�ɮ���ˣ���һ������·������������������
�ǵ�֪�˴��о�����û�󣬱���Ҳ���˸�������Ĳ�ľ�����ԡ�����
����֮��������ǧ���֣�������϶���
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "westup"   : __DIR__"jsjdg2",
          "eastdown" : __DIR__"qianfoan",
      ]));
      set("coor/x", -480);
        set("coor/y", -240);
        set("coor/z", 110);
        set("coor/x", -480);
        set("coor/y", -240);
        set("coor/z", 110);
        setup();
}

int valid_leave(object me, string dir)
{
        int c_skill;

        me = this_player();
        if (dir == "westup")
        {
                c_skill = me->query_skill("dodge", 1);
                if( query("qi", me)>40 )
                {
                        me->receive_damage("qi", 20 + random(20));

                        if (me->can_improve_skill("dodge") && c_skill < 100)
                                me->improve_skill("dodge", 1 + c_skill / 15);

                        tell_object(me, HIC "�����Ͼ�ʮ�ŵ��գ���Щ���ˡ�\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "��̫���ˣ���Ҳ�߲����ˡ�\n" NOR);
                        return -1;
                }
      }
      return 1;
}