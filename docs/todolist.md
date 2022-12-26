# Minishell
### 2022.12.23(금) (Day33)
- [X] tokenize쪼개기
- [X] 1. norm
- [X] 2. lsof로 minishell fd누수 잡아야 한다 (Minsukan)
- [ ] 3. Makefile 정리
	- [x] minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- [x] make fclean libft 지우기
	- [x] readline dir 경로 수정 (경기는 무조건 home)
	- [x] CFLAG 확인
	- [ ] source file 적기
	- [ ] bonusfile 적기
	- [ ] Makefile heredoc
- [ ] 4. 헤더 정리

### 2022.12.22(목) (Day 32)
- [X] main, subshell, parser 쪼개기
- [X] execute 쪼개기
- [X] norm
	- [X] execute
	- [X] refine_field
	- [X] tokenize
	- [X] main
### 2022.12.21(수) (Day 31)
- [X] ls() -> syntax error 볼지 아니면 command not found 로 냅둘지 => 저는 냅둬야 한다고 생각합니다!!!!! (cheseo가 한 말임)
- [X] subhsell (cat) | (cat) | (cat) -> 인터럽트 했을 때 띄어쓰기 3번되는 문제
- [X] builtin exit status 처리
- [X] 시스템 콜 처리 하지 못한거
	- [-] Signal 실패했을 경우는?
	- [-] open 가변인자..
	- [-] waitpid
	- [X] close
	- [X] opendir, readdir, closedir -> 내부적으로 처리하니까 우리는 X -> systemcall 아님
- [x] System Call 반환값 예외 핸들링!!
- [ ] 1. lsof로 minishell fd누수 잡아야 한다 (Minsukan)
- [ ] 2. Makefile 정리
	- [ ] minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- [ ] make fclean libft 지우기
	- [ ] readline dir 경로 수정 (경기는 무조건 home)
	- [ ] CFLAG 확인
	- [ ] Makefile heredoc
- [ ] 3. 헤더 정리 

<!-- - 지윤님이 확인해주셔야 할 것
	- 1. execute()
	- 2. expand
	- 3. heredoc
	- 4. subshell
	- 5. (그냥 다 해주세요 ㅎ) -->

### 2022.12.20(화) (Day 30)
- [ ] 폴더 나누기, 파일 나누기
- [ ] 1. System Call 반환값 예외 핸들링!!
- [ ] 2. 함수 25줄 (vs 과거의 나)
- [ ] 3. lsof로 minishell fd누수 잡아야 한다 (Minsukan)
- [ ] 4. norm
- [ ] 5. Makefile 정리
	- [ ] minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- [ ] make fclean libft 지우기
	- [ ] readline dir 경로 수정 (경기는 무조건 home)
	- [ ] CFLAG 확인

### 2022.12.19(월) (Day 29)
- [X] builtin 처리
	- [X] cd
		- PWD, OLDPWD, absolute path
	- [X] export , env
		- refactoring(unnecessary malloc)
	- [X] clear
		- env_list value format 수정
		- h="hello" -> h=hello
	- [X] subshell
		- redirection 있을 경우 syntax에러로 보는 것
	- [X] execute
		- leak 처리
- leak 처리
	- refind_field free wildcard_split
- [ ] 폴더 나누기, 파일 나누기
- [ ] 1. System Call 반환값 예외 핸들링!!
- [ ] 2. 함수 25줄 (vs 과거의 나)
- [ ] 3. lsof로 minishell fd누수 잡아야 한다 (Minsukan)
- [ ] 4. norm
- [ ] 5. Makefile 정리
	- [ ] minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- [ ] make fclean libft 지우기
	- [ ] readline dir 경로 수정 (경기는 무조건 home)
	- [ ] CFLAG 확인

### 2022.12.16(금) (Day 28)
- 구현사항
	- [x] expand
		- [x] echo $USER^$USER
		-> 조건식 고쳐서 해결 (ft_isalnum(*content) || *content == '?')
		- [x] echo $ -> 현재 pwd가 출력됨
		-> $뒤에 아무것도 없을 때 env_content의 길이가 0인데 ft_strncmp에서 len이 0일때 반환 값이 0이라서 문제가 되었음
	- [x] export 출력, 정렬
	- [x] unset
