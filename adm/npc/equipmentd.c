// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// equipmentd.c

#pragma optimize
#pragma save_binary

inherit F_DBASE;
#include <equipment.h>

#define EQUIP_DIR       "/inherit/template/"
#define EQUIP_LIST      CONFIG_DIR "equiplist/"

// �Ʒ���ߣ��ҵ��������Ŀǰ�Ʒ��ļ���������һ�������������Ʒ����10������ô������Ʒ�10�㣬�ͱ����11�㡣
// ���м�ǿ��˵ʵ�����ҿ���������ʲô��������
// ˫���������������˺��Ļ����ϣ���2������Ҫ��һ�����ԡ�����Խ��Խ�á�
// ����������ǳ���Ҫ�����ԣ���ɱ�����ѪЧ����
// ��������ѣ�� ˮ������ʽ���� ���������˺����� ľ������ä
// ɱ¾-����ʱ�м��ʶԵ�ǰ���������˽���һ�ι���
// ���� 5�п����� ���� ���� �񵲣������˺��� ��ͨ  ����
// ���پ������ӳ��еļ��� ������˫���˺����� ���Ǽ���30%�˺����ʡ����������������мܵļ��� ��ͨ��perform�˺��ӳ�
// 7������5�ף�2������7�ף�3����Ʒ3��

// ��������
mapping all_props = ([
        "consistence"   : "�;ö�",     // ��������
        "damage"        : "�����˺���", // ��������
        "unarmed_damage": "�����˺���", // ��������
        "armor"         : "������",     // ��������
        "damage2"       : "�����˺�",   // weapon
        "armor2"        : "���챣��",   // armor
        "damage1"       : "�����˺�",   // weapon
        "armor1"        : "���ӱ���",   // armor
       
        "str"           : "����",       // weapon/armor/rings
        "int"           : "����",       // weapon/armor/rings
        "con"           : "����",       // weapon/armor/rings
        "dex"           : "��",       // weapon/armor/rings
        "kar"           : "��Ե",       // weapon/armor/rings
        "per"           : "��ò",       // rings
        "attribute"     : "��������",   // rings
        
        "max_neili"     : "�������ֵ", // weapon/armor/rings
        "max_qi"        : "��Ѫ���ֵ", // weapon/armor/rings
        "max_jingli"    : "�������ֵ", // weapon/armor/rings
        "max_jing"      : "�������ֵ", // weapon/armor/rings
        "max_potential" : "Ǳ������",   // weapon/armor/rings
        "max_experience": "�������",   // weapon/armor/rings

        "sword"         : "����",       // weapon
        "blade"         : "����",       // weapon
        "club"          : "����",       // weapon
        "hammer"        : "����",       // weapon
        "staff"         : "�ȷ�",       // weapon
        "whip"          : "�޷�",       // weapon
        "unarmed"       : "ȭ��",       // weapon
        "strike"        : "�Ʒ�",       // weapon
        "cuff"          : "ȭ��",       // weapon
        "hand"          : "�ַ�",       // weapon
        "finger"        : "ָ��",       // weapon
        "claw"          : "צ��",       // weapon

        "attack"        : "����",       // weapon
        "parry"         : "�м�",       // armor
        "dodge"         : "����",       // armor
        "defense"       : "����",       // armor

        "ref_neili"     : "�����ָ�",   // armor/rings
        "ref_qi"        : "�����ָ�",   // armor/rings
        "ref_jing"      : "�����ָ�",   // armor/rings
        "suck_neili"    : "͵ȡ����",   // weapon/rings ����͵ȡ���������е���ʱ��һ�����ʰ��˺�ֵ��һ�����ʻظ�����
        "suck_qi"       : "͵ȡ����",   // weapon/rings ����͵ȡ���������е���ʱ��һ�����ʰ��˺�ֵ��һ�����ʻظ�����

        "gold_find"     : "��ȡ�ƽ���",       // weapon/rings
        "magic_find"    : "Ѱ����(MFֵ)",       // weapon/rings
                
        // �����˺����䶳�˺��������˺��������˺������𣬿����������磬����
        "add_poison"    : "���˺�",     // weapon
        "add_metal"     : "���˺�",     // weapon
        "add_wood"      : "ľ�˺�",     // weapon
        "add_water"     : "ˮ�˺�",     // weapon
        "add_fire"      : "���˺�",     // weapon
        "add_earth"     : "���˺�",     // weapon   
        "reduce_metal"  : "����",       // armor
        "reduce_wood"   : "��ľ",       // armor
        "reduce_water"  : "��ˮ",       // armor
        "reduce_fire"   : "����",       // armor
        "reduce_earth"  : "����",       // armor
        "reduce_poison" : "����",       // armor
        "avoid_poison"  : "�����ж�",   // armor/rings

        "research_effect"       : "�о�Ч��",   // weapon/armor/rings
        "practice_effect"       : "��ϰЧ��",   // weapon/armor/rings
        "study_effect"          : "����Ч��",   // weapon/armor/rings
        "learn_effect"          : "ѧϰЧ��",   // weapon/armor/rings
        "derive_effect"         : "��ȡЧ��",   // weapon/armor/rings
        "research_times"        : "�о�����",   // weapon/armor/rings
        "learn_times"           : "ѧϰ����",   // weapon/armor/rings
        "practice_times"        : "��ϰ����",   // weapon/armor/rings
        "study_times"           : "�������",   // weapon/armor/rings
        "derive_times"          : "��ȡ����",   // weapon/armor/rings
        // ���϶��ǻ������� 
        
        "ap_power"      : "���й�����",         // weapon/rings
        "dp_power"      : "���з�����",         // armor
        "da_power"      : "�����˺���",         // weapon/rings
        "avoid_defense" : "��������Ŀ�����",   // weapon/rings
        "avoid_parry"   : "��������Ŀ���м�",   // weapon/rings
        "avoid_dodge"   : "��������Ŀ�����",   // weapon/rings
        "avoid_force"   : "���������ڹ�����",   // weapon/rings
        "avoid_attack"  : "����Ŀ�����⹥��",   // armor
        
        //"trace"         : "����",       // weapon/rings ���ӶԷ��м�
        //"escape"        : "����",       // armor ��������
        //"proficient"    : "��ͨ",       // weapon/rings ��ͨ��perform�˺��ӳ�
        //"fatal_chance"  : "����",       // weapon/rings ����һ��
        //"antifatal_chance": "������",   // armor
   
        "attack_chance" : "������",             // weapon/rings ���پ������ӳ��еļ���
        "double_damage" : "˫���˺�",           // weapon/rings ����ɱ������һ��ɱ����������˫���˺����ĸ�������1%
        "through_armor" : "�Ƽ�",               // weapon/rings �Ƽ�-����ʱ����Ŀ����ߵı�����through_armor
        
        "qi_vs_neili"   : "���������תΪ����", // rings 30%�Ļ������������x%ת��Ϊ����
        
        //"block_heal"    : "��ֹ��������",       // weapon
        "absorb_blood"  : "��ħ����",           // weapon/rings �ٻ���ħս��

        "add_reward"    : "��ȡ���⽱��",       // weapon/rings
        "add_exp"       : "��ȡ���⾭��",       // weapon/rings
        "add_pot"       : "��ȡ����Ǳ��",       // weapon/rings
        "add_mar"       : "��ȡ�������",       // weapon/rings
        "add_force"     : "��ȡ������������",   // weapon/rings

        // ���ѷ�����ǿbuff
        // �Թ����debuff
        
        "add_blind"     : "��ä",                       // weapon �ռ����� ��ä-�ö���ʧ��
        "add_freeze"    : "����",                       // weapon �ռ����� ����-�ٻ��������Է�����������pfm�ٶȽ��ͣ����κη������޶��������мܣ����ǰ���
        "add_burning"   : "����",                       // weapon �ռ����� ����-һ��ʱ����Ŀ�겻ͣ�ļ�����������Ѫcondition
        "add_dizziness" : "ѣ��",                       // weapon �ռ����� ��˯-ѣ�Σ����ܽ����κ��ж���������ͨ������ٻظ����ܵ�����������������15����һֱ���������ս��״̬����˯��������һ����սʱ���Ȱ�һ�������ų���ս����ר�ĶԸ������˵ļ���
        "add_forget"    : "����",                       // weapon �ռ����� ����-ʹ�Է��������м��ܵľ���add_oblivion   
        "add_weak"      : "����",                       // weapon �ռ�����
        "add_busy"      : "æ��",                       // weapon �ռ�����

        "avoid_blind"   : "������ä",                   // armor/rings �ռ�����
        "avoid_freeze"  : "���ӱ���",                   // armor/rings �ռ�����
        "avoid_burning" : "��������",                   // armor/rings �ռ�����
        "avoid_dizziness": "����ѣ��",                  // armor/rings �ռ�����
        "avoid_forget"  : "��������",                   // armor/rings �ռ�����
        "avoid_weak"    : "��������",                   // armor/rings �ռ�����
        "avoid_busy"    : "����æ��",                   // armor/rings �ռ�����
        "reduce_busy"   : "����æ��",                   // armor/rings �ռ�����

        "fatal_blow"    : "��ɱ",                       // weapon �ռ����� ��ɱ��-ӵ��20%�ļ�������Ŀ�������x%     
        "slaughter"     : "ɱ¾",                       // weapon ɱ¾-����ʱ�м��ʶԵ�ǰ�������е��˽���һ�ι���     
        //"anti_fatal"    : "����ɱ��",
        "add_skill"     : "���м���",                   // weapon/rings �ռ�����
        "add_damage"    : "׷���˺�",                   // weapon �ռ�����
        "reduce_damage" : "�����˺�",                   // armor �ռ����� 
        "full_self"     : "ս����",                   // armor �ռ����� ս����-��Ѫ�Զ��ָ�
        "avoid_call"    : "��������",                   // armor/rings �ռ�����
        "counter_damage": "�˺�����",                   // armor �ռ����� �ܵ��˺�ʱ30%���ʵ��˺�x%������Է�
]);


