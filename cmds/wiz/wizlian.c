// wizlian.c ��ʦר��
// Written by Doing Lu 1998/11/1

#include <globals.h>
#include <ansi.h>

inherit F_CLEAN_UP;

void        restore_condition(object me);
void        restore_origin(object me);

mapping attrib =([
        "qi"                 : "",
        "��"                : "qi",
        "eff_qi"        : "",
        "��Ч��"        : "eff_qi",
        "max_qi"        : "",
        "�����"        : "max_qi",
        "jing"                : "",
        "��"                : "jing",
        "eff_jing"        : "",
        "��Ч��"        : "eff_jing",
        "max_jing"        : "",
        "���"        : "max_jing",
        "food"                : "",
        "ʳ��"                : "food",
        "water"                : "",
        "��ˮ"                : "water",
        "neili"                : "",
        "����"                : "neili",
        "max_neili"        : "",
        "�������"        : "max_neili",
        "jingli"        : "",
        "����"                : "jingli",
        "max_jingli"        : "",
        "�����"        : "max_jingli",
        "per"           : "",
        "��ò"          :  "per",
        "kar"           : "",
        "��Ե"          :  "kar",
        "shen"                : "",
        "��"                : "shen",
        "age"           : "",
        "����"          : "age",
        "mud_age"        : "",
        "����"                : "mud_age",
        "str"                : "",
        "����"                : "str",
        "����"                : "str",
        "int"                : "",
        "����"                : "int",
        "����"                : "int",
        "con"                : "",
        "����"                : "con",
        "dex"                : "",
        "����"                : "dex",
        "MKS"                : "",        
        "PKS"                : "",
        "potential"        : "",
        "Ǳ��"                : "potential",
        "Ǳ��"                : "potential",
        "combat_exp"        : "",
        "exp"                : "combat_exp",
        "����"                : "combat_exp",
        "learned_points": "",
        "ѧϰ����"        : "learnd_points",
        "score"         : "",
        "��������"      : "score",
        "weiwang"       : "",
        "��������"      : "weiwang",
        "meili"         : "",
        "����"          : "meili",
        "���ɹ���"      : "family/gongji",
        "gongji"        : "family/gongji",
        "magic_points"  : "",
        "���"          : "magic_points",
        "experience"    : "",
        "ʵս���"      : "experience",
        "balance"       : "",
        "��Ǯ"          : "balance",
        "total_hatred"  : "",
        "����"          : "total_hatred",
]);

int main(object me, string arg)
{
        object ob;
        mapping learned;
        string pack, argn, argm;        // ����/�书  ����1  ����2:��ʱ����
        int argnum;                        // �����ĸ��� (��������)

        int i;
        string attrs;
        
        if (! SECURITY_D->valid_grant(me, "(apprentice)")) 
                    return 0; 

        // �ָ�״̬��������������
        if (! arg)
        {
                message_vision(HIW "$N�૵�����һ�����һ������������$N��\n\n" NOR, me);
                restore_condition(me);
                return 1;
        }

        // �ָ���ԭʼ���ݣ������书
        if (arg == "org")
        {
                message_vision(HIW "$N�૵�����һ�����һ������������$N��\n\n" NOR, me);
                restore_origin(me);
                return 1;
        }

        argnum = sscanf(arg, "%s %d %d", pack, argn, argm);

        if (argnum < 2)
        {
                // û��ָ������
                message_vision(HIW "$N�૵�����һ�����ʲôҲû������\n\n" NOR, me);
                return 1;
        }

        if (! undefinedp(attrs = attrib[pack]))
        {
                // �޸�����
                if (attrs == "") attrs = pack;
                message_vision(HIW "$N�૵���߶�������飬�����飬��·���ɿ����飡\n\n" NOR, me);
                set(attrs, argn, me);
                message_vision(HIY "���Ϻ�¡¡������һ�ᣬ$N�Ǻǵ�Ц������˵�����������顣\n\n" NOR, me);
                return 1;
        } else
        {
                // �޸��书
                message_vision(HIW "$N��ȼһ�ŷ��䣬�ȵ���̫���Ͼ�����������\n\n" NOR, me);
                
                if( !find_object(SKILL_D(pack))
                        && file_size(SKILL_D(pack)+".c") < 0 )
                {
                        message_vision(HIR "���Ϻ�¡¡������һ�ᣬ̫���Ͼ�ŭ�ȵ������ʲô����\n\n" NOR, me);
                        return 1;
                }

                if (argn >= 0)
                {
                        me->set_skill(pack, argn);
                        message_vision(HIY "һ����������������������$N�����ڡ�\n\n" NOR, me);
                } else
                {
                        message_vision(HIR "���Ϻ�¡¡������һ�ᣬ̫���Ͼ�ŭ�ȵ�����Ҫ������\n\n" NOR, me);
                }
                return 1;
        }
}

void restore_condition(object me)
{
        message_vision(HIY "$N���������ȣ�\n\n" NOR, me);
        // �ָ���
        set("qi",query("max_qi",  me), me);
        set("eff_qi",query("max_qi",  me), me);

        // �ָ���
        set("jing",query("max_jing",  me), me);
        set("eff_jing",query("max_jing",  me), me);

        // �ָ�����
        set("neili",query("max_neili",  me), me);

        // �ָ�����
        set("jingli",query("max_jingli",  me), me);

        // �ָ�ʳ��
        set("food", me->max_food_capacity(), me);

        // �ָ���ˮ
        set("water", me->max_water_capacity(), me);

        // �ⶾ
        set("noposion", 1, me);
}

void restore_origin(object me)
{
        int i;
        mapping pmap;
        string* sk;

        message_vision(HIY "�ף�$N���������а��һ���޹�״��\n\n" NOR, me);
        
        // �ָ��� PK, MPK
        set("shen", 0, me);
        set("PKS", 0, me);
        set("MKS", 0, me);

        // disbale���ҷ��������书

        pmap = me->query_skill_prepare();                // ׼���ļ���
        if (!pmap) pmap = ([]);

        if( mapp(pmap) && sizeof(pmap) > 0 )
        {
                sk = keys(pmap);
                for (i=0; i<sizeof(sk); i++)
                {
                        me->prepare_skill(sk[i]);        // ���׼���ļ���
                }
        }
        
        sk = keys(me->query_skills());                        // ��ѧ�书�����Ƽ���
        for(i = 0; i<sizeof(sk); i++)
        {
                me->map_skill(sk[i]);                        // ȡ������ĳ���书
                map_delete(me->query_skills(), sk[i]);        // ������ѧ���书
        }

        delete("family", me);

        me->reset_action();                                // ���
}

int help(object me)
{
write(@HELP
ָ���ʽ : wizlian <�书/����> ֵ

������������ʦ���书�������޸ĸ������ԣ���������������...

wizlian          : �ָ��������԰�����������������������ʳ���ˮ��
wizlian org      : ��ʼ���������ݣ����������书���񽵵�0��
wizlian [����] n : �޸�ĳ������Ϊn��
wizlian [�书] n : �޸�ĳ���书Ϊn��������Ϊm�����С����Ͳ��޸ġ�

HELP
    );
    return 1;
}