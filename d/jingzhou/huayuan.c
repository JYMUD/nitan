// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "��԰");
        set("long", @LONG
�����Ǻ��ָ��Ļ�԰��Ժ�������˸�ɫ����ľջ����ƾ��ж�ʤ��
����ҩ������֪���׾������°ס�һ��ѩ���������¡��Ͼ���˫���ࡢ
������������̡���������˺졢���������ܽ�ء�����Ժ���м���
��ɫ�ر��޵Ļƻ�������Ƶ������һ������������Ӻ���ɻ���
�Ǿ��Ǵ����ô����Ľ�Ѯ����
LONG );
        set("outdoors", "jingzhou");
        set("region", "jingzhou");

        set("exits", ([
                "north" : __DIR__"houyuan",
                "west" : __DIR__"loudi",
                "east" : __DIR__"shufang",
        ]));
        set("objects", ([
                //__DIR__"npc/obj/juhua1" : 1,
                __DIR__"obj/jinboxunhua" : 2,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();

        if( !query_temp("jinboxunhua", me) && !wizardp(me) && playerp(me)){
                me->receive_damage("qi", 1000);
                me->receive_damage("jing", 800);
                set_temp("die_reason", "���˽�Ѯ��������", me);
                tell_object(me, "��ͻȻͷ��Ŀ����\n");
                return;
        }
}