inherit ROOM;

void create()
{
          set ("short", "����");
        set("long", @LONG
һ��������ͷ�����̵�������б�����������ɫ�Ĺ��͸����Ҷ
�ڵ����������������ˢˢ����������Զȥ�������ֵ��м䱻�˿�
����һƬ�յأ�������һ��Сé�ݡ�
LONG );

          set("outdoors", "kaifeng");
          set("exits", ([
                  "enter" : __DIR__"zhulin1",
                  "west":__DIR__"fanta",
        ]));
	set("coor/x", -5020);
	set("coor/y", 2140);
	set("coor/z", 10);
	setup();
          replace_program(ROOM);
}