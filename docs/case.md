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

19. echo $HOME "$"HOME "$HOME" $''HOME $""HOME $HO""ME $"HOME"
- mingylee case

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
display prev_str\