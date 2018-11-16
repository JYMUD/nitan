// Code of LXTX
// pine.c ����

inherit ITEM;

int shaking();
int collapse(object);
int do_chop(string);

void create()
{
        set_name("����", ({ "pine", "song shu", "tree" }) );
        set_weight(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����һ�������ﳣ����������\n");
                set("unit", "��");
                set("no_get", 1);
                set("tree_str", 100);

        }

}

void init()
{
        add_action("do_chop","chop");
}

int do_chop(string arg)
{
        object me=this_player();
        object weapon;
        int str;

        if (!arg) return 0;

        if (me->is_busy() || me->is_fighting() )
                return notify_fail("����æ���ء�\n");
        
        if (arg != "tree" && arg != "pine")
                return notify_fail("��Ҫ��ʲô��\n");
        
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("id", weapon) != "axe" )
                return notify_fail("����Ҫһ�Ѵ��ӡ�\n");

        if( query("jing", me)<30 || query("qi", me)<50 )
                return notify_fail("������������ˡ�\n");

        message_vision("$N�Ӷ��󸫣��ݺݵس������ɿ�����ȥ��\n",me);
        addn("jing", -20, me);
        addn("qi", -30, me);
        me->start_busy(3);
        str = me->query_str();
        addn("tree_str",-random(str)/2);
        if (query("tree_str") <=0)
        {
                remove_call_out("collape");
                call_out("collapse",1,me);
        }
        else if (query("tree_str") <= 50)
        {
                remove_call_out("shaking");
                call_out("shaking",1);
        }
        return 1;
}

int shaking()
{
        message_vision("�����Ѿ�ҡ�εĺ������ˡ�\n",this_object());
        return 1;
}

int collapse(object me)
{
        object ob=this_object();
        object shugan;
        message_vision("ֻ������һ���������Ӹ����۶ϣ������ź�¡һ�����죬����������\n",ob);
        shugan=new("/d/mingjiao/obj/shugan");
        shugan->move(environment(ob));
        set("owner",query("id",  me), shugan);
        destruct(ob);
        return 1;
}