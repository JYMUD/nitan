// itemmake.c ���Ƶ���

#include <ansi.h>
#include <name.h>
#include <move.h>
#include <command.h>

inherit F_OBSAVE;
inherit F_NOCLONE;

int is_item_make() { return 1; }

#define LEVEL1          5
#define LEVEL2          10
#define LEVEL3          30
#define LEVEL4          100
#define LEVEL5          300
#define LEVEL6          1000
#define LEVEL7          3000
#define LEVEL8          10000
#define LEVEL9          25000
#define MAX_LEVEL       LEVEL9
#define ULTRA_LEVEL     (LEVEL9 + 1)

nosave int *levels = ({ LEVEL1, LEVEL2, LEVEL3, LEVEL4,
                        LEVEL5, LEVEL6, LEVEL7, LEVEL8,
                        LEVEL9 });

nosave int performing  = 0;
nosave int attack_lvl  = 0;
nosave int defense_lvl = 0;
nosave string *qianghua_level = ({
        HBRED"��"NOR,
        HBRED"��"NOR,
        HBRED"���"NOR,
        HBRED"����"NOR,
        HBRED"�����"NOR,
        HBRED"������"NOR,
        HBRED"�������"NOR,
        HBRED"��������"NOR, 
        HBRED"���������"NOR, 
        HBRED"����������"NOR, 
}); 

int is_stay_in_room() { return attack_lvl >= ULTRA_LEVEL; }
int is_ultimate()
{
        return attack_lvl >= ULTRA_LEVEL || query("ultimate/69") || 
               query("ultimate/87") || query("ultimate/105") || query("ultimate/121");
}

string chinese_s(mixed arg)
{
      if( !stringp(arg) )  return HIW "��";
      if( arg == "metal" ) return HIY "��";
      if( arg == "wood" )  return HIM "ľ";
      if( arg == "water" ) return HIB "ˮ";
      if( arg == "fire" )  return HIR "��";
      if( arg == "earth" ) return HIG "��";
      if (arg == "cold")   return HIW "��";
      if (arg == "fire")   return HIR "��";
      if (arg == "magic")  return HIY "ħ";
      if (arg == "lighting")return HIM "��";
}

// ����������ID - ͨ���ļ����������ж�
string item_owner()
{
        string owner;
        if( sscanf(base_name(this_object()), ITEM_DIR "%*s/%s-%*s", owner) )
                return owner;

        return 0;
}

// �жϸ������Ƿ񱻵�ǰĳ��������
int is_not_belong_me(object me)
{
        string user;

        user = query("user");
        if( !user || !sscanf(user, "%*s(" + query("id", me) + ")") )
                return 1;

        return 0;
}

// ����װ���ĵȼ�
int weapon_level()
{
        mapping o;
        string *ks;
        mixed lvl;
        int i;

        lvl = 0;
        o = query("owner");
        if( mapp(o) ) {
                ks = keys(o);
                for (i = 0; i < sizeof(ks); i++)
                        lvl += o[ks[i]];
        }

        lvl /= 100;
        lvl = atoi(lvl);
        if( lvl > MAX_LEVEL ) lvl = MAX_LEVEL;

        if( lvl == MAX_LEVEL && query("magic/power") )
                // ����ħ������
                lvl = ULTRA_LEVEL;
        return lvl;
}

// ����װ���ĵȼ�
int armor_level()
{
        // More to be added
        // �������ӵȼ�?
        return 0;
}