- 평가 받기 전
	- [x] 1. leak잡기
		- free_function
			- 1. free_list_only_node
			- 2. free_list_node_content
			- 3. free_list_node_token
			- 4. free_tree_node_field
			- 5. free_2d_str
		- continue; 위에 잘 생각해 보기
		- [X] env_list  -> 2
			- node : malloc
			- node->content: 문자열(malloc) 
		- [x] cmd_list  -> 3
			- node : malloc
			- node->content : token(malloc)
			- node->content->value : 문자열(malloc)
		- [x] cmd_tree -> 4
			- tree_node : malloc 
			- tree_node->content : field(malloc)
			- tree_node->content->str_ptr : token(same with cmd_list) -> cmd_list free 하면 없어짐
		- [x] cmd_exec_list -> 1
			- node : malloc
			- node->content : field(same with tree) -> cmd_tree free 하면 없어짐
		- [X] line: malloc(readline)
		- [X] make_heredoc_file
			- ft_itoa(i) -> free(current_file_sequnce);
		- [X] limiter_list  
			- node : malloc
			- node->content : 문자열(malloc)
				- write_heredoc에서 pop();
				- 나와서 limiter_list free();
		- [X] pid_list -> 1
			- node : malloc
			- node->content : longlong(malloc 아님)
		- [X] expand_dollar
		- [X] expand_wildcard
		- [ ] refine_field
			- [X] refined
			- [ ] command -> 5
				- field에 들어간 것들이 있음
				- 이차원배열
			- [X] redirections -> 5
				- 이차원배열
			- [x] wildcard_split -> 5
				- 이차원배열

	- [ ] 2. System Call 반환값 예외 핸들링!!
	- [ ] 3. 함수 25줄 (vs 과거의 나)
	- [ ] 4. lsof로 minishell fd누수 잡아야 한다 (Minsukan)
	- [ ] 5. norm
	- [ ] 6. Makefile 정리
		- [ ] minishell 폴더에서 make 했을 때 libft 컴파일 되게
		- [ ] make fclean libft 지우기
		- [ ] readline dir 경로 수정 (경기는 무조건 home)
		- [ ] CFLAG 확인

### 2022.12.15(목) (Day 27)
- heredoc 로직 (전제: 비밀 폴더에 만든다. (이미 만들려고 하는 파일 이름이 존재하는 경우는 없음))
	- [X] 부모에서 exec_list 노드별로 순회하면서 << 있으면 히어독 만들어준다.
		- [X] 서브쉘이 아니라면 해당 필드의 모든 토큰을 순회하면서 << 있으면 갯수를 세준다..
		- [X] 서브쉘일 경우에는 문자열에서 << 찾아야 하고 쿼트 일때 쿼트 안의 << 는 무시("<<")
			- [X] 개수 만큼 파일만든다 네이밍 규칙: 특정경로/1.heredoc 특정경로/2.heredoc (특정경로는 makefile에서 만듬)
	- [X] heredoc 찾아내는 방법
		- [X] opendir
		- [X] readdir(skip dot directory 후)은 정렬된 순서로 읽어온다(검증 필요).  (0.heredoc -> 1.heredoc -> 2.heredoc) -> readdir 랜덤
		- [X] 바로 찾아온 거 반환. -> 그걸 열면 됌.
		- [X] 열고 리다이렉션 셋팅, 바로 찾아온 거 지우기
	- [X] 부모에서 시그널 받을 때 처리

- [X] cat << lim1 | ls | (cat << lim2) | (cat << lim3)
- [X] << abc | << abc 
- [X] cat << lim << lim2 | sleep 5 | (cat << lim3 << lim4)
- heredoc (	ls << lim | sleep 5 | ls << lim2)
	- [X] heredoc_list -> cur_node 진행을 알려주는 i
	- [X] i기반한 파일 이름 (access로 파일이 있는지 없는지 먼저 확인)
	- [X] heredoc node를 exec_list cur_node 에 맞춰서 진행시키기
