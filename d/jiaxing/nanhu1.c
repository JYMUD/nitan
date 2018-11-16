// Room: /d/jiaxing/nanhu1.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void init();
int do_out();

void create()
{
        set("short", "�����Ϻ�");
        set("long", @LONG
�������̲������Ϻ������ϼ�ֻ�������ε������ϵ��οͺ���¥
Ů������Ц����ˮ���û�д��Ƕɲ���ȥ�ġ�����֪��˭�ں��׶���
һЩľ׮��׮��Ǳ��ˮ��֮��һ����ĵط�����ʹ�ǲ����Ṧ��������
ȥҲ����ˮ��Ư�����ӡ�
LONG );
        set("exits", ([
                "south"     : __DIR__"yanyu",
                "northwest" : __DIR__"nanhu",
                "southeast" : __DIR__"road",
        ]));
        set("outdoors", "jiaxing");
        set("objects", ([
                "/clone/medicine/vegetable/heye" : random(2),
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

	set("coor/x", 1210);
	set("coor/y", -1780);
	set("coor/z", 0);
	setup();
}