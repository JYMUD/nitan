inherit ROOM;

void create()
{
        set("short", "�ɳ���");
        set("long", @LONG
����Ϳ쵽��翷�����ˣ�Խ�����ߣ�ɽ��Խ�ߣ������������
�İ���������Ũ������������ɽ��·������ɽ��û�߼�����������ǰ
����һ��ʯ�������顸�ɳ��š��������֣�������ɽ֮�����ɡ�
LONG );
        set("outdoors", "lingjiu");
        set("objects", ([
                CLASS_D("lingjiu") + "/first" : 1,
        ]));
        set("exits",([
                "eastup" : __DIR__"dadao1",
                "southdown" : __DIR__"jian",
        ]));
        setup();
        replace_program(ROOM);
}
