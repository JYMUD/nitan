// Pharmacy daemon(preparing and dispensing drugs)
// By landis@MYTH
// 2002.05.09
// last update 2002.08.23

//  ���������������ҩ����ص����񣬰�����
//
//  1.����ҩ�Ի����Ӧ��ҩ�ġ�
//  2.�˶Դ�����ҩ��ת��Ϊҩ�
//  3.���������µĴ������ݡ�
//  4.��ҩ�Ļ�ҩ����������Ż���ת����

/***********************************************************
����ҩ���ż���Ӧ���Ƶ�ӳ�����£�
mapping data = ([
        "herb" : ([
                0 : "�ʲ�",
                1 : "����",
                ]),
        "medicine" : ([
                0 : "�������嵤",
                1 : "�ʲ����ɢ",
                ]),
        ]);

���洦����ӳ�����£�
mapping prescription = ([
        1, 2, 3 : 1,
        2, 3, 4 : 2,
        ]);

����ҩ�������Ϣ��ӳ�����£�
mapping relation = ([
        0 : ([
                "eng"  : ({"gan cao", "cao"}),
                "unit" : "��",
                "desc" : "һ���Ϻ�ɫ��С�ݣ�������ɷ�ǿɰ���",
                ]),
        ]);
***********************************************************/

#include <ansi.h>

inherit F_DBASE;
inherit F_SAVE;

mapping data;
mapping prescription;

mapping relation;

void initialize();
int register_all_medicine();

void create()
{
        seteuid(ROOT_UID);
        initialize(); // ��ʼ���������������ݣ�ˢ��ӳ���

        set("channel_id", "��ҩ����");
        CHANNEL_D->do_channel( this_object(), "sys", "��ҩϵͳ�Ѿ�������");
}

// ��ʼ���������������ݣ�ˢ��ӳ���
void initialize()
{
        restore();        

        if (! mapp(data))
        {
                data = allocate_mapping(2);
                data["herb"] = allocate_mapping(50);
                data["medicine"] = allocate_mapping(50);
        }

        if (! sizeof(data["medicine"]))
                register_all_medicine();

        if (! mapp(prescription))
                prescription = allocate_mapping(50);

        if (! mapp(relation))
                relation = allocate_mapping(50);
}

void remove() { save(); }

string query_save_file() { return DATA_DIR "pharmacyd"; }

/*********************************************************************
                       ����Ϊ���ӡ�ɾ�����ݵĽӿ�
*********************************************************************/

// ע��ҩ��id����Ӧ��������
int register_herb(int id, string name)
{
        object ob;
        string file;

/*
        ob = previous_object();

        if (! is_root(ob) || geteuid(ob) != "Clone")
                error("Pharmacyd:Herb Registration conflict, Access denied.\n");
*/

        if (! mapp(data))
                data = ([ "herb" : ([ id : name ]) ]);
        else if (! mapp(data["herb"]))
                data["herb"] = ([ id : name ]);
        else
                data["herb"][id] = name;

        return 1;
}

// ����ҩ�ĵĻ�����Ϣ
int set_relation(int id, mapping rt)
{
        mapping map;

        relation[id] = allocate_mapping(3);

        map = relation[id];

        if (! mapp(map) || ! sizeof(map))
                map = ([ "eng" : rt["eng"] ]);
        else
                map["eng"]  = rt["eng"];

        map["unit"] = rt["unit"];
        map["desc"] = rt["desc"];

        relation[id] = map;

        return 1;
}

// ע��ҩ��id����Ӧ����(��ҩ�����ȡ��)
int register_medicine(int id)
{
        object obj;
        string file, name;

//      if (previous_object() != this_object())
//              return 0;

        file = id < 10 ? "0%d" : "%d";
        file = sprintf(file, id);
        file = MEDICINE_DIR(file);

        call_other(file, "???");
        obj = find_object(file);
        name = filter_color(obj->query("name"));

        if (geteuid(obj) != "Clone")
                error("Pharmacyd:Medicine Registration conflict, Access denied.\n");

        if (! mapp(data))
                data = ([ "medicine" : ([ id : name ]) ]);
        else if (! mapp(data["medicine"]))
                data["medicine"] = ([ id : name ]);
        else
                data["medicine"][id] = name;

        return 1;
}

