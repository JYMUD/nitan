// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// combatd.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_DBASE;

#define NCH_CHANNEL(x) CHANNEL_D->channel_broadcast("nch", "ս�����飺"+(string)x) 

#define DEFAULT_MAX_PK_PERDAY   8
#define DEFAULT_MAX_PK_PERMAN   3
#define EXP_LIMIT       50000000000

#define ATTACK          0
#define DODGE           1
#define PARRY           2
#define DAMAGE          3
#define FORCE2          4

#undef REDUCE_PVP_DAMAGE

#define PVP_DAMAGE_SCALE        40;  // ��Ҷ����ʱ�˺�����ǰֵ���½�Ϊ 40%
#define PVP_WOUND_SCALE         30;  // ��Ҷ����ʱ�˺������ֵ���½�Ϊ 30%

mapping limb_damage = ([
// �������岿λ
        "ͷ��"  :   100,
        "����"  :   90,
        "�ؿ�"  :   90,
        "����"  :   80,
        "���"  :   50,
        "�Ҽ�"  :   55,
        "���"  :   40,
        "�ұ�"  :   45,
        "����"  :   20,
        "����"  :   30,
        "����"  :   60,
        "С��"  :   70,
        "����"  :   40,
        "����"  :   50,
        "���"  :   35,
        "�ҽ�"  :   40,
//  �������岿λ
        "����"  :   80,
        "ǰ��"  :   40,
        "���"  :   50,
        "�Ȳ�"  :   40,
        "β��"  :   10,
        "���"  :   50,
        "צ��"  :   40,
]);

nosave string *danger_limbs = ({
        "ͷ��", "����", "�ؿ�", "����","С��",
});

string *head_damage_me_msg = ({
        append_color(HIR "�����ͷ��һ�㷢�Ρ�\n" NOR, HIR),
        append_color(HIB "�����һ����ѣ���������һ�¡�\n" NOR, HIB),
        append_color(BLU "��ֻ����ð���ǣ�����Ʈ��\n" NOR, BLU),
});

string *body_damage_me_msg = ({
        append_color(HIR "��ֻ��$l������ʹ�����������ܵ�һ���񵴡�\n" NOR, HIR),
        append_color(HIB "��ֻ��$l���ۣ���������һ���Ҵܡ�\n" NOR, HIB),
        append_color(BLU "��ֻ����$l����ʹ����������������һ����й��\n" NOR, BLU),
});

string *guard_msg = ({
        append_color(CYN "$Nע����$n���ж�����ͼѰ�һ�����֡�\n" NOR, CYN),
        append_color(CYN "$N������$n��һ��һ������ʱ׼���������ơ�\n" NOR, CYN),
        append_color(CYN "$N�������ƶ��Ų�����Ҫ�ҳ�$n��������\n" NOR, CYN),
        append_color(CYN "$NĿ��ת���ض���$n�Ķ�����Ѱ�ҽ��������ʱ����\n" NOR, CYN),
        append_color(CYN "$N�������ƶ����Ų����Ż����֡�\n" NOR, CYN),
});

string *catch_hunt_human_msg = ({
        append_color(HIW "$N��$n������������ۺ죬���̴���������\n" NOR, HIW),
        append_color(HIW "$N����$n��ȣ����ɶ������㣡��\n" NOR, HIW),
        append_color(HIW "$N��$nһ���棬������˵�ʹ���������\n" NOR, HIW),
        append_color(HIW "$Nһ��Ƴ��$n�����ߡ���һ�����˹�����\n" NOR, HIW),
        append_color(HIW "$Nһ����$n�����һ㶣���У����������㣡��\n" NOR, HIW),
        append_color(HIW "$N�ȵ�����$n�����ǵ��ʻ�û���꣬���У���\n" NOR, HIW),
        append_color(HIW "$N�ȵ�����$n�����У���\n" NOR, HIW),
});

string *catch_hunt_beast_msg = ({
        append_color(HIW "$Nŭ��һ�������˹�������$n��\n" NOR, HIW),
        append_color(HIW "$N����$n�����ɱ��$n��\n" NOR, HIW),
        append_color(HIW "$N���������ͺ�ͻȻ���𹥻�$n��\n" NOR, HIW),
});

string *catch_hunt_bird_msg = ({
        append_color(HIW "$N����$nһ��ŭ�����ɳ��˹�����\n" NOR, HIW),
        append_color(HIW "$Nŭ��������ͻȻ���𹥻�$n��\n" NOR, HIW),
        append_color(HIW "$Nһ����������Ȼ��$n����������\n" NOR, HIW),
});

string *catch_hunt_msg = ({
        append_color(HIW "$N��$n������������ۺ죬���̴���������\n" NOR, HIW),
        append_color(HIW "$N����$n��ȣ����ɶ������㣡��\n" NOR, HIW),
        append_color(HIW "$N��$nһ���棬������˵�ʹ���������\n" NOR, HIW),
        append_color(HIW "$Nһ��Ƴ��$n�����ߡ���һ�����˹�����\n" NOR, HIW),
        append_color(HIW "$Nһ����$n�����һ㶣���У����������㣡��\n" NOR, HIW),
        append_color(HIW "$N�ȵ�����$n�����ǵ��ʻ�û���꣬���У���\n" NOR, HIW),
        append_color(HIW "$N�ȵ�����$n�����У���\n" NOR, HIW),
});

string *winner_msg = ({
        append_color(CYN "\n$N������Ц��˵���������ˣ�\n\n" NOR, CYN),
        append_color(CYN "\n$N˫��һ����Ц��˵�������ã�\n\n" NOR, CYN),
        append_color(CYN "\n$Nʤ�����У����Ծ�����ߣ�Ц�������ã�\n\n" NOR, CYN),
        append_color(CYN "\n$N˫��һ����Ц��˵����֪���ҵ������˰ɣ�\n\n" NOR, CYN),
        append_color(CYN "\n$Nʤ�����У����Ծ�����ߣ�̾�������ǰν��Ĺ���ãȻ��\n\n" NOR, CYN),
        append_color(CYN "\n$n������˼�����˵�����ⳡ�����������ˣ��»ؿ�����ô��ʰ�㣡\n\n" NOR, CYN),
        append_color(CYN "\n$n���һ�ݣ��޺޵�˵�������ӱ���ʮ�겻��\n\n" NOR, CYN),
        append_color(CYN "\n$n��ɫһ����˵�����������ˣ��͵���������ɣ�\n\n" NOR, CYN),
        append_color(CYN "\n$n������Ц���е������������ã��������ã���һ���������������\n\n" NOR, CYN),
        append_color(CYN "\n$n��ɫ΢�䣬˵��������������\n\n" NOR, CYN),
        append_color(CYN "\n$n������˼�����˵�����ⳡ�����������ˣ�����������\n\n" NOR, CYN),
        append_color(CYN "\n$n���һ�ݣ�������Ҿ˵�����������ղ�������Ȼ������\n\n" NOR, CYN),
});

string *weapon_parry_throwing = ({
        append_color(HIR "$n����$vһ�ӣ���$w��ɡ�\n" NOR, HIR),
        append_color(HIR "$n��$v����ǰһ�ᣬ$w����$v�ϣ�$n���Ͼ���һ�����顣\n" NOR, HIR),
        append_color(HIR "$n�����Ӷ�����$v����$w�����Ӱ���١�\n" NOR, HIY),
});

string *unarm_parry_throwing = ({
        append_color(HIR "$n����һ����$w�������С�\n" NOR, HIY),
        append_color(HIR "$n���������ָ����һ�У��㽫$w�������С�\n" NOR, HIY),
        append_color(HIR "$n����һֻЬ�Ӷ�׼$wһ�̣�$w����$n��Ь�С�\n" NOR, HIY),
});

string *weapon_parry_sixmai = ({
        append_color(HIR "$n�趯$v������������һ����Ļ֮�У���ס��$N�����񽣵Ĺ��ơ�\n" NOR, HIY),
        append_color(HIR "$n�Ӷ�$v����ס��$N�����񽣵����ν�����\n" NOR, HIY),
        append_color(HIR "$n����$v�������񽣵����ν�����������$v�ϡ�\n" NOR, HIY),
});

string *unarm_parry_sixmai = ({
        append_color(HIR "$n��������������ķ��ǰ����ס��$N�������񽣣�����ȴ�����ν�������һƬ��\n" NOR, HIY),
        append_color(HIR "$n����ǰ����һ����ǽ��ֻ�����͡������͡�֮����$N�Ľ�������������ǽ�ϡ�\n" NOR, HIY),
        append_color(HIR "$n��������������$l����������$N�������񽣣���$l���ı�Ƥȴ���ս���\n" NOR, HIY),
});

string *star_move_weapon = ({
        append_color(HIR "ֻ��$n������$N��$w��һ��һ�ͣ�$w�ڿ���Ӳ����ת�˸��壬����$P�Լ���$l��\n" NOR, HIY),
        append_color(HIR "$nʹһ�ж�ת���ƣ�$N��$w��Ȼ��ת����������$P�Լ���$l��\n" NOR, HIY),
});

string *star_move_unarm = ({
        append_color(HIR "$n���ö�ת���ƣ����н�$N�������������˻�ȥ��$Nֻ����$l��һ����ۡ�\n" NOR, HIY),
        append_color(HIR "$n�ĳ���һ��һ�ͣ�$N����һ�о�Ȼ�����Լ����ϡ�\n" NOR, HIY),
});

string *qiankun_move_weapon = ({
        append_color(HIR "ֻ��$n������$N��$w��һ��һ�ͣ�$w�ڿ���Ӳ����ת�˸��壬����$P�Լ���$l��\n" NOR, HIY),
        append_color(HIR "$nʹһ��Ǭ����Ų�ƣ�$N��$w��Ȼ��ת����������$P�Լ���$l��\n" NOR, HIY),
});

string *qiankun_move_unarm = ({
        append_color(HIR "$n����Ǭ����Ų�ƣ����н�$N�������������˻�ȥ��$Nֻ����$l��һ����ۡ�\n" NOR, HIY),
        append_color(HIR "$n�ĳ���һ��һ�ͣ�$N����һ�о�Ȼ�����Լ����ϡ�\n" NOR, HIY),
});

// message after damage info
nosave string foo_before_hit = 0;
nosave string foo_after_hit = 0;
string query_bhinfo() { return foo_before_hit; }
string query_ahinfo() { return foo_after_hit; }
void clear_bhinfo() { foo_before_hit = 0; }
void clear_ahinfo() { foo_after_hit = 0; }
protected void quest_kill(object killer, object victim);

void create()
{
        int pd, pm;

        seteuid(getuid());
        set("channel_id", "ս������");

        if( undefinedp(pd = CONFIG_D->query_int("max pk perday")) )
                pd = DEFAULT_MAX_PK_PERDAY;

        if( undefinedp(pm = CONFIG_D->query_int("max pk perman")) )
                pm = DEFAULT_MAX_PK_PERMAN;

        set("pk_perday", pd);
        set("pk_perman", pm);
}

void set_bhinfo(string msg)
{
        if( !foo_before_hit ) {
                foo_before_hit = msg;
                return;
        }
        foo_before_hit += msg;
}

void set_ahinfo(string msg)
{
        if( !foo_after_hit ) {
                foo_after_hit = msg;
                return;
        }
        foo_after_hit += msg;
}

string damage_msg(int damage, string type)
{
        string str;

        if( damage == 0 )
                return "���û������κ��˺���\n";

        switch( type )
        {
        case "����":
        case "����":
        case "����":
                if( damage < 100 ) return "���ֻ������ػ���$p��Ƥ�⡣\n"; else
                if( damage < 200 ) return "�����$p$l����һ��ϸ����Ѫ�ۡ�\n"; else
                if( damage < 400 ) return "������͡���һ����$w����$p$l����һ���˿ڣ�\n"; else
                if( damage < 600 ) return "������͡���һ����$w����$p$l����һ��Ѫ���ܵ��˿ڣ�\n"; else
                if( damage < 1000 )return "������͡���һ����$w����$p$l����һ���ֳ�������˿ڣ�����$N������Ѫ��\n"; else
                                   return "���ֻ����$nһ���Һ���$w����$p$l����һ������ǵĿ����˿ڣ�\n";
                break;
        case "����":
                if( damage < 100 ) return "���ֻ������ش���$p��Ƥ�⡣\n"; else
                if( damage < 200 ) return "�����$p$l�̳�һ�����ڡ�\n"; else
                if( damage < 400 ) return "������ۡ���һ����$w�Ѵ�����$n$l����\n"; else
                if( damage < 800 ) return "������ۡ���һ����$w�Ѵ̽�$n��$l��ʹ$p�������������˼�����\n"; else
                if( damage < 1000 )return "��������͡���һ����$w����$p$l�̳�һ��Ѫ�������Ѫ������\n"; else
                                   return "���ֻ����$nһ���Һ���$w����$p��$l�Դ���������Ѫ�������أ�\n";
                break;
        case "����":
                if( damage < 50 )  return  "���ֻ��������ߵ������Ĳ�Ӭ��΢���˵㡣\n";else
                if( damage < 100 ) return "�����$n��$l���һ�����ࡣ\n";else
                if( damage < 200 ) return "���һ�����У�$n��$l��ʱ����һ���ϸߣ�\n";else
                if( damage < 400 ) return "���һ�����У�$n�ƺ���һ����Ȼ���˲�С�Ŀ���\n";else
                if( damage < 600 ) return "������项��һ����$n����������\n";else
                if( damage < 800 ) return "�����һ�¡��项��һ���ߵ�$n�����˺ü�������һ��ˤ����\n";else
                if( damage < 1000 )return "������ص����У�$n���ۡ���һ���³�һ����Ѫ��\n";else
                                   return "���ֻ�������项��һ�����죬$n��һ�����ݰ���˳�ȥ����\n";
                break;
        case "����":
        case "����":
                if( damage < 50 )  return "���ֻ����������������Ĳ�Ӭ��΢���˵㡣\n"; else
                if( damage < 100 ) return "�����$p��$l���һ�����ࡣ\n"; else
                if( damage < 200 ) return "���һ�����У�$n��$l��ʱ����һ���ϸߣ�\n"; else
                if( damage < 400 ) return "���һ�����У�$n�ƺ���һ����Ȼ���˲�С�Ŀ���\n"; else
                if( damage < 600 ) return "������项��һ����$n����������\n"; else
                if( damage < 800 ) return "�����һ�¡��项��һ�����$n�����˺ü�������һ��ˤ����\n"; else
                if( damage < 1000 )return "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��\n"; else
                                   return "���ֻ�������项��һ�����죬$n��һ�����ݰ���˳�ȥ��\n";
                break;
        case "ץ��":
                if( damage < 50 )  return "���ֻ�������ץ������ץ����΢���˵㡣\n";else
                if( damage < 100 ) return "�����$p��$lץ������Ѫ�ۡ�\n";else
                if( damage < 200 ) return "���һץ���У�$n��$l��ץ����Ѫ�ɽ���\n";else
                if( damage < 400 ) return "������͡���һ����$l��ץ����ɼ��ǣ���\n";else
                if( damage < 600 ) return "���һץ���У�$n��$l��ץ��Ѫ���ɣ�����\n";else
                if( damage < 800 ) return "�����һ�¡��͡���һ��ץ��$n���κü��£���һ��ˤ����\n";else
                if( damage < 1000 )return "���$n����һ����$l��ץ�ý�Ϲ��ۣ���\n";else
                                   return "���ֻ����$nһ���Һ���$l��ץ�����Ѫ��������Ѫ�������أ���\n";
                break;
        case "����":
                if( damage < 50 )  return "���ֻ�ǰ�$n������˰벽����������\n"; else
                if( damage < 100 ) return "���$nʹ��һ������$p��$l���һ�����ˡ�\n"; else
                if( damage < 200 ) return "���һ�����У���$n���ʹ��������ȥ��\n"; else
                if( damage < 400 ) return "���$n�ƺ���һ��������һ����һ��ף���Ȼ���˵����ˣ�\n"; else
                if( damage < 600 ) return "���$n��ɫһ�±�òҰף��������������˺ü�����\n"; else
                if( damage < 800 ) return "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��\n"; else
                if( damage < 1000 )return "������䡹��һ����$nȫ����Ѫ������������Ѫ���������\n"; else
                                   return "���ֻ���������������죬$nһ���ҽУ���̲�����������ȥ��\n";
                break;
        case "��Ѩ":
                if( damage < 60 )  return "���ֻ�����������$n��$l������û�е㵽Ѩ����\n"; else
                if( damage < 100 ) return "���$nʹ��һ������$p��$l���һ�����ࡣ\n"; else
                if( damage < 200 ) return "���һ�����У�$N������$n$l�ϵ�Ѩ����$nֻ��һ����ľ��\n"; else
                if( damage < 400 ) return "���$n�ƺ���һ��������һ����һ��ף���ʱ����$l��ľ��\n"; else
                if( damage < 800 ) return "���$n��ɫһ�±�òҰף���$N����$l��Ѩ��,һ����ʹ�鲼����$l��\n"; else
                if( damage < 1000 )return "���$nһ����У�$l��Ѩ��������,��ʹֱ���ķΣ�\n"; else
                                   return "���ֻ����$nһ���ҽУ�һ���ʹ�����������α�ȫ������ֱͦͦ�ĵ�����ȥ��\n";
                break;
        case "����":
        case "����":
                if( damage < 50 )  return "���ֻ����$n��Ƥ����������������ֻ���Ƶ�Ƥ��\n"; else
                if( damage < 100 ) return "�����$n$l���һ����΢���Ϻۡ�\n"; else
                if( damage < 200 ) return "�����ž����һ����$n$l���һ��������Ѫ�ۣ�\n"; else
                if( damage < 400 ) return "���ֻ����ž����һ����$n���κü��£���һ��ˤ����\n"; else
                if (damage < 600)  return "���$p��$l�ϱ�����һ��Ѫ���ܵĴ��ڣ�\n"; else
                if( damage < 800 ) return "���ֻ����ž����һ����$n��$l�����Ƥ��������ʹ��$pҧ���гݣ�\n"; else
                if( damage < 1000 )return "�����ž����һ�����죡��һ�º�������ֻ���$nƤ��������Ѫ���ɽ���\n"; else
                                   return "���ֻ����$nһ���Һ���$w���صس�����$p��$l��$n��ʱѪ���ɣ�ʮ�����˾�����\n";
                break;
        case "������":
        case "������":
                if( damage < 50 )  return "���$N�ܵ�$n�����������ƺ�һ����\n"; else
                if( damage < 100 ) return "���$N��$n�ķ������Ѫ���ڣ���ʧɫ��\n"; else
                if( damage < 200 ) return "���$N��$n�ķ����վ�����ȣ�ҡҡ�λΡ�\n"; else
                if( damage < 400 ) return "���$N��$n���������𣬡��١���һ������������\n"; else
                if( damage < 600 ) return "���$N��$n����÷���������������ð����顣\n"; else
                if( damage < 800 ) return "���$N��$n�����������ؿ������ܵ�һ���ػ�����������������\n"; else
                if( damage < 1000 )return "���$N��$n����������ǰһ�ڣ���������ɳ�����\n"; else
                                   return "���$N��$n����������ǰһ�ڣ�������Ѫ������������ߵķ��������ȥ��\n";
                break;
        case "����":
        case "����":
                if( damage < 50 )  return "���ֻ����������������Ǹ�$nɦ��һ������\n"; else
                if( damage < 100 ) return "�����$n��$l�ҳ�һ��С������\n"; else
                if( damage < 200 ) return "���$N��һ���Ҹ����ţ�$n��$l��ʱ����һ���ϸߣ�\n"; else
                if( damage < 400 ) return "���$N��һ���Ҹ����ţ�$n�ƺ�һ����Ȼ���˲�С�Ŀ���\n"; else
                if( damage < 600 ) return "���ֻ�����项��һ����$n�۵�����������������\n"; else
                if( damage < 800 ) return "�����һ�¡��䡹��һ���ҵ�$n��ð���ǣ���һ��ˤ����\n"; else
                if( damage < 1000 )return "������ص����У�$n��ǰһ�ڣ����ۡ���һ���³�һ����Ѫ��\n"; else
                                   return "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã�\n";
                break;
        case "ҧ��":
                if( damage < 100 ) return "���ֻ������ز���һ��$p��Ƥ�⡣\n";else
                if( damage < 200 ) return "�����$p$lҧ��һ����ӡ��\n";else
                if( damage < 400 ) return "���$p��ҧ��һƬ������\n";else
                if( damage < 800 ) return "���$p��Ƥ���ⱻҧ��һ��飡\n";else
                if( damage < 1000 )return "�����$p������ҧ����Ѫ��ģ����һ���$l�⣡\n";else
                                   return "���ֻ����$nһ���Һ���$p��$l�ϵ��ⱻһ��ҧ����¶����ͷ����\n";
                break;
        case "����":
        case "����":
                if( damage < 100 ) return "���ֻ�ǰ�$p��$l����һ�¡�\n";else
                if( damage < 200 ) return "���$p��$l��$w���˵����˸�С�塣\n";else
                if( damage < 400 ) return "���$p��$l��$w�յú�����ʹ��ʹ�ò�סð��ҧ����\n";else
                if( damage < 800 ) return "������͡�һ�����죬$p���$l��һƬ��ʹ���ѱ�$w�ճ��˰���ɫ�����罹̿��\n";else
                if( damage < 1000 )return "��������͡�һ�������ȥ��$n��ɫʹ���ѵ���$l��$w�յ�һƬ���ڣ�����ֱð��\n";else
                                   return "���ֻ����$n�����Һ����ڵ��ϲ�ס�����$l�ѱ�$w�յ�Ƥ�⾡�ã��������磡��\n";
                break;
        case "����":
                if( damage < 100 ) return "���$p���Ǿ���$l��Щ���쬵أ���ͦ����ġ�\n";else
                if( damage < 200 ) return "���$p��$l��������Щ��ľ��\n";else
                if( damage < 400 ) return "���$p������ش��˸�������\n";else
                if( damage < 800 ) return "���$p��ɫһ�䣬������Щ��Ӳ������Ҳ���ɪɪ������\n";else
                if( damage < 1000 )return "���$p���Ӵ������ɫ�԰ף��촽���÷��ϣ����ظ��ֱ�죡\n";else
                                   return "���������$n����һ�ƣ����ϲҰ׵�û���Ѫɫ���������ݣ�����ѪҺ�ƺ�������˱�����\n";
                break;
        default:
                if( !type) type = "�˺�";
                if( damage < 50 )  str = "���ֻ����ǿ���һ����΢"; else
                if( damage < 100 ) str = "��������΢��"; else
                if( damage < 200 ) str = "������һ��"; else
                if( damage < 400 ) str = "���һ������"; else
                if( damage < 500 ) str = "��������Ϊ���ص�"; else
                if( damage < 600 ) str = "�������൱���ص�"; else
                if( damage < 800 ) str = "������ʮ�����ص�"; else
                if( damage < 1000 )str = "�����ɼ������ص�"; else
                                   str = "�����ɷǳ����µ�����";
                return str + type + "��\n";
        }
}

