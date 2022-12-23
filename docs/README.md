### 변경된 실행로직(v1.0)
0. command_argv를 만든다.
1. 다음 필드가 파이프라면
	- 파이프를 뚫어준다.
2. 다음 필드가 파이프가 아니라면
	1. 현재 필드가 서브쉘인 경우
		- fork(), execve(minishell, command argv);
	2. 현재 필드가 빌트인인 경우
		- 리다이렉션
		- 부모에서 빌트인 실행
	3. 현재 필드가 서브쉘과 빌트인이 아닌 경우

1. 파이프 연결

2. 부모에서 command_argv보고, 빌트인인지 서브쉘인지 그 외인지 판단. 
	- 우선 빌트인 명령어 만든 폴더에서 먼저 보고
	- 찾지 못한다면 PATH에서 찾기

	1. 서브쉘인 경우
		- 다음 필드가 파이프라면
			- 
		- 다음 필드가 파이프가 아니라면
	2. 빌트인 경우
		- 다음 필드가 파이프라면
			- 파이프 만들고
			- 포크하고
			- 자식에서 파이프 셋팅
			- 자식에서 리다이렉션
			- 자식에서 빌트인 실행
		- 다음 필드가 파이프가 아니라면
			- 리다이렉션
			- 부모에서 빌트인 실행
	3. 빌트인이 아닌 경우
		- 다음 필드가 파이프라면
			- 파이프 만들고
			- 포크하고
			- 자식에서 파이프 셋팅
			- 자식에서 리다이렉션
			- 실행 가능 path를 만들고
			- 실행 가능한 path인지 검사
			- 자식에서 실행 파일 실행(execv)
		- 다음 필드가 파이프가 아니라면
			- 포크하고
			- 자식에서 리다이렉션
			- 실행 가능 path를 만들고
			- 실행 가능한 path인지 검사
			- 자식에서 커맨드 실행
while ()
{
	if (&&, || -> 전 프로세스 기다려줘서 exit_status 처리)
}
waitpid(모두를 기다린다.);
		//pid = fork()
		//child execve(echo)
		//if ( && 또는 ||)
		// pid = waitpid

4. 부모에서 wait
	- 여기서 exit_status 받아와서 update => 

(grep hello) < infile
### 빌트인
- echo, cd, pwd, export, unset, env, exit
# 실행

- pipe나 subshell이나 결 모두 subshell이 열림. pipe와 subshell 모두 프로세스임으로 경쟁 관계
hard case : (echo hello | cat ) > a | (sleep 3 && grep "hello" << limiter < a&& sleep 5)

soft case : echo hello > b | grep "hell0"
1. 현재 필드를 보고 다음 필드에 파이프가 있는지 없는지 확인
	- 있다면 :
		- 1) 부모에서 파이프를 열고 fork()
		- 2) 자식에서 pipe setting
	- 없다면 : 
		- 그냥 fork()
2. expand()
4. 리다이렉션 있는지 확인
	- 있다면 :
		- 리다이렉션 순서대로 수행
		- 괄호가 있다면
			- 리다이렉션 토큰은 제외 하고 괄호만 때서 string으로 만들기(리다이렉션 처리는 서브쉘에서)
		- 괄호가 없다면(쿼트 있다면 제거)
			- 리다이렉션 토큰은 제외하고 쿼트가 있을 때 string으로 만들기
			- example : echo "hello" < "<"
	- 없다면 :
		- 그냥 실행

// export 하위 프로세스에게 변수를 넘겨준다.

- |가 있으면
	- 자식에서
### 트리 왜 썼나?
```bash
$ echo a && echo b > a              // b
$ (echo a && echo b) > a            // a\nb
```
- 결국 괄호 깊이에 대한 우선순위를 처리하려면 그 깊이를 처리할 수 있는 `트리 로직`이나 `서브쉘 로직`이 필요한데, 우리는 서브쉘 로직이 있기 때문에 자연스럽게 깊이 처리가 가능하다. 우리 같은 경우에는 트리로 별도의 로직을 만들 필요는 없었음.
- 트리 사용하는 이유는 보통 부모가 subshell을 만들 때 처리 흐름이 있으니 부모에서 처리하기 쉽게 트리를 사용함 => lalr

case 1 - subshell이 있는 경우
case 2 - subshell 안에 redirection이 있는 경우

# 구조, 로직

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

### 연산자 우선순위

1. || , &&
2. | , < , > , >>, 
3. cmd, ( )

### 처리해야 할 것
1. &&
2. $?
3. * (와일드카드와 환경변수 확장)
4. 오늘 작성한 함수 구현 어떻게 할지 대략적으로 생각해오기

### PIPEX
```c
infile | yes | head -2 | outfile

1. 부모 fd : 0 1 2 3(curr_in) 4(curr_out)
2. 자식 fd : 0 1 2 3(curr_in) 4(curr_out) 5 (prev_in) -> infile
3. 자식 fd : 0 1 2 X(*)       X           X
		execve(yes) -> 1번 파이프에 계속 쓰고 있다.
4. 부모 fd : 0 1 2 3(prev_in = curr_in) // yes는 pipe에 계속 쓰고 있음
5. 부모 fd : 0 1 2 3(prev_in) 4(curr_pipe_out)
6. 자식 fd : 0 1 2 3(prev_in) 4(curr_pipe_out)
7. 자식 fd : 0 1 2 X          X
		execve(head) -> curr_pipe_out에 계속 쓰고 있다.
8. 부모 fd : 0 1 2 X(*)       X
```
- SIGPIPE: write on a pipe with no reader
	- reader는 `프로세스`가 아닌 `읽기 버퍼, fdpipe[0]`으로 본다.
- yes를 실행하기 전 부모프로세스에서 3번 FD, 자식 프로세스에서 3번 FD는 1번 파이프의 reader로 본다.
	- 이 두 FD 모두 닫히지 않는다면 SIGPIPE 신호를 보낼 수 없다.
	- 자식 프로세스에서 3번 FD를 닫지 않고, execve로 yes를 실행한다면 커널 버퍼에 3번 FD가 여전히 남아 있으므로, SIGPIPE 신호를 보낼 수 없다. (즉, 자식에서 curr_in을 닫고 pipe를 실행해야 한다.)
	- 부모 프로세스에서 3번 FD를 닫는 순간, 모든 reader가 닫히므로 SIGPIPE로 인해 yes 프로세스는 스스로 종료한다.

### homebrew 경로 변경 시 
LIB_READ_LINE = -L/opt/homebrew/opt/readline/lib -lreadline