// mask.c
//

inherit ITEM;

void create()
{
        set_name("���", ({ "mian ju", "mask" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "���ƺ���һ������Ƥ�Ƴɵ���ߡ�\n");
                set("value", 10000);
        }
        setup();
}

void init()
{
        add_action("do_pretend", "pretend");
}

int do_pretend(string arg)
{
        object who;
        object me;
        string *mask;
        string pshort;

        if (! arg)
                return notify_fail("�����װ˭��\n");

        me = this_player();
        if (arg == "none" || arg == "cancel")
        {
                if (! query_temp("owner"))
                        return notify_fail("�����ڲ�û��ʹ����ߡ�\n");

                delete_temp("apply/name", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);
                message_vision("$N������ȡ����һ����Ƥ��ߡ�\n", me);
                return 1;
        }

        if (me->query_skill("pretending", 1) < 100)
                return notify_fail("���������������ȥ�����ǲ���ʹ�á�\n");

        if( query("age", me) >= 60 && 
            !query("special_skill/youth", me) )
                return notify_fail("��̫���ˣ����԰����\n");

        if (me->query_condition("killer"))
                return notify_fail("ͨ�����޷�����ߡ�\n");

        if( sscanf(base_name(environment(me)), "/maze/battle%*s") )
                return notify_fail("ս�����޷�����ߡ�\n");

        if (! objectp(who = present(arg, environment(me))) || 
            ! living(who))
                return notify_fail("�����װ˭��\n");

        if (wizardp(who))
                return notify_fail("���޷��ٰ���ʦ��\n");

        if( !query("can_speak", who) )
                return notify_fail("�ٰ�" + who->name() + "������̫���˵㡣\n");

        // ��Ϊ����short()��ʱ�������Է���״̬�����Բ�ֱ��
        // ����who->short()������ֱ�ӿ����ƶԷ���Ӧ��short()��
        // ���û�о͸��ƶԷ�����ʵshort()��
        if( sizeof(mask=query_temp("apply/short", who)) )
                pshort = mask[sizeof(mask) - 1];
        else
                pshort = who->short(1);

        write("�㿪ʼ��װ" + who->name() + "��\n");
        set_temp("apply/name", ({who->name()}), me);
        set_temp("apply/short", ({pshort}), me);
        set_temp("apply/long", ({who->long()}), me);
        set_temp("owner", me);
        return 1;
}

int move(mixed dest)
{
        object me;

        if (me = query_temp("owner"))
        {
                delete_temp("apply/name", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);
                delete_temp("owner");
        }

        return ::move(dest);
}

void remove(string euid) 
{
        object me;

        if (me = query_temp("owner"))
        {
                delete_temp("apply/name", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);
                delete_temp("owner");
        }

        ::remove(euid);
}
int query_autoload() { return 1; }
