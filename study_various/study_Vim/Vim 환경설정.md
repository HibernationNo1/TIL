# Vim 환경설정

## 설정 방법

_vimrc file의 값을 변경하면 해당 환경설정이 영구적으로 vim editor에 저장된다.

### Window

_vimrc file은 vim의 .exe file이 있는 위치에 존재한다.

```
$ cd ~/vim
$ vi _vimrc
```







### Linux

우분투의 경우 `.vimrc` file을 만들어줘야 한다. 위치는 home directory이다.

```
$ vi ~/.vimrc
```





## 설정 문법

```
if has("syntax")
    syntax on
endif
```

> syntax 적용



```
set nu
```

> show line number



```
set autoindent
```

자동으로 들여쓰기 설정

> ```
> set cindent
> ```
>
> C언어 자동 들여쓰기
>
> 
>
> ```
> set shiftwidth=4
> ```
>
> 자동 들여쓰기 너비 설정 
>
> 
>
> ```
> set smartindent
> ```
>
> 문법에 맞게 자동으로 indent를 넣어줌 (여는 괄호 다음줄에 알맞는 들여쓰기)



```
set autowrite
```

> 다른 파일로 넘어갈 때 자동 저장



```
set mouse=a
```

> 마우스를 클릭하는 곳으로 커서 옮김



```
set incsearch
```

> 검색시 단어 전체를 입력하지 않아도, 입력된 글자까지 순차적으로 검색한다



```
set title
```

> 상단에 file name을 표시



```
set guifont=consolas:h11
```

> 글꼴 설정 . font : consolas, width = 11
>
> window에서만 가능



**최종 내 설정**

```
if has("syntax")
    syntax on
endif
set autowrite
set autoindent
set shiftwidth=4
set smartindent
set cindent
set nu
set title
set incsearch
set mouse=a
set autowrite
set guifont=consolas:h11
colorscheme dark_plus
```





#### colorscheme

- vim editer에서 `:colorscheme + Ctrl+d` 를 입력하면 현재 설치되어 있는 color scheme의 list를 볼 수 있다. 

- colorscheme example Reference : http://vimcolors.com/

  > 여기서 마음에 드는 colorscheme 의 소스를 다운받아 vim/colors 에 .vim file로 저장

- 내가 사용하는 colorscheme의 Reference : https://github.com/dunstontc/vim-vscode-theme/blob/master/colors/dark_plus.vim (License 무료 허가)

  > name : dark_plus



- cheme 적용 예시문

  ```
  require 'active_support'
  
   module VimColors
     class RubyExample
       CONSTANT = /^[0-9]+ regex awesomes$/
  
       attr_reader :colorscheme
  
       # TODO: Bacon ipsum dolor sit amet
       def initialize(attributes = {})
         @colorscheme = attributes[:colorscheme]
       end
  
       def self.examples
         # Bacon ipsum dolor sit amet
         ['string', :symbol, true, false, nil, 99.9, 1..2].each do |value|
           puts "it appears that #{value.inspect} is a #{value.class}"
         end
  
         {:key1 => :value1, key2: 'value2'}.each do |key, value|
           puts "the #{key.inspect} key has a value of #{value.inspect}"
         end
  
          %w[One Two Three].each { |number| puts number }
       end
  
       private
  
       def heredoc_example
        <<-SQL
          SELECT *
          FROM colorschemes
          WHERE background = 'dark'
        SQL
      end
    end
  end
  ```

  



**설정 방법**

##### Window 

1. vim을 다운받아서 사용하고 있다면 vim/colors 안에 colorscheme으로 적용할 수 있는 .vim file들이 다 있다.

   ```
   $ cd ~/vim/vim82/colors
   ```

   이곳에 `dark_plus.vim` 이라는 colorscheme 소스 파일을 저장한다.

2. ~/vim 에는 _vimrc 파일이 있다.

   vim/colors directory에 원하는 colorscheme을 다운받은 후 _vimrc 파일에 아래 문구를 써넣어 준다

   ```
   colorscheme dark_plus
   ```

   > dark_plus 이라는 colorscheme을 설정



##### Linux

vim colors directory의 위치

```
/usr/share/vim/vim81/colors
```

이곳에 `dark_plus.vim` 이라는 colorscheme 소스 파일을 저장한다.



`.vimrc` 파일에 `colorscheme dark_plus` 를 남긴다

```
$ vi ~/.vimrc
```



