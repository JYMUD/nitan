//Room: /d/dali/bingqiku.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","������");
        set("long", @LONG
���������������ı����������ܷ��⼸�������ܣ�������������
�˵���ƽʱ�����õ��񽣡�
LONG );
        set("objects", ([
            "/clone/weapon/zhujian" : 4,
            "/clone/weapon/changbian" : 1
        ]));
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/chahua1",
        ]));
        set("no_fight", 1);
	set("coor/x", -19091);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
}
int valid_leave(object me, string dir)
{
        int i, j;
        object *inv;
        inv = all_inventory(me);
        i = sizeof(inv);
        for (i = 0; i < sizeof(inv); i++)
        {
                if( query("id", inv[i]) == "zhujian")j++;
        }
        if (j > 1)
                return notify_fail("��λ" + RANK_D->query_respect(me) + "������̰�ģ�����һ���񽣾͹�����\n");
        return ::valid_leave(me, dir);
}