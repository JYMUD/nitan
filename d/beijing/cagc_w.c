#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�������㳡");
        set("long", @LONG
�������찲����ߵ��������ֹ㳡�������ĳ������������ͷ
���죬���ﾩ���������ַ����ĵضΣ����ǽ�ͨҪ����Ҳ�Ǿ��ǰ���
�ǵľ۵㣬 �㳡�ϳ�ˮ���������ַǷ���С�����ؽֽ������Լ��Ļ�
�һЩ���ֺ��е��˳����������������������������߸ߴ�
��ʵ�Ĺų�ǽ����������찲�Ź㳡�ˡ��������ǿ�������������֡�
LONG );
       set("exits", ([
                "west" : "/d/beijing/caroad_w2",
                "east" : "/d/beijing/tiananmen",
                "north" : "/d/beihai/ximen",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl4" : 1,
                "/d/beijing/npc/girl2" : 1,
                "/d/beijing/npc/shusheng2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}