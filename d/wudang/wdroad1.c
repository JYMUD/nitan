inherit ROOM;

void create()
{
        set("short", "��ʯ���");
        set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ������
������ҴҶ��������������һЩС��̯���ƺ��Ǽ��С�����
ͨ�����ݳǡ�������һ��Ƭ���֡�
LONG);
        set("outdoors", "sanbuguan");
        set("exits", ([
                "south" : __DIR__"wdroad2",
                "north" : "/d/city/dujiangqiao",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
