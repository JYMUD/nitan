inherit ROOM;

void create()
{
        set("short", "��������" );
        set("long", @LONG
���������ݵ����ţ������������Ǿ���Ҫ�أ���˳�ǽ��ʵ�ޱȣ�
��¥�߸��������������ţ���̤���˼��յ������һֱ���츩֮����
ȥ��·�϶������裬�����Ҫȥ�Ļ�����ض��С�ġ����˳��ţ���
�뾣�ݣ���͵��ڵ�����ԭ�ˡ�
LONG );
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/clone/npc/xunbu" : 1,
                "/d/beijing/npc/ducha" : 1,
        ]));

        set("exits", ([  
               "east" : __DIR__"xidajie2",
        ]));
        set("outdoors", "jingzhou");

        set("coor/x", -7130);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}