// ��ʯ��Ϊ4���ȼ�����Ƭ�����1��ϡ��1+1����֮1+2
// һ���̶�������(��ľˮ����)+1-2���������

// �ٷֱȵ�����
string *percent_props = ({
        "gold_find", "magic_find", "add_metal", "add_wood", "add_water", "add_fire", "add_earth", 
        "add_poison", "reduce_metal", "reduce_fire", "reduce_wood", "reduce_water", "reduce_earth",
        "reduce_poison", "avoid_poison", "research_effect", "learn_effect", "practice_effect", 
        "derive_effect", "study_effect", "ap_power", "dp_power", "da_power", "avoid_attack", 
        "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force", "trace,escape", "attack_chance",
        "double_damage", "through_armor", "qi_vs_neili", "block_heal", "absorb_blood", "add_reward",
        "add_exp", "add_pot", "add_mar", "add_force", "add_blind", "add_freeze", "add_burning", "add_dizziness",
        "add_forget", "add_weak", "add_busy", "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness",
        "avoid_forget", "avoid_weak", "avoid_busy", "reduce_busy", "fatal_blow", "anti_fatal", "slaughter",
        "add_damage", "reduce_damage", "full_self", "avoid_call", "counter_damage",
});

// ��ʯ����ֵ
mapping prop_values = ([
        "damage1"       : ({ 600, 800, 1000, 1200, 1400, 1600, 2000, }),
        "armor1"        : ({ 300, 400, 500, 600, 700, 800, 900, }),
        "damage2"       : ({ 4600, 6600, 9600, 13600, 18600, 24600, 31600, 39600, 50000, }),
        "armor2"        : ({ 2200, 2900, 3700, 4600, 5600, 7700, 8900, 10200, 11500, }),
        
        "str,con,dex,int,kar,per"     : ({ 1, 2, 3, }),         // 200
        "attribute"     : ({ 1, 2, 3, }),       // 27
        
        "max_qi"        : ({ 2500, 3500, 4500, }),              // 200000
        "max_jing"      : ({ 1200, 1700, 2200, }),              // 100000
        "max_jingli"    : ({ 2500, 3500, 4500, }),              // 200000
        "max_neili"     : ({ 6000, 8000, 10000, }),             // 500000
        "max_potential,max_experience"  : ({ 30000, 40000, 50000, }),   // 2000000
        
        "attack,sword,blade,hammer,staff,club,whip,unarmed,strike,cuff,hand,finger,claw": ({ 100, 150, 200, }),        // 500
        "defense,parry,dodge"  : ({ 50, 60, 70, }),

        "ref_jing,ref_qi"       : ({ 10, 15, 20, }),    // 1000
        "suck_qi,suck_jing,suck_neili"  : ({ 200, 300, 400, }),   // 1000
        
        "gold_find"     : ({ 2, 3, 4, }),       // 92
        "magic_find"    : ({ 1, 2, 3, }),       // 70
        
        "add_metal,add_wood,add_water,add_fire,add_earth"    : ({ 1, 2, 3, }),       // 42
        "add_poison"    : ({ 1, 2, 3, }),       // 42
        "reduce_metal,reduce_fire,reduce_wood,reduce_water,reduce_earth"     : ({ 1, 1, 1, }), // 35
        "reduce_poison,avoid_poison"    : ({ 1, 1, 1, }),       // 44
        
        "research_times,learn_times,practice_times,derive_times,study_times"    : ({ 5, 10, 15, }),    // 1000
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect"       : ({ 1, 2, 3, }), // 180
                
        "ap_power,dp_power,da_power"    : ({ 1, 2, 3, }),       // 70
        "avoid_attack,avoid_defense,avoid_parry,avoid_dodge,avoid_force": ({ 1, 2, 3, }),       // 70
        
        "trace,escape"  : ({ 1, 2, 3, }),       
        "attack_chance" : ({ 1, 2, 3, }),       // 70
        "double_damage,through_armor"   : ({ 1, 2, 3, }),       // 70
        "qi_vs_neili"   : ({ 5, 6, 7, }),       // 63
        "block_heal"    : ({ 3, 4, 5, }),       // 63
        "absorb_blood"  : ({ 1, 2, 3, }),       // 70
        
        "add_reward"    : ({ 1, 2, 3, }),       // 70
        "add_exp,add_pot,add_mar,add_force"     : ({ 2, 3, 4, }),       // 92
        
        "add_blind,add_freeze,add_burning,add_dizziness,add_forget,add_weak,add_busy"   : ({ 1, 2, 3 }),        // 42 
        "avoid_blind,avoid_freeze,avoid_burning,avoid_dizziness,avoid_forget,avoid_weak,avoid_busy,reduce_busy" : ({ 1, 1, 1, }), // 44
        "fatal_blow"    : ({ 3, 4, 5, }),       // 60
        "anti_fatal"    : ({ 1, 2, 3 }),        
        "slaughter"     : ({ 1, 2, 3 }),        // 42
        "add_skill"     : ({ 10, 15, 20, }),    // 500
        "add_damage"    : ({ 3, 4, 5, }),       // 60
        "reduce_damage" : ({ 1, 1, 1, }),       // 35
        "full_self"     : ({ 1, 1, 1, }),       // 35
        "avoid_call"    : ({ 1, 1, 1, }),       // 44
        "counter_damage": ({ 1, 1, 1, }),       // 70
]);

