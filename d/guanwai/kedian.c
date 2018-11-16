//Room: /d/dali/kedian.c

inherit ROOM;
void create()
{
        set("short","�͵�");
        set("long",@LONG
���ǳ���Ψһ��һ��С��ջ��ר�ŽӴ��������̣�����ǳ���¡��
��С����������æ������ת���˼���ƫԶ��ȴ�����ƿ��׿��ˣ�ס��һ
��ֻҪ�������ӡ�
LONG);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("exits",([ /* sizeof() == 1 */
            "west"    : __DIR__"majiu",
            "east"    : __DIR__"jishi",
            "up"      : __DIR__"kedian2",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("coor/x", 3980);
	set("coor/y", 9240);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("��С��һ�µ���¥��ǰ������һ���������ţ����ס����\n");

        if( query_temp("rent_paid", me) && dir == "west" )
        return notify_fail("��С���ܵ��ű���ס���͹��Ѿ��������ӣ����᲻ס��������أ�
���˻���ΪС���ź����أ�\n");

        return ::valid_leave(me, dir);
}