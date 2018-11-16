// Written by Lonely@chinamud.cn
// crystal.c ˮ��

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("������ˮ��", ({ "black crystal2", "crystal" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIC "һ���ɫ��ˮ�������Գ�ȡ(extract)��̬װ�������ԣ�������Ƕ��ǿ������װ����\n" NOR);
                set("value", 50000);
                set("can_extract", 1);
                set("unit", "��");
                set("autoload", 1);
        }
        setup();
}

int do_extract(object obj)
{
        object ob;
        mapping prop;
        string *ks, key, type;
        int value;

        ob = this_object();

        if( !obj ) return notify_fail("û�������Ʒ��\n");

        if( query("enchase", ob) )
                return notify_fail("������ˮ���Ѿ���ȡ��һ�������ˡ�\n");

        if( !query("enchase", obj) || !(prop=query("enchase/apply_prop", obj)) )
                return notify_fail("�����Ʒ����û�п�������ȡ�����ԡ�\n");

        if( obj->is_item_make() )
                return notify_fail("��ɫˮ��ֻ�ɳ�ȡ��̬װ�������ԡ�\n");

        if( this_player()->query_skill("enchanting", 1) < 200 &&
            !present("enchant scroll", this_player()) )
                return notify_fail("��ĸ�ħ���ղ�����Ҳû�и�ħ���ᣬ����óȻ���֡�\n");

        if( random(100) < 60 ) {
                destruct(ob);
                return notify_fail("��ȡʧ�ܣ�������ˮ����ʧ��\n");
        }
        ks = keys(prop);
        key = ks[random(sizeof(ks))];
        value = prop[key];

        delete("enchase/apply_prop/"+key, obj);
        if( sizeof(query("enchase/apply_prop", obj))<1 )
                delete("enchase/apply_prop", obj);

        if( query("skill_type", obj))type=query("skill_type", obj);
        else type=query("armor_type", obj);

        set("enchase/apply_prop/"+key, value, ob);
        set("enchase/type", type, ob);
        set("enchase/level",query("require/level",  obj), ob);

        set("set_data", 1, ob);
        if( this_player()->can_improve_skill("enchanting") )
                this_player()->improve_skill("enchanting", random(10) + 1);
        return 1;
}

string extra_long()
{
        int i, t;
        string *apply, str, msg, type;
        int value;

        str =  sprintf( YEL "\n��Ʒ���� : ��Ƕ��<ˮ��>������%d�ˣ�����%s��ʧ\n" NOR,
                        this_object()->query_weight(),
                        (this_object()->query_autoload() || query("autoload")) ? "��" : "" );

        if( query("bindowner") )
                msg = sprintf( "�Ѿ���ʹ����(%s)", query("bindowner") );
        else
                msg = "��δ��ʹ����";

        if( intp(t = query("bindable")) && t > 0 ) {
                if( t == 1 )      msg += "<װ����>";
                else if( t == 2 ) msg += "<ʰȡ�ﶨ>";
                else if( t == 3 ) msg += "<ֱ�Ӱ�>";
        }

        str += sprintf( YEL "��״̬ : %s\n\n" NOR, msg);

        if( query("enchase/apply_prop") ) {
                apply = keys(query("enchase/apply_prop"));
                for (i = 0; i<sizeof(apply); i++) {
                        value = query("enchase/apply_prop")[apply[i]];
                        str += HIK "ӵ������" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
                type = query("enchase/type");
                str += sprintf(HIK "����װ�� : %s(%s)\n" NOR, to_chinese(type), type);
                str += sprintf(HIK "����ȼ� : %d\n" NOR, query("enchase/level"));
        }

        return str;
}

string query_name() { return "��ˮ"; }