varargs string eff_status_msg(int ratio, int dam_type) 
{
        if( !dam_type ) dam_type = 1;
        if( ratio==100 ) return HIG "�������ϲ���˿���˺ۡ�" NOR;
        if( ratio > 95 ) return HIG "�ƺ�ֻ���˵����ˣ������˴��塣" NOR;
        if( ratio > 90 ) {
                if (dam_type == 3)
                        return HIY "������Щή�ң�����������" NOR;
                else if (dam_type == 2)
                        return HIY "�����ƺ�����Щ���ˣ������е㽩Ӳ��" NOR;
                else    return HIY "�������˼���Ƥ���ˡ�" NOR;
        }
        if( ratio > 80 ) return HIY "���˼������ˣ��ƺ��������¡�" NOR;
        if( ratio > 60 ) {
                if (dam_type == 3)
                        return HIY "������飬���ύ����" NOR;
                else if (dam_type == 2)
                        return HIY "�����Ȼ�������о�Ȼ����Ѫ������" NOR;
                else    return HIY "�������˲��ᣬ��������Ѫ��" NOR;
        }
        if( ratio > 40 ) {
                if (dam_type == 3)
                        return HIY "�沿�鴤��ֹ���Ѿ������Լ���" NOR;
                else    return HIR "��Ѫ��ֹ������ɢ�ң��Ѿ���������·�ˡ�" NOR;
        }
        if( ratio > 30 ) return HIR "�˺����ۣ���������֧����������ȥ��" NOR;
        if( ratio > 20 ) return HIR "�������ˣ�ֻʣ�����һ�����ˡ�" NOR;
        if( ratio > 10 ) return RED "����ԡѪ����Ҫ���ڵ��ϡ�" NOR;
        if( ratio > 5  ) return RED "ͫ�׷Ŵ��Ѿ�����һϢ�����ڵ�Ϧ�ˡ�" NOR;
        return RED "����в�����ʱ�����ܶ�����" NOR;
}

varargs string status_msg(int ratio, int dam_type) 
{
        if( !dam_type ) dam_type = 1;
        if( ratio==100 ) return HIG "�������棬�������㣬" NOR;
        if( ratio > 95 ) return HIG "�ƺ���Щƣ����������Ȼʮ���л�����" NOR;
        if( ratio > 90 ) return HIY "������������Щ���ã�" NOR;
        if( ratio > 80 ) {
                if (dam_type == 3)
                        return HIY "�����е㲻�㣬���Թ��ش��ݣ�" NOR;
                else if (dam_type == 2)
                        return HIY "������Щ��㱣�����Ӧ�����磬" NOR;
                else    return HIY "�����е㲻̫��⣬�����������ɣ�" NOR;
        }
        if( ratio > 60 ) {
                if (dam_type == 3)
                        return HIY "�ж���Ȼ�ް����������Ը������ˣ�" NOR;
                else if (dam_type == 2)
                        return HIY "��Ӧ��ʼ�ٻ���˫Ŀ����" NOR;
                else    return HIY "�������꣬��ɫ�Ұף�" NOR;
        }
        if( ratio > 40 ) {
                if (dam_type == 3)
                        return HIR "������ɢ���ƺ���ʹ����ʧȥ֪����" NOR;
                else if (dam_type == 2)
                        return HIR "�۹����룬����������" NOR;
                else    return HIR "�ƺ�ʮ��ƣ����������Ҫ�ú���Ϣ�ˣ�" NOR;
        }
        if( ratio > 30 ) return HIR "ͷ�ؽ��ᣬ��������֧����������ȥ��" NOR;
        if( ratio > 20 ) {
                if (dam_type == 3)
                        return HIR "�����Ѿ���ľ�����ˣ�" NOR;
                else if (dam_type == 2)
                        return HIR "�������Ѿ��겻�����ˣ�" NOR;
                else    return HIR "�������Ѿ����������ˣ�" NOR;
        }
        if( ratio > 10 ) return RED "ҡͷ���ԡ�����бб�������ε���" NOR;
        return RED "�Ѿ���������״̬������ȫʧ��" NOR;
}

varargs mixed report_status(object ob, int effective)
{
        int eff_ratio = 100;
        int ratio = 100;
        int k_stat, g_stat, s_stat;
        int d_type = 1;
        int e_type = 1;
        string *msg = ({RED,HIR,HIY,HIG,HIG});
        string str;
 
        if( !ob || !query("max_qi", ob) || !query("max_jing", ob) ) return;
               
        k_stat = (int) query("qi", ob) * 100 / (int)query("max_qi", ob);
        //s_stat = (int) query("sen", ob) * 100 / (int)query("max_sen", ob);
        g_stat = (int) query("jing", ob) * 100 / (int)query("max_jing", ob);
               
        if (ratio > k_stat ) {
                ratio =  k_stat;
        }
        /*
        if (ratio > s_stat ) {
                ratio =  s_stat;
                d_type = 2;
        }
        */
        if (ratio > g_stat ) {
                ratio =  g_stat;
                d_type = 3;
        }
        
        k_stat = (int) query("eff_qi", ob) * 100 / (int)query("max_qi", ob);
        //s_stat = (int) query("eff_sen", ob) * 100 / (int)query("max_sen", ob);
        g_stat = (int) query("eff_jing", ob) * 100 / (int)query("max_jing", ob);
        
        if (eff_ratio > k_stat ) {
                eff_ratio =  k_stat;
        }
        /*
        if (eff_ratio > s_stat ) {
                eff_ratio =  s_stat;
                e_type = 2;
        }
        */
        if (eff_ratio > g_stat ) {
                eff_ratio =  g_stat;
                e_type = 3;
        }
        
        str = "( $N" + status_msg(ratio, d_type) + eff_status_msg(eff_ratio, e_type) + " )\n";
        if( !effective )
                message_vision(str, ob);
        else
                return str;
}

#ifdef REDUCE_PVP_DAMAGE
int reduce_damage(object attacker, object victim, int damage)
{
        if( objectp(attacker) && objectp(victim) &&
            playerp(attacker) && playerp(victim) ) {
                damage = damage * PVP_DAMAGE_SCALE / 100;
        }

        return damage;
}

int reduce_wound(object attacker, object victim, int wound)
{
        if( objectp(attacker) && objectp(victim) &&
            playerp(attacker) && playerp(victim) ) {
                wound = wound * PVP_WOUND_SCALE / 100;
        }

        return wound;
}
#endif

int valid_power(object ob, int combat_exp)
{
        int t;
        
        t = query("reborn/times", ob);

        if( t >= 1 )
                combat_exp += 5000000000/2;
        
        if( t >= 2 )
                combat_exp += 10000000000/2;
        
        if( t >= 3 )
                combat_exp += 20000000000/2;
                
        return combat_exp/100;
}

// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
varargs mixed skill_power(object ob, string skill, int usage, int delta)
{
        int level, power;
        mapping dbase;
        mapping temp;
        mapping fight;
        mapping apply;
        int percent = 0;
        int bonus,buff;
        int ratio = 0;
        string martial_skill = ob->query_skill_mapped(skill);

        if( !living(ob) ) return 0; // �ε�ʱ power ��Զ������
        if( ob->over_encumbranced() )    return 0; // ����С����ʱ power ��Զ������
        
        if( userp(ob) && ob->is_ghost() )
                return 0;  // ���� power ��Զ������
                
        level = ob->query_skill(skill);

        dbase = ob->query_entire_dbase();
        temp = ob->query_entire_temp_dbase();
        if( temp ) 
        {
                apply = temp["apply"];
                fight = temp["fight"];
        }

        switch( usage ) {
        case SKILL_USAGE_ATTACK:
                if( apply )  {
                        level += apply[skill];
                        level += apply["attack"];
                }
                if( query("jingmai/finish", ob) )
                        buff = ZHOUTIAN_D->query_jingmai_effect("attack"); // ������ѨЧ�� 1640
                else
                        buff = query("jingmai/attack", ob);     
                bonus = query_temp("bonus/attack", ob);         // This bonus is ONE_SHOT_BONUS.
                ob->set_temp("bonus/attack", 0);                // after this calculation, release bonus.s
                break;
        case SKILL_USAGE_DEFENSE:
                if( apply ) {
                        level += apply[skill];
                        level += apply["defense"];
                }
                if( query("jingmai/finish", ob) )
                        buff = ZHOUTIAN_D->query_jingmai_effect("defense"); // ������ѨЧ�� 1140
                else
                        buff = query("jingmai/defense", ob);     
                bonus = query_temp("bonus/defense", ob);        // This bonus is ONE_SHOT_BONUS.
                ob->set_temp("bonus/defense", 0);               // after this calculation, release bonus.s
                break;
        case SKILL_USAGE_ABSORB:
                level += apply["iron-cloth"];
                bonus = query_temp("bonus/iron-cloth", ob);        // This bonus is ONE_SHOT_BONUS.
                ob->set_temp("bonus/iron-cloth", 0);               // after this calculation, release bonus.s
                if( !level )
                        return 0;
                break;
        }
        if( delta ) level += delta;

        if( !level || level < 1 ) 
        {
                power = valid_power(ob, query("combat_exp", ob)) / 2;

                if( ob->is_weak() ) power /= 2; // ���� power ����
                return  power;
        }

        power = level * level * level / 10;
        power+= bonus * bonus * bonus / 10;
        power+= buff * buff * buff / 10;

        if( usage == SKILL_USAGE_ATTACK ) 
        {
                power = power / 30 * dbase["str"];
                if( fight && ob->is_fighting() )
                         power += power / 100 * fight["attack"];
        } 
        else 
        {
                power = power / 30 * dbase["dex"];
                if( fight && ob->is_fighting() )
                         power += power / 100 * fight[skill];
        }
        
        power += valid_power(ob, dbase["combat_exp"]);
        
        
        // ��ң��������м��ر�
        if( ob->query_skill("xiaoyao-you", 1) >= 100 )
        {
                percent = ob->query_skill("xiaoyao-you", 1) / 100; // ÿ100������һ���ٷֵ�
                if( ratio < percent ) ratio = percent;
        }

        // �����޼��������
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("kunlun-wuji", 1) >= 50 && 
            skill == "sword" && martial_skill == "qiankun-jian" )
        {
                percent = ob->query_skill("kunlun-wuji", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // ���������������
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("qimen-xuanshu", 1) >= 50 &&
            skill == "finger" && martial_skill == "tanzhi-shentong" )
        {
                percent = ob->query_skill("qimen-xuanshu", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // ѪӰ���������
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("xueying-dafa", 1) >= 50 && 
            skill == "blade" && martial_skill == "xuedao-daofa" )
        {
                percent = ob->query_skill("xueying-dafa", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // �����������
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("jingxin", 1) >= 50 && 
            ((skill == "sword" && martial_skill == "huifeng-jian")
                || (skill == "strike" && martial_skill == "piaoxue-zhang")) )
        {
                percent = ob->query_skill("jingxin", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // �����������
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("jianyi", 1) >= 50 &&
            skill == "sword" && (martial_skill == "huashan-sword" || martial_skill == "lonely-sword") )
        {
                percent = ob->query_skill("jianyi", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // ������߷���
        if( usage == SKILL_USAGE_DEFENSE && ob->query_skill("jianyi", 1) >= 50 )
        {
                percent = ob->query_skill("jianyi", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // ������������
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("tianwei-zhengqi", 1) >= 50 &&
            ((skill == "sword" && martial_skill == "taiji-jian")
                || (skill == "cuff" && martial_skill == "taiji-quan")) )
        {
                percent = ob->query_skill("tianwei-zhengqi", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        power += power * ratio / 100;      
        
        // �󷨷���Ч��
        if( (usage == SKILL_USAGE_DEFENSE) && ob->in_array() ) 
        {
                int n;
        
                if( (n =  ob->query_array_level()/100) )
                {
                        power += power * n / 100;
                }
        }

        // ���λ�λ����ս���ر���15%
        if( usage == SKILL_USAGE_DEFENSE && query("special_skill/yixing", ob) )
                power += power * 15 / 100;

        // ��תǬ������10%����
        if( usage == SKILL_USAGE_ATTACK && query("special_skill/nizhuan", ob) )
                power += power * 10 / 100;

        // ���ǻ�������30%����
        if( usage == SKILL_USAGE_ATTACK && query("special_skill/huiyan", ob) )
                power += power * 30 / 100;

        // ����״������
        if( ob->is_weak() ) power /= 2;
        
        // �ֲ����ˣ�ʹ��unarmed������
        if( (skill == "unarmed") && (ob->query_limb_wound("����") || 
            ob->query_limb_wound("����")) ) 
                power /= 2;

        return power;
}

varargs mapping query_action(object me, int flag)
{
        mixed act,l_act;
        
        //me->reset_action();
        act = query("actions", me); // ���˵����� action
        if( functionp(act) ) act = evaluate(act, me);
        if( !mapp(act) )
        {
                me->reset_action();
                act = query("actions", me);
                if( functionp(act) ) act = evaluate(act, me);
                if( !mapp(act) ) 
                {
                        CHANNEL_D->do_channel( this_object(), "sys",
                                        sprintf("%s(%s): bad action = %O",
                                        me->name(1), me->query_id(1), 
                                        query("actions", me)));
                        return 0;
                }
        }
        
        if( flag && flag == 1 ) // ָ������
        {
                set_temp("hand_flag", 0, me);
                return act;
        }
                
        l_act = query("second_actions", me); // ���˵����� action 
        if( functionp(l_act) ) l_act = evaluate(l_act, me);
        if( !mapp(l_act) || !sizeof(l_act) )
        {
                set_temp("hand_flag", 0, me);
                return act;
        }

        if( flag && flag == 2 ) // ָ������
        {
                set_temp("hand_flag", 1, me);
                return l_act;
        }

        // ʲô���ؾ������������ֹ������������ֹ���? Ŀǰû��,�������������.
        if( random(100) < 55 ) // ���ֵĿ����Դ�һЩ.
        {
                set_temp("hand_flag", 0, me);
                return act;
        }
        else
        {
                set_temp("hand_flag", 1, me);
                return l_act;
        }
}

// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
varargs int do_attack(object me, object victim, object weapon, int attack_type, int flag)
{
        mapping my, your;
        mapping my_temp, your_temp;
        mapping fight;
        mapping prepare, action;
        string limb, *limbs;
        string attack_skill, martial_skill, force_skill, defense_skill;
        string parry_msg;
        mixed foo;

        int has_weapon;
        int delta;
        int ap, dp, pp;
        int damage, damage_bonus;
        int armor;
        int wounded;
        int array_flag;
        int attack;
        int avoid;

        object second_weapon;
        object weapon2; // weapon of victim
        object ob;

        string result;
        string damage_info;
        string *att;
        int hjs;

        if( !me || !victim ) return 1;
        if( !living(me) ) return 1;
        if( me->is_ghost() || victim->is_ghost() ) return 1;
        
        // ����ħ�� ����Ӱ
        if( query_temp("hiding_kuihua", victim) ) return 1;
        if( query("no_fight", environment(me))){
                message_vision("$N��$n��������һ������ס���С�\n",
                               me, victim);
                me->remove_enemy(victim);
                victim->remove_enemy(me);
                return 0;
        }

        if( environment(me) != environment(victim) ) {
                me->remove_enemy(victim);
                victim->remove_enemy(me);
                return 0;
        }

        hjs = me->query_skill("huajia-su", 1);
        my = copy(me->query_entire_dbase());
        your = copy(victim->query_entire_dbase());
        if( !(my_temp = copy(me->query_entire_temp_dbase())) )
                my_temp = allocate_mapping(5);
        if( !(your_temp = copy(victim->query_entire_temp_dbase())) )
                your_temp = allocate_mapping(5);
        //
        // (0) Choose skills.
        //
        prepare = me->query_skill_prepare();
        if( !prepare ) prepare = ([]);
        
        if( !objectp(weapon) ) weapon = query_temp("weapon", me);
        second_weapon = query_temp("secondary_weapon", me);
        
        if( objectp(weapon))attack_skill=query("skill_type", weapon);
        else if(  sizeof(prepare) == 0) attack_skill = "unarmed";
        else if(  sizeof(prepare) == 1) attack_skill = (keys(prepare))[0];
        else if(  sizeof(prepare) == 2) attack_skill = (keys(prepare))[query_temp("action_flag", me)];

        if( attack_skill == "pin" )
                attack_skill = "sword";

        //
        // (1) Find out what action the offenser will take.
        //
        action = query_action(me, flag);
        if( !action ) return 0;

        if( query_temp("hand_flag", me) )  // ����'��ǰ����' weapon
                weapon = second_weapon;

        has_weapon = objectp(weapon) || objectp(query_temp("armor/hands", me));
        
        if( stringp(query_temp("action_msg", me))){
                result="\n"+query_temp("action_msg", me)+action["action"]+"��\n";
                delete_temp("action_msg", me);
        }else if( query_temp("action_flag", me) == 0){
                result = "\n" + action["action"] + "��\n";
        } else
                result = WHT "\n$N����������ƥ��˲�����ѹ���һ�С�\n" NOR + action["action"] + "��\n";
                //result = "\n������" + action["action"] + "��\n";
        //
        // (2) Prepare AP, DP for checking if hit.
        //
        if( martial_skill = me->query_skill_mapped(attack_skill) )
                limb = SKILL_D(martial_skill)->query_attack_limb(me, victim);

        if( !limb ) {
                limbs=query("limbs", victim);
                if( !arrayp(limbs) ) {
                        limbs = ({ "����" });
                        set("limbs", limbs, victim);
                }
                limb = limbs[random(sizeof(limbs))];
        }

        // �󷨷���
        if( victim->in_array() && victim->query_array_status() &&
            (random(100) < (victim->query_array_level() / 100 + 60))) {
                if( ((your["qi"] < your["max_qi"] * 2 / 5) ||
                    (your["jing"] < your["max_jing"] * 2 / 5)) &&
                    !ob->is_busy() && objectp(ob = victim->query_array_obstructor()) ) {
                        result = replace_string(result, "$l", limb);
                        if( objectp(weapon) )
                                result = replace_string(result, "$w", weapon->name());
                        else if( stringp(action["weapon"]) )
                                result = replace_string(result, "$w", action["weapon"]);
                        else if( attack_skill == "finger" || attack_skill == "hand" )
                                result = replace_string(result, "$w", "��ָ" );
                        else if( attack_skill == "strike" || attack_skill == "claw" )
                                result = replace_string(result, "$w", "����" );
                        else    result = replace_string(result, "$w", "ȭͷ" );

                        message_combatd(result, me, victim);
                        message_combatd(HIC BWHT "$N�����Ʋ���������$n����ǰ��\n" NOR, ob, victim);
                        result = "";

                        victim = ob;
                        your = copy(ob->query_entire_dbase());
                        array_flag = 1;
                        attack_type = TYPE_QUICK;
                }
        }

        fight = ([]);
#ifdef USE_SKILLS_COMBAT
        if( att = SKILLS_D->skill_query_power(martial_skill) ) {
                fight["attack"] = to_int(att[ATTACK]);
                my_temp["fight"] = copy(fight);         // �ü������ӱ�����������
                fight = ([]);
                fight["dodge"]  = to_int(att[DODGE]);
                fight["parry"]  = to_int(att[PARRY]);
                your_temp["fight"] = copy(fight);       // �ü��ܽ��Ͷ��ֶ�������
        } else {
#endif
                if( intp(action["attack"]) )
                        fight["attack"] = action["attack"];
                my_temp["fight"] = copy(fight);
                fight = ([]);
                if( intp(action["dodge"]) )
                        fight["dodge"] = action["dodge"];
                if( intp(action["parry"]) )
                        fight["parry"] = action["dodge"];
                your_temp["fight"] = copy(fight);
#ifdef USE_SKILLS_COMBAT
        }
#endif

        ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK, 0);
        if( ap < 1) ap = 1;

        if( sizeof(me->query_enemy()) > 1 )
                ap = ap * 9 / (8 + sizeof(victim->query_enemy()));
        if( !me->visible(victim) ) ap /= 10;
        if( member_array(limb, danger_limbs) != -1 )
                ap -= ap / 10;
        if( my["character"] == "���ռ�թ" )
                ap += ap * 20 / 100;

        if( victim->in_array() ) ap /= 2; // �󷨽�������

        if( array_flag ) dp = 0;          // ���˵���ֻ���м�
        else {
                dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE, 0);
                if( dp < 1 ) dp = 1;

                if( stringp(defense_skill = victim->query_skill_mapped("dodge")) )
                        dp += dp / 100 * SKILL_D(defense_skill)->query_effect_dodge(me, victim);
                if( sizeof(victim->query_enemy()) > 1 )
                        dp = dp * 9 / (8 + sizeof(victim->query_enemy()));
                if( !victim->visible(me) ) dp /= 10;
                if( victim->is_busy() ) dp /= 3;
        }

        //
        // (3) Fight!
        //     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
        //     AP and DP are greater than zero, so we always have chance to hit
        //     or be hit.
        //
        damage = 0;
        wounded = 0;
        damage_info = "";

        if( random(ap + dp) < dp && living(victim) ) {
                // Does the victim dodge this hit?
#if INSTALL_COMBAT_TEST
                if( wizardp(me) && query("env/combat_test", me) )
                        tell_object(me, HIY "��ս�����顿������ AP��" + ap +
                                    "��DP��" + dp + "��\n" NOR);
                if( wizardp(victim) && query("env/combat_test", victim) )
                        tell_object(victim, HIC "��ս�����顿���Է� AP��" + ap +
                                    "��DP��" + dp + "��\n" NOR);
#endif
                if( !defense_skill ) defense_skill = "dodge";
                result += SKILL_D(defense_skill)->query_dodge_msg(limb, victim);

                damage = RESULT_DODGE;
        } else {
        //
        //  (4) Check if the victim can parry this attack.
        //
                delta = 0;
                if( weapon2 = your_temp["weapon"] ) {
                        if( !weapon ) delta = 100;
                } else {
                        if( weapon ) delta = -100;
                }

                pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE, delta);
                if( stringp(defense_skill = victim->query_skill_mapped("parry")))
                        pp += pp / 100 * SKILL_D(defense_skill)->query_effect_parry(me, victim);
                if( pp < 1 ) pp = 1;
                if( sizeof(victim->query_enemy()) > 1 )
                        pp = pp * 9 / (8 + sizeof(victim->query_enemy()));
                if( victim->is_busy() ) pp /= 3;

                if( random(ap + pp) < pp ) {
#if INSTALL_COMBAT_TEST
                        if( wizardp(me) && query("env/combat_test", me) )
                                tell_object(me, HIY "��ս�����顿������ AP��" + ap +
                                            "��PP��" + pp + "��\n" NOR);
                        if( wizardp(victim) && query("env/combat_test", victim) )
                                tell_object(victim, HIC "��ս�����顿���Է� AP��" + ap +
                                            "��PP��" + pp + "��\n" NOR);
#endif
                        if( !defense_skill) defense_skill = "parry";
                        if( attack_skill == "throwing" && your["race"] ==  "����" ) {
                                if( weapon2 )
                                        parry_msg = weapon_parry_throwing[random(sizeof(weapon_parry_throwing))];
                                else {
                                        parry_msg = unarm_parry_throwing[random(sizeof(unarm_parry_throwing))];
                                }
                        } else if( martial_skill == "six-finger" ) {
                                if( random(me->query_skill("six-finger", 1)) > victim->query_skill("force", 1)/2 ) {
                                        if( weapon2 ) {
                                                parry_msg = weapon_parry_sixmai[random(sizeof(weapon_parry_sixmai))];
                                                if( my["jiali"] > weapon2->weight() ) {
                                                        parry_msg = replace_string(parry_msg, "$v", weapon2->name());
                                                        weapon2->unequip();
                                                        weapon2->move(environment(victim));
                                                        set("consistence", 0, weapon2);
                                                        if( weapon2->is_item_make() ) {
                                                                parry_msg += HIW "$n" HIW "ֻ���û��ھ��𣬱������ֶ�������\n" NOR;
                                                        } else {
                                                                parry_msg += HIW "ֻ������ž����һ����$n" HIW "���е�" + weapon2->name() +
                                                                             HIW "�ѱ�$N" HIW "�����ν�����Ϊ���أ�\n" NOR;
                                                                set("name", "�ϵ���"+query("name", weapon2), weapon2);
                                                                set("value", 0, weapon2);
                                                                set("weapon_prop", 0, weapon2);
                                                        }
                                                        victim->reset_action();
                                                }
                                        } else parry_msg = unarm_parry_sixmai[random(sizeof(unarm_parry_sixmai))];
                                } else  parry_msg = SKILL_D(defense_skill)->query_parry_msg(weapon2, victim);

                        } else if( defense_skill == "douzhuan-xingyi" || defense_skill == "qiankun-danuoyi" ) {
                                if( random(victim->query_skill(defense_skill, 1)) > me->query_skill("force", 1)/2 ) {
                                        if( weapon) {
                                                if( defense_skill == "douzhuan-xingyi" )
                                                        parry_msg = star_move_weapon[random(sizeof(star_move_weapon))];
                                                else
                                                        parry_msg = qiankun_move_weapon[random(sizeof(qiankun_move_weapon))];

                                                damage=query_temp("apply/damage", me);
                                        } else {
                                                if( defense_skill == "douzhuan-xingyi" )
                                                        parry_msg = star_move_unarm[random(sizeof(star_move_unarm))];
                                                else
                                                        parry_msg = qiankun_move_unarm[random(sizeof(qiankun_move_unarm))];

                                                damage=query_temp("apply/unarmed_damage", me);
                                        }

                                        damage+=query_temp("apply/damage1", me);   // װ�������˺�
                                        damage+=query_temp("apply/damage2", me);   // װ�������˺�
                                        if( query("jingmai/finish", me) )
                                                damage+= ZHOUTIAN_D->query_jingmai_effect("damage");
                                        damage+=query("jingmai/damage", me);       // ���������˺�

                                        damage += (int)me->query_skill(attack_skill, 1);
                                        damage+=query("jiali", me);
                                        damage = (damage + random(damage)) / 2;
#ifdef USE_SKILLS_COMBAT
                                        if( arrayp(att) && sizeof(att) )
                                                damage += (int)att[DAMAGE] * damage / 100;
                                        else
#endif
                                        if( action["damage"] )
                                                damage += action["damage"] * damage / 100;
                                        
                                        damage_bonus = me->query_str();
#ifdef USE_SKILLS_COMBAT
                                        if( arrayp(att) && sizeof(att) )
                                                damage_bonus += (int)att[FORCE2] * damage_bonus / 100;
                                        else
#endif
                                        if( action["force"] )
                                                damage_bonus += action["force"] * damage_bonus / 100;
                                        // calculate the damage
                                        if( damage_bonus > 0 )
                                                damage += (damage_bonus + random(damage_bonus)) / 2;

                                        me->receive_damage("qi", damage, victim);
                                        armor=query_temp("apply/armor", me);
                                        armor+=query_temp("apply/armor1", me);
                                        armor+=query_temp("apply/armor2", me);
                                        if( query("jingmai/finish", me) )
                                                armor+= ZHOUTIAN_D->query_jingmai_effect("armor");
                                        armor+=query("jingmai/armor", me);
                                        if( damage > armor + 2 )
                                                me->receive_wound("qi", (damage - armor)/2, victim);

                                        foo = damage_msg(damage, action["damage_type"]);
                                        foo = replace_string(foo, "$n", "$N");
                                        foo = replace_string(foo, "$p", "$P");
                                        
                                        /*
                                        foo += "( $N" +
                                                status_msg(query("qi", me)*100/
                                                (query("max_qi", me)?query("max_qi", me):100))+")\n";
                                        */
                                        foo += report_status(me, 1);
                                        parry_msg += foo;
                                } else
                                        parry_msg = SKILL_D(defense_skill)->query_parry_msg(weapon2, victim);
                        } else {
                                // change to SKILL_D(defense_skill) after added parry msg to those
                                // martial arts that can parry.
                                parry_msg = SKILL_D(defense_skill)->query_parry_msg(weapon2, victim);
                        }

                        if( !stringp(parry_msg) )
                                parry_msg = SKILL_D("parry")->query_parry_msg(weapon2, victim);

                        if( stringp(parry_msg) )
                                result += parry_msg;

                        damage = RESULT_PARRY;
                } else {
        //
        //  (5) We hit the victim and the victim failed to parry
        //
                        attack = 1;

                        if( weapon )
                                damage=query_temp("apply/damage", me) +
                                       query_temp("apply/damage", me) * query("jingmai/weapon", me) / 100;
                        else
                                damage=query_temp("apply/unarmed_damage", me) +
                                       query_temp("apply/unarmed_damage", me) * query("jingmai/unarmed_damage", me) / 100;

                        damage+=query_temp("apply/damage1", me);
                        damage+=query_temp("apply/damage2", me);
                        damage+=query("jingmai/damage", me);    // ���������˺�

                        damage = damage + me->query_skill(attack_skill, 1);

                        damage+=query("jiali", me);

#ifdef USE_SKILLS_COMBAT
                        if( arrayp(att) && sizeof(att) )
                                damage += (int)att[DAMAGE] * damage / 100;
                        else
#endif
                        if( action["damage"] )
                                damage += action["damage"] * damage / 100;


                        // ���켼�ܺ�Ȼ������а����Ч���ӱ�
                        if( query("special/haoran") && victim->query("shen") < 0 )
                                damage *= 2;
                        else
                        // ���켼�ܾ���ħ����������Ч���ӱ�
                        if( query("special/jiuyou") && victim->query("shen") > 0 )
                                damage *= 2;

                        // �����޼���Ӱ��
                        if( martial_skill == "qiankun-jian" && me->query_skill("kunlun-wuji", 1) >= 100 )
                                damage += me->query_skill("kunlun-wuji", 1);

                        // ѪӰ�󷨵�Ӱ��
                        if( martial_skill == "xuedao-daofa" && me->query_skill("xueying-daofa", 1) >= 100 )
                                damage += me->query_skill("xueying-dafa", 1) * 2;

                        // ������Ӱ��
                        damage_bonus = me->query_str();
                        if( my["jianu"] ) {
                                // does angry bonus
                                damage_bonus += me->cost_craze(my["jianu"]);
                                if( me->query_craze() > 1000 &&
                                    random(my["jianu"] + 200) > 200 ) {
                                        damage_info += random(2) ? HIR "$N" HIR "���һ����˫ĿԲ����һ��������ɱ����Ȼ����\n" NOR
                                                                 : HIR "$N" HIR "�ܲ����������ǰ�������н���$n" HIR "���������顣\n" NOR;
                                        me->cost_craze(200 + random(300));
                                        damage_bonus += my["jianu"] * 2;
                                }
                        }

                        // Clear the special message info after damage info
                        foo_before_hit = 0;
                        foo_after_hit = 0;

                        // Let force skill take effect.
                        if( my["jiali"] && (my["neili"] > my["jiali"]) ) {
                                if( force_skill = me->query_skill_mapped("force") ) {
                                        // ��Ƕ�������������Ļ��׼����˺�����
                                        if( objectp(ob = query_temp("armor/armor", victim)) && ob->query_magic_item() == "�����������" )
                                                delta = 2;
                                        else
                                                delta = 1;

                                        foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus,
                                                my["jiali"] / delta);

                                        if( stringp(foo) ) damage_info += foo; else
                                        if( intp(foo) ) damage_bonus += foo; else
                                        if( mapp(foo) ) {
                                                damage_info += foo["msg"];
                                                damage_bonus += foo["damage"];
                                        }
                                }
                        }
#ifdef USE_SKILLS_COMBAT
                        if( arrayp(att) && sizeof(att) )
                                damage_bonus += (int)att[FORCE2] * damage_bonus / 100;
                        else
#endif
                        if( action["force"] )
                                damage_bonus += action["force"] * damage_bonus / 100;

                        // calculate the damage
                        if( damage_bonus > 0 )
                                damage += (damage_bonus + random(damage_bonus)) / 2;

                        // ���ݹ����Ĳ�λӰ���˺�
                        if( !undefinedp(limb_damage[limb]) )
                                damage = (damage * limb_damage[limb] / 100);

                        // Let's attack & parry skill, weapon & armor do effect
                        while( damage > 0)
                        {
                                if( my["not_living"] || your["not_living"] )
                                        break;

                                if( !living(me) || !living(victim) ) break;
                                if( damage < 1 ) break;

                                if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "���䱦ʯ" )
                                        damage_info += HIY "$N" HIY "�����䱦ʯ����һ��ҫ�۵Ĺ�â�����������޷������ǰ���� ����\n" NOR;
                                else {
                                        delta = 0;
                                        if( attack_skill == "unarmed" && me->query_skill_prepared("unarmed") == "xiantian-gong"
                                        ||  martial_skill == "quanzhen-jian" )
                                                delta = 1;

                                        // Let parry skill take its special effort.
                                        avoid=query_temp("apply/avoid_dodge", me);
                                        if( random(100) >= avoid &&
                                            stringp(defense_skill = victim->query_skill_mapped("dodge")) ) {
                                                foo = SKILL_D(defense_skill)->valid_damage(me, victim, damage, weapon);
                                                if( stringp(foo) ) damage_info += foo; else
                                                if( intp(foo) ) {
                                                        // ���ӻ���������Ч
                                                        if( delta )
                                                                foo = foo - foo / 100 * (hjs / 50);
                                                        else
                                                                foo = foo - foo / 100 * (hjs / 100);
                                                        damage += foo;
                                                } else
                                                if( mapp(foo) ) {
                                                        damage_info += foo["msg"];
                                                        // ���ӻ���������Ч
                                                        if( delta )
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 50);
                                                        else
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 100);
                                                        damage += foo["damage"];
                                                }
                                                if( damage < 1 ) break;
                                        }

                                        avoid=query_temp("apply/avoid_parry", me);
                                        if( random(100) >= avoid &&
                                            stringp(defense_skill = victim->query_skill_mapped("parry")) ) {
                                                foo = SKILL_D(defense_skill)->valid_damage(me, victim, damage, weapon);
                                                if( stringp(foo) ) damage_info += foo; else
                                                if( intp(foo) ) {
                                                        // ���ӻ���������Ч
                                                        if( delta )
                                                                foo = foo - foo / 100 * (hjs / 50);
                                                        else
                                                                foo = foo - foo / 100 * (hjs / 100);
                                                        damage += foo;
                                                } else
                                                if( mapp(foo) ) {
                                                        damage_info += foo["msg"];
                                                        // ���ӻ���������Ч
                                                        if( delta )
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 50);
                                                        else
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 100);
                                                        damage += foo["damage"];
                                                }
                                                if( damage < 1 ) break;
                                        }

                                        // Let armor/cloth take its special effort
                                        if( mapp(your_temp["armor"]) && objectp(ob = your_temp["armor"]["armor"]) ) {
                                                foo = ob->valid_damage(me, victim, damage, weapon);
                                                if( stringp(foo) ) damage_info += foo; else
                                                if( intp(foo) ) {
                                                        // ���ӻ���������Ч
                                                        if( delta )
                                                                foo = foo - foo / 100 * (hjs / 50);
                                                        else
                                                                foo = foo - foo / 100 * (hjs / 100);
                                                        damage += foo;
                                                } else
                                                if( mapp(foo) ) {
                                                        damage_info += foo["msg"];
                                                        // ���ӻ���������Ч
                                                        if( delta )
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 50);
                                                        else
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 100);
                                                        damage += foo["damage"];
                                                }
                                        } else if( mapp(your_temp["armor"]) && objectp(ob = your_temp["armor"]["cloth"]) ) {
                                                foo = ob->valid_damage(me, victim, damage, weapon);
                                                if( stringp(foo) ) damage_info += foo; else
                                                if( intp(foo) ) {
                                                        // ���ӻ���������Ч
                                                        if( delta )
                                                                foo = foo - foo / 100 * (hjs / 50);
                                                        else
                                                                foo = foo - foo / 100 * (hjs / 100);
                                                        damage += foo;
                                                } else
                                                if( mapp(foo) ) {
                                                        damage_info += foo["msg"];
                                                        // ���ӻ���������Ч
                                                        if( delta )
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 50);
                                                        else
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 100);
                                                        damage += foo["damage"];
                                                }
                                        }
                                        if( damage < 1 ) break;
                                        
                                        /*
                                        // ������͸����������͸��׶֮��İ���
                                        if(objectp(weapon) && weapon->through_armor())
                                                return 0;       // Ӳ���ķ������á�armor_vs_force
                                        absp = skill_power(victim, "iron-cloth", SKILL_USAGE_ABSORB);
                                        if(absp)
                                        {
                                                defense_skill = victim->query_skill_mapped("iron-cloth");
                                                if(!defense_skill) defense_skill = "iron-cloth";

                                                if(!mute_flag)
                                                        result += SKILL_D(defense_skill)->query_absorb_msg();
                                                foo = SKILL_D(defense_skill)->absorb_ob(victim, me, damage, absp);
                                                if(stringp(foo))
                                                {
                                                        if(!mute_flag)
                                                        result += foo;
                                                }
                                                else if(intp(foo)) damage += foo;
                                        }                       
                                        */
                                }
                                // Let attack skill take its special effort.
                                avoid=query_temp("apply/avoid_attack", victim);
                                if( random(100) >= avoid && stringp(martial_skill) ) {
                                        foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage);
                                        if( stringp(foo) ) damage_info += foo; else
                                        if( intp(foo) ) damage += foo; else
                                        if( mapp(foo) ) {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                        if( damage < 1 ) break;
                                }

                                // Let weapon or living have their special damage.
                                if( weapon ) {
                                        foo = weapon->hit_ob(me, victim, damage);
                                        if( stringp(foo) ) damage_info += foo; else
                                        if( intp(foo) ) damage += foo; else
                                        if( mapp(foo) ) {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                } else {
                                        foo = me->hit_ob(me, victim, damage);
                                        if( stringp(foo) ) damage_info += foo; else
                                        if( intp(foo) ) damage += foo; else
                                        if( mapp(foo) ) {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }

                                if( damage < 1 ) break;

                                if( mapp(my_temp["apply"]) && my_temp["apply"]["double_damage"] > 0 ) {
                                        if( random(100) < my_temp["apply"]["double_damage"] ) {
                                                int damage2, scale;
                                                damage2 = random(damage);
                                                scale = 100 + damage2 * 10 / damage * 10;
                                                damage += damage2;
                                                damage_info += HIY "$N" HIY "�������飬����������һ��֮�о����������˺�������$n" HIY "��ɡ�" + scale + "%�����˺���\n" NOR;
                                        }
                                }

                                // finish
                                break;
                        }
        //
        //  (6) Inflict the damage.
        //

                        if( victim->query_skill_mapped("dodge") == "lingbo-weibu" &&
                            query_temp("immortal", victim) && random(100) < 90 )
                        {
                                damage = 0;
                                damage_info += HIY "$n" HIY "ʩչ�貨΢��������С������ϡ���һ��ҫ�۵Ĺ�â����ȫ����ʱ�����еĹ������ ����\n" NOR;
                        }

                        if( damage > 0 ) {
                                /*
                                int def_exp;

                                // Let combat exp take effect
                                def_exp = your["combat_exp"];
                                while( random(def_exp) > my["combat_exp"] ) {
                                        damage -= damage / 4;
                                        def_exp /= 2;
                                }
                                */

                                if( my["character"] == "�ĺ�����" )
                                        damage += damage * 20 / 100;

                                if( my["breakup"] ) damage += damage * 10 / 100;

                                // Ԫ��
                                if( query("yuanshen/status", me) )
                                        damage += damage * 50 / 100;

                                if( objectp(ob = query_temp("armor/surcoat", victim)) && ob->query_magic_item() == "���и���" )
                                        damage -= damage * 5 / 100;

                                // calculate wounded
                                wounded = damage;
                                armor=query_temp("apply/armor", victim);
                                armor+=query_temp("apply/armor1", victim);
                                armor+=query_temp("apply/armor2", victim);
                                if( query("jingmai/finish", victim) )
                                        armor += ZHOUTIAN_D->query_jingmai_effect("armor");
                                armor+=query("jingmai/armor",victim);

                                // ���ӻ���������Ч
                                if( attack_skill == "unarmed" && me->query_skill_prepared("unarmed") == "xiantian-gong"
                                ||  martial_skill == "quanzhen-jian" )
                                        armor -= armor / 100 * hjs / 50;
                                else
                                        armor -= armor / 100 * hjs / 100;

                                //if( mapp(your_temp["apply"]) && your_temp["apply"]["armor"] > 0 )
                                //        wounded -= random(your_temp["apply"]["armor"]);
                                if( random(100) >= query_temp("apply/through_armor", me) )
                                        wounded -= random(armor);

                                // �����޼��Ĵ�͸����
                                if( martial_skill == "qiankun-jian" && me->query_skill("kunlun-wuji", 1) >= 125 )
                                        wounded += me->query_skill("kunlun-wuji", 1) / 125 * 100;

                                // ��������--������������Ч
                                if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "��������" )
                                {
                                        damage_info += HIR "\n$N" HIR "�ĳ���������ʯ����һ������Ĺ�â��һ�������"
                                                       "�ĳ���������צ�������$n" HIR "��\n" NOR;
                                        damage += damage / 2;
                                }

                                // ��������--�� ȸ ʯ��Ч��
                                if( objectp(ob = query_temp("armor/surcoat", victim)) && ob->query_magic_item() == "��ȸʯ" )
                                {
                                        result += HIG + victim->name() + HIG "�Ŀ�ȸʯ����һ������Ĺ�â��������⽫" + victim->name() +
                                                  HIG "���֣�����һֻ����Ŀ�ȸ\n��Ծ���裬ȴ�����κ��˿�����\n" NOR;

                                        // ��������--���䱦ʯ��Ч��
                                        if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "���䱦ʯ" )
                                                result += HIY "����" + me->name() + HIY "�����䱦ʯ����һ�����⣬"
                                                          "�Ƿ���Ŀ�ȸ��ʱ��ʧ������\n" NOR;
                                        else
                                        {
                                                message_combatd(result, me, victim);
                                                return 1;
                                        }
                                }

                                // ����ѫ��--�̺����������
                                if( objectp(ob = query_temp("armor/medal", me)) && ob->query_magic_item() == "�̺�����" )
                                {
                                        damage_info += HIC "$N" HIC "�ı̺��������һ�������̺���񷡹���֣����������ĺ�Х�� ����\n" NOR;
                                        damage += damage / 2;
                                        if( !victim->is_busy() )
                                                victim->start_busy(3);
                                }

                                else
                                // ����ѫ��--����������
                                if( objectp(ob = query_temp("armor/medal", me)) && ob->query_magic_item() == "�����" )
                                {
                                        damage_info += HIR "$N" HIR "���������������Ĺ�â��������ʥ�𡹳��ò�Ϩ���������Դ�Ϣ ����\n" NOR;
                                        damage += damage / 2;
                                        if( query("neili", victim) >= 300 )
                                        {
                                                addn("neili", -300, victim);
                                                addn("neili", 300, me);
                                        }
                                }
                                /*
                                if( wounded > 400 )
                                        wounded = (wounded - 400) / 4 + 300;
                                else if( wounded > 200 )
                                        wounded = (wounded - 200) / 2 + 200;
                                else if( wounded < 1 )
                                        wounded = 0;

                                // recalculate damage
                                if( damage > 400 )
                                        damage = (damage - 400) / 4 + 300;
                                else if( damage > 200 )
                                        damage = (damage - 200) / 2 + 200;
                                */
                                if( your["character"] == "��������" )
                                        wounded -= wounded * 20 / 100;

