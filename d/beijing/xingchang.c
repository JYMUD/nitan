inherit ROOM;

void create()
{
        set("short", "�̳�");
        set("long", @LONG
�����Ǿ��ǵ��̳����ǳ�͢�����շ��ĳ��������ߵ��������
�������̳����ǿտ����̳�������һ���߸ߵ�ʯ̨��ʯ̨���ɼ���Բ
ľ�������һ����ܣ����洹��һ���ֵܴ����������������һ��
�����εĴ�ľ׮�����滹�ܹ���������Ѫ����
LONG );
       set("exits", ([
                "west" : "/d/beijing/wang_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/guizishou" : 1,
               "/clone/npc/walker"  : 1, 
        ]));

	set("coor/x", -2760);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}