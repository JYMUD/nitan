
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "͵�컻��" NOR; }

int perform(object me, string skill)
{
        return notify_fail("�㲻���ǻ۳�Ⱥ���ҹ����ļơ���������˽��ڼ���ʱͨ���ɻ�ȡ����İ�����ͬ\n"
                           "ʱ���и��ߵ�����������ѧϰ����ʱ������ѧϰЧ��10%������Ҫ���á�\n");
}