// ����װ���ĳ�����
string weapon_long()
{
        string  n;
        mapping need;
        mapping c;
        int type;
        int k;
        int lvl;
        string tessera_name;
        string result = "";

        c = query("combat");
        n = query("unit") + name();
        if( !c )
                return "��" + n + "��Ȼ��û��������Ѫ�����洿����Ͼ��\n";
        k = c["MKS"] + c["PKS"];

        if( c["WPK_GOOD"] < k / 2 &&
            c["WPK_BAD"]  < k / 2 )
                type = 0;
        else
        if( c["WPK_GOOD"] > c["WPK_BAD"] * 2 )
                type = -1;
        else
                type = 1;

        if( c["MKS"] + c["PKS"] < 10 )
                return "��" + n + "�����Ѿ��ù���Ѫ��������������Ѫ�ۡ�\n";

        attack_lvl = weapon_level();
        lvl = sizeof(levels);
        while (--lvl)
                if( attack_lvl >= levels[lvl] )
                        break;
        lvl++;
        
        switch (type)
        {
        case 1:
                if( attack_lvl >= ULTRA_LEVEL )
                        result = HIY "������ȥƽƽ������û�а�����⣬ֻ��"
                                 "���������˸е��ǲ��������ʡ�\n" NOR;
                else
                if( attack_lvl >= MAX_LEVEL )
                        result = HIY "������ȥ���˷����������޳羴��һ��"
                               "�Ȼ������Ȼ���棬�ľߵ����緶������\n"
                               "���£�������·�����ɷ���ѵ�����Ǵ�˵�в�"
                               "����ֵ�����֮" + name() + HIY "��\n" NOR;
                else
                if( attack_lvl >= LEVEL8 )
                        result = HIC "һ����ȥ��������������������ڷ��"
                               "���裬�������أ�����֮�����ƺ�Ҫ�ط�\n"
                               "�˼䡣���̲�סҪ��̾һ����������ħ��Ҳ�������١�\n" NOR;
                else
                if( attack_lvl >= LEVEL7 )
                        result = HIC "�����渽���Ų�֪�����׻꣬����а��"
                               "��ħ�������£�һ�ɰ�����Ȼ��ɢ������\n"
                               "�̲�ס���˸���ս��\n" NOR;
                else
                if( attack_lvl >= LEVEL6 )
                        result = HIR "������ȥ���˾��Ķ��ǣ����������������" + name() + HIR
                               "��������ɷ�ʹ˱������ɾ��˼����塣\n" NOR;
                else
                if( attack_lvl >= LEVEL5 )
                        result = HIR "����������Ȼ͸��һ��Ѫ�⣬�������������"
                               "����������һʱ����ħ������" + name() + HIR "�µ��λꡣ\n" NOR;
                else
                if( attack_lvl >= LEVEL4 )
                        result = HIW "����ǽ��������������֮һ��" + name() + HIW
                               "�����׼���֮ͽ�������޲��ĳ���ҡ��\n" NOR;
                else
                if( attack_lvl >= LEVEL3 )
                        result = HIW "��" + n + HIW "��һ������ɢ�������������������׻겻�١�\n" NOR;
                else
                if( attack_lvl >= LEVEL2 )
                        result = RED "��" + n + RED "��Ȼ͸��һ��������"
                               "������ɱ�˲����׶�֮ͽ��\n" NOR;
                else
                if( attack_lvl >= LEVEL1 )
                        result = RED "ϸ��֮�£��п���һ˿Ѫ�ۣ��������ɱ�˲���"
                               "����Ѫ�ڴ˰ɣ�\n" NOR;
                else
                        result = CYN "���ó���" + n + CYN "����ɱ�������׶�֮ͽ��\n" NOR;
                break;

        case -1:
                if( attack_lvl >= ULTRA_LEVEL )
                        result = HIR "������ȥƽƽ������û�а�����⣬����"
                                 "��֪Ϊ��ȴ�������˸е���Щ������\n" NOR;
                else
                if( attack_lvl >= MAX_LEVEL )
                        result = HIR "������ȥ���˴��ĵ׷��������⣬��"
                               "��Ȼ�����ƺ�����������ԩ�꣬����ȫȻ\n����" + n + HIR
                               "�����ɱ�����ƣ��ѵ�����Ǵ�˵�вŻ���ֵ�а��֮" + name() + HIR
                               "��\n" NOR;
                else
                if( attack_lvl >= LEVEL8 )
                        result = HIC "һ����ȥ���������������ԩ��������"
                               "�����������أ�����֮�������̲�ס����\n"
                               "����ս�������ٿ��ڶ��ۡ�\n" NOR;
                else
                if( attack_lvl >= LEVEL7 )
                        result = HIC "�����渽���Ų�֪����ԩ�꣬��������"
                               "�������£�һ��Թ��ֱ�������������̲�\n"
                               "ס���˸���ս��\n" NOR;
                else
                if( attack_lvl >= LEVEL6 )
                        result = HIW "������ȥ���˾��Ķ��ǣ����������������" + name() + HIW
                               "����֪����Ӣ�۾ʹ����ޡ�\n" NOR;
                else
                if( attack_lvl >= LEVEL5 )
                        result = HIW "����������Ȼ͸��һ��Ѫ�⣬�������������"
                               "����������һʱ�ĸ��ֶ�����" + name() + HIW "�µ��λꡣ\n" NOR;
                else
                if( attack_lvl >= LEVEL4 )
                        result = HIG "����ǽ���������������֮һ��" + name() + HIG
                               "��˭������ô��������ʿ�������¡�\n" NOR;
                else
                if( attack_lvl >= LEVEL3 )
                        result = HIG "��" + n + HIG "��һ������ɢ�������������������λ겻�١�\n" NOR;
                else
                if( attack_lvl >= LEVEL2 )
                        result = RED "��" + n + RED "��Ȼ͸��һ��������������ɱ�˲����ˡ�\n" NOR;
                else
                if( attack_lvl >= LEVEL1 )
                        result = RED "ϸ��֮�£��п���һ˿Ѫ�ۣ��������ɱ�˲���"
                               "����Ѫ�ڴ˰ɣ�\n" NOR;
                else
                        result = CYN "���ó���" + n + CYN "����ɱ����������֮ʿ��\n" NOR;
                break;

        default:
                if( attack_lvl >= ULTRA_LEVEL )
                        result = HIC "������ȥƽƽ������û�а�����⣬ֻ��һ��"
                                 "ƽ��֮���ı������ѡ�\n" NOR;
                else
                if( attack_lvl >= MAX_LEVEL )
                        result = HIC "����Ȼ���⣬�ƺ���Ҫ�ڿն�ȥ������"
                               "���磬�������С���������·������\n"
                               "��������֮����ԩ�겻�衢Ⱥа���ף��޲�����" + n + HIC
                               "�Ϲ�����İ������ơ�\n" NOR;
                else
                if( attack_lvl >= LEVEL8 )
                        result = HIM "һ����ȥ����������������λ�������"
                               "�����������أ�����֮�������ʱ������\n"
                               "�����ޱȣ���������ס��\n" NOR;
                else
                if( attack_lvl >= LEVEL7 )
                        result = HIM "�����渽���Ų�֪�����λ꣬������а"
                               "����ɥ�����£�һ��Թ��������Ȼ������\n"
                               "�����̲�ס���˸���ս��\n" NOR;
                else
                if( attack_lvl >= LEVEL6 )
                        result = HIR "������ȥ���˾��Ķ��ǣ����������������" + name() + HIR
                               "��������а���ֶ����Ӵ˽٣������ֻء�\n" NOR;
                else
                if( attack_lvl >= LEVEL5 )
                        result = HIR "����������Ȼ͸��һ��Ѫ�⣬�������������"
                               "����������һʱ�ĸ��ֶ�������" + n + HIR "�µ��λꡣ\n" NOR;
                else
                if( attack_lvl >= LEVEL4 )
                        result = HIW "����ǽ���������������֮һ��" + name() + HIW
                               "��˭���뵽��ô������������¡�\n" NOR;
                else
                if( attack_lvl >= LEVEL3 )
                        result = HIW "��" + n + HIW "��һ��ɱ��ɢ�������������������λ겻�١�\n" NOR;

                else
                if( attack_lvl >= LEVEL2 )
                        result = RED "��" + n + RED "��Ȼ͸��һ��ɱ����������ɱ�˲����ˡ�\n" NOR;

                else
                if( attack_lvl >= LEVEL1 )
                        result = RED "ϸ��֮�£��п���һ˿Ѫ�ۣ��������ɱ�˲���"
                               "����Ѫ�ڴ˰ɣ�\n" NOR;
                else
                        result = CYN "���ó���" + n + CYN "����ɱ�������ˡ�\n" NOR;
                break;
        }
        /*
        if( attack_lvl == ULTRA_LEVEL ) {
                if( stringp(tessera_name = query("magic/tessera")) )
                        result += "��������Ƕ��" + tessera_name + "����˸������Ĺ�â��\n";
                if( query("ultimate/121") )
                        result += HIY + name() + HIY "�ĵȼ���̫����Ʒ  LV10\n" NOR;
                else
                if( query("ultimate/105") )
                        result += HIY + name() + HIY "�ĵȼ���Զ����Ʒ  LV10\n" NOR;
                else
                if( query("ultimate/87") )
                        result += HIY + name() + HIY "�ĵȼ����Ϲ���Ʒ  LV10\n" NOR;
                else
                        result += HIY + name() + HIY "�ĵȼ���������Ʒ  LV10\n" NOR;
        } else if( lvl ) {
                result += HIY + name() + HIY "�ĵȼ���" + lvl + "/9\n" NOR;

                if( query("magic/imbue_ok") )
                        result += HIM + name() + HIM "�Ѿ���ֵĽ����ˣ���Ҫ"
                                  "��Ƕ�Գ�ַ���������\n" NOR;
                else
                if( (n = query("magic/imbue")) > 0 )
                        result += HIM + name() + HIM "�Ѿ��������������" +
                                  chinese_number(n) + "�Σ����ڼ�������Ǳ�ܡ�\n" NOR;
        }
        */

        
        if( query_temp("bonus/success_points") ) 
                result += HIM "Ŀǰ��װ��ǿ��ʱ����" + HIY + sprintf("%d", query_temp("bonus/success_points")) + "%"HIM"�ĳɹ��ʣ���һ����Ч����\n" NOR; 
        if( query_temp("bonus/avoid_reduce") ) 
                result += HIM "Ŀǰ��װ��ǿ��ʱʧ�ܺ󲻻���ʧǿ���ȼ�����һ����Ч����\n" NOR; 
                
        result += sprintf(NOR "%s\n" NOR, qianghua_level[query("qianghua/level")]);
        
        result += sprintf(HIW "ħ������ : %s\n" NOR, chinese_s(query("magic/type")));
        result += sprintf(HIW "ħ �� ֵ : %d\n" NOR, query("magic/power"));
        result += sprintf(HIW "�� �� �� : %d\n" NOR, query("magic/blood"));
        if( this_object()->is_unarmed_weapon() )
                result += sprintf(HIW "�� �� �� : %d\n" NOR, query("armor_prop/unarmed_damage"));
        else
                result += sprintf(HIW "�� �� �� : %d\n" NOR, query("weapon_prop/damage"));
        result += sprintf(HIW "ɱ    ¾ : %d\n" NOR, query("combat/PKS"));
        result += sprintf(HIW "��Ƕ���� : %d\n" NOR, (int)query("enchase/flute"));
        //result += sprintf(HIW "�������� : %d\n" NOR, (int)query("enchase/wash"));
        if( query("mod_level") )
                result += sprintf(HIC "��װ�ȼ� : %s\n" NOR, query("mod_level"));
        /*
        if( mapp(need = query("require")) && sizeof(need) )
                foreach (string key in keys(need))
                        result += sprintf(RED "װ��Ҫ�� : %s  %d\n" NOR,
                                       to_chinese(key), need[key]);
        // result += sprintf(HIW "���߶�ʧ : %s\n" NOR, "��");
        */
        return result;
}

