// enchase.c
#include <ansi.h>
inherit ITEM;

int is_tessera() { return 1; }

string chinese_s(mixed arg)
{
      if( !stringp(arg) )  return HIW "��";
      if( arg == "metal" ) return HIY "��";
      if( arg == "wood" )  return HIM "ľ";
      if( arg == "water" ) return HIB "ˮ";
      if( arg == "fire" )  return HIR "��";
      if( arg == "earth" ) return HIG "��";
}

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


string extra_long()
{
        int i, level;
        string *apply, str, msg, type;
        mapping data;
        int value;

        str =  sprintf( WHT "\n��Ʒ���� : ��Ƕ��<%s" NOR+WHT">������%d�ˣ�����%s��ʧ\n" NOR,
                        this_object()->name(), this_object()->query_weight(),
                        (this_object()->query_autoload() || query("auto_load")) ? "��" : "" );

        if( mapp(query("magic")) )
        {
                str += sprintf(WHT "ħ������ : %s\n" NOR, chinese_s(query("magic/type")));
                str += sprintf(WHT "ħ �� ֵ : %d\n" NOR, (int)query("magic/power"));
        }

        type = query("enchase/type");
        if( type )
                str += sprintf(WHT "����װ�� : %s(%s)\n" NOR, to_chinese(type), type);
        level = query("enchase/level");
        if( level )
                str += sprintf(WHT "����ȼ� : %d\n" NOR, level);

        if( mapp(data = copy(query("enchase/weapon_prop"))) )
        {
                apply = keys(data);
                for (i = 0; i<sizeof(apply); i++) {
                        value = data[apply[i]];
                        str += HBCYN "��Ƕ����" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
        }
        if( mapp(data = copy(query("enchase/armor_prop"))) )
        {
                apply = keys(data);
                for (i = 0; i<sizeof(apply); i++) {
                        value = data[apply[i]];
                        str += HBYEL "��Ƕ����" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
        }
        if( mapp(data = copy(query("enchase/rings_prop"))) )
        {
                apply = keys(data);
                for (i = 0; i<sizeof(apply); i++) {
                        value = data[apply[i]];
                        str += HBGRN "��Ƕ��Ʒ" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
        }
        if( mapp(data = copy(query("enchase/apply_prop"))) )
        {
                apply = keys(data);
                for (i = 0; i<sizeof(apply); i++) {
                        value = data[apply[i]];
                        str += HBCYN "ӵ������" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
        }

        return str;
}