// ����ǿ��ֵ1-9��
mapping steady_values = ([
        "damage1,damage2"       : ({ 4600,6600,9600,13600,18600,24600,31600,39600,50000 }),
        "armor1,armor2"         : ({ 2200,2900,3700,4600,5600,7700,8900,10200,11500 }),
        
        "str,con,dex,int,kar,per,attribute"     : ({ 5, 7, 9, 11, 14, 17, 20, 25, 30, }),
        
        "max_qi"        : ({ 1000, 2000, 3000, 5000, 7000, 9000, 12000, 15000, 20000, }),
        "max_jing"      : ({ 500, 1000, 1500, 2500, 3500, 4500, 6000, 7500, 10000, }),
        "max_jingli"    : ({ 1000, 2000, 3000, 5000, 7000, 9000, 12000, 15000, 20000, }),
        "max_neili"     : ({ 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 100000, }),
        "max_potential,max_experience"  : ({ 200000, 400000, 600000, 1000000, 1500000, 2000000, 3000000, 4000000, 6000000, }),
        
        "attack,sword,blade,hammer,staff,club,whip,unarmed,strike,cuff,hand,finger,claw": ({ 20, 30, 40, 60, 80, 110, 150, 200 }),
        "dodge,parry,defense"   : ({ 10, 15, 20, 25, 30, 35, 40, 45, 60 }),

        "ref_jing,ref_qi"       : ({ 60, 70, 80, 100, 120, 140, 160, 180, 200, }),
        "suck_qi,suck_jing,suck_neili"  : ({ 20, 40, 60, 100, 150, 200, 250, 300, 400, }),
        
        "gold_find"     : ({ 2, 4, 6, 8, 10, 12, 14, 16, 20, }),
        "magic_find"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        
        "add_poison,add_metal,add_wood,add_water,add_fire,add_earth"    : ({ 6, 8, 10, 13, 16, 19, 22, 25, 28, }),
        "reduce_poison,avoid_poison,reduce_metal,reduce_fire,reduce_wood,reduce_water,reduce_earth"     : ({ 1, 2, 3, 4, 5, 5, 5, 5, 5, }),
        
        "research_times,learn_times,practice_times,derive_times,study_times"    : ({ 10, 25, 20, 25, 30, 35, 40, 45, 50 }),
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect"       : ({ 8, 10, 12, 15, 18, 21, 25, 35, 40, }),
                
        "ap_power,da_power"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "dp_power"      : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "avoid_defense,avoid_parry,avoid_dodge,avoid_force": ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "avoid_attack"  : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        
        "trace,escape"  : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "attack_chance" : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "double_damage,through_armor"   :  ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "qi_vs_neili"   : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "block_heal"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "absorb_blood"  : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        
        "add_reward"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "add_exp,add_pot,add_mar,add_force"     : ({ 5, 7, 9, 12, 15, 18, 22, 26, 30, }),
        
        "add_blind,add_freeze,add_burning,add_dizziness,add_forget,add_weak,add_busy"   : ({ 3, 5, 7, 9, 12, 15, 18, 21, 25, }),
        "avoid_blind,avoid_freeze,avoid_burning,avoid_dizziness,avoid_forget,avoid_weak,avoid_busy,reduce_busy" : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "fatal_blow"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "anti_fatal"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "slaughter"     : ({ 6, 8, 10, 13, 16, 19, 22, 25, 29, }),
        "add_skill"     : ({ 20, 30, 40, 60, 80, 110, 150, 250 }),
        "add_damage"    : ({ 3, 5, 7, 9, 12, 15, 18, 21, 25, }),
        "reduce_damage" : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "full_self"     : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "avoid_call"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "counter_damage": ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
]);

// װ����Ʒ����6����ǰ2��Ʒ������û�����⣬��ϡ�У���������Ʒ����ʼ����������
// ��ʯ�ĵȼ���3������ʯ������Ӧ�ú�װ��ǰ2��Ʒ��������һ��
// qlvl1ֻ�л������ԣ�qlvl2���б�ʯ���ԣ�qlvl3ӵ�б�ʯ���ԣ�qlvl4ӵ��ʷʫ���ԣ�qlvl5ӵ�д�˵���ԣ�qlvl6ӵ����������
mixed weapon_props = ({
        ({ "damage1", "int", "str", "con", "dex", "kar", "skill", "attack", 
           "suck_neili", "suck_qi", "gold_find", "magic_find", "add_poison",
           "research_times", "learn_times", "practice_times", "derive_times",
           "study_times", "research_effect", "learn_effect", "practice_effect",
           "derive_effect", "study_effect", "ap_power", "da_power", "avoid_defense",
           "avoid_parry", "avoid_dodge", "avoid_force", "attack_chance", "double_damage",
           "through_armor", "absorb_blood", "add_exp", "add_pot", "add_mar", "add_force",
           "add_reward", "add_blind", "add_freeze", "add_burning", "add_dizziness", "add_weak", 
           "add_forget", "add_busy", "fatal_blow", "slaughter", "add_skill", "add_damage", 
           "max_neili", "max_qi", "max_jing", "max_jingli", "max_potential", "max_experience",
        }),
        ({ "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect", 
           "attack", "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "suck_qi",
           "suck_neili", "avoid_force", "add_exp", "add_pot", "add_mar", "add_force", "skill", // skill���⴦�� 
        }), 
        ({ "through_armor", "slaughter", "double_damage", "add_reward", "absorb_blood", 
           "add_blind", "suck_qi", "suck_neili", "add_exp", "add_pot", "add_mar", "add_force",
           "research_effect", "practice_effect", "study_effect", "derive_effect", "add_reward",
           "ap_power", "da_power",
        }),
        ({ "add_reward", "add_blind", "add_freeze", "add_burning", "add_dizziness", "add_weak", 
           "add_forget", "add_busy", "fatal_blow", "slaughter", "add_skill", "add_damage",
           "research_effect", "practice_effect", "derive_effect", "add_reward",
           "ap_power", "da_power", "through_armor", 
        }),
});