// ע������ҩ��
int register_all_medicine()
{
        int i, id;
        string *dir;

        dir = get_dir(MEDICINE_DIR(""));

        if (! dir || ! sizeof(dir)) return 0;
        for (i = 0; i < sizeof(dir); i++)
        {
                if (! sscanf(dir[i], "%d.c", id))
                        continue;

                register_medicine(id);
        }

        return 1;
}

// ע��ĳһҩ�Ļ�ҩ��
int unregister(string type, int id)
{

//      if (previous_object() && geteuid(previous_object()) != ROOT_UID)
//	        return 0;

        if (type != "herb" && type != "medicine")
                return notify_fail("Pharmacyd:Wrong type, Access denied.\n");

        if (mapp(data) && mapp(data[type]))
                map_delete(data[type], id);

        return 1;
}

// ���Ӵ�������
int add_prescription(int *herbs, string medicine)
{
        if (! mapp(prescription))
                prescription = ([ herbs : medicine ]);
        else
                prescription[herbs] = medicine;

        return 1;
}

// ɾ����������
int delete_prescription(int *herbs)
{
        if (! mapp(prescription) || undefinedp(prescription[herbs]))
                return 0;

        map_delete(prescription, herbs);
        return 1;
}

/*********************************************************************
                       ����Ϊ���ⲿ���õĲ�ѯ�ӿ�
*********************************************************************/

// ���ظ�ҩ�ĵĻ�����Ϣ����ҩ�ĳ�ʼ��ʱ����
mapping query_relation(int id) { return relation[id]; }

// ͨ��ҩ�Ļ�ҩ������ѯ���
int check_id(string name)
{
        int loc;
        int *key;
        string *value;

        key   = keys(data["herb"]);
        value = values(data["herb"]);
        loc   = member_array(name, value);

        if (loc == -1)
        {
                key   = keys(data["medicine"]);
                value = values(data["medicine"]);
                loc   = member_array(value, name);
        }

        return key[loc];
}

// ͨ������(ҩ�Ļ�ҩ��)��id��ѯ��������
string check_name(string type, int id)
{
        mapping fname;

        if (type != "herb" && type != "medicine")
                error("Pharmacyd:Wrong Check Type,Access denied.\n");

        fname = data[type];
        return fname[id];
}

// ��ѯ������(ҩ�Ļ�ҩ��)ĳһid�Ƿ���ע��
int already_registerd(string type, int id)
{
        if (type != "herb" && type != "medicine")
                return notify_fail("��ѯ���ʹ���\n");

        return undefinedp(data[type][id]) == 0;
}

/*********************************************************************
                       ����Ϊ���ò鿴�����б�Ľӿ�
*********************************************************************/

// ����ҩ���б�
string list_herb()
{
        int i;
        string *key;
        string line;
        mapping herbs;

        herbs = data["herb"];

        if (! mapp(herbs) || ! sizeof(herbs))
                return "Ŀǰ��δ���ҩ�����ݹ��죡\n";

        line  = WHT"\nĿǰ���ռ���ҩ���������£�\n\n"NOR;
        key   = keys(herbs);
        key   = sort_array(key, 1);

        for(i = 0; i < sizeof(key); i++)
        {
                line += sprintf(CYN"%2d", key[i]);
                line += "����";
                line += sprintf(WHT"%-10s"NOR, herbs[key[i]]);

                line += (i<4 || i%4) ? "��" : "\n";
        }

        return line;
}

// ����ҩ���б�
string list_medicine()
{
        int i;
        string *key;
        string line;
        mapping medicines;

        medicines = data["medicine"];

        if (! mapp(medicines) || ! sizeof(medicines))
                return "Ŀǰ��δ���ҩ�����ݹ��죡\n";

        line  = WHT"\nĿǰ���ռ���ҩ���������£�\n\n"NOR;
        key   = keys(medicines);
        key   = sort_array(key, 1);

        for(i = 0; i < sizeof(key); i++)
        {
                line += sprintf(CYN"%2d", key[i]);
                line += "����";
                line += sprintf(WHT"%-10s"NOR, medicines[key[i]]);

                line += (i<4 || i%4) ? "��" : "\n";
        }

        return line;
}

