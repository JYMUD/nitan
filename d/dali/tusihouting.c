//Room: /d/dali/tusihouting.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����");
        set("long", @LONG
���������Ǻ�������һ¥һ�׵���ʽ�������ݽǵ��ϸ�ܣ�����
����������ͼ�������޻�ľ�ĵ�̣�������������·��ӱ����������
ʮ������˾���б�����õ�һ����
LONG );
        set("exits",([ /* sizeof() == 2 */
            "south"  : "/d/dali/tusimentang",
         "down" : "/d/xueshan/mishi" , 
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19141);
	set("coor/y", -6881);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}