mixed armor_props = ({
        ({ "armor1", "int", "str", "con", "dex", "kar", "max_neili", "max_qi", "max_jing",
           "max_jingli", "max_potential", "max_experience", "parry", "dodge", "defense",
           "ref_neili", "ref_jing", "ref_qi", "reduce_poison", "avoid_poison", "research_times",
           "learn_times", "practice_times", "derive_times", "study_times", "research_effect",
           "learn_effect", "practice_effect", "derive_effect", "study_effect", "dp_power", "avoid_attack",
           "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "avoid_busy", "reduce_busy", "reduce_damage", "full_self", "avoid_call", "counter_damage",
        }),
        ({ "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect", 
           "reduce_poison", "avoid_poison", "max_qi", "max_jing",
        }),
        ({ "ref_neili", "ref_jing", "ref_qi", "avoid_attack", "dp_power", "avoid_blind", "avoid_call",
           "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect",
        }),
        ({ "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "avoid_busy", "reduce_busy", "reduce_damage", "full_self", "avoid_call", "counter_damage",
           "research_effect", "practice_effect", "derive_effect", "dp_power",
        }),
});

// ����amulet����ָring�����������charm
mixed ring_props = ({
        ({ "per", "attribute", "max_neili", "max_qi", "max_jing", "max_jingli", "max_potential",
           "max_experience", "ref_neili", "ref_jing", "ref_qi", "suck_neili", "suck_qi", "gold_find",
           "magic_find", "avoid_poison", "research_times", "learn_times", "practice_times", "derive_times",
           "study_times", "research_effect", "learn_effect", "practice_effect", "derive_effect", "study_effect",
           "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force", "attack_chance",
           "double_damage", "through_armor", "qi_vs_neili", "absorb_blood", "add_exp", "add_pot", "add_mar", "add_force",
           "add_reward", "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "avoid_busy", "reduce_busy", "add_skill", "avoid_call",
        }),
        ({ "attribute", "gold_find", "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect", 
           "reduce_poison", "avoid_poison", "max_qi", "max_jing", "add_exp", "add_pot", "add_mar", "add_force", 
        }),
        ({ "magic_find", "suck_neili", "suck_qi" "qi_vs_neili", "research_effect", "practice_effect", "derive_effect",
           "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force", "attack_chance", "absorb_blood",
           "add_exp", "add_pot", "add_mar", "add_force", "add_reward",
        }),
        ({ "add_reward", "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "avoid_busy", "reduce_busy", "add_skill", "avoid_call", "magic_find", "qi_vs_neili", "double_damage", "through_armor",
           "research_effect", "practice_effect", "derive_effect","add_exp", "add_pot", "add_mar", "add_force", "add_reward",
        }),
});

// �׻��ı������� 
string *suit_weapon_props = ({
        "double_damage", "avoid_forget", "add_damage", "add_skill", "fatal_blow", "add_busy", "add_weak", "add_dizziness",
        "add_burning", "add_freeze",
        
});
// �׻��ķ������� 
string *suit_armor_props = ({
        "reduce_busy", "avoid_busy", "avoid_weak", "avoid_dizziness", "avoid_burning", 
        "counter_damage", "add_forget", "avoid_call", "full_self", "reduce_damage", 
});
// �׻��Ļ��������
string *suit_ring_props = ({
        "magic_find", "add_exp", "add_pot", "add_mar", "add_force", "suck_neili", "suck_qi",
        "add_reward", "full_self", "avoid_busy", "avoid_forget", "avoid_call", "antifatal_chance",
});

void create()
{
        seteuid(getuid());
        set("name", "װ������");
        set("id", "equipmentd");
}

// Ϊ��������ƥ������
varargs string chinese(string prop, int value)
{
        string desc;

        if( !undefinedp(all_props[prop]) )
                desc = all_props[prop];
        else
                desc = to_chinese(prop);

        if( !value ) return desc;

        if( member_array(prop, percent_props) != -1 )
                desc = sprintf(HIB "%s %s%d%s" NOR, desc,
                               value > 0 ? "+" : "-", abs(value), "%");
        else
                desc = sprintf(HIB "%s %s%d" NOR, desc,
                               value > 0 ? "+" : "-", abs(value));

        return desc;
}

// ��ȡװ������������
varargs int query_prop_value(string prop, int ilvl, int s)
{
        int i, j, flag;
        int *value;
        mapping data;
        string *ks;
        string *temp_str;

        flag = 0;
        if( s ) data = copy(steady_values); // ǿ������
        else data = copy(prop_values);
        ks = keys(data);
        for( i=0; i<sizeof(ks); i++ ) {
                //reset_eval_cost();
                temp_str = explode(ks[i], ",");
                for( j=0; j<sizeof(temp_str); j++ )
                        if( temp_str[j] == prop ) {
                                value = data[ks[i]];
                                flag = 1;
                                break;
                        }
                if( flag ) break;
        }
        if( !flag || !value ) return 0;
        if( ilvl ) {
                if( ilvl > sizeof(value) )
                        ilvl = sizeof(value);

                return value[ilvl-1];
        }
        return value[random(sizeof(value))];
}

// װ���̻�ʱ���õ�����
mapping apply_ultimate_prop(object ob, string type, int ilvl)
{
        string *props;
        string prop;
        mapping apply;
        int value, n;

        apply = ([]);

        if( type == "weapon"
        ||  type == "sword"
        ||  type == "blade"
        ||  type == "whip"
        ||  type == "hammer"
        ||  type == "staff"
        ||  type == "club"
        ||  type == "hands"
        ||  type == "finger" )
                props = suit_weapon_props;
        else
        if( type == "rings"
        ||  type == "charm"
        ||  type == "myheart"   // ���������
        ||  type == "myheart2"  // ���������
        ||  type == "neck" )
                props = suit_ring_props;
        else
                props = suit_armor_props;

        n = 1;
        if( random(10000) == 1 )
                n = 2;
        while( n > 0 )
        {
                prop = props[random(sizeof(props))];
                props -= ({ prop });

                value = (int)query_prop_value(prop, ilvl);
                apply[prop] = value;

                n--;
        }
        return apply;
}

