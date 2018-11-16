// This program is a part of NT MudLIB
// �̻������Ϥ��Ϸ

#include <ansi.h>

inherit F_DBASE;

#define LINE   "------------------------------------------------------------------"

string *keys_gift_list;

mapping gift_name = ([
        "exp"         :  "����",
        "pot"         :  "Ǳ��",
        "mar"         :  "���",
        "neili"       :  "����",
        "jingli"      :  "����",
        "gold"        :  "�ƽ𣨴�����)",
        "gongxian"    :  "���ɹ���",
        "fuzhong"     :  "����",
        "riding"      :  "����",
        "training"    :  "Ԧ����",     
        "hunting"     :  "���Լ���",
        "weiwang"     :  "����",
        "score"       :  "����",
        "tianfu"      :  "�����츳",
        "horse"       :  "�����¼��",
        "quitsave"    :  "���߱���������Ʒ",
]);

mapping gift_list = ([

        "1"   :   ([ "�������" : "�˽���ο�ʼ����Ϸ",
                     "������ʶ" : "newbie_mygift/help",
                     "������ֵ" : 1,
                     "��������" : "����ָ�� help start �鿴�����Ѷ",
                     "��������" : "/clone/goods/zhufu_cloth:1,neili:1000",
                     "�¸�����" : "2", ]),

        "2"   :   ([ "�������" : "�鿴�Լ��ķ�λ",
                     "������ʶ" : "newbie_mygift/map",
                     "������ֵ" : 1,    
                     "��������" : "����ָ�� map �鿴�Լ����ڷ�λ\n"
                                  HIR "              ��ʾ����ͼ����ɫ��ɫλ��Ϊ�㵱ǰ����λ�á�" NOR,
                     "��������" : "/clone/goods/zhufu_boots:1,jingli:1000",
                     "�¸�����" : "3", ]),

        "3"   :   ([ "�������" : "����2����",
                     "������ʶ" : "mud_age",
                     "������ֵ" : 120,
                     "��������" : "���ߴﵽ������",
                     "��������" : "/clone/goods/zhufu_armor:1,/clone/gift/xiandan:8",
                     "�¸�����" : "4", ]),
                     
        "4"   :   ([ "�������" : "�鿴����",
                     "������ʶ" : "newbie_mygift/news",
                     "������ֵ" : 1,    
                     "��������" : "����ָ�� news �鿴��Ϸ����",
                     "��������" : "/clone/goods/zhufu_head:1,/clone/gift/xisuidan:8",
                     "�¸�����" : "5", ]),

        "5"   :   ([ "�������" : "�Ķ���ѡ",
                     "������ʶ" : "newbie_mygift/wenxuan",
                     "������ֵ" : 1,
                     "��������" : "����ָ�� wenxuan ��ʾ�����ѡ��Ϣ",
                     "��������" : "/clone/goods/zhufu_waist:1,/clone/gift/shenliwan:8",
                     "�¸�����" : "6", ]),
                     
        "6"   :   ([ "�������" : "�鿴 msg ����",
                     "������ʶ" : "newbie_mygift/msg",
                     "������ֵ" : 1,
                     "��������" : "����ָ�� msg ��ʾ����յ�����Ϣ",
                     "��������" : "/clone/goods/zhufu_wrists:1,/clone/gift/unknowdan:8",
                     "�¸�����" : "7", ]),

        "7"   :   ([ "�������" : "��ѯ���ֵ�ʦ",
                     "������ʶ" : "newbie_mygift/who",
                     "������ֵ" : 1,
                     "��������" : "����ָ�� who -v ��ʾ���е����ֵ�ʦ",
                     "��������" : "/clone/goods/zhufu_surcoat:1,/clone/item/magicfruit:8",
                     "�¸�����" : "8", ]),
                     
        "8"   :   ([ "�������" : "��ѯ���еĸ�������",
                     "������ʶ" : "newbie_mygift/istat",
                     "������ֵ" : 1,
                     "��������" : "����ָ�� istat ��ʾ���еĸ�������",
                     "��������" : "/clone/goods/zhufu_sword:1,quitsave:8035200,exp:100000,pot:50000",
                     "�¸�����" : "9", ]),
                     
        "9"   :   ([ "�������" : "�˽�����������",
                     "������ʶ" : "newbie_mygift/ability",
                     "������ֵ" : 1,
                     "��������" : "����ָ�� help ability �˽�����������",
                     "��������" : "/clone/goods/zhufu_blade:1,tianfu:4,/adm/npc/obj/gift:1",
                     "�¸�����" : "10", ]),
                                          
        "10"  :   ([ "�������" : "��������",
                     "������ʶ" : "newbie_quest_completed/can_out",
                     "������ֵ" : 1,    
                     "��������" : "�ӹŴ��뿪��������йŴ������뿪��\n" 
                                  HIR "              ��ʾ�����ݵ�ʦ--�ϴ峤����ʾ����ɹŴ��������ܳ��塣\n"
                                      "              ������֮������ָ��" HIY "ask lao ����" HIR "��������ʾ���������ܳ��塣\n" NOR,
                     "��������" : "/clone/goods/dizangshi:1,pot:50000,riding:100,training:100,fuzhong:1",
                     "�¸�����" : "12", ]),
                     
        "12"  :   ([ "�������" : "��������Ǭ����",
                     "������ʶ" : "can_summon/qiankun",
                     "������ֵ" : 1,    
                     "��������" : "��������Ǭ����\n" 
                                  HIR "              ��ʾ�������ݳ�����¥�ҵ���磬ask kuang about all����������Ǭ������\n" NOR,
                     "��������" : "/clone/fam/gift/int3:3,gold:2",
                     "�¸�����" : "14", ]),

        "14"  :   ([ "�������" : "��ħ����ǩ��Ѫ֮��Լ",
                     //"������ʶ" : "newbie_mygift/warcraft",
                     "������ʶ" : "can_whistle",
                     "������ֵ" : 1,    
                     "��������" : "��ħ����ǩ��Ѫ֮��Լ\n" 
                                  HIR "              ��ʾ�������ݳ�����¥�ҵ���磬����ħ���޵��¡�\n" NOR,
                     "��������" : "/clone/fam/gift/str3:3,horse:1",
                     "�¸�����" : "16", ]),
                     
        "16"  :   ([ "�������" : "��������˲�䵽�ﱱ��",  
                     "������ʶ" : "newbie_mygift/rideto",
                     "������ֵ" : 1,
                     "��������" : "��������˲��ﵽ����\n" 
                                  HIR "              ��ʾ��ride ħ���ޣ�ʹ��ָ��"HIY" rideto beijing " NOR,
                     "��������" : "/clone/fam/gift/con3:3",
                     "�¸�����" : "18", ]),

        "18"  :   ([ "�������" : "ʹ�� recall back �ص�����",  
                     "������ʶ" : "newbie_mygift/recall",
                     "������ֵ" : 1,
                     "��������" : "ʹ��ָ�� recall back �ص����ݿ͵�\n",
                     "��������" : "/clone/fam/gift/dex3:3",
                     "�¸�����" : "20", ]),
                     
        "20"  :   ([ "�������" : "�˽� bug �ر�",  
                     "������ʶ" : "newbie_mygift/bug",
                     "������ֵ" : 1,
                     "��������" : "ʹ��ָ�� help bug �˽�bug�ر�\n",
                     "��������" : "/clone/goods/study-emblem:1",
                     "�¸�����" : "25", ]),     

        "25"   :   ([ "�������" : "ʹ�� do ����ָ��",
                     "������ʶ" : "newbie_mygift/do",
                     "������ֵ" : 1,
                     "��������" : "���� do <����ָ��>\n"
                                  HIR "              ��ʾ������"HIY"help do2"HIR"�鿴������Ȼ��ʹ��ָ��"HIY" do w,w �� do 2 w " NOR,
                     "��������" : "/clone/goods/bigu-fu:1",
                     "�¸�����" : "30", ]),

        "30"  :   ([ "�������" : "ʹ�ô����",
                     "������ʶ" : "newbie_mygift/cangku",
                     "������ֵ" : 1,
                     "��������" : "������Ǯׯ�Ĵ���񿴿��ɣ��˽�����ôʹ�ô����\n" 
                                  HIR "              ��ʾ������Ǯׯ������ָ��"HIY"cw help"HIR"�鿴���ɡ�" NOR,
                     "��������" : "/clone/armor/jinsi-shoutao2:1",
                     "�¸�����" : "35", ]),
                                                  
        "35"  :   ([ "�������" : "��ʦ�ɹ�",
                     "������ʶ" : "family/family_name",
                     "������ֵ" : 1,
                     "��������" : "����һ��ϲ��������,\n" 
                                  HIR "              ��ʾ���й���������μ� help family" NOR,
                     "��������" : "gongxian:10000,score:3000,weiwang:50",
                     "�¸�����" : "40", ]),

        "40"  :   ([ "�������" : "��ѯ���ܾ���",
                     "������ʶ" : "newbie_mygift/skill",
                     "������ֵ" : 1,
                     "��������" : "����ָ�� skill lonely-sword ��ʾ���¾Ž�������Ϣ",
                     "��������" : "neili:1000,gongxian:5000",
                     "�¸�����" : "45", ]),
                     
        "45"  :   ([ "�������" : "��ú���",
                     "������ʶ" : "newbie_mygift/haigui",
                     "������ֵ" : 1,
                     "��������" : "���һ������������������\n" 
                                  HIR "              ��ʾ������"HIY"rideto"HIR"�鿴����ɵ���ط���Ȼ��"HIY"do rideto nanhai,n,e"HIR"ǰ����" NOR,
                     "��������" : "neili:1000,gongxian:2000",
                     "�¸�����" : "50", ]),

        "50"  :   ([ "�������" : "������",
                     "������ʶ" : "newbie_mygift/shendiao",
                     "������ֵ" : 1,
                     "��������" : "������������������\n" 
                                  HIR "              ��ʾ������"HIY"rideto"HIR"�鿴����ɵ���ط���Ȼ��"HIY"rideto shendiao"HIR"ǰ����" NOR,
                     "��������" : "neili:1500,jingli:1000,gongxian:2000",
                     "�¸�����" : "55", ]),

        "55"  :   ([ "�������" : "�������",
                     "������ʶ" : "bunch",
                     "������ֵ" : 1,
                     "��������" : "�����������\n" 
                                  HIR "              ��ʾ������������Ƶ��"HIY"chat ��˵�Ļ�"HIR"����������鿴 help bunch.2\n"
                                      "                    ���û����Ұ��ɿ��Բμ�npc���ɣ�����鿴help bunch_quest" NOR,
                     "��������" : "pot:20000,weiwang:5000,neili:500,jingli:500",
                     "�¸�����" : "60", ]),

        "60"  :   ([ "�������" : "��ɰ�������",
                     "������ʶ" : "bunch_quest",
                     "������ֵ" : 1,
                     "��������" : "������ڵİ��ɷ����İ�������\n" 
                                  HIR "              ��ʾ���йذ�����������μ� help bunch_quest" NOR,
                     "��������" : "exp:20000,weiwang:2000,neili:500,jingli:500",
                     "�¸�����" : "65", ]),
                                          
        "65"  :   ([ "�������" : "���ʦ������",
                     "������ʶ" : "quest_count",
                     "������ֵ" : 1,
                     "��������" : "�ҵ��������Ż����񷢲�ʦ����ȡʦ���������\n" 
                                  HIR "              ��ʾ���й�ʦ�����������μ� help quest" NOR,
                     "��������" : "exp:10000,pot:10000,gongxian:5000",
                     "�¸�����" : "70", ]),

        "70"  :   ([ "�������" : "Ѱ�ҵ�����ͼ",
                     "������ʶ" : "quest_tuteng",
                     "������ֵ" : 1,
                     "��������" : "�����ʹ�����Ѱ�ҵ�����ͼ\n"
                                  HIR "              ��ʾ���й�Ѱ�ҵ�����ͼ���������μ� help tuteng" NOR,
                     "��������" : "exp:10000,pot:10000,mar:10000",
                     "�¸�����" : "75", ]), 

        "75"  :   ([ "�������" : "���롾ԭʼɭ�֡�����",
                     "������ʶ" : "newbie_mygift/fuben",
                     "������ֵ" : 1,
                     "��������" : "���롾ԭʼɭ�֡��������Ӹ������߳�\n" 
                                  HIR "              ��ʾ�������������ҵ������Ե����"HIY"enter door"HIR"���븱����" NOR,
                     "��������" : "exp:20000,pot:20000",
                     "�¸�����" : "80", ]),
                     
        "80"  :   ([ "�������" : "��øɽ���Īа",
                     "������ʶ" : "newbie_mygift/ganjiang",
                     "������ֵ" : 1,
                     "��������" : "�ݷ�һ�¸ɽ�Īа�ɣ��Ժ󻹵þ���������������\n" 
                                  HIR "              ��ʾ������"HIY"rideto"HIR"�鿴����ɵ���ط���Ȼ��"HIY"rideto ganjiang"HIR"ǰ����" NOR,
                     "��������" : "exp:20000,pot:20000,/clone/money/gold:1",
                     "�¸�����" : "85", ]),

        "85"  :   ([ "�������" : "װ��ǩ��",
                     "������ʶ" : "newbie_mygift/makeweapon",
                     "������ֵ" : 1,
                     "��������" : "��ʱ��ӵ��һ�������Լ���װ���ˣ�װ��ǩ��˵���μ�help weapon", 
                     "��������" : "/clone/armor/shuijing-guan:1",
                     "�¸�����" : "90", ]),

        "90"  :   ([ "�������" : "������ʦ����",
                     "������ʶ" : "newbie_mygift/kaiguang",
                     "������ֵ" : 1,
                     "��������" : "����ǩ����װ������ɣ�������ʱ�����ٻ�(summon)����\n" 
                                  HIR "              ��ʾ���ɽ������ҵ�����ʦ��ʹ��ָ��"HIY"show <����ID>"HIR"����\n"
                                      "                    �պ�����ʾ�������ɽ��п��⡣" NOR,
                     "��������" : "/clone/armor/zhanyao-xunzhang:1",
                     "�¸�����" : "95", ]),

        "95"  :  ([ "�������" : "��ѧ��ţ�һ��",
                     "������ʶ" : "newbie_mygift/certosina",
                     "������ֵ" : 1,
                     "��������" : "ѧϰ��Ƕ���յ�һ�ټ�\n" 
                                  HIR "              ��ʾ����³�ദѧϰ��ָ��"HIY"xue lu ban certosina"HIR"ѧϰ��" NOR,
                     "��������" : "/clone/armor/moling-zhiyi:1,/clone/armor/sheyao-ring:1",
                     "�¸�����" : "100", ]),

        "100"  :  ([ "�������" : "װ������",
                     "������ʶ" : "newbie_mygift/notch",
                     "������ֵ" : 1,
                     "��������" : "��װ�����п��ף����׺������Ƕ��ʯ\n" 
                                  HIR "              ��ʾ���ɽ���notch <װ��>��������Ҫ�ķ�������μ� help rune" NOR,
                     "��������" : "exp:1000000,pot:1000000,/clone/armor/wushi-pifeng:1",
                     "�¸�����" : "110", ]),
                                          
        "110"  :   ([ "�������" : "�ϳ�������Ʒ",
                     "������ʶ" : "newbie_mygift/combine",
                     "������ֵ" : 1,
                     "��������" : "�鿴��Ʒ�ϳɹ�ʽ���ϳɳ�һ��������Ʒ\n" 
                                  HIR "              ��ʾ���йغϳ���Ʒ������μ� help combine" NOR,
                     "��������" : "exp:10000,pot:10000,gongxian:5000",
                     "�¸�����" : "120", ]),

        "120"  :  ([ "�������" : "��ΪһƷ��ҩʦ",
                     "������ʶ" : "is_alchemy",
                     "������ֵ" : 1,
                     "��������" : "������������300��\n" 
                                  HIR "              ��ʾ����������300���󣬵�ƽһָ���������ҩʦƷ����" NOR,
                     "��������" : "exp:100000,pot:100000,/clone/armor/shuijing-guan:1",
                     "�¸�����" : "130", ]),

        "130"  :  ([ "�������" : "��ѧ��ʦ",
                     "������ʶ" : "opinion/ultra",
                     "������ֵ" : 1,
                     "��������" : "��ս��Ϊ��ѧ����ʦ��˵���ɲμ�help feature\n" 
                                  HIR "              ��ʾ��������������Ĵ���ʦ��ʹ��ָ��"HIY"ask <��ʦNPC ID> about ����"HIR"�󣬸�����ʾ\n"
                                      "                    ������ָ��"HIY"fight <��ʦNPC ID>"HIR"������ս��" NOR,
                     "��������" : "exp:2000000,pot:2000000,mar:2000000",
                     "�¸�����" : "140", ]),
                     
        "140"  :  ([ "�������" : "��ѧ��ţ�����",
                     "������ʶ" : "newbie_mygift/jingluoxue",
                     "������ֵ" : 1,
                     "��������" : "ѧϰ����ѧ��һ�ټ�",
                     "��������" : "pot:5000000,neili:500,jingli:500,gold:500",
                     "�¸�����" : "150", ]),

        "150"  :  ([ "�������" : "��ͨ������",
                     "������ʶ" : "newbie_mygift/yinqiaomai",
                     "������ֵ" : 1,
                     "��������" : "��������������ͭ�ˣ���ͨ��һ��С���쾭��--������\n" 
                                  HIR "              ��ʾ����Ӣ���̵깺������������ͭ�ˣ�����μ� help chongxue" NOR,
                     "��������" : "/clone/goods/tianshi-charm:1",
                     "�¸�����" : "160", ]),
                                          
        "160"  :  ([ "�������" : "��ͨ��С���쾭��",
                     "������ʶ" : "breakup",
                     "������ֵ" : 1,
                     "��������" : "��Ѩ��ͨ��С���쾭�����������������������\n" 
                                  HIR "              ��ʾ���չ�˵���ɲμ� help zhoutian" NOR,
                     "��������" : "mar:3000000,neili:1000,jingli:1000",
                     "�¸�����" : "170", ]),
                     
        "170"  :  ([ "�������" : "װ��ǿ��",
                     "������ʶ" : "newbie_mygift/qianghua",
                     "������ֵ" : 1,
                     "��������" : "��װ������ǿ����ǿ�����װ�����Դ��������\n" 
                                  HIR "              ��ʾ���ɽ�����shou <װ��>������Ҫ���qianghua <װ��>��ǿ��װ������μ� help qianghua" NOR,
                     "��������" : "pot:3000000,neili:1000,jingli:1000",
                     "�¸�����" : "180", ]),

        "180"  :  ([ "�������" : "װ���̻�",
                     "������ʶ" : "newbie_mygift/dosuit",
                     "������ֵ" : 1,
                     "��������" : "��װ�������̻����̻����װ�������װ��ӵ�м�Ʒ����\n" 
                                  HIR "              ��ʾ���ȸ��ɽ�����֮�ģ�Ȼ��dosuit <װ��>���̻�װ������μ� help suit" NOR,
                     "��������" : "exp:5000000,pot:5000000,mar:5000000,/clone/armor/yecha1:1",
                     "�¸�����" : "190", ]),
        /*
        "170"  :  ([ "�������" : "����ԪӤ����",
                     "������ʶ" : "animaout",
                     "������ֵ" : 1,
                     "��������" : "��������������չ�����ԪӤ����\n" 
                                  HIR "              ��ʾ���չ�˵���ɲμ� help closed" NOR,
                     "��������" : "pot:3000000,neili:1000,jingli:1000",
                     "�¸�����" : "180", ]),
            
        "180"  :  ([ "�������" : "��ͨ��������",
                     "������ʶ" : "death",
                     "������ֵ" : 1,
                     "��������" : "��������������չش�ͨ��������\n" 
                                  HIR "              ��ʾ���չ�˵���ɲμ� help closed" NOR,
                     "��������" : "exp:5000000,pot:5000000,mar:5000000,/clone/armor/yecha1:1",
                     "�¸�����" : "190", ]),                 
        */
        "190"  :  ([ "�������" : "ת������",
                     "������ʶ" : "reborn/times",
                     "������ֵ" : 1,
                     "��������" : "��ѧ��ֹ����Ψת������ͻ��ƿ��\n" 
                                  HIR "              ��ʾ��ת��˵���ɲμ� help reborn" NOR,
                     "��������" : "exp:10000000,pot:10000000,mar:10000000",
                     "�¸�����" : "200", ]),

        "200"  :  ([ "�������" : "�ȴ���һ����ս", // ����汾�������ˣ���������������￪ʼ
                     "������ʶ" : "newbie_mygift/waitfor_next1",
                     "������ֵ" : 1,
                     "��������" : "�ȴ���һ����ս�ɣ��������������ս���ݣ�\n" 
                                  HIR "              ��ʾ�������һ���䣬��������������ͨ�棡" NOR,
                     "��������" : "pot:10000000",
                     "�¸�����" : "210", ]),
]);


