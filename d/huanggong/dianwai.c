// dianwai.c
inherit ROOM;

void create()
{
        set("short", "���Ź㳡");
        set("long", @LONG
�����ǻʵ�͢�ȹ����ĵط�, Ҳ�Ǵ󽫵�ʤ����������׷����ǵ�
����. ÿ��ʮ�³�һ��, ��������ȫ���䷢��������, ʱ�ơ���˷��.
���ڽ�ˮ���ϵ��������������, ��������, ͬ��ΰ׳�۵����ų�¥��
��̻Ի͵�̫������ӳ, ����עĿ. 
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([
                "east"  : __DIR__"youmen",
                "west"  : __DIR__"zuomen",
                "north" : __DIR__"wumen",
                "south" : "/d/beijing/hgmen_s",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2800);
	set("coor/y", 7691);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}