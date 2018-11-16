// This program is a part of NT MudLIB

#include <ansi.h>

// classp ?
// abilities

// ��������
string *bas_ability = ({
        "str",
        "int",
        "con",
        "dex",
        "kar",
        "qi",
        "jing",
        "neili",
        "jingli",
        "ref_neili",
        "ref_qi",
        "ref_jing",
        "attack",
        "dodge",
        "parry",
        "fatal",
        "full_self",
        "avoid_busy",
        "avoid_weak",
        "reduce_damage",
});

mapping max_ability = ([
        "str"   : 500,
        "int"   : 500,
        "con"   : 500,
        "dex"   : 500,
        "kar"   : 70,
        "qi"    : 10,
        "jing"  : 10,
        "neili" : 10,
        "jingli": 10,
        "ref_neili": 20,
        "ref_qi"   : 20,
        "ref_jing" : 20,
        "attack": 10,
        "dodge" : 10,
        "parry" : 10,
        "fatal" : 10,
        "full_self" : 10,
        "avoid_busy": 10,
        "avoid_weak": 10,
        "reduce_damage": 10,
]);

string *bas_ability_info = ({
        "��ɫ����ֵ��ߣ���\t","��ɫ����ֵ��ߣ���\t","��ɫ����ֵ��ߣ���\t",
        "��ɫ��ֵ��ߣ���\t","��ɫ����ֵ��ߣ���\t","�����Ѫֵ��ߣ���\t",
        "�����ֵ��ߣ���\t","�������ֵ��ߣ���\t","�����ֵ��ߣ���\t",
        "�ָ���Ѫ��ߣ�����\t","�ָ�������ߣ�����\t","�ָ�������ߣ�����\t",
        "ֱ�����л���������\t","ֱ�����ܻ���������\t","ֱ���мܻ���������\t",
        "������������������\t","ս�������������\t","����æ�һ���������\t",
        "������������������\t","�����˺�����������\t",
});

mapping bas_ability_pot = ([
        "attack":       2,
        "dodge":        2,
        "parry":        2,
        "fatal":        3,
        "full_self":    3,
        "avoid_busy":   3,
        "avoid_weak":   3,
        "reduce_damage":3,
]);

mapping fam_ability = ([
        "�䵱��":({"reduce_busy", "add_busy", "tjq_defense", "tu_damage", "luan_attack"}),
]);

mapping fam_ability_info = ([
        "������": ({
                        "��yijinjing��ղ�������yun jin,����Ѫ���͵�20/25/30/35/40%����ŭĿ���Ч��",
                        "һ����ɢ ���н��� 80/70/60/50/40 %���˺�����100/200/300/400/500%,ͬʱ����Ϊ0���������� 90%",
                        "���ֵ��ӳֶ��������ʱ���˺��������� 2/4/6/8/10%",
                        "�����м�Ϊ��ղ�����ʱ������1/2/3/4/5%���˺�����",
                        "���ֵ���ÿ����ϰ10��parry skill��ս������������1/2/3/4/5%",
                }),
        "�䵱��": ({
                        "������ϻ���æ�Ҽ��ʣ�����",
                        "�������æ�Ҷ��ּ��ʣ�����",
                        "̫��ȭ�����������ߣ�����",
                        "����̫��ͼ�˺�����ߣ�����",
                        "�����һ�����������ߣ�����",
                }),
        "�������":({
                        "���º������Ͷ�������  2/4/6/8/10%",            
                        "���������챶���������� 6/12/18/24/30%",
                         "�ƶ���ɽ��������Ч������  2/4/6/8/10%",
                        "��������Ч������ (���������߶���) 20/40/60/80/100%",
                        "����Ѫ���͵�20/25/30/35/40%������ѪЧ��",
                }),
                
]);

string *tf_ability = ({
        "gold_find",
        "double_day",
        "add_zq",
        
        "kingkong",
        "magic_find",
        "ability_delay",
        
        "anti_blow",
        "add_damage",
        "dealer",
        
        "indentily",
        "wushen",
        "qn_lose",
        
        "attack"
        "dodge",
        "add_exp",
        
        "avoid_cd",
        "add_damage",
        "avoid_dodge",
        
        "reduce_damage",
        "add_buff",
        "avoid_busy",
        
        "defense",
        "double_damage",
        "shashen",
        
        "add_blade",
        "add_sword",
        "add_unarmed"
});

