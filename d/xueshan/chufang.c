inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
 ������ѩɽ�µĳ�����������ɮ�˿����ڴ˴��ӡ�������Ŀ��λ
����һ�����ӣ����Ѿ��ƾɲ������ּ�ģ����,��ϡ���ĳ�����ϲ���Ƶ���һ�Σ�����@
LONG );
        set("exits", ([
                "south" : __DIR__"xiaoyuan",
        ]));

        set("objects", ([
                __DIR__"obj/cha" : 2 + random(2),
                __DIR__"obj/nailao" : 2 + random(2),
        ]));

        set("resource/water", 1);

        set_temp("times" , 5);
        setup();
}