inherit SKILL;
void create() { seteuid(getuid()); }
string type() { return "knowledge"; }
int practice_skill(object me)
{   
        return notify_fail("������ֻ��ͨ��ѧϰ(learn)��������ʵ�������!\n");
}