#ifdef REDUCE_PVP_DAMAGE
                                damage = COMBAT_D->reduce_damage(me, victim, damage);
#endif
                                damage = victim->receive_damage("qi", damage, me);
                                if( damage < 1 )
                                        damage_info += BLU "$n" BLU "����Ļ�����$N" BLU "��һ���������˺���\n" NOR;

                                if( wounded > 0 &&
                                    // ((me->is_killing(your["id"]) && random(3) == 1) ||
                                    (has_weapon ||
                                     random(3) == 1) ) {
                                        // We are sure that damage is greater than victim's armor here.
#ifdef REDUCE_PVP_DAMAGE
                                        wounded = COMBAT_D->reduce_wound(me, victim, wounded);
#endif
                                        wounded = victim->receive_wound("qi", wounded, me);
                                } else  wounded = 0;

                                // add message before hit in victim
                                if( foo_before_hit )
                                        result += foo_before_hit;

                                result += damage_msg(damage, action["damage_type"]);
                                /*
                                damage_info += "( $n" +
                                        status_msg(query("qi", victim)*100/
                                        (query("max_qi", victim)?query("max_qi", victim):100))+")\n";
                                */
                                damage_info += replace_string(report_status(victim, 1), "$N", "$n");
                                // ���������ķ���Ч��
                                if( victim->query_skill("qimen-xuanshu", 1) >= 100 )
                                {
                                        if( random(victim->query_skill("qimen-xuanshu", 1)) > 100 && random(3) == 1 )
                                        {
                                                damage_info += HIG "$n" HIG "ʩչ���������������ķ���Ч����ʹ��$N" HIG "����ͬʱҲ�ܵ����ˡ�\n" NOR;
                                                me->receive_damage("qi", damage * victim->query_skill("qimen-xuanshu", 1) / 5000, victim);
                                                me->receive_wound("qi", wounded * victim->query_skill("qimen-xuanshu", 1) / 5000, victim);

                                                if( query("eff_qi", victim) + wounded * victim->query_skill("qimen-xuanshu", 1) / 5000 <
                                                    query("max_qi", victim) )
                                                        addn("eff_qi", wounded * victim->query_skill("qimen-xuanshu", 1) / 5000, victim);
                                                else
                                                        set("eff_qi", query("max_qi", victim), victim);

                                                if( query("qi", victim) + damage * victim->query_skill("qimen-xuanshu", 1) / 5000 <
                                                    query("eff_qi", victim) )
                                                        addn("qi", damage * victim->query_skill("qimen-xuanshu", 1) / 5000, victim);
                                                else
                                                       set("qi", query("eff_qi", victim), victim);
                                                
                                                /*
                                                damage_info += "( $N" +
                                                        status_msg(query("qi", me)*100/
                                                        (query("max_qi", me)?query("max_qi", me):100))+")\n";
                                                */
                                                damage_info += report_status(me, 1);
                                        }
                                }

                                // ѪӰ��������Ч��
                                if( martial_skill == "xuedao-daofa" && me->query_skill("xueying-dafa", 1) >= 1 )
                                {
                                        addn("neili", -1 * (me->query_skill("xueying-dafa", 1) + me->query_skill("xuedao-daofa", 1)) / 12, victim);
                                        if( query("neili", victim) < 0 )
                                                set("neili", 0, victim);
                                }

                                // ��Ʒ�����˺�����Ч��
                                avoid=query_temp("apply/counter_damage", victim);
                                if( random(100) < avoid && random(3) == 1 ) {
                                        if( objectp(ob=query_temp("armor/armor", victim)) &&
                                            query("enchase/apply_prop/counter_damage", ob) )
                                                damage_info += BLINK + HIM + ob->name() + BLINK + HIM "����һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;
                                        else
                                        if( objectp(ob=query_temp("armor/cloth", victim)) &&
                                            query("enchase/apply_prop/counter_damage", ob) )
                                                damage_info += BLINK + HIM + ob->name() + BLINK + HIM "����һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;
                                        else
                                                damage_info += BLINK + HIM "$n" BLINK + HIM "������һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;

                                        me->receive_damage("qi", damage/5, victim);
                                        me->receive_wound("qi", wounded/5, victim);
                                        /*
                                        damage_info += "( $N" +
                                                status_msg(query("qi", me)*100/
                                                (query("max_qi", me)?query("max_qi", me):100))+")\n";
                                        */
                                        damage_info += report_status(me, 1);
                                }
                        }

                        if( foo_after_hit )
                                damage_info += foo_after_hit;
        //
        //  (7) Give experience
        //
                        /*
                        if( victim->is_boss() && query("fight_boss", victim) &&
                            my["level"] < your["level"]*2 )
                                addn("combat_exp", me->query_int()/10, me);

                        if( your["combat_exp"] > my["combat_exp"] &&
                            (random(my["jing"]*100/my["max_jing"] + me->query_int()) > 50) ) {
                                if( my["combat_exp"] > EXP_LIMIT )
                                        addn("combat_exp", me->query_int()/60, me);
                                else
                                        addn("combat_exp", me->query_int()/15, me);
                                me->improve_skill(attack_skill, random(me->query_int()));
                                if( my["potential"] - my["learned_points"] < 10*me->query_int() )
                                        addn("potential", 1, me);

                        }
                        */
                }
        }

        result = replace_string(result, "$l", limb);
        if( objectp(weapon2=query_temp("weapon", victim)) )
                result = replace_string(result, "$v", weapon2->name());
        if( objectp(weapon) )
                result = replace_string(result, "$w", weapon->name());
        else if( stringp(action["weapon"]) )
                result = replace_string(result, "$w", action["weapon"]);
        else if( attack_skill == "finger" || attack_skill == "hand" )
                result = replace_string(result, "$w", "��ָ" );
        else if( attack_skill == "strike" || attack_skill == "claw" )
                result = replace_string(result, "$w", "����" );
        else    result = replace_string(result, "$w", "ȭͷ" );

        message_combatd(result, me, victim, damage_info);

        if( damage > 0 ) {
#if INSTALL_COMBAT_TEST
                if( userp(me)/* && query("env/combat_test", me)*/ )
                        tell_object(me, HIW "( ���" +
                                        query("name", victim)+HIW"���"+
                                        damage + "���˺���" +
                                        wounded + "�㴴�ˡ�)\n" NOR);
                if( userp(victim)/* && query("env/combat_test", victim)*/ )
                        tell_object(victim, HIG "( ���ܵ�" +
                                        query("name", me)+HIG+damage+"���˺���"+
                                        wounded + "�㴴�ˡ�)\n" NOR);
#endif
                if( attack == 1 ) {
                        switch( limb ) {
                        // ͷ�������˻���һЩ��
                        case "ͷ��":
                        case "����":
                                damage /= 4;
                                if( damage < 1 )
                                        damage = 1;
                                if( damage > 8000 )
                                        damage = 8000;
                                victim->receive_damage("jing", damage, me );
                                delta=query("jing", victim)*100/query("max_jing", victim);
                                if( delta <= 30 )
                                        tell_object(victim, head_damage_me_msg[2]);
                                else if( delta <= 70 )
                                        tell_object(victim, head_damage_me_msg[1]);
                                else
                                        tell_object(victim, head_damage_me_msg[0]);
                                break;
                        // ������Щ��λ�������ܵ��񵴡�
                        case "�ؿ�":
                        case "����":
                        case "С��":
                                if( query("max_neili", victim) && query("neili", victim)){
                                        damage /= 4;
                                        if( damage < 1 )
                                                damage = 1;
                                        if( damage > 10000 )
                                                damage = 10000;
                                        if( query("neili", victim) <= damage )
                                                set("neili", 0, victim);
                                        else
                                                addn("neili", -damage, victim);
                                        if( damage <= 500 )
                                                foo = body_damage_me_msg[0];
                                        else if( damage <= 1000 )
                                                foo = body_damage_me_msg[1];
                                        else
                                                foo = body_damage_me_msg[2];
                                        foo = replace_string(foo, "$l", limb);
                                        tell_object(victim, foo);
                                }
                                break;
                        }
                        victim->receive_limbs_wound(limb, damage);
                }

                // ��ʾ��Ҿ�������Ѫ
                /*
                if( query("env/verbose", me) )
                {
                        tell_object(me, SAVEC);
                        tell_object(me, SETDISPLAY(21,49)+DELLINE);
                        tell_object(me, SETDISPLAY(22,49)+DELLINE);
                        tell_object(me, SETDISPLAY(23,49)+DELLINE);
                        tell_object(me, SETDISPLAY(21,50)+HIY"������������������������������");
                        tell_object(me, SETDISPLAY(22,50)+HIY"��");
                        tell_object(me, SETDISPLAY(22,52)+HIG"����"HIR+query("jing",me)+"/"+query("eff_jing",me));
                        tell_object(me, SETDISPLAY(22,65)+HIG"����"HIR+query("qi",me)+"/"+query("eff_qi",me));
                        tell_object(me, SETDISPLAY(22,78)+HIY"��");
                        tell_object(me, SETDISPLAY(23,50)+HIY"������������������������������"NOR);
                        tell_object(me, REST);
                }
                */

                if( query("special_skill/monster", victim) && random(5) == 1){
                        message_vision(HIG "$N" HIG "ʩչ����������������$n" HIG "����ͬʱҲ�ܵ����ˡ�\n" NOR, victim, me);
                        me->receive_damage("qi", damage, victim);
                        if( random(2) == 1 ) me->receive_wound("qi", wounded, victim);
                        //damage_info = "(" + me->name() + status_msg(query("qi", me) * 100 / query("max_qi", me)) + ")\n";
                        damage_info = report_status(me, 1);
                        message_vision(damage_info, me);
                }

                if( query("special_skill/demon", victim) && random(5) == 1 )
                        message_vision(HIW "$N" HIW "ǿ��һ�ڵ���֮����������ת֮�£���������������\n" NOR, victim, me);
                        victim->receive_curing("qi", victim->query("max_qi") / 3);

                if( victim->is_busy() ) {
                        victim->interrupt_me(me, 30 + random(10));
                        message_vision(HIW "$N�ж�΢�����ƣ���æĬ���������ƿ�������ҪѨ��\n" NOR, victim);
                }

                if( victim->query_condition("no_perform") && !random(6) ) {
                        message_vision(HIY"$N�����Լ���Ѫ���в�������æĬ��������Ӳ��ѹ���˷��ڲ��ѵ���Ѫ��\n"NOR, victim);
                        victim->clear_condition("no_perform");
                }

                if( me->query_condition("no_exert") && !random(6) ) {
                        message_vision(HIC"$N�����Լ���Ϣ���ȣ���æĬ��������������Ϣ��\n"NOR, victim);
                        victim->clear_condition("no_exert");
                }
                
                if( (!me->is_killing(your["id"])) &&
                    (!victim->is_killing(my["id"])) &&
                    !query("not_living", victim) &&
                    your["qi"] * 2 <= your["max_qi"] ) {
                        me->remove_enemy(victim);
                        victim->remove_enemy(me);
                        if( query("can_speak", me) && query("can_speak", victim) )
                                message_vision(winner_msg[random(sizeof(winner_msg))],
                                               me, victim);
                        if( me == victim->query_competitor() ) {
                                me->win();
                                victim->lost();
                        }
                }
                // if(me->query("special_skill/tianmo") && random(5) == 1) {
                //         message_vision(HIR"$N���и��ֳ���ħ����ʱ��������ѧ�������Ե�Ѫ�����������Ƹ���������\n" NOR, me, victim);
                //         me->receive_curing("qi", (me->query("max_qi")*(int)me->query("special_skill/tianmo",1)*2/100));
                //         do_attack(me, victim, weapon, 3);
                // }
                //
                
        }
        if( functionp(action["post_action"]) )
                evaluate( action["post_action"], me, victim, weapon, damage);
        else
                WEAPON_D->bash_weapon(me, victim, weapon, damage);

        // See if the victim can make a riposte.
        if( attack_type == TYPE_REGULAR &&
            damage < 1 &&
            your_temp["guarding"] ) {
                your_temp["guarding"];
                if( random(my["dex"]) < 5 ) {
                        message_combatd("$Nһ�����У�¶����������\n",
                                        me, 0, "");
                        do_attack(victim, me, your["weapon"],
                                  TYPE_QUICK);
                } else {
                        message_combatd("$N��$n����ʧ�󣬳û�����������\n",
                                        victim, me, "");
                        do_attack(victim, me, your_temp["weapon"],
                                  TYPE_RIPOSTE);
                }
        }
}

