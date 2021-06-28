# Plugin

Vim 의 UI를 결정지어주는 Plug를 가져다 사용하기 위해 설치하는 모듈

vim 플러그인 패키지는 `Vundle`, `vim-plug`, `pathogen` 가 있다.

### Vundle

Reference : https://github.com/VundleVim/Vundle.vim



#### Sep up Vundle

> Linux라면 
>
> ```
> sudo apt-get install vim git
> ```
>
> 부터 해야됨

1. clone

   ```
   git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
   ```

   `vim` directory에 bundle이라는 directory를 만든 후, 그 안에서 git clone을 통해 package를 가져온다

2. set `.vimrc`

   ```
   
   
   set nocompatible              " be iMproved, required
   filetype off                  " required
   
   set rtp+=~/.vim/bundle/Vundle.vim 
   Vundle을 포함하도록 런타임 경로 설정 및 초기화
   
   "--------------------------------------------Plugin 시작
   call vundle#begin()
   
   Plugin 'VundleVim/Vundle.vim'  " 최초 vundle을 설정
   
   " 여기 부분부터 설치할 플러그인들을 작성해주면 된다.
   " ex) Plugin 'scrooloose/nerdtree'
   
   
   call vundle#end()            " required
   filetype plugin indent on    " required
   "---------------------------------------------Plugin 종료
   ```

   `.vimrc` 에 원하는 plugin을 작성 후 `:w` 로 저장, `:PluginInstall` 을 통해 plugin을 전부 install한다.

   > **plugin 명령어**
   >
   > - `:PluginInstall` : plugin을 전부 install
   > - `:PluginClean` : 사용하지 않을 plugin을 목록에서 삭제해준 후 실행하는 명령어
   > - `:PluginList` : 설치된 plugin을 보여주는 명령어

   





#### Plugin 종류

##### for Vim

- ```
  Plugin 'vim-airline/vim-airline' 
  Plugin 'vim-airline/vim-airline-themes'
  ```
  
  > " Vim 상태바 개선해주는 플러그인
  >
  > `let g:airline_powerline_fonts = 1` : 상태바를 이쁘게 만들어 줌
  >
  > `let g:airline_theme = 'codedark'` : 상대바 테마 설정
  
- ```
  Plugin 'airblade/vim-gitgutter'   
  ```

  >" Git으로 변경된 부분 표시해주는 플러그인

- ```
  Plugin 'vim-syntastic/syntastic'   
  ```

  > " 문법 체크해주는 플러그인

- ```
  Plugin 'ctrlpvim/ctrlp.vim'   
  ```

  >" 파일 찾기 플러그인

- ```
  Plugin 'tomasiser/vim-code-dark'
  ```

  > " codedark  colorscheme 플러그인
  
- ```
  Plugin 'tomasiser/vim-code-dark'
  ```

  >  " colorscheme 플러그인
  >
  > `colorscheme dark_plus` 사용

- 



##### for python

- ```
  Plugin 'vim-python/python-syntax'
  ```

  > " pyhon syntax 적용하는 Plugin
  >
  > `let g:python_highlight_all = 1`

- ```
  Plugin 'davidhalter/jedi-vim' 
  ```

  > " python 자동완성 Plugin
  >
  > `let g:jedi#show_call_signatures=0       " 자세히 설명하는 창을 보여준다 1=활성화, 0=비>활성화`
  >
  > `let g:jedi#popup_select_first=0       " 자동완성시 자동팝업 등장 x`
  >
  > `let g:jedi#force_py_version=3           " 자동완성 3 = python3 , 2 = python2`

- ```
  Plugin 'hynek/vim-python-pep8-indent'
  ```

  > " python 자동 들여쓰기 Plugin
  >
  > `filetype plugin indent on               " python 자동 들여쓰기 on`

- ```
  Plugin 'nvie/vim-flake8' 
  ```

  >" python 문법 검사 plugin
  >
  >`" let g:syntastic_python_checkers=['flake8']        " ↓ 실행시 현재줄 주석 해제필요   `
  >
  >`" let g:syntastic_python_flake8_args='--ignore='    " 무시하고자 하는 errorcode`         



