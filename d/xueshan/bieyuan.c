inherit ROOM;

void create()
{
        set("short", "ѩɽ��Ժ");
        set("long", @LONG
������ѩɽ�µķֲ������깱�Ʋִ����ﲻԶ���������ʥ����
��Ϊ��ʦ�����ڴ˴�����𷨡�
LONG );
        set("exits", ([
                "east" : "/d/beijing/road5",
        ]));
        set("objects" , ([
                __DIR__"npc/seng-bing1" : 4,
                __DIR__"npc/zhike" : 1,
                CLASS_D("xueshan") + "/guoshi" : 1 ,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if( query("id", me) == "sengbing"
           && dir == "east")
                return 0;

        return ::valid_leave(me, dir);
}