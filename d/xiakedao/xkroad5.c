inherit ROOM;

void create()
{
        set("short", "���ɹ����");
        set("long", @LONG
С�岻��ȴ�и��ô��ɹ����������С���ڳ������ǵ���ˣ��
�������֡����Ϻ����ϣ��и��������󺣣���Ȼ������
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "north"   : __DIR__"xkroad6",
                "west"    : __DIR__"xkroad4",
        ]));
        set("objects", ([
                __DIR__"npc/boy": 1,
                __DIR__"npc/girl": 1,
                __DIR__"npc/yufu": 1,
                CLASS_D("misc/haigui") : 1,
        ]));
        set("coor/x", -1390);
        set("coor/y", -9000);
        set("coor/z", 0);
        setup();
}

void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/haigui");
}

