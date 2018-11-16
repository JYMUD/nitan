// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short","�ɽ���");
        set("long",@LONG
һ������ʯ�ź����ڴ��˺��ϣ��ŵĲ�������֪��ŷ�������š���
���š������¸�ɫ��ֻ������Ϣ������������������ͷ�����˵���ʳ��
���������Σ����ڴ�װж�������ž������ݵ����š�
LONG );
        set("outdoors", "yangzhou");
        set("region", "yangzhou_zone");

        set("exits", ([
                "north"  : __DIR__"nanmen",
                "south"  : "/d/wudang/wdroad1",
                "west"  : __DIR__"shulin1",
                "east"  : __DIR__"matou",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/shipopo" : 1,
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));
	set("coor/x", 0);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
