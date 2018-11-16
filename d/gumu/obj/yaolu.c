// yaolu.c ��Ĺ��ҩ¯
// copy from xkx yaolu.c
// modified by April 2001.09.26
// update by april 2001.11.09

#include <ansi.h>

inherit ITEM;

#include "/d/gumu/obj/drug_list.h"

#define FILE_DIR "/d/gumu/obj/"

#define _DES "һֻ��Ĺ������ҩ¯������ʯ�Ƴɣ���ʵ�޻���\n¯���и�ʯ��(lip)������ƫ����һ�ף�¯����̿�裬���ڵ�ľ̿(coal)�������¼ӵġ�\n"
#define _FIRE HIR"\nҩ¯����ȼ�Ż�\n"NOR
#define _OPEN "ҩ¯�����Ѿ��ҿ���\n"

void create()
{
        set_name(CYN"��ʯҩ¯"NOR,( {"yao lu","yaolu","lu"} ));
        set_weight(10000);
        if (clonep() )
                set_default_object(__FILE__);
        else{
                set("unit","ֻ");
                set("long",_DES);
                set("value",10000);
                set("material","stone");
                set("no_get",1);
                set("cure_s",0);
                set("cure_d",0);
                set("cure_n",0);
                set("count",6);
                set("drug","none");
                set("no_refresh", 1);
        }
        
        setup();
}

void init()
{
        add_action("do_open","open");
        add_action("do_addyao","add");
        add_action("do_close","close");
        add_action("do_pour","dao");
        add_action("do_pour","pour");
        add_action("do_burn","burn");
        add_action("do_miehuo","mie");
        add_action("do_aoyao","aoyao");
        add_action("do_aoyao","lianyao");
        add_action("do_quyao","qu");
}

int do_open(string arg)
{
        object obj,me;
        me = this_player();
        obj = this_object();

        if (arg != "lip") return notify_fail("��Ҫ��ʲô��\n");
        if (query("open")) return notify_fail("�����Ѿ����ˡ�\n");

        if (query("is_burning")){
                message_vision(RED"ֻ����������һ���ҽУ�ԭ��$N��ҩ¯�����֡�\n"NOR,me);
                addn("qi",-150+random(50), me);
                set("long",_DES+_FIRE);
                return 1;
        }
        
        message_vision("$N��ҩ¯���ӽҿ���\n", me);
        set("long",_DES+_OPEN);
        set("open", 1);

        return 1;
}
        
int do_addyao(string arg)
{
        object me, obj,ob;
        string item, target; 
        int s,d,n;
        me = this_player();
        ob = this_object();

        if (!query("open")) return notify_fail("���ȰѸ��Ӵ򿪰ɡ�\n"); 

        if (!arg || sscanf(arg, "%s in %s", item, target) != 2 )
                return notify_fail("��Ҫ��ʲô�����Ž����\n");

        if (item == "all" ) return notify_fail("��ССҩ¯��ôװ������ô�ණ����\n");
                
        if (!objectp(obj = present(item, me))) return notify_fail("�����أ�\n");
                                                                
        if( !query("yaocai", obj))return notify_fail("ҩ¯��ֻ�ܷ��������Ƶ�ҩ�ġ�\n");
                        
        if (query("is_burning")) return notify_fail("���ѵ�ȼ����Ҫ�Ҷ���\n");
                
        if (query("count") < 1) return notify_fail("���ѷ���̫��ҩ���ˡ�\n");

        s=query("cure_s", obj);
        d=query("cure_d", obj);
        n=query("cure_n", obj);

        message_vision("$N��һ"+query("unit", obj)+query("name", obj)+"�Ž�ҩ¯��\n",me);
        destruct(obj);
        addn("count",-1);

        addn("cure_s",s);
        addn("cure_d",d);
        addn("cure_n",n);
        
        if (wizardp(me)) printf("%d\t%d\t%d\t\n",query("cure_s"),query("cure_d"),query("cure_n"));

        set("ready", 1);
        return 1;
}

