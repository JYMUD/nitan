inherit ROOM;

void create()
{
        set("short", "Сԡ��");
        set("long", @LONG
��ЩСԡ�Ҿ���ר��װ�ޣ�������ר���ź��ɨ�����Ժܸɾ���
ǽ�����л��������ʻ��������Ϲ�����С���񡣷������е�Ȼ��ԡ�裬
��Щ��Ϊʾ�Է���ģ��ݷ�֮ǰ��Ҫ��ԡ��
LONG );
        set("objects", ([
                __DIR__"npc/obj/zaopeng" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"yushi",
        ]));

	set("coor/x", -5060);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}