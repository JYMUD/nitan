//Room: /d/dali/xiaodao.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����С��");
        set("long", @LONG
������С������ǰ��Լ��ʮ���ߣ�ֻ������������Ũ����죬һ
����ȪǶ����䣬������ʯ��Ȫˮ��������������Ǯ���ڳ��У�����
�������䣬���������ɸ�£��ص�������˸������Ȫˮ�������ر߾�
����Լ�����ߵĵط���һ�ֿɺϱ������ɣ����Ȫ�ϣ����Խ���Сͤ��
С��������ʮ�����ġ� 
LONG );
        set("objects", ([
           "/d/dali/npc/maque": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "northup"  : "/d/dali/qingxi",
            "south"    : "/d/dali/heilongling",
            "west"     : "/d/dali/hudiequan",
        ]));
	set("coor/x", -19110);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}