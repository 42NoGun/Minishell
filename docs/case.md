### 케이스 정리
1. $ > pwd || ls
	- output: pwd

2. $ > pwd || ls && ls
	- output: ls

3. $ > pwd || (ls && ls)
	- output: pwd

4. ls&&ls
5. ls < |ls > out 
   - 뒤에 명령어도 실행되지 않음.

6. echo "str | " echo  " "| cat -e
	- output: str |  echo  $
7. echo "hello" || << ls : heredoc일 때는 || 무시한다.
	- 
8. grep "M" << ls |
	-
9. grep "M" << ls > out 
	- out에 담김
10. grep "M" << ls | >> out
	- out에 담기지 않음
11. echo '$fortytwo "axs"' "ahah"
	- $fortytwo "axs" ahah
	- ' '를 토큰에 담을 필요가 있나?
12.  grep "hello" && grep "h" << mks
13. (ls | ls && (ls && ls | ls)) || ls  >> filepath
14. (ls | echo "ls)"
15. echo "hel"lo""
16. "$h'$j'"'$h'$h
	-> hello''$hhello
17. echo "$h'$h'"'$h'$h
	-> hello'hello'$hhell
18. export a='a' && echo $?
- bash기준, 확장 이전 명령 기준

19. 파일이 없는 
19. echo $HOME "$"HOME "$HOME" $''HOME $""HOME $HO""ME $"HOME"
- mingylee case
20. grep "hello" < 1 < 2 < 3
21. cat << hello1 < infile << hello2 | cat << hello3

22. echo helloda | grep hello < infile 
-  infile에서  읽어어옴
23. (grep hello) < infile
24. (echo hello) <infile | grep "hello" < infile

25. echo 1 && echo 2 | cat > out && echo

### tokenize test
1. $ <<ls > pwd || ls 
2. $ > pwd || ls && ls
3. ls&&ls
4. exporta='a'&&echo$?
5. grep "hello" && grep "h" <<mks
6. echo "str | " echo  " "| cat -e
7. echo "str||"echo  " "|cat -e

### syntax error
`echo()` => 이건 무조건 syntax error, 만약 prev_str=""이 아닌데 괄호가 들어온다면 바로 sytax error로 판단  
`echo ()` => tokenize 해서 토큰으로 만들어놓고, 리스트 순회할 때 우선순위로 봤을 때 echo도 우선순위도 3, ()도 3이니, 우선 순위가 겹침으로 sytax error

display line
display *line
display prev_st

### 트리 왜 썼나?
```bash
$ echo a && echo b > a              // b
$ (echo a && echo b) > a            // a\nb
```
- 결국 괄호 깊이에 대한 우선순위를 처리하려면 그 깊이를 처리할 수 있는 `트리 로직`이나 `서브쉘 로직`이 필요한데, 우리는 서브쉘 로직이 있기 때문에 자연스럽게 깊이 처리가 가능하다. 우리 같은 경우에는 트리로 별도의 로직을 만들 필요는 없었다.
- 트리 사용하는 이유는 보통 부모가 subshell을 만들 때 처리 흐름이 있으니 부모에서 처리하기 쉽게 트리를 사용함 => lalr

### syntax error로 볼껀지 command error
- $HOME/foo -> 실행되게 처리
- echo {$PATH}  -> print {$PATH} : 중괄호는 문자로 보고 $PATH확장 닫는 중괄호 문자로 봄.
- echo ($PATH) 	-> syntax error : shell function 에러, 우선순위 3이 연속 나왔을 때 따라오는 토큰이 괄호로 시작하면 syntax error로 본다
- echo hello | (grep "h) : subshell
- echo $PATH -> 확장
- echo $(hello) -> (hello)를 환경변수로 본다.

- echo $(grep hello) -> (grep hello)를 환경변수로 본다.
- $(grep hello) -> (grep hello)를 환경변수로 본다. (쉘에서 다름)

- echo ($grep hello) -> 우선순위 3 연속
- echo $(grep hello) hi -> (grep hello)를 환경변수로 보고 hi
- echo (grep hello)
=> operator 옆에 괄호가 있으면 OK, 아니면 syntax error (token화 다 한 다음에 확인)

- ($) - 명령어 확장 -> 하지 않음
- $(()) -> 계산, 하지 않음
- echo `command`String으로 본다.
- <(list) : (list)를 파일로 본다.
- >(list) : (list)를 본다.
- < (list)
- < list
- 2>&1 : 2 >& 1 -> syntax error

- |&, |<, |> 등 리스트에 priority가 2번이지만, 정의되지 않은 operator일 때 syntax error 

- <, > 앞에 숫자가 있으면 

- <word
- 2<word
	- 2 < word 
- 2>word

- echo "2" > outfile

- echo "hello" 1>outfile 
- echo "hello" 2>outfile

- [n]<word
- [n]>[|]word
- [n]>>word
- &>word
- >&word
- &>>word
- [n]<&digit-
- <<< infile: < << infile, rediction이  여여러러개개 

- sleep 1 && echo hello && sleep 3 && (ls)
- (echo hello | cat ) > a | (sleep 3 && grep "hello" << limiter < a)

# 실제 쉘이랑 우리랑 다른 부분
- echo(HOME)
	- syntax error (bash)
	- command not found

# shell error message
- bash: syntax error near unexpected token `>'

# shell redirection 순서서
- echo hello 1 < infile | grep hello < infile
- : infile 의 hello grep
- echo hello 1 < infile | grep hello
- : echo의 결과물인 hello 1 grep

# echo hello 1 << limiter | grep hello << good
- broken pipe 
	- $ 1
	- $ 2
	- $ 3
	- limiter
	- good

### Syntax에러로 볼 것
- >&, >|, |&, <&
- |||, >>>, <<<
- echo (word), echo ($word), (world) echo(e)
- 짝 안맞는 괄호, 쿼트
- <, |, > 처음 마지막

- echo hello < infile  : 통째로 트리에 넣어야함.
	- <, >, >> 2번으로.
- > outfile echo hello 
- echo hello > outfile 
	- 즉 -먼저 찾아야 한다.

- 리다이렉션 + 히어독 기호 뒤에 파일 없는 경우

### expand()
- 트리 순회 (트리에 있는 필드를 순회) -> 토큰
	
1. find metacharacter for expansion in field : $, *
	except : `''$PATH''[o], '$PATH'[X], '''$PATH'''[X], ''''$PATH''''[O]`
    except : `"'$PATH'"`
2. if $, do env expand, `export a="*"; ls $a`의 결과물이 `ls *`의 결과물과 동일
3. if *, do filename expand
- 로직
	- 작은 따옴표 반환 문자열에 합치고, 현재 문자 밀어주고
	- 큰 따옴표 반환 문자열에 합치고, 현재 문자 밀어주고
	- 따옴표 없는 문자열에 합치고, 현재 문자 밀어주고
### 트리  
- 내가 파이프고 왼쪽 자식이나 오른쪽 자식 둘 중에 한명이 없다면 에러

### 쉘이 결국 모든 문자열을 파씽해서 프로그램(echo 등)에게 전달해준다.
```c
int main(int argc, char *argv[])
{
	char *str[3];
	str[0] = "/bin/echo";
	str[1] = "\"Hello'\"\"'$PATHHello\"";
	str[2] = NULL;

	execve("/bin/echo", str, NULL);
}
```
### command list의 구분
echo 1 || echo 2 | echo 3 | cat echo 5 echo 6 && echo 2

unset HOME 후 
cd ~
cd $HOME

> out
< in 
아무것도 없을 때 실행하면 세그폴트 나면 안됨