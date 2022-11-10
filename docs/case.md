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
