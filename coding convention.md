이름 규칙

일관성을 위해 가장 중요한 것은 이름 규칙을 따르는 것이다. 
이름의 스타일을 통해 요소의 선언을 찾지 않고도 해당 요소가 타입인지, 변수인지, 함수인지, 상수인지, 혹은 매크로인지 바로 알 수 있다. 
이름 규칙은 개인의 선호도보다 일관성이 더 중요하다. 합리적이라고 생각하든 아니든 규칙은 지켜야 한다.
 
일반

N-1. 함수 이름, 변수 이름, 파일 이름은 약어를 사용하지 않고 서술형으로 짓는다.
가능한 상세한 이름을 사용한다. 다른 사람이 즉시 이해할 수 있는 것이 글자 길이를 줄이는 것보다 중요하다. 
제 3자에게 익숙하지 않은 약어를 사용하지 않으며, 축약하지 않는다.
// 좋은 예
int price_count_reader;        // 축약 없음.
int num_errors;                    // 누구나 이해 가능
int num_dns_connections;   // DNS 정도면 누구나 이해 가능
 
// 나쁜 예
int n;                               // 의미 없음.
int nerr;                          // 모호한 축약.
int n_comp_conns;          // 모호한 축약.
int wgc_connections;      // 내부자만 아는 약어.
int pc_reader;                  // pc의 의미는?
int cstmr_id;                    // 중간 단어 축약

타입 이름

N-7. 타입 이름은 대문자로 시작하며, 언더바 "_" 없이 단어마다 첫 글자를 대문자로 작성한다. 
구조체, typedef, 열거형을 포함한 모든 타입에 대해 동일한 규칙이 적용된다. 
// 구조체

struct UrlTablePropertiesStruct { 
  ...
}
 
// typedef
typedef struct UrlTablePropertiesStruct * UrlTableProperties;
 
// 열거형

enum { 
  ...
} eUrlTableErrors;

변수 이름

N-8. 변수 이름은 모두 소문자로 작성하며 단어 사이에 언더바 "_" 를 사용한다. 
지역변수, 전역변수, 구조체 멤버 변수 모두 동일하다.
int table_name;  // 좋음 - 언더바 사용
int tablename;   // 좋음 - 모두 소문자
int tableName;   // 불가 - 대문자 사용
 
N-9. 전역변수는 "g_" 와 같이 지역 변수와 구분할 수 있는 접두어를 사용한다.
int g_table_num; 
 
함수 이름

N-11. 함수 이름은 소문자로 시작하고 각 단어의 첫 글자를 대문자로 쓰며, 언더바 "_" 는 사용하지 않는다.
함수의 실행 중 크래시가 발생할 수 있다면 함수의 이름 뒤에 OrDie 를 붙인다.
addTableEntry()
deleteUrl()
openFileOrDie()
 
클래스 이름

클래스 이름은 대문자로 시작하고 각 단어의 첫 글자를 대문자로 쓴다. 
class Object;
class BoxCollider;


Source : Google C++ Style Guide
https://google.github.io/styleguide/cppguide.html
