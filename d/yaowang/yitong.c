inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�������ҩ���ȵ����������ߴ�ĵ��ã��Ĵ�����������
������һ�Ѿ޴�ĺ�ľ̫ʦ�Σ�����һ�Ⱦ޴��������
���������ɷ
LONG
        );
        set("exits", ([
  "south" : __DIR__"myuan",
  "north" : __DIR__"xiangfang",
]));
/*
        set("objects", ([
        CLASS_D("yaowang") + "/wuchen" : 1,
]));
*/
        setup();
        replace_program(ROOM);
}
