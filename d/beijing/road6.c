inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵġ���
�̵ġ����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡���
ʱ����������������߷ɳ۶���������һ·��������·����������
����������֡�������ԶԶ�ľͿ������������ǡ�������ͨ����ɽ��
LONG );
        set("exits", ([
                "northwest" : "/d/beijing/road5",
                "southwest" : "/d/hengshan/jinlongxia",
                "southeast" : "/d/beijing/road7",
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7590);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}