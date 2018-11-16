
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "Ѫ֮����" NOR, ({ "blood taboo", "blood", "taboo" }));
        set_weight(30);

        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIW "һƿӨ��͸Ѫ֮���ɣ�ɢ���ѤĿ�Ĺ�ʡ�\n"
                            "����������ֱ�ӽ��(jiechu)����ħ����֮��ǩ����Ѫ֮��Լ��\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "ƿ");
        }
        set("auto_load", 1);
        setup();
}

void init()
{
        add_action("do_remove", ({ "jiechu", "remove" }));
}

int do_remove(string arg)
{
        object me;
        object warcraft;
        string filename;

        me = this_player();

        if( !query("warcraft", me) )
                return notify_fail("��û�к��κ�һֻħ����ǩ����Լ��������Ѫ֮��Լ��\n");
        
        filename = "/data/warcraft/" + query("id", me);
        if (file_size(filename + ".c") > 0) 
        {
                if (warcraft = find_object(filename)) 
                {
                        tell_object(me, HIR "����" + warcraft->name() + HIR "֮���Ѫ֮��Լ�Ѿ������\n" NOR);
                        destruct(warcraft); 
                }
                
                DBASE_D->clear_object(filename); 
                rm(filename + ".c"); 
        }
        
        delete("can_whistle", me); 
        delete("warcraft", me);
        me->save();
        
        destruct(this_object());
        return 1;
}

