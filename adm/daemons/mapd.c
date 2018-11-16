// mapd.c

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;

// ��ʶ��Ӧ�ĵ���
mapping map_short = ([
        "xiyu"      : "����",
        //"gaochang"  : "�߲�����",
        "hasake"    : "�߲�����",
        "xingxiu"   : "���޺�",
        "guanwai"   : "����",
        "yangzhou"  : "����",
        "fuzhou"    : "����",
        "xiangyang" : "����",
        "suzhou"    : "����",
        "hangzhou"  : "����",
        "xihu"      : "����",
        "quanzhou"  : "Ȫ��",
        "lingzhou"  : "����",
        "chengdu"   : "�ɶ�",
        "jingzhou"  : "����",
        "jiaxing"   : "����",
        "nanyang"   : "����",
        "foshan"    : "��ɽ",
        "dali"      : "����",
        "changan"   : "����",
        "hanzhong"  : "����",
        "hengyang"  : "����",
        "beijing"   : "����",
        "shaolin"   : "����",
        "wudang"    : "�䵱",
        "emei"      : "����",
        "qingcheng" : "���",
        "kunlun"    : "����ɽ",
        "zhongnan"  : "����ɽ",
        "henshan"   : "��ɽ",
        "taishan"   : "̩ɽ",
        "huashan"   : "��ɽ",
        "hengshan"  : "��ɽ",
        "songshan"  : "��ɽ",
        "huanghe"   : "�ƺ�",
        "lingjiu"   : "��ɽ",
        "gumu"      : "��Ĺ",
        "meizhuang" : "÷ׯ",
        "tianlongsi": "������",
        "xueshan"   : "ѩɽ",
        "taohua"    : "�һ���",
        "baituo"    : "����ɽ",
        "shenlong"  : "������",
        "yanziwu"   : "������",
        "village"   : "��ɽ��",
        //"xiakedao"  : "���͵�",
        "xiaoyao"   : "��ң��",
        "wanjiegu"  : "��ٹ�",
        "xuedao"    : "��ѩɽ",
        "guiyun"    : "����ׯ",
        "heimuya"   : "��ľ��",
        "motianya"  : "Ħ����",
        "nanhai"    : "�Ϻ�֮��",
        "tiezhang"  : "����ɽ",
        "kaifeng"   : "����",
        "ruzhou"    : "����",
        "zhongzhou" : "����",
        "luoyang"   : "����",
        "lingxiao"  : "������",
        "lanzhou"   : "����",
        "wudujiao"  : "�嶾��",
        "kunming"   : "����",
        "jueqing"   : "�����",
]);

// ��ʶ��Ӧ�ĵ�ͼ�����ļ�(ȫ����HELP_DIR��)
mapping map_to = ([
        "xiyu"      : "map_xy",
        "gaochang"  : "map_xy",
        "xingxiu"   : "map_xxh",
        "guanwai"   : "map_gw",
        "yangzhou"  : "map_yz",
        "fuzhou"    : "map_fz",
        "xiangyang" : "map_xi",
        "suzhou"    : "map_sz",
        "hangzhou"  : "map_hz",
        "quanzhou"  : "map_qz",
        "lingzhou"  : "map_lz",
        "chengdu"   : "map_cd",
        "jingzhou"  : "map_jz",
        "jiaxing"   : "map_jx",
        "nanyang"   : "map_ny",
        "foshan"    : "map_fs",
        "dali"      : ({ "map_dl", "map_dls" }),
        "changan"   : "map_ca",
        "hanzhong"  : "map_hanz",
        "hengyang"  : "map_hy",
        "beijing"   : "map_bj",
        "shaolin"   : "map_sl",
        "wudang"    : "map_wd",
        "emei"      : "map_em",
        "qingcheng" : "map_qc",
        "mingjiao"  : "map_kl",
        "quanzhen"  : ({ "map_zn", "map_cyg" }),
        "henshan"   : ({ "map_ss", "map_hy" }),
        "taishan"   : "map_es",
        "huashan"   : "map_ws",
        "hengshan"  : "map_ns",
        "songshan"  : "map_cs",
        "huanghe"   : "map_hh",
        "lingjiu"   : "map_ljg",
        "gumu"      : "map_gm",
        "meizhuang" : "map_mz",
        "tianlongsi": "map_tls",
        "xueshan"   : "map_xss",
        "taohua"    : "map_thd",
        "baituo"    : "map_bts",
        "shenlong"  : "map_sld",
        "yanziwu"   : "map_yzw",
        "village"   : "map_hsc",
        "xiakedao"  : "map_xkd",
        "xiaoyao"   : "map_xyl",
        "wanjiegu"  : "map_wjg",
        "xuedao"    : "map_xdm",
        "guiyun"    : "map_gyz",
        "heimuya"   : "map_hmy",
        "motianya"  : "map_mty",
        "nanhai"    : "map_nh",
        "tiezhang"  : "map_tz",
        "kaifeng"   : "map_kf",
        "ruzhou"    : "map_rz",
        "zhongzhou" : "map_zz",
        "luoyang"   : "map_ly",
        "lingxiao"  : "map_lxg",
        "lanzhou"   : "map_la",
        "wudujiao"  : ({ "map_wdj", "map_dls" }),
        "honghua"   : "map_hhh",
        "kunming"   : "map_km",
        "jueqing"   : "map_jqg",
        "battle1"   : "map_battle1",
]);

