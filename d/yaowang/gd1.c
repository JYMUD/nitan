inherit ROOM;
/*
string go_enter(object me)
{
        if( me && (query("family/family_name", me) == "ҩ����") )
                return __DIR__"dmq";

        else
                return __DIR__"shulin/entry";
}
*/
void create()
{
        set("short", "ʯ��С·");
        set("long", @LONG
����һ��ʯ��С·������������̲ݵ��У������Ǿ�������
�߶���·�ϵ�ʯ�ӱ�ĥ�÷ǳ���������ϸ�����滹���ò�ɫ��ʯ
��ƴ����һ����ҩ���֡�·������һ��Сʯ��(bei)��
LONG
        );

        set("exits", ([
  "north" : __DIR__"dmq",
  "south" : __DIR__"xiaoyuan",
]));

        set("outdoors", "yaowang");
        setup();
}
