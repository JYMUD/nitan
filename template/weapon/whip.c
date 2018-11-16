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
        "liangyin whip" : ({ ({ "����һ�����������������ޣ����淢��������Ϯ�˶�Ŀ��\n", 100 }), ({ 5000,  20, }), }),
        "zhujie whip"   : ({ ({ "����һ����ڸֱޡ�\n", 150 }), ({ 5000,  40, }), }),
        "baowei whip"   : ({ ({ "����һ����β�ޡ�\n", 200 }), ({ 5000, 60, }), }),
        "dajiang whip"  : ({ ({ "����һ���򽫱ޡ�\n", 250 }), ({ 5000, 80, }), }),
        "tuogu whip"    : ({ ({ "����һ���չ�����ޡ�\n", 300 }), ({ 5000, 100, }), }),
        "jinlong whip"  : ({ ({ "����һ�������ޡ�\n", 350 }), ({ 5000, 120, }), }),
        "huwei whip"    : ({ ({ "����һ����β�ֱޡ�\n", 400 }), ({ 5000, 140, }), }),
        "bingtie whip"  : ({ ({ "����һ�������ޡ�\n", 450 }), ({ 5000, 160, }), }),
        "longtou whip"  : ({ ({ "����һ����ͷ��β�ޡ�\n", 500 }), ({ 5000, 180, }), }),                
        "huyan whip"    : ({ ({ "����һ�����۸ֱޡ�\n", 550 }), ({ 5000, 200, }), }),  
        "jinsi whip"    : ({ ({ "����һ����˿��ޡ�\n", 600 }), ({ 5000, 220, }), }),  
        "hulu whip"     : ({ ({ "����һ����«�ޡ�\n", 650 }), ({ 5000, 240, }), }),  
        "guigu whip"    : ({ ({ "����һ����Ǳޡ�\n", 700 }), ({ 5000, 260, }), }),  
        "yugu whip"     : ({ ({ "����һ����β�ޡ�\n", 750 }), ({ 5000, 280, }), }),  
        "shegu whip"    : ({ ({ "����һ���߹Ǳޡ�\n", 800 }), ({ 5000, 300, }), }),  
        "yinsi whip"    : ({ ({ "����һ����˿��ޡ�\n", 850 }), ({ 5000, 320, }), }),  
        "zheyun whip"   : ({ ({ "����һ������ɨ���ޡ�\n", 900 }), ({ 5000, 350, }), }),         
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
        set_base_file("weapon/whip");

        // ���� dbase ��ʽ
        set_dbase_format(dbase_format);

        // ���ú�����ʽ
        set_function_format(function_format);

        // ����ģ������
        set_template_data(template_data);

        ::setup();
}
