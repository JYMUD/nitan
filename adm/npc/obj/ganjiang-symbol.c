#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "�ɽ�ʥ��" NOR, ({ "ganjiang charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "�ɽ�ʥ�����Խ���ͨ��������Ϊ��SUMMON���ߣ��Ժ������ʱ\n"
                            "�ٻ�(SUMMON)������ĵ��ߡ�\n"
                            "ָ���ʽ�� upd <����������ID> to <SUMMON�Ĵ���> \n" NOR);
                        
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_integrate", "upd");
}

int do_integrate(string arg)
{
        object me;
        object ob;
        string filename, content;
        string item, str;
        mapping data;

        if (! arg)
                return notify_fail("��Ҫ��ʲô������ʹ�ø�ʥ����\n");
        
        if (sscanf(arg, "%s to %s", item, str) != 2)
                return notify_fail("ָ���ʽ�� upd <����������ID> to <SUMMON��ID> \n");
                
        me = this_player();
        if (! objectp(ob = present(item, me)) &&
            ! objectp(ob = present(item, environment(me))))
                return notify_fail("�����Ϻ͸���û���������߰���\n");

        if (member_array(F_EQUIP, deep_inherit_list(ob)) == -1 &&
            !query("can_summon", ob) )
                return notify_fail("������Ʒ�޷�������\n");        
        
        if( query("unique", ob) || ob->is_item_make() || 
            ob->is_character() || ! clonep(ob) || ob->is_no_clone() ||
            query("task_ob", ob) || query("no_store", ob) || 
            query("maze_item", ob) )
                return notify_fail("�����Ʒ�޷�������\n");
        
        if( query("money_id", ob) )
                return notify_fail("��û�ù�Ǯ����\n"); 
                
        if( query("only_do_effect", ob) || 
            query("food_supply", ob) )
                return notify_fail("�����Ʒ�޷�������\n");
                
        if (sscanf(base_name(ob), "/data/%*s"))      
                return notify_fail("������Ʒ�޷���������\n");

        if( query("equipped", ob) )
                return notify_fail("����ж�����ȡ�\n");

        if( mapp(query("can_summon", me)) && sizeof(query("can_summon", me)) )
        {
                if( member_array(str,keys(query("can_summon", me))) != -1 )
                        return notify_fail("���Ѿ���ͬ����SUMMON ID��,�����»���!\n");
                        
                if( member_array(base_name(ob),values(query("can_summon", me))) != -1 )
                        return notify_fail("�����Ʒ�Ѿ��������ˡ�\n");
        }
                
        message_sort(HIR "\n$N" HIR "�����н�˫�����Ļ��ƣ�˫������" + ob->name() + HIR "�ϣ�"
                     "�����أ�" + ob->name() + HIR "��$N" HIR "����Ѫ���ա���\n\n" NOR, me);

        tell_object(me, "���" + name() + "����" + ob->name() + "�ϣ�Ȼ����������дʣ�\n"
                        "ֻ��ʥ������һ��������" + ob->name() + "���ڣ�\n");

        tell_object(me, HIC "�����" + ob->name() + HIC"�����˲��������ı仯��\n" NOR);
        
        data = copy(ob->query_entire_dbase());
        data["item_owner"] = query("id", me);
        data["no_sell"] = 1;
        data["no_store"] = 1;
        
        if( filename=TEMPLATE_D->create_file(base_name(ob),query("id", ob),data) )
        {       
                content = @TEXT

int is_no_clone() { return 1; }

TEXT;
                write_file(filename, content);
                
                destruct(ob);    
                catch(call_other(filename, "???"));
                ob = find_object(filename);      
                if (! ob)
                {
                        write("�ļ�����������ʦ��ϵ��\n");
                        log_file("static/template", sprintf("%s %s creating  %s(%s) had errors.\n",
                                 log_time(),log_id(me),filter_color(ob->name(1)),query("id", ob)));
                        return 1;
                } else
                {
                        ob->move(me, 1);
                        //str = replace_string(str, " ", "-");
                        tell_object(me, HIG "����ɹ����Ժ����� summon " + 
                                    str + " ���ٻ�����Ʒ��\n" NOR);
                        log_file("static/template", sprintf("%s %s created  %s(%s)\n",
                                 log_time(), log_id(me),
                                 filter_color(ob->name(1)),query("id", ob)));
                }
                set("can_summon/"+str, base_name(ob), me);
                me->save();
        }                                     

        destruct(this_object());
        return 1;
}