- [ ] export 출력, 정렬 
- [ ] unset
- [ ] lsof로 minishell fd누수 잡아야 한다 (Minsukan) 
- [ ] 함수 25줄 (vs 과거의 나)
- [ ] Makefile 정리
	- minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- make fclean libft 지우기
	- readline dir 경로 수정 (경기는 무조건 home)
- [ ] leak, norm
- [ ] 공백과 특수문자를 파일 이름에 포함하는 것을 권장하지 않기에 우리는 undefined behaviour로 남기기로 함
	- touch "ab c" -> ls * -> ls ab c -> ls: ab: no such file or directory

### 2022.12.14(수) (Day 26)
- [X] (echo $PATH) 전에 이걸 안했었음.
- [X] echo $PATH
- [ ] << abc | << abc
- [ ] cat << lim << lim2 | sleep 5 | (cat << lim3 << lim4)
	- heredoc
		- [ ] 
		- [ ] heredoc_list -> cur_node 진행을 알려주는 i
		- [ ] 기반한 파일 이름 (access로 파일이 있는지 없는지 먼저 확인)
		- [ ] heredoc node를 exec_list cur_node 에 맞춰서 진행시키기
			- [ ] 
		ls << lim | sleep 5 | ls << lim2
- [X] echo 1 | exit 123 // exit출력안도ㅣ야함
- [X] ls * => 파일 하나 실행하는 듯
	- cat *
	- refine_field 
	- token에서 value를 꺼낼 때 와일드 카드에서 확장 된 문자열인지 알수 있음
		1) 쿼트가 없으면서 문자열에 공백이 있으면 와일드 카드 확장임
			- 쿼트가 없는데 공백이 있는 반례가 있을까?
			- export 구현 할때 "쿼트 붙인 상태로 env_list에 추가 필요
- [X] minishell > exit 123 123 // exit: Too many arguments 출력
	- [X] echo $? => 갑자기 왜 터짐...???
- [ ] export 출력, 정렬 
- [ ] unset
- [ ] lsof로 minishell fd누수 잡아야 한다 (Minsukan) 
- [ ] 함수 25줄 (vs 과거의 나)
- [ ] Makefile 정리
	- minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- make fclean libft 지우기
	- readline dir 경로 수정 (경기는 무조건 home)
- [ ] leak, norm
- [ ] 공백과 특수문자를 파일 이름에 포함하는 것을 권장하지 않기에 우리는 undefined behaviour로 남기기로 함
	- touch "ab c" -> ls * -> ls ab c -> ls: ab: no such file or directory

### 2022.12.13(화) (Day 25)
- [x] echo 1 && (echo 2 && echo 3) => subshell 아예 실행 안됨
- [X] echo 1 | cat << end > out | cat > out2 => heredoc 파이프랑 같이 오면 안됨
- [X] echo $PATH
- [X] exit_status 고쳤음! (!is_alnum)
- [ ] << abc | << abc
	- heredoc
		- [ ] heredoc_list -> cur_node 진행을 알려주는 i
		- [ ] i기반한 파일 이름 (access로 파일이 있는지 없는지 먼저 확인)
		- [ ] heredoc node를 exec_list cur_node 에 맞춰서 진행시키기
		ls << lim | sleep 5 | ls << lim2
- [X] echo 1 | exit 123 // exit출력안도ㅣ야함
- [X] ls * => 파일 하나 실행하는 듯
	- cat *
	- refine_field 
	- token에서 value를 꺼낼 때 와일드 카드에서 확장 된 문자열인지 알수 있음
		1) 쿼트가 없으면서 문자열에 공백이 있으면 와일드 카드 확장임
			- 쿼트가 없는데 공백이 있는 반례가 있을까?
			- export 구현 할때 "쿼트 붙인 상태로 env_list에 추가 필요
- [x] minishell > exit 123 123 // exit: Too many arguments 출력
	- [ ] echo $? => 갑자기 왜 터짐...???
- [ ] export 출력, 정렬 
- [ ] unset
- [ ] lsof로 minishell fd누수 잡아야 한다 (Minsukan) 
- [ ] 함수 25줄 (vs 과거의 나)
- [ ] Makefile 정리
	- minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- make fclean libft 지우기
	- readline dir 경로 수정 (경기는 무조건 home)
