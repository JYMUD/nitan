#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "������" NOR);
        set("long", HIB @LONG
���ǵ�������ߵ�һ��������Լ������ߣ�����ʮ�˼����ഫ����
ס��������ȸ���������Ҳ��֪�����Ǽ١�
LONG NOR
        );

        set("exits", ([
              "up"   : __DIR__"yinyangta2",
              "east" : __DIR__"yanluodian",
        ]));
        
        set("objects",([
        ]));
        
        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}