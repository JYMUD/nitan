// master.c

#include <ansi.h>
#include <login.h>

string *all_basic= ({
        "array",        "axe",                  "blade",        "claw",         "club",
        "cuff",         "dagger",               "dodge",        "finger",       "force",
        "hammer",       "hand",                 "hook",         "leg",          "magic",
        "parry",        "spear",                "staff",        "stick",        "strike",
        "sword",        "throwing",             "unarmed",      "whip",
});

int is_master() { return 1; }
int can_learn_from() { return 1; }
int query_auto_perform() { return 2; }

int prevent_learn(object me, string skill)
{
        mapping fam;

        if( !me->is_apprentice_of(this_object()) &&
            mapp(fam = query("family", me)) &&
            fam["family_name"] == query("family/family_name") &&
            fam["generation"] > query("family/generation") ) {
                command("say ��Ȼ���������µĵ��ӣ����ǲ����ҵĵմ���"
                        "��... ����ȥ����ʦ��ѧ�ɡ�");
                return 1;
        }

        return 0;
}

void attempt_detach(object me)
{
        string *fams;

        if( !me->is_apprentice_of(this_object()) ) {
                 command("say ��ȥ������ʦ����");
                return;
        }

        command("sigh");

        // һת��ֻ������ʧ����һ��
        fams = query("reborn/fams", me);
        if( !arrayp(fams) || member_array(query("family/family_name", me), fams) == -1 )
        {
                command("say �߰��߰ɣ����߰ɣ�����ѧ�����书���£�");

                if( me->query_family() == "�һ���" )
                        set("combat_exp", query("combat_exp", me) / 3, me);
                me->skill_expell_penalty();
                me->unconcious();

                message_vision("$N������ճ��$n�ı��������"
                               "��֪����˵Щʲô��\n", this_object(), me);
                addn("detach/"+query("family/family_name", me), 1, me);
        }
        command("say �߰��߰ɣ������ڿ����߰ɣ�");
        delete("family", me);
        delete("quest", me);
        delete("quest_count", me);
        set("title", "��ͨ����", me);
        me->save();
}


nomask void master_accept_kill(object me)
{
        object *inv;

        inv = all_inventory(environment());
        for(int i = 0; i < sizeof(inv); i++) {
                if( !inv[i]->is_character()
                ||  !living(inv[i])
                ||  inv[i] == this_object()
                ||  inv[i] == me
                ||  playerp(inv[i])
                ||  !inv[i]->query_family()
                ||  inv[i]->query_family() != this_object()->query_family() )
                        continue;
                else
                {
                        message_vision(sprintf("$N��$n�ź���������%s�����ǻ�Ĳ��ͷ��ˣ�����\n\n",
                                (me->is_apprentice_of(this_object()))?
                                "������ʦ����":((query("family/family_name", me) == query("family/family_name"))?
                                "��ͬ��ʦ����Ҫɱ":"�Ҷ�����ʦ��" )),inv[i],me );
                        inv[i]->kill_ob(me);
                        me->kill_ob(inv[i]);
                }
        }
        return;
}