- [ ] leak, norm

### 완성도 올리기
- [X] ./minishell ./minishell ^C
- [X] cat << lim 에서 ctrl + c 들어오면 ^C
- [X] cat 하고 sigquit에서 출력
- [X] pipe속도
### 2022.12.12(월) (Day 24)
- [ ] 추가 구현
	- [X] 문법오류 시 exit status 맞출것
	- [ ] 빌트인 구현
		- [X] exit
			- [X] exit에 인자를 받으세요^^ (Minsukan)
			- exit 하고 난 뒤에 echo $?를 하면 전에 exit 1로 했다면 1이 출력됨
			- exit도 exit 코드 봐야함ㅇ루미;ㄴ아러ㅣ먀;ㄴ 어라ㅣ;ㅁㄴ어ㅏ;ㄹ
			- exit 뒤에 인자 하나만, 또는 하나도 없거나 또는 long max 넘어서는 거 그리고 문자열 =
		- [X] pwd
		- [X] cd
		- [X] echo -> 옵션 핸들링! -n 
		- [X] env
		- [ ] export (evn vs shell variable) -> 지윤님 주말 숙제?
		- [ ] unset
- [X] cd 경로 | ls -> 우리는 지금 이게 터진다. -> (Minsukan)
- [X] () | echo -> Minsukan
- [X] () -> syntax error , () -> 우리는 진행
- [X] (ls || ls (ls | ls)) -> Minsukan 
- [ ] lsof로 minishell fd누수 잡아야 한다 (Minukan) 
- [ ] 함수 25줄 (vs 과거의 나)
- [ ] Makefile 정리
	- minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- make fclean libft 지우기
	- readline dir 경로 수정 (경기는 무조건 home)
- [ ] leak, norm

### 2022.12.9(금) (Day 23)
- [ ] lsof로 minishell fd누수 잡아야 한다 (Minukan) 
- [ ] cd 경로 | ls -> 우리는 지금 이게 터진다. -> (Minsukan)
- [ ] () | echo -> Minsukan
- [ ] () -> syntax error , () -> 우리는 진행
- [ ] (ls || ls (ls | ls)) -> Minsukan 
- [ ] exit에 인자를 받으세요^^ (Minsukan)
- [ ] 함수 25줄 (vs 과거의 나)
- [X] 시그널 처리 (ctrl d, c, /) - Minsukan block_signal()
	- [X] ctrl + c : 새로운 행에 새로운 prompt를 띄워야함
	- [X] readline 전에서 signal set - sig handler가 readline 다시 나오게 하기
	- [X] fork 하고 부모가 sigint signal block 자식은 sigint default (process terminate)
	- [X] 자식 ctrl c 받았을 때 부모는 무시해야되는데, 히어독에서는 자식이 ctrl c로 종료되었을 때 부모가 이를 알고 더이상 실행하지 않는당 지우
		- [X] heredoc signal 
	- [X] cat || ls // bash case 비교
	- [X] heredoc, ctrl d handling
	- [X] 자식이 sigint로 죽으면 exit status가 130번이 되고 부모가 이를 인지하면 cur_node를 NULL 인지하는 타이밍은 | , ||, && 노드에서 waitpid로 알아낼 수 있다
		- [X] cat << limiter다
		- [X] << limiter -> segfault
		-> 중요개념 자식은 부모의 시그널 핸들러를 상속받는다.
- [X] 무지성 unlink here_doc vs 판단해서기 vs 자식이 인터럽트로 종료되었을 때만 안 지우기 -> signal받고 unlink 빨리 하고 죽기 -> 결국 숨긴파일로..
- [ ] Makefile 정리
	- minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- make fclean libft 지우기
	- readline dir 경로 수정 (경기는 무조건 home)