string *tf_ability_info = ({
        /*
ս���ؾ���ս��ʱ�Զ��ָ�������
     ս��������ս��ʱ�Զ��ָ���Ѫ��
        ��һ����

���ˣ�1�����������������ö���Ľ�Ǯ��
������1����������ÿ��˫������ʱ��1Сʱ��
���ӣ�1����ÿ����õ���������ֵ����1�㡣
����
ս��ʱ��HP=0ʱ��20%�ļ��ʳ������Ӹ���Ч���������Ժ�ӵ������HP
�ڶ�����

��գ�2�������Ӷ�boss�������ľ��Է���5%��10%�㡣
ǿ�ˣ�2��������װ����������5%��10%�㡣
������2���������书abilityЧ������ʱ������25%��50%��
����
��ͨ����������100%
����
���پ������ӳ��еļ��� ������˫���˺����� ���Ǽ���30%�˺����ʡ����������������мܵļ��� ��ͨ��perform�˺��ӳ�
��������

������3����ʹ�����20%��40%��60%�ļ��ʷ�ֹ����ı�ɱ����
��ħ��2�������Ӷ�boss����ľ����˺�5%��10%�㡣
�̲ţ�2���������������10%�������۸񽵵�10%��
����
���ܼ�������
ѥ
���ľ���

���ۣ�3��������ʱ��33%��66%��100%�������ñ�ʯ��װ���ĵȼ����һ����
����3���������ͷ���Ч������3%��6%��10%��
��ͣ�4��������ʱ��5%��10%��15%��20%�Ļ��ʲ���Ǳ�ܡ�
����ף��
�����������ѵ��˺��������ķ�ŭֵ40��
ս��ף��
ȫ������˺������������ķ�ŭֵ70��
����ף��
�����������ѵķ����������ķ�ŭֵ40��
�ػ�ף��
ȫ�����������������������ķ�ŭֵ80��
���徳��

ӥ�ۣ�3������������50%���ʴ�������������5%��10%��15%��BUFF�ࣩ��
���飨3������������50%���ʴ�������������5%��10%��15%��BUFF�ࣩ��
���̣�3���������л�ȡ��5%��10%��15%�Ķ��⾭�顣

��������

���棨2���������书����Ʒ���츳���ܣ���Ʒ������ȴʱ�併��10%��20% ��
ͨ����5����ÿһ�ι�����4%��5%��6%��7%��8%�ļ��ʽ���ͨ��״̬����ɵ��˺����� (�Է��ȼ�*4%��8%��12%��20%)�㣨BUFF�ࣩ��
ǿϮ��5����ÿһ�ι�����5%��10%��15%��20%��25%�Ļ����õз����貨΢��֮��������Ṧ�������������Ч��
�Ʒ���ߣ��ҵ��������Ŀǰ�Ʒ��ļ���������һ�������������Ʒ����10������ô������Ʒ�10�㣬
       �ͱ����11�㡣
   ���м�ǿ��˵ʵ�����ҿ���������ʲô��������
   ˫���������������˺��Ļ����ϣ���2������Ҫ��һ�����ԡ�����Խ��Խ�á�
   ����������ǳ���Ҫ�����ԣ���ɱ�����ѪЧ����
����������ǳ���Ҫ�����ԣ���ɱ�����ѪЧ����
���߾���

����ɼ��3������3%��6%��10%�ļ������ܵ�����ʱ�ֿ�һ����˺���
������5����������ֵ����40%ʱ����û������ԣ���װ��ʱ������ԣ�����4%��8%��12%��16%��20%��Ч��
��ң��3����ս������10%��20%��30%�Ļ�������æ�ҡ�

�ڰ˾���

������5�����ܵ������˺�����20%��40%��60%��80%��100%�������ӷ������ȼ�*5%����
����3��������ʱ����5%��10%��15%��˫���������ʡ�
ɱ��3��������Ŀ�꿹�ԣ�ֱ�����30%��40%��50%�Ķ��ι����˺���
ɱ¾-����ʱ�м��ʶԵ�ǰ���������˽���һ�ι���
������
��������쳣״̬���类������ħ�����ж������ҵȣ����ķ�ŭֵ50��
me->query_craze() < 1000
���ķ�ŭburning
me->cost_craze()
berserk���ӷ�ŭ
�ھž���

���ʣ�5����ʹ�õ����书����4%��8%��12%��16%��20%�����м��˺�Ч����
��ʥ��5����ʹ�ý����书����4%��8%��12%��16%��20%�����м��˺�Ч����
ȭ����5����ʹ��ȭ���书����4%��8%��12%��16%��20%�����м��˺�Ч����
*/
});
        
