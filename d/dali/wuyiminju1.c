//Room: /d/dali/wuyiminju1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�������");
        set("long", @LONG
����һ��������ķ��ݡ�������ӵĽ��غ����򽲾���������ɽ
�ƣ�һ����ʯΪǽ�ͻ�����ľΪ�����ṹ���ºͺ��˷�����£�����
ƽ����ʯ��Χǽ�����Ժ����һȦ������ţ����С�
LONG );
        set("objects", ([
           "/d/dali/npc/muyangnu": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/wumeng",
        ]));
	set("coor/x", -19170);
	set("coor/y", -6770);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}