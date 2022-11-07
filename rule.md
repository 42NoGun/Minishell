구조

1. read input
2. Analysis input
	a. parentheses & quote check(내일 만들기)
	b. tokenize & expand(환경 변수 와일드 카드 확장)
	c. syntax check (pipe 다음에 리다이렉션 기호 or pipe 다음 인자가 없거나)
	d. parse
3. execute
	a. traverse tree

expand
1. 토큰에 담을 때 풀어서 담는다.
2. 실행할 때 풀어서 실행한다.
3. 트리에 매달 때 풀어서 매단다.

1. token화
- 딱 정말 토근 단위로 끊기
- 토큰화가 되는지 확인하기 (이 때?)
- list 만들어짐
2. list를 순회하면서 expand하기
3. expand된 list값으로 tree 만들기
(순회는 2번)

규칙

토큰으로 자르는 순간
1. 공백을 만났을 때
2. operator를 만났을 때
3. inputdl 끝났을 때(NULL)

1. 입력의 끝이 있으면 현재 판단중인 문자열을 토큰으로 본다

2. 이전 문자가 operator의 일부이면서 현재 문자가 따옴표가 아니고 
	이전문자와 연결해서 operator 취급이 되면 operator의 일부임.
	
3. 이전 문자가 operator의 일부고, 
	현재 문자가 이전이랑 연관해서 operator가 안되면 이전 문자까지가 operator로 토큰화됨
	
4. ", ' 시작이면, 닫는 문자가 나오기 전까지 문자들을 문자 그대로 인식한다. + () (괄호 안에 있는 것은 통째로 한 토큰으로 처리) -> subshell의 line으로 넘어감

5. 현재 문자가 "에 감싸져있지 않은 `$`라면, 쉘은 확장 가능한 것인지 확인하거나, 명령 대체하거나, 산술 확장을 한다. 뒤에 오는것이 `$(`이거나 `${` 이거나 `$((`인지 따라서 각각..
 
6. 현재 문자가 " 안에 없고, operator의 시작이 될 수 있으면 토큰화한다. 그리고 현재 문자는 새로운 문자의 시작이 된다.

7. 공백을 만나면 지금까지 넣은 것을 토큰화 한다. 공백은 무시한다.

8. 전 문자가 단어의 일부라면 현 문자도 단어의 일부다.

9. 새로운 문자 시작.

$(PATH)
'"PATH"'
$"PATH"

예외
1. (ls | "ls && (ls && ls | ls))" -> 괄호 짝 체크 예외
2. (ls | "ls && (ls && ls | ls)") -> 괄호 짝 체크 예외
-> 괄호 짝 찾는 알고리즘 : junji
3. echo "hel"ol""
	-> sigle quote : close 만나기 전까지 읽음
	-> double quote : $만나면 확장하는데 공백, $, " 전까지 읽어서 판단
	확장한 값을 반환해서 이전 문자와 join
	공백 or $ or " 까지 포인터 넘김

"$h"'$h'$h
" $h$h ahl;sfjklasdfj"
echo $h$h
if (*str == $)
{
	while (!*str && *str != ' ' && *str != '$')
		expand..
}

token->conten-> ( ""->''->$h->''->'$h'->"$h" )

### 처리해야 할 것
1. &&
2. $?
3. * (와일드카드와 환경변수 확장)
4. 오늘 작성한 함수 구현 어떻게 할지 대략적으로 생각해오기