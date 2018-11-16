// sword.c
// The template of auto-created sword.
// An example of object template.

// ����ģ��ϵͳ�궨���ļ�
#include <template.h>

// �̳�ģ�����
inherit TEMPLATE_OB;

// ���������ݱ����ڱ�����

// dbase ��ʽ
mixed *dbase_format = ({ "long" });

// ������ʽ
mixed *function_format = ({ "set_weight", "init_damage" });

// ģ������
mapping template_data = ([
        // Ӣ����(����)  : ({ ����(long), ({ ����(set_weight) - �˺�(init_damage) }), �����׼�ļ� })
        "short sword"    : ({ "����һ������������խ�ʶ̽���\n",     ({ 5000,  10, }), }),
        "scimitar"       : ({ "����һ���������ε��䵶��\n",         ({ 7000,  20, }), }),
        "sabre"          : ({ "����һ���������������\n",         ({ 9000,  25, }), }),
        "war sword"      : ({ "����һ�ѿ��������ս��ʹ�õĽ���\n", ({ 9000,  30, }), }),
        "fachion"        : ({ "����һ�Ѽȿ��ҳ��Ĵ󵶡�\n",         ({ 12000, 30, }), }),
        "long sword"     : ({ "����һ�����������ĳ�����\n",         ({ 7000,  10, }), }),
        "crystal sword"  : ({ "����һ�Ѿ������������ν���\n",       ({ 12000, 35, }), }),
        "broad sword"    : ({ "����һ�ѽ����ر�����Ĵ󽣡�\n",     ({ 13000, 40, }), }),
        "two-hand sword" : ({ "����һ��˫�ֽԿ��õĳ�����\n",       ({ 12000, 35, }), }),
        "claymore"       : ({ "����һ�����߶����еķ��񳤵���\n",   ({ 12000, 40, }), }),
        "giant sword"    : ({ "����һ�����ξ޴���ؽ���\n",         ({ 20000, 40, }), }),
        "bastard sword"  : ({ "����һ�����Ÿ�ɫ��������ĳ�����\n", ({ 15000, 40, }), }),
        "flamberge"      : ({ "����һ�Ѻ�����Ƶ�Ѫɫ������\n",     ({ 15000, 45, }), }),
        "great sword"    : ({ "����һ�ѷǳ��޴���ؽ���\n",         ({ 30000, 50, }), }),
]);

// ��ʼ��ģ��
void create()
{
        setup();
}

// �����������Ƿ�ʹ��ȫ��ʽģʽ���ʽ��Ӧģʽ
void setup()
{
        // ����׼�ļ�Ϊ "/inherit/template/weapon/sword.c"��
        set_base_file("weapon/sword");

        // ���� dbase ��ʽ
        set_dbase_format(dbase_format);

        // ���ú�����ʽ
        set_function_format(function_format);

        // ����ģ������
        set_template_data(template_data);

        ::setup();
}
