// kongdong xinfa.c

inherit FORCE;

string query_xiuwei_type() { return "force"; }

int practice_skill(object me)
{
	return notify_fail("����ķ�ֻ����ѧ�ģ����Ǵ�����(exert)�����������ȡ�\n");
}

int valid_xiulian( object me ) { return 1; }

int query_level() { return 2; }
string query_type() { return "yin"; }