// ���ɱ�ʯ����
varargs mapping apply_gem_prop(string type, int ilvl, int n)
{
        string *props;
        string prop;
        mapping apply;
        int value;

        apply = ([]);
      
        if( type == "weapon"
        ||  type == "sword"
        ||  type == "blade"
        ||  type == "whip"
        ||  type == "hammer"
        ||  type == "staff"
        ||  type == "club"
        ||  type == "hands"
        ||  type == "finger" )
                props = weapon_props[0]; // ��ȡ��Ӧ��Ʒ������
        else
        if( type == "rings"
        ||  type == "charm"
        ||  type == "myheart"   // ���������
        ||  type == "myheart2"  // ���������
        ||  type == "neck" )
                props = ring_props[0];
        else
                props = armor_props[0];
        
        if( !n ) n = 1 + random(3);

        while( n > 0 )
        {
                prop = props[random(sizeof(props))];
                props -= ({ prop });

                if( prop == "skill" ) // skill�������
                {
                        int rate;
                        rate = random(100);
                        if( type == "finger" )
                        {
                                if( rate < 50 )
                                        prop = "claw";
                                else
                                        prop = "finger";
                        } else
                        if( type == "hands" )
                        {
                                if( rate < 25 )
                                        prop = "unarmed";
                                else if( rate < 50 )
                                        prop = "cuff";
                                else if( rate < 75 )
                                        prop = "hand";
                                else
                                        prop = "strike";
                        } else
                                prop = type;
                }
                value = (int)query_prop_value(prop, ilvl);
                apply[prop] = value;

                n--;
        }
        return apply;
}

// ����װ������
mapping apply_props(string type, int ilvl, int n)
{
        mapping applied_prop;
        mapping enchase_prop;
        mapping data = ([]);
        string *apply;
        mixed insert;
        int i, j;

        applied_prop = ([]);
        insert = ([]);
        
        if( !n ) return data;
        for( i=1; i<=n; i++ ) // ������
        {
                enchase_prop = copy(apply_gem_prop(type, ilvl));
                apply = keys(enchase_prop);
                for( j=0; j<sizeof(apply); j++ )
                {
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[apply[j]]) )
                                applied_prop[apply[j]] = enchase_prop[apply[j]];
                        else
                                applied_prop[apply[j]] += enchase_prop[apply[j]];
                }
                insert[to_string(i)] = (["name" : HIM"��ʯ"NOR, "id" : "magic stone", "apply_prop" : enchase_prop]);
        }
        
        data["apply_prop"] = applied_prop;
        data["insert"] = insert;
        return data;
}

protected mapping trans_data(string mark)
{
        int     i;
        mixed   temp_value;
        string  temp_str, temp_str2;
        string *temp_arr, *temp_val;
        string  temp_key, key;
        mapping temp_status;
        mapping temp_map, temp_map2;

        temp_status = ([ ]);

        // ����insert
        if( sscanf(mark, "%s<insert>%s</insert>", mark, temp_str2) == 2 ) 
        {
                while (sscanf(temp_str2, "%*s[%s]%s[/%s]%s", key, temp_str, key, temp_str2) > 3)
                {
                        temp_map = ([ ]);
                        temp_map2 = ([ ]);
                        temp_arr = explode(temp_str, "\n");
                        if( sizeof(temp_arr) < 2 ) {
                                if( atoi(temp_str) )
                                        temp_map2[key] = atoi(temp_str);
                                else
                                        temp_map2[key] = temp_str;

                        } else {
                                for ( i=0; i<sizeof(temp_arr); i++ ) {
                                        //temp_arr[i] = replace_string(temp_arr[i], " ", "");
                                        if( sscanf(temp_arr[i], "%s:%d", temp_key, temp_value) != 2 )
                                                sscanf(temp_arr[i], "%s:%s", temp_key, temp_value);

                                        // ����VALUE
                                        if( stringp(temp_value) && strsrch(temp_value, '/') != -1 ) {
                                                temp_val = explode(temp_value, "/");
                                                temp_value = ({});
                                                for (i = 0; i <sizeof(temp_val); i++)
                                                        if( atoi(temp_val[i]) )
                                                                temp_value += atoi(temp_val[i]);
                                                        else
                                                                temp_value += temp_val[i];
                                        }
                                        // ����KEY
                                        if( stringp(temp_key) && strsrch(temp_key, '/') != -1 )
                                                _set( temp_map, explode(temp_key, "/"), temp_value );
                                        else
                                                temp_map[temp_key] = temp_value;
                                        
                                        if( !undefinedp(temp_map["name"]) )
                                                temp_map["name"] = trans_color(temp_map["name"], 3);
                                }
                                temp_map2[key] = temp_map;                             
                        }
                }
                temp_status["insert"] = temp_map2;
        }   
        
        // ��ʼ����
        while (sscanf(mark, "%*s<%s>%s</%s>%s", key, temp_str, key, mark) > 3)
        {
                temp_map = ([ ]);
                temp_arr = explode(temp_str, "\n");
                if( sizeof(temp_arr) < 2 ) {
                        if( sscanf(temp_arr[0], "%s:%d", temp_key, temp_value) == 2 ||
                            sscanf(temp_arr[0], "%s:%s", temp_key, temp_value) == 2 ) {
                               // ����VALUE
                                if( stringp(temp_value) && strsrch(temp_value, '/') != -1 ) {
                                        temp_val = explode(temp_value, "/");
                                        temp_value = ({});
                                        for (i = 0; i <sizeof(temp_val); i++)
                                                if( atoi(temp_val[i]) )
                                                        temp_value += atoi(temp_val[i]);
                                                else
                                                        temp_value += temp_val[i];
                                }
                                // ����KEY
                                if( stringp(temp_key) && strsrch(temp_key, '/') != -1 )
                                        _set( temp_map, explode(temp_key, "/"), temp_value );
                                else
                                        temp_map[temp_key] = temp_value;
                                        
                                temp_status[key] = temp_map;
                        } 
                        else if( atoi(temp_str) )
                                temp_status[key] = atoi(temp_str);
                        else
                                temp_status[key] = temp_str;

                } else {
                        for ( i=0; i<sizeof(temp_arr); i++ ) {
                                temp_arr[i] = replace_string(temp_arr[i], " ", "");
                                if( sscanf(temp_arr[i], "%s:%d", temp_key, temp_value) != 2 )
                                        sscanf(temp_arr[i], "%s:%s", temp_key, temp_value);

                                // ����VALUE
                                if( stringp(temp_value) && strsrch(temp_value, '/') != -1 ) {
                                        temp_val = explode(temp_value, "/");
                                        temp_value = ({});
                                        for (i = 0; i <sizeof(temp_val); i++)
                                                if( atoi(temp_val[i]) )
                                                        temp_value += atoi(temp_val[i]);
                                                else
                                                        temp_value += temp_val[i];
                                }
                                // ����KEY
                                if( stringp(temp_key) && strsrch(temp_key, '/') != -1 )
                                        _set( temp_map, explode(temp_key, "/"), temp_value );
                                else
                                        temp_map[temp_key] = temp_value;
                        }
                        temp_status[key] = temp_map;
                }
        }
        
        if( !undefinedp(temp_status["name"]) )
                temp_status["name"] = trans_color(temp_status["name"], 3);

        if( !undefinedp(temp_status["mod_name"]) )
                temp_status["mod_name"] = trans_color(temp_status["mod_name"], 3);
                
        if( !undefinedp(temp_status["long"]) )
                temp_status["long"] = trans_color(temp_status["long"], 3) + "\n";

        return temp_status;
}