// do damage when perform
// I will consider the damage of the weapon
// what is final: final may be a function with result type string,
// or a single string.
// The syntax of the final string is info:damage_type@limb or info only,
// If the limb if ?, the system will auto select limb of
// target, if the final is a single string, the system will
// treat as damage infomation.
varargs string do_damage(object me, object target, mixed type,
                         int damage, int percent, mixed final)
{
        mapping my;
        object weapon;
        object cloth;
        object ob;
        int apply;
        int armor;
        int wound;
        int jiali;
        int bonus;
        mixed foo;
        string msg;
        string skill;
        string *limbs;
        string limb;
        string damage_type;
        string result;
        int str;
        int damage_bonus;
        mapping prepare;
        string attack_skill;
        int avoid;
        int def_exp, att_exp;
        int hjs;

        if( damage < 0 ) return "";
        if( me->is_ghost() || target->is_ghost() ) return "";
        if( environment(me) != environment(target) ) {
                me->remove_enemy(target);
                target->remove_enemy(me);
                return "";
        }

        hjs = me->query_skill("huajia-su", 1);

        // Am I use weapon
        if( type == WEAPON_ATTACK ) {
                apply=query_temp("apply/damage", me);
                apply+=query_temp("apply/damage1", me);
                apply+=query_temp("apply/damage2", me);
                apply+=apply*query("jingmai/weapon",me)/100;
                weapon=query_temp("weapon", me);
        } else if( type == UNARMED_ATTACK ) {
                apply=query_temp("apply/unarmed_damage", me);
                apply+=query_temp("apply/damage1", me);
                apply+=query_temp("apply/damage2", me);
                apply+=apply*query("jingmai/unarmed_damage",me)/100;
                weapon = 0;
        } else if( type == REMOTE_ATTACK ) {
                apply  = 0;
                weapon = 0;
        } else {
                if( query_temp("weapon", me)){
                        apply=query_temp("apply/damage", me);
                        apply+=apply*query("jingmai/weapon",me)/100;
                        weapon=query_temp("weapon", me);
                } else {
                        apply=query_temp("apply/unarmed_damage", me);
                        apply+=apply*query("jingmai/unarmed_damage",me)/100;
                        weapon = 0;
                }
                apply+=query_temp("apply/damage1", me);
                apply+=query_temp("apply/damage2", me);
        }

        prepare = me->query_skill_prepare();
        if( !prepare ) prepare = ([]);

        if( type == REMOTE_ATTACK )
                skill = "force";
        else if( weapon )
                skill=query("skill_type", weapon);
        else {
                switch( sizeof(prepare) ) {
                case 0: skill = "unarmed"; break;
                case 1:
                case 2: skill = (keys(prepare))[0]; break;
                }
        }

        if( skill == "pin" ) skill = "sword";

        attack_skill = me->query_skill_mapped(skill);

        // Check the target's armor
        armor=query_temp("apply/armor", target);
        armor+=query_temp("apply/armor1", target);
        armor+=query_temp("apply/armor2", target);
        armor+=query("jingmai/armor", target) * 100;

        damage += apply;
        damage += query("jingmai/damage",me);

        // ���������޼�������
        if( me->query_skill("kunlun-wuji", 1) >= 100 )
                damage += me->query_skill("kunlun-wuji", 1);

        msg = "";
        foo_after_hit = 0;

        while (type == UNARMED_ATTACK || type == WEAPON_ATTACK )
        {
                if( !living(target) ) break;

                if( random(100) < 20 &&
                   (attack_skill == "six-finger" ||
                    attack_skill == "dragon-strike" ||
                    attack_skill == "moon-blade" ||
                    attack_skill == "lonely-sword") )
                        break;

                if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "���䱦ʯ" )
                        msg += HIY "$N" HIY "�����䱦ʯ����һ��ҫ�۵Ĺ�â�����������޷������ǰ���� ����\n" NOR;
                else
                {
                        avoid=query_temp("apply/avoid_parry", me);
                        skill = target->query_skill_mapped("parry");

                        // Let parry skill take its special effort
                        if( stringp(skill) && (skill == "qiankun-danuoyi" ||
                            skill == "douzhuan-xingyi") ) {
                                foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) damage += foo; else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        damage += foo["damage"];
                                }
                        } else if( random(100) >= avoid && stringp(skill) ) {
                                foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) {
                                        // ���ӻ���������Ч
                                        if( hjs > 100 )
                                                foo = foo - foo / 100 * hjs / 100;
                                        damage += foo;
                                } else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        // ���ӻ���������Ч
                                        if( hjs > 100 )
                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * hjs / 100;
                                        damage += foo["damage"];
                                }
                        }

                        if( damage < 1 ) break;

                        avoid=query_temp("apply/avoid_dodge", me);
                        skill = target->query_skill_mapped("dodge");

                        // Let dodge skill take its special effort
                        if( stringp(skill) && skill == "lingbo-weibu") {
                                foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) damage += foo; else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        damage += foo["damage"];
                                }
                        } else if( random(100) > avoid && stringp(skill) ) {
                                foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) {
                                        // ���ӻ���������Ч
                                        if( hjs > 100 )
                                                foo = foo - foo / 100 * hjs / 100;
                                        damage += foo;
                                } else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        // ���ӻ���������Ч
                                        if( hjs > 100 )
                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * hjs / 100;
                                        damage += foo["damage"];
                                }
                        }

                        if( damage < 1) break;

                        // Let cloth & armor take its special effort
                        if( cloth=query_temp("armor/armor", target)){
                                foo = cloth->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) {
                                        // ���ӻ���������Ч
                                        if( hjs > 100 )
                                                foo = foo - foo / 100 * hjs / 100;
                                        damage += foo;
                                } else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        // ���ӻ���������Ч
                                        if( hjs > 100 )
                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * hjs / 100;
                                        damage += foo["damage"];
                                }
                        }else if( cloth=query_temp("armor/cloth", target)){
                                foo = cloth->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) {
                                        // ���ӻ���������Ч
                                        if( hjs > 100 )
                                                foo = foo - foo / 100 * hjs / 100;
                                        damage += foo;
                                } else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        // ���ӻ���������Ч
                                        if( hjs > 100 )
                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * hjs / 100;
                                        damage += foo["damage"];
                                }
                        }
                }
                // Finish
                break;
        }

        if( target->query_skill_mapped("dodge") == "lingbo-weibu" &&
            query_temp("immortal", target) && random(100) < 90 )
        {
                damage = 0;
                msg += HIY "$n" HIY "ʩչ�貨΢��������С������ϡ���һ��ҫ�۵Ĺ�â����ȫ����ʱ��ȥ���е��˺� ����\n" NOR;
        }

        /*
        // Let combat exp take effect
        if( damage > 0 )
        {
                def_exp=query("combat_exp", target);
                att_exp=query("combat_exp", me);
                while( random(def_exp) > att_exp ) {
                        damage -= damage / 4;
                        def_exp /= 2;
                }
        }
        */

        while (damage > 0)
        {
                if( target->is_busy() ) target->interrupt_me(target, 30 + random(10));

                // Let weapon/unarmed attack take its special effort
                if( type == WEAPON_ATTACK && objectp(weapon) )
                        // weapon attack
                        foo = weapon->hit_ob(me, target, damage);
                else if( type == UNARMED_ATTACK )
                        // unarmed attack
                        foo = me->hit_ob(me, target, damage);
                else if( type == SPECIAL_ATTACK ) {
                        if( objectp(weapon) )
                                foo = weapon->hit_ob(me, target, damage);
                        else
                                foo = me->hit_ob(me, target, damage);
                } else if( objectp(type) )
                        // special item attack
                        foo = type->hit_ob(me, target, damage);

                if( stringp(foo) ) msg += foo; else
                if( intp(foo) ) damage += foo; else
                if( mapp(foo) ) {
                        msg += foo["msg"];
                        damage += foo["damage"];
                }

                // do enforce effect
                my = me->query_entire_dbase();
                if( (jiali = my["jiali"]) > 0 && my["neili"] >= jiali ) {
                        // eforced
                        my["neili"] -= jiali;

                        if( objectp(ob = query_temp("armor/armor", target)) && ob->query_magic_item() == "�����������" )
                                jiali /= 2;

                        if( type == REMOTE_ATTACK || type == SPECIAL_ATTACK ) {
                                damage_bonus = SKILLS_D->enforce_power(me, jiali);
                        } else {
                                damage_bonus = SKILLS_D->enforce_power(me, jiali);

                                if( !living(target) ) break;
                                // check special force effort
                                skill = target->query_skill_mapped("force");
                                if( stringp(skill) && (!objectp(ob = query_temp("armor/surcoat", me)) || ob->query_magic_item() != "���䱦ʯ") ) {
                                        foo = SKILL_D(skill)->valid_damage(me, target, damage_bonus);
                                        if( stringp(foo) ) msg += foo; else
                                        if( intp(foo) ) damage_bonus += foo; else
                                        if( mapp(foo) ) {
                                                msg += foo["msg"];
                                                damage_bonus += foo["damage"];
                                        }
                                }
                        }
                        damage += damage_bonus;
                }

                if( damage < 1 ) break;

                if( query("breakup", me) ) damage += damage * 10 / 100;

                // Ԫ��
                if( query("yuanshen/status", me) )
                        damage += damage * 50 / 100;

                if( objectp(ob = query_temp("armor/surcoat", target)) && ob->query_magic_item() == "���и���" )
                        damage -= damage * 5 / 100;

                // ��������--������������Ч
                if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "��������" )
                {
                        msg += HIR "\n$N" HIR "�ĳ���������ʯ����һ������Ĺ�â��һ�������"
                               "�ĳ���������צ�������$n" HIR "��\n" NOR;
                        damage += damage / 2;
                }

                // ����ѫ��--�̺����������
                if( objectp(ob = query_temp("armor/medal", me)) && ob->query_magic_item() == "�̺�����" )
                {
                        msg += HIC "$N" HIC "�ı̺��������һ�������̺���񷡹���֣����������ĺ�Х�� ����\n" NOR;
                        damage += damage / 2;
                        if( !target->is_busy() )
                                target->start_busy(3);
                }

                else
                // ����ѫ��--����������
                if( objectp(ob = query_temp("armor/medal", me)) && ob->query_magic_item() == "�����" )
                {
                        msg += HIR "$N" HIR "���������������Ĺ�â��������ʥ�𡹳��ò�Ϩ���������Դ�Ϣ ����\n" NOR;
                        damage += damage / 2;
                        if( query("neili", target) >= 300 )
                        {
                                addn("neili", -300, target);
                                addn("neili", 300, me);
                        }
                }

                // ��������--�� ȸ ʯ��Ч��
                if( objectp(ob = query_temp("armor/surcoat", target)) && ob->query_magic_item() == "��ȸʯ" )
                {
                        msg += HIG + target->name() + HIG "�Ŀ�ȸʯ����һ������Ĺ�â��������⽫" +
                               target->name() +  HIG "���֣�����һֻ����Ŀ�\nȸ��Ծ���裬ȴ�����κ��˿�����\n" NOR;

                        // ��������--���䱦ʯ��Ч��
                        if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "���䱦ʯ" )
                        {
                                msg += HIY "����" + me->name() + HIY "�����䱦ʯ����һ�����⣬�Ƿ���"
                                       "�Ŀ�ȸ��ʱ��ʧ������\n" NOR;

                        }
                        else
                                return msg;
                }

                if( query_temp("apply/double_damage", me)>0){
                        if( random(100)<query_temp("apply/double_damage", me)){
                                int damage2, scale;
                                damage2 = random(damage);
                                scale = 100 + damage2 * 10 / damage * 10;
                                damage += damage2;
                                msg += HIY "$N" HIY "�������飬����������һ��֮�о����������˺�������$n" HIY "��ɡ�" + scale + "%�����˺���\n" NOR;
                        }
                }

                // do str effect
                str=me->query_str()+query_temp("str", me)+query("jingmai/str", me);
                if( str < 20 )
                        damage += damage * str / 50;
                else if( str < 40 )
                        damage += damage * ((str - 20) / 2 + 20) / 50;
                else
                        damage += damage / 50 * ((str - 40) / 4 + 30);

                // recalculate damage
                if( damage > 1500 )
                        damage = (damage - 1500) / 4 + 1000;
                else if( damage > 500 )
                        damage = (damage - 500) / 2 + 500;

                // do damage
#ifdef REDUCE_PVP_DAMAGE
                damage = COMBAT_D->reduce_damage(me, target, damage);
#endif
                // ���ӻ���������Ч
                if( hjs > 100 )
                        armor = armor - armor / 100 * hjs / 100;

                if( random(100) >= query_temp("apply/through_armor", me) )
                        wound = (damage - random(armor)) * percent / 100;
                else
                        wound = damage * percent / 100;

                if( me->query_skill("kunlun-wuji", 1) >= 125 )
                        wound += wound + me->query_skill("kunlun-wuji", 1) / 125 * 100;

                // ѪӰ��������Ч��
                if( me->query_skill("xueying-dafa", 1) >= 100 )
                {
                        addn("neili", -1 * (me->query_skill("xueying-dafa", 1) + me->query_skill("xuedao-daofa", 1)) / 12, target);
                        if( query("neili", target) < 0 )
                                set("neili", 0, target);
                }

                damage = target->receive_damage("qi", damage, me);
                if( damage < 1 )
                        msg += BLU "$n" BLU "����Ļ�����$N" BLU "��һ���������˺���\n" NOR;

                if( wound > 0 ) {
#ifdef REDUCE_PVP_DAMAGE
                        wound = COMBAT_D->reduce_wound(me, target, wound);
#endif
                        wound = target->receive_wound("qi", wound, me);
                }
                else wound = 0;

                if( functionp(final) ) final = evaluate(final);
                if( stringp(final) ) {
                        if( sscanf(final, "%s@%s", final, limb) == 2 ) {
                                if( sscanf(final, "%s:%s", result, damage_type) != 2 ) {
                                        result = HIR "���д��˸����У�";
                                        damage_type = final;
                                }
                                if( sscanf(limb, "?%*s") ) {
                                        // auto select limb
                                        limbs=query("limbs", target);
                                        if( !arrayp(limbs) ) {
                                                limbs = ({ "����" });
                                                set("limbs", limbs, target);
                                        }
                                        limb = limbs[random(sizeof(limbs))];
                                }

                                // indicate damage type & limb
                                final = replace_string(damage_msg(damage, damage_type), "$l", limb);
                                final = replace_string(final, "$n", "$n" HIR);
                                final = replace_string(final, "$N", "$N" HIR);
                                final = replace_string(final, "$p", "$p" HIR);
                                final = replace_string(final, "$P", "$P" HIR);
                                if( weapon )
                                        final = replace_string(final, "$w", weapon->name() + HIR);
                                final = result + HIR + final + NOR;
                        }
                        msg += final;
                        /*
                        msg +="($n"+status_msg(query("qi", target)*100/(query("max_qi", target)?
                                                   query("max_qi", target):100))+")\n";
                        */
                        msg += replace_string(report_status(target, 1), "$N", "$n");
                }
#if INSTALL_COMBAT_TEST
                msg += HIW "( $N" HIW "��$n" HIW "���" + damage + "���˺���" + wound + "�㴴�ˡ�)\n" NOR;
#endif

                // ���������ķ���Ч��
                if( target->query_skill("qimen-xuanshu", 1) >= 100 )
                {
                        if( random(target->query_skill("qimen-xuanshu", 1)) > 100 && random(3) == 1 )
                        {
                                msg += HIG "$n" HIG "ʩչ���������������ķ���Ч����ʹ��$N" HIG "����ͬʱҲ�ܵ����ˡ�\n" NOR;
                                // ����
                                me->receive_damage("qi", damage * target->query_skill("qimen-xuanshu", 1) / 5000, target);
                                me->receive_wound("qi", wound * target->query_skill("qimen-xuanshu", 1) / 5000, target);

                                if( query("eff_qi", target) + wound * target->query_skill("qimen-xuanshu", 1) / 5000 <
                                    query("max_qi", target) )
                                        addn("eff_qi", wound * target->query_skill("qimen-xuanshu", 1) / 5000, target);
                                else
                                        set("eff_qi", query("max_qi", target), target);

                                if( query("qi", target) + damage * target->query_skill("qimen-xuanshu", 1) / 5000 <
                                    query("eff_qi", target) )
                                        addn("qi", damage * target->query_skill("qimen-xuanshu", 1) / 5000, target);
                                else
                                       set("qi", query("eff_qi", target), target);
                                
                                /*
                                msg += "( $N" +
                                        status_msg(query("qi", me)*100/
                                        (query("max_qi", me)?query("max_qi", me):100))+")\n";
                                */
                                msg += report_status(me, 1);
                        }
                }

                // ��Ʒ���߷���Ч��
                avoid=query_temp("apply/counter_damage", target);
                if( random(100) < avoid && random(5) == 1 ) {
                        if( objectp(cloth=query_temp("armor/armor", target)) &&
                            query("enchase/apply_prop/counter_damage", cloth) )
                                msg += BLINK + HIM + cloth->name() + BLINK + HIM "����һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;
                        else
                        if( objectp(cloth=query_temp("armor/cloth", target)) &&
                            query("enchase/apply_prop/counter_damage", cloth) )
                                msg += BLINK + HIM + cloth->name() + BLINK + HIM "����һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;
                        else
                                msg += BLINK + HIM "$n" BLINK + HIM "������һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;

                        me->receive_damage("qi", damage/5, target);
                        me->receive_wound("qi", wound/5, target);
                        /*
                        msg += "( $N" +
                                status_msg(query("qi", me)*100/
                                (query("max_qi", me)?query("max_qi", me):100))+")\n";
                        */
                        msg += report_status(me, 1);
                }
                if( query("special_skill/monster", target) && random(5) == 1){
                        message_vision(HIG "$N" HIG "ʩչ����������������$n" HIG "����ͬʱҲ�ܵ����ˡ�\n" NOR, target, me);
                        me->receive_damage("qi", damage, target);
                        if( random(2) == 1 ) me->receive_wound("qi", wound, target);
                        /*
                        msg += "( $N" +
                                status_msg(query("qi", me)*100/
                                (query("max_qi", me)?query("max_qi", me):100))+")\n";
                        */
                        msg += report_status(me, 1);
                }
                break;
        }

        if( foo_after_hit ) msg += foo_after_hit;
        if( foo_before_hit ) msg = foo_before_hit + msg;
        // Clear the special message info after damage info
        foo_before_hit = 0;
        foo_after_hit = 0;

        return msg;
}

