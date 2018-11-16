// actionavailable.c

#include <ansi.h>
#include <weapon.h>
#include <login.h>
inherit F_CLEAN_UP;

int room_path(object, object);
int user_path(object, object);

int main(object me, string arg)
{
        object ob, *inv;
        string win,*ids;

        if (! arg || sscanf(arg, "%s,%s", arg, win) != 2)
                return 0;

        switch (win)
        {
                case "0" :
                        ob=present(arg,environment(me));
                        if(!objectp(ob)) {
                                inv=all_inventory(environment(me));
                                for(int i = 0; i<sizeof(inv); i++) {
                                        if(inv[i]==me) continue;
                                        if( ids=query_temp("apply/id", inv[i]) )
                                        for(int j=0;j<sizeof(ids);j++) {
                                                if(ids[j]==arg)
                                                ob=inv[i];
                                        }
                                }
                        }
                        room_path(me,ob);
                        break;
                case "1" :
                        ob=present(arg,me);
                        user_path(me,ob);
                        break;
        }
        return 1;
}

int room_path(object me, object ob)
{
        mapping skills,meskills;
        object *inv;
        string *str,*ids;
        string id,name,tmp;
        int i,my_skill;

        if(!objectp(ob)) return 1;

        if(stringp(tmp=ob->query_menu(me,0)))//��������ܽ��Ͳ˵�����ֱ�ӷ��ز˵�
        {
                write(tmp);
                return 1;
        }


        if( !query("apply/id", ob))id=query("id", ob);
        else {
                ids=query_temp("apply/id", ob);
                id=ids[sizeof(ids)-1];
        }

//      if(ob->query_temp("apply/name")) name=ob->query_temp("apply/name");
        tmp=TMI("mbegin "+ob->name(1)+";"+id)+TMI("mitem �۲�$U;look "+id);
        if(living(ob))
        {
                if(interactive(ob))
                {
                        tmp+=TMI("mitem ����$U...;tell "+id+" ...")+TMI("mitem ��$U����...;whisper "+id+" ...");
                        if( id == query_temp("reply", me) )
                                write(TMI("mitem �ش�$U...;reply ..."));
                }
                if( query("ridable", ob) )
                {
                        tmp+=TMI("mitem ����$U;ride "+id);
                }

                tmp+=(me->query_leader()==ob)?TMI("mitem ֹͣ����$U;follow none"):TMI("mitem ����$U;follow "+id);
                if( !query("no_fight", environment(me)) )
                {
                        tmp+=TMI("mitem ��$U�д�;fight "+id);
                        if( query("age", ob)>17 || !interactive(ob) )
                                tmp+=TMI("mitem ����$U;hit "+id)+TMI("mitem ɱ��$U;kill "+id)+TMI("mitem ͵Ϯ$U;touxi "+id)+TMI("mitem ͵$U��...;steal ... from "+id);
                }
                if( query("inquiry", ob)){
                        str=keys(query("inquiry", ob));
                        for(i=0; i<sizeof(str); i++)
                                tmp+=TMI("mitem ��$U��������"+str[i]+"����Ϣ;ask "+id+" about "+str[i]+"");
                }
                tmp+=TMI("mitem ��$U...����;give ... to "+id );
                if( query("owner", ob) == query("id", me) )
                {

                        if( query("magic/become", ob) )
                        {
                                if( query_temp("is_changing", me) )
                                {
                                        tmp+=TMI("mitem ���-->�������� ;recall recover "+id+"");
                                }
                                else
                                {
                                        tmp+=TMI("mitem ����-->�������� ;recall change "+id+"");
                                }

                        }
                        if( query("magic/owner", ob) )
                        {
                                tmp+=TMI("mitem ����-->��$U�� ;upgrade "+id+"");

                        }
                        // tmp+=TMI("mitem �̵�-->��$U�� ;teach "+"...");
                        // tmp+=TMI("mitem ����-->��$U�� ;skills "+id+"");
                }
                if( query("family/family_name", me) == "ؤ��"){
                        if ( me->query_skill("checking",1) >= 10 )
                                tmp+=TMI("mitem ��̽...�ļ���;check ...");
                        if( query("family/family_name", ob) != "ؤ��" )
                                tmp+=TMI("mitem ����$U��...;beg ... from "+id);
                }
                if( query("vendor_goods", ob)){
                        tmp+=TMI("mitem ��ѯ$U���۵Ķ���;list "+id+"");
                        tmp+=TMI("mitem ��$U��...;buy ...");
                }
                if( query("dealer", ob) == "pawn"){
                        if( !query("vendor_goods", ob)){
                                tmp+=TMI("mitem ��ѯ$U���۵Ķ���;list");
                                tmp+=TMI("mitem ��$U��...;buy ...");
                        }
                        tmp+=TMI("mitem ����...;value ...");
                        tmp+=TMI("mitem ��...��$U;sell ...");
                        tmp+=TMI("mitem �䵱...��$U;pawn ...");
                        if( query("pawns", me) )
                                tmp+=TMI("mitem �����Ʒ...;redeem ...");
                }
                if( query("dealer", ob) == "bank"){
                        tmp+=TMI("mitem �һ�����;convert ...");
                        tmp+=TMI("mitem ��Ǯ;deposit ...");
                        if( query("balance", me)){
                                tmp+=TMI("mitem ��ѯ���;check");
                                tmp+=TMI("mitem ȡǮ;withdraw ...");
                        }
                }
                if( query("family/master_name", me) != ob->name(1)){
                        if(ob->is_master())
                                tmp+=TMI("mitem ��$UΪʦ;bai "+id);
                } else {
                        tmp+=TMI("mitem ��ʦ��$U��ͷ;bai "+id);
                        tmp+=TMI("mitem ��ѯʦ��$U����;skills "+id);
                        if( ob->query_skills() && query("jing", me) >= 1
                                 && query("potential", me)>query("learned_points", me)){
                                skills=ob->query_skills();
                                str=keys(skills);
                                for(i=0; i<sizeof(str); i++) {
                                        if(me->query_skills()) {
                                                meskills=me->query_skills();
                                                my_skill = me->query_skill(str[i], 1);
                                                if( (string)SKILL_D(str[i])->type()=="martial"
                                                         && my_skill*my_skill*my_skill/10>query("combat_exp", me) )
                                                        continue;
                                                if(skills[str[i]]>my_skill && str[i]!="idle")
                                                        tmp+=TMI("mitem ѧϰ"+to_chinese(str[i])+";learn "+id+" "+str[i]+" ...");
                                        } else
                                        tmp+=TMI("mitem ѧϰ"+to_chinese(str[i])+";learn "+id+" "+str[i]+" ...");
                                }
                        }
                }
        } else {
                if( !query("no_get", ob) )
                        tmp+=TMI("mitem ��$U������;get "+id);
                if(ob->is_container()) {
                        inv = all_inventory(ob);
                        if(sizeof(inv)) {
                                tmp+=TMI("mitem ��$U��Ķ������ó���;get all from "+id);
                                tmp+=TMI("mitem ��$U���ó�...;get ... from "+id);
                        }
                        tmp+=TMI("mitem ��...װ��$U��;put ... in "+id);
                }
                if(id=="board") {
                        tmp+=TMI("mitem ���µ�����;read new");
                        tmp+=TMI("mitem ����...������;read ...");
                        tmp+=TMI("mitem д�µ�����;post ...");
                        tmp+=TMI("mitem ɾ������...;discard ...");
                }
        }
        tmp+=TMI("mendd");
        tell_object(me,tmp);
        return 1;
}

