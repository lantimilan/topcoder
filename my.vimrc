syntax on
set mouse=a
set showmatch
set ruler
set history=1000
set wildmenu
set list
set listchars=tab:,.,trail:.,extends:#,nbsp:. " Highlight problematic whitespace

" Formatting {
    set nowrap
    set autoindent
    set shiftwidth=4
    set expandtab
    set tabstop=4
    set softtabstop=4
    set pastetoggle=<F12>
    autocmd FileType c,cpp,java,php,javascript,python,twig,xml,yml autocmd BufWritePre <buffer> :call setline(1,map(getline(1,"$"),'substitute(v:val,"\\s\\+$","","")'))
    autocmd BufNewFile,BufRead *.html.twig set filetype=html.twig
" }

" Ctags {
    set tags=./tags;/,~/.vimtags
" }

" AutoCloseTag {
" Make it so AutoCloseTag works for xml and xhtml files as well
    au FileType xhtml,xml ru ftplugin/html/autoclosetag.vim
    nmap <Leader>ac <Plug>ToggleAutoCloseMappings
" }
