//tangfeng@SJ 
//story��¼
//add ���Ǿ� by tangfeng 2004/11/1
//add ���Ӣ�۴� by redhat@Sjmud 2009/4/8

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);
string get_string(string str);

//feihu
string quest_feihu(object me); 
string feihu_skill(object me);
//tlbb
string quest_tlbb(object me); 
string tlbb_skill(object me); 
//lchj
string quest_lchj(object me); 
string lchj_skill(object me); 
//shediao
string quest_shediao(object me); 
string shediao_skill(object me); 
//tulong
string quest_tulong(object me);
string tulong_skill(object me);

int main(object me, string arg)
{
        object ob;
        string arg1,arg2,str;
        int i_all=0,i_feihu=0,i_tlbb=0,i_lchj=0,i_shediao=0,i_tulong=0;

        str="\n";
        if (!arg)
        {
                ob = me;
                i_all=1;
        }
        else if (sscanf(arg, "%s form %s", arg1,arg2)) 
        {     
                switch (arg1)
                {
                case "feihu" : i_feihu=1;break;
                case "tlbb"  : i_tlbb=1;break;
                case "lchj"  : i_lchj=1;break;//���Ǿ�
                case "shediao"  : i_shediao=1;break;//���Ӣ�۴�
                case "tulong": i_tulong=1;break;//����������
                default :
                        return notify_fail("Ŀǰֻ����ѩɽ�ɺ��������˲������Ǿ������Ӣ�۴������������ǡ���ϸ��������İ�����\n");
                }
                if (wizardp(me))
                {
                        ob = present(arg2, environment(me));
                        if (!ob) ob = LOGIN_D->find_body(arg2);
                        if (!ob) ob = find_living(arg2);
                        if (!ob || !me->visible(ob)) return notify_fail("��Ҫ�쿴˭��״̬��\n");
                } 
                else
                        return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");
        }
        else
        {
                ob = me;
                switch (arg)
                {
                        case "feihu" : i_feihu=1;break;
                        case "tlbb"  : i_tlbb=1;break;
                        case "lchj"  : i_lchj=1;break;//���Ǿ�
                        case "shediao"  : i_shediao=1;break;//���Ӣ�۴�
                        case "tulong": i_tulong=1;break;
                        default :
                                if (wizardp(me))
                                {
                                        ob = present(arg, environment(me));
                                        if (!ob) ob = LOGIN_D->find_body(arg);
                                        if (!ob) ob = find_living(arg);
                                        if (!ob || !me->visible(ob)) return notify_fail("��Ҫ�쿴˭��״̬��\n");
                                        i_all=1;
                                } 
                                else
                                        return notify_fail("Ŀǰֻ����ѩɽ�ɺ��������˲������Ǿ������Ӣ�۴������������ǡ���ϸ��������İ�����\n");
                }
        }


        if (!wizardp(me) && me->is_busy())
                return notify_fail("����æ���ء�\n");
        
        if(wizardp(me) && userp(ob)&& me!=ob)
        {
                str =   "������������������������������������������������������������\n";
                str +=get_string(YEL"�������ڲ�ѯ"+query("name", ob)+"�ļ�¼��"NOR);
                tell_object(me,str);
        }

        if(i_all==1)  
        {
                str =  "������������������������������������������������������������\n";
                str +=get_string(HIY"��ʮ�����������¼��"NOR);
                str += "������������������������������������������������������������\n";
                if(query("mana", ob)||wizardp(me))
                {   
                        str +=sprintf("%30s",HIG"������")+query("name", ob);
                        str +="\n";
                        str +=sprintf("%30s",HIG"������")+chinese_number(query("mana", ob))+NOR;
                        str +="\n";
                }
                if(wizardp(me) && query("id", me)=="lonely")
                {
                        str +=sprintf("%30s",HIG"��Դ��")+chinese_number(ob->query_kar())+NOR;
                        str +="\n";
                        str +=sprintf("%30s",HIG"���ԣ�")+chinese_number(ob->query_int())+NOR;
                        str +="\n";
                }
                str += quest_feihu(ob);
                str += quest_tlbb(ob);
                str += quest_lchj(ob);
                str += quest_shediao(ob);
                str += quest_tulong(ob);
        }
        else if(i_feihu==1)        
                str = quest_feihu(ob);
        else if(i_tlbb==1)
                str = quest_tlbb(ob);
        else if(i_lchj==1)
                str = quest_lchj(ob);
        else if(i_shediao==1)
                str = quest_shediao(ob);
        else if(i_tulong==1)
                str = quest_tulong(ob);
        else return notify_fail("Ŀǰֻ����ѩɽ�ɺ��������˲������Ǿ������Ӣ�۴������������ǡ���ϸ��������İ�����\n");

        str +=   "������������������������������������������������������������\n";
        tell_object(me,str);
        return 1;
}

