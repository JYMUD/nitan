//Room: /d/dali/tusimentang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����");
        set("long", @LONG
�����Լ�����һЩ������������Ȳ֣����������������ж��׶�
�����޵�Χǽ�����彨���ǹ�ģ�������������������ϵ�����Ъ
ɽ������ʽ����������ʮ�ߣ�����ʮ���壬����ʮ�ߡ���¥��������
����Сͷ�����ص㣬Ҳ�������ҡ�
LONG );
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/tusihouting",
            "up"     : "/d/dali/tusiyishi",
            "out"    : "/d/dali/tusifu",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19141);
	set("coor/y", -6891);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}