// ����װ���ĳ�����
string armor_long()
{
        mapping need;
        string result = "";

        if( query("ultimate/87") )
                result += HIY + name() + HIY "�ĵȼ���Զ����Ʒ\n" NOR;
        else
        if( query("ultimate/69") )
                result += HIY + name() + HIY "�ĵȼ����Ϲ���Ʒ\n" NOR;
        else
        if( query("ultimate/37") || query("ultimate/39") )
                result += HIY + name() + HIY "�ĵȼ���������Ʒ\n" NOR;

        if( query_temp("bonus/success_points") ) 
                result += HIM "Ŀǰ��װ��ǿ��ʱ����" + HIY + sprintf("%d", query_temp("bonus/success_points")) + "%"HIM"�ĳɹ��ʣ���һ����Ч����\n" NOR; 
        if( query_temp("bonus/avoid_reduce") ) 
                result += HIM "Ŀǰ��װ��ǿ��ʱʧ�ܺ󲻻���ʧǿ���ȼ�����һ����Ч����\n" NOR; 
                
        result += sprintf(NOR "%s\n" NOR, qianghua_level[query("qianghua/level")]);

        result += sprintf(HIW "ħ������ : %s\n" NOR, chinese_s(query("magic/type")));
        result += sprintf(HIW "�� �� �� : %d\n" NOR, query("armor_prop/armor"));
        result += sprintf(HIW "��Ƕ���� : %d\n" NOR, (int)query("enchase/flute"));
        //result += sprintf(HIW "�������� : %d\n" NOR, (int)query("enchase/wash"));
        if( query("mod_level") )
                result += sprintf(HIC "��װ�ȼ� : %s\n" NOR, query("mod_level"));
        /*
        if( mapp(need = query("require")) && sizeof(need) )
                foreach (string key in keys(need))
                        result += sprintf(RED "װ��Ҫ�� : %s  %d\n" NOR,
                                       to_chinese(key), need[key]);
        // result += sprintf(HIW "���߶�ʧ : %s\n" NOR, "��");
        */

        return result;
}

