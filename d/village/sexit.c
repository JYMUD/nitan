inherit ROOM;

void create()
{
        set("short", "�ϴ��");
        set("long", @LONG
�����ǻ�ɽ���£���ȻԶ���سǣ�ȴû��ʲ��ɽ���ݿ��ڸ�����
û��������һ��С��ׯ�������������˼Ҳ��࣬�����ǹ����ճ�������
�����Ϣ����������������С���ӣ������ϻ�ɽ��ɽ·�ˡ�
LONG );
        set("exits", ([
                "north" : __DIR__"sroad1",
                "south" : __DIR__"hsroad3",
        ]));
        set("objects", ([
                "/clone/quarry/gou" : 1,
        ]));
        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}