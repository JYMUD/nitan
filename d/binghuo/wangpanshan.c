// Room: /binghuo/wangpanshan.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "����ɽ��̲");
        set("long", @LONG
ֻ���õ��ϺŽ�֮�����ش��𣬰������˸��ٴ��죬����ʾ�⡣
ֻ����������Ͼ�����һͷ��ӥ��˫����չ���������䡣�������֮
��վ��һ�����ߡ�ֻ��������˵����������̳�׹��ٹ�ӭ��͡�����
���������������ܣ��䲻������ȴ�����ϴ���������һ��ɽ�ȡ���
���и����壬Φ�ɸ��ʣ�ͣ����ʮ���Ҵ󴬣����Ǿ޾����ɳ��һ
���˵�������
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("exits", ([
                "north":"/d/tulong/tulong/boat2",
                "south" : __DIR__"wangpangu1",
                //"east"  : __DIR__"wangpanlin",
        ]));
        set("objects", ([
                 "/d/tulong/tulong/npc/jiaozhong1": 2,
                 "/d/tulong/tulong/npc/jiaozhong2": 2,
                 "/d/tulong/tulong/npc/bai": 1,
        ]));
        setup();
}

int valid_leave(object me,string dir)
{
        object ob;
        if( !query_temp("dao", me) && dir == "south" )
        return notify_fail("һ���˻᳡��������֮�����������������ǵĴ�(break boat)�Է����⡣\n");

        if( query_temp("dao", me) && dir == "south" && ob=present("bai guishou") )
        {
                ob->ccommand("tnnd"+query("id", me));
                ob->ccommand("slap3"+query("id", me));
                message_vision("$N�ȵ���$n��ȥ���ɣ�\n",ob,me);
                ob->kill_ob(me);
                ob=present("jiao zhong");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("jiao zhong 2");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("jiao zhong 3");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("jiao zhong 4");
                if (objectp(ob)) ob->kill_ob(me);
                return notify_fail("���ϵ�·���׹�����ס�ˡ�\n");
        }
        return 1;
}

