inherit ROOM;

void create()
{
        set("short", "Ƥ����");
        set("long", @LONG
����������һ��Ƥ���꣬ר����ʽ������Ƥ������˵�����Կ�������
��������ʲô������Ƥ�������Ǵ������������ǵظ߼۳���һЩ�黭����
�����ù��ı��⡣�������ù���һ���ǳ�����ϸ�ֳ��ң��������С�ͯ��
���ۡ����֡�
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"nroad4",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/huizhang" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}