inherit ROOM;

void create()
{
        set("short", "��ٵ�");
        set("long", @LONG
����һ��������ֱ����������Ĵ�ٵ����������˶���������������
�����ٵ����ǿ�㣬����ݵ���ʮ���ۡ�����ֱ�ﳤ���Ķ��ţ�������
���������ųǡ�
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"guandaow2",
                  "west" : __DIR__"guandaow4",
        ]));

        set("coor/x", -3590);
        set("coor/y", 1090);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}