//  auto_perform()
int auto_perform(object me, object target, string skill)
{
        int l;
        string dir;
        string file;
        mixed *all_file;

        if( !stringp(dir = SKILL_D(skill) + "/") ||
            file_size(dir) != -2 )
                return 0;

        if( file_size(dir + "perform/") == -2 ) {
                all_file = get_dir(dir + "perform/");
                if( !sizeof(all_file) )
                        all_file = get_dir(dir);
                else
                        dir += "perform/";
        } else
                all_file = get_dir(dir);

        if( !sizeof(all_file) )
                return 0;

        all_file = filter_array(all_file, (: is_c_file($1) :));
        if( !sizeof(all_file) )
                return 0;

        file = all_file[random(sizeof(all_file))];
        l = strlen(file);
        file = dir + file[0..l-3];
        return (int)call_other(file, "perform", me, target);
}

//  fight()
//
//  This is called in the attack() defined in F_ATTACK, which handles fighting
//  in the heart_beat() of all livings. Be sure to optimize it carefully.
//
void fight(object me, object victim)
{
        object ob;
        string skill_name;
        object weapon, weapon2;
        string attack_skill;
        int double_attack;
        mapping prepare;
        string result;
        mapping my_temp;
        int i, auto_pf, pf_flag;
        string pf_skill, pf_skill1, pf_skill2;

        if( !living(me) || me->is_busy() ) return;
        if( !me->visible(victim)) return;
        if( environment(me)!=environment(victim) ) return;

        if( !mapp(my_temp = me->query_entire_temp_dbase()) )
                my_temp = ([ ]);

        auto_pf = 0;
        if( query("auto_perform", me))auto_pf=query("auto_perform", me);
        else            auto_pf = me->query_auto_perform();
        if( auto_pf < 0 ) auto_pf = 0;
        if( auto_pf > 10 ) auto_pf = 10;

        prepare = me->query_skill_prepare();
        if( sizeof(prepare) && stringp(attack_skill = (keys(prepare))[0]) ) {
                if( !query_temp("weapon", me) && (attack_skill == "sword" ||
                    attack_skill == "blade" || attack_skill == "hammer" || attack_skill == "whip") ) {
                        for (i=0; i<sizeof(keys(prepare)); i++)
                                me->prepare_skill((keys(prepare))[i]);
                        tell_object(me, HIY "�����ڲ���" HIR "���ּ���" HIY "���й�����"
                                        HIY "ȡ������" HIR "��������" HIY "������\n" NOR);
                }
        }

        if( weapon = my_temp["weapon"] )
                attack_skill=query("skill_type", weapon);
        else if( !prepare || sizeof(prepare) == 0 ) attack_skill = "unarmed";
        else if( sizeof(prepare) ) attack_skill = (keys(prepare))[0];
        if( attack_skill == "pin" ) attack_skill = "sword";

        attack_skill = me->query_skill_mapped(attack_skill);

        if( auto_pf == 1 || (random(auto_pf) == 1) ) {
                pf_flag = 0;
                if( attack_skill ) {
                        pf_skill1 = attack_skill;
                        pf_flag = 1;
                }
                if( !weapon && prepare && sizeof(prepare) > 1 )
                        pf_skill2 = me->query_skill_mapped((keys(prepare))[1]);
                if( pf_skill2 ) pf_flag = 2;
                if( pf_flag == 1 )
                        auto_perform(me, victim, pf_skill1);
                else if( pf_flag == 2 ) {
                        if( random(2) ) pf_skill = pf_skill1;
                        else pf_skill = pf_skill2;
                        if( !auto_perform(me, victim, pf_skill) )
                                auto_perform(me, victim, (pf_skill == pf_skill1) ?
                                                        pf_skill2 : pf_skill1);
                }
        }

        if( !objectp(me) || !objectp(victim) ) return;
        if( me->is_busy() ) return;

        if( attack_skill && random(me->query_dex()) >= 8 )
                double_attack = (sizeof(prepare) >= 2 && !weapon) ||
                        SKILL_D(attack_skill)->double_attack();

        // If victim is busy or unconcious, always take the chance to make an attack.
        if( victim->is_busy() || !living(victim) ) {
                set_temp("guarding", 0, me);
                if( !victim->is_fighting(me) ) victim->fight_ob(me);
                do_attack(me,victim,query_temp("weapon", me),TYPE_QUICK);

                if( me->is_fighting(victim) && victim->is_fighting(me) ) {
                        if( double_attack ) {
                                set_temp("action_flag", 1, me);
                                do_attack(me, victim, my_temp["weapon"], TYPE_QUICK);
                                set_temp("action_flag", 0, me);
                        } else // ��������
                        if( objectp(weapon) &&
                            objectp(weapon2=query_temp("secondary_weapon", me)) &&
                            sizeof(me->query_skill_prepare()) > 1 &&
                            me->query_skill_prepared(query("skill_type", weapon)) &&
                            me->query_skill_prepared(query("skill_type", weapon2))) {
                                if( query_temp("hand_flag", me) ) // �ϴ�ʹ�õ�������
                                        do_attack(me, victim, weapon, TYPE_QUICK, 1);
                                else
                                        do_attack(me, victim, weapon2, TYPE_QUICK, 2);
                        }
                }
                /*
                if( living(victim) ) {
                        if( stringp(attack_skill) ) {
                                set_temp("action_flag", 1, me);
                                SKILL_D(attack_skill)->do_interlink(me, victim);
                                set_temp("action_flag", 0, me);
                        }
                }
                */
        // Else, see if we are brave enough to make an aggressive action.
        } else if( me->query_str() > random(victim->query_str() * 3 / 4) ) {
                set_temp("guarding", 0, me);
                if( !victim->is_fighting(me) ) victim->fight_ob(me);
                do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);

                if( me->is_fighting(victim) && victim->is_fighting(me) ) {
                        if( double_attack ) {
                                set_temp("action_flag", 1, me);
                                do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);
                                set_temp("action_flag", 0, me);
                        } else // ��������
                        if( objectp(weapon) &&
                            objectp(weapon2=query_temp("secondary_weapon", me)) &&
                            sizeof(me->query_skill_prepare()) > 1 &&
                            me->query_skill_prepared(query("skill_type", weapon)) &&
                            me->query_skill_prepared(query("skill_type", weapon2))) {
                                if( query_temp("hand_flag", me) ) // �ϴ�ʹ�õ�������
                                        do_attack(me, victim, weapon, TYPE_REGULAR, 1);
                                else
                                        do_attack(me, victim, weapon2, TYPE_REGULAR, 2);
                        }
                }
                /*
                if( stringp(attack_skill) ) {
                        set_temp("action_flag", 1, me);
                        SKILL_D(attack_skill)->do_interlink(me, victim);
                        set_temp("action_flag", 0, me);
                }
                */

        // Else, we just start guarding.
        }else if( !query_temp("guarding", me)){
                set_temp("guarding", 1, me);
                message_combatd( guard_msg[random(sizeof(guard_msg))], me, victim, "");
                return;
        } else return;
}

