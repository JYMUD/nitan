// ���ļ��� all_room_info_hj.h
// �� 1_room_info_special.h 
// ��  void init() �ڵ��á�

// naihe 0:29 03-10-21


// ��������ǰ�� {} ���������ﶼ�ǲ���Ҫ�ģ���������ڸ����ӣ���������Щ
//void init()
//{

    object me = this_player();

    if( query_temp("huanjing", me) != "start" && !query("hj_game/npc", me) )
    {
        remove_call_out("get_out_here");
        call_out("get_out_here",1, me);
    }
    // �������Ϸʱ������������״̬������
    if( query_temp("huanjing", me) == "start" )
        full_all( me );

    if( query("room_mark") != 1 && query("hj_game/npc", me) )
        return;
// ������� 1 �ŷ��䣬�������� NPC �Ļ���ֱ�� return ���ˣ����
// add_action() �ܺ���Դ��
// ����NPC����Ҫ����һЩ�����Ķ����������������� return ��

    // ��ֹ��ָ��
    add_action( "block_cmds", ({
        "exercise", "dazuo", "respirate",
        "tuna", "practice", "lian",  "exert",
        "study", "du", 
        "to", "scheme", "put",
        "paimai", "jiaoyi", "paimai*", "jiaoyi*",
        "kill", "yun", "pfm", "perform", "hit", "throw", "shoot", "steal", "fight",
        "score", "hp", "hp2", "score2", "score3", "scorenew", "jifa", "enable",
        "jiali", "jiajin", "enforce", "enpower", "prepare", "bei", "inventory",
        "xue", "learn", "skills", "cha", "quest", "questobj",
        "wield", "unwield", "wear", "remove", 
        "new", "new*", "menpai", "menpai*", "jiaoyi", "jiaoy*", "rumor", "rumor*",
        "bangpai", "bangpai*", 
        "bunch", "store", "take", "qu", "cun", 
        "bid", "auction",
    }) );
    add_action("do_look","look");
    add_action("do_get","get");
//}
