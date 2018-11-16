// xiandan.c �ɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "ħ����Ĺ�" NOR, ({ "magic fruit", "magic", "fruit" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ��ͬʱ��������ħ��ͷ��Ĺ�ʵ����˵�����Ժ��������Ե����µĺ���֢��\n");
                set("value", 10000);
                set("unit", "��");
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);

        if( query("gift/int/fail", me) )
        {
                addn("gift/int/fail", -1, me);
                if( query("gift/int/all", me) )
                {
                        addn("gift/int/all", -1, me);
                        if( query("gift/int/all", me)<1 )
                                delete("gift/int/all", me);
                }
                else
                        addn("gift/xiandan", -1, me);
                if( query("gift/int/fail", me)<1 )
                        delete("gift/int/fail", me);
        } else
        if( query("gift/str/fail", me) )
        {
                addn("gift/str/fail", -1, me);
                if( query("gift/str/all", me) )
                {
                        addn("gift/str/all", -1, me);
                        if( query("gift/str/all", me)<1 )
                                delete("gift/str/all", me);
                }
                else
                        addn("gift/shenliwan", -1, me);
                if( query("gift/str/fail", me)<1 )
                        delete("gift/str/fail", me);
        } else
        if( query("gift/con/fail", me) )
        {
                addn("gift/con/fail", -1, me);
                if( query("gift/con/all", me) )
                {
                        addn("gift/con/all", -1, me);
                        if( query("gift/con/all", me)<1 )
                                delete("gift/con/all", me);
                }
                else
                        addn("gift/xisuidan", -1, me);
                if( query("gift/con/fail", me)<1 )
                        delete("gift/con/fail", me);
        } else  
        if( query("gift/dex/fail", me) )
        {
                addn("gift/dex/fail", -1, me);
                if( query("gift/dex/all", me) )
                {
                        addn("gift/dex/all", -1, me);
                        if( query("gift/dex/all", me)<1 )
                                delete("gift/dex/all", me);
                }
                else
                        addn("gift/unknowdan", -1, me);
                if( query("gift/dex/fail", me)<1 )
                        delete("gift/dex/fail", me);
        } 
        
        tell_object(me, HIG "һ�ɻ�����Ȼ��ȫ������"
                            "��ȫ�����ѣ�ǡ�ڴ�ʱһ����̹֮��"
                            "��Ȼ���𣬶ٸ�ȫ��������ˡ�\n" NOR);

        destruct(this_object());
        return 1;
}