// ����һ���̶�������������
varargs mixed create_object(string num, int level)
{
        string *list;
        string  mark, part, rec;
        string  type, str;
        string  filename, this_file;
        mapping temp_status;
        mapping temp_function;
        object  ob;

        if( !num || num == "" ) {
                if( !level ) level = random(3);

                switch( random(3) )
                {
                case 0 :
                        rec = "W";
                        if( level == 0) filename = EQUIP_LIST+"basic.weapon";
                        else if( level == 1) filename = EQUIP_LIST+"advance.weapon";
                        else if( level == 2) filename = EQUIP_LIST+"expert.weapon";
                        break;
                case 1 :
                        rec = "A";
                        if( level == 0) filename = EQUIP_LIST+"basic.armor";
                        else if( level == 1) filename = EQUIP_LIST+"advance.armor";
                        else if( level == 2) filename = EQUIP_LIST+"expert.armor";
                        break;
                default:
                        rec = "G";
                        if( level == 0) filename = EQUIP_LIST+"basic.gem";
                        else if( level == 1) filename = EQUIP_LIST+"advance.gem";
                        else if( level == 2) filename = EQUIP_LIST+"expert.gem";
                        break;
                }

                this_file = read_file(filename);
                str = sprintf("%s%d", rec, level);
                list = ({});
                while (sscanf(this_file, "%*s<"+str+part+">%*s</"+str+part+">%*s"))
                {
                        rec = sprintf("%s%s", str, part);
                        list += ({ rec });
                }
                if( !sizeof(list) ) return 0;
                num = list[random(sizeof(list))];
        } else {
                if( num[0] == 'W' ) {
                        if( num[1] == '0' && strlen(num) == 5 )
                                filename = EQUIP_LIST+"basic.weapon";
                        else if( num[1] == '1' && strlen(num) == 5 )
                                filename = EQUIP_LIST+"advance.weapon";
                        else if( num[1] == '2' && strlen(num) == 5 )
                                filename = EQUIP_LIST+"expert.weapon";
                } else if( num[0] == 'A' ) {
                        if( num[1] == '0' && strlen(num) == 5)
                                filename = EQUIP_LIST+"basic.armor";
                        else if(  num[1] == '1' && strlen(num) == 5)
                                filename = EQUIP_LIST+"advance.armor";
                        else if(  num[1] == '2' && strlen(num) == 5)
                                filename = EQUIP_LIST+"expert.armor";
                } else if( num[0] == 'G' ) {
                        if(  num[1] == '0' && strlen(num) == 5)
                                filename = EQUIP_LIST+"basic.gen";
                        else if(  num[1] == '1' && strlen(num) == 5)
                                filename = EQUIP_LIST+"advance.gen";
                        else if(  num[1] == '2' && strlen(num) == 5)
                                filename = EQUIP_LIST+"expert.gen";
                }

                if( !filename )
                        return 0;

                this_file = read_file(filename);
        }

        // ������Ŷ�Ӧ���ַ���
        if( sscanf(this_file, "%*s<"+num+">%s</"+num+">%*s", mark) ) {
                sscanf(mark, "%*s<type>%s</type>%s", type, mark);
                filename = EQUIP_DIR + type;
                temp_status = trans_data(mark);
                temp_function = temp_status["function"];
                if( temp_function )
                        map_delete(temp_status, "function");
                else
                        temp_function = allocate_mapping(0);

                ob = TEMPLATE_D->create_object(filename, temp_status["id"], temp_status, 1, temp_function);
                set("mod_mark", num, ob);
                set("can_sign", 1, ob); // װ��ǩ��
                if( temp_status["mod_level"] )
                        set("mod_level", temp_status["mod_level"], ob);

                return ob;
        } else {
                CHANNEL_D->do_channel(this_object(),"sys", "����һ������������");
                return 0;
        }
}