// ���ؽ�ͨ�����
mapping map_trans = ([
        "beijing"   : ([ "name" : "����",     "room" : "/d/beijing/majiu", ]),
        "yangzhou"  : ([ "name" : "����",     "room" : "/d/city/majiu", ]),
        "dali"      : ([ "name" : "����",     "room" : "/d/dali/majiu", ]),
        "foshan"    : ([ "name" : "��ɽ",     "room" : "/d/foshan/majiu", ]),
        "fuzhou"    : ([ "name" : "����",     "room" : "/d/fuzhou/majiu", ]),
        "guanwai"   : ([ "name" : "����",     "room" : "/d/guanwai/majiu", ]),
        "hangzhou"  : ([ "name" : "����",     "room" : "/d/hangzhou/majiu", ]),
        "lanzhou"   : ([ "name" : "����",     "room" : "/d/lanzhou/majiu", ]),
        "lingzhou"  : ([ "name" : "����",     "room" : "/d/lingzhou/majiu", ]),
        "luoyang"   : ([ "name" : "����",     "room" : "/d/luoyang/majiu", ]),
        "yongdeng"  : ([ "name" : "����",     "room" : "/d/yongdeng/majiu", ]),
        "suzhou"    : ([ "name" : "����",     "room" : "/d/suzhou/majiu", ]),
        "xiangyang" : ([ "name" : "����",     "room" : "/d/xiangyang/majiu", ]),
        "yili"      : ([ "name" : "����",     "room" : "/d/xingxiu/majiu", ]),
        "chengdu"   : ([ "name" : "�ɶ�",     "room" : "/d/chengdu/majiu", ]),
        "emei"      : ([ "name" : "����ɽ",   "room" : "/d/emei/majiu1", ]),
        "emei2"     : ([ "name" : "���Ұ�ɽ", "room" : "/d/emei/majiu2", ]),
        "quanzhou"  : ([ "name" : "Ȫ��",     "room" : "/d/quanzhou/majiu", ]),
        "jiaxing"   : ([ "name" : "����",     "room" : "/d/jiaxing/majiu", ]),
        "jingzhou"  : ([ "name" : "����",     "room" : "/d/jingzhou/majiu", ]),
        "nanyang"   : ([ "name" : "����",     "room" : "/d/nanyang/majiu", ]),
        "changan"   : ([ "name" : "����",     "room" : "/d/changan/majiu", ]),
        "hanzhong"  : ([ "name" : "������",   "room" : "/d/hanzhong/majiu", ]),
        "hengyang"  : ([ "name" : "����",     "room" : "/d/henshan/majiu", ]),
        "kaifeng"   : ([ "name" : "����",     "room" : "/d/kaifeng/majiu", ]),
        "kunming"   : ([ "name" : "����",     "room" : "/d/kunming/majiu", ]),
        "zhongzhou" : ([ "name" : "����",     "room" : "/d/zhongzhou/majiu", ]),
]);


// ��ͨ����
mixed connect_info = ({
        ({ "beijing", "guanwai",        300, }),
        ({ "beijing", "lingzhou",       300, }),
        ({ "beijing", "changan",        200, }),
        ({ "beijing", "xiangyang",      180, }),
        ({ "beijing", "luoyang",        160, }),
        ({ "beijing", "nanyang",        150, }),
        ({ "beijing", "kaifeng",        160, }),
        ({ "beijing", "zhongzhou",      150, }),
        ({ "beijing", "yangzhou",       200, }),
        ({ "lingzhou", "yili",          250, }),
        ({ "lingzhou", "kaifeng",       180, }),
        ({ "lingzhou", "lanzhou",       120, }),
        ({ "lingzhou", "yongdeng",      100, }),
        ({ "lingzhou", "changan",       200, }),
        ({ "luoyang", "kaifeng",        140, }),
        ({ "luoyang", "changan",        100, }),
        ({ "luoyang", "yangzhou",       160, }),
        ({ "luoyang", "xiangyang",      100, }),
        ({ "luoyang", "zhongzhou",      120, }),
        ({ "luoyang", "hanzhong",          80, }),
        ({ "luoyang", "nanyang",        120, }),
        ({ "changan", "yili",           250, }),
        ({ "changan", "lanzhou",        100, }),
        ({ "changan", "hanzhong",          50, }),
        ({ "changan", "xiangyang",      200, }),
        ({ "changan", "nanyang",        200, }),
        ({ "changan", "kaifeng",        160, }),
        ({ "changan", "zhongzhou",      100, }),
        ({ "changan", "chengdu",        250, }),
        ({ "changan", "jingzhou",       230, }),
        ({ "changan", "yangzhou",       260, }),
        ({ "yangzhou", "nanyang",       100, }),
        ({ "yangzhou", "kaifeng",       120, }),
        ({ "yangzhou", "xiangyang",     150, }),
        ({ "yangzhou", "hengyang",      250, }),
        ({ "yangzhou", "suzhou",         80, }),
        ({ "yangzhou", "zhongzhou",      80, }),
        ({ "yangzhou", "hangzhou",      120, }),
        ({ "yangzhou", "jiaxing",       150, }),
        ({ "nanyang", "kaifeng",         50, }),
        ({ "nanyang", "zhongzhou",      120, }),
        ({ "xiangyang", "chengdu",      200, }),
        ({ "xiangyang", "jingzhou",      80, }),
        ({ "xiangyang", "dali",         400, }),
        ({ "xiangyang", "kunming",      500, }),
        ({ "xiangyang", "hengyang",     200, }),
        ({ "xiangyang", "zhongzhou",     80, }),
        ({ "chengdu", "jingzhou",       140, }),
        ({ "chengdu", "kunming",        220, }),
        ({ "chengdu", "emei",           150, }),
        ({ "chengdu", "dali",           300, }),
        ({ "dali",  "jingzhou",         180, }),
        ({ "dali",  "kunming",          150, }),
        ({ "emei",  "kunming",          120, }),
        ({ "emei",  "jingzhou",         140, }),
        ({ "emei",  "emei2",             20, }),
        ({ "hengyang", "foshan",        150, }),
        ({ "suzhou", "hangzhou",         80, }),
        ({ "suzhou", "jiaxing",         120, }),
        ({ "suzhou", "quanzhou",        150, }),
        ({ "suzhou", "zhongzhou",        80, }),
        ({ "hangzhou", "jiaxing",        50, }),
        ({ "hangzhou", "quanzhou",      150, }),
        ({ "hangzhou", "fuzhou",        140, }),
        ({ "lanzhou", "yongdeng",       100, }),
        ({ "lanzhou", "yili",           160, }),
        ({ "jiaxing", "fuzhou",         130, }),
        ({ "jingzhou", "kunming",       140, }),
        ({ "fuzhou", "quanzhou",         30, }),
        ({ "kaifeng", "yongdeng",       110, }),
        ({ "kaifeng", "zhongzhou",      100, }),
});