public mixed teach_perform(object me, object master, mapping args)
{
        string family,name,perform,msg,msg1,msg2;
        string sk1, sk2, sk3, sk4       ;
        int lv1, lv2, lv3, lv4          ;
        int i,free,gongxian,shen,force,neili;

        // ����Ҫ�����������书��������������������Ӣ����
        if( !stringp(name = args["name"])
        ||  !stringp(perform = args["perform"])
        ||  !stringp(sk1 = args["sk1"])
          )
                return 0;

        // �ж��������ɣ���Ϊ�������ڣ�Ӧ��� free ����
        if( !intp(free = args["free"]) || free <= 0 ) {
                family = query("family/family_name", master);

                if( query("family/family_name", me) != family )
                        return RANK_D->query_respect(me) + "����" +
                               family + "����ԨԴ����֪�˻��Ӻ�˵��";
        }

        // ����Ѿ�ѧ�ᣬ�򷵻�
        if( query("can_perform/"+sk1+"/"+perform, me) )
                return "�����㲻���Ѿ�����ô������������ʲô��";

        //�ж���
        if( intp(shen = args["shen"]) ) {
                if( shen < 0 && query("shen", me) > shen )
                        return "�ߣ������������Ĵ�����֮�������ܸɳ�ʲô���£�";
                if( shen > 0 && query("shen", me) < shen )
                        return "��Ŀǰ�������������²�����������ʱ�����ܴ��㡣";
        }

        // �ж����ɹ��׵�Ҫ��
        if( intp(gongxian = args["gongxian"])
        &&  query("family/gongji", me) < gongxian)
                return "�㻹�Ƕ�Ϊ������һЩ���������ɡ�";

        // �ж��ض����书�������� sk1 ӦΪ�� skills
        if( !me->query_skill(sk1, 1) )
                return "����" + to_chinese(sk1) + "��ûѧ��������ʲô���У�";

        if( intp(lv1= args["lv1"]) && me->query_skill(sk1, 1) < lv1 )
                return "���" + to_chinese(sk1) + "��ûѧ���ң�ȥ�����������ɡ�";

        if( stringp(sk2 = args["sk2"]) && intp(lv2 = args["lv2"]) && me->query_skill(sk2,1) < lv2 )
                return "���" + to_chinese(sk2) + "��û�е��ң�ȥ�����������ɡ�";

        if( stringp(sk3 = args["sk3"]) && intp(lv3 = args["lv3"]) && me->query_skill(sk3,1) < lv3 )
                return "���" + to_chinese(sk3) + "��û���ң�ȥ�����������ɡ�";

        if( stringp(sk2 = args["sk4"]) && intp(lv2 = args["lv4"]) && me->query_skill(sk4,1) < lv4 )
                return "���" + to_chinese(sk4) + "��û���ң�ȥ�����������ɡ�";

        // �жϾ��ж��ڹ���Ҫ��
        if( intp(force = args["force"]) && me->query_skill("force") < force )
                return "��Ļ����ڹ���򻹲������������������ɡ�";

        // �жϾ��ж��������޵�Ҫ��
        if( intp(neili = args["neili"]) && query("max_neili", me) < neili )
                return "���������Ϊ��������ѧ�������У�";

        // ����ѧϰ���е�������Ϣ
        if( stringp(msg1 = args["msg1"]) ) {
                msg = msg1;
        } else {
                switch (random(4))
                {
                case 0 :
                        msg = "$N΢΢���˵�ͷ�����ֽ�$n" HIY "��"
                              "����ǰ��������$n" HIY "���Ͻ�����"
                              "���죬����ʱ���ֱȻ���ʾ��ʲô����"
                              "��ȫ��" + to_chinese(sk1) + "�ľ�"
                              "΢Ҫ�衣$n" HIY "�������һЦ����"
                              "����$N�Ľ̵���������";
                        break;

                case 1 :
                        msg = "$N������$n" HIY "��ã�����΢΢��"
                              "�˵�ͷ��˵�������Ҹ�����ʾһ�飬��"
                              "������ˡ���$N�������䣬�漴�����"
                              "���������ƣ���������ʾ��" +
                              to_chinese(sk1) + "����ʽ��$n" HIY
                              "ֻ��$N��ʽ���棬����Ƿ���ʵ��ǰ��"
                              "δ�ţ���ʱ���и���";
                        break;

                case 2 :
                        msg = "$N���˿�$n" HIY "����Ϊ�����˵��"
                              "�����벻�����" + to_chinese(sk1) +
                              "��չ������٣��Ѵ�˰㾳�硣���ף�"
                              "���ס������ұ㴫�����У��ɼ������"
                              "����˵��$N�㽫$n" HIY "������ǰ��"
                              "���Ľ���" + name + "����ྫҪ��$n"
                              HIY "һ����һ�߲�ס�ĵ�ͷ��";
                        break;

                default :
                        msg = "$N����һЦ����$n" HIY "�޵�������"
                              "����������������" +
                              to_chinese(sk1) + "�����裬�ұ㴫��"
                              "��" + name + "���кη�����˵���ֻ"
                              "��$N�ӻ�������һ����Ϊ�žɵ�С����"
                              "��ָ������һ�ζ�$n" HIY "��ϸ����"
                              "��$n" HIY "�����˼���ã���������";
                        break;
                }
        }
        message_vision(HIY "\n" + msg + "\n\n" NOR, master, me);

        // ѧ��������
        addn("can_perform/"+sk1+"/"+perform, 1, me);

        // ������ʾ��Ϣ
        tell_object(me, HIC "��ѧ���ˡ�" HIW + name +
                         HIC "����\n" NOR);

        // �������Ӧ���书����
        if( stringp(sk1) ) me->improve_skill(sk1, 500000);
        if( stringp(sk2) ) me->improve_skill(sk2, 500000);
        if( stringp(sk3) ) me->improve_skill(sk3, 500000);
        if( stringp(sk4) ) me->improve_skill(sk4, 500000);


        // ������ skill �Ļ�������
        for (i = 0; i < sizeof(all_basic); i++) {
                if( SKILL_D(sk1)->valid_enable(all_basic[i]) )
                        me->improve_skill(all_basic[i], 500000);
        }

        // �������ɹ���ֵ
        if( intp(gongxian) && gongxian > 0 )
                addn("family/gongji", -gongxian, me);
        // ���Ļش���Ϣ
        if( stringp(msg2 = args["msg2"]) ) {
                msg = msg2;
        } else {
                // ���Ļش���Ϣ
                switch (random(5))
                {
                case 0 :
                        msg = "�ղŵ���ʽ���������˶��٣�";
                        break;
                case 1 :
                        msg = "��ʽ������ˣ����Լ���ȥ����ɡ�";
                        break;
                case 2 :
                        msg = "�ղ��������ڵ�ȫ�Ǹ��еľ��⣬�ɼ����ˡ�";
                        break;
                case 3 :
                        msg = "��������ȥ�����ڼ���ϰ�������������硣";
                        break;
                default :
                        msg = "������ʵ�������ӣ����Լ���ȥ��ϰ�ɡ�";
                        break;
                }
        }
        return msg;
}
/* ����
string ask_skill2(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                                "perform"       : "fugu",               //pfm�Ĵ���������
                                "name"          : "���ǲ���",           //pfm������
                                "sk1"           : "jinshe-zhang",       //��Ҫ���书��id
                                "lv1"           : 100,                  //��Ҫ���书�ĵȼ�
                                "sk2"           : "strike",             //��Ҫ�书sk2��id
                                "lv2"           : 100,                  //��Ҫ�书sk2 �ĵȼ�
//                              "sk3"           : "throwing",           //�书sk3
//                              "lv3"           : 100,
//                              "sk4"           : "throwing",           //�书sk4
//                              "lv4"           : 100,
                                "neili"         : 300,                  //��Ҫ��������
                                "free"          : 1,                    //free=1����Ҫͬһ����
//                              "shen"          : 100,                  //��Ҫ��shen
//                              "msg1"          : "�̵�����",
//                              "msg2"          : "���������",

                                                                                                                                ]));
}
*/
