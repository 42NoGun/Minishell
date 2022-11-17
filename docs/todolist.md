# Minishell

### 2022.11.17~18(목, 금) (Day 13, 14)
- [X] expand 
	- [X] getenv
	- [X] logic 완성
- [X] parsing 끝
- [ ] leaks 잡기
- [ ] 25줄 이상인 함수 쪼개기
- [ ] closedir 해줄 것!


### 2022.11.16(수) (Day 12)
- [x] expand
	- [x] 1. 환경변수 => 어떻게 담고 다닐 것인지 
	- [x] 2. wildcard
	- [x] opendir, readdir, closedir
	- [ ] getenv
- [ ] redirect
	- [ ] 중복 연산자가 있는지(syntax error)
- [ ] quote 제거 (ls "> abcde" outfile ">" ) => word spliting
- [ ] execute
- [X] 확장할때 ? 확장 (exit status)도 해줘야함

### 2022.11.15(화) (Day 11)
- [X] Field 만든 후, 규칙에 맞게 트리에 담는다.
- [X] tree순회, 현재 트리가 operator일 때 자식이 하나라도 없는 경우 에러 처리(syntax error) + 테스트 코드

### 2022.11.14(월) (Day 10)
- [x] Syntax Error 케이스 정리
- [x] Tokenize 케이스 보완
- [x] Tree에 넣을 구조 생각
	- $echo hello hello hello | ls
		- field: shell 확장 결과로 만들어진 텍스트. 총 3개가 나온다. 
		- field는 리스트의 시작 주소와 길이를 가진다.
		- 나중에 execute전에 확장하고 strjoin으로 붙여준다.

### 2022.11.11(금) (Day 9)
- [ ] tokenize 구현
	- [x] is_bracket
	- [x] read_bracket_content
	- [x] is_dollor
	- [ ] expand(), 환경변수 확장 (getenv, opendir, readdir)
- 이거 다 하면 pasing 끝!

- 남은 일:
	1. parsing (50%)
	2. 토큰화해서 list로 만들기
	3. tree 안에 list 담기
	4. pipe 연결해서 cmd 구현 (echo -> built-in 구현)
	5. signal 처리 (exit status -> `ctrl+d`, `ctrl+c`, `ctrl+\`)

### 2022.11.10(목) (Day 8)
- [X] tokenize 구현
	- [X]  토큰을 만들어 리스트에 넣는 함수
	- [X] "||"와 ||를 구분하기 위해 quote안에 문자열을 읽는 함수 구현
	- 모니터칠판 이슈, vscode wifi 이슈 -> 결국엔 클러스터 IMAC codeshare

### 2022.11.09(수) (Day 7)
- tokenize 중 execute 해결
	- 기존 로직: 마지막 프로세스만 기다린다.
	- 바뀐 로직: 모든 프로세스가 종료될 떄까지 기다린다.
- 바뀐 로직을 적용했더니, 문제는 해결되었는데 `yes | head -2`가 왜 종료되었는지 납득이 안되어 하루 종일 고민
	- yes를 종료시키기 위해선 `SIGPIPE` 시그널을 받을 수 있어야 한다. (default behavior: terminate process, SIGPIPE: write on a pipe with no reader)
	- 부모에서 pipe_in, yes를 실행하기 전 pipe_in 2명의 reader를 닫아야 `SIGPIPE`로 yes가 종료된다.

### 2022.11.08(화) (Day 6)
- tokenize 중 execute 부분 처리
```bash
$ yes | head -n			// 처리 O
$ sleep5 | sleep 1		// 처리 X
```
	- 현재 로직에서 yes | head -n은 처리한다. (마지막 프로세스만 기다리므로)
	- 단, sleep 5 | sleep 1은 해결하지 못한다. (실제 쉘에선 5초를 기다리지만, 우리 로직에선 sleep 1이 종료될 때 끝)

### 2022.11.07(월) (Day 5)
- [O] tokenize 시작
	- [X] token 구조체(value, prioity, type)
	- [X] bash[token_recognition]: 한줄 한줄 해석
	- https://pubs.opengroup.org/onlinepubs/9699919799/toc.htm
	- [X] token_recognition을 코드로 구현
	- [X] 괄호와 쿼트 체크 로직 + 테스트

### 2022.11.04(금) (Day 4)
- [X] 전반적인 구조 
	1. read input
	2. Analysis input
		- a. parentheses & quote check(내일 만들기)
		- b. tokenize & expand(환경 변수 와일드 카드 확장)
		- c. syntax check (pipe 다음에 리다이렉션 기호 or pipe 다음 인자가 없거나)
		- d. parse
	3. execute
		-  reverse tree
- [o] Test를 project에 포함하기 위한 작업
	- [X] Test directory, Makefile
	- [X] 단위테스트 가능한 Assert
```c
void	ft_assert(bool test_func, bool answer, char *error_message)
{
	if (test_func == answer)
		return ;
	ft_putstr_fd("Assert : ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
```

### 2022.11.03(목) (Day 3)
- [X] 트리 우선순위(heredoc은 별도로 처리)
	1. ||, &&
	2. <, >, >>, |,
	3. (괄호안 커맨드), CMD
- [o] 트리를 어떻게 만드는가?
	- [X] 수식파서트리 이용
	- https://ehpub.co.kr/9-3-%ec%88%98%ec%8b%9d-%ed%8c%8c%ec%84%9c-%ed%8a%b8%eb%a6%acnumeric-parser-tree/
```bash
1. root 우선순위 >= now 우선순위
	- now left에 root 달기
	- root update
2. root 우선순위 < now 우선순위
	- 1) now가 연산자인 경우
		- now left에 root right 달기
		- root right에 now 달기
	- 2) now가 연산자가 아닌 경우
		- now를 root의 오른쪽 끝 달기
```

### 2022.11.02(수) (Day 2)
- [X] linked_list 구현
- [X] readline, addhistory추가
- [X] tree 구현
	- init_tree
	- make_tree_node
	- push_left
	- push_right
	- inorder_traverse(트리의 기능이 아닌, 트리에 삽입할 때 사용한다)

### 2022.11.01(화) (Day 1)
- [X] jiyunpar 사전 학습 자료
	- https://grizzly-touch-858.notion.site/minishell-483e1e34034f42f4b2afeb2ad4b989aa
- [X] readline 사용법 (-lreadline)
	- [X] 입력 중 ctrl + d: 아무 일도 없음.
	- [X] 아무 입력 없을 때 ctrl + d: exit (minishell)
	- [X] rl_replace_line issue
		- [X] :D없애주기 위해서 rl_replace_line이 필요. 
		- -lreadline의 상세경로를 적어주면, :D가 없어지고 출력된다. 
- [X] Makefile 작성
```bash
$ gcc main.c -lreadline -L/opt/homebrew/opt/readline/lib/ -I /opt/homebrew/opt/readline/include
```
- 해당 경로를 추가하면 rl_replace_line()을 쓰지 않더라도 :D가 없어진다.
- 기본 경로와 상세 경로에서 readline 구현부가 다를 것으로 예상됌. (굳이 상세경로를 추가하면서구현부가 다른 readline 함수를 쓸 필요를 못 느낌)
	- 다음 방법으로 해결.
```bash
printf("\033[1A"); // 한줄 커서 위로(맨왼쪽끝)
printf("\033[7C"); // cursor move right
```