int arrived_dest(object me, mixed follower, object running, object horse, string trans_path);
// �鿴ĳ���ص��Ƿ�MAPD��֪��
public int been_known(string outdoors)
{
        return stringp(map_short[outdoors]);
}

// ���ĳ������ص����������
public string query_map_short(string outdoors)
{
        string str;

        if (stringp(str = map_short[outdoors]))
                return str;

        return "����ص�";
}

// ������л���ص�ļ���
public string *query_all_map_zone()
{
        return keys(map_short);
}

// ���ĳ������ص�ĵ�ͼ
public string query_maps(string outdoors)
{
        mixed maps;
        string file;
        string map_result;

        if (undefinedp(maps = map_to[outdoors]))
                return "δ����ϸ��ͼ��\n";

        if (stringp(maps))
        {
                file = HELP_DIR + maps;
                map_result = read_file(file);
                if (! stringp(map_result))
                        map_result = "�޷���ȡ��ͼ" + file + "��\n";
                map_result = color_filter(map_result);
                return map_result;
        }

        if (arrayp(maps))
        {
                map_result = "";
                foreach (file in maps)
                {
                        if (file_size(HELP_DIR + file) > 0)
                                map_result += read_file(HELP_DIR + file);
                        else
                                map_result += "�޷���ȡ��ͼ" + file + "��\n";
                }
                map_result = color_filter(map_result);
                return map_result;
        }

        error("δ֪����\n");
}

// ��õ�ͼ��ĳһ�еĵ�x��ʼ��n���ַ������е�ͼ����@��ͷ����
// ���������ַ�һ����Ϊ��ռ�ط�������"@B123@E"����ڶ����ַ�
// ��'2'��������B�����nΪ-1���򷵻�һֱ��ĩβ�������ַ�
//
// �����������⣬�б�Ҫ����һ�������� ��ʶ�Ƿ�ȡ����ɫ������
// ���ڳ���ļ����൱С�����Թ��Ҳ��ơ�
string get_map_line(string line, int x, int n)
{
        string rs;

        rs = "";
        if (n == 0)
                return rs;

        // �ҵ���Ӧ��λ��
        while (x)
        {
                if (strlen(line) == 0)
                        // �ַ������Ȳ���
                        return rs;

                if (line[0] == '@')
                {
                        if (strlen(line) >= 2)
                                // ȥ��@�ͺ������ַ�
                                line = line[2..<1];
                        else
                                // ���Ȳ��������ؿ��ַ���
                                return rs;
                } else
                {
                        // �ַ���ȥ����һ���ַ����൱�������ƶ�
                        x--;
                        line = line[1..<1];
                }
        }

        // ��ȡn���ַ�
        // Ϊʲô������do-while������ֱ����while��������ԭ��
        // �ġ�
        rs = "";
        for (;;)
        {
                if (strlen(line) == 0)
                        // �Ѿ����ַ���ȡ
                        return rs;

                if (line[0] == '@')
                {
                        if (strlen(line) >= 2)
                        {
                                rs += line[0..1];
                                line = line[2..<1];
                        } else
                        {
                                rs += line;
                                return rs;
                        }
                } else
                {
                        if (n == 0) break; // ������ȡ
                        n--;
                        rs += line[0..0];
                        line = line[1..<1];
                        continue;
                }
        }
        return rs;
}

