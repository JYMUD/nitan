inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����̼ұ��ڵ�һ��ľ�Ƶ����ȣ����������ǹ⻬������
���ȱ�������һ����Ⱦ���㲻ʱ�ܹ����������̼ұ��ļҶ��ڴ�
�߶���æµ����ͣ��
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_houyuan",
                "south"  : __DIR__"shang_zoulang1",
        ]));
	set("coor/x", -6750);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}