// �ⲿ���ã������ж��Ƿ���ָ�������Ҵ�������������������
public void check_mygift(object me, string quest_flag)
{
        string nquest;
        if( !me || !quest_flag ) return;
        if( !nquest = query("newbie_mygift/cur_quest_number", me) )
                return ;
        
        if( gift_list[nquest]["������ʶ"] == quest_flag )
        {
                if( gift_list[nquest]["������ֵ"] > 1 )
                        addn(gift_list[nquest]["������ʶ"], 1, me);
                else
                        set(gift_list[nquest]["������ʶ"], 1, me);
                
                me->save();
        }
        return;
}

void create()
{
        seteuid(getuid());
        set("channel_id", "���˽�������");   
        set("no_clean_up", 1);
        CHANNEL_D->do_channel(this_object(), "sys", "���˽���ϵͳ�Ѿ�������");

        keys_gift_list = keys(gift_list);
}

// �ж��ַ����Ƿ�����Ʒ����
int is_obgift(string arg)
{
        if( strsrch(arg, "/") == -1 )
                return 0;
                
        return 1;
}

// ���� exp:3334 ��ʽ�Ľ�������
string sub_gift_desc(string arg)
{
        string sdesc, sgift;
        object ob;
        int ncount;
        
        sscanf(arg, "%s:%d", sgift, ncount);
        
        sdesc = "";
        // �ж��Ƿ�����Ʒ
        if( is_obgift(sgift) )
        {
                if( !objectp(ob = find_object(sgift)) )
                        ob = load_object(sgift);
                        
                if( !ob ) return "error:" + sgift;

                sdesc = filter_color(ob->name()) + "x" + sprintf("%d",ncount);
        }
        else
        {
                sdesc = gift_name[sgift] + "+" + 
                        (ncount >= 10000 ? sprintf("%d��", ncount / 10000):sprintf("%d", ncount));
        }       
        
        return sdesc;
}

