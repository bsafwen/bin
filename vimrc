au BufRead,BufNewFile *.tpl set filetype=smarty 
filetype on
syntax on
set number
set nohlsearch
set shiftwidth=4
set softtabstop=4
" set expandtab
set ai
set si
set nrformats=
set clipboard=unnamedplus
execute pathogen#infect()
syntax enable
filetype plugin indent on
" Put plugins and dictionaries in this dir (also on Windows)
 let vimDir = '$HOME/.vim'
 let &runtimepath.=','.vimDir

" Keep undo history across sessions by storing it in a file
 if has('persistent_undo')
     let myUndoDir = expand(vimDir . '/undodir')
     " Create dirs
     call system('mkdir ' . vimDir)
     call system('mkdir ' . myUndoDir)
     let &undodir = myUndoDir
     set undofile
 endif
 set statusline+=%#warningmsg#
 set statusline+=%{SyntasticStatuslineFlag()}
 set statusline+=%*

 let g:syntastic_always_populate_loc_list = 1
 let g:syntastic_auto_loc_list = 1
 let g:syntastic_check_on_open = 1
 let g:syntastic_check_on_wq = 1
 let g:syntastic_mode_map = { 'mode': 'passive', 'active_filetypes': [],'passive_filetypes': [] }
 nnoremap <C-w>E :SyntasticCheck<CR> :SyntasticToggleMode<CR>
 nmap <CR> o<Esc>
