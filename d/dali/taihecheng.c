//Room: /d/dali/taihecheng.c
//Date: June. 29 1998 by Java

#include <room.h>
inherit BUNCH_ROOM;

void create()
{
        set("short","̫�ͳ�");
        set("long", @LONG
�˳�����������θ���ȫ����İ����ʯ�ݳɣ������࣬��������
���ϡ�̫�Ͳ����ǣ����˿�Ϊ�������٣������Ϻ;������Ǵ����
�ı��Ż������������������ڴ˼ӹ̳ǳأ���פ������������һЩ��
�Ĳ���۾ӡ�������һƬƽԭ����ʮ���������ǡ�
LONG );
        set("outdoors", "dalin");
        set("objects",([
            "/d/dali/npc/bing": 2,
            "/d/dali/npc/jiang": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/dehuabei",
            "south"  : "/d/dali/dalinorth",
        ]));
	set("coor/x", -19160);
	set("coor/y", -6840);
	set("coor/z", 20);
	setup();
}
