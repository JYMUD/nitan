// six-book.c
#include <ansi.h>
inherit ITEM;

string skl_name();
int do_yanjiu(string arg);
void create()
{
        set_name( HIC"��������"NOR,({ "sixfinger book","book"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","����һ��ͼ�����涼���ݺύ���ֱ�ߡ�ԲȦ�ͻ��Ρ�\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name":         (: skl_name :), //name of the skill
                        "exp_required": 500000,         //minimum combat experience required
                        "jing_cost":    100,            // jing cost every time study this
                        "difficulty":   45,             // the base int to learn this skill
                        "min_skill":    0,              // the minimum level you can learn
                        "max_skill":    120,            // the maximum level you can learn
                        "need" : ([ "force" : 301 ]),
                ]) );
        }
}

string skl_name()
{
        string *sks;

        sks = keys(SKILL_D("six-finger")->query_sub_skills());
        return sks[random(sizeof(sks))];
}

void init()
{
        add_action("do_yanjiu","yanjiu");
        add_action("do_yanjiu","research");
}
int do_yanjiu(string arg)
{
        object ob = this_object();
        object me = this_player();
        string skill,book;
        string msg;
        
        if (!present(ob,me)) return 0;

        if ((int)me->query_skill("literate",1)<1)
        {
                write("���Ǹ���ä����ѧ�����д��(literate)�ɡ�\n");
                return 1;
        }

        if (me->is_busy() || me->is_fighting())
        {
                write("����æ���ء�\n");
                return 1;
        }

        if (!arg || sscanf(arg,"%s from %s",skill,book)!=2)
        {
                write("�ж�������ָ���� yanjiu ������ from book\n");
                return 1;
        }

        if (!id(book))
        {
                write("û���Ȿ�顣\n");
                return 1;
        }

        if (skill != "��ȥ����" && skill != "Ԧ����" 
           && skill != "ciqu" && skill != "yuqi")
        {
                write("���ϲ�û�н��ܹ���"+skill+"�����ݡ�\n");
                return 1;
        }

        if( query("combat_exp", me)<1000000 )
        {
                write("���ʵս����̫�ͣ���������ô��µĶ�����\n");
                return 1;
        }

        if( query("jing", me)<100 || 
            query("qi", me)<100 || 
            query("neili", me)<200 )
  {
          write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
          return 1;
  }
  
  switch(skill)
  {
          case "ciqu":
          case "��ȥ����":
           if( query("can_perform/six-finger/ciqu", me) )
           {
                write("�㲻���Ѿ�������\n");
                return 1;
           }
           if (me->query_skill("six-finger", 1) < 120)
           {
                write("�������񽣲����������޷��ж��˾��У�\n");
                return 1;
           }

           if (random (10) != 1)
           {
                write("���о��˰��죬��Ȼ�޷�������ȥ�������ڻ��ͨ��\n");
                me->start_busy(15); 
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "�������ף���ϸ�о����������ص���ѧ�����Ǽ��������"
                     "����\n" NOR;
           msg += HIW "$N" HIW "̯��˫�֣���ָ��������ʱ��������ȣ���"
                  "�����ڣ���������������Ѩ��һ��������" HIW "��\n" NOR;
           msg += HIG "$N" HIG "��̾һ�����п���ǧ���������ջص��\n" NOR; 
           message_vision(msg, me); 

                   me->improve_skill("finger", 1500000);
                   me->improve_skill("six-finger", 1500000);

           write(HIW "��ѧ���ˡ�" HIG "��ȥ����" HIW "����\n" NOR);
           set("can_perform/six-finger/ciqu", 1, me);
           return 1;
          case "yuqi":
          case "Ԧ����":
           if( query("can_perform/six-finger/yuqi", me) )
           {
                write("�㲻���Ѿ�������\n");
                return 1;
           }
           if (me->query_skill("six-finger", 1) < 120)
           {
                write("�������񽣲����������޷��ж��˾��У�\n");
                return 1;
           }
           if (me->query_skill("force", 1) < 120)
           {
                write("���ڹ���򲻹����޷��ж��˾��У�\n");
                return 1;
           }

           if (random (20) != 1)
           {
                write("���о��˰��죬��Ȼ�޷�����Ԧ�������ڻ��ͨ��\n");
                me->start_busy(15);
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "�������ף���ϸ�о����������ص���ѧ�����Ǽ��������"
                     "����\n" NOR;
           msg += HIM "$N" HIM "һ����Х��ʮָ�׵����پ�����������ӿ����ͷ������"
                  "�˷������಻������ʱ�����籼�������޾������������Ȼ�������" HIM 
                  "��\n" NOR;
           msg += HIG "$N" HIG "��̾һ�����п���ǧ���������ջص��\n" NOR; 
           message_vision(msg, me); 

                   me->improve_skill("finger", 1500000);
                   me->improve_skill("six-finger", 1500000);

           write(HIW "��ѧ���ˡ�" HIG "Ԧ����" HIW "����\n" NOR);
           set("can_perform/six-finger/yuqi", 1, me);
           return 1;
                  break;
          default:
                  return 0;
  }
  return 0;
}