# Minishell
### minishell 구조

1. read input
2. Analysis input
	a. parentheses & quote check(내일 만들기)
	b. tokenize & expand(환경 변수 와일드 카드 확장)
	c. syntax check (pipe 다음에 리다이렉션 기호 or pipe 다음 인자가 없거나)
	d. parse
3. execute
	a. traverse tree

오늘의 할일
### 2022.11.04
- [X] assert, test unit 구현
- [X] quote 짝 확인

### 2022.11.07
- [ ] 예외 처리
	- [ ] bool	is_pair_bracket(const char *line)
	- [ ] bool	is_correct_pair(const char *line)
- [ ] 토큰화
- [ ] 환경변수 확장 (getenv, opendir, readdir)
- [ ] 함수 공부해!!!!!!
	- [ ] wait, waitpid, wait3, wait4
	- [ ] getcwd, chdir
	- [ ] stat, lstat, fstat
	- [ ] opendir, readdir, closedir
	- [ ] isatty, ttyname, ttyslot, ioctl
	- [ ] getenv
	- [ ] tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, togoto, tputs