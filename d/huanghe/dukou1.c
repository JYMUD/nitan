#include <ansi.h>
inherit RIVER;

void create()
{
        set ("short", "�ƺӶɿ�");
        set ("long", @LONG
�ɿ�ǰ������ӿ���ȵĻƺ� (river)�ˡ�������������ɳ
���£�������������ɴ������������ڲ����д��У���Ϊ��
�ա����˻ƺӣ����ǻ����ˡ�
LONG);
        set("to", "/d/beijing/dukou2");
        set("exits", ([
                "south" : __DIR__"huanghe4",
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu",
        }));

        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        setup();
        replace_program(RIVER);
}