// ����ͨ����װ��
int is_weapon()
{
        return stringp(query("skill_type"));
}

// �ǿ�������װ��
int is_unarmed_weapon()
{
        return query("armor_type") == "hands" ||
               query("armor_type") == "finger";
}

// ���ߵĳ�����
string item_long()
{
        if( is_weapon() || is_unarmed_weapon() )
                return weapon_long();

        return armor_long();
}

// ����װ�����˺�ֵ
int apply_damage()
{
        int d;
        int p;
        int r;
        int s;
        mixed q;

/*
        attack_lvl = weapon_level();
        p = query("point");
        //d = attack_lvl * p / MAX_LEVEL + query("bless") * 10; // Ǭ��ʥˮʥ��һ������ʮ�㹥��
        d = attack_lvl * p / MAX_LEVEL + query("require/level") * 10;
        return d + p;
*/
        p = query("quality_level");
        d = query("require/level");
        r = query("status");
        s = (d + r * 15) * p * 10;
        q = ITEM_D->qianghua_effect(this_object(), "weapon"); 
        s += s * q;
        return s;
}

// ����װ������Чֵ
int apply_armor()
{
        int d;
        int p;
        int r;
        int s;
        mixed q;

/*
        defense_lvl = armor_level();
        p = query("point");
        //if( d > p * 3 / 2) d = p * 3 / 2 + query("bless") * 10;// Ǭ��ʥˮʥ��һ������10�����
        //d = p * 3 / 2 + query("bless") * 2;// Ǭ��ʥˮʥ��һ������2�����
        d = p * 3 / 2 + query("require/level") * 2;
        return d + p;
*/
        p = query("quality_level");
        d = query("require/level");
        r = query("status");
        s = (d + r * 15) * p * 2;
        q = ITEM_D->qianghua_effect(this_object(), "armor"); 
        s += s * q;
        return s;
}

