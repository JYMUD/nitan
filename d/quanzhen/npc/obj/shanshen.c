// shanshen.c ��ɽ��

inherit ITEM;

void create()
{
        set_name("��ɽ��", ({"laoshan shen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ��մ��ɽ�����ɽ�Ρ�\n");
                set("value", 10000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if( query("eff_qi", me)>query("max_qi", me)-20 )
                return notify_fail("������û�б�Ҫ������֧��ɽ�Ρ�\n");

        addn("eff_qi", 200, me);

        message_vision("$N����һ����ɽ�Σ�ֻ���û���һ����������ð������ !\n", this_player());
        destruct(this_object());
        return 1;
}