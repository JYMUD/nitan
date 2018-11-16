// Room: /d/guiyun/road4.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "����ׯǰ");
        set("long",@LONG
����ͨ�����ׯ�ĵ�·��������ǹ���ׯ��������һ��С·������
��һƬ�����͵Ĳݵء�
LONG
);
        set("exits",([
                "west"  : __DIR__"shiqiao",
                "south" : __DIR__"road3",
                "north" : __DIR__"caodi1",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 290);
        set("coor/y", -840);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "west")
        {
                write("ׯǰ��һ�����ݾŹ��������ɵ��һ���\n");
                if( (query("family/family_name", me) == "�һ���" && 
                        me->query_skill("qimen-wuxing", 1) > 14) ||
                        me->query_skill("qimen-wuxing", 1) > 39)
                        write( "������ƽ����������Щ���׵��󷨣����Բ���ϸ�룬�Ų����߳�����\n");
                else {
                        set_temp("jiugong_dir", "w", me);
                        me->move(__DIR__"jiugong" + (random(9) + 1));
                        return -1;
                }
        }
        return ::valid_leave(me, dir);
}
