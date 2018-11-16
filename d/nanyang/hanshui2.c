// This program is a part of NT MudLIB

inherit RIVER;

void create()
{
        set("short", "��ˮ����");
        set("long", @LONG
��ˮ����Ҳ���൱���֣��Ա����ɿ�������һ����ֱ�Ĺٵ�ֱͨ��
�����˵���紾�ӣ�·�Լ��������������������Ҷ���һ����ġ���
����ӭ��Ʈ�εΪ׳�ۡ�Ҳ�в���С����·��������ѱ棬ȴҲ��
��ʢ����ȴ��
LONG );

        set("outdoors", "nanyang");
        set("region", "nanyang_zone");
        set("to", __DIR__"hanshui1");

        set("exits", ([
                "north" : __DIR__"nanmen",
        ]));

        set("objects", ([
                __DIR__"npc/chuanfu2" : 1,
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));
        set("no_clean_up", 0);
	set("coor/x", -6940);
	set("coor/y", 740);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
