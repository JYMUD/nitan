inherit ROOM;
/*
string go_enter(object me)
{
        if( query_temp("been_recommend_to_yaowang", me )
         || (query("family/family_name", me) == "ҩ����") )
                return __DIR__"gd2";
        else
                return __DIR__"gd1";
}
//��֪��Ϊʲô������������䡣
string go_out(object me)
{
        if( query("family/family_name", me) == "ҩ����" )
                return __DIR__"gd1";
        else
                return __DIR__"shulin/exit";
}
*/
void create()
{
        set("short", "��ľ��");
        set("long", @LONG
����һ��ԭľ��ɵ�С�ţ�����������֨֨�¸µ����죬��
����ʱ���ᵹ�����������ĵ�����
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"gd2",
  "south" : __DIR__"gd1",
]));

        set("outdoors", "yaowang");
        setup();
}
