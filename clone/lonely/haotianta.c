#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIM + "�����" NOR, ({ "haotian ta", "haotian", "ta" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIM "����һ��ӵ�����ǻ���֮���ı�������ʱ�ش���Ͷ���\n"
                                "����Ĺ�â��\n"                                
                                "�����ͨʮ������ﵽ��������ܽ��ø���֮������������\n" 
                                "*����֮���������ֻ�˾�У�use haotian ta����\n"NOR);

        }
        setup();
}

void init()
{
        add_action("do_use", "use");       
}

int do_use(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("haotian ta", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");
        
        if( !query("outdoors", environment(me)) )
                 return notify_fail("����ȵ�����ȥ��\n");
                 
        message_sort(HIM + "\n$N" HIM "�������е����������Ȼ�䣬��ɫ��â�����������"
                     "������$N���˽�ȥ��\n" NOR, me);
                
        me->move("/kungfu/class/sky/lunhuisi");
        set("startroom", "/kungfu/class/sky/lunhuisi", me);
        destruct(this_object());

        return 1;
}