//  auto_fight()
//
//  This function is to start an automatically fight. Currently this is
//  used in "aggressive", "vendetta", "hatred", "berserk" fight.
//
void auto_fight(object me, object obj, string type)
{
        // Don't let NPC autofight NPC.
        if( !playerp(me) && !playerp(obj) ) return;

        if( query_temp("owner", me) == obj ||
            obj->quety_temp("owner") == me )
                return;

        // Because most of the cases that we cannot start a fight cannot be checked
        // before we really call the kill_ob(), so we just make sure we have no
        // aggressive callout wating here.
        if( query_temp("looking_for_trouble", me))return ;
        set_temp("looking_for_trouble", 1, me);

        // This call_out gives victim a chance to slip trough the fierce guys.
        call_out("start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
        int shen, sb_shen;

        if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?
        set_temp("looking_for_trouble", 0, me);

        if( me->is_fighting(obj)                // Are we busy fighting?
        ||  !living(me)                         // Are we capable for a fight?
        ||  environment(me)!=environment(obj)   // Are we still in the same room?
         || query("no_fight", environment(me))//Areweinapeaceroom?
        )   return;

        message_vision("$N��һ������������ɨ�����ڳ���ÿһ���ˡ�\n", me);
        if( (shen < -50000 || sb_shen>100000) && me->query_per()>random(obj->query_per())*2 &&  !wizardp(obj) ) {
                message_vision("$N����$n�ȵ���" + RANK_D->query_self_rude(me)
                        + "����ʵ�ںܲ�˳�ۣ�ȥ���ɡ�\n", me, obj);
                me->want_kill(obj);
                me->kill_ob(obj);
                obj->fight_ob(me);
        } else {
                message_vision("$N����$n�ȵ���ι��" + RANK_D->query_rude(obj)
                        + "��" + RANK_D->query_self_rude(me) + "�������˴�ܣ����������ְɣ�\n",me, obj);
                me->fight_ob(obj);
                obj->fight_ob(me);
        }
}

void start_hatred(object me, object obj)
{
        if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?
        set_temp("looking_for_trouble", 0, me);

        if( me->is_fighting(obj)                // Are we busy fighting?
        ||  !living(me)                         // Are we capable for a fight?
        ||  environment(me)!=environment(obj)   // Are we still in the same room?
         || (query("no_fight", environment(me))//Areweinapeaceroom?
        &&  !me->is_demogorgon() && !obj->is_demogorgon())
        )   return;

        if( query_temp("owner", me) == query("id", obj) ||
            query_temp("owner", obj) == query("id", me) )
                return;

        // We found our hatred!Charge!
        message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
        me->want_kill(obj);
        me->kill_ob(obj);
        obj->fight_ob(me);

        if( !playerp(me) && me->is_busy() && !intp(me->query_busy()) )
                me->interrupt_me(me);
}

void start_vendetta(object me, object obj)
{
        if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?
        set_temp("looking_for_trouble", 0, me);

        if( me->is_fighting(obj)                // Are we busy fighting?
        ||  !living(me)                         // Are we capable for a fight?
        ||  environment(me)!=environment(obj)   // Are we still in the same room?
         || query("no_fight", environment(me))//Areweinapeaceroom?
        )   return;

        // We found our vendetta opponent!Charge!
        me->want_kill(obj);
        me->kill_ob(obj);
        obj->fight_ob(me);
}

void start_aggressive(object me, object obj)
{
        if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?
        set_temp("looking_for_trouble", 0, me);

        if( me->is_fighting(obj)                // Are we busy fighting?
        ||  !living(me)                         // Are we capable for a fight?
        ||  environment(me)!=environment(obj)   // Are we still in the same room?
         || query("no_fight", environment(me))//Areweinapeaceroom?
        )   return;

        // We got a nice victim!Kill him/her/it!!!
        me->want_kill(obj);
        me->kill_ob(obj);
        obj->fight_ob(me);
}

int player_escape(object killer, object ob)
{
        object iob;
        string msg;

        if( !objectp(ob) ) return 0;
        if( !playerp(ob) ) return 0;

        if( query("combat/which_day", ob) == time()/86400 &&
            query("total_count", ob)>0 )
                return 0;

        if( !killer ) killer = ob->query_defeated_by();
        if( !killer)killer=query("query_last_damage", ob);
        if( !killer || !playerp(killer) ||
            !killer->is_want_kill(query("id", ob)) )
                return 0;

        if( query("no_newbie", ob) ||
            query("combat/WPK", ob) ||
            (query("age", ob) >= 20 &&
            query("combat_exp", ob) >= 20000000) )
                return 0;

        switch( random(7) )
        {
        case 0:
                msg = "ͻȻֻ������һ����̾��һ�����ᰴ����$N���һ��������"
                      "���˼����ֻ��̧��һ�񡣴�æ֮��ֻ�¶��ֹ�����������"
                      "���мܣ���æ���Ծ����ȴ�����˲���׷����ֻ��һ������"
                      "��$n��ת��ƮȻ��ȥ��������Ȼ��\n";
                break;

        case 1:
                msg = "$N��$n���ڵأ���������һ��Ц����δ���£�ֻ��������"
                      "��һ������Ȼ���Ʒ�Ϯ�壬$N�ٸк���������������Ϣ����"
                      "æ�м�æ�˺󣬴������ȽŸ���ȴ��$n������Ӱ���١�\n";
                break;

        case 2:
                msg = "һ�˺�Ȼ�������ȵ��������д�������������޴�������"
                      "��֮�������ߣ���˵��һ�ƻ�����$N�����мܣ�һ��֮�¼�"
                      "����Ѫ��ֻ��������������$n����Ц������ת����ȥ��$N��"
                      "��֮�£���Ȼ˵����һ�仰����\n";
                break;

        case 3:
                msg = "ͻȻһ�˺ȵ�������������ֻ��һ����Ӱ�ӵ�������һ�Ž�"
                      "$N���˸���ͷ����������$n�������$N����������������δ"
                      "����������������������ȥ�ɣ���$N������������ס��Ϣ"
                      "���������Ŀ�������ȥ�ˡ�\n";
                break;

        case 4:
                msg = "$N��ǰһ������Ȼ������ǰ�Ѷ������ˣ�һ��һ�ݣ�һϲһ"
                      "ŭ�����ɰ�����񼡣һ����������һ��ͭ�ƣ�Ц��������λ" +
                      RANK_D->quert_respect(killer)+ "�����淣��ͭ�������¿�"
                      "�ã���$N���˴��һ������ֻ��һ�����ﻹ�Ҵ��仰��"
                      "���������俴�˹�����Ŀ����磬$NڨڨЦ��������Ŀ����"
                      "�˴���$n��ң��ȥ��\n";

        case 5:
                msg = "ǡ�ڴ�ʱ������һ����·����ֻ����΢һ�ü���ȵ�����أ"
                      "��" + RANK_D->query_rude(killer)+ "��������������$N��"
                      "ŭ���������Ǻ��ˣ�������ţ������ߴ�ŭ��һ�����䣬$N"
                      "����ֻ��һ�񣬡����ࡱһ��˫���������У����а�ߡ���"
                      "��ɭȻ�������������͵�ľ������Ҳ�����в�����������"
                      "������ʱ$N��Ϣ������䳡�滰Ҳ˵��������ֻ���ۿ�$n"
                      "����ľ����������ȥ��\n";
                break;

        default:
                msg = "������������һ��Ц��һ�˵��������֣��벻��������ʮ"
                      "�겻����������Щ���ָ���ȴ��Խ��Խ�������ˣ�����һ��"
                      "���������ǣ��������Ʒ����������ڣ����޾�ͷ����$N��"
                      "�ô��乶��£������ķ�ȴ��һ�ˣ�ת��ͷ�������Ǵ��"
                      "һ������$nҲ�����ˡ�\n";
                break;
        }

        if( (environment(killer) == environment(ob)) &&
            killer->is_fighting(ob) ) {
                msg = replace_string(msg, "$n", ob->name());
                message_sort(msg, killer);
        } else {
                msg = "����һ����·��������" + ob->name() + "�ε��ڵأ�̾��"
                      "����������������ˡ�\n";
                message("vision", msg, environment(ob));
        }

        /*
        foreach (iob in all_inventory(ob))
                if( !query("money_id", iob) &&
                    !query("equipped", iob) )
                        iob->move(environment(ob));
        */

        // ��ʼ����ҵ�״̬
        ob->clear_condition();
        ob->remove_killer(killer);
        killer->remove_killer(ob);

        // ͨ����������
        if( !killer->query_condition("killer") ) {
                msg = "��˵�ٸ����º������飬������������" +
                             killer->name(1) + "��";
                killer->apply_condition("killer", 500);
        } else {
                msg = "��˵�ٸ��ӽ�׽���۴����˵ı�ͽ" +
                             killer->name(1) + "��";
                killer->apply_condition("killer", 800 +
                        (int)killer->query_condition("killer"));
        }
        CHANNEL_D->do_channel(this_object(), "rumor", msg);

        ob->move("/d/xiakedao/shiroom24");
        set("startroom", "/d/xiakedao/shiroom24", ob);
        ob->revive();
        set("eff_qi",query("max_qi",  ob), ob);
        set("eff_jing",query("max_jing",  ob), ob);
        set("qi", 0, ob);
        set("jing", 0, ob);

        if( intp(ob->query_busy()) )
                ob->start_busy(30);

        tell_object(ob, "������������������λ�������ھ���������\n"
                    HIG "�����������㣺" + RANK_D->query_respect(ob) +
                        "����Ҫ���뵺��������˵һ��(ask long about �뵺)��\n" NOR);
        return 1;
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
        object *target;
        int i;

        switch( event ) {
        case "dead":
                message_vision(NOR "\n$N���ڵ��������˼��£���һ�죬�����������"
                               HIR "��Ѫ" NOR "�����ˣ�\n\n" NOR, ob);
                if( environment(ob) && playerp(environment(ob)) && living(environment(ob)) )
                        tell_object(environment(ob),NOR "\n" + ob->name() + "�����˼��£���һ�죬�����������"
                               HIR "��Ѫ" NOR "�����ˣ�\n\n" NOR);
                break;
        case "unconcious":
                message_vision("\n$N����һ�����ȣ����ڵ���һ��Ҳ�����ˡ�\n\n", ob);
                player_escape(0, ob);
                break;
        case "revive":
                message_vision("\n$N���������۾��������˹�����\n\n", ob);
                break;
        }
}

void winner_reward(object winner, object victim)
{
        object owner;
        int temp;
        int td;
        mapping today;

        owner=query_temp("owner", winner);
        if( objectp(owner) )
                winner = owner;

        winner->defeated_enemy(victim);

        if( !playerp(winner) || wizardp(victim) && 0 )
                return;

        if( !winner->is_want_kill(query("id", victim)) )
                // only if I want kill ob, I will record it.
                return;

        addn("combat/DPS", 1, winner);
        if( victim->is_not_bad())  addn("combat/DPS_NOTBAD", 1, winner);
        if( victim->is_not_good()) addn("combat/DPS_NOTGOOD", 1, winner);
        if( victim->is_bad())      addn("combat/DPS_BAD", 1, winner);
        if( victim->is_good())     addn("combat/DPS_GOOD", 1, winner);

        if( victim->query_condition("killer") )
                return;

        log_file("static/killrecord",
                 sprintf("%s %s defeat %s\n",
                         log_time(), log_id(winner), log_id(victim)));

        td = time() / 86400;
        today=query("combat/today", winner);
        if( !mapp(today) || today["which_day"] != td ) {
                today = ([ "which_day" : td,
                           "total_count" : 1,
                           query("id", victim):1,]);
        } else {
                // count how many times that winner hit the victim to unconcious
                temp=++today[query("id", victim)];
                if( query("newbie", victim)){
                        today[query("id", victim)] = temp + 1;
                        temp = today[query("id", victim)];
                }

                if( temp == query("pk_perman") ) {
                        // reach limit
                        tell_object(winner, BLINK HIR "\n�������Ѿ�����" +
                                    victim->name() + chinese_number(temp) +
                                    "���ˣ�������"
                                    "��ɣ������鷳��Ҫ�������ˡ�\n" NOR);
                } else if( temp > query("pk_perman") )
                        // too many times
                        set("combat/need_punish", "���˱���̫�����������д���", winner);

                // count how many users that winner hit to unconcious
                temp = ++today["total_count"];
                if( query("newbie", victim)){
                        today["total_count"] = temp + 5;
                        temp = today["total_count"];
                }

                if( temp == query("pk_perday") ) {
                        // reach limit
                        tell_object(winner, BLINK HIR "\n�������Ѿ�����" +
                                    chinese_number(temp) + "������ˣ�������"
                                    "��ɣ������鷳��Ҫ�������ˡ�\n" NOR);
                } else if( temp > query("pk_perday") )
                        // too many users
                        set("combat/need_punish", "ɥ��������������¾�����޿�ˡ��", winner);
        }
        set("combat/today", today, winner);
}

void family_kill(object killer, object victim)
{
        // ����Ϊ���ɹ�������
        if( !objectp(killer) || !playerp(killer) ||
            !objectp(victim) ||
            !stringp(query("family/family_name", killer)) )
                return;

        if( query("family/family_name", killer) !=
            query("family/family_name", victim) )
                return;

        // quest ����
        if( stringp(query("quest/id", killer)) &&
            query("quest/id", killer) == query("id", victim) )
                return;

        // free ����
        if( !playerp(victim) && query_temp("quest_ob", victim) )
                return;

        // ultra ����
        if( !playerp(victim) && stringp(query_temp("quester", victim)) &&
            query_temp("quester", victim) == query("id", killer) )
                return;

        // ultra ����
        if( !playerp(victim) && (query("quest_dg", killer) ||
            query("quest_hs", killer) || query("quest_sn", killer) ||
            query("quest_kh", killer)) )
                return;

        if( playerp(victim) ) {
                addn("family/gongji", -500, killer);
                tell_object(killer, sprintf("������к�ͬ�ŵ��ӣ�ʦ�Ź����½� %d �㡣\n", 500));
        } else {
                if( killer->is_apprentice_of(victim) ) {
                        addn("family/gongji", -1000, killer);
                        tell_object(killer,sprintf("������ʦ�������Ϊ��ʦ�Ź����½� %d �㡣\n", 1000));
                }
                else if( query("family/generation", killer)>query("family/generation", victim)){
                        addn("family/gongji", -600, killer);
                        tell_object(killer,sprintf("������к�ͬ���𳤣�ʦ�Ź����½� %d �㡣\n", 600));
                }
                else {
                        addn("family/gongji", -300, killer);
                        tell_object(killer,sprintf("������к�ͬ�ţ�ʦ�Ź����½� %d �㡣\n", 300));
                }
        }
        if( query("family/gongji", killer)<0 )
                delete("family/gongji", killer);
}

void killer_reward(object killer, object victim)
{
        object owner, charm;
        string vmark;
        string msg = "Ī�����������";
        string follow_msg = 0;
        object weapon;
        mapping actions, quest, bonus;
        int shen_delta,exp_damage;
        mixed exp_lost;
        mapping ks, vs, kcombat;
        int flag, no_loss = 0;
        int exp, pot, score;
        int kill_bonus;

        if( !objectp(victim) )
                return;

        if( objectp(killer) ) {
                owner=query_temp("owner", killer);
                if( objectp(owner) )
                        killer = owner;
        }

        // This while is only to enable "break"
        vs = victim->query_entire_dbase();
        while( 1 )
        {
                if( !objectp(killer) )
                        break;

                // call the killer's override function
                killer->killed_enemy(victim);

                if( !objectp(killer) || !playerp(killer) )
                        break;

                // assure the killer's dbase
                ks = killer->query_entire_dbase();
                if( !mapp(kcombat = ks["combat"]) ) {
                        kcombat = ([ ]);
                        ks["combat"] = kcombat;
                }

                if( ks["combat_exp"]/2 < vs["combat_exp"] ) {
                        if( ks["combat_exp"] >= 100000 &&
                            ks["combat_exp"] >= vs["combat_exp"] * 2 / 3 ) {
                                // adjust experience
                                if( !ks["experience"] )
                                        ks["experience"] = 0;
                                killer->improve_experience(1 + random(5));
                        }

                        // adjust shen
                        shen_delta = -vs["shen"] / 2;
                        if( shen_delta > 100 ) {
                                // ������У����õ�����
                                shen_delta = (shen_delta - 100) / 3 + 100;

                                if( shen_delta > 200 )
                                        shen_delta = (shen_delta - 200) / 3 + 200;

                                if( shen_delta > 300 )
                                        shen_delta = (shen_delta - 300) / 3 + 300;
                        } else
                        if( shen_delta < -100 ) {
                                // ������У����õĸ���
                                shen_delta = (shen_delta + 100) / 3 - 100;

                                if( shen_delta < -200 )
                                        shen_delta = (shen_delta + 200) / 3 - 200;

                                if( shen_delta < -300 )
                                        shen_delta = (shen_delta + 300) / 3 - 300;
                        }

                        ks["shen"] += shen_delta;
                }

                // weapon get the bonus
                if( weapon=query_temp("weapon", killer) ||
                    weapon=query_temp("armor/finger", killer) ||
                    weapon=query_temp("armor/hands", killer) )
                        weapon->killer_reward(killer, victim);

                if( weapon=query_temp("secondary_weapon", killer) )
                        weapon->killer_reward(killer, victim);

                if( weapon=query_temp("handing", killer) )
                        weapon->killer_reward(killer, victim);

                // record the user's killing
                if( playerp(victim) ) {
                        if( !intp(kcombat["PKS"]) )
                                kcombat["PKS"] = 1;
                        else
                                kcombat["PKS"]++;

                        //killer->set("pktime", (int)killer->query("mud_age"));
                        set("combat/pktime", time(), killer);

                        // do family action
                        FAMILY_D->family_kill(killer, victim);

                        // do league action
                        LEAGUE_D->league_kill(killer, victim);

                        // do bunch action
                        BUNCH_D->bunch_kill(killer, victim);

                        //if( victim->query_condition("killer") ) {
                        if( query("pk_score", victim)>0){
                                // ��������
                                if( query("combat/today/"+query("id", killer), victim) )
                                        addn("pk_score", -1, victim);
                                else {
                                        kill_bonus=query("combat_exp", victim)/100;
                                        if( kill_bonus > 1000000 ) kill_bonus = 1000000;
                                        addn("combat_exp", kill_bonus, killer);
                                        tell_object(killer, "������" + kill_bonus + "�㾭�齱����\n");
                                }

                                set("combat/punish", time(), victim);
                                follow_msg = "��˵ɱ������" + victim->name(1) +
                                             "��" + killer->name(1) + "��" +
                                             environment(victim)->short() + HIM
                                             "�͵������ˡ�";
                                break;
                        }

                        if( playerp(killer) && killer->in_array() && killer->query_array_status() ) {
                                follow_msg = sprintf("%s(%s)��%s(%s)����ġ�%s������������\n",
                                                victim->name(1),
                                                capitalize(query("id", victim)),
                                                killer->query_array_master()->name(1),
                                                capitalize(query("id", killer->query_array_master())),
                                                killer->query_array_name());
                        }

                       if( playerp(killer) && killer->in_team() && objectp(killer->query_team_leader()) ) {
                                follow_msg = sprintf("%s(%s)��%s(%s)����Ķ�������������\n",
                                                victim->name(1),
                                                capitalize(query("id", victim)),
                                                killer->query_team_leader()->name(1),
                                                capitalize(query("id", killer->query_team_leader())));
                        }

                        if( !killer->is_want_kill(vs["id"]) )
                                break;

                        if( !intp(kcombat["WPK"]) )
                                kcombat["WPK"] = 1;
                        else
                                kcombat["WPK"]++;

                        if( !killer->query_condition("killer") ) {
                                follow_msg = "��˵�ٸ����º������飬����ɱ������" +
                                             killer->name(1) + "��";
                                killer->apply_condition("killer", 500);
                        } else {
                                follow_msg = "��˵�ٸ��ӽ�׽���۷��ذ��ı�ͽ" +
                                             killer->name(1) + "��";
                                killer->apply_condition("killer", 800 +
                                        (int)killer->query_condition("killer"));
                        }

                        addn("pk_score", 1, killer);
                        set("pk_score_time", time(), killer);
                        
                        HISTORY_D->add_history("PK_SCORE", query("id", killer), sprintf("ɱ����� %s(%s)������ %d���ȼ� %d�����ֵȼ� %d\n", 
                                query("name", victim), query("id", victim), query("age", killer), query("level", killer), query("level", victim)));     
                        // be killed
                        HISTORY_D->add_history("BK_SCORE", query("id", victim), sprintf("����� %s(%s)ɱ�������� %d���ȼ� %d�����ֵȼ� %d\n", 
                                query("name", killer), query("id", killer), query("age", victim), query("level", victim), query("level", killer))); 
                                   
                        // assure data of kcombat
                        if( !intp(kcombat["WPK_NOTBAD"]) ) kcombat["WPK_NOTBAD"] = 0;
                        if( !intp(kcombat["WPK_NOTGOOD"]) ) kcombat["WPK_NOTGOOD"] = 0;
                        if( !intp(kcombat["WPK_GOOD"]) ) kcombat["WPK_GOOD"] = 0;
                        if( !intp(kcombat["WPK_BAD"]) ) kcombat["WPK_BAD"] = 0;

                        // record the combat info.
                        if( victim->is_not_bad() )  kcombat["WPK_NOTBAD"]++;
                        if( victim->is_not_good() ) kcombat["WPK_NOTGOOD"]++;
                        if( victim->is_good() )     kcombat["WPK_GOOD"]++;
                        if( victim->is_bad() )      kcombat["WPK_BAD"]++;
                        break;
                } else {
                        if( mapp(query("drops", victim)) )
                                EQUIPMENT_D->killer_reward(killer,victim,query("drops", victim));

                        // ����
                }

                if( vs["can_speak"] )
                        if( !intp(kcombat["MKS"]) )
                                kcombat["MKS"] = 1;
                        else
                                kcombat["MKS"]++;

                family_kill(killer, victim);
                quest_kill(killer, victim);

                break;
        }

        // die penalty & message of victim
        if( playerp(victim) ) {
                // clear punish info.
                delete("combat/need_punish", victim);

                // remove vendetta
                map_delete(vs, "vendetta");

                // ��tianshi charm�Ҳ���ͨ����������ʧ
                if( objectp(charm = present("tianshi charm", victim)) /*&& !victim->query_condition("killer")*/ )
                {
                        set_temp("tianshi_charm", 1, victim);
                        no_loss = 1;
                }

                // �����ɱ�����Լ��ܵ�������������ʧ
                else
                if( objectp(killer) && playerp(killer) &&
                    (query("age", victim)<20 ||
                    query("combat_exp", victim)<20000000) &&
                    !query("no_newbie", victim) &&
                    !query("combat/WPK", victim) )
                        no_loss = 1;

                // �����ɱ����ɱ�����С��20�����С��2000����������ʧ
                else
                if( objectp(killer) && playerp(killer) &&
                    (query("age", killer)<20 ||
                    query("combat_exp", killer)<20000000) )
                        no_loss = 1;

                // clear all condition
                victim->clear_condition();

                if( !no_loss ) {
                        // adjust shen
                        vs["shen"] -= vs["shen"] / 10;
                        if( vs["max_neili"] >= 20 )
                                vs["max_neili"] -= 20;
                        else
                                vs["max_neili"] = 0;

                        // adjust combat exp.
                        if( !mapp(vs["combat"]) ) exp_damage = 1;
                        else exp_damage = vs["combat"]["WPK"];
                        if( exp_damage < 1 ) exp_damage = 1;
                        if( exp_damage > 5 ) exp_damage = 5;

                        // pk�����ͷ�
                        if( vs["pk_score"] > 3 )
                                exp_damage += 5;
                        else if( vs["pk_score"] >= 1 )
                                exp_damage += 2;

                        exp_lost = vs["combat_exp"] * exp_damage / 5000;
                        vs["combat_exp"] -= exp_lost;

                        if( killer )
                                addn("combat/WPKEXP", exp_lost, killer);
                        addn("combat/dieexp", exp_lost, victim);
                        set("combat/last_dieexp", exp_lost, victim);

                        // adjust weiwang
                        vs["weiwang"] -= vs["weiwang"] / 10;
                        // adjust score
                        vs["score"] -= vs["score"] / 10;


                        // lost half of potential
                        if( vs["potential"] > vs["learned_points"])
                                vs["potential"] += (vs["learned_points"] - vs["potential"]) / 100;

                        // lost half of experience
                        if( vs["experience"] > vs["learned_experience"] )
                                 vs["experience"] += (vs["learned_experience"] - vs["experience"]) / 100;

                        if( !query("death", victim))flag=100;//��������
                        else {
                                // ����ʵս�������������ܼ���
                                if( query("combat_exp", victim) >= 200000000)flag=20;
                                else if( query("combat_exp", victim) >= 80000000)flag=30;
                                else if( query("combat_exp", victim) >= 50000000)flag=40;
                                else if( query("combat_exp", victim) >= 30000000)flag=50;
                                else if( query("combat_exp", victim) >= 15000000)flag=55;
                                else if( query("combat_exp", victim) >= 8000000)flag=60;
                                else if( query("combat_exp", victim) >= 5000000)flag=65;
                                else                                               flag = 70;
                        }
                        if( random(100) < flag ) victim->skill_death_penalty();
                }

                if( objectp(charm) && no_loss )
                        destruct(charm);

                // generate message of die reason
                if( objectp(killer) && killer->is_character() ) {
                        msg = "��" + filter_color(killer->name(1));

                        if( query("race", killer) == "Ұ��"
                         || query("race", killer) == "����"
                         || query("race", killer) == "����"
                         || query("race", killer) == "����")msg+="ҧ����";
                        else if( query("race", killer) == "����")msg+="������";
                        else if( query("race", killer) == "����")msg+="������";
                        else {
                                if( query_temp("hand_flag", killer) )
                                        actions = query("second_actions", killer);
                                else
                                        actions = query("actions", killer);
                                switch (mapp(actions) ? actions["damage_type"] : "ɱ��") {
                                case "����":
                                case "����":
                                        msg+="������";
                                        break;
                                case "����":
                                        msg+="������";
                                        break;
                                case "����":
                                case "����":
                                        msg+="������";
                                        break;
                                case "����":
                                        msg+="������";
                                        break;
                                default:
                                        msg+="ɱ����";
                                }
                        }
                }

                if( stringp(query_temp("die_reason", victim)) )
                        msg=filter_color(query_temp("die_reason", victim));

                delete_temp("die_reason", victim);
                CHANNEL_D->channel_broadcast("combat",
                        sprintf("��˵%s" HIR + msg + "��", victim->name(1)));

                // show the follow msg after victim die
                if( follow_msg )
                        CHANNEL_D->channel_broadcast("rumor",
                                              follow_msg);

                set("combat/last_die", filter_color(msg), victim);
                if( objectp(killer) && playerp(killer) && playerp(victim) ) {
                        string cname;
                        object couple;

                        log_file("static/killrecord",
                                 sprintf("%s %s killed %s\n",
                                         log_time(),
                                         log_id(killer), log_id(victim)));

                        killer->remove_killer(victim);

                        // check sadly
                        cname=query("couple/couple_id", victim);
                        if( cname &&
                            query("gender", victim) == "Ů��" &&
                            query("combat_exp", victim) >= 970000 &&
                            objectp(couple = find_player(cname)) &&
                            couple != killer &&
                            query("couple/married", couple) <= 1 &&
                            query("couple/married", victim) <= 1){
                                addn("static/sadly", 1, couple);
                                tell_object(couple, "�������������" +
                                            killer->name(1) + "������" +
                                            "����е���һ������İ��ˡ�\n");
                        }
                }
        }

        if( stringp(vmark=query("vendetta_mark", victim)) && objectp(killer) )
                addn("vendetta/"+vmark, 1, killer);
}

// me hit victim with poison in ob
void hit_with_poison(object me, object victim, object ob)
{
        mapping p, ap;
        string msg;
        string poison_type;

        if( !mapp(p=query_temp("daub/poison", ob)) )
                return;

        if( !stringp(poison_type=query_temp("daub/poison_type", ob)) )
                return;

        if( !p["remain"] )
                return;

        // affect parameter
        ap = allocate_mapping(4);
        if( ob == me )
                ap["level"] = p["level"] * 9 / 10 + 1;
        else
                ap["level"] = p["level"] * 8 / 10 + 1;

        ap["id"]       = p["id"];
        ap["name"]     = p["name"];
        ap["duration"] = 1;

        if( p["remain"] > p["level"] ) {
                // decrase the remain poison
                p["remain"] -= p["level"];
        } else {
                // the poison has run out
                delete_temp("daub", ob);
        }

        msg = HIG "ͻȻ$n�������˵ĵط���һЩ����";
        if( p["id"] == query("id", victim)){
                if( !query_temp("has_announce/defense1", victim)){
                        set_temp("has_announce/defense1", 1, victim);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "��\n" NOR HIC "$nĬһ�˹�����Ц�������������" +
                               RANK_D->query_rude(me) + "����Ȼ������ǰ��Ū" +
                               RANK_D->query_self_rude(victim) +
                               "��ҩ�����Ǽ���������������ˣ���\n" NOR;
                } else
                        msg += "������$n��û�����⡣\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if( p["level"] < victim->query_skill("poison", 1) ) {
                if( !query_temp("has_announce/defense2", victim)){
                        set_temp("has_announce/defense2", 1, victim);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "��\n" NOR HIC "$n�������Σ���Ȼ��Ц����"
                               "������֮�飬Ҳ�Ź⻪����\n" NOR;
                } else
                        msg += "������$n��Ȼ��û�а����������ϡ�\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if( p["level"] < victim->query_skill("force") / 2 ) {
                if( !query_temp("has_announce/defense3", victim)){
                        set_temp("has_announce/defense3", 1, victim);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "��\n" NOR HIC "$n����һ������������Ц�������üһ��Ȼ" +
                               (ob == me ? "�����ϴ㶾" : "ʹ�ô㶾����") +
                               "������Щ�����ĵ��ֶ�Ҳ�ҵ�����ǰ��Ū����\n" NOR;
                } else
                        msg += "������$n�������ƺ����޴󰭡�\n" NOR;
                set_ahinfo(msg);
                return;
        }

        victim->affect_by(poison_type, ap);

        msg += "��������ж��ˡ�\n" NOR;
        if( p["level"] < victim->query_skill("force") ) {
                msg += HIG "$n������һ�˿�������Ŀ���أ����еĹ��ƶ�Ȼһ����\n" NOR;
                set_ahinfo(msg);
                return;
        }

        msg += HIR "$n�ƺ�һ�������ƶٻ�����������ʹ�ࡣ\n" NOR;
        if( !victim->is_busy() )
                victim->start_busy(1 + random(2));
        set_ahinfo(msg);
        return;
}

// me hit victim, but poison by victim in ob
void hit_poison(object me, object victim, object ob)
{
        mapping p, ap;
        string msg;
        string poison_type;

        if( !mapp(p=query_temp("daub/poison", ob)) )
                return;

        if( !stringp(poison_type=query_temp("daub/poison_type", ob)) )
                return;

        if( !p["remain"] )
                return;

        if( query_temp("armor/hands", me) )
                return;

        // affect parameter
        ap = allocate_mapping(4);
        ap["level"]    = p["level"] * 7 / 10 + 1;

        ap["id"]       = p["id"];
        ap["name"]     = p["name"];
        ap["duration"] = 1;

        if( p["remain"] > p["level"] ) {
                // decrase the remain poison
                p["remain"] -= p["level"];
        } else {
                // the poison has run out
                delete_temp("daub", ob);
        }

        msg = HIG "ͻȻ$N���û�����Щ����";
        if( p["id"] == query("id", me)){
                if( !query_temp("has_announce/defense1", me)){
                        set_temp("has_announce/defense1", 1, me);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "��\n" NOR HIC "$NĬһ�˹�����Ц�������������" +
                               RANK_D->query_rude(victim) + "����Ȼ������ǰ��Ū" +
                               RANK_D->query_self_rude(victim) +
                               "�Ķ�ҩ�������·��ϵĶ�ҩ�������ң���\n" NOR;
                } else
                        msg += "������$N��û�����⡣\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if( p["level"] < me->query_skill("poison", 1) ) {
                if( !query_temp("has_announce/defense2", me)){
                        set_temp("has_announce/defense2", 1, me);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "��\n" NOR HIC "$N�������Σ���Ȼ��Ц����������֮�飬Ҳ"
                               "�Ź⻪�����������ϴ㶾�Ҿ������ˣ���\n" NOR;
                } else
                        msg += "������$N��Ȼ��û�а����������ϡ�\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if( p["level"] < me->query_skill("force") / 2 ) {
                if( !query_temp("has_announce/defense3", me)){
                        set_temp("has_announce/defense3", 1, me);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "��\n" NOR HIC "$N����һ������������Ц���������Ȼ��������"
                               "�㶾����Щ�����ĵ��ֶ�Ҳ�ҵ�����ǰ��Ū����\n" NOR;
                } else
                        msg += "������$N�������ƺ����޴󰭡�\n" NOR;
                set_ahinfo(msg);
                return;
        }

        me->affect_by(poison_type, ap);

        msg += "��������Щ���\n" NOR;
        if( p["level"] < me->query_skill("force") ) {
                msg += HIG "$N������һ�˿�������Ŀ���أ����еĹ��ƶ�Ȼһ����\n" NOR;
                set_ahinfo(msg);
                return;
        }

        msg += HIR "$N�Ų�һ�����ԣ����ƶٻ�����ɫ�ѿ�֮����\n" NOR;
        me->start_busy(1 + random(2));
        set_ahinfo(msg);
        return;
}

void clear_announce(object me)
{
        if( !objectp(me) )
                return;

        delete_temp("has_announce", me);
}

protected void quest_kill(object killer, object victim)
{
        mapping quest,b;
        int level,i,n,exp,pot,score,weiwang,mar,quest_count,all_quest;
        mixed special = 0;
        mixed money = 0;
        object ob,*all_killer,obj;
        object tongren;

        // ������NPC��������Ľ���
        // �����׷ɱ����
        if( !playerp(victim) && query("bunch_quest", victim)){
                quest=query("bunch_quest", victim);
                if( quest["type"] == "׷ɱ" &&
                    ((quest["bunch_type"] == "good" && good_bunch(killer) && query("shen", killer) >= 0) ||
                    (quest["bunch_type"] == "bad" && bad_bunch(killer) && query("shen", killer) <= 0)) &&
                    query("combat_exp", killer)<270000000){
                        exp = quest["bonus"];
                        exp += 120;
                        exp += random(exp/2);
                        pot = exp/(2 + random(2));
                        score = 25 + random(20);
                        weiwang = 25 + random(20);

                        b = ([ "exp" : exp,
                               "pot" : pot,
                               "score" : score,
                               "weiwang" : weiwang,
                               "prompt": "��׷ɱ" + victim->name() + HIG "�Ĺ����У���������"
                        ]);

                        GIFT_D->delay_bonus(killer, b);
                }
                return;
        }

        // ����ǲ����������
        if( query("bunch_quest", killer) &&
            query("bunch_quest", killer)["type"] == "�������" &&
            query("bunch_quest", killer)["ob"] == victim){
                quest=query("bunch_quest", killer);

                exp = quest["bonus"];
                exp += 120;
                exp += random(exp/2);
                pot = exp/(2 + random(2));
                score = 25 + random(20);
                weiwang = 25 + random(20);

                b = ([ "exp" : exp,
                       "pot" : pot,
                       "score" : score,
                       "weiwang" : weiwang,
                       "prompt": "�ڲ�����������" + victim->name() + HIG "�Ĺ����У���������"
                ]);

                GIFT_D->delay_bonus(killer, b);

                delete("bunch_quest", killer);
                addn_temp("finish_bunch_times", 1, killer);
                return;
        }

        // �������������Ľ���
        if( !playerp(victim) && query("my_type", victim)){
                /*
                if( objectp(victim->query_defeated_by()) &&
                    playerp(victim->query_defeated_by()) )
                    killer = victim->query_defeated_by();
                */
                switch(query("my_type", victim) )
                {
                case "���":
                        GROUP_QUEST_D->be_killed(1);
                        GROUP_QUEST_D->add_killer(killer);
                        exp=query("bonus", victim);
                        pot = exp;
                        score = random(exp);
                        weiwang = exp + random(exp);
                        mar = random(exp/2);
                        if( GROUP_QUEST_D->query_drop() < 2 && random(10) == 1 ) {
                                GROUP_QUEST_D->add_drop(1);
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "��~~һ������$N" HIR "����һ��������$n" HIR
                                               "�Ͻ�����������\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "��õ���" + tongren->name() + BLINK + HIG "��\n" NOR);
                                tongren->move(killer, 1);
                        }
                        GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                 "weiwang" : weiwang, "score" : score ]), 1);
                        if( GROUP_QUEST_D->query_enemy() == 0 ) {
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "��~~һ������$N" HIR "����һ��������$n" HIR
                                               "�Ͻ�����������\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "��õ���" + tongren->name() + BLINK + HIG "��\n" NOR);
                                tongren->move(killer, 1);

                                all_killer = GROUP_QUEST_D->query_killer();
                                n = sizeof(all_killer);
                                exp = 2000+20*n;
                                pot = exp;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if( !objectp(ob) || !playerp(ob) )
                                                continue;

                                        tell_object(ob, HIW "�������ֵĵ��˶��������ˣ�������Ҳ������ս����" +
                                                            "���������Ҳһ�����ʤ����ʵ��\n" NOR);
                                        GIFT_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                             "weiwang" : weiwang, "score" : score ]), 1);
                                }
                        }
                        break;
                case "����":
                        GROUP_QUEST_D->be_killed(1);
                        if( query("����", victim) == query("family/family_name", killer)){
                                GROUP_QUEST_D->add_killer(killer);
                                exp=query("bonus", victim);
                                pot = exp;
                                score = random(exp);
                                weiwang = exp + random(exp);
                                mar = random(exp/2);
                        if( GROUP_QUEST_D->query_drop() < 2 && random(10) == 1 ) {
                                GROUP_QUEST_D->add_drop(1);
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "��~~һ������$N" HIR "����һ��������$n" HIR
                                               "�Ͻ�����������\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "��õ���" + tongren->name() + BLINK + HIG "��\n" NOR);
                                tongren->move(killer, 1);
                                }
                                GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                         "gongxian" : weiwang, "score" : score, "weiwang" : weiwang ]), 1);
                        }
                        if( GROUP_QUEST_D->query_enemy() == 0 ) {
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "��~~һ������$N" HIR "����һ��������$n" HIR
                                               "�Ͻ�����������\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "��õ���" + tongren->name() + BLINK + HIG "��\n" NOR);
                                tongren->move(killer, 1);
                                all_killer = GROUP_QUEST_D->query_killer();
                                n = sizeof(all_killer);
                                exp = 2000+20*n;
                                pot = exp;
                                score = 1000;
                                weiwang = 30000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if( !objectp(ob) || !playerp(ob))
                                                continue;

                                        tell_object(ob, HIW "�������ֵĵ��˶��������ˣ�������Ҳ������ս����" +
                                                            "���������Ҳһ�����ʤ����ʵ��\n" NOR);
                                        GIFT_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                             "gongxian" : weiwang, "score" : score, "weiwang" : weiwang ]), 1);
                                }
                        }
                        break;
                case "����":
                        GROUP_QUEST_D->be_killed(1);
                        if( query("����", victim) == query("bunch/bunch_name", killer)){
                                GROUP_QUEST_D->add_killer(killer);
                                exp=query("bonus", victim);
                                pot = exp;
                                score = random(exp);
                                weiwang = exp + random(exp);
                                mar = random(exp/2);
                                if( GROUP_QUEST_D->query_drop() < 2 && random(10) == 1 ) {
                                GROUP_QUEST_D->add_drop(1);
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "��~~һ������$N" HIR "����һ��������$n" HIR
                                               "�Ͻ�����������\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "��õ���" + tongren->name() + BLINK + HIG "��\n" NOR);
                                tongren->move(killer, 1);
                                }
                                GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                   "weiwang" : weiwang, "score" : score ]), 1);
                        }
                        if( GROUP_QUEST_D->query_enemy() == 0 ) {
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "��~~һ������$N" HIR "����һ��������$n" HIR
                                               "�Ͻ�����������\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "��õ���" + tongren->name() + BLINK + HIG "��\n" NOR);
                                tongren->move(killer, 1);
                                all_killer = GROUP_QUEST_D->query_killer();
                                n = sizeof(all_killer);
                                exp = 2000+20*n;
                                pot = exp;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if( !objectp(ob) || !playerp(ob) )
                                                continue;

                                        tell_object(ob, HIW "�������ֵĵ��˶��������ˣ�������Ҳ������ս����" +
                                                            "���������Ҳһ�����ʤ����ʵ��\n" NOR);
                                        GIFT_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                             "weiwang" : weiwang, "score" : score ]), 1);
                                }
                        }
                        break;
                }
                return;
        }

        // ��������ʦ����Ľ���
        if( mapp(quest=query("quest_kh", killer)) && quest["desc"] == "��"){//����̫��
                if( (quest["name"] == "����" && query("gender", victim) == "����") ||
                    (quest["name"] == "Ů��" && query("gender", victim) == "Ů��") ||
                    (quest["type"] == "�ص�" && (domain_file(base_name(victim)) == quest["dir"] ||
                    (stringp(query("startroom", victim)) && (domain_file(query("startroom", victim)) == quest["dir"])) ||
                     base_dir(victim) == quest["dir1"])) ) {
                        if( (quest["time"]-time()) < 0 ) {
                                delete("quest_kh", killer);
                                return ;
                        }
                        else if( query("race", victim) == "Ұ��")return ;
                        else {
                                level = (quest["level"]+1)*(70+random(20));
                                exp = level;
                                pot = exp/(2+random(2));
                                score = random(exp/20);
                                weiwang = random(exp/15);
                                if( query("questkh_times", killer)+1>200 )
                                        mar=exp/5+random(query("questkh_times", killer));
                                else mar = 20 + random(20);
                                if( mar > 1000 ) mar = 1000;

                                GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                         "weiwang" : weiwang, "score" : score ]), 1);

                                return ;
                        }
                }
        }

        if( mapp(quest=query("quest_dg", killer))){//�������
                if( quest["type"] == "ɱ" && victim->name(1) == quest["name"] ) {
                        if( (i=query("questdg_times", killer))<8 )
                                i = 15-i;
                        else
                                i = 1;
                        level = quest["level"]+1;
                        exp = level*105 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        /*
                        if( level == 9 )
                                exp+=query("questdg_times", killer);
                        if( level == 9)
                                pot = exp*(2+random(2));
                        else
                        */
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);

                        if( query("questdg_times", killer)+1>200 )
                                mar=exp/5+random(query("questdg_times", killer));
                        else mar = 20 + random(20);
                        if( mar > 1000 ) mar = 1000;

                        GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                 "weiwang" : weiwang, "score" : score ]), 1);

                        addn("questdg_times", 1, killer);

                        quest_count=query("questdg_times", killer)%500;
                        if( quest_count == 50 )
                                special = 1;
                        else if( quest_count == 100)
                                special = "/clone/gift/puti-zi";
                        else if( quest_count == 150)
                                money = 1;
                        else if( quest_count == 200)
                                money = 1;
                        else if( quest_count == 250)
                                money = 1;
                        else if( quest_count == 300)
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 350)
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 400)
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 450)
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 0)
                                special = "/clone/gift/jiuzhuan";

                        if( special ) GIFT_D->special_bonus(victim, killer, special);
                        if( money ) QUEST_D->money_bonus(victim, killer, money);

                        addn("total_hatred", -5, killer);
                        if( query("total_hatred", killer) < 0 ) set("total_hatred", 0, killer);
                        delete("quest_dg", killer);