// Ϊ�ص�����ɫ�����ֱ���Ϊ����
// ��ǵ�ʱ��һ����ɨ�裬ɨ���ͬʱ���ǣ����������Ϊ@B��
// @E�����ɨ��ɹ��Ͱ�@B��@E�滻��Ϊ@R��@N�������ȥ����Щ
// ��ʱ��ǡ�
// ��󽫽����еı���滻����ɫ��@R->WHT @N->NOR
public string mark_map(string map, string name)
{
        string *lines;
        string temp;
        string rs;
        int i;
        int x, y, xd;           // �Ƚϵĵ�ͼλ��
        int n;

        // ȥ����ͼ����ɫ����������׼ȷ���жϾ��Ե�����
        map = filter_color(map);

        // ����ͼ�ֳ���
        lines = explode(map, "\n");
        for (i = 0; i < sizeof(lines); i++)
        {
                if (strsrch(lines[i], name[0..1]) == -1)
                        // ���в��������Ƶĵ�һ�����֣�������������һ��
                        continue;

                x = 0;
                temp = replace_string(lines[i], "@R", "");
                temp = replace_string(temp, "@N", "");
                while (x < strlen(temp) - 1)
                {
                        xd = strsrch(temp[x..<1], name[0..1]);
                        if (xd == -1)
                                // ���к���û�����Ƶĵ�һ�����֣�������һ��
                                break;

                        // ����ƥ�����˵�һ�����֣��ȽϺ����ĺ��֣�
                        // ���Ⱥ���Ƚϣ���˲����ƶ�xd���������ɨ
                        // �費������������Ƚϣ��仯y��
                        x += xd;
                        y = i;
                        xd = 2;
                        rs = get_map_line(lines[y], 0, x);
                        rs += "@B";
                        rs += get_map_line(lines[y], x, 2);
                        for (n = 2; n < strlen(name); n += 2, xd += 2)
                        {
                                // ���Ⱥ���Ƚ�
                                if (x + xd + 2 <= strlen(lines[y]) &&
                                    get_map_line(lines[y], x + xd, 2) == name[n..n + 1])
                                {
                                        // ����Ƚϵ��ˣ���������Ƚ�
                                        rs += name[n..n + 1];
                                        continue;
                                }

                                // ����Ƚ�ʧ���ˣ�����ԭ���룬����Ƚ�
                                rs += "@E" + get_map_line(lines[y], x + xd, -1);
                                xd = 0;
                                y++;
                                if (y < sizeof(lines) &&
                                    x + 2 <= strlen(lines[y]) &&
                                    get_map_line(lines[y], x, 2) == name[n..n + 1])
                                {
                                        // ����Ƚϵ��ˣ���������Ƚ�
                                        lines[y - 1] = rs;
                                        rs = get_map_line(lines[y], 0, x);
                                        rs += "@B";
                                        rs += name[n..n + 1];
                                        continue;
                                }

                                // �Ƚ�ʧ�ܣ�����(x, i)���λ��
                                y--;
                                while (y >= i)
                                {
                                        // �ָ�ԭ�ȵĵ�ͼ��ȥ�����
                                        lines[y] = replace_string(lines[y], "@B", "");
                                        lines[y] = replace_string(lines[y], "@E", "");
                                        y--;
                                }
                                break;
                        }

                        if (n >= strlen(name))
                        {
                                // ƥ��ɹ�
                                rs += "@E" + get_map_line(lines[y], x + xd, -1);
                                lines[y] = rs;
                                while (y >= i)
                                {
                                        // ���������Ϊ�������
                                        lines[y] = replace_string(lines[y], "@B", "@R");
                                        lines[y] = replace_string(lines[y], "@E", "@N");
                                        y--;
                                }
                        }

                        // �ƶ�x������ƥ��
                        x++;
                }
                // ɨ�����һ�У�����ɨ����һ��
        }
        // �������

        return implode(lines, "\n") + "\n";
}

// �������ĳ���ص�ĵ�ͼ����ǵ�ǰ���ڵ�λ��
public string marked_map(object env)
{
        mixed maps;
        string file;
        string outdoors;
        string map_result;
        int result_ok;

        if (! objectp(env))
                return "�����޷���õ�ͼ��\n";

        if( !stringp(outdoors=query("outdoors", env)) )
                return "����������쿴�����ľ���λ�á�\n";

        if (undefinedp(maps = map_to[outdoors]))
                return "δ����ϸ��ͼ��\n";

        if (stringp(maps))
        {
                file = HELP_DIR + maps;
                map_result = read_file(file);
                if (! stringp(map_result))
                        map_result = "�޷���ȡ��ͼ" + file + "��\n";
                map_result = color_filter(map_result);
                map_result = mark_map(map_result, env->short());
        } else
        if (arrayp(maps))
        {
                map_result = "";
                result_ok = 0;
                foreach (file in maps)
                {
                        if (file_size(HELP_DIR + file) > 0)
                                map_result = read_file(HELP_DIR + file);
                        else
                        {
                                map_result = "�޷���ȡ��ͼ" + file + "��\n";
                                result_ok = 1;
                                break;
                        }

                        map_result = color_filter(map_result);
                        map_result = mark_map(map_result, env->short());
                        if (strsrch(map_result, "@R") != -1)
                        {
                                result_ok = 1;
                                break;
                        }
                }
                // ���еĵ�ͼ��û�б仯��ȡ��һ��
                if (! result_ok)
                {
                        map_result = read_file(HELP_DIR + maps[0]);
                        map_result = color_filter(map_result);
                }
        } else
                error("δ֪����\n");

        map_result = replace_string(map_result, "@R", HIC);
        map_result = replace_string(map_result, "@N", NOR);
        return map_result;
}

// ��Ҽ�¼����
public int record_rumor(mixed obs, string topic, mixed event_ob)
{
        object ob;
        string title;
        int n;

        if (objectp(obs)) obs = ({ obs }); else
        if (! arrayp(obs)) return 0;

        if (! stringp(title = event_ob->query_detail(topic)))
                return 0;

        if (stringp(event_ob)) event_ob = base_name(find_object(event_ob)); else
                               event_ob = base_name(event_ob);
        n = 0;
        foreach (ob in obs)
        {
                if( !playerp(ob) || !query("out_family", ob))continue;
                if( query("rumor/"+topic, ob))continue;
                set("rumor/"+topic, event_ob, ob);
                message("vision", "���ͳ���ͼ�ᣬ��������棬д�����йء�" +
                                  topic + "���ļ�¼��\n", ob);
                n++;
        }

        return n;
}

// ���ĳ����ͨ�ص����Ϣ
public varargs mixed query_trans_info(string to)
{
        if (! stringp(to))
                return map_trans;

        return map_trans[to];
}

// ��ý�ͨ������Ϣ
public mapping query_connect_info()
{
        return connect_info;
}

