//Room: /d/dali/nianhua1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�黨��Ժ");
        set("long",@LONG
��ٲ����£�ֻ���ö����������࣬���ƴӺ�Ժ��������ʱ֮�䣬
ֻ�б����������⾲���С���̤ʵ����Ժ����Ҷ���߽���Ժ����վ��
ͥ�У��ۼ�ͥ��һ�깫������һƬ��Ҷ�������䣬����ȫ����
LONG);
        set("outdoors", "daliw");
        set("no_clean_up", 0);
        set("exits",([ /* sizeof() == 1 */
            "out"  : __DIR__"nianhuasi",
        ]));
	set("coor/x", -19161);
	set("coor/y", -6881);
	set("coor/z", 9);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/nh1", 1, me);
        }
}