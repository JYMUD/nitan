inherit ROOM;

void create()
{
        set("short", "��Ժ");
        set("long", @LONG
�������ݳ��ϵ�һ����Ժ����˵�����Ժ������˵����
��ѧ�����ɵ��˻����٣���������������Ҳ����������顣��
Ժ���м�����ҡͷ�����������������徭��
LONG);

        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"wendingnan4",
        ]));

        set("no_fight",1);
        set("coor/x", -9050);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
}