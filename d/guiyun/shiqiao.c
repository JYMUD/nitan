// Room: /d/guiyun/shiqiao.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "��ʯ��");
        set("long",@LONG
���ǹ���ׯǰ��ʯ�ţ��������ͽ�ׯ�ˡ���ׯ������ȥ������¥��������
���Ǻô�һ��ׯԺ��
LONG );
        set("exits",([
                "north" : __DIR__"damen",
                "east"  : __DIR__"road4",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 280);
        set("coor/y", -840);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "east")
        {
                write("ׯǰ��һ�����ݾŹ��������ɵ��һ���\n");
                if( (query("family/family_name", me) == "�һ���" && 
                        me->query_skill("qimen-wuxing", 1) > 14) ||
                        me->query_skill("qimen-wuxing", 1) > 39)
                        write( "������ƽ����������Щ���׵��󷨣����Բ���ϸ�룬�Ų����߳�����\n");
                else {
                        set_temp("jiugong_dir", "e", me);
                        me->move(__DIR__"jiugong" + (random(9) + 1));
                        return -1;
                }
        }
        return ::valid_leave(me, dir);
}
