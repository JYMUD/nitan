// This program is a part of NT MudLIB
// ab_crystal.c ����ˮ��

#include <ansi.h>

inherit ITEM;

mapping dict = ([
        "axe"           :"��",
        "bow"           :"��",
        "sword"         :"��",
        "blade"         :"��",
        "club"          :"��",
        "dagger"        :"ذ��",
        "fork"          :"��",
        "hammer"        :"��",
        "staff"         :"��",
        "throwing"      :"����",
        "whip"          :"��",
        "xsword"        :"��",
        "head"          :"ͷ��",
        "neck"          :"����",
        "cloth"         :"�·�",
        "charm"         :"����",
        "rings"         :"��ָ",
        "armor"         :"����",
        "surcoat"       :"����",
        "waist"         :"����",
        "wrists"        :"����",
        "shield"        :"�ܼ�",
        "hands"         :"����",
        "boots"         :"ѥ��",
        "finger"        :"ָ��",
        "all"           :"��������",
]);

string to_chinese(string str)
{
        if (! undefinedp(dict[str]))
                return dict[str];
        else
                return str;
}

void create()
{
        set_name(HIM"����ˮ��"NOR, ({ "ability crystal", "ability", "crystal" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "���淺�ŷ�ɫ��â������ˮ�������Խ�ǩ�����װ������Ƕ��ʯ���ԡ�ǿ��Ч��\n"
                            HIM "���켰��װЧ������(store)������Ȼ���������ʧע��(infuse)���µ�ǩ��װ���ϡ�\n" NOR);
                set("value", 50000);
                set("unit", "��");
        }
        //set("set_data", 1);
        set("autoload", 1);
        setup();
}

void init()
{
        add_action("do_store", "store");
        add_action("do_infuse", "infuse");
}

int do_store(string arg)
{
        object me, ob;
        mapping magic, enchase, insert, apply, qianghua;
        string mod_name, mod_level;
        string type;
        int status;
        
        me = this_player();
        
        if( !arg || arg == "" )  
                return notify_fail("��Ҫ����ʲôװ���ϵ�������\n");

        if( !objectp(ob = present(arg, me)) && 
            !objectp(ob = present(arg, environment(me)))) 
                return notify_fail("�����Ϻ͸���û������װ������\n"); 

        if( !ob->is_item_make() )
                return notify_fail("����ˮ��ֻ�ɴ洢��ǩ��װ����������\n");

        if( !wizardp(me) && ob->item_owner() != query("id", me) )
                return notify_fail("���������������ɣ�����������ʡ�\n");

        if( query("equipped", ob) ) 
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n"); 
                
        if( !mapp(enchase = query("enchase", ob)) || !mapp(insert=query("insert", ob)) )
                return notify_fail("����ˮ��ֻ�ܴ洢��Ƕ����ʯ��װ�����ԡ�\n");
        
        if( query("can_infuse") )
                return notify_fail("����ˮ���Ѿ�������������޷��ٴ洢��\n");
                
        if( ob->is_weapon() )
                type = query("skill_type", ob);
        else
                type = query("armor_type", ob);
        
        set("can_infuse", type);
                
        status = query("status", ob); // ����
        set("status", status);
        set("status", 1, ob); 
        delete("reform", ob);
        
        if( !undefinedp(enchase["mod_prop"]) ) // ��װ
        {
                mod_name = query("mod_name", ob);
                mod_level = query("mod_level", ob);
                set("mod_name", mod_name);
                set("mod_level", mod_level);
                delete("mod_name", ob);
                delete("mod_level", ob);
                delete("mod_mark", ob);
        }
        
        set("enchase", enchase);      // ��Ƕ
        set("insert", insert);
        delete("enchase", ob);
        delete("insert", ob);
        
        qianghua = query("qianghua", ob); // ǿ��
        if( mapp(qianghua) && sizeof(qianghua) > 0 )
        {
                set("qianghua", qianghua);
                delete("qianghua", ob);
        }

        magic = query("magic", ob); // ��ľˮ��������
        if( mapp(magic) && sizeof(magic) > 0 )
        {
                set("magic", magic);
                delete("magic", ob);
        }
        
        set("set_data", 1);
        
        ob->save(); 
        
        tell_object(me, HIC "�㽫" +ob->name()+ HIC "�������洢������ˮ���ɹ���\n" NOR);
        return 1;
}

int do_infuse(string arg)
{
        object me, ob;
        mapping magic, enchase, insert, apply, qianghua, props;
        string *key;
        string type;
        int i, value, flute;
        int status;

        me = this_player();
        
        if( !arg || arg == "" )  
                return notify_fail("��Ҫ��ʲôװ��ע��������\n");

        if( !objectp(ob = present(arg, me)) && 
            !objectp(ob = present(arg, environment(me)))) 
                return notify_fail("�����Ϻ͸���û������װ������\n"); 

        if( !ob->is_item_make() )
                return notify_fail("����ˮ��ֻ�ɸ���ǩ��װ��ע��������\n");

        if( !wizardp(me) && ob->item_owner() != query("id", me) ) 
                return notify_fail("���������������ɣ�����������ʡ�\n");

        if( query("equipped", ob) ) 
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n"); 
                        
        enchase = query("enchase");
        if( !mapp(enchase) || sizeof(enchase) < 1 )
                return notify_fail("����ˮ��û�д�����κ�������\n");
        
        type = query("can_infuse");
        if(  type != query("skill_type", ob) && type != query("armor_type", ob) )
                return notify_fail("����ˮ��ֻ�ܸ�"+to_chinese(type)+"ע��������\n");
        
        /*        
        flute = enchase["flute"];
        if( query("enchase/flute", ob) < flute )
                return notify_fail(ob->name()+"���ѿ��������벻С������ˮ���д洢�����Ŀ���("+flute+")��\n");
        */
        
        if( (status = query("status")) > 1 ) // ����
        {
                set("status", status, ob);
                for( i=2;i<=status;i++ )
                {
                        addn("reform/apply_prop/max_jing", 1000*i, ob);     // ���Ӿ�
                        addn("reform/apply_prop/max_qi", 2000*i, ob);       // ������
                }
                
                if( type == "rings" || type == "neck" || type == "charm" )
                {
                        addn("reform/apply_prop/research_effect", status-1, ob);
                        addn("reform/apply_prop/derive_effect", status-1, ob);
                        addn("reform/apply_prop/practice_effect", status-1, ob);
                }
                if( query("status") == 6 )
                {
                        if( type == "rings" || type == "neck" || type == "charm" )
                        {
                                addn("reform/apply_prop/research_effect", 3, ob);
                                addn("reform/apply_prop/derive_effect", 3, ob);
                                addn("reform/apply_prop/practice_effect", 3, ob);
                        }
                
                        if( ob->is_weapon() )
                        {
                                props = query("weapon_prop", ob);
                                map_delete(props, "damage");
                        }
                        else 
                        {
                                props = query("armor_prop", ob);
                                map_delete(props, "unarmed_damage");
                                map_delete(props, "armor");
                        }
                        if( sizeof(props) > 0 )
                        {
                                key = keys(props);
                                for( i=0;i<sizeof(key);i++ )
                                {
                                        value = EQUIPMENT_D->query_prop_value(key[i], 3, 1); // ǿ��ֵ
                                        if( query("quality_level", ob) == 4 )
                                        {
                                                if( sizeof(key) == 1 )
                                                        value = value * 3;
                                        } else
                                        if( query("quality_level", ob) == 5 )
                                        {
                                                if( sizeof(key) == 1 )
                                                        value = value * 4;
                                                else if( sizeof(key) == 2 )
                                                        value = value * 2;
                                        } else
                                        if( query("quality_level", ob) == 6 )
                                        {
                                                if( sizeof(key) == 1 )
                                                        value = value * 16;
                                                else if( sizeof(key) == 2 )
                                                        value = value * 8;
                                                else if( sizeof(key) == 3 )
                                                        value = value * 4;
                                                else
                                                        value = value * 2;
                                        }
                                        addn("reform/apply_prop/"+key[i], value, ob); 
                                }
                        }
                }
        }
                 
        set("enchase", enchase, ob);  // ��Ƕ
        insert = query("insert");
        set("insert", insert, ob);
        qianghua = query("qianghua");   // ǿ��
        if( mapp(qianghua) && sizeof(qianghua) > 1 )
                set("qianghua", qianghua, ob);

        magic = query("magic");   // ��ľˮ��������
        if( mapp(magic) && sizeof(magic) > 1 )
                set("magic", magic, ob);
        
        if( query("mod_name") )    // ��װ
        {
                set("mod_name", query("mod_name"), ob);
                set("mod_mark", base_name(ob), ob);
        }

        if( query("mod_level") )
                set("mod_level", query("mod_level"), ob);
                                
        ob->save();
        
        tell_object(me, HIC "�㽫����ˮ���е�����ע��" +ob->name()+ HIC "�ɹ���\n" NOR);
        destruct(this_object());
        return 1;
}

string extra_long()
{
        mapping enchase, qianghua;
        string *apply, str, type;
        int value;
        int i;

        str =  sprintf( YEL "\n��Ʒ���� : ������<����ˮ��>������%d�ˣ�����%s��ʧ\n" NOR,
                        this_object()->query_weight(),
                        (this_object()->query_autoload() || query("autoload")) ? "��" : "" );

        if( mapp(enchase=copy(query("enchase/apply_prop"))) ) 
        {
                type = query("can_infuse");
                str += sprintf(HIK "��ħװ�� : %s(%s)\n" NOR, to_chinese(type), type);
                apply = keys(enchase);
                for (i = 0; i<sizeof(apply); i++) 
                {
                        value = enchase[apply[i]];
                        str += HIK "ӵ������" NOR " : ";
                        str += HIB + EQUIPMENT_D->chinese(apply[i], value) + NOR + "\n";
                }    
        }

        if( mapp(enchase=query("enchase/mod_prop")) ) 
        {
                apply = keys(enchase);
                for (i = 0; i<sizeof(apply); i++) 
                {
                        value = enchase[apply[i]];
                        str += HIK "ӵ������" NOR " : ";
                        str += HIB + EQUIPMENT_D->chinese(apply[i], value) + NOR + "\n";
                }
        }
                
        if( mapp(qianghua=query("qianghua/apply_prop")) ) 
        {
                apply = keys(qianghua);
                for (i = 0; i<sizeof(apply); i++) 
                {
                        value = qianghua[apply[i]];
                        str += HIK "ӵ������" NOR " : ";
                        str += HIB + EQUIPMENT_D->chinese(apply[i], value) + NOR + "\n";
                }
        }
        
        return str;
}

string query_name() { return HIM"����ˮ��"NOR; }