// ����һ���̶���װ�������������
varargs object create_module(string num, int level)
{
        string mark, part, str, rec;
        string *list;
        string type;
        string filename, this_file;
        mapping temp_status;
        mapping temp_function;
        object ob;

        if( !num || num == "" ) {
                if( !level ) level = random(4);

                if( level == 0 ) filename = EQUIP_LIST+"basic.mod";
                else if( level == 1 ) filename = EQUIP_LIST+"advance.mod";
                else if( level == 2 ) filename = EQUIP_LIST+"expert.mod";
                else if( level == 3 ) filename = EQUIP_LIST+"boss.mod";

                this_file = read_file(filename);
                str = sprintf("A%d", level);
                list = ({});
                while (sscanf(this_file, "%*s<"+str+part+">%*s</"+str+part+">%*s"))
                {
                        rec = sprintf("%s%s", str, part);
                        list += ({ rec });
                }
                if( !sizeof(list) ) return 0;
                num = list[random(sizeof(list))];
        } else {
                if(  num[1] == '0' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"basic.mod";
                else if(  num[1] == '1' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"advance.mod";
                else if(  num[1] == '2' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"expert.mod";
                else if(  num[1] == '3' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"boss.mod";

                this_file = read_file(filename);
        }
        //������Ŷ�Ӧ���ַ���
        if( sscanf(this_file, "%*s<"+num+">%s</"+num+">%*s", mark) )
        {
                sscanf(mark, "%*s<type>%s</type>%s", type, mark);
                filename = EQUIP_DIR + type;
                temp_status = trans_data(mark);
                temp_function = temp_status["function"];
                if( temp_function )
                        map_delete(temp_status, "function");
                else
                        temp_function = allocate_mapping(0);

                ob = TEMPLATE_D->create_object(filename, temp_status["id"], temp_status, 1, temp_function);
                set("mod_mark", num, ob);
                set("can_sign", 1, ob); // װ��ǩ��
                //if( temp_status["mod_level"] )
                //        set("mod_level", temp_status["mod_level"], ob);

                return ob;
        } else {
                CHANNEL_D->do_channel(this_object(), "sys", "����һ����װ��������");
                return 0;
        }
}

// ����һ����̬�����
public varargs object create_dynamic(string obj_type, int ilvl, int mf, int flag)
{
        mapping temp_status, all_list, data;
        mapping applied_prop = ([]);
        mapping insert;
        string *all_id, *types;
        string id;
        string *file;
        string color, filename;
        string base_type;
        object ob;
        int qlvl;
        int rate, n, uf, sf, rf;
        string prop, *props;

        if( !ilvl || ilvl < 1 )
                return 0;

        if( !obj_type || obj_type == "" ) { // �������װ�������ʯ
                rate = random(100);
                if( rate < 30 ) obj_type = "weapon";
                else if( rate < 70 ) obj_type = "armor";
                else if( rate < 90 ) obj_type = "rings";
                else obj_type = "gem";
                flag = 0;
        }

        if( flag ) { // ָ���ı������͡��������ͻ�ʯ����
                if( flag == 1 ) {
                        if( member_array(obj_type, weapon_type) != -1 )
                                base_type = "weapon";
                        else if( member_array(obj_type, armor_type) != -1 )
                                base_type = "armor";
                        else if( member_array(obj_type, rings_type) != -1 )
                                base_type = "rings";
                        else    base_type = "gem";
                } else {
                        // ϵͳ�̶������ƺ�ID��װ��
                        all_list = type_list[obj_type];
                        all_id = values(all_list);
                        id = all_id[random(sizeof(all_id))];
                }
        } else {
                base_type = obj_type;
                types = all_type[obj_type];
                obj_type = types[random(sizeof(types))]; // ���һ��
        }

        if( flag && flag > 1 ) // ��ģ���ļ�����Ҫ���д��
                filename = sprintf("%s%s/%s.c", TEMPLATE_DIR, base_type, obj_type);
        else
                filename = sprintf("%s%s/%s.c", EQUIP_DIR, base_type, obj_type);

        data = ([]);
        temp_status = ([]);
        rate = random(100);
        if( rate < 40 ) data["str"] = ilvl*2 + random(ilvl);
        else if( rate < 60 ) data["con"] = ilvl*2 + random(ilvl);
        else if( rate < 80 ) data["dex"] = ilvl*2 + random(ilvl);
        else data["int"] = ilvl*2 + random(ilvl);

        data["level"] = ilvl;
        temp_status["require"] = copy(data); // ����װ��Ҫ��

        if( base_type != "gem" ) // ����װ�����Ǳ�ʯ
        {
                // ������������ͨ0������1����ϡ2��ʷʫ3����˵4������5
                // ����6�ף�����4�ף������3�ף�����4��
                
                if( !mf ) mf = 0;
                
                if( mf <= 10 )
                        uf = sf = rf = mf;
                
                uf = mf*20/(mf+20);  // ��˵Ʒ��
                sf = mf*200/(mf+200);  // ʷʫƷ��
                rf = mf*600/(mf+600);  // ��ϡƷ��
                                     
                rate = random(100);
                if( rate < uf )
                {
                        if( base_type == "weapon" )
                                n = 4;       // ��������
                        else if( base_type == "armor" )
                                n = 3;
                        else // �����
                                n = 3;
                        qlvl = 5; 
                        color = HIY; // ��˵
                } else
                if( rate < sf )
                {
                        n = 3;
                        qlvl = 4;
                        color = HIM; // ʷʫ
                } else
                if( rate < rf )
                {
                        n = 2;
                        qlvl = 3;
                        color = HIR; // ��ϡ
                }
                else
                if( rate < mf )
                {
                        n = 1;
                        qlvl = 2;
                        color = HIB; // ����
                }
                else
                {
                        n = 0;
                        qlvl = 1;
                        color = HIW; // ��ͨ
                }
                data = ([]);
                if( n > 1 )
                        n = random(n); // ���������
                if( n > 0 )
                {
                        data = apply_props(obj_type, ilvl/10, n);
                        data["flute"] = n; //socket
                        data["used"] = n;
                        insert = data["insert"];
                        map_delete(data, "insert");
                        temp_status["enchase"] = copy(data); // ����װ������ buff/enchase ?
                        temp_status["insert"] = insert;      // ��۱�ʯ����
                }
                if( qlvl > 5 ) // ����
                {
                        if( base_type == "weapon" )          // ���������ߡ������
                                props = weapon_props[3];
                        else if( base_type == "armor" )  
                                props = armor_props[3];
                        else 
                                props = ring_props[3];
                                
                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl);               
                }
                if( qlvl > 4 ) // ��˵
                {
                        if( base_type == "weapon" )    
                                props = weapon_props[2];
                        else if( base_type == "armor" )  
                                props = armor_props[2];
                        else 
                                props = ring_props[2];
                                
                        prop = props[random(sizeof(props))];                
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl);  
                }
                if( qlvl > 3 ) // ʷʫ
                {
                        if( base_type == "weapon" )    
                                props = weapon_props[1];
                        else if( base_type == "armor" )  
                                props = armor_props[1];
                        else 
                                props = ring_props[1];
                                
                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl);  
                } 
                if( qlvl > 2 ) // ��ϡ
                {
                        if( base_type == "weapon" )    
                                props = weapon_props[0];
                        else if( base_type == "armor" )  
                                props = armor_props[0];
                        else 
                                props = ring_props[0];
                                
                        prop = props[random(sizeof(props))];    
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl);         
                } 
                        
                if( base_type == "weapon" )
                {
                        temp_status["weapon_prop"] = ([ "damage" : (ilvl+15)*qlvl*10 ]); // ��������-�˺�                        
                        if( applied_prop )
                                temp_status["weapon_prop"] += applied_prop;
                }
                else if( base_type == "armor" )
                {
                        if( obj_type == "hands"
                        ||  obj_type == "finger" )
                        {
                                temp_status["armor_prop"] = ([ "armor" : 10 ]);
                                temp_status["armor_prop"]+= ([ "unarmed_damage" : (ilvl+15)*qlvl*10 ]);
                                if( applied_prop )
                                        temp_status["armor_prop"] += applied_prop;
                        }
                        else
                        {
                                temp_status["armor_prop"] = ([ "armor" : (ilvl+15)*qlvl*2 ]); // ��������-����
                                if( applied_prop )
                                        temp_status["armor_prop"] += applied_prop;
                        }    
                }
                else // �����
                {
                        temp_status["armor_prop"] = ([ "armor" : 10 ]);
                        if( applied_prop )
                                temp_status["armor_prop"] += applied_prop; 
                }
                
                ob = TEMPLATE_D->create_object(filename, obj_type, temp_status, 1);
                set("quality_level", qlvl, ob); // Ʒ��
                set("can_sign", 1, ob); // װ��ǩ��
                set("auto_load", 1, ob); // ���߲���
                if( color )
                        ob->set_color(color); // ������ɫ,x_name���Ѿ�������ɫ�ˣ�
        }
        else // ���䱦ʯ
        {
                // ��ʯ��Ϊ4���ȼ�����Ƭ�����1��ϡ��1+1����֮1+2����ʯӵ�б����ͷ����Լ���Ʒ3�����ԣ�
                // ����δ�����ı�ʯ����
                ob = new("/clone/tessera/gem.c");
                //file = map_array(get_dir("/inherit/template/gem/"), (: "/inherit/template/gem/" + $1 :)); 
                //filename = file[random(sizeof(file))]; 
                //ob = new(filename);
        }

        return ob;
}

