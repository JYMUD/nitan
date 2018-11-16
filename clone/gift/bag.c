
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "����" NOR, ({ "bag" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");                
        }
        setup();
}

void init()
{
        add_action("do_open", "open");
}

int do_open(string arg)
{

        object me, ob;
        int exp, qn;
        string sob, msg;
        string *gifts =({
                       "/clone/fam/gift/con2",
                       "/clone/fam/gift/dex2",
                       "/clone/fam/gift/str2",
                       "/clone/fam/gift/int2",
                       "/clone/fam/pill/full1",
                       "/clone/fam/pill/sheli4",
                       "/clone/fam/pill/xuelian3",
                       "/clone/fam/pill/lingzhi3",
                           "/clone/fam/pill/puti2",
               "/clone/fam/gift/con1",
               "/clone/fam/gift/str1",
               "/clone/fam/gift/dex1",
               "/clone/fam/gift/int1",
               "/clone/fam/pill/food",
               "/clone/fam/pill/food1",
               "/clone/fam/pill/linghui1",
               "/clone/fam/pill/lingzhi1",
               "/clone/fam/pill/neili1",
               "/clone/fam/pill/puti1",
               "/clone/fam/pill/renshen1",
               "/clone/fam/pill/water",
               "/clone/fam/pill/xuelian1",
               "/clone/food/baozi",
               "/clone/food/fish",
               "/clone/food/jiudai",
               "/clone/food/peanut",
               "/clone/food/xia",
               "/clone/money/gold",
               "/clone/gift/jinkuai",                
               "/clone/tattoo/face1",
               "/clone/tattoo/face2",
               "/clone/fam/gift/int2",
               "/clone/fam/gift/str2",
               "/clone/fam/gift/con2",
               "/clone/fam/gift/dex2",
               "/clone/fam/etc/va2",
               "/clone/fam/etc/va3",
               "/clone/fam/etc/va4",
               "/clone/fam/etc/va5",
               "/clone/fam/item/stone3",
               "/clone/fam/item/stone4",
               "/clone/fam/item/stone5",                                   
        });

        me = this_player();

        if (environment(this_object()) != me)return 0;

        if (random(10) < 3)
        {                
                write("��򿪰���һ�������澡��һЩ��ֵǮ�Ķ��������ֽ�֮����һ�ߡ�\n");
                destruct(this_object());
                return 1;
        }

        // ��ȡһЩ����
        exp = me->query("combat_exp") / 1000000 + 50 + random(100);
        qn = 50 + random(200);

        sob = gifts[random(sizeof(gifts))];

        ob = new(sob);

        if (objectp(ob))
        {
                msg = HIR "\n������ " + chinese_number(exp) + " ��ʵս���鼰 " + chinese_number(qn) + " ��Ǳ�ܡ�\n" NOR;
                msg += HIY "���" + this_object()->name() + HIY "�ѳ�" + ob->name() + HIY "��\n\n" NOR;
                tell_object(me, msg);
                ob->move(me, 1);
                me->add("combat_exp", exp);
                me->add("potential", qn);
        }
        else
        {
                write("���" + sob + " ����\n");
        }

        destruct(this_object());
        return 1;
}

