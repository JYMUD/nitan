// sword.c
// The template of auto-created sword.
// An example of object template.

// ����ģ��ϵͳ�궨���ļ�
#include <template.h>

// �̳�ģ�����
inherit TEMPLATE_OB;

// ���������ݱ����ڱ�����

// dbase ��ʽ
mixed *dbase_format = ({ "long", "value" });

// ������ʽ
mixed *function_format = ({ "set_weight", "init_damage" });

// ģ������
mapping template_data = ([
        // Ӣ����(����)  : ({ ����(long), ({ ����(set_weight) - �˺�(init_damage) }), �����׼�ļ� })
        "scimitar"       : ({ ({ "����һ���������ε��䵶��\n", 100 }),        ({ 7000,  20, }), }),
        "sabre"          : ({ ({"����һ���������������\n", 200 }),        ({ 9000,  25, }), }),
        "fachion"        : ({ ({"����һ�Ѽȿ��ҳ��Ĵ󵶡�\n", 300 }),        ({ 12000, 30, }), }),
        "claymore"       : ({ ({ "����һ�����߶����еķ��񳤵���\n", 400 }),  ({ 12000, 40, }), }),
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
        set_base_file("weapon/blade");

        // ���� dbase ��ʽ
        set_dbase_format(dbase_format);

        // ���ú�����ʽ
        set_function_format(function_format);

        // ����ģ������
        set_template_data(template_data);

        ::setup();
}