// ���б������ݵĽӿں���
mixed save_dbase_data()
{
        mapping data;
        object  user;

        data = ([ "combat" : query("combat"),
                  "owner"  : query("owner"),
                  "magic"  : query("magic"),
                  "quality_level" : query("quality_level"),
                  "status" : query("status"),
                  "require"   : query("require"),
                  //"makeinfo"  : query("makeinfo"),
                  "mod_name"   : query("mod_name"),
                  "mod_mark"   : query("mod_mark"),
                  "mod_level"  : query("mod_level"),
                  "mod_prop"   : query("mod_prop"),
                  //"modfile"  : query("modfile"),
                  //"color"   : query("color"),
                  //"colorname"   : query("colorname"),
                  "enchase"     : query("enchase"),
                  "insert"      : query("insert"),
                  "reform"      : query("reform"),
                  "qianghua"    : query("qianghua"),
                  "ultimate"    : query("ultimate"),
                  "consistence" : query("consistence"),
                  "bless"       : query("bless"),
                  "stable"      : query("stable")]);

        if( !(user = environment()) )
                data += ([ "user" : query("user") ]);
        else
        if( playerp(user) )
                data += ([ "user" : user->name(1) + "(" + query("id", user) + ")" ]);

        return data;
}

// ���ܴ������ݵĽӿں���
int receive_dbase_data(mixed data)
{
        if( !mapp(data) )
                return 0;

        if( mapp(data["combat"]) )
                set("combat", data["combat"]);

        if( mapp(data["owner"]) )
                set("owner", data["owner"]);

        if( mapp(data["magic"]) )
                set("magic", data["magic"]);

        if( intp(data["quality_level"]) )
                set("quality_level", data["quality_level"]);

        if( intp(data["status"]) )
                set("status", data["status"]);
                
        if( mapp(data["require"]) )
                set("require", data["require"]);

        //if( stringp(data["makeinfo"]) )
        //        set("makeinfo", data["makeinfo"]);

        if( stringp(data["mod_name"]) )
                set("mod_name", data["mod_name"]);

        if( stringp(data["mod_mark"]) )
                set("mod_mark", data["mod_mark"]);

        if( stringp(data["mod_level"]) )
                set("mod_level", data["mod_level"]);
   
        if( mapp(data["mod_prop"]) )
                set("mod_prop", data["mod_prop"]);
                            
        //if( stringp(data["color"]) )
        //        set("color", data["color"]);

        //if( stringp(data["colorname"]) )
        //        set("colorname", data["colorname"]);

        if( mapp(data["enchase"]) )
                set("enchase", data["enchase"]);

        if( mapp(data["insert"]) )
                set("insert", data["insert"]);

        if( mapp(data["reform"]) )
                set("reform", data["reform"]);
                        
        if( mapp(data["qianghua"]) )
                set("qianghua", data["qianghua"]);
                      
        if( mapp(data["ultimate"]) )
                set("ultimate", data["ultimate"]);

        if( stringp(data["user"]) )
                set("user", data["user"]);

        if( !undefinedp(data["consistence"]) )
                set("consistence", data["consistence"]);

        if( intp(data["bless"]) )
                set("bless", data["bless"]);

        if( intp(data["stable"]) )
                set("stable", data["stable"]);

        return 1;
}