// ��ʽ����Ľ�������
// exp:10000000_pot:10000000_mar:10000000_/clone/armor/zhanyao-xunzhang:1
string gift_desc(string arg)
{
        object ob;
        string sdesc, *keys_list;
        int i;
        
        sdesc = "";
        
        // �ж��Ƿ��ǵ�������
        if( strsrch(arg, ",") == -1 )
        {       
                sdesc = sub_gift_desc(arg);
        }
        else // �������
        {
                keys_list = explode(arg, ",");
                
                for( i = 0; i < sizeof(keys_list); i ++ )
                {
                        sdesc += sub_gift_desc(keys_list[i]);
                        if( i < sizeof(keys_list) - 1 )
                                sdesc += "��";
                }
        }
        
        return sdesc;
}

// ��ʾ��������
string mygift_string(mapping mygift_map)
{
        string squest, sgift_desc;
        
        squest = HIC + LINE + "\n";
        
        squest += "���������ơ���" + mygift_map["�������"] + "\n";
        squest += "�������������" + mygift_map["��������"] + "\n";
        squest += HIY "������������" + gift_desc(mygift_map["��������"]) + "\n";
        squest += HIC + LINE + "\n" NOR;
        
        return squest;
}

// ����һ������
void give_mygift(object me, string s)
{
        string squest;
        
        set("newbie_mygift/cur_quest_number", s, me);
        
        // ��ʾ
        squest = HIR "�������µĸ������� ָ�� " HIY "mygift" HIR" �鿴��ǰ��������" + BLINK + HIC "    ������" + NOR "\n" ;
        squest += mygift_string(gift_list[s]);
        
        tell_object(me, squest);
        
        return;
}