int user_path(object me, object ob)
{
        mapping prop;
        string id,tmp;

        if(!objectp(ob)) return 1;

        if(stringp(tmp=ob->query_menu(me,1)))//��������ܽ��Ͳ˵�����ֱ�ӷ��ز˵�
        {
                write(tmp);
                return 1;
        }

        id=query("id", ob);
        tmp=TMI("mbegin "+ob->name(1)+";"+id)+TMI("mitem �۲�$U;look "+id);

        if( !query("no_drop", ob) )
                tmp+=TMI("mitem ����$U;drop "+id);

        if( !query("no_give", ob) )
                tmp+=TMI("mitem ��$U��...;give "+id+" to ...");

        if( query("ridable", ob) && query_temp("is_rided_by", ob) == me && 
           query_temp("is_riding", me) == ob )
        {
                tmp+=TMI("mitem ����$U;unride "+id);
        }

        if( query("liquid", ob)){
                if( query("liquid/remaining", ob) )
                        tmp+=TMI("mitem ��$U;drink "+id);
                if( query("resource/water", environment(me)) )
                        tmp+=TMI("mitem ��$Uװ��ˮ;fill "+id);
        }

        if( query("food_remaining", ob) )
                tmp+=TMI("mitem ��$U;eat "+id);

        if(ob->is_container()) {
                tmp+=TMI("mitem ��$U��Ķ������ó���;get all from "+id);
                tmp+=TMI("mitem ��$U���ó�...;get ... from "+id);
                tmp+=TMI("mitem ��...װ��$U��;put ... in "+id);
        }
        if(mapp(prop=query("armor_prop",ob)) && stringp(query("armor_type", ob)) ) {
                if( !query("equipped", ob) )
                        tmp+=TMI("mitem ����$U;wear "+id);
                else
                        tmp+=TMI("mitem ����$U;remove "+id);
        }

        if(mapp(prop=query("weapon_prop", ob)) && stringp(query("skill_type", ob))) {
                if( !query("equipped", ob) )
                        tmp+=TMI("mitem װ��$U;wield "+id);
                else
                        tmp+=TMI("mitem ���װ��$U;unwield "+id);
        }

        if( query("skill", ob) )
                tmp+=TMI("mitem ��$U;study "+id);

        // "���޵�ʹ���б�
        if(id=="shou shao")
        {
                if( query("can_whistle", me) )
                {
                        string *huanshou_str;

                        huanshou_str=keys(query("can_whistle", me));
                        if( query_temp("pet_id", me) )
                        {
                                tmp+=TMI("mitem ��ʹ�������� ;attack "+"...");
                                tmp+=TMI("mitem ֹͣ�������� ;stop "+huanshou_str[0]+"");
                                tmp+=TMI("mitem �鿴�����ޡ� ;shape "+huanshou_str[0]+"");
                                tmp+=TMI("mitem �ٻء����ޡ� ;whistle "+huanshou_str[0]+"");
                        }
                        else
                        {
                                tmp+=TMI("mitem �ٻ������ޡ� ;whistle "+huanshou_str[0]+"");
                        }
                                // tmp+=TMI("mitem ���������ޡ� ;modify "+huanshou_str[0]+"");
                        if( query_temp("beastdied", me) )
                        {
                                tmp+=TMI("mitem ������ޡ� ;recall reborn "+huanshou_str[0]+"");
                        }
                }
        }
        //��ҩʹ�ü�ǿ
        if( query("poison_type", ob) == "poison" )
        {
                if( query("can_pour", ob) )
                        tmp+=TMI("mitem �ڡ��������д㶾 ;pour "+id+" in ...");
                if( query("can_drug", ob) )
                        tmp+=TMI("mitem �ڡ�ʳ��д㶾 ;drug "+id+" in ...");
                if( query("can_daub", ob) )
                {
                        tmp+=TMI("mitem �ڡ��������ϴ㶾 ;daub "+id+" on ...");
                        tmp+=TMI("mitem �ڡ����ߡ��ϴ㶾(Σ��) ;daub "+id+" on ...");
                        tmp+=TMI("mitem �ڡ����ϡ��ϴ㶾(Σ��) ;daub "+id+" on hand ...");
                }
        }
        tmp+=TMI("mendd");
        tell_object(me,tmp);
        return 1;
}
