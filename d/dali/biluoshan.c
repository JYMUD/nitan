//Room: /d/dali/biluoshan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����ɽ��");
        set("long",@LONG
�˼���������ɽ���£�����������ɽ�¶��ϣ����ؿ���һ��Ҳ��
���֣������ϡ�衣���ĵ���ũҵ������л����ָ��������ڲ�ͬ
�ļ��ڸ�����ͬ����أ���฽�������������������˸�����
LONG);
        set("objects", ([
           __DIR__"npc/nongfu": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "west"      : __DIR__"yixibu",
        ]));
	set("coor/x", -19190);
	set("coor/y", -6900);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/bls", 1, me);
        }
}