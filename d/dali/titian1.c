//Room: /d/dali/titian1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����");
        set("long",@LONG
����ˮ�ӹ��������ů������������ɽ�¿����˲�������˼�
���ǵ��£�����������¶��ϣ����ؿ����������֣������ϡ�裬��
�ĵ���ũҵ��Ϊ��󣬶��л����ָ�������ɽ�ϵ�һЩ�����������
���������š�
LONG);
        set("objects", ([
           __DIR__"npc/nongfu": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "west"  : __DIR__"zhenxiong",
        ]));
	set("coor/x", -19200);
	set("coor/y", -6860);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/tt", 1, me);
        }
}