// ���轱���ӹ��ܵ���
string sub_gift_send(object me, string arg)
{
        string sdesc, sgift;
        object ob;
        int ncount, i;
        
        sscanf(arg, "%s:%d", sgift, ncount);
        
        sdesc = "";
        // �ж��Ƿ�����Ʒ
        if( is_obgift(sgift) )
        {
                if( !objectp(ob = find_object(sgift)) )
                        ob = load_object(sgift);

                if( !ob )
                {
                        write(HIR + sgift + "��ȡ����\n");
                        log_file("mygiftd", "����mygiftd��" + sgift + "��Ʒ����\n");
                        return;
                }
                
                // ������Ʒ������
                // ���ֿܷ�ʹ�õ���Ʒ��������
                ob = new(sgift);
                if( !objectp(ob) )
                {
                        write(HIR + sgift + "��ȡ����-2��\n");
                        log_file("mygiftd", "����mygiftd��" + sgift + "������Ʒ����\n");
                        return;                 
                }
                if( !ob->query_amount() )
                {
                        for (i = 1; i <= ncount; i ++)
                        {
                                reset_eval_cost();
                                ob->move(me, 1);
                                set("bindable", 3, ob);
                                set("bind_owner", query("id", me), ob);
                                set("set_data", 1, ob);
                                set("auto_load", 1, ob);
                                ob = new(sgift);                                                
                        }
                }
                else
                {
                        ob->set_amount(ncount);
                        ob->move(me, 1);
                        set("bindable", 3, ob);
                        set("bind_owner", query("id", me), ob);
                        set("no_sell", 1, ob);
                        set("set_data", 1, ob);
                        set("auto_load", 1, ob);
                }
                
                
                sdesc = HIY "-�����Ʒ��" +  filter_color(ob->name()) + "x" + sprintf("%d",ncount) + "\n" NOR;
        }
        else
        {
                // ����������
                switch(sgift)
                {
                        case "exp":
                                addn("combat_exp", ncount, me);
                        break;
                        
                        case "pot":
                                addn("potential", ncount,  me);
                        break;

                        case "mar":
                                addn("experience", ncount, me);
                        break;
                                                
                        case "gongxian":
                                addn("family/gongji", ncount, me);
                        break;
                        
                        case "gold":
                                addn("balance", ncount*10000, me);
                        break;

                        case "neili":
                                addn("drug_addneili", ncount, me);
                                addn("max_neili", ncount,  me);
                                if( query("neili", me)<query("max_neili", me) )
                                        set("neili",query("max_neili",  me), me);
                        break;
                
                        case "jingli":
                                addn("drug_addjingli", ncount, me);
                                addn("max_jingli", ncount, me);
                                if( query("jingli", me)<query("max_jingli", me) )
                                        set("jingli",query("max_jingli", me), me);
                        break;

                        case "fuzhong":
                                addn("add_max_encumbrance", 50000, me);
                        break;
                        
                        case "riding":
                                if( me->query_skill("riding") < ncount )
                                        me->set_skill("riding", ncount);
                        break;
                        
                        case "hunting":
                                if( me->query_skill("hunting") < ncount )
                                        me->set_skill("hunting", ncount);
                        break;

                        case "training":
                                if( me->query_skill("training") < ncount )
                                        me->set_skill("training", ncount);
                        break;
                        
                        case "weiwang":
                                addn("weiwang", ncount, me);
                        break;

                        case "score":
                                addn("score", ncount, me);
                        break;

                        case "tianfu":
                                addn("tianfu", ncount, me);
                        break;
                        
                        case "horse":
                                addn("horse/stone", 1, me);
                        break;
                        
                        case "quitsave":
                                me->set_srv("quit_save", 8035200);
                        break;
                        
                        default:
                                write("���ʹ���\n");
                                return;
                        break;
                }
                
                sdesc = HIY "-��ý���" + gift_name[sgift] + "+" + sprintf("%d",ncount) + "\n" NOR;
        }
        
        return sdesc;
}

