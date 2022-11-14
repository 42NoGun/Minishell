# BASH  매뉴얼 정리

## 용어 정의

### built in
- 파일시스템 어딘가에서 실행가능한 파일이 아니라 쉘 자체에 의해 내부적으로 구현되어 있는 명령어.  
### control operator
- 제어 기능을 수행하는 토큰.
- ||, &&, &, ;, ;;, ;&, ;;&, |, |&, (, )
### exit status
- 명령이 호출자에게 반환한 값, 8비트로 제한되어 있어 255까지 표현됨.  
### metacharacter
- 따옴표에 쌓여 있지 않을 때, 단어를 구분하는데 사용되는 문자.
- |, &, ;, (, ), <, >  
### field
- 쉘 확장의 결과로 만들어진 텍스트. 확장 이후 명령어를 실행할 때, field는 명령어 이름과 인자로 사용 됨.  
### operator
- control operator or redirection operator.
- operator는 최소 하나이상의 따옴표로 둘러 쌓이지 않는 metacharacter를 포함한다.  
### token
- 쉘에 의해 하나의 단위로 인식되는 연속된 문자열. word 혹은 operator 
### word
- 쉘에 의해 하나의 단위로 취급되는 연속된 문자열. word는 따옴표로 둘러쌓인 metacharacter를 포함하지 않음.

## 쉘의 syntax(구문)
- syntax : 문법, 구조 또는 언어 문장 내에 있는 구성요소의 순서
### 쉘의 동작 과정
1. 파일, -c 옵션적용 조건, user's terminal로 부터 입력을 읽는다.
2. 입력을 quoting rule에 따라 word와 operator로 나눈다. 이러한 token은 metacharacter로 분리되어 진다. 이 단계에서 alias 확장이 이루어 진다.
3. 토큰을 simple command 와 compound command로 구문분석(parse) 한다.
	- simple command : echo a b c 와 같이 명령어와 공백으로 구분된 인자들로 구성되어 있음.
	- compound command : 쉘 프로그래밍 언어의 구조임. 
4. 쉘 확장을 수행하고, 확장된 토큰을 파일 이름 리스트, 명령어, 인자로 나눈다.
5. 필요한 리디렉션을 수행하고, 리디렉션 operator와 피연산자를 목록에서 제거한다.
6. 명령어를 실행한다.
7. 명령들이 완료될 때 까지 기다리고 명령들의 exit status를 수집 한다.  

### quoting
1. single quote
- 작은 따옴표안에 있는 각문자의 리터럴 값이 유지됨.
- 작은 따옴표안에 작은 따옴표가 올 수 없음.
2. double quote
- 큰 따옴표안에 있는 각 문자의 리터럴 값이 유지 되지만 $는 제외한다.
- 큰 따옴표안에 있는 $는 특별한 의미를 유지 한다.(shell expansion)
- 큰 따옴표안에 있는 *는 특별한 의미를 가진다.(shell parameter expansion : shell expansion 중 일부)
3. Locale-Specific Translation
- $"hello, world" 와 같이 큰따옴표 앞에 \$가 있을 때 string은 현재 locale에 맞게 변환된다.
- 해당 예시도 minishell의 구현 요구사항에는 없음. 예) $"PATH" 

### shell command
- simple command
	- 공백으로 구분된 연속적인 word이고, control operator에 의해 절단된다 (다른 simple command와 control operator에 의해 구분된다는 뜻 같음)
	- 첫 word는 명령어 이고 나머지는 명령어의 인자이다.
	- return status는 posix 1003.1 waitpid함수 에서 제공하는 exit status이고, signal n에 의해 종료 된다면 128 + n의 값을 갖는다. 

### shell parameter
-  

### shell expansion
- 확장에는 여러 종류들이 있고 minishell 과제에서 요구하는 확장은 parameter and variable expansion 안에서도 환경 변수의 확장에 대해서만 구현할 것을 명시하고 있다.
- \*는 filename expansion에 속한다