//Room: /d/suzhou/hong-damen.c
// by llm 99/06/12

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "����ׯ����");
        set("long", @LONG
��ǰ��һ��������ΰ�Ĵ�ׯͥ�����ȸߴ���ǽ���ߣ�����Щ��
�ʹ����Ƶ�ζ����ֻ�Ǵ����������Ĳ������롢ʨ�ޣ�����Ц���е�
ϲ��ͯ��ͯŮ�����Ҵ��ų���������������룬��������һ��޴��
��ľ����
            ��    ��    ׯ

LONG );
        set("exits", ([
                "west" : "/d/suzhou/canlangting",
                "east" : "/d/suzhou/hong-zoulang",
   ]) );


   set("objects", ([
//           "/d/suzhou/npc/meipo" : 1,
      ]) );
   set("coor/x", 210);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
   replace_program(ROOM);
}

