inherit ROOM;

void create()
{
        set("short", "��µ�");
        set("long", @LONG
����һ����խ����ʯ��ֵ���������ͷ���졣��ס���������ϵĴ�
����һЩ������ʿ�����ϰ��֮�缫ʤ�������ɼ�����֮�ˣ���ݣ��䳡��
�ھ�Ҳ�ȱȽ��ǣ�Ϊ�˰�ȫ���ٸ������ﲼ���˹ٱ��������ǹٸ����õ�
Ѳ�������η������Ϸ����ס�ŵ�ʱ�������ֽ����ң���������������
���˼ң����������������Ժգ������ǰ���������������ʿ�Ⱥ�ݷá�
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"wroad2",
                "south" : __DIR__"wanggate",
                  "north" : __DIR__"xunbu",
                  "west" : __DIR__"wroad4",
        ]));

        set("objects", ([
                "/d/city/npc/liumang" : 2,
                "/d/city/npc/liumangtou" : 1,
                __DIR__"npc/wangbofen" : 1,
        ]));
	set("coor/x", -7020);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}