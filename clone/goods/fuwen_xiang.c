#include <ansi.h>
inherit BAOXIANG_ITEM;

void create()
{
        set_name(HIM"��������"NOR,({"xiang"}));
        //���һ��Ҫ���ã�
        set("BAOXIANG_LIST",([
                "/clone/tessera/rune01":100,   //��Ʒ�ļ���:����
                "/clone/tessera/rune02":95,   //��Ʒ�ļ���:����
                "/clone/tessera/rune03":90,   //��Ʒ�ļ���:����
                "/clone/tessera/rune04":85,   //��Ʒ�ļ���:����
                "/clone/tessera/rune05":80,   //��Ʒ�ļ���:����
                "/clone/tessera/rune06":75,
                "/clone/tessera/rune07":70,
                "/clone/tessera/rune08":65,
                "/clone/tessera/rune09":60,
                "/clone/tessera/rune10":55,
                "/clone/tessera/rune11":43,
                "/clone/tessera/rune12":40,
                "/clone/tessera/rune13":37,
                "/clone/tessera/rune14":35,
                "/clone/tessera/rune15":30,
                "/clone/tessera/rune16":15,
                "/clone/tessera/rune17":10,
                "/clone/tessera/rune18":8,
                "/clone/tessera/rune19":5,
                "/clone/tessera/rune20":2,
        ])); //��������1000��Ϊ�������Ҽ���ĸ����ܺ�Ϊ1000�����ʴ�ĳ��ּ��ʸߡ�����
        
        set("long", HIY "����һֻ��ɫ�ı��䣬װ�ε���ⱦ�����������Դ򿪣�open������\n" NOR); 
        set("unit", "Щ");
        set("base_unit", "��");
        set("no_give",1);
        set("no_drop",1);
        set("base_weight",1);
        set("base_value",1);
        set_amount(1); //��Ϊ�Ǹ�combined��Ʒ �������һ��Ҫ���ã���Ȼ�����

}
void init()
{
        add_action("do_open","open"); //���ʹ�õĽӿ� ����������std��
        add_action("do_test","test"); //������ʦ������ ����ok��ע�ʹ���
}