public varargs void killer_reward(object killer, object victim, mapping drops)
{
        object ob, *obs;
        string *ks, key, str;
        string ob_file, ob_quality, ob_num, ob_typ;
        int i, n, value, level, team_size, mf, uf, sf, rf;
        int rand, times, score;
        object where;

        if(  !mapp(drops) || !sizeof(drops) )
                return;

        where = environment(victim);
        obs = pointerp(killer->query_team()) ? killer->query_team() : ({ killer });
        team_size = sizeof(filter_array(obs, (: objectp($1) && environment($1) == environment($(killer)) :)));

        times = ACTION_D->query_action("boss_reward");
        if( !times ) times = ACTION_D->query_action("fuben_reward");
        if( !times ) times = 1;
        //if( killer->is_vip() ) times = times * 2;
        mf=query_temp("apply/magic_find", killer);
        if( mf <= 10 )
                uf = sf = rf = mf;
                
        uf = mf*250/(mf+250);  // ��˵Ʒ��
        sf = mf*500/(mf+500);  // ʷʫƷ��
        rf = mf*600/(mf+600);  // ��ϡƷ��
        
        score = 0;
        ks = keys(drops);
        for( i=0; i<sizeof(ks); i++ ) {
                key = ks[i];
                score += drops[ks[i]];
        }
        for( i=0; i<sizeof(ks); i++ ) {
                key = ks[i];              
                value = drops[ks[i]];
                value += value * mf/100;
                
                // ���伸�ʹ�ʽ                
                if( team_size >= 5 )
                        value = value * 220 / 100;
                else if( team_size == 4 )
                        value = value * 182 / 100;
                else if( team_size == 3 )
                        value = value * 152 / 100;
                else if( team_size == 2 )
                        value = value * 121 / 100;
                for( n=0; n<times; n++ ) {
                        //rand = random(100);
                        rand = random(score);
                        if( rand < value) {
                                str = key[0..1];
                                // �������йؼ����� F I ��ͷ��ʾΪ����ĳ����Ʒ
                                if( str == "FI" ) {
                                        if( sscanf(key, "FI&%s", ob_file) )
                                                ob = new(ob_file);

                                }
                                // �������йؼ����� N U ��ͷ��ʾΪ����ĳ����ŵ���Ʒ
                                else if( str == "NU" ) {
                                        if(  sscanf(key, "NU&%s", ob_num) )
                                                ob = create_object(ob_num);

                                }
                                // �������йؼ����� T Y ��ͷ��ʾΪ����ĳ�����͵���Ʒ
                                else if( str == "TY" ) {
                                        if(  sscanf(key, "TY&%s%d", ob_typ, level) == 2 )
                                                ob = create_dynamic(ob_typ, level, mf);

                                }
                                // �������йؼ����� M O ��ͷ��ʾΪ����ĳ����ŵ���װ����
                                else if( str == "MO" ) {
                                        if( sscanf(key, "MO&%s", ob_num) )
                                                ob = create_module(ob_num);

                                }
                                // �������йؼ����� R A ��ͷ��ʾΪ����ĳ��Ʒ�ʵĵ������Ʒ���������ĳ��װ��
                                else if( str == "RA" ) {
                                        if( sscanf(key, "RA&%s%d", ob_quality, level) == 2 ) {
                                                switch (ob_quality)
                                                {
                                                case "MODULE"   :
                                                        ob = create_module("", level);
                                                        break;
                                                case "NUMBER"   :
                                                        ob = create_object("", level);
                                                        break;
                                                case "RANDOM"   :
                                                        ob = create_dynamic("", level, mf);
                                                default         :
                                                        break;
                                                }
                                        }
                                }
                                if( objectp(ob) ) {
                                        // HIW+treasure_level+NOR" ��"HIC"ϡ"NOR CYN"��"NOR"��Ʒ
                                        if( query("quality_level", ob) == 3 ) // ��ϡ
                                                CHANNEL_D->channel_broadcast("news",  
                                                        killer->name() + "ɱ��" + victim->name() + NOR YEL"������ʬ���ϼ�����һ"+query("unit", ob)+HIR" ��"NOR RED"ϡ"HIW"�� "NOR YEL+ob->name()+YEL"��\n"NOR);
                                        else if( query("quality_level", ob) == 4 ) // ʷʫ
                                                CHANNEL_D->channel_broadcast("news",  
                                                        killer->name() + "ɱ��" + victim->name() + NOR YEL"������ʬ���ϼ�����һ"+query("unit", ob)+HIM" ʷ"NOR MAG"ʫ"HIW"�� "NOR YEL+ob->name()+YEL"��\n"NOR);
                                        else if( query("quality_level", ob) == 5 ) // ��˵
                                                CHANNEL_D->channel_broadcast("news",  
                                                        killer->name() + "ɱ��" + victim->name() + NOR YEL"������ʬ���ϼ�����һ"+query("unit", ob)+HIY" ��"NOR YEL"˵"HIW"�� "NOR YEL+ob->name()+YEL"��\n"NOR);
                                        else if( query("quality_level", ob) == 6 ) // ����
                                                CHANNEL_D->channel_broadcast("news",  
                                                        killer->name() + "ɱ��" + victim->name() + NOR YEL"������ʬ���ϼ�����һ"+query("unit", ob)+HIY" ��"NOR YEL"��"HIW"�� "NOR YEL+ob->name()+YEL"��\n"NOR);
                                        //message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + ob->name() + NOR + HIC "�����ڵ��ϡ�\n" NOR, victim);
                                        ob->move(killer);                   
                                }
                        }
                }
        }
        mf=query_temp("apply/gold_find", killer);
        if( random(100) < mf )
        {
                ob = new("/clone/money/gold");
                ob->set_amount(random(20)+20);
                ob->move(where);
                message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + ob->name() + NOR + HIC "�����ڵ��ϡ�\n" NOR, victim);
        }

        // ��������Ʒ��ͳһ����giftd�ӿ�
        //GIFT_D->boss_drops(this_object());

        return;
}