mapping max_ability3 = ([
        "str"   : 1,
        "int"   : 1,
        "con"   : 2,
        "dex"   : 2,
        "kar"   : 2,
        "qi"    : 10,
        "jing"  : 10,
        "neili" : 10,
        "jingli": 10,
        "ref_neili": 20,
        "ref_qi"   : 20,
        "ref_jing" : 20,
        "attack": 10,
        "dodge" : 10,
        "parry" : 10,
        "fatal" : 10,
        "full_self" : 10,
        "avoid_busy": 10,
        "avoid_weak": 10,
        "reduce_damage": 10,
]);        
        

int do_ability_cost(object ob, string arg, int flag);
int check_ability(object me,string arg, int flag);
int improve_ability(object me,string arg, int flag);
int valid_ability_improve(object me, string arg, int flag);
string get_ability_idf(object me,string arg, int flag);
string get_ability_info(object ob, string arg, int flag);

int valid_ability_improve(object me, string arg, int flag)
{
        int level;
        int a_lvl;

        a_lvl = check_ability(me, arg, flag);
        level = max_ability[arg];
        if( a_lvl >= level ) 
                return 0;
 
        return 1;
}

varargs int check_ability(object me,string arg, int flag)
{
        int result;
        
        // Ability ����
        result=query("ability2/"+query("family/family_name", me)+"/"+arg, me)+query("ability1/"+arg, me);
                
        return result;
}

int check_ability_cost(object me, string arg, int flag) 
{
        int cost;

        if( flag == 1 ) {
                cost = 2;
        } else {
                if( member_array(arg, bas_ability) == -1 ) {
                        return 0;
                }
                cost = bas_ability_pot[arg];
                if( !cost ) {
                        cost = 1;
                }
        }
        return cost;
}

// ÿ�κķ�һ��������
int do_ability_cost(object me, string arg, int flag)
{
        int cost;

        cost = check_ability_cost(me, arg, flag);
        
        if( flag == 1 || flag == 0 ) {
                if( cost>query("ability", me)-query("learned_ability", me)){
                        return 0;
                }
                addn("learned_ability", cost, me);
        }
        
        return 1;
}

int improve_ability(object me,string arg, int flag)
{
        int lv;
        string myclass;

        myclass = query("family/family_name", me);
        if( !flag ) {
                addn("ability1/"+arg, 1, me);
        } else if( flag == 1 ) {
                addn("ability2/"+myclass+"/"+arg, 1, me);
        } 
        return 1;
}

string get_ability_info(object ob, string arg, int flag)
{
        int lv, cost, n;
        string desc, msg, myclass;

        //lv = check_ability(ob, arg, flag);
        cost = check_ability_cost(ob, arg, flag);
        desc = get_ability_idf(ob,arg,flag);
        if( flag == 1 ) {
                // ability's ���ɼ���
                myclass=query("family/family_name", ob);
                if( arrayp(fam_ability[myclass]) ) {
                        n = member_array(arg,fam_ability[myclass]);
                        if( n != -1 ) {
                                msg = fam_ability_info[myclass][n];
                                msg = sprintf(msg+"\t%-12s"HIC"%5d\n"NOR,desc, cost);
                                return msg;
                        }
                }
                return "";
        }
        
        n = member_array(arg, bas_ability);
        if( n != -1 ) {
                msg = bas_ability_info[n];
                msg = sprintf(msg+"\t%-12s"HIC"%5d\n"NOR, desc, cost);
                return msg;
        }
        return "";
}


string get_ability_idf(object me,string arg, int flag)
{
        int level = max_ability[arg];
        int lev = check_ability(me,arg,flag);       
        // 1,2,3,4 Basic
        // 5,6,7 Advanced
        // 8,9: Master
        // 10: Grand Master
        string *tough_level_desc = ({
                YEL "һ����֪" NOR,//0
                HIB "�����ž�" NOR,//1
                HIB "��֪һ��" NOR,//2
                HIB "��ͨƤë" NOR,//3
                HIB "������" NOR,//4
                CYN "��Ȼ���" NOR,//5
                CYN "�������" NOR,//6
                CYN "�Ƿ��켫" NOR,//7
                HIC "һ����ʦ" NOR,//8
                HIC "������˫" NOR,//9
                HIW "��ɲ�" NOR,//10
        });
        string desc = sprintf(HIM"%3d/%3d"NOR, lev, level);
        if( lev >= 10 ) lev = 10;
        return (tough_level_desc[lev]+"��"+ desc+"��");
}

