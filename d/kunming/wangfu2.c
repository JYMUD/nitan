inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
������ƽ����������������������̫ʦ�Σ�ǽ�Ϲ���һ��
�ֻ������õļ���ࡣ����յ�����û��һ���ˣ�����ƽ��
��ƽʱ���������ֻ�м������˲�ʱ����ɨһ�¡�
LONG);
        set("exits", ([
                "south"    :__DIR__"wangfu1",
        ]));

	set("coor/x", -16840);
	set("coor/y", -7170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);         
}