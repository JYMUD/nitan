inherit ROOM;

void create()
{
        set("short", "�ӻ���");
        set("long", @LONG
��֪Ϊʲô�������ȴֻ����һ���ӻ��̡�����ÿ������������Ҳ
ͦ���֡��������������ν��ף����Ǵ��װ��棬�����ճ���ƷҲ��������
ȫ���м�һ�Ź�̨�������������ڹ�̨�������ʡ���˵˽������Ҳ��һЩ
���صĶ�����
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"sroad4",
        ]));
        set("objects", ([
                __DIR__"npc/xiao" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}