string make_color(string map)
{
        map = replace_string(map, "��", HIR"��"NOR);
        map = replace_string(map, "��", HIC"��"NOR);
        map = replace_string(map, "��", HIC"��"NOR);
        map = replace_string(map, "��", HIG"��"NOR);
        map = replace_string(map, "��", GRN"��"NOR);
        map = replace_string(map, "��", HIR"��"NOR);
        map = replace_string(map, "��", HIM"��"NOR);
        map = replace_string(map, "��", HIG"��"NOR);
        map = replace_string(map, "��", YEL"��"NOR);
        map = replace_string(map, "��", YEL"��"NOR);
        map = replace_string(map, "��", HIW"��"NOR);
        map = replace_string(map, "��", MAG"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "��", HIY"��"NOR);
        map = replace_string(map, "-", HIY"-"NOR);
        map = replace_string(map, "~", HIC"~"NOR);
        map = replace_string(map, "|", HIC"|"NOR);
        map = replace_string(map, "@", HIW"@"NOR);
        map = replace_string(map, "*", GRN"@"NOR);
        map = replace_string(map, "<", GRN"<");
        map = replace_string(map, ">", ">"NOR);
        map = replace_string(map, "��", YEL"��");
        map = replace_string(map, "��", "��"NOR);
        map = replace_string(map, "��", CYN"��"NOR);
        map = replace_string(map, "��", CYN"��"NOR);
        return map;
}

string *dirs = ({
        "north",
        "south",
        "east",
        "west",
        "northup",
        "southup",
        "eastup",
        "westup",
        "northdown",
        "southdown",
        "eastdown",
        "westdown",
        "northeast",
        "northwest",
        "southeast",
        "southwest",
        "up",
        "down",
        "enter",
        "out",
});

public string show_map(object env)
{
        int i, j, jj = 0, k, kk = 0;
        string file,map,name,dest,*search;
        mapping exit1, exit2, exit3;
        object room1, room2, room3, room4;

        if( !(file=query("region", env)) && !(file=query("outdoors", env)) )
        {
                if( mapp(exit1=query("exits", env)) )
                {
                        for (i=0; i<sizeof(dirs); i++)
                        {
                                if(dest = exit1[dirs[i]])
                                {
                                        if(!(room2 = find_object(dest)))
                                                room2=load_object(dest);
                                        if( file=query("outdoors", room2) )
                                                break;
                                        else
                                        {
                                                if( mapp(exit2=query("exits", room2)) )
                                                {
                                                        for (j=0; j<sizeof(dirs); j++)
                                                        {
                                                                if(dest = exit2[dirs[j]])
                                                                {
                                                                        if(!( room3 = find_object(dest)) )
                                                                                room3 = load_object(dest);
                                                                        if( file=query("outdoors", room3) )
                                                                        {
                                                                                jj = 1;
                                                                                break;
                                                                        }
                                                                        else
                                                                        if( mapp(exit3=query("exits", room3)) )
                                                                        {
                                                                                for (k=0; k<sizeof(dirs); k++)
                                                                                {
                                                                                        if(dest = exit3[dirs[k]])
                                                                                        {
                                                                                                if(!( room4 = find_object(dest)) )
                                                                                                        room4 = load_object(dest);
                                                                                                if( file=query("outdoors", room4) )
                                                                                                {
                                                                                                        kk = 1;
                                                                                                        break;
                                                                                                }
                                                                                        }
                                                                                }
                                                                        }
                                                                        if (kk == 1)
                                                                        {
                                                                                jj = 1;
                                                                                break;
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                        if (jj == 1) break;
                                }
                        }
                }
                if (i==sizeof(dirs))
                        return HIG"���ﲻ�ܲ鿴��ͼ���뵽���⡣\n"NOR;
        }
        if( !stringp(file) || !sizeof(file) ) return HIY"��ʱ��û�п�������ĵ�ͼ��ѯ��\n"NOR;
        name = filter_color(query("short", env));
        if( strsrch(file, "_zone") != -1 )
                sscanf(file, "%s_zone", file);
        if( file_size("/doc/map/" + file)>0 )
        {
                if(stringp(map = read_file("/doc/map/" + file)))
                {
                        //map = make_color(map);
                        map = replace_string(map, name, HBBLU+HIG+name+NOR);
                        return map;
                }
        }
        return HIY"��ʱ��û�п�������ĵ�ͼ��ѯ��\n"NOR;
}

/********************************************************************/
#define LINE HIM "------------------------------------------------------------------------------------------" NOR
#define LINE_COUNT 4

mapping trans = ([
        // ����
        "beijing"   : "/d/beijing/tiananmen",
        "yangzhou"  : "/d/city/guangchang",
        "gc"        : "/d/city/guangchang",
        "chengdu"   : "/d/chengdu/guangchang",
        "changan"   : "/d/changan/bridge2",
        "luoyang"   : "/d/luoyang/center",
        "suzhou"    : "/d/suzhou/canlangting",
        "hangzhou"  : "/d/hangzhou/road10",
        "hanzhong"  : "/d/hanzhong/zhongxin",
        "fuzhou"    : "/d/fuzhou/dongjiekou",
        "foshan"    : "/d/foshan/street3",
        "dali"      : "/d/dali/center",
        "nanyang"   : "/d/nanyang/nanyang",
        "ruzhou"    : "/d/ruzhou/ruzhou",
        "guanwai"   : "/d/guanwai/jishi",
        "lanzhou"   : "/d/lanzhou/square",
        "yongdeng"  : "/d/yongdeng/yongdeng",
        "lingzhou"  : "/d/lingzhou/center",       
        "xiangyang" : "/d/xiangyang/guangchang",     
        "quanzhou"  : "/d/quanzhou/guangchang",
        "jiaxing"   : "/d/jiaxing/jiaxing",
        "jingzhou"  : "/d/jingzhou/guangchang",      
        "emei2"     : "/d/emei/majiu1",
        "zhongnan"  : "/d/quanzhen/shanjiao",   
        "henyang"   : "/d/henshan/hengyang",
        "hengyang"  : "/d/henshan/hengyang",
        "kaifeng"   : "/d/kaifeng/zhuque",
        "kunming"   : "/d/kunming/jinrilou",
        "zhongzhou" : "/d/zhongzhou/shizhongxin",
        "wuxi"      : "/d/wuxi/guangchang", // ����
        "juyong"    : "/d/changcheng/juyongguan",  //��ӹ��
        "jiayu"     : "/d/xingxiu/jiayuguan",  //������
        "huibu"     : "/d/huijiang/buluo1", //�ؽ� �ز�����
        "xinjiang"  : "/d/huijiang/caoyuan", //�½�  ���ԭ
        "yili"      : "/d/xingxiu/yili", //�����
        "yueyang"   : "/d/yueyang/zhongxin", //������
        "yanping"   : "/d/yanping/fuqiao1", //��ƽ��

        // ����
        "songshan"  : "/d/songshan/dadian",
        "henshan"   : "/d/henshan/zhurongdian",
        "guiyun"    : "/d/yixing/taihu",
        "taohua"    : "/d/taohua/jingshe",
        "gaibang"   : "/d/gaibang/inhole",
        "tiezhang"  : "/d/tiezhang/guangchang",
        "honghua"   : "/d/huijiang/damen",
        "wudu"      : "/d/wudu/damen",
        "meizhuang" : "/d/meizhuang/keting",
        "lingxiao"  : "/d/lingxiao/bar",
        "jueqing"   : "/d/jueqing/shanzhuang",
        "heimuya"   : "/d/heimuya/up1",
        "taishan"   : "/d/taishan/taishanjiao",
        "xingxiu"   : "/d/xingxiu/xxh1",
        "ouyang"    : "/d/baituo/guangchang",
        "baituo"    : "/d/baituo/guangchang",
        "quanzhen"  : "/d/quanzhen/damen",
        "gumu"      : "/d/gumu/mumen",
        "lingjiu"   : "/d/lingjiu/jian",
        "shaolin"   : "/d/shaolin/shanmen",
        "wudang"    : "/d/wudang/jiejianyan",
        "xiaoyao"   : "/d/xiaoyao/xiaodao4",
        "huashan"   : "/d/huashan/shaluo",
        "xueshan"   : "/d/xuedao/nroad4",
        "xuedao"    : "/d/xuedao/wangyougu",
        "kunlun"    : "/d/kunlun/klshanlu",
        "qingcheng" : "/d/qingcheng/tianshidong", 
        "emei"      : "/d/emei/huayanding",
        "mingjiao"  : "/d/mingjiao/shanjiao",
        "mojiao"    : "/d/yuanyue/damen",
        "murong"    : "/d/yanziwu/bozhou",
        "tang"      : "/d/tangmen/tmyizhan",  
        "tangmen"   : "/d/tangmen/tmyizhan",  
        "miao"      : "/d/zhongzhou/miaojia_houting",
        "hu"        : "/d/guanwai/xiaoyuan",
        "duan"      : "/d/dali/neitang",
        
        // ����
        "kedian"    : "/d/city/kedian",
        "wumiao"    : "/d/city/wumiao",
        "guofu"     : "/d/wuguan/guofu_gate",///
        "ganjiang"  : "/d/item/xiaowu",
        "tianshi"   : "/d/item/road1",
        "haigui"    : "/d/xiakedao/xkroad5",
        "shendiao"  : "/d/huashan/jianzhong",
        "luban"     : "/d/room/xiaoyuan",
        "dugu"      : "/d/huashan/shandong",
        "huang"     : "/d/dali/lushui",
        "shenni"    : "/d/xiakedao/zhuwu2",
        "kuihua"    : "/d/beijing/shanlu3",
        "nanhai"    : "/d/xiakedao/haibin",
]);

mapping show_trans_info = ([
        // ����
        "beijing"   : ({ "����", "city" }),
        "luoyang"   : ({ "����", "city" }),
        "yangzhou"  : ({ "����", "city" }),
        "dali"      : ({ "����", "city" }),
        "foshan"    : ({ "��ɽ", "city" }),
        "fuzhou"    : ({ "����", "city" }),
        "guanwai"   : ({ "����", "city" }),
        "hangzhou"  : ({ "����", "city" }),
        "lanzhou"   : ({ "����", "city" }),
        "lingzhou"  : ({ "����", "city" }),
        "yongdeng"  : ({ "����", "city" }),
        "suzhou"    : ({ "����", "city" }),
        "xiangyang" : ({ "����", "city" }),
        "yili"      : ({ "����", "city" }),
        "chengdu"   : ({ "�ɶ�", "city" }),
        "emei2"     : ({ "����ɽ", "city" }),
        "zhongnan"  : ({ "����ɽ", "city" }),
        "quanzhou"  : ({ "Ȫ��", "city" }),
        "jiaxing"   : ({ "����", "city" }),
        "jingzhou"  : ({ "����", "city" }),
        "nanyang"   : ({ "����", "city" }),
        "ruzhou"    : ({ "����", "city" }),
        "changan"   : ({ "����", "city" }),
        "hanzhong"  : ({ "����", "city" }),
        "hengyang"  : ({ "����", "city" }),
        "kaifeng"   : ({ "����", "city" }),
        "kunming"   : ({ "����", "city" }),
        "zhongzhou" : ({ "����", "city" }),
        "wuxi"      : ({ "����", "city" }),
        "yueyang"   : ({ "����", "city" }),
        "yanping"   : ({ "��ƽ", "city" }),
        "juyong"    : ({ "��ӹ��", "city" }),
        "jiayu"     : ({ "������", "city" }),
        "huibu"     : ({ "�ؽ�", "city" }),
        "xinjiang"  : ({ "�½�", "city" }),

        // ����
        "huashan"   : ({ "��ɽ��", "family" }),
        "xuedao"    : ({ "Ѫ����", "family" }),
        "songshan"  : ({ "��ɽ��", "family" }),
        "xueshan"   : ({ "ѩɽ��", "family" }),
        "henshan"   : ({ "��ɽ��", "family" }),
        "gaibang"   : ({ "ؤ��", "family" }),
        "shaolin"   : ({ "������", "family" }),
        "tiezhang"  : ({ "���ư�", "family" }),
        "wudang"    : ({ "�䵱��", "family" }),
        "honghua"   : ({ "�컨��", "family" }),
        "emei"      : ({ "������", "family" }),
        "wudu"      : ({ "�嶾��", "family" }),
        "xiaoyao"   : ({ "��ң��", "family" }),
        "mingjiao"  : ({ "����", "family" }),
        "lingjiu"   : ({ "���չ�", "family" }),
        "xuanming"  : ({ "��ڤ��", "family" }),
        "xingxiu"   : ({ "������", "family" }),
        "meizhuang" : ({ "÷ׯ", "family" }),
        "gumu"      : ({ "��Ĺ��", "family" }),
        "lingxiao"  : ({ "ѩɽ����", "family" }),
        "quanzhen"  : ({ "ȫ����", "family" }),
        "mojiao"    : ({ "ħ��", "family" }),
        "kunlun"    : ({ "������", "family" }),
        "qingcheng" : ({ "�����", "family" }),
        "jueqing"   : ({ "�����", "family" }),
        "guiyun"    : ({ "����ׯ", "family" }),
        "taohua"    : ({ "�һ���", "family" }),
        "heimuya"   : ({ "�������", "family" }),
        "ouyang"    : ({ "ŷ������", "family" }),
        "miao"      : ({ "��ԭ���", "family" }),
        "murong"    : ({ "Ľ������", "family" }),
        "hu"        : ({ "�������", "family" }),
        "duan"      : ({ "�������", "family" }),
        "tang"      : ({ "��������", "family" }),
        
        // ����
        "kedian"    : ({ "���ݿ͵�", "common" }),
        "wumiao"    : ({ "����", "common" }),
        "guofu"     : ({ "������", "common" }),///d/wuguan/guofu_gate
        "ganjiang"  : ({ "�ɽ�Īа", "common" }),
        "tianshi"   : ({ "����ʦ", "common" }),
        "haigui"    : ({ "����", "common" }),
        "shendiao"  : ({ "���", "common" }),
        "luban"     : ({ "³��", "common" }),
        "dugu"      : ({ "�������", "common" }),
        "huang"     : ({ "����", "common" }),
        "shenni"    : ({ "�Ϻ�����", "common" }),
        "kuihua"    : ({ "����̫��", "common" }),
        "nanhai"    : ({ "�Ϻ�", "common" }),

]);

string g_show_trans;

mapping get_trans2()
{
        mapping m;
        string *keys_show_trans;
        int i;

        m = ([]);
        keys_show_trans = keys(show_trans_info);

        for (i = 0; i < sizeof(keys_show_trans); i ++)
        {
                m += ([ show_trans_info[keys_show_trans[i]][0] : keys_show_trans[i] ]);
        }

        return m;
}

mapping show_trans2 = get_trans2(); 

string get_trans_path(string s)
{
        string st;

        // ͬʱ�������ĺ�Ӣ��
        if (member_array(s, keys(trans)) == -1)
        {
                s = show_trans2[s];
        }

        return trans[s];
}

int show_trans(object me)
{
        mapping self_flag;
        int i;
        string *places, show_places;
        string show_city, show_family, show_comm;
        int ncity, nfamily, ncomm;

        show_places = "";
        show_city = "";
        show_family = "";
        show_comm = "";
        
        if (sizeof(g_show_trans))
        {
                show_places += g_show_trans;
        }
        else
        {

                show_places += HIY "��������������µط���\n" + LINE + "\n"NOR;

                places = keys(show_trans_info);
                places = sort_array(places, 1);
                for (i = 0; i < sizeof(places); i ++)
                {
                        if( show_trans_info[places[i]][1] == "common" )
                        {
                                show_comm += sprintf("%-10s: %-12s", places[i], show_trans_info[places[i]][0]);
                                ncomm ++;
                                if (ncomm % LINE_COUNT == 0)show_comm += "\n";
                        }                               
                        else if( show_trans_info[places[i]][1] == "family" )
                        {
                                show_family += sprintf("%-10s: %-12s", places[i], show_trans_info[places[i]][0]);
                                nfamily ++;
                                if (nfamily % LINE_COUNT == 0)show_family += "\n";
                        }
                        else
                        {
                                show_city += sprintf("%-10s: %-12s", places[i], show_trans_info[places[i]][0]);
                                ncity ++;
                                if (ncity % LINE_COUNT == 0)show_city += "\n";
                        }
                }
                show_places += HIG + "<����>\n" NOR;
                show_places += show_city;
                show_places += HIY + "\n<����>\n" NOR;
                show_places += show_family;
                show_places += HIC + "\n<����>\n" NOR;
                show_places += show_comm;

                g_show_trans = show_places; // ȫ�ּ�¼������Ҫÿ�ζ�����
        }

        // �Լ���¼�ĵص�
        self_flag=query("horse/flags", me);

        if (mapp(self_flag))
        {
                show_places += HIR "\n<�û���¼�ص�>\n" NOR;
                if (sizeof(self_flag))
                {
                        places = keys(self_flag);
                        for (i = 0; i < sizeof(places); i ++)
                        {
                                show_places += sprintf("%-10s: %-12s", places[i], get_object(self_flag[places[i]])->short());
                                if ((i+1) % LINE_COUNT == 0)show_places += "\n";
                        }
                        if (sizeof(places) % LINE_COUNT != 0)show_places += "\n";
                }
        }
        else
        {
                show_places += "\n";
        }

        show_places += LINE + HIY "\n��ʹ�� rideto <Ŀ�ĵ�> ����ָ���ط������磺rideto �͵�\n" NOR;

        write(show_places);
        return 1;
}

// ����ָ���ص�
int move_to(object me, string place)
{
        object running, horse, follower;
        string trans_path;
        int trans_times, sk_riding, level;
        string temp,temp2;
        object trans_target, me_env;

        // ����Ƿ�����
        if( !objectp(horse=query_temp("is_riding", me)) )
        {
                write("�㲢û��������\n" );
                return 1;
        }
        if( query_temp("running", horse) )
        {
                write(horse->name() + NOR "���ڱ����أ�\n" NOR);
                return 1;
        }
        if( query_temp("running", me) )
        {
                write("�����ڱ������ء�\n");
                return 1;
        }
        if (me->is_busy() || me->is_fighting())
        {
                write("����æ�أ�\n");
                return 1;
        }

        sk_riding = me->query_skill("riding", 1);
        if( sk_riding < 1 ) sk_riding = 1;
        /*
        if (sk_riding < 30)
        {
                write("�������������޷�����ָ���ص㡣\n");
                return 1;
        }
        */

        // ����Ƿ��иõط���ȥ
        if (! stringp(trans_path = get_trans_path(place)))
        {
                if( !stringp(trans_path=query("horse/flags/"+place, me)) )
                {
                        write("���޷�����ﵽ����ط���\n");
                        return 1;
                }
                if (! find_object(trans_path) && ! load_object(trans_path))
                {
                        write("���޷�����ﵽ����ط���\n");
                        return 1;
                }
        }

        // ĳЩ�ط��޷�������
        trans_target = find_object(trans_path);
        if (! objectp(trans_target))trans_target = load_object(trans_path);

        if (! objectp(trans_target))
        {
                write("���޷�����ﵽ����ط���\n");
                return 1;
        }

        if( query("no_magic", trans_target) )
        {
                write("���޷�����ﵽ����ط���\n");
                return 1;
        }

        if (sscanf(base_name(trans_target), "/d/city2/%s", temp) == 1)
        {
                write("���޷�����ﵽ����ط���\n");
                return 1;
        }

        me_env = environment(me);

        if( query("no_rideto", me_env) )
        {
                write("�˴���������\n");
                return 1;
        }

        // dream_boat���޷�����
        if (sscanf(base_name(me_env), "/clone/misc/dream_%s", temp) == 1)
        {
                write("�˴��޷�����\n");
                return 1;
        }

        // ��ҷ����޷�����Լ��ķ������
        if (sscanf(trans_path, "/data/room/%s/%s", temp, temp2) == 2)
        {
                // �Լ�������Խ���
                if( query("id", me) != temp )
                {
                        write("���޷��������˽��סլ��\n");
                        return 1;
                }
        }

        if (sscanf(trans_path, "/clone/misc/dream_%s", temp) == 1)
        {
                write("���޷�����ﵽ����ط���\n");
                return 1;
        }
        
/*
        level = query("level", horse); // ���100
        trans_times = 2 + random(1 + 300 / sk_riding) + (10 - (level/10)*3);
        if( trans_times > 1 ) trans_times = 1;
        if( trans_times < 0 ) trans_times = 0;
*/
        
        message("vision",  "\n" + horse ->name() + HIW "һ����"
                  "˻����һ��س�� ����\n" NOR, environment(me), ({horse}));

        running = new("/clone/misc/running");
        me->move(running);
        if( objectp(follower=query_temp("is_rided_follow", horse)) )
        {
                if (environment(follower) && (interactive(follower) || ! userp(follower)))
                        follower->move(running);
        }
        
        set_temp("running", 1,  horse);
        set_temp("running", 1,  me);

        if( !trans_times ) arrived_dest(me, follower, running, horse, trans_path); else
        //call_out("arrived_dest", trans_times, me, follower, running, horse, trans_path);
        arrived_dest(me, follower, running, horse, trans_path);

        return 1;
}

int arrived_dest(object me, mixed follower, object running, object horse, string trans_path)
{
        object ob, ob2;

        if (! objectp(me)) return 0;
        if (objectp(horse))
                tell_object(me, "\n" + horse->name() + HIW "����Ŀ�ĵأ���˻һ������Ȼͣ�£���ʱ������ɢ����\n" NOR);
        //if (objectp(me))
        //{
                me->move(trans_path);
                delete_temp("running",  me);
                if (random(2))me->improve_skill("riding", 1);
        //}
        if (objectp(follower))follower->move(trans_path);
        if( objectp(horse))delete_temp("running", horse);

        if(objectp(running))destruct(running);

        if (objectp(horse))
                message("vision",  "\n" + this_object()->name() + HIW "����Ŀ�ĵأ���˻һ������Ȼ"
                        "ͣ�£���ʱ������ɢ����\n" NOR, environment(horse), ({me, horse}));

        return 1;
}

// ǿ������
int me_ride(object me, object horse)
{
        object owner;

        if( !objectp(me) || !objectp(horse) )
        {
                write("�������\n");
                return 0;
        }

        if( query_temp("is_rided_follow", horse) )
                return 0;

        owner = query_temp("is_rided_by", horse);

        set_temp("is_rided_follow", me, horse);
        set_temp("is_riding_follow", horse, me);

        message_vision("$NԾ��$n" NOR "������" + owner->name() + "�����\n", me, horse);

        return 1;
}
