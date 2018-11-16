// Room: /d/huangshan/shijian.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "�Խ�ʯ");
        set("long", @LONG
һ��޴��ʯͷ ��stone�����´�·�У��м�һ�ۣ�����룬��
������һ�Ŵ���ʦ�Խ�֮��������ǧ�࣬����������һ�ѿ���������
ʯ�Ľ�����Ϊ������񽣡�����ϧ��ʦ�������㲶������ഫ��ɽ��®
���������ഫ�ı��Ǵ˽���
LONG
        );
        set("exits", ([ 
                "east" : __DIR__"zuishi",
        ]));
        set("item_desc", ([
                "stone": "һ��޴��ʯͷ���м�һ�ۣ��ѷ���ƺ���һ
�����������⡣���ƺ�Ҳ������������һ�ԣ�test�����������\n"
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -615);
        set("coor/y", -1080);
        set("coor/z", -30);
        setup();
}
void init()
{
        add_action("do_test","test");
}
int do_test(string arg)
{
        object weapon, me = this_player();
        object piece;

        if(!arg ) return notify_fail("��Ҫ��һ�������ϵ�����������\n");
        if(!(weapon = present(arg,me)))
                return notify_fail("�������ƺ�û������������\n");
        if( !query("weapon_prop", weapon) )
                return notify_fail(weapon->name()+"�ƺ�������һ��������\n");
        if( !query("equipped", weapon) )
                return notify_fail("�㲢û�н�"+weapon->name()+"�������С�\n");
        message_vision("$N�þ�ȫ���������е�"+weapon->name()+"�������ʯ��ȥ��������\n",me);
        weapon->unequip();
        set("weapon_prop", 0, weapon);
        weapon->save();
        me->reset_action();
        message_vision("ֻ������������һ����$N���е�"+weapon->name()+"Ӧ�����ϣ�\n",me);
        seteuid(getuid());
        piece = new("/clone/misc/piece");
        piece->set_name("�ϵ���"+query("name", weapon),({query("id", weapon),"piece"}));
        piece->move(this_player());
        destruct(weapon);
        if(random(500))
                tell_object(this_object(),"��ʯ�ϵ��Ѻ��ƺ�������һЩ��\n");
        else
        {
                tell_object(this_object(),"һ�������Ķ�����ʯ���е��˳�����\n");
                weapon = new(__DIR__"obj/banzhi");
                weapon->move(this_object());
        }
        me->start_busy(2);
        return 1;
}