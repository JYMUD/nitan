inherit ROOM;

void create()
{
	set("short", "������԰");
	set("long", @LONG
�����ǹ����Ļ�԰��԰�ڼ�ɽ��������������Щ���񣬶�
���Ǽ���֦Ҷïʢ��ľ�ʻ�������һ�߽��������ŵ�һ������
�µġ������Ļ��㡣
LONG);
        set("no_fight", 1);
	set("exits", ([
		"east"  : __DIR__"guofu_woshigh",
		"west"  : __DIR__"guofu_kefang",
		"south" : __DIR__"guofu_lang5",
		"north" : __DIR__"guofu_shufang",
	]));
	setup();
        (CLASS_D("taohua") + "/rong")->come_here();
}

void reset()
{
        ::reset();
        (CLASS_D("taohua") + "/rong")->come_here();
}

