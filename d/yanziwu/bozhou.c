#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
        set("short", "������");
        set("long", @LONG
�˴�һƬ«έ�����״����ֳ�һ�����룬��С��ֻ�����ſ�����
����Ҷ��������ˮ�� (river)��ͨ�˴�ɴ˿ɳ˴��뿪�����롣��
��ϵ��βС�ۡ�����ԶԶ����ȥ�и����ӡ�
LONG );
        //set("arrive_room", "/d/yanziwu/hupan");
        set("to", __DIR__"hupan");
        set("exits", ([
                "east"      : __DIR__"pindi",
                "northdown" : __DIR__"muti",
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "yanziwu");
        replace_program(RIVER);
}