// ��ȡ���̵�����
int restore()
{
        int r;

        if( base_name(this_object()) + ".c" == __FILE__ )
                return 0;

        r = ::restore();
        set("no_sell", 1);
        set("stable", query("stable"));
        set("bless", query("bless"));
        return r;
}

// ��������
int save()
{
        int res;

        if( base_name(this_object()) + ".c" == __FILE__ )
                return 0;

        return ::save();
}

// 9/10��������������
mixed weapon_hit_ob(object me, object victim, int damage_bonus)
{
        int ap;
        int dp;
        int damage;

/*
        if( attack_lvl < MAX_LEVEL ||
            query("owner/" + query("id", me)) < MAX_LEVEL*80 )
                return;

        if( attack_lvl >= ULTRA_LEVEL &&
            mapp(query("magic")) ) {
                return ITEM_D->weapon10lv_hit_ob(me, victim, this_object(), damage_bonus);
        }
*/
        if( query("status") < 5 )
                return;

        if( query("status") >= 6 && query("magic/type") )
                return ITEM_D->weapon10lv_hit_ob(me, victim, this_object(), damage_bonus);

        return ITEM_D->weapon_hit_ob(me, victim, this_object(), damage_bonus);
}

// ���µĺ�����Ϊִ�е�Ƶ�Ȳ����ߣ����Ҿ��и߶��ظ������ʣ�
// ���Զ�����ITEM_D�е�ִ�г���

// ɱ�����Ժ�Ľ���
void killer_reward(object me, object victim)
{
        ITEM_D->killer_reward(me, victim, this_object());
}

// ������Ʒ
int receive_summon(object me)
{
        return ITEM_D->receive_summon(me, this_object());
}

// ������Ʒ
int hide_anywhere(object me)
{
        return ITEM_D->hide_anywhere(me, this_object());
}

// ׷Ѱ��Ʒ
int receive_miss(object me)
{
        if( !is_weapon() && !is_unarmed_weapon() ) {
                write("���޷�׷Ѱ" + name() + "��\n");
                return 0;
        }

        if( attack_lvl < ULTRA_LEVEL ) {
                write(name() + "��δͨ�飬����������ĸ�Ӧ��\n");
                return 0;
        }

        return ITEM_D->receive_miss(me, this_object());
}

// ���ڵ���
int do_stab(object me)
{
        return ITEM_D->do_stab(me, this_object());
}

// ��������
int do_touch(object me)
{
        if( attack_lvl != ULTRA_LEVEL )
                return notify_fail("�����˰��죬����ûʲô��Ӧ��\n");

        return ITEM_D->do_touch(me, this_object());
}

// װ��ʥ��
int do_san(object me)
{
        if( (is_weapon() || is_unarmed_weapon()) &&
             attack_lvl < MAX_LEVEL )
                return notify_fail("��������ȼ��������޷�ʥ����\n");

        return ITEM_D->do_san(me, this_object());
}

// ��͸��Ʒ
int do_imbue(object me, object imbue)
{
        return ITEM_D->do_imbue(me, this_object(), imbue);
}

// ��Ƕ��Ʒ
int do_enchase(object me, object tessera)
{
        return ITEM_D->do_enchase(me, this_object(), tessera);
}

// װ������
int do_wash(object me)
{
        return ITEM_D->do_wash(me, this_object());
}

// װ������
int do_forging(object me, object ob)
{
        return ITEM_D->do_forging(me, this_object(), ob);
}

// װ��Ҫ��
int do_require(object me, object ob)
{
        return ITEM_D->do_require(me, this_object(), ob);
}

mixed query_autoload() { return (query("equipped") ? query("equipped") : "kept"); }

void autoload(string parameter)
{
        switch (parameter)
        {
        case "worn":
                this_object()->wear();
                break;

        case "wielded":
                this_object()->wield();
                break;
        }
}
