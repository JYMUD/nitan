inherit ROOM;

void create()
{
        set("short", "��Ժ��Ժ");
        set("long", @LONG
������������Ժ�ĺ�Ժ����ɨ�÷ǳ��ɾ��������ǹ��˸ߵ�Χǽ��
ż����������������˾��ð�����г���ϱ���һ��С�ţ�ͨ��һƬ
���֡�
LONG );
        set("exits", ([
                  "north" : __DIR__"shuyuan",
                  "south" : __DIR__"shijie",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7090);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}