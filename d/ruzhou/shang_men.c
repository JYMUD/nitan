inherit ROOM;

void create()
{
        set("short", "�̼ұ�����");
        set("long", @LONG
һ���޴��լԺӳ����������������������һ������ͭ��
�Ĵ��ţ������ǽ��ɸߵ�Χǽ�����ŵ��Ϸ�����һ���ң�����д
�š��̼ұ����������֡�
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_qgc",
                "south"  : __DIR__"shang_road3",
        ]));
        set("objects", ([
                CLASS_D("shang") + "/zhen" : 1,
                __DIR__"npc/shang2" : 2,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6750);
	set("coor/y", 1840);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object zhen;

        if (dir != "north"
           || ! objectp(zhen = present("shang baozhen", this_object()))
            || (query("born_family", me) == "ɽ���̼�"
            && !query("family/family_name", me)) )
                return ::valid_leave(me, dir);

        return zhen->permit_pass(me, dir);
}