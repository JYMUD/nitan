// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
       set("short","��ɳĮ");
        set("long", @LONG
����һƬһ���޼ʵĴ�ɳĮ����һ��������ʧ�˷��򡣿���Ҫ��
�����ɳĮ�������¡�
LONG );
        set("exits", ([
                "east" : __FILE__,
                "west" : __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));

        set("outdoors", "xiyu");
        set("no_map", "����ĵ��������������޴����ֻ��Ƶ�ͼ��\n");

        setup();
}

int valid_leave(object me, string dir)
{
        int water, food;
        int qi, jing;
        string dest;

        if (playerp(me))
        {
                if( !objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
                {
                water=query("water", me);
                food=query("food", me);
                water -= (random(2) + 1) * water / 20 + 5;
                food -= (random(2) + 1) * food / 20 + 5;
                if (water < 0) water = 0;
                if (food < 0) food = 0;
                set("water", water, me);
                set("food", food, me);
                }

                qi=query("max_qi", me)*5/100+random(10);
                jing=query("max_jing", me)*5/100+random(10);

                if( query("qi", me)<qi || query("jing", me)<jing )
                {
                        write("���Ѿ��е������ˣ�ڤڤ����������˰���̧����ɽ���¡�\n");
                        me->move(__DIR__"shanjiao");
                        me->unconcious();
                        return -1;
                }

                me->receive_damage("qi", qi);
                me->receive_damage("jing", jing);
        }

        dest = sprintf("/d/xingxiu/shamo%d", random(10) + 1);
        me->move(dest);
        switch (random(3))
        {
        case 0:
                write("�㶥�ŷ�ɳ�߰��ߣ�����û���߳�ɳĮ��\n");
                break;

        case 1:
                write("�����������Ұ�Ļ�ɳ��̾�˿������޾���ɵ����š�\n");
                break;

        case 2:
                write("��һ��������ǰŲ�ţ����ѷֲ�������\n");
                break;
        }
        return -1;
}