- [ ] leak, norm
- [ ] 추가 구현
	- [ ] 문법오류 시 exit status 맞출것
	- [ ] 빌트인 구현
		- [ ] exit
			- exit 하고 난 뒤에 echo $?를 하면 전에 exit 1로 했다면 1이 출력됨
			- exit도 exit 코드 봐야함ㅇ루미;ㄴ아러ㅣ먀;ㄴ 어라ㅣ;ㅁㄴ어ㅏ;ㄹ
			- exit 뒤에 인자 하나만, 또는 하나도 없거나 또는 long max 넘어서는 거 그리고 문자열 =
		- [X] pwd
		- [X] cd
		- [ ] echo -> 옵션 핸들링! -n 
		- [ ] env
		- [ ] unset
		- [ ] export (evn vs shell variable) -> 지윤님 주말 숙제?

- 시그널 이슈
	(WIFSIGNALED(status)로 exit status가 시그널로 종료 되었는지 확인할 수 있음 -> 자식에서 인터럽트를 받는 동시에 부모가 waitpid에서 깨어나 signal 처리를 하기 때문에 불완전함 

### 2022.12.8(목) (Day 22)
- [X] 서브쉘 실행 확인 필요
- [x] $? 한비킴 
- [x] pipe 속도 해결하기 
- [ ] 함수 25줄 (vs 과거의 나)
- [ ] 시그널 처리 (ctrl d, c, /) - Minsukan block_signal()
	- [ ] ctrl + c : 새로운 행에 새로운 prompt를 띄워야함
	- [x] ctrl + d : shell을 종료 시켜야함
	- [x] ctrl + \ : 아무것도 하지 않음
	- [ ] readline 전에서 signal set - sig handler가 readline 다시 나오게 하기
	- [ ] fork 하고 부모가 sigint signal block 자식은 sigint default (process terminate)
	- [ ] 자식 ctrl c 받았을 때 부모는 무시해야되는데, 히어독에서는 자식이 ctrl c로 종료되었을 때 부모가 이를 알고 더이상 실행하지 않는당
		- [ ] heredoc signal (WIFSIGNALED(status)로 exit status가 시그널로 종료 되었는지 확인할 수 있음 https://www.it-note.kr/133 )
	- [ ] cat || ls // bash case 비교
	- [ ] 자식이 sigint로 죽으면 exit status가 130번이 되고 부모가 이를 인지하면 cur_node를 NULL 인지하는 타이밍은 | , ||, && 노드에서 waitpid로 알아낼 수 있다
		- [ ] cat << limiter다
		- [ ] << limiter -> segfault
		-> 중요개념 자식은 부모의 시그널 핸들러를 상속받는다.
- [ ] 무지성 unlink here_doc vs 판단해서 지우기 vs 자식이 인터럽트로 종료되었을 때만 안 지우기 -> signal받고 unlink빨리하고 죽기
- [ ] Makefile 정리
	- minishell 폴더에서 make 했을 때 libft 컴파일 되게
	- make fclean libft 지우기
	- readline dir 경로 수정 (경기는 무조건 home)
- [ ] leak, norm

- [ ] 추가 구현
	- [x] ||, &&도 짝이 없을 때 syntax error
	- [ ] 문법오류 시 exit status 맞출것
	- [ ] 빌트인 구현
	- [ ] echo, cd, pwd, export, unset, env, exit

### 2022.12.7(수) (Day 21)
- [ ] 마저 실행부 코드 작성
	- [X] &&, || 연산자까지 포함한 실행 로직 완성하기
	- [x] 빌트인인 경우 실행 로직
	- [ ] 빌트인 구현
		- [ ] echo, cd, pwd, export, unset, env, exit
	- [X] 리다이렉션 실행 확인
	- [X] exit status update 실행 확인
	- [X] 히어독 로직(<< 'limit', "limit 입코딩) -> 확장 안 함
	- [X] 서브쉘에서 실행로직 구상
	- [X] $? 구현
	- [ ] systemcall 실패했을 때 처리(open ...)
	- [X] 히어독 구현
	- [ ] 서브쉘 실행 확인 필요
	- [ ] pipe 속도 해결하기 
	- [ ] 함수 25줄 (vs 과거의 나)
	- [ ] 시그널 처리 (ctrl d, c, /)
		- ctrl + c : 새로운 행에 새로운 prompt를 띄워야함
		- ctrl + d : shell을 종료 시켜야함
		- ctrl + \ : 아무것도 하지 않음
	- [ ] Makefile 정리
		- minishell 폴더에서 make 했을 때 libft 컴파일 되게
		- readline dir 경로 수정 (경로는 무조건 home)
	- [ ] leak, norm
- [ ] 추가 구현
	- [ ] ||, &&도 짝이 없을 때 syntax error
	- [ ] 문법오류 시 exit status 맞출것

### 2022.12.6(화) (Day 20)
- [ ] 마저 실행부 코드 작성
	- [x] &&, || 연산자까지 포함한 실행 로직 완성하기
	- [x] prev_pipe_in 연결 로직 
	- [X] command_argv 첫번째 명령령어 추추가  
	- [x] execve path 찾는 로직 추가

	- [X] 리다이렉션
	- [X] 서브쉘 인자
	- [ ] 빌트인인 경우 실행 로직
	- [X] 서브쉘, 빌트인이 아닌 경우 실행 로직  
	- [X] 미니쉘이 실행만된다?!!!
- [ ] 추가 구현
	- [ ] ||, &&도 짝이 없을 때 syntax error

### 2022.12.5(월) (Day 19)
- [ ] 마저 실행부 코드 작성
	- [X] 리다이렉션
	- [X] 서브쉘 인자
	- [ ] 미니쉘이 실행된다?!!!
- [ ] 추가 구현
	- [ ] ||, &&도 짝이 없을 때 syntax error

### 2022.12.2(금) (Day 18)
- [ ] 마저 실행부 코드 작성
	- [ ] 리다이렉션
	- [ ] 서브쉘 인자
	- [ ] 미니쉘이 실행된다?!!!
- [ ] 추가 구현
	- [ ] ||, &&도 짝이 없을 때 syntax error

### 2022.12.1(목) (Day 17)
- [ ] 본격적으로 실행부 코드 작성!
	- [x] 정제된 필드를 만들어야 한다. (서브쉘인 경우 괄호를 없애주고, 자식에서 리다이렉션을 처리하고 나서 execve에게 넘길 정제된 필드 -> 리스트를 이차원 배열로 만들기)
	- [x] exit_status를 어떻게 처리해야 할까? 
		- &&, || 연산자는 전에 프로세스의 실행결과를 받아서 다음 명령을 실행할지 말지 결정한다.
- [ ] 시그널처리 (ctrl C, ctrl D...)
- [ ] 빌트인

### 2022.11.30(수) (Day 16)
- [X] execute logic
	- [X] execute 로직 
		- [X] 1. 왜 트리를 썼는가?
		- [X] 2. ||, &&, () 생각해보기
			-> command1 && command2 : command2 execute if and only if command1 
			echo hello || echo hello | wc && (echo "hello subshell" || grep "h" || cat -e) | wc
		- [X] 3. 서브쉘 생각해보기
	- [X] 매번 필드를 실행하기 전에 리다이렉션 하고 -> 리다이렉션을 부모가 아닌 자식에서 한다
	- [X] 쿼트 없애주고, 정제된 field(따옴표 없고, 리다이렉션없고 리다이렉션 피연산자 없고) -> expand하고 쿼트 제거

### 2022.11.29(화) (Day 15)
- [X] check_redirection_error
- [ ] execute logic 고민

### 2022.11.17~18(목, 금) (Day 13, 14)
- [X] expand 
	- [X] getenv
	- [X] logic 완성
- [X] parsing 끝
- [X] leaks 잡기
- [ ] 25줄 이상인 함수 쪼개기
- [X] closedir 해줄 것!
- [ ] test make하면 libft 갈아끼워야함.
- [X] expand dollar case $?

### 2022.11.16(수) (Day 12)
- [x] expand
	- [x] 1. 환경변수 => 어떻게 담고 다닐 것인지 
	- [x] 2. wildcard
	- [x] opendir, readdir, closedir
	- [ ] getenv
- [ ] redirect
- [ ] 중복 연산자가 있는지(syntax error)
	<<< infile echo | grep
	echo "<" < infile
	echo "<" < infile
	// 
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
dfsdf