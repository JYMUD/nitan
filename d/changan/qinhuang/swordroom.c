inherit ROOM;
int do_xue(string arg);
void create()
{
    set("short", "��ٸ");
        set("long", @LONG
�������ٸ���ﶼ���Ž������Ÿ������ƣ���̬���졣
LONG );
    set("exits", ([
        "east" : __DIR__"shidao2",
    ]));
    setup();
}
void init()
{
    add_action("do_xue", "xue");
}


int do_xue(string arg)
{
    object me;
    me = this_player();
    if ( !arg || ( arg != "ٸ" ) )
        return notify_fail("ʲô��\n");
    if ( (int)me->query_skill("literate", 1) < 1)
        return notify_fail("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
    if( query("unarmed", me))return notify_fail("���Ѿ�ѧ��ȭٸ�ˡ�\n");
    if( query("hammer", me))return notify_fail("���Ѿ�ѧ����ٸ�ˡ�\n");
    if( query("club", me))return notify_fail("���Ѿ�ѧ����ٸ�ˡ�\n");
    if( query("blade", me))return notify_fail("���Ѿ�ѧ����ٸ�ˡ�\n");
    if( query("whip", me))return notify_fail("���Ѿ�ѧ����ٸ�ˡ�\n");
    if( query("staff", me))return notify_fail("���Ѿ�ѧ����ٸ�ˡ�\n");
    if( query("throwing", me))return notify_fail("���Ѿ�ѧ����ٸ�ˡ�\n");
    if( query("axe", me))return notify_fail("���Ѿ�ѧ����ٸ�ˡ�\n");
    me->receive_damage("jing", 1000);
    message_vision("$N��ʼģ��ѧϰ��Щ��ٸ�ĸ��ֶ�����\n", me);
    if ( (int)me->query_skill("sword", 1) < 851)
    {
        me->improve_skill("sword", me->query_int());
        set("sword", 1, me);
        return 1;
    }
    write("�������ٸ����һ�ض��������Ѿ�û��ʲô��ѧ���ˡ�\n");
    return 1;
}