#ifdef DB_SAVE
                        if( MEMBER_D->is_valid_member(query("id", killer))){
                                if( query("special_skill/sophistry", killer)){
                                        if( query("questdg_times", killer) >= 5000 )
                                                set("questdg_times", 0, killer);
                                } else {
                                        if( query("questdg_times", killer) >= 2000 )
                                                set("questdg_times", 0, killer);
                                }
                        } else {
#endif
                                if( query("questdg_times", killer) >= 1000 )
                                        set("questdg_times", 0, killer);
#ifdef DB_SAVE
                        }
#endif
                        all_quest=query("all_quest_dg", killer);
                        if( !all_quest ) all_quest = 0;
                        all_quest += 1;
                        if( all_quest == 1000 ) {
                                obj = new("/clone/gift/xuanhuang");
                                tell_object(killer,"�������Ѿ��ۼ������һǧ�����������õ���һ��" +
                                                query("name", obj)+"��Ϊ����\n");
                                if( !obj->move(killer) )
                                        obj->move(environment(killer));
                                set("all_quest_dg", 0, killer);
                        } else
                                set("all_quest_dg", all_quest, killer);
                        return ;
                }
        }

        if( mapp(quest=query("quest_hs", killer))){//����
                if( quest["type"]=="ɱ"&&quest["name"]==victim->name(1) ) {
                        tell_object(killer,"��ϲ�㣡����Ϊ��������һ����\n");
                        if( (i=query("quesths_times", killer))<15 )
                                i = 15-i;
                        else
                                i = 1;
                        level = quest["level"]+1;
                        exp = level*80 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if( level > 4 && i > 5 )
                                exp /= 2;
                        if( level == 9 )
                                exp+=query("quesths_times", killer);
                        /*
                        if( level == 9 )
                                pot = exp*(2+random(2));
                        else
                        */
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);
                        if( query("quesths_times", killer)+1>200 )
                                mar=exp/5+random(query("quesths_times", killer));
                        else mar = 20 + random(20);
                        if( mar > 1000 ) mar = 1000;

                        GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                 "weiwang" : weiwang, "score" : score ]), 1);

                        addn("quesths_times", 1, killer);
                        quest_count=query("quesths_times", killer)%500;
                        if( quest_count == 50)
                                special = 1;
                        else if( quest_count == 100 )
                                special = "/clone/gift/puti-zi";
                        else if( quest_count == 150 )
                                money = 1;
                        else if( quest_count == 200 )
                                money = 1;
                        else if( quest_count == 250 )
                                money = 1;
                        else if( quest_count == 300 )
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 350 )
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 400 )
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 450 )
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 0 )
                                special = "/clone/gift/jiuzhuan";

                        if( special ) GIFT_D->special_bonus(victim, killer, special);
                        if( money ) QUEST_D->money_bonus(victim, killer, money);

                        addn("total_hatred", -5, killer);
                        if( query("total_hatred", killer) < 0 ) set("total_hatred", 0, killer);
                        delete("quest_hs", killer);
                        set_temp("hs_giveup", 0, killer);

#ifdef DB_SAVE
                        if( MEMBER_D->is_valid_member(query("id", killer))){
                                if( query("special_skill/sophistry", killer)){
                                        if( query("quesths_times", killer) >= 5000 )
                                                set("quesths_times", 0, killer);
                                } else {
                                        if( query("quesths_times", killer) >= 2000 )
                                                set("quesths_times", 0, killer);
                                }
                        } else {
#endif
                                if( query("quesths_times", killer) >= 1000 )
                                        set("quesths_times", 0, killer);
#ifdef DB_SAVE
                        }
#endif

                        all_quest = (int)query("all_quest_hs", killer);
                        if( !all_quest ) all_quest = 0;
                        all_quest += 1;
                        if( all_quest == 1000 ) {
                                obj = new("/clone/gift/xuanhuang");
                                tell_object(killer,"�������Ѿ��ۼ������һǧ�����������õ���һ��" +
                                                query("name", obj)+"��Ϊ����\n");
                                if( !obj->move(killer) )
                                        obj->move(environment(killer));
                                set("all_quest_hs", 0, killer);
                        } else
                                set("all_quest_hs", all_quest, killer);
                        return ;
                }
        }

        if( mapp(quest=query("quest_sn", killer))){//�Ϻ�����
                if( quest["type"]=="ɱ"&&quest["name"]==victim->name(1) ) {
                        tell_object(killer,"��ϲ�㣡����Ϊ�Ϻ���������һ����\n");
                        if( (i=query("questsn_times", killer))<15 )
                                i = 15-i;
                        else i = 1;
                        level = quest["level"]+1;
                        exp = level*80 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if( level > 4 && i > 5 )
                                exp /= 2;
                        if( level == 9 )
                                exp+=query("questsn_times", killer);
                        /*
                        if( level == 9 )
                                pot = exp*(2+random(2));
                        else
                        */
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);
                        if( query("questsn_times", killer)+1>200 )
                                mar=exp/5+random(query("questsn_times", killer));
                        else mar = 20 + random(20);
                        if( mar > 1000 ) mar = 1000;

                        GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                 "weiwang" : weiwang, "score" : score ]), 1);

                        addn("questsn_times", 1, killer);
                        quest_count=query("questsn_times", killer)%500;
                        if( quest_count == 50 )
                                special = 1;
                        else if( quest_count == 100 )
                                special = "/clone/gift/puti-zi";
                        else if( quest_count == 150 )
                                money = 1;
                        else if( quest_count == 200 )
                                money = 1;
                        else if( quest_count == 250 )
                                money = 1;
                        else if( quest_count == 300 )
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 350 )
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 400 )
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 450 )
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 0 )
                                special = "/clone/gift/jiuzhuan";

                        if( special ) GIFT_D->special_bonus(victim, killer, special);
                        if( money ) QUEST_D->money_bonus(victim, killer, money);

                        addn("total_hatred", -5, killer);
                        if( query("total_hatred", killer) < 0 ) set("total_hatred", 0, killer);
                        delete("quest_sn", killer);
                        set_temp("sn_giveup", 0, killer);

#ifdef DB_SAVE
                        if( MEMBER_D->is_valid_member(query("id", killer))){
                                if( query("special_skill/sophistry", killer)){
                                        if( query("questsn_times", killer) >= 5000 )
                                                set("questsn_times", 0, killer);
                                } else {
                                        if( query("questsn_times", killer) >= 2000 )
                                                set("questsn_times", 0, killer);
                                }
                        } else {
#endif
                                if( query("questsn_times", killer) >= 1000 )
                                        set("questsn_times", 0, killer);
#ifdef DB_SAVE
                        }
#endif

                        all_quest = (int)query("all_quest_sn", killer);
                        if( !all_quest ) all_quest = 0;
                        all_quest += 1;
                        if( all_quest == 1000 ) {
                                obj = new("/clone/gift/xuanhuang");
                                tell_object(killer,"�������Ѿ��ۼ������һǧ�����������õ���һ��" +
                                                query("name", obj)+"��Ϊ����\n");
                                if( !obj->move(killer) )
                                        obj->move(environment(killer));
                                set("all_quest_sn", 0, killer);
                        } else
                                set("all_quest_sn", all_quest, killer);
                        return ;
                }
        }
}
