inherit ROOM;

void create()
{
        set("short", "�㳡");
        set("long", @LONG
 ������ѩɽ���ڵĹ㳡���㳡ʯ���̾ͣ�����������ƽ������ʵ��
�㳡�ı��������ɽ������ѩɽ�´������ǿ����䳡��������ɽ
�š�������һЩ�ֳ�ɮ����ɮ����Ѳ�ߡ�
LONG );
        set("outdoors", "xueshan");
        set("exits", ([
                "east" : __DIR__"xiaoyuan",
                "west" : __DIR__"chang2",
                "north" : __DIR__"dadian",
                "south" : __DIR__"frontyard",
                "south" : "/d/xueshan/frontyard",
        ]));
        set("objects" , ([
                __DIR__"npc/seng-bing1"  : 4 ,
        ]));
        setup();
}