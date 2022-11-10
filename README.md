# Minishell
### minishell 구조

1. read input
2. Analysis input
	- a. parentheses & quote check(내일 만들기)
	- b. tokenize & expand(환경 변수 와일드 카드 확장)
	- c. syntax check (pipe 다음에 리다이렉션 기호 or pipe 다음 인자가 없거나)
	- d. parse
3. execute
	- a. traverse tree

오늘의 할일
### 2022.11.04
- [X] assert, test unit 구현
- [X] quote 짝 확인

### 2022.11.07
- [X] 예외 처리
	- [X] bool	is_pair_bracket(const char *line)
	- [X] bool	is_correct_pair(const char *line)
- [ ] 토큰화
- [ ] 환경변수 확장 (getenv, opendir, readdir)
- [ ] 함수 공부해!!!!!!
	- [X] wait, waitpid, wait3, wait4
	- [ ] getcwd, chdir
	- [ ] stat, lstat, fstat
	- [ ] opendir, readdir, closedir
	- [ ] isatty, ttyname, ttyslot, ioctl
	- [ ] getenv
	- [ ] tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, togoto, tputs

### 2022.11.11
- [ ] 토큰화
	- [ ] is_bracket
	- [ ] read_bracket_content
	- [ ] is_dollor
	- [ ] expand(), 환경변수 확장 (getenv, opendir, readdir)
- 이거 다 하면 pa
sing 끝!

남은 일:
1. parsing (50%)
2. 토큰화해서 list로 만들기
3. tree 안에 list 담기
4. pipe 연결해서 cmd 구현 (echo -> built-in 구현)
5. signal 처리 (exit status -> `ctrl+d`, `ctrl+c`, `ctrl+\`)