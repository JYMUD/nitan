inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ������ʵ���ʯ���̳ɵ�С·�����Ķ������죬·��
��������۲ݣ�·�����Ը���һ��С��̳�����濪�������Ļ��䡣
������һ����ճ���������һ����ש�߷���
LONG
        );
        set("exits", ([
  "north" : __DIR__"sleeproom",
  "east" : __DIR__"ssl3",
  "west" : __DIR__"myuan",
]));

        set("outdoors", "yaowang");
        setup();
}

int valid_leave(object ob,string dir)
{
        if( !wizardp(ob)
        && (dir == "north")
         && (query("family/family_name", ob) != "ҩ����") )
                return notify_fail("���ϴܳ�����ͯ����ס�����ȥ·��\n");

        return ::valid_leave(ob,dir);
}
