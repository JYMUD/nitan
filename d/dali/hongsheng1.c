//Room: /d/dali/hongsheng1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����");
        set("long", @LONG
��ʥ��������ϵ��ʯ�����ɣ���ǧѰ����Ϊש����ͬ����������
�����ţ��������ʵǶ��ϡ�
LONG );
        set("exits",([ /* sizeof() == 1 */
            "out"    : "/d/dali/hongsheng",
            "up"     : "/d/dali/hongsheng2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19151);
	set("coor/y", -6821);
	set("coor/z", 19);
	setup();
}

int valid_leave(object me, string dir)
{
        int c_exp;
        int c_skill;
        if (dir == "up" )
        {
                c_exp=query("combat_exp", me);
                c_skill = (int)me->query_skill("dodge",1);
                if( query("qi", me)>20 )
                {
                        me->receive_damage("qi", 20);
                        if (c_skill*c_skill*c_skill/10 < c_exp && c_skill<101)
                                me->improve_skill("dodge", (int)me->query_skill("dodge", 1) / 5);
                        tell_object(me,"������һ��¥����Щ���ˡ�\n");
                } else
                {
                        set("qi", 0, me);
                        tell_object(me,"�������������ˡ�\n");
                        return 0;
                }
        }
        return 1;
}