// Room: /d/huanggong/jingshan.c

inherit ROOM;

void create()
{
        set("short", "��ɽ");
        set("long", @LONG
�˵�����úɽ, ����ɽ, ��һƬ�羰�����Ļʼ�԰��. ���ľ�����
������, һƬ�����де�ϲ������, �Եò��Ϻ��۾�, Ҳ���������޵�
���ķ��. ��ɽ�Ķ�´��һ�껱��, ��Ϊ���������Ѵ�.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 1 */
                "south" : __DIR__"shenwumen",
                "north" : "/d/beijing/hgmen_n",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2820);
	set("coor/y", 7761);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}