syntax on
set number
set secure
set exrc

set expandtab
set tabstop=3
set softtabstop=3
set shiftwidth=3
set noswapfile
set smarttab
set smartindent
set t_C0=256

"mapper
nnoremap <C-Left> :tabprevious<CR>                                                                         
nnoremap <C-Right> :tabnext<CR>
nnoremap <C-o> <c-w>gf
map <C-n> :NERDTreeToggle<CR>


" Specify a directory for plugins
" - For Neovim: stdpath('data') . '/plugged'
" - Avoid using standard Vim directory names like 'plugin'
set nocompatible
call plug#begin('~/.vim/plugged')

Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }

Plug 'vim-airline/vim-airline'

Plug 'sheerun/vim-polyglot'

" Use release branch (recommend)
Plug 'neoclide/coc.nvim', {'branch': 'release'}

Plug 'jackguo380/vim-lsp-cxx-highlight'

"colorscheme
Plug 'joshdick/onedark.vim'
Plug 'tomasr/molokai'
Plug 'morhetz/gruvbox'

"git
Plug 'tpope/vim-fugitive'

call plug#end()



"AIRLINE_SETTINGS 
let g:airline#extensions#tabline#enabled = 1
let g:airline_powerline_fonts = 1
let g:airline#extensions#hunks#enabled=0
let g:airline#extensions#branch#enabled=1
let g:airline#extensions#tabline#enabled=1
let g:airline#extensions#tabline#show_buffers=0

if !exists('g:airline_symbols')
    let g:airline_symbols = {}
endif

let g:airline_theme='onedark'
"highlight LspCxxHlSymField guifg=#E06C75
"highlight LspCxxHlSymNamespace guifg=#E06C75

" unicode symbols
let g:airline_left_sep = '»'
let g:airline_left_sep = '▶'
let g:airline_right_sep = '«'
let g:airline_right_sep = '◀'
let g:airline_symbols.linenr = '␊'
let g:airline_symbols.linenr = '␤'
let g:airline_symbols.linenr = '¶'
let g:airline_symbols.branch = '⎇'
let g:airline_symbols.paste = 'ρ'
let g:airline_symbols.paste = 'Þ'
let g:airline_symbols.paste = '∥'
let g:airline_symbols.whitespace = 'Ξ'

" airline symbols
let g:airline_left_sep = ''
let g:airline_left_alt_sep = ''
let g:airline_right_sep = ''
let g:airline_right_alt_sep = ''
let g:airline_symbols.branch = ''
let g:airline_symbols.readonly = ''
let g:airline_symbols.linenr = 'Ln'

call airline#parts#define_raw('liner', ' %l:%c')
call airline#parts#define_accent('liner', 'bold')
let g:airline_section_z = airline#section#create(['%2p%%', 'liner'])


"COLOR_SCHEME
colorscheme onedark
set background=dark
let g:onedark_termcolors=16

if (empty($TMUX))
  if (has("nvim"))
    let $NVIM_TUI_ENABLE_TRUE_COLOR=1
  endif
  if (has("termguicolors"))
    set termguicolors
  endif
endif



"COC_NVIM
let g:coc_disable_startup_warning = 1

