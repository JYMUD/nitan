inherit ROOM;

void create()
{
        set("short", "ҩ��");
        set("long", @LONG
������һ���ܴ��ҩ���ԣ���ؿ��Ÿ�ɫ�����С��������
��������������ӵĹ�ζ����
LONG
        );
        set("exits", ([
  "northeast" : __DIR__"xiaodao5",
  "west" : __DIR__"lu2",
  "south" : __DIR__"xiaodao4",
]));

        set("objects", ([
                "/kungfu/class/yaowang/xue" : 1,
        ]));
        
        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
