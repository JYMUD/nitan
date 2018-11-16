
#define BASEINCOME              400000000
#define TICKTIME                14
#define POSTSEASON_TICKTIME     9
#define PREPARETIME             600
#define HINTTIMES               6

#define HANDSIDE_NONE           0
#define HANDSIDE_LEFTHAND       (1<<0)
#define HANDSIDE_RIGHTHAND      (1<<1)
#define HANDSIDE_TWOHANDS       (HANDSIDE_LEFTHAND|HANDSIDE_RIGHTHAND)

#define RECORD_TEAM                     0
#define RECORD_PLAYER           1
#define RECORD_SPECIAL          2

#define STATUS_IDLE                     0
#define STATUS_PREPARING        1
#define STATUS_PLAYING          2

#define TICK                    0       // ����
#define TEAM1                   1       // �������
#define TEAM2                   2       // �ͳ����
#define INNING                  3       // ����
#define OUT                             4       // ������
#define STRIKE                  5       // ����
#define BALL                    6       // ����
#define RUNNER1ST               7       // һ������
#define RUNNER2ND               8       // ��������
#define RUNNER3RD               9       // ��������
#define TEAM1NUMBER             10      // �������Ŀǰ����
#define TEAM2NUMBER             11      // �ͳ����Ŀǰ����
#define TEAM1SCORE              12      // ������ӵ÷�
#define TEAM2SCORE              13      // �ͳ���ӵ÷�
#define TEAM1HIT                14      // ������Ӱ�����
#define TEAM2HIT                15      // �ͳ���Ӱ�����
#define TEAM1MISS               16      // �������ʧ����
#define TEAM2MISS               17      // �ͳ����ʧ����
#define TEAM1K                  18      // �������Ͷ��������
#define TEAM2K                  19      // �ͳ����Ͷ��������
#define TEAM1WALK               20      // ������ӱ�����
#define TEAM2WALK               21      // �ͳ���ӱ�����

#define BASETYPE_STRIKEOUT              0       // ����
#define BASETYPE_BALL                   1       // ��������
#define BASETYPE_HIT                    2       // ��������
#define BASETYPE_BUNT                   3       // �����̴�
#define BASETYPE_TOUCHKILL              4       // ��ɱ
#define BASETYPE_CATCHKILL              5       // ��ɱ
#define BASETYPE_DOUBLEPLAY             6       // ˫ɱ
#define BASETYPE_TRIPLEPLAY             7       // ��ɱ
#define BASETYPE_STEAL                  8       // ����

#define SCORETYPE_HOMERUN               1       // ȫ�ݴ�
#define SCORETYPE_FOURBALL              2       // ����
#define SCORETYPE_SACRIFICE             3       // ������
#define SCORETYPE_HIT                   4       // ����

#define HINTTYPE_BATTER                 1       
#define HINTTYPE_PITCHER                2       
#define HINTTYPE_BUNT                   3       
#define HINTTYPE_WALK                   4