string quest_feihu(object me)
{
        string str= "\n";

        if(!query("quest/ѩɽ�ɺ�",me))
        {
                str = "������������������������������������������������������������\n";
                str +=get_string(HIW"��Ŀǰ����ѩɽ�ɺ���û���κμ�¼��"NOR);
                return str;
        }

        str =   "������������������������������������������������������������\n";
        str +=get_string(HIW"��ѩɽ�ɺ���"NOR);
        str +=  "������������������������������������������������������������\n";
        if(query("quest/ѩɽ�ɺ�/time",me))
        {
                if(!query("quest/ѩɽ�ɺ�/��ҩƪ/over",me) )
                        str +=get_string(WHT"��Ϸ��¼ʱ��"+CHINESE_D->chinese_time(time()-query("quest/ѩɽ�ɺ�/time",me))+"��"NOR);
                else str +=get_string(WHT"��Ϸ��¼ʱ�䣺"+CHINESE_D->chinese_date(query("quest/ѩɽ�ɺ�/time",me),1)+"��"NOR);
        }
        if(query("quest/ѩɽ�ɺ�/combat_exp", me))
        {
                        if(!query("quest/ѩɽ�ɺ�/��ҩƪ/over",me) )
                                str +=get_string(WHT"��Ϸ��¼����"+chinese_number(query("combat_exp",me)-query("quest/ѩɽ�ɺ�/combat_exp",me))+"��"NOR);
                        else str +=get_string(WHT"��Ϸ��¼���飺"+query("quest/ѩɽ�ɺ�/combat_exp",me)+"��"NOR);
                        str +="\n";
        }
        if(!query("quest/ѩɽ�ɺ�/��ҳ����ƪ",me))
        {
                str +=get_string(HBRED"��Ϸ��¼���ҡ��㻹��ҪŬ����"NOR);
                str +=feihu_skill(me);
                return str;
        }
        if(!query("quest/ѩɽ�ɺ�/��ҳ����ƪ/over",me))
        {
                if(random(2)) str +=get_string(HBRED"��һ������ΰ�����쳽�һ�����ƺ��ҵ�����"NOR);
                else str +=get_string(HBRED"��һ��̽�������Ѱ��ʧ��������ҳ������"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=get_string(YEL"���Ѿ�����������ƺ��ҵ��������һЩ������"NOR);
        
        if(!query("quest/ѩɽ�ɺ�/����ƪ",me))
        {
                if(random(2)) str +=get_string(HBRED"���ֻ������ù�һЩ���£���һ��������١�"NOR);
                else          str +=get_string(HBRED"���������˷�����һ���������ׯ��"NOR);
                str +=feihu_skill(me);
                return str;
        }
        
        if(!query("quest/ѩɽ�ɺ�/����ƪ/over",me))
        {
                if(random(2)) str +=get_string(HBRED"�����硢��֮�����ƺ��Ѿ����ˣ�ֻ�ǹ��������"NOR);
                else          str +=get_string(HBRED"���������Ѿ����ˣ�ֻ��������������������˷���"NOR);
                str +=feihu_skill(me);
                return str;
        }   
        str +=get_string(YEL"���Ѿ���ԭ�����˷�ͺ��һ�����࣬���һЩ������"NOR);
        
        if(!query("quest/ѩɽ�ɺ�/��ҩƪ",me))
        {
                if(random(2)) str +=get_string(HBRED"������С�˰��㣬���˷��ж�����δ����"NOR);
                else          str +=get_string(HBRED"20��ǰ�ľ����Ѿ����ˣ�����֮˵Ҳ��һ����ᡣ"NOR);
                str +=feihu_skill(me);
                return str;
        }
        
        if(!query("quest/ѩɽ�ɺ�/��ҩƪ/over",me))
        {
                if(random(2)) str +=get_string(HBRED"�����Ѿ����ˣ������˷��ж�����δ������һ����Ѱ�ҽ�ҩ��"NOR);
                else          str +=get_string(HBRED"20��ǰ�������Ѿ����ˣ�Ŀǰ�ؼ������Ѱ���������˷�Ľ�ҩ��"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=get_string(YEL"�嶾�̣���ɹ����������ض�����Ǻ��ġ�"NOR);
        str +=get_string(YEL"ҩ���ȣ���ɹ������ƽ�ҩ�ɹ������һЩ������"NOR);
        
        if(!query("quest/ѩɽ�ɺ�/����",me))
        {
                str +=get_string(HBRED"���Ѿ����ѩɽ�ɺ��Ļ�����ڣ�����漰��һ�����ء�"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=   "������������������������������������������������������������\n";
        str +=get_string(HIB"���������ء�"NOR);
        str +=   "������������������������������������������������������������\n";
        if(query("quest/ѩɽ�ɺ�/����/time",me))
                str +=get_string(WHT"Ѱ����¼ʱ�䣺"+CHINESE_D->chinese_date(query("quest/ѩɽ�ɺ�/����/time",me),1)+"��"NOR);
        if(query("quest/ѩɽ�ɺ�/����/combat_exp",me))
        {
                str +=get_string(WHT"Ѱ����¼���飺"+query("quest/ѩɽ�ɺ�/����/combat_exp",me)+"��"NOR);
                str +="\n";
        }
        if(!query("quest/ѩɽ�ɺ�/����/start",me))
        {
                str +=get_string(HBRED"������Ѱ�Ҵ�˵�еĴ������ء�"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=get_string(YEL"���Ѿ���ʼѰ�Ҵ�˵�еĴ������ء�"NOR);
        if(query("quest/ѩɽ�ɺ�/����/jinku",me))
                str +=get_string(YEL"���Ѿ��Ӵ������ػ�ô����ĲƱ��������ƽ�ȵȡ�"NOR);
        if(query("quest/ѩɽ�ɺ�/����/yaoku", me))
                str +=get_string(YEL"�㷢���˴���ҩ�⣬����ҩ��������������������ҩ��"NOR);
        if(query("quest/ѩɽ�ɺ�/����/bingqiku",me))
                str +=get_string(YEL"���Ѿ��ھ������������ı�����"+chinese_number(query("quest/ѩɽ�ɺ�/����/bingqiku",me))+"������"NOR);
        if(query("quest/ѩɽ�ɺ�/����/shuku",me))
                str +=get_string(YEL"����鷿���ֵ�һ�����ң���������Ѱ�ҵ����������������ҩ��"NOR);
        if(query("quest/ѩɽ�ɺ�/�书/lengquanshengong",me))
                str +=get_string(YEL"�㾹Ȼ��һ����ҩ���ҵ�һ��ֽ�ţ���������Ȫ���ؼ��ĵص㡣"NOR);
        else if(query("quest/ѩɽ�ɺ�/����/shuku",me)>=3)
                str +=get_string(YEL"���һ����ҩ���ҵ�һ���ƺ��������书��ֽ�ţ�Ŀǰֻ��δ��Ҫ�졣"NOR);
        str +=feihu_skill(me);
        return str;
}
string feihu_skill(object me)
{
        string str= "";

        if(me->query("quest/ѩɽ�ɺ�/��ҳ����ƪ/over"))
        {
                str =   "������������������������������������������������������������\n";
                str +=get_string(HIC"���ɺ��书��"NOR);
                str +=  "������������������������������������������������������������\n";
                if(query("quest/ѩɽ�ɺ�/�书/time",me))
                        str +=get_string(WHT"�书��¼ʱ�䣺"+CHINESE_D->chinese_date(query("quest/ѩɽ�ɺ�/�书/time",me),1)+"��"NOR);
                if(query("quest/ѩɽ�ɺ�/�书/combat_exp",me))
                {
                        str +=get_string(WHT"�书��¼���飺"+query("quest/ѩɽ�ɺ�/�书/combat_exp",me)+"��"NOR);
                        str +="\n";
                }
                if(query("quest/ѩɽ�ɺ�/�书/fight_hu",me))
                {
                   if(query("quest/ѩɽ�ɺ�/�书/win_hu",me))
                           str +=get_string(HIC"�������쳽��й�"+chinese_number(query("quest/ѩɽ�ɺ�/�书/fight_hu",me))+"�ν����������"+chinese_number(query("quest/ѩɽ�ɺ�/�书/win_hu",me))+"��ʤ����"NOR);
                   else
                           str +=get_string(HIC"�������쳽��й�"+chinese_number(query("quest/ѩɽ�ɺ�/�书/fight_hu",me))+"�ν�������ϧһ��Ҳû��ʤ����"NOR);
                }

                if(query("quest/ѩɽ�ɺ�/�书/hujiadaofa",me))
                        str +=get_string(HBYEL"���Ѿ�ѧ���˺��ҵ��������ŵ�������Ľ�������������"NOR);
                else if(query("quest/ѩɽ�ɺ�/�书/hujiadaofa_fail",me)>=3 && query("registered",me)<3) // �������е��ظ�
                        str +=get_string(YEL"��ʧȥ��ѧϰ���ҵ����Ļ��ᣬ���������VIP���㽫����µĻ��ᡣ"NOR);
                else if(query("quest/ѩɽ�ɺ�/�书/hujiadaofa_fail",me) && query("quest/ѩɽ�ɺ�/�书/hujiadaofa_fail",me)<3 && query("registered",me)<3)
                        str +=get_string(YEL"��ʧȥ��ѧϰ���ҵ�����"+chinese_number(query("quest/ѩɽ�ɺ�/�书/hujiadaofa_fail",me))+"�λ��ᣬ���㻹��"+chinese_number(3-query("quest/ѩɽ�ɺ�/�书/hujiadaofa_fail",me))+"���ᡣ"NOR);
                else if(query("quest/ѩɽ�ɺ�/�书/hujiadaofa_fail",me))
                        str +=get_string(YEL"��ʧȥ��ѧϰ���ҵ�����"+chinese_number(query("quest/ѩɽ�ɺ�/�书/hujiadaofa_fail",me))+"�λ��ᣬ���㻹�����޻��ᡣ"NOR);
                else
                        str +=get_string(HBRED"������ӵ��ѧϰ���ҵ����Ļ��ᡣ��������ʵ���ʱ����̺�쳡�"NOR);
       
           if(query("quest/ѩɽ�ɺ�/��ҩƪ/over",me))
           {
                   if(query("quest/ѩɽ�ɺ�/�书/fight_miao",me))
                   {
                           if(query("quest/ѩɽ�ɺ�/�书/win_miao",me))
                                   str +=get_string(HIC"���������˷���й�"+chinese_number(query("quest/ѩɽ�ɺ�/�书/fight_miao",me))+"�ν����������"+chinese_number(query("quest/ѩɽ�ɺ�/�书/win_miao",me))+"��ʤ����"NOR);
                           else str +=get_string(HIC"���������˷���й�"+chinese_number(query("quest/ѩɽ�ɺ�/�书/fight_miao",me))+"�ν�������ϧһ��Ҳû��ʤ����"NOR);
                   }
                   if(query("quest/ѩɽ�ɺ�/�书/miaojiajianfa",me))
                           str +=get_string(HBYEL"���Ѿ�ѧ������ҽ��������������Ž����������߽��������ܴ�"NOR);
                   else if(query("quest/ѩɽ�ɺ�/�书/miaojiajianfa_fail",me)>=3 && query("registered",me)<3)
                           str +=get_string(YEL"���˷���ѧϰ��ҽ����Ļ��ᣬ���������VIP���㽫����µĻ��ᡣ"NOR);
                   else if(query("quest/ѩɽ�ɺ�/�书/miaojiajianfa_fail",me) && query("quest/ѩɽ�ɺ�/�书/miaojiajianfa_fail",me)<3 && query("registered",me)<3)
                           str +=get_string(YEL"��ʧȥ��ѧϰ��ҽ�����"+chinese_number(query("quest/ѩɽ�ɺ�/�书/miaojiajianfa_fail",me))+"�λ��ᣬ���㻹��"+chinese_number(3-query("quest/ѩɽ�ɺ�/�书/miaojiajianfa_fail",me))+"���ᡣ"NOR);
                   else if(query("quest/ѩɽ�ɺ�/�书/miaojiajianfa_fail",me))
                           str +=get_string(YEL"��ʧȥ��ѧϰ��ҽ�����"+chinese_number(query("quest/ѩɽ�ɺ�/�书/miaojiajianfa_fail",me))+"�λ��ᣬ���㻹�����޻��ᡣ"NOR);
                   else str +=get_string(HBRED"������ӵ��ѧϰ��ҽ����Ļ��ᡣ��������ʵ���ʱ��������˷硣"NOR);

                   if(query("quest/ѩɽ�ɺ�/�书/lengquanshengong_teach",me))
                           str +=get_string(HBYEL"���Ѿ������硢���ϴ������ܣ��������˷ﴦ������Ȫ�񹦡�"NOR);
                   else if(query("quest/ѩɽ�ɺ�/�书/lengquanshengong",me))
                           str +=get_string(YEL"���ƺ�����Ҫ�����Ȫ�񹦵�������ᡣ"NOR);
                   else if(query("quest/ѩɽ�ɺ�/�书/shuku",me)<3 )
                           str +=get_string(YEL"�㻹��ѧϰ��Ȫ�񹦵Ļ��ᡣ�񹦾�˵�ڱ���֮�С�"NOR);
                   else if(query("quest/ѩɽ�ɺ�/�书/shuku",me)==3 )
                           str +=get_string(YEL"��������һ��ѧϰ��Ȫ�񹦵Ļ��ᡣ��ϧû�гɹ���"NOR);
                   else if(query("quest/ѩɽ�ɺ�/�书/shuku",me)>=4 && query("registered",me)>=3)
                           str +=get_string(YEL"������������ѧϰ��Ȫ�񹦵Ļ��ᡣ��ϧû�гɹ���"NOR);
           }
        }
        return str;
}
string quest_lchj(object me)
{
        string str= "\n";

        if(!query("quest/���Ǿ�",me))
        {
                str =    "������������������������������������������������������������\n";
                str +=get_string(HIW"��Ŀǰ�������Ǿ���û���κμ�¼��"NOR);
                return str;
        }

        str =   "������������������������������������������������������������\n";
        str +=get_string(HIW"�����Ǿ���"NOR);
        str +=  "������������������������������������������������������������\n";

        if(query("quest/���Ǿ�/time",me))
        {
                if(!query("quest/���Ǿ�/���̽��ƪ/over",me))
                        str +=get_string(WHT"��Ϸ��¼ʱ��"+CHINESE_D->chinese_time(time()-query("quest/���Ǿ�/time",me))+"��"NOR);
                else str +=get_string(WHT"��Ϸ��¼ʱ�䣺"+CHINESE_D->chinese_date(query("quest/���Ǿ�/time",me),1)+"��"NOR);
        }
        if(query("quest/���Ǿ�/combat_exp",me))
        {
                if(!query("quest/���Ǿ�/���̽��ƪ/over",me) && !query("quest/���Ǿ�/���̽��ƪ/over",me))
                {
                        if(query("combat_exp",me)> query("quest/���Ǿ�/combat_exp",me))
                                str +=get_string(WHT"��Ϸ��¼����"+chinese_number(query("combat_exp",me)-query("quest/���Ǿ�/combat_exp",me))+"��"NOR);
                        else if(query("combat_exp",me)== query("quest/���Ǿ�/combat_exp",me))
                                str +=get_string(WHT"��Ϸ��¼�����û���κα仯��"NOR);
                        else str +=get_string(WHT"��Ϸ��¼���鳬��Ŀǰ���飺"+chinese_number(query("quest/���Ǿ�/combat_exp",me)-query("combat_exp",me))+"��"NOR);
                }
                else str +=get_string(WHT"�����Ϸ��¼���飺"+query("quest/���Ǿ�/combat_exp",me)+"��"NOR);
                str +="\n";
        }

        if(!query("quest/���Ǿ�/ѩ�ȼ���ƪ",me))
        {
                str +=get_string(HBRED"������Ŭ����........"NOR);
                str +=lchj_skill(me);
                return str;
        }
        if(!query("quest/���Ǿ�/ѩ�ȼ���ƪ/over",me))
        {
                if(random(2)) str +=get_string(HBRED"��ʾ�������ڲ��£�Ѱ��ѩ�ȵ��ơ�"NOR);
                else str +=get_string(HBRED"һ��ԩ����һ�����£�һ�ξ��棬һ�α��顣"NOR);
                str +=lchj_skill(me);
                return str;
        }

        str +=get_string(YEL"��Ӷ������ڲ��£�����ѩ�ȵ������ơ�"NOR);

        if(!query("quest/���Ǿ�/���̽��ƪ/over",me))
        {               
                if(random(2)) str +=get_string(HBRED"��һ������̽��ݡ�Ҳ��������Զ����һ���ա�"NOR);
                else          str +=get_string(HBRED"���Ǵ�˵�еľ����书�����ǲƱ�������������Σ�"NOR);
                str +=lchj_skill(me);
                return str;
        }
        str +=get_string(YEL"����̽��ݣ��ҿ�����ԩ�飬Ҳ�����ʫѡ����"NOR);
        if(query("quest/���Ǿ�/���̽��ƪ/baozang",me))
        {
                str +=get_string(YEL"�㷢�����Ǳ��أ����ӵ��ƴ���֪һ�С�"NOR);
                str +=get_string(YEL"��Ȼû������֮�ƣ�����л��ǻ�ò��־��齱����"NOR);
                str +=lchj_skill(me);
                return str;
        }
        str +=lchj_skill(me);
        return str;
}
string lchj_skill(object me)
{
        string str= "";

        if(query("quest/���Ǿ�/ѩ�ȼ���ƪ/start",me))
        {
                str =   "������������������������������������������������������������\n";
                str +=get_string(HIB"�������书��"NOR);
                str +=  "������������������������������������������������������������\n";
                if(query("quest/���Ǿ�/�书/time",me))
                        str +=get_string(WHT"�书��¼ʱ�䣺"+CHINESE_D->chinese_date(query("quest/���Ǿ�/�书/time",me),1)+"��"NOR);
                if(query("quest/���Ǿ�/�书/combat_exp",me))
                {
                        str +=get_string(WHT"�书��¼���飺"+query("quest/���Ǿ�/�书/combat_exp",me)+"��"NOR);
                        str +="\n";
                }
                if(query("quest/���Ǿ�/�书/shenzhao",me)>=2)
                {
                        str +=get_string(HBYEL"��Ӷ���ѧ�����վ������������ʹ�����վ�����"NOR);
                        str +=get_string(HBYEL"���ִӵ��ƴ����һЩ���飬�����վ����Ÿ����ε�����"NOR);
                }       
                else if(query("quest/���Ǿ�/�书/shenzhao",me)==1)
                {
                        str +=get_string(HBYEL"��Ӷ���ѧ�����վ������������ʹ�����վ�����"NOR);
                        if(query("quest/���Ǿ�/ѩ�ȼ���ƪ/over",me))
                        {
                           if(query("quest/���Ǿ�/�书/shenzhao_fail2",me)>=3 && query("registered",me)<3)
                           {
                                   str +=get_string(YEL"������ʧȥ�˴ӵ��ƴ�ѧϰ���վ����߲�ε�������ᡣ"NOR);
                                   str +=get_string(YEL"��Ȼ����������VIP���㽫����µ�������ᡣ"NOR);
                           }
                           else if(query("quest/���Ǿ�/�书/shenzhao_fail2",me) && query("quest/���Ǿ�/�书/shenzhao_fail2",me) <3 && query("registered",me)<3)
                                   str +=get_string(YEL"��ʧȥ�˵��ƴ��������վ���"+chinese_number(query("quest/���Ǿ�/�书/shenzhao_fail2",me))+"�λ��ᣬ���㻹��"+chinese_number(3-query("quest/���Ǿ�/�书/shenzhao_fail2",me))+"���ᡣ"NOR);
                           else if(query("quest/���Ǿ�/�书/shenzhao_fail2",me))
                                   str +=get_string(YEL"��ʧȥ�˵��ƴ��������վ���"+chinese_number(query("quest/���Ǿ�/�书/shenzhao_fail2",me))+"�λ��ᣬ���㻹�����޻��ᡣ"NOR);
                           else str +=get_string(HBRED"������ӵ�дӵ��ƴ�������߲�����վ��Ļ��ᡣ��������ʵ���ʱ����̵��ơ�"NOR);
                   }
                } 
                else if(query("quest/���Ǿ�/�书/shenzhao_fail",me)>=3 && query("registered",me)<3)
                        str +=get_string(YEL"��ʧȥ�Ӷ����������վ��Ļ��ᣬ���������VIP���㽫����µĻ��ᡣ"NOR);
                else if(query("quest/���Ǿ�/�书/shenzhao_fail",me) && query("quest/���Ǿ�/�书/shenzhao_fail",me)<3 && query("registered",me)<3)
                        str +=get_string(YEL"��ʧȥ�Ӷ����������վ���"+chinese_number(query("quest/���Ǿ�/�书/shenzhao_fail",me))+"�λ��ᣬ���㻹��"+chinese_number(3-query("quest/���Ǿ�/�书/shenzhao_fail",me))+"���ᡣ"NOR);
                else if(query("quest/���Ǿ�/�书/shenzhao_fail",me))
                        str +=get_string(YEL"��ʧȥ�Ӷ����������վ���"+chinese_number(query("quest/���Ǿ�/�书/shenzhao_fail",me))+"�λ��ᣬ���㻹�����޻��ᡣ"NOR);
                else str +=get_string(HBRED"������ӵ���������վ��Ļ��ᡣ��������ʵ���ʱ����̶��䡣"NOR);
        
                if(query("quest/���Ǿ�/ѩ�ȼ���ƪ/over",me))
                {
                        if(query("quest/���Ǿ�/�书/sword",me))
                                str +=get_string(HBYEL"��ӵ���ѧϰ����ʬ�����������������־�����"NOR);
                        else if(query("quest/���Ǿ�/�书/sword_fail",me)>=3 && query("registered",me)<3)
                        {
                                str +=get_string(YEL"������ʧȥѧϰ�ӵ��ƴ���ʬ�����Ļ��ᡣ\n"NOR);
                                str +=get_string(YEL"��Ȼ����������VIP���㽫����µ�������ᡣ"NOR);
                        }
                        else if(query("quest/���Ǿ�/�书/sword_fail",me) && query("quest/���Ǿ�/�书/sword_fail",me) <3 && query("registered",me)<3)
                                str +=get_string(YEL"��ʧȥѧϰ��ʬ������"+chinese_number(query("quest/���Ǿ�/�书/sword_fail",me))+"�λ��ᣬ���㻹��"+chinese_number(3-query("quest/���Ǿ�/�书/sword_fail",me))+"���ᡣ"NOR);
                        else if(query("quest/���Ǿ�/�书/sword_fail",me))
                                str +=get_string(YEL"��ʧȥѧϰ��ʬ������"+chinese_number(query("quest/���Ǿ�/�书/sword_fail",me))+"�λ��ᣬ���㻹�����޻��ᡣ"NOR);
                        else str +=get_string(HBRED"������ӵ��ѧϰ��ʬ�����Ļ��ᡣ��������ʵ���ʱ����̵��ơ�"NOR);
                }
        }
        return str;
}
string quest_tlbb(object me)
{
        string str= "\n";

        if(!query("quest/�����˲�",me))
        {
                str =    "������������������������������������������������������������\n";
                str +=get_string(HIW"��Ŀǰ���������˲���û���κμ�¼��"NOR);
                return str;
        }

        str =   "������������������������������������������������������������\n";
        str +=get_string(HIW"�������˲���"NOR);
        str +=  "������������������������������������������������������������\n";

        if(query("quest/�����˲�/time",me))
        {
                if(!query("quest/�����˲�/��������ƪ/over",me) && !query("quest/�����˲�/���ɾ�Ԯƪ/over",me))
                        str +=get_string(WHT"��Ϸ��¼ʱ��"+CHINESE_D->chinese_time(time()-query("quest/�����˲�/time",me))+"��"NOR);
                else str +=get_string(WHT"��Ϸ��¼ʱ�䣺"+CHINESE_D->chinese_date(query("quest/�����˲�/time",me),1)+"��"NOR);
        }
        if(query("quest/�����˲�/combat_exp",me))
        {
                if(!query("quest/�����˲�/��������ƪ/over",me) && !query("quest/�����˲�/���ɾ�Ԯƪ/over",me))
                {
                        if(query("combat_exp",me)> query("quest/�����˲�/combat_exp",me))
                                str +=get_string(WHT"��Ϸ��¼����"+chinese_number(query("combat_exp",me)-query("quest/�����˲�/combat_exp",me))+"��"NOR);
                        else if(query("combat_exp",me)== query("quest/�����˲�/combat_exp",me))
                                str +=get_string(WHT"��Ϸ��¼�����û���κα仯��"NOR);
                        else str +=get_string(WHT"��Ϸ��¼���鳬��Ŀǰ���飺"+chinese_number(query("quest/�����˲�/combat_exp",me)-query("combat_exp",me))+"��"NOR);
                }
                else str +=get_string(WHT"�����Ϸ��¼���飺"+query("quest/�����˲�/combat_exp",me)+"��"NOR);
                str +="\n";
        }

        if(!query("quest/�����˲�/�貨΢��ƪ",me))
        {
                str +=get_string(HBRED"������Ŭ����........"NOR);
                str +=tlbb_skill(me);
                return str;
        }
        if(!query("quest/�����˲�/�貨΢��ƪ/over",me))
        {
                if(!query("quest/�����˲�/�貨΢��ƪ/wuliangover",me))
                {
                        if(random(2)) str +=get_string(HBRED"���Ѱ�Ҷ�������˵������ɽ������̽���С�"NOR);
                        else str +=get_string(HBRED"Ѱ��ʧ�ٵĶ����У�ע��������������貨΢���ͱ����񹦡�"NOR);
                }
                else
                {
                        if(random(2)) str +=get_string(HBRED"������ɽ�����Ķ���ȴ���ٳֵ���ٹȡ�����̽���С�"NOR);
                        else str +=get_string(HBRED"Ѱ��ʧ�ٵĶ����У�ע��С���и�����ء�"NOR);
                }
                return str;
        }

        str +=get_string(YEL"���Ѿ�����������ٹȾȻأ������һЩ������"NOR);

        if(!query("quest/�����˲�/����Ӫ��ƪ/over",me))
        {               
                if(random(2)) str +=get_string(HBRED"��һ���������´�ս����ù�Ķ�����ǣ�����У���Ȼֻ��������æ��"NOR);
                else          str +=get_string(HBRED"���ĵ�һ�𷨸�ɮ���书Ҳ����ɲ⣬����ֹ����ֻ�����ˡ�"NOR);
                str +=tlbb_skill(me);
                return str;
        }

        str +=get_string(YEL"������ָ����ڵ��⣬�ȶ��������ģ������һЩ������"NOR);

        if(!query("quest/�����˲�/��������ƪ/over",me))
        {
                if(random(2)) str +=get_string(HBRED"˭��С�ˣ�˭��Ӣ�ۣ���ԭ���£������������ܱ�����"NOR);
                else          str +=get_string(HBRED"���־��䣬����ׯ��ս����Ħ���Ż꣬��ʷ��������..."NOR);
                str +=tlbb_skill(me);
                return str;
        }
        str +=get_string(YEL"����ׯ������������ɹ������ֳ���"NOR);
        str +=get_string(YEL"��Ħ�£���ɹ��ҿ��±���������ܡ�"NOR);
        if(query("quest/�����˲�/��������ƪ/good",me))
                str +=get_string(YEL"����ǳɹ�˵�������������������ò��ֽ�����"NOR);
        if(query("quest/�����˲�/��������ƪ/bad",me))
                str +=get_string(YEL"����ǳɹ��˻��������������壬��ò��ֽ�����"NOR);

        if(query("quest/�����˲�/��������ƪ/start",me))
        {
                if(!query("quest/�����˲�/��������ƪ/over",me))
                        str +=get_string(HBRED"Ϊ�������֣�����Ľ�ݣ������ϣ��Ͼ����ǵÿ�ȭͷ�ġ�"NOR);
                else 
                        str +=get_string(YEL"��������ִ��Ⱥؤ������������ɮ���������֣�Ϊ���µ�һ��"NOR);
                str +=tlbb_skill(me);
                return str;
        }
        if(query("quest/�����˲�/���ɾ�Ԯƪ/start",me))
        {
                if(!query("quest/�����˲�/���ɾ�Ԯƪ/over",me))
                        str +=get_string(HBRED"����Ϊ�������룬�Ĳ�ս�������˵�Ҫ�ȵġ�ֻ��Σ�����ء�"NOR);
                else 
                        str +=get_string(YEL"����ʤ��ԭȺ�ۣ���Ǳ����ɣ��ɹ�Ӫ�����壬Ϊ������ܡ�"NOR);
                str +=tlbb_skill(me);
                return str;
        }
        str +=tlbb_skill(me);
        return str;
}
string tlbb_skill(object me)
{
        string str= "";

        if(query("quest/�����˲�/�书", me))
        {
                str =   "������������������������������������������������������������\n";
                str +=get_string(HIC"�������书��"NOR);
                str +=  "������������������������������������������������������������\n";
                if(query("quest/�����˲�/�书/time",me))
                        str +=get_string(WHT"���ѧϰ��¼ʱ�䣺"+CHINESE_D->chinese_date(query("quest/�����˲�/�书/time",me),1)+"��"NOR);
                if(query("quest/�����˲�/�书/combat_exp",me))
                {
                        str +=get_string(WHT"���ѧϰ��¼���飺"+query("quest/�����˲�/�书/combat_exp",me)+"��"NOR);
                        str +="\n";
                }
                if(query("quest/�����˲�/�书/yuxiang",me))
                {            
                        if(query("quest/�����˲�/�貨΢��ƪ/over",me))
                                str +=get_string(YEL"���ҵ�MM�����񣬲����һЩ��ʾ�����ü����貨΢���Ĳ�����"NOR);
                        else
                                str +=get_string(YEL"���ҵ�MM�����񣬲����һЩ��ʾ��"NOR);
                }
                if(query("quest/�����˲�/��ڤ��/pass",me))
                        str +=get_string(HBYEL"������ɽ�������Ѿ�ѧ���˱�ڤ�񹦾�ѧ��"NOR);
                else if(query("quest/�����˲�/��ڤ��/fail",me)>=3 && query("registered",me)<3)
                {
                        str +=get_string(YEL"�������˷���ѧϰ��ڤ�񹦵Ļ��ᡣ"NOR);
                        str +=get_string(YEL"��Ȼ����������VIP���㽫����µ�������ᡣ"NOR);
                }
                else if(query("quest/�����˲�/��ڤ��/fail",me))
                {
                        str +=get_string(YEL"������ʧȥ��ѧϰ��ڤ�񹦵�"+chinese_number(query("quest/�����˲�/��ڤ��/fail",me))+"�λ��ᡣ"NOR);
                        str +=get_string(YEL"���㻹�л���ѧϰ���µĲ������Դ��������»�á�"NOR);
                }
                else str +=get_string(HBRED"������ӵ��ѧϰ��ڤ�񹦵Ļ��ᡣ"NOR);
        
                if(query("quest/�����˲�/�书/pass",me))
                        str +=get_string(HBYEL"�������Ѿ�ѧ�����貨΢����"NOR);
                else if(query("quest/�����˲�/�书/fail",me)>=3 && query("registered",me)<3)
                {
                        str +=get_string(YEL"�������˷���ѧϰ�貨΢���Ļ��ᡣ"NOR);
                        str +=get_string(YEL"��Ȼ����������VIP���㽫����µ�������ᡣ"NOR);
                }
                else if(query("quest/�����˲�/�书/fail",me))
                {
                        str +=get_string(YEL"������ʧȥ��ѧϰ�貨΢����"+chinese_number(query("quest/�����˲�/�书/fail",me))+"�λ��ᡣ"NOR);
                        str +=get_string(YEL"���㻹�л���ѧϰ���µĲ������Դ��������»�á�"NOR);
                }
                else str +=get_string(HBRED"������ӵ��ѧϰ�貨΢���Ļ��ᡣ"NOR);
        }
        if(query("quest/tonglao/quest",me))
        {
                if(query("quest/tonglao/pass",me))
                        str +=get_string(YEL"����"+chinese_number(query("quest/tonglao/quest",me))+"�μ�����ɽ�ƻ�ż����ɽͯ�ѣ���ѧ�������书��"NOR);
                else if(query("quest/tonglao/second",me))
                        str +=get_string(YEL"����"+chinese_number(query("quest/tonglao/quest",me))+"�μ�����ɽ�ƻ�ż����ɽͯ�ѡ�"NOR); 
                else str +=get_string(YEL"����"+chinese_number(query("quest/tonglao/quest",me))+"�μ�����ɽ�ƻ𣬵�ʲôҲû���֡�"NOR);
        }

        if(query("quest/�����˲�/�书/quanli",me))
                str +=get_string(HBYEL"��������������򵽡���豹��桱���书���С�"NOR);
        return str;
}

string quest_shediao(object me)
{
        string str= "\n";

        if(!me->query("quest/���Ӣ�۴�"))
        {
                str =    "������������������������������������������������������������\n";
                str +=get_string(HIW"��Ŀǰ�������Ӣ�۴���û���κμ�¼��"NOR);
                return str;
        }

        str =   "������������������������������������������������������������\n";
        str +=get_string(HIW"�����Ӣ�۴���"NOR);
        str +=  "������������������������������������������������������������\n";

        if(query("quest/���Ӣ�۴�/time",me))
        {
                if(!query("quest/���Ӣ�۴�/��ѩ����/over",me) )
                        str +=get_string(WHT"��Ϸ��¼ʱ��"+CHINESE_D->chinese_time(time()-query("quest/���Ӣ�۴�/time",me))+"��"NOR);
                else str +=get_string(WHT"��Ϸ��¼ʱ�䣺"+CHINESE_D->chinese_date(query("quest/���Ӣ�۴�/time",me),1)+"��"NOR);
        }
        if(query("quest/���Ӣ�۴�/combat_exp",me))
        {
                if(!query("quest/���Ӣ�۴�/��ѩ����/over",me) )
                {
                        if(query("combat_exp",me)> query("quest/���Ӣ�۴�/combat_exp",me))
                                str +=get_string(WHT"��Ϸ��¼����"+chinese_number(query("combat_exp",me)-query("quest/���Ӣ�۴�/combat_exp",me))+"��"NOR);
                        else if(query("combat_exp",me)== query("quest/���Ӣ�۴�/combat_exp",me))
                                str +=get_string(WHT"��Ϸ��¼�����û���κα仯��"NOR);
                        else str +=get_string(WHT"��Ϸ��¼���鳬��Ŀǰ���飺"+chinese_number(query("quest/���Ӣ�۴�/combat_exp",me)-query("combat_exp",me))+"��"NOR);
                                str +=get_string(HIC"���Ѿ��ɹ����������ġ���Х����λ�����������һЩ������"NOR);
                }
                else str +=get_string(WHT"�����Ϸ��¼���飺"+query("quest/���Ӣ�۴�/combat_exp",me)+"��"NOR);
                str +="\n";
        }
        else
        {

        }

        str +=shediao_skill(me);
        return str;
}

string shediao_skill(object me)
{
        string str= "";

        if(query("quest/���Ӣ�۴�/yangjiaqiang",me))
        {
                str =   "������������������������������������������������������������\n";
                str +=get_string(HIC"������书��"NOR);
                str +=  "������������������������������������������������������������\n";
                if(query("quest/���Ӣ�۴�/yangjiaqiang/time",me))
                        str +=get_string(WHT"���ѧϰ��¼ʱ�䣺"+CHINESE_D->chinese_date(query("quest/���Ӣ�۴�/yangjiaqiang/time",me),1)+"��"NOR);
                if(query("quest/���Ӣ�۴�/yangjiaqiang/combat_exp",me))
                {
                        str +=get_string(WHT"���ѧϰ��¼���飺"+query("quest/���Ӣ�۴�/yangjiaqiang/combat_exp",me)+"��"NOR);
                        str +="\n";
                }
                if(query("quest/���Ӣ�۴�/��ѩ����/over",me))
                {            
                                str +=get_string(YEL"��ɹ���Ԯ��Х�졢���������ң������һЩ������"NOR);
                }
                if(query("quest/���Ӣ�۴�/yangjiaqiang/pass",me))
                        str +=get_string(HBYEL"�������Ѿ�ѧ�������ǹ��"NOR);
                else if(query("quest/���Ӣ�۴�/yangjiaqiang/fail",me)>=3 && query("registered",me)<3)
                {
                        str +=get_string(YEL"�������˷���ѧϰ���ǹ�Ļ��ᡣ"NOR);
                        str +=get_string(YEL"��Ȼ����������VIP���㽫����µ�ѧϰ���ᡣ"NOR);
                }
                else if(query("quest/���Ӣ�۴�/yangjiaqiang/fail",me))
                {
                        str +=get_string(YEL"������ʧȥ��ѧϰ���ǹ��"+chinese_number(query("quest/���Ӣ�۴�/yangjiaqiang/fail",me))+"�λ��ᡣ"NOR);
                        str +=get_string(YEL"���㻹�л���ѧϰ�����ʵ���ʱ�����ȥѰ����������̡�"NOR);
                }
                else str +=get_string(HBRED"������ӵ��ѧϰ���ǹ�Ļ��ᡣ"NOR);
        }
        if(query("quest/jiuyin1/pass",me))
                str +=get_string(HBYEL"����ܲ�ͨ��������������¾����澭�Ͼ���"NOR);
        if(query("quest/jiuyin2/pass",me))
                str +=get_string(HBYEL"��ӳ����紦����˳������������澭�¾���"NOR);
        return str;
}

string quest_tulong(object me)
{
        string str= "";
        return str;
}

string tulong_skill(object me)
{
        string str= "";
        return str;
}

string get_string(string str)
{
        return sprintf("%|60s",str)+"\n";
}
int help(object me)
{
        write("
������������������������������������������������������������
             ָ���ʽ : "+YEL"story <......>"NOR"
������������������������������������������������������������
"HIW"���������������������˽���story�Ѿ��ҿ��ĳ̶ȡ���Ҳ����ʹ
���������õ�һ����һ������ʾ��"NOR"
������������������������������������������������������������"YEL"
                story  ������м�¼
          story feihu  ���ѩɽ�ɺ���¼
           story tlbb  ��������˲���¼
           story lchj  ������Ǿ���¼
         story tulong  �������������¼
         story <���>  ��ʦר�ò�ѯ����
 story ...<form ���>  ��ʦר�ò�ѯ����"NOR"
������������������������������������������������������������
"HIC"Ŀǰֻ����ѩɽ�ɺ��������˲������Ǿ������Ӣ�۴������������ǡ�"NOR"
������������������������������������������������������������
                  \n"NOR);
return 1;
}