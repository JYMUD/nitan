inherit ROOM;

void create()
{
        set("short", "��ԭ");
        set("long", @LONG
������ѩɽ���µ�һƬ��ԭ�������������Ⱥɽ��ɽ���ϻ�����
�겻����ѩ��������һ����·��
LONG );

        set("exits", ([
                "west"      : __DIR__"tulu1",
                "northeast" : "/d/xingxiu/silk5" ,
        ]));

        set("objects", ([
                "/clone/quarry/tu" : 4 ,
        ]));

        set("outdoors", "xuedao");

        setup();
        replace_program(ROOM);
}