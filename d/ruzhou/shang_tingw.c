inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
ƫ�����õ���Ϊ���ţ�˿��û�������ϵ��������ա�һ�ź�
ľ���������и���񣬹�����˸�ʽ�������顣ǽ�Ϲ��ż�����
��������������ʱ�������ֿ��Ե��鷿�á�
LONG);
        set("exits", ([
                "east"  : __DIR__"shang_dating",
        ]));
	set("coor/x", -6760);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}