int do_pour(string arg)
{
        object ping,me,box;
        int lvl,i,has_ping;
        object *inv;
        me = this_player();

        if (!query("open"))        return notify_fail("���ȰѸ��Ӵ򿪰ɡ�\n");

        if (arg == "water")        return notify_fail("�ѵ������տ�ˮ��\n");

        if (query("is_burning")) return notify_fail("���ѵ�ȼ����Ҫ�Ҷ���\n");

        if (arg != "�����" && arg != "�������" && arg != "��Ĺ��" && arg != "��䶾")
                return notify_fail("��Ҫ���ʲô��\n");

        lvl = me->query_skill("qufeng",1);
        if ( lvl < 61
                || ( lvl <  91 && arg == "��䶾" )
                || ( lvl < 121 && arg == "�������" )
                || ( lvl < 151 && arg == "��Ĺ��" ))
                return notify_fail("��İ�ҩˮƽ���������Ǳ��˷��ˡ�\n");

        lvl = me->query_skill("yunv-xinjing",1);
        if ( lvl < 61
                || ( lvl < 91 && arg == "�������" )
                || ( lvl < 121 && arg == "��Ĺ��" ))
                return notify_fail("����ڹ���Ϊ����������ҩ�����������Ǳ��˷���.\n");

        if ( arg == "��䶾" ){
                if ( !box = present("beehive",me) )        return notify_fail("�������أ�\n");
                if( query("escaped", box) )
                        return notify_fail("ʣ�µ�����ŵö������أ���һֻҲץ������\n");
                set("escaped", 1, box);
                addn("cure_s",0);
                addn("cure_d",0);
                addn("cure_n",-80);
                message_vision("$N��"+query("name", box)+"��ץ�˼�ֻ��䣬���˼�����䶾��ҩ¯�\n",me);
                return 1;
        }

        if (!query("ready")) return notify_fail("��ϲ�����ۺ���\n");

        has_ping = 0;
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("name", inv[i]) == CYN"���ƿ"NOR
                         && query("liquid/name", inv[i]) == arg
                         && query("liquid/remaining", inv[i]) == 10){
                        has_ping = 1;
                        ping = inv[i];
                }

        if (!has_ping) return notify_fail("����Ҫһ��ƿ��"+arg+"����ҩ��\n");

        set("liquid/remaining", 0, ping);
        if ( arg == "�����" ) set("mi",1);

        if ( arg == "�������" ) {
                addn("cure_s",70);
                addn("cure_d",70);
                addn("cure_n",-20);
        }
        if ( arg == "��Ĺ��" ) {
                addn("cure_s",90);
                addn("cure_d",90);
                addn("cure_n",-30);
        }
        message_vision("$N��"+query("name", ping)+"�е���һЩ"+arg+"��ҩ¯�\n",me);
        return 1;
}

int do_close(string arg)
{       
        object me;
        me = this_player();

        if (arg != "lip") return notify_fail("��Ҫ�ر�ʲô��\n");

        if (!(query("open"))) return notify_fail("�����Ѿ������ˡ�\n");
        if (query("is_burning")){
                message_vision(RED"ֻ����������һ���ҽУ�ԭ��$N��ҩ¯�����֡�\n"NOR,me);
        addn("qi", -150+random(50), me);
                set("long",_DES+_OPEN+_FIRE);
                return 1;
        }
        
        message_vision("$N��ҩ¯���ӿ��ϡ�\n", me);
        set("long",_DES);
        set("open", 0);
        return 1;
}

int do_burn(string arg)
{
        object me;
        me = this_player();

        if (arg != "coal") return notify_fail("��Ҫ��ȼʲô��\n");

        if (!present("fire",me)) return notify_fail("����ʲô���\n");

        if (!(query("ready"))) return notify_fail("ҩ¯��ʲô��û�С�\n");

        if (query("is_burning")) return notify_fail("���Ѿ���ȼ�ˡ�\n");
                
        if (query("open")) return notify_fail("���ȰѸ��ӸǺðɡ�\n");

        message_vision(RED"$N��̿���ȼ��\n\n"NOR,me);
        message_vision(HIB"����ɫ�Ļ���������������$N����ӳ����ɭ�ֲ���\n"NOR,me);
        set("is_burning", 1);

        if (query("open")) set("long",_DES+_OPEN+_FIRE);
        else set("long",_DES+_FIRE);

        remove_call_out("burning");
        call_out("burning",10+random(5),me);

    return 1;
}

int do_miehuo(string arg)
{
        object me;
        me = this_player();

        if (arg != "huo") return 0;

        if (!(query("is_burning"))) return notify_fail("��û��ȼ��\n");
                
        message_vision(RED"$N��̿��Ϩ��\n"NOR, me);

        if (query("open")) set("long",_DES+_OPEN);
        else set("long",_DES);

        set("is_burning", 0);
        set("fire_ready", 0);
        remove_call_out("burning");
        return 1;
}

void burning(object me)
{
        if (!query("mi")){
                set("long","һֻС���������ҩ¯��\n");
                message_vision(HIR"ͻȻ��ҩ¯�ڻ���ʢ������ð����$N��æ����ͷ����\n"NOR,me);
                message_vision(HIR"$Nȡ��ҩ��һ�����Ѿ��ճ�һ�Ž�̿��\n"NOR,me);
                remove_call_out("renewing");
                call_out("renewing",1,this_object());
                return;
        }

        message_vision("\n"HIY"̿�𽥽��������������Կ�ʼ�ˡ�\n"NOR,me);
        set("fire_ready", 1);
        return;
}