### 내 설정

```
" Vim with all enhancements
source $VIMRUNTIME/vimrc_example.vim

" Use the internal diff if available.
" Otherwise use the special 'diffexpr' for Windows.
if &diffopt !~# 'internal'
  set diffexpr=MyDiff()
endif
function MyDiff()
  let opt = '-a --binary '
  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
  let arg1 = v:fname_in
  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
  let arg1 = substitute(arg1, '!', '\!', 'g')
  let arg2 = v:fname_new
  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
  let arg2 = substitute(arg2, '!', '\!', 'g')
  let arg3 = v:fname_out
  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
  let arg3 = substitute(arg3, '!', '\!', 'g')
  if $VIMRUNTIME =~ ' '
    if &sh =~ '\<cmd'
      if empty(&shellxquote)
        let l:shxq_sav = ''
        set shellxquote&
      endif
      let cmd = '"' . $VIMRUNTIME . '\diff"'
    else
      let cmd = substitute($VIMRUNTIME, ' ', '" ', '') . '\diff"'
    endif
  else
    let cmd = $VIMRUNTIME . '\diff'
  endif
  let cmd = substitute(cmd, '!', '\!', 'g')
  silent execute '!' . cmd . ' ' . opt . arg1 . ' ' . arg2 . ' > ' . arg3
  if exists('l:shxq_sav')
    let &shellxquote=l:shxq_sav
  endif
endfunction

"-----------------------------------vim 기본 설정 
" syntax on  " 구문 강조 (colorscheme에 의해 다시 정의됨)
filetype on
set encoding=utf-8  " 한글 깨짐 방지
set autowrite " 다른 파일로 넘어갈 때 자동 저장
set autoindent " 자동으로 들여쓰기 설정
set shiftwidth=4 " 들여쓰기 너비 설정 
set smartindent
set nu " show line number
set incsearch " 검색시 입력된 글자까지 순차적으로 검색한다
set mouse=a " 마우스를 클릭하는 곳으로 커서 옮김
set guifont=consolas:h11 " 글꼴 설정
"-----------------------------------vim 기본 설정 끝

"----------------------------------- plugin 기본 설정

set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

"----------- plugin for vim

Plugin 'vim-airline/vim-airline' 
Plugin 'vim-airline/vim-airline-themes'
" Vim 상태바 개선해주는 플러그인
	
Plugin 'airblade/vim-gitgutter'     
" Git으로 변경된 부분 표시해주는 플러그인

Plugin 'vim-syntastic/syntastic'    
" 문법 체크해주는 플러그인

Plugin 'ctrlpvim/ctrlp.vim'         
" 파일 찾기 플러그인

Plugin 'tomasiser/vim-code-dark'
" colorscheme Plugin (code-dark)


"----------- Plugin for python
Plugin 'vim-python/python-syntax'
" pyhon syntax 적용하는 Plugin

Plugin 'HibernationNo1/vim-darkplus-python3'

Plugin 'hynek/vim-python-pep8-indent'   
" python 자동 들여쓰기 Plugin

Plugin 'nvie/vim-flake8'                
" python 문법 검사 plugin
" let g:syntastic_python_checkers=['flake8']        " ↓ 실행시 현재줄 주석 해제필요    
" let g:syntastic_python_flake8_args='--ignore='    " 무시하고자 하는 errorcode


" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
"-----------------------------------plugin 설정 끝

"-----------plugin option
colorscheme dark_plus_python		" colorscheme 설정
filetype plugin indent on     	" python 자동 들여쓰기 on

let g:airline_powerline_fonts = 1 
let g:airline_theme = 'codedark' " airline theme

let g:python_highlight_class_vars = 1
let g:python_highlight_builtins = 1
let g:python_highlight_func_calls = 1
let g:python_highlight_string_format = 1
```