// ���轱��
void give_gift(object me, string arg)
{
        int i, count;
        object ob;
        string *keys_list, sgift, sdesc;
                
        
        set("newbie_mygift/is_running_gift_list_send", 1, me);

        sdesc = "";
        // �ж��Ƿ��ǵ�������
        if( strsrch(arg, ",") == -1 )
        {       
                sdesc += sub_gift_send(me, arg);
        }
        else // �������
        {
                keys_list = explode(arg, ",");
                
                for( i = 0; i < sizeof(keys_list); i ++ )
                {
                        sdesc += sub_gift_send(me, keys_list[i]);
                }
        }
        
        delete("newbie_mygift/is_running_gift_list_send", me);
        me->save();
        
        write(sdesc);
        
        return;
}

// /cmds/usr/mygift ���� 
int mygift(object me, string arg)
{
        string squest, nquest;
        string splayer;
        object ob;
        
        int i;
        
        // ��ʾ��ǰ����
        if( !objectp(me) )return 0;
                
        if( !arg )
        {
                if( !nquest=query("newbie_mygift/cur_quest_number", me) )
                        return notify_fail("�㵱ǰû�и���������Ϣ��\n");
                
                squest = mygift_string(gift_list[nquest]);
        
                squest = HIG "����ǰ�����������¡�\n" + squest; 
                
                me->start_more(squest);
                
                return 1;               
        }
        
        if( arg == "list" )
        {
                if( !wizardp(me) ) return 0;
                
                // ��ʾ���н����������ϸ���ݣ���Ҫ����У��
                squest = "��У����������\n";

                for( i = 0; i < sizeof(keys_gift_list); i ++ )
                {
                        squest += mygift_string(gift_list[keys_gift_list[i]]) + "\n";
                }
                
                write(squest);
                
                return 1;
        }
        else if( sscanf(arg, "give %s %s", splayer, nquest) == 2 )
        {
                if( !wizardp(me) ) return 0;
                
                // �ֶ�����ҷ���ָ����ŵ�����
                if( !objectp(ob = find_player(splayer)) )
                        return notify_fail("Ŀ����Ҳ����ߣ�\n");
                
                if( member_array(nquest, keys_gift_list) == -1 )
                        return notify_fail("û��ָ����ŵ�����ʹ�� mygift list �鿴���������б�\n");
                
                give_mygift(ob, nquest);
                
                return 1;
                
        }
        

        return 1;
        
}

// �ⲿ���ã���鵱ǰ�Ƿ�����Ѿ���ɵ��������������������
public void check_curgift(object me)
{
        mapping tmap;
        string nquest;
        
        if( !objectp(me) ) return;
        
        if( !query("newbie_mygift/cur_quest_number", me) )
                return;

        // ���ڴ��������򷵻�
        if( query("newbie_mygift/is_running_gift_list_send", me) ) return ;
        
        // �ж��Ƿ����
        nquest=query("newbie_mygift/cur_quest_number", me);
        tmap = gift_list[nquest];
        
        if( !intp(query(tmap["������ʶ"], me)) || query(tmap["������ʶ"], me) >= tmap["������ֵ"] )
        {
                // ���Ž���
                write(HIG + "��" + tmap["�������"]+ "��" BLINK + HIM "�����ɣ�\n" NOR);
                give_gift(me, tmap["��������"]);

                // ������һ������
                give_mygift(me, tmap["�¸�����"]);
        }
        
        return;
}
