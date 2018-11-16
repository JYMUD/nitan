#include <ansi.h>
inherit ROOM;
//void kf_same(object who,object me);

void create()
{
        set("short", "��������");
        set("long", @LONG
    ���϶����������ס������һ������������������ϸ������
ǽ������һ�����ң������ĸ���������Ĵ��֡�֪���������İ�����
�����飬ʦү�����ں󡣴������и���һ�ң�[1��31m               ��   
 ��    ��    ��[2��37��0m
LONG );
        set("valid_startroom",1);
        set("no_steal", "1");
        set("no_magic", "1");
        set("no_fight", "1");
        set("exits", ([
           "east"  : "/d/city/dongting", 
                      "west"  : "/d/city/xiting", 
                      "north" : "/d/city/neizhai", 
                      "south" : "/d/city/yamen", 

        ]));
  

        set("objects", ([
                  "/d/city/npc/cheng" : 1, 
                  "/d/city/npc/shiye" : 1, 
        ]));
        setup();
}

void init ()
{
        add_action("do_work","work");
        add_action("do_finish","finish");
}

int do_work (string arg)
{
        object ob,ob1;
        int kf_npc,kf_whatnpc,worked_num;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        if( query("kf_jiangli", me) )
                return notify_fail("��ҩ��˵�����񲶴��˻�û������ʥ����\n");

        if( !query("kaifengfu", me) )
                return notify_fail("�������۴����ȵ����󵨵��񣬲����������ã�\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("��������Ц������ҩ���Ѿ������ˣ�Ҫ��������������������\n");

        if( present("lingpai",me) || query("kf_working", me) )
                return notify_fail("��ҩ����ɫһ����������ǰ�ս�����Ĳ�����ȥ���������������أ�\n");
        kf_npc = 1 + random(209);
        kf_whatnpc =1+random(8);
        set("kf_whatnpc", kf_whatnpc, me);
        ob = new("/d/city/obj/lingpai");        //50
        if(kf_whatnpc==1){ob1 = new("/d/city/npc/tufei1");}
        if(kf_whatnpc==2){ob1 = new("/d/city/npc/tufei2");}
        if(kf_whatnpc==3){ob1 = new("/d/city/npc/tufei3");}
        if(kf_whatnpc==4){ob1 = new("/d/city/npc/tufei4");}
        if(kf_whatnpc==5){ob1 = new("/d/city/npc/tufei5");}
        if(kf_whatnpc==6){ob1 = new("/d/city/npc/tufei6");}
        if(kf_whatnpc==7){ob1 = new("/d/city/npc/tufei7");}
        if(kf_whatnpc==8){ob1 = new("/d/city/npc/tufei8");}
        ob ->move(me);
        set_temp("kf_npc", kf_npc, me);
        if(kf_npc<210) kf_where = "�䵱����";
        if(kf_npc<191) kf_where = "��ɽ����";
        if(kf_npc<166) kf_where = "��ң�ɸ���";
        if(kf_npc<152) kf_where = "�����ɸ���";
        if(kf_npc<141) kf_where = "̩ɽ����";
        if(kf_npc<125) kf_where = "ѩɽ����";
        if(kf_npc<107) kf_where = "���ݸ���";
        if(kf_npc<84) kf_where = "��������";
        if(kf_whatnpc==1){ kf_name = "������"; kf_name1 = "��·����,ɱ������";}
        if(kf_whatnpc==2){ kf_name = "��Ӱ��͵"; kf_name1 = "�Ĵ����Բ���";}
        if(kf_whatnpc==3){ kf_name = "���������"; kf_name1 = "����������Ů���޶���";}
        if(kf_whatnpc==4){ kf_name = "ħ��ϸ��"; kf_name1 = "�Ĵ��";}
        if(kf_whatnpc==5){ kf_name = "���ڼ�ϸ"; kf_name1 = "�Ĵ���ҥ�ƻ�";}
        if(kf_whatnpc==6){ kf_name = "������"; kf_name1 = "��ɱ��͢����";}
        if(kf_whatnpc==7){ kf_name = "��Ԫ��"; kf_name1 = "��ҽ���";}
        if(kf_whatnpc==8){ kf_name = "����"; kf_name1 = "��������";}

        set_temp("kf_whatnpc", kf_whatnpc, me);
        set_temp("kf_name", kf_name, me);
        set_temp("kf_where", kf_where, me);
        message_vision("��ҩ��һ�ľ���ľŭ�����ݲ����"+kf_name+"��"+kf_where+kf_name1+"��"+query("name", me)+"��ȥ�ư�����������\n",me);
        set("kf_working", 1, me);
        return 1;
}
int do_finish (string arg)
{
        object ob;
        int kf_npc,kf_whatnpc,kf_exp,kf_qn;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        ob= present("ling pai",me);
        kf_name=query_temp("kf_name", me);
        kf_where=query_temp("kf_where", me);
        
        if( !query("kaifengfu", me) )
                return notify_fail("���Եķ������۴����ȵ����󵨵��񣬲����������ã�\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("��������Ц�����̴����Ѿ������ˣ�Ҫ�뽻����������������\n");
        if( !query("kf_working", me) )
                return notify_fail("��ҩ����ɫһ����������ʲôʱ���ɹ�����°���\n");
        if( !query_temp("kf_finish", me) )
                return notify_fail("��ҩ����ɫһ��������������Ĳ�ʹ����δ���ף��㻹����Ŀ�����ң�\n");
        if (present("ling pai",me)){
                tell_object(me, "�㹧�������Ľ������ơ�\n" NOR );
        destruct(present("ling pai",me));
        }        
        message_vision(WHT"��ҩ��΢΢һЦ����"+query("name", me)+WHT"��"+kf_where+WHT"�ƻ�"+kf_name+WHT"һ�����Ϳ๦�ߣ��Ͽ���ȥ��Ϣ�ɣ�\n"NOR,me);
        kf_exp = 2000+random(2000);
        kf_qn = 500+random(500);
        addn("combat_exp", kf_exp, me);
        addn("kf_worked", 1, me);
        addn("potential", kf_qn, me);
        addn("kf_worked", 1, me);
        set("kf_working", 0, me);
        delete_temp("kf_finish", me);
        tell_object(me, "������" + chinese_number(kf_exp)+ "�㾭�顣\n" NOR );
        tell_object(me, "������" + chinese_number(kf_qn)+ "��Ǳ�ܡ�\n" NOR );
        if( query("kf_worked", me) == 4800){
                set("kainame", 10, me);
                addn("shen", 3000, me);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me,"�����ڵ�������"+chinese_number((query("shen", me)))+"��\n"NOR);
                message_vision(WHT"��ҩ��΢Ц��˵����"+query("name", me)+"���ƴ󰸣����������������Ѿ��������ϡ�\n���ճ�ּ���£�����ƽ���ǧ��������Ե�Ǯׯ��ȡ��"NOR,me);
                 addn("balance", 10000000, me);
               set("kf_jiangli", 1, me);

      }
        if( query("kf_worked", me) == 3200){
                addn("shen", 3000, me);
                set("kainame", 9, me);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me,"�����ڵ�������"+chinese_number((query("shen", me)))+"��\n"NOR);
                message_vision(WHT"��ҩ��΢Ц��˵����"+query("name", me)+"���ƴ󰸣���������,�������ͣ���"NOR,me);
      }
        if( query("kf_worked", me) == 1600){
                set("kainame", 8, me);
                addn("shen", 1500, me);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me,"�����ڵ�������"+chinese_number((query("shen", me)))+"��\n"NOR);
      }
        if( query("kf_worked", me) == 800){
                set("kainame", 7, me);
                addn("shen", 1000, me);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me,"�����ڵ�������"+chinese_number((query("shen", me)))+"��\n"NOR);
        }
        if( query("kf_worked", me) == 400){
                set("kainame", 6, me);
                addn("shen", 800, me);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me,"�����ڵ�������"+chinese_number((query("shen", me)))+"��\n"NOR);
        }
        if( query("kf_worked", me) == 200){
                set("kainame", 5, me);
                addn("shen", 400, me);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me,"�����ڵ�������"+chinese_number((query("shen", me)))+"��\n"NOR);
        }
        if( query("kf_worked", me) == 100){
                set("kainame", 4, me);
                addn("shen", 200, me);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me,"�����ڵ�������"+chinese_number((query("shen", me)))+"��\n"NOR);
        }
        if( query("kf_worked", me) == 50){
                set("kainame", 3, me);
                addn("shen", 100, me);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me,"�����ڵ�������"+chinese_number((query("shen", me)))+"��\n"NOR);
        }
        if( query("kf_worked", me) == 20){
                set("kainame", 2, me);
        }
        me->save();
        return 1;
}
int valid_leave (object who, string dir)
{
        if(who->query_condition("kf_stop")<1){
                return ::valid_leave(who, dir);
        }
        else{
                message_vision ("$N���������������ܡ�\n",who);
                return notify_fail(WHT"�����������㰴�ڵ��Ϻȵ�����ʵ�㣡\n"NOR);
                return 1;
}
}