int do_aoyao()
{
        object me;
        int time,s,d,n,ds,dd,dn,i;
        
        me = this_player();
        time = 0;
        if (!query("fire_ready")) return notify_fail("���δ����\n");
        
        if ((int)me->query_skill("qufeng",1) < 60 )
                return notify_fail("�������۵�������ʶ������\n");

        if( query("neili", me)<500)return notify_fail("����������㣡\n");

        if( query("jingli", me)<1000)return notify_fail("��ľ������㣡\n");

        s = query("cure_s");
        d = query("cure_d");
        n = query("cure_n");

        if (wizardp(me)) printf("%d\t%d\t%d\t\n\n--------------------\n",s,d,n);

        for (i=0;i<sizeof(drug_list);i++){
                ds = drug_list[i]["s"];
                dd = drug_list[i]["d"];
                dn = drug_list[i]["n"];
                if (wizardp(me)) printf("%d\t%d\t%d\t\n",ds,dd,dn);
                if ( s == ds && d == dd && n == dn ){
                        set("drug",drug_list[i]["file"]);
                        set("drug_name",drug_list[i]["name"]);
                        set("drug_level",drug_list[i]["level"]);
                        time = drug_list[i]["time"];
                        break;
                }
        }

        if ( me->query_skill("qufeng",1) < query("drug_level") )
                return notify_fail("��İ�ҩ֪ʶ������");
        if ( me->query_skill("yunv-xinjing",1) < query("drug_level")-30 )
                return notify_fail("�����Ů�ľ���Ϊ������");

        message_vision(HIC"$Nһ�ֿ���¯��һ��һ�ţ��������ٿػ��ƣ�һ����סҩ�ƣ��Ӹ��Ͽ�������\n��ͣ���衣\n"NOR,me);
        message_vision(HIR"\n$N��ͣ���ظ��˶���һ�����������󺹡�\n"NOR,me);

    if (time == 0) time = 20;
        if (time > 30) me->start_busy(time-random(10));
        else me->start_busy((int)(time/2));

        set("pending", 1);
        remove_call_out("finish");
        call_out("finish",time,me);
        return 1;
}

void finish(object me)
{
        object obj;
        obj = this_object();

        message_vision("\n"HIY"$N����һ������ͣ��������\n"NOR,me);
        addn("neili", -(300+random(200)), me);
        addn("jingli", -(500+random(300)), me);
        addn("potential", (query("jingli", me)/200), me);
        addn("combat_exp", (query("neili", me)/500), me);
        set("done", 1);
        set("pending",0);
}

int do_quyao(string arg)
{
        object ob,me,obj,zhen1,zhen2,ping;
        object *inv;
        int i;

        me = this_player();
        obj = this_object();

        if (arg != "yao") return notify_fail("��Ҫȡʲô��\n");

        if (query("pending")) return notify_fail("�������˹���ҩ��\n");

        if (!(query("done"))) return notify_fail("��Ҫȡʲô��\n");
                
        if (query("is_burning")){
                message_vision(RED"ֻ����������һ���ҽУ�ԭ��$N��ҩ¯�����֡�\n"NOR,me);
                addn("qi", -150+random(50), me);
                return 1;
        }

        if (!(query("open"))) return notify_fail("���ȰѸ��Ӵ򿪰ɡ�\n");

        if (!query("drug") || query("drug") == "none")
                message_vision(HIB"$N��¯һ����¯��֮����һ�Ž���һ��������ûʲô�á�\n"NOR,me);
        else if ( query("drug_name") == "����붾" ) {
                if ( !zhen1 = present("jin zhen",me) ) 
                        return notify_fail("������û�н��롣\n");
                zhen2 = new("/d/gumu/obj/yufeng-zhen");
                zhen2->set_amount(zhen1->query_amount());
                destruct(zhen1);
                zhen2->move(me);
                message_vision("$Nȡ������պ��պҩ¯�а��õ���䶾���ŵ����ϴ�𡭡�\n", me);
                message_vision("ֻ���Æꡭ����һ��������������$N�����Ц��ӳ��¯�����������\n\n", me);
        }
        else if ( query("drug_name") == "��Ĺ��" || query("drug_name") == "��Ĺʥ��" ) {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++){
                        if( query("name", inv[i]) == CYN"���ƿ"NOR )
                                if( !query("liquid/remaining", inv[i])){
                                        ping = inv[i];
                                }
                }
                if (!ping) return notify_fail("����Ҫһ����ƿ��\n");
                set("liquid/name", query("drug_name"), ping);
                set("liquid/remaining", 10, ping);
                message_vision("$N��С�ĵذ�ҩ¯���"+query("drug_name")+"�������ƿ��\n\n", me);
        }
        else{
                ob = new(FILE_DIR+query("drug"));
                message_vision("$N��ҩ¯��ȡ��һ"+query("unit", ob)+query("name", ob)+"\n\n",me);
                ob->move(me);
        }

        remove_call_out("renewing");
        call_out("renewing",1,obj);
        return 1;
}

void renewing(object obj)
{
        set("open", 0, obj);
        set("is_burning", 0, obj);
        set("ready", 0, obj);
        set("fire_ready", 0, obj);
        set("pending", 0, obj);
        set("done", 0, obj);
        set("long", _DES, obj);
        set("cure_s", 0, obj);
        set("cure_d", 0, obj);
        set("cure_n", 0, obj);
        set("drug", "none", obj);
        set("count", 6, obj);
}