// ���ش����б�
string list_prescription()
{
        int i;
        string line;
        int *key, *value;

        if (! mapp(prescription) || ! sizeof(prescription))
                return "Ŀǰ����ҩ�����ݿɹ���ѯ��\n";

        line  = "";
        key   = keys(prescription);
        value = values(prescription);

        for (i=0; i<sizeof(key); i++)
        {
                foreach(int id in key[i])
                        line += sprintf(HIW"%-8s", check_name("herb", id));

                line += sprintf(HIC"��%-20s", check_name("medicine", value[i]));
                line += "\n" NOR;
        }

        return line;
}

/*********************************************************************
                       ����Ϊ��Ҫ������ҩ�ĵĽӿ�

                ���У�ÿ��ҩ�ĵ����Զ���Ψһ�ģ���ʽ���£�

                ζ��(Taste)     ���ࡢ�̡��ᡢ�ʡ���
                ҩ��(Officinal) ����������ƽ���¡���
                ����(toXicity)  ���С���

                ���ԣ��� {x,y,z} ��ʽ�������ӦΨһһ��ҩ
                �ģ�������Ϊ 5x5x2 = 50 �֡�

*********************************************************************/

// �������Լ����ţ�����ҩ��
object build_herb(int *prop)
{
        int num;
        int tp, op, xp;
        object ob;
        string name;

        tp = prop[0];
        op = prop[1];
        xp = prop[2];

        if (tp < 0 || op < 0 || xp < 0 ||
            tp > 4 || op > 4 || xp > 1 ||
            sizeof(prop) > 3)
                error("Pharmacyd:Wrong Herb Prop.\n");

        // �㷨Ϊ 10*x + 2*y + z ���ɵõ���ҩ�ĵ�Ψһ��š�
        num  = xp;
        num += op * 2;
        num += tp * 10;

        name = data["herb"][num];

        if (! stringp(name))
                error("Pharmacyd:Fail in Loading Herb object.\n");

        ob = new(HERB_OB);               // ����ԭ��
        ob->initialize(num, name, prop); // ��ʼ��

        return ob;
}

// ���ݱ�Ŵ���ҩ��
object clone_herb(int id)
{
        object ob;
        string name;
        int *prop;
        int tp, op, xp;

        name = data["herb"][id];

        if (! stringp(name))
                error("Pharmacyd:Fail in Loading Herb object.\n");

        tp = id / 10;
        op = (id%10) / 2;
        xp = id - (tp * 10) - (op * 2);

        prop = ({ tp, op , xp });

        ob = new(HERB_OB);              // ����ԭ��
        ob->initialize(id, name, prop); // ��ʼ��

        return ob;
}

/*********************************************************************
                       ����Ϊ����������ҩ��Ľӿ�

                ÿ����ҩ�ĳɹ��ʴ�ԼΪ50%��
                �ܷ���ҩ������������ʱδ���Կ��ǡ�
                ����ҩʧ�ܣ���һ������õ� �߻��� ����ˮ �ƽ�
                �е�һ�֣����򽫵õ����ϡ�

*********************************************************************/

// �˶Դ�����ҩ��ת��Ϊҩ��
object build_medicine(object *herbs)
{
        object obj;
        int *id_list;
        int i, id, flag;
        string *recipe;
        string bname, name;

        id_list = allocate(sizeof(herbs));

        for (i = 0; i < sizeof(herbs); i++)
        {
                if (herbs[i]->is_activator()) { flag = 1; continue; }
                bname = base_name(herbs[i]);
                if (bname != HERB_OB) continue;
                id_list[i] = id;
        }

        foreach (recipe in keys(prescription))
        {
                if (recipe - id_list == ({ }) &&
                    flag ? 1 : random(10) > 5)
                {
                        name = sprintf("%d", prescription[recipe]);
                        name = MEDICINE_DIR(name);

                        for (i = 0; i < sizeof(herbs); i++)
                                destruct(herbs[i]);

                        call_other(name, "???");
                        if (! objectp(find_object(name)))
                                error("Pharmacyd:Fail in Loading Medicine object.\n");

                        return new(name);;
                } else
                {
                        switch (random(100))
                        {
                                case 84: obj = new(GOLD_OB); break;
                                case 11: obj = new(MEDICINE_DIR("activator")); break;
                                case 30: obj = new(MEDICINE_DIR("elixir")); break;
                                default: obj = new(MEDICINE_DIR("waste"));
                        }

                        return obj;
                }
        }
}
