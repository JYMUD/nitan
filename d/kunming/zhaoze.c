inherit ROOM;

void create()
{
        set("short", "�����Ե");
        set("long", @LONG
���������ܲ�����ɫ����������ǰ�߾������������������� 
�������������ﲻ�������ܲ������޳�û������������������ 
��һ˲����ʱ����Ķ���Ȫ������ԭʼɭ�����(Forest door)��
LONG
        );
        set("item_desc", ([
                "door" : "�������ڿ��Խ���ԭʼɭ���Թ�������(enter door)\n",
                "Forest door" : "�������ڿ��Խ���ԭʼɭ���Թ�������(enter door)\n",
                "forest door" : "�������ڿ��Խ���ԭʼɭ���Թ�������(enter door)\n",
        ]));

        set("exits",([
                "east" : __DIR__"yunnan1",
        ]));
        set("objects", ([ 
                "maze/forest/forest_door" : 1,
        ]));
	set("coor/x", -16770);
	set("coor/y", -7160);
	set("coor/z", 0);
	setup();
        // replace_program(ROOM);
}
